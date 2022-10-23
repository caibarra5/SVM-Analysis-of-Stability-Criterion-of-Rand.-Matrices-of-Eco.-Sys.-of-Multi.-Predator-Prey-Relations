#include <stdlib.h>
#include <math.h>

void RandomNormal(double mean, double stdDev,double* pos, double* neg){

	// Generate two random numbers from a normal distribution


	double x,y,s;

	do{
		x = 2.0*(-0.5 + ((double) rand()/RAND_MAX));
		y = 2.0*(-0.5 + ((double) rand()/RAND_MAX));
		s = x * x + y * y;
	}
	while( s>=1.0 || s==0.0);

	double tmp = sqrt(-2.0*log(s)/s);

	*pos = x * tmp;
	*neg = y * tmp;

	// Here we are using the method of scaling and shifting. 
	// Using the mean and the standard deviation (stdDev), we can get a random number from the distribution
	// with mean (mean) and variance (stdDev^2) such that
	// (mean + stdDev * *X) is a member members of N(mean,stdDev^2)
	// However, for the purposes of populating the community matrix M,
	// We wil 

	*pos = mean + stdDev * *pos;
	*neg = mean + stdDev * *neg;

	if(*pos < 0){
		*pos = -*pos;
	}

	if(*neg > 0){
		*neg = -*neg;
	}
}
