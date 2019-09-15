/**
 *******************************************************************************
 * @file    txz_uart_dma.c
 * @brief   This file provides API functions for UART driver.
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
#include "txz_uart_include.h"
#include "txz_uart_dma.h"

#if defined(__UART_DMA_H)

/**
 *  @addtogroup Periph_Driver
 *  @{
 */

/** 
 *  @addtogroup UART
 *  @{
 */
/*------------------------------------------------------------------------------*/
/*  Configuration                                                               */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup UART_Private_define
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group UART_Private_define */

/*------------------------------------------------------------------------------*/
/*  Macro Definition                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup UART_Private_define
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group UART_Private_define */

/*------------------------------------------------------------------------------*/
/*  Enumerated Type Definition                                                  */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup UART_Private_define
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group UART_Private_define */

/*------------------------------------------------------------------------------*/
/*  Structure Definition                                                        */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup UART_Private_typedef
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group UART_Private_typedef */

/*------------------------------------------------------------------------------*/
/*  Private Function                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup UART_Private_fuctions
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
  * @retval UART_PARAM_OK :Valid
  * @retval UART_PARAM_NG :Invalid
  * @note   Macro definition is @ref UART_DMA_TransferType"UART_DMA_TYPE_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_tx_type(uint32_t param)
{
    int32_t result = UART_PARAM_NG;

    switch (param) 
    {
    case UART_DMA_TYPE_UNUSE:
    case UART_DMA_TYPE_MEM_TO_PERI:
    case UART_DMA_TYPE_PERI_TO_PERI:
        result = UART_PARAM_OK;
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
  * @retval UART_PARAM_OK :Valid
  * @retval UART_PARAM_NG :Invalid
  * @note   Macro definition is @ref UART_DMA_TransferType"UART_DMA_TYPE_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_rx_type(uint32_t param)
{
    int32_t result = UART_PARAM_NG;

    switch (param) 
    {
    case UART_DMA_TYPE_UNUSE:
    case UART_DMA_TYPE_PERI_TO_MEM:
    case UART_DMA_TYPE_PERI_TO_PERI:
        result = UART_PARAM_OK;
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
  * @param     id     :User ID(UART DMA object).
  * @param     result :Result.
  * @retval    -
  * @note      This Function is called by DMA driver.
  */
/*--------------------------------------------------*/
static void tx_transfer_done(uint32_t id, TXZ_Result result)
{
    uart_dma_t *p_obj = (uart_dma_t *)id;

    /* UART Transmit Handler Call. */
    if ((p_obj != UART_NULL) && (p_obj->super.transmit.handler != UART_NULL))
    {
        p_obj->super.transmit.handler(p_obj->super.init.id, result);
    }
}

/*--------------------------------------------------*/
/**
  * @brief     DMA RX Transfer Done Handler.
  * @param     id     :User ID(UART DMA object).
  * @param     result :Result.
  * @retval    -
  * @note      This Function is called by DMA driver.
  */
/*--------------------------------------------------*/
static void rx_transfer_done(uint32_t id, TXZ_Result result)
{
    uart_dma_t *p_obj = (uart_dma_t *)id;

    /* UART Transmit Handler Call. */
    if ((p_obj != UART_NULL) && (p_obj->super.receive.handler != UART_NULL))
    {
        p_obj->super.receive.handler(p_obj->super.init.id, result, &p_obj->super.receive.info);
    }
}
/**
 *  @}
 */ /* End of group UART_Private_functions */


/*------------------------------------------------------------------------------*/
/*  Public Function                                                             */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup UART_Exported_functions
 *  @{
 */
/*--------------------------------------------------*/
/**
  * @brief     Initialize the UART DMA object.
  * @param     p_obj   :UART DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result uart_dma_init(uart_dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the UART_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_obj->init.p_obj));
    /* Check the parameter. */
    assert_param(check_param_tx_type(p_obj->init.tx.type));
    assert_param(check_param_rx_type(p_obj->init.rx.type));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Construct Superclass        */
    /*------------------------------*/
    if (uart_init(&p_obj->super) != TXZ_SUCCESS)
    {
        result = TXZ_ERROR;
    }
    /*------------------------------*/
    /*  Construct Subclass          */
    /*------------------------------*/
    if (result == TXZ_SUCCESS)
    {
        __IO uint32_t cr1 = p_obj->super.p_instance->CR1;

        /*--- DMA Driver "Transmit Channel" ---*/
        if (p_obj->init.tx.type != UART_DMA_TYPE_UNUSE)
        {
            dma_ch_setting_t *p_dma = &p_obj->init.p_obj->ch[p_obj->init.tx.ch];

            p_dma->handler       = tx_transfer_done;
            p_dma->id            = (uint32_t)p_obj;
            p_dma->priority      = DMA_PRIORITY_NORMAL;
            if (dma_ch_init(p_obj->init.p_obj, p_obj->init.tx.ch) != TXZ_SUCCESS)
            {
                result = TXZ_ERROR;
            }
            cr1 &= ~UARTxCR1_DMATE_MASK;
            cr1 |=  UARTxCR1_DMATE_ENABLE;
        }
        /*--- DMA Driver "Receive Channel" ---*/
        if (p_obj->init.rx.type != UART_DMA_TYPE_UNUSE)
        {
            dma_ch_setting_t *p_dma = &p_obj->init.p_obj->ch[p_obj->init.rx.ch];

            p_dma->handler       = rx_transfer_done;
            p_dma->id            = (uint32_t)p_obj;
            p_dma->priority      = DMA_PRIORITY_NORMAL;
            if (dma_ch_init(p_obj->init.p_obj, p_obj->init.rx.ch) != TXZ_SUCCESS)
            {
                result = TXZ_ERROR;
            }
            cr1 &= ~UARTxCR1_DMARE_MASK;
            cr1 |=  UARTxCR1_DMARE_ENABLE;
        }
        /*--- UARTxCR1 ---*/
        if (result == TXZ_SUCCESS)
        {
            p_obj->super.p_instance->CR1 = cr1;
        }
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Release the UART DMA object.
  * @param     p_obj   :UART DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result uart_dma_deinit(uart_dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the UART_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Destruct Subclass           */
    /*------------------------------*/
    /*--- DMA Driver "Transmit Channel" ---*/
    if (p_obj->init.tx.type != UART_DMA_TYPE_UNUSE)
    {
        __IO uint32_t cr1 = p_obj->super.p_instance->CR1;

        /*--- UARTxCR1   ---*/
        cr1 &= ~UARTxCR1_DMATE_MASK;
        cr1 |=  UARTxCR1_DMATE_DISABLE;
        p_obj->super.p_instance->CR1 = cr1;
        /*--- DMA Driver ---*/
        if (dma_ch_deinit(p_obj->init.p_obj, p_obj->init.tx.ch) != TXZ_SUCCESS)
        {
            result = TXZ_ERROR;
        }
    }
    /*--- DMA Driver "Receive Channel" ---*/
    if (p_obj->init.rx.type != UART_DMA_TYPE_UNUSE)
    {
        __IO uint32_t cr1 = p_obj->super.p_instance->CR1;

        /*--- UARTxCR1   ---*/
        cr1 &= ~UARTxCR1_DMARE_MASK;
        cr1 |=  UARTxCR1_DMARE_DISABLE;
        p_obj->super.p_instance->CR1 = cr1;
        /*--- DMA Driver ---*/
        if (dma_ch_deinit(p_obj->init.p_obj, p_obj->init.rx.ch) != TXZ_SUCCESS)
        {
            result = TXZ_ERROR;
        }
    }
    /*------------------------------*/
    /*  Destruct Superclass         */
    /*------------------------------*/
    if (uart_deinit(&p_obj->super) != TXZ_SUCCESS)
    {
        result = TXZ_ERROR;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Discard transmit.
  * @param     p_obj   :UART DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      This function clears transmit's fifo, end flag and error info.
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  */
/*--------------------------------------------------*/
TXZ_Result uart_dma_discard_transmit(uart_dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the UART_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Stop DMA                    */
    /*------------------------------*/
    if (p_obj->init.tx.type != UART_DMA_TYPE_UNUSE)
    {
        if ( dma_normal_stopIt(p_obj->init.p_obj, p_obj->init.tx.ch) != TXZ_SUCCESS)
        {
            result = TXZ_ERROR;
        }
    }
    /*------------------------------*/
    /*  Use Super Class             */
    /*------------------------------*/
    if (uart_discard_transmit(&p_obj->super) != TXZ_SUCCESS)
    {
        result = TXZ_ERROR;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Discard receive.
  * @param     p_obj   :UART DMA object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      This function clears receive's fifo, end flag and error info.
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  */
/*--------------------------------------------------*/
TXZ_Result uart_dma_discard_receive(uart_dma_t *p_obj)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the UART_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Stop DMA                    */
    /*------------------------------*/
    if (p_obj->init.rx.type != UART_DMA_TYPE_UNUSE)
    {
        if ( dma_normal_stopIt(p_obj->init.p_obj, p_obj->init.rx.ch) != TXZ_SUCCESS)
        {
            result = TXZ_ERROR;
        }
    }
    /*------------------------------*/
    /*  Use Super Class             */
    /*------------------------------*/
    if (uart_discard_receive(&p_obj->super) != TXZ_SUCCESS)
    {
        result = TXZ_ERROR;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief  Transmit data. Non-Blocking Communication.
  * @param  p_obj   :UART DMA object.
  * @param  p_info  :The information of transmit data.
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   Asynchronous Processing.
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result uart_dma_transmitIt(uart_dma_t *p_obj, uart_transmit_t *p_info)
{
    TXZ_Result result  = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the UART_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_info));
    /* Check the parameter of transmit. */
    if (p_obj->super.init.sm == UART_DATA_LENGTH_9 )
    {
        /* 9 bit */
        assert_param(IS_POINTER_NOT_NULL(p_info->tx16.p_data));
    }
    else
    {
        /* 7/8 bit */
        assert_param(IS_POINTER_NOT_NULL(p_info->tx8.p_data));
    }
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Disable Transmit            */
    /*------------------------------*/
    /*--- UARTxTRANS ---*/
    /* Write to TXE(=0).               */
    /* Bitband Access.                 */
    disable_UARTxTRANS_TXE(p_obj->super.p_instance);
    /*------------------------------*/
    /*  DMA Setting                 */
    /*------------------------------*/
    {
        dma_normal_cfg_t cfg;

        cfg.destination = (uint32_t)&p_obj->super.p_instance->DR;
        if (p_obj->super.init.sm == UART_DATA_LENGTH_9)
        {
            p_obj->super.transmit.info.tx16.p_data = p_info->tx16.p_data;
            p_obj->super.transmit.info.tx16.num    = p_info->tx16.num;
            cfg.source  = (uint32_t)p_info->tx16.p_data;
            cfg.control = (uint32_t)(DMA_DST_INC_NON     | DMA_DST_SIZE_2BYTE |
                                     DMA_SRC_INC_2BYTE   | DMA_SRC_SIZE_2BYTE |
                                     DMA_ARBITRATION_1   | DMA_EX_TRANS_NUM(p_info->tx16.num) |
                                     DMA_BURST_UNUSE     | DMA_CYCLE_MODE_BASE);
        }
        else
        {
            p_obj->super.transmit.info.tx8.p_data  = p_info->tx8.p_data;
            p_obj->super.transmit.info.tx8.num     = p_info->tx8.num;
            cfg.source  = (uint32_t)p_info->tx8.p_data;
            cfg.control = (uint32_t)(DMA_DST_INC_NON     | DMA_DST_SIZE_1BYTE |
                                     DMA_SRC_INC_1BYTE   | DMA_SRC_SIZE_1BYTE |
                                     DMA_ARBITRATION_1   | DMA_EX_TRANS_NUM(p_info->tx8.num) |
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
    /*--- UARTxTRANS ---*/
    /* Write to TXE(=1).               */
    /* Bitband Access.                 */
    enable_UARTxTRANS_TXE(p_obj->super.p_instance);

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief  Receive data. Non-Blocking Communication.
  * @param  p_obj   :UART DMA object.
  * @param  p_info  :The information of receive buffer.
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   Asynchronous Processing.
  * @attention  "p_info->rx8(or rx16).num" must be over FIFO max(Refer @ref UART_FifoMax) num.
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result uart_dma_receiveIt(uart_dma_t *p_obj, uart_receive_t *p_info)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the UART_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    assert_param(IS_POINTER_NOT_NULL(p_info));
    /* Check the parameter of transmit. */
    if (p_obj->super.init.sm == UART_DATA_LENGTH_9 )
    {
        /* 9 bit */
        assert_param(IS_POINTER_NOT_NULL(p_info->rx16.p_data));
    }
    else
    {
        /* 7/8 bit */
        assert_param(IS_POINTER_NOT_NULL(p_info->rx8.p_data));
    }
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Disable Receive             */
    /*------------------------------*/
    /* Write to RXE(=0).               */
    /* Bitband Access.                 */
    disable_UARTxTRANS_RXE(p_obj->super.p_instance);
    /*------------------------------*/
    /*  DMA Setting                 */
    /*------------------------------*/
    {
        dma_normal_cfg_t cfg;

        cfg.source = (uint32_t)&p_obj->super.p_instance->DR;
        if (p_obj->super.init.sm == UART_DATA_LENGTH_9)
        {
            p_obj->super.receive.info.rx16.p_data = p_info->rx16.p_data;
            p_obj->super.receive.info.rx16.num    = p_info->rx16.num;
            cfg.destination = (uint32_t)p_info->rx16.p_data;
            cfg.control     = (uint32_t)(DMA_DST_INC_2BYTE   | DMA_DST_SIZE_2BYTE |
                                         DMA_SRC_INC_NON     | DMA_SRC_SIZE_2BYTE |
                                         DMA_ARBITRATION_1   | DMA_EX_TRANS_NUM(p_info->rx16.num) |
                                         DMA_BURST_UNUSE     | DMA_CYCLE_MODE_BASE);
        }
        else
        {
            p_obj->super.receive.info.rx8.p_data  = p_info->rx8.p_data;
            p_obj->super.receive.info.rx8.num     = p_info->rx8.num;
            cfg.destination = (uint32_t)p_info->rx8.p_data;
            cfg.control     = (uint32_t)(DMA_DST_INC_1BYTE   | DMA_DST_SIZE_1BYTE |
                                         DMA_SRC_INC_NON     | DMA_SRC_SIZE_1BYTE |
                                         DMA_ARBITRATION_1   | DMA_EX_TRANS_NUM(p_info->rx8.num) |
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
    /*--- UARTxTRANS ---*/
    /* Write to RXE(=1).               */
    /* Bitband Access.                 */
    enable_UARTxTRANS_RXE(p_obj->super.p_instance);

    return (result);
}

/**
 *  @}
 */ /* End of group UART_Exported_functions */

/**
 *  @} 
 */ /* End of group UART */

/**
 *  @} 
 */ /* End of group Periph_Driver */

#endif /* defined(__UART_DMA_H)  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

