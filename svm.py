#!/usr/bin/env python3
import py_readdata as pr
import numpy as np
import math as mt
import cvxopt

# Reading Training Data
inParas,outPara = pr.read_data("./training_set.txt");

x = np.zeros((len(inParas),len(inParas[0])));
row_idx = 0;
for data in inParas:
	x[row_idx,:] = np.asarray(data);
	row_idx += 1;
x = np.asarray(x);
t = np.asarray(outPara);
n = len(outPara);
t = t.reshape(n,1);
C = 0.5
q = -np.ones((n,1));



def Kernel(x,y):
	dot_product = np.dot(x,y);


	result = (1 + dot_product)**2;

	return result;

# kernel matrix as an ndarray
K = np.zeros((n,n))
for i in range(0,n):
  for j in range(0,n):
    K[i,j] = Kernel(x[i,:],x[j,:])


P = t*np.transpose(t)*K;

A = t.reshape(1,n);

b = 0.;

G = np.concatenate((np.eye(n),-np.eye(n)));

h = np.concatenate((C*np.ones((n,1)),np.zeros((n,1))));

Lambda = cvxopt.solvers.qp(cvxopt.matrix(P),cvxopt.matrix(q),cvxopt.matrix(G),cvxopt.matrix(h),cvxopt.matrix(A),cvxopt.matrix(b))['x'];



b_hat = 0.
ztol = 1e-10
n_nz = 0
for i in range(0,n):
  if C > Lambda[i] > ztol:
    n_nz += 1
    b_hat += t[i];
    for j in range(0,n):
      b_hat -= Lambda[j] * t[j] * K[j,i]
b_hat /= n_nz

def L(x_test_i,x,Lambda,t,Kernel,b_hat):

	result = 0;
	for i in range(len(t)):
		result = result + Lambda[i]*t[i]*Kernel(x[i,:],x_test_i);
	return result + b_hat


# Reading Testing Data
inParas_test,outPara_test = pr.read_data("./testing_set.txt");

x_test = np.zeros((len(inParas_test),len(inParas_test[0])));
row_idx = 0;
for data in inParas_test:
	x_test[row_idx,:] = np.asarray(data);
	row_idx += 1;
x_test = np.asarray(x_test);
t_test = np.asarray(outPara_test);
n_test = len(outPara_test);
t_test = t_test.reshape(n_test,1);



result = [];

for i in range(len(t_test)):

	result.append(L(x_test[i,:],x,Lambda,t,Kernel,b_hat));


counter = 0;
for i in range(len(result)):

#	print(t_test[i]," ",result[i])

#	if (result[i] > 0 and t_test[i] > 0) or (result[i] < 0 and t_test[i] < 0):
	if result[i]/t_test[i] >0:
		counter = counter +1;

counter = float(counter)
n_test = float(n_test)


#print("counter = ",type(counter))
#print("n_test = ",type(n_test))

fraction = counter/n_test;
print("score of classifier: ",fraction)
