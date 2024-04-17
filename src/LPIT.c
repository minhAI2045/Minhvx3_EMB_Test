#include "LPIT.h"

void delay(uint32_t count) {
    while (count--) {
    	__asm("nop");
    }
}

void LPIT_Init(LPITConfig* LPIT)
{
	if (LPIT != NULL && LPIT->channel < LPIT_TMR_COUNT)
	{
		PCC->PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_PCS(LPIT->clksoure);    /* Clock Src*/
		PCC->PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clk to LPIT0 regs */
		LPIT0->MCR |= LPIT_MCR_M_CEN_MASK;/* Enable module Clk */
		delay(4); /* Wait for 4 peripheral clock cycles */
		LPIT0->TMR[LPIT->channel].TCTRL &= (uint32_t)(~(1u)); /* disable LPIT0 timer */
		if(LPIT->TVAL>0)
		{
			LPIT0->TMR[LPIT->channel].TVAL = LPIT_TMR_TVAL_TMR_VAL(LPIT->TVAL); /* Configure LPIT0 timer 0 for a period */
		}
		if(LPIT->irq)
		{
			LPIT0->MIER |= (uint32_t)(1u<<LPIT->channel); /* Enable LPIT0 timer 0 interrupt */
		}
		else
		{
			LPIT0->MIER &= (uint32_t)(~(1u<<LPIT->channel)); /* Enable LPIT0 timer 0 interrupt */
		}
		LPIT0->MCR |= LPIT_MCR_DOZE_EN(1)| LPIT_MCR_DBG_EN(1); /* Configure the low power modes of the module */
		LPIT0->TMR[LPIT->channel].TCTRL |= (uint32_t)(1u); /* Start LPIT0 timer 0 */
	}
}
void ClearFlag_LPIT(uint8_t channel)
{
	LPIT0->MSR |= (uint32_t)(1u<<channel); /* Clear channel 0's interrupt flag */
}
