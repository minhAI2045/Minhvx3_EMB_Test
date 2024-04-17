/*
 * user.c
 *
 *  Created on: Mar 29, 2024
 *      Author: ADMIN
 */

#include <Middleware.h>
#include "device_registers.h"	/* include peripheral declarations S32K144 */
#define PWM_CLOCK_FREQ 62500

void Init_Port_UART(void)
{
	PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC(1U);
	PortConfigType Uart_RXcfg = {
		.PORTx=PORTC,
		.pin=UART1_RX,
		.mux=PORTx_MUX_ALT2,
		.pull=PORT_PULL_DISABLED,
		.interrupt= PORT_INT_DISABLE,
	};
	PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC(1U);
	PortConfigType Uart_TXcfg = {
		.PORTx=PORTC,
		.pin=UART1_TX,
		.mux=PORTx_MUX_ALT2,
		.pull=PORT_PULL_DISABLED,
		.interrupt= PORT_INT_DISABLE,
	};
	myPORT_PinInit(&Uart_RXcfg);
	myPORT_PinInit(&Uart_TXcfg);
}
void Init_button(void)
{
	PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC(1U);
	/*Init button1*/
	PortConfigType Button1cfg = {
		.PORTx=PORTC,
		.pin=Button1,
		.mux=PORTx_MUX_GPIO,
		.pull=PORT_PULL_DISABLED,
		.interrupt= PORT_INT_RISING,
		.IRQ=PORTC_IRQn,
	};
	GPIOConfigType Button1GPIO ={
		.PTx=PTC,
		.pin=Button1,
		.pinDirection=input,
	};
	NVIC_Config_IRQ NVICPortC ={
		.IRQn=PORTC_IRQn,
		.Piority=9,
	};
	myPORT_PinInit(&Button1cfg);
	myGPIO_Init(&Button1GPIO);

	/*Init button 2*/
	PortConfigType Button2cfg = {
		.PORTx=PORTC,
		.pin=Button2,
		.mux=PORTx_MUX_GPIO,
		.pull=PORT_PULL_DISABLED,
		.interrupt= PORT_INT_EITHER,
		.IRQ=PORTC_IRQn,
	};
	GPIOConfigType Button2GPIO ={
		.PTx=PTC,
		.pin=13,
		.pinDirection=input,
		};
	myPORT_PinInit(&Button2cfg);
	myGPIO_Init(&Button2GPIO);\

	/*Init button3*/
	PortConfigType Button3_cfg = {
				.PORTx=PORTC,
				.pin=Button3,
				.mux=PORTx_MUX_GPIO,
				.pull=PORT_PULL_DOWN,
				.interrupt= PORT_INT_RISING,
				.IRQ=PORTC_IRQn,
		};
		GPIOConfigType Button3_GPIO ={
				.PTx=PTC,
				.pin=Button3,
				.pinDirection=input,
			};
	myPORT_PinInit(&Button3_cfg);
	myGPIO_Init(&Button3_GPIO);
	NVIC_Set_IRQs(&NVICPortC);
}

void LED_Init(void)
{
	//Clock for portD
	PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC(1U);

	// Init RED LED PTD15
	PortConfigType RedLed = {
		.PORTx=PORTD,
		.pin=PTD15,
		.mux=PORTx_MUX_ALT2 ,
	};
//	GPIOConfigType RedLedGPIO ={
//		.PTx=PTD,
//		.pin=PTD15,
//		.pinDirection=output,
////	};
    myPORT_PinInit(&RedLed);
//	//myGPIO_Init(&RedLedGPIO);
//
//	// Init BLUE LED PTD0
//	PortConfigType Blueled = {
//		.PORTx=PORTD,
//		.pin=PTD0,
//		.mux=PORTx_MUX_GPIO,
//	};
//	GPIOConfigType BlueledGPIO ={
//		.PTx=PTD,
//		.pin=PTD0,
//		.pinDirection=output,
//	};
//	myPORT_PinInit(&Blueled);
//	myGPIO_Init(&BlueledGPIO);
//	// Init GREEN LED PTD16
//	PortConfigType Greenled = {
//		.PORTx=PORTD,
//		.pin=PTD16,
//		.mux=PORTx_MUX_GPIO,
//	};
//	GPIOConfigType GreenledGPIO ={
//		.PTx=PTD,
//		.pin=PTD16,
//		.pinDirection=output,
//	};
//	myPORT_PinInit(&Greenled);
//	myGPIO_Init(&GreenledGPIO);
}
void FTM0_PORT_init (void)
{
	//Clock for portD
	PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC(1U);

	/* Port D15: MUX = ALT2, FTM0CH0 */
	PortConfigType  Port_FTM0CH0= {
		.PORTx=PORTD,
		.pin=15,
		.mux=PORTx_MUX_ALT2,
	};
	myPORT_PinInit(&Port_FTM0CH0);
}
void FlexCAN_Init(void){
	initFlexcan();
	NVIC_Config_IRQ NVIC_CAN0 ={
			.IRQn=CAN0_ORed_0_15_MB_IRQn,
			.Piority=8,
		};
	NVIC_Set_IRQs(&NVIC_CAN0);
}
void FlexCan_Port_Init(void){
	// Init CAN0_TX, CAN0_RX
		PortConfigType CAN0_TX = {
			.PORTx=PORTE,
			.pin=5,
			.mux=PORTx_MUX_ALT5,
		};
		myPORT_PinInit(&CAN0_TX);

		PortConfigType CAN0_RX = {
			.PORTx=PORTE,
			.pin=4,
			.mux=PORTx_MUX_ALT5,
		};
		myPORT_PinInit(&CAN0_RX);
}
void LPIT_Timer_Init(uint8_t chanel, uint32_t tval_ch0)
{
	LPITConfig Set_lpit={
		.clksoure=CLOCK_SOURCE_SPLLDIV2,
		.channel =chanel,
		.TVAL=tval_ch0,
		.irq=IRQ_ENABLE,
	};
	LPIT_Init(&Set_lpit);
	if(Set_lpit.irq)
	{
		NVIC_Config_IRQ NVIC_LPIT_Chanl ={
			.IRQn=LPIT0_Ch0_IRQn+chanel,
			.Piority=10,
		};
		NVIC_Set_IRQs(&NVIC_LPIT_Chanl);
	}
}

void Init_UART(void)
{
	UARTConfig uartconfig={
		.baud=BaudRate9600,
		.parity=Parity_Disable,
		.numberBitData=Bit8Data,
	};
	LPUART1_init(&uartconfig);
}
void Enable_Clock(void)
{
	SOSC_init_8MHz();
	SPLL_init_160MHz();
}
void Blink_RGB(void)
{
	static volatile uint32_t statement = 0;
	// Turn off all LEDs
	PTD->PSOR |= (1u << PTD15) | (1u << PTD16) | (1u << PTD0);
	switch (statement % 3) {
	      case 0: // Red LED on
	          PTD->PCOR |= (1u << PTD15);
	          //PTD->PCOR |= GPIO_PCOR_PTCO(PTD15);
	          break;
	      case 1: // Green LED on
	          PTD->PCOR |= (1u << PTD16);
	          break;
	      case 2: // Blue LED on
	          PTD->PCOR |= (1u << PTD0);
	          break;
	 }
	 statement++; // Increment state
}
void receive_CAN_message(uint8_t buff_num,uint32_t id, uint8_t data) {
	CAN_RXINFO rxinfo = {
        .buff_num = buff_num,
        .id = id,
        .length = 1,
        .data = {data},
		.frt = CAN0->TIMER
    };
    can_rxmsg(&rxinfo);
}


void send_CAN_message(uint32_t id, uint8_t data) {
    CAN_TXINFO txinfo = {
        .buff_num = 0,
        .id = id,
        .length = 1,
        .data = {data}
    };
    can_txmsg(&txinfo);
}

void FTM_Init(int channel)
{
 	FTM_ConfigType Ftm_init = {
		.FTMx=FTM0,
		.FTM_Chanel=channel,
		.Clock_Source_FTM=CLOCK_FTM_SOURCE_SIRCDIV1,
		.Polarity=ACTIVE_HIGH,
		.Prescaler=7,			/* 8MHz /128 = 62.5kHz ->  ticks -> 1H		*/
		.PWM_Enable=true
	};
	FTMx_init(&Ftm_init);
}
void PWM_Init(int channel, int frequency, float dutyCycle)
{
	uint32_t modulo_value = (PWM_CLOCK_FREQ/frequency)-1;
	uint32_t compare_value = dutyCycle*(modulo_value+1)/100;
	if(modulo_value > 0 && modulo_value < 0xFFFFU)
	{
	PWM_ConfigType PWM_init=
	{
		.FTMx=FTM0,
		.PWM_Chanel=channel,
		.Pwm_Mode_Select=EDGE_ALIGNED_PWM,
		.Pwm_Edge_Level_Select=HIGH_TRUE_PULSES,
		.Modulo_Value=modulo_value,
		.CnV=compare_value
	};
	FTMx_CHx_PWM_init(&PWM_init);
	}
}






