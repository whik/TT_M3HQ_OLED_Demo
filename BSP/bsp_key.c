#include "bsp_key.h"

void KEY_Init(void)
{
    gpio_t port;

    port.p_pv_instance = TSB_PV;    
    
    gpio_init(&port, KEY_PORT);  

    gpio_func(&port, KEY_PORT, KEY_PIN, KEY_FUN, GPIO_PIN_INPUT);   //输入模式
    gpio_SetPullUp(&port, KEY_PORT, KEY_PIN, GPIO_PIN_SET);        //上拉
}

gpio_pinstate_t Get_Key(void)
{
    gpio_pinstate_t key_status;
    gpio_t port;

    gpio_read_bit(&port, KEY_PORT, KEY_PIN, GPIO_Mode_DATA, &key_status);
    return key_status;
}
