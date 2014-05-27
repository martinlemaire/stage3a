#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Fuzzy.h"
#include "Functions.h"

#define TAILLE 3

int main()
{
	// Initialisation compteurs
	int i,j;

	// Instanciation variables temporaires
	clock_t time;
	float Min, Max;
	float Centroide;

	// Entrées de la fonction
	int regle_IN[TAILLE][TAILLE] = { { 0, 0, 1} , { 0, 1, 2} , { 1, 2, 2} };
	float MF_X_IN[TAILLE][3] = { {0 ,0 , 0.5 } , { 0 , 0.5 , 1 } , {0.5 , 1 , 1} };
	int NbPointsA = 1000;
	int NbPointsB = 1000;
	float A_Min = 0.0;
	float B_Min = 0.0; 
	float A_Max = 1.0;
	float B_Max = 1.0;
	float Q_A = (A_Max - A_Min)/NbPointsA;
	float Q_B = (B_Max - B_Min)/NbPointsB;
	
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

	time = clock();

	// On calcule Min et Max pour la normalisation
	NormalValues(TAILLE, MF_X, &Min, &Max); 

	// On boucle et on écrit dans le fichier pour ensuite afficher les points
	for (i=0; i<NbPointsA; i++)
	{
		for (j=0; j<NbPointsB; j++)
		{
				Centroide = Fuzzy(regle, TAILLE, MF_X, (A_Min + Q_A*i), (B_Min + Q_B*j), "Min", "Max");
			// On normalise
			Centroide = Normalisation(Centroide, Min, Max);
		}
	}
	
	time = clock() - time;

	printf("Le programme a pris %d ticks (%f secondes) pour calculer %i points\nCela fait un temps moyen pour un point de %f ticks (%.12fsecondes)\n\n", (int)time, ((float)time)/CLOCKS_PER_SEC, NbPointsA*NbPointsB, (float)time / (NbPointsA*NbPointsB), (((float)time)/CLOCKS_PER_SEC)/ (NbPointsA*NbPointsB));

	return 0;
}
