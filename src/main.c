
/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * NXP Confidential. This software is owned or controlled by NXP and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */
/*
Description:
* ==============================================================================================================
 */


#include "Middleware.h"
#include "sdk_project_config.h"
#include "clocks_and_modes.h"
#include "stdio.h"
#include "PORT.h"
#include "FTM.h"


volatile uint32_t led_stop=0;

volatile int32_t counter = 10;
volatile uint32_t tval_ch0 = 40000000;
volatile int32_t Duty_cycle = 50;
char transmit_data[128];


void WDOG_disable (void){
	WDOG->CNT=0xD928C520; 	/*Unlock watchdog*/
	WDOG->TOVAL=0x0000FFFF; /*Maximum timeout value*/
	WDOG->CS = 0x00002100; 	/*Disable watchdog*/
}


void LPIT0_Ch0_IRQHandler(void)
{
	ClearFlag_LPIT(channel_0); 							/* Clear channel 0 interrupt flag */
	sprintf(transmit_data, "Duty cycle: %ld\r\n",Duty_cycle/10 );             /*[SRS_05] */
	LPUART1_transmit_string(transmit_data);    			/* Transmit char string */
}


void LPIT0_Ch1_IRQHandler(void)
{
	ClearFlag_LPIT(channel_1); 					/* Clear channel 1 interrupt flag */
	send_CAN_message(0xA0,0X01);			    /*SRS_8*/
}

void remain_duty_cycle(int32_t duty_cycle){
	if(duty_cycle>100)
		{duty_cycle =100;}
	else if(duty_cycle<0)
		{duty_cycle= 0;}

}
void PORTC_IRQHandler(void) {
	if(PORTC->ISFR & (1u<<Button1))
	{
		PORT_ClearFlag(PORTC,Button1); 			/* Clear PORTC interrupt flag */
		Duty_cycle+=10;							/*[SRS_02] */
												/*increase the duty cycle by 10%*/
		remain_duty_cycle(Duty_cycle);			/*[SRS_04] */
		PWM_Init(0, 2000, Duty_cycle);
		counter++;								/*increase the counter variable value by 1*/
	}
	if(PORTC->ISFR & (1u<<Button2))
	{
		PORT_ClearFlag(PORTC,Button2); 			/* Clear interrupt flag */
		Duty_cycle-=10;							/*[SRS_03] */
												/* decrease the duty cycle by 10%*/
		remain_duty_cycle(Duty_cycle);			/*[SRS_04] */
		PWM_Init(0, 2000, Duty_cycle);
		counter--;								/*decrease the counter variable value by 1*/
	}
	if(PORTC->ISFR & (1u<<Button3))
	{
		PORT_ClearFlag(PORTC,Button3); 			/* Clear interrupt flag */
		Duty_cycle=50;
		PWM_Init(0, 4000, Duty_cycle);  		/*SRS_6 */
												/* init PWM chanel 0 frequency =4000hz, dutyCycle =50%*/ /*[SRS_01] */
		}
}

void CAN0_ORed_0_15_MB_IRQHandler(void){
	if(can_get_buff_flag(4)){
		can_clear_buff_flag(4);               	/* Clear the IFLAG bit. */
		receive_CAN_message(4,0xC0, 0x01);      /*Reads CAN message from RX message buffer 4 , ID 0xC0, data 0x01*/
	    FTM0_stop_counter();					/*SRS_9*/
	    										/* Stop PWM 0 */
	}
	if(can_get_buff_flag(5)){
	    can_clear_buff_flag(5);					/* Clear the IFLAG bit. */
	    receive_CAN_message(5,0xD0, 0x01);		/*Reads CAN message from RX message buffer 5 , ID 0xD0, data 0x01*/
	    FTM0_start_counter();					/*SRS_10*/
	    										/* Start PWM 0 */
	}
}

int main(void)
{
	WDOG_disable();
	Enable_Clock(); 						/* Enable clock SPLLDIV2_CLK source 40 Mhz */
	Init_button(); 							/* Initialize Button1 as input and IRQ on rising edge,
											//Button2 as input  IRQ on either edge  */
											//Button3 as input  IRQ on rising edge */
	FlexCAN_Init();         				/* Initializes the CAN module */
	FlexCan_Port_Init();					/* Initializes TX, RX */

	//Init_Port_UART(); 						/* Configure ports TX ,RX */
	Init_UART(); 							/* Initialize LPUART 9600*/

	FTM0_PORT_init();
	FTM_Init(0);							/* init FTM0 chanel 0 */
	PWM_Init(0, 2000, Duty_cycle);  		/*[SRS_01] */
											/* init PWM chanel 0 frequency =2000hz, dutyCycle =50%*/
	FTM0_start_counter();

	LPIT_Timer_Init(channel_0,tval_ch0);    /* Timer Channel 0 : 40M hz/40M hz = 1000ms period */
	LPIT_Timer_Init(channel_1,tval_ch0);    /* Timer Channel 1 : 40M hz/40M hz = 1000ms period */


	if(counter>=20)
	{
		can_rxbuff_init(4,0xC0);
	}
	else if(counter<5)
	{
		can_rxbuff_init(5,0xD0);
	}

    while (1)
    {
    }
	return 0;
}




