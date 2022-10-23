
def read_data(filename):
	with open(filename,mode='r')as f:
		lineno = 0;
		X = [];
		Y = [];
		for line in f:
			lineno += 1;
			x_par = ();
			pars = line.split();
			for i in range(len(pars)-1):
				x_par += (float(pars[i]),);
			X += [x_par];
			Y.append(float(pars[len(pars)-1]));
	return X,Y;
