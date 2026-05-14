/*
 * bsp_button.c
 *
 *  Created on: Apr 7, 2026
 *      Author: huysk
 */


#include "bsp_button.h"

uint8_t BSP_Button1_Read(void)
{
    return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
}

uint8_t BSP_Button2_Read(void)
{
    return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
}
