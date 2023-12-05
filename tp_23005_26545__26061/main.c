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
	default:printf("Invalid Option!!!!");
		break;
	}

}
#pragma endregion

#pragma region New game


#pragma region factory
/**
 *
 * \function name- showGondorFactory
 * \brief- Mostra ao utilizador os edifícios de gondor
 * 
 *  
 */
void showGondorFactory() 
{
	//declarar as variaveis dos edificios de gondor
	struct faction gondor = { "Gondor", "GGGG", "SS", "RR", "LL", "GF" }; //como é o lado gondor
	printf("Faction: %s\n", gondor.factionName);
	printf("Base: %s\n", gondor.base);
	printf("Mine: %s\n", gondor.mine);
	printf("Barracks: %s\n", gondor.barracks);
	printf("Stables: %s\n", gondor.stables);
	printf("Armoury: %s\n", gondor.armoury);
}
/**
 *
 * \function name- showMordorFactory
 * \brief- Mostra ao utilizador os edifícios de mordor
 * 
 *  
 */
void showMordorFactory()
{
	//declarar as variaveis dos edificios de mordor
	struct faction mordor = { "Mordor", "MMMM", "EE", "II", "MK", "DF" }; //como é o lado mordor
	printf("Faction: %s\n", mordor.factionName);
	printf("Base: %s\n", mordor.base);
	printf("Mine: %s\n", mordor.mine);
	printf("Barracks: %s\n", mordor.barracks);
	printf("Stables: %s\n", mordor.stables);
	printf("Armoury: %s\n", mordor.armoury);
}
#pragma endregion

#pragma region Units


/**
 *
 * \function name- showGondorUnits
 * \brief- Mostra ao utilizador quais as unidades de militares de gondor
 * 
 *  
 */
void showGondorUnits() 
{
	//declarar as unidades de batalha de gondor
	struct gondorUnits gUnit = {"G", "SK", "T" };

	printf("Gondor Units: \n");
	printf("Infantry: %\n", gUnit.infantry);
	printf("Cavalry: %s\n", gUnit.cavalry);
	printf("Artillery: %s\n", gUnit.artillery);
}

/**
 *
 * \function name- showGondorUnits
 * \brief- Mostra ao utilizador quais as unidades de militares de mordor
 *
 *
 */
void showMordorUnits()
{
	//declarar as unidades de batalha de mordor
	struct mordorUnits mUnit = { "OW", "W", "ST" };
	printf("Mordor Units: \n");
	printf("Infantry: %s\n", mUnit.infantry);
	printf("Cavalry: %s\n", mUnit.cavalry);
	printf("Artillery: %s\n", mUnit.artillery);
}
#pragma endregion

/**
 *
 * \function name- StartNewGameMenu
 * \brief- Menu para escolher o lado que se quer jogar
 *  
 */
int StartNewGameMenu() 
{
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
void gordorMenu() {

	int gordorOption;
	printf("WELCOME TO GORDOR SIDE\n");

	gordorOption = gordorMovesMenu();
	switch (gordorOption) {
	case 1: gordorMovesBattle();
		break;
	case 2:
		break;
	default: printf("Invalid Option!!!\n");
		break;
	}

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
	printf("10- Show my coins: \n"); //podemos ou nao ter isto, dps vê-se
	printf("11- Back to the New Game Menu: \n");
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
	gordorPlayer* gordPlayer = NULL;
	mordorPlayer* mordPLayer = NULL;
	//***********************************************

	opcaoMoves = gordorMovesMenu();

	switch (opcaoMoves) {

	case 1:	printfField(gordPlayer, mordPLayer);
		break;

	case 2:showGondorFactory(gordPlayer);
		printf("Units\n");
		showGondorUnits(gordPlayer);
		break;
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

	case 10: showCoinsGondor(gordPlayer);
		break;

	case 11: StartNewGameMenu();
		break;
	default: printf("Invalid option!!!!\n");
		break;
	}

}

int mordorMovesBattle() {

	int mordSecOption;
	printf("1- Print field: \n");
	printf("2- Print Gordor Status: \n");
	printf("3- Insert Base Gondor: \n");
	printf("4- Insert Barrack\n");
	printf("5- Insert Stable\n");
	printf("6- Insert Infantry\n");
	printf("7- Insert Cavalry\n");
	printf("8- Insert Artillhery\n");
	printf("9- Choose the unit that you wanna move (I / C/ A)\n"); // I -> infantry, C-> cavalry, A -> artillery
	printf("10- Show my coins: \n"); //podemos ou nao ter isto, dps vê-se
	printf("11- Back to the New Game Menu: \n");
	printf("***********************\n");
	printf("Opcao: \n");
	scanf_s("%d", &mordSecOption);
	return(mordSecOption);
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
	default: printf("Invalid Option!!!!\n");
		break;
	}

}
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

