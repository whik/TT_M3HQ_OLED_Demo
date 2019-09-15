/** 
 *******************************************************************************
 * @file    txz_dma.h
 * @brief   This file provides all the functions prototypes for DMA driver.
 * @version V1.0.0.5
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
#ifndef __DMA_H
#define __DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*  Includes                                                                    */
/*------------------------------------------------------------------------------*/
#include "txz_driver_def.h"

/**
 *  @addtogroup Periph_Driver
 *  @{
 */

/** 
 *  @defgroup DMA DMA
 *  @brief    DMA Driver.
 *  @{
 */
/*------------------------------------------------------------------------------*/
/*  Macro Function                                                              */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup DMA_Exported_macro DMA Exported Macro
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group DMA_Exported_macro */


/*------------------------------------------------------------------------------*/
/*  Macro Definition                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup DMA_Exported_define DMA Exported Define
 *  @{
 */

/** 
 *  @defgroup DMA_ChannelNum  Channel Num
 *  @brief    DMA Channel.
 *  @{
 */
#define DMA_CH_NUM                      ((uint32_t)32)            /*!< Num of total channel (1<= value <= 32). */
/**
 *  @}
 */ /* End of group DMA_ChannelNum */

/** 
 *  @defgroup DMA_DestinationInc  Destination Address Increment Type
 *  @brief    Destination address increment type.
 *  @{
 */
#define DMA_DST_INC_1BYTE               ((uint32_t)0x00000000)    /*!< 1 byte.               */
#define DMA_DST_INC_2BYTE               ((uint32_t)0x40000000)    /*!< 2 byte.               */
#define DMA_DST_INC_4BYTE               ((uint32_t)0x80000000)    /*!< 4 byte.               */
#define DMA_DST_INC_NON                 ((uint32_t)0xC0000000)    /*!< Without increment.    */
/**
 *  @}
 */ /* End of group DMA_DestinationInc */

/** 
 *  @defgroup DMA_DestinationSize  Destination Data Size
 *  @brief    Destination data size.
 *  @{
 */
#define DMA_DST_SIZE_1BYTE              ((uint32_t)0x00000000)    /*!< 1 byte.               */
#define DMA_DST_SIZE_2BYTE              ((uint32_t)0x10000000)    /*!< 2 byte.               */
#define DMA_DST_SIZE_4BYTE              ((uint32_t)0x20000000)    /*!< 4 byte.               */
/**
 *  @}
 */ /* End of group DMA_DestinationSize */

/** 
 *  @defgroup DMA_SourceInc  Source Address Increment Type
 *  @brief    Source address increment type.
 *  @{
 */
#define DMA_SRC_INC_1BYTE               ((uint32_t)0x00000000)    /*!< 1 byte.               */
#define DMA_SRC_INC_2BYTE               ((uint32_t)0x04000000)    /*!< 2 byte.               */
#define DMA_SRC_INC_4BYTE               ((uint32_t)0x08000000)    /*!< 4 byte.               */
#define DMA_SRC_INC_NON                 ((uint32_t)0x0C000000)    /*!< Without increment.    */
/**
 *  @}
 */ /* End of group DMA_SourceInc */

/** 
 *  @defgroup DMA_SourceSize  Source Data Size
 *  @brief    Source data size.
 *  @{
 */
#define DMA_SRC_SIZE_1BYTE              ((uint32_t)0x00000000)    /*!< 1 byte.               */
#define DMA_SRC_SIZE_2BYTE              ((uint32_t)0x01000000)    /*!< 2 byte.               */
#define DMA_SRC_SIZE_4BYTE              ((uint32_t)0x02000000)    /*!< 4 byte.               */
/**
 *  @}
 */ /* End of group DMA_SourceSize */

/** 
 *  @defgroup DMA_Arbitration  Arbitration Timing
 *  @brief    Arbitration timing.
 *  @{
 */
#define DMA_ARBITRATION_1               ((uint32_t)0x00000000)    /*!< After   1 Transfer.   */
#define DMA_ARBITRATION_2               ((uint32_t)0x00004000)    /*!< After   2 Transfer.   */
#define DMA_ARBITRATION_4               ((uint32_t)0x00008000)    /*!< After   4 Transfer.   */
#define DMA_ARBITRATION_8               ((uint32_t)0x0000C000)    /*!< After   8 Transfer.   */
#define DMA_ARBITRATION_16              ((uint32_t)0x00010000)    /*!< After  16 Transfer.   */
#define DMA_ARBITRATION_32              ((uint32_t)0x00014000)    /*!< After  32 Transfer.   */
#define DMA_ARBITRATION_64              ((uint32_t)0x00018000)    /*!< After  64 Transfer.   */
#define DMA_ARBITRATION_128             ((uint32_t)0x0001C000)    /*!< After 128 Transfer.   */
#define DMA_ARBITRATION_256             ((uint32_t)0x00020000)    /*!< After 256 Transfer.   */
#define DMA_ARBITRATION_512             ((uint32_t)0x00024000)    /*!< After 512 Transfer.   */
#define DMA_ARBITRATION_NON             ((uint32_t)0x0003C000)    /*!< Without arbitration.  */
/**
 *  @}
 */ /* End of group DMA_Arbitration */

/** 
 *  @defgroup DMA_TransferNumRange  Transfer Num Range
 *  @brief    Range of Transfer Num Macro Definisiton.
 *  @brief    Range of Transfer Num be set "(DMA_TRANS_NUM_RANGE_MIN <= Value <= DMA_TRANS_NUM_RANGE_MAX)".
 *  @{
 */
#define DMA_TRANS_NUM_RANGE_MIN         ((uint32_t)0x00000001)    /*!< Minimum  Value :1    */
#define DMA_TRANS_NUM_RANGE_MAX         ((uint32_t)0x00000400)    /*!< Maximum  Value :1024 */
/**
 *  @}
 */ /* End of group DMA_TransferNumRange */

/** 
 *  @defgroup DMA_Burst  Use Burst
 *  @brief    Use burst transfer.
 *  @{
 */
#define DMA_BURST_UNUSE                 ((uint32_t)0x00000000)    /*!< Unuse.  */
#define DMA_BURST_USE                   ((uint32_t)0x00000008)    /*!< Use.    */
/**
 *  @}
 */ /* End of group DMA_Burst */

/** 
 *  @defgroup DMA_CycleControl  Cycle Control Mode
 *  @brief    DMA cycle control mode.
 *  @{
 */
#define DMA_CYCLE_MODE_DISABLE          ((uint32_t)0x00000000)    /*!< Stop cycle.                          */
#define DMA_CYCLE_MODE_BASE             ((uint32_t)0x00000001)    /*!< Basic mode.                          */
#define DMA_CYCLE_MODE_CNT_BASE         ((uint32_t)0x00000002)    /*!< Continuation Basic mode.             */
#define DMA_CYCLE_MODE_REPEAT           ((uint32_t)0x00000003)    /*!< Repeat mode.                         */
#define DMA_CYCLE_MODE_CNT_CHAIN_1      ((uint32_t)0x00000004)    /*!< Continuation Chain mode. (1st data). */
#define DMA_CYCLE_MODE_CNT_CHAIN_2      ((uint32_t)0x00000005)    /*!< Continuation Chain mode. (2nd data). */
#define DMA_CYCLE_MODE_CHAIN_1          ((uint32_t)0x00000006)    /*!< Unit Chain mode. (1st data).         */
#define DMA_CYCLE_MODE_CHAIN_2          ((uint32_t)0x00000007)    /*!< Unit Chain mode. (2nd data).         */
/**
 *  @}
 */ /* End of group DMA_CycleControl */

/** 
 *  @defgroup DMA_Priority  Priority
 *  @brief    Priority.
 *  @{
 */
#define DMA_PRIORITY_NORMAL             ((uint32_t)0x00000000)    /*!< Normal.    */
#define DMA_PRIORITY_HIGH               ((uint32_t)0x00000001)    /*!< High.      */
/**
 *  @}
 */ /* End of group DMA_Priority */

/**
 *  @}
 */ /* End of group DMA_Exported_define */


/*------------------------------------------------------------------------------*/
/*  Enumerated Type Definition                                                  */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup DMA_Exported_define DMA Exported Define
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group DMA_Exported_define */


/*------------------------------------------------------------------------------*/
/*  Structure Definition                                                        */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup DMA_Exported_typedef DMA Exported Typedef
 *  @{
 */

/*----------------------------------*/
/** 
 * @brief  Initial setting structure definenition.
 * @details  Primary(Work area) base address. \n
 * Need Size(byte) = ((The total number of the used channel) * (4 * DWORD) * 2);
 * | Use channel | The address by which setting is possible |
 * | :---        | :---                                     |
 * | 0           | 0xXXXX_XX00, 0xXXXX_XX20, 0xXXXX_XX40, 0xXXXX_XX60, \n  0xXXXX_XX80, 0xXXXX_XXA0, 0xXXXX_XXC0, 0xXXXX_XXE0 |
 * | 0 - 1       | 0xXXXX_XX00, 0xXXXX_XX40, 0xXXXX_XX80, 0xXXXX_XXC0 |
 * | 0 - 3       | 0xXXXX_XX00, 0xXXXX_XX80                 |
 * | 0 - 7       | 0xXXXX_X000, 0xXXXX_X100, 0xXXXX_X200, 0xXXXX_X300, \n  0xXXXX_X400, 0xXXXX_X500, 0xXXXX_X600, 0xXXXX_X700, \n 0xXXXX_X800, 0xXXXX_X900, 0xXXXX_XA00, 0xXXXX_XB00, \n 0xXXXX_XC00, 0xXXXX_XD00, 0xXXXX_XE00, 0xXXXX_XF00       |
 * | 0 - 15      | 0xXXXX_X000, 0xXXXX_X200, 0xXXXX_X400, 0xXXXX_X600, \n  0xXXXX_X800, 0xXXXX_XA00, 0xXXXX_XC00, 0xXXXX_XE00 |
 * | 0 - 31      | 0xXXXX_X000, 0xXXXX_X400, 0xXXXX_X800, 0xXXXX_XC00 |
*/
/*----------------------------------*/
typedef struct
{
    uint32_t baseAdd;           /*!< Primary(Work area) base address.  */
} dma_initial_setting_t;

/*----------------------------------*/
/** 
 * @brief  Channel config setting structure definenition.
 * @brief  If extended transfer isn't used, it isn't necessary.
*/
/*----------------------------------*/
typedef struct
{
    uint32_t dstInc;            /*!< Destination address increment type. 
                                    : Use @ref DMA_DestinationInc             */
    uint32_t dstSize;           /*!< Destination data size(Set it as the same size as "srcSize"). 
                                    : Use @ref DMA_DestinationSize            */
    uint32_t srcInc;            /*!< Source address increment type. 
                                    : Use @ref DMA_SourceInc                  */
    uint32_t srcSize;           /*!< Source data size(Set it as the same size as "dstSize").
                                    : Use @ref DMA_SourceSize                 */
    uint32_t arbitNum;          /*!< Arbitration timing.
                                    : Use @ref DMA_Arbitration                */
    uint32_t burst;             /*!< Use burst transfer.
                                    : Use @ref DMA_Burst                      */
} dma_ch_cfg_t;

/*----------------------------------*/
/** 
 * @brief  Channel setting structure definenition.
*/
/*----------------------------------*/
typedef struct
{
    void (*handler)(uint32_t id, TXZ_Result result);        /*!< Notity converted value.  */
    uint32_t        id;         /*!< ID: User Value.                                   */
    uint32_t        priority;   /*!< Priority.
                                    : Use @ref DMA_Priority                            */
    dma_ch_cfg_t    cfg;        /*!< Channel config setting. 
                                    : Use @ref dma_ch_cfg_t                            */
} dma_ch_setting_t;

/*----------------------------------*/
/** 
 * @brief  Channel configration structure definenition.
 * @brief  For basic transfer.
*/
/*----------------------------------*/
typedef struct
{
    uint32_t    source;       /*!< Source data start pointer.       */
    uint32_t    destination;  /*!< Destination data start pointer.  */
    uint32_t    num;          /*!< Num of transfer.
                                  : Range (DMA_TRANS_NUM_RANGE_MIN <= Value <= DMA_TRANS_NUM_RANGE_MAX)  @ref DMA_TransferNumRange */
} dma_cfg_t;

/*----------------------------------*/
/** 
 * @brief  DMA handle structure definenition.
*/
/*----------------------------------*/
typedef struct dma_handle
{
    TSB_DMA_TypeDef         *p_instance;    /*!< Registers base address.           */
    dma_initial_setting_t   init;           /*!< Initial setting.                  */
    dma_ch_setting_t        ch[DMA_CH_NUM]; /*!< Channel setting.                  */
} dma_t;

/**
 *  @}
 */ /* End of group DMA_Exported_typedef */

/*------------------------------------------------------------------------------*/
/*  Functions                                                                   */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup DMA_Exported_functions DMA Exported Functions
 *  @{
 */
TXZ_Result dma_init(dma_t *p_obj);
TXZ_Result dma_deinit(dma_t *p_obj);
TXZ_Result dma_get_error(dma_t *p_obj, uint32_t *p_err);
TXZ_Result dma_clear_error(dma_t *p_obj);
void dma_error_irq_handler(dma_t *p_obj);
void dma_irq_handler(dma_t *p_obj, uint32_t ch);
TXZ_Result dma_ch_init(dma_t *p_obj, uint32_t ch);
TXZ_Result dma_ch_deinit(dma_t *p_obj, uint32_t ch);
TXZ_Result dma_startIt(dma_t *p_obj, uint32_t ch, dma_cfg_t *p_cfg);
TXZ_Result dma_stopIt(dma_t *p_obj, uint32_t ch);
/**
 *  @}
 */ /* End of group DMA_Exported_functions */

/**
 *  @}
 */ /* End of group DMA */

/**
 *  @}
 */ /* End of group Periph_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __DMA_H */


