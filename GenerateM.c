#include "general.h"
#include <omp.h>

void DiagRandomNormal(double mean, double stdDev, double* X, double* Y);
void RandomNormal(double mean, double stdDev, double* pos, double* neg);

void GenerateM(double** pptrM, int N, double d, double delta, double sigma, double C){

	//M_ii ~ N(-d,delta^2)
	//For all i < j
	//	with possibility C/2 generate M_ij ~ |N(0,sigma^2)| and M_ji ~ -|N(0,sigma^2)|
	//	with possibility C/2 generate M_ij ~ -|N(0,sigma^2)| and M_ji ~ |N(0,sigma^2)|
	//	with possibility 1 - C set M_ij = M_ji = 0
	//
	//0< C <1 are in predator-prey relation
	//0< 1-C <1 not in one
	//d = order of magnitude of r_i x Y*_i/K_i, delta = it's small variation
	//C = proportion of predator-prey pairs among all
	//sigma = order of magnitude of alpha_ij x Y*_i
	


	// M is an N by N matrix. Here, the memory space for M is allocated with malloc().

	*pptrM = (double*) malloc( N * N * sizeof(double) );
	
	// Generate values for M_ii
	double dummy;//in case N is not even, for RandomNormal() generates two random variables from a normal distribution at a time
	

	for(int i = 0; i < N; i++){
	//	k = i;
		DiagRandomNormal(-d,delta,  *pptrM + N*i + i  ,  &dummy  );
	}


	// Here we need to use the value of C to determine the rest of the elements for i=/=j.
	// We do this by noting that 0 <= C <= 1.
	// As such, we get a random number form a unifrom distribution using rand(), afterwards, we divide that number by RAND_MAX and 
	// store the value in u.
	
	double u;
	for(int j = 0; j < N; j++){
		
		for(int i = 0; i < j; i++){

			u = (double) rand()/RAND_MAX;
			
			if(u < C/2){

				RandomNormal(0,sigma,  *pptrM + i*N + j, *pptrM + j*N + i);
			}


			else if(u < C){

				RandomNormal(0,sigma,  *pptrM + j*N + i, *pptrM + i*N + j);
			}

			else{
				*(*pptrM + j*N + i) = 0;
				*(*pptrM + i*N + j) = 0;
			}
		}
	}


}
