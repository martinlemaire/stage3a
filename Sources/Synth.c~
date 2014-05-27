#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"

float Synth(int* regle, int TAILLE, float** MF_X, float A_norm, char* And, char* Or)
{

	// Initialisation des variables utilisées dans le main
		
		// Compteurs
	int i = 0;
	int j = 0;

		// Variables d'échanges entre fonctions
	int MF_And[4] = {-1, -1, -1, -1};
	float Y_And[4] = {-1, -1, -1, -1};
	int N_And = 0;

	float Y_Or[14] = {0};
	float X_Or[14] = {0};
	int N_Or = 0;

	float Centroide = 0.0;

		// Variables de test
	int test_And;
	int test_Or; 

	// On appele la fonction choisie pour le And pour commencer
	if ( strcmp(And, "Min") == 0)
		test_And = SynthMin(TAILLE, regle, A_norm, MF_X, MF_And, Y_And, &N_And);
	//else if ( strcmp(And, "Product") == 0)
		//test_And = ProdFun(TAILLE, regle, A_norm, B_norm, MF_X, MF_And, Y_And, &N_And);
	else 
		return -2; // TO DO : définir les valeurs de sorties suivant les erreurs
	
	if (test_And != 0)
		return -1;
	
	// Ensuite, on appele la fonction pour le Or
	if ( strcmp(Or, "Max") == 0)
		test_Or = MaxFun(TAILLE, MF_X, MF_And, Y_And, N_And, X_Or, Y_Or, &N_Or);
	else if ( strcmp(Or, "ProbSum") == 0)
		i = 1;// à écrire
	else 
		return -3;	// cf. line 48

	// Ensuite on calcule le centroide de tout ca
	Centroide = Centroid(X_Or, Y_Or, N_Or);

	// On a fini, on retourne le centroide
	return Centroide;
}

