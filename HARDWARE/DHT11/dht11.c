#include "dht11.h"
#include "delay.h"

void dht_input(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	dht_APB();
	
	GPIO_InitStructure.GPIO_Pin=dht_pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(dht_port,&GPIO_InitStructure);
}

void dht_output(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	dht_APB();
	
	GPIO_InitStructure.GPIO_Pin=dht_pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(dht_port,&GPIO_InitStructure);
}

void dht_Rst(void)
{
	dht_output();
	dht_low_input();
	delay_ms(20);
	dht_high_input();
	delay_us(30);
	
}

u8 dht_Check(void)
{
	u8 k = 0;
	dht_input();
	while(dht_read_input && k < 100)  //83 低电平
	{
		k++;
		delay_us(1);
	}
	if(k >= 100 )return 1;
	else k = 0;
	while(!dht_read_input && k<100 )		//87 高电平
	{
		k++;
		delay_us(100);
	}
	if(k>=100)return 1;
	return 0;

}

u8 dht_ReadBit(void)
{
	u8 k = 0;
	while(dht_read_input && k<100)
	{
		k++;
		delay_us(1);
	}
	k = 0;
	while(!dht_read_input && k<100)
	{
		k++;
		delay_us(1);
	}
	delay_us(40);
	if(dht_read_input) return 1;
	else return 0;

}

u8 dht_ReadByte(void)
{
	u8 i,dat;
	dat = 0;
	for(i=0;i<8;i++)
	{
		dat<<=1;
		dat|=dht_ReadBit();
		
	}
	return dat;
}

u8 dht_ReadData(u8 *t,u8 *h)
{
	u8 temp[5];
	u8 i;
	dht_Rst();
	if(dht_Check() == 0)
	{
		for(i=0;i<5;i++)
		{
			temp[i] = dht_ReadByte();
		}
		if(temp[0]+temp[1]+temp[2]+temp[3] == temp[4])
		{
			*h = temp[0];
			*t = temp[2];
		}
	}else return 1;
	return 0;
}

u8 dht_Init(void)
{
	dht_output();
	dht_Rst();
	return dht_Check();

}
