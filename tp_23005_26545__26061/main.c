/*****************************************************************//**
 * \file   main.c
 * 
 * \author Eduardo Queir�s, Jo�o Lima, Lu�s Gon�alves
 * \date   November 2023
 *********************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "Header.h"
#pragma warning(disable: 4996)


#pragma region Main menu

/**
 *
 * \function name- mainMenu
 * \brief- Este � o primeiro menu que aparece quando se inicializa o jogo
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

	int mainOption =  mainMenu();	
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
	int newOption; //opcao para escolher o que fazer quando se come�a um novo jogo
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
	#pragma region Moves/buildings

int gordorMovesMenu()
{
	int gordorSecOption;
	printf("1- Print field: \n");
	printf("2- Print Gordor Status: \n");
	printf("3- Insert Base Gondor: \n");
	printf("4- Insert Barrack\n");
	printf("5- Insert Stable\n");
	printf("6- Insert Infantry\n");
	printf("7- Insert Cavalry\n");
	printf("8- Insert Artillhery\n");
	printf("9- Choose the unit that you wanna move (I / C/ A)\n"); // I -> infantry, C-> cavalry, A -> artillery
	printf("10- Show my coins: \n"); //podemos ou nao ter isto, dps v�-se
	printf("11- Back to the New Game Menu: \n");
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
	int opcaoMoves;
	int resultado;
	// *********para imprimir o campo de batalha********
	
	gordorPlayer *gordPlayer = NULL;
	mordorPlayer *mordPLayer = NULL;
	//***********************************************
	

	do {
		opcaoMoves = gordorMovesMenu();
		switch (opcaoMoves) {
		case 1:	printfField();
			break;

		case 2:printf("Factory\n");
			showGondorFactory(gordPlayer);
			printf("Units\n");
			showGondorUnits(gordPlayer);
			break;
			/* 
		case 3: printf("Where do you wanna insert your base? \n");
			//scanf_s("%s", );
			//resultado = createBaseGondor();
			break;

		case 4:printf("Where do you wanna insert the barrack? \n");
			//scanf_s("%s", );
			//resultado = createBaseGondor();
			break;

		case 5:printf("Where do you wanna insert the stable? \n");
			//scanf_s("%s", );
			//resultado = createBaseGondor();
			break;

		case 6:printf("Where do you wanna insert the infantry unit? \n");
			//scanf_s("%s", );
			//resultado = createBaseGondor();
			break;

		case 7:printf("Where do you wanna insert the cavalry unit? \n");
			//scanf_s("%s", );
			//resultado = createBaseGondor();
			break;

		case 8:printf("Where do you wanna insert the artillery unit? \n");
			//scanf_s("%s", );
			//resultado = createBaseGondor();
			break;

		case 9:printf("Where do you wanna insert your base? \n");
			//scanf_s("%s", );
			//resultado = createBaseGondor();
			break;
			*/
		case 10: showCoinsGondor(gordPlayer, mordPLayer);
			break;

		case 11: NewGame();
			break;
		case 0: printf("Leaving...!!!\n");
			break;
		}
	} while (opcaoMoves != 0);
}

int mordorMenu() {

}


/**
 *
 * \function name- gordorBuildingBattle
 * \brief- Escolher quais os edificios que queremos adicionar
 *  
 */
/*
gordorBuildingBattle() 
{
	gordorPlayer player1 = { "Player 1", 100, 0, 0, 0,};
	char building_type;
	char unit_type;

	printf("Enter building type (B/M/R/S/A):\n ");
	scanf_s(" %c", &building_type);

	buildBuilding(&player1, building_type);

}
*/
	#pragma endregion


#pragma endregion

#pragma region Load Game

int LoadGameMenu()
{
	int loadOption; //opcao para escolher o que fazer quando se carrega um jogo ja existente
}
int LoadGame() {

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

