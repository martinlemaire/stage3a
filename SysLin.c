#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fuzzy.h"
#include "Functions.h"

int main(int argc, char *argv[])
{
	// Initialisation compteurs
	int i,j;

	// Instanciation variables temporaires
	float Min, Max;
	float Centroide;
	FILE* fichier = NULL;
	float Q = 0;
	
	// Entrées de la fonction
	int NbPoints = 100;
	float A_Min = 0.0;
	float A_Max = 1.0;
	float Q_A = (A_Max - A_Min)/NbPoints;
	int NbIterations = 2;
	int taille=3;	

	if (argc != 1)
		taille = atoi(argv[1]);

	if (argc > 2)
		NbIterations = atoi(argv[2]);

		// Création de toutes les matrices dynamiquement
	//MF_X
	float** MF_X = NULL;
	MF_X = malloc(sizeof(float*)*taille);
  for(i = 0; i<taille; i++)
  	MF_X[i] = malloc(sizeof(float)*3);
	
	//regle
	int* regle = NULL;
	regle = malloc(sizeof(int)*taille);

	// Results
	float* Results = NULL;
	Results = malloc(sizeof(float)*(NbPoints+1));

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
			regle[i] = i;	
	}

	// On prepare le fichier pour les sorties
	fichier = fopen("Results/SysLin.dat", "w+");
	fprintf(fichier, "#X\tY\n#\n");

	// On calcule Min et Max pour la normalisation
	NormalValues(taille, MF_X, &Min, &Max); 

	// On boucle et on écrit dans le fichier pour ensuite afficher les points
	for (i=0; i<NbIterations; i++)
	{
		for (j=0; j<NbPoints+1; j++)
		{	
			if (i==0)
				Results[j] = (A_Min + Q_A*j);
			Centroide = Synth(regle, taille, MF_X, Results[j], "Min", "Max");
			
			// On normalise si c'est demandé
			if (argc == 3 && (!(strcmp(argv[2], "Norm"))))
				Centroide = Normalisation(Centroide, Min, Max);

			if (argc == 4 && (!(strcmp(argv[3], "Norm"))))
				Centroide = Normalisation(Centroide, Min, Max);
		 
			if (i == NbIterations -1)
			{
				fprintf(fichier, "%f\t%f\n", (A_Min + Q_A*j), Centroide);	
			}	
			else 
				Results[j] = Centroide;
		}
	}
	
	fclose(fichier);

	// Et on libere la memoire allouée
	for(i=0; i<taille; i++)
	{
		free(MF_X[i]);
		MF_X[i] = NULL;
	}

	free(MF_X);
	MF_X = NULL;
	free(regle);
	regle = NULL;
 	free(Results);
	Results = NULL;

	return 0;
}

