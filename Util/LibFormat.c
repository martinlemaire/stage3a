#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	// Instanciations variables
	int i,j;
	int Taille;
	FILE* fichierIn = NULL;
	FILE* fichierOut = NULL;

	if(argc > 3 && !(strcmp(argv[1],"file")) )
	{
		fichierIn = fopen(argv[2], "r");
		if(fichierIn != NULL)
			fichierOut = fopen(argv[3], "w+");
		else 
		{
			printf("Mauvais fichier d'entrée");
			return -1;
		}
	
		if (fichierOut != NULL)
		{
			// On recupere le fichier d'entrée et on fait ce qu'on a a faire, mais pour l'instant on s'en fout...
		}
		else 
		{
			printf("Mauvais fichier de sortie");
			return -1;
		}
		fclose(fichierIn);	
	}
	else if(argc > 3 && !(strcmp(argv[1],"auto")) )
	{
		Taille = atoi(argv[2]);
		fichierOut = fopen(argv[3], "r+");
		if(fichierOut != NULL)
		{
			fseek(fichierOut, -1, SEEK_END); 
			float Q = 1.0/((float)Taille -1);
			fprintf(fichierOut, "\n%f\t%f\t%f\n", 0.0, 0.0, Q);
			for(i=1; i<Taille -1; i++)
			{
				fprintf(fichierOut, "%f\t%f\t%f\n", (i-1)*Q, Q*i, (i+1)*Q);
			} 
			fprintf(fichierOut, "%f\t%f\t%f\n", (Taille - 2)*Q, 1.0, 1.0);
		}
		else
		{
			printf("Mauvais fichier de sortie");
			return -1;
		}
	}
	
	// On libère la mémoire
	
	fclose(fichierOut);


	return 0;
}

