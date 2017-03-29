#define p 1
#define nv 2
#define nr 2

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
		
		float f_i = 3.000000 -1e-05 -0.0001 -0.001 -0.01 -0.1 -1 -10 -100 -1000 -10000 -100000 -1e+06 -1e+07 -1e+08 -1e+09 -1e+10 -1e+11 -1e+12 -1e+13 -1e+14 -1e+15 -1e+16 -1e+17 -1e+18 -1e+19 -1e+20 -1e+21 -1e+22 -1e+23 -1e+24 -1e+25 -1e+26 -1e+27 -1e+28 -1e+29 -1e+30 -1e+31 -1e+32 -1e+33 -1e+34 -1e+35 -1e+36 -1e+37 -1e+38 -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf -inf;

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
     
        int lim[4] = {(4.94066e-324*1-1)*10,(4.94066e-324*1+1)*10,(2.96439e-323*1-1)*10,(2.96439e-323*1+1)*10};

        for (i = 0; i < nv; i++) {
            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );
            __ESBMC_assume( X[i] == (float) x[i]/p	); 
        }
     
        //-----------------------------------------------------------	

		fobj = (X[0] -1)*(X[0] -1) + 2*(2*X[1]*X[1] - X[1]-1)*(2*X[1]*X[1] - X[1]-1);

		__ESBMC_assume(fobj < f_i );

		assert(fobj > f_i);
		return 0;
	}
