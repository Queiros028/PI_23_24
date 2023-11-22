/*****************************************************************//**
 * \file   Header.h
 * 
 * \author Eduardo Queirós, João Lima, Luís Gonçalves
 * \date   November 2023
 *********************************************************************/
#include<stdio.h>
#include <string.h>
#pragma warning(disable: 4996)

#pragma region Structs
/**
 * struct para o utilizador conseguir ver quais os seus edificios de batalha
 */
typedef struct faction 
{
	char factionName[20];
	char base[5];
	char mine[3];
	char barracks[3];
	char stables[3];
	char armoury[3];

}faction;


typedef struct gondorUnits
{
	char infantry[1];
	char cavalry[2];
	char artillery[1];

}gondorUnits;

typedef struct mordorUnits
{
	char infantry[2];
	char cavalry[1];
	char artillery[2];

}mordorUnits;

typedef struct gordorPlayer{
	char name[20];
	int coins;
	int infantry;
	int cavalry;
	int artillery;
	int mines;
	int base;
	int barracks;
	int stables;
	int armoury;
} gordorPlayer;

typedef struct mordorPlayer {
	char name[20];
	int coins;
	int infantry;
	int cavalry;
	int artillery;
	int mines;
	int base;
	int barracks;
	int stables;
	int armoury;
} mordorPlayer;

typedef struct Building {
	char type; //tipo de edificio
	int cost;  //custo
}Building;


typedef struct cell {

	char building;
	char unit;
}cell;
#pragma endregion

#pragma region Funcoes

void printStatus(gordorPlayer* player);
void move(gordorPlayer* player, char unitType, int cells);
void placeBuilding(char grid[17][26], int row, int col, struct Building building);
void collectMineIncome(gordorPlayer* player);
void buildBuilding(gordorPlayer* player, char building_type);
void trainUnit(gordorPlayer* player, char unit_type);
#pragma endregion

