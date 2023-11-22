/*****************************************************************//**
 * \file   main.c
 * 
 * \author Eduardo Queir�s, Jo�o Lima, Lu�s Gon�alves
 * \date   November 2023
 *********************************************************************/
#include<stdio.h>
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
 * \brief- Mostra ao utilizador os edif�cios de gondor
 * 
 *  
 */
void showGondorFactory() 
{
	//declarar as variaveis dos edificios de gondor
	struct faction gondor = { "Gondor", "GGGG", "SS", "RR", "LL", "GF" }; //como � o lado gondor
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
 * \brief- Mostra ao utilizador os edif�cios de mordor
 * 
 *  
 */
void showMordorFactory()
{
	//declarar as variaveis dos edificios de mordor
	struct faction mordor = { "Mordor", "MMMM", "EE", "II", "MK", "DF" }; //como � o lado mordor
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
void gordorMenu() {

	int gordorOption;
	printf("WELCOME TO GORDOR SIDE\n");

	gordorPlayer player1 = { "Player 1", 100, 0, 0, 0, 0 };
	printStatus(&player1);

	char unit_type;
	int cells;

	printf("Enter your move (unit type - I/C/A, cells): ");
	scanf(" %c %d", &unit_type, &cells);

	move(&player1, unit_type, cells);
	collectMineIncome(&player1);

	printStatus(&player1);




}

/**
 *
 * \function name- mordorMenu
 * \brief- Menu para mordor
 */
void mordorMenu() {
	int mordorOption;
	printf("WELCOME TO MORDOR SIDE\n");
}
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

