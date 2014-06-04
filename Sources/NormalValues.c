//---------------------------------------------------------------------------//
// Fichier      : NormalValues.c                                       	     //
// Auteur 	: LEMAIRE Martin                                             //
// Description	: Fonction qui en recevant le profil des MFs et leur nombre  //
//                va définir les valeurs Max et Min pouvant etre prise en    //
//                calculant un point Fuzzy.				     //
//---------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>

#define K_Tri 0.292893218813

int NormalValues(int TAILLE, float** MF_X, float* Min, float* Max)
{

	*Min = K_Tri*(MF_X[0][2] - MF_X[0][1]);
	*Max = (1 - K_Tri)*(MF_X[TAILLE -1][1] - MF_X[TAILLE -1][0]) + MF_X[TAILLE -1][0];

	return 0;
} 
