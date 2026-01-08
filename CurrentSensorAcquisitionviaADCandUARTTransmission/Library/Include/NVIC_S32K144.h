#ifndef INCLUDE_NVIC_S32K144_H_
#define INCLUDE_NVIC_S32K144_H_

#include <stdint.h>

typedef enum
{
    priority_0, /* Highest */
    priority_1,
    priority_2,
    priority_3,
    priority_4,
    priority_5,
    priority_6,
    priority_7,
    priority_8,
    priority_9,
    priority_10,
    priority_11,
    priority_12,
    priority_13,
    priority_14,
    priority_15 /* Lowest */
} IRQ_priority;

typedef struct
{
    volatile uint32_t CPUID;          	/* 0xE000E000: CPUID Base Register */
    volatile uint32_t ICTR;      		/* 0xE000E004: reserved/ICTR */
    uint32_t RESERVED1[62];
    volatile uint32_t ISER[8];        	/* 0xE000E100 - 0xE000E11C: Interrupt Set-Enable */
    uint32_t RESERVED2[24];
    volatile uint32_t ICER[8];        	/* 0xE000E180 - 0xE000E19C: Interrupt Clear-Enable */
    uint32_t RESERVED3[24];
    volatile uint32_t ISPR[8];        	/* 0xE000E200 - 0xE000E21C: Interrupt Set-Pending */
    uint32_t RESERVED4[24];
    volatile uint32_t ICPR[8];        	/* 0xE000E280 - 0xE000E29C: Interrupt Clear-Pending */
    uint32_t RESERVED5[24];
    volatile const uint32_t IABR[8];  	/* 0xE000E300 - 0xE000E31C: Interrupt Active Bit */
    uint32_t RESERVED6[56];
    volatile uint8_t IPR[240];        	/* 0xE000E400 - 0xE000E4EC: Interrupt Priority */
} NVIC_Type;

#define NVIC_BASE        (0xE000E000UL)
#define NVIC             ((NVIC_Type *) NVIC_BASE)

void NVIC_enable_IRQ(uint32_t IRQ_id);
void NVIC_disable_IRQ(uint32_t IRQ_id);
void NVIC_set_pending(uint32_t IRQ_id);
void NVIC_clear_pending(uint32_t IRQ_id);
void NVIC_set_priority(uint32_t IRQ_id, IRQ_priority priority);
void NVIC_enable_global_irq(void);

#endif /* INCLUDE_NVIC_S32K144_H_ */
