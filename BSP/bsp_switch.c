#include "bsp_switch.h"

void SW_Init(void)
{
    gpio_t port;

    port.p_pp_instance = TSB_PP;    
    
    gpio_init(&port, SW1_PORT);  
    gpio_init(&port, SW2_PORT);  

    gpio_func(&port, SW1_PORT, SW1_PIN, SW1_FUN, GPIO_PIN_INPUT);   //输入模式
    gpio_func(&port, SW2_PORT, SW2_PIN, SW2_FUN, GPIO_PIN_INPUT);   //输入模式
    
    gpio_SetPullUp(&port, SW1_PORT, SW1_PIN, GPIO_PIN_SET);        //上拉
    gpio_SetPullUp(&port, SW2_PORT, SW2_PIN, GPIO_PIN_SET);        //上拉
}

uint8_t Get_SW(void)
{

     return (SW1_IN*2 + SW2_IN);    //00/01/10/11=0/1/2/3
}
