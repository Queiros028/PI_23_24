/*****************************************************************//**
 * \file   Header.h
 * 
 * \author Eduardo Queir�s, Jo�o Lima, Lu�s Gon�alves
 * \date   November 2023
 *********************************************************************/
#include<stdio.h>
#include <string.h>
#pragma warning(disable: 4996)

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
