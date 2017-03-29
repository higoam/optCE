#define p 100000
#define nv 2
#define nr 4

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
		
		float f_c = 0;
		float f_i = 18.000000 -1e-05 -0.0001 -0.001 -0.01 -0.1 -1 -10 -100 -1e-05 -1e-05 -1e-05 -1e-05 -1e-05;

		int i,j;
		int x[3];
		float X[2];
		float fobj;

		for (i = 0; i<2; i++){
			x[i] = nondet_int();
			X[i] = nondet_float();
		}
     
        //-----------------------------------------------------------	     
        // Restrictions
     
        int A[nr][nv] = {-1*p, 0*p, 1*p, 0*p, 0*p, -1*p, 0*p, 1*p};
        int B[nr] = {10*p, 10*p, 10*p, 10*p};     
        float s = 0;
     
        for (i = 0; i < nr; i++) {
            for (j = 0; j < nv; j++){
                 s = s + A[i][j]*x[j]/p;
            }
            __ESBMC_assume( s < (float) B[i] );
           s = 0;
        }
		
        for (i = 0; i < nv; i++) {
            __ESBMC_assume( X[i] == (float) x[i]/p	);
        }
     
        //-----------------------------------------------------------	

		fobj = 0.25*X[0]*X[0]*X[0]*X[0] -0.5*X[0]*X[0] + 0.1*X[0] + 0.5*X[1]*X[1];

		__ESBMC_assume(fobj < f_i );

		float delta = (f_i-f_c)/5;
		if ((f_i-f_c) > 0.00001){
			while (f_c <= f_i){
				assert(fobj > f_c);
				f_c += delta;
			}
		}

		return 0;
	}
