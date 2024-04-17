#include "NVIC.h"

void NVIC_Set_IRQs(NVIC_Config_IRQ* config)
{
	S32_NVIC->ISER[config->IRQn/32] |= (uint32_t)(1u<<(config->IRQn%32)); /* Enable IRQ */
}
void NVIC_Set_Priority_IRQs(NVIC_Config_IRQ* NVIC_Config)
{
	S32_NVIC->IP[NVIC_Config->IRQn] |=(uint8_t)(((((uint32_t)NVIC_Config->Piority) << 4u)) & 0xFFuL); /* Set priority */
}
