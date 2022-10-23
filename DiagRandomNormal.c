#include <stdlib.h>
#include <math.h>

void DiagRandomNormal(double mean, double stdDev,double* X, double* Y){

	// Generate two random numbers from a normal distribution and store them
	// in the address pointed at by the pointers X and Y


	double x,y,s;

	do{
		x = 2.0*(-0.5 + ((double) rand()/RAND_MAX));
		y = 2.0*(-0.5 + ((double) rand()/RAND_MAX));
		s = x * x + y * y;
	}
	while( s>=1.0 || s==0.0);

	double tmp = sqrt(-2.0*log(s)/s);

	*X = x * tmp;
	*Y = y * tmp;

	// Here we are using the method of scaling and shifting. 
	// Using the mean and the standard deviation (stdDev), we can get a random number from the distribution
	// with mean (mean) and variance (stdDev^2) such that
	// (mean + stdDev * *X) and (mean + stdDev * *Y) are members of N(mean,stdDev^2)

	*X = mean + stdDev * *X;
	*Y = mean + stdDev * *Y;
}
