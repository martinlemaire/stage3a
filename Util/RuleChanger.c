/* ./RuleChanger fichierMatIn TailleOut fichierMatOut*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)
#define dM	1.41421356237

int round2(float);

int main(int argc, char *argv[])
{
	// Instanciations variables
	int i,j; 
	int TailleIn, TailleOut;
	FILE* fichierMatIn = NULL;
	FILE* fichierMatOut = NULL;
	int** MatIn = NULL;
	int** MatOut = NULL;
	float zoom;
	
	/* --------On gère la matrice en entrée-----------*/

	// On lit le fichier en entrée pour récuperer la taille de notre matrice a transformer
	if(argc > 1)
	{
		fichierMatIn = fopen(argv[1], "r");
		if(fichierMatIn != NULL)
			fscanf(fichierMatIn, "%i\n", &TailleIn);
		else 
		{
			printf("Mauvais fichier d'entrée");
			return -1;
		}
	}
	else 
	{
		printf("Aucun fichier en entrée");
		return -1;
	}

	// On instancie une matrice qui peut le contenir
	MatIn = malloc(sizeof(int*)*TailleIn);
	for(i=0; i<TailleIn; i++)
		MatIn[i] = malloc(sizeof(int)*TailleIn);
	
	// On remplit la matrice
	for(i=0; i<TailleIn*TailleIn; i++)
		fscanf(fichierMatIn, "%i\t", &MatIn[(int)(i/TailleIn)][i % TailleIn]);
	
	/* On ouvre le fichier de sortie */
	if (argc > 3)
	{
		fichierMatOut = fopen(argv[3], "w+");
		if (fichierMatOut == NULL)
		{
			printf("Mauvais fichier de sortie");
			return -1;
		}	
	}
	/* ---------On crée la matrice de sortie -----------*/

	// On récupere sa taille
	if(argc > 2)
	{
		TailleOut = atoi(argv[2]);
	}
	
	// On instancie une matrice pour la contenir
	MatOut = malloc(sizeof(int*)*TailleOut);
	for(i=0; i<TailleOut; i++)
	{
		MatOut[i] = malloc(sizeof(int)*TailleOut);
	}

	
	/* --------- On retrouve le facteur de zoom ou étirement ---------------*/
	
	zoom = (float)(TailleOut-1) / (TailleIn-1);
	printf("TailleOut = %i\tTailleIn = %i\t zoom = %f\n\n", TailleOut, TailleIn, zoom);

	/* -------- On implémente l'algorithme -------------- */

	//
	for (i=0; i<TailleOut; i++)
	{
		for (j=0; j<TailleOut; j++)
		{
			if ( (int)(i/zoom) == i/zoom )
			/* On est entre deux valeurs justes horizontales */  
			{
				/* On est sur une valeur juste */
				if ( (int)(j/zoom) == j/zoom )
					MatOut[i][j] = round2(MatIn[(int)(i/zoom)][(int)(j/zoom)] * zoom);
				else if ( (int)(j/zoom) +1 < TailleIn )
					MatOut[i][j] = round2( ( MatIn[(int)(i/zoom)][(int)(j/zoom)] + ( MatIn[(int)(i/zoom)][(int)(j/zoom)+1] - MatIn[(int)(i/zoom)][(int)(j/zoom)] )*(j/zoom - (int)(j/zoom)) )*zoom );
			}
			else if ( (int)(j/zoom) == j/zoom && (int)(i/zoom) +1 < TailleIn )
			/* On est entre deux valeurs justes verticales */
			{
				MatOut[i][j] = round2( ( MatIn[(int)(i/zoom)][(int)(j/zoom)] + ( MatIn[(int)(i/zoom)+1][(int)(j/zoom)] - MatIn[(int)(i/zoom)][(int)(j/zoom)] )*(i/zoom - (int)(i/zoom) ) )*zoom ); 
			}
			else if (  (int)(j/zoom) +1 < TailleIn && (int)(i/zoom) +1 < TailleIn )
			/* On est entre quatres valeurs justes */
			{
				float d1, d2, d3, d4, dNorm;
				d1 = sqrt( ((int)(i/zoom) - i/zoom)*((int)(i/zoom) - i/zoom) + ((int)(j/zoom) - j/zoom)*((int)(j/zoom) - j/zoom) );	
				d2 = sqrt( ((int)(i/zoom) - i/zoom + 1)*((int)(i/zoom) - i/zoom + 1) + ((int)(j/zoom) - j/zoom)*((int)(j/zoom) - j/zoom) );	
				d3 = sqrt( ((int)(i/zoom) - i/zoom)*((int)(i/zoom) - i/zoom) + ((int)(j/zoom) - j/zoom + 1)*((int)(j/zoom) - j/zoom + 1) );	
				d4 = sqrt( ((int)(i/zoom) - i/zoom + 1)*((int)(i/zoom) - i/zoom + 1) + ((int)(j/zoom) - j/zoom + 1)*((int)(j/zoom) - j/zoom + 1) );	
				dNorm = 4*dM - d1 - d2 - d3 - d4;
				MatOut[i][j] = round2(( ( (dM - d1)*MatIn[(int)(i/zoom)][(int)(j/zoom)] + (dM - d2)*MatIn[(int)(i/zoom) + 1][(int)(j/zoom)] + (dM - d3)*MatIn[(int)(i/zoom)][(int)(j/zoom) +1] + (dM - d4)*MatIn[(int)(i/zoom) + 1][(int)(j/zoom) +1])/dNorm)*zoom);
			}
			//if (i == TailleOut -1 || j == TailleOut -1)
			else
				printf("i = %i\tj = %i\t(int)(j/zoom) = %i\tj/zoom = %f\t(int)(i/zoom) = %i\ti/zoom = %f\t\tMatOut[%i][%i] = %i\n",i , j, (int)(j/zoom), j/zoom, (int)(i/zoom), i/zoom, i, j, MatOut[i][j]);
		}
	}
	
	/* -------- On écrit dans le fichier de sortie ---------*/
	fprintf(fichierMatOut, "%i\n", TailleOut);
	for(i=0; i<TailleOut; i++)
	{
		for(j=0; j<TailleOut; j++)
		{
				fprintf(fichierMatOut, "%i\t", MatOut[i][j]);
		}
		//fprintf(fichierMatOut, "\n");
	}

	return 0;
}


int round2(float number)
{
    return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
}
	
