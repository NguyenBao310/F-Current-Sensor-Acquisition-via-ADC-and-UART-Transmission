#ifndef INCLUDE_LPUART_H_
#define INCLUDE_LPUART_H_

#include "S32K144.h"
#include <stdio.h>
#include <string.h>

#include "utils.h"

void LPUART1_PORT_Init();
void LPUART1_Init(uint32_t baudrateSetting);

void LPUART1_Transmit_Char(char c);
void LPUART1_Transmit_Str(char *s);
void LPUART1_Transmit_Data(uint32_t value);
char LPUART1_Receive();

#endif /* INCLUDE_LPUART_H_ */
