/*
 * Timer_Driver.c
 *
 *  Created on: Dec 3, 2024
 *      Author: trevo
 */

#include "Timer_Driver.h"

static TIM_HandleTypeDef htim2;//their is a chance that this code will not work due to it attmepting to write on a buissy bus
static TIM_HandleTypeDef htim3;

void Timer_Config(uint8_t timer){
	if(timer==2){
		htim2.Instance = TIM2;
		htim2.Init.Prescaler = TIM2_PRESCALER;
		htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
		htim2.Init.Period = 4294967295;
		htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
		Timer_Change_IT(timer,1);
	}
	if(timer==3){
		htim3.Instance = TIM3;
		htim3.Init.Prescaler = TIM3_PRESCALER;
		htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
		htim3.Init.Period = 65535;
		htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
		__HAL_TIM_SET_AUTORELOAD(&htim3, (uint32_t)(TIM3_AUTORELOAD));
		__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);
		Timer_Change_IT(timer,1);
	}
}
void Timer_Pause(uint8_t timer){
	if(timer==2){
		__HAL_TIM_DISABLE(&htim2);
		return;
	}
	if(timer==3){
		__HAL_TIM_DISABLE(&htim3);
		return;
	}
}
void Timer_Start(uint8_t timer){
	if(timer==2){
		__HAL_TIM_ENABLE(&htim2);
		return;
	}
	if(timer==3){
		__HAL_TIM_ENABLE(&htim3);
		return;
	}
}
void Timer_Reset(uint8_t timer){
	if(timer==2){
		__HAL_TIM_SET_COUNTER(&htim2,0);
		return;
	}
	if(timer==3){
		__HAL_TIM_SET_COUNTER(&htim3,0);
		return;
	}
}
uint32_t Timer_Get_Value(uint8_t timer){
	if(timer==2){
		return __HAL_TIM_GET_COUNTER(&htim2);
	}
	if(timer==3){
		return __HAL_TIM_GET_COUNTER(&htim3);
	}
	return 0;
}
void Timer_Change_IT(uint8_t timer, uint8_t state){
	if(timer==2){
		state ? IRQ_Enable(TIM2_IRQ_NUMBER): IRQ_Disable(TIM2_IRQ_NUMBER);
		return;
	}
	if(timer==3){
		state ? IRQ_Enable(TIM3_IRQ_NUMBER): IRQ_Disable(TIM3_IRQ_NUMBER);
		return;
	}
}
void Timer_Added2RemoveSRcuzItStartsOnHere(){
	TIMR_Clear_Pending(INTERRUPT_TIM3);
	IRQ_Enable(TIM3_IRQ_NUMBER);
}
