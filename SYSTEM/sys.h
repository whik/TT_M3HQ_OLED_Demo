#ifndef __SYS_H__
#define __SYS_H__

#include "TMPM3HQ.h"
#include "TMPM3Hy.h"

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define PORTx_BASE(group)       (0x400C0000UL + (uint32_t)((0x0000100UL) * (group)))
#define PORTx_MODE_BASE(group)   ((uint32_t)(PORTx_BASE(group)) + (uint32_t)(GPIO_Mode_DATA))

#define PORTA_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_A)
#define PORTB_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_B)
#define PORTC_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_C)
#define PORTD_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_D)
#define PORTE_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_E)
#define PORTF_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_F)
#define PORTG_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_G)
#define PORTH_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_H)
#define PORTJ_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_J)
#define PORTK_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_K)
#define PORTL_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_L)
#define PORTM_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_M)
#define PORTN_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_N)
#define PORTP_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_P)
#define PORTR_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_R)
#define PORTT_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_T)
#define PORTU_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_U)
#define PORTV_ODR_ADDR      PORTx_MODE_BASE(GPIO_PORT_V)

#define PAout(n)   BIT_ADDR(PORTA_ODR_ADDR, n)   
#define PBout(n)   BIT_ADDR(PORTB_ODR_ADDR, n)   
#define PCout(n)   BIT_ADDR(PORTC_ODR_ADDR, n)   
#define PDout(n)   BIT_ADDR(PORTD_ODR_ADDR, n)   
#define PEout(n)   BIT_ADDR(PORTE_ODR_ADDR, n)   
#define PFout(n)   BIT_ADDR(PORTF_ODR_ADDR, n)   
#define PGout(n)   BIT_ADDR(PORTG_ODR_ADDR, n)   
#define PHout(n)   BIT_ADDR(PORTH_ODR_ADDR, n)   
#define PJout(n)   BIT_ADDR(PORTJ_ODR_ADDR, n)   
#define PKout(n)   BIT_ADDR(PORTK_ODR_ADDR, n)   
#define PLout(n)   BIT_ADDR(PORTL_ODR_ADDR, n)   
#define PMout(n)   BIT_ADDR(PORTM_ODR_ADDR, n)   
#define PNout(n)   BIT_ADDR(PORTN_ODR_ADDR, n)   
#define PPout(n)   BIT_ADDR(PORTP_ODR_ADDR, n)   
#define PRout(n)   BIT_ADDR(PORTR_ODR_ADDR, n)   
#define PTout(n)   BIT_ADDR(PORTT_ODR_ADDR, n)   
#define PUout(n)   BIT_ADDR(PORTU_ODR_ADDR, n)   
#define PVout(n)   BIT_ADDR(PORTV_ODR_ADDR, n)   


//实现指定管脚置位和复位
/*
PORTx_SET(GPIO_PORT_K, 5);
PORTx_CLR(GPIO_PORT_K, 4);
*/
#define PORTx_SET(group, pin)   (*((__IO uint32_t *)PORTx_MODE_BASE(group)) |= (uint32_t)(0x0000001UL<< pin))
#define PORTx_CLR(group, pin)   (*((__IO uint32_t *)PORTx_MODE_BASE(group)) &= ~((uint32_t)(0x0000001UL<< pin)))

/*
//实现指定管脚置位和复位
#define PORTx_SET(group, pin)   (BIT_ADDR(PORTx_MODE_BASE(group), pin)=1)
#define PORTx_CLR(group, pin)   (BIT_ADDR(PORTx_MODE_BASE(group), pin)=0)
*/

//读取指定引脚的输入状态
#define READ_PIN(group, pin)    ((*((__IO uint32_t *)(PORTx_MODE_BASE(group))) & (uint32_t)(0x0000001UL<< pin)) >> pin)

//输入状态 = GPIO_PIN_RESET or GPIO_PIN_SET
#define PAin(pin)   READ_PIN(GPIO_PORT_A, pin)
#define PBin(pin)   READ_PIN(GPIO_PORT_B, pin)
#define PCin(pin)   READ_PIN(GPIO_PORT_C, pin)
#define PDin(pin)   READ_PIN(GPIO_PORT_D, pin)
#define PEin(pin)   READ_PIN(GPIO_PORT_E, pin)
#define PFin(pin)   READ_PIN(GPIO_PORT_F, pin)
#define PGin(pin)   READ_PIN(GPIO_PORT_G, pin)
#define PHin(pin)   READ_PIN(GPIO_PORT_H, pin)
#define PJin(pin)   READ_PIN(GPIO_PORT_J, pin)
#define PKin(pin)   READ_PIN(GPIO_PORT_K, pin)
#define PLin(pin)   READ_PIN(GPIO_PORT_L, pin)
#define PMin(pin)   READ_PIN(GPIO_PORT_M, pin)
#define PNin(pin)   READ_PIN(GPIO_PORT_N, pin)
#define PPin(pin)   READ_PIN(GPIO_PORT_P, pin)
#define PRin(pin)   READ_PIN(GPIO_PORT_R, pin)
#define PTin(pin)   READ_PIN(GPIO_PORT_T, pin)
#define PUin(pin)   READ_PIN(GPIO_PORT_U, pin)

#define PVin(pin)   READ_PIN(GPIO_PORT_V, pin)


#endif


