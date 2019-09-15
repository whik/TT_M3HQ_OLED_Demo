#include "bsp.h"

void ClockInit(void)
{
    TSB_CG_FSYSENA_IPENA00 = 1;     /* Port A    */
    TSB_CG_FSYSENA_IPENA01 = 1;     /* Port B    */
    TSB_CG_FSYSENA_IPENA02 = 1;     /* Port C    */
    TSB_CG_FSYSENA_IPENA03 = 1;     /* Port D    */
    TSB_CG_FSYSENA_IPENA04 = 1;     /* Port E    */
    TSB_CG_FSYSENA_IPENA05 = 1;     /* Port F    */
    TSB_CG_FSYSENA_IPENA06 = 1;     /* Port G    */
    TSB_CG_FSYSENA_IPENA07 = 1;     /* Port H    */
    TSB_CG_FSYSENA_IPENA08 = 1;     /* Port J    */
    TSB_CG_FSYSENA_IPENA09 = 1;     /* Port K    */
    TSB_CG_FSYSENA_IPENA10 = 1;     /* Port L    */
    TSB_CG_FSYSENA_IPENA11 = 1;     /* Port M    */
    TSB_CG_FSYSENA_IPENA12 = 1;     /* Port N    */
    TSB_CG_FSYSENA_IPENA13 = 1;     /* Port P    */
    TSB_CG_FSYSENA_IPENA14 = 1;     /* Port R    */
    TSB_CG_FSYSENA_IPENA15 = 1;     /* Port T    */
    TSB_CG_FSYSENA_IPENA16 = 1;     /* Port U    */
    TSB_CG_FSYSENA_IPENA17 = 1;     /* Port V    */
    TSB_CG_FSYSENA_IPENA18 = 1;     /* DMAC 0    */
    TSB_CG_FSYSENA_IPENA19 = 1;     /* DMAC 1    */
    TSB_CG_FSYSENA_IPENA20 = 1;     /* A-PMD     */
    TSB_CG_FSYSENA_IPENA21 = 1;     /* A-ENC     */
    TSB_CG_FSYSENA_IPENA22 = 1;     /* RMC       */
    TSB_CG_FSYSENA_IPENA23 = 1;     /* RTC       */
    TSB_CG_FSYSENA_IPENA24 = 1;     /* T32A 0    */
    TSB_CG_FSYSENA_IPENA25 = 1;     /* T32A 1    */
    TSB_CG_FSYSENA_IPENA26 = 1;     /* T32A 2    */
    TSB_CG_FSYSENA_IPENA27 = 1;     /* T32A 3    */
    TSB_CG_FSYSENA_IPENA28 = 1;     /* T32A 4    */
    TSB_CG_FSYSENA_IPENA29 = 1;     /* T32A 5    */
    TSB_CG_FSYSENA_IPENA30 = 1;     /* T32A 6    */
    TSB_CG_FSYSENA_IPENA31 = 1;     /* T32A 7    */

    TSB_CG_FSYSENB_IPENB00 = 1;     /* TSPI 0    */
    TSB_CG_FSYSENB_IPENB01 = 1;     /* TSPI 1    */
    TSB_CG_FSYSENB_IPENB02 = 1;     /* TSPI 2    */
    TSB_CG_FSYSENB_IPENB03 = 1;     /* TSPI 3    */
    TSB_CG_FSYSENB_IPENB04 = 1;     /* TSPI 4    */
    TSB_CG_FSYSENB_IPENB05 = 1;     /* UART 0    */
    TSB_CG_FSYSENB_IPENB06 = 1;     /* UART 1    */
    TSB_CG_FSYSENB_IPENB07 = 1;     /* UART 2    */
    TSB_CG_FSYSENB_IPENB08 = 1;     /* UART 3    */
    TSB_CG_FSYSENB_IPENB09 = 1;     /* UART 4    */
    TSB_CG_FSYSENB_IPENB10 = 1;     /* UART 5    */
    TSB_CG_FSYSENB_IPENB11 = 1;     /* I2C 0     */
    TSB_CG_FSYSENB_IPENB12 = 1;     /* I2C 1     */
    TSB_CG_FSYSENB_IPENB13 = 1;     /* I2C 2     */
    TSB_CG_FSYSENB_IPENB14 = 1;     /* I2C 3     */
    TSB_CG_FSYSENB_IPENB15 = 1;     /* ADC       */
    TSB_CG_FSYSENB_IPENB16 = 0;     /* Reserved  */
    TSB_CG_FSYSENB_IPENB17 = 1;     /* DAC 0     */
    TSB_CG_FSYSENB_IPENB18 = 1;     /* DAC 1     */
    TSB_CG_FSYSENB_IPENB19 = 1;     /* RAMPARITY */
    TSB_CG_FSYSENB_IPENB20 = 1;     /* CRC       */
    TSB_CG_FSYSENB_IPENB21 = 1;     /* OFD       */
    TSB_CG_FSYSENB_IPENB22 = 1;     /* TRM       */
    TSB_CG_FSYSENB_IPENB23 = 1;     /* TRGSEL    */
    TSB_CG_FSYSENB_IPENB31 = 1;     /* SIWDT     */

    TSB_CG_FCEN_FCIPEN07   = 1;
    TSB_CG_SPCLKEN_TRCKEN  = 1;
    TSB_CG_SPCLKEN_ADCKEN  = 1;
}

uint32_t fac_us=0;							//us延时倍乘数			   
uint32_t fac_ms=0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数
	
void delay_init(void)
{
    SystemCoreClockUpdate();        //可以省略
}
void SysTick_Handler(void)
{
    if(fac_us) fac_us--;
    if(fac_ms) fac_ms--;
}
void delay_us(uint32_t nus)
{	
    SysTick_Config(SystemCoreClock / 1000000);  //定时1us
    fac_us = nus;
    while(fac_us != 0);	 
}

void delay_ms(uint32_t nms)
{	 		  	  
    SysTick_Config(SystemCoreClock / 1000);     //定时1ms
    fac_ms = nms;
    while(fac_ms != 0);	 	  	    
} 

