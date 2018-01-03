/*
 * netlayer.c
 *
 *  Created on: 03-08-2015
 *      Author: adam
 */

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "../lcdpcf8574_PL/lcdpcf8574_PL.h"
#include "netlayer.h"
#include <util/crc16.h>
#include "../config.h"

uint8_t rejestr[5];// posiada zdublowany wpis extern w funkcji komunikacja.c

int8_t safeConvert(uint8_t x) {
	return x < 128 ? x : x - 256;
}




extern uint8_t wyslij(uint8_t skad,uint8_t dokad,uint8_t *co)
{
	//zmienne lokalne
	uint8_t pipe = 0;
	uint8_t bufferout[6];
	uint8_t odpowiedz[6];
	char znak[3];
	uint8_t retransmisja=3;
	uint8_t ret=0;

while(retransmisja>0)//petla retransmisji
 {

	//formatowanie pakietu
	bufferout[0]=skad;//0
	bufferout[1]=dokad;//1
	bufferout[2]=co[0];//bajt 1
	bufferout[3]=co[1];//bajt 2
	bufferout[4]=3;//bit0-NEW=1 bit1-ACK=1 bit2-OK
	bufferout[5]=check_crc(bufferout,5);
	uint8_t default_timeout=200;
	uint8_t timeout;


	//wysylka pakietu
	blink(1);
	nrf24l01_write(bufferout);

	//czekanie na odpowiedz

	timeout=0;
	while(!nrf24l01_readready(&pipe) & (timeout<=default_timeout))//wait if data is ready
		{
			timeout ++;
			_delay_ms(20);
		}

	if(debug==2)
			{
				lcd_gotoxy(7, 0);
				lcd_puts_P("R:");
				itoa(retransmisja,znak,10);
				lcd_puts(znak);

				lcd_gotoxy(0, 1);
				lcd_puts_P("T:");
				itoa(timeout,znak,10);
				lcd_puts(znak);
				lcd_puts_P("  ");

				lcd_gotoxy(6, 1);
				lcd_puts_P("crc:");
				itoa(bufferout[5],znak,10);
				lcd_puts(znak);
				lcd_puts_P("  ");
			}

			nrf24l01_read(odpowiedz);
			blink(1);
						if(debug==2)
						{
								lcd_gotoxy(0, 0);
			    	       		lcd_puts_P("(D)A:");
			    	       		itoa(odpowiedz[0],znak,10);
			    	       		lcd_puts(znak);

			    	       		lcd_puts_P(" B:");
			    	       		itoa(odpowiedz[1],znak,10);
			    	       		lcd_puts(znak);

			    	       		lcd_puts_P(" C:");
			    	       		itoa(odpowiedz[2],znak,10);
			    	       		lcd_puts(znak);

			    	       		lcd_puts_P("    ");
			    	       		lcd_gotoxy(0, 1);
			    	       		lcd_puts_P("D:");
			    	       		itoa(odpowiedz[3],znak,10);
			    	       		lcd_puts(znak);
			    	       		lcd_puts_P("        ");
						}
			if (odpowiedz[2]==4) // czu OK
				{
					//transmisja udana = odpowiedz OK
					retransmisja=0;
					ret=1;//transmisja OK
					if(debug==1)
						{
							lcd_gotoxy(11, 0);
							lcd_puts_P(" <OK>");
						}
				}


	 if (retransmisja>0) --retransmisja;//jest timeout, wiec zmniejsz petle retransmisji i ponow
 }
if((retransmisja==0) & (ret==0))//stwierdzenie bledu retransmisji
		{
			ret=2;//blad retransmisji
			if(debug==1)
						{
							lcd_gotoxy(11, 0);
							lcd_puts_P("<BAD>");
						}
		}
return ret;
}

extern uint8_t odczytaj(uint8_t moj_adres,uint8_t *co)
{
	//zmienne
	uint8_t pipe = 0;
	uint8_t crc;
	uint8_t buffer[6];
	char znak[3];
	uint8_t ret=0;

	blink(2);
	//czekaj na pakiet
	if(nrf24l01_readready(&pipe))//if data is ready
		{
			nrf24l01_read(co);
			if(co[1]==moj_adres)
			{
				blink(3);
				ret=1;
				//wylicz sume CRC
				crc=check_crc(co,5);

				if(debug==2)
					{
						lcd_gotoxy(0, 2);
						lcd_puts_P("(D):");
						itoa(crc,znak,10);
						lcd_puts(znak);
					}
				//utworz pakiet odpowiedzi
				buffer[0]=1;
				buffer[1]=0;

				//sprawdz CRC odebranego pakietu
				 if (co[5]==crc)
					{
						buffer[2]=04;//OK
						buffer[3]=check_crc(buffer,3);
						blink(3);
					}else
					{
						buffer[2]=02;//ACK
						buffer[3]=check_crc(buffer,3);
						blink(2);
					}
				//wyslij odpowiedz
				nrf24l01_write(buffer);
			} //end if adres
		}//end if pipe

	return ret;
}

extern uint8_t check_crc(uint8_t *co,uint8_t dl){
	uint8_t crc = 0, i;

	for (i = 0; i < dl; i++) crc = _crc_ibutton_update(crc, co[i]);

	return crc;
}

void blink(uint8_t nr){
	switch(nr)
	{
		//default:		return 0;

		case 1:
		LEDOUT_PORT &= ~(1<<LEDOUT); //wlacz D1
		_delay_ms(100);
		LEDOUT_PORT |= (1<<LEDOUT); //wylacz D1
		break;

		case 2:
		LEDOUT_PORT2 &= ~(1<<LEDOUT2);
		_delay_ms(100);
		LEDOUT_PORT2 |= (1<<LEDOUT2);
		break;

		case 3:
		LEDOUT_PORT3 &= ~(1<<LEDOUT3);
		_delay_ms(100);
		LEDOUT_PORT3 |= (1<<LEDOUT3);
		break;


	}
}


//*******************************************************************************
//*******************************************************************************
//*******************************************************************************


