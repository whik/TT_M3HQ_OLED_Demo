/** 
 *******************************************************************************
 * @file    txz_dma_ex.h
 * @brief   This file provides all the functions prototypes for DMA driver.
 * @brief   Extended functionality.
 * @version V1.0.0.4
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
#ifndef __DMA_EX_H
#define __DMA_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*  Includes                                                                    */
/*------------------------------------------------------------------------------*/
#include "txz_driver_def.h"
#include "txz_dma.h"

/**
 *  @addtogroup Periph_Driver
 *  @{
 */

/** 
 *  @addtogroup DMA
 *  @{
 */
/*------------------------------------------------------------------------------*/
/*  Macro Function                                                              */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup DMA_Exported_macro
 *  @{
 */
#define DMA_EX_TRANS_NUM(x)   ((uint32_t)((uint32_t)((x) - 1) << 4))  /*!< The number of transfer times(for Channel configration control). */
/** 
 *  @}
 */ /* End of group DMA_Exported_macro */


/*------------------------------------------------------------------------------*/
/*  Macro Definition                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup DMA_Exported_define
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group DMA_Exported_define */


/*------------------------------------------------------------------------------*/
/*  Enumerated Type Definition                                                  */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup DMA_Exported_define
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
 *  @addtogroup DMA_Exported_typedef
 *  @{
 */

/*----------------------------------*/
/** 
 * @brief  Channel configration structure definenition.
 * @brief  For normal transfer.
*/
/*----------------------------------*/
typedef struct
{
    uint32_t      source;       /*!< Source data start pointer.      */
    uint32_t      destination;  /*!< Destination data start pointer. */
    uint32_t      control;      /*!< Control.                        */
} dma_normal_cfg_t;

/*----------------------------------*/
/** 
 * @brief  Channel configration structure definenition.
 * @brief  For DMA continuation transfer.
*/
/*----------------------------------*/
typedef struct
{
    uint32_t      source;       /*!< Source data start pointer.      */
    uint32_t      destination;  /*!< Destination data start pointer. */
    uint32_t      control;      /*!< Control.                        */
} dma_cnt_cfg_t;

/*----------------------------------*/
/** 
 * @brief  Channel configration structure definenition.
 * @brief  For repeat transfer.
*/
/*----------------------------------*/
typedef struct
{
    uint32_t      source;       /*!< Source data start pointer.      */
    uint32_t      destination;  /*!< Destination data start pointer. */
    uint32_t      control;      /*!< Control.                        */
} dma_repeat_cfg_t;

/*----------------------------------*/
/** 
 * @brief  Channel configration structure definenition.
 * @brief  For chain transfer.
*/
/*----------------------------------*/
typedef struct
{
    uint32_t      source;       /*!< Source chain start pointer.   */
    uint32_t      num;          /*!< Num of alternate task.          */
} dma_chain_cfg_t;

/**
 *  @}
 */ /* End of group DMA_Exported_typedef */

/*------------------------------------------------------------------------------*/
/*  Functions                                                                   */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup DMA_Exported_functions
 *  @{
 */
TXZ_Result dma_sw_request(dma_t *p_obj, uint32_t ch);
/* for normal mode */
TXZ_Result dma_normal_startIt(dma_t *p_obj, uint32_t ch, uint32_t burst, dma_normal_cfg_t *p_cfg);
TXZ_Result dma_normal_stopIt(dma_t *p_obj, uint32_t ch);
/* for Continuation normal mode */
TXZ_Result dma_normal_cnt_startIt(dma_t *p_obj, uint32_t ch, uint32_t burst, dma_cnt_cfg_t *p_cfg);
TXZ_Result dma_normal_cnt_stopIt(dma_t *p_obj, uint32_t ch);
/* for Continuation chain mode */
TXZ_Result dma_cnt_chain_startIt(dma_t *p_obj, uint32_t ch, uint32_t burst, dma_chain_cfg_t *p_cfg);
TXZ_Result dma_cnt_chain_stopIt(dma_t *p_obj, uint32_t ch);
/* for chain mode */
TXZ_Result dma_chain_startIt(dma_t *p_obj, uint32_t ch, uint32_t burst, dma_chain_cfg_t *p_cfg);
TXZ_Result dma_chain_stopIt(dma_t *p_obj, uint32_t ch);
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
#endif /* __DMA_EX_H */


