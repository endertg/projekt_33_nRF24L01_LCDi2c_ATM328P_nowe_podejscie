/*
   Plik ds18b20.h

   (xyz.isgreat.org)
*/

#ifndef DS18B20_H
#define DS18B20_H

/* DS18B20 przy��czony do portu  PD7 AVRa
#define SET_ONEWIRE_PORT     PORTD  |=  _BV(7)
#define CLR_ONEWIRE_PORT     PORTD  &= ~_BV(7)
#define IS_SET_ONEWIRE_PIN   PIND   &   _BV(7)
#define SET_OUT_ONEWIRE_DDR  DDRD   |=  _BV(7)
#define SET_IN_ONEWIRE_DDR   DDRD   &= ~_BV(7)
*/


unsigned char ds18b20_ConvertT(void);
int ds18b20_Read(unsigned char []);

#endif
