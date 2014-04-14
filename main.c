#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAILLE 3

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

int main()
{

    int regle[TAILLE][TAILLE] = { { 1 , 2 , 3 } , { 2 , 3 , 3 } , { 3 , 3 , 3 } };
    float A = 1*exp(-8);
    float A_min = 1*exp(-9);
    float A_max = 1*exp(-7);
    char A_scale[] = "log";
    float B = 0.1;
    float B_min = 0;
    float B_max = 1;
    char B_scale[] = "lin";


    float A_pourc = 0.0;
    float B_pourc = 0.0;
    float x_tri[TAILLE+2] = {0};
    int MF_A[2] = {0};
    int MF_B[2] = {0};
    int i = 0;
    int j = 0;
    int n = 0;
    int m = 0;
    int count = 0;

    if (strcmp(A_scale,"log") == 0)
    {
        A_pourc = (log(A)-log(A_min))/(log(A_max)-log(A_min));
    }
    else
    {
        A_pourc = (A-A_min)/(A_max-A_min);
    }


    if (strcmp(B_scale,"log") == 0)
    {
        B_pourc = (log(B)-log(B_min))/(log(B_max)-log(B_min));
    }
    else
    {
        B_pourc = (B-B_min)/(B_max-B_min);
    }

    printf("A_pourc = %f\n",A_pourc);
    printf("B_pourc = %f\n",B_pourc);

    for (i = 0 ; i < TAILLE+2 ; i++)
    {
        x_tri[i]=(i-1.0)/(TAILLE-1);
        printf("x_tri = %f\n",x_tri[i]);
    }

    for (i = 0 ; i < TAILLE ; i++)
    {
        if (A_pourc > x_tri[i] && A_pourc < x_tri[i+2])
        {
            MF_A[n]=i+1;
            n = n+1;
        }
        if (B_pourc > x_tri[i] && B_pourc < x_tri[i+2])
        {
            MF_B[m]=i+1;
            m = m+1;
        }
    }

    printf("MF_A[1] = %d\n",MF_A[0]);
    printf("MF_A[2] = %d\n",MF_A[1]);
    printf("MF_B[1] = %d\n",MF_B[0]);
    printf("MF_B[2] = %d\n",MF_B[1]);

    float out_x[4][4] = {{0}};
    float out_y[4][4] = {{0}};
    float partA_x = 0;
    float partB_x = 0;
    float Coo_x = 0;
    float ptA = 0;
    float ptB = 0;

    count = 0;

    for (i = 0 ; i < m ; i++)
    {
        for (j = 0 ; j < n ; j++)
        {
            partA_x = min(A_pourc-x_tri[MF_A[j]],x_tri[MF_A[j]+2]-A_pourc);
            partB_x = min(B_pourc-x_tri[MF_B[i]],x_tri[MF_B[i]+2]-B_pourc);

            printf("partA_x = %f\n",partA_x);
            printf("partB_x = %f\n",partB_x);

            out_x[count][0] = max(x_tri[regle[MF_B[i]][MF_A[j]]],0);
            out_x[count][1] = max((x_tri[regle[MF_B[i]][MF_A[j]]]+min(partA_x,partB_x)),0);
            out_x[count][2] = min((x_tri[regle[MF_B[i]][MF_A[j]]+2]-min(partA_x,partB_x)),1);
            out_x[count][3] = min(x_tri[regle[MF_B[i]][MF_A[j]]+2],1);

            printf("out_x[1] = %f\n",out_x[count][0]);
            printf("out_x[2] = %f\n",out_x[count][1]);
            printf("out_x[3] = %f\n",out_x[count][2]);
            printf("out_x[4] = %f\n",out_x[count][3]);
            if (out_x[count][1]==0)
            {
                Coo_x = -out_x[count][2];
            }
            else
            {
                Coo_x = out_x[count][1];
            }
            ptA = x_tri[regle[MF_B[i]][MF_A[j]]];
            ptB = x_tri[regle[MF_B[i]][MF_A[j]+1]];
            out_y[count][0] = 0.0;
            //out_y[count][1] = (Coo_x-ptA)/(ptB-ptA);
            //out_y[count][2] = out_y[count][1];
            out_y[count][3] = 0.0;
            count=count+1;
        }

    }

    for (i = 0 ; i < count ; i++)
    {
        printf("Output X num %d\n",i);
        printf("out_x[1] = %f\n",out_x[i][0]);
        printf("out_x[2] = %f\n",out_x[i][1]);
        printf("out_x[3] = %f\n",out_x[i][2]);
        printf("out_x[4] = %f\n",out_x[i][3]);
//        printf("Output Y num %d\n",i);
//        printf("out_y[1] = %f\n",out_y[i][0]);
//        printf("out_y[2] = %f\n",out_y[i][1]);
//        printf("out_y[3] = %f\n",out_y[i][2]);
//        printf("out_y[4] = %f\n",out_y[i][3]);
    }

    return 0;
}
