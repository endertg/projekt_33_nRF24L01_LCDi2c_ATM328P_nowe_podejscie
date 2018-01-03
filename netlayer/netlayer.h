/*
 * netlayer.h
 *
 *  Created on: 03-08-2015
 *      Author: adam
 */

//definicje zmiennych
//#define moj_addres      	0x02 w eeprom





#ifndef NETLAYER_H_
#define NETLAYER_H_

#include "../nrf24l01/nrf24l01.h"




//definicje funkcji
int8_t safeConvert(uint8_t x);

extern uint8_t wyslij(uint8_t skad,uint8_t dokad,uint8_t *co);
extern uint8_t odczytaj(uint8_t moj_adres,uint8_t *co);
extern uint8_t check_crc(uint8_t *co,uint8_t dl);
void blink(uint8_t nr);




#endif /* NETLAYER_H_ */
