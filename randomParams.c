#include <stdlib.h>
#include <math.h>

void randomParams(int N_L,int N_U,int *ptrN,double d_L,double d_U,double *ptrd,double delta_L,double delta_U,double *ptrdelta, double C_L, double C_U, double *ptrC, double sigma_L, double sigma_U, double *ptrsigma){


	// Random integer assigned to *ptrN between N_L and N_U 
	double N_C = N_U - N_L;
	*ptrN = (int)((double)rand()/RAND_MAX*N_C) + N_L;


	// Random integer assigned to *ptrd between d_L and d_U 
	double d_C = d_U - d_L;
	*ptrd = (((double)rand()/RAND_MAX)*d_C) + d_L;


	// Random integer assigned to *ptrdelta between delta_L and delta_U 
	double delta_C = delta_U - delta_L;
	*ptrdelta = (((double)rand()/RAND_MAX)*delta_C) + delta_L;


	// Random integer assigned to *ptrC between C_L and C_U 
	double C_C = C_U - C_L;
	*ptrC = (((double)rand()/RAND_MAX)*C_C) + C_L;


	// Random integer assigned to *ptrsigma between sigma_L and sigma_U 
	double sigma_C = sigma_U - sigma_L;
	*ptrsigma = (((double)rand()/RAND_MAX)*sigma_C) + sigma_L;
}
