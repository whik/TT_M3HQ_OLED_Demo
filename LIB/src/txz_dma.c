/**
 *******************************************************************************
 * @file    txz_dma.c
 * @brief   This file provides API functions for DMA driver.
 * @version V1.0.0.6
 * $Date:: 2018-01-22 15:14:05 #$
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA MICROELECTRONICS CORPORATION 2017 All rights reserved
 *******************************************************************************
 */

#ifdef __cplusplus
 extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*  Includes                                                                    */
/*------------------------------------------------------------------------------*/
#include "txz_dma_include.h"
#include "txz_dma.h"

#if defined(__DMA_H)
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
 *  @defgroup DMA_Private_macro DMA Private Macro
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group DMA_Private_macro */


/*------------------------------------------------------------------------------*/
/*  Configuration                                                               */
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
/*  Macro Definition                                                            */
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
 *  @defgroup DMA_Private_typedef DMA Private Typedef
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group DMA_Private_typedef */


/*------------------------------------------------------------------------------*/
/*  Private Function                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup DMA_Private_fuctions DMA Private Fuctions
 *  @{
 */
#ifdef DEBUG
    __STATIC_INLINE int32_t check_param_primary_base_address(uint32_t num, uint32_t param);
    __STATIC_INLINE int32_t check_param_priority(uint32_t param);
    __STATIC_INLINE int32_t check_param_burst(uint32_t param);
    __STATIC_INLINE int32_t check_param_dest_inc(uint32_t param);
    __STATIC_INLINE int32_t check_param_dest_size(uint32_t param);
    __STATIC_INLINE int32_t check_param_src_inc(uint32_t param);
    __STATIC_INLINE int32_t check_param_src_size(uint32_t param);
    __STATIC_INLINE int32_t check_param_arbitration_num(uint32_t param);
    __STATIC_INLINE int32_t check_param_transfer_num(uint32_t param);
#endif
#ifdef DEBUG
/*--------------------------------------------------*/
/** 
  * @brief  Check the primary base address.
  * @param  num      :Num of total channel.
  * @param  param    :Primary base address.
  * @retval DMA_PARAM_OK :Valid
  * @retval DMA_PARAM_NG :Invalid
  * @note   -
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_primary_base_address(uint32_t num, uint32_t param)
{
    int32_t result = DMA_PARAM_NG;

    if (num == 1)
    {
        /* 0xXXXX_XX00, 0xXXXX_XX20, 0xXXXX_XX40, 0xXXXX_XX60 */
        /* 0xXXXX_XX80, 0xXXXX_XXA0, 0xXXXX_XXC0, 0xXXXX_XXE0 */
        if ((param % 0x20) == 0)
        {
            result = DMA_PARAM_OK;
        }
    }
    else if (num <= 2)
    {
        /* 0xXXXX_XX00, 0xXXXX_XX40, 0xXXXX_XX80, 0xXXXX_XXC0 */
        if ((param % 0x40) == 0)
        {
            result = DMA_PARAM_OK;
        }
    }
    else if (num <= 4)
    {
        /* 0xXXXX_XX00, 0xXXXX_XX80 */
        if ((param % 0x80) == 0)
        {
            result = DMA_PARAM_OK;
        }
    }
    else if (num <= 8)
    {
        /* 0xXXXX_X000, 0xXXXX_X100, 0xXXXX_X200, 0xXXXX_X300 */
        /* 0xXXXX_X400, 0xXXXX_X500, 0xXXXX_X600, 0xXXXX_X700 */
        /* 0xXXXX_X800, 0xXXXX_X900, 0xXXXX_XA00, 0xXXXX_XB00 */
        /* 0xXXXX_XC00, 0xXXXX_XD00, 0xXXXX_XE00, 0xXXXX_XF00 */
        if ((param % 0x100) == 0)
        {
            result = DMA_PARAM_OK;
        }
    }
    else if (num <= 16)
    {
        /* 0xXXXX_X000, 0xXXXX_X200, 0xXXXX_X400, 0xXXXX_X600 */
        /* 0xXXXX_X800, 0xXXXX_XA00, 0xXXXX_XC00, 0xXXXX_XE00 */
        if ((param % 0x200) == 0)
        {
            result = DMA_PARAM_OK;
        }
    }
    else if (num <= 32)
    {
        /* 0xXXXX_X000, 0xXXXX_X400, 0xXXXX_X800, 0xXXXX_XC00 */
        if ((param % 0x400) == 0)
        {
            result = DMA_PARAM_OK;
        }
    }

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Check the Priority's parameter.
  * @param  param    :Priority's parameter
  * @retval DMA_PARAM_OK :Valid
  * @retval DMA_PARAM_NG :Invalid
  * @note   Macro definition is @ref DMA_Priority"DMA_PRIORITY_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_priority(uint32_t param)
{
    int32_t result = DMA_PARAM_NG;

    switch(param)
    {
    case DMA_PRIORITY_NORMAL:
    case DMA_PRIORITY_HIGH:
        result = DMA_PARAM_OK;
        break;
    default:
        /* no process */
        break;
    }

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Check the Use Burst's parameter.
  * @param  param    :Use Burst's parameter
  * @retval DMA_PARAM_OK :Valid
  * @retval DMA_PARAM_NG :Invalid
  * @note   Macro definition is @ref DMA_Burst"DMA_BURST_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_burst(uint32_t param)
{
    int32_t result = DMA_PARAM_NG;

    switch(param)
    {
    case DMA_BURST_UNUSE:
    case DMA_BURST_USE:
        result = DMA_PARAM_OK;
        break;
    default:
        /* no process */
        break;
    }

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Check the Destination Address Increment Type's parameter.
  * @param  param    :Destination Address Increment Type's parameter
  * @retval DMA_PARAM_OK :Valid
  * @retval DMA_PARAM_NG :Invalid
  * @note   Macro definition is @ref DMA_DestinationInc"DMA_DST_INC_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_dest_inc(uint32_t param)
{
    int32_t result = DMA_PARAM_NG;

    switch(param)
    {
    case DMA_DST_INC_1BYTE:
    case DMA_DST_INC_2BYTE:
    case DMA_DST_INC_4BYTE:
    case DMA_DST_INC_NON:
        result = DMA_PARAM_OK;
        break;
    default:
        /* no process */
        break;
    }

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Check the Destination Data Size's parameter.
  * @param  param    :Destination Data Size's parameter
  * @retval DMA_PARAM_OK :Valid
  * @retval DMA_PARAM_NG :Invalid
  * @note   Macro definition is @ref DMA_DestinationSize"DMA_DST_SIZE_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_dest_size(uint32_t param)
{
    int32_t result = DMA_PARAM_NG;

    switch(param)
    {
    case DMA_DST_SIZE_1BYTE:
    case DMA_DST_SIZE_2BYTE:
    case DMA_DST_SIZE_4BYTE:
        result = DMA_PARAM_OK;
        break;
    default:
        /* no process */
        break;
    }

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Check the Source Address Increment Type's parameter.
  * @param  param    :Source Address Increment Type's parameter
  * @retval DMA_PARAM_OK :Valid
  * @retval DMA_PARAM_NG :Invalid
  * @note   Macro definition is @ref DMA_SourceInc"DMA_SRC_INC_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_src_inc(uint32_t param)
{
    int32_t result = DMA_PARAM_NG;

    switch(param)
    {
    case DMA_SRC_INC_1BYTE:
    case DMA_SRC_INC_2BYTE:
    case DMA_SRC_INC_4BYTE:
    case DMA_SRC_INC_NON:
        result = DMA_PARAM_OK;
        break;
    default:
        /* no process */
        break;
    }

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Check the Source Data Size's parameter.
  * @param  param    :Source Data Size's parameter
  * @retval DMA_PARAM_OK :Valid
  * @retval DMA_PARAM_NG :Invalid
  * @note   Macro definition is @ref DMA_SourceSize"DMA_SRC_SIZE_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_src_size(uint32_t param)
{
    int32_t result = DMA_PARAM_NG;

    switch(param)
    {
    case DMA_SRC_SIZE_1BYTE:
    case DMA_SRC_SIZE_2BYTE:
    case DMA_SRC_SIZE_4BYTE:
        result = DMA_PARAM_OK;
        break;
    default:
        /* no process */
        break;
    }

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Check the Arbitration Timing's parameter.
  * @param  param    :Arbitration Timing's parameter
  * @retval DMA_PARAM_OK :Valid
  * @retval DMA_PARAM_NG :Invalid
  * @note   Macro definition is @ref DMA_Arbitration"DMA_ARBITRATION_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_arbitration_num(uint32_t param)
{
    int32_t result = DMA_PARAM_NG;

    switch(param)
    {
    case DMA_ARBITRATION_1:
    case DMA_ARBITRATION_2:
    case DMA_ARBITRATION_4:
    case DMA_ARBITRATION_8:
    case DMA_ARBITRATION_16:
    case DMA_ARBITRATION_32:
    case DMA_ARBITRATION_64:
    case DMA_ARBITRATION_128:
    case DMA_ARBITRATION_256:
    case DMA_ARBITRATION_512:
    case DMA_ARBITRATION_NON:
        result = DMA_PARAM_OK;
        break;
    default:
        /* no process */
        break;
    }

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Check the Transfer Num Range's parameter.
  * @param  param    :Transfer Num Range's parameter
  * @retval ADC_PARAM_OK :Valid
  * @retval ADC_PARAM_NG :Invalid
  * @note   Macro definition is @ref DMA_TransferNumRange"DMA_TRANS_NUM_RANGE_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_transfer_num(uint32_t param)
{
    int32_t result = DMA_PARAM_NG;

    if ((DMA_TRANS_NUM_RANGE_MIN <= param) && (param <= DMA_TRANS_NUM_RANGE_MAX))
    {
        result = DMA_PARAM_OK;
    }

    return (result);
}
#endif
/**
 *  @}
 */ /* End of group DMA_Private_functions */

/*------------------------------------------------------------------------------*/
/*  Public Function                                                             */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup DMA_Exported_functions
 *  @{
 */
/*==========================*/
/*  Common                  */
/*==========================*/
/*--------------------------------------------------*/
/**
  * @brief     Initialize the DMA object.
  * @param     p_obj   :DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_init(dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the DMA_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->p_instance));
    /* Check the parameter of Primary Base Address. */
    assert_param(check_param_primary_base_address(DMA_CH_NUM, p_obj->init.baseAdd));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Register Setting            */
    /*------------------------------*/
    /*--- DMAxCtrlBasePtr    ---*/
    p_obj->p_instance->CTRLBASEPTR     = (CTRLBASEPTR_MASK & p_obj->init.baseAdd);
    /*--- DMAxChnlReqMaskSet ---*/
    p_obj->p_instance->CHNLREQMASKSET  = CHNLREQMASKSET_ALL_MASK;
    /*--- DMAxCfg            ---*/
    p_obj->p_instance->CFG             = CFG_MASTER_ENABLE;

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Release the DMA object.
  * @param     p_obj   :DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_deinit(dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the DMA_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->p_instance));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Register Setting            */
    /*------------------------------*/
    /*--- DMAxCfg            ---*/
    p_obj->p_instance->CFG             = CFG_MASTER_DISABLE;
    /*--- DMAxChnlEnableClr  ---*/
    p_obj->p_instance->CHNLENABLECLR   = CHNLENABLECLR_ALL_DISABLE;
    /*--- DMAxChnlReqMaskSet ---*/
    p_obj->p_instance->CHNLREQMASKSET  = CHNLREQMASKSET_ALL_MASK;
    /*--- DMAxErrClr         ---*/
    p_obj->p_instance->ERRCLR          = ERRCLR_MASK_BUS_W_CLR;

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     IRQ handler.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @retval    -
  * @note      -
  * @attention -
  */
/*--------------------------------------------------*/
void dma_irq_handler(dma_t *p_obj, uint32_t ch)
{
    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the DMA_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->p_instance));
    /* Check the Channel. */
    assert_param(check_param_channel(DMA_CH_NUM, ch));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /* Interrupt Check              */
    /*------------------------------*/
    /* Check the interrupt flag. */
    if (ch < DMA_CH_NUM)
    {
        if (p_obj->ch[ch].handler != DMA_NULL)
        {
            uint32_t regCh = convert_ch_to_reg(ch);

            /*>>> To stop occurrence of ABnormal END interrupt. */
            /*--- DMAxChnlReqMaskSet  ---*/
            p_obj->p_instance->CHNLREQMASKSET = regCh;
            /*--- DMAxChnlEnableSet   ---*/
            p_obj->p_instance->CHNLENABLESET  = regCh;
            /*<<< To stop occurrence of ABnormal END interrupt. */
            /* Call handler. */
            p_obj->ch[ch].handler(p_obj->ch[ch].id, TXZ_SUCCESS);
        }
    }
}

/*--------------------------------------------------*/
/**
  * @brief     Error IRQ handler.
  * @param     p_obj   :DMA object.
  * @retval    -
  * @note      -
  * @attention -
  */
/*--------------------------------------------------*/
void dma_error_irq_handler(dma_t *p_obj)
{
    uint32_t i;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the DMA_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->p_instance));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /* Interrupt Check              */
    /*------------------------------*/
    /* Check the interrupt flag. */
    for (i=0; i<DMA_CH_NUM; i++)
    {
        /* Call handler. */
        if (p_obj->ch[i].handler != DMA_NULL)
        {
            p_obj->ch[i].handler(p_obj->ch[i].id, TXZ_ERROR);
        }
    }
}

/*--------------------------------------------------*/
/**
  * @brief     Get Error.
  * @details   Error bits.
  * | Bit   | Bit Symbol | Function           |
  * | :---  | :---       | :---               |
  * | 31-1  | -          | -                  |
  * | 0     | err_clr    | Bus Error.         |
  * 
  * @param     p_obj   :DMA object.
  * @param     p_err   :Destination address.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention -
  */
/*--------------------------------------------------*/
TXZ_Result dma_get_error(dma_t *p_obj, uint32_t *p_err)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the DMA_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->p_instance));
    assert_param(IS_POINTER_NOT_NULL(p_err));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Register Read               */
    /*------------------------------*/
    /*--- DMAxErrClr ---*/
    *p_err = p_obj->p_instance->ERRCLR;

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Clear Error.
  * @param     p_obj   :DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention -
  */
/*--------------------------------------------------*/
TXZ_Result dma_clear_error(dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the DMA_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->p_instance));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Register Setting            */
    /*------------------------------*/
    /*--- DMAxErrClr ---*/
    p_obj->p_instance->ERRCLR = ERRCLR_MASK_BUS_W_CLR;

    return (result);
}

/*==========================*/
/*  Channel                 */
/*==========================*/
/*--------------------------------------------------*/
/**
  * @brief     Initialize the DMA channel object.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_ch_init(dma_t *p_obj, uint32_t ch)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the DMA_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->p_instance));
    /* Check the Channel. */
    assert_param(check_param_channel(DMA_CH_NUM, ch));
    /* Check the Parameter. */
    assert_param(check_param_priority(p_obj->ch[ch].priority));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Register Setting            */
    /*------------------------------*/
    {
        uint32_t regCh = convert_ch_to_reg(ch);

        if (p_obj->ch[ch].priority == DMA_PRIORITY_HIGH)
        {
            /*--- DMAxChnlPrioritySet ---*/
            /* High priority. */
            p_obj->p_instance->CHNLPRIORITYSET = regCh;
        }
        else
        {
            /*--- DMAxChnlPriorityClr ---*/
            /* Low priority.  */
            p_obj->p_instance->CHNLPRIORITYCLR = regCh;
        }
        /*>>> To stop occurrence of ABnormal END interrupt. */
        /*--- DMAxChnlReqMaskSet  ---*/
        p_obj->p_instance->CHNLREQMASKSET = regCh;
        /*--- DMAxChnlEnableSet   ---*/
        p_obj->p_instance->CHNLENABLESET  = regCh;
        /*<<< To stop occurrence of ABnormal END interrupt. */
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Release the DMA channel object.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_ch_deinit(dma_t *p_obj, uint32_t ch)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the DMA_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->p_instance));
    /* Check the Channel. */
    assert_param(check_param_channel(DMA_CH_NUM, ch));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Register Setting            */
    /*------------------------------*/
    {
        uint32_t regCh = convert_ch_to_reg(ch);

        /*--- DMAxChnlReqMaskSet  ---*/
        p_obj->p_instance->CHNLREQMASKSET  = regCh;
        /*--- DMAxChnlEnableClr   ---*/
        p_obj->p_instance->CHNLENABLECLR   = regCh;
        /*--- DMAxChnlPriorityClr ---*/
        p_obj->p_instance->CHNLPRIORITYCLR = regCh;
    }
    /*------------------------------*/
    /*  Clear Information           */
    /*------------------------------*/
    p_obj->ch[ch].handler = DMA_NULL;

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Start DMA mode.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @param     p_cfg   :config.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_startIt(dma_t *p_obj, uint32_t ch, dma_cfg_t *p_cfg)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the DMA_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->p_instance));
    assert_param(IS_POINTER_NOT_NULL(p_cfg));
    assert_param(IS_POINTER_NOT_NULL(p_cfg->source));
    assert_param(IS_POINTER_NOT_NULL(p_cfg->destination));
    /* Check the Channel. */
    assert_param(check_param_channel(DMA_CH_NUM, ch));
    /* Check the Parameter. */
    assert_param(check_param_transfer_num(p_cfg->num));
    assert_param(check_param_dest_inc(p_obj->ch[ch].cfg.dstInc));
    assert_param(check_param_dest_size(p_obj->ch[ch].cfg.dstSize));
    assert_param(check_param_src_inc(p_obj->ch[ch].cfg.srcInc));
    assert_param(check_param_src_size(p_obj->ch[ch].cfg.srcSize));
    assert_param(check_param_arbitration_num(p_obj->ch[ch].cfg.arbitNum));
    assert_param(check_param_burst(p_obj->ch[ch].cfg.burst));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Channel Control Data Making */
    /*------------------------------*/
    /* Use primary. */
    {
        uint32_t *p_primary = (uint32_t *)get_primary_address(p_obj->init.baseAdd, ch);

        /*--- source ---*/
        {
            uint32_t inc  = 0;
            uint32_t size = 0;

            /* increment */
            switch(p_obj->ch[ch].cfg.srcInc)
            {
            case DMA_SRC_INC_1BYTE:
                inc  = 1;
                break;
            case DMA_SRC_INC_2BYTE:
                inc  = 2;
                break;
            case DMA_SRC_INC_4BYTE:
                inc  = 4;
                break;
            default:
                inc  = 0;
                break;
            }
            /* size */
            switch(p_obj->ch[ch].cfg.srcSize)
            {
            case DMA_SRC_SIZE_1BYTE:
                size  = 1;
                break;
            case DMA_SRC_SIZE_2BYTE:
                size  = 2;
                break;
            case DMA_SRC_SIZE_4BYTE:
                size  = 4;
                break;
            default:
                size  = 0;
                break;
            }
            /* Set value. */
            *p_primary = get_end_address(p_cfg->source, inc, size, p_cfg->num);
        }
        /*--- destination ---*/
        {
            uint32_t inc  = 0;
            uint32_t size = 0;

            /* increment */
            switch(p_obj->ch[ch].cfg.dstInc)
            {
            case DMA_DST_INC_1BYTE:
                inc  = 1;
                break;
            case DMA_DST_INC_2BYTE:
                inc  = 2;
                break;
            case DMA_DST_INC_4BYTE:
                inc  = 4;
                break;
            default:
                inc  = 0;
                break;
            }
            /* size */
            switch(p_obj->ch[ch].cfg.dstSize)
            {
            case DMA_DST_SIZE_1BYTE:
                size  = 1;
                break;
            case DMA_DST_SIZE_2BYTE:
                size  = 2;
                break;
            case DMA_DST_SIZE_4BYTE:
                size  = 4;
                break;
            default:
                size  = 0;
                break;
            }
            /* Set value. */
            *(p_primary + 1) = get_end_address(p_cfg->destination, inc, size, p_cfg->num);
        }
        /*---- control ----*/
        {
            uint32_t control;

            /* Use auto mode. */
            control = (uint32_t)(p_obj->ch[ch].cfg.dstInc   | p_obj->ch[ch].cfg.dstSize | 
                                 p_obj->ch[ch].cfg.srcInc   | p_obj->ch[ch].cfg.srcSize |
                                 p_obj->ch[ch].cfg.arbitNum | convert_transfer_num_to_reg(p_cfg->num) |
                                 DMA_BURST_UNUSE            |  DMA_CYCLE_MODE_CNT_BASE);
            *(p_primary + 2) = control;
        }
    }
    /*------------------------------*/
    /*  Register Setting            */
    /*------------------------------*/
    {
        uint32_t regCh = convert_ch_to_reg(ch);

        /*--- DMAxChnlPriAltClr ---*/
        p_obj->p_instance->CHNLPRIALTCLR  = regCh;
        if (p_obj->ch[ch].cfg.burst == DMA_BURST_USE)
        {
            /*--- DMAxChnlUseburstSet ---*/
            /* Burst transfer. */
            p_obj->p_instance->CHNLUSEBURSTSET = regCh;
        }
        else
        {
            /*--- DMAxChnlUseburstClr ---*/
            /* Single transfer. */
            p_obj->p_instance->CHNLUSEBURSTCLR = regCh;
        }
        /*--- DMAxChnlReqMaskClr  ---*/
        p_obj->p_instance->CHNLREQMASKCLR = regCh;
        /*--- DMAxChnlSwRequest   ---*/
        p_obj->p_instance->CHNLSWREQUEST  = regCh;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Stop DMA mode.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_stopIt(dma_t *p_obj, uint32_t ch)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the DMA_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->p_instance));
    /* Check the Channel. */
    assert_param(check_param_channel(DMA_CH_NUM, ch));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Register Setting            */
    /*------------------------------*/
    {
        uint32_t regCh = convert_ch_to_reg(ch);

        /*--- DMAxChnlReqMaskSet  ---*/
        p_obj->p_instance->CHNLREQMASKSET = regCh;
    }

    return (result);
}

/**
 *  @}
 */ /* End of group DMA_Exported_functions */

/**
 *  @} 
 */ /* End of group DMA */

/**
 *  @} 
 */ /* End of group Periph_Driver */

#endif /* defined(__DMA_H)  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

