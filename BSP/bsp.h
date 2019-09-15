#ifndef __BSP__
#define __BSP__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "TMPM3HQ.h"
#include "TMPM3Hy.h"

#include "txz_adc.h"
#include "txz_adc_ch.h"
#include "txz_adc_dma.h"
#include "txz_adc_include.h"
#include "txz_cg.h"
#include "txz_dma.h"
#include "txz_dma_ex.h"
#include "txz_dma_include.h"
#include "txz_driver_def.h"
#include "txz_gpio.h"
#include "txz_hal.h"
#include "txz_i2c.h"
#include "txz_t32a.h"
#include "txz_tspi.h"
#include "txz_tspi_dma.h"
#include "txz_uart.h"
#include "txz_uart_dma.h"
#include "txz_uart_ex.h"
#include "txz_uart_include.h"

#include "sys.h"    //包含位带操作功能

#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define LOG(fmt,args...) printf(fmt,##args)

void ClockInit(void);
void TT_M3HQ_EnableExLOSC(void);

void delay_init(void);
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);

#endif

