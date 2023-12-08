/*****************************************************************//**
 * \file   funcoes.c
 * 
 * \author Eduardo Queir�s, Jo�o Lima, Lu�s Gon�alves
 * \date   November 2023
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#pragma warning(disable: 4996)
#define ROWS 17
#define COLS 26

entity field[ROWS][COLS];


#pragma region Funcoes gerais

/**
 *
 * \function name- startGame
 * \brief- come�a o jogo e faz com que as linhas e colunas do campo de batalha comecem com o s�mbolo "."
 * 
 *  
 */
void startGame() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            field[i][j].symbol = ' ';
        }
    }
}
/**
 *
 * \function name- printfFiel
 * \brief- Imprime o campo de batalha, as colunas de A a Z e as linhas de 0 a 16
 * 
 *  
 */

void printSquareCell() {
    printf("----");
}


void printTableLine() {
    for (int i = 0; i <= COLS; i++) {
        printSquareCell();
    }
    printf("\n");
}


void initializeGame() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            field[i][j].symbol = ' ';
        }
    }
}


void printField() {
    // Print column numbers ('A' to 'Z')
    printf("\n    ");
    for (int i = 0; i < COLS; i++) {
        printf(" %c  ", 'A' + i);
    }
    printf("\n");

    // Print game grid with row numbers (0 to 16)
    for (int i = 0; i < ROWS; i++) {
        printTableLine();
        printf("%2d ", i);
        for (int j = 0; j < COLS; j++) {
            printf("| %c ", field[i][j].symbol);
        }
        printf("|\n");
    }
    printTableLine();
}


/*
void printfField(const gordorPlayer *gordPlayer, const mordorPlayer *mordPlayer) {
    // Print column numbers ('A' to 'Z')
    int i;
    printf(" \n");
    for (i = 0; i < COLS; i++) {
        printf(" %c ", 'A' + i);
    }
    printf("\n");

    // Print game grid with row numbers (0 to 16)
    for (i = 0; i < ROWS; i++) {
        printTableLine();
        printf("%2d ", i);
        for (int j = 0; j < COLS; j++) {
            printf("| %c ", field[i][j].symbol);
            /*
            if (field[i][j].symbol == '.') {
                printf(" . ");
            }
            else {
                printf("%c ", field[i][j].symbol);
            }
        }
        printf("\n");
    }
    printTableLine();
}*/
   

/**
 *
 * \function name- showCoins
 * \params- gordPLayer
 * \params- mordPlayer
 * \brief-  Fun��o para mostrar as coins do jogador de gondor
 * 
 *  
 */
void showCoinsGondor(const gordorPlayer* gordPLayer) {

    printf("Gordor player coins: %d\n",gordPLayer->coins);

}
/**
 *
 * \function name- showCoinsMordor
 * \params- mordPlayer
 * \brief- Funcao para mostrar as coins do jogador de mordor
 * 
 *  
 */
void showCoinsMordor(const mordorPlayer* mordPlayer){
        printf("Mordor player coins: %d\n", mordPlayer->coins);
    }


/**
 *
 * \function name- checkEmptyPosition
 * \params- row
 * \params- col
 * \brief- verifica se a c�lula que o jogador quer mover a unidade esta ocupada
 *
 * \return- Caso a c�lula esteja ocupada a fun��o retorna 1, caso esteja livre retorna 0
 *
 */
int checkEmptyPosition(int row, int col) {
    if (field[row][col].symbol != ' ') {
        printf("That cell is occupied!!\n");
        printf("Choose another cell to move your unit!!!\n");
        return 1;
    }
    return 0;
}


void getGridCords(int* row, int* col) {

    char colInput;
    if (checkEmptyPosition) {
        printf("Choose the row (0-%d): \n", ROWS - 1);
        scanf_s("%d", row);

        printf("Choose the column(A-Z): ");
        scanf_s(" %c", &colInput);
        *col = colInput - 'A';
    }
    
}




#pragma endregion

#pragma region gondor functions

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
    printf("\n");
    printf("***********************************\n");
}

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
    struct gUnits gUnit= { "G", "SK", "T" };
    //aqui esta a imprimir td, por exemplo quando imprimo infantaria vai me aparecer o codigo das 3 units
    printf("Gondor Units: \n");
    printf("Infantry: %s\n", gUnit.infantry);
    printf("Cavalry: %s\n", gUnit.cavalry);
    printf("Artillery: %s\n", gUnit.artillery);
    printf("\n");
    printf("***********************************\n");
}


/**
 *
 * \function name- printStatusGordor
 * \params- player
 * \brief- Mostra os status do jogador do lado gordor
 * 
 *  
 */
void printStatusGondor(gordorPlayer* gordPlayer) {
	printf("\nPlayer: %s\n", gordPlayer->name);
	printf("Coins: %d\n", gordPlayer->coins);
	printf("Infantry: %d | Cavalry: %d | Artillery: %d\n", gordPlayer->infantry, gordPlayer->cavalry, gordPlayer->artillery);
}


    #pragma region ENCONOMY AND COSTS
/**
 *
 * \function name- createBase
 * \params- row
 * \params- col
 * \params- gordPlayer
 * \brief- Criar uma base 
 * 
 */
void createBaseGondor(int row, int col, gordorPlayer* gordPlayer) {
    
    if (row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ' &&
        field[row + 1][col].symbol == ' ' &&
        field[row + 1][col + 1].symbol == ' ') {
        field[row][col].symbol = BASE_SYMB_G;

        //como o custo de uma base � 30 coins, tiramos 30 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 30;
        printf("Base created!\n");
    }
    else {
        printf("Cannot perform this action!!!!\n");
    }
}
typedef struct entity {
    char symbol; //� representado assim: " "
    int health; //a vida come�a a 100% em todos os elementos do jogo que t�m vida
}entity;


/**
 *
 * \function name- placingBaseG
 * \params- gordPlayer
 * \brief-  Colocar a base no campo de batalha
 * 
 *  
 */
void placingBaseG(gordorPlayer* gordPlayer) {

    int baseRow, baseCol;

    getGridCords(&baseRow, &baseCol);
    printf("Creating the base!!!!\n");
    createBaseGondor(&baseRow, &baseCol,gordPlayer);
    printf("Select Row (0-16): \n");
    scanf_s("%d", &baseRow);
    printf("Select COL (A-Z): \n");
    scanf_s(" %c", &baseCol);

}

/**
 *
 * \function name- createMineGondor
 * \params- row
 * \params- col
 * \params- mine
 * \params- gordPlayer
 * \brief- Criar uma mina 
 * 
 *  
 */
void createMineGondor(int row, int col,building mine,gordorPlayer *gordPlayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.'){
        field[row][col] = mine.mine;
        field[row][col + 1] = mine.mine;
        field[row + 1][col] = mine.mine;
        field[row + 1][col + 1] = mine.mine;

        //como o custo de uma mina � 20 coins, tiramos 20 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 20;   
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}

void placingMineG(gordorPlayer* gordPlayer) {

    int mineRow, mineCol;

    getGridCords(&mineRow, &mineCol);
    printf("Creating the base!!!!\n");
    createBaseGondor(&mineRow, &mineCol, gordPlayer);
    printf("Select Row (0-16): \n");
    scanf_s("%d", &mineRow);
    printf("Select COL (A-Z): \n");
    scanf_s(" %c", &mineCol);
}




/**
 *
 * \function name- createBarrack
 * \params- row
 * \params- col
 * \params- barrack
 * \params- gordPlayer
 * \brief- Criar uma barricada no campo de batalha
 * 
 *  
 */
void createBarrack(int row, int col, gordorPlayer *gordPlayer) {
    if (row >= 0 && row + 1 < ROWS && col >= 0 && col < COLS + 1 &&
        field[row][col].symbol == '.' &&
        field[row][col + 1].symbol == '.' &&
        field[row + 1][col].symbol == '.' &&
        field[row + 1][col + 1].symbol == '.') {
        field[row][col].symbol = BARRACK_SYMB_G;

        //como o custo de uma barricada � 25 coins, tiramos 25 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 25;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}

void placingBarrackG(gordorPlayer* gordPlayer) {

    int barrackRow, barrackCol;

    getGridCords(&barrackRow, &barrackCol);
    printf("Creating the base!!!!\n");
    createBaseGondor(&barrackRow, &barrackCol, gordPlayer);
    printf("Select Row (0-16): \n");
    scanf_s("%d", &barrackRow);
    printf("Select COL (A-Z): \n");
    scanf_s(" %c", &barrackCol);

}


/**
 *
 * \function name- createStables
 * \params- row
 * \params- col
 * \params- stable
 * \params- gordPlayer
 * \brief- Criar uma barricada no campo de batalha
 * 
 *  
 */
void createStables(int row, int col, building stable, gordorPlayer *gordPlayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.') {
        field[row][col] = stable.stables;
        field[row][col + 1] = stable.stables;
        field[row + 1][col] = stable.stables;
        field[row + 1][col + 1] = stable.stables;

        //como o custo de um estabulo � 25 coins, tiramos 25 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 25;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}

void placingStableG(gordorPlayer* gordPlayer) {
    int stableRow, stableCol;

    getGridCords(&stableRow, &stableCol);
    printf("Creating the base!!!!\n");
    createBaseGondor(&stableRow, &stableCol, gordPlayer);
    printf("Select Row (0-16): \n");
    scanf_s("%d", &stableRow);
    printf("Select COL (A-Z): \n");
    scanf_s(" %c", &stableCol);
}

/**
 *
 * \function name- createInfantry
 * \params- row
 * \params- col
 * \params- infantry
 * \params- gordPLayer
 * \brief- Cria um soldado de infantaria
 * 
 *  
 */
//void createInfantry(int row, int col, gondorUnits infantry, gordorPlayer *gordPLayer)

void createInfantry(int row, int col, gondorUnits infantry, gordorPlayer *gordPLayer){
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.') {
        field[row][col] = infantry.infantry;
        field[row][col + 1] = infantry.infantry;

        //como o custo de um soldado de infantaria � 10 coins, tiramos 10 coins ao total de coins que o jogador tem
        gordPLayer->coins -= 10;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}

void placingInfantryG(gordorPlayer* gordPlayer) {
    int infantryRow, infantryCol;

    getGridCords(&infantryRow, &infantryCol);
    printf("Creating the base!!!!\n");
    createBaseGondor(&infantryRow, &infantryCol, gordPlayer);
    printf("Select Row (0-16): \n");
    scanf_s("%d", &infantryRow);
    printf("Select COL (A-Z): \n");
    scanf_s(" %c", &infantryCol);
}

/**
 *
 * \function name- createCavalry
 * \params- row
 * \params- col
 * \params- cavalry
 * \params- gordPlayer
 * \brief- Cria um soldado de cavalaria
 * 
 *  
 */
void createCavalry(int row, int col, gondorUnits cavalry, gordorPlayer *gordPlayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.') {
        field[row][col] = cavalry.cavalry;
        field[row][col + 1] = cavalry.cavalry;

        //como o custo de um soldado de cavalaria � 15 coins, tiramos 15 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 15;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }

}

void placingCavalryG(gordorPlayer* gordPlayer) {
    int cavalryRow, cavalryCol;

    getGridCords(&cavalryRow, &cavalryCol);
    printf("Creating the base!!!!\n");
    createBaseGondor(&cavalryRow, &cavalryCol, gordPlayer);
    printf("Select Row (0-16): \n");
    scanf_s("%d", &cavalryRow);
    printf("Select COL (A-Z): \n");
    scanf_s(" %c", &cavalryCol);
}



/**
 *
 * \function name- createArtillery
 * \params- row
 * \params- col
 * \params- artillery
 * \params- gordPlayer
 * \brief- Cria um soldado de artilharia
 * 
 *  
 */
void createArtillery(int row, int col, gondorUnits artillery, gordorPlayer *gordPlayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.') {
        field[row][col] = artillery.artillery;
        field[row][col + 1] = artillery.artillery;

        //como o custo de um soldado de artilharia � 20 coins, tiramos 20 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 20;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}

void placingArtilleryG(gordorPlayer* gordPlayer) {
    int artilleryRow, artilleryCol;

    getGridCords(&artilleryRow, &artilleryCol);
    printf("Creating the base!!!!\n");
    createBaseGondor(&artilleryRow, &artilleryCol, gordPlayer);
    printf("Select Row (0-16): \n");
    scanf_s("%d", &artilleryRow);
    printf("Select COL (A-Z): \n");
    scanf_s(" %c", &artilleryCol);
}


#pragma endregion

    #pragma region MOVE UNITS


/**
 *
 * \function name- moveGondorInfantry
 * \params- originRow
 * \params- originCol
 * \params- destRow
 * \params- destCol
 * \brief- Funcao que faz com que seja possivel mover uma unidade de infantaria
 * 
 *  
 */
void moveInfantryGondor(int originRow, int originCol,int destRow, int destCol)
{
    if (field[destRow][destCol].symbol == '.' && !(checkEmptyPosition(destRow, destCol))) {
        field[destRow][destCol].symbol == field[originRow][originCol].symbol;
        //depois de mover a unit, a celula de onde esta a unit fica vazia, logo temos de dizer que a linha e coluna de origem fica assim '.'
        field[originRow][originCol].symbol == '.'; 
    }
}

/**
 *
 * \function name- moveGondorCavalry
 * \params- originRow
 * \params- originCol
 * \params- destRow
 * \params- destCol
 * \brief- Funcao que faz com que seja possivel mover uma unidade de infantaria
 * 
 *  
 */
void moveCavalryGondor(int originRow, int originCol, int destRow, int destCol) {
    if (field[destRow][destCol].symbol == '.' && !(checkEmptyPosition(destRow, destCol))) {
        field[destRow][destCol].symbol == field[originRow][originCol].symbol;
        //depois de mover a unit, a celula de onde esta a unit fica vazia, logo temos de dizer que a linha e coluna de origem fica assim '.'
        field[originRow][originCol].symbol == '.';
    }
}

/**
 *
 * \function name- moveGondorArtillery
 * \params- originRow
 * \params- originCol
 * \params- destRow
 * \params- destCol
 * \brief- Funcao que faz com que seja possivel mover uma unidade de infantaria
 * 
 *  
 */
void moveArtilleryGondor(int originRow, int originCol, int destRow, int destCol) {
    if (field[destRow][destCol].symbol == '.' && !(checkEmptyPosition(destRow, destCol))) {
        field[destRow][destCol].symbol == field[originRow][originCol].symbol;
        //depois de mover a unit, a celula de onde esta a unit fica vazia, logo temos de dizer que a linha e coluna de origem fica assim '.'
        field[originRow][originCol].symbol == '.';
    }
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
void moveGordorUnits(gordorPlayer* player, char unitType, int cells, int originRow, int originCol, int destRow, int destCol, gordorPlayer* gordPlayer) {
    int costPerCell;

    switch (unitType) {
    case 'I':
    case 'i':
        moveInfantryGondor(originRow, originCol, destRow, destCol, gordPlayer);
        costPerCell = 2; //custo de uma pe�a de infantaria
        break;
    case 'C':
    case 'c':
        moveCavalryGondor(originRow, originCol, destRow, destCol, gordPlayer);
        costPerCell = 1;//custo de uma pe�a de cavalaria
        break;
    case 'A':
    case 'a':
        moveArtilleryGondor(originRow, originCol, destRow, destCol, gordPlayer);
        costPerCell = 3; //custo de uma pe�a de artilharia
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
    
    #pragma endregion

#pragma endregion

#pragma region mordor Functions

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
/**
 *
 * \function name- printMordorStatus
 * \params- mordPlayer
 * \brief- Mostra os status do jogador do lado mordor
 * 
 *  
 */
void printMordorStatus(mordorPlayer* mordPlayer) {
    printf("\nPlayer: %s\n", mordPlayer->name);
    printf("Coins: %d\n", mordPlayer->coins);
    printf("Infantry: %d | Cavalry: %d | Artillery: %d\n", mordPlayer->infantry, mordPlayer->cavalry, mordPlayer->artillery);
}

    #pragma region ECONOMY AND COSTS
/**
 *
 * \function name- createBaseMordor
 * \params- row
 * \params- col
 * \params- mordPLayer
 * \params- base
 * \brief- Criar uma base mordor
 * 
 *  
 */
void createBaseMordor(int row, int col,mordorPlayer *mordPLayer , building base) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        field[row][col] = base.base;
        field[row][col + 1] = base.base;
        field[row + 1][col] = base.base;
        field[row + 1][col + 1] = base.base;

        //como o custo de uma base � 30 coins, tiramos 30 coins ao total de coins que o jogador tem
        mordPLayer->coins -= 30;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}


    
/**
 *
 * \function name- createMineMordor
 * \params- row
 * \params- col
 * \params- mine
 * \params- mordPlayer
 * \brief- Criar uma mina no campo de batalha
 * 
 *  
 */
void createMineMordor(int row, int col, building mine, mordorPlayer *mordPlayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.') {
        field[row][col] = mine.mine;
        field[row][col + 1] = mine.mine;
        field[row + 1][col] = mine.mine;
        field[row + 1][col + 1] = mine.mine;

        //como o custo de uma mina � 20 coins, tiramos 20 coins ao total de coins que o jogador tem
        mordPlayer->coins -= 20;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}
/**
 *
 * \function name- createBarrackMordor
 * \params- row
 * \params- col
 * \params- barrack
 * \params- mordPlayer
 * \brief- Cria uma barricada no campo de batalha
 * 
 *  
 */
void createBarrackMordor(int row, int col, building barrack, mordorPlayer* mordPlayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.') {
        field[row][col] = barrack.barracks;
        field[row][col + 1] = barrack.barracks;
        field[row + 1][col] = barrack.barracks;
        field[row + 1][col + 1] = barrack.barracks;

        //como o custo de uma barricada � 25 coins, tiramos 25 coins ao total de coins que o jogador tem
        mordPlayer->coins -= 25;

    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}
/**
 *
 * \function name- createStablesMordor
 * \params- row
 * \params- col
 * \params- stable
 * \params- gordPlayer
 * \brief- Criar uma barricada no campo de batalha
 *
 *
 */
void createStablesMordor(int row, int col, building stable, mordorPlayer* mordPlayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.') {
        field[row][col] = stable.stables;
        field[row][col + 1] = stable.stables;
        field[row + 1][col] = stable.stables;
        field[row + 1][col + 1] = stable.stables;

        //como o custo de um estabulo � 25 coins, tiramos 25 coins ao total de coins que o jogador tem
        mordPlayer->coins -= 25;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}
/**
 *
 * \function name- createInfantryMordor
 * \params- row
 * \params- col
 * \params- infantry
 * \params- gordPLayer
 * \brief- Cria um soldado de infantaria
 *
 *
 */
void createInfantryMordor(int row, int col, mordorUnits infantry, mordorPlayer* mordPLayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.') {
        field[row][col] = infantry.infantry;
        field[row][col + 1] = infantry.infantry;

        //como o custo de um soldado de infantaria � 10 coins, tiramos 10 coins ao total de coins que o jogador tem
        mordPLayer->coins -= 10;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}
/**
 *
 * \function name- createCavalryMordor
 * \params- row
 * \params- col
 * \params- cavalry
 * \params- gordPlayer
 * \brief- Cria um soldado de cavalaria
 *
 *
 */
void createCavalryMordor(int row, int col, mordorUnits cavalry, mordorPlayer* mordPlayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.') {
        field[row][col] = cavalry.cavalry;
        field[row][col + 1] = cavalry.cavalry;

        //como o custo de um soldado de cavalaria � 15 coins, tiramos 15 coins ao total de coins que o jogador tem
        mordPlayer->coins -= 15;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }

}
/**
 *
 * \function name- createArtilleryMordor
 * \params- row
 * \params- col
 * \params- artillery
 * \params- gordPlayer
 * \brief- Cria um soldado de artilharia
 *
 *
 */
void createArtilleryMordor(int row, int col, mordorUnits artillery, mordorPlayer* mordPlayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.') {
        field[row][col] = artillery.artillery;
        field[row][col + 1] = artillery.artillery;

        //como o custo de um soldado de artilharia � 20 coins, tiramos 20 coins ao total de coins que o jogador tem
        mordPlayer->coins -= 10;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}
#pragma endregion

    #pragma region MOVE UNITS
/**
 *
 * \function name- moveGondorInfantry
 * \params- originRow
 * \params- originCol
 * \params- destRow
 * \params- destCol
 * \brief- Funcao que faz com que seja possivel mover uma unidade de infantaria
 *
 *
 */
void moveInfantryMordor(int originRow, int originCol, int destRow, int destCol)
{
    if (field[destRow][destCol].symbol == '.' && !(checkEmptyPosition(destRow, destCol))) {
        field[destRow][destCol].symbol == field[originRow][originCol].symbol;
        //depois de mover a unit, a celula de onde esta a unit fica vazia, logo temos de dizer que a linha e coluna de origem fica assim '.'
        field[originRow][originCol].symbol == '.';
    }
}

/**
 *
 * \function name- moveGondorCavalry
 * \params- originRow
 * \params- originCol
 * \params- destRow
 * \params- destCol
 * \brief- Funcao que faz com que seja possivel mover uma unidade de infantaria
 *
 *
 */
void moveCavalryMordor(int originRow, int originCol, int destRow, int destCol) {
    if (field[destRow][destCol].symbol == '.' && !(checkEmptyPosition(destRow, destCol))) {
        field[destRow][destCol].symbol == field[originRow][originCol].symbol;
        //depois de mover a unit, a celula de onde esta a unit fica vazia, logo temos de dizer que a linha e coluna de origem fica assim '.'
        field[originRow][originCol].symbol == '.';
    }
}

/**
 *
 * \function name- moveGondorArtillery
 * \params- originRow
 * \params- originCol
 * \params- destRow
 * \params- destCol
 * \brief- Funcao que faz com que seja possivel mover uma unidade de infantaria
 *
 *
 */
void moveArtilleryMordor(int originRow, int originCol, int destRow, int destCol) {
    if (field[destRow][destCol].symbol == '.' && !(checkEmptyPosition(destRow, destCol))) {
        field[destRow][destCol].symbol == field[originRow][originCol].symbol;
        //depois de mover a unit, a celula de onde esta a unit fica vazia, logo temos de dizer que a linha e coluna de origem fica assim '.'
        field[originRow][originCol].symbol == '.';
    }
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
void moveMordorUnits(mordorPlayer* mordPlayer, char unitType, int cells, int originRow, int originCol, int destRow, int destCol) {
    int costPerCell;

    switch (unitType) {
    case 'I':
    case 'i':
        moveInfantryMordor(originRow, originCol, destRow, destCol, mordPlayer);
        costPerCell = 2; //custo de uma pe�a de infantaria
        break;
    case 'C':
    case 'c':
        moveCavalryMordor(originRow, originCol, destRow, destCol, mordPlayer);
        costPerCell = 1;//custo de uma pe�a de cavalaria
        break;
    case 'A':
    case 'a':
        moveArtilleryMordor(originRow, originCol, destRow, destCol, mordPlayer);
        costPerCell = 3; //custo de uma pe�a de artilharia
        break;
    default:
        printf("Invalid unit type.\n");
        return;
    }

    int totalCost = costPerCell * cells;

    if (totalCost > mordPlayer->coins) {
        printf("Not enough coins to make the move.\n");
    }
    else {
        mordPlayer->coins -= totalCost;
        printf("Moved %c %d cells. Remaining coins: %d\n", unitType, cells, mordPlayer->coins);
    }
}
    #pragma endregion

#pragma endregion

#pragma region funcoes Gravar ficheiro

#pragma endregion


#pragma region Codigo em comentarios

/**
 *
 * \function name- collectMineIncome
 * \params- player
 * \brief- Funcao para custo de minas
 *
 *
 */
 /*
 void collectMineIncome(gordorPlayer* player) {
     int mine_income = 5 * player->mines;
     player->coins += mine_income;
     printf("Collected mine income. Total coins: %d\n", player->coins);
 }*/

 /**
  *
  * \function name- buildBuilding
  * \params- player
  * \params- building_type
  * \brief- custo de construcao
  *
  *
  */
  /*
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
  }*/
  /**
   *
   * \function name- trainUnit
   * \params- player
   * \params- unit_type
   * \brief- funcao para os custos das unidades
   *
   *
   */
   /*
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
   */
#pragma endregion