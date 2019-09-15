/**
 *******************************************************************************
 * @file    txz_gpio.c
 * @brief   This file provides API functions for GPIO driver.
 * @version V1.0.0.9
 * $Date:: 2018-11-06 14:52:07 #$
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
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
#include "txz_gpio.h"
     
#if defined(__GPIO_H)
/**
 *  @addtogroup Periph_Driver
 *  @{
 */

/** 
 *  @addtogroup GPIO
 *  @{
 */

/*------------------------------------------------------------------------------*/
/*  Macro Definition                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup GPIO_Private_define GPIO Private Define
 *  @{
 */
/** 
 *  @name  Parameter Result
 *  @brief Whether the parameter is specified or not.
 *  @{
 */
#define PARAM_OK    ((int32_t)1)    /*!< Parameter is valid(specified).         */
#define PARAM_NG    ((int32_t)0)    /*!< Parameter is invalid(not specified).   */
/**
 *  @}
 */ /* End of name Parameter Result */
 
/** 
 *  @name  Bit Operation Macro
 *  @brief Whether the parameter is specified or not.
 *  @{
 */
#define PORT_BASE (0x400C0000UL) /*!< Port Register Base Adress */
#define BITBAND_PORT_OFFSET (0x0000100UL) /*!< Port Register Offset Value */
#define BITBAND_PORT_BASE(gr) (PORT_BASE + (uint32_t)((BITBAND_PORT_OFFSET) * (gr)) ) /*!<  Operational target Port Adress */
#define BITBAND_PORT_MODE_BASE(base, pinmode) ((uint32_t)(base) + (uint32_t)(pinmode) )  /*!< Operational target Control Register Adress */
#define BITBAND_PORT_SET(base, bitnum) (*((__IO uint32_t *)base) |= (uint32_t)(0x0000001UL<< bitnum)) /*!< Target Pin Bit set */
#define BITBAND_PORT_CLR(base, bitnum) (*((__IO uint32_t *)base) &= ~((uint32_t)(0x0000001UL<< bitnum))) /*!< Target Pin Bit clear */
#define BITBAND_PORT_READ(val, base, bitnum) val = ((*((__IO uint32_t *)base) & (uint32_t)(0x0000001UL<< bitnum)) >> bitnum) /*!< Target Pin Bit read */
/**
 *  @}
 */ /* End of Bit Operation Macro */
/**
 *  @}
 */ /* End of group GPIO_Private_typedef */

/*------------------------------------------------------------------------------*/
/*  Enumerated Type Definition                                                  */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup GPIO_Private_define GPIO Private Define
 *  @{
 */

/* no define */

/** 
 *  @}
 */ /* End of group GPIO_Private_define */
/*------------------------------------------------------------------------------*/
/*  Structure Definition                                                        */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup GPIO_Private_typedef GPIO Private Typedef
 *  @{
 */
/*!
  * @brief  Pin Exist Table
  * @details Bit0 :GPIO_Mode_DATA
  * @details Bit1 :GPIO_Mode_CR
  * @details Bit2 :GPIO_Mode_FR1
  * @details Bit3 :GPIO_Mode_FR2
  * @details Bit4 :GPIO_Mode_FR3
  * @details Bit5 :GPIO_Mode_FR4
  * @details Bit6 :GPIO_Mode_FR5
  * @details Bit7 :GPIO_Mode_FR6
  * @details Bit8 :-
  * @details Bit9 :GPIO_Mode_OD
  * @details Bit10 :GPIO_Mode_PUP
  * @details Bit11 :GPIO_Mode_PDN
  * @details Bit12 :GPIO_Mode_IE
  */
#if defined(TMPM3HL)
static uint16_t PinExistTbl[GPIO_GROUP_Max][GPIO_PORT_Max] =
{
   /* Port-0  Port-1  Port-2  Port-3  Port-4  Port-5  Port-6  Port-7 */
    { 0x1EF7, 0x1EFF, 0x1EFF, 0x1EBB, 0x0000, 0x0000, 0x1E0F, 0x1E0F },     /** GPIO_PORT_A */
    { 0x0EE3, 0x1EE7, 0x1E6F, 0x1E2F, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_B */
    { 0x1E37, 0x1E37, 0x0000, 0x1E1F, 0x1E1F, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_C */
    { 0x1E03, 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_D */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000 },     /** GPIO_PORT_E */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_F */
    { 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_G */
    { 0x1801, 0x1801, 0x1801, 0x1801, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_H */
    { 0x1E77, 0x1E7F, 0x1E7F, 0x1E5F, 0x1E5F, 0x1E53, 0x0000, 0x0000 },     /** GPIO_PORT_J */
    { 0x1E47, 0x1E4F, 0x1E3F, 0x1E3F, 0x1E3F, 0x1E13, 0x1E13, 0x0000 },     /** GPIO_PORT_K */
    { 0x1E1F, 0x1E1F, 0x1E1F, 0x1E1F, 0x1E13, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_L */
    { 0x1E77, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_M */
    { 0x0000, 0x1E3F, 0x1E3F, 0x1E5F, 0x1E17, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_N */
    { 0x0000, 0x0000, 0x0000, 0x1E07, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_P */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_R */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_T */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_U */
    { 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_V */
};
#endif  /* TMPM3HL */
#if defined(TMPM3HM)
static uint16_t PinExistTbl[GPIO_GROUP_Max][GPIO_PORT_Max] =
{
   /* Port-0  Port-1  Port-2  Port-3  Port-4  Port-5  Port-6  Port-7 */
    { 0x1EF7, 0x1EFF, 0x1EFF, 0x1EBB, 0x1E37, 0x1E27, 0x1E0F, 0x1E0F },     /** GPIO_PORT_A */
    { 0x0EE3, 0x1EE7, 0x1E7F, 0x1E3F, 0x1E3F, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_B */
    { 0x1E37, 0x1E37, 0x1E77, 0x1E1F, 0x1E1F, 0x1E1F, 0x110F, 0x0000 },     /** GPIO_PORT_C */
    { 0x1E03, 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_D */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000 },     /** GPIO_PORT_E */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_F */
    { 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_G */
    { 0x1801, 0x1801, 0x1801, 0x1801, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_H */
    { 0x1F77, 0x1E7F, 0x1E7F, 0x1E5F, 0x1E5F, 0x1E53, 0x0000, 0x0000 },     /** GPIO_PORT_J */
    { 0x1E47, 0x1E4F, 0x1E3F, 0x1E3F, 0x1E3F, 0x1E13, 0x1E13, 0x1E13 },     /** GPIO_PORT_K */
    { 0x1E1F, 0x1E1F, 0x1E1F, 0x1E1F, 0x1E13, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_L */
    { 0x1EF7, 0x1EFF, 0x1EFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_M */
    { 0x1E3F, 0x1E3F, 0x1E3F, 0x1E5F, 0x1E17, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_N */
    { 0x1E3B, 0x1E3B, 0x1E3B, 0x1E07, 0x1E07, 0x1E07, 0x1E1F, 0x0000 },     /** GPIO_PORT_P */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_R */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_T */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_U */
    { 0x1E83, 0x1E83, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_V */
};
#endif  /* TMPM3HM */
#if defined(TMPM3HN)
static uint16_t PinExistTbl[GPIO_GROUP_Max][GPIO_PORT_Max] =
{
   /* Port-0  Port-1  Port-2  Port-3  Port-4  Port-5  Port-6  Port-7 */
    { 0x1EF7, 0x1EFF, 0x1EFF, 0x1EBB, 0x1E37, 0x1E27, 0x1E0F, 0x1E0F },     /** GPIO_PORT_A */
    { 0x0EE3, 0x1EE7, 0x1E7F, 0x1E3F, 0x1E3F, 0x1E7F, 0x1E13, 0x1E03 },     /** GPIO_PORT_B */
    { 0x1E37, 0x1E37, 0x1E77, 0x1E1F, 0x1E1F, 0x1E1F, 0x110F, 0x0000 },     /** GPIO_PORT_C */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_D */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000 },     /** GPIO_PORT_E */
    { 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_F */
    { 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_G */
    { 0x1801, 0x1801, 0x1801, 0x1801, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_H */
    { 0x1F77, 0x1E7F, 0x1E7F, 0x1E5F, 0x1E5F, 0x1E53, 0x0000, 0x0000 },     /** GPIO_PORT_J */
    { 0x1E47, 0x1E4F, 0x1E3F, 0x1E3F, 0x1E3F, 0x1E13, 0x1E13, 0x1E13 },     /** GPIO_PORT_K */
    { 0x1E1F, 0x1E1F, 0x1E1F, 0x1E1F, 0x1E13, 0x1E33, 0x1E33, 0x0000 },     /** GPIO_PORT_L */
    { 0x1EF7, 0x1EFF, 0x1EFF, 0x1EFF, 0x1EBF, 0x1E23, 0x1E03, 0x0000 },     /** GPIO_PORT_M */
    { 0x1E3F, 0x1E3F, 0x1E3F, 0x1E5F, 0x1E17, 0x1E13, 0x0000, 0x0000 },     /** GPIO_PORT_N */
    { 0x1E3B, 0x1E3B, 0x1E3B, 0x1E07, 0x1E07, 0x1E07, 0x1E1F, 0x1E07 },     /** GPIO_PORT_P */
    { 0x1E33, 0x1E33, 0x1E33, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_R */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_T */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_U */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_V */
};
#endif  /* TMPM3HN */
#if defined(TMPM3HN_L)
static uint16_t PinExistTbl[GPIO_GROUP_Max][GPIO_PORT_Max] =
{
   /* Port-0  Port-1  Port-2  Port-3  Port-4  Port-5  Port-6  Port-7 */
    { 0x1EF7, 0x1EFF, 0x1EFF, 0x1EBB, 0x1E37, 0x1E27, 0x1E0F, 0x1E0F },     /** GPIO_PORT_A */
    { 0x0EE3, 0x1EE7, 0x1E7F, 0x1E3F, 0x1E3F, 0x1E7F, 0x1E13, 0x1E03 },     /** GPIO_PORT_B */
    { 0x1E37, 0x1E37, 0x1E77, 0x1E1F, 0x1E1F, 0x1E1F, 0x110F, 0x0000 },     /** GPIO_PORT_C */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_D */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000 },     /** GPIO_PORT_E */
    { 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_F */
    { 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_G */
    { 0x1801, 0x1801, 0x1801, 0x1801, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_H */
    { 0x1E77, 0x1E7F, 0x1E7F, 0x1E5F, 0x1E5F, 0x1E53, 0x0000, 0x0000 },     /** GPIO_PORT_J */
    { 0x1E47, 0x1E4F, 0x1E3F, 0x1E3F, 0x1E3F, 0x1E13, 0x1E13, 0x1E13 },     /** GPIO_PORT_K */
    { 0x1E1F, 0x1E1F, 0x1E1F, 0x1E1F, 0x1E13, 0x1E33, 0x1E33, 0x0000 },     /** GPIO_PORT_L */
    { 0x1EF7, 0x1EFF, 0x1EFF, 0x1EFF, 0x1EBF, 0x1E23, 0x0000, 0x0000 },     /** GPIO_PORT_M */
    { 0x1E3F, 0x1E3F, 0x1E3F, 0x1E5F, 0x1E17, 0x1E13, 0x0000, 0x0000 },     /** GPIO_PORT_N */
    { 0x1E3B, 0x1E3B, 0x1E3B, 0x1E07, 0x1E07, 0x1E07, 0x1E1F, 0x1E07 },     /** GPIO_PORT_P */
    { 0x1E33, 0x1E33, 0x1E33, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_R */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_T */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_U */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_V */
};
#endif  /* TMPM3HN_L */
#if defined(TMPM3HP)
static uint16_t PinExistTbl[GPIO_GROUP_Max][GPIO_PORT_Max] =
{
   /* Port-0  Port-1  Port-2  Port-3  Port-4  Port-5  Port-6  Port-7 */
    { 0x1EF7, 0x1EFF, 0x1EFF, 0x1EBB, 0x1E37, 0x1E27, 0x1E0F, 0x1E0F },     /** GPIO_PORT_A */
    { 0x0EE3, 0x1EE7, 0x1E7F, 0x1E3F, 0x1E3F, 0x1E7F, 0x1E13, 0x1E03 },     /** GPIO_PORT_B */
    { 0x1E37, 0x1E37, 0x1E77, 0x1E1F, 0x1E1F, 0x1E1F, 0x110F, 0x0000 },     /** GPIO_PORT_C */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_D */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000 },     /** GPIO_PORT_E */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03 },     /** GPIO_PORT_F */
    { 0x1E03, 0x1E03, 0x1E3F, 0x1E3F, 0x1E37, 0x1E13, 0x1E13, 0x1E13 },     /** GPIO_PORT_G */
    { 0x1801, 0x1801, 0x1801, 0x1801, 0x1E07, 0x1E07, 0x1E07, 0x1E03 },     /** GPIO_PORT_H */
    { 0x1F77, 0x1E7F, 0x1E7F, 0x1E5F, 0x1E5F, 0x1E53, 0x0000, 0x0000 },     /** GPIO_PORT_J */
    { 0x1E47, 0x1E4F, 0x1E3F, 0x1E3F, 0x1E3F, 0x1E13, 0x1E13, 0x1E13 },     /** GPIO_PORT_K */
    { 0x1E1F, 0x1E1F, 0x1E1F, 0x1E1F, 0x1E13, 0x1E33, 0x1E33, 0x1E33 },     /** GPIO_PORT_L */
    { 0x1EF7, 0x1EFF, 0x1EFF, 0x1EFF, 0x1EBF, 0x1E23, 0x1E03, 0x1E03 },     /** GPIO_PORT_M */
    { 0x1E3F, 0x1E3F, 0x1E3F, 0x1E5F, 0x1E17, 0x1E13, 0x0000, 0x0000 },     /** GPIO_PORT_N */
    { 0x1E3B, 0x1E3B, 0x1E3B, 0x1E07, 0x1E07, 0x1E07, 0x1E1F, 0x1E07 },     /** GPIO_PORT_P */
    { 0x1E33, 0x1E33, 0x1E33, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03 },     /** GPIO_PORT_R */
    { 0x1E0F, 0x1E1F, 0x1E17, 0x1E17, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_T */
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_U */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000, 0x0000, 0x0000, 0x0000 },     /** GPIO_PORT_V */
};
#endif  /* TMPM3HP */
#if defined(TMPM3HQ)
static uint16_t PinExistTbl[GPIO_GROUP_Max][GPIO_PORT_Max] =
{
   /* Port-0  Port-1  Port-2  Port-3  Port-4  Port-5  Port-6  Port-7 */
    { 0x1EF7, 0x1EFF, 0x1EFF, 0x1EBB, 0x1E37, 0x1E27, 0x1E0F, 0x1E0F },     /** GPIO_PORT_A */
    { 0x0EE3, 0x1EE7, 0x1E7F, 0x1E3F, 0x1E3F, 0x1E7F, 0x1E13, 0x1E03 },     /** GPIO_PORT_B */
    { 0x1E37, 0x1E37, 0x1E77, 0x1E1F, 0x1E1F, 0x1E1F, 0x1E0F, 0x0000 },     /** GPIO_PORT_C */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000, 0x0000 },     /** GPIO_PORT_D */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000 },     /** GPIO_PORT_E */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03 },     /** GPIO_PORT_F */
    { 0x1E03, 0x1E03, 0x1E3F, 0x1E3F, 0x1E37, 0x1E13, 0x1E13, 0x1E13 },     /** GPIO_PORT_G */
    { 0x1801, 0x1801, 0x1801, 0x1801, 0x1E07, 0x1E07, 0x1E07, 0x1E03 },     /** GPIO_PORT_H */
    { 0x1F77, 0x1E7F, 0x1E7F, 0x1E5F, 0x1E5F, 0x1E53, 0x0000, 0x0000 },     /** GPIO_PORT_J */
    { 0x1E47, 0x1E4F, 0x1E3F, 0x1E3F, 0x1E3F, 0x1E13, 0x1E13, 0x1E13 },     /** GPIO_PORT_K */
    { 0x1E1F, 0x1E1F, 0x1E1F, 0x1E1F, 0x1E13, 0x1E33, 0x1E33, 0x1E33 },     /** GPIO_PORT_L */
    { 0x1EF7, 0x1EFF, 0x1EFF, 0x1EFF, 0x1EBF, 0x1E23, 0x1E03, 0x1E03 },     /** GPIO_PORT_M */
    { 0x1E3F, 0x1E3F, 0x1E3F, 0x1E5F, 0x1E17, 0x1E13, 0x0000, 0x0000 },     /** GPIO_PORT_N */
    { 0x1E3B, 0x1E3B, 0x1E3B, 0x1E07, 0x1E07, 0x1E07, 0x1E1F, 0x1E07 },     /** GPIO_PORT_P */
    { 0x1E33, 0x1E33, 0x1E33, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03 },     /** GPIO_PORT_R */
    { 0x1E0F, 0x1E1F, 0x1E17, 0x1E17, 0x1E17, 0x1E33, 0x1E33, 0x1E33 },     /** GPIO_PORT_T */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x0000, 0x0000 },     /** GPIO_PORT_U */
    { 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E03, 0x1E07, 0x1E0F, 0x1E0F },     /** GPIO_PORT_V */
};
#endif  /* TMPM3HQ */

/**
 *  @}
 */ /* End of group GPIO_Private_typedef */
 
/*------------------------------------------------------------------------------*/
/*  Private Function                                                            */
/*------------------------------------------------------------------------------*/
/** 
 *  @defgroup GPIO_Private_fuctions GPIO Private Fuctions
 *  @{
 */
static uint8_t change_mode_to_num( uint32_t mode );
static uint8_t change_func_to_num( uint32_t mode );
static int32_t check_param_pin_exist(gpio_t *p_obj, uint32_t group, uint32_t num, uint32_t mode);
static int32_t check_param_func_pin_exist(gpio_t *p_obj, uint32_t group, uint32_t num, uint32_t mode);

/*--------------------------------------------------*/
/*!
  * @fn     static int32_t check_param_pin_exist(gpio_t *p_obj, uint32_t group, uint32_t num, uint32_t mode)
  * @brief  Check the Pin Exist.
  * @param[in] p_obj :GPIO object.
  * @param[in] group :GPIO Port Group.  : Use @ref gpio_gr_t
  * @param[in] num   :GPIO Port Number. : Use @ref gpio_num_t
  * @param[in] mode  :GPIO Port Mode. : Use @ref gpio_mode_t
  * @retval PARAM_OK :Valid
  * @retval PARAM_NG :Invalid
  */
/*--------------------------------------------------*/

static uint8_t change_mode_to_num( uint32_t mode )
{
    uint8_t retVal = 0;

    if (mode == GPIO_Mode_DATA) {retVal = 0;}
    else if (mode == GPIO_Mode_CR) {retVal = 1;}
    else if (mode == GPIO_Mode_FR1) {retVal = 2;}
    else if (mode == GPIO_Mode_FR2) {retVal = 3;}
    else if (mode == GPIO_Mode_FR3) {retVal = 4;}
    else if (mode == GPIO_Mode_FR4) {retVal = 5;}
    else if (mode == GPIO_Mode_FR5) {retVal = 6;}
    else if (mode == GPIO_Mode_FR6) {retVal = 7;}
    else if (mode == GPIO_Mode_FR7) {retVal = 8;}
    else if (mode == GPIO_Mode_OD) {retVal = 9;}
    else if (mode == GPIO_Mode_PUP) {retVal = 10;}
    else if (mode == GPIO_Mode_PDN) {retVal = 11;}
    else if (mode == GPIO_Mode_IE) {retVal = 12;}
    else {retVal = 13;}

    return retVal;
}

static uint8_t change_func_to_num( uint32_t mode )
{
    uint8_t retVal = 0;

    if  (mode == GPIO_FR_1) {retVal = 2;}
    else if (mode == GPIO_FR_2) {retVal = 3;}
    else if (mode == GPIO_FR_3) {retVal = 4;}
    else if (mode == GPIO_FR_4) {retVal = 5;}
    else if (mode == GPIO_FR_5) {retVal = 6;}
    else if (mode == GPIO_FR_6) {retVal = 7;}
    else if (mode == GPIO_FR_7) {retVal = 8;}
    else if (mode == GPIO_FR_NA) {retVal = 1;}
    else if (mode == 0) {retVal = 1;}
    else {retVal = 13;}

    return retVal;
}

static int32_t check_param_pin_exist(gpio_t *p_obj, uint32_t group, uint32_t num, uint32_t mode)
{
    int32_t result = PARAM_NG;
    uint8_t chgmode;
    uint16_t tmp;

    chgmode = change_mode_to_num(mode);
    if ((chgmode < 13) && (group < GPIO_GROUP_Max) && (num < GPIO_PORT_Max))
    {
        tmp = (PinExistTbl[group][num] >> chgmode) & 0x01;
        result = PARAM_OK;
        if (tmp == 0) {result = PARAM_NG;}
    }
    else
        {result = PARAM_NG;}

    return (result);
}
static int32_t check_param_func_pin_exist(gpio_t *p_obj, uint32_t group, uint32_t num, uint32_t mode)
{
    int32_t result = PARAM_NG;
    uint8_t chgfunc;
    uint16_t tmp;

    chgfunc = change_func_to_num(mode);
    /* param check skip if func is INPUT or OUTPUT */
    if(chgfunc == 1)
    {
        return (PARAM_OK);
    }       
    if ((chgfunc < 13) && (group < GPIO_GROUP_Max) && (num < GPIO_PORT_Max))
    {
        tmp = (PinExistTbl[group][num] >> chgfunc) & 0x01;
        result = PARAM_OK;
        if (tmp == 0) {result = PARAM_NG;}
    }
    else
        {result = PARAM_NG;}

    return (result);
}
/**
 *  @}
 */ /* End of group GPIO_Private_functions */



/*------------------------------------------------------------------------------*/
/*  Public Function                                                             */
/*------------------------------------------------------------------------------*/
/** 
 *  @addtogroup GPIO_Exported_functions
 *  @{
 */
/*--------------------------------------------------*/
/*!
  * @fn     TXZ_Result gpio_init(gpio_t *p_obj, uint32_t group)
  * @brief     Initialize the GPIO object.
  * @param[in] p_obj :GPIO object.
  * @param[in] group :GPIO Port Group.  : Use @ref gpio_gr_t
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note      When p_obj is NULL, "Failure" is returned.
  * @note      An initial value of default is set at the
               reset status value. If needed, please
               rewrite and use an initial value.
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result gpio_init(gpio_t *p_obj, uint32_t group)
{
    TXZ_Result result = TXZ_SUCCESS;

    /* Check the NULL of address. */
    if ((void*)(p_obj) == (void*)0)
    {
        result = TXZ_ERROR;
    }
    else
    {
        switch (group)
        {
#if defined(TMPM3HL)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Enable */
            TSB_CG_FSYSENA_IPENA00 = 1U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Enable */
            TSB_CG_FSYSENA_IPENA01 = 1U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Enable */
            TSB_CG_FSYSENA_IPENA02 = 1U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Enable */
            TSB_CG_FSYSENA_IPENA03 = 1U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Enable */
            TSB_CG_FSYSENA_IPENA04 = 1U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Enable */
            TSB_CG_FSYSENA_IPENA06 = 1U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Enable */
            TSB_CG_FSYSENA_IPENA07 = 1U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Enable */
            TSB_CG_FSYSENA_IPENA08 = 1U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Enable */
            TSB_CG_FSYSENA_IPENA09 = 1U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Enable */
            TSB_CG_FSYSENA_IPENA10 = 1U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Enable */
            TSB_CG_FSYSENA_IPENA11 = 1U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->FR5   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Enable */
            TSB_CG_FSYSENA_IPENA12 = 1U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Enable */
            TSB_CG_FSYSENA_IPENA13 = 1U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Enable */
            TSB_CG_FSYSENA_IPENA17 = 1U;
            break;
#endif  /* TMPM3HL */
#if defined(TMPM3HM)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Enable */
            TSB_CG_FSYSENA_IPENA00 = 1U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR3   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Enable */
            TSB_CG_FSYSENA_IPENA01 = 1U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Enable */
            TSB_CG_FSYSENA_IPENA02 = 1U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Enable */
            TSB_CG_FSYSENA_IPENA03 = 1U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Enable */
            TSB_CG_FSYSENA_IPENA04 = 1U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Enable */
            TSB_CG_FSYSENA_IPENA06 = 1U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Enable */
            TSB_CG_FSYSENA_IPENA07 = 1U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Enable */
            TSB_CG_FSYSENA_IPENA08 = 1U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Enable */
            TSB_CG_FSYSENA_IPENA09 = 1U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Enable */
            TSB_CG_FSYSENA_IPENA10 = 1U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Enable */
            TSB_CG_FSYSENA_IPENA11 = 1U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Enable */
            TSB_CG_FSYSENA_IPENA12 = 1U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->FR2   =  0x00;
            p_obj->p_pp_instance->FR3   =  0x00;
            p_obj->p_pp_instance->FR4   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Enable */
            TSB_CG_FSYSENA_IPENA13 = 1U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Enable */
            TSB_CG_FSYSENA_IPENA17 = 1U;
            break;
#endif  /* TMPM3HM */
#if defined(TMPM3HN)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Enable */
            TSB_CG_FSYSENA_IPENA00 = 1U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR3   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Enable */
            TSB_CG_FSYSENA_IPENA01 = 1U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Enable */
            TSB_CG_FSYSENA_IPENA02 = 1U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Enable */
            TSB_CG_FSYSENA_IPENA03 = 1U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Enable */
            TSB_CG_FSYSENA_IPENA04 = 1U;
            break;
        case GPIO_PORT_F:
            p_obj->p_pf_instance->DATA  =  0x00;
            p_obj->p_pf_instance->IE    =  0x00;
            p_obj->p_pf_instance->CR    =  0x00;
            p_obj->p_pf_instance->OD    =  0x00;
            p_obj->p_pf_instance->PUP   =  0x00;
            p_obj->p_pf_instance->PDN   =  0x00;
            /* PF Clock Enable */
            TSB_CG_FSYSENA_IPENA05 = 1U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Enable */
            TSB_CG_FSYSENA_IPENA06 = 1U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Enable */
            TSB_CG_FSYSENA_IPENA07 = 1U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Enable */
            TSB_CG_FSYSENA_IPENA08 = 1U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Enable */
            TSB_CG_FSYSENA_IPENA09 = 1U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Enable */
            TSB_CG_FSYSENA_IPENA10 = 1U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Enable */
            TSB_CG_FSYSENA_IPENA11 = 1U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->FR5   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Enable */
            TSB_CG_FSYSENA_IPENA12 = 1U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->FR2   =  0x00;
            p_obj->p_pp_instance->FR3   =  0x00;
            p_obj->p_pp_instance->FR4   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Enable */
            TSB_CG_FSYSENA_IPENA13 = 1U;
            break;
        case GPIO_PORT_R:
            p_obj->p_pr_instance->DATA  =  0x00;
            p_obj->p_pr_instance->IE    =  0x00;
            p_obj->p_pr_instance->FR3   =  0x00;
            p_obj->p_pr_instance->FR4   =  0x00;
            p_obj->p_pr_instance->CR    =  0x00;
            p_obj->p_pr_instance->OD    =  0x00;
            p_obj->p_pr_instance->PUP   =  0x00;
            p_obj->p_pr_instance->PDN   =  0x00;
            /* PR Clock Enable */
            TSB_CG_FSYSENA_IPENA14 = 1U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Enable */
            TSB_CG_FSYSENA_IPENA17 = 1U;
            break;
#endif  /* TMPM3HN */
#if defined(TMPM3HN_L)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Enable */
            TSB_CG_FSYSENA_IPENA00 = 1U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR3   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Enable */
            TSB_CG_FSYSENA_IPENA01 = 1U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Enable */
            TSB_CG_FSYSENA_IPENA02 = 1U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Enable */
            TSB_CG_FSYSENA_IPENA03 = 1U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Enable */
            TSB_CG_FSYSENA_IPENA04 = 1U;
            break;
        case GPIO_PORT_F:
            p_obj->p_pf_instance->DATA  =  0x00;
            p_obj->p_pf_instance->IE    =  0x00;
            p_obj->p_pf_instance->CR    =  0x00;
            p_obj->p_pf_instance->OD    =  0x00;
            p_obj->p_pf_instance->PUP   =  0x00;
            p_obj->p_pf_instance->PDN   =  0x00;
            /* PF Clock Enable */
            TSB_CG_FSYSENA_IPENA05 = 1U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Enable */
            TSB_CG_FSYSENA_IPENA06 = 1U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Enable */
            TSB_CG_FSYSENA_IPENA07 = 1U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Enable */
            TSB_CG_FSYSENA_IPENA08 = 1U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Enable */
            TSB_CG_FSYSENA_IPENA09 = 1U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Enable */
            TSB_CG_FSYSENA_IPENA10 = 1U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Enable */
            TSB_CG_FSYSENA_IPENA11 = 1U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->FR5   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Enable */
            TSB_CG_FSYSENA_IPENA12 = 1U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->FR2   =  0x00;
            p_obj->p_pp_instance->FR3   =  0x00;
            p_obj->p_pp_instance->FR4   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Enable */
            TSB_CG_FSYSENA_IPENA13 = 1U;
            break;
        case GPIO_PORT_R:
            p_obj->p_pr_instance->DATA  =  0x00;
            p_obj->p_pr_instance->IE    =  0x00;
            p_obj->p_pr_instance->FR3   =  0x00;
            p_obj->p_pr_instance->FR4   =  0x00;
            p_obj->p_pr_instance->CR    =  0x00;
            p_obj->p_pr_instance->OD    =  0x00;
            p_obj->p_pr_instance->PUP   =  0x00;
            p_obj->p_pr_instance->PDN   =  0x00;
            /* PR Clock Enable */
            TSB_CG_FSYSENA_IPENA14 = 1U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Enable */
            TSB_CG_FSYSENA_IPENA17 = 1U;
            break;
#endif  /* TMPM3HN_L */
#if defined(TMPM3HP)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Enable */
            TSB_CG_FSYSENA_IPENA00 = 1U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR3   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Enable */
            TSB_CG_FSYSENA_IPENA01 = 1U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Enable */
            TSB_CG_FSYSENA_IPENA02 = 1U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Enable */
            TSB_CG_FSYSENA_IPENA03 = 1U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Enable */
            TSB_CG_FSYSENA_IPENA04 = 1U;
            break;
        case GPIO_PORT_F:
            p_obj->p_pf_instance->DATA  =  0x00;
            p_obj->p_pf_instance->IE    =  0x00;
            p_obj->p_pf_instance->CR    =  0x00;
            p_obj->p_pf_instance->OD    =  0x00;
            p_obj->p_pf_instance->PUP   =  0x00;
            p_obj->p_pf_instance->PDN   =  0x00;
            /* PF Clock Enable */
            TSB_CG_FSYSENA_IPENA05 = 1U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->FR1   =  0x00;
            p_obj->p_pg_instance->FR2   =  0x00;
            p_obj->p_pg_instance->FR3   =  0x00;
            p_obj->p_pg_instance->FR4   =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Enable */
            TSB_CG_FSYSENA_IPENA06 = 1U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->FR1   =  0x00;
            p_obj->p_ph_instance->CR    =  0x00;
            p_obj->p_ph_instance->OD    =  0x00;
            p_obj->p_ph_instance->PUP   =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Enable */
            TSB_CG_FSYSENA_IPENA07 = 1U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Enable */
            TSB_CG_FSYSENA_IPENA08 = 1U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Enable */
            TSB_CG_FSYSENA_IPENA09 = 1U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Enable */
            TSB_CG_FSYSENA_IPENA10 = 1U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Enable */
            TSB_CG_FSYSENA_IPENA11 = 1U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->FR5   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Enable */
            TSB_CG_FSYSENA_IPENA12 = 1U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->FR2   =  0x00;
            p_obj->p_pp_instance->FR3   =  0x00;
            p_obj->p_pp_instance->FR4   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Enable */
            TSB_CG_FSYSENA_IPENA13 = 1U;
            break;
        case GPIO_PORT_R:
            p_obj->p_pr_instance->DATA  =  0x00;
            p_obj->p_pr_instance->IE    =  0x00;
            p_obj->p_pr_instance->FR3   =  0x00;
            p_obj->p_pr_instance->FR4   =  0x00;
            p_obj->p_pr_instance->CR    =  0x00;
            p_obj->p_pr_instance->OD    =  0x00;
            p_obj->p_pr_instance->PUP   =  0x00;
            p_obj->p_pr_instance->PDN   =  0x00;
            /* PR Clock Enable */
            TSB_CG_FSYSENA_IPENA14 = 1U;
            break;
        case GPIO_PORT_T:
            p_obj->p_pt_instance->DATA  =  0x00;
            p_obj->p_pt_instance->IE    =  0x00;
            p_obj->p_pt_instance->FR1   =  0x00;
            p_obj->p_pt_instance->FR2   =  0x00;
            p_obj->p_pt_instance->FR3   =  0x00;
            p_obj->p_pt_instance->CR    =  0x00;
            p_obj->p_pt_instance->OD    =  0x00;
            p_obj->p_pt_instance->PUP   =  0x00;
            p_obj->p_pt_instance->PDN   =  0x00;
            /* PT Clock Enable */
            TSB_CG_FSYSENA_IPENA15 = 1U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Enable */
            TSB_CG_FSYSENA_IPENA17 = 1U;
            break;
#endif  /* TMPM3HP */
#if defined(TMPM3HQ)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Enable */
            TSB_CG_FSYSENA_IPENA00 = 1U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR3   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Enable */
            TSB_CG_FSYSENA_IPENA01 = 1U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Enable */
            TSB_CG_FSYSENA_IPENA02 = 1U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Enable */
            TSB_CG_FSYSENA_IPENA03 = 1U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Enable */
            TSB_CG_FSYSENA_IPENA04 = 1U;
            break;
        case GPIO_PORT_F:
            p_obj->p_pf_instance->DATA  =  0x00;
            p_obj->p_pf_instance->IE    =  0x00;
            p_obj->p_pf_instance->CR    =  0x00;
            p_obj->p_pf_instance->OD    =  0x00;
            p_obj->p_pf_instance->PUP   =  0x00;
            p_obj->p_pf_instance->PDN   =  0x00;
            /* PF Clock Enable */
            TSB_CG_FSYSENA_IPENA05 = 1U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->FR1   =  0x00;
            p_obj->p_pg_instance->FR2   =  0x00;
            p_obj->p_pg_instance->FR3   =  0x00;
            p_obj->p_pg_instance->FR4   =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Enable */
            TSB_CG_FSYSENA_IPENA06 = 1U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->FR1   =  0x00;
            p_obj->p_ph_instance->CR    =  0x00;
            p_obj->p_ph_instance->OD    =  0x00;
            p_obj->p_ph_instance->PUP   =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Enable */
            TSB_CG_FSYSENA_IPENA07 = 1U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Enable */
            TSB_CG_FSYSENA_IPENA08 = 1U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Enable */
            TSB_CG_FSYSENA_IPENA09 = 1U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Enable */
            TSB_CG_FSYSENA_IPENA10 = 1U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Enable */
            TSB_CG_FSYSENA_IPENA11 = 1U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->FR5   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Enable */
            TSB_CG_FSYSENA_IPENA12 = 1U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->FR2   =  0x00;
            p_obj->p_pp_instance->FR3   =  0x00;
            p_obj->p_pp_instance->FR4   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Enable */
            TSB_CG_FSYSENA_IPENA13 = 1U;
            break;
        case GPIO_PORT_R:
            p_obj->p_pr_instance->DATA  =  0x00;
            p_obj->p_pr_instance->IE    =  0x00;
            p_obj->p_pr_instance->FR3   =  0x00;
            p_obj->p_pr_instance->FR4   =  0x00;
            p_obj->p_pr_instance->CR    =  0x00;
            p_obj->p_pr_instance->OD    =  0x00;
            p_obj->p_pr_instance->PUP   =  0x00;
            p_obj->p_pr_instance->PDN   =  0x00;
            /* PR Clock Enable */
            TSB_CG_FSYSENA_IPENA14 = 1U;
            break;
        case GPIO_PORT_T:
            p_obj->p_pt_instance->DATA  =  0x00;
         	p_obj->p_pt_instance->IE    =  0x00;
            p_obj->p_pt_instance->FR1   =  0x00;
            p_obj->p_pt_instance->FR2   =  0x00;
            p_obj->p_pt_instance->FR3   =  0x00;
            p_obj->p_pt_instance->FR4   =  0x00;
            p_obj->p_pt_instance->CR    =  0x00;
            p_obj->p_pt_instance->OD    =  0x00;
            p_obj->p_pt_instance->PUP   =  0x00;
            p_obj->p_pt_instance->PDN   =  0x00;
            /* PT Clock Enable */
            TSB_CG_FSYSENA_IPENA15 = 1U;
            break;
        case GPIO_PORT_U:
            p_obj->p_pu_instance->DATA  =  0x00;
            p_obj->p_pu_instance->IE    =  0x00;
            p_obj->p_pu_instance->CR    =  0x00;
            p_obj->p_pu_instance->OD    =  0x00;
            p_obj->p_pu_instance->PUP   =  0x00;
            p_obj->p_pu_instance->PDN   =  0x00;
            /* PU Clock Enable */
            TSB_CG_FSYSENA_IPENA16 = 1U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->FR1   =  0x00;
            p_obj->p_pv_instance->FR2   =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Enable */
            TSB_CG_FSYSENA_IPENA17 = 1U;
            break;
#endif  /* TMPM3HQ */
        default:
            result = TXZ_ERROR;
            return (result);
        }
    }

    return (result);
}

/*--------------------------------------------------*/
/*!
  * @fn     TXZ_Result gpio_deinit(gpio_t *p_obj, uint32_t group)
  * @brief     Release the GPIO object.
  * @param     p_obj :GPIO object.
  * @param     group  :GPIO Port Group.: Use @ref gpio_gr_t
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note      When p_obj is NULL, "Failure" is returned.
  * @attention This function is not available in interrupt.
  */
/*--------------------------------------------------*/
TXZ_Result gpio_deinit(gpio_t *p_obj, uint32_t group)
{
    TXZ_Result result = TXZ_SUCCESS;

    /* Check the NULL of address. */
    if ((void*)(p_obj) == (void*)0)
    {
        result = TXZ_ERROR;
    }
    else
    {
        /* Disable the selected GPIO peripheral  */
        switch (group)
        {
#if defined(TMPM3HL)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Disable */
            TSB_CG_FSYSENA_IPENA00 = 0U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Disable */
            TSB_CG_FSYSENA_IPENA01 = 0U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Disable */
            TSB_CG_FSYSENA_IPENA02 = 0U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Disable */
            TSB_CG_FSYSENA_IPENA03 = 0U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Disable */
            TSB_CG_FSYSENA_IPENA04 = 0U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Disable */
            TSB_CG_FSYSENA_IPENA06 = 0U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Disable */
            TSB_CG_FSYSENA_IPENA07 = 0U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Disable */
            TSB_CG_FSYSENA_IPENA08 = 0U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Disable */
            TSB_CG_FSYSENA_IPENA09 = 0U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Disable */
            TSB_CG_FSYSENA_IPENA10 = 0U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Disable */
            TSB_CG_FSYSENA_IPENA11 = 0U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->FR5   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Disable */
            TSB_CG_FSYSENA_IPENA12 = 0U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Disable */
            TSB_CG_FSYSENA_IPENA13 = 0U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Disable */
            TSB_CG_FSYSENA_IPENA17 = 0U;
            break;
#endif  /* TMPM3HL */
#if defined(TMPM3HM)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Disable */
            TSB_CG_FSYSENA_IPENA00 = 0U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR3   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Disable */
            TSB_CG_FSYSENA_IPENA01 = 0U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Disable */
            TSB_CG_FSYSENA_IPENA02 = 0U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Disable */
            TSB_CG_FSYSENA_IPENA03 = 0U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Disable */
            TSB_CG_FSYSENA_IPENA04 = 0U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Disable */
            TSB_CG_FSYSENA_IPENA06 = 0U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Disable */
            TSB_CG_FSYSENA_IPENA07 = 0U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Disable */
            TSB_CG_FSYSENA_IPENA08 = 0U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Disable */
            TSB_CG_FSYSENA_IPENA09 = 0U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Disable */
            TSB_CG_FSYSENA_IPENA10 = 0U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Disable */
            TSB_CG_FSYSENA_IPENA11 = 0U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Disable */
            TSB_CG_FSYSENA_IPENA12 = 0U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->FR2   =  0x00;
            p_obj->p_pp_instance->FR3   =  0x00;
            p_obj->p_pp_instance->FR4   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Disable */
            TSB_CG_FSYSENA_IPENA13 = 0U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Disable */
            TSB_CG_FSYSENA_IPENA17 = 0U;
            break;
#endif  /* TMPM3HM */
#if defined(TMPM3HN)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Disable */
            TSB_CG_FSYSENA_IPENA00 = 0U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR3   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Disable */
            TSB_CG_FSYSENA_IPENA01 = 0U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Disable */
            TSB_CG_FSYSENA_IPENA02 = 0U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Disable */
            TSB_CG_FSYSENA_IPENA03 = 0U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Disable */
            TSB_CG_FSYSENA_IPENA04 = 0U;
            break;
        case GPIO_PORT_F:
            p_obj->p_pf_instance->DATA  =  0x00;
            p_obj->p_pf_instance->IE    =  0x00;
            p_obj->p_pf_instance->CR    =  0x00;
            p_obj->p_pf_instance->OD    =  0x00;
            p_obj->p_pf_instance->PUP   =  0x00;
            p_obj->p_pf_instance->PDN   =  0x00;
            /* PF Clock Disable */
            TSB_CG_FSYSENA_IPENA05 = 0U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Disable */
            TSB_CG_FSYSENA_IPENA06 = 0U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Disable */
            TSB_CG_FSYSENA_IPENA07 = 0U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Disable */
            TSB_CG_FSYSENA_IPENA08 = 0U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Disable */
            TSB_CG_FSYSENA_IPENA09 = 0U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Disable */
            TSB_CG_FSYSENA_IPENA10 = 0U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Disable */
            TSB_CG_FSYSENA_IPENA11 = 0U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->FR5   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Disable */
            TSB_CG_FSYSENA_IPENA12 = 0U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->FR2   =  0x00;
            p_obj->p_pp_instance->FR3   =  0x00;
            p_obj->p_pp_instance->FR4   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Disable */
            TSB_CG_FSYSENA_IPENA13 = 0U;
            break;
        case GPIO_PORT_R:
            p_obj->p_pr_instance->DATA  =  0x00;
            p_obj->p_pr_instance->IE    =  0x00;
            p_obj->p_pr_instance->FR3   =  0x00;
            p_obj->p_pr_instance->FR4   =  0x00;
            p_obj->p_pr_instance->CR    =  0x00;
            p_obj->p_pr_instance->OD    =  0x00;
            p_obj->p_pr_instance->PUP   =  0x00;
            p_obj->p_pr_instance->PDN   =  0x00;
            /* PR Clock Disable */
            TSB_CG_FSYSENA_IPENA14 = 0U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Disable */
            TSB_CG_FSYSENA_IPENA17 = 0U;
            break;
#endif  /* TMPM3HN */
#if defined(TMPM3HN_L)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Disable */
            TSB_CG_FSYSENA_IPENA00 = 0U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR3   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Disable */
            TSB_CG_FSYSENA_IPENA01 = 0U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Disable */
            TSB_CG_FSYSENA_IPENA02 = 0U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Disable */
            TSB_CG_FSYSENA_IPENA03 = 0U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Disable */
            TSB_CG_FSYSENA_IPENA04 = 0U;
            break;
        case GPIO_PORT_F:
            p_obj->p_pf_instance->DATA  =  0x00;
            p_obj->p_pf_instance->IE    =  0x00;
            p_obj->p_pf_instance->CR    =  0x00;
            p_obj->p_pf_instance->OD    =  0x00;
            p_obj->p_pf_instance->PUP   =  0x00;
            p_obj->p_pf_instance->PDN   =  0x00;
            /* PF Clock Disable */
            TSB_CG_FSYSENA_IPENA05 = 0U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Disable */
            TSB_CG_FSYSENA_IPENA06 = 0U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Disable */
            TSB_CG_FSYSENA_IPENA07 = 0U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Disable */
            TSB_CG_FSYSENA_IPENA08 = 0U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Disable */
            TSB_CG_FSYSENA_IPENA09 = 0U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Disable */
            TSB_CG_FSYSENA_IPENA10 = 0U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Disable */
            TSB_CG_FSYSENA_IPENA11 = 0U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->FR5   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Disable */
            TSB_CG_FSYSENA_IPENA12 = 0U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->FR2   =  0x00;
            p_obj->p_pp_instance->FR3   =  0x00;
            p_obj->p_pp_instance->FR4   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Disable */
            TSB_CG_FSYSENA_IPENA13 = 0U;
            break;
        case GPIO_PORT_R:
            p_obj->p_pr_instance->DATA  =  0x00;
            p_obj->p_pr_instance->IE    =  0x00;
            p_obj->p_pr_instance->FR3   =  0x00;
            p_obj->p_pr_instance->FR4   =  0x00;
            p_obj->p_pr_instance->CR    =  0x00;
            p_obj->p_pr_instance->OD    =  0x00;
            p_obj->p_pr_instance->PUP   =  0x00;
            p_obj->p_pr_instance->PDN   =  0x00;
            /* PR Clock Disable */
            TSB_CG_FSYSENA_IPENA14 = 0U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Disable */
            TSB_CG_FSYSENA_IPENA17 = 0U;
            break;
#endif  /* TMPM3HN_L */
#if defined(TMPM3HP)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Disable */
            TSB_CG_FSYSENA_IPENA00 = 0U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR3   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Disable */
            TSB_CG_FSYSENA_IPENA01 = 0U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Disable */
            TSB_CG_FSYSENA_IPENA02 = 0U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Disable */
            TSB_CG_FSYSENA_IPENA03 = 0U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Disable */
            TSB_CG_FSYSENA_IPENA04 = 0U;
            break;
        case GPIO_PORT_F:
            p_obj->p_pf_instance->DATA  =  0x00;
            p_obj->p_pf_instance->IE    =  0x00;
            p_obj->p_pf_instance->CR    =  0x00;
            p_obj->p_pf_instance->OD    =  0x00;
            p_obj->p_pf_instance->PUP   =  0x00;
            p_obj->p_pf_instance->PDN   =  0x00;
            /* PF Clock Disable */
            TSB_CG_FSYSENA_IPENA05 = 0U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->FR1   =  0x00;
            p_obj->p_pg_instance->FR2   =  0x00;
            p_obj->p_pg_instance->FR3   =  0x00;
            p_obj->p_pg_instance->FR4   =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Disable */
            TSB_CG_FSYSENA_IPENA06 = 0U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->FR1   =  0x00;
            p_obj->p_ph_instance->CR    =  0x00;
            p_obj->p_ph_instance->OD    =  0x00;
            p_obj->p_ph_instance->PUP   =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Disable */
            TSB_CG_FSYSENA_IPENA07 = 0U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Disable */
            TSB_CG_FSYSENA_IPENA08 = 0U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Disable */
            TSB_CG_FSYSENA_IPENA09 = 0U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Disable */
            TSB_CG_FSYSENA_IPENA10 = 0U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Disable */
            TSB_CG_FSYSENA_IPENA11 = 0U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->FR5   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Disable */
            TSB_CG_FSYSENA_IPENA12 = 0U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->FR2   =  0x00;
            p_obj->p_pp_instance->FR3   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Disable */
            TSB_CG_FSYSENA_IPENA13 = 0U;
            break;
        case GPIO_PORT_R:
            p_obj->p_pr_instance->DATA  =  0x00;
            p_obj->p_pr_instance->IE    =  0x00;
            p_obj->p_pr_instance->FR3   =  0x00;
            p_obj->p_pr_instance->FR4   =  0x00;
            p_obj->p_pr_instance->CR    =  0x00;
            p_obj->p_pr_instance->OD    =  0x00;
            p_obj->p_pr_instance->PUP   =  0x00;
            p_obj->p_pr_instance->PDN   =  0x00;
            /* PR Clock Disable */
            TSB_CG_FSYSENA_IPENA14 = 0U;
            break;
        case GPIO_PORT_T:
            p_obj->p_pt_instance->DATA  =  0x00;
            p_obj->p_pt_instance->IE    =  0x00;
            p_obj->p_pt_instance->FR1   =  0x00;
            p_obj->p_pt_instance->FR2   =  0x00;
            p_obj->p_pt_instance->FR3   =  0x00;
            p_obj->p_pt_instance->CR    =  0x00;
            p_obj->p_pt_instance->OD    =  0x00;
            p_obj->p_pt_instance->PUP   =  0x00;
            p_obj->p_pt_instance->PDN   =  0x00;
            /* PT Clock Disable */
            TSB_CG_FSYSENA_IPENA15 = 0U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Disable */
            TSB_CG_FSYSENA_IPENA17 = 0U;
            break;
#endif  /* TMPM3HP */
#if defined(TMPM3HQ)
        case GPIO_PORT_A:
            p_obj->p_pa_instance->DATA  =  0x00;
            p_obj->p_pa_instance->IE    =  0x00;
            p_obj->p_pa_instance->FR1   =  0x00;
            p_obj->p_pa_instance->FR2   =  0x00;
            p_obj->p_pa_instance->FR3   =  0x00;
            p_obj->p_pa_instance->FR4   =  0x00;
            p_obj->p_pa_instance->FR5   =  0x00;
            p_obj->p_pa_instance->FR6   =  0x00;
            p_obj->p_pa_instance->CR    =  0x00;
            p_obj->p_pa_instance->OD    =  0x00;
            p_obj->p_pa_instance->PUP   =  0x00;
            p_obj->p_pa_instance->PDN   =  0x00;
            /* PA Clock Disable */
            TSB_CG_FSYSENA_IPENA00 = 0U;
            break;
        case GPIO_PORT_B:
            p_obj->p_pb_instance->DATA  =  0x00;
            p_obj->p_pb_instance->IE    =  0x00;
            p_obj->p_pb_instance->FR1   =  0x00;
            p_obj->p_pb_instance->FR2   =  0x00;
            p_obj->p_pb_instance->FR3   =  0x00;
            p_obj->p_pb_instance->FR4   =  0x00;
            p_obj->p_pb_instance->FR5   =  0x00;
            p_obj->p_pb_instance->FR6   =  0x00;
            p_obj->p_pb_instance->CR    =  0x00;
            p_obj->p_pb_instance->OD    =  0x00;
            p_obj->p_pb_instance->PUP   =  0x00;
            p_obj->p_pb_instance->PDN   =  0x00;
            /* PB Clock Disable */
            TSB_CG_FSYSENA_IPENA01 = 0U;
            break;
        case GPIO_PORT_C:
            p_obj->p_pc_instance->DATA  =  0x00;
            p_obj->p_pc_instance->IE    =  0x00;
            p_obj->p_pc_instance->FR1   =  0x00;
            p_obj->p_pc_instance->FR2   =  0x00;
            p_obj->p_pc_instance->FR3   =  0x00;
            p_obj->p_pc_instance->FR4   =  0x00;
            p_obj->p_pc_instance->FR5   =  0x00;
            p_obj->p_pc_instance->CR    =  0x00;
            p_obj->p_pc_instance->OD    =  0x00;
            p_obj->p_pc_instance->PUP   =  0x00;
            p_obj->p_pc_instance->PDN   =  0x00;
            /* PC Clock Disable */
            TSB_CG_FSYSENA_IPENA02 = 0U;
            break;
        case GPIO_PORT_D:
            p_obj->p_pd_instance->DATA  =  0x00;
            p_obj->p_pd_instance->IE    =  0x00;
            p_obj->p_pd_instance->CR    =  0x00;
            p_obj->p_pd_instance->OD    =  0x00;
            p_obj->p_pd_instance->PUP   =  0x00;
            p_obj->p_pd_instance->PDN   =  0x00;
            /* PD Clock Disable */
            TSB_CG_FSYSENA_IPENA03 = 0U;
            break;
        case GPIO_PORT_E:
            p_obj->p_pe_instance->DATA  =  0x00;
            p_obj->p_pe_instance->IE    =  0x00;
            p_obj->p_pe_instance->CR    =  0x00;
            p_obj->p_pe_instance->OD    =  0x00;
            p_obj->p_pe_instance->PUP   =  0x00;
            p_obj->p_pe_instance->PDN   =  0x00;
            /* PE Clock Disable */
            TSB_CG_FSYSENA_IPENA04 = 0U;
            break;
        case GPIO_PORT_F:
            p_obj->p_pf_instance->DATA  =  0x00;
            p_obj->p_pf_instance->IE    =  0x00;
            p_obj->p_pf_instance->CR    =  0x00;
            p_obj->p_pf_instance->OD    =  0x00;
            p_obj->p_pf_instance->PUP   =  0x00;
            p_obj->p_pf_instance->PDN   =  0x00;
            /* PF Clock Disable */
            TSB_CG_FSYSENA_IPENA05 = 0U;
            break;
        case GPIO_PORT_G:
            p_obj->p_pg_instance->DATA  =  0x00;
            p_obj->p_pg_instance->IE    =  0x00;
            p_obj->p_pg_instance->FR1   =  0x00;
            p_obj->p_pg_instance->FR2   =  0x00;
            p_obj->p_pg_instance->FR3   =  0x00;
            p_obj->p_pg_instance->FR4   =  0x00;
            p_obj->p_pg_instance->CR    =  0x00;
            p_obj->p_pg_instance->OD    =  0x00;
            p_obj->p_pg_instance->PUP   =  0x00;
            p_obj->p_pg_instance->PDN   =  0x00;
            /* PG Clock Disable */
            TSB_CG_FSYSENA_IPENA06 = 0U;
            break;
        case GPIO_PORT_H:
            p_obj->p_ph_instance->DATA  =  0x00;
            p_obj->p_ph_instance->IE    =  0x00;
            p_obj->p_ph_instance->FR1   =  0x00;
            p_obj->p_ph_instance->CR    =  0x00;
            p_obj->p_ph_instance->OD    =  0x00;
            p_obj->p_ph_instance->PUP   =  0x00;
            p_obj->p_ph_instance->PDN   =  0x00;
            /* PH Clock Disable */
            TSB_CG_FSYSENA_IPENA07 = 0U;
            break;
        case GPIO_PORT_J:
            p_obj->p_pj_instance->DATA  =  0x00;
            p_obj->p_pj_instance->IE    =  0x00;
            p_obj->p_pj_instance->FR1   =  0x00;
            p_obj->p_pj_instance->FR2   =  0x00;
            p_obj->p_pj_instance->FR3   =  0x00;
            p_obj->p_pj_instance->FR4   =  0x00;
            p_obj->p_pj_instance->FR5   =  0x00;
            p_obj->p_pj_instance->CR    =  0x00;
            p_obj->p_pj_instance->OD    =  0x00;
            p_obj->p_pj_instance->PUP   =  0x00;
            p_obj->p_pj_instance->PDN   =  0x00;
            /* PJ Clock Disable */
            TSB_CG_FSYSENA_IPENA08 = 0U;
            break;
        case GPIO_PORT_K:
            p_obj->p_pk_instance->DATA  =  0x00;
            p_obj->p_pk_instance->IE    =  0x00;
            p_obj->p_pk_instance->FR1   =  0x00;
            p_obj->p_pk_instance->FR2   =  0x00;
            p_obj->p_pk_instance->FR3   =  0x00;
            p_obj->p_pk_instance->FR4   =  0x00;
            p_obj->p_pk_instance->FR5   =  0x00;
            p_obj->p_pk_instance->CR    =  0x00;
            p_obj->p_pk_instance->OD    =  0x00;
            p_obj->p_pk_instance->PUP   =  0x00;
            p_obj->p_pk_instance->PDN   =  0x00;
            /* PK Clock Disable */
            TSB_CG_FSYSENA_IPENA09 = 0U;
            break;
        case GPIO_PORT_L:
            p_obj->p_pl_instance->DATA  =  0x00;
            p_obj->p_pl_instance->IE    =  0x1B;
            p_obj->p_pl_instance->FR1   =  0x00;
            p_obj->p_pl_instance->FR2   =  0x00;
            p_obj->p_pl_instance->FR3   =  0x00;
            p_obj->p_pl_instance->FR4   =  0x00;
            p_obj->p_pl_instance->FR5   =  0x1F;
            p_obj->p_pl_instance->CR    =  0x14;
            p_obj->p_pl_instance->OD    =  0x00;
            p_obj->p_pl_instance->PUP   =  0x13;
            p_obj->p_pl_instance->PDN   =  0x08;
            /* PL Clock Disable */
            TSB_CG_FSYSENA_IPENA10 = 0U;
            break;
        case GPIO_PORT_M:
            p_obj->p_pm_instance->DATA  =  0x00;
            p_obj->p_pm_instance->IE    =  0x00;
            p_obj->p_pm_instance->FR1   =  0x00;
            p_obj->p_pm_instance->FR2   =  0x00;
            p_obj->p_pm_instance->FR3   =  0x00;
            p_obj->p_pm_instance->FR4   =  0x00;
            p_obj->p_pm_instance->FR5   =  0x00;
            p_obj->p_pm_instance->FR6   =  0x00;
            p_obj->p_pm_instance->CR    =  0x00;
            p_obj->p_pm_instance->OD    =  0x00;
            p_obj->p_pm_instance->PUP   =  0x00;
            p_obj->p_pm_instance->PDN   =  0x00;
            /* PM Clock Disable */
            TSB_CG_FSYSENA_IPENA11 = 0U;
            break;
        case GPIO_PORT_N:
            p_obj->p_pn_instance->DATA  =  0x00;
            p_obj->p_pn_instance->IE    =  0x00;
            p_obj->p_pn_instance->FR1   =  0x00;
            p_obj->p_pn_instance->FR2   =  0x00;
            p_obj->p_pn_instance->FR3   =  0x00;
            p_obj->p_pn_instance->FR4   =  0x00;
            p_obj->p_pn_instance->FR5   =  0x00;
            p_obj->p_pn_instance->CR    =  0x00;
            p_obj->p_pn_instance->OD    =  0x00;
            p_obj->p_pn_instance->PUP   =  0x00;
            p_obj->p_pn_instance->PDN   =  0x00;
            /* PN Clock Disable */
            TSB_CG_FSYSENA_IPENA12 = 0U;
            break;
        case GPIO_PORT_P:
            p_obj->p_pp_instance->DATA  =  0x00;
            p_obj->p_pp_instance->IE    =  0x00;
            p_obj->p_pp_instance->FR1   =  0x00;
            p_obj->p_pp_instance->FR2   =  0x00;
            p_obj->p_pp_instance->FR3   =  0x00;
            p_obj->p_pp_instance->FR4   =  0x00;
            p_obj->p_pp_instance->CR    =  0x00;
            p_obj->p_pp_instance->OD    =  0x00;
            p_obj->p_pp_instance->PUP   =  0x00;
            p_obj->p_pp_instance->PDN   =  0x00;
            /* PP Clock Disable */
            TSB_CG_FSYSENA_IPENA13 = 0U;
            break;
        case GPIO_PORT_R:
            p_obj->p_pr_instance->DATA  =  0x00;
            p_obj->p_pr_instance->IE    =  0x00;
            p_obj->p_pr_instance->FR3   =  0x00;
            p_obj->p_pr_instance->FR4   =  0x00;
            p_obj->p_pr_instance->CR    =  0x00;
            p_obj->p_pr_instance->OD    =  0x00;
            p_obj->p_pr_instance->PUP   =  0x00;
            p_obj->p_pr_instance->PDN   =  0x00;
            /* PR Clock Disable */
            TSB_CG_FSYSENA_IPENA14 = 0U;
            break;
        case GPIO_PORT_T:
            p_obj->p_pt_instance->DATA  =  0x00;
            p_obj->p_pt_instance->IE    =  0x00;
            p_obj->p_pt_instance->FR1   =  0x00;
            p_obj->p_pt_instance->FR2   =  0x00;
            p_obj->p_pt_instance->FR3   =  0x00;
            p_obj->p_pt_instance->FR4   =  0x00;
            p_obj->p_pt_instance->CR    =  0x00;
            p_obj->p_pt_instance->OD    =  0x00;
            p_obj->p_pt_instance->PUP   =  0x00;
            p_obj->p_pt_instance->PDN   =  0x00;
            /* PT Clock Disable */
            TSB_CG_FSYSENA_IPENA15 = 0U;
            break;
        case GPIO_PORT_U:
            p_obj->p_pu_instance->DATA  =  0x00;
            p_obj->p_pu_instance->IE    =  0x00;
            p_obj->p_pu_instance->CR    =  0x00;
            p_obj->p_pu_instance->OD    =  0x00;
            p_obj->p_pu_instance->PUP   =  0x00;
            p_obj->p_pu_instance->PDN   =  0x00;
            /* PU Clock Disable */
            TSB_CG_FSYSENA_IPENA16 = 0U;
            break;
        case GPIO_PORT_V:
            p_obj->p_pv_instance->DATA  =  0x00;
            p_obj->p_pv_instance->IE    =  0x00;
            p_obj->p_pv_instance->FR1   =  0x00;
            p_obj->p_pv_instance->FR2   =  0x00;
            p_obj->p_pv_instance->CR    =  0x00;
            p_obj->p_pv_instance->OD    =  0x00;
            p_obj->p_pv_instance->PUP   =  0x00;
            p_obj->p_pv_instance->PDN   =  0x00;
            /* PV Clock Disable */
            TSB_CG_FSYSENA_IPENA17 = 0U;
            break;
#endif  /* TMPM3HQ */
        default:
            result = TXZ_ERROR;
            return (result);
        }
    }

    return (result);
}

/*--------------------------------------------------*/
/*!
  * @fn     TXZ_Result gpio_write_mode(gpio_t *p_obj, uint32_t group, uint32_t mode, uint32_t val)
  * @brief  Port Mode Write
  * @param[in] p_obj :GPIO object.
  * @param[in] group :GPIO Port Group. : Use @ref gpio_gr_t
  * @param[in] mode  :GPIO Port Mode. : Use @ref gpio_num_t
  * @param[in] val   :value
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   When p_obj is NULL, no processing.
  */
/*--------------------------------------------------*/
TXZ_Result gpio_write_mode(gpio_t *p_obj, uint32_t group, uint32_t mode, uint32_t val)
{
    TXZ_Result result = TXZ_SUCCESS;
    int32_t i;
    int32_t param_result = PARAM_NG;

    /* Check the parameters, the NULL of address */
    for (i = GPIO_PORT_0; i < GPIO_PORT_Max; i++)
    {
        param_result = check_param_pin_exist(p_obj, group, i, mode);
        if(param_result == PARAM_OK)
        { 
            break;
        }
        else
        {
             /* No Process */
        }
    }
    if (((void*)(p_obj) == (void*)0) || (param_result == PARAM_NG))
    {
        result = TXZ_ERROR;
    }
    else
    {
        switch (group)
        {
#if defined(TMPM3HL)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pa_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pa_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pa_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pa_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pa_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pa_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pa_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pa_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pa_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pa_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pa_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pa_instance->PDN  = val;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pb_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pb_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pb_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pb_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pb_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pb_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pb_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pb_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pb_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pb_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pb_instance->PDN  = val;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pc_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pc_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pc_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pc_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pc_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pc_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pc_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pc_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pc_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pc_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pc_instance->PDN  = val;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pd_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pd_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pd_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pd_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pd_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pd_instance->PDN  = val;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pe_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pe_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pe_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pe_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pe_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pe_instance->PDN  = val;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pg_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pg_instance->IE  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pg_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pg_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pg_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pg_instance->PDN  = val;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_ph_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_ph_instance->IE   = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_ph_instance->PDN  = val;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pj_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pj_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pj_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pj_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pj_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pj_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pj_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pj_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pj_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pj_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pj_instance->PDN  = val;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pk_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pk_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pk_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pk_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pk_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pk_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pk_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pk_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pk_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pk_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pk_instance->PDN  = val;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pl_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pl_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pl_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pl_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pl_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pl_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pl_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pl_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pl_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pl_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pl_instance->PDN  = val;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pm_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pm_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pm_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pm_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pm_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pm_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pm_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pm_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pm_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pm_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pm_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pm_instance->PDN  = val;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pn_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pn_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pn_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pn_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pn_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pn_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pn_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pn_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pn_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pn_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pn_instance->PDN  = val;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pp_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pp_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pp_instance->FR1  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pp_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pp_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pp_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pp_instance->PDN  = val;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pv_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pv_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pv_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pv_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pv_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pv_instance->PDN  = val;}
            break;
#endif  /* TMPM3HL */
#if defined(TMPM3HM)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pa_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pa_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pa_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pa_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pa_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pa_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pa_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pa_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pa_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pa_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pa_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pa_instance->PDN  = val;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pb_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pb_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pb_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pb_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pb_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pb_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pb_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pb_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pb_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pb_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pb_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pb_instance->PDN  = val;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pc_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pc_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pc_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pc_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pc_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pc_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pc_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pc_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pc_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pc_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pc_instance->PDN  = val;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pd_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pd_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pd_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pd_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pd_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pd_instance->PDN  = val;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pe_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pe_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pe_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pe_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pe_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pe_instance->PDN  = val;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pg_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pg_instance->IE  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pg_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pg_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pg_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pg_instance->PDN  = val;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_ph_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_ph_instance->IE   = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_ph_instance->PDN  = val;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pj_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pj_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pj_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pj_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pj_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pj_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pj_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pj_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pj_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pj_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pj_instance->PDN  = val;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pk_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pk_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pk_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pk_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pk_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pk_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pk_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pk_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pk_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pk_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pk_instance->PDN  = val;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pl_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pl_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pl_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pl_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pl_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pl_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pl_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pl_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pl_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pl_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pl_instance->PDN  = val;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pm_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pm_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pm_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pm_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pm_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pm_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pm_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pm_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pm_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pm_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pm_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pm_instance->PDN  = val;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pn_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pn_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pn_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pn_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pn_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pn_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pn_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pn_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pn_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pn_instance->PDN  = val;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pp_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pp_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pp_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pp_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pp_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pp_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pp_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pp_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pp_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pp_instance->PDN  = val;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pv_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pv_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pv_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pv_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pv_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pv_instance->PDN  = val;}
            break;
#endif  /* TMPM3HM */
#if defined(TMPM3HN)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pa_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pa_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pa_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pa_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pa_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pa_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pa_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pa_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pa_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pa_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pa_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pa_instance->PDN  = val;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pb_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pb_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pb_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pb_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pb_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pb_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pb_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pb_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pb_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pb_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pb_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pb_instance->PDN  = val;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pc_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pc_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pc_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pc_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pc_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pc_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pc_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pc_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pc_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pc_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pc_instance->PDN  = val;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pd_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pd_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pd_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pd_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pd_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pd_instance->PDN  = val;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pe_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pe_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pe_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pe_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pe_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pe_instance->PDN  = val;}
            break;
        case GPIO_PORT_F:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pf_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pf_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pf_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pf_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pf_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pf_instance->PDN  = val;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pg_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pg_instance->IE  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pg_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pg_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pg_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pg_instance->PDN  = val;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_ph_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_ph_instance->IE   = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_ph_instance->PDN  = val;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pj_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pj_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pj_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pj_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pj_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pj_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pj_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pj_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pj_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pj_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pj_instance->PDN  = val;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pk_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pk_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pk_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pk_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pk_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pk_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pk_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pk_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pk_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pk_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pk_instance->PDN  = val;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pl_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pl_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pl_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pl_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pl_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pl_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pl_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pl_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pl_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pl_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pl_instance->PDN  = val;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pm_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pm_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pm_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pm_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pm_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pm_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pm_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pm_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pm_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pm_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pm_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pm_instance->PDN  = val;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pn_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pn_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pn_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pn_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pn_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pn_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pn_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pn_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pn_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pn_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pn_instance->PDN  = val;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pp_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pp_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pp_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pp_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pp_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pp_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pp_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pp_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pp_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pp_instance->PDN  = val;}
            break;
        case GPIO_PORT_R:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pr_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pr_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pr_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pr_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pr_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pr_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pr_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pr_instance->PDN  = val;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pv_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pv_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pv_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pv_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pv_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pv_instance->PDN  = val;}
            break;
#endif  /* TMPM3HN */
#if defined(TMPM3HN_L)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pa_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pa_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pa_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pa_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pa_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pa_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pa_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pa_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pa_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pa_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pa_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pa_instance->PDN  = val;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pb_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pb_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pb_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pb_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pb_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pb_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pb_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pb_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pb_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pb_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pb_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pb_instance->PDN  = val;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pc_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pc_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pc_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pc_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pc_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pc_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pc_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pc_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pc_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pc_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pc_instance->PDN  = val;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pd_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pd_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pd_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pd_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pd_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pd_instance->PDN  = val;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pe_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pe_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pe_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pe_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pe_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pe_instance->PDN  = val;}
            break;
        case GPIO_PORT_F:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pf_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pf_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pf_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pf_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pf_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pf_instance->PDN  = val;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pg_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pg_instance->IE  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pg_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pg_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pg_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pg_instance->PDN  = val;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_ph_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_ph_instance->IE   = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_ph_instance->PDN  = val;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pj_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pj_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pj_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pj_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pj_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pj_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pj_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pj_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pj_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pj_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pj_instance->PDN  = val;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pk_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pk_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pk_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pk_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pk_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pk_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pk_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pk_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pk_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pk_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pk_instance->PDN  = val;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pl_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pl_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pl_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pl_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pl_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pl_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pl_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pl_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pl_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pl_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pl_instance->PDN  = val;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pm_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pm_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pm_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pm_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pm_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pm_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pm_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pm_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pm_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pm_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pm_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pm_instance->PDN  = val;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pn_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pn_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pn_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pn_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pn_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pn_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pn_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pn_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pn_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pn_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pn_instance->PDN  = val;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pp_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pp_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pp_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pp_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pp_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pp_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pp_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pp_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pp_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pp_instance->PDN  = val;}
            break;
        case GPIO_PORT_R:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pr_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pr_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pr_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pr_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pr_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pr_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pr_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pr_instance->PDN  = val;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pv_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pv_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pv_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pv_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pv_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pv_instance->PDN  = val;}
            break;
#endif  /* TMPM3HN_L */
#if defined(TMPM3HP)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pa_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pa_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pa_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pa_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pa_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pa_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pa_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pa_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pa_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pa_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pa_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pa_instance->PDN  = val;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pb_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pb_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pb_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pb_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pb_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pb_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pb_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pb_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pb_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pb_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pb_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pb_instance->PDN  = val;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pc_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pc_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pc_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pc_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pc_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pc_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pc_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pc_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pc_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pc_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pc_instance->PDN  = val;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pd_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pd_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pd_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pd_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pd_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pd_instance->PDN  = val;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pe_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pe_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pe_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pe_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pe_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pe_instance->PDN  = val;}
            break;
        case GPIO_PORT_F:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pf_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pe_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pf_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pf_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pf_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pf_instance->PDN  = val;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pg_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pg_instance->IE  = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pg_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pg_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pg_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pg_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pg_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pg_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pg_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pg_instance->PDN  = val;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_ph_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_ph_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_ph_instance->FR1  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_ph_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_ph_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_ph_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_ph_instance->PDN  = val;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pj_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pj_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pj_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pj_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pj_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pj_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pj_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pj_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pj_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pj_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pj_instance->PDN  = val;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pk_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pk_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pk_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pk_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pk_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pk_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pk_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pk_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pk_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pk_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pk_instance->PDN  = val;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pl_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pl_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pl_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pl_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pl_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pl_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pl_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pl_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pl_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pl_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pl_instance->PDN  = val;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pm_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pm_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pm_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pm_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pm_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pm_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pm_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pm_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pm_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pm_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pm_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pm_instance->PDN  = val;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pn_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pn_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pn_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pn_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pn_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pn_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pn_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pn_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pn_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pn_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pn_instance->PDN  = val;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pp_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pp_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pp_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pp_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pp_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pp_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pp_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pp_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pp_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pp_instance->PDN  = val;}
            break;
        case GPIO_PORT_R:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pr_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pr_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pr_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pr_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pr_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pr_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pr_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pr_instance->PDN  = val;}
            break;
        case GPIO_PORT_T:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pt_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pt_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pt_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pt_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pt_instance->FR3  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pt_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pt_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pt_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pt_instance->PDN  = val;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pv_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pv_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pv_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pv_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pv_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pv_instance->PDN  = val;}
            break;
#endif  /* TMPM3HP */
#if defined(TMPM3HQ)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pa_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pa_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pa_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pa_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pa_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pa_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pa_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pa_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pa_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pa_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pa_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pa_instance->PDN  = val;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pb_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pb_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pb_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pb_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pb_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pb_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pb_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pb_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pb_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pb_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pb_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pb_instance->PDN  = val;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pc_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pc_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pc_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pc_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pc_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pc_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pc_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pc_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pc_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pc_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pc_instance->PDN  = val;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pd_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pd_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pd_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pd_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pd_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pd_instance->PDN  = val;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pe_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pe_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pe_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pe_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pe_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pe_instance->PDN  = val;}
            break;
        case GPIO_PORT_F:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pf_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pf_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pf_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pf_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pf_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pf_instance->PDN  = val;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pg_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pg_instance->IE  = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pg_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pg_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pg_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pg_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pg_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pg_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pg_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pg_instance->PDN  = val;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_ph_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_ph_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_ph_instance->FR1  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_ph_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_ph_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_ph_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_ph_instance->PDN  = val;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pj_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pj_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pj_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pj_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pj_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pj_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pj_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pj_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pj_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pj_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pj_instance->PDN  = val;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pk_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pk_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pk_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pk_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pk_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pk_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pk_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pk_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pk_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pk_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pk_instance->PDN  = val;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pl_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pl_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pl_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pl_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pl_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pl_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pl_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pl_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pl_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pl_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pl_instance->PDN  = val;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pm_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pm_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pm_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pm_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pm_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pm_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pm_instance->FR5  = val;}
            else if(mode == GPIO_Mode_FR6) {p_obj->p_pm_instance->FR6  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pm_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pm_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pm_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pm_instance->PDN  = val;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pn_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pn_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pn_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pn_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pn_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pn_instance->FR4  = val;}
            else if(mode == GPIO_Mode_FR5) {p_obj->p_pn_instance->FR5  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pn_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pn_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pn_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pn_instance->PDN  = val;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pp_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pp_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pp_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pp_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pp_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pp_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pp_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pp_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pp_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pp_instance->PDN  = val;}
            break;
        case GPIO_PORT_R:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pr_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pr_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pr_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pr_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pr_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pr_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pr_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pr_instance->PDN  = val;}
            break;
        case GPIO_PORT_T:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pt_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pt_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pt_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pt_instance->FR2  = val;}
            else if(mode == GPIO_Mode_FR3) {p_obj->p_pt_instance->FR3  = val;}
            else if(mode == GPIO_Mode_FR4) {p_obj->p_pt_instance->FR4  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pt_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pt_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pt_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pt_instance->PDN  = val;}
            break;
        case GPIO_PORT_U:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pu_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pu_instance->IE   = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pu_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pu_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pu_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pu_instance->PDN  = val;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {p_obj->p_pv_instance->DATA = val;}
            else if(mode == GPIO_Mode_IE)  {p_obj->p_pv_instance->IE   = val;}
            else if(mode == GPIO_Mode_FR1) {p_obj->p_pv_instance->FR1  = val;}
            else if(mode == GPIO_Mode_FR2) {p_obj->p_pv_instance->FR2  = val;}
            else if(mode == GPIO_Mode_CR)  {p_obj->p_pv_instance->CR   = val;}
            else if(mode == GPIO_Mode_OD)  {p_obj->p_pv_instance->OD   = val;}
            else if(mode == GPIO_Mode_PUP) {p_obj->p_pv_instance->PUP  = val;}
            else if(mode == GPIO_Mode_PDN) {p_obj->p_pv_instance->PDN  = val;}
            break;
#endif  /* TMPM3HQ */
        default:
            result = TXZ_ERROR;
            return (result);
        }
    }

    return (result);
}

/*--------------------------------------------------*/
/*!
  * @fn     TXZ_Result gpio_read_mode(gpio_t *p_obj, uint32_t group, uint32_t mode, uint32_t *val)
  * @brief  Port Mode Read
  * @param[in]  p_obj :GPIO object.
  * @param[in]  group :GPIO Port Group.  : Use @ref gpio_gr_t
  * @param[in]  mode  :GPIO Port Mode. : Use @ref gpio_num_t
  * @param[out] val   :Store of value
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   When p_obj is NULL, no processing.
  */
/*--------------------------------------------------*/
TXZ_Result gpio_read_mode(gpio_t *p_obj, uint32_t group, uint32_t mode, uint32_t *val)
{
    TXZ_Result result = TXZ_SUCCESS;
    int32_t param_result = PARAM_NG;
    int32_t i;

    /* Check the parameters, the NULL of address */
    for (i = GPIO_PORT_0; i < GPIO_PORT_Max; i++ )
    {
        param_result = check_param_pin_exist(p_obj, group, i, mode);
        if(param_result == PARAM_OK)
        { 
            break;
        }
        else
        {
             /* No Process */
        }
    }
    if (((void*)(p_obj) == (void*)0) || (param_result == PARAM_NG))
    {
        result = TXZ_ERROR;
    }
    else
    {
        switch (group)
        {
#if defined(TMPM3HL)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pa_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pa_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pa_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pa_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pa_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pa_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pa_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pa_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pa_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pa_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pa_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pa_instance->IE;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pb_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pb_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pb_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pb_instance->FR2;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pb_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pb_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pb_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pb_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pb_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pb_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pb_instance->IE;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pc_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pc_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pc_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pc_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pc_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pc_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pc_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pc_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pc_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pc_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pc_instance->IE;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pd_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pd_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pd_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pd_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pd_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pd_instance->IE;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pe_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pe_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pe_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pe_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pe_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pe_instance->IE;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pg_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pg_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pg_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pg_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pg_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pg_instance->IE;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_ph_instance->DATA;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_ph_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_ph_instance->IE;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pj_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pj_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pj_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pj_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pj_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pj_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pj_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pj_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pj_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pj_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pj_instance->IE;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pk_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pk_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pk_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pk_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pk_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pk_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pk_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pk_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pk_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pk_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pk_instance->IE;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pl_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pl_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pl_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pl_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pl_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pl_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pl_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pl_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pl_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pl_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pl_instance->IE;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pm_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pm_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pm_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pm_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pm_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pm_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pm_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pm_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pm_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pm_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pm_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pm_instance->IE;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pn_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pn_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pn_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pn_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pn_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pn_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pn_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pn_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pn_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pn_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pn_instance->IE;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pp_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pp_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pp_instance->FR1;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pp_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pp_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pp_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pp_instance->IE;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pv_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pv_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pv_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pv_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pv_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pv_instance->IE;}
            break;
#endif  /* TMPM3HL */
#if defined(TMPM3HM)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pa_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pa_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pa_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pa_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pa_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pa_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pa_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pa_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pa_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pa_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pa_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pa_instance->IE;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pb_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pb_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pb_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pb_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pb_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pb_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pb_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pb_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pb_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pb_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pb_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pb_instance->IE;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pc_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pc_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pc_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pc_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pc_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pc_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pc_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pc_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pc_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pc_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pc_instance->IE;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pd_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pd_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pd_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pd_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pd_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pd_instance->IE;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pe_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pe_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pe_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pe_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pe_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pe_instance->IE;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pg_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pg_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pg_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pg_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pg_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pg_instance->IE;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_ph_instance->DATA;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_ph_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_ph_instance->IE;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pj_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pj_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pj_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pj_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pj_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pj_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pj_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pj_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pj_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pj_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pj_instance->IE;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pk_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pk_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pk_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pk_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pk_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pk_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pk_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pk_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pk_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pk_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pk_instance->IE;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pl_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pl_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pl_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pl_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pl_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pl_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pl_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pl_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pl_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pl_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pl_instance->IE;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pm_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pm_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pm_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pm_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pm_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pm_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pm_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pm_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pm_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pm_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pm_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pm_instance->IE;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pn_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pn_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pn_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pn_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pn_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pn_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pn_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pn_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pn_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pn_instance->IE;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pp_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pp_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pp_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pp_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pp_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pp_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pp_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pp_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pp_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pp_instance->IE;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pv_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pv_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pv_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pv_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pv_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pv_instance->IE;}
            break;
#endif  /* TMPM3HM */
#if defined(TMPM3HN)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pa_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pa_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pa_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pa_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pa_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pa_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pa_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pa_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pa_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pa_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pa_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pa_instance->IE;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pb_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pb_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pb_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pb_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pb_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pb_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pb_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pb_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pb_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pb_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pb_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pb_instance->IE;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pc_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pc_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pc_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pc_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pc_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pc_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pc_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pc_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pc_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pc_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pc_instance->IE;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pd_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pd_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pd_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pd_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pd_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pd_instance->IE;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pe_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pe_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pe_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pe_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pe_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pe_instance->IE;}
            break;
        case GPIO_PORT_F:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pf_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pf_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pf_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pf_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pf_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pf_instance->IE;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pg_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pg_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pg_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pg_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pg_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pg_instance->IE;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_ph_instance->DATA;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_ph_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_ph_instance->IE;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pj_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pj_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pj_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pj_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pj_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pj_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pj_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pj_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pj_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pj_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pj_instance->IE;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pk_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pk_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pk_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pk_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pk_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pk_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pk_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pk_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pk_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pk_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pk_instance->IE;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pl_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pl_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pl_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pl_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pl_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pl_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pl_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pl_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pl_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pl_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pl_instance->IE;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pm_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pm_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pm_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pm_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pm_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pm_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pm_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pm_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pm_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pm_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pm_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pm_instance->IE;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pn_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pn_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pn_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pn_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pn_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pn_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pn_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pn_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pn_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pn_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pn_instance->IE;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pp_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pp_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pp_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pp_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pp_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pp_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pp_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pp_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pp_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pp_instance->IE;}
            break;
        case GPIO_PORT_R:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pr_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pr_instance->CR;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pr_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pr_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pr_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pr_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pr_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pr_instance->IE;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pv_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pv_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pv_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pv_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pv_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pv_instance->IE;}
            break;
#endif  /* TMPM3HN */
#if defined(TMPM3HN_L)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pa_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pa_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pa_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pa_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pa_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pa_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pa_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pa_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pa_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pa_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pa_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pa_instance->IE;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pb_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pb_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pb_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pb_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pb_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pb_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pb_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pb_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pb_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pb_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pb_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pb_instance->IE;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pc_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pc_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pc_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pc_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pc_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pc_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pc_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pc_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pc_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pc_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pc_instance->IE;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pd_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pd_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pd_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pd_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pd_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pd_instance->IE;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pe_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pe_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pe_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pe_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pe_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pe_instance->IE;}
            break;
        case GPIO_PORT_F:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pf_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pf_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pf_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pf_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pf_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pf_instance->IE;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pg_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pg_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pg_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pg_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pg_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pg_instance->IE;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_ph_instance->DATA;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_ph_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_ph_instance->IE;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pj_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pj_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pj_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pj_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pj_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pj_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pj_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pj_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pj_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pj_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pj_instance->IE;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pk_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pk_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pk_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pk_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pk_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pk_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pk_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pk_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pk_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pk_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pk_instance->IE;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pl_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pl_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pl_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pl_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pl_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pl_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pl_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pl_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pl_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pl_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pl_instance->IE;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pm_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pm_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pm_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pm_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pm_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pm_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pm_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pm_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pm_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pm_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pm_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pm_instance->IE;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pn_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pn_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pn_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pn_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pn_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pn_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pn_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pn_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pn_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pn_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pn_instance->IE;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pp_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pp_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pp_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pp_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pp_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pp_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pp_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pp_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pp_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pp_instance->IE;}
            break;
        case GPIO_PORT_R:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pr_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pr_instance->CR;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pr_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pr_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pr_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pr_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pr_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pr_instance->IE;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pv_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pv_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pv_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pv_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pv_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pv_instance->IE;}
            break;
#endif  /* TMPM3HN_L */
#if defined(TMPM3HP)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pa_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pa_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pa_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pa_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pa_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pa_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pa_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pa_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pa_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pa_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pa_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pa_instance->IE;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pb_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pb_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pb_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pb_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pb_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pb_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pb_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pb_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pb_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pb_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pb_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pb_instance->IE;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pc_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pc_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pc_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pc_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pc_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pc_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pc_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pc_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pc_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pc_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pc_instance->IE;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pd_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pd_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pd_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pd_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pd_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pd_instance->IE;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pe_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pe_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pe_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pe_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pe_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pe_instance->IE;}
            break;
        case GPIO_PORT_F:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pf_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pf_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pf_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pf_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pf_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pf_instance->IE;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pg_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pg_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pg_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pg_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pg_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pg_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pg_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pg_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pg_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pg_instance->IE;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_ph_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_ph_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_ph_instance->FR1;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_ph_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_ph_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_ph_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_ph_instance->IE;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pj_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pj_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pj_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pj_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pj_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pj_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pj_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pj_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pj_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pj_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pj_instance->IE;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pk_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pk_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pk_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pk_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pk_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pk_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pk_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pk_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pk_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pk_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pk_instance->IE;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pl_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pl_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pl_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pl_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pl_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pl_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pl_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pl_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pl_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pl_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pl_instance->IE;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pm_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pm_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pm_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pm_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pm_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pm_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pm_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pm_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pm_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pm_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pm_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pm_instance->IE;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pn_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pn_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pn_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pn_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pn_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pn_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pn_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pn_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pn_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pn_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pn_instance->IE;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pp_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pp_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pp_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pp_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pp_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pp_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pp_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pp_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pp_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pp_instance->IE;}
            break;
        case GPIO_PORT_R:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pr_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pr_instance->CR;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pr_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pr_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pr_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pr_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pr_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pr_instance->IE;}
            break;
        case GPIO_PORT_T:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pt_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pt_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pt_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pt_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pt_instance->FR3;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pt_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pt_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pt_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pt_instance->IE;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pv_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pv_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pv_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pv_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pv_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pv_instance->IE;}
            break;
#endif  /* TMPM3HP */
#if defined(TMPM3HQ)
        case GPIO_PORT_A:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pa_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pa_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pa_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pa_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pa_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pa_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pa_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pa_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pa_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pa_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pa_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pa_instance->IE;}
            break;
        case GPIO_PORT_B:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pb_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pb_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pb_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pb_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pb_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pb_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pb_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pb_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pb_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pb_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pb_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pb_instance->IE;}
            break;
        case GPIO_PORT_C:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pc_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pc_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pc_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pc_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pc_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pc_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pc_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pc_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pc_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pc_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pc_instance->IE;}
            break; 
        case GPIO_PORT_D:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pd_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pd_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pd_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pd_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pd_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pd_instance->IE;}
            break;
        case GPIO_PORT_E:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pe_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pe_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pe_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pe_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pe_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pe_instance->IE;}
            break;
        case GPIO_PORT_F:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pf_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pf_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pf_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pf_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pf_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pf_instance->IE;}
            break;
        case GPIO_PORT_G:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pg_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pg_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pg_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pg_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pg_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pg_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pg_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pg_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pg_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pg_instance->IE;}
            break;
        case GPIO_PORT_H:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_ph_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_ph_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_ph_instance->FR1;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_ph_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_ph_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_ph_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_ph_instance->IE;}
            break;
        case GPIO_PORT_J:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pj_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pj_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pj_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pj_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pj_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pj_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pj_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pj_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pj_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pj_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pj_instance->IE;}
            break;
        case GPIO_PORT_K:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pk_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pk_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pk_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pk_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pk_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pk_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pk_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pk_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pk_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pk_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pk_instance->IE;}
            break;
        case GPIO_PORT_L:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pl_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pl_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pl_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pl_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pl_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pl_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pl_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pl_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pl_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pl_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pl_instance->IE;}
            break;
        case GPIO_PORT_M:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pm_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pm_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pm_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pm_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pm_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pm_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pm_instance->FR5;}
            else if(mode == GPIO_Mode_FR6) {*val = p_obj->p_pm_instance->FR6;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pm_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pm_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pm_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pm_instance->IE;}
            break;
        case GPIO_PORT_N:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pn_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pn_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pn_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pn_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pn_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pn_instance->FR4;}
            else if(mode == GPIO_Mode_FR5) {*val = p_obj->p_pn_instance->FR5;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pn_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pn_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pn_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pn_instance->IE;}
            break;
        case GPIO_PORT_P:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pp_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pp_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pp_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pp_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pp_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pp_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pp_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pp_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pp_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pp_instance->IE;}
            break;
        case GPIO_PORT_R:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pr_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pr_instance->CR;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pr_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pr_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pr_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pr_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pr_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pr_instance->IE;}
            break;
        case GPIO_PORT_T:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pt_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pt_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pt_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pt_instance->FR2;}
            else if(mode == GPIO_Mode_FR3) {*val = p_obj->p_pt_instance->FR3;}
            else if(mode == GPIO_Mode_FR4) {*val = p_obj->p_pt_instance->FR4;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pt_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pt_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pt_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pt_instance->IE;}
            break;
        case GPIO_PORT_U:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pu_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pu_instance->CR;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pu_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pu_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pu_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pu_instance->IE;}
            break;
        case GPIO_PORT_V:
            if(mode == GPIO_Mode_DATA)     {*val = p_obj->p_pv_instance->DATA;}
            else if(mode == GPIO_Mode_CR)  {*val = p_obj->p_pv_instance->CR;}
            else if(mode == GPIO_Mode_FR1) {*val = p_obj->p_pv_instance->FR1;}
            else if(mode == GPIO_Mode_FR2) {*val = p_obj->p_pv_instance->FR2;}
            else if(mode == GPIO_Mode_OD)  {*val = p_obj->p_pv_instance->OD;}
            else if(mode == GPIO_Mode_PUP) {*val = p_obj->p_pv_instance->PUP;}
            else if(mode == GPIO_Mode_PDN) {*val = p_obj->p_pv_instance->PDN;}
            else if(mode == GPIO_Mode_IE)  {*val = p_obj->p_pv_instance->IE;}
            break;
#endif  /* TMPM3HQ */
        default:
            result = TXZ_ERROR;
        }
    }

    return result;
}

/*--------------------------------------------------*/
/**
  * @brief  Port Function switching
  * @param  p_obj  :GPIO object.
  * @param  group  :GPIO Port Group.  : Use @ref gpio_gr_t
  * @param  num    :GPIO Port Number. : Use @ref gpio_num_t
  * @param  func   :GPIO Portxx Func. : Use @ref gpio_pa0_func_t - @ref gpio_pl4_func_t
  * @param  inout  :GPIO Input/Output.: Use @ref gpio_pininout_t
  * @retval GPIO_RESULT_SUCCESS :Success.
  * @retval GPIO_RESULT_FAILURE :Failure.
  * @note   When p_obj is NULL, no processing.
  */
/*--------------------------------------------------*/
TXZ_Result gpio_func(gpio_t *p_obj, gpio_gr_t group, gpio_num_t num, uint32_t func, gpio_pininout_t inout)
{
    TXZ_Result result = TXZ_SUCCESS;
    uint32_t port_base;
    uint32_t mode_base;
    int32_t param_result = PARAM_NG;
    
    /* Check the parameters, the NULL of address */
    param_result = check_param_func_pin_exist(p_obj, group, num, func);
    if (((void*)(p_obj) == (void*)0) || (param_result == PARAM_NG))
    {
        result = TXZ_ERROR;
    }
    else
    {
        switch (group)
        {
        #if defined(TMPM3HL)
        case GPIO_PORT_A:
            port_base = (uint32_t)p_obj->p_pa_instance;
            break;
        case GPIO_PORT_B:
            port_base = (uint32_t)p_obj->p_pb_instance;
            break;
        case GPIO_PORT_C:
            port_base = (uint32_t)p_obj->p_pc_instance;
            break; 
        case GPIO_PORT_D:
            port_base = (uint32_t)p_obj->p_pd_instance;
            break;
        case GPIO_PORT_E:
            port_base = (uint32_t)p_obj->p_pe_instance;
            break;
        case GPIO_PORT_G:
            port_base = (uint32_t)p_obj->p_pg_instance;
            break;
        case GPIO_PORT_H:
            port_base = (uint32_t)p_obj->p_ph_instance;
            break;
        case GPIO_PORT_J:
            port_base = (uint32_t)p_obj->p_pj_instance;
            break;
        case GPIO_PORT_K:
            port_base = (uint32_t)p_obj->p_pk_instance;
            break;
        case GPIO_PORT_L:
            port_base = (uint32_t)p_obj->p_pl_instance;
            break;
        case GPIO_PORT_M:
            port_base = (uint32_t)p_obj->p_pm_instance;
            break;
        case GPIO_PORT_N:
            port_base = (uint32_t)p_obj->p_pn_instance;
            break;
        case GPIO_PORT_P:
            port_base = (uint32_t)p_obj->p_pp_instance;
            break;
        case GPIO_PORT_V:
            port_base = (uint32_t)p_obj->p_pv_instance;
            break;
        #endif  /* TMPM3HL */
        #if defined(TMPM3HM)
        case GPIO_PORT_A:
            port_base = (uint32_t)p_obj->p_pa_instance;
            break;
        case GPIO_PORT_B:
            port_base = (uint32_t)p_obj->p_pb_instance;
            break;
        case GPIO_PORT_C:
            port_base = (uint32_t)p_obj->p_pc_instance;
            break; 
        case GPIO_PORT_D:
            port_base = (uint32_t)p_obj->p_pd_instance;
            break;
        case GPIO_PORT_E:
            port_base = (uint32_t)p_obj->p_pe_instance;
            break;
        case GPIO_PORT_G:
            port_base = (uint32_t)p_obj->p_pg_instance;
            break;
        case GPIO_PORT_H:
            port_base = (uint32_t)p_obj->p_ph_instance;
            break;
        case GPIO_PORT_J:
            port_base = (uint32_t)p_obj->p_pj_instance;
            break;
        case GPIO_PORT_K:
            port_base = (uint32_t)p_obj->p_pk_instance;
            break;
        case GPIO_PORT_L:
            port_base = (uint32_t)p_obj->p_pl_instance;
            break;
        case GPIO_PORT_M:
            port_base = (uint32_t)p_obj->p_pm_instance;
            break;
        case GPIO_PORT_N:
            port_base = (uint32_t)p_obj->p_pn_instance;
            break;
        case GPIO_PORT_P:
            port_base = (uint32_t)p_obj->p_pp_instance;
            break;
        case GPIO_PORT_V:
            port_base = (uint32_t)p_obj->p_pv_instance;
            break;
        #endif  /* TMPM3HM */
        #if defined(TMPM3HN)
        case GPIO_PORT_A:
            port_base = (uint32_t)p_obj->p_pa_instance;
            break;
        case GPIO_PORT_B:
            port_base = (uint32_t)p_obj->p_pb_instance;
            break;
        case GPIO_PORT_C:
            port_base = (uint32_t)p_obj->p_pc_instance;
            break; 
        case GPIO_PORT_D:
            port_base = (uint32_t)p_obj->p_pd_instance;
            break;
        case GPIO_PORT_E:
            port_base = (uint32_t)p_obj->p_pe_instance;
            break;
        case GPIO_PORT_F:
            port_base = (uint32_t)p_obj->p_pf_instance;
            break;
        case GPIO_PORT_G:
            port_base = (uint32_t)p_obj->p_pg_instance;
            break;
        case GPIO_PORT_H:
            port_base = (uint32_t)p_obj->p_ph_instance;
            break;
        case GPIO_PORT_J:
            port_base = (uint32_t)p_obj->p_pj_instance;
            break;
        case GPIO_PORT_K:
            port_base = (uint32_t)p_obj->p_pk_instance;
            break;
        case GPIO_PORT_L:
            port_base = (uint32_t)p_obj->p_pl_instance;
            break;
        case GPIO_PORT_M:
            port_base = (uint32_t)p_obj->p_pm_instance;
            break;
        case GPIO_PORT_N:
            port_base = (uint32_t)p_obj->p_pn_instance;
            break;
        case GPIO_PORT_V:
            port_base = (uint32_t)p_obj->p_pv_instance;
            break;
        #endif  /* TMPM3HN */
        #if defined(TMPM3HN_L)
        case GPIO_PORT_A:
            port_base = (uint32_t)p_obj->p_pa_instance;
            break;
        case GPIO_PORT_B:
            port_base = (uint32_t)p_obj->p_pb_instance;
            break;
        case GPIO_PORT_C:
            port_base = (uint32_t)p_obj->p_pc_instance;
            break; 
        case GPIO_PORT_D:
            port_base = (uint32_t)p_obj->p_pd_instance;
            break;
        case GPIO_PORT_E:
            port_base = (uint32_t)p_obj->p_pe_instance;
            break;
        case GPIO_PORT_F:
            port_base = (uint32_t)p_obj->p_pf_instance;
            break;
        case GPIO_PORT_G:
            port_base = (uint32_t)p_obj->p_pg_instance;
            break;
        case GPIO_PORT_H:
            port_base = (uint32_t)p_obj->p_ph_instance;
            break;
        case GPIO_PORT_J:
            port_base = (uint32_t)p_obj->p_pj_instance;
            break;
        case GPIO_PORT_K:
            port_base = (uint32_t)p_obj->p_pk_instance;
            break;
        case GPIO_PORT_L:
            port_base = (uint32_t)p_obj->p_pl_instance;
            break;
        case GPIO_PORT_M:
            port_base = (uint32_t)p_obj->p_pm_instance;
            break;
        case GPIO_PORT_N:
            port_base = (uint32_t)p_obj->p_pn_instance;
            break;
        case GPIO_PORT_P:
            port_base = (uint32_t)p_obj->p_pp_instance;
            break;
        case GPIO_PORT_R:
            port_base = (uint32_t)p_obj->p_pr_instance;
            break;
        case GPIO_PORT_V:
            port_base = (uint32_t)p_obj->p_pv_instance;
            break;
        #endif  /* TMPM3HN_L */
        #if defined(TMPM3HP)
        case GPIO_PORT_A:
            port_base = (uint32_t)p_obj->p_pa_instance;
            break;
        case GPIO_PORT_B:
            port_base = (uint32_t)p_obj->p_pb_instance;
            break;
        case GPIO_PORT_C:
            port_base = (uint32_t)p_obj->p_pc_instance;
            break; 
        case GPIO_PORT_D:
            port_base = (uint32_t)p_obj->p_pd_instance;
            break;
        case GPIO_PORT_E:
            port_base = (uint32_t)p_obj->p_pe_instance;
            break;
        case GPIO_PORT_F:
            port_base = (uint32_t)p_obj->p_pf_instance;
            break;
        case GPIO_PORT_G:
            port_base = (uint32_t)p_obj->p_pg_instance;
            break;
        case GPIO_PORT_H:
            port_base = (uint32_t)p_obj->p_ph_instance;
            break;
        case GPIO_PORT_J:
            port_base = (uint32_t)p_obj->p_pj_instance;
            break;
        case GPIO_PORT_K:
            port_base = (uint32_t)p_obj->p_pk_instance;
            break;
        case GPIO_PORT_L:
            port_base = (uint32_t)p_obj->p_pl_instance;
            break;
        case GPIO_PORT_M:
            port_base = (uint32_t)p_obj->p_pm_instance;
            break;
        case GPIO_PORT_N:
            port_base = (uint32_t)p_obj->p_pn_instance;
            break;
        case GPIO_PORT_P:
            port_base = (uint32_t)p_obj->p_pp_instance;
            break;
        case GPIO_PORT_R:
            port_base = (uint32_t)p_obj->p_pr_instance;
            break;
        case GPIO_PORT_T:
            port_base = (uint32_t)p_obj->p_pt_instance;
            break;
        case GPIO_PORT_V:
            port_base = (uint32_t)p_obj->p_pv_instance;
            break;
        #endif  /* TMPM3HP */
        #if defined(TMPM3HQ)
        case GPIO_PORT_A:
            port_base = (uint32_t)p_obj->p_pa_instance;
            break;
        case GPIO_PORT_B:
            port_base = (uint32_t)p_obj->p_pb_instance;
            break;
        case GPIO_PORT_C:
            port_base = (uint32_t)p_obj->p_pc_instance;
            break; 
        case GPIO_PORT_D:
            port_base = (uint32_t)p_obj->p_pd_instance;
            break;
        case GPIO_PORT_E:
            port_base = (uint32_t)p_obj->p_pe_instance;
            break;
        case GPIO_PORT_F:
            port_base = (uint32_t)p_obj->p_pf_instance;
            break;
        case GPIO_PORT_G:
            port_base = (uint32_t)p_obj->p_pg_instance;
            break;
        case GPIO_PORT_H:
            port_base = (uint32_t)p_obj->p_ph_instance;
            break;
        case GPIO_PORT_J:
            port_base = (uint32_t)p_obj->p_pj_instance;
            break;
        case GPIO_PORT_K:
            port_base = (uint32_t)p_obj->p_pk_instance;
            break;
        case GPIO_PORT_L:
            port_base = (uint32_t)p_obj->p_pl_instance;
            break;
        case GPIO_PORT_M:
            port_base = (uint32_t)p_obj->p_pm_instance;
            break;
        case GPIO_PORT_N:
            port_base = (uint32_t)p_obj->p_pn_instance;
            break;
        case GPIO_PORT_P:
            port_base = (uint32_t)p_obj->p_pp_instance;
            break;
        case GPIO_PORT_R:
            port_base = (uint32_t)p_obj->p_pr_instance;
            break;
        case GPIO_PORT_T:
            port_base = (uint32_t)p_obj->p_pt_instance;
            break;
        case GPIO_PORT_U:
            port_base = (uint32_t)p_obj->p_pu_instance;
            break;
        case GPIO_PORT_V:
            port_base = (uint32_t)p_obj->p_pv_instance;
            break;
        #endif  /* TMPM3HQ */
        default:
            result = TXZ_ERROR;
        }
        if(result == TXZ_ERROR)
        {
            return (result);
        }

        /* Initialization PxFR OFF */    
        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR1);
        BITBAND_PORT_CLR(mode_base, num);
        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR2);
        BITBAND_PORT_CLR(mode_base, num);
        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR3);
        BITBAND_PORT_CLR(mode_base, num);
        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR4);
        BITBAND_PORT_CLR(mode_base, num);
        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR5);
        BITBAND_PORT_CLR(mode_base, num);
        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR6);
        BITBAND_PORT_CLR(mode_base, num);
        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR7);
        BITBAND_PORT_CLR(mode_base, num);
        
        /* Initialize Input/Output */
        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
        BITBAND_PORT_CLR(mode_base, num);
        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
        BITBAND_PORT_CLR(mode_base, num);
    
        switch (func) {
            case 0:
                if(inout== GPIO_PIN_OUTPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_CLR(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_INPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_CLR(mode_base, num);
                }else if(inout== GPIO_PIN_INOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_NOTINOUT){
                    /* No Process */
                }
                break;
            case GPIO_FR_1:
                if(inout== GPIO_PIN_OUTPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_CLR(mode_base, num);
               		mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR1);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_INPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
               		mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR1);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_CLR(mode_base, num);
                }else if(inout== GPIO_PIN_INOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
               		mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR1);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_NOTINOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR1);
                	BITBAND_PORT_SET(mode_base, num);
                }
                break;
            case GPIO_FR_2:
                if(inout== GPIO_PIN_OUTPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_CLR(mode_base, num);
  	             	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR2);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_INPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
  	             	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR2);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_CLR(mode_base, num);
                }else if(inout== GPIO_PIN_INOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
  	             	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR2);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_NOTINOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR2);
                	BITBAND_PORT_SET(mode_base, num);
                }
                break;
            case GPIO_FR_3:
                if(inout== GPIO_PIN_OUTPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_CLR(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR3);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_INPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR3);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_CLR(mode_base, num);
                }else if(inout== GPIO_PIN_INOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR3);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_NOTINOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR3);
                	BITBAND_PORT_SET(mode_base, num);
                }
                break;
             case GPIO_FR_4:
                if(inout== GPIO_PIN_OUTPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_CLR(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR4);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_INPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR4);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_CLR(mode_base, num);
                }else if(inout== GPIO_PIN_INOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR4);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_NOTINOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR4);
                	BITBAND_PORT_SET(mode_base, num);
                }
                break;
             case GPIO_FR_5:
                if(inout== GPIO_PIN_OUTPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_CLR(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR5);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_INPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR5);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_CLR(mode_base, num);
                }else if(inout== GPIO_PIN_INOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR5);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }
                break;
             case 6:
                if(inout== GPIO_PIN_OUTPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_CLR(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR6);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_INPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR6);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_CLR(mode_base, num);
                }else if(inout== GPIO_PIN_INOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR6);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_NOTINOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR6);
                	BITBAND_PORT_SET(mode_base, num);
                }
                break;
             case GPIO_FR_7:
                if(inout== GPIO_PIN_OUTPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_CLR(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR7);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_INPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
               		mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR7);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_CLR(mode_base, num);
                }else if(inout== GPIO_PIN_INOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                	mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR7);
                	BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_NOTINOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_FR7);
                	BITBAND_PORT_SET(mode_base, num);
                }
                break;
            case GPIO_FR_NA:
                if(inout== GPIO_PIN_OUTPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_CLR(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_INPUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_CLR(mode_base, num);
                }else if(inout== GPIO_PIN_INOUT){
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_IE);
                    BITBAND_PORT_SET(mode_base, num);
                    mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_CR);
                    BITBAND_PORT_SET(mode_base, num);
                }else if(inout== GPIO_PIN_NOTINOUT){
                    /* No Process */
                }
                break;
            default:
                result = TXZ_ERROR;
                return (result);
         }
    }

    return (result);
}

/*--------------------------------------------------*/
/**
  * @brief  Set Pull up mode
  * @param  p_obj  :GPIO object.
  * @param  group  :GPIO Port Group.  : Use @ref gpio_gr_t
  * @param  num    :GPIO Port Number. : Use @ref gpio_num_t
  * @param  val    :GPIO Pin Reset/Set. : Use @ref gpio_pinstate_t
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   When p_obj is NULL, no processing.
  */
/*--------------------------------------------------*/
TXZ_Result gpio_SetPullUp(gpio_t *p_obj, gpio_gr_t group, gpio_num_t num, gpio_pinstate_t val)
{
    TXZ_Result result = TXZ_SUCCESS;
    uint32_t port_base;
    uint32_t mode_base;

    if (((void*)(p_obj) == (void*)0) ||
        (check_param_pin_exist(p_obj, group, num, GPIO_Mode_PUP) == PARAM_NG))
    {
        result = TXZ_ERROR;
    }
    else
    {
        port_base = BITBAND_PORT_BASE(group);

        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_PUP);
        if (val == GPIO_PIN_SET)
           {BITBAND_PORT_SET(mode_base, num);}
        else if (val == GPIO_PIN_RESET)
           {BITBAND_PORT_CLR(mode_base, num);}
        else {result = TXZ_ERROR;}
    }

    return result;
}

/*--------------------------------------------------*/
/**
  * @brief  Set Pull down mode
  * @param  p_obj  :GPIO object.
  * @param  group  :GPIO Port Group.  : Use @ref gpio_gr_t
  * @param  num    :GPIO Port Number. : Use @ref gpio_num_t
  * @param  val    :GPIO Pin Reset/Set. : Use @ref gpio_pinstate_t
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   When p_obj is NULL, no processing.
  */
/*--------------------------------------------------*/
TXZ_Result gpio_SetPullDown(gpio_t *p_obj, gpio_gr_t group, gpio_num_t num, gpio_pinstate_t val)
{
    TXZ_Result result = TXZ_SUCCESS;
    uint32_t port_base;
    uint32_t mode_base;

    if (((void*)(p_obj) == (void*)0) ||
        (check_param_pin_exist(p_obj, group, num, GPIO_Mode_PDN) == PARAM_NG))
    {
        result = TXZ_ERROR;
    }
    else
    {
        port_base = BITBAND_PORT_BASE(group);

        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_PDN);
        if (val == GPIO_PIN_SET)
            {BITBAND_PORT_SET(mode_base, num);}
        else if (val == GPIO_PIN_RESET)
            {BITBAND_PORT_CLR(mode_base, num);}
        else {result = TXZ_ERROR;}
    }

    return result;
}

/*--------------------------------------------------*/
/**
  * @brief  Set Open drain mode
  * @param  p_obj  :GPIO object.
  * @param  group  :GPIO Port Group.  : Use @ref gpio_gr_t
  * @param  num    :GPIO Port Number. : Use @ref gpio_num_t
  * @param  val    :GPIO Pin Reset/Set. : Use @ref gpio_pinstate_t
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   When p_obj is NULL, no processing.
  */
/*--------------------------------------------------*/
TXZ_Result gpio_SetOpenDrain(gpio_t *p_obj, gpio_gr_t group, gpio_num_t num, gpio_pinstate_t val)
{
    TXZ_Result result = TXZ_SUCCESS;
    uint32_t port_base;
    uint32_t mode_base;

    if (((void*)(p_obj) == (void*)0) ||
        (check_param_pin_exist(p_obj, group, num, GPIO_Mode_OD) == PARAM_NG))
    {
        result = TXZ_ERROR;
    }
    else
    {
        port_base = BITBAND_PORT_BASE(group);

        mode_base = BITBAND_PORT_MODE_BASE(port_base, GPIO_Mode_OD);
        if (val == GPIO_PIN_SET)
            {BITBAND_PORT_SET(mode_base, num);}
        else if (val == GPIO_PIN_RESET) 
            {BITBAND_PORT_CLR(mode_base, num);}
        else {result = TXZ_ERROR;}
    }

    return result;
}

/*--------------------------------------------------*/
/*!
  * @fn     TXZ_Result gpio_write_bit(gpio_t *p_obj, uint32_t group, uint32_t num, uint32_t mode, uint32_t val)
  * @brief  Port Bit Write
  * @param  p_obj  :GPIO object.
  * @param  group  :GPIO Port Group.  : Use @ref gpio_gr_t
  * @param  num    :GPIO Port Number. : Use @ref gpio_num_t
  * @param  mode   :GPIO Port Mode. : Use @ref gpio_mode_t
  * @param  val    :GPIO Pin Reset/Set.
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   When p_obj is NULL, no processing.
  */
/*--------------------------------------------------*/
TXZ_Result gpio_write_bit(gpio_t *p_obj, uint32_t group, uint32_t num, uint32_t mode, uint32_t val)
{
    TXZ_Result result = TXZ_SUCCESS;
    uint32_t base;

    /* Check the parameters */
    if (((void*)(p_obj) == (void*)0) ||
        (check_param_pin_exist(p_obj, group, num, mode) == PARAM_NG))
    {
        result = TXZ_ERROR;
    }
    else
    {
        base = BITBAND_PORT_BASE(group);
        base = BITBAND_PORT_MODE_BASE(base, mode);
        if (val == GPIO_PIN_SET) {BITBAND_PORT_SET(base, num);}
        else if (val == GPIO_PIN_RESET) {BITBAND_PORT_CLR(base, num);}
        else {result = TXZ_ERROR;}
    }

    return (result);
}

/*--------------------------------------------------*/
/*!
  * @fn     TXZ_Result gpio_read_bit(gpio_t *p_obj, uint32_t group, uint32_t num, uint32_t mode, gpio_pinstate_t *pinstate)
  * @brief  Port Bit Read
  * @param[in]  p_obj  :GPIO object.
  * @param[in]  group  :GPIO Port Group.  : Use @ref gpio_gr_t
  * @param[in]  num    :GPIO Port Number. : Use @ref gpio_num_t
  * @param[in]  mode   :GPIO Port Mode. : Use @ref gpio_mode_t
  * @param[out] *pinstate  : store  Value of GPIO BitPin. : Use @ref gpio_pinstate_t
  * @retval TXZ_SUCCESS :Success.
  * @retval TXZ_ERROR   :Failure.
  * @note   When p_obj is NULL, no processing.: Use @ref gpio_pinstate_t
  */
/*--------------------------------------------------*/
TXZ_Result gpio_read_bit(gpio_t *p_obj, uint32_t group, uint32_t num, uint32_t mode, gpio_pinstate_t *pinstate)
{
    TXZ_Result result = TXZ_SUCCESS;
    uint32_t base;
    uint32_t val;

    /* Check the parameters */   
    if (((void*)(p_obj) == (void*)0) ||
        (check_param_pin_exist(p_obj, group, num, mode) == PARAM_NG))
    {
        result = TXZ_ERROR;
    }
    else
    {
        base = BITBAND_PORT_BASE(group);
        base = BITBAND_PORT_MODE_BASE(base, mode);
        BITBAND_PORT_READ(val, base, num);
        if(val == GPIO_PIN_RESET) {*pinstate = GPIO_PIN_RESET;}
        else if (val == GPIO_PIN_SET) {*pinstate = GPIO_PIN_SET;}
        else {result = TXZ_ERROR;}
    }

    return result;
}

/**
 *  @}
 */ /* End of group GPIO_Exported_functions */

/**
 *  @} 
 */ /* End of group GPIO */

/**
 *  @} 
 */ /* End of group Periph_Driver */

#endif /* defined(__GPIO_H)  */

#ifdef __cplusplus
}
#endif /* __cplusplus */


