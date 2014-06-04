#include <stdio.h>
#include <stdlib.h>
	
#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

int ProdFun(int TAILLE, int** regle, float A_Norm, float B_Norm, float** MF_X, int* MF_Prod, float* Y_Prod, int* N_Prod)
{
	// Initialisation compteurs
	int i = 0;
	int j = 0;
	int count = 0;	

	// Initialisation variables
	int N_A = 0;
	int N_B = 0;
	
	int MF_A[2] = {0,0};
	int MF_B[2] = {0,0};
	
	float Y_A[2] = {0,0};
	float Y_B[2] = {0,0};

	int A_Normal = 1;
	int B_Normal = 1;
		
	//------ Appartenances aux différentes MFs pour A_Norm et B_norm ------//

		// On teste d'abord les points 0 et 1
	if (A_Norm == 0 || A_Norm == 1)
	{
		MF_A[N_A] = A_Norm * (TAILLE -1);
		N_A++;
		A_Normal = 0;
	}
	if (B_Norm == 0 || B_Norm == 1)
	{	
		MF_B[N_B] = B_Norm * (TAILLE -1);
		N_B++;
		B_Normal = 0;
	}
		// On teste les autres si besoin
	if (A_Normal == 1 && B_Normal == 1)
	{
		for ( i = 0; i<TAILLE; i++ )
		{
			if ( (A_Norm > MF_X[i][0] && A_Norm < MF_X[i][2]) && A_Normal == 1 )
			{
				MF_A[N_A] = i;
				N_A++;
			} 
			if ( (B_Norm > MF_X[i][0] && B_Norm < MF_X[i][2]) && B_Normal == 1 )
			{
				MF_B[N_B] = i;
				N_B++;
			}
		}
	}
	
	//------ On définit la hauteur relative aux differentes MFs ------//

		// Pour A

	for ( i = 0; i < N_A; i++ )
	{
		// on teste les cas particuliers : 
		// Ici si A appartient a la premiere MF
		if (MF_A[i] == 0)
		{
			Y_A[i] = min(1,(1 + ( (-1)/(MF_X[0][2] - MF_X[0][1]) ) * ( A_Norm - MF_X[0][1])));
		} 
		// Ici si A appartient a la derniere
		else if (MF_A[i] == TAILLE -1)
		{
			Y_A[i] = min(1,(0 + ( 1/( MF_X[TAILLE-1][1] - MF_X[TAILLE-1][0] )) * ( A_Norm - MF_X[TAILLE-1][0] )));
		}
		// Cas géneral 
		else if (MF_A[i] < TAILLE - 1 && MF_A[i] > 0)
		{
			Y_A[i] = min((1 - ( 1/( MF_X[MF_A[i]][1] - MF_X[MF_A[i]][0] )) * ( MF_X[MF_A[i]][1] - A_Norm )), (1 - ( 1/( MF_X[MF_A[i]][2] - MF_X[MF_A[i]][1] )) * ( A_Norm - MF_X[MF_A[i]][1] )));
		} 
		// Erreur
		else 
		{
			return -1;
		}
	}
 
		// Pour B

	for ( i = 0; i < N_B; i++ )
	{
		// on teste les cas particuliers : 
		// Ici si B appartient a la premiere MF
		if (MF_B[i] == 0)
		{
			Y_B[i] = min(1,(1 + ( (-1)/(MF_X[0][2] - MF_X[0][1]) ) * ( B_Norm - MF_X[0][1])));
		} 
		// Ici si B appartient a la derniere
		else if (MF_B[i] == TAILLE -1)
		{
			Y_B[i] = min(1,(0 + ( 1/( MF_X[TAILLE-1][1] - MF_X[TAILLE-1][0] )) * ( B_Norm - MF_X[TAILLE-1][0] )));
		}
		// Cas géneral 
		else if (MF_B[i] < TAILLE - 1 && MF_B[i] > 0)
		{
			Y_B[i] = min((1 - ( 1/( MF_X[MF_B[i]][1] - MF_X[MF_B[i]][0] )) * ( MF_X[MF_B[i]][1] - B_Norm )), (1 - ( 1/( MF_X[MF_B[i]][2] - MF_X[MF_B[i]][1] )) * ( B_Norm - MF_X[MF_B[i]][1] )));
		} 
		// Erreur
		else 
		{
			return -1;
		}
	} 
	
	//------ On applique maintenant la matrice des règles ------//	
	for (i = 0; i < N_A; i++)
	{
		for (j = 0; j < N_B; j++)
		{
			MF_Prod[count] = regle[MF_A[i]][MF_B[j]];
			Y_Prod[count++] = Y_A[i] * Y_B[j];
		} 
	}
		
	// On définit le nombre de MFs de sortie
	*N_Prod = count;
}
