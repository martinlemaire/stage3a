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

