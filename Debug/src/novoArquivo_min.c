#define p 1
#define n 2			// número de variáveis
#define nr 4		// número de restrições


#include <math.h>

	int nondet_int();
	float nondet_float();

	int main() {

		float f_i = 0;

		int x[n]; 
		int i, j;
		float X[2];
		float fobj;
		
		int lim[4] = {-5*p, 10*p, -5*p, 10*p};

		for (i = 0; i < n; i++) {
			x[i] = nondet_int();
			X[i] = nondet_float();
		}

		int A[nr][n] = {-1*p, 0*p, 1*p, 0*p, 0*p, -1*p, 0*p, 1*p};
		int B[nr] = {5*p, 10*p, 5*p, 10*p};
		float s = 0;

		for (i = 0; i < nr; i++) {
			for (j = 0; j < n; j++){
				s = s + A[i][j]*x[j]/p;
			}
			__ESBMC_assume( s < (float) B[i] );
			s = 0;	
		}

		for (i = 0; i < n; i++) {
			__ESBMC_assume( X[i] == (float) x[i]/p	);
		}

		fobj = (X[0]*X[0] + X[1]*X[1] -2*X[0])*(X[0]*X[0] + X[1]*X[1] -2*X[0]) + 0.25*X[0];

		__ESBMC_assume(fobj < f_i );

		assert(fobj > f_i);
		return 0;
	}
