#ifndef __BSP_H__
#define __BSP_H__

#include "bsp.h"

void TT_M3HQ_UART0_TxHandler(uint32_t id, TXZ_Result result);
void TT_M3HQ_UART0_RxHandler(uint32_t id, TXZ_Result result, uart_receive_t *p_info);
void UART0_Init(uint32_t baudrate);
void INTUART0RX_IRQHandler(void);
void INTUART0TX_IRQHandler(void);
void INTUART0ERR_IRQHandler(void);
void INTT32A00A_IRQHandler(void);
void INTT32A03A_IRQHandler(void);
static void TT_M3HQ_UART0_Send(uint8_t ch);
int fputc(int ch, FILE *f);
void TT_M3HQ_Warning(void);

#endif



