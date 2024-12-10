/*
 * Button_Driver.h
 *
 *  Created on: Sep 24, 2024
 *      Author: trevo
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include "stm32f4xx_hal.h"
#include <InterruptControl.h>

#define ButtonGPIO GPIOA //this needs to be changed
#define ButtonPinNumber GPIO_PIN_0
#define ButtonIsDepressed 1
#define ButtonIsUnpressed 0

#define EXTI0_IRQ_NUMBER 6

void Button_Init();
void Clock_Init();
uint8_t getButtonCurrentState();
void Button_Init_InterruptMode();

#endif /* BUTTON_DRIVER_H_ */
