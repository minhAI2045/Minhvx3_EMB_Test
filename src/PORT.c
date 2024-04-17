#include "Port.h"
#include "NVIC.h"
static CallBackType PortCDCallBack =NULL;
void myPORT_PinInit(PortConfigType* config )
{
	if (config != NULL && config->PORTx != NULL)
	    {
		//MUX
			config->PORTx->PCR[config->pin]&= ~PORT_PCR_MUX_MASK;
			if ( PORTx_MUX_ANALOG != config->mux )
			{
				config->PORTx->PCR[config->pin] |= PORT_PCR_MUX(config->mux);
			}
			//Pull
			if(config->pull==0)
			{
				config->PORTx->PCR[config->pin] &= ~PORT_PCR_PE_MASK;
				config->PORTx->PCR[config->pin] &= ~PORT_PCR_PS_MASK;
			}
			else if (config->pull==1)
			{
				config->PORTx->PCR[config->pin] |= PORT_PCR_PE(1U);
				config->PORTx->PCR[config->pin] &= ~PORT_PCR_PS_MASK;
			}
			else if (config->pull==2)
			{
				config->PORTx->PCR[config->pin] |= PORT_PCR_PE(1U);
				config->PORTx->PCR[config->pin] |= PORT_PCR_PS(1U);
			}
			if(PORT_INT_DISABLE != config->interrupt)
			{
			config->PORTx->PCR[config->pin] |= PORT_PCR_IRQC(config->interrupt);
			}
	    }
}

void PORT_EXTI_Config (PortConfigType* config){
	if (config != NULL && config->PORTx != NULL)
	{
		config->PORTx->PCR[config->pin] &= ~PORT_PCR_IRQC_MASK;
		if(PORT_INT_DISABLE != config->interrupt)
		{

			//NVIC_Set_IRQs(config);//Enable interrupt

			config->PORTx->PCR[config->pin] |= PORT_PCR_IRQC(config->interrupt);//(Falling/Rising)
			//Assign callback function
			if(PORTC==config->PORTx||PORTD==config->PORTx)
			{
				PortCDCallBack = config->callback;
			}
		}
	}
}

void PORT_ClearFlag(PORT_Type* PORTx,uint8_t pinNumber)
{
	if (PORTx != NULL && pinNumber < PORT_PCR_COUNT)
	{
		PORTx->ISFR |= (uint32_t)(1u << pinNumber); /* Clear interrupt flag */
	}
}
