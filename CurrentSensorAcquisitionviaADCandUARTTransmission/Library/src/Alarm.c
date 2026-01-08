#include "../Include/Alarm.h"

/* Alarm functions */
void alarmInit()
{
	IP_PCC->PCCn[PCC_PORTD_INDEX] &= ~PCC_PCCn_CGC_MASK; 	// unable clock port d
	IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK; 	// enable clock port d

	IP_PORTD->PCR[15] &= ~(7<<8); 							// clear mode mux
	IP_PORTD->PCR[16] &= ~(7<<8); 							// clear mode mux

	IP_PORTD->PCR[15] |= PORT_PCR_MUX(1); 					// set GPIO
	IP_PORTD->PCR[16] |= PORT_PCR_MUX(1); 					// set GPIO

	IP_PTD->PDDR |= (1<<15)|(1<<16); 						// set output mode

	IP_PTD->PSOR |= (1<<15)|(1<<16); 						// turn off led (active low)
}

void alarmBuzzer()
{

}

void alarmRedLed()
{
	IP_PTD->PSOR |= 0xFFFFFFFF; 							// turn off all led
	IP_PTD->PCOR |= (1<<15); 								// turn on red led
}

void alarmGreenLed()
{
	IP_PTD->PSOR |= 0xFFFFFFFF; 							// turn off all led
	IP_PTD->PCOR |= (1<<16); 								// turn on green led
}
