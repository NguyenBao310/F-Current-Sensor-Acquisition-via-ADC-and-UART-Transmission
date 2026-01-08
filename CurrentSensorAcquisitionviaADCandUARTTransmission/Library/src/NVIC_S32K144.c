#include "../Include/NVIC_S32K144.h"

void NVIC_enable_IRQ(uint32_t IRQ_id)
{
    uint32_t reg = IRQ_id / 32;
    uint32_t bit = IRQ_id % 32;
    NVIC->ISER[reg] = (1u << bit);
}

void NVIC_disable_IRQ(uint32_t IRQ_id)
{
    uint32_t reg = IRQ_id / 32;
    uint32_t bit = IRQ_id % 32;
    NVIC->ICER[reg] = (1u << bit);
}

void NVIC_set_pending(uint32_t IRQ_id)
{
    uint32_t reg = IRQ_id / 32;
    uint32_t bit = IRQ_id % 32;
    NVIC->ISPR[reg] = (1u << bit);
}

void NVIC_clear_pending(uint32_t IRQ_id)
{
    uint32_t reg = IRQ_id / 32;
    uint32_t bit = IRQ_id % 32;
    NVIC->ICPR[reg] = (1u << bit);
}

void NVIC_set_priority(uint32_t IRQ_id, IRQ_priority priority)
{
	uint32_t reg = IRQ_id / 4;
	uint32_t bit_field = 8 * (IRQ_id % 4) + 4;
    NVIC->IPR[reg] = (priority << bit_field);
}

void NVIC_enable_global_irq(void)
{
	__asm volatile ("cpsie i" : : : "memory");
}
