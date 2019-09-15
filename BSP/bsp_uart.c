#include "bsp_uart.h"
#include "stdio.h"

uint8_t UART0_Buffer[100];
uint16_t idx = 0;
uart_t uart0;

void TT_M3HQ_Warning(void)
{
}

void TT_M3HQ_UART0_TxHandler(uint32_t id, TXZ_Result result)
{
}

void TT_M3HQ_UART0_RxHandler(uint32_t id, TXZ_Result result, uart_receive_t *p_info)
{
    uint32_t i = 0;
    uint16_t RxNum = p_info->rx8.num;
    uint8_t dat = 0;
    if(result == TXZ_SUCCESS)
    {
        for(i = 0; i < RxNum; i++)    //接收到的数据总数RxNum
        {
            dat = p_info->rx8.p_data[i];
//            QUEUE_WRITE(QUEUE_DEBUG_RX_IDX, p_info->rx8.p_data[i]);
        }
    }
}

void UART0_Init(uint32_t baudrate)
{
    cg_t paramCG;
    uart_receive_t rx;
    gpio_t port;
    port.p_pa_instance = TSB_PA;
    
    TSB_CG_FSYSENB_IPENB05 = 1;
    
    paramCG.p_instance = TSB_CG;
    
    gpio_init(&port, GPIO_PORT_A);
    
    //PA1-UT0TX
    gpio_func(&port, GPIO_PORT_A, GPIO_PORT_1, (uint32_t)GPIO_PA1_UT0TXDA, GPIO_PIN_OUTPUT);
    //PA2-UT0RX
    gpio_func(&port, GPIO_PORT_A, GPIO_PORT_2, (uint32_t)GPIO_PA2_UT0RXD, GPIO_PIN_INPUT);
    
    //波特率配置为115200
    uart_get_boudrate_setting(cg_get_phyt0(&paramCG), &uart0.init.clock, baudrate,  &uart0.init.boudrate);

    uart0.p_instance         = TSB_UART0;                       //外设串口0
    uart0.init.id            = 0;
    uart0.init.clock.prsel   = UART_PLESCALER_1;
    uart0.init.intrx         = UART_RX_INT_ENABLE;              //接收中断使能
//    uart0.init.inttx         = UART_TX_INT_ENABLE;              //发送中断使能
//    uart0.init.interr        = UART_ERR_INT_ENABLE;             //错误中断使能
    uart0.init.txfifo.inttx  = UART_TX_FIFO_INT_DISABLE;        //发送FIFO中断禁止
    uart0.init.txfifo.level  = 0;
    uart0.init.rxfifo.intrx  = UART_RX_FIFO_INT_DISABLE;        //接收FIFO中断禁止
    uart0.init.rxfifo.level  = 8;
    uart0.init.nf            = UART_NOISE_FILTER_NON;       //无噪声滤波器
    uart0.init.ctse          = UART_CTS_DISABLE;            //不使用CTS
    uart0.init.rtse          = UART_RTS_DISABLE;            //不使用RTS
    uart0.init.iv            = UART_DATA_COMPLEMENTION_DISABLE;
    uart0.init.dir           = UART_DATA_DIRECTION_LSB;     //低位在前
    uart0.init.sblen         = UART_STOP_BIT_1;             //1位停止位
//    uart0.init.even          = UART_PARITY_BIT_ODD;
    uart0.init.pe            = UART_PARITY_DISABLE;         //无奇偶校验
    uart0.init.sm            = UART_DATA_LENGTH_8;          //8位数据位
    uart0.transmit.handler   = TT_M3HQ_UART0_TxHandler;     //指定发送中断函数
    uart0.receive.handler    = TT_M3HQ_UART0_RxHandler;     //指定接收中断函数
    
    uart_init(&uart0);

    rx.rx8.p_data = UART0_Buffer;
    rx.rx8.num    = 100;
    uart_receiveIt(&uart0, &rx);        //中断模式下不可用

    NVIC_EnableIRQ(INTUART0RX_IRQn);
//    NVIC_EnableIRQ(INTUART0TX_IRQn);
//    NVIC_EnableIRQ(INTUART0ERR_IRQn);
}

void INTUART0RX_IRQHandler(void)
{
    uart_receive_irq_handler(&uart0);
}

void INTUART0TX_IRQHandler(void)
{
    uart_transmit_irq_handler(&uart0);
}

void INTUART0ERR_IRQHandler(void)
{
    uart_error_irq_handler(&uart0);
}

void TT_M3HQ_UART0_Send(uint8_t ch)
{
    uart_transmit_t param;
    uint32_t state;

    param.tx8.p_data = &ch;
    param.tx8.num    = 1;

    if(uart_transmitIt(&uart0, &param) != TXZ_SUCCESS)
    {
        TT_M3HQ_Warning();
    }
    do
    {
        if(uart_get_status(&uart0, &state) != TXZ_SUCCESS)
        {
            TT_M3HQ_Warning();
        }
    }
    while((state & UART_TX_STATE_RUN) == UART_TX_STATE_RUN);
}
//必须勾选使用MicroLib，才能重定向printf到串口0
int fputc(int ch, FILE *f)
{
    TT_M3HQ_UART0_Send((uint8_t)ch);
    return ch;
}





