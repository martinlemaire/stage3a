#include <stdio.h>
#include <stdlib.h>

float Normalisation(float Centroid_IN, float Min, float Max)
{
	return (Centroid_IN - Min)/(Max - Min);
}
