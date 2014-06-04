//------------------------------------------------------------------------//
// Fichier      : CrossFun.c                                           	  //
// Auteur 	: LEMAIRE Martin                                          //
// Description	: Fonction qui donne l'abcisse d'un point à               //
//                partir de l'ordonné de celui ci et de l'abcisse         //
//                et l'ordonnée de deux points sur la meme droite         //
//------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>

float CrossFun( float X_A, float Y_A, float X_B, float Y_B, float Y_C)
{
	float X_C = 0.0;

	if (X_A > X_B)
	{
		X_C = X_B + (Y_C - Y_B)*( (X_A - X_B)/(Y_A - Y_B) );
	}
	else if (X_B > X_A) 
	{
		X_C = X_A + (Y_C - Y_A)*( (X_B - X_A)/(Y_B - Y_A) );
	}
	else 
	{
		X_C = X_A;
	}
	
	return X_C; 
}
