//----------------------------------------------------------------------------------//  
// Fichier : Min_Fun.c							            //
// Auteur : LEMAIRE Martin   							    //
// Description	: Fonction Fuzzy qui va prendre les valeurs normalisées d'entrées,  //         
//                définir leur appartenance aux différentes MFs, la hauteur associé //	
//                à ces MFs (Ordonnées de croisement entre la MF et la droite       //
//		  x = A_Norm par exemple). Ensuite cette fonction va appliquer      //
//                la matrice des règles à ces MFs définissant suivant les entrées   //
//		  les MFs de sortie correspondantes, et la hauteur associée à       //
//                celle ci grace a la fonction Minimum.			            //
//----------------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
	
#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

//#define DEBUG

int Min_Fun(int TAILLE, int** regle, float A_Norm, float B_Norm, float** MF_X, int* MF_Min, float* Y_Min, int* N_Min)
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
	
	int testA = 1;
	int testB = 1;

	#ifdef DEBUG
		printf("DEBUG --- Line 41 --- Min_Fun.c\n");
		printf("A = %.10f\tB = %10f\n", A_Norm, B_Norm);
	#endif

	//------ Appartenances aux différentes MFs pour A_Norm et B_norm ------//
		// On teste deja si c'est égal a 0 ou 1
	if (A_Norm == 0.0 || A_Norm == 1)
	{
		MF_A[N_A] = A_Norm * (TAILLE -1);
		N_A++;
	}
	if (B_Norm == 0.0 || B_Norm == 1)
	{
		MF_B[N_B] = B_Norm * (TAILLE -1);
		N_B++;
	}
	
	for ( i = 0; i<TAILLE; i++ )
	{
		if ( A_Norm > MF_X[i][0] && A_Norm < MF_X[i][2] )
		{
			MF_A[N_A] = i;
			N_A++;
			#ifdef DEBUG
				printf("DEBUG --- Line 48 --- Min_Fun.c\n");
				printf("MF_A[%i] = %i\n", N_A -1, i);
			#endif	
		} 
		if ( B_Norm > MF_X[i][0] && B_Norm < MF_X[i][2] )
		{
			MF_B[N_B] = i;
			N_B++;

			#ifdef DEBUG
				printf("MF_B[%i] = %i\n", N_B -1, i);
				printf("\n");
			#endif
		}
	}
	
	#ifdef DEBUG		
		printf("DEBUG --- Line 65 -- Min_Fun.c\n");
		printf("N_A = %i	N_B = %i\n", N_A, N_B);
		printf("\n");
	#endif

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

		#ifdef DEBUG
			printf("DEBUG --- Line 96 --- Min_Fin.c\n");
			printf("Y_A[%i] = %f\n", i, Y_A[i]);
			printf("\n");
		#endif
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

		#ifdef DEBUG
			printf("DEBUG --- Line 128 --- Min_Fin.c\n");
			printf("Y_B[%i] = %f\n", i, Y_B[i]);
			printf("\n");
		#endif
	} 
	
	//------ On applique maintenant la matrice des règles ------//	
	for (i = 0; i < N_A; i++)
	{
		for (j = 0; j < N_B; j++)
		{
			MF_Min[count] = regle[MF_A[i]][MF_B[j]];
			Y_Min[count++] = min(Y_A[i], Y_B[j]);
		} 
	}
	
	#ifdef DEBUG
		printf("DEBUG --- Line 145 --- Min_Fun.c\n");
		for (i=0; i<count; i++)
		{
		printf("MF_Min[%i] = %i		Y_Min[%i] = %f\n", i, MF_Min[i], i, Y_Min[i]);
		}
		printf("\n");
		printf("N_Min = %i\n\n", count);
	#endif
		
	// On définit le nombre de MFs de sortie
	*N_Min = count;
  
	return 0;
}
