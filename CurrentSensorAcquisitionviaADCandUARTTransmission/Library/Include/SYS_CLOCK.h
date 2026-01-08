#ifndef INCLUDE_SYS_CLOCK_H_
#define INCLUDE_SYS_CLOCK_H_

#include "S32K144.h"

void SOSC_Init_8MHz();
void SPLL_Init_160MHz();
void NormalRUNmode_80MHz();

#endif /* INCLUDE_SYS_CLOCK_H_ */
