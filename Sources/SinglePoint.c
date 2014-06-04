//---------------------------------------------------------------------------//
// Fichier      : SinglePoint.c                                       	     //
// Auteur 	: LEMAIRE Martin                                             //
// Description	: Main qui recoit matrice de règle, Mfs, Nbr de Mfs, valeur  //
//                de deux entrées et calcul la sortie en appelant les        //
//                fcontions necessaires.				     //
//---------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../Headers/Fuzzy.h"
#include "../Headers/Functions.h"

#define TAILLE 3

int main()
{
	// Entrées de la fonction
	int regle_IN[TAILLE][TAILLE] = { { 0, 0, 1} , { 0, 1, 2} , { 1, 2, 2} };
	float MF_X_IN[TAILLE][3] = { {0 ,0 , 0.5 } , { 0 , 0.5 , 1 } , {0.5 , 1 , 1} };
	float A_norm = 0.0;
	float B_norm = 0.0;
	
	// Initialisation des variables
	
		// Compteurs
	int i = 0;
	int j =0;
		
		// Variable a modifier
	int MF_Min[4] = {-1, -1, -1,-1 };
	float Y_Min[4] = {-1, -1, -1, -1};
	int N_Min = 0; 
	
	float Y_Max[14] = {0};
	float X_Max[14] = {0};
	int N_Max = 0;	

	float Centroide = 0.0;

	float Min = 0;
	float Max = 0;

		// Variables de test
	int test_min = 0;
	int test_max = 0;	
	
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

	// On appele la fonction Fuzzy
	Centroide = Fuzzy(regle, TAILLE, MF_X, A_norm, B_norm, "Min", "Max");

	printf("Centroide = %f\n", Centroide); 

	// On normalise les valeurs
		// On calcule le min et le max
	NormalValues(TAILLE, MF_X, &Min, &Max);
	
		// On normalise la valeur
	Centroide = Normalisation(Centroide, Min, Max);

	printf("Centroide Normalisé = %f\n", Centroide);

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
