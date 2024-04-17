/*
 * Copyright (c) 2014 - 2016, Freescale Semiconductor, Inc.
 * Copyright (c) 2016 - 2018, NXP.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "device_registers.h"	/* include peripheral declarations */
#include "FTM.h"

void FTMx_init(FTM_ConfigType *FTM_type)
{
	if(FTM_type->FTM_Chanel<=7 && FTM_type->FTM_Chanel>=0)
	{
		/**
		 * FTM Clocking:
		 * ==================================================
		 */
		PCC->PCCn[PCC_FTM0_INDEX] &= ~PCC_PCCn_CGC_MASK; 	/* Ensure clk disabled for config 	*/
		PCC->PCCn[PCC_FTM0_INDEX] |= PCC_PCCn_PCS(FTM_type->Clock_Source_FTM)	/* Clock Src=1, 8 MHz SIRCDIV1_CLK */
								  |  PCC_PCCn_CGC_MASK;  	/* Enable clock for FTM regs 		*/

		/*!
		 * FTM Initialization:
		 * ===================================================
		 */
		FTM_type->FTMx->MODE |= FTM_MODE_WPDIS_MASK;  /* Write protect to registers disabled (default) */
		FTM_type->FTMx->SC = 0x00000000; /* Clear the status and control register */
		if(FTM_type->PWM_Enable)
		{
			FTM_type->FTMx->SC |= (uint32_t)(1<<(16u+FTM_type->FTM_Chanel));/* Enable PWM channel x output	*/
		}
		if(FTM_type->Prescaler <=7)
		{

			FTM_type->FTMx->SC |= FTM_SC_PS(FTM_type->Prescaler);
		}
		FTM_type->FTMx->COMBINE = 0x00000000;	/* FTM mode settings used: DECAPENx, MCOMBINEx, COMBINEx=0 */
		FTM_type->FTMx->POL = 0x00000000;    	/* Polarity for all channels is active high (default) 		*/
		if(FTM_type->Polarity)
		{
			FTM_type->FTMx->POL |= (uint32_t)(1<<(FTM_type->FTM_Chanel));    	/* Polarity for channels x is active low 	*/
		}

	}
}
void FTMx_CHx_PWM_init(PWM_ConfigType *PWM_type)
{
	PWM_type->FTMx->MOD = FTM_MOD_MOD(PWM_type->Modulo_Value);     	/* FTM counter final value (used for PWM mode) 			*/
								/* FTM Period = MOD-CNTIN+0x0001 ~=*/
	if(PWM_type->Pwm_Mode_Select==EDGE_ALIGNED_PWM)
	{
		PWM_type->FTMx->CONTROLS[PWM_type->PWM_Chanel].CnSC = FTM_CnSC_MSB_MASK; /* MSB:MSA (chan Mode Select)=0b10, Edge Align PWM		*/
	}
	if(PWM_type->Pwm_Edge_Level_Select==LOW_TRUE_PULSES)
	{
		PWM_type->FTMx->CONTROLS[PWM_type->PWM_Chanel].CnSC |= FTM_CnSC_ELSB_MASK; /* ELSB:ELSA (chan Edge/Level Select)=0b10, low true */
	}
	else
	{
		PWM_type->FTMx->CONTROLS[PWM_type->PWM_Chanel].CnSC |= FTM_CnSC_ELSA_MASK; /* ELSB:ELSA (chan Edge/Level Select)=0bX1, High-true */
	}
	PWM_type->FTMx->CONTROLS[PWM_type->PWM_Chanel].CnV =  FTM_CnV_VAL(PWM_type->CnV);	/* FTM0 ch1 compare value (set % duty cycle) */
}
void FTM0_start_counter (void)
{
	FTM0->SC |= FTM_SC_CLKS(3);
	/* Start FTM0 counter with clk source = external clock (SOSCDIV1_CLK)*/
}
void FTM0_stop_counter (void)
{
	FTM0->SC &= (uint32_t)(~(1U<<3U));
	/* Start FTMx counter with clk source = external clock*/
}

