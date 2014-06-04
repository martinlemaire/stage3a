//---------------------------------------------------------------------------//
// Fichier      : Normalisation.c                                      	     //
// Auteur 	: LEMAIRE Martin                                             //
// Description	: Fcontion qui en recevant les valeurs minimales et maximales//
//                (Min et Max) va normaliser la valeur "Centroid_IN"         //
//---------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>

float Normalisation(float Centroid_IN, float Min, float Max)
{
	float temp;

	temp = (Centroid_IN - Min)/(Max - Min);

	if(temp > 1.0)
		temp = 1.0;
	else if (temp < 0.0)
		temp = 0.0;

	return temp;
}
