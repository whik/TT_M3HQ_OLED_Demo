/** 
 *******************************************************************************
 * @file    txz_gpio.h
 * @brief   This file provides all the functions prototypes for GPIO driver.
 * @version V1.0.0.4
 * $Date:: 2018-11-06 14:51:48 #$
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA MICROELECTRONICS CORPORATION 2017 All rights reserved
 *******************************************************************************
 */
/*------------------------------------------------------------------------------*/
/*  Define to prevent recursive inclusion                                       */
/*------------------------------------------------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

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
 *  @defgroup GPIO GPIO
 *  @brief    GPIO Driver.
 *  @{
 */

/*------------------------------------------------------------------------------*/
/*  Macro Definition                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup GPIO_Exported_define GPIO Exported Define
 *  @{
 */


/** 
 *  @defgroup GPIO_Result  Result
 *  @brief    GPIO Result Macro Definition.
 *  @{
 */
#define GPIO_RESULT_SUCCESS     (0)          /*!< Success       */
#define GPIO_RESULT_FAILURE     (-1)         /*!< Failure       */
#define GPIO_READ_FAILURE       (0xFFFFFFFF) /*!< Failure       */
/**
 *  @}
 */ /* End of group GPIO_Result */

/**
 *  @}
 */ /* End of group GPIO_Exported_define */

/*------------------------------------------------------------------------------*/
/*  Enumerated Type Definition                                                  */
/*------------------------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Typedef GPIO Exported Typedef
  * @{
  */

/** 
 *  @enum gpio_pinstate_t
 *  @brief    Pin State Reset/Set Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PIN_RESET = 0,  /*!< 0: Clear       */
  GPIO_PIN_SET,        /*!< 1: Set         */
}gpio_pinstate_t;

/**
 *  @enum gpio_pininout_t
 *  @brief    Pin Input/Output Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PIN_INPUT = 0,  /*!< 0: Input       */
  GPIO_PIN_OUTPUT,     /*!< 1: Output       */
  GPIO_PIN_INOUT,      /*!< 2: Input/Output */
  GPIO_PIN_NOTINOUT,   /*!< 3: Not Input/Output */
}gpio_pininout_t;
 
/** 
 *  @enum gpio_gr_t
 *  @brief    Port Group Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PORT_A = 0x0, /*!< 0: PA       */
  GPIO_PORT_B,       /*!< 1: PB       */
  GPIO_PORT_C,       /*!< 2: PC       */
  GPIO_PORT_D,       /*!< 3: PD       */
  GPIO_PORT_E,       /*!< 4: PE       */
  GPIO_PORT_F,       /*!< 5: PF       */
  GPIO_PORT_G,       /*!< 6: PG       */
  GPIO_PORT_H,       /*!< 7: PH       */
  GPIO_PORT_J,       /*!< 8: PJ       */
  GPIO_PORT_K,       /*!< 9: PK       */
  GPIO_PORT_L,       /*!< 10:PL       */
  GPIO_PORT_M,       /*!< 11: PM       */
  GPIO_PORT_N,       /*!< 12: PN       */
  GPIO_PORT_P,       /*!< 13: PP       */
  GPIO_PORT_R,       /*!< 14: PR       */
  GPIO_PORT_T,       /*!< 15: PT       */
  GPIO_PORT_U,       /*!< 16: PU       */
  GPIO_PORT_V,       /*!< 17: PV       */
  GPIO_GROUP_Max     /*!< Max Number   */
}gpio_gr_t;

/** 
 *  @enum gpio_num_t
 *  @brief    Port Number Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PORT_0 = 0x0, /*!< 0: Port0       */
  GPIO_PORT_1,       /*!< 1: Port1       */
  GPIO_PORT_2,       /*!< 2: Port2       */
  GPIO_PORT_3,       /*!< 3: Port3       */
  GPIO_PORT_4,       /*!< 4: Port4       */
  GPIO_PORT_5,       /*!< 5: Port5       */
  GPIO_PORT_6,       /*!< 6: Port6       */
  GPIO_PORT_7,       /*!< 7: Port7       */
  GPIO_PORT_Max      /*!< Max Number     */
}gpio_num_t;

/** 
 *  @enum gpio_fr_t
 *  @brief    Port Function Number Enumerated Type Definition.
 */
typedef enum
{
  GPIO_FR_1 = 1,   /*!< 1: PxFR1       */
  GPIO_FR_2,       /*!< 2: PxFR2       */
  GPIO_FR_3,       /*!< 3: PxFR3       */
  GPIO_FR_4,       /*!< 4: PxFR4       */
  GPIO_FR_5,       /*!< 5: PxFR5       */
  GPIO_FR_6,       /*!< 6: PxFR6       */
  GPIO_FR_7,       /*!< 7: PxFR7       */
  GPIO_FR_NA,      /*!< 8: N/A         */
  GPIO_FR_Max,      /*!< Max Number     */
}gpio_fr_t;

/** 
 *  @enum gpio_mode_t
 *  @brief    Port Mode Enumerated Type Definition.
 */
typedef enum
{
  GPIO_Mode_DATA = 0x0,  /*!< 0x0: PxDATA       */
  GPIO_Mode_CR  = 0x4,   /*!< 0x4: PxCR         */
  GPIO_Mode_FR1 = 0x8,   /*!< 0x8: PxFR1        */
  GPIO_Mode_FR2 = 0xC,   /*!< 0xC: PxFR2        */
  GPIO_Mode_FR3 = 0x10,  /*!< 0x10: PxFR3        */
  GPIO_Mode_FR4 = 0x14,  /*!< 0x14: PxFR4        */
  GPIO_Mode_FR5 = 0x18,  /*!< 0x18: PxFR5        */
  GPIO_Mode_FR6 = 0x1C,  /*!< 0x1C: PxFR6        */
  GPIO_Mode_FR7 = 0x20,  /*!< 0x20: PxFR7        */
  GPIO_Mode_OD  = 0x28,  /*!< 0x28: PxOD         */
  GPIO_Mode_PUP = 0x2C,  /*!< 0x2C: PxPUP        */
  GPIO_Mode_PDN = 0x30,  /*!< 0x30: PxPDN        */
  GPIO_Mode_IE  = 0x38   /*!< 0x38: PxIE         */
}gpio_mode_t;
 
/** 
 *  @enum gpio_pa0_func_t
 *  @brief    PortA0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PA0_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PA0_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PA0_UT0TXDB    = GPIO_FR_1, /*!< PAFR1: UT0TXDB        */
  GPIO_PA0_TSPI0SCK   = GPIO_FR_3, /*!< PAFR3: TSPI0SCK       */
  GPIO_PA0_T32A00OUTA = GPIO_FR_4, /*!< PAFR4: T32A00OUTA     */
  GPIO_PA0_T32A00OUTC = GPIO_FR_5, /*!< PAFR5: T32A00OUTC     */
  GPIO_PA0_ENC0A      = GPIO_FR_6, /*!< PAFR6: ENC0A          */
}gpio_pa0_func_t;
 
/** 
 *  @enum gpio_pa1_func_t
 *  @brief    PortA1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PA1_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PA1_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PA1_UT0TXDA    = GPIO_FR_1, /*!< PAFR1: UT0TXDA        */
  GPIO_PA1_UT0RXD     = GPIO_FR_2, /*!< PAFR2: UT0RXD         */
  GPIO_PA1_TSPI0TXD   = GPIO_FR_3, /*!< PAFR3: TSPI0TXD       */
  GPIO_PA1_T32A00INA0 = GPIO_FR_4, /*!< PAFR4: T32A00INA0     */
  GPIO_PA1_T32A00INC0 = GPIO_FR_5, /*!< PAFR5: T32A00INC0     */
  GPIO_PA1_ENC0B      = GPIO_FR_6, /*!< PAFR6: ENC0B          */
}gpio_pa1_func_t;
 
/** 
 *  @enum gpio_pa2_func_t
 *  @brief    PortA2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PA2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PA2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PA2_UT0RXD     = GPIO_FR_1, /*!< PAFR1: UT0RXD         */
  GPIO_PA2_UT0TXDA    = GPIO_FR_2, /*!< PAFR2: UT0TXDA        */
  GPIO_PA2_TSPI0RXD   = GPIO_FR_3, /*!< PAFR3: TSPI0RXD       */
  GPIO_PA2_T32A00INA1 = GPIO_FR_4, /*!< PAFR4: T32A00INA1     */
  GPIO_PA2_T32A00INC1 = GPIO_FR_5, /*!< PAFR5: T32A00INC1     */
  GPIO_PA2_ENC0Z      = GPIO_FR_6, /*!< PAFR6: ENC0Z          */
}gpio_pa2_func_t;
 
 /** 
 *  @enum gpio_pa3_func_t
 *  @brief    PortA3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PA3_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PA3_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PA3_TSPI0CSIN  = GPIO_FR_2, /*!< PAFR2: TSPI0CSIN      */
  GPIO_PA3_TSPI0CS0   = GPIO_FR_3, /*!< PAFR3: TSPI0CS0       */
  GPIO_PA3_T32A00OUTB = GPIO_FR_4, /*!< PAFR4: T32A00OUTB     */
  GPIO_PA3_TRGIN1     = GPIO_FR_6, /*!< PAFR6: TRGIN1         */
}gpio_pa3_func_t;

 /** 
 *  @enum gpio_pa4_func_t
 *  @brief    PortA4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PA4_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PA4_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PA4_I2C1SCL    = GPIO_FR_1, /*!< PAFR1: I2C1SCL        */
  GPIO_PA4_TSPI0CS1   = GPIO_FR_3, /*!< PAFR3: TSPI0CS1       */
  GPIO_PA4_T32A00INB0 = GPIO_FR_4, /*!< PAFR4: T32A00INB0     */
}gpio_pa4_func_t;
 
/** 
 *  @enum gpio_pa5_func_t
 *  @brief    PortA5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PA5_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PA5_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PA5_I2C1SDA    = GPIO_FR_1, /*!< PAFR1: I2C1SDA        */
  GPIO_PA5_T32A00INB1 = GPIO_FR_4, /*!< PAFR4: T32A00INB1     */
}gpio_pa5_func_t;
 
/** 
 *  @enum gpio_pa6_func_t
 *  @brief    PortA6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PA6_INPUT   = 0,         /*!<     0: Input Port     */
  GPIO_PA6_OUTPUT  = 0,         /*!<     0: Output Port    */
  GPIO_PA6_INT07   = 0,         /*!<     0: INT07          */
  GPIO_PA6_UT3RXD  = GPIO_FR_1, /*!< PAFR1: UT3RXD         */
  GPIO_PA6_UT3TXDA = GPIO_FR_2, /*!< PAFR2: UT3TXDA        */
}gpio_pa6_func_t;
 
 
/** 
 *  @enum gpio_pa7_func_t
 *  @brief    PortA6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PA7_INPUT   = 0,         /*!<     0: Input Port     */
  GPIO_PA7_OUTPUT  = 0,         /*!<     0: Output Port    */
  GPIO_PA7_INT11   = 0,         /*!<     0: INT11          */
  GPIO_PA7_UT3TXDA = GPIO_FR_1, /*!< PAFR1: UT3TXDA        */
  GPIO_PA7_UT3RXD  = GPIO_FR_2, /*!< PAFR2: UT3RXD         */
}gpio_pa7_func_t;
 


/** 
 *  @enum gpio_pb0_func_t
 *  @brief    PortB0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PB0_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PB0_T32A01OUTA = GPIO_FR_4, /*!< PBFR4: T32A01OUTA     */
  GPIO_PB0_T32A01OUTC = GPIO_FR_5, /*!< PBFR5: T32A01OUTC     */
  GPIO_PB0_SCOUT      = GPIO_FR_6, /*!< PBFR6: SCOUT          */
}gpio_pb0_func_t;
 
/** 
 *  @enum gpio_pb1_func_t
 *  @brief    PortB1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PB1_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PB1_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PB1_INT03      = 0,         /*!<     0: INT03          */
  GPIO_PB1_RXIN0      = GPIO_FR_1, /*!< PBFR1: RXIN0          */
  GPIO_PB1_T32A01INA0 = GPIO_FR_4, /*!< PBFR4: T32A01INA0     */
  GPIO_PB1_T32A01INC0 = GPIO_FR_5, /*!< PBFR5: T32A01INC0     */
  GPIO_PB1_TRGIN0     = GPIO_FR_6, /*!< PBFR6: TRGIN0         */
}gpio_pb1_func_t;
 
/** 
 *  @enum gpio_pb2_func_t
 *  @brief    PortB2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PB2_INPUT      = 0,         /*!<      0: Input Port     */
  GPIO_PB2_OUTPUT     = 0,         /*!<      0: Output Port    */
  GPIO_PB2_UT2TXDA    = GPIO_FR_1, /*!<  PBFR1: UT2TXDA        */
  GPIO_PB2_UT2RXD     = GPIO_FR_2, /*!<  PBFR2: UT2RXD         */
  GPIO_PB2_TSPI1SCK   = GPIO_FR_3, /*!<  PBFR3: TSPI1SCK       */
  GPIO_PB2_T32A01INA1 = GPIO_FR_4, /*!<  PBFR4: T32A01INA1     */
  GPIO_PB2_T32A01INC1 = GPIO_FR_5, /*!<  PBFR5: T32A01INC1     */
}gpio_pb2_func_t;
 
 /** 
 *  @enum gpio_pb3_func_t
 *  @brief    PortB3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PB3_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PB3_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PB3_UT2RXD     = GPIO_FR_1, /*!< PBFR1: UT2RXD         */
  GPIO_PB3_UT2TXDA    = GPIO_FR_2, /*!< PBFR2: UT2TXDA        */
  GPIO_PB3_TSPI1TXD   = GPIO_FR_3, /*!< PBFR3: Output Port    */
  GPIO_PB3_T32A01OUTB = GPIO_FR_4, /*!< PBFR4: Output Port    */
}gpio_pb3_func_t;

 /** 
 *  @enum gpio_pb4_func_t
 *  @brief    PortB4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PB4_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PB4_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PB4_UT2CTS_N   = GPIO_FR_1, /*!< PBFR1: UT2CTS_N       */
  GPIO_PB4_UT2RTS_N   = GPIO_FR_2, /*!< PBFR2: UT2RTS_N       */
  GPIO_PB4_TSPI1RXD   = GPIO_FR_3, /*!< PBFR3: TSPI1RXD       */
  GPIO_PB4_T32A01INB0 = GPIO_FR_4, /*!< PBFR4: T32A01INB0     */
}gpio_pb4_func_t;
 
/** 
 *  @enum gpio_pb5_func_t
 *  @brief    PortB5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PB5_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PB5_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PB5_UT2RTS_N   = GPIO_FR_1, /*!< PBFR1: UT2RTS_N       */
  GPIO_PB5_UT2CTS_N   = GPIO_FR_2, /*!< PBFR2: T2CTS_N        */
  GPIO_PB5_TSPI1CS0   = GPIO_FR_3, /*!< PBFR3: TSPI1CS0       */
  GPIO_PB5_T32A01INB1 = GPIO_FR_4, /*!< PBFR4: T32A01INB1     */
  GPIO_PB5_TSPI1CSIN  = GPIO_FR_5, /*!< PBFR5: TSPI1CSIN      */
}gpio_pb5_func_t;
 
/** 
 *  @enum gpio_pb6_func_t
 *  @brief    PortB6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PB6_INPUT     = 0,         /*!<     0: Input Port     */
  GPIO_PB6_OUTPUT    = 0,         /*!<     0: Output Port    */
  GPIO_PB6_TSPI1CS1  = GPIO_FR_3, /*!< PBFR3: TSPI1CS1       */
}gpio_pb6_func_t;

/** 
 *  @enum gpio_pb7_func_t
 *  @brief    PortB7 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PB7_INPUT      = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PB7_OUTPUT     = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PB7_INT16      = GPIO_FR_NA, /*!< N/A: INT16          */
}gpio_pb7_func_t;


/** 
 *  @enum gpio_pc0_func_t
 *  @brief    PortC0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PC0_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PC0_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PC0_INT00      = 0,         /*!<     0: INT00          */
  GPIO_PC0_I2C0SCL    = GPIO_FR_1, /*!< PCFR1: I2C0SCL        */
  GPIO_PC0_T32A02OUTA = GPIO_FR_3, /*!< PCFR3: T32A02OUTA      */
  GPIO_PC0_T32A02OUTC = GPIO_FR_4, /*!< PCFR4: T32A02OUTC      */
}gpio_pc0_func_t;
 
/** 
 *  @enum gpio_pc1_func_t
 *  @brief    PortC1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PC1_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PC1_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PC1_INT01      = 0,         /*!<     0: INT01          */
  GPIO_PC1_I2C0SDA    = GPIO_FR_1, /*!< PCFR1: ISC0SDA        */
  GPIO_PC1_T32A02INA0 = GPIO_FR_3, /*!< PCFR3: T32A02INA0     */
  GPIO_PC1_T32A02INC0 = GPIO_FR_4, /*!< PCFR4: T32A02INC0     */
}gpio_pc1_func_t;
 
/** 
 *  @enum gpio_pc2_func_t
 *  @brief    PortC2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PC2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PC2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PC2_INT02      = 0,         /*!<     0: INT02          */
  GPIO_PC2_UT4TXDB    = GPIO_FR_1, /*!< PCFR1: UT4TXDB        */
  GPIO_PC2_T32A02INA1 = GPIO_FR_3, /*!< PCFR3: T32A02INA1     */
  GPIO_PC2_T32A02INC1 = GPIO_FR_4, /*!< PCFR4: T32A02INC1     */
  GPIO_PC2_RTCOUT     = GPIO_FR_5, /*!< PCFR5: RTCOUT         */
}gpio_pc2_func_t;
 
 /** 
 *  @enum gpio_pc3_func_t
 *  @brief    PortC3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PC3_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PC3_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PC3_UT4TXDA    = GPIO_FR_1, /*!< PCFR1: UT4TXDA        */
  GPIO_PC3_UT4RXD     = GPIO_FR_2, /*!< PCFR2: UT4RXD         */
  GPIO_PC3_T32A02OUTB = GPIO_FR_3, /*!< PCFR3: T32A2OUTB      */
}gpio_pc3_func_t;

 /** 
 *  @enum gpio_pc4_func_t
 *  @brief    PortC4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PC4_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PC4_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PC4_UT4RXD     = GPIO_FR_1, /*!< PCFR1: UT4RXD         */
  GPIO_PC4_UT4TXDA    = GPIO_FR_2, /*!< PCFR2: UT4TXDA        */
  GPIO_PC4_T32A02INB0 = GPIO_FR_3, /*!< PCFR3: T32A2INB0      */
}gpio_pc4_func_t;
 
/** 
 *  @enum gpio_pc5_func_t
 *  @brief    PortC5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PC5_INPUT       = 0,         /*!<     0: Input Port     */
  GPIO_PC5_OUTPUT      = 0,         /*!<     0: Output Port    */
  GPIO_PC5_UT4CTS_N    = GPIO_FR_1, /*!< PCFR1: UT4CTS_N       */
  GPIO_PC5_UT4RTS_N    = GPIO_FR_2, /*!< PCFR2: UT4RTS_N       */
  GPIO_PC5_T32A02INB1  = GPIO_FR_3, /*!< PCFR3: T32A2INB1      */
}gpio_pc5_func_t;

/** 
 *  @enum gpio_pc6_func_t
 *  @brief    PortC6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PC6_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PC6_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PC6_UT4RTS_N   = GPIO_FR_1,  /*!< PCFR1: UT4RTS_N       */
  GPIO_PC6_UT4CTS_N   = GPIO_FR_2,  /*!< PCFR2: UT4CTS_N       */
}gpio_pc6_func_t;


/** 
 *  @enum gpio_pd0_func_t
 *  @brief    PortD0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PD0_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PD0_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PD0_AINA00 = GPIO_FR_NA, /*!< N/A: AINA00         */
}gpio_pd0_func_t;
 
/** 
 *  @enum gpio_pd1_func_t
 *  @brief    PortD1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PD1_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PD1_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PD1_AINA01 = GPIO_FR_NA, /*!< N/A: AINA01         */
}gpio_pd1_func_t;
 
/** 
 *  @enum gpio_pd2_func_t
 *  @brief    PortD2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PD2_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PD2_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PD2_AINA02 = GPIO_FR_NA, /*!< N/A: AINA02         */
}gpio_pd2_func_t;
 
 /** 
 *  @enum gpio_pd3_func_t
 *  @brief    PortD3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PD3_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PD3_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PD3_AINA03 = GPIO_FR_NA, /*!< N/A: AINA03         */
}gpio_pd3_func_t;

/** 
 *  @enum gpio_pd4_func_t
 *  @brief    PortD4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PD4_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PD4_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PD4_AINA19 = GPIO_FR_NA, /*!< N/A: AINA19         */
}gpio_pd4_func_t;

/** 
 *  @enum gpio_pd5_func_t
 *  @brief    PortD5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PD5_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PD5_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PD5_AINA20 = GPIO_FR_NA, /*!< N/A: AINA20         */
}gpio_pd5_func_t;
/** 
 *  @enum gpio_pe0_func_t
 *  @brief    PortE0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PE0_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PE0_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PE0_AINA04 = GPIO_FR_NA, /*!< N/A: AINA04         */
}gpio_pe0_func_t;
 
/** 
 *  @enum gpio_pe1_func_t
 *  @brief    PortE1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PE1_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PE1_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PE1_AINA05 = GPIO_FR_NA, /*!< N/A: AINA05         */
}gpio_pe1_func_t;
 
/** 
 *  @enum gpio_pe2_func_t
 *  @brief    PortE2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PE2_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PE2_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PE2_AINA06 = GPIO_FR_NA, /*!< N/A: AINA06         */
}gpio_pe2_func_t;
 
 /** 
 *  @enum gpio_pe3_func_t
 *  @brief    PortE3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PE3_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PE3_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PE3_AINA07 = GPIO_FR_NA, /*!< N/A: AINA07         */
}gpio_pe3_func_t;

 /** 
 *  @enum gpio_pe4_func_t
 *  @brief    PortE4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PE4_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PE4_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PE4_AINA08 = GPIO_FR_NA, /*!< N/A: AINA08         */
}gpio_pe4_func_t;
 
/** 
 *  @enum gpio_pe5_func_t
 *  @brief    PortE5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PE5_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PE5_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PE5_AINA09 = GPIO_FR_NA, /*!< N/A: AINA09         */
}gpio_pe5_func_t;
 
/** 
 *  @enum gpio_pe6_func_t
 *  @brief    PortE6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PE6_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PE6_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PE6_AINA10 = GPIO_FR_NA, /*!< N/A: AINA10         */
}gpio_pe6_func_t;


/** 
 *  @enum gpio_pf0_func_t
 *  @brief    PortF0 Function Enumerated TyPF Definition.
 */
typedef enum
{
  GPIO_PF0_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PF0_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PF0_AINA11 = GPIO_FR_NA, /*!< N/A: AINA11         */
}gpio_pf0_func_t;
 
/** 
 *  @enum gpio_pf1_func_t
 *  @brief    PortF1 Function Enumerated TyPF Definition.
 */
typedef enum
{
  GPIO_PF1_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PF1_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PF1_AINA12 = GPIO_FR_NA, /*!< N/A: AINA12         */
}gpio_pf1_func_t;
 
/** 
 *  @enum gpio_pf2_func_t
 *  @brief    PortF2 Function Enumerated TyPF Definition.
 */
typedef enum
{
  GPIO_PF2_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PF2_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PF2_AINA13 = GPIO_FR_NA, /*!< N/A: AINA13         */
}gpio_pf2_func_t;
 
 /** 
 *  @enum gpio_pf3_func_t
 *  @brief    PortF3 Function Enumerated TyPF Definition.
 */
typedef enum
{
  GPIO_PF3_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PF3_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PF3_AINA14 = GPIO_FR_NA, /*!< N/A: AINA14         */
}gpio_pf3_func_t;

 /** 
 *  @enum gpio_pf4_func_t
 *  @brief    PortF4 Function Enumerated TyPF Definition.
 */
typedef enum
{
  GPIO_PF4_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PF4_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PF4_AINA15 = GPIO_FR_NA, /*!< N/A: AINA15         */
}gpio_pf4_func_t;

 /** 
 *  @enum gpio_pf5_func_t
 *  @brief    PortF5 Function Enumerated TyPF Definition.
 */
typedef enum
{
  GPIO_PF5_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PF5_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PF5_AINA16 = GPIO_FR_NA, /*!< N/A: AINA16         */
}gpio_pf5_func_t;

 /** 
 *  @enum gpio_pf6_func_t
 *  @brief    PortF6 Function Enumerated TyPF Definition.
 */
typedef enum
{
  GPIO_PF6_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PF6_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PF6_AINA17 = GPIO_FR_NA, /*!< N/A: AINA17         */
}gpio_pf6_func_t;

 /** 
 *  @enum gpio_pf7_func_t
 *  @brief    PortF7 Function Enumerated TyPF Definition.
 */
typedef enum
{
  GPIO_PF7_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PF7_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PF7_AINA18 = GPIO_FR_NA, /*!< N/A: AINA18         */
}gpio_pf7_func_t;

/** 
 *  @enum gpio_pg0_func_t
 *  @brief    PortG0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PG0_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PG0_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PG0_DAC0   = GPIO_FR_NA, /*!< N/A: DAC0           */
}gpio_pg0_func_t;
 
/** 
 *  @enum gpio_pg1_func_t
 *  @brief    PortG1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PG1_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PG1_OUTPUT = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PG1_DAC1   = GPIO_FR_NA, /*!< N/A: DAC1           */
}gpio_pg1_func_t;

/** 
 *  @enum gpio_pg2_func_t
 *  @brief    PortG2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PG2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PG2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PG2_INT27      = 0,         /*!<     0: INT27          */
  GPIO_PG2_UT3RXD     = GPIO_FR_1, /*!< PGFR1: UT3RXD         */
  GPIO_PG2_UT3TXDA    = GPIO_FR_2, /*!< PGFR2: UT3TXDA        */
  GPIO_PG2_T32A07OUTA = GPIO_FR_3, /*!< PGFR3: T32A07OUTA     */
  GPIO_PG2_T32A07OUTC = GPIO_FR_4, /*!< PGFR4: T32A07OUTC     */
}gpio_pg2_func_t;

/** 
 *  @enum gpio_pg3_func_t
 *  @brief    PortG3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PG3_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PG3_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PG3_INT28      = 0,         /*!<     0: INT27          */
  GPIO_PG3_UT3TXDA    = GPIO_FR_1, /*!< PGFR1: UT3TXDA        */
  GPIO_PG3_UT3RXD     = GPIO_FR_2, /*!< PGFR2: UT3RXD         */
  GPIO_PG3_T32A07INA0 = GPIO_FR_3, /*!< PGFR3: T32A07INA0     */
  GPIO_PG3_T32A07INC0 = GPIO_FR_4, /*!< PGFR4: T32A07INC0     */
}gpio_pg3_func_t;

/** 
 *  @enum gpio_pg4_func_t
 *  @brief    PortG4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PG4_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PG4_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PG4_UT3TXDB    = GPIO_FR_1, /*!< PGFR1: UT3TXDB        */
  GPIO_PG4_T32A07INA1 = GPIO_FR_3, /*!< PGFR3: T32A07INA1     */
  GPIO_PG4_T32A07INC1 = GPIO_FR_4, /*!< PGFR4: T32A07INC1     */
}gpio_pg4_func_t;

/** 
 *  @enum gpio_pg5_func_t
 *  @brief    PortG5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PG5_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PG5_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PG5_T32A07OUTB = GPIO_FR_3, /*!< PGFR3: T32A07OUTB     */
}gpio_pg5_func_t;

/** 
 *  @enum gpio_pg6_func_t
 *  @brief    PortG6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PG6_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PG6_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PG6_T32A07INB0 = GPIO_FR_3, /*!< PGFR3: T32A07INB0     */
}gpio_pg6_func_t;

/** 
 *  @enum gpio_pg7_func_t
 *  @brief    PortG7 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PG7_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PG7_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PG7_T32A07INB1 = GPIO_FR_3, /*!< PGFR3: T32A07INB1     */
}gpio_pg7_func_t;

/** 
 *  @enum gpio_ph0_func_t
 *  @brief    PortH0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PH0_INPUT   = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PH0_X1      = GPIO_FR_NA, /*!< N/A: X1             */
  GPIO_PH0_EHCLKIN = GPIO_FR_NA, /*!< N/A: EHCLKIN        */
}gpio_ph0_func_t;
 
/** 
 *  @enum gpio_ph1_func_t
 *  @brief    PortH1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PH1_INPUT  = GPIO_FR_NA,  /*!< N/A Input Port     */
  GPIO_PH1_X2     = GPIO_FR_NA, /*!< N/A X2             */
}gpio_ph1_func_t;
 
/** 
 *  @enum gpio_ph2_func_t
 *  @brief    PortH2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PH2_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PH2_XT1    = GPIO_FR_NA, /*!< N/A: XT1            */
}gpio_ph2_func_t;
 
 /** 
 *  @enum gpio_ph3_func_t
 *  @brief    PortH3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PH3_INPUT  = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PH3_XT2    = GPIO_FR_NA, /*!< N/A: XT2            */
  GPIO_PH3_INT06  = GPIO_FR_NA, /*!< N/A: INT06          */
}gpio_ph3_func_t;

 /** 
 *  @enum gpio_ph4_func_t
 *  @brief    PortH4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PH4_INPUT     = 0,         /*!<     0: Input Port     */
  GPIO_PH4_OUTPUT    = 0,         /*!<     0: Output Port    */
  GPIO_PH4_INT19     = 0,         /*!<     0: INT19          */
  GPIO_PH4_TSPI4SCK  = GPIO_FR_1, /*!< PHFR1: TSPI4SCK       */
}gpio_ph4_func_t;

 /** 
 *  @enum gpio_ph5_func_t
 *  @brief    PortH5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PH5_INPUT    = 0,         /*!<     0: Input Port     */
  GPIO_PH5_OUTPUT   = 0,         /*!<     0: Output Port    */
  GPIO_PH5_INT20    = 0,         /*!<     0: INT19          */
  GPIO_PH5_TSPI4TXD = GPIO_FR_1, /*!< PHFR1: TSPI4TXD       */
}gpio_ph5_func_t;

 /** 
 *  @enum gpio_ph6_func_t
 *  @brief    PortH6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PH6_INPUT    = 0,         /*!<     0: Input Port     */
  GPIO_PH6_OUTPUT   = 0,         /*!<     0: Output Port    */
  GPIO_PH6_INT21    = 0,         /*!<     0: INT21          */
  GPIO_PH6_TSPI4RXD = GPIO_FR_1, /*!< PHFR1: TSPI4RXD       */
}gpio_ph6_func_t;

 /** 
 *  @enum gpio_ph7_func_t
 *  @brief    PortH7 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PH7_INPUT    = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PH7_OUTPUT   = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PH7_INT22    = GPIO_FR_NA, /*!< N/A: INT22          */
}gpio_ph7_func_t;

/** 
 *  @enum gpio_pj0_func_t
 *  @brief    PortJ0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PJ0_INPUT       = 0,         /*!<     0: Input Port     */
  GPIO_PJ0_OUTPUT      = 0,         /*!<     0: Output Port    */
  GPIO_PJ0_UT1TXDB     = GPIO_FR_1, /*!< PJFR1: UT1TXDB        */
  GPIO_PJ0_T32A03OUTA  = GPIO_FR_3, /*!< PJFR3: T32A03OUTA      */
  GPIO_PJ0_T32A03OUTC  = GPIO_FR_4, /*!< PJFR4: T32A03OUTC      */
  GPIO_PJ0_UO0         = GPIO_FR_5, /*!< PJFR5: UO0             */
}gpio_pj0_func_t;
 
/** 
 *  @enum gpio_pj1_func_t
 *  @brief    PortJ1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PJ1_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PJ1_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PJ1_UT1TXDA    = GPIO_FR_1, /*!< PJFR1: UT1TXDA        */
  GPIO_PJ1_UT1RXD     = GPIO_FR_2, /*!< PJFR2: UT1RXD         */
  GPIO_PJ1_T32A03INA0 = GPIO_FR_3, /*!< PJFR3: T32A03INA0     */
  GPIO_PJ1_T32A03INC0 = GPIO_FR_4, /*!< PJFR4: T32A03INC0     */
  GPIO_PJ1_XO0        = GPIO_FR_5, /*!< PJFR5: XO0            */
}gpio_pj1_func_t;
 
/** 
 *  @enum gpio_pj2_func_t
 *  @brief    PortJ2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PJ2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PJ2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PJ2_UT1RXD     = GPIO_FR_1, /*!< PJFR1: UT1RXD         */
  GPIO_PJ2_UT1TXDA    = GPIO_FR_2, /*!< PJFR2: UT1TXDA        */
  GPIO_PJ2_T32A03INA1 = GPIO_FR_3, /*!< PJFR3: T32A03INA1     */
  GPIO_PJ2_T32A03INC1 = GPIO_FR_4, /*!< PJFR4: T32A03INC1     */
  GPIO_PJ2_VO0        = GPIO_FR_5, /*!< PJFR5: VO0            */
}gpio_pj2_func_t;
 
 /** 
 *  @enum gpio_pj3_func_t
 *  @brief    PortJ3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PJ3_INPUT       = 0,         /*!<     0: Input Port     */
  GPIO_PJ3_OUTPUT      = 0,         /*!<     0: Output Port    */
  GPIO_PJ3_UT1CTS_N    = GPIO_FR_1, /*!< PJFR1: UT1CTS_N       */
  GPIO_PJ3_UT1RTS_N    = GPIO_FR_2, /*!< PJFR2: UT1RTS_N       */
  GPIO_PJ3_T32A03OUTB  = GPIO_FR_3, /*!< PJFR3: T32A03OUTB     */
  GPIO_PJ3_YO0         = GPIO_FR_5, /*!< PJFR5: YO0            */
}gpio_pj3_func_t;

 /** 
 *  @enum gpio_pj4_func_t
 *  @brief    PortJ4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PJ4_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PJ4_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PJ4_INT04      = 0,         /*!<     0: INT04          */
  GPIO_PJ4_UT1RTS_N   = GPIO_FR_1, /*!< PJFR1: UT1RTS_N       */
  GPIO_PJ4_UT1CTS_N   = GPIO_FR_2, /*!< PJFR2: UT1CTS_N       */
  GPIO_PJ4_T32A03INB0 = GPIO_FR_3, /*!< PJFR3: T32A03INB0     */
  GPIO_PJ4_WO0        = GPIO_FR_5, /*!< PJFR5: WO0            */
}gpio_pj4_func_t;
 
/** 
 *  @enum gpio_pj5_func_t
 *  @brief    PortJ5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PJ5_INPUT      = 0,         /*!< 0: Input Port     */
  GPIO_PJ5_OUTPUT     = 0,         /*!< 0: Output Port    */
  GPIO_PJ5_T32A03INB1 = GPIO_FR_3, /*!< PJFR3: T32A03INB1     */
  GPIO_PJ5_ZO0        = GPIO_FR_5, /*!< PJFR5: ZO0            */
}gpio_pj5_func_t;

/** 
 *  @enum gpio_pk0_func_t
 *  @brief    PortK0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PK0_INPUT    = 0,         /*!<     0: Input Port     */
  GPIO_PK0_OUTPUT   = 0,         /*!<     0: Output Port    */
  GPIO_PK0_UT1TXDB  = GPIO_FR_1, /*!< PKFR1: UT1TXDB        */
  GPIO_PK0_EMG0     = GPIO_FR_5, /*!< PKFR5: EMG0           */
}gpio_pk0_func_t;
 
/** 
 *  @enum gpio_pk1_func_t
 *  @brief    PortK1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PK1_INPUT    = 0,         /*!<     0: Input Port     */
  GPIO_PK1_OUTPUT   = 0,         /*!<     0: Output Port    */
  GPIO_PK1_INT05    = 0,         /*!<     0: INT05          */
  GPIO_PK1_UT1TXDA  = GPIO_FR_1, /*!< PKFR1: UT1TXDA        */
  GPIO_PK1_UT1RXD   = GPIO_FR_2, /*!< PKFR2: UT1RXD         */
  GPIO_PK1_OVV0     = GPIO_FR_5, /*!< PKFR5: OVV0           */
}gpio_pk1_func_t;
 
/** 
 *  @enum gpio_pk2_func_t
 *  @brief    PortK2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PK2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PK2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PK2_UT1RXD     = GPIO_FR_1, /*!< PKFR1: UT1RXD         */
  GPIO_PK2_UT1TXDA    = GPIO_FR_2, /*!< PKFR2: UT1TXDA        */
  GPIO_PK2_T32A04OUTA = GPIO_FR_3, /*!< PKFR3: T32A04OUTA     */
  GPIO_PK2_T32A04OUTC = GPIO_FR_4, /*!< PKFR4: T32A04OUTC     */
}gpio_pk2_func_t;
 
 /** 
 *  @enum gpio_pk3_func_t
 *  @brief    PortK3 Function Enumerated Type Definition.
 */
typedef enum
{ 
  GPIO_PK3_INPUT      = 0,        /*!<     0: Input Port     */
  GPIO_PK3_OUTPUT     = 0,        /*!<     0: Output Port    */
  GPIO_PK3_UT1CTS_N   = GPIO_FR_1, /*!< PKFR1: UT1CTS_N       */
  GPIO_PK3_UT1RTS_N   = GPIO_FR_2, /*!< PKFR2: UT1RTS_N       */
  GPIO_PK3_T32A04INA0 = GPIO_FR_3, /*!< PKFR3: T32A04INA0     */
  GPIO_PK3_T32A04INC0 = GPIO_FR_4, /*!< PKFR4: T32A04INC0     */
}gpio_pk3_func_t;

 /** 
 *  @enum gpio_pk4_func_t
 *  @brief    PortK4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PK4_INPUT       = 0,        /*!<     0: Input Port     */
  GPIO_PK4_OUTPUT      = 0,        /*!<     0: Output Port    */
  GPIO_PK4_UT1RTS_N    = GPIO_FR_1, /*!< PKFR1: UT1RTS_N       */
  GPIO_PK4_UT1CTS_N    = GPIO_FR_2, /*!< PKFR2: UT1CTS_N       */
  GPIO_PK4_T32A04INA1  = GPIO_FR_3, /*!< PKFR3: T32A4INA1 2     */
  GPIO_PK4_T32A04INC1  = GPIO_FR_4, /*!< PKFR4: T32A4INC1      */
}gpio_pk4_func_t;
 
/** 
 *  @enum gpio_pk5_func_t
 *  @brief    PortK5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PK5_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PK5_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PK5_T32A04OUTB = GPIO_FR_3, /*!< PKFR3: T32A04OUTB     */
}gpio_pk5_func_t;
 
/** 
 *  @enum gpio_pk6_func_t
 *  @brief    PortK6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PK6_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PK6_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PK6_T32A04INB0 = GPIO_FR_3, /*!< PKFR3: T32A04INB0     */
}gpio_pk6_func_t;

/** 
 *  @enum gpio_pk7_func_t
 *  @brief    PortK7 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PK7_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PK7_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PK7_INT13      = 0,         /*!<     0: INT13          */
  GPIO_PK7_T32A04INB1 = GPIO_FR_3, /*!< PKFR3: T32A04INB1     */
}gpio_pk7_func_t;

/** 
 *  @enum gpio_pl0_func_t
 *  @brief    PortL0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PL0_INPUT   = 0,         /*!<     0: Input Port     */
  GPIO_PL0_OUTPUT  = 0,         /*!<     0: Output Port    */
  GPIO_PL0_UT2TXDA = GPIO_FR_1, /*!< PLFR1: UT2TXDA        */
  GPIO_PL0_UT2RXD  = GPIO_FR_2, /*!< PLFR2: UT2RXD         */
  GPIO_PL0_I2C2SCL = GPIO_FR_3, /*!< PLFR3: I2C2SCL        */
}gpio_pl0_func_t;
 
/** 
 *  @enum gpio_pl1_func_t
 *  @brief    PortL1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PL1_INPUT   = 0,         /*!<     0: Input Port     */
  GPIO_PL1_OUTPUT  = 0,         /*!<     0: Output Port    */
  GPIO_PL1_UT2RXD  = GPIO_FR_1, /*!< PLFR1: UT2RXD         */
  GPIO_PL1_UT2TXDA = GPIO_FR_2, /*!< PLFR2: UT2TXDA        */
  GPIO_PL1_I2C2SDA = GPIO_FR_3, /*!< PLFR3: I2C2SDA        */
}gpio_pl1_func_t;
 
/** 
 *  @enum gpio_pl2_func_t
 *  @brief    PortL2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PL2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PL2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PL2_UT2CTS_N   = GPIO_FR_1, /*!< PLFR1: UT2CTS_N       */
  GPIO_PL2_UT2RTS_N   = GPIO_FR_2, /*!< PLFR2: UT2RTS_N       */
  GPIO_PL2_T32A06OUTB = GPIO_FR_3, /*!< PLFR3: T32A06OUTB     */
}gpio_pl2_func_t;
 
 /** 
 *  @enum gpio_pl3_func_t
 *  @brief    PortL3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PL3_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PL3_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PL3_INT08      = 0,         /*!<     0: INT08          */
  GPIO_PL3_UT2RTS_N   = GPIO_FR_1, /*!< PLFR1: UT2RTS_N       */
  GPIO_PL3_UT2CTS_N   = GPIO_FR_2, /*!< PLFR2: UT2CTS_N       */
  GPIO_PL3_T32A06INB0 = GPIO_FR_3, /*!< PLFR3: T32A06INB0     */
}gpio_pl3_func_t;

 /** 
 *  @enum gpio_pl4_func_t
 *  @brief    PortL4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PL4_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PL4_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PL4_INT12      = 0,         /*!<     0: IN112          */
  GPIO_PL4_T32A06INB1 = GPIO_FR_3, /*!< PLFR3: T32A06INB1     */
}gpio_pl4_func_t;
 
/** 
 *  @enum gpio_pl5_func_t
 *  @brief    PortL5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PL5_INPUT      = 0,         /*!< 0: Input Port     */
  GPIO_PL5_OUTPUT     = 0,         /*!< 0: Output Port    */
  GPIO_PL5_T32A06OUTA = GPIO_FR_3, /*!< PLFR3: T32A06OUTA     */
  GPIO_PL5_T32A06OUTC = GPIO_FR_4, /*!< PLFR4: T32A06OUTC     */
}gpio_pl5_func_t;
 
/** 
 *  @enum gpio_pl6_func_t
 *  @brief    PortL6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PL6_INPUT      = 0,         /*!< 0: Input Port     */
  GPIO_PL6_OUTPUT     = 0,         /*!< 0: Output Port    */
  GPIO_PL6_T32A06INA0 = GPIO_FR_3, /*!< PLFR3: T32A06INA0     */
  GPIO_PL6_T32A06INC0 = GPIO_FR_4, /*!< PLFR4: T32A06INC0     */
}gpio_pl6_func_t;

/** 
 *  @enum gpio_pl7_func_t
 *  @brief    PortL7 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PL7_INPUT      = 0,         /*!< 0: Input Port     */
  GPIO_PL7_OUTPUT     = 0,         /*!< 0: Output Port    */
  GPIO_PL7_T32A06INA1 = GPIO_FR_3, /*!< PLFR3: T32A06INA1     */
  GPIO_PL7_T32A06INC1 = GPIO_FR_4, /*!< PLFR4: T32A06INC1     */
}gpio_pl7_func_t;

/** 
 *  @enum gpio_pm0_func_t
 *  @brief    PortM0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PM0_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PM0_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PM0_UT0TXDB    = GPIO_FR_1, /*!< PMFR1: UT0TXDB        */
  GPIO_PM0_TSPI0SCK   = GPIO_FR_3, /*!< PMFR3: TSPI0SCK       */
  GPIO_PM0_T32A00OUTA = GPIO_FR_4, /*!< PMFR4: T32A00OUTA     */
  GPIO_PM0_T32A00OUTC = GPIO_FR_5, /*!< PMFR5: T32A00OUTC     */
  GPIO_PM0_TRACECLK   = GPIO_FR_6, /*!< PMFR6: TRACECLK       */
}gpio_pm0_func_t;

/** 
 *  @enum gpio_pm1_func_t
 *  @brief    PortM1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PM1_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PM1_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PM1_UT0TXDA    = GPIO_FR_1, /*!< PMFR1: UT0TXDA        */
  GPIO_PM1_UT0RXD     = GPIO_FR_2, /*!< PMFR2: UT0RXD         */
  GPIO_PM1_TSPI0TXD   = GPIO_FR_3, /*!< PMFR3: TSPI0TXD       */
  GPIO_PM1_T32A00INA0 = GPIO_FR_4, /*!< PMFR4: T32A00INA0     */
  GPIO_PM1_T32A00INC0 = GPIO_FR_5, /*!< PMFR5: T32A00INC0     */
  GPIO_PM1_TRACEDATA0 = GPIO_FR_6, /*!< PMFR6: TRACEDATA0     */
}gpio_pm1_func_t;

/** 
 *  @enum gpio_pm2_func_t
 *  @brief    PortM2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PM2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PM2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PM2_INT09      = 0,         /*!<     0: Output Port    */
  GPIO_PM2_UT0RXD     = GPIO_FR_1, /*!< PMFR1: UT0RXD         */
  GPIO_PM2_UT0TXDA    = GPIO_FR_2, /*!< PMFR2: UT0TXDA        */
  GPIO_PM2_TSPI0RXD   = GPIO_FR_3, /*!< PMFR3: TSPI0RXD       */
  GPIO_PM2_T32A00INA1 = GPIO_FR_4, /*!< PMFR4: T32A00INA1     */
  GPIO_PM2_T32A00INC1 = GPIO_FR_5, /*!< PMFR5: T32A00INC1     */
  GPIO_PM2_TRACEDATA1 = GPIO_FR_6, /*!< PMFR6: TRACEDATA1     */
}gpio_pm2_func_t;
 
 /** 
 *  @enum gpio_pm3_func_t
 *  @brief    PortM3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PM3_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PM3_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PM3_UT0CTS_N   = GPIO_FR_1, /*!< PMFR1: UT0CTS_N       */
  GPIO_PM3_UT0RTS_N   = GPIO_FR_2, /*!< PMFR2: UT0RTS_N       */
  GPIO_PM3_TSPI0CS0   = GPIO_FR_3, /*!< PMFR3: TSPI0CS0       */
  GPIO_PM3_T32A00OUTB = GPIO_FR_4, /*!< PMFR4: T32A00OUTB     */
  GPIO_PM3_TSPI0CSIN  = GPIO_FR_5, /*!< PMFR5: TSPI0CSIN      */
  GPIO_PM3_TRACEDATA2 = GPIO_FR_6, /*!< PMFR6: TRACEDATA2     */
}gpio_pm3_func_t;

 /** 
 *  @enum gpio_pm4_func_t
 *  @brief    PortM4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PM4_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PM4_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PM4_UT0RTS_N   = GPIO_FR_1, /*!< PMFR1: UT0RTS_N       */
  GPIO_PM4_UT0CTS_N   = GPIO_FR_2, /*!< PMFR2: UT0CTS_N       */
  GPIO_PM4_TSPI0CS1   = GPIO_FR_3, /*!< PMFR3: TSPI0CS1       */
  GPIO_PM4_T32A00INB0 = GPIO_FR_4, /*!< PMFR4: T32A00INB0     */
  GPIO_PM4_TRACEDATA3 = GPIO_FR_6, /*!< PMFR6: TRACEDATA3     */
}gpio_pm4_func_t;
 
/** 
 *  @enum gpio_pm5_func_t
 *  @brief    PortM5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PM5_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PM5_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PM5_T32A00INB1 = GPIO_FR_4, /*!< PMFR4: T32A00INB1      */
}gpio_pm5_func_t;
 
/** 
 *  @enum gpio_pm6_func_t
 *  @brief    PortM6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PM6_INPUT   = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PM6_OUTPUT  = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PM6_INT15   = GPIO_FR_NA, /*!< N/A: INT15          */
}gpio_pm6_func_t;

/** 
 *  @enum gpio_pm7_func_t
 *  @brief    PortM7 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PM7_INPUT   = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PM7_OUTPUT  = GPIO_FR_NA, /*!< N/A: Output Port    */
}gpio_pm7_func_t;

/** 
 *  @enum gpio_pn0_func_t
 *  @brief    PortN0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PN0_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PN0_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PN0_UT5RTS_N   = GPIO_FR_1, /*!< PNFR1: UT5RTS_N       */
  GPIO_PN0_UT5CTS_N   = GPIO_FR_2, /*!< PNFR2: UT5CTS_N       */
  GPIO_PN0_T32A05OUTA = GPIO_FR_3, /*!< PNFR3: T32A05OUTA     */
  GPIO_PN0_T32A05OUTC = GPIO_FR_4, /*!< PNFR4: T32A05OUTC     */
}gpio_pn0_func_t;
 
/** 
 *  @enum gpio_pn1_func_t
 *  @brief    PortN1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PN1_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PN1_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PN1_UT5CTS_N   = GPIO_FR_1, /*!< PNFR1: UT5CTS_N       */
  GPIO_PN1_UT5RTS_N   = GPIO_FR_2, /*!< PNFR2: UT5RTS_N       */
  GPIO_PN1_T32A05INA0 = GPIO_FR_3, /*!< PNFR3: T32A05INA0      */
  GPIO_PN1_T32A05INC0 = GPIO_FR_4, /*!< PNFR4: T32A05INC0      */
}gpio_pn1_func_t;
 
/** 
 *  @enum gpio_pn2_func_t
 *  @brief    PortN2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PN2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PN2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PN2_UT5RXD     = GPIO_FR_1, /*!< PNFR1: UT5RXD         */
  GPIO_PN2_UT5TXDA    = GPIO_FR_2, /*!< PNFR2: UT5TXDA        */
  GPIO_PN2_T32A05INA1 = GPIO_FR_3, /*!< PNFR3: T32A05INA1     */
  GPIO_PN2_T32A05INC1 = GPIO_FR_4, /*!< PNFR4: T32A05INC1     */
}gpio_pn2_func_t;
 
/** 
 *  @enum gpio_pn3_func_t
 *  @brief    PortN3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PN3_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PN3_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PN3_INT10      = 0,         /*!<     0: INT10          */
  GPIO_PN3_UT5TXDA    = GPIO_FR_1, /*!< PNFR1: UT5TXDA        */
  GPIO_PN3_UT5RXD     = GPIO_FR_2, /*!< PNFR2: UT5RXD         */
  GPIO_PN3_T32A05OUTB = GPIO_FR_3, /*!< PNFR3: T32A05OUTB     */
  GPIO_PN3_TRGIN2     = GPIO_FR_5, /*!< PNFR5: TRGIN2         */
}gpio_pn3_func_t;

 /** 
 *  @enum gpio_pn4_func_t
 *  @brief    PortN4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PN4_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PN4_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PN4_UT5TXDB    = GPIO_FR_1, /*!< PNFR1: UT5TXDB        */
  GPIO_PN4_T32A05INB0 = GPIO_FR_3, /*!< PNFR3: T32A05INB0     */
}gpio_pn4_func_t;
 
/** 
 *  @enum gpio_pn5_func_t
 *  @brief    PortN5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PN5_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PN5_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PN5_T32A05INB1 = GPIO_FR_3, /*!< PNFR3: T32A05INB1     */
}gpio_pn5_func_t;

/** 
 *  @enum gpio_pp0_func_t
 *  @brief    PortP0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PP0_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PP0_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PP0_TSPI2SCK   = GPIO_FR_2, /*!< PPFR2: TSPI2SCK       */
  GPIO_PP0_T32A01OUTA = GPIO_FR_3, /*!< PPFR3: T32A01OUTA     */
  GPIO_PP0_T32A01OUTC = GPIO_FR_4, /*!< PPFR4: T32A01OUTC     */
}gpio_pp0_func_t;
 
/** 
 *  @enum gpio_pp1_func_t
 *  @brief    PortP1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PP1_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PP1_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PP1_TSPI2TXD   = GPIO_FR_2, /*!< PPGFR2: TSPI2TXD       */
  GPIO_PP1_T32A01INA0 = GPIO_FR_3, /*!< PPFR3: T32A01INA0     */
  GPIO_PP1_T32A01INC0 = GPIO_FR_4, /*!< PPFR4: T32A01INC0     */
}gpio_pp1_func_t;
 
/** 
 *  @enum gpio_pp2_func_t
 *  @brief    PortP2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PP2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PP2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PP2_TSPI2RXD   = GPIO_FR_2, /*!< PPFR2: TSPI2RXD       */
  GPIO_PP2_T32A01INA1 = GPIO_FR_3, /*!< PPFR3: T32A01INA1     */
  GPIO_PP2_T32A01INC1 = GPIO_FR_4, /*!< PPFR4: T32A01INC1     */
}gpio_pp2_func_t;
 
 /** 
 *  @enum gpio_pp3_func_t
 *  @brief    PortP3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PP3_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PP3_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PP3_INT14      = 0,         /*!<     0: INT14          */
  GPIO_PP3_TSPI3RXD   = GPIO_FR_1, /*!< PPFR1: TSPI3RXD       */
}gpio_pp3_func_t;

 /** 
 *  @enum gpio_pp4_func_t
 *  @brief    PortP4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PP4_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PP4_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PP4_TSPI3TXD   = GPIO_FR_1, /*!< PPFR1: TSPI3TXD       */
}gpio_pp4_func_t;

 /** 
 *  @enum gpio_pp5_func_t
 *  @brief    PortP5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PP5_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PP5_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PP5_TSPI3SCK   = GPIO_FR_1, /*!< PPFR1: TSPI3SCK       */
}gpio_pp5_func_t;

/** 
 *  @enum gpio_pp6_func_t
 *  @brief    PortP6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PP6_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PP6_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PP6_TSPI3CS0   = GPIO_FR_1, /*!< PPFR1: TSPI3CS0       */
  GPIO_PP6_TSPI3CSIN  = GPIO_FR_2, /*!< PPFR2: TSPI3CSIN      */
  GPIO_PP6_PMD0DBG    = GPIO_FR_3, /*!< PPFR3: PMD0DBG        */
}gpio_pp6_func_t;

 /** 
 *  @enum gpio_pp7_func_t
 *  @brief    PortP7 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PP7_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PP7_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PP7_TSPI3CS1   = GPIO_FR_1, /*!< PPFR1: TSPI3SCK       */
}gpio_pp7_func_t;

/** 
 *  @enum gpio_pr0_func_t
 *  @brief    PortR0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PR0_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PR0_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PR0_T32A02OUTA = GPIO_FR_3, /*!< PRFR3: T32A02OUTA     */
  GPIO_PR0_T32A02OUTC = GPIO_FR_4, /*!< PRFR4: T32A02OUTC     */
}gpio_pr0_func_t;
 
/** 
 *  @enum gpio_pr1_func_t
 *  @brief    PortR1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PR1_INPUT       = 0,         /*!<     0: Input Port     */
  GPIO_PR1_OUTPUT      = 0,         /*!<     0: Output Port    */
  GPIO_PR1_T32A02INA0  = GPIO_FR_3, /*!< PRFR3: T32A02INA0     */
  GPIO_PR1_T32A02INC0  = GPIO_FR_4, /*!< PRFR4: T32A02INC0     */
}gpio_pr1_func_t;
 
/** 
 *  @enum gpio_pr2_func_t
 *  @brief    PortR2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PR2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PR2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PR2_T32A02INA1 = GPIO_FR_3, /*!< PRFR3: T32A02INA1     */
  GPIO_PR2_T32A02INC1 = GPIO_FR_4, /*!< PRFR4: T32A02INC1     */
}gpio_pr2_func_t;

/** 
 *  @enum gpio_pr3_func_t
 *  @brief    PortR3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PR3_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PR3_OUTPUT     = 0,         /*!<     0: Output Port    */
}gpio_pr3_func_t;

/** 
 *  @enum gpio_pr4_func_t
 *  @brief    PortR4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PR4_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PR4_OUTPUT     = 0,         /*!<     0: Output Port    */
}gpio_pr4_func_t;

/** 
 *  @enum gpio_pr5_func_t
 *  @brief    PortR5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PR5_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PR5_OUTPUT     = 0,         /*!<     0: Output Port    */
}gpio_pr5_func_t;

/** 
 *  @enum gpio_pr6_func_t
 *  @brief    PortR6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PR6_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PR6_OUTPUT     = 0,         /*!<     0: Output Port    */
}gpio_pr6_func_t;

/** 
 *  @enum gpio_pr7_func_t
 *  @brief    PortR7 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PR7_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PR7_OUTPUT     = 0,         /*!<     0: Output Port    */
}gpio_pr7_func_t;


/** 
 *  @enum gpio_pt0_func_t
 *  @brief    PortT0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PT0_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PT0_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PT0_INT23      = 0,         /*!<     0: INT23          */
  GPIO_PT0_I2C3SDA    = GPIO_FR_1, /*!< PTFR1: I2C3SDA        */
  GPIO_PT0_TSPI2CS1   = GPIO_FR_2, /*!< PTFR2: TSPI2CS1       */
}gpio_pt0_func_t;

/** 
 *  @enum gpio_pt1_func_t
 *  @brief    PortT1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PT1_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PT1_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PT1_INT24      = 0,         /*!<     0: INT24          */
  GPIO_PT1_I2C3SCL    = GPIO_FR_1, /*!< PTFR1: I2C3SCL        */
  GPIO_PT1_TSPI2CS0   = GPIO_FR_2, /*!< PTFR2: TSPI2CS0       */
  GPIO_PT1_TSPI2CSIN  = GPIO_FR_3, /*!< PTFR3: TSPI2CSIN      */
}gpio_pt1_func_t;

/** 
 *  @enum gpio_pt2_func_t
 *  @brief    PortT2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PT2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PT2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PT2_INT25      = 0,         /*!<     0: INT25          */
  GPIO_PT2_TSPI2SCK   = GPIO_FR_1, /*!< PTFR1: TSPI2SCK       */
  GPIO_PT2_T32A06OUTB = GPIO_FR_3, /*!< PTFR3: T32A06OUTB     */
}gpio_pt2_func_t;

/** 
 *  @enum gpio_pt3_func_t
 *  @brief    PortT3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PT3_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PT3_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PT3_INT26      = 0,         /*!<     0: INT26          */
  GPIO_PT3_TSPI2TXD   = GPIO_FR_1, /*!< PTFR1: TSPI2TXD       */
  GPIO_PT3_T32A06INB0 = GPIO_FR_3, /*!< PTFR3: T32A06INB0     */
}gpio_pt3_func_t;

/** 
 *  @enum gpio_pt4_func_t
 *  @brief    PortT4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PT4_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PT4_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PT4_TSPI2RXD   = GPIO_FR_1, /*!< PTFR1: TSPI2RXD       */
  GPIO_PT4_T32A06INB1 = GPIO_FR_3, /*!< PTFR3: T32A06INB1     */
}gpio_pt4_func_t;

/** 
 *  @enum gpio_pt5_func_t
 *  @brief    PortT5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PT5_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PT5_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PT5_T32A06OUTA = GPIO_FR_3, /*!< PTFR3: T32A06OUTA     */
  GPIO_PT5_T32A06OUTC = GPIO_FR_4, /*!< PTFR4: T32A06OUTC     */
}gpio_pt5_func_t;

/** 
 *  @enum gpio_pt6_func_t
 *  @brief    PortT6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PT6_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PT6_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PT6_T32A06INA0 = GPIO_FR_3, /*!< PTFR3: T32A06INA0     */
  GPIO_PT6_T32A06INC0 = GPIO_FR_4, /*!< PTFR4: T32A06INC0     */
}gpio_pt6_func_t;

/** 
 *  @enum gpio_pt7_func_t
 *  @brief    PortT7 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PT7_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PT7_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PT7_INT29      = 0,         /*!<     0: INT29          */
  GPIO_PT7_T32A06INA1 = GPIO_FR_3, /*!< PTFR3: T32A06INA1     */
  GPIO_PT7_T32A06INC1 = GPIO_FR_4, /*!< PTFR4: T32A06INC1     */
}gpio_pt7_func_t;

/** 
 *  @enum gpio_pu0_func_t
 *  @brief    PortU0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PU0_INPUT      = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PU0_OUTPUT     = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PU0_INT30      = GPIO_FR_NA, /*!< N/A: INT30          */
}gpio_pu0_func_t;

/** 
 *  @enum gpio_pu1_func_t
 *  @brief    PortU1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PU1_INPUT      = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PU1_OUTPUT     = GPIO_FR_NA, /*!< N/A: Output Port    */
  GPIO_PU1_INT31      = GPIO_FR_NA, /*!< N/A: INT31          */
}gpio_pu1_func_t;

/** 
 *  @enum gpio_pu2_func_t
 *  @brief    PortU2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PU2_INPUT      = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PU2_OUTPUT     = GPIO_FR_NA, /*!< N/A: Output Port    */
}gpio_pu2_func_t;

/** 
 *  @enum gpio_pu3_func_t
 *  @brief    PortU3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PU3_INPUT      = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PU3_OUTPUT     = GPIO_FR_NA, /*!< N/A: Output Port    */
}gpio_pu3_func_t;

/** 
 *  @enum gpio_pu4_func_t
 *  @brief    PortU4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PU4_INPUT      = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PU4_OUTPUT     = GPIO_FR_NA, /*!< N/A: Output Port    */
}gpio_pu4_func_t;

/** 
 *  @enum gpio_pu5_func_t
 *  @brief    PortU5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PU5_INPUT      = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PU5_OUTPUT     = GPIO_FR_NA, /*!< N/A: Output Port    */
}gpio_pu5_func_t;

/** 
 *  @enum gpio_pv0_func_t
 *  @brief    PortV0 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PV0_INPUT      = 0,          /*!<   0: Input Port     */
  GPIO_PV0_OUTPUT     = 0,          /*!<   0: Output Port    */
}gpio_pv0_func_t;

/** 
 *  @enum gpio_pv1_func_t
 *  @brief    PortV1 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PV1_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PV1_OUTPUT     = 0,         /*!<     0: Output Port    */
}gpio_pv1_func_t;

/** 
 *  @enum gpio_pv2_func_t
 *  @brief    PortV2 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PV2_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PV2_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PV2_INT17      = 0,         /*!<     0: INT17          */
}gpio_pv2_func_t;

/** 
 *  @enum gpio_pv3_func_t
 *  @brief    PortV3 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PV3_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PV3_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PV3_INT18      = 0,         /*!<     0: INT18          */
}gpio_pv3_func_t;

/** 
 *  @enum gpio_pv4_func_t
 *  @brief    PortV4 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PV4_INPUT      = GPIO_FR_NA, /*!< N/A: Input Port     */
  GPIO_PV4_OUTPUT     = GPIO_FR_NA, /*!< N/A: Output Port    */
}gpio_pv4_func_t;

/** 
 *  @enum gpio_pv5_func_t
 *  @brief    PortV5 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PV5_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PV5_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PV5_UT4TXDB    = GPIO_FR_1, /*!< PVFR1: UT4TXDB        */
}gpio_pv5_func_t;

/** 
 *  @enum gpio_pv6_func_t
 *  @brief    PortV6 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PV6_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PV6_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PV6_UT4TXDA    = GPIO_FR_1, /*!< PVFR1: UT4TXDA        */
  GPIO_PV6_UT4RXD     = GPIO_FR_2, /*!< PVFR2: UT4RXD         */
}gpio_pv6_func_t;

/** 
 *  @enum gpio_pv7_func_t
 *  @brief    PortV7 Function Enumerated Type Definition.
 */
typedef enum
{
  GPIO_PV7_INPUT      = 0,         /*!<     0: Input Port     */
  GPIO_PV7_OUTPUT     = 0,         /*!<     0: Output Port    */
  GPIO_PV7_UT4RXD     = GPIO_FR_1, /*!< PVFR1: UTRXD          */
  GPIO_PV7_UT4TXDA    = GPIO_FR_2, /*!< PVFR2: UT4TXDA        */
}gpio_pv7_func_t;

/**
 *  @} 
 */ /* End of group GPIO_Exported_Typedef */
 
/*------------------------------------------------------------------------------*/
/*  Structure Definition                                                        */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup GPIO_Exported_Typedef GPIO Exported Typedef
 *  @{
 */
/*----------------------------------*/
/** 
 * @brief  GPIO handle structure definenition.
*/
/*----------------------------------*/
#if defined(TMPM3HL)
typedef struct gpio_pa_handle
{  
    TSB_PA_TypeDef       *p_pa_instance;     /*!< Registers base address.           */
    TSB_PB_TypeDef       *p_pb_instance;     /*!< Registers base address.           */
    TSB_PC_TypeDef       *p_pc_instance;     /*!< Registers base address.           */
    TSB_PD_TypeDef       *p_pd_instance;     /*!< Registers base address.           */
    TSB_PE_TypeDef       *p_pe_instance;     /*!< Registers base address.           */
    TSB_PG_TypeDef       *p_pg_instance;     /*!< Registers base address.           */
    TSB_PH_TypeDef       *p_ph_instance;     /*!< Registers base address.           */
    TSB_PJ_TypeDef       *p_pj_instance;     /*!< Registers base address.           */
    TSB_PK_TypeDef       *p_pk_instance;     /*!< Registers base address.           */
    TSB_PL_TypeDef       *p_pl_instance;     /*!< Registers base address.           */
    TSB_PM_TypeDef       *p_pm_instance;     /*!< Registers base address.           */
    TSB_PN_TypeDef       *p_pn_instance;     /*!< Registers base address.           */
    TSB_PP_TypeDef       *p_pp_instance;     /*!< Registers base address.           */
    TSB_PV_TypeDef       *p_pv_instance;     /*!< Registers base address.           */
} gpio_t;
#endif  /* TMPM3HL */
#if defined(TMPM3HM)
typedef struct gpio_pa_handle
{  
    TSB_PA_TypeDef       *p_pa_instance;     /*!< Registers base address.           */
    TSB_PB_TypeDef       *p_pb_instance;     /*!< Registers base address.           */
    TSB_PC_TypeDef       *p_pc_instance;     /*!< Registers base address.           */
    TSB_PD_TypeDef       *p_pd_instance;     /*!< Registers base address.           */
    TSB_PE_TypeDef       *p_pe_instance;     /*!< Registers base address.           */
    TSB_PG_TypeDef       *p_pg_instance;     /*!< Registers base address.           */
    TSB_PH_TypeDef       *p_ph_instance;     /*!< Registers base address.           */
    TSB_PJ_TypeDef       *p_pj_instance;     /*!< Registers base address.           */
    TSB_PK_TypeDef       *p_pk_instance;     /*!< Registers base address.           */
    TSB_PL_TypeDef       *p_pl_instance;     /*!< Registers base address.           */
    TSB_PM_TypeDef       *p_pm_instance;     /*!< Registers base address.           */
    TSB_PN_TypeDef       *p_pn_instance;     /*!< Registers base address.           */
    TSB_PP_TypeDef       *p_pp_instance;     /*!< Registers base address.           */
    TSB_PV_TypeDef       *p_pv_instance;     /*!< Registers base address.           */
} gpio_t;
#endif  /* TMPM3HM */
#if defined(TMPM3HN)
typedef struct gpio_pa_handle
{  
    TSB_PA_TypeDef       *p_pa_instance;     /*!< Registers base address.           */
    TSB_PB_TypeDef       *p_pb_instance;     /*!< Registers base address.           */
    TSB_PC_TypeDef       *p_pc_instance;     /*!< Registers base address.           */
    TSB_PD_TypeDef       *p_pd_instance;     /*!< Registers base address.           */
    TSB_PE_TypeDef       *p_pe_instance;     /*!< Registers base address.           */
    TSB_PF_TypeDef       *p_pf_instance;     /*!< Registers base address.           */
    TSB_PG_TypeDef       *p_pg_instance;     /*!< Registers base address.           */
    TSB_PH_TypeDef       *p_ph_instance;     /*!< Registers base address.           */
    TSB_PJ_TypeDef       *p_pj_instance;     /*!< Registers base address.           */
    TSB_PK_TypeDef       *p_pk_instance;     /*!< Registers base address.           */
    TSB_PL_TypeDef       *p_pl_instance;     /*!< Registers base address.           */
    TSB_PM_TypeDef       *p_pm_instance;     /*!< Registers base address.           */
    TSB_PN_TypeDef       *p_pn_instance;     /*!< Registers base address.           */
    TSB_PP_TypeDef       *p_pp_instance;     /*!< Registers base address.           */
    TSB_PR_TypeDef       *p_pr_instance;     /*!< Registers base address.           */
    TSB_PV_TypeDef       *p_pv_instance;     /*!< Registers base address.           */
} gpio_t;
#endif  /* TMPM3HN */
#if defined(TMPM3HN_L)
typedef struct gpio_pa_handle
{  
    TSB_PA_TypeDef       *p_pa_instance;     /*!< Registers base address.           */
    TSB_PB_TypeDef       *p_pb_instance;     /*!< Registers base address.           */
    TSB_PC_TypeDef       *p_pc_instance;     /*!< Registers base address.           */
    TSB_PD_TypeDef       *p_pd_instance;     /*!< Registers base address.           */
    TSB_PE_TypeDef       *p_pe_instance;     /*!< Registers base address.           */
    TSB_PF_TypeDef       *p_pf_instance;     /*!< Registers base address.           */
    TSB_PG_TypeDef       *p_pg_instance;     /*!< Registers base address.           */
    TSB_PH_TypeDef       *p_ph_instance;     /*!< Registers base address.           */
    TSB_PJ_TypeDef       *p_pj_instance;     /*!< Registers base address.           */
    TSB_PK_TypeDef       *p_pk_instance;     /*!< Registers base address.           */
    TSB_PL_TypeDef       *p_pl_instance;     /*!< Registers base address.           */
    TSB_PM_TypeDef       *p_pm_instance;     /*!< Registers base address.           */
    TSB_PN_TypeDef       *p_pn_instance;     /*!< Registers base address.           */
    TSB_PP_TypeDef       *p_pp_instance;     /*!< Registers base address.           */
    TSB_PR_TypeDef       *p_pr_instance;     /*!< Registers base address.           */
    TSB_PV_TypeDef       *p_pv_instance;     /*!< Registers base address.           */
} gpio_t;
#endif  /* TMPM3HN_L */
#if defined(TMPM3HP)
typedef struct gpio_pa_handle
{  
    TSB_PA_TypeDef       *p_pa_instance;     /*!< Registers base address.           */
    TSB_PB_TypeDef       *p_pb_instance;     /*!< Registers base address.           */
    TSB_PC_TypeDef       *p_pc_instance;     /*!< Registers base address.           */
    TSB_PD_TypeDef       *p_pd_instance;     /*!< Registers base address.           */
    TSB_PE_TypeDef       *p_pe_instance;     /*!< Registers base address.           */
    TSB_PF_TypeDef       *p_pf_instance;     /*!< Registers base address.           */
    TSB_PG_TypeDef       *p_pg_instance;     /*!< Registers base address.           */
    TSB_PH_TypeDef       *p_ph_instance;     /*!< Registers base address.           */
    TSB_PJ_TypeDef       *p_pj_instance;     /*!< Registers base address.           */
    TSB_PK_TypeDef       *p_pk_instance;     /*!< Registers base address.           */
    TSB_PL_TypeDef       *p_pl_instance;     /*!< Registers base address.           */
    TSB_PM_TypeDef       *p_pm_instance;     /*!< Registers base address.           */
    TSB_PN_TypeDef       *p_pn_instance;     /*!< Registers base address.           */
    TSB_PP_TypeDef       *p_pp_instance;     /*!< Registers base address.           */
    TSB_PR_TypeDef       *p_pr_instance;     /*!< Registers base address.           */
    TSB_PT_TypeDef       *p_pt_instance;     /*!< Registers base address.           */
    TSB_PV_TypeDef       *p_pv_instance;     /*!< Registers base address.           */
} gpio_t;
#endif  /* TMPM3HP */
#if defined(TMPM3HQ)
typedef struct gpio_pa_handle
{  
    TSB_PA_TypeDef       *p_pa_instance;     /*!< Registers base address.           */
    TSB_PB_TypeDef       *p_pb_instance;     /*!< Registers base address.           */
    TSB_PC_TypeDef       *p_pc_instance;     /*!< Registers base address.           */
    TSB_PD_TypeDef       *p_pd_instance;     /*!< Registers base address.           */
    TSB_PE_TypeDef       *p_pe_instance;     /*!< Registers base address.           */
    TSB_PF_TypeDef       *p_pf_instance;     /*!< Registers base address.           */
    TSB_PG_TypeDef       *p_pg_instance;     /*!< Registers base address.           */
    TSB_PH_TypeDef       *p_ph_instance;     /*!< Registers base address.           */
    TSB_PJ_TypeDef       *p_pj_instance;     /*!< Registers base address.           */
    TSB_PK_TypeDef       *p_pk_instance;     /*!< Registers base address.           */
    TSB_PL_TypeDef       *p_pl_instance;     /*!< Registers base address.           */
    TSB_PM_TypeDef       *p_pm_instance;     /*!< Registers base address.           */
    TSB_PN_TypeDef       *p_pn_instance;     /*!< Registers base address.           */
    TSB_PP_TypeDef       *p_pp_instance;     /*!< Registers base address.           */
    TSB_PR_TypeDef       *p_pr_instance;     /*!< Registers base address.           */
    TSB_PT_TypeDef       *p_pt_instance;     /*!< Registers base address.           */
    TSB_PU_TypeDef       *p_pu_instance;     /*!< Registers base address.           */
    TSB_PV_TypeDef       *p_pv_instance;     /*!< Registers base address.           */
} gpio_t;
#endif  /* TMPM3HQ */
/**
 *  @}
 */ /* End of group GPIO_Exported_Typedef */
 
/*------------------------------------------------------------------------------*/
/*  Functions                                                                   */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup GPIO_Exported_functions GPIO Exported Functions
 *  @{
 */
TXZ_Result gpio_init(gpio_t *p_obj, uint32_t group);
TXZ_Result gpio_deinit(gpio_t *p_obj, uint32_t group);
TXZ_Result gpio_write_mode(gpio_t *p_obj, uint32_t group, uint32_t mode, uint32_t val);
TXZ_Result gpio_read_mode(gpio_t *p_obj, uint32_t group, uint32_t mode, uint32_t *val);
TXZ_Result gpio_func(gpio_t *p_obj, gpio_gr_t group, gpio_num_t num, uint32_t func, gpio_pininout_t inout);
TXZ_Result gpio_SetPullUp(gpio_t *p_obj, gpio_gr_t group, gpio_num_t num, gpio_pinstate_t val);
TXZ_Result gpio_SetPullDown(gpio_t *p_obj, gpio_gr_t group, gpio_num_t num, gpio_pinstate_t val);
TXZ_Result gpio_SetOpenDrain(gpio_t *p_obj, gpio_gr_t group, gpio_num_t num, gpio_pinstate_t val);
TXZ_Result gpio_write_bit(gpio_t *p_obj, uint32_t group, uint32_t num, uint32_t mode, uint32_t val);
TXZ_Result gpio_read_bit(gpio_t *p_obj, uint32_t group, uint32_t num, uint32_t mode, gpio_pinstate_t *pinstate);

/**
 *  @}
 */ /* End of group GPIO_Exported_functions */
 
/**
 *  @}
 */ /* End of group GPIO */
 
/**
 *  @}
 */ /* End of group Periph_Driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __GPIO_H */
