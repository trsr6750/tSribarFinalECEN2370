/*
 * Timer_Driver.h
 *
 *  Created on: Oct 8, 2024
 *      Author: trevo
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include "stm32f4xx_hal.h"
#include <InterruptControl.h>

//16 MHz clock of 16 million a second, but it should 6.25 MHz, so 6250000
#define TIMxCountsPerSecond 84000000
#define TIM2CountsPerSec	2000
#define TIM2CountsPer100thSec	(TIM2CountsPerSec/100)
#define TIM2CountsPerMin	(TIM2CountsPerSec*60)
#define TIM3CountsPerSec 10000
#define OneTick 1
#define MaxPlaytime 4294967296 //this is in ticks

#define TIM3_AUTORELOAD (TIM3CountsPerSec*3)

#define TIM2_PRESCALER ((TIMxCountsPerSecond/2000)-1)
#define TIM3_PRESCALER ((TIMxCountsPerSecond/8400)-1)

#define tim2 2
#define tim3 3

void Timer_Config(uint8_t timer);
void Timer_Pause(uint8_t timer);
void Timer_Start(uint8_t timer);
void Timer_Reset(uint8_t timer);
uint32_t Timer_Get_Value(uint8_t timer);
void Timer_Change_IT(uint8_t timer, uint8_t state);
void Timer_Added2RemoveSRcuzItStartsOnHere();

#endif /* TIMER_DRIVER_H_ */
