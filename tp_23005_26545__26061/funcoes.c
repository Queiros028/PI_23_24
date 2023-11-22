/*****************************************************************//**
 * \file   funcoes.c
 * 
 * \author Eduardo Queirós, João Lima, Luís Gonçalves
 * \date   November 2023
 *********************************************************************/
#include <stdio.h>
#include "Header.h"
#pragma warning(disable: 4996)

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

#pragma region Coins
/**
 *
 * \function name- printStatus
 * \params- player
 * \brief- Status de um jogador
 * 
 *  
 */
/*
void printStatus(gordorPlayer* player) {
	printf("\nPlayer: %s\n", player->name);
	printf("Coins: %d\n", player->coins);
	printf("Infantry: %d | Cavalry: %d | Artillery: %d\n", player->infantry, player->cavalry, player->artillery);
	printf("Mines: %d\n", player->mines);
}
*/
/**
 *
 * \function name- move
 * \params- player
 * \params- unit_type
 * \params- cells
 * \brief- funcao para ser possivel realizar o movimento
 * 
 *  
 */
/*
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
*/
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
#pragma endregion

