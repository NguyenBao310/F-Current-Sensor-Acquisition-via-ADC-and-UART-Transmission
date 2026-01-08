#include "../Include/SYS_CLOCK.h"

void SOSC_Init_8MHz()
{
	IP_SCG->SOSCDIV = 0x00000101; // SOSCDIV1 = 8MHz, SOSCFIV2 = 8MHz
	IP_SCG->SOSCCFG = 0x00000024; // check RM to understand
	while(IP_SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); // check LK bit = 0 -> unlocked to write
	IP_SCG->SOSCCSR = 0x00000001; // SOSCEN = 1 -> enable oscillator
	while(!(IP_SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); // wait for sys OSC clock valid
}

void SPLL_Init_160MHz()
{
	while(IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); // check LK bit = 0 -> unlocked to write
	IP_SCG->SPLLCSR = 0x00000000;
	IP_SCG->SPLLDIV = 0x00000302; // SPLLDIV1 = 80MHz, SPLLDIV2 = 40MHz
	IP_SCG->SPLLCFG = 0x00180000; // SPLL_CLK = SOSC_CLK*(MULT+16)/2(PREDIV+1)
	while(IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); // check LK bit = 0 -> unlocked to write
	IP_SCG->SPLLCSR = 0x00000001; // SPLLEN = 1 -> enable SPLL
	while(!(IP_SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); // wait for SPLL clock valid
}

void NormalRUNmode_80MHz()
{
	IP_SCG->RCCR = SCG_RCCR_SCS(6) | SCG_RCCR_DIVCORE(0b01) | SCG_RCCR_DIVBUS(0b01) | SCG_RCCR_DIVSLOW(0b10);
	while(((IP_SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT) != 6); // wait for sys clk src = SPLL
}
