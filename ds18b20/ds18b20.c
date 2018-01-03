/*
   Plik ds18b20.c
   (minimum kodu do odczytu temperatury z ds18b20)

   xyz.isgreat.org
*/

#include <avr/io.h>
#include <util/delay.h>
#include "ds18b20.h"
#include "../config.h"
#include "onewire.h"
/**********************************************************/
unsigned char ds18b20_ConvertT(void)
{
  if (!OneWireReset()) return 0;

  OneWireWriteByte(0xcc); // SKIP ROM
  OneWireWriteByte(0x44); // CONVERT T

  return -1;
}

/***********************************************************/

int ds18b20_Read(unsigned char scratchpad[])
{
  unsigned char i;

  if (!OneWireReset()) return 0;

  OneWireWriteByte(0xcc); // SKIP ROM
  OneWireWriteByte(0xbe); // READ SCRATCHPAD

  for(i=0; i<9; i++) scratchpad[i] = OneWireReadByte();

  return 1;
}

/**********************************************************/



