/*****************************************************************//**
 * \file   main.c
 *
 * \author Eduardo Queirós, João Lima, Luís Gonçalves
 * \date   November 2023
 *********************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "Header.h"
#pragma warning(disable: 4996)
#define ROWS 17
#define COLS 26

entity field[ROWS][COLS];

#pragma region Main menu

/**
 *
 * \function name- mainMenu
 * \brief- Este é o primeiro menu que aparece quando se inicializa o jogo
 *
 */
int mainMenu()
{
	int opcaoPrincipal;
	printf("WELCOME TO THE GAME OF THE RINGS\n");
	printf("*********************************\n");
	printf("1- Start new game\n");
	printf("2- Load game\n");
	printf("3- Settings\n");
	printf("0- Exit\n");
	printf("*********************************\n");
	printf("Option: ");
	scanf_s("%d", &opcaoPrincipal);
	printf("*********************************\n");
	return(opcaoPrincipal);

}

int main()
{
	startGame();
	int field[17][26];

	int mainOption = mainMenu();
	switch (mainOption)
	{
	case 1: NewGame();
		break;
	case 2: LoadGame();
		break;
	case 3: Settings();
		break;
	case 0: printf("Leaving...\n");
		break;
	}

}

#pragma endregion

#pragma region New game

/**
 *
 * \function name- NewGame
 * \brief- Menu para escolher se queremos jogar em mordor ou gondor
 *
 */
int NewGame()
{
	int optionNewgame;

	optionNewgame = StartNewGameMenu();
	switch (optionNewgame)
	{
	case 1: gordorMenu();
		break;
	case 2: mordorMenu();
		break;
	default:printf("Invalid option...\nLeaving...\n");
		break;
	}
}
/**
 *
 * \function name- StartNewGameMenu
 * \brief- Menu para escolher o lado que se quer jogar
 *
 */
int StartNewGameMenu()
{
	gordorPlayer gordPlayer;
	mordorPlayer mordPlayer;

	gordPlayer.coins = 100;
	mordPlayer.coins = 100;

	int newOption; //opcao para escolher o que fazer quando se começa um novo jogo
	printf("CHOOSE YOUR SIDE\n");
	printf("1- Gondor/Rivendell\n");
	printf("2- Mordor\n");
	printf("*********************************\n");
	printf("Option: ");
	scanf_s("%d", &newOption);
	printf("*********************************\n");
	return(newOption);

}
/**
 *
 * \function name- gordorMenu
 * \brief- Menu para gordor
 *
 */
int gordorMenu() {

	int gordorOption;

	printf("WELCOME TO GORDOR SIDE\n");

	gordorOption = gordorMovesBattle();
}


int mordorMenu() {

	int mordorOption;

	printf("WELCOME TO MORDOR SIDE\n");

	mordorOption = mordorMovesBattle();

}

#pragma region Moves/buildings 
#pragma region Moves/buildings - mordor
int mordorMovesMenu()
{
	int mordorSecOption;
	printf("1- Print field: \n");
	printf("2- Print Mordor Status: \n");
	printf("3- Insert Base Mordor: \n");
	printf("4- Insert Mine Mordor: \n");
	printf("5- Insert Barrack\n");
	printf("6- Insert Stable\n");
	printf("7- Insert Armourty\n");
	printf("8- Insert Infantry\n");
	printf("9- Insert Cavalry\n");
	printf("10- Insert Artillhery\n");
	printf("11- Move Units\n"); // I -> infantry, C-> cavalry, A -> artillery
	printf("12- Atack\n");
	printf("13- Show my coins: \n"); //podemos ou nao ter isto, dps vê-se
	printf("14- Back to the New Game Menu: \n");
	printf("15- SAVE!!!\n");
	printf("0- Exit\n");
	printf("***********************\n");
	printf("Opcao: \n");
	scanf_s("%d", &mordorSecOption);
	return(mordorSecOption);
}

int mordorMovesBattle()
{
	mordorPlayer mPlayer;
	gordorPlayer gPlayer;
	mPlayer.coins = 100;

	mPlayer.infantryHealth = 100;
	mPlayer.cavalryHealth = 100;
	mPlayer.artilleryHealth = 100;

	mPlayer.mBaseHealth = 100;
	mPlayer.mMineHealth = 100;
	mPlayer.mBarrackHealth = 100;
	mPlayer.mStableHealth = 100;
	mPlayer.mArmouryHealth = 100;

	int opcaoMoves;
	int resultado;
	// *********para imprimir o campo de batalha********

	//gordorPlayer *gordPlayer = NULL;

	//***********************************************
	int row;
	char col; //variaveis para escolher onde o utilizador quer inserir a base

	int barrackRow;
	char barrackCol;
	initializeGrid(field);

	do {
		opcaoMoves = mordorMovesMenu();
		switch (opcaoMoves) {
		case 1:	printField();
			break;
			/*
		case 2:printf("Factory\n");
			showGondorFactory(gordPlayer);
			printf("Units\n");
			showGondorUnits(gordPlayer);
			break;*/

		case 3:placingBaseM(&mPlayer);
			break;
		case 4: placingMineM(&mPlayer);
			break;
		case 5:placingBarrackM(&mPlayer);
			break;
		case 6:placingStableM(&mPlayer);
			break;
		case 7: placingArmouryM(&mPlayer);
			break;
		case 8:placingInfantryM(&mPlayer);
			break;
		case 9:placingCavalryM(&mPlayer);
			break;
		case 10:placingArtilleryM(&mPlayer);
			break;
		case 11: moveMordorUnits(&mPlayer);
			break;
		case 12:mordorAttackBattle();
			break;
			/*
		case 11: showCoinsGondor(gordPLayer, mordPlayer);
			break;
			*/
		case 13: showCoinsGondor(&mPlayer);
			break;
		case 14: NewGame();
			break;
		case 15: save("Game.txt", &gPlayer, &mPlayer);
			break;
		case 0: printf("Leaving...!!!\n");
			break;
		}

	} while (opcaoMoves != 0);
}

#pragma region Movements from mordor

int mordorMovesUnit()
{
	int mordorOption;
	printf("------------------\n");
	printf("1- Move Infantry: \n");
	printf("2- Move Cavalry: \n");
	printf("3- Move Artillery: \n");
	printf("0- Return\n");
	printf("------------------\n");
	printf("Opcao: \n");
	scanf_s("%d", &mordorOption);
	return(mordorOption);
}

/**
 *
 * \function name- move
 * \params- player
 * \params- unitType
 * \params- cells
 * \brief- Movimento das units e calcula respetivo custo
 *
 *
 */
int moveMordorUnits(mordorPlayer* mordorPlayer) {

	int opcaoMovesUnits;
	showCoinsGondor(mordorPlayer);
	do {
		opcaoMovesUnits = mordorMovesUnit();
		switch (opcaoMovesUnits) {
		case 1:
			moveInfantryMordor(mordorPlayer);
			break;
		case 2:
			moveCavalryMordor(mordorPlayer);
			break;
		case 3:
			moveArtilleryMordor(mordorPlayer);
			break;
		case 0: printf("Returning...!!!\n");
			mordorMovesBattle();
			break;
		default:
			printf("Invalid unit type.\n");
			return;
		}

	} while (opcaoMovesUnits != 0);
}

#pragma endregion

#pragma endregion


#pragma region Moves/buildings gondor

int gordorMovesMenu()
{
	int gordorSecOption;
	printf("1- Print field: \n");
	printf("2- Print Gordor Status: \n");
	printf("3- Insert Base Gondor: \n");
	printf("4- Insert Mine Gondor: \n");
	printf("5- Insert Barrack\n");
	printf("6- Insert Stable\n");
	printf("7- Insert Armourty\n");
	printf("8- Insert Infantry\n");
	printf("9- Insert Cavalry\n");
	printf("10- Insert Artillhery\n");
	printf("11- Move Units\n"); // I -> infantry, C-> cavalry, A -> artillery
	printf("12- Atack\n");
	printf("13- Show my coins: \n"); //podemos ou nao ter isto, dps vê-se
	printf("14- Back to the New Game Menu: \n");
	printf("15- SAVE!\n");
	printf("0- Exit\n");
	printf("***********************\n");
	printf("Opcao: \n");
	scanf_s("%d", &gordorSecOption);
	return(gordorSecOption);
}
/**
 *
 * \function name- gordorMovesBattle
 * \brief- Para realizar o que fzr dps de escolher mos o que fzr

 *
 */
int gordorMovesBattle()
{
	gordorPlayer gPlayer;
	mordorPlayer mPlayer;
	gPlayer.coins = 100;

	int r = 0, c = 0;

	gPlayer.infantryHealth = 100;
	gPlayer.cavalryHealth = 100;
	gPlayer.artilleryHealth = 100;

	gPlayer.gBaseHealth = 100;
	gPlayer.gMineHealth = 100;
	gPlayer.gBarrackHealth = 100;
	gPlayer.gStableHealth = 100;
	gPlayer.gArmouryHealth = 100;

	mPlayer.infantryHealth = 100;
	mPlayer.cavalryHealth = 100;
	mPlayer.artilleryHealth = 100;

	mPlayer.mBaseHealth = 100;
	mPlayer.mMineHealth = 100;
	mPlayer.mBarrackHealth = 100;
	mPlayer.mStableHealth = 100;
	mPlayer.mArmouryHealth = 100;

	int opcaoMoves;
	int resultado;
	initializeGrid(field);

	do {
		opcaoMoves = gordorMovesMenu();
		switch (opcaoMoves) {
		case 1:
			printField();
			break;
			/*
		case 2:printf("Factory\n");
			showGondorFactory(gordPlayer);
			printf("Units\n");
			showGondorUnits(gordPlayer);
			break;*/

		case 3:placingBaseG(&gPlayer);
			break;
		case 4: placingMineG(&gPlayer);
			break;
		case 5:placingBarrackG(&gPlayer);
			break;
		case 6:placingStableG(&gPlayer);
			break;
		case 7: placingArmouryG(&gPlayer);
			break;
		case 8:placingInfantryG(&gPlayer);
			break;
		case 9:placingCavalryG(&gPlayer);
			break;
		case 10:placingArtilleryG(&gPlayer);
			break;

		case 11: moveGordorUnits(&gPlayer);
		case 12:gordorAttackBattle();
			break;
		case 13: showCoinsGondor(&gPlayer);
			break;
		case 14: NewGame();
			break;
		case 15: save("Game.txt", &gPlayer, &mPlayer);
			break;

		case 0: printf("Leaving...!!!\n");
			break;
		}

	} while (opcaoMoves != 0);
}

#pragma endregion

#pragma region atack from gondor to mordor
int gondorAtackOption()
{
	mordorPlayer mordplayer;

	mordplayer.mBaseHealth = 100;

	int gordorSecOption;
	printf("--------------------------------------------------------\n");
	printf("1- Attack mordor base with infantry \n");
	printf("2- Attack mordor base with cavalry \n");
	printf("3- Attack mordor base with artillery \n");
	printf("4- Attack mordor mine with infantry \n");
	printf("5- Attack mordor mine with cavalry \n");
	printf("6- Attack mordor mine with artillery \n");
	printf("7- Attack mordor barrack with infantry\n");
	printf("8- Attack mordor barrack with cavalry\n");
	printf("9- Attack mordor barrack with artillery\n");
	printf("10- Attack mordor stable with infantry\n");
	printf("11- Attack mordor stable with cavalry\n");
	printf("12- Attack mordor stable with artillery\n");
	printf("13- Attack mordor armoury with infantry \n");
	printf("14- Attack mordor armoury with cavalry \n");
	printf("15- Attack mordor armoury with artillery \n");
	printf("16- Attack mordor infantry with gondor infantry \n");
	printf("17- Attack mordor infantry with gondor cavalry \n");
	printf("18- Attack mordor infantry with gondor artillery \n");
	printf("19- Attack mordor cavalry with gondor infantry \n");
	printf("20- Attack mordor cavalry with gondor cavalry \n");
	printf("21- Attack mordor cavalry with gondor artillery \n");
	printf("22- Attack mordor artillery with gondor infantry\n");
	printf("23- Attack mordor artillery with gondor cavalry \n");
	printf("24- Attack mordor artillery with gondor artillery \n");
	printf("0- Return\n");
	printf("--------------------------------------------------------\n");
	printf("Opcao: \n");
	scanf_s("%d", &gordorSecOption);
	return(gordorSecOption);
}

/**
 *
 * \function name- gordorMovesBattle
 * \brief- Para realizar o que fzr dps de escolher mos o que fzr

 *
 */
int gordorAttackBattle()
{
	gordorPlayer gPlayer;
	mordorPlayer mPlayer;



	int row = 0;
	int col = 0;

	int opcaoAttack;
	int resultado;

	printf("--------------------------------------------------------\n");
	printf("1- Attack mordor base with infantry \n");
	printf("2- Attack mordor base with cavalry \n");
	printf("3- Attack mordor base with artillery \n");
	printf("4- Attack mordor mine with infantry \n");
	printf("5- Attack mordor mine with cavalry \n");
	printf("6- Attack mordor mine with artillery \n");
	printf("7- Attack mordor barrack with infantry\n");
	printf("8- Attack mordor barrack with cavalry\n");
	printf("9- Attack mordor barrack with artillery\n");
	printf("10- Attack mordor stable with infantry\n");
	printf("11- Attack mordor stable with cavalry\n");
	printf("12- Attack mordor stable with artillery\n");
	printf("13- Attack mordor armoury with infantry \n");
	printf("14- Attack mordor armoury with cavalry \n");
	printf("15- Attack mordor armoury with artillery \n");
	printf("16- Attack mordor infantry with gondor infantry \n");
	printf("17- Attack mordor infantry with gondor cavalry \n");
	printf("18- Attack mordor infantry with gondor artillery \n");
	printf("19- Attack mordor cavalry with gondor infantry \n");
	printf("20- Attack mordor cavalry with gondor cavalry \n");
	printf("21- Attack mordor cavalry with gondor artillery \n");
	printf("22- Attack mordor artillery with gondor infantry\n");
	printf("23- Attack mordor artillery with gondor cavalry \n");
	printf("24- Attack mordor artillery with gondor artillery \n");
	printf("0- Return\n");
	printf("--------------------------------------------------------\n");
	printf("Opcao: \n");
	scanf_s("%d", &opcaoAttack);

	do {
		/*opcaoAttack = gondorAtackOption();*/
		switch (opcaoAttack) {
		case 1:	GondorInfantryVSMordBase(row, col, &mPlayer);
			/* saadasdsa();*/
			break;
		case 2:GondorCavalryVSMordBase(row, col, &mPlayer);
			break;
		case 3: GondorArtilleryVSMordBase(row, col, &mPlayer);
			break;
		case 4:GondorInfantryVSMordMine(row, col, &mPlayer);
			break;
		case 5:GondorCavalryVSMordMine(row, col, &mPlayer);
			break;
		case 6: GondorArtilleryVSMordMine(row, col, &mPlayer);
			break;
		case 7:GondorInfantrVSMordBarrack(row, col, &mPlayer);
			break;
		case 8:GondorCavalryVSMordBarrack(row, col, &mPlayer);
			break;
		case 9:GondorArtilleryVSMordBarrack(row, col, &mPlayer);
			break;
		case 10: GondorInfantrVSMordStable(row, col, &mPlayer);
			break;
		case 11: GondorCavalryVSMordStable(row, col, &mPlayer);
			break;
		case 12: GondorArtilleryVSMordStable(row, col, &mPlayer);
			break;
		case 13: GondorInfantrVSMordArmoury(row, col, &mPlayer);
			break;
		case 14: GondorCavalryVSMordArmoury(row, col, &mPlayer);
			break;
		case 15: GondorArtilleryVSMordArmoury(row, col, &mPlayer);
			break;
		case 16: GondorInfantrVSMordInfantry(row, col, &mPlayer);
			break;
		case 17: GondorCavalryVSMordInfantry(row, col, &mPlayer);
			break;
		case 18: GondorArtilleryVSMordInfantry(row, col, &mPlayer);
			break;

		case 19: GondorInfantryVSMordCavalry(row, col, &mPlayer);
			break;
		case 20: GondorCavalryVSMordCavalry(row, col, &mPlayer);
			break;
		case 21: GondorArtillheryVSMordCavalry(row, col, &mPlayer);
			break;
		case 22: GondorInfantryVSMordArtillhery(row, col, &mPlayer);
			break;
		case 23: GondorCavalryVSMordArtillhery(row, col, &mPlayer);
			break;
		case 24: GondorArtilleryVSMordArtillhery(row, col, &mPlayer);
			break;
		case 0: printf("Returning...!!!\n");
			gordorMovesBattle();
			break;
		}

	} while (opcaoAttack != 0);
}
#pragma endregion

#pragma region atack from mordor to gondor
int mordorAttackBattle()
{
	gordorPlayer gPlayer;
	mordorPlayer mPlayer;
	int row = 0;
	int col = 0;

	int opcaoAttack;
	int resultado;

	printf("--------------------------------------------------------\n");
	printf("1- Attack gondor base with infantry \n");
	printf("2- Attack gondor base with cavalry \n");
	printf("3- Attack gondor base with artillery \n");
	printf("4- Attack gondor mine with infantry \n");
	printf("5- Attack gondor mine with cavalry \n");
	printf("6- Attack gondor mine with artillery \n");
	printf("7- Attack gondor barrack with infantry\n");
	printf("8- Attack gondor barrack with cavalry\n");
	printf("9- Attack gondor barrack with artillery\n");
	printf("10- Attack gondor stable with infantry\n");
	printf("11- Attack gondor stable with cavalry\n");
	printf("12- Attack gondor stable with artillery\n");
	printf("13- Attack gondor armoury with infantry \n");
	printf("14- Attack gondor armoury with cavalry \n");
	printf("15- Attack gondor armoury with artillery \n");
	printf("16- Attack gondor infantry with mordor infantry \n");
	printf("17- Attack gondor infantry with mordor cavalry \n");
	printf("18- Attack gondor infantry with mordor artillery \n");
	printf("19- Attack gondor cavalry with mordor infantry \n");
	printf("20- Attack gondor cavalry with mordor cavalry \n");
	printf("21- Attack gondor cavalry with mordor artillery \n");
	printf("22- Attack gondor artillery with mordor infantry\n");
	printf("23- Attack gondor artillery with mordor cavalry \n");
	printf("24- Attack gondor artillery with mordor artillery \n");
	printf("0- Return\n");
	printf("--------------------------------------------------------\n");
	printf("Opcao: \n");
	scanf_s("%d", &opcaoAttack);

	do {
		/*opcaoAttack = gondorAtackOption();*/
		switch (opcaoAttack) {
		case 1:	GondorInfantryVSMordBase(row, col, &mPlayer);
			/* saadasdsa();*/
			break;
		case 2:GondorCavalryVSMordBase(row, col, &mPlayer);
			break;
		case 3: GondorArtilleryVSMordBase(row, col, &mPlayer);
			break;
		case 4:GondorInfantryVSMordMine(row, col, &mPlayer);
			break;
		case 5:GondorCavalryVSMordMine(row, col, &mPlayer);
			break;
		case 6: GondorArtilleryVSMordMine(row, col, &mPlayer);
			break;
		case 7:GondorInfantrVSMordBarrack(row, col, &mPlayer);
			break;
		case 8:GondorCavalryVSMordBarrack(row, col, &mPlayer);
			break;
		case 9:GondorArtilleryVSMordBarrack(row, col, &mPlayer);
			break;
		case 10: GondorInfantrVSMordStable(row, col, &mPlayer);
			break;
		case 11: GondorCavalryVSMordStable(row, col, &mPlayer);
			break;
		case 12: GondorArtilleryVSMordStable(row, col, &mPlayer);
			break;
		case 13: GondorInfantrVSMordArmoury(row, col, &mPlayer);
			break;
		case 14: GondorCavalryVSMordArmoury(row, col, &mPlayer);
			break;
		case 15: GondorArtilleryVSMordArmoury(row, col, &mPlayer);
			break;
		case 16: GondorInfantrVSMordInfantry(row, col, &mPlayer);
			break;
		case 17: GondorCavalryVSMordInfantry(row, col, &mPlayer);
			break;
		case 18: GondorArtilleryVSMordInfantry(row, col, &mPlayer);
			break;

		case 19: GondorInfantryVSMordCavalry(row, col, &mPlayer);
			break;
		case 20: MordCavalryVSGondCavalry(row, col, &mPlayer);
			break;
		case 21: GondorArtillheryVSMordCavalry(row, col, &mPlayer);
			break;
		case 22: GondorInfantryVSMordArtillhery(row, col, &mPlayer);
			break;
		case 23: GondorCavalryVSMordArtillhery(row, col, &mPlayer);
			break;
		case 24: GondorArtilleryVSMordArtillhery(row, col, &mPlayer);
			break;
		case 0: printf("Returning...!!!\n");
			gordorMovesBattle();
			break;
		}

	} while (opcaoAttack != 0);
}
#pragma endregion


#pragma region Movements from gondor

int gordorMovesUnit()
{
	int gordorOption;
	printf("------------------\n");
	printf("1- Move Infantry: \n");
	printf("2- Move Cavalry: \n");
	printf("3- Move Artillery: \n");
	printf("0- Return\n");
	printf("------------------\n");
	printf("Opcao: \n");
	scanf_s("%d", &gordorOption);
	return(gordorOption);
}
/**
 *
 * \function name- move
 * \params- player
 * \params- unitType
 * \params- cells
 * \brief- Movimento das units e calcula respetivo custo
 *
 *
 */
int moveGordorUnits(gordorPlayer* gordPlayer) {

	int opcaoMovesUnits;
	showCoinsGondor(gordPlayer);
	//printf("Wich unit you wanna move( I -> 1 / C -> 2 / A -> 3 )? \n");
	//scanf_s("%d", &opcaoMovesUnits);

	do {
		opcaoMovesUnits = gordorMovesUnit();
		switch (opcaoMovesUnits) {
		case 1:
			moveInfantryGondor(gordPlayer);
			break;
		case 2:
			moveCavalryGondor(gordPlayer);
			break;
		case 3:
			moveArtilleryGondor(gordPlayer);
			break;
		case 0: printf("Returning...!!!\n");
			gordorMovesBattle();
			break;
		default:
			printf("Invalid unit type.\n");
			return;
		}

	} while (opcaoMovesUnits != 0);
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region Load Game

int LoadGameMenu()
{
	int loadOption; //opcao para escolher o que fazer quando se carrega um jogo ja existente

	loadOption = LoadGame();
	switch (loadOption)
	{
	case 1: gordorMenu();
		break;
	case 2: mordorMenu();
		break;
	default:printf("Invalid option...\nLeaving...\n");
		break;
	}
}
int LoadGame() 
{
	gordorPlayer gPlayer;
	mordorPlayer mPlayer;
	load("Game.txt", &gPlayer, &mPlayer);

	int lOption;

	printf("CHOOSE YOUR SIDE\n");
	printf("1- Gondor/Rivendell\n");
	printf("2- Mordor\n");
	printf("*********************************\n");
	printf("Option: ");
	scanf_s("%d", &lOption);
	printf("*********************************\n");
	return(lOption);
}
#pragma endregion

#pragma region Settings


int SettingsMenu()
{
	int setOption; //opcao para escolher o que fazer nas definicoes
}
int Settings() {

}
#pragma endregion


