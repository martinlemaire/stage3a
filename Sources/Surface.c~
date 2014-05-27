#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Fuzzy.h"
#include "Functions.h"

//#define DEBUG

int Surface(int TAILLE,float** MF_X, int** regle, float A_Min, float A_Max, float B_Min, float B_Max, char* And, char* Or, int NbPointsA, int NbPointsB)
{	
		// On instancie les variables internes
		
			// Compteurs
		int i = 0;
		int j = 0;

			// Variables temporaires
		float Centroide = 0.0;
		float Q_A = (A_Max - A_Min)/NbPointsA;
		float Q_B = (B_Max - B_Min)/NbPointsB;
		float Min, Max;

			// Fichier pour ecritures données
		FILE* fichier = NULL;
	
		// On prépare le fichier
		fichier = fopen("Results/test.txt", "w+");
		fprintf(fichier,"#X\tY\tZ\n");

		// On calcule Min et Max pour la normalisation
		NormalValues(TAILLE, MF_X, &Min, &Max); 

		// On boucle et on écrit dans le fichier pour ensuite afficher les points
		for (i=0; i<NbPointsA; i++)
		{
			for (j=0; j<NbPointsB; j++)
			{
				 #ifdef DEBUG
					printf("DEBUG --- Line38 --- Surface.c ---\nA = %f		B = %f\n\n",(A_Min + Q_A*i), (B_Min + Q_B*j));
				#endif

				Centroide = Fuzzy(regle, TAILLE, MF_X, (A_Min + Q_A*i), (B_Min + Q_B*j), "Min", "Max");
				// On normalise
				Centroide = Normalisation(Centroide, Min, Max);
				fprintf(fichier,"%f\t%f\t%f\n", A_Min + Q_A*i, B_Min + Q_B*j, Centroide);
			}
			fprintf(fichier,"\n");	
		}
		
		fclose(fichier);
	
		return 0;		
}
