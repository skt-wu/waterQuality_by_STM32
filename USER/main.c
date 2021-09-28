//C��
#include <string.h>

//��Ƭ��ͷ�ļ�
#include "sys.h"

//����Э���
#include "onenet.h"

//�����豸
#include "esp8266.h"

//Ӳ������
#include "delay.h"
#include "usart.h"
#include "dht11.h"
#include "adc.h"
#include "OLED_I2C.h"
#include "bsp_i2c_gpio.h"

extern u8 t,h;




//Ӳ����ʼ��
void Hardware_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	delay_init();			//��ʱ������ʼ��

	dht_Init();				//��ʪ�ȳ�ʼ��
	Adc_Init();				//adc��ģ���ź�ת�����źţ���ʼ��
	gpio_dig();				//adc��P13���ų�ʼ��
	
	i2c_CfgGpio();		//i2c�������ų�ʼ����SCL-PA6,SDA-PA7	
	OLED_Init();					 /* OLED��ʼ�� */
	
	Usart1_Init(115200);	//����1��ʼ��Ϊ115200    //��ӡ������Ϣ�����ڷ������
	Usart2_Init(115200); 	//����2������ESP8266��
	
	OLED_Fill(0xFF);			//ȫ������
	delay_ms(2000);		
		
	OLED_Fill(0x00);			//ȫ����
	delay_ms(2000);

}

void Net_Init()
{
	ESP8266_Init();					//��ʼ��ESP8266
	
	while(OneNet_DevLink())			//����OneNET
		delay_ms(500);

}

int main(void)
{
	unsigned char *dataPtr = NULL;
	unsigned short timeCount = 300;	//���ͼ������
	
	unsigned char i; 
	char str[100]={0};
	char ctr[100]={0};
	
	
	Hardware_Init();				//��ʼ����ΧӲ��
	Net_Init();						//�����ʼ��

	while(1)
	{	
		delay_ms(10);
		timeCount ++;
		
		if(timeCount >= 300)	//���ͼ��
		{
			
			dht_ReadData(&t,&h);
			sprintf (str,"%d",t);
			sprintf (ctr,"%d",h);
//			
			for(i=0;i<4;i++)
		{
			OLED_ShowCN(22+i*16,0,i);									//������ʾ����								//1
		}
		delay_ms(2000);
		for(i=0;i<3;i++)
		{
			OLED_ShowCN8(i*12,3,i);									//������ʾ����								//1
		}
		OLED_ShowStr(40,3,/*(unsigned char*)"Wildfire Tech"*/ (unsigned char*)str,3);				//����6*12�ַ�    //1
		OLED_ShowCN8(30+3*12,3,3);									//������ʾ����				
		
		for(i=4;i<7;i++)
		{
			OLED_ShowCN8(i*12-48,5,i);									//������ʾ����								//1
		}
		OLED_ShowStr(40,5,/*(unsigned char*)"Wildfire Tech"*/ (unsigned char*)ctr,3);				//����6*12�ַ�    //1
		OLED_ShowCN8(30+3*12,5,3);									//������ʾ����		
			
			
			OneNet_SendData();	//��������
			timeCount = 0;
			ESP8266_Clear();
		}
		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
		{
			OneNet_RevPro(dataPtr);
		}	
	}
}



















