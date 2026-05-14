/*
 * bsp_gas.c
 *
 *  Created on: Apr 7, 2026
 *      Author: huysk
 */

#include "bsp_gas.h"
#include "adc.h"
#include <math.h>

#define VREF     3.3f
#define ADC_RES  4095.0f
#define RL       4700.0f
#define RO       10000.0f
#define A        565.0f
#define B        -1.48f

uint32_t BSP_Gas_ReadADC(void)
{
    uint32_t sum = 0;

    for (int i = 0; i < 10; i++)
    {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        sum += HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);
        HAL_Delay(5);
    }

    return sum / 10;
}

void BSP_Gas_Calibrate(void)
{
    // tạm thời để trống, chưa dùng
}

uint32_t BSP_Gas_ReadPPM(void)
{
    uint32_t adc = BSP_Gas_ReadADC();
    int32_t ppm = ((int32_t)(adc * 1000) / 4095) - 200;

    if (ppm < 0)
        ppm = 0;

    return (uint32_t)ppm;
}
