#ifndef __DHT11_H
#define __DHT11_H
#include "stm32f10x.h"

#define 	dht_port       	  GPIOB
#define 	dht_pin        	  GPIO_Pin_13
#define   dht_read_input  	GPIO_ReadInputDataBit( dht_port, dht_pin) 
#define   dht_high_input()  GPIO_SetBits( dht_port, dht_pin)
#define   dht_low_input()   GPIO_ResetBits( dht_port, dht_pin)
#define   dht_APB()					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);


void dht_input(void);
void dht_output(void);

void dht_Rst(void);
u8 dht_Check(void);
u8 dht_ReadBit(void);
u8 dht_ReadByte(void);

u8 dht_ReadData(u8 *t,u8 *h);
u8 dht_Init(void);


#endif

