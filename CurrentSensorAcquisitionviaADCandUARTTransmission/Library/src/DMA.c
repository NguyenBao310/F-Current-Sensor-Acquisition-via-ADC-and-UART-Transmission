#include "../Include/DMA.h"

volatile uint16_t g_adc_buf[ADC_BUFFER_LEN];
volatile uint16_t g_avg_latest;
volatile uint8_t  g_avg_done;

uint32_t avg_32(void)
{
    uint32_t sum = 0;
    for (int i = 0; i < ADC_BUFFER_LEN; ++i)
        sum += (uint32_t)(g_adc_buf[i] & 0xFFFFu);
    return (sum / ADC_BUFFER_LEN);
}

void DMA_ADC_Init(uint16_t *value)
{
    /* DMAMUX + DMA clock */
    IP_PCC->PCCn[PCC_DMAMUX_INDEX] |= PCC_PCCn_CGC_MASK; 	//Enable CLK DMAMUX
    IP_SIM->PLATCGC |= SIM_PLATCGC_CGCDMA_MASK;				//Enable CLK eDMA

    /* DMAMUX */
    IP_DMAMUX->CHCFG[DMA_CH] = 0; 							//Reset DMAMUX->CHCFG
    IP_DMAMUX->CHCFG[DMA_CH] =
        DMAMUX_CHCFG_SOURCE(DMAMUX_SRC_ADC0_COCO) |			//Request source
        DMAMUX_CHCFG_ENBL_MASK;								//Enable DMAMUX

    /* TCD */
    IP_DMA->TCD[DMA_CH].SADDR = ADC_Data_Address;			//Source Address
    IP_DMA->TCD[DMA_CH].SOFF  = 0;							//Address offset minor loop
    IP_DMA->TCD[DMA_CH].ATTR  = DMA_TCD_ATTR_SSIZE(1) | 	//Read 16-bit
                                DMA_TCD_ATTR_DSIZE(1);  	//Write 16-bit
    IP_DMA->TCD[DMA_CH].NBYTES.MLNO = 2;                	//2 byte transfer minor loop
    IP_DMA->TCD[DMA_CH].SLAST = 0;                      	//Source address offset major loop

    IP_DMA->TCD[DMA_CH].DADDR = (uint32_t)value;			//Destination Address
    IP_DMA->TCD[DMA_CH].DOFF  = 0;							//Destination Address offset minor loop

    IP_DMA->TCD[DMA_CH].CITER.ELINKNO =
        DMA_TCD_CITER_ELINKNO_CITER(ADC_BUFFER_LEN);		//current number of minor loop
    IP_DMA->TCD[DMA_CH].BITER.ELINKNO =
        DMA_TCD_BITER_ELINKNO_BITER(ADC_BUFFER_LEN);		//Beginning number of minor loop

    IP_DMA->TCD[DMA_CH].DLASTSGA = 0;						//Destination address offset major loop

    IP_DMA->TCD[DMA_CH].CSR =
        DMA_TCD_CSR_INTMAJOR(1) |							//Enable interrupt DMA
        DMA_TCD_CSR_DREQ(0);								//Keep ERQ = 1 after major loop complete

    /* Enable DMA channel */
    IP_DMA->ERQ |= (1u << DMA_CH);

    //Enable NVIC DMA
    NVIC_clear_pending(DMA0_IRQn);
	NVIC_set_priority(DMA0_IRQn, 2); 						//optional
    NVIC_enable_IRQ(DMA0_IRQn);
}

void DMA0_IRQHandler(void)
{
    IP_DMA->CINT = DMA_CINT_CINT(DMA_CH);
}

