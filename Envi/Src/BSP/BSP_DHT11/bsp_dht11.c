/*
 * bsp_dht11.c
 *
 *  Created on: Apr 11, 2026
 *      Author: huysk
 */


#include "bsp_dht11.h"
#include "tim.h"
#include "gpio.h"

void BSP_DHT11_SetPinOutput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void BSP_DHT11_SetPinInput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void BSP_DHT11_DelayUs(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (__HAL_TIM_GET_COUNTER(&htim2) < us);
}

uint8_t BSP_DHT11_Read(DHT11_Data_t *data)
{
    uint8_t bits = 0;
    uint8_t packets[5] = {0};
    uint8_t packetIndex = 0;
    uint32_t timeout;

    // Start signal
    BSP_DHT11_SetPinOutput();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    BSP_DHT11_DelayUs(40);
    BSP_DHT11_SetPinInput();

    // Nếu line vẫn HIGH quá lâu -> sensor không phản hồi
    timeout = 100;
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
    {
        BSP_DHT11_DelayUs(1);
        if (--timeout == 0) return 2;
    }

    // Chờ sensor kéo HIGH
    timeout = 100;
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
    {
        BSP_DHT11_DelayUs(1);
        if (--timeout == 0) return 3;
    }

    // Chờ sensor kéo LOW lại, kết thúc handshake
    timeout = 100;
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
    {
        BSP_DHT11_DelayUs(1);
        if (--timeout == 0) return 4;
    }

    while (bits < 40)
    {
        // Chờ bắt đầu bit: line lên HIGH
        timeout = 100;
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
        {
            BSP_DHT11_DelayUs(1);
            if (--timeout == 0) return 5;
        }

        // Đo thời gian line ở mức HIGH
        __HAL_TIM_SET_COUNTER(&htim2, 0);
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
        {
            if (__HAL_TIM_GET_COUNTER(&htim2) > 100)
                return 6;
        }

        packets[packetIndex] <<= 1;
        packets[packetIndex] |= (__HAL_TIM_GET_COUNTER(&htim2) > 50);

        bits++;
        if ((bits % 8) == 0) packetIndex++;
    }

    // checksum
    if (packets[4] != (uint8_t)(packets[0] + packets[1] + packets[2] + packets[3]))
        return 7;

    data->humidity = packets[0];
    data->temperature = packets[2];
    data->valid = 1;

    return 1;
}
