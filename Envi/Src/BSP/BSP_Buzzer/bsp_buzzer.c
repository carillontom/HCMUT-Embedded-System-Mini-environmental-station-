/*
 * bsp_buzzer.c
 *
 *  Created on: Apr 7, 2026
 *      Author: huysk
 */


#include "bsp_buzzer.h"

void BSP_Buzzer_On(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

void BSP_Buzzer_Off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}
