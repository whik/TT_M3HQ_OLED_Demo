/**
 *******************************************************************************
 * @file    txz_adc_dma.c
 * @brief   This file provides API functions for ADC driver.
 * @brief   If DMA transfer is used, it is necessary.
 * @version V1.0.0.2
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
#include "txz_adc_include.h"
#include "txz_adc_dma.h"
#include "txz_adc_ch.h"
#include "txz_dma.h"

#if defined(__ADC_DMA_H)
/**
 *  @addtogroup Periph_Driver Peripheral Driver
 *  @{
 */

/** 
 *  @addtogroup ADC
 *  @{
 */

/*------------------------------------------------------------------------------*/
/*  Configuration                                                               */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup ADC_Private_define ADC Private Define
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group ADC_Private_define */

/*------------------------------------------------------------------------------*/
/*  Macro Definition                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup ADC_Private_define ADC Private Define
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group ADC_Private_define */


/*------------------------------------------------------------------------------*/
/*  Enumerated Type Definition                                                  */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup ADC_Private_define ADC Private Define
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group ADC_Private_define */


/*------------------------------------------------------------------------------*/
/*  Structure Definition                                                        */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup ADC_Private_typedef ADC Private Typedef
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group ADC_Private_typedef */
/*------------------------------------------------------------------------------*/
/*  Variable Definition                                                        */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup ADC_Private_variable ADC Private Variable Definition
 *  @{
 */
static adc_dma_t *p_AdcDmaObj;
/**
 *  @}
 */ /* End of group ADC_Private_variable */


/*------------------------------------------------------------------------------*/
/*  Private Function                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup ADC_Private_fuctions ADC Private Fuctions
 *  @{
 */
 /*--------------------------------------------------*/
/*!
  * @fn     static void adc_dma_single_irq_handler( void )
  * @brief  IRQ Handler for single conversion done.
  * @param -
  * @retval -
  * @note   Call by Single Conversion Done IRQ Handler.
 */
/*--------------------------------------------------*/
void adc_dma_single_irq_handler( void )
{
    /*------------------------------*/
    /*  Call Handler                */
    /*------------------------------*/
    if ((p_AdcDmaObj != ADC_NULL) &&
        (p_AdcDmaObj->super.handler.single != ADC_NULL))
    {
        p_AdcDmaObj->super.handler.single(p_AdcDmaObj->super.init.id, TXZ_SUCCESS);
    }
}

/*--------------------------------------------------*/
/*!
  * @fn     static void adc_dma_continuity_irq_handler( void )
  * @brief  IRQ Handler for continuity conversion done.
  * @param -
  * @retval -
  * @note   Call by Continuity Conversion Done IRQ Handler.
 */
/*--------------------------------------------------*/
void adc_dma_continuity_irq_handler( void )
{
    /*------------------------------*/
    /*  Call Handler                */
    /*------------------------------*/
    if ((p_AdcDmaObj != ADC_NULL) &&
        (p_AdcDmaObj->super.handler.continuity != ADC_NULL))
    {
        p_AdcDmaObj->super.handler.continuity(p_AdcDmaObj->super.init.id, TXZ_SUCCESS);
    }
}

/*--------------------------------------------------*/
/*!
  * @fn     static void adc_dma_trigger_irq_handler( void )
  * @brief  IRQ Handler for trigger conversion done.
  * @param -
  * @retval -
  * @note   Call by Trigger Conversion Done IRQ Handler.
 */
/*--------------------------------------------------*/
void adc_dma_trigger_irq_handler( void )
{
    /*------------------------------*/
    /*  Call Handler                */
    /*------------------------------*/
    if ((p_AdcDmaObj!= ADC_NULL) &&
        (p_AdcDmaObj->super.handler.trigger != ADC_NULL))
    {
        p_AdcDmaObj->super.handler.trigger(p_AdcDmaObj->super.init.id, TXZ_SUCCESS);
    }
}

/*--------------------------------------------------*/
/*
  * @fn     static void transfer_done(uint32_t id, TXZ_Result result)
  * @brief     DMA Transfer Done Handler.
  * @param     id     :User ID(ADC DMA object).
  * @param     result :Result.
  * @retval    -
  * @note      This Function is called by DMA driver.
  */
/*--------------------------------------------------*/
static void transfer_done(uint32_t id, TXZ_Result result)
{
    adc_dma_t *p_obj = (adc_dma_t *)id;

    /*------------------*/
    /* Call Handler     */
    /*------------------*/
    if ((p_obj != ADC_NULL) && (p_obj->super.handler.single != ADC_NULL))
    {
        uint32_t i;
        uint32_t work;

        /* Mask Conversion Data. */
        for (i=0; i<ADC_NUM_MAX; i++)
        {
            work = *(p_obj->info.buf[i].p_data + i);
            *(p_obj->info.buf[i].p_data + i) = get_conversion_data(work);
        }
        /* Call handler.         */
        p_obj->super.handler.single(p_obj->super.init.id, result);
    }
}
/**
 *  @}
 */ /* End of group ADC_Private_functions */

/*------------------------------------------------------------------------------*/
/*  Public Function                                                             */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup ADC_Exported_functions
 *  @{
 */
/*--------------------------------------------------*/
/**
  * @brief     Initialize the ADC DMA object.
  * @param     p_obj   :ADC DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result adc_dma_init(adc_dma_t *p_obj)
{
    TXZ_Result result  = TXZ_SUCCESS;
    p_AdcDmaObj = p_obj;
    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the UART_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->init.p_obj));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Construct Superclass        */
    /*------------------------------*/
    if (adc_init(&p_obj->super) != TXZ_SUCCESS)
    {
        result = TXZ_ERROR;
    }
    /*------------------------------*/
    /*  Construct Subclass          */
    /*------------------------------*/
    if (result == TXZ_SUCCESS)
    {
        dma_ch_setting_t *p_dma = &p_obj->init.p_obj->ch[p_obj->init.ch];

        p_dma->handler       = transfer_done;
        p_dma->id            = (uint32_t)p_obj;
        p_dma->priority      = DMA_PRIORITY_NORMAL;
        if (dma_ch_init(p_obj->init.p_obj, p_obj->init.ch) != TXZ_SUCCESS)
        {
            result = TXZ_ERROR;
        }
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Release the ADC DMA object.
  * @param     p_obj   :ADC DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result adc_dma_deinit(adc_dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;
    p_AdcDmaObj = p_obj;
    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the UART_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->init.p_obj));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Destruct Subclass           */
    /*------------------------------*/
    if (dma_ch_deinit(p_obj->init.p_obj, p_obj->init.ch) != TXZ_SUCCESS)
    {
        result = TXZ_ERROR;
    }
    /*------------------------------*/
    /*  Destruct Superclass         */
    /*------------------------------*/
    if (result == TXZ_SUCCESS)
    {
        if (adc_deinit(&p_obj->super) != TXZ_SUCCESS)
        {
            result = TXZ_ERROR;
        }
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief  Start Non-Blocking DMA Single Conversion
  * @param  p_obj   :ADC DMA object.
  * @param  p_data  :Conversion Data(Destination address).
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result adc_dma_start(adc_dma_t *p_obj, uint32_t *p_data)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the ADC_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->super.p_instance));
    assert_param(IS_POINTER_NOT_NULL(p_data));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Disable Conversion          */
    /*------------------------------*/
    /*--- ADxCR0   ---*/
    p_obj->super.p_instance->CR0 = (ADxCR0_ADEN_DISABLE | ADxCR0_CNT_DISABLE);
    /*------------------------------*/
    /*  DMA Setting                 */
    /*------------------------------*/
    {
        dma_normal_cfg_t base_cfg;
        dma_cnt_cfg_t cnt_cfg;
        switch (p_obj->info.type)
        {
        case ADC_CONVERSION_CNT:
            cnt_cfg.source      = (uint32_t)(&p_obj->super.p_instance->REG0 + p_obj->info.ch);
            cnt_cfg.destination = (uint32_t)p_data;
            cnt_cfg.control     = (uint32_t)(DMA_SRC_INC_4BYTE | DMA_DST_SIZE_4BYTE  |
                                     DMA_SRC_INC_NON     | DMA_SRC_SIZE_4BYTE  |
                                     DMA_ARBITRATION_1 | DMA_EX_TRANS_NUM(ADC_DMA_TRANS_NUM) |
                                     DMA_BURST_UNUSE     | DMA_CYCLE_MODE_CNT_BASE);
            if (dma_normal_cnt_startIt(p_obj->init.p_obj, p_obj->init.ch, DMA_BURST_USE, &cnt_cfg) != TXZ_SUCCESS)
            {
                result  = TXZ_ERROR;
            }
            break;
        case ADC_CONVERSION_SGL:
            base_cfg.source      = (uint32_t)(&p_obj->super.p_instance->REG0 + p_obj->info.ch);
            base_cfg.destination = (uint32_t)p_data;
            base_cfg.control     = (uint32_t)(DMA_SRC_INC_NON | DMA_DST_SIZE_4BYTE  |
                                     DMA_SRC_INC_NON     | DMA_SRC_SIZE_4BYTE  |
                                     DMA_ARBITRATION_1 | DMA_EX_TRANS_NUM(1) |
                                     DMA_BURST_UNUSE     | DMA_CYCLE_MODE_BASE);
            if (dma_normal_startIt(p_obj->init.p_obj, p_obj->init.ch, DMA_BURST_USE, &base_cfg) != TXZ_SUCCESS)
            {
                result  = TXZ_ERROR;
            }       
            break;
        case ADC_CONVERSION_TRG:
            break;
        default:
            /* no processing */
            break;
        }
        
    }
    if (result == TXZ_SUCCESS)
    {
        uint32_t cr0 = (ADxCR0_ADEN_ENABLE | ADxCR0_CNT_DISABLE);
        uint32_t cr1 = (ADxCR1_CNTDMEN_DISABLE | ADxCR1_SGLDMEN_DISABLE | ADxCR1_TRGDMEN_DISABLE | ADxCR1_TRGEN_DISABLE);
        /*------------------------------*/
        /*  Enable Conversion           */
        /*------------------------------*/
        switch (p_obj->info.type)
        {
        case ADC_CONVERSION_CNT:
            cr0 |= ADxCR0_CNT_ENABLE;
            break;
        case ADC_CONVERSION_SGL:
            cr0 |= ADxCR0_SGL_ENABLE;
            break;
        case ADC_CONVERSION_TRG:
            break;
        default:
            /* no processing */
            break;
        }
        switch (p_obj->info.dma_interrupt)
        {
        case ADC_CONVERSION_CNT:
            cr1 |= ADxCR1_CNTDMEN_ENABLE;
            break;
        case ADC_CONVERSION_SGL:
            /*--- ADxTSET ---*/
            cr1 |= ADxCR1_SGLDMEN_ENABLE;
            break;
        case ADC_CONVERSION_TRG:
            /*--- ADxTSET ---*/
            cr1 |= ADxCR1_TRGEN_ENABLE;
            break;
        default:
            /* no processing */
            break;
        }
        /*--- ADxCR1  ---*/
        p_obj->super.p_instance->CR1 = cr1;
        /*--- ADxCR0  ---*/
        p_obj->super.p_instance->CR0 = cr0;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief  Stop Non-Blocking DMA Single Conversion.
  * @param  p_obj   :ADC DMA object.
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result adc_dma_stop(adc_dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the ADC_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->super.p_instance));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Disable Conversion          */
    /*------------------------------*/
    if (adc_stop(&p_obj->super) != TXZ_SUCCESS)
    {
        result  = TXZ_ERROR;
    }
    /*------------------------------*/
    /*  Stop DMA                    */
    /*------------------------------*/
    if (dma_normal_stopIt(p_obj->init.p_obj, p_obj->init.ch) != TXZ_SUCCESS)
    {
        result  = TXZ_ERROR;
    }

    return (result);
}
/**
 *  @}
 */ /* End of group ADC_Exported_functions */

/**
 *  @} 
 */ /* End of group ADC */

/**
 *  @} 
 */ /* End of group Periph_Driver */

#endif /* defined(__ADC_DMA_H)  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

