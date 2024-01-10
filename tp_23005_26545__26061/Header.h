/*****************************************************************//**
 * \file   Header.h
 *
 * \author Eduardo Queirós, João Lima, Luís Gonçalves
 * \date   November 2023
 *********************************************************************/
#include<stdio.h>
#include <string.h>
#pragma warning(disable: 4996)

#define ROWS 17
#define COLS 26
#define PLAYER 2 //numero de jogadores do jogo
/*------------------- DEFINIR PARA GORDOR---------------*/
//definir para a base
#define BASE_SYMB_G 'G' 
#define BASE_SYMB_G1 'G' 
#define BASE_SYMB_G2 'G' 
#define BASE_SYMB_G3 'G' 
//definir para a mina
#define MINE_SYMB_G 'S'
#define MINE_SYMB_G1 'S'
//definir para a barrack
#define BARRACK_SYMB_G 'R'
#define BARRACK_SYMB_G1 'R'
//definir para o estabulo 
#define STABLES_SYMB_G 'L' 
#define STABLES_SYMB_G1 'L' 
//definir para a armoury
#define ARMOURY_SYMB_G 'G'
#define ARMOURY_SYMB_G1 'F'

//definir para a infantaria
#define INFANTARY_SYMB_G 'G' 
//definir para a cavalaria
#define CAVALARY_SYMB_G 'S'
#define CAVALARY_SYMB_G1 'K'
//definir para a artilharia
#define ARTILLERY_SYMB_G 'T'


/* ----------------------DEFINIR PARA GORDOR--------------------*/
//definir para a base
#define BASE_SYMB_M 'M' 
#define BASE_SYMB_M1 'M' 
#define BASE_SYMB_M2 'M' 
#define BASE_SYMB_M3 'M' 
//definir para a mina
#define MINE_SYMB_M 'E'
#define MINE_SYMB_M1 'E'
//definir para a barrack
#define BARRACK_SYMB_M 'I'
#define BARRACK_SYMB_M1 'I'
//definir para o estabulo 
#define STABLES_SYMB_M 'M' 
#define STABLES_SYMB_M1 'K' 
//definir para a armoury
#define ARMOURY_SYMB_M 'D'
#define ARMOURY_SYMB_M1 'F'


//definir para a infantaria
#define INFANTARY_SYMB_M 'O' 
#define INFANTARY_SYMB_M1 'W' 
//definir para a cavalaria
#define CAVALARY_SYMB_M 'W'
//definir para a artilharia
#define ARTILLERY_SYMB_M 'S'
#define ARTILLERY_SYMB_M1 'T'

 //entity base;
 //entity mine;
 //entity barracks;
 //entity stables;
 //entity armoury;

#pragma region Structs

/**
 * Esta struct vai servir para as outras structs
 */
typedef struct entity {
	char symbol; //é representado assim: " "
	int health; //a vida começa a 100% em todos os elementos do jogo que têm vida
}entity;


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

typedef struct gUnits
{
	char infantry[1];
	char cavalry[2];
	char artillery[1];

}gUnits;


/**
 * Mostra as unidades de gondor
 */
typedef struct gondorUnits
{
	entity infantry;
	entity cavalry;
	entity artillery;

}gondorUnits;
/**
  * Mostra as unidades de mordor
 */
typedef struct mordorUnits
{
	entity infantry;
	entity cavalry;
	entity artillery;

}mordorUnits;

typedef struct building {
	char type; //tipo de edificio
	int cost;  //custo
	char symbol;
	entity base;
	entity mine;
	entity barracks;
	entity stables;
	entity armoury;
}building;

typedef struct gordorPlayer {
	char name[20];
	int coins;
	int infantry;
	int infantryHealth;
	int cavalry;
	int cavalryHealth;
	int artillery;
	int artilleryHealth;
	int gBaseHealth;
	int gMineHealth;
	int gBarrackHealth;
	int gStableHealth;
	int gArmouryHealth;
	building buildingsGordor;
	//building buildingMordor;
	gondorUnits gUnits;

} gordorPlayer;

typedef struct mordorPlayer {
	char name[20];
	int coins;
	int infantry;
	int infantryHealth;
	int cavalry;
	int cavalryHealth;
	int artillery;
	int artilleryHealth;
	int mBaseHealth;
	int mMineHealth;
	int mBarrackHealth;
	int mStableHealth;
	int mArmouryHealth;
	building buildingsMordor;
	mordorUnits mUnits;

} mordorPlayer;

typedef struct cell {

	char building;
	char unit;
}cell;

#pragma endregion

#pragma region Funcoes
void saadasdsa();
int mordorMovesBattle();
int gordorAttackBattle();

	#pragma region funcaoes gerais
void startGame();
//void printfField(const gordorPlayer* gordPlayer, const mordorPlayer* mordPlayer);
void printField();
void showCoinsGondor(const gordorPlayer* gordPLayer);
void showCoinsMordor(const mordorPlayer* mordPlayer);
int checkEmptyPosition(int row, int col);
void printStatusGondor(gordorPlayer* player);
void printMordorStatus(mordorPlayer* mordPlayer);
void getGridCords(int* row, int* col);
	#pragma endregion

	#pragma region funcoes gordor
void showGondorFactory();
void showGondorUnits();
	#pragma region CRIAR
void createBaseGondor(int row, int col, gordorPlayer* gordPlayer);
void placingBaseG(gordorPlayer* gordPlayer);

void createBarrack(int row, int col, gordorPlayer* gordPlayer);
void placingBarrackG(gordorPlayer* gordPlayer);

void createMineGondor(int row, int col, building mine, gordorPlayer* gordPlayer);
void placingMineG(gordorPlayer* gordPlayer);

void createStables(int row, int col, building stable, gordorPlayer* gordPlayer);
void placingStableG(gordorPlayer* gordPlayer);

void createArmouryGondor(int row, int col, gordorPlayer* gordPlayer);
void placingArmouryG(gordorPlayer* gordPlayer);

void createInfantry(int row, int col, gondorUnits infantry, gordorPlayer* gordPLayer);
void placingInfantryG(gordorPlayer* gordPlayer);

void createCavalry(int row, int col, gondorUnits cavalry, gordorPlayer* gordPlayer);
void placingCavalryG(gordorPlayer* gordPlayer);

void createArtillery(int row, int col, gondorUnits artillery, gordorPlayer* gordPlayer);
void placingArtilleryG(gordorPlayer* gordPlayer);
	#pragma endregion
/*
void moveInfantryGondor(int originRow, int originCol, int destRow, int destCol);
void moveCavalryGondor(int originRow, int originCol, int destRow, int destCol);
void moveArtilleryGondor(int originRow, int originCol, int destRow, int destCol);
*/
	#pragma region MOVER
void moveInfantryGondor(gordorPlayer* gordPlayer);
void moveCavalryGondor(gordorPlayer* gordPlayer);
void moveArtilleryGondor(gordorPlayer* gordPlayer);
	#pragma endregion

	#pragma region ATACAR
void GondorInfantryVSMordBase(int row, int col,mordorPlayer* mordPlayer);
void GondorCavalryVSMordBase(int row, int col, mordorPlayer* mordPlayer);
void GondorArtilleryVSMordBase(int row, int col, mordorPlayer* mordPlayer);

void GondorInfantryVSMordMine(int row, int col, mordorPlayer* mordPlayer);
void GondorCavalryVSMordMine(int row, int col,mordorPlayer* mordPlayer);
void GondorArtilleryVSMordMine(int row, int col, mordorPlayer* mordPlayer);

void GondorInfantrVSMordBarrack(int row, int col, mordorPlayer* mordPlayer);
void GondorCavalryVSMordBarrack(int row, int col, mordorPlayer* mordPlayer);
void GondorArtilleryVSMordBarrack(int row, int col, mordorPlayer* mordPlayer);

void GondorInfantrVSMordStable(int row, int col,  mordorPlayer* mordPlayer);
void GondorCavalryVSMordStable(int row, int col, mordorPlayer* mordPlayer);
void GondorArtilleryVSMordStable(int row, int col, mordorPlayer* mordPlayer);

void GondorInfantrVSMordArmoury(int row, int col,  mordorPlayer* mordPlayer);
void GondorCavalryVSMordArmoury(int row, int col, mordorPlayer* mordPlayer);
void GondorArtilleryVSMordArmoury(int row, int col, mordorPlayer* mordPlayer);

void GondorInfantrVSMordInfantry(int row, int col, mordorPlayer* mordPlayer);
void GondorCavalryVSMordInfantry(int row, int col, mordorPlayer* mordPlayer);
void GondorArtilleryVSMordInfantry(int row, int col, mordorPlayer* mordPlayer);

void GondorInfantryVSMordCavalry(int row, int col,  mordorPlayer* mordPlayer);
void GondorCavalryVSMordCavalry(int row, int col,  mordorPlayer* mordPlayer);
void GondorArtillheryVSMordCavalry(int row, int col, mordorPlayer* mordPlayer);

void GondorInfantryVSMordArtillhery(int row, int col, mordorPlayer* mordPlayer);
void GondorCavalryVSMordArtillhery(int row, int col, mordorPlayer* mordPlayer);
void GondorArtilleryVSMordArtillhery(int row, int col, mordorPlayer* mordPlayer);

	#pragma endregion

	#pragma endregion	


	#pragma region funcoes mordor
void showMordorFactory();
void showMordorUnits();

	#pragma region CRIAR
void createBaseMordor(int row, int col, mordorPlayer* mordPLayer, building base);
void placingBaseM(mordorPlayer* mordPlayer);

void createMineMordor(int row, int col, building mine, mordorPlayer* mordPlayer);
void placingMineM(mordorPlayer* mordPlayer);

void createBarrackMordor(int row, int col, building barrack, mordorPlayer* mordPlayer);
void placingBarrackM(mordorPlayer* mordPlayer);

void createStablesMordor(int row, int col, building stable, mordorPlayer* mordPlayer);
void placingStableM(mordorPlayer* mordPlayer);

void createArmouryMordor(int row, int col, mordorPlayer* mordPlayer);
void placingArmouryM(mordorPlayer* mordPlayer);

void createInfantryMordor(int row, int col, mordorUnits infantry, mordorPlayer* mordPLayer);
void placingInfantryM(mordorPlayer* mordPLayer);

void createCavalryMordor(int row, int col, mordorUnits cavalry, mordorPlayer* mordPlayer);
void placingCavalryM(mordorPlayer* mordPLayer);

void createArtilleryMordor(int row, int col, mordorUnits artillery, mordorPlayer* mordPlayer);
void placingArtilleryM(mordorPlayer* mordPLayer);
	#pragma endregion

/*
void moveInfantryMordor(int originRow, int originCol, int destRow, int destCol);
void moveCavalryMordor(int originRow, int originCol, int destRow, int destCol);
void moveArtilleryMordor(int originRow, int originCol, int destRow, int destCol);
*/
	#pragma region MOVER
void moveInfantryMordor(mordorPlayer* mordorPlayer);
void moveCavalryMordor(mordorPlayer* mordorPlayer);
void moveArtilleryMordor(mordorPlayer* mordorPlayer);
	#pragma endregion 

	#pragma region ATACAR
void MordorInfantryVSGondBase(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorCavalryVSGondBase(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorArtilleryVSGondBase(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);

void MordorInfantryVSGondMine(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorCavalryVSGondMine(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorArtilleryVSGondMine(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);

void MordorInfantrVSGondBarrack(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorCavalryVSGondBarrack(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorArtilleryVSGondBarrack(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);

void MordorInfantrVSGondStable(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorCavalryVSGondStable(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorArtilleryVSGondStable(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);

void MordorInfantrVSGondArmoury(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorCavalryVSGondArmoury(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorArtilleryVSGondArmoury(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);

void MordorInfantrVSGondInfantry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorCavalryVSGondInfantry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorArtilleryVSGondInfantry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);

void MordInfantryVSGondCavalry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordCavalryVSGondCavalry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordArtilleryVSGondCavalry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);

void MordorInfantryVSGondArtillhery(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorCavalryVSGondArtillhery(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void MordorArtilleryVSGondArtillhery(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);


	#pragma endregion

#pragma endregion

#pragma region funcoes gravar
void save(const char* filename, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);
void load(const char* filename, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer);


#pragma endregion



