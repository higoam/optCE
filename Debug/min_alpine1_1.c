#define p 1
#define nv 2
#define nr 2

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
		
		float f_c = 0;
		float f_i = 64;

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
     
        int lim[4] = {-10*p, 10*p, -10*p, 10*p};

        for (i = 0; i < nv; i++) {
            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );
            __ESBMC_assume( X[i] == (float) x[i]/p	); 
        }
     
        //-----------------------------------------------------------	

		fobj = abs2(X[0]*sin2(X[0]) + 0.1*X[0]) + abs2(X[1]*sin2(X[1]) + 0.1*X[1]);

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
