
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#define debug 			1

//magistrala I2C sprzętowa
//LCD na I2C
//1-GND
//2-VCC
//3-SDA-A4
//4-SCL-A5
//mozliwosc podlaczenia wiecej urzadzen - kazde ma adres
//#define PCF8574_ADDRBASE (39) //device base address - w pcf8574.h
//#define LCD_PCF8574_DEVICEID 0 //kolejne urzadzenie - w w lcdpcf8574.h

//magistrala SPI
//NRF24L01
//spi ports
#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define SPI_MISO PB4
#define SPI_MOSI PB3
#define SPI_SCK PB5
#define SPI_SS PB2
//CE and CSN port definitions
#define NRF24L01_DDR DDRB
#define NRF24L01_PORT PORTB
#define NRF24L01_CE PB0
#define NRF24L01_CSN PB2


//konfiguracja DS18B20
// DS18B20 przyĹ‚Ä…czony do portu  PD5 AVRa
#define SET_ONEWIRE_PORT     PORTD  |=  _BV(5)
#define CLR_ONEWIRE_PORT     PORTD  &= ~_BV(5)
#define IS_SET_ONEWIRE_PIN   PIND   &   _BV(5)
#define SET_OUT_ONEWIRE_DDR  DDRD   |=  _BV(5)
#define SET_IN_ONEWIRE_DDR   DDRD   &= ~_BV(5)
/*
//konfiguracja DTH11 lub DTH22
//setup parameters
#define DHT11_DDR DDRD
#define DHT11_PORT PORTD
#define DHT11_PIN PIND
#define DHT11_INPUTPIN PD0
*/

// konfiguracja przyciskow
//role button 1
#define BUTTON1_DDR DDRD
#define BUTTON1_PORT PORTD
#define BUTTON1_PIN PIND
#define BUTTON1 PD2
//send button 2
#define BUTTON2_DDR DDRD
#define BUTTON2_PORT PORTD
#define BUTTON2_PIN PIND
#define BUTTON2 PD3
//send button 3
#define BUTTON3_DDR DDRD
#define BUTTON3_PORT PORTD
#define BUTTON3_PIN PIND
#define BUTTON3 PD2
//send button 4
#define BUTTON4_DDR DDRD
#define BUTTON4_PORT PORTD
#define BUTTON4_PIN PIND
#define BUTTON4 PD3




//output led 1
#define LEDOUT_DDR DDRD
#define LEDOUT_PORT PORTD
#define LEDOUT PD4
#define LEDOUTPAUSE 100
//output led 2
#define LEDOUT_DDR2 DDRD
#define LEDOUT_PORT2 PORTD
#define LEDOUT2 PD6
//output led 3
#define LEDOUT_DDR3 DDRD
#define LEDOUT_PORT3 PORTD
#define LEDOUT3 PD7

//----------------------
// LCD 
//----------------------

//AMEGA32
//SCL PC0	PIN23
//SDA PC1	PIN22



/*
// dane konfiguracyjne magistrali I2CSoft
#define SCLPORT	PORTC	//TAKE PORTD as SCL OUTPUT WRITE
#define SCLDDR	DDRC	//TAKE DDRB as SCL INPUT/OUTPUT configure

#define SDAPORT	PORTC	//TAKE PORTD as SDA OUTPUT WRITE
#define SDADDR	DDRC	//TAKE PORTD as SDA INPUT configure

#define SDAPIN	PINC	//TAKE PORTD TO READ DATA
#define SCLPIN	PINC	//TAKE PORTD TO READ DATA

#define SCL	PC0		//PORTD.0 PIN AS SCL PIN
#define SDA	PC1		//PORTD.1 PIN AS SDA PIN


#define SOFT_I2C_SDA_LOW	SDADDR|=((1<<SDA))
#define SOFT_I2C_SDA_HIGH	SDADDR&=(~(1<<SDA))

#define SOFT_I2C_SCL_LOW	SCLDDR|=((1<<SCL))
#define SOFT_I2C_SCL_HIGH	SCLDDR&=(~(1<<SCL))
*/

// dane konfiguracyjne magistrali I2C
//#define I2C_PORT 	PORTC	//port do ktĂ‹â€ˇrego sĂ˘â€˘Ĺ� podĂ˘â€ťâ€šĂ˘â€˘Ĺ�czone linie magistrali
//#define I2C_SDA		1	//bit powyĂ˘â€ťďż˝szego portu uĂ˘â€ťďż˝ywany jako linia SDA
//#define I2C_SCL		0	//bit powyĂ˘â€ťďż˝szego portu uĂ˘â€ťďż˝ywany jako linia SCL
