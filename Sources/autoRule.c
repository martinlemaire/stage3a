//---------------------------------------------------------------------------//
// Fichier      : autoRule.c                                           	     //
// Auteur 	: LEMAIRE Martin                                                 //
// Description	: Main qui à partir de valeurs experimentales contenues dans //
//                "fichierExp" va essayer de trouver une matrice de regle de //
//                taille "TailleOut" qui va fitter ces valeurs experimentales//
//		  Ce main va ensuite renvoyer cette matrice de regle dans le           //
//                fichier "fichierOut"                                       //
//---------------------------------------------------------------------------//
/* ./autoRule fichierExp fichierOut TailleOut */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define min(a,b) (a<=b?a:b)	

int main(int argc, char *argv[])
{
	// Instanciation variables
	int i, j, k, l; 
	int Taille;
	FILE* fichierExp = NULL;
	FILE* fichierOut = NULL;
	FILE* fichierMF = NULL;
	int xRange, yRange;	
	float MinX, MinY, MinZ, MaxX, MaxY, MaxZ;
	float TempFloat = 0;
	int count = 0;

	// Instanciation structure
	typedef struct
	{
		float x; 
		float y;
		float z;
	}Point;
	
	if (argc > 4)
	{
		fichierExp = fopen(argv[1], "r");
		fichierOut = fopen(argv[2], "w+");
		if (fichierExp == NULL || fichierOut == NULL)
		{
			printf("error\n");
			return -1;
		}
		else if( !(strcmp(argv[3], "auto")) )
		{
			Taille = atoi(argv[4]);
			
		}
		else if( !(strcmp(argv[3], "file")) )
		{
			fichierMF = fopen(argv[4], "r");
		}
		else
		{
			printf("error");
			return -1;
		}
	}
	else
	{
		printf("error\n");
		return -1;
	}

	// on recupere la taille des données en entrée
	fscanf(fichierExp, "%i\t%i\n", &xRange, &yRange);
	
	// On instancie une matrice pouvant les contenir
	Point** TabExp = NULL;
	TabExp = malloc(sizeof(Point*)*xRange);
	for(i=0; i<xRange; i++)
		TabExp[i] = malloc(sizeof(Point)*yRange);	
	
	// On instancie notre future matrice des regles
	int** Regle = NULL;
	Regle = malloc(sizeof(int*)*Taille);
	for(i=0; i<Taille; i++)
		Regle[i] = malloc(sizeof(int)*Taille);	

	// Lecture du fichier experimental
	MinX = INFINITY;
	MinY = INFINITY;
	MinZ = INFINITY;
	MaxX = -1*INFINITY;
	MaxY = -1*INFINITY;
	MaxZ = -1*INFINITY;

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

	l = 0;
	k = 0;
	for(i=0; i<Taille; i++)
	{
		for(j=0; j<Taille; j++)
		{
			for(k=0; k<xRange; k++)
			{
				for(l=0; l<yRange; l++)
				{		
					if(TabExp[k][l].x >= i*(1/(float)Taille) && TabExp[k][l].x < (i+1)*(1/(float)Taille) && TabExp[k][l].y >= j*(1/(float)Taille) && TabExp[k][l].y < (j+1)*(1/(float)Taille) )
					{
						TempFloat += TabExp[k][l].z;
						count++;
					}
				}
			}

			TempFloat = TempFloat/count*Taille;	
			Regle[i][j] = (int)(TempFloat);
			fprintf(fichierOut,"%i\t", Regle[i][j]);
			TempFloat = 0.0;
			count = 0.0;
		}
	}		

	return 0;
}
