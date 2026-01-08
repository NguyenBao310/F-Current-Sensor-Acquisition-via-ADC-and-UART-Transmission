#ifndef INCLUDE_DMA_H_
#define INCLUDE_DMA_H_

#include "S32K144.h"
#include <stdint.h>

#include "NVIC_S32K144.h"

#define ADC_BUFFER_LEN   		(32)
#define DMA_CH               	(0)
#define DMAMUX_SRC_ADC0_COCO 	(42)
#define ADC_Data_Address 		((uint32_t)&IP_ADC0->R[0])

void DMA_ADC_Init(uint16_t *value);
void DMA0_IRQHandler(void);
uint32_t avg_32(void);

#endif /* INCLUDE_DMA_H_ */
