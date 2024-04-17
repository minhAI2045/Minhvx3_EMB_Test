/*
 * user.h
 *
 *  Created on: Mar 29, 2024
 *      Author: ADMIN
 */

#ifndef MIDDLEWARE_H_
#define MIDDLEWARE_H_

#include "GPIO.h"
#include "NVIC.h"
#include "PORT.h"
#include "LPIT.h"
#include "clocks_and_modes.h"
#include "LUART.h"
#include "FlexCAN.h"
#include "FTM.h"

#define Button1 12
#define Button2 13
#define Button3 6
#define PTD0 	0       // BLUE_LED
#define PTD15   15		// RED_LED
#define PTD16   16  	// GREEN_LED
#define UART1_RX 6
#define UART1_TX 7

#define	channel_0 0
#define	channel_1 1
#define	channel_2 3
#define	channel_3 3

void Init_Port_UART(void);
void Init_button(void);
void LED_Init(void);
void LPIT_Timer_Init(uint8_t chanel, uint32_t tval_ch0);
void Init_UART(void);
void Enable_Clock(void);
void Blink_RGB(void);
void send_CAN_message(uint32_t id, uint8_t data);
void receive_CAN_message(uint8_t buff_num,uint32_t id, uint8_t data);
void FlexCAN_Init(void);
void FlexCan_Port_Init(void);
void FTM0_PORT_init (void);
void FTM_Init(int channel);
void PWM_Init(int channel, int frequency, float dutyCycle);

#endif /* MIDDLEWARE_H_ */
