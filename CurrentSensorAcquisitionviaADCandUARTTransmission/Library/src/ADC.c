#include "../Include/ADC.h"

void ADC_Init(uint32_t channel, uint8_t mode)
{
	//Clock configuration
	IP_PCC->PCCn[PCC_PORTA_INDEX] |= PCC_PCCn_CGC_MASK; 						//Enable Clock PTA
	IP_PORTA->PCR[0] = PORT_PCR_MUX(0); 										// Disable Digital Mux PTA0 (SE0: analog)
	IP_SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV2(5); 									//  Enable FIRCDIV2/16
IP_PCC->PCCn[PCC_ADC0_INDEX] &= ~PCC_PCCn_CGC_MASK;								// Disable clock ADC0
	IP_PCC->PCCn[PCC_ADC0_INDEX]  = PCC_PCCn_PCS(3) | PCC_PCCn_CGC_MASK;		//Select FIRCDIV2, esable clock ADC0

	/* Calibration */
	IP_ADC0->SC3 = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3) | ADC_SC3_CAL_MASK;		//Average 32 samples to calibrate
	while ((IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0) {/*wait for calibration*/}
	(void)IP_ADC0->R[0]; 														/* Read to clear COCO flag and buffer */

	//Analog running: 12-bit, sample time
	IP_ADC0->CFG1 = ADC_CFG1_ADIV(0) | ADC_CFG1_MODE(1); 						// Clock/1, 12 bit conversion
	IP_ADC0->CFG2 = ADC_CFG2_SMPLTS(12);										//Waiting time to charge capacity before conversion is 12 clock
	IP_ADC0->SC2  = ADC_SC2_REFSEL(0);      									//default VREF
	IP_ADC0->SC3  = ADC_SC3_ADCO_MASK;   										// Continuous conversion
	IP_ADC0->SC3  = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3) | ADC_SC3_ADCO_MASK;	//Enable Average, 32 samples, continuous conversion

	if(mode == Normal_Mode)
	{
		// Enable interrupt ADC0
		IP_ADC0->SC1[0] = ADC_SC1_AIEN_MASK;
		//Enable ADC0 NVIC
		NVIC_clear_pending(ADC0_IRQn);
		NVIC_set_priority(ADC0_IRQn, 2);
		NVIC_enable_IRQ(ADC0_IRQn);
	}
	else
	{
		IP_ADC0->SC2 |= ADC_SC2_DMAEN_MASK; 									// Enable DMA
	}
	/* Restart ADC */
	IP_ADC0->SC1[0] &= ~ADC_SC1_ADCH_MASK;
	IP_ADC0->SC1[0] |= ADC_SC1_ADCH(channel);
}

void ADC0_IRQHandler(void)
{
	ADC0_raw_value = (uint32_t)(IP_ADC0->R[0] & 0xFFFFu);
}


