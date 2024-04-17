#include "device_registers.h"	/* include peripheral declarations S32K144 */
#include "LUART.h"

void LPUART1_init(UARTConfig* config)  /* Init. summary: 9600 baud, 1 stop bit, 8 bit format, no parity */
{
	PCC->PCCn[PCC_LPUART1_INDEX] &= ~PCC_PCCn_CGC_MASK;    /* Ensure clk disabled for config */

	PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_PCS(0b110)    /* Clock Src = 2 (SPLLDIV2_CLK) */
                            	 |  PCC_PCCn_CGC_MASK;     /* Enable clock for LPUART1 regs */

	LPUART1->BAUD = LPUART_BAUD_SBR(config->baud)  	/* Initialize for 9600 baud, 1 stop: */
                	|LPUART_BAUD_OSR(15);
											/* OSR=15: Over sampling ratio = 15+1=16 */
											/* SBNS=0: One stop bit */
											/* BOTHEDGE=0: receiver samples only on rising edge */
											/* M10=0: Rx and Tx use 7 to 9 bit data characters */
											/* RESYNCDIS=0: Resync during rec'd data word supported */
											/* LBKDIE, RXEDGIE=0: interrupts disable */
											/* TDMAE, RDMAE, TDMAE=0: DMA requests disabled */
											/* MAEN1, MAEN2,  MATCFG=0: Match disabled */
	LPUART1->CTRL =	LPUART_CTRL_RE_MASK
					|LPUART_CTRL_TE_MASK;
												/* Enable transmitter & receiver, no parity, 8 bit char: */

	if(config->parity!=Parity_Disable)
	{
		if(config->parity==Odd_parity)
		{
			LPUART1->CTRL &=(uint32_t)(~(1U));
		}
		if(config->parity==Even_parity)
		{
			LPUART1->CTRL |=(uint32_t)(1U);
		}
		LPUART1->CTRL |= LPUART_CTRL_PE(1);
	}
	if(config->numberBitData)
	{
		LPUART1->CTRL |= LPUART_CTRL_M(1U);
	}
}
void LPUART1_transmit_char(char send) {    /* Function to Transmit single Char */
	while((LPUART1->STAT & LPUART_STAT_TDRE_MASK)>>LPUART_STAT_TDRE_SHIFT==0);
	/* Wait for transmit buffer to be empty */
	LPUART1->DATA=send;              /* Send data */
}

void LPUART1_transmit_string(char data_string[])  {  /* Function to Transmit whole string */
	uint32_t i=0;
	while(data_string[i] != '\0')  {           /* Send chars one at a time */
		LPUART1_transmit_char(data_string[i]);
		i++;
	}
}

char LPUART1_receive_char(void) {    /* Function to Receive single Char */
	char receive;
	while((LPUART1->STAT & LPUART_STAT_RDRF_MASK)>>LPUART_STAT_RDRF_SHIFT==0);
	/* Wait for received buffer to be full */
	receive= LPUART1->DATA;            /* Read received data*/
	return receive;
}

void LPUART1_receive_and_echo_char(void)  {  /* Function to echo received char back */
	char send = LPUART1_receive_char();        /* Receive Char */
	LPUART1_transmit_char(send);               /* Transmit same char back to the sender */
	LPUART1_transmit_char('\n');               /* New line */
	LPUART1_transmit_char('\r');               /* Return */
}
