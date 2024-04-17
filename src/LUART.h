/*
 * LUART.h
 *
 *  Created on: Apr 7, 2024
 *      Author: ADMIN
 */

#ifndef LUART_H_
#define LUART_H_

typedef enum{
	CLOCK_UART_SOURCE_DISABLED=0U,
	CLOCK_UART_SOURCE_SOSCDIV2=1U,
	CLOCK_UART_SOURCE_SIRCDIV2=2U,
	CLOCK_UART_SOURCE_FIRCDIV2=3U,
	CLOCK_UART_SOURCE_SPLLDIV2=6U,
}ClockSourceUart;

typedef enum{
	BaudRate2400=65U,
	BaudRate4800=130U,
	BaudRate9600=260U,
	BaudRate19200=520U,
	BaudRate38400=1040U,
}BaudRate;

typedef enum{
	Odd_parity=0U,
	Even_parity=1U,
	Parity_Disable=2U,
}Parity;

typedef enum{
	Bit8Data=0U,
	Bit9Data=1U,
}NumberBitData;

typedef struct {
	BaudRate baud;
	Parity parity;
	NumberBitData numberBitData;
}UARTConfig;

void LPUART1_init(UARTConfig* config);
void LPUART1_transmit_char(char send);
void LPUART1_transmit_string(char data_string[]);
char LPUART1_receive_char(void);
void LPUART1_receive_and_echo_char(void);

#endif /* LUART_H_ */
