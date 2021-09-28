#ifndef _BSP_I2C_GPIO_H
#define _BSP_I2C_GPIO_H

#include <inttypes.h>

#define OLED_I2C_WR	0		/* д����bit */
#define OLED_I2C_RD	1		/* ������bit */

/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */
#define OLED_GPIO_PORT_I2C	GPIOA			/* GPIO�˿� */
#define OLED_RCC_I2C_PORT 	RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define OLED_I2C_SCL_PIN		GPIO_Pin_6			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define OLED_I2C_SDA_PIN		GPIO_Pin_7			/* ���ӵ�SDA�����ߵ�GPIO */


/* �����дSCL��SDA�ĺ꣬�����Ӵ���Ŀ���ֲ�ԺͿ��Ķ��� */
#if 0	/* �������룺 1 ѡ��GPIO�Ŀ⺯��ʵ��IO��д */
	#define OLED_I2C_SCL_1()  GPIO_SetBits(OLED_GPIO_PORT_I2C, OLED_I2C_SCL_PIN)		/* SCL = 1 */
	#define OLED_I2C_SCL_0()  GPIO_ResetBits(OLED_GPIO_PORT_I2C, OLED_I2C_SCL_PIN)		/* SCL = 0 */
	
	#define OLED_I2C_SDA_1()  GPIO_SetBits(OLED_GPIO_PORT_I2C, OLED_I2C_SDA_PIN)		/* SDA = 1 */
	#define OLED_I2C_SDA_0()  GPIO_ResetBits(OLED_GPIO_PORT_I2C, OLED_I2C_SDA_PIN)		/* SDA = 0 */
	
	#define OLED_I2C_SDA_READ()  GPIO_ReadInputDataBit(OLED_GPIO_PORT_I2C, OLED_I2C_SDA_PIN)	/* ��SDA����״̬ */
#else	/* �����֧ѡ��ֱ�ӼĴ�������ʵ��IO��д */
    /*��ע�⣺����д������IAR��߼����Ż�ʱ���ᱻ�����������Ż� */
	#define OLED_I2C_SCL_1()  OLED_GPIO_PORT_I2C->BSRR = OLED_I2C_SCL_PIN				/* SCL = 1 */
	#define OLED_I2C_SCL_0()  OLED_GPIO_PORT_I2C->BRR = OLED_I2C_SCL_PIN				/* SCL = 0 */
	
	#define OLED_I2C_SDA_1()  OLED_GPIO_PORT_I2C->BSRR = OLED_I2C_SDA_PIN				/* SDA = 1 */
	#define OLED_I2C_SDA_0()  OLED_GPIO_PORT_I2C->BRR = OLED_I2C_SDA_PIN				/* SDA = 0 */
	
	#define OLED_I2C_SDA_READ()  ((OLED_GPIO_PORT_I2C->IDR & OLED_I2C_SDA_PIN) != 0)	/* ��SDA����״̬ */
#endif


void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);

void i2c_CfgGpio(void);



#endif

