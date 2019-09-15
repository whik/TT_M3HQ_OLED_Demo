/** 
 *******************************************************************************
 * @file    txz_adc_dma.h
 * @brief   This file provides all the functions prototypes for ADC driver.
 * @brief   If DMA transfer is used, it is necessary.
 * @version V1.0.0.0
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
#ifndef __ADC_DMA_H
#define __ADC_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*  Includes                                                                    */
/*------------------------------------------------------------------------------*/
#include "txz_adc.h"
#include "txz_dma_ex.h"

/**
 *  @addtogroup Periph_Driver Peripheral Driver
 *  @{
 */

/** 
 *  @defgroup ADC ADC
 *  @brief    ADC Driver.
 *  @{
 */
/*------------------------------------------------------------------------------*/
/*  Macro Definition                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup ADC_Exported_define ADC Exported Define
 *  @{
 */

/* no define */

/**
 *  @}
 */ /* End of group ADC_Exported_define */

/*------------------------------------------------------------------------------*/
/*  Enumerated Type Definition                                                  */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup ADC_Exported_define ADC Exported Define
 *  @{
 */

#define ADC_DMA_TRANS_NUM 2

/**
 *  @}
 */ /* End of group ADC_Exported_define */

/*------------------------------------------------------------------------------*/
/*  Structure Definition                                                        */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup ADC_Exported_typedef ADC Exported Typedef
 *  @{
 */
/*----------------------------------*/
/** 
 * @brief  Initial setting structure definenition.
*/
/*----------------------------------*/
typedef struct
{
    dma_t    *p_obj;       /*!< DMA object address.  */
    uint32_t ch;           /*!< DMA ADC channel.     */
} adc_dma_initial_setting_t;

/*----------------------------------*/
/** 
 * @brief  DMA data information structure definenition.
 * @brief  When data length definenition is "8bit", use this.
*/
/*----------------------------------*/
typedef struct
{
    uint8_t *p_data;     /*!< The buffer to transmit data.   */
    uint32_t num;        /*!< The number of transmit data.   */
} adc_dma_data8_t;

/*----------------------------------*/
/*! @struct adc_dma_internal_info_t
    @brief  Driver DMA internal information structure definenition.
*/
/*----------------------------------*/
typedef struct
{
    uint32_t ch;            /*!< ADC channel.
                                                                */
    uint32_t dma_interrupt; /*!< Interrupt Enable/Disable.
                                : Use @ref adc_dma_int_t.       */
    uint32_t type;          /*!< Conversion Type.
                                : Use @ref adc_conversion_t.    */
    adc_dma_data8_t buf[ADC_NUM_MAX];
} adc_dma_internal_info_t;
/*----------------------------------*/
/** 
 * @brief  ADC handle structure definenition.
*/
/*----------------------------------*/
typedef struct
{
    adc_t                       super;  /*!< ADC super class. 
                                            : Use @ref adc_t                       */
    adc_dma_initial_setting_t   init;   /*!< Initial setting.
                                            : Use @ref adc_dma_initial_setting_t   */
    adc_dma_internal_info_t   info;   /*!< Initial setting.
                                            : Use @ref adc_dma_internal_info_t   */
} adc_dma_t;

/**
 *  @}
 */ /* End of group ADC_Exported_typedef */

/*------------------------------------------------------------------------------*/
/*  Functions                                                                   */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup ADC_Exported_functions ADC Exported Functions
 *  @{
 */
void adc_dma_single_irq_handler( void );
void adc_dma_continuity_irq_handler( void );
void adc_dma_trigger_irq_handler( void );
TXZ_Result adc_dma_init(adc_dma_t *p_obj);
TXZ_Result adc_dma_deinit(adc_dma_t *p_obj);
TXZ_Result adc_dma_start(adc_dma_t *p_obj, uint32_t *p_data);
TXZ_Result adc_dma_stop(adc_dma_t *p_obj);
/**
 *  @}
 */ /* End of group ADC_Exported_functions */

/**
 *  @}
 */ /* End of group ADC */

/**
 *  @}
 */ /* End of group Periph_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __ADC_DMA_H */


