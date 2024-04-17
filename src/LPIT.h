/*
 * LPIT.h
 *
 *  Created on: Apr 3, 2024
 *      Author: ADMIN
 */

#ifndef LPIT_H_
#define LPIT_H_
#include"S32K144.h"
#include <stdint.h>
#include<string.h>
typedef enum{
	CLOCK_SOURCE_DISABLED=0U,
	CLOCK_SOURCE_SOSCDIV2=1U,
	CLOCK_SOURCE_SIRCDIV2=2U,
	CLOCK_SOURCE_FIRCDIV2=3U,
	CLOCK_SOURCE_SPLLDIV2=6U,
	CLOCK_SOURCE_LPO128=7U,
}ClockSource;

typedef enum{
	IRQ_DISABLE=0U,
	IRQ_ENABLE =1U,
}LPITINT_t;

typedef struct {
	ClockSource clksoure;
	uint8_t channel;
	uint32_t TVAL;
	LPITINT_t irq;
}LPITConfig;

void LPIT_Init(LPITConfig* LPIT);
void ClearFlag_LPIT(uint8_t chanel);
#endif /* LPIT_H_ */
