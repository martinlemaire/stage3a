#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../Headers/Fuzzy.h"
#include "../Headers/Surface.h"
#include "../Headers/Functions.h"

#define TAILLE 3

//#define DEBUG

int main()
{
	// Initialisation compteurs
	int i,j;
	
	// Entrées de la fonction
	int regle_IN[TAILLE][TAILLE] = { { 0, 0, 0} , { 0, 1, 1} , {0, 1, 2} };
	float MF_X_IN[TAILLE][3] = { {0 ,0 , 0.5 } , { 0 , 0.5 , 1 } , {0.5 , 1 , 1} };
	
		// Création de toutes les matrices dynamiquement
	//MF_X
	float** MF_X = NULL;
	MF_X = malloc(sizeof(float*)*TAILLE);
  for(i = 0; i<TAILLE; i++)
  	MF_X[i] = malloc(sizeof(float)*3);
	
	//regle
	int** regle = NULL;
	regle = malloc(sizeof(int*)*TAILLE);
	for(i = 0; i<TAILLE; i++)
		regle[i] = malloc(sizeof(int)*TAILLE);

		// Remplissage de ces matrices avec les valeurs récuperées de l'utilisateur
	//MF_X
	for(i = 0; i<TAILLE; i++)
	{
		for(j = 0; j<3; j++)
		{
			MF_X[i][j] = MF_X_IN[i][j];	
		}
	}

	//regle
	for(i = 0; i<TAILLE; i++)
	{
		for(j = 0; j<TAILLE; j++)
		{
			regle[i][j] = regle_IN[i][j];	
		}
	}


	Surface(TAILLE, MF_X, regle, 0.0, 1.0, 0.0, 1.0, "Min", "Max", 100, 100);


	// On libere la mémoire allouée
	for(i=0; i<TAILLE; i++)
	{
		free(MF_X[i]);
		MF_X[i] = NULL;
		free(regle[i]);
		regle[i] = NULL;
	}

	free(MF_X);
	MF_X = NULL;

	free(regle);
	regle = NULL;

	return 0;
}
