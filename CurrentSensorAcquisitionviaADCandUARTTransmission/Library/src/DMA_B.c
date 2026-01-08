#include "../Include/DMA_B.h"

void DMA_ADC_Init1(void)
{
	IP_PCC->PCCn[PCC_DMAMUX_INDEX] |= PCC_PCCn_CGC_MASK; 						/* Enable clock for DMAMUX */
	IP_DMAMUX->CHCFG[0] |= DMAMUX_CHCFG_SOURCE(42) | DMAMUX_CHCFG_ENBL_MASK; 	/* Choose source for DMA */
}

void DMA_ADC_Config1(uint16_t volatile *Value)
{
	IP_DMA->TCD[0].SADDR = DMA_TCD_SADDR_SADDR(&(IP_ADC0->R[0])); 				/* Source address */
	IP_DMA->TCD[0].SOFF = DMA_TCD_SOFF_SOFF(0);									/* Src adr add 0 byte after transfer */
	IP_DMA->TCD[0].ATTR = DMA_TCD_ATTR_SMOD(0)  |								/* Src modulo not used */
						  DMA_TCD_ATTR_SSIZE(1) |								/* Src read 2 bytes per transfer */
						  DMA_TCD_ATTR_DMOD(0) |								/* Dest modulo not used */
						  DMA_TCD_ATTR_DSIZE(1) ;								/* Dest read 2 bytes per transfer */
	IP_DMA->TCD[0].NBYTES.MLNO = DMA_TCD_NBYTES_MLNO_NBYTES(2); 				/* Transfer 2 byte/mini loop */
	IP_DMA->TCD[0].SLAST = DMA_TCD_SLAST_SLAST(0);								/* Src adr no change after a major loop */
	IP_DMA->TCD[0].DADDR = DMA_TCD_SADDR_SADDR((uint32_t) Value); 				/* Dest */
	IP_DMA->TCD[0].DOFF = DMA_TCD_DOFF_DOFF(0); 								/* Dest adr add 0 byte after transfer */
	IP_DMA->TCD[0].CITER.ELINKNO = DMA_TCD_CITER_ELINKNO_CITER(1) | 			/* 1 minor loop */
								   DMA_TCD_CITER_ELINKNO_ELINK(0); 				/* No minor loop channel link */
	IP_DMA->TCD[0].DLASTSGA = DMA_TCD_DLASTSGA_DLASTSGA(0); 					/* No change dest after major loop */
	IP_DMA->TCD[0].CSR = DMA_TCD_CSR_START(0) 	 | 								/* Clear START flag */
						 DMA_TCD_CSR_INTMAJOR(0) | 								/* No IRQ after major loop */
						 DMA_TCD_CSR_INTHALF(0)  | 								/* No IRQ after 1/2 major loop */
						 DMA_TCD_CSR_DREQ(0)	 | 								/* Disable channel after major loop */
						 DMA_TCD_CSR_ESG(0)      | 								/* No IRQ after major loop */
						 DMA_TCD_CSR_MAJORELINK(0) |							/* Disable Scatter Gather */
						 DMA_TCD_CSR_ACTIVE(0)	 | 								/* No IRQ after major loop */
						 DMA_TCD_CSR_DONE(0)	 | 								/* Clear DONE flag */
						 DMA_TCD_CSR_MAJORLINKCH(0) | 							/* No channel-to-channel linking */
						 DMA_TCD_CSR_BWC(0); 									/* No eDMA stalls */
	IP_DMA->TCD[0].BITER.ELINKNO = DMA_TCD_BITER_ELINKNO_BITER(1) | 			/* Initial iteration count */
			   	   	   	   	   	   DMA_TCD_BITER_ELINKNO_ELINK(0); 				/* No minor loop channel link */
	IP_DMA->SERQ = DMA_SERQ_SERQ(0);
}

