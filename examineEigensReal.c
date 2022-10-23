#include <stdlib.h>
#include <math.h>

int examineEigensReal(double *b, int N){

	for(int i = 0; i < N; i++){

		if(*(b+i) > 0){

			return 0;
		}
	}

	return 1;
}
