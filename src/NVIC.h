/*
 * NVIC.h
 *
 *  Created on: Apr 3, 2024
 *      Author: ADMIN
 */

#ifndef NVIC_H_
#define NVIC_H_
#include"S32K144.h"
#include <stdint.h>
#include<string.h>

typedef struct {
	IRQn_Type IRQn;
	uint8_t Piority;
}NVIC_Config_IRQ;

void NVIC_Set_IRQs(NVIC_Config_IRQ* config);
void NVIC_Set_Priority_IRQs(NVIC_Config_IRQ* NVIC_Config);

#endif /* NVIC_H_ */
