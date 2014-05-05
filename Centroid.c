#include <stdio.h>
#include <stdio.h>

#define K_Tri 0.292893218813

//#define DEBUG

#define Dx	(X_Max[i+1] - X_Max[i])
#define Dy	(Y_Max[i+1] - Y_Max[i])
#define X0	X_Max[i]


float Centroid(float* X_Max, float* Y_Max, int N_Max)
{
	// Instanciation compteurs 
	int i = 0;

	// Instanciation variables temporaires
	float Centro_Temp = 0.0;
	float Area = 0.0;
	float Centro_Tot = 0.0;
	float Area_Tot = 0.0;
	float Centroid = 0.0;
	
	// On calcule area et centroide de chaque petite zone et on commence a sommer le tout
	for(i=0; i<N_Max-1; i++)
	{
		if(Y_Max[i] > Y_Max[i+1])
		{
			Area = (Dx*Y_Max[i+1]) + (Dx*(-1*Dy))/2;
			Centro_Temp = X0 + (K_Tri*Dx*Dx*(-1*Dy) + Dx*Dx*Y_Max[i+1])/(2*Area);
		}
		else if(Y_Max[i] < Y_Max[i+1])
		{	
			Area = (Dx * Y_Max[i]) + (Dx * Dy)/2;
			Centro_Temp = X0 + ((1 - K_Tri)*Dx*Dx*Dy + Dx*Dx*Y_Max[i])/(2*Area); 
		}
		else if(Y_Max[i] == Y_Max[i+1])
		{
			Area = (X_Max[i+1] - X_Max[i]) * Y_Max[i];
			Centro_Temp = (X_Max[i+1] - X_Max[i])/2 + X_Max[i];
		}

		#ifdef DEBUG
			printf("DEBUG --- Line 39 iteration %i\n", i);
			printf("Centro_Temp = %f		Area = %f\n\n", Centro_Temp, Area);
		#endif
	
		Centro_Tot += Centro_Temp * Area;
		Area_Tot += Area;
	}
	#ifdef DEBUG
		printf("DEBUG --- Line 42:\n");
		printf("Centro_Tot = %f		Area_Tot = %f\n\n", Centro_Tot, Area_Tot);
	#endif
	
	// On calcule le centroide total
	Centroid = Centro_Tot / Area_Tot;
	
	return Centroid;
}
