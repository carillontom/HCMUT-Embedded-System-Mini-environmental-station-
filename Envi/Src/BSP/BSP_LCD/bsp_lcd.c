/*
 * bsp_lcd.c
 *
 *  Created on: Apr 24, 2026
 *      Author: huysk
 */

#include "bsp_lcd.h"
#include "i2c.h"

#define SLAVE_ADDRESS_LCD 0x4E

void BSP_LCD_SendCmd(char cmd)
{
    char data_u, data_l;
    data_u = (cmd & 0xF0);
    data_l = ((cmd << 4) & 0xF0);

    uint8_t data_t[4];
    data_t[0] = data_u | 0x0C;
    data_t[1] = data_u | 0x08;
    data_t[2] = data_l | 0x0C;
    data_t[3] = data_l | 0x08;

    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, (uint8_t *)data_t, 4, 100);
}

void BSP_LCD_SendData(char data)
{
    char data_u, data_l;
    uint8_t data_t[4];

    data_u = (data & 0xF0);
    data_l = ((data << 4) & 0xF0);

    data_t[0] = data_u | 0x0D;
    data_t[1] = data_u | 0x09;
    data_t[2] = data_l | 0x0D;
    data_t[3] = data_l | 0x09;

    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, (uint8_t *)data_t, 4, 100);
}

void BSP_LCD_Init(void)
{
    HAL_Delay(50);
    BSP_LCD_SendCmd(0x30);
    HAL_Delay(5);
    BSP_LCD_SendCmd(0x30);
    HAL_Delay(1);
    BSP_LCD_SendCmd(0x30);
    HAL_Delay(10);
    BSP_LCD_SendCmd(0x20);
    HAL_Delay(10);

    BSP_LCD_SendCmd(0x28);
    HAL_Delay(1);
    BSP_LCD_SendCmd(0x08);
    HAL_Delay(1);
    BSP_LCD_SendCmd(0x01);
    HAL_Delay(2);
    BSP_LCD_SendCmd(0x06);
    HAL_Delay(1);
    BSP_LCD_SendCmd(0x0C);
}

void BSP_LCD_SendString(char *str)
{
    while (*str) BSP_LCD_SendData(*str++);
}

void BSP_LCD_SetCursor(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
    BSP_LCD_SendCmd(col);
}
