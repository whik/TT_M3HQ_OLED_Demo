/** 
 *******************************************************************************
 * @file    txz_dma_include.h
 * @brief   This file provides internal common definition.
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
#ifndef __DMA_INCLUDE_H
#define __DMA_INCLUDE_H

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
 *  @addtogroup DMA
 *  @{
 */
/*------------------------------------------------------------------------------*/
/*  Macro Function                                                              */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup DMA_Private_macro
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group DMA_Private_macro */


/*------------------------------------------------------------------------------*/
/*  Macro Definition                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup DMA_Private_define
 *  @{
 */

/** 
 *  @defgroup DMA_NullPointer  Null Pointer
 *  @brief    NULL Pointer.
 *  @{
 */
#define DMA_NULL        ((void *)0)
/**
 *  @}
 */ /* End of group DMA_NullPointer */

/** 
 *  @defgroup DMA_ParameterResult  Parameter Result
 *  @brief    Whether the parameter is specified or not.
 *  @{
 */
#define DMA_PARAM_OK             ((int32_t)1)              /*!< Parameter is valid(specified).         */
#define DMA_PARAM_NG             ((int32_t)0)              /*!< Parameter is invalid(not specified).   */
/**
 *  @}
 */ /* End of group DMA_ParameterResult */

/** 
 *  @defgroup DMAxCfg  DMAxCfg Register
 *  @brief    DMAxCfg Register Definition.
 *  @details  Detail.
 *  | Bit   | Bit Symbol    |
 *  | :---  | :---          |
 *  | 31-1  | -             |
 *  | 0     | master_enable |
 *  @{
 */
/* master_enable */
#define CFG_MASTER_DISABLE       ((uint32_t)0x00000000)    /*!< master_enable :Disable.   */
#define CFG_MASTER_ENABLE        ((uint32_t)0x00000001)    /*!< master_enable :Enable.    */
/**
 *  @}
 */ /* End of group DMAxCfg */

/** 
 *  @defgroup DMAxCtrlBasePtr  DMAxCtrlBasePtr Register
 *  @brief    DMAxCtrlBasePtr Register Definition.
 *  @details  Detail.
 *  | Bit   | Bit Symbol    |
 *  | :---  | :---          |
 *  | 31-10 | ctrl_base_ptr |
 *  | 9-0   | -             |
 *  @{
 */
/* ctrl_base_ptr  */
#define CTRLBASEPTR_MASK         ((uint32_t)0xFFFFFC00)    /*!< ctrl_base_ptr :Mask.      */
/**
 *  @}
 */ /* End of group DMAxCtrlBasePtr */

/** 
 *  @defgroup DMAxChnlReqMaskSet  DMAxChnlReqMaskSet Register
 *  @brief    DMAxChnlReqMaskSet Register Definition.
 *  @details  Detail.
 *  | Bit   | Bit Symbol               |
 *  | :---  | :---                     |
 *  | 31    | chnl_req_mask_set (ch31) |
 *  | 30    | chnl_req_mask_set (ch30) |
 *  | 29    | chnl_req_mask_set (ch29) |
 *  | 28    | chnl_req_mask_set (ch28) |
 *  | 27    | chnl_req_mask_set (ch27) |
 *  | 26    | chnl_req_mask_set (ch26) |
 *  | 25    | chnl_req_mask_set (ch25) |
 *  | 24    | chnl_req_mask_set (ch24) |
 *  | 23    | chnl_req_mask_set (ch23) |
 *  | 22    | chnl_req_mask_set (ch22) |
 *  | 21    | chnl_req_mask_set (ch21) |
 *  | 20    | chnl_req_mask_set (ch20) |
 *  | 19    | chnl_req_mask_set (ch19) |
 *  | 18    | chnl_req_mask_set (ch18) |
 *  | 17    | chnl_req_mask_set (ch17) |
 *  | 16    | chnl_req_mask_set (ch16) |
 *  | 15    | chnl_req_mask_set (ch15) |
 *  | 14    | chnl_req_mask_set (ch14) |
 *  | 13    | chnl_req_mask_set (ch13) |
 *  | 12    | chnl_req_mask_set (ch12) |
 *  | 11    | chnl_req_mask_set (ch11) |
 *  | 10    | chnl_req_mask_set (ch10) |
 *  |  9    | chnl_req_mask_set (ch9)  |
 *  |  8    | chnl_req_mask_set (ch8)  |
 *  |  7    | chnl_req_mask_set (ch7)  |
 *  |  6    | chnl_req_mask_set (ch6)  |
 *  |  5    | chnl_req_mask_set (ch5)  |
 *  |  4    | chnl_req_mask_set (ch4)  |
 *  |  3    | chnl_req_mask_set (ch3)  |
 *  |  2    | chnl_req_mask_set (ch2)  |
 *  |  1    | chnl_req_mask_set (ch1)  |
 *  |  0    | chnl_req_mask_set (ch0)  |
 *  @{
 */
/* chnl_req_mask_set  */
#define CHNLREQMASKSET_ALL_MASK  ((uint32_t)0xFFFFFFFF)    /*!< chnl_req_mask_set :All Mask. */
/**
 *  @}
 */ /* End of group DMAxChnlReqMaskSet */

/** 
 *  @defgroup DMAxChnlEnableClr  DMAxChnlEnableClr Register
 *  @brief    DMAxChnlEnableClr Register Definition.
 *  @details  Detail.
 *  | Bit   | Bit Symbol               |
 *  | :---  | :---                     |
 *  | 31    | chnl_enable_clr (ch31)   |
 *  | 30    | chnl_enable_clr (ch30)   |
 *  | 29    | chnl_enable_clr (ch29)   |
 *  | 28    | chnl_enable_clr (ch28)   |
 *  | 27    | chnl_enable_clr (ch27)   |
 *  | 26    | chnl_enable_clr (ch26)   |
 *  | 25    | chnl_enable_clr (ch25)   |
 *  | 24    | chnl_enable_clr (ch24)   |
 *  | 23    | chnl_enable_clr (ch23)   |
 *  | 22    | chnl_enable_clr (ch22)   |
 *  | 21    | chnl_enable_clr (ch21)   |
 *  | 20    | chnl_enable_clr (ch20)   |
 *  | 19    | chnl_enable_clr (ch19)   |
 *  | 18    | chnl_enable_clr (ch18)   |
 *  | 17    | chnl_enable_clr (ch17)   |
 *  | 16    | chnl_enable_clr (ch16)   |
 *  | 15    | chnl_enable_clr (ch15)   |
 *  | 14    | chnl_enable_clr (ch14)   |
 *  | 13    | chnl_enable_clr (ch13)   |
 *  | 12    | chnl_enable_clr (ch12)   |
 *  | 11    | chnl_enable_clr (ch11)   |
 *  | 10    | chnl_enable_clr (ch10)   |
 *  |  9    | chnl_enable_clr (ch9)    |
 *  |  8    | chnl_enable_clr (ch8)    |
 *  |  7    | chnl_enable_clr (ch7)    |
 *  |  6    | chnl_enable_clr (ch6)    |
 *  |  5    | chnl_enable_clr (ch5)    |
 *  |  4    | chnl_enable_clr (ch4)    |
 *  |  3    | chnl_enable_clr (ch3)    |
 *  |  2    | chnl_enable_clr (ch2)    |
 *  |  1    | chnl_enable_clr (ch1)    |
 *  |  0    | chnl_enable_clr (ch0)    |
 *  @{
 */
/* chnl_enable_clr  */
#define CHNLENABLECLR_ALL_DISABLE   ((uint32_t)0xFFFFFFFF)    /*!< chnl_enable_clr :All Mask. */
/**
 *  @}
 */ /* End of group DMAxChnlEnableClr */

/** 
 *  @defgroup DMAxErrClr  DMAxErrClr Register
 *  @brief    DMAxErrClr Register Definition.
 *  @details  Detail.
 *  | Bit   | Bit Symbol    |
 *  | :---  | :---          |
 *  | 31-1  | -             |
 *  | 0     | err_clr       |
 *  @{
 */
/* err_clr  */
#define ERRCLR_MASK_BUS         ((uint32_t)0x00000001)    /*!< err_clr: Bus error mask.      */
#define ERRCLR_MASK_BUS_R_NON   ((uint32_t)0x00000000)    /*!< err_clr:[read]  No error.     */
#define ERRCLR_MASK_BUS_R_ERR   ((uint32_t)0x00000001)    /*!< err_clr:[read]  Error.        */
#define ERRCLR_MASK_BUS_W_CLR   ((uint32_t)0x00000001)    /*!< err_clr:[write] Clear.        */
/**
 *  @}
 */ /* End of group DMAxErrClr */

/** 
 *  @defgroup ChannelCfg  ChannelCfg
 *  @brief    ChannelCfg Definition.
 *  @details  Detail.
 *  | Bit   | Bit Symbol    |
 *  | :---  | :---          |
 *  | 31-30 | dst_inc       |
 *  | 29-28 | dst_size      |
 *  | 27-26 | src_inc       |
 *  | 25-24 | src_size      |
 *  | 23-18 | reserved      |
 *  | 17-14 | r_power       |
 *  | 13-4  | n_minus_1     |
 *  | 3     | next_useburst |
 *  | 2-0   | cycle_ctrl    |
 *  @{
 */
#define CH_CFG_MASK_DST_INC     ((uint32_t)0xC0000000)    /*!< Mask: dst_inc.      */
#define CH_CFG_MASK_DST_SIZE    ((uint32_t)0x30000000)    /*!< Mask: dst_size.     */
#define CH_CFG_MASK_SRC_INC     ((uint32_t)0x0C000000)    /*!< Mask: src_inc.      */
#define CH_CFG_MASK_SRC_SIZE    ((uint32_t)0x03000000)    /*!< Mask: src_size.     */
#define CH_CFG_MASK_TRANS_NUM   ((uint32_t)0x00003FF0)    /*!< Mask: trans num.    */
#define CH_CFG_MASK_CYCLE_CTRL  ((uint32_t)0x00000007)    /*!< Mask: cycle ctrl.   */
/**
 *  @}
 */ /* End of group ChannelCfg */

/** 
 *  @}
 */ /* End of group DMA_Private_define */


/*------------------------------------------------------------------------------*/
/*  Enumerated Type Definition                                                  */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup DMA_Private_define DMA Private Define
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group DMA_Private_define */


/*------------------------------------------------------------------------------*/
/*  Structure Definition                                                        */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup DMA_Private_typedef
 *  @{
 */

/*----------------------------------*/
/** 
 * @brief  Control data structure definenition.
*/
/*----------------------------------*/
typedef struct
{
    uint32_t srcEnd;        /*!< Source end pointer.      */
    uint32_t dstEnd;        /*!< Destination end pointer. */
    uint32_t control;       /*!< Control data.            */
    uint32_t reserved;      /*!< Reserved.                */
} control_data_t;

/**
 *  @}
 */ /* End of group DMA_Private_typedef */


/*------------------------------------------------------------------------------*/
/*  Inline Functions                                                             */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup DMA_Private_fuctions
 *  @{
 */
#ifdef DEBUG
    __STATIC_INLINE int32_t check_param_channel(uint32_t numMax, uint32_t ch);
#endif
__STATIC_INLINE uint32_t get_primary_address(uint32_t base, uint32_t ch);
__STATIC_INLINE uint32_t convert_transfer_num_to_reg(uint32_t num);
__STATIC_INLINE uint32_t convert_ch_to_reg(uint32_t ch);
__STATIC_INLINE uint32_t get_end_address(uint32_t start, uint32_t inc, uint32_t size, uint32_t num);
#ifdef DEBUG
/*--------------------------------------------------*/
/** 
  * @brief  Check the channel no.
  * @param  numMax   :Channel Max Num.
  * @param  ch       :Channel No.
  * @retval DMA_PARAM_OK :Valid
  * @retval DMA_PARAM_NG :Invalid
  * @note   -
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_channel(uint32_t numMax, uint32_t ch)
{
    int32_t result = DMA_PARAM_NG;

    if (ch < numMax)
    {
        result = DMA_PARAM_OK;
    }

    return (result);
}
#endif

/*--------------------------------------------------*/
/** 
  * @brief  Get primary start address.
  * @param  base :Primary base address.
  * @param  ch   :Channel.
  * @retval Primary start address.
  * @note   -
  */
/*--------------------------------------------------*/
__STATIC_INLINE uint32_t get_primary_address(uint32_t base, uint32_t ch)
{
    uint32_t result = base + (uint32_t)(ch * sizeof(control_data_t));

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Convert transfer num to register.
  * @param  num :Transfer num(Interface format).
  * @retval Transfer num(Register format).
  * @note   -
  */
/*--------------------------------------------------*/
__STATIC_INLINE uint32_t convert_transfer_num_to_reg(uint32_t num)
{
    uint32_t result = (uint32_t)((uint32_t)(num - 1) << 4);

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Convert channel to register.
  * @param  ch :Channel(Interface format).
  * @retval Channel(Register format).
  * @note   -
  */
/*--------------------------------------------------*/
__STATIC_INLINE uint32_t convert_ch_to_reg(uint32_t ch)
{
    uint32_t result = (uint32_t)((uint32_t)1 << (uint8_t)ch);

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Get Tansfer End Address.
  * @param  start :Start Address.
  * @param  inc   :Address increment type.
  * @param  size  :One data size.
  * @param  num   :Num of transfer data. 
  * @retval Tansfer End Address.
  * @note   Must be set (num > 0).
  */
/*--------------------------------------------------*/
__STATIC_INLINE uint32_t get_end_address(uint32_t start, uint32_t inc, uint32_t size, uint32_t num)
{
    uint32_t result = (uint32_t)(start + (uint32_t)((uint32_t)(num - 1) * inc));

    return (result);
}

/**
 *  @}
 */ /* End of group DMA_Private_functions */

/**
 *  @}
 */ /* End of group DMA */

/**
 *  @}
 */ /* End of group Periph_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __DMA_INCLUDE_H */


