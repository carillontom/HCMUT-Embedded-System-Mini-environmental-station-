/*
 * app.c
 *
 *  Created on: Apr 7, 2026
 *      Author: huysk
 */


#include "app.h"
#include "bsp_led.h"
#include "bsp_buzzer.h"
#include "bsp_uart.h"
#include "bsp_gas.h"
#include "bsp_button.h"
#include "bsp_hc05.h"
#include "bsp_dht11.h"
#include "bsp_lcd.h"

#include "tim.h"

#include <stdio.h>

static uint32_t gas_ppm = 0;
static uint8_t gas_alert = 0;
static uint32_t gas_threshold = 500;
static DHT11_Data_t dht11_data = {0};
static uint32_t dht11_last_tick = 0;
static uint32_t led_last_tick = 0;
static uint8_t lcd_mode = 0;
static uint32_t lcd_last_tick = 0;

static void APP_HandleButtons(void)
{
    static uint8_t last_b1 = 1;
    static uint8_t last_b2 = 1;

    uint8_t b1 = BSP_Button1_Read();
    uint8_t b2 = BSP_Button2_Read();

    if ((last_b1 == 1) && (b1 == 0))
    {
        HAL_Delay(20);
        if (BSP_Button1_Read() == 0)
        {
            BSP_UART_DebugPrint("[DBG] BUTTON_1 pressed\r\n");

            if (gas_threshold == 660)
            {
                gas_threshold = 10;
                BSP_UART_DebugPrint("[DBG] THRESHOLD = 10 ppm\r\n");
            }
            else
            {
                gas_threshold = 660;
                BSP_UART_DebugPrint("[DBG] THRESHOLD = 660 ppm\r\n");
            }
        }
    }

    if ((last_b2 == 1) && (b2 == 0))
    {
        HAL_Delay(20);
        if (BSP_Button2_Read() == 0)
        {
            BSP_UART_DebugPrint("[DBG] BUTTON_2 pressed\r\n");

            lcd_mode++;
            if (lcd_mode > 3) lcd_mode = 0;

            if (lcd_mode == 0) BSP_UART_DebugPrint("[DBG] LCD MODE = WELCOME\r\n");
            else if (lcd_mode == 1) BSP_UART_DebugPrint("[DBG] LCD MODE = GAS\r\n");
            else if (lcd_mode == 2) BSP_UART_DebugPrint("[DBG] LCD MODE = TEMP\r\n");
            else if (lcd_mode == 3) BSP_UART_DebugPrint("[DBG] LCD MODE = HUMI\r\n");
        }
    }

    last_b1 = b1;
    last_b2 = b2;
}

static void APP_UpdateGasSystem(void)
{
    //char msg[100];
    char bt_msg[100];

    gas_ppm = BSP_Gas_ReadPPM();

    if (gas_ppm > gas_threshold)
        gas_alert = 1;
    else
        gas_alert = 0;

    if (gas_alert)
    {
        BSP_Buzzer_On();
    }
    else
    {
        BSP_Buzzer_Off();
    }

    //snprintf(msg, sizeof(msg),
            // "GAS=%lu | TH=%lu | ALERT=%d | MUTE=%d\r\n",
             //gas_adc, gas_threshold, gas_alert, alarm_mute);
    //BSP_UART_DebugPrint(msg);

    snprintf(bt_msg, sizeof(bt_msg),
             "Temp:%d.0*C\r\n",
             dht11_data.temperature);
    BSP_HC05_Print(bt_msg);

    snprintf(bt_msg, sizeof(bt_msg),
             "Humidity:%d.0%%RH\r\n",
             dht11_data.humidity);
    BSP_HC05_Print(bt_msg);

    snprintf(bt_msg, sizeof(bt_msg),
    		"Gas density:%lu ppm\r\n",
    		gas_ppm);
    BSP_HC05_Print(bt_msg);
    BSP_HC05_Print("========================\r\n");
}

void APP_Init(void)
{
	lcd_mode = 0;
    BSP_UART_DebugPrint("\r\n=== GAS MONITOR DEMO ===\r\n");
    BSP_UART_DebugPrint("[DBG] BUTTON_1: Change threshold\r\n");
    BSP_UART_DebugPrint("[DBG] BUTTON_2: Change LCD mode\r\n");

    BSP_HC05_Print("\r\n=== HC05 LINK STARTED ===\r\n");

    BSP_LED_Off();
    BSP_Buzzer_Off();

    BSP_Gas_Calibrate();

    BSP_LCD_Init();
    BSP_LCD_SetCursor(0, 0);
    BSP_LCD_SendString("Envir Station");
    BSP_LCD_SetCursor(1, 0);
    BSP_LCD_SendString("Group 8");

    HAL_TIM_Base_Start(&htim2);
}

void APP_Run(void)
{
    if (HAL_GetTick() - dht11_last_tick >= 2000)
    {
        dht11_last_tick = HAL_GetTick();
        dht11_data.valid = 0;

        uint8_t dht_ret = BSP_DHT11_Read(&dht11_data);

        if (dht_ret != 1)
        {
            char err_msg[40];
            snprintf(err_msg, sizeof(err_msg), "DHT11 fail code = %d\r\n", dht_ret);
            BSP_UART_DebugPrint(err_msg);
        }
    }

    if (HAL_GetTick() - led_last_tick >= 500)
    {
        led_last_tick = HAL_GetTick();
        BSP_LED_Toggle();
    }

    APP_HandleButtons();
    APP_UpdateGasSystem();

    if (HAL_GetTick() - lcd_last_tick >= 500)
    {
        char line2[20];

        lcd_last_tick = HAL_GetTick();

        BSP_LCD_SendCmd(0x01);
        HAL_Delay(2);

        if (lcd_mode == 0)
        {
            BSP_LCD_SetCursor(0, 0);
            BSP_LCD_SendString("Envir Station");
            BSP_LCD_SetCursor(1, 0);
            BSP_LCD_SendString("Group 8");
        }
        else if (lcd_mode == 1)
        {
            BSP_LCD_SetCursor(0, 0);
            BSP_LCD_SendString("Gas density:");
            snprintf(line2, sizeof(line2), "%lu ppm", gas_ppm);
            BSP_LCD_SetCursor(1, 0);
            BSP_LCD_SendString(line2);
        }
        else if (lcd_mode == 2)
        {
            BSP_LCD_SetCursor(0, 0);
            BSP_LCD_SendString("Temperature:");
            snprintf(line2, sizeof(line2), "%d C", dht11_data.temperature);
            BSP_LCD_SetCursor(1, 0);
            BSP_LCD_SendString(line2);
        }
        else if (lcd_mode == 3)
        {
            BSP_LCD_SetCursor(0, 0);
            BSP_LCD_SendString("Humidity:");
            snprintf(line2, sizeof(line2), "%d %%RH", dht11_data.humidity);
            BSP_LCD_SetCursor(1, 0);
            BSP_LCD_SendString(line2);
        }
    }
    HAL_Delay(800);
}
