/*
 * gameLogic.h
 *
 *  Created on: Nov 19, 2024
 *      Author: trevo
 */

#ifndef INC_GAMELOGIC_H_
#define INC_GAMELOGIC_H_

#include <stdbool.h>
#include <stdint.h>
#include <RNG.h>
#include <stdlib.h>

typedef struct Game_Block Game_Block;

typedef struct Game_Block{
	bool Shape[4][4];
    uint8_t length;
    uint8_t height;
    Game_Block *NextBlock;
    Game_Block *PrevBlock;
}Game_Block;

#define SQUARE_BLOCK (Game_Block){\
	.Shape={{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},\
	.length=2,\
	.height=2}
#define LINE_BLOCK (Game_Block){\
	.Shape={{1,1,1,1}},\
	.length=4,\
	.height=1}
#define LINE_BLOCK_VERT (Game_Block){\
	.Shape={{1},{1},{1},{1}},\
	.length=1,\
	.height=4}
#define RL_BLOCK (Game_Block) {\
	.Shape={{1,1,1},{0,0,1}},\
	.length=3,\
	.height=2}
#define RL_BLOCK_90 (Game_Block){\
	.Shape={{0,1},{0,1},{1,1}},\
	.length=2,\
	.height=3}
#define RL_BLOCK_180 (Game_Block){\
	.Shape={{1},{1,1,1}},\
	.length=3,\
	.height=2}
#define RL_BLOCK_270 (Game_Block){\
	.Shape={{1,1},{1},{1}},\
	.length=2,\
	.height=3}
#define L_BLOCK (Game_Block){\
	.Shape={{1,1,1},{1}},\
	.length=3,\
	.height=2}
#define L_BLOCK_90 (Game_Block){\
	.Shape={{1,1},{0,1},{0,1}},\
	.length=2,\
	.height=3}
#define L_BLOCK_180 (Game_Block){\
	.Shape={{0,0,1},{1,1,1}},\
	.length=3,\
	.height=2}
#define L_BLOCK_270 (Game_Block){\
	.Shape={{1},{1},{1,1}},\
	.length=2,\
	.height=3}
#define S_BLOCK (Game_Block){\
	.Shape={{0,1,1},{1,1}},\
	.length=3,\
	.height=2}
#define S_BLOCK_VERT (Game_Block){\
	.Shape={{1},{1,1},{0,1}},\
	.length=2,\
	.height=3}
#define RS_BLOCK (Game_Block){\
	.Shape={{1,1},{0,1,1}},\
	.length=3,\
	.height=2}
#define RS_BLOCK_VERT (Game_Block){\
	.Shape={{0,1},{1,1},{1}},\
	.length=2,\
	.height=3}
#define T_BLOCK (Game_Block){\
	.Shape={{1,1,1},{0,1}},\
	.length=3,\
	.height=2}
#define T_BLOCK_90 (Game_Block){\
	.Shape={{0,1},{1,1},{0,1}},\
	.length=2,\
	.height=3}
#define T_BLOCK_180 (Game_Block){\
	.Shape={{0,1},{1,1,1}},\
	.length=3,\
	.height=2}
#define T_BLOCK_270 (Game_Block){\
	.Shape={{1},{1,1},{1}},\
	.length=2,\
	.height=3}

#define SQUARE_NUM 0
#define LINE_NUM 1
#define LINE_NUM_VERT 7
#define RL_NUM 2
#define RL_NUM_90 8
#define RL_NUM_180 9
#define RL_NUM_270 10
#define L_NUM 3
#define L_NUM_90 11
#define L_NUM_180 12
#define L_NUM_270 13
#define S_NUM 4
#define S_NUM_VERT 14
#define RS_NUM 5
#define RS_NUM_VERT 15
#define T_NUM 6
#define T_NUM_90 16
#define T_NUM_180 17
#define T_NUM_270 18

#define SHAPE_ARR_SIZE 4
#define BLOCK_OVERFLOW_NUM 7
#define ONLY_LINE_PEICES false

void Game_init();
void Game_Start();
void Game_Move_Left();
void Game_Move_Right();
void Game_Rotate_Clock();
void Game_Rotate_Counter_Clock();
bool Game_Drop_Block();
void Game_Lock_Block();
void Game_Spawn_Block();
void Game_Set_Block(uint8_t blockNum, Game_Block block,uint8_t nextBlockNum, uint8_t prevBlockNum);
void Game_Find_Clear_Lines();
void Game_Clear_Line(uint8_t lineNum);
bool Game_Check_Collision(uint8_t newX, uint8_t newY);
bool Game_Check_Alive();
uint8_t Game_get_Xcord();
uint8_t Game_get_Ycord();
Game_Block *Game_get_Current_Block();
bool Game_get_State_At(uint8_t x, uint8_t y);
uint16_t Game_get_Single_Clears();
uint16_t Game_get_Double_Clears();
uint16_t Game_get_Tripple_Clears();
uint16_t Game_get_Tetris_Clears();
void Game_Reset_Clears();

#endif /* INC_GAMELOGIC_H_ */
