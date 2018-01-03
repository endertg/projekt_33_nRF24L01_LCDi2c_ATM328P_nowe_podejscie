/*
 * 1wire.h
 *
 *  Created on: 22-08-2015
 *      Author: adam
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_


void OneWireStrong(char);
unsigned char OneWireReset(void);
void OneWireWriteByte(unsigned char);
unsigned char OneWireReadByte(void);
unsigned char OneWireSearchRom(unsigned char serial[]);



#endif /* 1WIRE_H_ */
