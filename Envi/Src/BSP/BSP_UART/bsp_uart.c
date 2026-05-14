 /*
 * bsp_uart.c
 *
 *  Created on: Apr 7, 2026
 *      Author: huysk
 */


#include "bsp_uart.h"
#include "usart.h"
#include <string.h>

void BSP_UART_DebugPrint(char *msg)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

