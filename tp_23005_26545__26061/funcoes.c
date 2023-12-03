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

entity field[ROWS][COLS];

#pragma region Funcoes gerais
/**
 *
 * \function name- startGame
 * \brief- começa o jogo e faz com que as linhas e colunas do campo de batalha comecem com o símbolo "."
 * 
 *  
 */
void startGame() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            field[i][j].symbol = '.';
        }
    }
}
/**
 *
 * \function name- printfFiel
 * \params- gordPlayer
 * \params- mordPLayer
 * \brief- Imprime o campo de batalha 
 * 
 *  
 */
void printfFiel(const gordorPlayer  *gordPlayer, const mordorPlayer *mordPLayer) {

    for (int i = 0; i < COLS; i++) {
        printf("%2d", i);
    }
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf("%2d ", i);
        for (int j = 0; j < COLS; j++) {
            if (field[i][j].symbol == '.') {
                printf(". ");
            }
            else {
                printf("%c ", field[i][j].symbol);
            }
        }
        printf("\n");
    }
}
/**
 *
 * \function name- showCoins
 * \params- gordPLayer
 * \params- mordPlayer
 * \brief-  Função para mostrar aos jogadores as suas coins
 * 
 *  
 */
void showCoins(const gordorPlayer* gordPLayer, const mordorPlayer* mordPlayer) {

    printf("Gordor player coins: %d\n",gordPLayer->coins);
    printf("Mordor player coins: %d\n", mordPlayer->coins);
}


/**
 *
 * \function name- checkEmptyPosition
 * \params- row
 * \params- col
 * \brief- verifica se a célula que o jogador quer mover a unidade esta ocupada
 *
 * \return- Caso a célula esteja ocupada a função retorna 1, caso esteja livre retorna 0
 *
 */
int checkEmptyPosition(int row, int col) {
    if (field[row][col].symbol != '.') {
        printf("That cell is occupied!!\n");
        printf("Choose another cell to move your unit!!!\n");
        return 1;
    }
    return 0;
}
#pragma endregion

#pragma region gordor functions
/**
 *
 * \function name- printStatusGordor
 * \params- player
 * \brief- Mostra os status do jogador do lado gordor
 * 
 *  
 */
void printStatusGordor(gordorPlayer* gordPlayer) {
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
 * \brief- Criar uma base no campo de batalha
 * 
 */
void createBaseGondor(int row, int col, gordorPlayer *gordPlayer, building base) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS){
        field[row][col] = base.base;
        field[row][col + 1] = base.base;
        field[row + 1][col] = base.base;
        field[row + 1][col + 1] = base.base;

        //como o custo de uma base é 30 coins, tiramos 30 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 30;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
}
/**
 *
 * \function name- createMineGondor
 * \params- row
 * \params- col
 * \params- mine
 * \params- gordPlayer
 * \brief- Criar uma mina no campo de batalha
 * 
 *  
 */
void createMineGondor(int row, int col,building mine,gordorPlayer *gordPlayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.'){
        field[row][col] = mine.mine;
        field[row][col + 1] = mine.mine;
        field[row + 1][col] = mine.mine;
        field[row + 1][col + 1] = mine.mine;

        //como o custo de uma mina é 20 coins, tiramos 20 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 20;   
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
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
void createBarrack(int row, int col, building barrack, gordorPlayer *gordPlayer) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && field[row][col].symbol == '.') {
        field[row][col] = barrack.barracks;
        field[row][col + 1] = barrack.barracks;
        field[row + 1][col] = barrack.barracks;
        field[row + 1][col + 1] = barrack.barracks;

        //como o custo de uma barricada é 25 coins, tiramos 25 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 25;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
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

        //como o custo de um estabulo é 25 coins, tiramos 25 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 25;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
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

        //como o custo de um soldado de infantaria é 10 coins, tiramos 10 coins ao total de coins que o jogador tem
        gordPLayer->coins -= 10;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }
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

        //como o custo de um soldado de cavalaria é 15 coins, tiramos 15 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 15;
    }
    else {
        printf("Nao e possivel realizar essa acao!!!!\n");
    }

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

        //como o custo de um soldado de artilharia é 20 coins, tiramos 20 coins ao total de coins que o jogador tem
        gordPlayer->coins -= 20;
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
        costPerCell = 2; //custo de uma peça de infantaria
        break;
    case 'C':
    case 'c':
        moveCavalryGondor(originRow, originCol, destRow, destCol, gordPlayer);
        costPerCell = 1;//custo de uma peça de cavalaria
        break;
    case 'A':
    case 'a':
        moveArtilleryGondor(originRow, originCol, destRow, destCol, gordPlayer);
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
    
    #pragma endregion

#pragma endregion

#pragma region mordor Functions
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

        //como o custo de uma base é 30 coins, tiramos 30 coins ao total de coins que o jogador tem
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

        //como o custo de uma mina é 20 coins, tiramos 20 coins ao total de coins que o jogador tem
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

        //como o custo de uma barricada é 25 coins, tiramos 25 coins ao total de coins que o jogador tem
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

        //como o custo de um estabulo é 25 coins, tiramos 25 coins ao total de coins que o jogador tem
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

        //como o custo de um soldado de infantaria é 10 coins, tiramos 10 coins ao total de coins que o jogador tem
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

        //como o custo de um soldado de cavalaria é 15 coins, tiramos 15 coins ao total de coins que o jogador tem
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

        //como o custo de um soldado de artilharia é 20 coins, tiramos 20 coins ao total de coins que o jogador tem
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
        costPerCell = 2; //custo de uma peça de infantaria
        break;
    case 'C':
    case 'c':
        moveCavalryMordor(originRow, originCol, destRow, destCol, mordPlayer);
        costPerCell = 1;//custo de uma peça de cavalaria
        break;
    case 'A':
    case 'a':
        moveArtilleryMordor(originRow, originCol, destRow, destCol, mordPlayer);
        costPerCell = 3; //custo de uma peça de artilharia
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