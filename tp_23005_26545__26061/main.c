/*****************************************************************//**
 * \file   main.c
 * 
 * \author Eduardo Queir�s, Jo�o Lima, Lu�s Gon�alves
 * \date   November 2023
 *********************************************************************/
#include<stdio.h>

/**
 *
 * \function name- menuPrincipal
 * \brief- Esta fun��o ser� utilizada como um menu principal do programa. Este menu ser� apresentado no in�cio do programa. 
 *		   A fun��o ir� perguntar ao jogador qual o que ele quer fazer no jogo. 
 *  
 */
int mainMenu() 
{
	int opcaoPrincipal;
	printf("Welcome to the game of the Rings\n");
	printf("1- Start new game\n");
	printf("2- Load game\n");
	printf("3- Settings\n");
	printf("0- Exit\n");
	printf("Option: \n");
	printf("\n");
	printf("\n");
	scanf_s("%d", &opcaoPrincipal);
	return(opcaoPrincipal);

}


int StartNewGameMenu() {

}

int LoadGameMenu() {

}

int SettingsMenu() {

}


int NewGame() {

}

int LoadGame() {

}

int Settings() {

}

int main()
{
	int opPrincipal =  mainMenu();	
	switch (opPrincipal)
	{
	case 1: NewGame();
		break;
	case 2: LoadGame();
		break;
	case 3: Settings();
		break;
	default:printf("Invalid Option!!!!");
		break;
	}

}
