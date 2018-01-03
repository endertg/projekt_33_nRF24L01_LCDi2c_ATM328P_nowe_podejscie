/*
 * esp8266.c
 *
 *  Created on: 09-05-2017
 *      Author: adam weglarczyk
 */
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
//#include <avr/pgmspace.h>

#include "../lcdpcf8574_PL/lcdpcf8574_PL.h"
//include nrf24l01
#include "../nrf24l01/nrf24l01.h"


char HTML_strona1[] PROGMEM = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\"><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><title>Sterownik Pieca</title><style type=\"text/css\">body {	background-color: #333;	color: white;	margin: 0px;	padding: 0px;}.ramka {	width: 600px;	background-color: #000;	text-align: center;	height: 400px;	margin-top: 0px;	margin-right: auto;	margin-bottom: 0px;	margin-left: auto;}.ramka p {	color: #FFF}.ustawienia {	background-color: #333;}#guzik {	width: 100px;	height: 60px;	border: thin solid #666;	padding: 5px;}</style></head><body><div class=\"ramka\"><h1>Sterownik Pieca</h1><p>Temp. pomieszczenia: 21,35 st.C</p><p>Grzanie: Wlaczone</p><p>Aktualny program: dzien</p><button id=\"guzik\" onclick=\"window.location.href='st.html?tryb=0'\">Wylacz</button><button id=\"guzik\" onclick=\"window.location.href='st.html?tryb=1'\">Dzien</button><button id=\"guzik\" onclick=\"window.location.href='st.html?tryb=2'\">Noc</button><p>&nbsp; </p><button id=\"guzik\" onclick=\"window.location.href='st2.html'\">Ustawienia</button><p>&nbsp; </p><p>&nbsp;</p></div></body></html>";
char HTML_strona2[] PROGMEM = "<HTML>B</HTML>";

PGM_P tablica_HTML[] PROGMEM =
{
	HTML_strona1,
	HTML_strona2
};

//esp8266 init
void esp8266_ini(void)
{


	int HTML_strona[2];

	char ID_parametry1[] = "par1";
	char ID_parametry2[] = "par2";
	//char POINT_parametry[6];

	HTML_strona[0]=HTML_strona1;
	HTML_strona[1]=HTML_strona2;


	char *wskaznik;

	char znak2[4];

	lcd_gotoxy(0,0);
	lcd_puts_P("w1:");
	itoa(*(HTML_strona1+13),znak2,10);
	lcd_puts(znak2);
	lcd_puts_P("w2:");
	wskaznik=HTML_strona[1]+14;
	itoa(*wskaznik,znak2,10);
	lcd_puts(znak2);

/*
 * korzystanie z danych z pamieci programu
 *

    char buffer[10];

  	//kopiuje ciag do buffora
	strcpy_P(buffer, (PGM_P)pgm_read_word(&(string_table[i])));


*/
}

