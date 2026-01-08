#include "../Include/Debounce.h"

ADCThreshold_t ADCThreshold(ACS712_t sensorType, float overCurrentThreshold)
{
    float currentMax = 0;

    switch (sensorType)
    {
        case ACS712_30A:    currentMax = 30;
        	break;
        case ACS712_20A:    currentMax = 20;
        	break;
        case ACS712_5A:     currentMax = 5;
        	break;
        default:            currentMax = 30;
    }

    if (overCurrentThreshold > currentMax)
    {
        overCurrentThreshold = currentMax;
    }

    // avoid currentMax cant be read
    if (currentMax <= 0)
    {
        currentMax = 1;
    }

    uint32_t adcDelta =  (uint32_t)((overCurrentThreshold/currentMax)*2048);

    ADCThreshold_t threshold;
    threshold.upper = 2048 + adcDelta;
    threshold.lower = 2048 - adcDelta;

    return threshold;
}

bool DebounceHandler(Debounce_t* debounceState, uint32_t adcValue, ADCThreshold_t threshold)
{
    bool faultPresent = (adcValue >= threshold.upper) || (adcValue < threshold.lower);

    if (faultPresent)
    {
        if (debounceState->counter < debounceState->qualifyLimit)
        {
            debounceState->counter++;
        }
    }
    else
    {
        if (debounceState->counter > debounceState->disqualifyLimit)
        {
            debounceState->counter--;
        }
    }

    if (!debounceState->faultFlag)
    {
        if (debounceState->counter >= debounceState->qualifyLimit)
        {
            debounceState->faultFlag = true;
        }
    }
    else
    {
        if (debounceState->counter <= debounceState->disqualifyLimit)
        {
            debounceState->faultFlag = false;
            debounceState->counter = 0;
        }
    }

    return debounceState->faultFlag;
}

float ConvertIntoCurrent(ACS712_t sensorType, uint32_t adcValue)
{
    float sensitivity = 0.0f;
    float Vcc = 5.0f;
    float Vout = ((float)adcValue / 4095.0f) * Vcc;
    float Vzero = Vcc / 2.0f;

    switch (sensorType)
    {
        case ACS712_30A:
            sensitivity = 0.066f;
            break;
        case ACS712_20A:
            sensitivity = 0.100f;
            break;
        case ACS712_5A:
            sensitivity = 0.185f;
            break;
        default:
            return 0.0f;
    }

    float current = (Vout - Vzero) / sensitivity;
    return current;
}

