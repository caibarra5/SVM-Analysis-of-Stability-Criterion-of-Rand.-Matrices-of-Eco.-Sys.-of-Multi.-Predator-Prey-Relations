#include "general.h"
#include <omp.h>
void randomParams(int N_L,int N_U,int *ptrN,double d_L,double d_U,double *ptrd,double delta_L,double delta_U,double *ptrdelta, double C_L, double C_U, double *ptrC, double sigma_L, double sigma_U, double *ptrsigma);

void GenerateM(double** pptrM, int N, double d, double delta, double C, double sigma);

extern void dgeev_(char*,char*,int*,double*,int*,double*,double*,double*,int*,double*,int*,double*, int*,int*);

int examineEigensReal(double *b, int N);



int main(int argc, char** argv){

	// Data generation parameters
	int N_L;
	int N_U;

	double d_L;
	double d_U;

	double delta_L;
	double delta_U;

	double C_L;
	double C_U;

	double sigma_L;
	double sigma_U;

	int Nmc;

	double etha_s;

	int N1;

	int N2;



	FILE *fp0;
	fp0 = fopen("parameters.txt","r");

	fscanf(fp0,"%d",&N_L);
	fscanf(fp0,"%d",&N_U);

	fscanf(fp0,"%lf",&d_L);
	fscanf(fp0,"%lf",&d_U);

	fscanf(fp0,"%lf",&delta_L);
	fscanf(fp0,"%lf",&delta_U);

	fscanf(fp0,"%lf",&C_L);
	fscanf(fp0,"%lf",&C_U);

	fscanf(fp0,"%lf",&sigma_L);
	fscanf(fp0,"%lf",&sigma_U);

	fscanf(fp0,"%d",&Nmc);

	fscanf(fp0,"%lf",&etha_s);

	fscanf(fp0,"%d",&N1);

	fscanf(fp0,"%d",&N2);

	fclose(fp0);



	FILE *fp1;
	fp1 = fopen("training_set.txt","w");


	for(int p =0; p < N1; p++){

		double nmbrStable = 0; // Counter
		double proportion = 0;
		

		// Direct control parameters
		int N;
		double d;
		double delta;
		double C;
		double sigma;
		int t;	// Output parameter
		randomParams(N_L,N_U,&N,d_L,d_U,&d,delta_L,delta_U,&delta,C_L,C_U,&C,sigma_L,sigma_U,&sigma);
	
		#pragma omp parallel
		{

			int mynmbrStable = 0;

			#pragma omp for
			for(int k = 0; k < Nmc; k++){
		
				// Create Community Matrix
			
				double *ptrM;
			
				GenerateM(&ptrM,N,d,delta,C,sigma);
			
			
				// Using lapack function dgeev_() to solve for eigenvalues of community matrix M.
			
			
				char JOBVL = 'N';
				char JOBVR = 'N';
				int LDA = N;
				double *ptrEvalsR = malloc(N * sizeof(double)); // For determining stability
				double *ptrEvalsI = malloc(N *  sizeof(double));
				double *VL = malloc(N *  sizeof(double));
				int LDVL = N;
				double *VR = malloc(N *  sizeof(double));
				int LDVR = N;
				double *WORK = malloc(4 * N *  sizeof(double));
				int LWORK = 4 * N;
				int infor;
			
				dgeev_(&JOBVL,&JOBVR,&N,ptrM,&N,ptrEvalsR,ptrEvalsI,VL,&LDVL,VR,&LDVR,WORK,&LWORK,&infor);
				
				
				int add = examineEigensReal(ptrEvalsR, N);
		
			
				free(ptrM);
				free(ptrEvalsR);
				free(ptrEvalsI);
				free(VL);
				free(VR);
				free(WORK);
	
				mynmbrStable = mynmbrStable + add;
			}

		#pragma omp critical
		{
			nmbrStable = nmbrStable + mynmbrStable;

		}
		}	
		proportion = nmbrStable/Nmc;
	
		if(proportion >= etha_s){
	
			t = 1;
		}else{
			t = -1;
		}

		fprintf(fp1,"%d %f %f %f %f %d\n",N,d,delta,C,sigma,t);
		
		
	}

	fclose(fp1);


	FILE *fp2;
	fp2 = fopen("testing_set.txt","w");


	for(int p =0; p < N2; p++){

		double nmbrStable = 0; // Counter
		double proportion = 0;
		

		// Direct control parameters
		int N;
		double d;
		double delta;
		double C;
		double sigma;
		int t;	// Output parameter
		randomParams(N_L,N_U,&N,d_L,d_U,&d,delta_L,delta_U,&delta,C_L,C_U,&C,sigma_L,sigma_U,&sigma);
	
		#pragma omp parallel
		{

			int mynmbrStable = 0;

			#pragma omp for
			for(int k = 0; k < Nmc; k++){
		
				// Create Community Matrix
			
				double *ptrM;
			
				GenerateM(&ptrM,N,d,delta,C,sigma);
			
			
				// Using lapack function dgeev_() to solve for eigenvalues of community matrix M.
			
			
				char JOBVL = 'N';
				char JOBVR = 'N';
				int LDA = N;
				double *ptrEvalsR = malloc(N * sizeof(double)); // For determining stability
				double *ptrEvalsI = malloc(N *  sizeof(double));
				double *VL = malloc(N *  sizeof(double));
				int LDVL = N;
				double *VR = malloc(N *  sizeof(double));
				int LDVR = N;
				double *WORK = malloc(4 * N *  sizeof(double));
				int LWORK = 4 * N;
				int infor;
			
				dgeev_(&JOBVL,&JOBVR,&N,ptrM,&N,ptrEvalsR,ptrEvalsI,VL,&LDVL,VR,&LDVR,WORK,&LWORK,&infor);
				
				
				int add = examineEigensReal(ptrEvalsR, N);
		
			
				free(ptrM);
				free(ptrEvalsR);
				free(ptrEvalsI);
				free(VL);
				free(VR);
				free(WORK);
	
				mynmbrStable = mynmbrStable + add;
			}

		#pragma omp critical
		{
			nmbrStable = nmbrStable + mynmbrStable;

		}
		}	
		proportion = nmbrStable/Nmc;
	
		if(proportion >= etha_s){
	
			t = 1;
		}else{
			t = -1;
		}

		fprintf(fp2,"%d %f %f %f %f %d\n",N,d,delta,C,sigma,t);
		
		
	}

	fclose(fp2);



	return 0;


}
