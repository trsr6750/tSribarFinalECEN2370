/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */


extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#if TOUCH_INTERRUPT_ENABLED == 1
static EXTI_HandleTypeDef LCDTouchIRQ;
void LCDTouchScreenInterruptGPIOInit(void);
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS
static uint32_t GameTimeOveflows = 0;

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
	LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_BLACK);
    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#if TOUCH_INTERRUPT_ENABLED == 1
	LCDTouchScreenInterruptGPIOInit();
	#endif // TOUCH_INTERRUPT_ENABLED

	#endif // COMPILE_TOUCH_FUNCTIONS
	RNG_init();
	Game_init();
	Button_Init_InterruptMode();
	Timer_Config(2);
	Timer_Config(3);
}
void startTimers(){
	Timer_Start(2);
	Timer_Start(3);
}
void stopTimers(){
	Timer_Pause(2);
	Timer_Pause(3);
	Timer_Reset(2);
	Timer_Reset(3);
}
void LCD_Visual_Demo(void)
{
	visualDemo();
}
void Display_Play_Screen(){
	LCD_Draw_Play_Icon();
	LCD_Draw_Homescreen_Blocks();
}
void Display_Game_Bckrnd(){
	LCD_Draw_Board_Background();
}
void Display_Game_Time(){
	uint32_t ticks = Timer_Get_Value(tim2);
	uint32_t min = ticks/TIM2CountsPerMin;
	uint8_t sec = (ticks/TIM2CountsPerSec)%60;
	uint8_t ms = (ticks/TIM2CountsPer100thSec)%100;
	LCD_Draw_Game_Time(min,sec,ms);
}
void Clear_Game_Time(){
	LCD_Clear_Game_Time();
}
#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}
bool Check_Play_Pressed(){
	return (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed);
}
void Clear_LCD_Screen(){
	LCD_Clear(0,LCD_COLOR_BLACK);
}
void Display_Current_Square(){
	uint8_t xCoordinate = Game_get_Xcord();
	uint8_t yCoordinate = Game_get_Ycord();
	Game_Block *CurrentBlock = Game_get_Current_Block();
	LCD_Update_Block_Location(xCoordinate,yCoordinate,CurrentBlock->Shape,LCD_COLOR_WHITE);
}
void Display_Current_GameState(){
	uint16_t sideLength=15;
	for(int y = 0; y<20;y++){
		for(int x = 0; x<10; x++){
			if(Game_get_State_At(x,y)){
				LCD_Draw_Square((sideLength*x)+x+40,(sideLength*y)+y,sideLength,LCD_COLOR_WHITE);
			}
			else{
				LCD_Draw_Square((sideLength*x)+x+40,(sideLength*y)+y,sideLength,LCD_COLOR_BLACK);
			}
		}
	}
}
void Erase_Current_Square(){
	uint8_t xCoordinate = Game_get_Xcord();
	uint8_t yCoordinate = Game_get_Ycord();
	Game_Block *CurrentBlock = Game_get_Current_Block();
	LCD_Update_Block_Location(xCoordinate,yCoordinate,CurrentBlock->Shape,LCD_COLOR_BLACK);
}
void Pull_Touch_Input(){
	if(returnTouchStateAndLocation(&StaticTouchData)==STMPE811_State_Pressed){//need to add masking for interrupt
		TIMR_Mask_IRQ(INTERRUPT_TIM3);
		Erase_Current_Square();
		uint16_t xCords = StaticTouchData.x;
		uint16_t yCords = StaticTouchData.y;
		if(yCords>(320-64)){
			Game_Rotate_Clock();
		}
		else if(yCords<64){
			Game_Rotate_Counter_Clock();
		}
		else if(xCords>120){
			Game_Move_Right();
		}
		else if(xCords<120){
			Game_Move_Left();
		}
		Display_Current_Square();
		TIMR_Unmask_IRQ(INTERRUPT_TIM3);
		HAL_Delay(50);
	}
}
bool Check_Alive(){
	return Game_Check_Alive();
}
void New_Game(){
	Game_Start();
	__NVIC_EnableIRQ(EXTI0_IRQn);
}
void End_Game(){
	__NVIC_DisableIRQ(EXTI0_IRQn);
	LCD_Draw_Game_Over();
	uint16_t singles = Game_get_Single_Clears();
	uint16_t dooubles = Game_get_Double_Clears();
	uint16_t tripples = Game_get_Tripple_Clears();
	uint16_t tetri = Game_get_Tetris_Clears();
	LCD_Draw_Lines_Cleared(singles,dooubles,tripples,tetri);
}
//uint8_t ScreenBeenPressed(){
//	STMPE811_State_t TouchState = returnTouchStateAndLocation(&StaticTouchData);
//	if(TouchState==STMPE811_State_Pressed){
//		return true;
//	}
//	return false;
//}

// TouchScreen Interrupt
#if TOUCH_INTERRUPT_ENABLED == 1

void LCDTouchScreenInterruptGPIOInit(void)
{
	GPIO_InitTypeDef LCDConfig = {0};
    LCDConfig.Pin = GPIO_PIN_15;
    LCDConfig.Mode = GPIO_MODE_IT_RISING_FALLING;
    LCDConfig.Pull = GPIO_NOPULL;
    LCDConfig.Speed = GPIO_SPEED_FREQ_HIGH;
    
    // Clock enable
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // GPIO Init      
    HAL_GPIO_Init(GPIOA, &LCDConfig);

    // Interrupt Configuration
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	LCDTouchIRQ.Line = EXTI_LINE_15;

}

#define TOUCH_DETECTED_IRQ_STATUS_BIT   (1 << 0)  // Touchscreen detected bitmask

static uint8_t statusFlag;

void EXTI15_10_IRQHandler()
{
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); // May consider making this a universial interrupt guard
	bool isTouchDetected = false;

	static uint32_t count;
	count = 0;
	while(count == 0){
		count = STMPE811_Read(STMPE811_FIFO_SIZE);
	}

	// Disable touch interrupt bit on the STMPE811
	uint8_t currentIRQEnables = ReadRegisterFromTouchModule(STMPE811_INT_EN);
	WriteDataToTouchModule(STMPE811_INT_EN, 0x00);

	// Clear the interrupt bit in the STMPE811
	statusFlag = ReadRegisterFromTouchModule(STMPE811_INT_STA);
	uint8_t clearIRQData = (statusFlag | TOUCH_DETECTED_IRQ_STATUS_BIT); // Write one to clear bit
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);
	
	uint8_t ctrlReg = ReadRegisterFromTouchModule(STMPE811_TSC_CTRL);
	if (ctrlReg & 0x80)
	{
		isTouchDetected = true;
	}

	// Determine if it is pressed or unpressed
	if(isTouchDetected) // Touch has been detected
	{
		printf("\nPressed");
		// May need to do numerous retries? 
		DetermineTouchPosition(&StaticTouchData);
		/* Touch valid */
		printf("\nX: %03d\nY: %03d \n", StaticTouchData.x, StaticTouchData.y);
		LCD_Clear(0, LCD_COLOR_RED);

	}else{

		/* Touch not pressed */
		printf("\nNot pressed \n");
		LCD_Clear(0, LCD_COLOR_GREEN);
	}

	STMPE811_Write(STMPE811_FIFO_STA, 0x01);
	STMPE811_Write(STMPE811_FIFO_STA, 0x00);

	// Re-enable IRQs
    WriteDataToTouchModule(STMPE811_INT_EN, currentIRQEnables);
	HAL_EXTI_ClearPending(&LCDTouchIRQ, EXTI_TRIGGER_RISING_FALLING);

	HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	//Potential ERRATA? Clearing IRQ bit again due to an IRQ being triggered DURING the handling of this IRQ..
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);

}
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS

void EXTI0_IRQHandler(){
	//IRQ_Disable(EXTI0_IRQ_NUMBER);
	__NVIC_DisableIRQ(EXTI0_IRQn);
	Erase_Current_Square();
	while(Game_Drop_Block()){
		Display_Current_Square();
		Erase_Current_Square();
	}
	Game_Find_Clear_Lines();
	Display_Current_GameState();
	Game_Spawn_Block();
	Display_Current_Square();
	EXTI_Clear_Pending(IRQ_BUTTON_PIN_NUM);
	//IRQ_Enable(EXTI0_IRQ_NUMBER);
	__NVIC_EnableIRQ(EXTI0_IRQn);
}

void TIM2_IRQHandler(){
	IRQ_Disable(TIM2_IRQ_NUMBER);
	GameTimeOveflows++;
	TIMR_Clear_Pending(INTERRUPT_TIM2);
	IRQ_Enable(TIM2_IRQ_NUMBER);
}
void TIM3_IRQHandler(){
//	IRQ_Disable(TIM3_IRQ_NUMBER);
	__NVIC_DisableIRQ(TIM2_IRQn);
	Erase_Current_Square();
	if(!Game_Drop_Block()){
		Game_Find_Clear_Lines();
		Display_Current_GameState();
		Game_Spawn_Block();
	}
	Display_Current_Square();
	TIMR_Clear_Pending(INTERRUPT_TIM3);
//	IRQ_Enable(TIM3_IRQ_NUMBER);
	__NVIC_EnableIRQ(TIM2_IRQn);
}

