//---------------------------------------------------------------------------//
// Fichier      : MaxFun.c                                           	     //
// Auteur 	: LEMAIRE Martin                                             //
// Description	: Fonction qui va réaliser l'opérateur Fuzzy OU.	     //
//                A partir du nombre de MFs (Taille), de la géometrie de ces //
//                Mfs (MF_X), et des résultats de la fonction Fuzzy Min (ET) //
//		  (MF_Min, Y_Min, N_Min) va modifier les valeurs de X_Max,   //
//                Y_Max et N_Max passés a la fonction. 			     //
//		  Pour cela il va prendre le maximum des valeurs contenues   //
//		  dans Y_Min pour chaque X_Min correspondant, et renvoyer les//
//		  points "intéressants"		                             //
//---------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>

#include "../Headers/CrossFun.h"

//#define DEBUG

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

	#ifdef DEBUG	
		printf("DEBUG --- line 43:\n");
		for (i=0; i<Taille-1; i++)
			printf("X_Cross[%i] = %f		Y_Cross[%i] = %f\n", i, X_Cross[i], i, Y_Cross[i]);

		printf("\n");
	#endif

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
	#ifdef DEBUG
		printf("DEBUG --- Line 71:\n");
		for(i = 0; i<4; i++)
		{
			printf("MF_Min[%i] = %i		Y_Min[%i] = %f\n", i, MF_Min[i], i, Y_Min[i]);
		}
		printf("\n");
	#endif
	// On enleve ensuite les doublons dans MF_Min et on garde la valeur Y_Min correspondante la plus grande
	Y_Min_Temp = 0.0;
	
	#ifdef DEBUG
		printf("DEBUG --- Line 82:\n");
		printf("N_Min = %i\n\n",N_Min);
	#endif

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
				Y_Min[i-1] = Y_Min_Temp;
				Y_Min[i] = Y_Min[j];
				Y_Min_Temp = 0.0;
			}
    }
  N_Single = i + 1;  
	
	#ifdef DEBUG
		printf("DEBUG -- Line 106:\n");
		for(k = 0; k<4; k++)
		{
			printf("MF_Min[%i] = %i		Y_Min[%i] = %f\n", k, MF_Min[k], k, Y_Min[k]);
		}
		printf("N_Single = %i\n", N_Single);
		printf("N_Max_Temp = %i\n\n", N_Max_Temp);
	#endif

	// cas ou on a des doublons en fin de liste (fout la merde parfois!!)
	if(i != j-1 && MF_Min[i+1] == MF_Min[i] )
	{	
		for(k = i; k < j+1; k++)
		{
			if( Y_Min[k] > Y_Min_Temp )
				Y_Min_Temp = Y_Min[k];
		}
		Y_Min[i] = Y_Min_Temp;	
	}
	
	#ifdef DEBUG
		printf("DEBUG -- Line 126:\n");
		for(i = 0; i<4; i++)
		{
			printf("MF_Min[%i] = %i		Y_Min[%i] = %f\n", i, MF_Min[i], i, Y_Min[i]);
		}
		printf("N_Single = %i\n", N_Single);
		printf("N_Max_Temp = %i\n\n", N_Max_Temp);
	#endif
		
	// On enregistre dans N_Single le nombre d'elements "en simple" qui sont rangé en premier dans Y_Min et MF_Min
	// Maintenant on doit réaliser la fonction Max et définir les points "intéressants" pour défuzzifier par la suite
		
	//On ajoute le premier point
	if(MF_Min[0] == 0)	//Si la premiere MF est MF[0]
	{
		X_Max[N_Max_Temp] = 0.0;
		Y_Max[N_Max_Temp++] = Y_Min[0];
	}
	else if(MF_Min[0] >= 0 && MF_Min[0] < Taille) //Sinon
	{
		X_Max[N_Max_Temp] = MF_X[MF_Min[0]][0];
		Y_Max[N_Max_Temp++] = 0.0;
		
		X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[0]][0], 0.0, MF_X[MF_Min[0]][1], 1.0, Y_Min[0]);
		Y_Max[N_Max_Temp++] = Y_Min[0];
	}
	else
	{
		return -1;
	}
	
	#ifdef DEBUG
		printf("DEBUG -- Line 136:\n");
		printf("N_Max_Temp = %i\n", N_Max_Temp);
		for(i=0; i<N_Max_Temp; i++)
			printf("X_Max[%i] = %f		Y_Max[%i] = %f\n",i, X_Max[i], i, Y_Max[i]);
		printf("\n");
	#endif

	// Pour tous les autres points sauf le dernier
	for(i = 0; i<N_Single-1; i++)
	{
		if(MF_Min[i] >= 0 && MF_Min[i] < Taille)
		{
			//PLusieurs cas différents:
			if( Y_Min[i] > Y_Cross[MF_Min[i]] && Y_Min[i+1] > Y_Cross[MF_Min[i]] )
			{
				X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i]][1], 1.0, MF_X[MF_Min[i]][2], 0.0, Y_Min[i]);
				Y_Max[N_Max_Temp++] = Y_Min[i];
		
				X_Max[N_Max_Temp] = X_Cross[MF_Min[i]];
				Y_Max[N_Max_Temp++] = Y_Cross[MF_Min[i]];
	   			
				X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i+1]][0], 0.0, MF_X[MF_Min[i+1]][1], 1.0, Y_Min[i+1]);
				Y_Max[N_Max_Temp++] = Y_Min[i+1];
			}
			else if( Y_Min[i] >= Y_Cross[MF_Min[i]] && Y_Min[i+1] <= Y_Cross[MF_Min[i]] )
			{
				X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i]][1], 1.0, MF_X[MF_Min[i]][2], 0.0, Y_Min[i]);
				Y_Max[N_Max_Temp++] = Y_Min[i];	
	
				X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i]][1], 1.0, MF_X[MF_Min[i]][2], 0.0, Y_Min[i+1]);
				Y_Max[N_Max_Temp++] = Y_Min[i+1];	
			}
			else if( Y_Min[i] <= Y_Cross[MF_Min[i]] && Y_Min[i+1] >= Y_Cross[MF_Min[i]] )
			{
				X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i+1]][1], 1.0, MF_X[MF_Min[i+1]][0], 0.0, Y_Min[i]);
				Y_Max[N_Max_Temp++] = Y_Min[i];	
	
				X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i+1]][1], 1.0, MF_X[MF_Min[i+1]][0], 0.0, Y_Min[i+1]);
				Y_Max[N_Max_Temp++] = Y_Min[i+1];	
			}
			else if( Y_Min[i] <= Y_Cross[MF_Min[i]] && Y_Min[i+1] <= Y_Cross[MF_Min[i]] )
			{
			  if( Y_Min[i] > Y_Min[i+1] + 0.0001 )
				{		  
				X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i]][1], 1.0, MF_X[MF_Min[i]][2], 0.0, Y_Min[i]);
				Y_Max[N_Max_Temp++] = Y_Min[i];	
	
				X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i]][1], 1.0, MF_X[MF_Min[i]][2], 0.0, Y_Min[i+1]);
				Y_Max[N_Max_Temp++] = Y_Min[i+1];	
				}
				else if( Y_Min[i] < Y_Min[i+1] -0.0001)
				{
				X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i+1]][1], 1.0, MF_X[MF_Min[i+1]][0], 0.0, Y_Min[i]);
				Y_Max[N_Max_Temp++] = Y_Min[i];	

				X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[i+1]][1], 1.0, MF_X[MF_Min[i+1]][0], 0.0, Y_Min[i+1]);
				Y_Max[N_Max_Temp++] = Y_Min[i+1];		
				}
			}
			// Error
			else 
				return -1;
		}	
		else 
		{
			return -1;
		}
	}			
	//On rajoute le dernier point
	if (MF_Min[N_Single-1] == Taille-1) // La derniere MF de MF_Min est MF[taille-1]
	{
		X_Max[N_Max_Temp] = 1.0;
		Y_Max[N_Max_Temp++] = Y_Min[N_Single-1];
	}
	else //Sinon
	{	
		X_Max[N_Max_Temp] = CrossFun(MF_X[MF_Min[N_Single-1]][1], 1.0, MF_X[MF_Min[N_Single-1]][2], 0.0, Y_Min[N_Single-1]);
		Y_Max[N_Max_Temp++] = Y_Min[N_Single-1];

		X_Max[N_Max_Temp] = MF_X[MF_Min[N_Single-1]][2];
		Y_Max[N_Max_Temp++] = 0.0;
	}


	*N_Max = N_Max_Temp;

	#ifdef DEBUG 
		printf("Valeurs de sorties de MaxFun : \n");
		for(i=0; i<14; i++ )
			printf("X_Max[%i] = %f		Y_Max[%i] = %f\n", i, X_Max[i], i, Y_Max[i]);
		printf("N_Max = %i\n\n", *N_Max);
	#endif

	free(X_Cross);
	X_Cross = NULL;
	free(Y_Cross);
	Y_Cross = NULL;

	return 0;
}
