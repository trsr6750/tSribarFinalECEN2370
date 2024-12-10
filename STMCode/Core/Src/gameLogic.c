/*
 * gameLogic.c
 *
 *  Created on: Nov 19, 2024
 *      Author: trevo
 */

#include "gameLogic.h"

static bool Alive = 1;
static bool GameState[10][20];
static uint8_t CurrentBlockPos[2];
static uint8_t CurrentBlockNum; //init this to 7
static Game_Block *CurrentBlock;
static Game_Block *AllBlocks[19];
static uint16_t singleClears =0;
static uint16_t doubleClears =0;
static uint16_t trippleClears =0;
static uint16_t tetrisClears =0;

void Game_init(){
	for(int i = 0; i<19;i++){
		AllBlocks[i]=(Game_Block *)malloc(sizeof(Game_Block));
	}
	for(int i = 0; i<SHAPE_ARR_SIZE; i++){
		for(int j = 0; j<SHAPE_ARR_SIZE;j++){
			AllBlocks[SQUARE_NUM]->Shape[i][j]=SQUARE_BLOCK.Shape[i][j];

			AllBlocks[LINE_NUM]->Shape[i][j]=LINE_BLOCK.Shape[i][j];
			AllBlocks[LINE_NUM_VERT]->Shape[i][j]=LINE_BLOCK_VERT.Shape[i][j];

			AllBlocks[RL_NUM]->Shape[i][j]=RL_BLOCK.Shape[i][j];
			AllBlocks[RL_NUM_90]->Shape[i][j]=RL_BLOCK_90.Shape[i][j];
			AllBlocks[RL_NUM_180]->Shape[i][j]=RL_BLOCK_180.Shape[i][j];
			AllBlocks[RL_NUM_270]->Shape[i][j]=RL_BLOCK_270.Shape[i][j];

			AllBlocks[L_NUM]->Shape[i][j]=L_BLOCK.Shape[i][j];
			AllBlocks[L_NUM_90]->Shape[i][j]=L_BLOCK_90.Shape[i][j];
			AllBlocks[L_NUM_180]->Shape[i][j]=L_BLOCK_180.Shape[i][j];
			AllBlocks[L_NUM_270]->Shape[i][j]=L_BLOCK_270.Shape[i][j];

			AllBlocks[RS_NUM]->Shape[i][j]=RS_BLOCK.Shape[i][j];
			AllBlocks[RS_NUM_VERT]->Shape[i][j]=RS_BLOCK_VERT.Shape[i][j];

			AllBlocks[S_NUM]->Shape[i][j]=S_BLOCK.Shape[i][j];
			AllBlocks[S_NUM_VERT]->Shape[i][j]=S_BLOCK_VERT.Shape[i][j];

			AllBlocks[T_NUM]->Shape[i][j]=T_BLOCK.Shape[i][j];
			AllBlocks[T_NUM_90]->Shape[i][j]=T_BLOCK_90.Shape[i][j];
			AllBlocks[T_NUM_180]->Shape[i][j]=T_BLOCK_180.Shape[i][j];
			AllBlocks[T_NUM_270]->Shape[i][j]=T_BLOCK_270.Shape[i][j];
		}
	}
	Game_Set_Block(SQUARE_NUM, SQUARE_BLOCK, SQUARE_NUM,SQUARE_NUM);
	Game_Set_Block(LINE_NUM, LINE_BLOCK, LINE_NUM_VERT, LINE_NUM_VERT);
	Game_Set_Block(LINE_NUM_VERT, LINE_BLOCK_VERT, LINE_NUM, LINE_NUM);

	Game_Set_Block(RL_NUM, RL_BLOCK, RL_NUM_90, RL_NUM_270);
	Game_Set_Block(RL_NUM_90, RL_BLOCK_90, RL_NUM_180, RL_NUM);
	Game_Set_Block(RL_NUM_180, RL_BLOCK_180, RL_NUM_270, RL_NUM_90);
	Game_Set_Block(RL_NUM_270, RL_BLOCK_270, RL_NUM, RL_NUM_180);

	Game_Set_Block(L_NUM, L_BLOCK, L_NUM_90, L_NUM_270);
	Game_Set_Block(L_NUM_90, L_BLOCK_90, L_NUM_180, L_NUM);
	Game_Set_Block(L_NUM_180, L_BLOCK_180, L_NUM_270, L_NUM_90);
	Game_Set_Block(L_NUM_270, L_BLOCK_270, L_NUM, L_NUM_180);

	Game_Set_Block(RS_NUM, RS_BLOCK, RS_NUM_VERT, RS_NUM_VERT);
	Game_Set_Block(RS_NUM_VERT, RS_BLOCK_VERT, RS_NUM, RS_NUM);

	Game_Set_Block(S_NUM, S_BLOCK, S_NUM_VERT, S_NUM_VERT);
	Game_Set_Block(S_NUM_VERT, S_BLOCK_VERT, S_NUM, S_NUM);

	Game_Set_Block(T_NUM, T_BLOCK, T_NUM_90, T_NUM_270);
	Game_Set_Block(T_NUM_90, T_BLOCK_90, T_NUM_180, T_NUM);
	Game_Set_Block(T_NUM_180, T_BLOCK_180, T_NUM_270, T_NUM_90);
	Game_Set_Block(T_NUM_270, T_BLOCK_270, T_NUM, T_NUM_180);

	Alive=1;
	CurrentBlockNum=7;
}
void Game_Start(){
	for(int x = 0; x<10; x++){
		for(int y = 0; y<20; y++){
			GameState[x][y]=false;
		}
	}
	Game_Reset_Clears();
	CurrentBlockNum=7;
	Alive = 1;
	Game_Spawn_Block();
}

void Game_Set_Block(uint8_t blockNum, Game_Block block, uint8_t nextBlockNum, uint8_t prevBlockNum){
	AllBlocks[blockNum]->height=block.height;
	AllBlocks[blockNum]->length=block.length;
	AllBlocks[blockNum]->NextBlock=AllBlocks[nextBlockNum];
	AllBlocks[blockNum]->PrevBlock=AllBlocks[prevBlockNum];
}
void Game_Move_Left(){
	if(!Game_Check_Collision(CurrentBlockPos[0]-1,CurrentBlockPos[1])){
		CurrentBlockPos[0]--;
	}
}
void Game_Move_Right(){
	if(!Game_Check_Collision(CurrentBlockPos[0]+1,CurrentBlockPos[1])){
		CurrentBlockPos[0]++;
	}
}
void Game_Rotate_Clock(){
	CurrentBlock=CurrentBlock->NextBlock;
	if(Game_Check_Collision(CurrentBlockPos[0],CurrentBlockPos[1])){
		CurrentBlock=CurrentBlock->PrevBlock;
	}
}
void Game_Rotate_Counter_Clock(){
	CurrentBlock=CurrentBlock->PrevBlock;
	if(Game_Check_Collision(CurrentBlockPos[0],CurrentBlockPos[1])){
		CurrentBlock=CurrentBlock->NextBlock;
	}
}
bool Game_Drop_Block(){
	if(!Game_Check_Collision(CurrentBlockPos[0],CurrentBlockPos[1]+1)){
		CurrentBlockPos[1]++;
		return true;
	}
	Game_Lock_Block();
	return false;
}
void Game_Lock_Block(){
	for(int x = 0; x<CurrentBlock->length; x++){
		for(int y = 0; y<CurrentBlock->height;y++){
			if(CurrentBlock->Shape[y][x]){
				GameState[CurrentBlockPos[0]+x][CurrentBlockPos[1]+y]=true;
			}
		}
	}
}
void Game_Spawn_Block(){//could have this return a bool in order to not have the alive bool
#if ONLY_LINE_PEICES
	uint8_t blockToSpawn = 1;
#else
	uint8_t blockToSpawn = (uint8_t)(RNG_getRandom()%8);
	if(blockToSpawn == CurrentBlockNum||blockToSpawn == BLOCK_OVERFLOW_NUM){
		blockToSpawn = (uint8_t)(RNG_getRandom()%7);
	}
#endif
	CurrentBlockNum = blockToSpawn;
	CurrentBlock = AllBlocks[blockToSpawn];
	CurrentBlockPos[0]=4;
	CurrentBlockPos[1]=0;
	if(Game_Check_Collision(CurrentBlockPos[0],CurrentBlockPos[1])){
		Alive = false;
	}
}
void Game_Find_Clear_Lines(){
	uint8_t numLines = 0;
	uint8_t minHeight = 0;
	uint8_t numLinesCleared = 0;
	for(int i = 19; i>=minHeight;i--){
		bool fullLine = true;
		for(int j=0;j<10;j++){
			if(!GameState[j][i]){
				fullLine = false;
			}
		}
		if(fullLine){
			numLines++;
			Game_Clear_Line(i);
			numLinesCleared++;
			minHeight++;
			i++;
		}
	}
	if(numLinesCleared==1){
		singleClears++;
		return;
	}
	if(numLinesCleared==2){
		doubleClears++;
		return;
	}
	if(numLinesCleared==3){
		trippleClears++;
		return;
	}
	if(numLinesCleared==4){
		tetrisClears++;
		return;
	}

}
void Game_Clear_Line(uint8_t lineNum){
	for(int i = lineNum; i>0;i--){
		for(int j = 0; j<10; j++){
			GameState[j][i]=GameState[j][i-1];
		}
	}
	for(int i = 0; i<10; i++){
		GameState[i][0]=false;
	}
}
bool Game_Check_Collision(uint8_t newX, uint8_t newY){
	//out of bounds
	if(newX<0||(newX+CurrentBlock->length)>10||(newY+CurrentBlock->height)>20){
		return true;
	}
	//collision w/ blocks
	for(int x = 0; x<CurrentBlock->length; x++){
		for(int y = 0; y<CurrentBlock->height;y++){
			if(CurrentBlock->Shape[y][x]&GameState[newX+x][newY+y]){
				return true;
			}
		}
	}
	return false;
}
bool Game_Check_Alive(){
	return Alive;
}
uint8_t Game_get_Xcord(){
	return CurrentBlockPos[0];
}
uint8_t Game_get_Ycord(){
	return CurrentBlockPos[1];
}
Game_Block *Game_get_Current_Block(){
	return CurrentBlock;
}
bool Game_get_State_At(uint8_t x, uint8_t y){
	return GameState[x][y];
}
uint16_t Game_get_Single_Clears(){
	return singleClears;
}
uint16_t Game_get_Double_Clears(){
	return doubleClears;
}
uint16_t Game_get_Tripple_Clears(){
	return trippleClears;
}
uint16_t Game_get_Tetris_Clears(){
	return tetrisClears;
}
void Game_Reset_Clears(){
	singleClears=0;
	doubleClears=0;
	trippleClears=0;
	tetrisClears=0;
}
