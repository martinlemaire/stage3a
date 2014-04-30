#include <stdio.h>
#include <stdlib.h>

#include "CrossFun.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

int MaxFun(int Taille, float** MF_X, int* MF_Min, float* Y_Min, int N_Min, float* X_Max, float* Y_Max, int* N_Max)
{
	// Instanciation compteurs
	int i = 0;
	int j = 0;
	int k = 0;

	// Instanciation variables temporaires
	int MF_Min_Temp = 0;
	float Y_Min_Temp = 0;
	int N_Single = 0;
	int N_Max_Temp = 0.0;


	float* X_Cross = NULL;
	X_Cross = malloc(sizeof(float)*(Taille-1));
	float* Y_Cross = NULL;
	Y_Cross = malloc(sizeof(float)*(Taille - 1));

	for(i = 0; i < Taille-1; i++)
	{
		X_Cross[i] = 0.0;
		Y_Cross[i] = 0.0;
	}	
	
	// Pour commencer, on trouve les abcisses des points de croisements entre les différentes MFs
	for(i = 0; i<(Taille-1); i++)
	{
		X_Cross[i] = MF_X[i][1] + 1/( (1/(MF_X[i][2] - MF_X[i][1])) + (1/(MF_X[i+1][1] - MF_X[i+1][0])));	
		Y_Cross[i] = 1 - (X_Cross[i] - MF_X[i][1])/(MF_X[i][2] - MF_X[i][1]);
	}

	printf("39\n");
	// On range le tableau MF_Min et on garde la correspondance avec Y_Min
  for(i = 1; i < N_Min; i++)
	{
    for(j = N_Min-1; j >= i; j--) 
		{
      // comparaisons des MF_min adjacentes 
      if(MF_Min[ j - 1] > MF_Min[ j ]) 
			{
        // Echanger les MF_min selon leurs ordres 
        MF_Min_Temp = MF_Min[ j - 1];
        MF_Min[ j - 1] = MF_Min[ j ];
        MF_Min[ j ] = MF_Min_Temp;

				// Echanger les Y_Min correspondant			
        Y_Min_Temp = Y_Min[ j - 1];
        Y_Min[ j - 1] = Y_Min[ j ];
        Y_Min[ j ] = Y_Min_Temp;
      }
    }
	}
	printf("60\n");
	// On enleve ensuite les doublons dans MF_Min et on garde la valeur Y_Min correspondante la plus grande
	Y_Min_Temp = 0.0;
	
	for(i = 0, j = 1; j < N_Min; j++)
  	if(MF_Min[i] != MF_Min[j])
    {
	    i++;
  	  if(i != j)
			{
    		MF_Min[i] = MF_Min[j];
				for(k = i-1; k < j; k++)
				{
					if( Y_Min[k] > Y_Min_Temp )
						Y_Min_Temp = Y_Min[k];
				}
				Y_Min[i] = Y_Min_Temp;
			}
    }
	// On enregistre dans N_Single le nombre d'elements "en simple" qui sont rangé en premier dans Y_Min et MF_Min
  N_Single = i + 1;  
	printf("81\n");

	// Maintenant on doit réaliser la fonction Max et définir les points "intéressants" pour défuzzifier par la suite
		
	printf("N_Max_Temp = %i\n", N_Max_Temp);
	//On ajoute le premier point
	if(MF_Min[0] == 0)	//Si la premiere MF est MF[0]
	{
		X_Max[N_Max_Temp] = 0.0;
		Y_Max[N_Max_Temp++] = Y_Min[0];
	}
	else //Sinon
	{
		printf("95\n");
		X_Max[N_Max_Temp] = MF_X[MF_Min[0]][0];
		Y_Max[N_Max_Temp++] = 0.0;
		
		X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[0]][0], 0.0, MF_X[MF_Min[0]][1], 1.0, Y_Min[0]);
		Y_Max[N_Max_Temp++] = Y_Min[0];
	//debug
	printf("N_Max_Temp = %i\n", N_Max_Temp);
	}
	printf("98\n");
	// Pour tous les autres points sauf le dernier
	for(i = 0; i<N_Single-1; i++)
	{
		//PLusieurs cas différents:
		if( Y_Min[i] > Y_Cross[MF_Min[i]] && Y_Min[i+1] > Y_Cross[MF_Min[i]] )
		{
			printf("105\n");
			X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i]][1], 1.0, MF_X[MF_Min[i]][2], 0.0, Y_Min[i]);
			Y_Max[N_Max_Temp++] = Y_Min[i];
	
			X_Max[N_Max_Temp] = X_Cross[MF_Min[i]];
			Y_Max[N_Max_Temp++] = Y_Cross[MF_Min[i]];
   			
			X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i+1]][0], 0.0, MF_X[MF_Min[i+1]][1], 1.0, Y_Min[i+1]);
			Y_Max[N_Max_Temp++] = Y_Min[i+1];
		}
		else if( Y_Min[i] > Y_Cross[MF_Min[i]] && Y_Min[i+1] < Y_Cross[MF_Min[i]] )
		{
			printf("117\n");
			X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i]][1], 1.0, MF_X[MF_Min[i]][2], 0.0, Y_Min[i]);
			Y_Max[N_Max_Temp++] = Y_Min[i];	

			X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i]][1], 1.0, MF_X[MF_Min[i]][2], 0.0, Y_Min[i+1]);
			Y_Max[N_Max_Temp++] = Y_Min[i+1];	
		}
		else if( Y_Min[i] < Y_Cross[MF_Min[i]] && Y_Min[i+1] > Y_Cross[MF_Min[i]] )
		{
			printf("126\n");
			X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i+1]][1], 1.0, MF_X[MF_Min[i+1]][2], 0.0, Y_Min[i]);
			Y_Max[N_Max_Temp++] = Y_Min[i];	

			X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i+1]][1], 1.0, MF_X[MF_Min[i+1]][2], 0.0, Y_Min[i+1]);
			Y_Max[N_Max_Temp++] = Y_Min[i+1];	
		}
		else if( Y_Min[i] < Y_Cross[MF_Min[i]] && Y_Min[i+1] < Y_Cross[MF_Min[i]] )
		{
			printf("135\n");
			if( Y_Min[i] > Y_Min[i+1] )
			{		  
			X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i]][1], 1.0, MF_X[MF_Min[i]][2], 0.0, Y_Min[i]);
			Y_Max[N_Max_Temp++] = Y_Min[i];	

			X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i]][1], 1.0, MF_X[MF_Min[i]][2], 0.0, Y_Min[i+1]);
			Y_Max[N_Max_Temp++] = Y_Min[i+1];	
			}
			else if( Y_Min[i] < Y_Min[i+1] )
			{
			X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i+1]][1], 1.0, MF_X[MF_Min[i+1]][2], 0.0, Y_Min[i]);
			Y_Max[N_Max_Temp++] = Y_Min[i];	

			X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i+1]][1], 1.0, MF_X[MF_Min[i+1]][2], 0.0, Y_Min[i+1]);
			Y_Max[N_Max_Temp++] = Y_Min[i+1];		
			}
		}
		// Error
		else 
			return -1;
	}			
	//On rajoute le dernier point
	if (MF_Min[N_Single-1] == Taille-1) // La derniere MF de MF_Min est MF[taille-1]
	{
		printf("157\n");
		X_Max[N_Max_Temp] = 1.0;
		Y_Max[N_Max_Temp++] = Y_Min[N_Single-1];
	}
	else //Sinon
	{
		printf("164\n");
		X_Max[N_Max_Temp] = MF_X[MF_Min[N_Single-1]][2];
		Y_Max[N_Max_Temp++] = 0.0;
	
		X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[N_Single-1]][1], 1.0, MF_X[MF_Min[N_Single-1]][2], 0.0, Y_Min[N_Single-1]);
		Y_Max[N_Max_Temp++] = Y_Min[0];
	}
	// Maintenant si tout c'est bien passé, on a tous les points :-) 

	for(i=0; i<14; i++ )
		printf("X_Max[%i] = %f\nY_Max[%i] = %f\n", i, X_Max[i], i, Y_Max[i]);

	printf("N_Max = %i\n", N_Max_Temp);
	return 0;
}
