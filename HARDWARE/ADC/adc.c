#include "delay.h"
#include "adc.h"

void gpio_dig(void)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStrue.GPIO_Mode = GPIO_Mode_Out_PP;									//USB ��Rx
	GPIO_InitStrue.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStrue.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GPIO_InitStrue);

}

/*

	��ʼ��ADC���ţ���Ƶ

*/


void Adc_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
	
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init( GPIOA, &GPIO_InitStruct);
	
	ADC_DeInit(ADC1);

	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	
	ADC_Init(ADC1,&ADC_InitStruct);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration( ADC1); //ʹ�ܸ�λУ׼
	while(ADC_GetResetCalibrationStatus(ADC1)); //�ȴ���λУ׼����
	
	ADC_StartCalibration( ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	
}

u16 Get_Adc(u8 ch)
{
	
	ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_1Cycles5);
	ADC_SoftwareStartConvCmd( ADC1, ENABLE);													
	
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));    //�ж��Ƿ�ת������
	
	return ADC_GetConversionValue(ADC1);
	
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		//delay_ms(5);	 
	}
	return temp_val/times;

}


