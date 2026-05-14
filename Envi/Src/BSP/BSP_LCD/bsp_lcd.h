/*
 * bsp_lcd.h
 *
 *  Created on: Apr 24, 2026
 *      Author: huysk
 */

#ifndef INC_BSP_LCD_H_
#define INC_BSP_LCD_H_

#include "main.h"

void BSP_LCD_Init(void);
void BSP_LCD_SendCmd(char cmd);
void BSP_LCD_SendData(char data);
void BSP_LCD_SendString(char *str);
void BSP_LCD_SetCursor(int row, int col);

#endif /* INC_BSP_LCD_H_ */
