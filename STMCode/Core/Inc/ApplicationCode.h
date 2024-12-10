/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "LCD_Driver.h"
#include "stm32f4xx_hal.h"
#include "gameLogic.h"
#include "Timer_Driver.h"
#include <Button_Driver.h>

#include <stdio.h>


#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

void ApplicationInit(void);
void LCD_Visual_Demo(void);
void Display_Play_Screen();
void Display_Game_Bckrnd();
void Display_Game_Time();
void Clear_Game_Time();
bool Check_Play_Pressed();
void Clear_LCD_Screen();
void Display_Current_Square();
void Display_Current_GameState();
void Pull_Touch_Input();
bool Check_Alive();
void New_Game();
void End_Game();
void startTimers();
void stopTimers();

#if (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)

void TIM2_IRQHandler();
void TIM3_IRQHandler();

#endif /* INC_APPLICATIONCODE_H_ */
