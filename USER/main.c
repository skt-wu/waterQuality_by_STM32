//C库
#include <string.h>

//单片机头文件
#include "sys.h"

//网络协议层
#include "onenet.h"

//网络设备
#include "esp8266.h"

//硬件驱动
#include "delay.h"
#include "usart.h"
#include "dht11.h"
#include "adc.h"
#include "OLED_I2C.h"
#include "bsp_i2c_gpio.h"

extern u8 t,h;




//硬件初始化
void Hardware_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	
	delay_init();			//延时函数初始化

	dht_Init();				//温湿度初始化
	Adc_Init();				//adc（模拟信号转数字信号）初始化
	gpio_dig();				//adc中P13引脚初始化
	
	i2c_CfgGpio();		//i2c函数引脚初始化，SCL-PA6,SDA-PA7	
	OLED_Init();					 /* OLED初始化 */
	
	Usart1_Init(115200);	//串口1初始化为115200    //打印串口信息，用于方便调试
	Usart2_Init(115200); 	//串口2，驱动ESP8266用
	
	OLED_Fill(0xFF);			//全屏点亮
	delay_ms(2000);		
		
	OLED_Fill(0x00);			//全屏灭
	delay_ms(2000);

}

void Net_Init()
{
	ESP8266_Init();					//初始化ESP8266
	
	while(OneNet_DevLink())			//接入OneNET
		delay_ms(500);

}

int main(void)
{
	unsigned char *dataPtr = NULL;
	unsigned short timeCount = 300;	//发送间隔变量
	
	unsigned char i; 
	char str[100]={0};
	char ctr[100]={0};
	
	
	Hardware_Init();				//初始化外围硬件
	Net_Init();						//网络初始化

	while(1)
	{	
		delay_ms(10);
		timeCount ++;
		
		if(timeCount >= 300)	//发送间隔
		{
			
			dht_ReadData(&t,&h);
			sprintf (str,"%d",t);
			sprintf (ctr,"%d",h);
//			
			for(i=0;i<4;i++)
		{
			OLED_ShowCN(22+i*16,0,i);									//测试显示中文								//1
		}
		delay_ms(2000);
		for(i=0;i<3;i++)
		{
			OLED_ShowCN8(i*12,3,i);									//测试显示中文								//1
		}
		OLED_ShowStr(40,3,/*(unsigned char*)"Wildfire Tech"*/ (unsigned char*)str,3);				//测试6*12字符    //1
		OLED_ShowCN8(30+3*12,3,3);									//测试显示中文				
		
		for(i=4;i<7;i++)
		{
			OLED_ShowCN8(i*12-48,5,i);									//测试显示中文								//1
		}
		OLED_ShowStr(40,5,/*(unsigned char*)"Wildfire Tech"*/ (unsigned char*)ctr,3);				//测试6*12字符    //1
		OLED_ShowCN8(30+3*12,5,3);									//测试显示中文		
			
			
			OneNet_SendData();	//发送数据
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



















