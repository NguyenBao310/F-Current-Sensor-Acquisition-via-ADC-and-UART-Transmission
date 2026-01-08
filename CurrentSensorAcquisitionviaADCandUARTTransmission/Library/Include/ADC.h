#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

#include "S32K144.h"
#include <stdio.h>
#include <stdint.h>

#include "NVIC_S32K144.h"

#define DMA_Mode 	(1)
#define Normal_Mode (0)

extern uint16_t volatile ADC0_raw_value;

void ADC_Init(uint32_t channel, uint8_t mode);

#endif /* INCLUDE_ADC_H_ */
