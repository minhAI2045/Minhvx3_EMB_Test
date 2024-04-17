#ifndef _PORT_H_
#define _PORT_H_

#include"S32K144.h"
#include <stdint.h>
#include<string.h>

typedef void(*CallBackType)(void);

typedef enum{
	PORTx_MUX_ANALOG =0U,
	PORTx_MUX_GPIO 	=1U,
	PORTx_MUX_ALT2 	=2U,
	PORTx_MUX_ALT3 	=3U,
	PORTx_MUX_ALT4 	=4U,
	PORTx_MUX_ALT5 	=5U,
	PORTx_MUX_ALT6 	=6U,
	PORTx_MUX_ALT7 	=7U,
//	/...

}PORTMUXTYPE;

typedef enum{
	PORT_PULL_DISABLED	=0U,
	PORT_PULL_DOWN	 	=2U,
	PORT_PULL_UP	 	=3U,
}PORTPULLTYPE;
typedef enum{
	PORT_INT_FALLING =10U,
	PORT_INT_DISABLE=0U,
	PORT_INT_RISING =9U,
	PORT_INT_EITHER =11U,

}PORTINTTYPE;
typedef struct {
	PORT_Type* PORTx;
	uint8_t pin;
	PORTMUXTYPE mux;
	PORTPULLTYPE pull;
	PORTINTTYPE interrupt;
	IRQn_Type IRQ;
	CallBackType callback;
}PortConfigType;

void myPORT_PinInit(PortConfigType* config );
void PORT_EXTI_Config (PortConfigType* config);
void PORT_EXTI_ClearFlag (PORT_Type* PORTx,uint8_t pinNumber);
void PORT_ClearFlag(PORT_Type* PORTx,uint8_t pinNumber);

#endif
