/** 
 *******************************************************************************
 * @file    txz_uart_dma.h
 * @brief   This file provides all the functions prototypes for UART driver.
 * @brief   If DMA transfer is used, it is necessary.
 * @version V1.0.0.2
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
#ifndef __UART_DMA_H
#define __UART_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*  Includes                                                                    */
/*------------------------------------------------------------------------------*/
#include "txz_driver_def.h"
#include "txz_uart.h"
#include "txz_dma_ex.h"

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
 *  @defgroup UART_DMA_TransferType  Transfer Type
 *  @brief    DMA transfer type.
 *  @{
 */
#define UART_DMA_TYPE_UNUSE             ((uint32_t)0)    /*!< Unuse DMA.                */
#define UART_DMA_TYPE_MEM_TO_MEM        ((uint32_t)1)    /*!< Memory to Memory.         */
#define UART_DMA_TYPE_MEM_TO_PERI       ((uint32_t)2)    /*!< Memory to Peripheral.     */
#define UART_DMA_TYPE_PERI_TO_MEM       ((uint32_t)3)    /*!< Peripheral to Memory.     */
#define UART_DMA_TYPE_PERI_TO_PERI      ((uint32_t)4)    /*!< Peripheral to Peripheral. */
/**
 *  @}
 */ /* End of group UART_DMA_TransferType */

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

/*----------------------------------*/
/** 
 * @brief  DMA setting structure definenition.
*/
/*----------------------------------*/
typedef struct
{
    uint32_t type;      /*!< DMA transfer type. 
                            : Use @ref UART_DMA_TransferType          */
    uint32_t ch;        /*!< DMA uart channel.  
                            : If DMA isn't used, it isn't necessary.  */
} uart_dma_setting_t;

/*----------------------------------*/
/** 
 * @brief  UART DMA initial setting structure definenition.
*/
/*----------------------------------*/
typedef struct
{
    dma_t              *p_obj;  /*!< DMA object address.  */
    uart_dma_setting_t tx;      /*!< Transmit setting.    */
    uart_dma_setting_t rx;      /*!< Receive setting.     */
} uart_dma_initial_setting_t;

/*----------------------------------*/
/** 
 * @brief  UART DMA handle structure definenition.
*/
/*----------------------------------*/
typedef struct
{
    uart_t super;                       /*!< Uart super class. 
                                            : Use @ref uart_t                       */
    uart_dma_initial_setting_t init;    /*!< Initial setting.
                                            : Use @ref uart_dma_initial_setting_t   */
    uint32_t work[8];                   /*!< Work area.                             */
} uart_dma_t;

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
TXZ_Result uart_dma_init(uart_dma_t *p_obj);
TXZ_Result uart_dma_deinit(uart_dma_t *p_obj);
TXZ_Result uart_dma_discard_transmit(uart_dma_t *p_obj);
TXZ_Result uart_dma_discard_receive(uart_dma_t *p_obj);
TXZ_Result uart_dma_transmitIt(uart_dma_t *p_obj, uart_transmit_t *p_info);
TXZ_Result uart_dma_receiveIt(uart_dma_t *p_obj, uart_receive_t *p_info);
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
#endif /* __UART_DMA_H */


