/*
 * RNG.h
 *
 *  Created on: Nov 22, 2024
 *      Author: trevo
 */

#ifndef INC_RNG_H_
#define INC_RNG_H_

#include "stm32f4xx_hal.h"

void RNG_init();
uint32_t RNG_getRandom();
void RNG_Error_Handler();
void RNG_Check_Hal_Status();

#endif /* INC_RNG_H_ */
