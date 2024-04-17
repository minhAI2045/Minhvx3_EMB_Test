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

#ifndef FTM_H_
#define FTM_H_
typedef enum{
	CLOCK_FTM_SOURCE_DISABLED=0U,
	CLOCK_FTM_SOURCE_SOSCDIV1=1U,
	CLOCK_FTM_SOURCE_SIRCDIV1=2U,
	CLOCK_FTM_SOURCE_FIRCDIV1=3U,
	CLOCK_FTM_SOURCE_SPLLDIV1=6U,
}ClockSource_FTM_Type;
typedef enum{
	ACTIVE_HIGH=0U,
	ACTIVE_LOW=1U,
}Polarity_Active;
typedef enum{
	CENTER_ALIGNED_PWM=0U,
	EDGE_ALIGNED_PWM=1U
}PWM_Mode_Select;
typedef enum{
	HIGH_TRUE_PULSES=0U,
	LOW_TRUE_PULSES=1U
}PWM_Edge_Level_Select;
typedef struct
{
	FTM_Type* FTMx;
	uint8_t PWM_Chanel;
	PWM_Mode_Select Pwm_Mode_Select;
	PWM_Edge_Level_Select Pwm_Edge_Level_Select;
	uint16_t Modulo_Value; /* FTM counter final value (used for PWM mode)*/
	uint16_t CnV;
}PWM_ConfigType;
typedef struct
{
	FTM_Type* FTMx;
	uint8_t FTM_Chanel;
	ClockSource_FTM_Type Clock_Source_FTM;
	Polarity_Active Polarity;
	uint8_t Prescaler;
	bool PWM_Enable;
} FTM_ConfigType;

void FTMx_init(FTM_ConfigType *FTM_type);
void FTMx_CHx_PWM_init(PWM_ConfigType *PWM_type);
void FTM0_start_counter (void);
void FTM0_stop_counter (void);
#endif /* PWM_H_ */
