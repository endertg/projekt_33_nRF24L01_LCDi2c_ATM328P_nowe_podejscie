
#include <avr/io.h>
#include <util/delay.h>
#include "onewire.h"
#include "../config.h"



/**********************************************************/
void OneWireStrong(char s)
{
  if (s)
  {
     SET_ONEWIRE_PORT;
     SET_OUT_ONEWIRE_DDR;
  }
  else
  {
     SET_IN_ONEWIRE_DDR;
  }
}

/**********************************************************/

unsigned char OneWireReset()
{
  CLR_ONEWIRE_PORT;

  if (!(IS_SET_ONEWIRE_PIN)) return 0;

  SET_OUT_ONEWIRE_DDR;
  _delay_us(500);
  SET_IN_ONEWIRE_DDR;
  _delay_us(70);

  if(!(IS_SET_ONEWIRE_PIN))
  {
    _delay_us(500);
    return(1);
  }

  _delay_us(500);

return(0);
}

/**********************************************************/

void OneWireWriteByte(unsigned char byte)
{
   unsigned char i;

   CLR_ONEWIRE_PORT;

   for (i=0; i<8; i++)
   {
     SET_OUT_ONEWIRE_DDR;

     if (byte & 0x01)
     {
       _delay_us(7);
       SET_IN_ONEWIRE_DDR;
       _delay_us(70);
     }
     else
     {
        _delay_us(70);
        SET_IN_ONEWIRE_DDR;
        _delay_us(7);
     }

     byte >>= 1;
   }
}

/***********************************************************/

unsigned char OneWireReadByte(void)
{
  unsigned char i, byte = 0;

  SET_IN_ONEWIRE_DDR;

  for (i=0; i<8; i++)
  {
     SET_OUT_ONEWIRE_DDR;
     _delay_us(7);
     SET_IN_ONEWIRE_DDR;
     _delay_us(7);
     byte >>= 1;

     if(IS_SET_ONEWIRE_PIN) byte |= 0x80;

     _delay_us(70);
  }

  return byte;
}

/***********************************************************/
unsigned char OneWireSearchRom(unsigned char serial[])
{
	unsigned char i;
	if (!OneWireReset()) return 0;

	OneWireWriteByte(0x33); // skip rom - SEARCH ROM
	for(i=0; i<9; i++) serial[i] = OneWireReadByte();

	return 1;
}
/**********************************************************/
//match ROM


/**********************************************************/
//search ROM
///////////////////////////////////////////////////////
//Szuka urzadzen 1Wire/////////////////////////////////
// char buffer[N], gdzie N to liczba urz¹dzeñ,
// zainicjowany jest z zawartoœci¹ {0,0,0...,0}
// tablicaRekordow[N][8] przechowuje ID uk³adu;
///////////////////////////////////////////////////////

unsigned char searchROM1Wire(unsigned char tablicaRekordow[][8],char N) {
/*
unsigned char bit,bit_complementary,pozycja,buffer[N];

for(unsigned char i=0;buffer[i]=0; // tu bylo ibuffer
{
   for(unsigned char i=0;i   pozycja=0;
   if(~reset1Wire()&1) return 0;
   sendByte1Wire(SEARCH_ROM);
      for(unsigned char bitNo=0;bitNo<64;bitNo++) {
      bit=readBit();
      bit_complementary=readBit();
         if ((~(bit|bit_complementary))&1) {
            if(buffer[pozycja+1]==0) {
            buffer[pozycja]++;
            }
         writeBit((buffer[pozycja]-1));
          tablicaRekordow[i][bitNo/8]|=((buffer[pozycja]-1))<<(bitNo%8);
         pozycja++;
         } else {
         writeBit(bit);
         tablicaRekordow[i][bitNo/8]|=bit<<(bitNo%8);
         }
      }
      while(buffer[pozycja-1]==2) {
      buffer[pozycja]=0;
      pozycja--;
      }
}

   */
	return 1;
}
//////////////////////////////////////////////////////
/**********************************************************/
