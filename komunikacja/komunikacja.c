#include <avr/io.h>
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "komunikacja.h"
#include "../uart.h"
#include "../lcdpcf8574_PL/lcdpcf8574_PL.h"
#include <util/delay.h>
#include "../netlayer/netlayer.h"
#include "../config.h"

extern uint8_t rejestr[5];// posiada podstawowy wpis w funkcji netlayer.c

uint8_t odbierz_komende(void)
	{
	uint8_t i,f1,ret=0;
	char *fwv = "0.03B";
	char tresc[12];

	char znak[4];
	char *string_table[] =
	{
	    "AT\r\n",
	    "ATV\r\n",
	    "ATMODE?\r\n",
	    "ATTEMPd?\r\n",
	    "ATTEMPn?\r\n",
	    "ATHIS?\r\n",
	    "ATMODE="
	};
	if (uart_available()>0)
	 {
		_delay_ms(100);
		ret=100;


		//odczytaj komende z buffora
		for (i=0;i<=11;i++)
			{
			f1=uart_getc();
			if (echo==1) uart_putc(f1);
			tresc[i]=f1;
			if (f1==0x00) i=12;
			}

		for (i=0;i<8;i++)
			{
				if (strstr(tresc,string_table[i])!=0) ret=i+1;
			}

		switch(ret)
			{
				default:
				uart_puts("ERROR\r\n");
				break;

				case 1://OK
				uart_puts("OK\r\n");
				break;

				case 2://wyslij dane sys
				uart_puts("firmware ");
				uart_puts(fwv);
				uart_puts("\r\n");
				uart_puts("OK\r\n");
				break;

				case 3://wyslij tryb pracy
				uart_puts("mode ");
				itoa(rejestr[0],znak,10);
				uart_puts(znak);
				uart_puts("\r\n");
				uart_puts("OK\r\n");
				break;

				case 4://wyslij temp nadajnika
				uart_puts("temp_d 22,75\r\n");
				uart_puts("OK\r\n");
				break;

				case 5://wyslij temp nadajnika
				uart_puts("temp_n 20,25\r\n");
				uart_puts("OK\r\n");
				break;

				case 6://wyslij temp histerezy
				uart_puts("histereza 0,30\r\n");
				uart_puts("OK\r\n");
				break;

				case 7://wyslij temp nadajnika
				//checking for numbers
				if ((tresc[7]>47) & (tresc[7]<58))
					{

						//setting mode
						if (tresc[7]==48)
							{
								rejestr[0]=0;
								uart_puts("off\r\n");
							}
						if (tresc[7]==49)
							{
								rejestr[0]=1;
								uart_puts("day\r\n");
							}
						if (tresc[7]==50)
							{
								rejestr[0]=2;
								uart_puts("night\r\n");
							}

						uart_puts("OK\r\n");
					}else
					{
						uart_puts("ERROR\r\n");
					}
				break;
			}
	 }

	  return ret;
	}



//stare komendy do wykasowania
void odbierz(void)
{
	uint8_t f1,i;
	char f3;

	lcd_clrscr();
	lcd_gotoxy(0, 0);
	f1=uart_available();

	for (i=0;i<=f1;i++)
		{
		f3=uart_getc();
		_delay_ms(100);
		if (f3==0x0D) {
			NEW_LINE;
		}else{
			lcd_putc(f3);
			}
		}
	//lcd_puts(bufferin);
}

void odbierz_ciag(int dlugosc,char *tresc)
	{
	uint8_t i;

		while (uart_available()!=dlugosc)
				{

				}
		for(i=0;i<dlugosc;i++)
			{
			*(tresc+i)=uart_getc();
			}

	}

int oczekuj_ciag(const char *tresc)
	{
	uint8_t i,j=0,z=0;
	size_t dl;
	dl=strlen(tresc)-1;

		while (uart_available()!=dl)
				{

				}

		for(i=0;i<dl;i++)
			{
			if (*(tresc+i)==uart_getc()) j++;
			}

		if (j==dl) z=1;
		return z;
	}

void wyslij_SMS(char numer[],char tresc[])
{
	uart_puts("AT+CMGF=1\r");
	_delay_ms(1000);
	//odbierz();
	uart_flush();

	uart_puts("AT+CSCS=\"GSM\"\r");
	_delay_ms(1000);
	//odbierz();
	uart_flush();

	uart_puts("AT+CMGS=\"");
	uart_puts(numer);
	uart_puts("\"\r");
	_delay_ms(1000);
	//odbierz();
	uart_flush();

	uart_puts(tresc);
	uart_putc(0x0D);
	_delay_ms(1000);
	//odbierz();
	uart_flush();

	uart_putc(0x1A);
	_delay_ms(3000);
	//odbierz();
	uart_flush();
}

void pokaz_siec(void)
{
	uart_puts("AT+COPS?\r");
	_delay_ms(3000);
	odbierz();
	uart_flush();
}

void lista_SMS(void)
{
	uart_puts("AT+CMGL=4\r");//4-all, 3-wyslane, 2-niewyslane, 1-od. przeczytane,0-ode.nieprzeczytane
	_delay_ms(3000);
	odbierz();
	uart_flush();
}

void sim_info(void)
{
	uart_puts("AT+CCID\r");
	_delay_ms(1000);
	odbierz();
	uart_flush();
}

void text_mode(void)
{
	uart_puts("AT+CMGF=1\r");
	_delay_ms(1000);
	odbierz();
	uart_flush();

	uart_puts("AT+CSCS=\"GSM\"\r");
	_delay_ms(1000);
	odbierz();
	uart_flush();
}

void komenda_AT(char komenda[])
{
	uart_puts(komenda);
	uart_putc(0x0D);
	_delay_ms(2000);
	odbierz();
	uart_flush();
}
