#ifndef __OLED_IIC_H__
#define __OLED_IIC_H__

#include "bsp.h" 

//SDA - PN2
//SCL - PN4

#define OLED_IIC_SDA_PORT       GPIO_PORT_N
#define OLED_IIC_SCL_PORT       GPIO_PORT_N

#define OLED_IIC_SDA_PIN    GPIO_PORT_2
#define OLED_IIC_SCL_PIN    GPIO_PORT_4

#define OLED_IIC_SCL_OUTPUT_FUN     GPIO_PN4_OUTPUT

#define OLED_IIC_SDA_INPUT_FUN     GPIO_PN2_INPUT
#define OLED_IIC_SDA_OUTPUT_FUN    GPIO_PN2_OUTPUT
//配置输入输出模式
#define OLED_SDA_IN()   gpio_func(&port, OLED_IIC_SDA_PORT, OLED_IIC_SDA_PIN, OLED_IIC_SDA_INPUT_FUN, GPIO_PIN_INPUT)   //输入模式
#define OLED_SDA_OUT()  gpio_func(&port, OLED_IIC_SDA_PORT, OLED_IIC_SDA_PIN, OLED_IIC_SDA_OUTPUT_FUN, GPIO_PIN_OUTPUT)

//位带方式操作IO
#define OLED_IIC_SCL    PNout(4) //SCL
#define OLED_IIC_SDA    PNout(2) //SDA	 
#define OLED_READ_SDA   PNin(2)  //输入SDA 

//IIC所有操作函数
void OLED_IIC_Init(void);                //初始化IIC的IO口				 
void OLED_IIC_Start(void);				//发送IIC开始信号
void OLED_IIC_Stop(void);	  			//发送IIC停止信号
void OLED_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 OLED_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 OLED_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void OLED_IIC_Ack(void);					//IIC发送ACK信号
void OLED_IIC_NAck(void);				//IIC不发送ACK信号

void OLED_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 OLED_IIC_Read_One_Byte(u8 daddr,u8 addr);	  

#endif




