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
	int xRange, yRange;	
	float MinX, MinY, MinZ, MaxX, MaxY, MaxZ;
	float TempFloat;
	int count = 0;
	
	// Instanciation structure
	typedef struct
	{
		float x; 
		float y;
		float z;
	}Point;
	
	if (argc > 3)
	{
		fichierExp = fopen(argv[1], "r");
		fichierOut = fopen(argv[2], "w+");
		Taille = atoi(argv[3]);
		if (fichierExp == NULL || fichierOut == NULL)
		{
			printf("error\n");
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


	for(i=0; i<Taille; i++)
		for(j=0; j<Taille; j++)
		{
			Regle[i][j] = 0;
		}

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

	// DEBUG
	/*for(i=0; i<xRange; i++)
	{
		for(j=0; j<yRange; j++)
		{
			printf("%f\t%f\t%f\n", TabExp[i][j].x, TabExp[i][j].y, TabExp[i][j].z );
		}
	}*/
	

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
					if(TabExp[k][l].x >= i*(1/((float)Taille)) && TabExp[k][l].x < (i+1)*(1/(float)Taille) && TabExp[k][l].y >= j*(1/(float)Taille) && TabExp[k][l].y < (j+1)*(1/(float)Taille) )
					{
						TempFloat += TabExp[k][l].z;
						count++;
					}
				}
			}
			//printf("TempFloat = %f\tcount = %i\n", TempFloat, count);	

			TempFloat = TempFloat/count*Taille;	
			//printf("TempFloat = %f\n", TempFloat);

			Regle[i][j] = (int)(TempFloat);
			fprintf(fichierOut,"%i\t", Regle[i][j]);
			TempFloat = 0.0;
			count = 0.0;
		}
	}		

	return 0;
}
