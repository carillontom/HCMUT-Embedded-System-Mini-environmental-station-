/*
 * bsp_led.c
 *
 *  Created on: Apr 7, 2026
 *      Author: huysk
 */


#include "bsp_led.h"

void BSP_LED_On(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
}

void BSP_LED_Off(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}

void BSP_LED_Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
}
