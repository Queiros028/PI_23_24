/*****************************************************************//**
 * \file   funcoes.c
 * 
 * \author Eduardo Queirós, João Lima, Luís Gonçalves
 * \date   November 2023
 *********************************************************************/
#include <stdio.h>
#include "Header.h"
#pragma warning(disable: 4996)
#define ROWS 17
#define COLS 26


#pragma region Funcoes gerais
printMatriz(int m[][3], int linhas, int colunas)
{
	int i, j;
	for (i = 0; i < linhas; i++) {
		for (j = 0; j < colunas; j++) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}
#pragma endregion

#pragma region gordor functions
/**
 *
 * \function name- printStatus
 * \params- player
 * \brief- Status de um jogador
 * 
 *  
 */

void printStatus(gordorPlayer* player) {
	printf("\nPlayer: %s\n", player->name);
	printf("Coins: %d\n", player->coins);
	printf("Infantry: %d | Cavalry: %d | Artillery: %d\n", player->infantry, player->cavalry, player->artillery);
	printf("Mines: %d\n", player->mines);
}
    #pragma region ENCONOMY AND COSTS
/**
 *
 * \function name- move
 * \params- player
 * \params- unit_type
 * \params- cells
 * \brief- custo movimento
 * 
 *  
 */
void move(gordorPlayer* player, char unitType, int cells) {
    int costPerCell;

    switch (unitType) {
    case 'I':
    case 'i':
        costPerCell = 2; //custo de uma peça de infantaria
        break;
    case 'C':
    case 'c':
        costPerCell = 1;//custo de uma peça de cavalaria
        break;
    case 'A':
    case 'a':
        costPerCell = 3; //custo de uma peça de artilharia
        break;
    default:
        printf("Invalid unit type.\n");
        return;
    }

    int totalCost = costPerCell * cells;

    if (totalCost > player->coins) {
        printf("Not enough coins to make the move.\n");
    }
    else {
        player->coins -= totalCost;
        printf("Moved %c %d cells. Remaining coins: %d\n", unitType, cells, player->coins);
    }
}

/**
 *
 * \function name- collectMineIncome
 * \params- player
 * \brief- Funcao para custo de minas
 * 
 *  
 */
void collectMineIncome(gordorPlayer* player) {
    int mine_income = 5 * player->mines;
    player->coins += mine_income;
    printf("Collected mine income. Total coins: %d\n", player->coins);
}

/**
 *
 * \function name- buildBuilding
 * \params- player
 * \params- building_type
 * \brief- custo de construcao
 * 
 *  
 */
void buildBuilding(gordorPlayer* player, char building_type) {
    int cost;

    switch (building_type) {
    case 'B':
    case 'b':
        cost = 30;
        player->base++;
        break;
    case 'M':
    case 'm':
        cost = 20;
        player->mines++;
        break;
    case 'R':
    case 'r':
        cost = 25;
        player->barracks++;
        break;
    case 'S':
    case 's':
        cost = 25;
        player->stables++;
        break;
    case 'A':
    case 'a':
        cost = 30;
        player->armoury++;
        break;
    default:
        printf("Invalid building type.\n");
        return;
    }

    if (cost > player->coins) {
        printf("Not enough coins to build %c.\n", building_type);
    }
    else {
        player->coins -= cost;
        printf("Built %c. Remaining coins: %d\n", building_type, player->coins);
    }
}
/**
 *
 * \function name- trainUnit
 * \params- player
 * \params- unit_type
 * \brief- funcao para os custos das unidades
 * 
 *  
 */
void trainUnit(gordorPlayer* player, char unit_type) {
    int cost;

    switch (unit_type) {
    case 'I':
    case 'i':
        cost = 10;
        player->infantry++;
        break;
    case 'C':
    case 'c':
        cost = 15;
        player->cavalry++;
        break;
    case 'A':
    case 'a':
        cost = 20;
        player->artillery++;
        break;
    default:
        printf("Invalid unit type.\n");
        return;
    }

    if (cost > player->coins) {
        printf("Not enough coins to train %c.\n", unit_type);
    }
    else {
        player->coins -= cost;
        printf("Trained %c. Remaining coins: %d\n", unit_type, player->coins);
    }
}
        #pragma endregion 

#pragma endregion

#pragma region Game Rules


#pragma endregion

