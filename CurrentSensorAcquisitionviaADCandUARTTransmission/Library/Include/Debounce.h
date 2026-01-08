#ifndef INCLUDE_DEBOUNCE_H_
#define INCLUDE_DEBOUNCE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Alarm.h"

typedef enum
{
    ACS712_30A,
    ACS712_20A,
    ACS712_5A
} ACS712_t;

typedef struct
{
  uint32_t upper;
  uint32_t lower;
} ADCThreshold_t;

typedef struct
{
    int16_t    counter;
    bool       faultFlag;
    int16_t    qualifyLimit;
    int16_t    disqualifyLimit;
} Debounce_t;

ADCThreshold_t ADCThreshold(ACS712_t sensorType, float overCurrentThreshold);
bool DebounceHandler(Debounce_t* debounceState, uint32_t adcValue, ADCThreshold_t threshold);
float ConvertIntoCurrent(ACS712_t sensorType, uint32_t adcValue);

#endif /* INCLUDE_DEBOUNCE_H_ */
