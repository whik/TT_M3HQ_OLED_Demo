/**
 *******************************************************************************
 * @file    txz_tspi_dma.c
 * @brief   This file provides API functions for TSPI driver.
 * @brief   If DMA transfer is used, it is necessary.
 * @version V1.0.0.5
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
#include "txz_tspi_dma.h"

#if defined(__TSPI_DMA_H)

/**
 *  @addtogroup Periph_Driver
 *  @{
 */

/** 
 *  @addtogroup TSPI
 *  @{
 */
/*------------------------------------------------------------------------------*/
/*  Configuration                                                               */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup TSPI_Private_define
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group TSPI_Private_define */

/*------------------------------------------------------------------------------*/
/*  Macro Definition                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup TSPI_Private_define
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group TSPI_Private_define */

/*------------------------------------------------------------------------------*/
/*  Enumerated Type Definition                                                  */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup TSPI_Private_define
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group TSPI_Private_define */

/*------------------------------------------------------------------------------*/
/*  Structure Definition                                                        */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup TSPI_Private_typedef
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group TSPI_Private_typedef */

/*------------------------------------------------------------------------------*/
/*  Private Function                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup TSPI_Private_fuctions
 *  @{
 */
#ifdef DEBUG
    __STATIC_INLINE int32_t check_param_tx_type(uint32_t param);
    __STATIC_INLINE int32_t check_param_rx_type(uint32_t param);
#endif /* #ifdef DEBUG */
static void tx_transfer_done(uint32_t id, TXZ_Result result);
static void rx_transfer_done(uint32_t id, TXZ_Result result);

#ifdef DEBUG
/*--------------------------------------------------*/
/** 
  * @brief  Check the Tx DMA transfer type's parameter.
  * @param  param    :Tx DMA transfer type's parameter
  * @retval TSPI_PARAM_OK :Valid
  * @retval TSPI_PARAM_NG :Invalid
  * @note   Macro definition is @ref TSPI_DMA_TransferType"TSPI_DMA_TYPE_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_tx_type(uint32_t param)
{
    int32_t result = TSPI_PARAM_NG;

    switch (param) 
    {
    case TSPI_DMA_TYPE_UNUSE:
    case TSPI_DMA_TYPE_MEM_TO_PERI:
    case TSPI_DMA_TYPE_PERI_TO_PERI:
        result = TSPI_PARAM_OK;
        break;
    default:
        /* no process */
        break;
    }

    return (result);
}

/*--------------------------------------------------*/
/** 
  * @brief  Check the Rx DMA transfer type's parameter.
  * @param  param    :Rx DMA transfer type's parameter
  * @retval TSPI_PARAM_OK :Valid
  * @retval TSPI_PARAM_NG :Invalid
  * @note   Macro definition is @ref TSPI_DMA_TransferType"TSPI_DMA_TYPE_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_rx_type(uint32_t param)
{
    int32_t result = TSPI_PARAM_NG;

    switch (param) 
    {
    case TSPI_DMA_TYPE_UNUSE:
    case TSPI_DMA_TYPE_PERI_TO_MEM:
    case TSPI_DMA_TYPE_PERI_TO_PERI:
        result = TSPI_PARAM_OK;
        break;
    default:
        /* no process */
        break;
    }

    return (result);
}
#endif /* #ifdef DEBUG */

/*--------------------------------------------------*/
/**
  * @brief     DMA TX Transfer Done Handler.
  * @param     id     :User ID(TSPI DMA object).
  * @param     result :Result.
  * @retval    -
  * @note      This Function is called by DMA driver.
  */
/*--------------------------------------------------*/
static void tx_transfer_done(uint32_t id, TXZ_Result result)
{
    tspi_dma_t *p_obj = (tspi_dma_t *)id;

    /* TSPI Transmit Handler Call. */
    if ((p_obj != TSPI_NULL) && (p_obj->super.transmit.handler != TSPI_NULL))
    {
        p_obj->super.transmit.handler(p_obj->super.init.id, result);
    }
}

/*--------------------------------------------------*/
/**
  * @brief     DMA RX Transfer Done Handler.
  * @param     id     :User ID(TSPI DMA object).
  * @param     result :Result.
  * @retval    -
  * @note      This Function is called by DMA driver.
  */
/*--------------------------------------------------*/
static void rx_transfer_done(uint32_t id, TXZ_Result result)
{
    tspi_dma_t *p_obj = (tspi_dma_t *)id;

    /* TSPI Transmit Handler Call. */
    if ((p_obj != TSPI_NULL) && (p_obj->super.receive.handler != TSPI_NULL))
    {
        p_obj->super.receive.handler(p_obj->super.init.id, result, &p_obj->super.receive.info);
    }
}
/**
 *  @}
 */ /* End of group TSPI_Private_functions */


/*------------------------------------------------------------------------------*/
/*  Public Function                                                             */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup TSPI_Exported_functions
 *  @{
 */
/*--------------------------------------------------*/
/**
  * @brief     Initialize the TSPI DMA object.
  * @param     p_obj   :TSPI DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result tspi_dma_init(tspi_dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the TSPI_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->init.p_obj));
    /* Check the parameter. */
    assert_param(check_param_tx_type(p_obj->init.tx.type));
    assert_param(check_param_rx_type(p_obj->init.rx.type));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Construct Superclass        */
    /*------------------------------*/
    if (tspi_init(&p_obj->super) != TXZ_SUCCESS)
    {
        result = TXZ_ERROR;
    }
    /*------------------------------*/
    /*  Construct Subclass          */
    /*------------------------------*/
    if (result == TXZ_SUCCESS)
    {
        __IO uint32_t cr2 = p_obj->super.p_instance->CR2;

        /*--- DMA Driver "Transmit Channel" ---*/
        if (p_obj->init.tx.type != TSPI_DMA_TYPE_UNUSE)
        {
            dma_ch_setting_t *p_dma = &p_obj->init.p_obj->ch[p_obj->init.tx.ch];

            p_dma->handler       = tx_transfer_done;
            p_dma->id            = (uint32_t)p_obj;
            p_dma->priority      = DMA_PRIORITY_NORMAL;
            if (dma_ch_init(p_obj->init.p_obj, p_obj->init.tx.ch) != TXZ_SUCCESS)
            {
                result = TXZ_ERROR;
            }
            cr2 &= ~TSPI_TX_DMA_INT_MASK;
            cr2 |=  TSPI_TX_DMA_INT_ENABLE;
        }
        /*--- DMA Driver "Receive Channel" ---*/
        if (p_obj->init.rx.type != TSPI_DMA_TYPE_UNUSE)
        {
            dma_ch_setting_t *p_dma = &p_obj->init.p_obj->ch[p_obj->init.rx.ch];

            p_dma->handler       = rx_transfer_done;
            p_dma->id            = (uint32_t)p_obj;
            p_dma->priority      = DMA_PRIORITY_NORMAL;
            if (dma_ch_init(p_obj->init.p_obj, p_obj->init.rx.ch) != TXZ_SUCCESS)
            {
                result = TXZ_ERROR;
            }
            cr2 &= ~TSPI_RX_DMA_INT_MASK;
            cr2 |=  TSPI_RX_DMA_INT_ENABLE;
        }
        /*--- TSPIxCR2 ---*/
        if (result == TXZ_SUCCESS)
        {
            p_obj->super.p_instance->CR2 = cr2;
        }
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Release the TSPI DMA object.
  * @param     p_obj   :TSPI DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result tspi_dma_deinit(tspi_dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the TSPI_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Destruct Subclass           */
    /*------------------------------*/
    /*--- DMA Driver "Transmit Channel" ---*/
    if (p_obj->init.tx.type != TSPI_DMA_TYPE_UNUSE)
    {
        __IO uint32_t cr2 = p_obj->super.p_instance->CR2;

        /*--- TSPIxCR2   ---*/
        cr2 &= ~TSPI_TX_DMA_INT_MASK;
        cr2 |=  TSPI_TX_DMA_INT_DISABLE;
        p_obj->super.p_instance->CR2 = cr2;
        /*--- DMA Driver ---*/
        if (dma_ch_deinit(p_obj->init.p_obj, p_obj->init.tx.ch) != TXZ_SUCCESS)
        {
            result = TXZ_ERROR;
        }
    }
    /*--- DMA Driver "Receive Channel" ---*/
    if (p_obj->init.rx.type != TSPI_DMA_TYPE_UNUSE)
    {
        __IO uint32_t cr2 = p_obj->super.p_instance->CR2;

        /*--- TSPIxCR2   ---*/
        cr2 &= ~TSPI_RX_DMA_INT_MASK;
        cr2 |=  TSPI_RX_DMA_INT_DISABLE;
        p_obj->super.p_instance->CR2 = cr2;
        /*--- DMA Driver ---*/
        if (dma_ch_deinit(p_obj->init.p_obj, p_obj->init.rx.ch) != TXZ_SUCCESS)
        {
            result = TXZ_ERROR;
        }
    }
    /*------------------------------*/
    /*  Destruct Superclass         */
    /*------------------------------*/
    if (tspi_deinit(&p_obj->super) != TXZ_SUCCESS)
    {
        result = TXZ_ERROR;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Discard transmit.
  * @param     p_obj   :TSPI DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      This function clears transmit's fifo, end flag and error info.
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  */
/*--------------------------------------------------*/
TXZ_Result tspi_dma_discard_transmit(tspi_dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the TSPI_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Stop DMA                    */
    /*------------------------------*/
    if (p_obj->init.tx.type != TSPI_DMA_TYPE_UNUSE)
    {
        if ( dma_normal_stopIt(p_obj->init.p_obj, p_obj->init.tx.ch) != TXZ_SUCCESS)
        {
            result = TXZ_ERROR;
        }
    }
    /*------------------------------*/
    /*  Use Super Class             */
    /*------------------------------*/
    if (tspi_discard_transmit(&p_obj->super) != TXZ_SUCCESS)
    {
        result = TXZ_ERROR;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Discard receive.
  * @param     p_obj   :TSPI DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      This function clears receive's fifo, end flag and error info.
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  */
/*--------------------------------------------------*/
TXZ_Result tspi_dma_discard_receive(tspi_dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the TSPI_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Stop DMA                    */
    /*------------------------------*/
    if (p_obj->init.rx.type != TSPI_DMA_TYPE_UNUSE)
    {
        if ( dma_normal_stopIt(p_obj->init.p_obj, p_obj->init.rx.ch) != TXZ_SUCCESS)
        {
            result = TXZ_ERROR;
        }
    }
    /*------------------------------*/
    /*  Use Super Class             */
    /*------------------------------*/
    if (tspi_discard_receive(&p_obj->super) != TXZ_SUCCESS)
    {
        result = TXZ_ERROR;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief  Transmit data. Non-Blocking Communication.
  * @param  p_obj   :TSPI DMA object.
  * @param  p_info  :The information of transmit data.
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   Asynchronous Processing.
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result tspi_dma_transmitIt(tspi_dma_t *p_obj, tspi_transmit_t *p_info)
{
    TXZ_Result result  = TXZ_SUCCESS;
    uint32_t length = 0;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the TSPI_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_info));
    /* Check the parameter of transmit. */
    if(p_obj->super.init.fmr0.fl  == TSPI_DATA_LENGTH_8)
    {
        /* 8 bit */
        assert_param(IS_POINTER_NOT_NULL(p_info->tx8.p_data));
    }
    else if ((p_obj->super.init.fmr0.fl > TSPI_DATA_LENGTH_8) && (p_obj->super.init.fmr0.fl  < TSPI_DATA_LENGTH_17) )
    {
        /* 9 - 16 bit */
        assert_param(IS_POINTER_NOT_NULL(p_info->tx16.p_data));
    }
    else
    {
        /* 17 - 32 bit */
        assert_param(IS_POINTER_NOT_NULL(p_info->tx32.p_data));
    }
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Disable Transmit            */
    /*------------------------------*/
    /*--- TSPIxTRANS ---*/
    /* Write to TXE(=0).               */
    /* Bitband Access.                 */
    //disable_TSPIxTRANS_TXE(p_obj->super.p_instance);
    /*------------------------------*/
    /*  DMA Setting                 */
    /*------------------------------*/
    {
        dma_normal_cfg_t cfg;

        cfg.destination = (uint32_t)&p_obj->super.p_instance->DR;
        length = ((p_obj->super.p_instance->FMTR0 & TSPI_DATA_LENGTH_MASK)  >> 24);
        if(length == DATA_LENGTH_8)
        {
            /* 8 bit */
            p_obj->super.transmit.info.tx8.p_data  = p_info->tx8.p_data;
            p_obj->super.transmit.info.tx8.num     = p_info->tx8.num;
            p_obj->super.transmit.info.tx8.num     = p_info->tx8.num;
            cfg.source  = (uint32_t)p_info->tx8.p_data;
            cfg.control = (uint32_t)(DMA_DST_INC_NON     | DMA_DST_SIZE_1BYTE |
                                     DMA_SRC_INC_1BYTE   | DMA_SRC_SIZE_1BYTE |
                                     DMA_ARBITRATION_1   | DMA_EX_TRANS_NUM(p_info->tx8.num) |
                                     DMA_BURST_UNUSE     | DMA_CYCLE_MODE_BASE);
        }
        else if ((length > DATA_LENGTH_8) && (length  < DATA_LENGTH_17) )
        {
            /* 9 - 16 bit */
            p_obj->super.transmit.info.tx16.p_data = p_info->tx16.p_data;
            p_obj->super.transmit.info.tx16.num    = p_info->tx16.num;
            cfg.source  = (uint32_t)p_info->tx16.p_data;
            cfg.control = (uint32_t)(DMA_DST_INC_NON     | DMA_DST_SIZE_2BYTE |
                                     DMA_SRC_INC_1BYTE   | DMA_SRC_SIZE_2BYTE |
                                     DMA_ARBITRATION_1   | DMA_EX_TRANS_NUM(p_info->tx16.num) |
                                     DMA_BURST_UNUSE     | DMA_CYCLE_MODE_BASE);
        }
        else
        {
            /* 17 - 32 bit */
            p_obj->super.transmit.info.tx32.p_data = p_info->tx32.p_data;
            p_obj->super.transmit.info.tx32.num    = p_info->tx32.num;
            cfg.source  = (uint32_t)p_info->tx32.p_data;
            cfg.control = (uint32_t)(DMA_DST_INC_NON     | DMA_DST_SIZE_4BYTE |
                                     DMA_SRC_INC_1BYTE   | DMA_SRC_SIZE_4BYTE |
                                     DMA_ARBITRATION_1   | DMA_EX_TRANS_NUM(p_info->tx32.num) |
                                     DMA_BURST_UNUSE     | DMA_CYCLE_MODE_BASE);
        }
        
        if (dma_normal_startIt(p_obj->init.p_obj, p_obj->init.tx.ch, DMA_BURST_USE, &cfg) != TXZ_SUCCESS)
        {
            result  = TXZ_ERROR;
        }
    }
    /*------------------------------*/
    /*  Enable Transmit             */
    /*------------------------------*/
    /*--- TSPIxTRANS ---*/
    /* Write to TRXE(=1).               */
    /* Check if the TSPI is already enabled */
    if((p_obj->super.p_instance->CR0 & TSPI_ENABLE) != TSPI_ENABLE)
    {
        p_obj->super.p_instance->CR0 |=  TSPI_ENABLE;
    }
    
    /* Enable TSPI Transmission Control */
    p_obj->super.p_instance->CR1 |= TSPI_TRXE_ENABLE;

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief  Receive data. Non-Blocking Communication.
  * @param  p_obj   :TSPI DMA object.
  * @param  p_info  :The information of receive buffer.
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   Asynchronous Processing.
  * @attention  "p_info->rx8(or rx16).num" must be over FIFO max(Refer @ref TSPI_FifoMax) num.
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result tspi_dma_receiveIt(tspi_dma_t *p_obj, tspi_receive_t *p_info)
{
    TXZ_Result result = TXZ_SUCCESS;
    uint32_t length = 0;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the TSPI_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_info));
    /* Check the parameter of transmit. */
    if(p_obj->super.init.fmr0.fl  == TSPI_DATA_LENGTH_8)
    {
        /* 8 bit */
        assert_param(IS_POINTER_NOT_NULL(p_info->rx8.p_data));
    }
    else if ((p_obj->super.init.fmr0.fl > TSPI_DATA_LENGTH_8) && (p_obj->super.init.fmr0.fl  < TSPI_DATA_LENGTH_17) )
    {
        /* 9 - 16 bit */
        assert_param(IS_POINTER_NOT_NULL(p_info->rx16.p_data));
    }
    else
    {
        /* 17 - 32 bit */
        assert_param(IS_POINTER_NOT_NULL(p_info->rx32.p_data));
    }
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Disable Receive             */
    /*------------------------------*/
    /* Write to RXE(=0).               */
    /* Bitband Access.                 */
    //disable_TSPIxTRANS_RXE(p_obj->super.p_instance);
    /*------------------------------*/
    /*  DMA Setting                 */
    /*------------------------------*/
    {
        dma_normal_cfg_t cfg;

        cfg.source = (uint32_t)&p_obj->super.p_instance->DR;
        length = ((p_obj->super.p_instance->FMTR0 & TSPI_DATA_LENGTH_MASK)  >> 24);
        if(length == DATA_LENGTH_8)
        {
            /* 8 bit */
            cfg.destination = (uint32_t)p_info->rx8.p_data;
            cfg.control     = (uint32_t)(DMA_DST_INC_1BYTE   | DMA_DST_SIZE_1BYTE |
                                         DMA_SRC_INC_NON     | DMA_SRC_SIZE_1BYTE |
                                         DMA_ARBITRATION_1   | DMA_EX_TRANS_NUM(p_info->rx8.num) |
                                         DMA_BURST_UNUSE     | DMA_CYCLE_MODE_BASE);
            
        }
        else if ((length > DATA_LENGTH_8) && (length  < DATA_LENGTH_17) )
        {
            /* 9 - 16 bit */
            cfg.destination = (uint32_t)p_info->rx16.p_data;
            cfg.control     = (uint32_t)(DMA_DST_INC_1BYTE   | DMA_DST_SIZE_2BYTE |
                                         DMA_SRC_INC_NON     | DMA_SRC_SIZE_2BYTE |
                                         DMA_ARBITRATION_1   | DMA_EX_TRANS_NUM(p_info->rx16.num) |
                                         DMA_BURST_UNUSE     | DMA_CYCLE_MODE_BASE);
        }
        else
        {
            /* 17 - 32 bit */
            cfg.destination = (uint32_t)p_info->rx32.p_data;
            cfg.control     = (uint32_t)(DMA_DST_INC_1BYTE   | DMA_DST_SIZE_4BYTE |
                                         DMA_SRC_INC_NON     | DMA_SRC_SIZE_4BYTE |
                                         DMA_ARBITRATION_1   | DMA_EX_TRANS_NUM(p_info->rx32.num) |
                                         DMA_BURST_UNUSE     | DMA_CYCLE_MODE_BASE);
        }
        
        if (dma_normal_startIt(p_obj->init.p_obj, p_obj->init.rx.ch, DMA_BURST_UNUSE, &cfg) != TXZ_SUCCESS)
        {
            result  = TXZ_ERROR;
        }
    }
    /*------------------------------*/
    /*  Enable Receive              */
    /*------------------------------*/
    /*--- TSPIxTRANS ---*/
    /* Write to TRXE(=1).               */
    /* Check if the TSPI is already enabled */
    if((p_obj->super.p_instance->CR0 & TSPI_ENABLE) != TSPI_ENABLE)
    {
        p_obj->super.p_instance->CR0 |=  TSPI_ENABLE;
    }
    
    /* Enable TSPI Transmission Control */
    p_obj->super.p_instance->CR1 |= TSPI_TRXE_ENABLE;

    return (result);
}

/**
 *  @}
 */ /* End of group TSPI_Exported_functions */

/**
 *  @} 
 */ /* End of group TSPI */

/**
 *  @} 
 */ /* End of group Periph_Driver */

#endif /* defined(__TSPI_DMA_H)  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

