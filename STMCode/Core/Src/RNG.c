/*
 * RNG.c
 *
 *  Created on: Nov 22, 2024
 *      Author: trevo
 */
#include "RNG.h"//this has not been initialized correctly

static HAL_StatusTypeDef RNGState;
static RNG_HandleTypeDef RNGConfig;

void RNG_init(){
	RNGConfig.Instance = RNG;
	__HAL_RNG_ENABLE(&RNGConfig);
	RNGState = HAL_RNG_Init(&RNGConfig);
	RNG_Check_Hal_Status();
}


void RNG_Error_Handler(){
	while(1);;
}
void RNG_Check_Hal_Status(){
	if(RNGState!=HAL_OK){
		RNG_Error_Handler();
	}
}
uint32_t RNG_getRandom(){
	//uint32_t randomNum = HAL_RNG_GetRandomNumber(&RNGConfig);//add the thing
	uint32_t randomNum = 0;
	RNGState = HAL_RNG_GenerateRandomNumber(&RNGConfig,&randomNum);
	if(randomNum==0U){
		RNG_Error_Handler();
	}
	return randomNum;
}
