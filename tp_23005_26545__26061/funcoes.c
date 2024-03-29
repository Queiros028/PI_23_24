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
#pragma warning(disable: 6386)
#define ROWS 17
#define COLS 26

entity field[ROWS][COLS];


#pragma region Funcoes gerais
void initializeGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = ' ';
        }
    }
}

void displayGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

void placeBuilding(char grid[ROWS][COLS], int row, int col, char symbol) {
    grid[row][col] = symbol;
}

// Functions from your second code

void startGame() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            field[i][j].symbol = ' ';
        }
    }
}

void printSquareCell() {
    printf("----");
}

void printTableLine() {
    for (int i = 0; i <= COLS; i++) {
        printSquareCell();
    }
    printf("\n");
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

    printf("Gordor player coins: %d\n", gordPLayer->coins);

}
/**
 *
 * \function name- showCoinsMordor
 * \params- mordPlayer
 * \brief- Funcao para mostrar as coins do jogador de mordor
 *
 *
 */
void showCoinsMordor(const mordorPlayer* mordPlayer) {
    printf("Mordor player coins: %d\n", mordPlayer->coins);
}


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

    // Loop until you get a position that is not occupied
    do {
        printf("Choose the row (0-%d): ", ROWS - 1);
        scanf_s("%d", row);

        printf("Choose the column (A-Z): ");
        scanf_s(" %c", &colInput);
        *col = colInput - 'A';

        printf("DEBUG: Checking position %d, %d\n", *row, *col);
    } while (checkEmptyPosition(*row, *col));

    printf("DEBUG: Position is valid\n");
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
    struct gUnits gUnit = { "G", "SK", "T" };
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
 * \function name- createBaseGondor
 * \params- row
 * \params- col
 * \params- gordPlayer
 * \brief- Criar uma Base
 *
 *
 */
void createBaseGondor(int row, int col, gordorPlayer* gordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ' &&
        field[row + 1][col].symbol == ' ' &&
        field[row + 1][col + 1].symbol == ' ') && gordPlayer->coins >= 30)
    {
            field[row][col].symbol = BASE_SYMB_G;
            field[row][col + 1].symbol = BASE_SYMB_G1;
            field[row][col + 2].symbol = BASE_SYMB_G2;
            field[row][col - 1].symbol = BASE_SYMB_G3;
            gordPlayer->coins -= 30;   
            showCoinsGondor(gordPlayer);
            printf("Base created at [%d][%d]!\n", row, col);
            if (gordPlayer->coins <= 30) {
                printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!\n", gordPlayer->coins);
            }
            else if (gordPlayer->coins > 30) {
                printf("Coins after base creation: %d\n", gordPlayer->coins);

            }
                    
    }
    else {
        printf("Cannot create base at [%d][%d]!!!!\n", row, col);
    }
}

/**
 *
 * \function name- placingBaseG
 * \params- gordPlayer
 * \brief-  Colocar a Base no campo de batalha
 *
 *
 */
void placingBaseG(gordorPlayer* gordPlayer) {
    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createBaseGondor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the base at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createBaseGondor com as novas coordenadas
    createBaseGondor(baseRow, baseCol, gordPlayer);

    // Print the field after creating the base
    printField();
}


/**
 *
 * \function name- createMineGondor
 * \params- row
 * \params- col
 * \params- gordPlayer
 * \brief- Criar uma mina
 *
 *
 */
void createMineGondor(int row, int col, gordorPlayer* gordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ') && gordPlayer->coins >= 20)
    {
        field[row][col].symbol = MINE_SYMB_G;
        field[row][col + 1].symbol = MINE_SYMB_G1;
        gordPlayer->coins -= 20;
        showCoinsGondor(gordPlayer);
        printf("Mine created at [%d][%d]!\n", row, col);
        if (gordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!\n", gordPlayer->coins);
        }
        else if (gordPlayer->coins > 30) {
            printf("Coins after  creation: %d\n", gordPlayer->coins);

        }
    }
    else {
        printf("Cannot create Mine at [%d][%d]!!!!\n", row, col);
    }
}

/**
 *
 * \function name- placingMineG
 * \params- gordPlayer
 * \brief-  Colocar a Mina no campo de batalha
 *
 *
 */
void placingMineG(gordorPlayer* gordPlayer) {
    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createMineGondor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Mine at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createMineGondor com as novas coordenadas
    createMineGondor(baseRow, baseCol, gordPlayer);

    // Print the field after creating the base
    printField();
}


/**
 *
 * \function name- createBarrackGondor
 * \params- row
 * \params- col
 * \params- barrack
 * \params- gordPlayer
 * \brief- Criar uma barricada no campo de batalha
 *
 *
 */
void createBarrackGondor(int row, int col, gordorPlayer* gordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ') && gordPlayer >= 25)
    {
        field[row][col].symbol = BARRACK_SYMB_G;
        field[row][col].symbol = BARRACK_SYMB_G1;
        gordPlayer->coins -= 25;
        showCoinsGondor(gordPlayer);
        printf("Barrack created at [%d][%d]!\n", row, col);
        if (gordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!\n", gordPlayer->coins);
        }
        else if (gordPlayer->coins > 30){
            printf("Coins after  creation: %d\n", gordPlayer->coins);

        }
    }
    else {
        printf("Cannot create Barrack at [%d][%d]!!!!\n", row, col);
    }

}

/**
 *
 * \function name- placingBarrackG
 * \params- gordPlayer
 * \brief-  Colocar o Quartel no campo de batalha
 *
 *
 */
void placingBarrackG(gordorPlayer* gordPlayer) {

    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createBarrackGondor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Barrack at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createBarrackGondor com as novas coordenadas
    createBarrackGondor(baseRow, baseCol, gordPlayer);

    // Print the field after creating the base
    printField();

}


/**
 *
 * \function name- createStablesGondor
 * \params- row
 * \params- col
 * \params- gordPlayer
 * \brief- Criar um Estabulo no campo de batalha
 *
 *
 */
void createStablesGondor(int row, int col, gordorPlayer* gordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ') && gordPlayer->coins >= 25) 
    {
        field[row][col].symbol = STABLES_SYMB_G;
        field[row][col].symbol = STABLES_SYMB_G1;
        gordPlayer->coins -= 25;
        showCoinsGondor(gordPlayer);
        printf("Stables created at [%d][%d]!\n", row, col);
        if (gordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!\n", gordPlayer->coins);
        }
        else if (gordPlayer->coins > 30) {
            printf("Coins after  creation: %d\n", gordPlayer->coins);
        }
    }
    else {
        printf("Cannot create Stables at [%d][%d]!!!!\n", row, col);
    }
}

/**
 *
 * \function name- placingStableG
 * \params- gordPlayer
 * \brief-  Colocar o Estabulo no campo de batalha
 *
 *
 */
void placingStableG(gordorPlayer* gordPlayer) {

    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createStablesGondor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Stables at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createStablesGondor com as novas coordenadas
    createStablesGondor(baseRow, baseCol, gordPlayer);

    // Print the field after creating the base
    printField();

}


/**
 *
 * \function name- createArmouryGondor
 * \params- row
 * \params- col
 * \params- gordPlayer
 * \brief- Criar um Arsenal no campo de batalha
 *
 *
 */
void createArmouryGondor(int row, int col, gordorPlayer* gordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ') && gordPlayer->coins >= 30)
    {
        field[row][col].symbol = ARMOURY_SYMB_G;
        field[row][col + 1].symbol = ARMOURY_SYMB_G1;
        gordPlayer -= 30;
        showCoinsGondor(gordPlayer);
        printf("Armoury created at [%d][%d]!\n", row, col);
        if (gordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!\n", gordPlayer->coins);
        }
        else if (gordPlayer->coins > 30) {
            printf("Coins after  creation: %d\n", gordPlayer->coins);
        }
           }
    else {
        printf("Cannot create Armoury at [%d][%d]!!!!\n", row, col);
    }
}

/**
 *
 * \function name- placingArmouryG
 * \params- gordPlayer
 * \brief-  Colocar o Arsenal no campo de batalha
 *
 *
 */
void placingArmouryG(gordorPlayer* gordPlayer) {

    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createArmouryGondor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Armoury at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createArmouryGondor com as novas coordenadas
    createArmouryGondor(baseRow, baseCol, gordPlayer);

    // Print the field after creating the base
    printField();

}


/**
 *
 * \function name- createInfantry
 * \params- row
 * \params- col
 * \params- gordPLayer
 * \brief- Cria um soldado de infantaria
 *
 *
 */
 //void createInfantry(int row, int col, gondorUnits infantry, gordorPlayer *gordPLayer)
void createInfantryGondor(int row, int col, gordorPlayer* gordPLayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ') && gordPLayer->coins >= 10) 
    {
        field[row][col].symbol = INFANTARY_SYMB_G;
        gordPLayer->coins -= 10;
        showCoinsGondor(gordPLayer);
        printf("Infantry created at [%d][%d]!\n", row, col);
        if (gordPLayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!\n", gordPLayer->coins);
        }
        else if (gordPLayer->coins > 30) {
            printf("Coins after creation: %d\n", gordPLayer->coins);
        }
    }
    else {
        printf("Cannot create Infantry at [%d][%d]!!!!\n", row, col);
    }
}

void placingInfantryG(gordorPlayer* gordPlayer) {

    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createArmouryGondor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Infantry at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createArmouryGondor com as novas coordenadas
    createInfantryGondor(baseRow, baseCol, gordPlayer);

    // Print the field after creating the base
    printField();

}


/**
 *
 * \function name- createCavalry
 * \params- row
 * \params- col

 * \params- gordPlayer
 * \brief- Cria um soldado de cavalaria
 *
 *
 */
void createCavalryGondor(int row, int col, gordorPlayer* gordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ') && gordPlayer->coins >= 15) 
    {
        field[row][col].symbol = CAVALARY_SYMB_G;
        field[row][col + 1].symbol = CAVALARY_SYMB_G1;
        gordPlayer->coins -= 15;

        showCoinsGondor(gordPlayer);
        printf("Cavalry created at [%d][%d]!\n", row, col);
        if (gordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!\n", gordPlayer->coins);
        }
        else if (gordPlayer->coins > 30) {
            printf("Coins after creation: %d\n", gordPlayer->coins);
        }
    }
    else {
        printf("Cannot create Cavalry at [%d][%d]!!!!\n", row, col);
    }
}

void placingCavalryG(gordorPlayer* gordPlayer) {
    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createCavalryGondor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Cavalry at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createCavalryGondor com as novas coordenadas
    createCavalryGondor(baseRow, baseCol, gordPlayer);

    // Print the field after creating the base
    printField();

}


/**
 *
 * \function name- createArtillery
 * \params- row
 * \params- col
 * \params- gordPlayer
 * \brief- Cria um soldado de artilharia
 *
 *
 */
void createArtilleryGondor(int row, int col, gordorPlayer* gordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ') && gordPlayer->coins >= 20)
    {
        field[row][col].symbol = ARTILLERY_SYMB_G;
        gordPlayer->coins -= 20;
        showCoinsGondor(gordPlayer);
        printf("Artillery created at [%d][%d]!\n", row, col);
        if (gordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!\n", gordPlayer->coins);
        }
        else if (gordPlayer->coins > 30) {
            printf("Coins after creation: %d\n", gordPlayer->coins);
        }
    }
    else {
        printf("Cannot create base at [%d][%d]!!!!\n", row, col);
    }
}

void placingArtilleryG(gordorPlayer* gordPlayer) {
    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createArtilleryGondor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Artillery at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createArtilleryGondor com as novas coordenadas
    createArtilleryGondor(baseRow, baseCol, gordPlayer);

    // Print the field after creating the base
    printField();
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
void moveInfantryGondor(gordorPlayer* gordPlayer) {
    int sourceRow, destRow;
    char sourceCol[2], destCol[2];
    showCoinsGondor(gordPlayer);

    // Get source position
    printf("\nEnter the row where the Gondor Infantry is located: ");
    scanf_s("%d", &sourceRow, sizeof(sourceRow));
    printf("Enter the column where the Gondor Infantry is located (A-Z): ");
    scanf_s("%s", &sourceCol, sizeof(sourceCol));

    // Get destination position
    printf("\nEnter the row to move the Gondor Infantry: ");
    scanf_s("%1d", &destRow, sizeof(destRow));
    printf("Enter the column to move the Gondor Infantry (A-Z): ");
    scanf_s("%1s", destCol, sizeof(destCol));

    // Convert column characters to uppercase for consistency
    sourceCol[0] = toupper(sourceCol[0]);
    destCol[0] = toupper(destCol[0]);

    // Convert column characters to 0-based index
    int sourceColumn = sourceCol[0] - 'A';
    int destColumn = destCol[0] - 'A';

    // Debug information
    printf("DEBUG: Moving Gondor Infantry from [%d][%s] to [%d][%s]\n", sourceRow, sourceCol, destRow, destCol);

    // Check if the source cell is out of bounds
    if (sourceRow < 0 || sourceRow >= ROWS || sourceColumn < 0 || sourceColumn >= COLS) {
        printf("\nDEBUG: Invalid source position for the Gondor Infantry.\n");
        return;
    }

    // Check if the source cell is occupied by 'F'
    if (field[sourceRow][sourceColumn].symbol != INFANTARY_SYMB_G) {
        printf("\nDEBUG: No Gondor Infantry found at the specified source position.\n");
        return;
    }

    // Check if the destination cell is within bounds
    if (destRow >= 0 && destRow < ROWS && destColumn >= 0 && destColumn < COLS) {
        // Deduct 2 coins for each cell moved horizontally
        int cellsMoved = abs(destColumn - sourceColumn) + 1;  // Adding 1 to include the destination cell
        int totalCost = 2 * cellsMoved;

        // Check if the player has enough coins for the movement
        if (gordPlayer->coins >= totalCost) {
            // Update the positions of Gondor Infantry
            field[destRow][destColumn].symbol = INFANTARY_SYMB_G;  // New position
            field[sourceRow][sourceColumn].symbol = ' ';  // Clear the old position

            // Deduct coins from the player
            gordPlayer->coins -= totalCost;

            printf("\nDEBUG: Gondor Infantry moved successfully to the intended place.\n");
            printf("\nCoins before movement: %d\n", gordPlayer->coins + totalCost);  // Display coins before the movement
            printf("\nCoins after movement: %d\n", gordPlayer->coins);

            // Ensure to print the updated field
            printField(field);
        }
        else {
            printf("\nDEBUG: Insufficient coins to move Gondor Infantry.\n");
            return;
        }
    }
    else {
        printf("\nDEBUG: Invalid destination position for Gondor Infantry.\n");
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
void moveCavalryGondor(gordorPlayer* gordPlayer) {
    int sourceRow, destRow;
    char sourceCol[2], destCol[2];
    showCoinsGondor(gordPlayer);

    // Get source position
    printf("\nEnter the row where the Gondor Cavalry is located: ");
    scanf_s("%d", &sourceRow, sizeof(sourceRow));
    printf("Enter the column where the Gondor Cavalry is located (A-Z): ");
    scanf_s("%s", sourceCol, sizeof(sourceCol));

    // Get destination position
    printf("\nEnter the row to move the Gondor Cavalry: ");
    scanf_s("%d", &destRow, sizeof(destRow));
    printf("Enter the column to move the Gondor Cavalry (A-Z): ");
    scanf_s("%s", destCol, sizeof(destCol));

    // Convert column characters to uppercase for consistency
    sourceCol[0] = toupper(sourceCol[0]);
    destCol[0] = toupper(destCol[0]);

    // Convert column characters to 0-based index
    int sourceColumn = sourceCol[0] - 'A';
    int destColumn = destCol[0] - 'A';

    // Debug information
    printf("DEBUG: Moving Gondor Cavalry from [%d][%s] to [%d][%s]\n", sourceRow, sourceCol, destRow, destCol);

    // Check if the source cell is out of bounds
    if (sourceRow < 0 || sourceRow >= ROWS || sourceColumn < 0 || sourceColumn >= COLS) {
        printf("\nDEBUG: Invalid source position for the Gondor Cavalry.\n");
        return;
    }

    // Check if the source cell is occupied by 'S' or 'K'
    if (field[sourceRow][sourceColumn].symbol != CAVALARY_SYMB_G &&
        field[sourceRow][sourceColumn].symbol != CAVALARY_SYMB_G1) {
        printf("\nDEBUG: No Gondor Cavalry found at the specified source position.\n");
        return;
    }

    // Check if the destination cells are within bounds
    if (destRow >= 0 && destRow < ROWS && destColumn >= 0 && destColumn + 1 < COLS) {
        // Check if the destination cells are empty
        if (field[destRow][destColumn].symbol == ' ' &&
            field[destRow][destColumn + 1].symbol == ' ') {

            // Calculate the distance moved by Gondor Cavalry
            int cellsMoved = abs(destRow - sourceRow) + 1;  // Adding 1 to include the destination cell
            int totalCost = 2 * cellsMoved;  // Deduct 2 coins for each cell moved

            // Check if the player has enough coins for the movement
            if (gordPlayer->coins >= totalCost) {
                // Update the positions of Gondor Cavalry
                field[destRow][destColumn].symbol = CAVALARY_SYMB_G;      // New position
                field[destRow][destColumn + 1].symbol = CAVALARY_SYMB_G1;  // New position
                field[sourceRow][sourceColumn].symbol = ' ';               // Clear the old position
                field[sourceRow][sourceColumn + 1].symbol = ' ';           // Clear the old position

                // Deduct coins from the player
                gordPlayer->coins -= totalCost;

                printf("\nDEBUG: Gondor Cavalry moved successfully to the intended place.\n");
                printf("\nCoins before movement: %d\n", gordPlayer->coins + totalCost);  // Display coins before the movement
                printf("\nCoins after movement: %d\n", gordPlayer->coins);

                printField(field);  // Ensure to print the updated field
            }
            else {
                printf("\nDEBUG: Insufficient coins to move Gondor Cavalry.\n");
            }

            return;
        }
        else {
            printf("\nDEBUG: Destination cells are occupied.\n");
        }
    }

    printf("\nDEBUG: Invalid destination position for Gondor Cavalry.\n");
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
void moveArtilleryGondor(gordorPlayer* gordPlayer) {
    int sourceRow, destRow;
    char sourceCol[2], destCol[2];
    showCoinsGondor(gordPlayer);

    // Get source position
    printf("\nEnter the row where the Gondor Artillery is located: ");
    scanf_s("%d", &sourceRow, sizeof(sourceRow));
    printf("Enter the column where the Gondor Artillery is located (A-Z): ");
    scanf_s("%s", sourceCol, sizeof(sourceCol));

    // Get destination position
    printf("\nEnter the row to move the Gondor Artillery: ");
    scanf_s("%d", &destRow, sizeof(destRow));
    printf("Enter the column to move the Gondor Artillery (A-Z): ");
    scanf_s("%s", destCol, sizeof(destCol));

    // Convert column characters to uppercase for consistency
    sourceCol[0] = toupper(sourceCol[0]);
    destCol[0] = toupper(destCol[0]);

    // Convert column characters to 0-based index
    int sourceColumn = sourceCol[0] - 'A';
    int destColumn = destCol[0] - 'A';

    // Debug information
    printf("DEBUG: Moving Gondor Artillery from [%d][%s] to [%d][%s]\n", sourceRow, sourceCol, destRow, destCol);

    // Check if the source cell is out of bounds
    if (sourceRow < 0 || sourceRow >= ROWS || sourceColumn < 0 || sourceColumn >= COLS) {
        printf("\nDEBUG: Invalid source position for the Gondor Artillery.\n");
        return;
    }

    // Check if the source cell is occupied by Artillery
    if (field[sourceRow][sourceColumn].symbol != ARTILLERY_SYMB_G) {
        printf("\nDEBUG: No Gondor Artillery found at the specified source position.\n");
        return;
    }

    // Check if the destination cell is within bounds
    if (destRow >= 0 && destRow < ROWS && destColumn >= 0 && destColumn < COLS) {
        // Deduct 2 coins for each cell moved horizontally
        int cellsMoved = abs(destColumn - sourceColumn) + 1;  // Adding 1 to include the destination cell
        int totalCost = 3 * cellsMoved;

        // Check if the player has enough coins for the movement
        if (gordPlayer->coins >= totalCost) {
            // Update the positions of Gondor Infantry
            field[destRow][destColumn].symbol = ARTILLERY_SYMB_G;  // New position
            field[sourceRow][sourceColumn].symbol = ' ';  // Clear the old position

            // Deduct coins from the player
            gordPlayer->coins -= totalCost;

            printf("\nDEBUG: Gondor Artillery moved successfully to the intended place.\n");
            printf("\nCoins before movement: %d\n", gordPlayer->coins + totalCost);  // Display coins before the movement
            printf("\nCoins after movement: %d\n", gordPlayer->coins);

            // Ensure to print the updated field
            printField(field);
        }
        else {
            printf("\nDEBUG: Insufficient coins to move Gondor Artillery.\n");
            return;
        }
    }
    else {
        printf("\nDEBUG: Invalid destination position for Gondor Artillery.\n");
    }
}


#pragma endregion

    #pragma region ATTACK 

                        //Funcoes para atacar a partir das unidades de Gondor


    #pragma region Gondor units vs MordorBase

void GondorInfantryVSMordBase(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack;
    int rowPosition;
    char colPosition;
    char colAtack;

    printf("ATTACKING WITH GONDOR INFANTRY\n");
    printf("Select the row where gondor infantry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor infantry is positioned: \n");
    scanf_s(" %c", &colPosition);


    printf("Select the row where mordor base is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor base is positioned: \n");
    scanf_s("%c", &colAtack);

    if (rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS &&
        rowAtack >= 0 && rowAtack < ROWS && rowAtack >= 0 && colAtack < COLS) {

        if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_G) {
            // Verifique se a posi��o da infantaria � adjacente � posi��o da base
            if ((abs(rowPosition - rowAtack) <= 1 && abs(colPosition - colAtack) == 0) ||
                (abs(rowPosition - rowAtack) == 0 && abs(colPosition - colAtack) <= 1)) {

                mordPlayer->mBaseHealth -= 5; // Dano que a infantaria causa � base
                printf("Mordor base health after attack: %d\n", mordPlayer->mBaseHealth);

                if (mordPlayer->mBaseHealth <= 0) {
                    // Defina os s�mbolos como espa�o em branco para representar a destrui��o da base
                    field[rowAtack][colAtack].symbol = ' ';
                    printf("Mordor base was destroyed!\n");
                    printf("You won the game!!!\n");
                    printf("Gondor is safe because of you!!\n");
                }
            }
            else {
                printf("Mordor base not adjacent to Gondor infantry!!\n");
            }
        }
        else {
            printf("Mordor base not found!!\n");
        }
    }
    else {
        printf("Invalid position!!\n");
    }
}

void GondorCavalryVSMordBase(int row, int col, mordorPlayer* mordPlayer) 
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR INFANTRY\n");
    printf("Select the row where gondor cavalry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor cavalry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor base is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor base is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_G) {
            if ((field[row][col].symbol == BASE_SYMB_M) && (field[row][col + 1].symbol == BASE_SYMB_M1) &&
                (field[row][col + 2].symbol == BASE_SYMB_M2) && (field[row][col - 1].symbol == BASE_SYMB_M3))
            {
                mordPlayer->mBaseHealth -= 7; //dano que a cavalaria vai dar ao atacar a base
                printf("Mordor base health after attack: %d\n ", mordPlayer->mBaseHealth);

                if (mordPlayer->mBaseHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' ') &&
                        (field[row][col + 2].symbol = ' ') && (field[row][col - 1].symbol = ' '));
                    printf("Mordor base was destroyed!\n");
                    printf("You won the game!!!\n");
                    printf("Gondor is safed because of you!!\n");
                }


            }
            else {
                printf("Mordor base not found!!\n");
            }

        }
       


    }
    else {
        printf("Invalid position!!\n");
    }

}


void GondorArtilleryVSMordBase(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR ARTILLERY\n");
    printf("Select the row where gondor artillery is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor artillery is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor base is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor base is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_G) {

            if ((field[row][col].symbol == BASE_SYMB_M) && (field[row][col + 1].symbol == BASE_SYMB_M1) &&
                (field[row][col + 2].symbol == BASE_SYMB_M2) && (field[row][col - 1].symbol == BASE_SYMB_M3))
            {

                mordPlayer->mBaseHealth -= 10; //dano que a artilharia vai dar ao atacar a base
                printf("Mordor base health after attack: %d\n ", mordPlayer->mBaseHealth);

                if (mordPlayer->mBaseHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' ') &&
                        (field[row][col + 2].symbol = ' ') && (field[row][col - 1].symbol = ' '));
                    printf("Mordor base was destroyed!\n");
                    printf("You won the game!!!\n");
                    printf("Gondor is safed because of you!!\n");
                }


            }
            else {
                printf("Mordor base not found!!\n");
            }
        }
        


    }
    else {
        printf("Invalid position!!\n");
    }

}

#pragma endregion

    #pragma region Gondor Units vs Mordor Mine

void GondorInfantryVSMordMine(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR INFANTRY\n");
    printf("Select the row where gondor artillery is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor artillery is positioned: \n");
    scanf_s("%d", &colPosition);


    printf("Select the row where mordor mine is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor mine is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_G) 
        {

            if ((field[row][col].symbol == MINE_SYMB_M) && (field[row][col + 1].symbol == MINE_SYMB_M1))
            {

                mordPlayer->mMineHealth -= 5; //dano que a infantaria vai dar ao atacar a mina
                printf("Mordor mine health after attack: %d\n ", mordPlayer->mMineHealth);

                if (mordPlayer->mMineHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor mine was destroyed!\n");
                }


            }
            else {
                printf("Mordor mine not found!!\n");
            }
        }
        


    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorCavalryVSMordMine(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR CAVALRY\n");
    printf("Select the row where gondor cavalry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor cavalry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor mine is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor mine is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_G)
        {
            if ((field[row][col].symbol == MINE_SYMB_M) && (field[row][col + 1].symbol == MINE_SYMB_M1))
            {

                mordPlayer->mMineHealth -= 7; //dano que a cavalaria vai dar ao atacar a mina
                printf("Mordor mine health after attack: %d\n ", mordPlayer->mMineHealth);

                if (mordPlayer->mMineHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor mine was destroyed!\n");
                }


            }
            else {
                printf("Mordor mine not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorArtilleryVSMordMine(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR ARTILLERY\n");
    printf("Select the row where gondor artillery is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor artillery is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor mine is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor mine is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_G)
        {
            if ((field[row][col].symbol == MINE_SYMB_M) && (field[row][col + 1].symbol == MINE_SYMB_M1))
            {

                mordPlayer->mMineHealth -= 10; //dano que a cavalaria vai dar ao atacar a mina
                printf("Mordor mine health after attack: %d\n ", mordPlayer->mMineHealth);

                if (mordPlayer->mMineHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor mine was destroyed!\n");
                }


            }
            else {
                printf("Mordor mine not found!!\n");
            }

        }    

    }
    else {
        printf("Invalid position!!\n");
    }

}

    #pragma endregion

    #pragma region Gondor Units vs Mordor Barrack

void GondorInfantrVSMordBarrack(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR INFANTRY\n");
    printf("Select the row where gondor infantry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor infantry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor barrack is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor barrack is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol ==  INFANTARY_SYMB_G)
        {
            if ((field[row][col].symbol == BARRACK_SYMB_M) && (field[row][col + 1].symbol == BARRACK_SYMB_M1))
            {

                mordPlayer->mBarrackHealth -= 5; //dano que a infantaria vai dar ao atacar a barrack
                printf("Mordor barrack health after attack: %d\n ", mordPlayer->mBarrackHealth);

                if (mordPlayer->mBarrackHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor barrack was destroyed!\n");
                }


            }
            else {
                printf("Mordor barrack not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorCavalryVSMordBarrack(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR CAVALRY\n");
    printf("Select the row where gondor cavalry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor cavalry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor barrack is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor barrack is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_G) 
        {

            if ((field[row][col].symbol == BARRACK_SYMB_M) && (field[row][col + 1].symbol == BARRACK_SYMB_M1))
            {

                mordPlayer->mBarrackHealth -= 7; //dano que a cavalaria vai dar ao atacar a barrack
                printf("Mordor barrack health after attack: %d\n ", mordPlayer->mBarrackHealth);

                if (mordPlayer->mBarrackHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor barrack was destroyed!\n");
                }


            }
            else {
                printf("Mordor barrack not found!!\n");
            }

            
        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorArtilleryVSMordBarrack(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR ARTILLERY\n");
    printf("Select the row where gondor artillery is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor artillery is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor barrack is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor barrack is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_G) 
        {
            if ((field[row][col].symbol == BARRACK_SYMB_M) && (field[row][col + 1].symbol == BARRACK_SYMB_M1))
            {

                mordPlayer->mBarrackHealth -= 10; //dano que a artilharia vai dar ao atacar a barrack
                printf("Mordor barrack health after attack: %d\n ", mordPlayer->mBarrackHealth);

                if (mordPlayer->mBarrackHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor barrack was destroyed!\n");
                }


            }
            else {
                printf("Mordor barrack not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}


#pragma endregion

    #pragma region Gondor Units vs Mordor Stable

void GondorInfantrVSMordStable(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR INFANTRY\n");
    printf("Select the row where gondor infantry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor infantry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor stable is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor stable is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_G)
        {
            if ((field[row][col].symbol == STABLES_SYMB_M) && (field[row][col + 1].symbol == STABLES_SYMB_M1))
            {

                mordPlayer->mStableHealth -= 5; //dano que a infantaria vai dar ao atacar a stable
                printf("Mordor stable health after attack: %d\n ", mordPlayer->mStableHealth);

                if (mordPlayer->mStableHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor stable was destroyed!\n");
                }


            }
            else {
                printf("Mordor stable not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorCavalryVSMordStable(int row, int col,  mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR CAVALRY\n");
    printf("Select the row where gondor cavalry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor cavalry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor stable is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor stable is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_G)
        {
            if ((field[row][col].symbol == STABLES_SYMB_M) && (field[row][col + 1].symbol == STABLES_SYMB_M1))
            {

                mordPlayer->mStableHealth -= 7; //dano que a cavalaria vai dar ao atacar a stable
                printf("Mordor stable health after attack: %d\n ", mordPlayer->mStableHealth);

                if (mordPlayer->mStableHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor stable was destroyed!\n");
                }


            }
            else {
                printf("Mordor stable not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorArtilleryVSMordStable(int row, int col,  mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR CAVALRY\n");
    printf("Select the row where gondor artillery is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor artillery is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor stable is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor stable is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_G)
        {
            if ((field[row][col].symbol == STABLES_SYMB_M) && (field[row][col + 1].symbol == STABLES_SYMB_M1))
            {

                mordPlayer->mStableHealth -= 10; //dano que a artilharia vai dar ao atacar a stable
                printf("Mordor stable health after attack: %d\n ", mordPlayer->mStableHealth);

                if (mordPlayer->mStableHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor stable was destroyed!\n");
                }


            }
            else {
                printf("Mordor stable not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}


    #pragma endregion

    #pragma region Gondor Units vs Mordor Armoury

void GondorInfantrVSMordArmoury(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR INFANTRY\n");
    printf("Select the row where gondor infantry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor infantry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor armoury is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor armoury is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if(field[rowAtack][colAtack].symbol == INFANTARY_SYMB_G)
        {
            if ((field[row][col].symbol == ARMOURY_SYMB_M) && (field[row][col + 1].symbol == ARMOURY_SYMB_M1))
            {

                mordPlayer->mArmouryHealth -= 5; //dano que a infantaria vai dar ao atacar a stable
                printf("Mordor armoury health after attack: %d\n ", mordPlayer->mArmouryHealth);

                if (mordPlayer->mArmouryHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor armoury was destroyed!\n");
                }


            }
            else {
                printf("Mordor armoury not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorCavalryVSMordArmoury(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR CAVALRY\n");
    printf("Select the row where gondor cavalry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor cavalry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor armoury is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor armoury is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_G)
        {
            if ((field[row][col].symbol == ARMOURY_SYMB_M) && (field[row][col + 1].symbol == ARMOURY_SYMB_M1))
            {

                mordPlayer->mArmouryHealth -= 7; //dano que a cavalaria vai dar ao atacar a stable
                printf("Mordor armoury health after attack: %d\n ", mordPlayer->mArmouryHealth);

                if (mordPlayer->mArmouryHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor armoury was destroyed!\n");
                }

            }
            else {
                printf("Mordor armoury not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorArtilleryVSMordArmoury(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR ARTILLERY\n");
    printf("Select the row where gondor artillery is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor artillery is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor armoury is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor armoury is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_G)
        {
            if ((field[row][col].symbol == ARMOURY_SYMB_M) && (field[row][col + 1].symbol == ARMOURY_SYMB_M1))
            {

                mordPlayer->mArmouryHealth -= 10; //dano que a artilharia vai dar ao atacar a stable
                printf("Mordor armoury health after attack: %d\n ", mordPlayer->mArmouryHealth);

                if (mordPlayer->mArmouryHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor armoury was destroyed!\n");
                }

            }
            else {
                printf("Mordor armoury not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}

    #pragma endregion


    #pragma region Gondor Units vs Mordor Infantry

void GondorInfantrVSMordInfantry(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR INFANTRY\n");
    printf("Select the row where gondor infantry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor infantry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor infantry is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor infantry is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_G)
        {
            if ((field[row][col].symbol == INFANTARY_SYMB_M) && (field[row][col + 1].symbol == INFANTARY_SYMB_M1))
            {

                mordPlayer->infantryHealth -= 5; //dano que a infantariaGondor vai dar ao atacar a infantariaMordor
                printf("Mordor infantry health after attack: %d\n ", mordPlayer->infantryHealth);

                if (mordPlayer->infantryHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor infantry was destroyed!\n");
                }
            }
            else {
                printf("Mordor infantry not found!!\n");
            }
        }

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorCavalryVSMordInfantry(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR CAVALRY\n");
    printf("Select the row where gondor cavalry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor cavalry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor infantry is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor infantry is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_G)
        {
            if ((field[row][col].symbol == INFANTARY_SYMB_M) && (field[row][col + 1].symbol == INFANTARY_SYMB_M1))
            {

                mordPlayer->infantryHealth -= 7; //dano que a cavalaria Gondor vai dar ao atacar a cavalaria Mordor
                printf("Mordor infantry health after attack: %d\n ", mordPlayer->infantryHealth);

                if (mordPlayer->infantryHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor infantry was destroyed!\n");
                }
            }
            else {
                printf("Mordor infantry not found!!\n");
            }
        }    


    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorArtilleryVSMordInfantry(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR ARTILLERY\n");
    printf("Select the row where gondor artillery is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor artillery is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor infantry is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor infantry is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_G)
        {
            if ((field[row][col].symbol == INFANTARY_SYMB_M) && (field[row][col + 1].symbol == INFANTARY_SYMB_M1))
            {

                mordPlayer->infantryHealth -= 10; //dano que a artilharia Gondor vai dar ao atacar a artilharia Mordor
                printf("Mordor infantry health after attack: %d\n ", mordPlayer->infantryHealth);

                if (mordPlayer->infantryHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor infantry was destroyed!\n");
                }
            }
            else {
                printf("Mordor infantry not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}

#pragma endregion

    #pragma region Gondor Units vs Mordor Cavalry

void GondorInfantryVSMordCavalry(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR INFANTRY\n");
    printf("Select the row where gondor infantry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor infantry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor cavalry is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor cavalry is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_G) 
        {
            if ((field[row][col].symbol == CAVALARY_SYMB_M))
            {

                mordPlayer->cavalryHealth -= 5; //dano que a infantaria Gondor vai dar ao atacar a cavalaria Mordor
                printf("Mordor cavalry health after attack: %d\n ", mordPlayer->cavalryHealth);

                if (mordPlayer->cavalryHealth <= 0) {
                    field[row][col].symbol = ' ';
                    printf("Mordor cavalry was destroyed!\n");
                }
            }
            else {
                printf("Mordor cavalry not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorCavalryVSMordCavalry(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR CAVALRY\n");
    printf("Select the row where gondor cavalry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor cavalry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor cavalry is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor cavalry is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_G)
        {
            if ((field[row][col].symbol == CAVALARY_SYMB_M))
            {

                mordPlayer->cavalryHealth -= 7; //dano que a cavalaria Gondor vai dar ao atacar a cavalaria Mordor
                printf("Mordor cavalry health after attack: %d\n ", mordPlayer->cavalryHealth);

                if (mordPlayer->cavalryHealth <= 0) {
                    field[row][col].symbol = ' ';
                    printf("Mordor cavalry was destroyed!\n");
                }
            }
            else {
                printf("Mordor cavalry not found!!\n");
            }
        }

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorArtillheryVSMordCavalry(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR ARTILLERY\n");
    printf("Select the row where gondor artillery is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor artillery is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor cavalry is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor cavalry is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_G)
        {
            if ((field[row][col].symbol == CAVALARY_SYMB_M))
            {

                mordPlayer->cavalryHealth -= 10; //dano que a artilharia Gondor vai dar ao atacar a cavalaria Mordor
                printf("Mordor cavalry health after attack: %d\n ", mordPlayer->cavalryHealth);

                if (mordPlayer->cavalryHealth <= 0) {
                    field[row][col].symbol = ' ';
                    printf("Mordor cavalry was destroyed!\n");
                }
            }
            else {
                printf("Mordor cavalry not found!!\n");
            }

        }       

    }
    else {
        printf("Invalid position!!\n");
    }

}

    #pragma endregion

    #pragma region Gondor Units vs Mordor Artillery

void GondorInfantryVSMordArtillhery(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR INFANTRY\n");
    printf("Select the row where gondor infantry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor infantry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor artillery is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor artillery is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_G)
        {
            if ((field[row][col].symbol == ARTILLERY_SYMB_M) && (field[row][col + 1].symbol == ARTILLERY_SYMB_M1))
            {

                mordPlayer->artilleryHealth -= 5; //dano que a infantaria Gondor vai dar ao atacar a artilharia Mordor
                printf("Mordor artillery health after attack: %d\n ", mordPlayer->artilleryHealth);

                if (mordPlayer->artilleryHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor artillery was destroyed!\n");
                }
            }
            else {
                printf("Mordor artillery not found!!\n");
            }

        }
        

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorCavalryVSMordArtillhery(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR CAVALRY\n");
    printf("Select the row where gondor cavalry is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor cavalry is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor artillery is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor artillery is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_G)
        {
            if ((field[row][col].symbol == ARTILLERY_SYMB_M) && (field[row][col + 1].symbol == ARTILLERY_SYMB_M1))
            {

                mordPlayer->artilleryHealth -= 7; //dano que a infantaria Gondor vai dar ao atacar a artilharia Mordor
                printf("Mordor artillery health after attack: %d\n ", mordPlayer->artilleryHealth);

                if (mordPlayer->artilleryHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor artillery was destroyed!\n");
                }
            }
            else {
                printf("Mordor artillery not found!!\n");
            }

        }    

    }
    else {
        printf("Invalid position!!\n");
    }

}

void GondorArtilleryVSMordArtillhery(int row, int col, mordorPlayer* mordPlayer)
{
    int rowAtack, colAtack;
    int rowPosition, colPosition;

    printf("ATTACKING WITH GONDOR ARTILLERY\n");
    printf("Select the row where gondor artillery is positioned: \n");
    scanf_s("%d", &rowPosition);
    printf("Select the column where gondor artillery is positioned: \n");
    scanf_s("%d", &colPosition);

    printf("Select the row where mordor artillery is positioned: \n");
    scanf_s("%d", &rowAtack);
    printf("Select the column where mordor artillery is positioned: \n");
    scanf_s("%d", &colAtack);

    row = rowAtack;
    col = colAtack;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
    {
        if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_G)
        {
            if ((field[row][col].symbol == ARTILLERY_SYMB_M) && (field[row][col + 1].symbol == ARTILLERY_SYMB_M1))
            {

                mordPlayer->artilleryHealth -= 10; //dano que a infantaria Gondor vai dar ao atacar a artilharia Mordor
                printf("Mordor artillery health after attack: %d\n ", mordPlayer->artilleryHealth);

                if (mordPlayer->artilleryHealth <= 0) {
                    ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                    printf("Mordor artillery was destroyed!\n");
                }
            }
            else {
                printf("Mordor artillery not found!!\n");
            }
        }

    }
    else {
        printf("Invalid position!!\n");
    }

}


#pragma endregion


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
void createBaseMordor(int row, int col, mordorPlayer* mordPLayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ' &&
        field[row + 1][col].symbol == ' ' &&
        field[row + 1][col + 1].symbol == ' ') && mordPLayer->coins >=30)
    {
        field[row][col].symbol = BASE_SYMB_M;
        field[row][col + 1].symbol = BASE_SYMB_M1;
        field[row][col + 2].symbol = BASE_SYMB_M2;
        field[row][col - 1].symbol = BASE_SYMB_M3;
        mordPLayer->coins -= 30;
        showCoinsMordor(mordPLayer);
        printf("Base created at [%d][%d]!\n", row, col);
        if (mordPLayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!", mordPLayer->coins);
        }
        else if (mordPLayer->coins > 30) {
            printf("Coins after base creation: %d\n", mordPLayer->coins);
        }
        
    }
    else {
        printf("Cannot create base at [%d][%d]!!!!\n", row, col);
    }
}

/**
 *
 * \function name- placingBaseM
 * \params- mordPlayer
 * \brief-  Colocar a base no campo de batalha
 *
 *
 */
void placingBaseM(mordorPlayer* mordPlayer) {

    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createBaseMordor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Base at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createBaseMordor com as novas coordenadas
    createBaseMordor(baseRow, baseCol, mordPlayer);

    // Print the field after creating the base
    printField();

}


/**
 *
 * \function name- createMineMordor
 * \params- row
 * \params- col
 * \params- mordPlayer
 * \brief- Criar uma mina no campo de batalha
 *
 *
 */
void createMineMordor(int row, int col, mordorPlayer* mordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ') && mordPlayer->coins >= 20) 
    {
        field[row][col].symbol = MINE_SYMB_M;
        field[row][col+1].symbol = MINE_SYMB_M1;
        mordPlayer->coins -= 20;
        showCoinsMordor(mordPlayer);
        printf("Mine created at [%d][%d]!\n", row, col);
        if (mordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!", mordPlayer->coins);
        }else if (mordPlayer->coins > 30) {
            printf("Coins after  creation: %d\n", mordPlayer->coins);
        }
    }
    else {
        printf("Cannot create Mine at [%d][%d]!!!!\n", row, col);
    }
}

/**
 *
 * \function name- placingMineM
 * \params- mordPlayer
 * \brief-  Colocar a mina no campo de batalha
 *
 *
 */
void placingMineM(mordorPlayer* mordPlayer) {
    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createMineMordor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Mine at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createMineMordor com as novas coordenadas
    createMineMordor(baseRow, baseCol, mordPlayer);

    // Print the field after creating the base
    printField();
}


/**
 *
 * \function name- createBarrackMordor
 * \params- row
 * \params- col
 * \params- mordPlayer
 * \brief- Cria uma barricada no campo de batalha
 *
 *
 */
void createBarrackMordor(int row, int col, mordorPlayer* mordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ') && mordPlayer->coins >= 25)
    {
        field[row][col].symbol = BARRACK_SYMB_M;
        field[row][col + 1].symbol = BARRACK_SYMB_M1;
        mordPlayer->coins -= 25;
        showCoinsMordor(mordPlayer);
        printf("Barrack created at [%d][%d]!\n", row, col);
        if (mordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!", mordPlayer->coins);
        }
        else if (mordPlayer->coins > 30) {
            printf("Coins after  creation: %d\n", mordPlayer->coins);
        }

    }
    else {
        printf("Cannot create Barrack at [%d][%d]!!!!\n", row, col);
    }
}

/**
 *
 * \function name- placingBarrackM
 * \params- mordPlayer
 * \brief-  Colocar a Barraca no campo de batalha
 *
 *
 */
void placingBarrackM(mordorPlayer* mordPlayer) {

    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createBarrackMordor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Barrack at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createBarrackMordor com as novas coordenadas
    createBarrackMordor(baseRow, baseCol, mordPlayer);

    // Print the field after creating the base
    printField();
}


/**
 *
 * \function name- createStablesMordor
 * \params- row
 * \params- col
 * \params- gordPlayer
 * \brief- Criar uma barricada no campo de batalha
 *
 *
 */
void createStablesMordor(int row, int col, mordorPlayer* mordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ') && mordPlayer->coins >= 25)
    {
        field[row][col].symbol = STABLES_SYMB_M;
        field[row][col + 1].symbol = STABLES_SYMB_M1;
        mordPlayer->coins -= 25;
        showCoinsMordor(mordPlayer);
        printf("Stables created at [%d][%d]!\n", row, col);
        if (mordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!", mordPlayer->coins);
        }
        else if (mordPlayer->coins > 30) {
            printf("Coins after  creation: %d\n", mordPlayer->coins);
        }
    }
    else {
        printf("Cannot create Stables at [%d][%d]!!!!\n", row, col);
    }
}

/**
 *
 * \function name- placingStableM
 * \params- mordPlayer
 * \brief-  Colocar o Estabulo no campo de batalha
 *
 *
 */
void placingStableM(mordorPlayer* mordPlayer) {

    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createStablesMordor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Stables at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createStablesMordor com as novas coordenadas
    createStablesMordor(baseRow, baseCol, mordPlayer);

    // Print the field after creating the base
    printField();
}


/**
 *
 * \function name- createArmouryMordor
 * \params- row
 * \params- col
 * \params- barrack
 * \params- gordPlayer
 * \brief- Criar um Arsenal no campo de batalha
 *
 *
 */
void createArmouryMordor(int row, int col, mordorPlayer* mordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ') && mordPlayer->coins >= 30)
    {
        field[row][col].symbol = ARMOURY_SYMB_M;
        field[row][col+1].symbol = ARMOURY_SYMB_M1;
        mordPlayer->coins -= 30;
        showCoinsMordor(mordPlayer);
        printf("Armoury created at [%d][%d]!\n", row, col);
        if (mordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!", mordPlayer->coins);
        }
        else if (mordPlayer->coins > 30) {
            printf("Coins after  creation: %d\n", mordPlayer->coins);
        }
    }
    else {
        printf("Cannot create Armoury at [%d][%d]!!!!\n", row, col);
    }
}

/**
 *
 * \function name- placingArmouryG
 * \params- gordPlayer
 * \brief-  Colocar o Arsenal no campo de batalha
 *
 *
 */
void placingArmouryM(mordorPlayer* mordPlayer) {

    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createArmouryMordor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Armoury at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createArmouryMordor com as novas coordenadas
    createArmouryMordor(baseRow, baseCol, mordPlayer);

    // Print the field after creating the base
    printField();

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
void createInfantryMordor(int row, int col, mordorPlayer* mordPLayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ') && mordPLayer->coins >= 10) 
    {
        field[row][col].symbol = INFANTARY_SYMB_M;
        field[row][col+1].symbol = INFANTARY_SYMB_M1;
        mordPLayer->coins -= 10;
        showCoinsMordor(mordPLayer);
        printf("Infantry created at [%d][%d]!\n", row, col);
        if (mordPLayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!", mordPLayer->coins);
        }
        else if (mordPLayer->coins > 30) {
            printf("Coins after  creation: %d\n", mordPLayer->coins);
        }

    }

    else {
        printf("Cannot create Infantry at [%d][%d]!!!!\n", row, col);
    }
}

void placingInfantryM(mordorPlayer* mordPLayer) {
    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createInfantryMordor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Infantry at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createInfantryMordor com as novas coordenadas
    createInfantryMordor(baseRow, baseCol, mordPLayer);

    // Print the field after creating the base
    printField();
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
void createCavalryMordor(int row, int col, mordorPlayer* mordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ') && mordPlayer->coins >= 15)
    {
        field[row][col].symbol = CAVALARY_SYMB_M;
        mordPlayer->coins -= 15;
        showCoinsMordor(mordPlayer);
        printf("Cavalry created at [%d][%d]!\n", row, col);
        if (mordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!", mordPlayer->coins);
        }
        else if (mordPlayer->coins > 30) {
            printf("Coins after  creation: %d\n", mordPlayer->coins);
        }
    }
    else {
        printf("Cannot create Cavalry at [%d][%d]!!!!\n", row, col);
    }
}

void placingCavalryM(mordorPlayer* mordPLayer) {
    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createCavalryMordor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Cavalry at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createCavalryMordor com as novas coordenadas
    createCavalryMordor(baseRow, baseCol, mordPLayer);

    // Print the field after creating the base
    printField();
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
void createArtilleryMordor(int row, int col, mordorPlayer* mordPlayer) {
    if ((row >= 0 && row + 1 < ROWS && col >= 0 && col + 1 < COLS &&
        field[row][col].symbol == ' ' &&
        field[row][col + 1].symbol == ' ') && mordPlayer->coins >= 20)
    {
        field[row][col].symbol = ARTILLERY_SYMB_M;
        field[row][col+1].symbol = ARTILLERY_SYMB_M1;
        mordPlayer->coins -= 20;
        showCoinsMordor(mordPlayer);
        printf("Artillery created at [%d][%d]!\n", row, col);
        if (mordPlayer->coins <= 30) {
            printf("WARNING!!!! YOU ONLY HAVE %d REMAINING COINS!!!", mordPlayer->coins);
        }
        else if (mordPlayer->coins > 30) {
            printf("Coins after creation: %d\n", mordPlayer->coins);
        }
    }
    else {
        printf("Cannot create Artillery at [%d][%d]!!!!\n", row, col);
    }
}

void placingArtilleryM(mordorPlayer* mordPLayer) {
    int baseRow, baseCol;

    // Obtendo as coordenadas antes de chamar createArtilleryMordor
    getGridCords(&baseRow, &baseCol);
    printf("Creating the Artillery at [%d][%d]!!!!\n", baseRow, baseCol);

    // Chamando createArtilleryMordor com as novas coordenadas
    createArtilleryMordor(baseRow, baseCol, mordPLayer);

    // Print the field after creating the base
    printField();
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
void moveInfantryMordor(mordorPlayer* mordPlayer) {
    int sourceRow, destRow;
    char sourceCol[2], destCol[2];
    showCoinsMordor(mordPlayer);

    // Get source position
    printf("\nEnter the row where the Mordor Infantry is located: ");
    scanf_s("%d", &sourceRow, sizeof(sourceRow));
    printf("Enter the column where the Mordor Infantry is located (A-Z): ");
    scanf_s("%s", sourceCol, sizeof(sourceCol));

    // Get destination position
    printf("\nEnter the row to move the Mordor Infantry: ");
    scanf_s("%d", &destRow, sizeof(destRow));
    printf("Enter the column to move the Mordor Infantry (A-Z): ");
    scanf_s("%s", destCol, sizeof(destCol));

    // Convert column characters to uppercase for consistency
    sourceCol[0] = toupper(sourceCol[0]);
    destCol[0] = toupper(destCol[0]);

    // Convert column characters to 0-based index
    int sourceColumn = sourceCol[0] - 'A';
    int destColumn = destCol[0] - 'A';

    // Debug information
    printf("DEBUG: Moving Mordor Infantry from [%d][%s] to [%d][%s]\n", sourceRow, sourceCol, destRow, destCol);

    // Check if the source cell is out of bounds
    if (sourceRow < 0 || sourceRow >= ROWS || sourceColumn < 0 || sourceColumn >= COLS) {
        printf("\nDEBUG: Invalid source position for the Mordor Infantry.\n");
        return;
    }

    // Check if the source cell is occupied by 'O' or 'W'
    if (field[sourceRow][sourceColumn].symbol != INFANTARY_SYMB_M &&
        field[sourceRow][sourceColumn].symbol != INFANTARY_SYMB_M1) {
        printf("\nDEBUG: No Mordor Infantry found at the specified source position.\n");
        return;
    }

    // Check if the destination cells are within bounds
    if (destRow >= 0 && destRow < ROWS && destColumn >= 0 && destColumn + 1 < COLS) {
        // Check if the destination cells are empty
        if (field[destRow][destColumn].symbol == ' ' &&
            field[destRow][destColumn + 1].symbol == ' ') {

            // Calculate the distance moved by Mordor Infantr
            int cellsMoved = abs(destRow - sourceRow) + 1;  // Adding 1 to include the destination cell
            int totalCost = 2 * cellsMoved;  // Deduct 2 coins for each cell moved

            // Check if the player has enough coins for the movement
            if (mordPlayer->coins >= totalCost) {
                // Update the positions of Mordor Infantr
                field[destRow][destColumn].symbol = INFANTARY_SYMB_M;      // New position
                field[destRow][destColumn + 1].symbol = INFANTARY_SYMB_M1;  // New position
                field[sourceRow][sourceColumn].symbol = ' ';               // Clear the old position
                field[sourceRow][sourceColumn + 1].symbol = ' ';           // Clear the old position

                // Deduct coins from the player
                mordPlayer->coins -= totalCost;

                printf("\nDEBUG: Mordor Infantry moved successfully to the intended place.\n");
                printf("\nCoins before movement: %d\n", mordPlayer->coins + totalCost);  // Display coins before the movement
                printf("\nCoins after movement: %d\n", mordPlayer->coins);

                printField(field);  // Ensure to print the updated field
            }
            else {
                printf("\nDEBUG: Insufficient coins to move Mordor Infantry.\n");
            }

            return;
        }
        else {
            printf("\nDEBUG: Destination cells are occupied.\n");
        }
    }

    printf("\nDEBUG: Invalid destination position for Gondor Cavalry.\n");
}

/**
 *
 * \function name- moveCavalryMordor
 * \params- originRow
 * \params- originCol
 * \params- destRow
 * \params- destCol
 * \brief- Funcao que faz com que seja possivel mover uma unidade de infantaria
 *
 *
 */
void moveCavalryMordor(mordorPlayer* mordPlayer) {
    int sourceRow, destRow;
    char sourceCol[2], destCol[2];
    showCoinsMordor(mordPlayer);

    // Get source position
    printf("\nEnter the row where the Mordor Cavalry is located: ");
    scanf_s("%d", &sourceRow, sizeof(sourceRow));
    printf("Enter the column where the Mordor Cavalry is located (A-Z): ");
    scanf_s("%s", sourceCol, sizeof(sourceCol));

    // Get destination position
    printf("\nEnter the row to move the Mordor Cavalry: ");
    scanf_s("%d", &destRow, sizeof(destRow));
    printf("Enter the column to move the Mordor Cavalry (A-Z): ");
    scanf_s("%s", destCol, sizeof(destCol));

    // Convert column characters to uppercase for consistency
    sourceCol[0] = toupper(sourceCol[0]);
    destCol[0] = toupper(destCol[0]);

    // Convert column characters to 0-based index
    int sourceColumn = sourceCol[0] - 'A';
    int destColumn = destCol[0] - 'A';

    // Debug information
    printf("DEBUG: Moving Mordor Cavalry from [%d][%s] to [%d][%s]\n", sourceRow, sourceCol, destRow, destCol);

    // Check if the source cell is out of bounds
    if (sourceRow < 0 || sourceRow >= ROWS || sourceColumn < 0 || sourceColumn >= COLS) {
        printf("\nDEBUG: Invalid source position for the Mordor Cavalry.\n");
        return;
    }

    // Check if the source cell is occupied by 'W'
    if (field[sourceRow][sourceColumn].symbol != CAVALARY_SYMB_M) {
        printf("\nDEBUG: No Mordor Cavalry found at the specified source position.\n");
        return;
    }

    // Check if the destination cell is within bounds
    if (destRow >= 0 && destRow < ROWS && destColumn >= 0 && destColumn < COLS) {
        // Deduct 2 coins for each cell moved horizontally
        int cellsMoved = abs(destColumn - sourceColumn) + 1;  // Adding 1 to include the destination cell
        int totalCost = 2 * cellsMoved;

        // Check if the player has enough coins for the movement
        if (mordPlayer->coins >= totalCost) {
            // Update the positions of Mordor Cavalry
            field[destRow][destColumn].symbol = CAVALARY_SYMB_M;  // New position
            field[sourceRow][sourceColumn].symbol = ' ';  // Clear the old position

            // Deduct coins from the player
            mordPlayer->coins -= totalCost;

            printf("\nDEBUG: Mordor Cavalry moved successfully to the intended place.\n");
            printf("\nCoins before movement: %d\n", mordPlayer->coins + totalCost);  // Display coins before the movement
            printf("\nCoins after movement: %d\n", mordPlayer->coins);

            // Ensure to print the updated field
            printField(field);
        }
        else {
            printf("\nDEBUG: Insufficient coins to move Mordor Cavalry.\n");
            return;
        }
    }
    else {
        printf("\nDEBUG: Invalid destination position for Mordor Cavalry.\n");
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
void moveArtilleryMordor(mordorPlayer* mordPlayer) {
    int sourceRow, destRow;
    char sourceCol[2], destCol[2];
    showCoinsMordor(mordPlayer);

    // Get source position
    printf("\nEnter the row where the Mordor Artillery is located: ");
    scanf_s("%d", &sourceRow, sizeof(sourceRow));
    printf("Enter the column where the Mordor Artillery is located (A-Z): ");
    scanf_s("%s", sourceCol, sizeof(sourceCol));

    // Get destination position
    printf("\nEnter the row to move the Mordor Artillery: ");
    scanf_s("%d", &destRow, sizeof(destRow));
    printf("Enter the column to move the Mordor Artillery (A-Z): ");
    scanf_s("%s", destCol, sizeof(destCol));

    // Convert column characters to uppercase for consistency
    sourceCol[0] = toupper(sourceCol[0]);
    destCol[0] = toupper(destCol[0]);

    // Convert column characters to 0-based index
    int sourceColumn = sourceCol[0] - 'A';
    int destColumn = destCol[0] - 'A';

    // Debug information
    printf("DEBUG: Moving Mordor Artillery from [%d][%s] to [%d][%s]\n", sourceRow, sourceCol, destRow, destCol);

    // Check if the source cell is out of bounds
    if (sourceRow < 0 || sourceRow >= ROWS || sourceColumn < 0 || sourceColumn >= COLS) {
        printf("\nDEBUG: Invalid source position for the Mordor Artillery.\n");
        return;
    }

    // Check if the source cell is occupied by 'S' or 'T'
    if (field[sourceRow][sourceColumn].symbol != ARTILLERY_SYMB_M &&
        field[sourceRow][sourceColumn].symbol != ARTILLERY_SYMB_M1) {
        printf("\nDEBUG: No Mordor Artillery found at the specified source position.\n");
        return;
    }

    // Check if the destination cells are within bounds
    if (destRow >= 0 && destRow < ROWS && destColumn >= 0 && destColumn + 1 < COLS) {
        // Check if the destination cells are empty
        if (field[destRow][destColumn].symbol == ' ' &&
            field[destRow][destColumn + 1].symbol == ' ') {

            // Calculate the distance moved by Mordor Artillery
            int cellsMoved = abs(destRow - sourceRow) + 1;  // Adding 1 to include the destination cell
            int totalCost = 2 * cellsMoved;  // Deduct 2 coins for each cell moved

            // Check if the player has enough coins for the movement
            if (mordPlayer->coins >= totalCost) {
                // Update the positions of Mordor Artillery
                field[destRow][destColumn].symbol = ARTILLERY_SYMB_M;      // New position
                field[destRow][destColumn + 1].symbol = ARTILLERY_SYMB_M1;  // New position
                field[sourceRow][sourceColumn].symbol = ' ';               // Clear the old position
                field[sourceRow][sourceColumn + 1].symbol = ' ';           // Clear the old position

                // Deduct coins from the player
                mordPlayer->coins -= totalCost;

                printf("\nDEBUG: Mordor Artillery moved successfully to the intended place.\n");
                printf("\nCoins before movement: %d\n", mordPlayer->coins + totalCost);  // Display coins before the movement
                printf("\nCoins after movement: %d\n", mordPlayer->coins);

                printField(field);  // Ensure to print the updated field
            }
            else {
                printf("\nDEBUG: Insufficient coins to move Mordor Artillery.\n");
            }

            return;
        }
        else {
            printf("\nDEBUG: Destination cells are occupied.\n");
        }
    }

    printf("\nDEBUG: Invalid destination position for Gondor Artillery.\n");
}

#pragma endregion

    #pragma region ATTACK
    //Funcoes para atacar a partir das unidades de mordor

    #pragma region Mordor units vs Gondor Base

    void MordorInfantryVSGondBase(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR INFANTRY\n");
        printf("Select the row where mordor infantry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor infantry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor base is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor base is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_M)
            {
                if ((field[row][col].symbol == BASE_SYMB_G) && (field[row][col + 1].symbol == BASE_SYMB_G1) &&
                    (field[row][col + 2].symbol == BASE_SYMB_G2) && (field[row][col - 1].symbol == BASE_SYMB_G3))
                {
                    gordPlayer->gBaseHealth -= 5; //dano que a infantaria vai dar ao atacar a base
                    printf("Gondor base health after attack: %d\n ", gordPlayer->gBaseHealth);

                    if (gordPlayer->gBaseHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' ') &&
                            (field[row][col + 2].symbol = ' ') && (field[row][col - 1].symbol = ' '));
                        printf("Gondor base was destroyed!\n");
                        printf("You won the game!!!\n");
                        printf("The middle-earth era is ours!!\n");
                    }
                }
                else {
                    printf("Gondor base not found!!\n");
                }

            }     

        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorCavalryVSGondBase(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR CAVALRY\n");
        printf("Select the row where mordor cavalry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor cavalry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor base is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor base is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_M)
            {
                if ((field[row][col].symbol == BASE_SYMB_G) && (field[row][col + 1].symbol == BASE_SYMB_G1) &&
                    (field[row][col + 2].symbol == BASE_SYMB_G2) && (field[row][col - 1].symbol == BASE_SYMB_G3))
                {
                    gordPlayer->gBaseHealth -= 7; //dano que a cavalaria vai dar ao atacar a base
                    printf("Gondor base health after attack: %d\n ", gordPlayer->gBaseHealth);

                    if (gordPlayer->gBaseHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' ') &&
                            (field[row][col + 2].symbol = ' ') && (field[row][col - 1].symbol = ' '));
                        printf("Gondor base was destroyed!\n");
                        printf("You won the game!!!\n");
                        printf("The middle-earth era is ours!!\n");
                    }


                }
                else {
                    printf("Gondor base not found!!\n");
                }

            }        

        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorArtilleryVSGondBase(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR ARTILLERY\n");
        printf("Select the row where mordor artillery is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor artillery is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor base is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor base is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_M) 
            {
                if ((field[row][col].symbol == BASE_SYMB_G) && (field[row][col + 1].symbol == BASE_SYMB_G1) &&
                    (field[row][col + 2].symbol == BASE_SYMB_G2) && (field[row][col - 1].symbol == BASE_SYMB_G3))
                {
                    gordPlayer->gBaseHealth -= 10; //dano que a cavalaria vai dar ao atacar a base
                    printf("Gondor base health after attack: %d\n ", gordPlayer->gBaseHealth);

                    if (gordPlayer->gBaseHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' ') &&
                            (field[row][col + 2].symbol = ' ') && (field[row][col - 1].symbol = ' '));
                        printf("Gondor base was destroyed!\n");
                        printf("You won the game!!!\n");
                        printf("The middle-earth era is ours!!\n");
                    }
                }
                else {
                    printf("Gondor base not found!!\n");
                }

            }
           

        }
        else {
            printf("Invalid position!!\n");
        }

    }

    #pragma endregion

    #pragma region Mordor Units vs Gondor Mine

    void MordorInfantryVSGondMine(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR INFANTRY\n");
        printf("Select the row where mordor infantry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor infantry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor mine is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor mine is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_M) 
            {
                if ((field[row][col].symbol == MINE_SYMB_G) && (field[row][col + 1].symbol == MINE_SYMB_G1))
                {

                    gordPlayer->gMineHealth -= 5; //dano que a infantaria vai dar ao atacar a mina
                    printf("Gondor mine health after attack: %d\n ", gordPlayer->gMineHealth);

                    if (gordPlayer->gMineHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Gondor mine was destroyed!\n");
                    }

                }
                else {
                    printf("Gondor mine not found!!\n");
                }


            }
         
        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorCavalryVSGondMine(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR CAVALRY\n");
        printf("Select the row where mordor cavalry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor cavalry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor mine is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor mine is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if(field[rowAtack][colAtack].symbol == CAVALARY_SYMB_M)
            {
                if ((field[row][col].symbol == MINE_SYMB_G) && (field[row][col + 1].symbol == MINE_SYMB_G1))
                {

                    gordPlayer->gMineHealth -= 7; //dano que a cavalaria vai dar ao atacar a mina
                    printf("Gondor mine health after attack: %d\n ", gordPlayer->gMineHealth);

                    if (gordPlayer->gMineHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Gondor mine was destroyed!\n");
                    }


                }
                else {
                    printf("Gondor mine not found!!\n");
                }


            }
            
        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorArtilleryVSGondMine(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR ARTILLERY\n");
        printf("Select the row where mordor artillery is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor artillery is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor mine is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor mine is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_M)
            {
                if ((field[row][col].symbol == MINE_SYMB_G) && (field[row][col + 1].symbol == MINE_SYMB_G1))
                {

                    gordPlayer->gMineHealth -= 10; //dano que a artilharia vai dar ao atacar a mina
                    printf("Gondor mine health after attack: %d\n ", gordPlayer->gMineHealth);

                    if (gordPlayer->gMineHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Gondor mine was destroyed!\n");
                    }

                }
                else {
                    printf("Gondor mine not found!!\n");
                }

            }
           
        }
        else {
            printf("Invalid position!!\n");
        }
    }

    #pragma endregion

    #pragma region Mordor Units vs Gondor Barrack

    void MordorInfantrVSGondBarrack(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR INFANTRY\n");
        printf("Select the row where mordor infantry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor infantry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor barrack is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor barrack is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_M)
            {
                if ((field[row][col].symbol == BARRACK_SYMB_G) && (field[row][col + 1].symbol == BARRACK_SYMB_G1))
                {

                    gordPlayer->gBarrackHealth -= 5; //dano que a infantaria vai dar ao atacar a barrack
                    printf("Mordor barrack health after attack: %d\n ", gordPlayer->gBarrackHealth);

                    if (gordPlayer->gBarrackHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Gondor barrack was destroyed!\n");
                    }
                }
                else {
                    printf("Gondor barrack not found!!\n");
                }

            }
           

        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorCavalryVSGondBarrack(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR CAVALRY\n");
        printf("Select the row where mordor cavalry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor cavalry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor barrack is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor barrack is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_M)
            {
                if ((field[row][col].symbol == BARRACK_SYMB_G) && (field[row][col + 1].symbol == BARRACK_SYMB_G1))
                {

                    gordPlayer->gBarrackHealth -= 7; //dano que a cavalaria vai dar ao atacar a barrack
                    printf("Mordor barrack health after attack: %d\n ", gordPlayer->gBarrackHealth);

                    if (gordPlayer->gBarrackHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Gondor barrack was destroyed!\n");
                    }
                }
                else {
                    printf("Gondor barrack not found!!\n");
                }

            }
            
        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorArtilleryVSGondBarrack(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR ARTILLERY\n");
        printf("Select the row where mordor artillery is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor artillery is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor barrack is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor barrack is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_M)
            {
                if ((field[row][col].symbol == BARRACK_SYMB_G) && (field[row][col + 1].symbol == BARRACK_SYMB_G1))
                {

                    gordPlayer->gBarrackHealth -= 10; //dano que a cavalaria vai dar ao atacar a barrack
                    printf("Mordor barrack health after attack: %d\n ", gordPlayer->gBarrackHealth);

                    if (gordPlayer->gBarrackHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Gondor barrack was destroyed!\n");
                    }
                }
                else {
                    printf("Gondor barrack not found!!\n");
                }
            }
          
        }
        else {
            printf("Invalid position!!\n");
        }

    }


    #pragma endregion

    #pragma region Mordor Units vs Gondor Stable

    void MordorInfantrVSGondStable(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR INFANTRY\n");
        printf("Select the row where mordor infantry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor infantry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor stable is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor stable is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_M)
            {
                if ((field[row][col].symbol == STABLES_SYMB_G) && (field[row][col + 1].symbol == STABLES_SYMB_G1))
                {

                    gordPlayer->gStableHealth -= 5; //dano que a infantaria vai dar ao atacar a stable
                    printf("Mordor stable health after attack: %d\n ", mordPlayer->mStableHealth);

                    if (mordPlayer->mStableHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Mordor stable was destroyed!\n");
                    }


                }
                else {
                    printf("Mordor stable not found!!\n");
                }

            }
            
        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorCavalryVSGondStable(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH GONDOR CAVALRY\n");
        printf("Select the row where mordor cavalry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor cavalry is positioned: \n");
        scanf_s("%d", &colPosition);


        printf("Select the row where mordor stable is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where mordor stable is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_M) 
            {
                if ((field[row][col].symbol == STABLES_SYMB_M) && (field[row][col + 1].symbol == STABLES_SYMB_M1))
                {

                    mordPlayer->mStableHealth -= 7; //dano que a cavalaria vai dar ao atacar a stable
                    printf("Mordor stable health after attack: %d\n ", mordPlayer->mStableHealth);

                    if (mordPlayer->mStableHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Mordor stable was destroyed!\n");
                    }

                }
                else {
                    printf("Mordor stable not found!!\n");
                }

            }   

        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorArtilleryVSGondStable(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH GONDOR CAVALRY\n");
        printf("Select the row where mordor artillery is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor artillery is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where mordor stable is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where mordor stable is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)       
        {
            if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_M) 
            {
                if ((field[row][col].symbol == STABLES_SYMB_M) && (field[row][col + 1].symbol == STABLES_SYMB_M1))
                {

                    mordPlayer->mStableHealth -= 10; //dano que a artilharia vai dar ao atacar a stable
                    printf("Mordor stable health after attack: %d\n ", mordPlayer->mStableHealth);

                    if (mordPlayer->mStableHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Mordor stable was destroyed!\n");
                    }


                }
                else {
                    printf("Mordor stable not found!!\n");
                }

            }
           

        }
        else {
            printf("Invalid position!!\n");
        }

    }

    #pragma endregion

    #pragma region Mordor Units vs Gondor Armoury

    void MordorInfantrVSGondArmoury(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR INFANTRY\n");
        printf("Select the row where mordor infantry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor infantry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor armoury is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor armoury is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_M) 
            {
                if ((field[row][col].symbol == ARMOURY_SYMB_G) && (field[row][col + 1].symbol == ARMOURY_SYMB_G1))
                {

                    gordPlayer->gArmouryHealth -= 5; //dano que a infantaria vai dar ao atacar a armoury
                    printf("Gondor armoury health after attack: %d\n ", gordPlayer->gArmouryHealth);

                    if (gordPlayer->gArmouryHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Gondor armoury was destroyed!\n");
                    }


                }
                else {
                    printf("Gondor armoury not found!!\n");
                }
            }

        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorCavalryVSGondArmoury(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR CAVALRY\n");
        printf("Select the row where mordor cavalry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor cavalry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor armoury is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor armoury is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_M)
            {
                if ((field[row][col].symbol == ARMOURY_SYMB_G) && (field[row][col + 1].symbol == ARMOURY_SYMB_G1))
                {

                    gordPlayer->gArmouryHealth -= 7; //dano que a cavalaria vai dar ao atacar a armoury
                    printf("Gondor armoury health after attack: %d\n ", gordPlayer->gArmouryHealth);

                    if (gordPlayer->gArmouryHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Gondor armoury was destroyed!\n");
                    }


                }
                else {
                    printf("Gondor armoury not found!!\n");
                }

            }
            
        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorArtilleryVSGondArmoury(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR ARTILLERY\n");
        printf("Select the row where mordor artillery is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor artillery is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor armoury is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor armoury is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_M)
            {
                if ((field[row][col].symbol == ARMOURY_SYMB_G) && (field[row][col + 1].symbol == ARMOURY_SYMB_G1))
                {

                    gordPlayer->gArmouryHealth -= 10; //dano que a artilharia vai dar ao atacar a armoury
                    printf("Gondor armoury health after attack: %d\n ", gordPlayer->gArmouryHealth);

                    if (gordPlayer->gArmouryHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Gondor armoury was destroyed!\n");
                    }

                }
                else {
                    printf("Gondor armoury not found!!\n");
                }
            }
            

        }
        else {
            printf("Invalid position!!\n");
        }

    }

    #pragma endregion


    #pragma region Mordor Units vs Gondor Infantry

    void MordorInfantrVSGondInfantry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR INFANTRY\n");
        printf("Select the row where mordor infantry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor infantry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor infantry is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor infantry is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_M)
            {
                if ((field[row][col].symbol == INFANTARY_SYMB_G))
                {
                    gordPlayer->infantryHealth -= 5; //dano que a infantaria Mordor vai dar ao atacar a infantaria Gondor
                    printf("Mordor infantry health after attack: %d\n ", gordPlayer->infantryHealth);

                    if (gordPlayer->infantryHealth <= 0) {
                        (field[row][col].symbol = ' ');
                        printf("Gondor infantry was destroyed!\n");
                    }
                }
                else {
                    printf("Gondor infantry not found!!\n");
                }
            }
            
        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorCavalryVSGondInfantry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR CAVALRY\n");
        printf("Select the row where mordor cavalry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor cavalry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor infantry is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor infantry is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_M)
            {
                if ((field[row][col].symbol == INFANTARY_SYMB_G))
                {
                    gordPlayer->infantryHealth -= 7; //dano que a cavalaria Mordor vai dar ao atacar a infantaria Gondor
                    printf("Mordor infantry health after attack: %d\n ", gordPlayer->infantryHealth);

                    if (gordPlayer->infantryHealth <= 0) {
                        (field[row][col].symbol = ' ');
                        printf("Gondor infantry was destroyed!\n");
                    }
                }
                else {
                    printf("Gondor infantry not found!!\n");
                }
            }
            }
           
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorArtilleryVSGondInfantry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR ARTILLERY\n");
        printf("Select the row where mordor artillery is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor artillery is positioned: \n");
        scanf_s("%d", &colPosition);


        printf("Select the row where gondor infantry is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor infantry is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_M)
            {
                if ((field[row][col].symbol == INFANTARY_SYMB_G))
                {

                    gordPlayer->infantryHealth -= 10; //dano que a artilharia Mordor vai dar ao atacar a infantaria Gondor
                    printf("Mordor infantry health after attack: %d\n ", gordPlayer->infantryHealth);

                    if (gordPlayer->infantryHealth <= 0) {
                        (field[row][col].symbol = ' ');
                        printf("Gondor infantry was destroyed!\n");
                    }
                }
                else {
                    printf("Gondor infantry not found!!\n");
                }
            }
            
        }
        else {
            printf("Invalid position!!\n");
        }

    }

    #pragma endregion

    #pragma region Mordor Units vs Gondor Cavalry

    void MordInfantryVSGondCavalry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR INFANTRY\n");
        printf("Select the row where mordor infantry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor infantry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor cavalry is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor cavalry is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == INFANTARY_SYMB_M)
            {
                if ((field[row][col].symbol == CAVALARY_SYMB_G) && (field[row][col + 1].symbol == CAVALARY_SYMB_G1))
                {
                    gordPlayer->cavalryHealth -= 5;
                    printf("Gondor cavalry health after attack: %d\n ", gordPlayer->cavalryHealth);

                    if (gordPlayer->cavalryHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Gondor cavalry was destroyed!\n");
                    }
                }
                else {
                    printf("Gondor cavalry not found!!\n");
                }

            }         

        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordCavalryVSGondCavalry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer *mordPlayer)
{
        int r, c, r1, c1;

    printf("\nInsert the row to where is the Mordor Cavalry: ");
    scanf_s("%d", &r1);
    printf("\nInsert the column where is the Mordor Cavalry: ");
    scanf_s("%d", &c1);


    printf("\nInsert the row to where is the Gondor Cavalry: ");
    scanf_s("%d", &r);
    printf("\nInsert the column where is the Gondor Cavalry: ");
    scanf_s("%d", &c);

    row = r;
    col = c;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && r1 >= 0 && r1 < ROWS && c1 >= 0 && c1 < COLS) {


        if (field[r1][c1].symbol == 'W') {

            if ((r - 1 >= 0 && field[r - 1][c].symbol == 'W') ||
                (r + 1 < ROWS && field[r + 1][c].symbol == 'W') ||
                (c - 1 >= 0 && field[r][c - 1].symbol == 'W') ||
                (c + 1 < COLS && field[r][c + 1].symbol == 'W')) 
            {
               
                    gordPlayer->cavalryHealth -= 7;

                    printf("\nMordor Cavalry attacked Gondor Cavalry! Gondor Cavalry health: %d\n", gordPlayer->cavalryHealth);

                    if (gordPlayer->cavalryHealth <= 0) {

                        for (int i = 0; i < 2; ++i) {
                            field[r][c + i].symbol = ' ';
                        }

                        printf("\nGondor Cavalry has been eliminated!\n");
                    }                    
            }
            else {
                printf("\nNo Gondor Cavalry found adjacent to Mordor Cavalry.\n");
            }
        }
        else {
            printf("\nNo Mordor Cavalry found at the specified position.\n");
        }
    }
    else {
        printf("\nInvalid position for Mordor Cavalry attack.\n");
    }
    return mordorMovesBattle();
}

    void MordArtilleryVSGondCavalry(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR ARTILLERY\n");
        printf("Select the row where mordor artillery is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor artillery is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor cavalry is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor cavalry is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_M)
            {
                if ((field[row][col].symbol == CAVALARY_SYMB_G) && (field[row][col + 1].symbol == CAVALARY_SYMB_G1))
                {
                    gordPlayer->cavalryHealth -= 10;
                    printf("Gondor cavalry health after attack: %d\n ", gordPlayer->cavalryHealth);

                    if (gordPlayer->cavalryHealth <= 0) {
                        ((field[row][col].symbol = ' ') && (field[row][col + 1].symbol = ' '));
                        printf("Gondor cavalry was destroyed!\n");
                    }
                }
                else {
                    printf("Gondor cavalry not found!!\n");
                }

            }
          
        }
        else {
            printf("Invalid position!!\n");
        }

    }

    #pragma endregion

    #pragma region Mordor Units vs Gondor Artillery

    void MordorInfantryVSGondArtillhery(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR INFANTRY\n");
        printf("Select the row where mordor infantry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor infantry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor artillery is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor artillery is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if(field[rowAtack][colAtack].symbol == INFANTARY_SYMB_M)
            {
                if (field[row][col].symbol == ARTILLERY_SYMB_G)
                {

                    gordPlayer->artilleryHealth -= 5;
                    printf("Gondor artillery health after attack: %d\n ", gordPlayer->artilleryHealth);

                    if (gordPlayer->artilleryHealth <= 0) {
                        (field[row][col].symbol = ' ');
                        printf("Gondor artillery was destroyed!\n");
                    }
                }
                else {
                    printf("Gondor artillery not found!!\n");
                }
            }
           
        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorCavalryVSGondArtillhery(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR CAVALRY\n");
        printf("Select the row where mordor cavalry is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor cavalry is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor artillery is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor artillery is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if (field[rowAtack][colAtack].symbol == CAVALARY_SYMB_M)
            {
                if (field[row][col].symbol == ARTILLERY_SYMB_G)
                {

                    gordPlayer->artilleryHealth -= 7;
                    printf("Gondor artillery health after attack: %d\n ", gordPlayer->artilleryHealth);

                    if (gordPlayer->artilleryHealth <= 0) {
                        (field[row][col].symbol = ' ');
                        printf("Gondor artillery was destroyed!\n");
                    }
                }
                else {
                    printf("Gondor artillery not found!!\n");
                }
            }
        }
        else {
            printf("Invalid position!!\n");
        }

    }

    void MordorArtilleryVSGondArtillhery(int row, int col, gordorPlayer* gordPlayer, mordorPlayer* mordPlayer)
    {
        int rowAtack, colAtack;
        int rowPosition, colPosition;

        printf("ATTACKING WITH MORDOR ARTILLERY\n");
        printf("Select the row where mordor artillery is positioned: \n");
        scanf_s("%d", &rowPosition);
        printf("Select the column where mordor artillery is positioned: \n");
        scanf_s("%d", &colPosition);

        printf("Select the row where gondor artillery is positioned: \n");
        scanf_s("%d", &rowAtack);
        printf("Select the column where gondor artillery is positioned: \n");
        scanf_s("%d", &colAtack);

        row = rowAtack;
        col = colAtack;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rowPosition >= 0 && rowPosition < ROWS && colPosition >= 0 && colPosition < COLS)
        {
            if(field[rowAtack][colAtack].symbol == ARTILLERY_SYMB_M)
            {
                if (field[row][col].symbol == ARTILLERY_SYMB_G)
                {

                    gordPlayer->artilleryHealth -= 10;
                    printf("Gondor artillery health after attack: %d\n ", gordPlayer->artilleryHealth);

                    if (gordPlayer->artilleryHealth <= 0) {
                        (field[row][col].symbol = ' ');
                        printf("Gondor artillery was destroyed!\n");
                    }
                }
                else {
                    printf("Gondor artillery not found!!\n");
                }
            }
            
        }
        else {
            printf("Invalid position!!\n");
        }

    }
    #pragma endregion

    #pragma endregion



#pragma endregion

#pragma region funcoes Gravar ficheiro
void save(const char* filename,gordorPlayer* gordPlayer, mordorPlayer * mordPlayer) {
    FILE* arquivo = fopen(filename, "w");  

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return;
    }
    // Write player details to the file
    fprintf(arquivo, "Gondor Coins: %d\n", gordPlayer->coins);
    fprintf(arquivo, "Base : %d | Mine: %d | Barrack: %d | Stable: %d | Armoury: %d\n", gordPlayer->gBaseHealth, gordPlayer->gMineHealth, gordPlayer->gBarrackHealth,
        gordPlayer->gStableHealth, gordPlayer->gArmouryHealth);
    fprintf(arquivo, "Infantry: %d | Cavalry: %d | Artillery: %d\n", gordPlayer->infantryHealth, gordPlayer->cavalryHealth, gordPlayer->artilleryHealth);

    fprintf(arquivo, "Mordor Coins: %d\n", mordPlayer->coins);
    fprintf(arquivo, "Base : %d | Mine: %d | Barrack: %d | Stable: %d | Armoury: %d\n", mordPlayer->mBaseHealth, mordPlayer->mMineHealth, mordPlayer->mBarrackHealth,
        mordPlayer->mStableHealth, mordPlayer->mArmouryHealth);
    fprintf(arquivo, "Infantry: %d | Cavalry: %d | Artillery: %d\n", mordPlayer->infantryHealth, mordPlayer->cavalryHealth, mordPlayer->artilleryHealth);

    // Write unit movement details to the file
    //fprintf(arquivo, "Moved %c %d cells from (%d, %d) to (%d, %d).\n", unitType, cells, originRow, originCol, destRow, destCol);

    // Write remaining coins to the file
    fprintf(arquivo, "Remaining coins gondor: %d\n", gordPlayer->coins);
    fprintf(arquivo, "Remaining coins mordor: %d\n", mordPlayer->coins);

    //Save battle field
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            fprintf(arquivo, "%c ", field[i][j].symbol);
        }
        fprintf(arquivo, "\n");
    }

    // Close the file
    fclose(arquivo);
}

void load(const char* filename, gordorPlayer* gordPlayer, mordorPlayer *mordPlayer)
{
    FILE* arquivo = fopen(filename, "r");
    
    if (arquivo == NULL) {
        perror("Error opening file for reading!!\n");
        return;
    }

    char buffer[256];

    if (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        sscanf_s(buffer, "Gondor Base : %d | Mine: %d | Barrack: %d | Stable: %d | Armoury: %d", &gordPlayer->gBaseHealth, &gordPlayer->gMineHealth, &gordPlayer->gBarrackHealth,
            &gordPlayer->gStableHealth, &gordPlayer->gArmouryHealth);
        sscanf_s(buffer, "Infantry: %d | Cavalry: %d | Artillery: %d\n", &gordPlayer->infantryHealth, &gordPlayer->cavalryHealth, &gordPlayer->artilleryHealth);

        sscanf_s(buffer, "Mordor Base : %d | Mine: %d | Barrack: %d | Stable: %d | Armoury: %d", &mordPlayer->mBaseHealth, &mordPlayer->mMineHealth, &mordPlayer->mBarrackHealth,
            &mordPlayer->mStableHealth, &mordPlayer->mArmouryHealth);
        sscanf_s(buffer, "Infantry: %d | Cavalry: %d | Artillery: %d\n", &mordPlayer->infantryHealth, &mordPlayer->cavalryHealth, &mordPlayer->artilleryHealth);
    }

    //Read battle field
    for (int i = 0; i < ROWS; ++i) {
        if (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
            for (int j = 0; j < COLS; ++j) {
                sscanf_s(buffer + (2 * j), "%c", &field[i][j].symbol, sizeof(field[i][j].symbol));
            }
        }
    }
        fclose(arquivo);

        printf("Load game from : %s", arquivo);
        printField();


}





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