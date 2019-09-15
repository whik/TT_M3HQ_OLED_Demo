/** 
 *******************************************************************************
 * @file    txz_uart_ex.h
 * @brief   This file provides all the functions prototypes for UART driver.
 * @brief   Extended functionality.
 * @version V1.0.0.1
 * $Date:: 2018-01-22 15:14:05 #$
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA MICROELECTRONICS CORPORATION 2017 All rights reserved
 *******************************************************************************
 */
/*------------------------------------------------------------------------------*/
/*  Define to prevent recursive inclusion                                       */
/*------------------------------------------------------------------------------*/
#ifndef __UART_EX_H
#define __UART_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*  Includes                                                                    */
/*------------------------------------------------------------------------------*/
#include "txz_driver_def.h"
#include "txz_uart.h"

/**
 *  @addtogroup Periph_Driver
 *  @{
 */

/** 
 *  @addtogroup UART
 *  @{
 */
/*------------------------------------------------------------------------------*/
/*  Macro Definition                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup UART_Exported_define
 *  @{
 */

/** 
 *  @defgroup UART_HalfClockStart  Half Clock Mode Start Control
 *  @brief    Half Clock Mode Start Control Macro Definition.
 *  @{
 */
#define UART_HALF_CLOCK_START_TXDA      ((uint32_t)0x00000000)    /*!< Start to transmit on UTxTXDA.   */
#define UART_HALF_CLOCK_START_TXDB      ((uint32_t)0x00040000)    /*!< Start to transmit on UTxTXDB.   */
/**
 *  @}
 */ /* End of group UART_HalfClockStart */

/** 
 *  @defgroup UART_HalfClockOutput  Half Clock Mode Output Control
 *  @brief    Half Clock Mode Output Control Macro Definition.
 *  @{
 */
#define UART_HALF_CLOCK_OUTPUT_1        ((uint32_t)0x00000000)    /*!< 1 teminal mode.  */
#define UART_HALF_CLOCK_OUTPUT_2        ((uint32_t)0x00020000)    /*!< 2 teminal mode.  */
/**
 *  @}
 */ /* End of group UART_HalfClockOutput */

/**
 *  @}
 */ /* End of group UART_Exported_define */


/*------------------------------------------------------------------------------*/
/*  Enumerated Type Definition                                                  */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup UART_Exported_define
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group UART_Exported_define */


/*------------------------------------------------------------------------------*/
/*  Structure Definition                                                        */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup UART_Exported_typedef
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group UART_Exported_typedef */


/*------------------------------------------------------------------------------*/
/*  Functions                                                                   */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup UART_Exported_functions
 *  @{
 */
TXZ_Result uart_send_break(uart_t *p_obj);
TXZ_Result uart_stop_break(uart_t *p_obj);
TXZ_Result uart_enable_half_clock(uart_t *p_obj, uint32_t start, uint32_t output);
TXZ_Result uart_disable_half_clock(uart_t *p_obj);
TXZ_Result uart_enable_loopback(uart_t *p_obj);
TXZ_Result uart_disable_loopback(uart_t *p_obj);
TXZ_Result uart_enable_wakeup(uart_t *p_obj);
TXZ_Result uart_disable_wakeup(uart_t *p_obj);
/**
 *  @}
 */ /* End of group UART_Exported_functions */

/**
 *  @}
 */ /* End of group UART */

/**
 *  @}
 */ /* End of group Periph_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __UART_EX_H */


