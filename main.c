/*
2017 by Adam Wêglarczyk
p.33_nRF24L01_LCDi2c_ATM328P
*/
/* Define UART buad rate here */
#define UART_BAUD_RATE      9600

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "config.h"

#include "lcdpcf8574_PL/lcdpcf8574_PL.h"
//include nrf24l01
#include "nrf24l01/nrf24l01.h"

#include "netlayer/netlayer.h"
#include <avr/eeprom.h>

//ds18b20
#include "ds18b20/ds18b20.h"

//#include "uart.h"
//#include "komunikacja/komunikacja.h"

#include <avr/wdt.h> // watchdog do resetu softwarowego

//#include "ESP8266/esp8266.h"

//*****************************************************************
//							zmienne
//*****************************************************************
//





//uint8_t restart=1;
uint8_t i = 90;
uint8_t moj_adres,obcy_adres,odb,odt;
uint8_t *my_eeprom_byte=0x00;
char znak2[4];
char *fwv = "0.05B";

uint16_t licznik,licznik_k;

//wysylka danych
uint8_t bufferin[6];
uint8_t bufferout[2];

//temperatura
uint8_t temp1,temp2; //aktualna temperatura
uint8_t temp1_d,temp2_d; // nastawa temperatury dzien
uint8_t temp1_n,temp2_n; // nastawa temperatury noc
uint8_t histereza; // histereza
uint8_t czy_noc;//2-off 1-noc 0-dzien
uint8_t czy_on;// 0-off 1-on
uint16_t temp;

//rejestr klawiatury
uint8_t keyb[4];

/* W tablicy zapisywane bêd¹ dane odczytane z uk³adu ds18b20 */
unsigned char ds18b20_pad[9];
unsigned char numer_seryjny[8];

extern uint8_t rejestr[5];// posiada podstawowy wpis w funkcji netlayer.c


//********************************************************************
//								main program
//********************************************************************
int main(void)
{
//**************************** function heads ********************
void Timer1Init(void);
void eeprom(void);
void inout_init(void);
void ekran_powitalny(void);
void wyswietl_LCD (void);
void wyswietl_LCD_test (void);
void klawiatura(void);
//void wyswietl_RS (void);
void odczyt_temp(void);
void czy_wlaczyc(void);
//****************************************************************



//sekcja NRF24L01
//sending buffer addresses
uint8_t addrtx0[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP0;
//init nrf24l01
nrf24l01_init();
nrf24l01_settxaddr(addrtx0);

//uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );//- odchaczyc jak biblioteki uart beda podpiete
//init interrupt
sei();// zezwol na przerwania UART

//setup buffer - czyszczenie buffora - sprawdzic czy przydatne
//for(i=0; i<sizeof(bufferin); i++)
//bufferin[i] = 0;



//******************* main loop ************************************
rejestr[0]=0;
Timer1Init();
eeprom();
inout_init();
ekran_powitalny();
//wyslij na uart - nieprzydatne bo bedzie tam esp8266
if (odb==2)//off
     {
		//uart_puts("DEV RX READY\r\n");//- odchaczyc jak biblioteki uart beda podpiete
     }else{
    	//uart_puts("DEV TX READY\r\n");//- odchaczyc jak biblioteki uart beda podpiete
     }


//bufferout[0]=0x61;
//bufferout[1]=0x63;
//if (odb==1) wyslij(moj_adres,obcy_adres,bufferout);

	while(1)
    {
		odczyt_temp();
		wyswietl_LCD();
		//klawiatura();
		//esp8266_ini();
		czy_wlaczyc();

    	 if (odb==2)
    	      {
    		 	//ODBIORNIK <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    	       	//odt=odczytaj(moj_adres,bufferin);
   	       		//odt=odbierz_komende();
    	      }else
    	      {
    	    	//NADAJNIK >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    	    	//bufferout[0]=i;
    	    	//bufferout[1]=i+1;
    	    	//wyslij(moj_adres,obcy_adres,bufferout);


    	      }//end IF odb-nad ======================================

    }//while - koniec petli glownej

}//main - koniec programu #########################################################################################




//********************************************************************
//								FUNCTIONS
//********************************************************************

void czy_wlaczyc(void)
{

//dzien
if ( ( (temp1<temp1_d) & (czy_noc==0) ) | (( (temp1==temp1_d) & (temp2_d<(temp2_d-histereza) ) ) & (czy_noc==0)))
	{
	czy_on=1;
	}

if ( ( (temp1>temp1_d) & (czy_noc==0) ) | (( (temp1==temp1_d) & (temp2_d>(temp2_d+histereza) ) ) & (czy_noc==0)))
	{
	czy_on=0;
	}

//noc
if ( ( (temp1<temp1_d) & (czy_noc==1) ) | (( (temp1==temp1_d) & (temp2_d<(temp2_d-histereza) ) ) & (czy_noc==1)))
	{
	czy_on=1;
	}

if ( ( (temp1>temp1_d) & (czy_noc==1) ) | (( (temp1==temp1_d) & (temp2_d>(temp2_d+histereza) ) ) & (czy_noc==1)))
	{
	czy_on=0;
	}

if (czy_noc==2)//off
	{
	czy_on=0;
	}

}
void klawiatura(void){

	if (((BUTTON1_PIN & _BV(BUTTON1))==0))
	{
		licznik_k=0;
		while (((BUTTON1_PIN & _BV(BUTTON1))==0))
		{
			if (licznik_k==10)
			{
				//f1
				break;
			}
		}
	}
}

void odczyt_temp(void){
ds18b20_ConvertT();
_delay_ms(750);
cli();//wylacz przerwania
ds18b20_Read(ds18b20_pad);
sei();//wlacz przerwania
temp1 = ((ds18b20_pad[1] << 8) + ds18b20_pad[0])/16;//jednosci i dziesiatki dla LCD
temp2=ds18b20_pad[0] & 0b00001111; //dziesiate i setne dla LCD
temp2=temp2*6,25;
temp=((temp1*100)+temp2);//temperatura *100 dla przekaznika 24,54stopnia - 2454

}
void eeprom(void){
	//odczyt danych stalych z EEPROM
	moj_adres = eeprom_read_byte(my_eeprom_byte); // moja adres w bajcie 0 eeprom
	obcy_adres = eeprom_read_byte(my_eeprom_byte+1); // obcy adres w bajcie 1 eeprom
	odb = eeprom_read_byte(my_eeprom_byte+2);//0-odbiornik czy 1-nadajnik 2-off
	temp1_d = eeprom_read_byte(my_eeprom_byte+8);
	temp2_d = eeprom_read_byte(my_eeprom_byte+9);
	temp1_n = eeprom_read_byte(my_eeprom_byte+10);
	temp2_n = eeprom_read_byte(my_eeprom_byte+11);
	histereza = eeprom_read_byte(my_eeprom_byte+12);
}
void inout_init(void){

	//inicjalizacja portów
	//IN - wejscie
	BUTTON1_DDR &= (1<<BUTTON1); //input 1
	BUTTON1_PORT |= (1<<BUTTON1); //podciagnij do 1
	BUTTON2_DDR &= (1<<BUTTON2); //input 2
	BUTTON2_PORT |= (1<<BUTTON2); //podciagnij do 1
	BUTTON3_DDR &= (1<<BUTTON3); //input 1
	BUTTON3_PORT |= (1<<BUTTON3); //podciagnij do 1
	BUTTON4_DDR &= (1<<BUTTON4); //input 2
	BUTTON4_PORT |= (1<<BUTTON4); //podciagnij do 1

	//OUT - wyjcie
	LEDOUT_DDR |= (1<<LEDOUT); //output 1
	LEDOUT_DDR2 |= (1<<LEDOUT2); //output 2
	LEDOUT_DDR3 |= (1<<LEDOUT3); //output 3

	//inicjuj diody w stan off
	LEDOUT_PORT |= (1<<LEDOUT);//off - dioda podlaczona do Vcc on- jak podlacona do masy
	LEDOUT_PORT2 |= (1<<LEDOUT2);//off - dioda podlaczona do Vcc on- jak podlacona do masy
	LEDOUT_PORT3 |= (1<<LEDOUT3);//off - dioda podlaczona do Vcc on- jak podlacona do masy
	//LEDOUT_PORT &= ~(1<<LEDOUT); //off-jak podlaczona do masy
	//LEDOUT_PORT2 &= ~(1<<LEDOUT2);//off-jak podlaczona do masy
	//LEDOUT_PORT3 &= ~(1<<LEDOUT3);//off-jak podlaczona do masy

}

void ekran_powitalny(void){

	//init lcd - inicjalizacja LCD
	lcd_init(LCD_DISP_ON);

	//lcd go home
	lcd_home();
    //tytul
    lcd_led(0); //set led - wlaczenie podwietlania LCD
    lcd_clrscr();
    lcd_gotoxy(0, 0);
    lcd_puts_P("Sterownik Pieca");
    lcd_gotoxy(0, 1);
    lcd_puts_P("    ATMEGA328P");
    _delay_ms(500);

    lcd_gotoxy(0, 0);
    lcd_puts(fwv);
    if (odb==0)
      {
       	lcd_puts_P("  (odb)");
      }else{
       	lcd_puts_P("  (nad)");
      }

    lcd_gotoxy(0, 1);
    lcd_puts_P("                ");
    lcd_gotoxy(0, 1);
    lcd_puts_P("My=");
    itoa(moj_adres,znak2,10);
    lcd_puts(znak2);
    lcd_puts_P(" Rx=");
    itoa(obcy_adres,znak2,10);
    lcd_puts(znak2);
    _delay_ms(500);
    lcd_clrscr();

}

#define soft_reset()        \
do                          \
{                           \
    wdt_enable(WDTO_15MS);  \
    for(;;)                 \
    {                       \
    }                       \
} while(0)

void wyswietl_LCD (void)
					{
						//gorna linia
						lcd_gotoxy(0, 0);
						lcd_puts_P("T:");
						itoa(temp1,znak2,10);
	    	       		lcd_puts(znak2);
	    	       		lcd_puts_P(",");
	    	       		itoa(temp2,znak2,10);
	    	       		lcd_puts(znak2);
	    	       		lcd_puts_P(" C ");
	    	       		lcd_gotoxy(11, 0);
	    	       		lcd_puts_P("[");

	    	       		if (czy_on==1)
	    	       			{
	    	       				lcd_puts_P("X");
	    	       			}else
	    	       			{
	    	       				lcd_puts_P(" ");
	    	       			}

	    	       		lcd_puts_P("]");

	    	       		if (odb==0)
	    	       	      {
	    	       	       	lcd_puts_P("R");
	    	       	      }else{
	    	       	       	lcd_puts_P("S");
	    	       	      }

	    	       		if (czy_noc==1)
	    	       		{
	    	       			lcd_puts_P("N");
	    	       		}else
	    	       		{
	    	       			lcd_puts_P("D");
	    	       		}
	    	       		if (czy_noc==2)
	    	       		{
	    	       			lcd_puts_P(" ");
	    	       		}
	    	       		//dolna linia
	    	       		lcd_gotoxy(0, 1);
	    	       		lcd_puts_P("Td:");
	    	       		itoa(temp1_d,znak2,10);
	    	       		lcd_puts(znak2);
	    	       		lcd_puts_P(",");
	    	       		itoa(temp2_d,znak2,10);
	    	       		lcd_puts(znak2);
	    	       		lcd_puts_P("Tn:");
	    	       		itoa(temp1_n,znak2,10);
	    	       		lcd_puts(znak2);
	    	       		lcd_puts_P(",");
	    	       		itoa(temp2_n,znak2,10);
	    	       		lcd_puts(znak2);
					}

void wyswietl_LCD_test (void)
					{
						lcd_gotoxy(0, 0);

	    	       		lcd_puts_P("A:");
	    	       		itoa(bufferin[0],znak2,10);
	    	       		lcd_puts(znak2);

	    	       		lcd_puts_P(" B:");
	    	       		itoa(bufferin[1],znak2,10);
	    	       		lcd_puts(znak2);

	    	       		lcd_puts_P(" C:");
	    	       		itoa(bufferin[2],znak2,10);
	    	       		lcd_puts(znak2);

	    	       		lcd_puts_P("    ");

	    	       		lcd_gotoxy(0, 1);

	    	       		lcd_puts_P(" D:");
	    	       		itoa(bufferin[3],znak2,10);
	    	       		lcd_puts(znak2);

	    	       		lcd_puts_P(" E:");
	    	       		itoa(bufferin[4],znak2,10);
	    	       		lcd_puts(znak2);

	    	       		lcd_puts_P(" F:");
	    	       		itoa(bufferin[5],znak2,10);
	    	       		lcd_puts(znak2);

	    	       		lcd_puts_P("    ");
					}
/*- odchaczyc jak biblioteki uart beda podpiete
void wyswietl_RS (void)
{

	uart_puts("ramka:\r\n");

	uart_puts("skad:");
	itoa(bufferin[0],znak2,10);
	uart_puts(znak2);

	uart_puts(" dokad:");
	itoa(bufferin[1],znak2,10);
	uart_puts(znak2);

	uart_puts("\r\n");

	uart_puts("co1:");
	itoa(bufferin[2],znak2,10);
	uart_puts(znak2);

	uart_puts(" co2:");
	itoa(bufferin[3],znak2,10);
	uart_puts(znak2);

	uart_puts("\r\n");

	uart_puts("ctrl:");
	itoa(bufferin[4],znak2,10);
	uart_puts(znak2);

	uart_puts(" CRC:");
	itoa(bufferin[5],znak2,10);
	uart_puts(znak2);

	uart_puts("\r\n");

}
*/
//****************************************************************************************************
//przerwanie licznika
ISR(TIMER1_COMPA_vect)
{
cli();//wylacz przerwania

//zwieksz licznik - pracuje jak przerwanie co 1 ms
licznik++;
licznik_k++;

//klawiatura
if (licznik_k==50)
	{
		//sprawdzanie stanow klawiszy
		if (((BUTTON1_PIN & _BV(BUTTON1))==0))//day
			{
				keyb[0]=1;
				keyb[1]=0;
				keyb[2]=0;
			}
		if (((BUTTON2_PIN & _BV(BUTTON2))==0))//night
			{
				keyb[0]=0;
				keyb[1]=1;
				keyb[2]=0;
			}
		if (((BUTTON3_PIN & _BV(BUTTON3))==0))//off
			{
				keyb[0]=0;
				keyb[1]=0;
				keyb[2]=1;
			}
		if (((BUTTON4_PIN & _BV(BUTTON4))==0))//set
			{
				keyb[3]=1;
			}
		licznik_k=0;
	}


sei();//wlacz przerwania
}

//****************************************************************************************************
//inicjalizacja przerwania
void Timer1Init(void)
{
//blokada przerwan
cli();
// czyszczenie rejestrow przerwan
	TCCR1A = 0;
	TCCR1B = 0;


// set up timer with prescaler = 64 and CTC mode (tryb 4)
// u nas 8MHz /64 = 125000
TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);

// initialize counter
TCNT1 = 0;

// initialize compare value 125000 / 125 = 1000
OCR1A = 124;


// wlaczenie przerwan timera1
    TIMSK1 |= (1 << OCIE1A); //ATMEGA 8 i 32 TIMSK    ATMEGA328P TIMSK1

//wlaczenie przerwan
sei();
}
