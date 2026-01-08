#include "../Include/LPUART.h"

void LPUART1_PORT_Init()
{
	IP_PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK; 								// enable clock for port c
	IP_PORTC->PCR[6] |= PORT_PCR_MUX(2); 												// ALT2
	IP_PORTC->PCR[7] |= PORT_PCR_MUX(2); 												// ALT2
}

void LPUART1_Init(uint32_t baudrateSetting)
{
	IP_PCC->PCCn[PCC_LPUART1_INDEX] &= ~PCC_PCCn_CGC_MASK; 								// disabled clock for config
	IP_PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_PCS(0b001) | PCC_PCCn_CGC_MASK; 		// clock option = 001 -> SOSCDIV2_CLK
	switch(baudrateSetting)
	{
	case 9600:
		baudrateSetting = 0x0F000034;
		break;
	case 115200:
		baudrateSetting = 0x0F000004;
		break;
	}
	IP_LPUART1->BAUD = baudrateSetting;
	IP_LPUART1->CTRL = 0x000C0000; 														// 8-bit, No Parity, 1 Stop bit, RE=1, TE=1
}

void LPUART1_Transmit_Char(char message)
{
	while((IP_LPUART1->STAT & LPUART_STAT_TDRE_MASK) >> LPUART_STAT_TDRE_SHIFT == 0); 	// wait for transmit buffer to be empty
	IP_LPUART1->DATA = message; 														//  give data
}

void LPUART1_Transmit_Str(char *s){
	while(*s){
		LPUART1_Transmit_Char(*s);
		s++;
	}
}

char LPUART1_Receive()
{
	char message;
	while((IP_LPUART1->STAT & LPUART_STAT_RDRF_MASK) >> LPUART_STAT_RDRF_SHIFT == 0); 	// wait for receive buffer to be full
	message = IP_LPUART1->DATA; 														// take data
	return message;
}

void LPUART1_Transmit_Data(uint32_t value)
{
	char bufferData[100];
	sprintf(bufferData, "%lu", value);
	uint32_t i = 0;
	while(bufferData[i] != '\0')
	{
		LPUART1_Transmit_Char(bufferData[i]);
		i++;
	}
	LPUART1_Transmit_Char(0x0A);
	LPUART1_Transmit_Char(0x0D);
}
