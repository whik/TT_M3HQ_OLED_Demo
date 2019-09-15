#include "main.h"

int main(void)
{
    uint8_t month = 9, day = 13, week = 5;
    uint8_t hour = 22, minute = 28, second = 11;

    delay_init();      //延时函数初始化
    LED_Init();         //LED初始化
    KEY_Init();         //按键初始化
    OLED_Init();        //OLED初始化
    SW_Init();          //拨码开关初始化
    
    UART0_Init(115200);
    LOG("\r\nTT_M3HQ %s %s", __DATE__, __TIME__);
    
    Display_LOGO();
    OLED_DisTime(hour,minute,second);     //显示时间
    OLED_DisDate(month,day,week);       //显示日期
    
    while(1)
    {
        delay_ms(80);
        second++;
        if(second >= 60)
        {
            minute++;
            second = 0;
        }
        if(minute >= 60)
        {
            hour++;
            minute = 0;
        }
        OLED_DisTime(hour, minute, second);
        LOG("Now: %d-%d 星期%d %d:%d:%d  %d \r\n", month, day, week, hour, minute, second, Get_SW());
        /*
        //按键按下LED闪烁
        if(KEY_IN == GPIO_PIN_RESET)
        {
            PKout(4) = 1;   //点亮  PORTx_SET(GPIO_PORT_K, 4);
            PKout(5) = 1;
            PKout(6) = 1;
            PKout(7) = 1;
            delay_ms(50);
            LOG("\r\nTT_M3HQ %s %s", __DATE__, __TIME__);

            PORTx_CLR(GPIO_PORT_K, 4);  //熄灭 PKout(4)=0
            PORTx_CLR(GPIO_PORT_K, 5);
            PORTx_CLR(GPIO_PORT_K, 6);
            PORTx_CLR(GPIO_PORT_K, 7);
            delay_ms(50);
        }*/
    }
}
