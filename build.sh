
gcc main.c -fopenmp -lblas -llapack GenerateM.c randomParams.c examineEigensReal.c RandomNormal.c -lm DiagRandomNormal.c -lm -std=c99
