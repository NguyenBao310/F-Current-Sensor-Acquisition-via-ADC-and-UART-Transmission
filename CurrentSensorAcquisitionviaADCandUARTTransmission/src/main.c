#include "S32K144.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "../Library/Include/ADC.h"
#include "../Library/Include/Alarm.h"
#include "../Library/Include/Debounce.h"
#include "../Library/Include/DMA_B.h"
#include "../Library/Include/DMA.h"
#include "../Library/Include/LPIT0.h"
#include "../Library/Include/LPUART.h"
#include "../Library/Include/NVIC_S32K144.h"
#include "../Library/Include/SYS_CLOCK.h"
#include "../Library/Include/utils.h"

uint16_t volatile ADC0_raw_value = 0;
Debounce_t debounceLogic = {.counter = 0, .qualifyLimit = 10, .disqualifyLimit = 0, .faultFlag = false};
ADCThreshold_t threshold;
bool is_overloaded = false;

int main (void)
{
	SOSC_Init_8MHz();
	SPLL_Init_160MHz();
	NormalRUNmode_80MHz();
	alarmInit();
	LPUART1_PORT_Init();
	LPUART1_Init(9600);
	LPIT0_Init(100, 500, 10000, 10000);
	DMA_ADC_Init1();
	DMA_ADC_Config1(&ADC0_raw_value);
	ADC_Init(12, DMA_Mode);
	threshold =  ADCThreshold(ACS712_30A, 15);

	while(1);
}
