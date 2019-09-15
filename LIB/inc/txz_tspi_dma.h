/** 
 *******************************************************************************
 * @file    txz_tspi_dma.h
 * @brief   This file provides all the functions prototypes for TSPI driver.
 * @brief   If DMA transfer is used, it is necessary.
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
#ifndef __TSPI_DMA_H
#define __TSPI_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*  Includes                                                                    */
/*------------------------------------------------------------------------------*/
#include "txz_driver_def.h"
#include "txz_tspi.h"
#include "txz_dma_ex.h"

/**
 *  @addtogroup Periph_Driver
 *  @{
 */

/** 
 *  @addtogroup TSPI
 *  @{
 */
/*------------------------------------------------------------------------------*/
/*  Macro Definition                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup TSPI_Exported_define
 *  @{
 */

/** 
 *  @defgroup TSPI_DMA_TransferType  Transfer Type
 *  @brief    DMA transfer type.
 *  @{
 */
#define TSPI_DMA_TYPE_UNUSE             ((uint32_t)0)    /*!< Unuse DMA.                */
#define TSPI_DMA_TYPE_MEM_TO_MEM        ((uint32_t)1)    /*!< Memory to Memory.         */
#define TSPI_DMA_TYPE_MEM_TO_PERI       ((uint32_t)2)    /*!< Memory to Peripheral.     */
#define TSPI_DMA_TYPE_PERI_TO_MEM       ((uint32_t)3)    /*!< Peripheral to Memory.     */
#define TSPI_DMA_TYPE_PERI_TO_PERI      ((uint32_t)4)    /*!< Peripheral to Peripheral. */
/**
 *  @}
 */ /* End of group TSPI_DMA_TransferType */
/** 
 *  @name  TSPIxDR_MASK Macro Definition.
 *  @brief TSPIxDR_MASK Macro Definition.
 *  @{
 */
/* DR */ 
#define TSPI_DR_8BIT_MASK        ((uint32_t)0x000000FF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_9BIT_MASK        ((uint32_t)0x000001FF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_10BIT_MASK      ((uint32_t)0x000003FF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_11BIT_MASK      ((uint32_t)0x000007FF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_12BIT_MASK      ((uint32_t)0x00000FFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_13BIT_MASK      ((uint32_t)0x00001FFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_14BIT_MASK      ((uint32_t)0x00003FFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_15BIT_MASK      ((uint32_t)0x00007FFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_16BIT_MASK      ((uint32_t)0x0000FFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_17BIT_MASK      ((uint32_t)0x0001FFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_18BIT_MASK      ((uint32_t)0x0003FFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_19BIT_MASK      ((uint32_t)0x0007FFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_20BIT_MASK      ((uint32_t)0x000FFFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_21BIT_MASK      ((uint32_t)0x001FFFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_22BIT_MASK      ((uint32_t)0x003FFFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_23BIT_MASK      ((uint32_t)0x007FFFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_24BIT_MASK      ((uint32_t)0x00FFFFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_25BIT_MASK      ((uint32_t)0x01FFFFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_26BIT_MASK      ((uint32_t)0x03FFFFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_27BIT_MASK      ((uint32_t)0x07FFFFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_28BIT_MASK      ((uint32_t)0x0FFFFFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_29BIT_MASK      ((uint32_t)0x1FFFFFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_30BIT_MASK      ((uint32_t)0x3FFFFFFF)    /*!< DR     :Mask for 8bit */
#define TSPI_DR_37BIT_MASK      ((uint32_t)0x7FFFFFFF)    /*!< DR     :Mask for 8bit */
/**
 *  @}
 */ /* End of name TSPIxDR_MASK Macro Definition */

/** 
 *  @name  TSPI _DATA_LENGTH Macro Definition.
 *  @brief TSPI  DATA LENGTH Macro Definition.
 *  @{
 */
#define DATA_LENGTH_8              ((uint32_t)0x08)    /*!< 8 bit  */
#define DATA_LENGTH_9              ((uint32_t)0x09)    /*!< 9 bit  */
#define DATA_LENGTH_10             ((uint32_t)0x0a)    /*!< 10 bit */
#define DATA_LENGTH_11             ((uint32_t)0x0b)    /*!< 11 bit */
#define DATA_LENGTH_12             ((uint32_t)0x0c)    /*!< 12 bit */
#define DATA_LENGTH_13             ((uint32_t)0x0d)    /*!< 13 bit */
#define DATA_LENGTH_14             ((uint32_t)0x0e)    /*!< 14 bit */
#define DATA_LENGTH_15             ((uint32_t)0x0f)    /*!< 15 bit */
#define DATA_LENGTH_16             ((uint32_t)0x10)    /*!< 16 bit */
#define DATA_LENGTH_17             ((uint32_t)0x11)    /*!< 17 bit */
#define DATA_LENGTH_18             ((uint32_t)0x12)    /*!< 18 bit */
#define DATA_LENGTH_19             ((uint32_t)0x13)    /*!< 19 bit */
#define DATA_LENGTH_20             ((uint32_t)0x14)   /*!< 20 bit */
#define DATA_LENGTH_21             ((uint32_t)0x15)    /*!< 21 bit */
#define DATA_LENGTH_22             ((uint32_t)0x16)    /*!< 22 bit */
#define DATA_LENGTH_23             ((uint32_t)0x17)   /*!< 23 bit */
#define DATA_LENGTH_24             ((uint32_t)0x18)    /*!< 24 bit */
#define DATA_LENGTH_25             ((uint32_t)0x19)    /*!< 25 bit */
#define DATA_LENGTH_26             ((uint32_t)0x1a)    /*!< 26 bit */
#define DATA_LENGTH_27             ((uint32_t)0x1b)    /*!< 27 bit */
#define DATA_LENGTH_28             ((uint32_t)0x1c)    /*!< 28 bit */
#define DATA_LENGTH_29             ((uint32_t)0x1d)    /*!< 29 bit */
#define DATA_LENGTH_30             ((uint32_t)0x1e)    /*!< 30 bit */
#define DATA_LENGTH_31             ((uint32_t)0x1f)    /*!< 31 bit */
#define DATA_LENGTH_32             ((uint32_t)0x20)    /*!< 32 bit */
/**
 *  @}
 */ /* End of name TSPI _DATA_LENGTH Macro Definition */
/**
 *  @}
 */ /* End of group TSPI_Exported_define */


/*------------------------------------------------------------------------------*/
/*  Enumerated Type Definition                                                  */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup TSPI_Exported_define
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group TSPI_Exported_define */


/*------------------------------------------------------------------------------*/
/*  Structure Definition                                                        */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup TSPI_Exported_typedef
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
                            : Use @ref TSPI_DMA_TransferType          */
    uint32_t ch;        /*!< DMA tspi channel.  
                            : If DMA isn't used, it isn't necessary.  */
} tspi_dma_setting_t;

/*----------------------------------*/
/** 
 * @brief  TSPI DMA initial setting structure definenition.
*/
/*----------------------------------*/
typedef struct
{
    dma_t              *p_obj;  /*!< DMA object address.  */
    tspi_dma_setting_t tx;      /*!< Transmit setting.    */
    tspi_dma_setting_t rx;      /*!< Receive setting.     */
} tspi_dma_initial_setting_t;

/*----------------------------------*/
/** 
 * @brief  TSPI DMA handle structure definenition.
*/
/*----------------------------------*/
typedef struct
{
    tspi_t super;                       /*!< Uart super class. 
                                            : Use @ref tspi_t                       */
    tspi_dma_initial_setting_t init;    /*!< Initial setting.
                                            : Use @ref tspi_dma_initial_setting_t   */
    uint32_t work[8];                   /*!< Work area.                             */
} tspi_dma_t;

/**
 *  @}
 */ /* End of group TSPI_Exported_typedef */


/*------------------------------------------------------------------------------*/
/*  Functions                                                                   */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup TSPI_Exported_functions
 *  @{
 */
TXZ_Result tspi_dma_init(tspi_dma_t *p_obj);
TXZ_Result tspi_dma_deinit(tspi_dma_t *p_obj);
TXZ_Result tspi_dma_discard_transmit(tspi_dma_t *p_obj);
TXZ_Result tspi_dma_discard_receive(tspi_dma_t *p_obj);
TXZ_Result tspi_dma_transmitIt(tspi_dma_t *p_obj, tspi_transmit_t *p_info);
TXZ_Result tspi_dma_receiveIt(tspi_dma_t *p_obj, tspi_receive_t *p_info);
/**
 *  @}
 */ /* End of group TSPI_Exported_functions */

/**
 *  @}
 */ /* End of group TSPI */

/**
 *  @}
 */ /* End of group Periph_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __TSPI_DMA_H */


