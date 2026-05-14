/*
 * bsp_gas.h
 *
 *  Created on: Apr 7, 2026
 *      Author: huysk
 */

#ifndef INC_BSP_GAS_H_
#define INC_BSP_GAS_H_

#include "main.h"

void BSP_Gas_Calibrate(void);
uint32_t BSP_Gas_ReadADC(void);
uint32_t BSP_Gas_ReadPPM(void);

#endif /* INC_BSP_GAS_H_ */
