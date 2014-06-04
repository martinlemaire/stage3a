//---------------------------------------------------------------------------//
// Fichier      : MainAutoBench.c                                     	     //
// Auteur 	: LEMAIRE Martin                                             //
// Description	: Main qui va appeler la fonction AutoBench avec un nombre de//
//                points "NbPoints"² et avec tous les nombre de MFs compris  //
//                entre "MF_Start" et "MF_Stop".			     //
//		  On renvoie ensuite les temps de calculs pour chaque nombre //
//                de MF dans "Results/AutoBench.dat"                         //
//---------------------------------------------------------------------------//
// ./autoBench "MF_Start" "MF_Stop" "NbPoints"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/Functions.h"


//#define DEBUG

int main(int argc, char *argv[])
{
	// Initialisation compteurs
	int i,j;

	// instanciation variables temporaires
	int MF_Start = 1;
	int MF_Stop = 10;
	int NbPoints = 100;
	float time;

	if (argc > 3)
	{
		MF_Start = atoi(argv[1]);
		MF_Stop = atoi(argv[2]);
		NbPoints = atoi(argv[3]);
	} 
	// On gere le fichier
	FILE* fichier = NULL;
	fichier = fopen("Results/AutoBench.dat", "w+");
	fprintf(fichier, "#Nbr MFs\tNbr Points\tTps calcul\n");

	for(i = MF_Start; i<= MF_Stop; i++)
	{
		time = AutoBench(i, NbPoints, NbPoints);
		fprintf(fichier, "%i\t%i\t%f\n", i, NbPoints*NbPoints, time);
	}

	fclose(fichier);
	
	return 0;
}

