/*****************************************************************//**
 * \file   funcoes.c
 * 
 * \author Eduardo Queirós, João Lima, Luís Gonçalves
 * \date   November 2023
 *********************************************************************/
#include <stdio.h>
#include "Header.h"
#pragma warning(disable: 4996)

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