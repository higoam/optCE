#define p 100
#include "math2.h"
int nondet_int();
float nondet_float();

	int main() {

		
		float f_i =  -1e-05;

		int x[3], i;
		float X[2];
		float fobj;

		int lim[4] = {-5*p, 10*p, -5*p, 10*p};

		for (i = 0; i<2; i++){
			x[i] = nondet_int();
			X[i] = nondet_float();
		}

		for (i = 0; i<2; i++){
			__ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );
			__ESBMC_assume( X[i] == (float) x[i]/p	);
		}

		fobj = (X[0]*X[0] + X[1]*X[1] -2*X[0])*(X[0]*X[0] + X[1]*X[1] -2*X[0]) + 0.25*X[0];


		__ESBMC_assume(fobj < f_i );

		assert(fobj > f_i);
		return 0;
	}
