#include <stdlib.h>
#include <stdio.h>

int main( int argc, char *argv[])
{
	// Instanciation variables
	int i, j ;		
	FILE* fichierLu = NULL;
	FILE* fichierEcrit = NULL;
	float X_Temp, Z_Temp;
	int NbSerie = 0;	

	if (argc > 3)
	{
		NbSerie = atoi(argv[3]);		
		fichierLu = fopen(argv[1], "r");
		fichierEcrit = fopen(argv[2], "w+");

		float* tabY = NULL;
		tabY = malloc(sizeof(float)*NbSerie);

		fprintf(fichierEcrit, "%i\t%i\n", NbSerie + 1, NbSerie );
		if (fichierLu != NULL && fichierEcrit != NULL)
		{
			for(i = 0; i<NbSerie+1; i++)
			{
				for(j = 0; j<NbSerie; j++)
				{
					if(i == 0)
					{
						fscanf(fichierLu,"%e\t%e\n", &tabY[j], &Z_Temp);
						fprintf(fichierEcrit,"%.15f\t%.15f\t%.15f\n",tabY[0], tabY[j], Z_Temp); 
					}
					else if (i == NbSerie)
					{
						fscanf(fichierLu,"%e\t%e\n", &X_Temp, &Z_Temp);
						fprintf(fichierEcrit,"%.15f\t%.15f\t%.15f\n",tabY[NbSerie-1] + tabY[1] - tabY[0], tabY[j], Z_Temp); 
					}
					else 
					{
						fscanf(fichierLu,"%e\t%e\n", &X_Temp, &Z_Temp);
						fprintf(fichierEcrit,"%.15f\t%.15f\t%.15f\n", tabY[i] ,X_Temp, Z_Temp); 
					}
				}
				//fprintf(fichierEcrit,"\n");				
			}
			fclose(fichierLu);
			fclose(fichierEcrit); 	
			free(tabY);
			tabY = NULL;
		}
		else 
		{
			printf("ERROR : Pas de fichier de ce nom\n");
			return 1;
		}
	}
}
