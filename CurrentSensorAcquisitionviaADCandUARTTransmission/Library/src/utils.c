#include "../Include/utils.h"

/* Delay functions */
void delay_ms(uint32_t delayTime)
{
	for(int i=0; i<(delayTime*4800); i++); // using 48MHz clock
}

void delay_s (uint32_t delayTime)
{
	for(int i=0; i<(delayTime); i++)
	{
		delay_ms(1000);
	}
}

