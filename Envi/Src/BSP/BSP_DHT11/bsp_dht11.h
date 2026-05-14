/*
 * bsp_dht11.h
 *
 *  Created on: Apr 11, 2026
 *      Author: huysk
 */

#ifndef INC_BSP_DHT11_H_
#define INC_BSP_DHT11_H_

#include "main.h"

typedef struct
{
    uint8_t temperature;
    uint8_t humidity;
    uint8_t valid;
} DHT11_Data_t;

void BSP_DHT11_SetPinOutput(void);
void BSP_DHT11_SetPinInput(void);
void BSP_DHT11_DelayUs(uint16_t us);
uint8_t BSP_DHT11_Read(DHT11_Data_t *data);

#endif /* INC_BSP_DHT11_H_ */
