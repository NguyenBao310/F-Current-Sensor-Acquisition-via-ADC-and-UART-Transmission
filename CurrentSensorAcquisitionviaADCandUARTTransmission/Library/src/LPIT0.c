#include "../Include/LPIT0.h"

void LPIT0_Init(uint32_t time_ms_CH0, uint32_t time_ms_CH1, uint32_t time_ms_CH2, uint32_t time_ms_CH3)
{
	/* Disable clock to LPIT0 */
	IP_PCC->PCCn[PCC_LPIT_INDEX] = 0;
	/* Set clock source as SPLL div2 */
	IP_PCC->PCCn[PCC_LPIT_INDEX] = PCC_PCCn_PCS(6);
	/* Enable clock to LPIT0 */
	IP_PCC->PCCn[PCC_LPIT_INDEX] |= (1<<30);
	/* Timer can run in Debug mode */
	IP_LPIT0->MCR |= (1<<3);
	/* Enable clock to LPIT0 */
	IP_LPIT0->MCR |= (1<<0);
	/* Enable LPIT0 CH0, CH1, CH2 interrupt */
	IP_LPIT0->MIER |= (1<<0);
	IP_LPIT0->MIER |= (1<<1);
	IP_LPIT0->MIER |= (1<<2);
	IP_LPIT0->MIER |= (1<<3);
	/* Max counting value */
	IP_LPIT0->TMR[0].TVAL = (time_ms_CH0*40000);
	IP_LPIT0->TMR[1].TVAL = (time_ms_CH1*40000);
	IP_LPIT0->TMR[2].TVAL = (time_ms_CH2*40000);
	IP_LPIT0->TMR[3].TVAL = (time_ms_CH3*40000);
	/* Enable counter of LPIT CH0, CH1, CH3 */
	IP_LPIT0->TMR[0].TCTRL |= (1<<0);
	IP_LPIT0->TMR[1].TCTRL |= (1<<0);
	IP_LPIT0->TMR[2].TCTRL |= (1<<0);
	IP_LPIT0->TMR[3].TCTRL |= (1<<0);
	/* Enable counter of LPIT CH0, CH1, CH3 */
	IP_LPIT0->SETTEN |= (1<<0);
	IP_LPIT0->SETTEN |= (1<<1);
	IP_LPIT0->SETTEN |= (1<<2);
	IP_LPIT0->SETTEN |= (1<<3);
	/*  */
	NVIC_enable_IRQ(LPIT0_Ch0_IRQn);
	NVIC_clear_pending(LPIT0_Ch0_IRQn);
	NVIC_set_priority(LPIT0_Ch0_IRQn, priority_0);
	NVIC_enable_IRQ(LPIT0_Ch1_IRQn);
	NVIC_clear_pending(LPIT0_Ch1_IRQn);
	NVIC_set_priority(LPIT0_Ch1_IRQn, priority_0);
	NVIC_enable_IRQ(LPIT0_Ch2_IRQn);
	NVIC_clear_pending(LPIT0_Ch2_IRQn);
	NVIC_set_priority(LPIT0_Ch2_IRQn, priority_0);
	NVIC_enable_IRQ(LPIT0_Ch3_IRQn);
	NVIC_clear_pending(LPIT0_Ch3_IRQn);
	NVIC_set_priority(LPIT0_Ch3_IRQn, priority_0);
}

void LPIT0_Ch0_IRQHandler(void)
{
	IP_LPIT0->MSR |= (1<<0);
	is_overloaded = DebounceHandler(&debounceLogic, ADC0_raw_value, threshold);
}

void LPIT0_Ch1_IRQHandler(void)
{
	IP_LPIT0->MSR |= (1<<1);
	float temp = ConvertIntoCurrent(ACS712_30A, ADC0_raw_value);
	char s[50];
	sprintf(s, "Current %.3fA\t---\tVoltage %dmV\t---\tADC %d\n\r", temp, ADC0_raw_value*5000/0xFFF, ADC0_raw_value);
	if(is_overloaded){
		alarmRedLed();
		LPUART1_Transmit_Str("[OVERLOAD] ");
	} else {
		alarmGreenLed();
		LPUART1_Transmit_Str("[   OK   ] ");
	}
	LPUART1_Transmit_Str(s);
}

void LPIT0_Ch2_IRQHandler(void)
{
	IP_LPIT0->MSR |= (1<<2);
}

void LPIT0_Ch3_IRQHandler(void)
{
	IP_LPIT0->MSR |= (1<<3);
}
