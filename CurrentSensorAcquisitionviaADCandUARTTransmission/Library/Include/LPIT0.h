#ifndef INCLUDE_LPIT0_H_
#define INCLUDE_LPIT0_H_

#include "S32K144.h"

#include "Debounce.h"
#include "LPUART.h"
#include "NVIC_S32K144.h"

extern uint16_t volatile ADC0_raw_value;
extern Debounce_t debounceLogic;
extern ADCThreshold_t threshold;
extern bool is_overloaded;

void LPIT0_Init(uint32_t time_ms_CH0, uint32_t time_ms_CH1, uint32_t time_ms_CH2, uint32_t time_ms_CH3);
void LPIT0_Ch0_IRQHandler(void);
void LPIT0_Ch1_IRQHandler(void);
void LPIT0_Ch2_IRQHandler(void);
void LPIT0_Ch3_IRQHandler(void);

#endif /* INCLUDE_LPIT0_H_ */
