//---------------------------------------------------------------------------//
// File : Functions.h		Auteur : LEMAIRE Martin															 //
// 																																					 //
// Description : Header de toutes les fonctions utilisées										 //
//																																					 //
//---------------------------------------------------------------------------//



int MaxFun(int Taille, float** MF_X, int* MF_Min, float* Y_Min, int N_Min, float* X_Max, float* Y_Max, int* N_Max);

int Min_Fun(int TAILLE, int** regle, float A_Norm, float B_Norm, float** MF_X, int* MF_Min, float* Y_Min, int* N_Min);

float Centroid(float* X_Max, float* Y_Max, int N_Max);

int ProdFun(int TAILLE, int** regle, float A_Norm, float B_Norm, float** MF_X, int* MF_Prod, float* Y_Prod, int* N_Prod);

float CrossFun( float X_A, float Y_A, float X_B, float Y_B, float Y_C);

int NormalValues(int TAILLE, float** MF_X, float* Min, float* Max);

float Normalisation(float Centroid_IN, float Min, float Max);

float Synth(int* regle, int TAILLE, float** MF_X, float A_norm, char* And, char* Or);

int SynthMin(int TAILLE, int* regle, float A_Norm, float** MF_X, int* MF_Min, float* Y_Min, int* N_Min);

float AutoBench(int taille, int NbPointsA, int NbPointsB);
