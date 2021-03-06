#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../Headers/Fuzzy.h"
#include "../Headers/Functions.h"

#define max(a,b) (a>=b?a:b)

float AutoBench(int taille, int NbPointsA, int NbPointsB)
{
	// Initialisation compteurs
	int i,j;

	// Instanciation variables temporaires
	clock_t time;
	float Min, Max;
	float Centroide;
	float Q = 0.0;

	// Entrées de la fonction
	float A_Min = 0.0;
	float B_Min = 0.0; 
	float A_Max = 1.0;
	float B_Max = 1.0;
	float Q_A = (A_Max - A_Min)/NbPointsA;
	float Q_B = (B_Max - B_Min)/NbPointsB;
	
		// Création de toutes les matrices dynamiquement
	//MF_X
	float** MF_X = NULL;
	MF_X = malloc(sizeof(float*)*taille);
  for(i = 0; i<taille; i++)
  	MF_X[i] = malloc(sizeof(float)*3);
	
	//regle
	int** regle = NULL;
	regle = malloc(sizeof(int*)*taille);
	for(i = 0; i<taille; i++)
		regle[i] = malloc(sizeof(int)*taille);

		// Remplissage de ces matrices avec les valeurs récuperées de l'utilisateur
	//MF_X
	Q = (float)1/(taille-1);
	
	MF_X[0][0] = 0;
	MF_X[0][1] = 0;
	MF_X[0][2] = Q;
	for(i = 1; i<taille-1; i++)
	{
		MF_X[i][0] = (i-1)*Q;	
		MF_X[i][1] = (i)*Q;	
		MF_X[i][2] = (i+1)*Q;	
	}
	MF_X[taille -1][0] = (taille -2)*Q;
	MF_X[taille -1][1] = 1;
	MF_X[taille -1][2] = 1;

	//regle
	for(i = 0; i<taille; i++)
	{
		for(j = 0; j<taille; j++)
		{
			regle[i][j] = max(i,j);	
		}
	}

	time = clock();

	// On calcule Min et Max pour la normalisation
	NormalValues(taille, MF_X, &Min, &Max); 

	// On boucle et on écrit dans le fichier pour ensuite afficher les points
	for (i=0; i<NbPointsA; i++)
	{
		for (j=0; j<NbPointsB; j++)
		{
				Centroide = Fuzzy(regle, taille, MF_X, (A_Min + Q_A*i), (B_Min + Q_B*j), "Min", "Max");
			// On normalise
			Centroide = Normalisation(Centroide, Min, Max);
		}
	}
	
	time = clock() - time;

	for(i=0; i<taille; i++)
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

	return (float)time;
}
