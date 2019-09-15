#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "bsp.h"

#define LED0_PORT       GPIO_PORT_K
#define LED1_PORT       GPIO_PORT_K
#define LED2_PORT       GPIO_PORT_K
#define LED3_PORT       GPIO_PORT_K

#define LED0_PIN        GPIO_PORT_4
#define LED1_PIN        GPIO_PORT_5
#define LED2_PIN        GPIO_PORT_6
#define LED3_PIN        GPIO_PORT_7

#define LED0_FUN        GPIO_PK4_OUTPUT
#define LED1_FUN        GPIO_PK5_OUTPUT
#define LED2_FUN        GPIO_PK6_OUTPUT
#define LED3_FUN        GPIO_PK7_OUTPUT

typedef enum
{
    LED0 = 0,
    LED1,
    LED2,
    LED3,
}LED_Num;
 
typedef enum
{
    ON = GPIO_PIN_SET,
    OFF = GPIO_PIN_RESET,
}LED_Status;

void LED_Init(void);
void LED_Set(LED_Num LEDn, LED_Status status);


#endif



