#include "oled_iic.h"
#include "bsp.h"
//SDA - PA12
//SCL - PA11
gpio_t port;

//初始化IIC
void OLED_IIC_Init(void)
{
    port.p_pn_instance = TSB_PN;        //PN时钟使能
    
    gpio_init(&port, OLED_IIC_SDA_PORT);  
    gpio_init(&port, OLED_IIC_SCL_PORT);  

    gpio_func(&port, OLED_IIC_SDA_PORT, OLED_IIC_SDA_PIN, OLED_IIC_SDA_OUTPUT_FUN, GPIO_PIN_OUTPUT);   
    gpio_func(&port, OLED_IIC_SCL_PORT, OLED_IIC_SCL_PIN, OLED_IIC_SCL_OUTPUT_FUN, GPIO_PIN_OUTPUT);  

    OLED_IIC_SCL = 1;
    OLED_IIC_SDA = 1;
}
//产生IIC起始信号
void OLED_IIC_Start(void)
{
    OLED_SDA_OUT();     //sda线输出
    OLED_IIC_SDA = 1;
    OLED_IIC_SCL = 1;
    delay_us(4);
    OLED_IIC_SDA = 0; //START:when CLK is high,DATA change form high to low
    delay_us(4);
    OLED_IIC_SCL = 0; //钳住I2C总线，准备发送或接收数据
}
//产生IIC停止信号
void OLED_IIC_Stop(void)
{
    OLED_SDA_OUT();//sda线输出
    OLED_IIC_SCL = 0;
    OLED_IIC_SDA = 0; //STOP:when CLK is high DATA change form low to high
    delay_us(4);
    OLED_IIC_SCL = 1;
    OLED_IIC_SDA = 1; //发送I2C总线结束信号
    delay_us(4);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 OLED_IIC_Wait_Ack(void)
{
    u8 ucErrTime = 0;
    OLED_SDA_IN();      //SDA设置为输入
    OLED_IIC_SDA = 1;
    delay_us(1);
    OLED_IIC_SCL = 1;
    delay_us(1);
    while(OLED_READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            OLED_IIC_Stop();
            return 1;
        }
    }
    OLED_IIC_SCL = 0; //时钟输出0
    return 0;
}
//产生ACK应答
void OLED_IIC_Ack(void)
{
    OLED_IIC_SCL = 0;
    OLED_SDA_OUT();
    OLED_IIC_SDA = 0;
    delay_us(2);
    OLED_IIC_SCL = 1;
    delay_us(2);
    OLED_IIC_SCL = 0;
}
//不产生ACK应答
void OLED_IIC_NAck(void)
{
    OLED_IIC_SCL = 0;
    OLED_SDA_OUT();
    OLED_IIC_SDA = 1;
    delay_us(2);
    OLED_IIC_SCL = 1;
    delay_us(2);
    OLED_IIC_SCL = 0;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void OLED_IIC_Send_Byte(u8 txd)
{
    u8 t;
    OLED_SDA_OUT();
    OLED_IIC_SCL = 0; //拉低时钟开始数据传输
    for(t = 0; t < 8; t++)
    {
        OLED_IIC_SDA = (txd & 0x80) >> 7;
        txd <<= 1;
        delay_us(2);  
        OLED_IIC_SCL = 1;
        delay_us(2);
        OLED_IIC_SCL = 0;
        delay_us(2);
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 OLED_IIC_Read_Byte(unsigned char ack)
{
    unsigned char i, receive = 0;
    OLED_SDA_IN();//SDA设置为输入
    for(i = 0; i < 8; i++)
    {
        OLED_IIC_SCL = 0;
        delay_us(2);
        OLED_IIC_SCL = 1;
        receive <<= 1;
        if(OLED_READ_SDA)receive++;
        delay_us(1);
    }
    if(!ack)
        OLED_IIC_NAck();//发送nACK
    else
        OLED_IIC_Ack(); //发送ACK
    return receive;
}




