/*
 * bsp_hc05.c
 *
 *  Created on: Apr 11, 2026
 *      Author: huysk
 */


#include "bsp_hc05.h"
#include "usart.h"
#include <string.h>

void BSP_HC05_Print(char *msg)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}
