/**
 *******************************************************************************
 * @file    txz_uart_ex.c
 * @brief   This file provides API functions for UART driver.
 * @brief   Extended functionality.
 * @version V1.0.0.1
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
#include "txz_uart_ex.h"

#if defined(__UART_EX_H)

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
    __STATIC_INLINE int32_t check_param_half_clock_start(uint32_t param);
    __STATIC_INLINE int32_t check_param_half_clock_output(uint32_t param);
#endif
#ifdef DEBUG
/*--------------------------------------------------*/
/** 
  * @brief  Check the Half Clock Mode Start Control's parameter.
  * @param  param    :Half Clock Mode Start Control's parameter
  * @retval UART_PARAM_OK :Valid
  * @retval UART_PARAM_NG :Invalid
  * @note   Macro definition is @ref UART_HalfClockStart"UART_HALF_CLOCK_START_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_half_clock_start(uint32_t param)
{
    int32_t result = UART_PARAM_NG;

    switch (param) 
    {
    case UART_HALF_CLOCK_START_TXDA:
    case UART_HALF_CLOCK_START_TXDB:
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
  * @brief  Check the Half Clock Mode Output Control's parameter.
  * @param  param    :Half Clock Mode Output Control's parameter
  * @retval UART_PARAM_OK :Valid
  * @retval UART_PARAM_NG :Invalid
  * @note   Macro definition is @ref UART_HalfClockOutput"UART_HALF_CLOCK_OUTPUT_xxxx".
  */
/*--------------------------------------------------*/
__STATIC_INLINE int32_t check_param_half_clock_output(uint32_t param)
{
    int32_t result = UART_PARAM_NG;

    switch (param) 
    {
    case UART_HALF_CLOCK_OUTPUT_1:
    case UART_HALF_CLOCK_OUTPUT_2:
        result = UART_PARAM_OK;
        break;
    default:
        /* no process */
        break;
    }

    return (result);
}
#endif
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
  * @brief     Send Break.
  * @param     p_obj   :UART object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  */
/*--------------------------------------------------*/
TXZ_Result uart_send_break(uart_t *p_obj)
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
    /*  Set Break                   */
    /*------------------------------*/
    {
        uint32_t trans = p_obj->p_instance->TRANS; 

        trans &= ~UARTxTRANS_BK_MASK;
        trans |=  UARTxTRANS_BK_SEND;
        p_obj->p_instance->TRANS = trans;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Stop Break.
  * @param     p_obj   :UART object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  */
/*--------------------------------------------------*/
TXZ_Result uart_stop_break(uart_t *p_obj)
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
    /*  Set Break                   */
    /*------------------------------*/
    {
        uint32_t trans = p_obj->p_instance->TRANS; 

        trans &= ~UARTxTRANS_BK_MASK;
        trans |=  UARTxTRANS_BK_STOP;
        p_obj->p_instance->TRANS = trans;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Enable Half Clock Mode.
  * @param     p_obj   :UART object.
  * @param     start   :Half Clock Mode Start Control. @ref UART_HalfClockStart.
  * @param     output  :Half Clock Mode Output Control. @ref UART_HalfClockOutput.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  * @attention It can be set only at "SUE = 0"(@ref UART_SettingEnable).
  */
/*--------------------------------------------------*/
TXZ_Result uart_enable_half_clock(uart_t *p_obj, uint32_t start, uint32_t output)
{
    TXZ_Result result = TXZ_SUCCESS;

    /*------------------------------*/
    /*  Parameter Check             */
    /*------------------------------*/
#ifdef DEBUG
    /* Check the UART_NULL of address. */
    assert_param(IS_POINTER_NOT_NULL(p_obj));
    /* Check the Parameter. */
    check_param_half_clock_start(start);
    check_param_half_clock_output(output);
#endif /* #ifdef DEBUG */
    /*------------------------------*/
    /*  Enable Half Clock Mode      */
    /*------------------------------*/
    {
        uint32_t cr0  = p_obj->p_instance->CR0; 
        uint32_t mask = (uint32_t)(UARTxCR0_HBSST_MASK | UARTxCR0_HBSMD_MASK | UARTxCR0_HBSEN_MASK); 

        cr0 &= ~mask;
        cr0 |= (uint32_t)(start | output | UARTxCR0_HBSEN_ENABLE);
        p_obj->p_instance->CR0 = cr0;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Disable Half Clock Mode.
  * @param     p_obj   :UART object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  * @attention It can be set only at "SUE = 0"(@ref UART_SettingEnable).
  */
/*--------------------------------------------------*/
TXZ_Result uart_disable_half_clock(uart_t *p_obj)
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
    /*  Enable Half Clock Mode      */
    /*------------------------------*/
    {
        uint32_t cr0  = p_obj->p_instance->CR0; 

        cr0 &= ~UARTxCR0_HBSEN_MASK;
        cr0 |=  UARTxCR0_HBSEN_DISABLE;
        p_obj->p_instance->CR0 = cr0;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Enable Loopback.
  * @param     p_obj   :UART object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  * @attention It can be set only at "SUE = 0"(@ref UART_SettingEnable).
  */
/*--------------------------------------------------*/
TXZ_Result uart_enable_loopback(uart_t *p_obj)
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
    /*  Enable Loopback             */
    /*------------------------------*/
    {
        uint32_t cr0  = p_obj->p_instance->CR0; 

        cr0 &= ~UARTxCR0_LPB_MASK;
        cr0 |=  UARTxCR0_LPB_ENABLE;
        p_obj->p_instance->CR0 = cr0;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Disable Loopback.
  * @param     p_obj   :UART object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  * @attention It can be set only at "SUE = 0"(@ref UART_SettingEnable).
  */
/*--------------------------------------------------*/
TXZ_Result uart_disable_loopback(uart_t *p_obj)
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
    /*  Enable Loopback             */
    /*------------------------------*/
    {
        uint32_t cr0  = p_obj->p_instance->CR0; 

        cr0 &= ~UARTxCR0_LPB_MASK;
        cr0 |=  UARTxCR0_LPB_DISABLE;
        p_obj->p_instance->CR0 = cr0;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Enable Wakeup.
  * @param     p_obj   :UART object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  * @attention It can be set only at "SUE = 0"(@ref UART_SettingEnable).
  * @attention It's effective only in case of a 9 bits UART mode, and it's ignored by other modes.
  */
/*--------------------------------------------------*/
TXZ_Result uart_enable_wakeup(uart_t *p_obj)
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
    /*  Enable Loopback             */
    /*------------------------------*/
    {
        uint32_t cr0  = p_obj->p_instance->CR0; 

        cr0 &= ~UARTxCR0_WU_MASK;
        cr0 |=  UARTxCR0_WU_ENABLE;
        p_obj->p_instance->CR0 = cr0;
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief     Disable Wakeup.
  * @param     p_obj   :UART object.
  * @retval    TXZ_SUCCESS :Success.
  * @retval    TXZ_ERROR   :Failure.
  * @note      -
  * @attention This function is not available in interrupt.
  * @attention Use after interrupt is disabled.
  * @attention It can be set only at "SUE = 0"(@ref UART_SettingEnable).
  */
/*--------------------------------------------------*/
TXZ_Result uart_disable_wakeup(uart_t *p_obj)
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
    /*  Enable Loopback             */
    /*------------------------------*/
    {
        uint32_t cr0  = p_obj->p_instance->CR0; 

        cr0 &= ~UARTxCR0_WU_MASK;
        cr0 |=  UARTxCR0_WU_DISABLE;
        p_obj->p_instance->CR0 = cr0;
    }

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

#endif /* defined(__UART_EX_H)  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

