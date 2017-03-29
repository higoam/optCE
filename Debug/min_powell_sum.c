#define p 10000
#define nv 2
#define nr 2

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
		
		float f_i = 0.000000 -1e-05 -1e-05 -1e-05 -1e-05 -1e-05;

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
     
        int lim[4] = {(4.94066e-324*10000-1)*10,(4.94066e-324*10000+1)*10,(2.96439e-323*10000-1)*10,(2.96439e-323*10000+1)*10};

        for (i = 0; i < nv; i++) {
            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );
            __ESBMC_assume( X[i] == (float) x[i]/p	); 
        }
     
        //-----------------------------------------------------------	

		fobj = abs2(X[0])*abs2(X[0]) + abs2(X[1])*abs2(X[1])*abs2(X[1]);

		__ESBMC_assume(fobj < f_i );

		assert(fobj > f_i);
		return 0;
	}
