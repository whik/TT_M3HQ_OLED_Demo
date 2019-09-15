/**
 *******************************************************************************
 * @file    txz_dma_ex.c
 * @brief   This file provides API functions for DMA driver.
 * @brief   Extended functionality.
 * @version V1.0.0.8
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
#include "txz_dma_ex.h"

#if defined(__DMA_EX_H)
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
/*  Configuration                                                               */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup DMA_Private_define
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
 *  @addtogroup DMA_Private_define
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
 *  @addtogroup DMA_Private_define
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

/* no define */

/**
 *  @}
 */ /* End of group DMA_Private_typedef */


/*------------------------------------------------------------------------------*/
/*  Private Function                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup DMA_Private_fuctions
 *  @{
 */
#ifdef DEBUG
    __STATIC_INLINE int32_t check_param_compare_mode(uint32_t src1, uint32_t src2);
#endif
__STATIC_INLINE uint32_t get_alternate_address(uint32_t base, uint32_t ch);
__STATIC_INLINE uint32_t convert_transfer_num_to_if(uint32_t reg);
#ifdef DEBUG
/*--------------------------------------------------*/
/** 
  * @brief  Compare the DMA cycle control mode's parameter.
  * @param  src1    :DMA cycle control mode's parameter
  * @param  src2    :DMA cycle control mode's parameter
  * @retval DMA_PARAM_OK :Equal
  * @retval DMA_PARAM_NG :Not Equal
  * @note   Macro definition is @ref DMA_CycleControl"DMA_CYCLE_MODE_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_compare_mode(uint32_t src1, uint32_t src2)
{
    int32_t result = DMA_PARAM_NG;

    if (src1 == src2)
    {
        result = DMA_PARAM_OK;
    }

    return (result);
}
#endif

/*--------------------------------------------------*/
/** 
  * @brief  Get alternate start address.
  * @param  base :Primary base address.
  * @param  ch   :Channel.
  * @retval Alternate start address.
  * @note   -
  */
/*--------------------------------------------------*/
__STATIC_INLINE uint32_t get_alternate_address(uint32_t base, uint32_t ch)
{
    uint32_t result = get_primary_address(base, ch) + (DMA_CH_NUM * sizeof(control_data_t));

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Convert transfer num to interface.
  * @param  num :Transfer num(Register format).
  * @retval Transfer num(Interface format).
  * @note   -
  */
/*--------------------------------------------------*/
__STATIC_INLINE uint32_t convert_transfer_num_to_if(uint32_t num)
{
    uint32_t result = (uint32_t)((uint32_t)(num >> 4) + 1);

    return (result);
}
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
/*--------------------------------------------------*/
/**
  * @brief     DMA Request Self Trigger.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  */
/*--------------------------------------------------*/
TXZ_Result dma_sw_request(dma_t *p_obj, uint32_t ch)
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
    p_obj->p_instance->CHNLSWREQUEST = convert_ch_to_reg(ch);

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Start DMA normal mode.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @param     burst   :Use burst. @ref DMA_Burst.
  * @param     p_cfg   :config.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_normal_startIt(dma_t *p_obj, uint32_t ch, uint32_t burst, dma_normal_cfg_t *p_cfg)
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
    assert_param(check_param_compare_mode((p_cfg->control&CH_CFG_MASK_CYCLE_CTRL), DMA_CYCLE_MODE_BASE));
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
            uint32_t num  = 0;

            /* increment */
            switch(p_cfg->control & CH_CFG_MASK_SRC_INC)
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
            switch(p_cfg->control & CH_CFG_MASK_SRC_SIZE)
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
            /* num */
            num = convert_transfer_num_to_if((p_cfg->control & CH_CFG_MASK_TRANS_NUM));
            /* Set value. */
            *p_primary = get_end_address(p_cfg->source, inc, size, num);
        }
        /*--- destination ---*/
        {
            uint32_t inc  = 0;
            uint32_t size = 0;
            uint32_t num  = 0;

            /* increment */
            switch(p_cfg->control & CH_CFG_MASK_DST_INC)
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
            switch(p_cfg->control & CH_CFG_MASK_DST_SIZE)
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
            /* num */
            num = convert_transfer_num_to_if((p_cfg->control & CH_CFG_MASK_TRANS_NUM));
            /* Set value. */
            *(p_primary + 1) = get_end_address(p_cfg->destination, inc, size, num);
        }
        /*---- control ----*/
        *(p_primary + 2) = p_cfg->control;
    }
    /*------------------------------*/
    /*  Register Setting            */
    /*------------------------------*/
    {
        uint32_t regCh = convert_ch_to_reg(ch);

        /*--- DMAxChnlPriAltClr ---*/
        p_obj->p_instance->CHNLPRIALTCLR  = regCh;
        if (burst == DMA_BURST_USE)
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
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Stop DMA normal mode.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_normal_stopIt(dma_t *p_obj, uint32_t ch)
{
    TXZ_Result result = TXZ_SUCCESS;

    /* Now, common processing. */
    result = dma_stopIt(p_obj, ch);

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Start DMA DMA Continuation mode.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @param     burst   :Use burst. @ref DMA_Burst.
  * @param     p_cfg   :config.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_normal_cnt_startIt(dma_t *p_obj, uint32_t ch, uint32_t burst, dma_cnt_cfg_t *p_cfg)
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
    assert_param(check_param_compare_mode((p_cfg->control&CH_CFG_MASK_CYCLE_CTRL), DMA_CYCLE_MODE_CNT_BASE));
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
            uint32_t num  = 0;

            /* increment */
            switch(p_cfg->control & CH_CFG_MASK_SRC_INC)
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
            switch(p_cfg->control & CH_CFG_MASK_SRC_SIZE)
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
            /* num */
            num = convert_transfer_num_to_if((p_cfg->control & CH_CFG_MASK_TRANS_NUM));
            /* Set value. */
            *p_primary = get_end_address(p_cfg->source, inc, size, num);
        }
        /*--- destination ---*/
        {
            uint32_t inc  = 0;
            uint32_t size = 0;
            uint32_t num  = 0;

            /* increment */
            switch(p_cfg->control & CH_CFG_MASK_DST_INC)
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
            switch(p_cfg->control & CH_CFG_MASK_DST_SIZE)
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
            /* num */
            num = convert_transfer_num_to_if((p_cfg->control & CH_CFG_MASK_TRANS_NUM));
            /* Set value. */
            *(p_primary + 1) = get_end_address(p_cfg->destination, inc, size, num);
        }
        /*---- control ----*/
        *(p_primary + 2) = p_cfg->control;
    }
    /*------------------------------*/
    /*  Register Setting            */
    /*------------------------------*/
    {
        uint32_t regCh = convert_ch_to_reg(ch);

        /*--- DMAxChnlPriAltClr ---*/
        p_obj->p_instance->CHNLPRIALTCLR  = regCh;
        if (burst == DMA_BURST_USE)
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
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Stop DMA DMA Continuation mode.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_normal_cnt_stopIt(dma_t *p_obj, uint32_t ch)
{
    TXZ_Result result = TXZ_SUCCESS;

    /* Now, common processing. */
    result = dma_stopIt(p_obj, ch);

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Start DMA Continuation Chain mode.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @param     burst   :Use burst. @ref DMA_Burst.
  * @param     p_cfg   :config.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_cnt_chain_startIt(dma_t *p_obj, uint32_t ch, uint32_t burst, dma_chain_cfg_t *p_cfg)
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
    assert_param(IS_POINTER_NOT_NULL(p_cfg->num));
    /* Check the Channel. */
    assert_param(check_param_channel(DMA_CH_NUM, ch));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Channel Control Data Making */
    /*------------------------------*/
    /* Use primary. */
    {
        uint32_t *p_primary = (uint32_t *)get_primary_address(p_obj->init.baseAdd, ch);

        /*--- source ---*/
        *p_primary      = p_cfg->source + (p_cfg->num * sizeof(control_data_t) - 4);
        /*--- destination ---*/
        *(p_primary+ 1) = get_alternate_address(p_obj->init.baseAdd, ch) + sizeof(control_data_t) - 4;
        /*---- control ----*/
        *(p_primary+ 2) = (uint32_t)(DMA_DST_INC_4BYTE   | DMA_DST_SIZE_4BYTE | 
                                     DMA_SRC_INC_4BYTE   | DMA_SRC_SIZE_4BYTE |
                                     DMA_ARBITRATION_4   | convert_transfer_num_to_reg((p_cfg->num*4)) |
                                     DMA_BURST_UNUSE     | DMA_CYCLE_MODE_CNT_CHAIN_1);
    }
    /*------------------------------*/
    /*  Register Setting            */
    /*------------------------------*/
    {
        uint32_t regCh = convert_ch_to_reg(ch);

        /*--- DMAxChnlPriAltClr ---*/
        p_obj->p_instance->CHNLPRIALTCLR  = regCh;
        if (burst == DMA_BURST_USE)
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
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Stop DMA Continuation Chain mode.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_cnt_chain_stopIt(dma_t *p_obj, uint32_t ch)
{
    TXZ_Result result = TXZ_SUCCESS;

    /* Now, common processing. */
    result = dma_stopIt(p_obj, ch);

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Start DMA Chain mode.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @param     burst   :Use burst. @ref DMA_Burst.
  * @param     p_cfg   :config.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_chain_startIt(dma_t *p_obj, uint32_t ch, uint32_t burst, dma_chain_cfg_t *p_cfg)
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
    assert_param(IS_POINTER_NOT_NULL(p_cfg->num));
    /* Check the Channel. */
    assert_param(check_param_channel(DMA_CH_NUM, ch));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Channel Control Data Making */
    /*------------------------------*/
    /* Use primary. */
    {
        uint32_t *p_primary = (uint32_t *)get_primary_address(p_obj->init.baseAdd, ch);

        /*--- source ---*/
        *p_primary      = p_cfg->source + (p_cfg->num * sizeof(control_data_t) - 4);
        /*--- destination ---*/
        *(p_primary+ 1) = get_alternate_address(p_obj->init.baseAdd, ch) + sizeof(control_data_t) - 4;
        /*---- control ----*/
        *(p_primary+ 2) = (uint32_t)(DMA_DST_INC_4BYTE   | DMA_DST_SIZE_4BYTE | 
                                     DMA_SRC_INC_4BYTE   | DMA_SRC_SIZE_4BYTE |
                                     DMA_ARBITRATION_4   | convert_transfer_num_to_reg((p_cfg->num*4)) |
                                     DMA_BURST_UNUSE     | DMA_CYCLE_MODE_CHAIN_1);
    }
    /*------------------------------*/
    /*  Register Setting            */
    /*------------------------------*/
    {
        uint32_t regCh = convert_ch_to_reg(ch);

        /*--- DMAxChnlPriAltClr ---*/
        p_obj->p_instance->CHNLPRIALTCLR  = regCh;
        if (burst == DMA_BURST_USE)
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
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Stop DMA Chain mode.
  * @param     p_obj   :DMA object.
  * @param     ch      :Channel.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result dma_chain_stopIt(dma_t *p_obj, uint32_t ch)
{
    TXZ_Result result = TXZ_SUCCESS;

    /* Now, common processing. */
    result = dma_stopIt(p_obj, ch);

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

#endif /* defined(__DMA_EX_H)  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

