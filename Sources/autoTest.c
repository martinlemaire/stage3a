//---------------------------------------------------------------------------//
// Fichier      : autoTest.c                                                 //
// Auteur       : LEMAIRE Martin                                             //
// Description  : TO DO                                                      //
//---------------------------------------------------------------------------//
// Prototypefonction : ./autoTest "fichierLib" "fichierExp" "fichierVal" "retro"(ou rien) "log"(ou rien) "fichierLog"(ou rien)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "../Headers/Fuzzy.h"
#include "../Headers/Functions.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

//#define DEBUG

int main(int argc, char *argv[])
{
	// ---------------- Instanciations des variables, tableaus, matrices ...-------------//

	// Instanciations variables
	int i, j, k, l, m, x, y;
	int Taille = 0; 
	int NbSynth = 0;
	int NbBond = 0;
  int NbGfp = 0;
	int xRange = 0;
  int yRange = 0;
	float MinX, MinY, MinZ;
	float MaxX, MaxY, MaxZ;
	float Min, Max;
	float MseMin = INFINITY;
	int indSynth0, indSynth1, indBond0, indBond1, indGfp;
	float A, B, Ae, Be, GFP, Centroide;
	clock_t time;

	// On prend le temps au début du programme 
	time = clock();

	// Instanciatiin d'une structure pour renter les points expermientaux
	typedef struct
	{
		float x; 
		float y;
		float z;
	}Point;	

	FILE* fichierLib = NULL;
	if (argc > 1)
	{
		fichierLib = fopen (argv[1], "r");
		if (fichierLib != NULL)
			fscanf(fichierLib, "%i\n\n%i\t%i\t%i\n", &Taille, &NbSynth, &NbBond, &NbGfp);
		else 
		{
			printf("erreur fichierLib\n");
			return -1;
		}
	}	

	FILE* fichierExp = NULL;
	if (argc > 2)
	{
		fichierExp = fopen(argv[2], "r");
		if (fichierExp != NULL)
			fscanf(fichierExp, "%i\t%i\n", &xRange, &yRange);
		else
		{
			printf("erreur fichierExp\n");
			return -1;	
		}
	}
	
	FILE* fichierVal = NULL;
	if (argc > 3)
	{
		fichierVal = fopen(argv[3], "w+");
		if (fichierVal != NULL)
		 fprintf(fichierVal, "#X\tY\tZ\n");
		else 
		{
			printf("erreur fichierVal\n");
		}
	}
	
	FILE* fichierLog = NULL;
	if(argc > 5 && !(strcmp(argv[5], "log")))
	{
		if(argc > 6)
  	{
  		fichierLog = fopen(argv[6], "w+");
			if (fichierLog != NULL)
				fprintf(fichierLog, "-------------- Fichier Log --------------\nAppel commande : %s %s %s %s %s %s %s\n\n\n", argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]); 
  	}
	}
	if(argc > 4 && !(strcmp(argv[4], "log")))
	{
		if(argc > 5)
  	{
  		fichierLog = fopen(argv[5], "w+");
			if (fichierLog != NULL)
				fprintf(fichierLog, "-------------- Fichier Log --------------\nAppel commande : %s %s %s %s %s %s \n\n\n", argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]); 
  	}
	}

	// Instanciation d'un tableau de matrice de regles pour Synth, Bond et GFP
	int** TabSynth = NULL;
	TabSynth = malloc(sizeof(int*)*NbSynth);
	for(i=0; i<NbSynth; i++)
	{
		TabSynth[i] = malloc(sizeof(int)*Taille);
	}

	int*** TabBond = NULL;
	TabBond = malloc(sizeof(int**)*NbBond);
	for(i=0; i<NbBond; i++)
	{
		TabBond[i] = malloc(sizeof(int*)*Taille);
		for(j=0; j<Taille; j++)
		{
			TabBond[i][j] = malloc(sizeof(int)*Taille);
		}
	}
		
	int*** TabGfp = NULL;
	TabGfp = malloc(sizeof(int**)*NbGfp);
	for(i=0; i<NbGfp; i++)
	{
		TabGfp[i] = malloc(sizeof(int*)*Taille);
		for(j=0; j<Taille; j++)
		{
			TabGfp[i][j] = malloc(sizeof(int)*Taille);
		}
	}

	// Instanciation d'une matrice de "Points" pour rentrer les points experimentaux
	Point** TabExp = NULL;
	TabExp = malloc(sizeof(Point*)*xRange);
	for(i=0; i<xRange; i++)
		TabExp[i] = malloc(sizeof(Point)*yRange);

	// Instanciation d'une énorme matrice de float pour rentrer les résultats 
	float***** TabResults = NULL;
	TabResults = malloc(sizeof(float****)*NbSynth);
	for(i=0; i<NbSynth; i++)
	{
		TabResults[i] = malloc(sizeof(float***)*NbSynth);
		for(j=0; j<NbSynth; j++)
		{
			TabResults[i][j] = malloc(sizeof(float**)*NbBond);
			for(k=0; k<NbBond; k++)
			{
				TabResults[i][j][k] = malloc(sizeof(float*)*NbBond);
				for(l=0; l<NbBond; l++)
				{
					TabResults[i][j][k][l] = malloc(sizeof(float)*NbGfp);
					for(m=0; m<NbGfp; m++)
						TabResults[i][j][k][l][m] = 0;
				}
			}
		}
	}

	// Instanciation d'une matrice pour les MFs
	float** MF_X = NULL;
	MF_X = malloc(sizeof(float*)*Taille);
	for(i=0; i<Taille; i++)
		MF_X[i] = malloc(sizeof(float)*3);

	// ---------- Lecture du fichier "Librairie" et écriture dans les variables ---------//
	
	// Synth 
	for(i=0; i<NbSynth; i++)
	{
		for(j=0; j<Taille; j++)
		{
			fscanf(fichierLib, "%i\t", &TabSynth[i][j]);	
		}
		fscanf(fichierLib, "\n");
	}
	// Bond
	for(i=0; i<NbBond; i++)
	{
		for(j=0; j<Taille*Taille; j++)
		{
			fscanf(fichierLib, "%i\t", &TabBond[i][(int)(j/Taille)][j % Taille]);	
		}
		fscanf(fichierLib, "\n");
	}
	// GFP	
	for(i=0; i<NbGfp; i++)
	{
		for(j=0; j<Taille*Taille; j++)
		{
			fscanf(fichierLib, "%i\t", &TabGfp[i][(int)(j/Taille)][j % Taille]);	
		}
		fscanf(fichierLib, "\n");
	}
	// MF_X
	for(i=0; i<Taille; i++)
		fscanf(fichierLib, "%f\t%f\t%f\n", &MF_X[i][0], &MF_X[i][1], &MF_X[i][2]);
	// --------- Lecture du fichier experimental et écriture dans la structure -------- //
	
	// Minimisation et maximisation des variables temp pour la normalisation
	MinX = INFINITY;
	MinY = INFINITY;
	MinZ = INFINITY;
	MaxX = -1*INFINITY;
	MaxY = -1*INFINITY;
	MaxZ = -1*INFINITY;
	// Lecture de valeurs et récuparation des valeurs Min et Max selon X, Y et Z
	for(i=0; i<xRange; i++)
	{
		for(j=0; j<yRange; j++)
		{		
			fscanf(fichierExp,"%f\t%f\t%f\n", &(TabExp[i][j].x), &(TabExp[i][j].y), &(TabExp[i][j].z));

			if(TabExp[i][j].x < MinX)
				MinX = TabExp[i][j].x;
			else if (TabExp[i][j].x > MaxX)
				MaxX = TabExp[i][j].x;
			if(TabExp[i][j].y < MinY)
				MinY = TabExp[i][j].y;
			else if (TabExp[i][j].y > MaxY)
				MaxY = TabExp[i][j].y;
			if(TabExp[i][j].z < MinZ)
				MinZ = TabExp[i][j].z;
			else if (TabExp[i][j].z > MaxZ)
				MaxZ = TabExp[i][j].z;
		}
	}

	// ------ DEBUG ------ //
	//printf("------ DEBUG ------\n\n");

	// Normalisation des valeurs
  for(i=0; i<xRange; i++)
	{
		for(j=0; j<yRange; j++)
		{
			TabExp[i][j].x = max(( log(TabExp[i][j].x) - log(MinX) )/( log(MaxX) - log(MinX) ),0);
			TabExp[i][j].y = max(( log(TabExp[i][j].y) - log(MinY) )/( log(MaxY) - log(MinY) ),0);
			TabExp[i][j].z = max(( log(TabExp[i][j].z) - log(MinZ) )/( log(MaxZ) - log(MinZ) ),0);
	//		printf("TabExp[%i][%i].x = %f\tTabExp[%i][%i].y = %f\tTabExp[%i][%i].z = %f\n", i, j, TabExp[i][j].x, i, j, TabExp[i][j].y, i, j, TabExp[i][j].z);
		}
	}
	
	

	// ---------- On récupere les valeurs de normalisation pour l'appel de Fuzzy --------//
	NormalValues(Taille, MF_X, &Min, &Max);

	// --------- On envoie les lourds calculs pour la porte XOR :'( ------------- //

	for(x=0; x<xRange; x++)
	{
		for(y=0; y<yRange; y++)
		{
			for(i=0; i<NbSynth; i++)
			{
				for(j=0; j<NbSynth; j++)
				{
				#ifdef DEBUG
					fprintf(fichierLog, "----- DEBUG ----- Line 237 ----- autoTest.c\n");
					fprintf(fichierLog, "x = %i\ty = %i\ti = %i\tj = %i\nTabExp[%i][%i].x = %f\tTabExp[%i][%i].y = %f\n", x, y, i, j, x, y, TabExp[x][y].x, x, y, TabExp[x][y].y);
				#endif
				A = Synth(TabSynth[i], Taille, MF_X, TabExp[x][y].x, "Min", "Max");
				A = Normalisation(A, Min, Max);
				
				B = Synth(TabSynth[j], Taille, MF_X, TabExp[x][y].y, "Min", "Max");
				B = Normalisation(B, Min, Max);
				#ifdef DEBUG
					fprintf(fichierLog, "----- DEBUG ----- Line 246 ----- autoTest.c\n");
					fprintf(fichierLog, "A = %f\tB = %f\n", A, B);
				#endif
					for(k=0; k<NbBond; k++)
					{
						for(l=0; l<NbBond; l++)
						{
							#ifdef DEBUG
								fprintf(fichierLog, "----- DEBUG ----- Line 254 ----- autoTest.c\n");
								fprintf(fichierLog, "k = %i\tl = %i\n", k, l);
							#endif

							Ae = Fuzzy(TabBond[k], Taille, MF_X, A, B, "Min", "Max");
							Be = Fuzzy(TabBond[l], Taille, MF_X, A, B, "Min", "Max");

							#ifdef DEBUG
								fprintf(fichierLog, "----- DEBUG ----- Line 260 ----- autoTest.c\n");
								fprintf(fichierLog, "Ae = %f\tBe = %f\n", Ae, Be);
							#endif

							if(argc > 4 && !(strcmp(argv[4],"retro")))
							{
								Be = max(B - Normalisation(Be, Min, Max),0);
								Ae = max(A - Normalisation(Ae, Min, Max),0);
							}
							else 
							{
								Be = Normalisation(Be, Min, Max);
								Ae = Normalisation(Ae, Min, Max);
							}

							#ifdef DEBUG
								fprintf(fichierLog, "----- DEBUG ----- Line 276 ----- autoTest.c\n");
								fprintf(fichierLog, "Ae_Norm = %f\tBe_Norm = %f\n", Ae, Be);
							#endif

							for(m=0; m<NbGfp; m++)
							{
									#ifdef DEBUG
										fprintf(fichierLog, "----- DEBUG ----- Line 285 ----- autoTest.c\n");
										fprintf(fichierLog, "m = %i\n", m);
									#endif
									GFP = Fuzzy(TabGfp[m], Taille, MF_X, Ae , Be , "Min", "Max");
									GFP = Normalisation(GFP, Min, Max);
									#ifdef DEBUG
										fprintf(fichierLog, "----- DEBUG ----- Line 291 ----- autoTest.c\n");
										fprintf(fichierLog, "GFP = %f\n", GFP);
									#endif
									TabResults[i][j][k][l][m] += (GFP - TabExp[x][y].z)*(GFP - TabExp[x][y].z);
									#ifdef DEBUG
										fprintf(fichierLog, "-----DEBUG ----- Line 296 ----- autoTest.c\n");
										fprintf(fichierLog, "TabResults[%i][%i][%i][%i][%i] = %f\n", i, j, k, l, m, TabResults[i][j][k][l][m]);
									#endif
							}
						}
					}
				}
			}
		}	
	}

	// ------------ On récupere la plus petite valeur du tableau TabResults ------------//

	for(i=0; i<NbSynth; i++)
		for(j=0; j<NbSynth; j++)
			for(k=0; k<NbBond; k++)
				for(l=0; l<NbBond; l++)
					for(m=0; m<NbGfp; m++)
						if(TabResults[i][j][k][l][m] < MseMin)
						{
							MseMin = TabResults[i][j][k][l][m];
							indSynth0 = i; 
							indSynth1 = j;
							indBond0 = k;
							indBond1 = l;
							indGfp = m;
						}
						
	time = clock() - time;	

	// -------- Si demandé, on sort la surface des regles du champion --------//

	for(i=0; i<xRange; i++)
	{
		for(j=0; j<yRange; j++)
		{
				
			A = Synth(TabSynth[indSynth0], Taille, MF_X, TabExp[i][j].x, "Min", "Max");
			A = Normalisation(A, Min, Max);

			B = Synth(TabSynth[indSynth1], Taille, MF_X, TabExp[i][j].y, "Min", "Max");
			B = Normalisation(B, Min, Max);
			
			Ae = Fuzzy(TabBond[indBond0], Taille, MF_X, A, B, "Min", "Max");
			Be = Fuzzy(TabBond[indBond1], Taille, MF_X, B, A, "Min", "Max");

			if(argc > 4 && !(strcmp(argv[4],"retro")))
			{
				Be = max(B - Normalisation(Be, Min, Max),0);
				Ae = max(A - Normalisation(Ae, Min, Max),0);
			}
			else 
			{
				Be = Normalisation(Be, Min, Max);
				Ae = Normalisation(Ae, Min, Max);
			}

			GFP = Fuzzy(TabGfp[indGfp], Taille, MF_X, Ae, Be, "Min", "Max");
			GFP = Normalisation(GFP, Min, Max);

			fprintf(fichierVal, "%f\t%f\t%f\n", TabExp[i][j].x, TabExp[i][j].y, GFP);
		}
		fprintf(fichierVal, "\n");
	}

	// ------- Affichage des résultats ------- //
	
	printf("MseMin = %f avec : \n indSynth0 = %i\n indSynth1 = %i\n indBond0 = %i\n indBond1 = %i\n indGfp = %i\n\n", sqrt(MseMin/(xRange*yRange)), indSynth0, indSynth1, indBond0, indBond1, indGfp);
	printf("Le calcul	a pris %f secondes\n\n", ((float)time)/CLOCKS_PER_SEC);

	// On libère la mémoire
	
	for(i=0; i<xRange; i++)
		free(TabExp[i]);
	free(TabExp);

	for (i = 0; i<Taille; i++)
		free(MF_X[i]);
	free(MF_X);

	if(fichierLib != NULL)
		fclose(fichierLib);
	if(fichierExp != NULL)
		fclose(fichierExp);
	if(fichierVal != NULL)
		fclose(fichierVal);
	if(fichierLog != NULL)
		fclose(fichierLog);	

	for(i=0; i< NbSynth; i++)
		free(TabSynth[i]);
	free(TabSynth);

	for(i=0; i < NbBond; i++)
	{
		for(j=0; j<Taille; j++)
		{
			free(TabBond[i][j]);
		}
		free(TabBond[i]);
	}
	free(TabBond);
	
	for(i=0; i<NbGfp; i++)
	{
		for(j=0; j<Taille; j++)
		{
			free(TabGfp[i][j]);
		}
		free(TabGfp[i]);
	}
	free(TabGfp);	

	for(i=0; i<NbGfp; i++)
	{
		for(j=0; j<NbBond; j++)
		{
			for(k=0; k<NbBond; k++)
			{
				for(l=0; l<NbSynth; l++)
				{
					free(TabResults[i][j][k][l]);
				}
				free(TabResults[i][j][k]);
			}
			free(TabResults[i][j]);
		}
		free(TabResults[i]);
	}	
	free(TabResults);

	return 0;
} 
