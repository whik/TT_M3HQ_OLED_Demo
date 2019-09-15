#ifndef __BSP_SWITCH_H__
#define __BSP_SWITCH_H__

#include "bsp.h"

#define SW1_PORT        GPIO_PORT_P
#define SW2_PORT        GPIO_PORT_P

#define SW1_PIN         GPIO_PORT_6
#define SW2_PIN         GPIO_PORT_7

#define SW1_FUN        GPIO_PP6_INPUT
#define SW2_FUN        GPIO_PP7_INPUT

//位带操作方式读取输入，以下两种方式都一样
#define SW1_IN      READ_PIN(SW1_PORT, SW1_PIN)
#define SW2_IN      READ_PIN(SW2_PORT, SW2_PIN)
//#define SW1_IN      PPin(SW1_PIN)
//#define SW2_IN      PVin(SW1_PIN)

void SW_Init(void);
uint8_t Get_SW(void);


#endif
