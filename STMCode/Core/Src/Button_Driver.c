/*
 * Button_Driver.c
 *
 *  Created on: Sep 24, 2024
 *      Author: trevo
 */

#include <Button_Driver.h>

void Button_Init(){
	GPIO_InitTypeDef ButtonConfig;
	ButtonConfig.Pin = ButtonPinNumber;
	ButtonConfig.Mode = GPIO_MODE_INPUT;
	ButtonConfig.Speed = GPIO_SPEED_FREQ_LOW;
	ButtonConfig.Pull = GPIO_PULLUP; //could be no pull
	ButtonConfig.Alternate = DISABLE;
	Clock_Init();
	HAL_GPIO_Init(ButtonGPIO, &ButtonConfig);
}
void Clock_Init(){
	__HAL_RCC_GPIOA_CLK_ENABLE();
}
uint8_t getButtonCurrentState(){
	//return GPIO_ReadFromInputPin(ButtonGPIO, ButtonPinNumber);
	return DISABLE;
}
void Button_Init_InterruptMode(){
	GPIO_InitTypeDef ButtonConfig;
	ButtonConfig.Pin = ButtonPinNumber;
	ButtonConfig.Mode = GPIO_MODE_IT_RISING;
	ButtonConfig.Speed = GPIO_SPEED_FREQ_LOW;
	ButtonConfig.Pull = GPIO_NOPULL; //could be no pull
	ButtonConfig.Alternate = DISABLE;
	Clock_Init();
	HAL_GPIO_Init(ButtonGPIO, &ButtonConfig);
	IRQ_Enable(EXTI0_IRQ_NUMBER);
	__NVIC_DisableIRQ(EXTI0_IRQn);
}
