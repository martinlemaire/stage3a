// Prototype fonction : ./AndSimu "fichierLib" "fichierExp" "Norm" "fichierVal"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../Headers/Fuzzy.h"
#include "../Headers/Functions.h"

int main(int argc, char *argv[])
{
	//Instanciations variables
	int i, j, k;
	int Taille;
	int NbrPortes;
	int xRange, yRange;
	float Centroide;
	float Min, Max;
	float MseMin = 10000;
	int IndMseMin;	
 	float MinX, MinY, MinZ;
	float MaxX, MaxY, MaxZ;

	// Instanciation Structure
	typedef struct 
	{
		float x;
		float y;
		float z;
	}Point;	


	FILE* fichierLib = NULL;
	if (argc > 1)
	{
		fichierLib = fopen(argv[1], "r");
		if (fichierLib != NULL)
			fscanf(fichierLib, "%i\t%i\n", &Taille, &NbrPortes);
		else 
			return -1;
	}
	else 
		return -1;
	
	FILE* fichierExp = NULL;
	if (argc > 2)
	{
		fichierExp = fopen(argv[2], "r");
		if ( fichierExp != NULL)
			fscanf(fichierExp, "%i\t%i\n", &xRange, &yRange);
	}

	FILE* fichierVal = NULL;
	if (argc > 3 && strcmp(argv[3],"norm"))
	{
		fichierVal = fopen(argv[3], "w+");
	}
	else if (argc > 4)
	{
		fichierVal = fopen(argv[4], "w+");
	} 

	// Instanciation "matrice" de dimension 3 
	int*** TabAnd = NULL;
	TabAnd = malloc(sizeof(int**)*NbrPortes);
	for(i=0; i<NbrPortes; i++)
	{
		TabAnd[i] = (int**)malloc(sizeof(int*)*Taille);
	}
	for(i=0; i<NbrPortes; i++)
	{
		for(j=0; j<Taille; j++)
		{
			TabAnd[i][j] = (int*)malloc(sizeof(int)*Taille);
		}
	}

	// Instanciation matrice de notre structure
	Point** TabExp = NULL;
	TabExp = malloc(sizeof(Point*)*xRange);
	for(i=0; i<xRange; i++)
		TabExp[i] = malloc(sizeof(Point)*yRange);

	// Instanciation liste pour enregistrer les différentes Mse (erreur quadratique moyennes)
	float* Mse = NULL;
	Mse = malloc(sizeof(float)*NbrPortes);
	
	// Instanciation Mf_X
	float** MF_X = NULL;
	MF_X = malloc(sizeof(float*)*Taille);	
	for (i=0; i<Taille; i++)
		MF_X[i] = malloc(sizeof(float)*3);
	
	// Ecriture des matrices a tester
	for(i=0; i<NbrPortes; i++)
	{
		for(j=0; j<Taille*Taille; j++)
		{
			fscanf(fichierLib, "%i\t", &TabAnd[i][(int)(j/Taille)][j % Taille]);
		}
		fscanf(fichierLib, "\n");
	}
	
	// Ecritures des Mfs
	for(i=0; i<Taille; i++)
	{
			fscanf(fichierLib, "%f\t%f\t%f\n", &MF_X[i][0], &MF_X[i][1], &MF_X[i][2]);
	}

	// Lecture du fichier experimental
	MinX = INFINITY;
	MinY = INFINITY;
	MinZ = INFINITY;
	MaxX = -1*INFINITY;
	MaxY = -1*INFINITY;
	MaxZ = -1*INFINITY;

	//printf("MinX = %.30f\tMinY = %.30f\tMinZ = %.30f\nMaxX = %.10f\tMaxY = %.10f\tMaxZ = %.10f\n", MinX, MinY, MinZ, MaxX, MaxY, MaxZ);
	
	for(i=0; i<xRange; i++)
	{
		for(j=0; j<yRange; j++)
		{
			fscanf(fichierExp,"%f\t%f\t%f\n", &(TabExp[i][j].x), &(TabExp[i][j].y), &(TabExp[i][j].z));

			if(TabExp[i][j].x < MinX)
				MinX = TabExp[i][j].x;
			else if (TabExp[i][j].x > MaxX)
				MaxX = TabExp[i][j].x;
			if(TabExp[i][j].y < MinY)
				MinY = TabExp[i][j].y;
			else if (TabExp[i][j].y > MaxY)
				MaxY = TabExp[i][j].y;
			if(TabExp[i][j].z < MinZ)
				MinZ = TabExp[i][j].z;
			else if (TabExp[i][j].z > MaxZ)
				MaxZ = TabExp[i][j].z;
		}
	}

	//printf("MinX = %.30f\tMinY = %.30f\tMinZ = %.30f\nMaxX = %.10f\tMaxY = %.10f\tMaxZ = %.10f\n", MinX, MinY, MinZ, MaxX, MaxY, MaxZ);
	// Normalisation des valeurs
  for(i=0; i<xRange; i++)
	{
		for(j=0; j<yRange; j++)
		{
			TabExp[i][j].x = ( log(TabExp[i][j].x) - log(MinX) )/( log(MaxX) - log(MinX) );
			TabExp[i][j].y = ( log(TabExp[i][j].y) - log(MinY) )/( log(MaxY) - log(MinY) );
			TabExp[i][j].z = ( log(TabExp[i][j].z) - log(MinZ) )/( log(MaxZ) - log(MinZ) );
		}
	}
	
	//DEBUG
  /*for(i=0; i<xRange; i++)
	{
		for(j=0; j<yRange; j++)
		{
			printf("%f\t", TabExp[i][j].x);
			printf("%f\t", TabExp[i][j].y);
			printf("%f\n", TabExp[i][j].z);
		}
		printf("\n");
	}*/
	

	// On récupere les valeurs de normalisation
	NormalValues(Taille, MF_X, &Min, &Max);
	
	// On appele la fonction Fuzzy sur l'ensemble des points 
	for(i=0; i<NbrPortes; i++)
	{
		Mse[i] = 0.0;
		for(j=0; j<xRange; j++)
		{
			for(k=0; k<yRange; k++)
			{
				Centroide = Fuzzy(TabAnd[i], Taille, MF_X, TabExp[j][k].x, TabExp[j][k].y, "Min","Max");
				if( argc > 3 && !(strcmp(argv[3], "norm")) ) 
					Centroide = Normalisation(Centroide, Min, Max);
				Mse[i] += (Centroide - TabExp[j][k].z)*(Centroide - TabExp[j][k].z);
			}
		}
		Mse[i] = Mse[i]/(xRange*yRange);
	}
	

	// On cherche la valeur minimale des Mse[i]
	for(i=0; i<NbrPortes; i++)
	{
		if (Mse[i] < MseMin)
		{
			MseMin = Mse[i];
			IndMseMin = i;
		}
	}
	
	printf("MseMin = %f\tIndMseMin = %i\n",MseMin, IndMseMin);
	
	if (fichierVal != NULL)
	{
		for(i=0; i<xRange; i++)
		{
			for(j=0; j<yRange; j++)
			{
				Centroide = Fuzzy(TabAnd[IndMseMin], Taille, MF_X, TabExp[i][j].x, TabExp[i][j].y, "Min","Max");
				
				if( !(strcmp(argv[3], "norm")) ) 
					Centroide = Normalisation(Centroide, Min, Max);

				fprintf(fichierVal,"%f\t%f\t%f\n", TabExp[i][j].x, TabExp[i][j].y, Centroide);
			}
			fprintf(fichierVal,"\n");
		}
	}
	
	//Liberation mémoire
	for(i=0; i<NbrPortes; i++)
	{
		for(j=0; j<Taille; j++)
		{
			free(TabAnd[i][j]);
		}
		free(TabAnd[i]);
	}
	free(TabAnd);
	
	for(i=0; i<xRange; i++)
		free(TabExp[i]);
	free(TabExp);

	for (i = 0; i<Taille; i++)
		free(MF_X[i]);
	free(MF_X);
	free(Mse);

	if(fichierLib != NULL)
		fclose(fichierLib);
	if(fichierExp != NULL)
		fclose(fichierExp);
	if(fichierVal != NULL)
		fclose(fichierVal);

	return 0;
}
