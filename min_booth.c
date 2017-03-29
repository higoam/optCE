
    #include "math2.h"
    #define p 10000
    int nondet_int();
    float nondet_float();

	int main() {

		float f_i = 0.000000 -1e-05;

		int x[3], i;
		float X[3];
		float fobj;

 		int lim[4] = { 99990, 100010, 299990, 300010 };

		for (i = 0; i<2; i++){
			x[i] = nondet_int();
			X[i] = nondet_float();
		}

		for (i = 0; i<2; i++){
			__ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );
			__ESBMC_assume( X[i] == (float) x[i]/p	);
		}

		fobj = (X[0] + 2*X[1] -7)*(X[0] + 2*X[1] -7) + (2*X[0] + X[1] -5)*(2*X[0] + X[1] -5);

		__ESBMC_assume(fobj < f_i );

		assert(fobj > f_i);

		return 0;
	}
