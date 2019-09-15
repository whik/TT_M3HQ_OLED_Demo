#include "bsp_led.h"


void LED_Init(void)
{
    gpio_t port;
    port.p_pk_instance = TSB_PK;    //GPIOK
    
    gpio_init(&port, LED0_PORT);    //初始化GPIOK 
//    gpio_init(&port, LED1_PORT);      
//    gpio_init(&port, LED2_PORT);     
//    gpio_init(&port, LED3_PORT);     

    gpio_func(&port, LED0_PORT, LED0_PIN, LED0_FUN, GPIO_PIN_OUTPUT);
    gpio_func(&port, LED1_PORT, LED1_PIN, LED1_FUN, GPIO_PIN_OUTPUT);
    gpio_func(&port, LED2_PORT, LED2_PIN, LED2_FUN, GPIO_PIN_OUTPUT);
    gpio_func(&port, LED3_PORT, LED3_PIN, LED3_FUN, GPIO_PIN_OUTPUT);

    //初始化熄灭
    gpio_write_bit(&port, LED0_PORT, LED0_PIN, GPIO_Mode_DATA, GPIO_PIN_RESET);
    gpio_write_bit(&port, LED1_PORT, LED1_PIN, GPIO_Mode_DATA, GPIO_PIN_RESET);
    gpio_write_bit(&port, LED2_PORT, LED2_PIN, GPIO_Mode_DATA, GPIO_PIN_RESET);
    gpio_write_bit(&port, LED3_PORT, LED3_PIN, GPIO_Mode_DATA, GPIO_PIN_RESET);
}

void LED_Set(LED_Num LEDn, LED_Status status)
{
    gpio_t port;

    switch (LEDn)
    {
        case LED0:
             gpio_write_bit(&port, LED0_PORT, LED0_PIN, GPIO_Mode_DATA, status);
            break;
        case LED1:
             gpio_write_bit(&port, LED1_PORT, LED1_PIN, GPIO_Mode_DATA, status);
            break;
        case LED2:
             gpio_write_bit(&port, LED2_PORT, LED2_PIN, GPIO_Mode_DATA, status);
            break;
        case LED3:
             gpio_write_bit(&port, LED3_PORT, LED3_PIN, GPIO_Mode_DATA, status);
            break;
        default:
            break;
    } 
}

