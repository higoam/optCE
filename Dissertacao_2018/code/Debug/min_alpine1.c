#define p 

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = ;

    int i,j;
    float fobj;

      x[i] = nondet_int();
      X[i] = nondet_float();
    }
     
        //-----------------------------------------------------------       
        // Restrictions
     
        int lim[4] =};

        for (i = 0; i < nv; i++) {
            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );
            __ESBMC_assume( X[i] == (float) x[i]/p  ); 
        }
     
        //-----------------------------------------------------------  

    fobj = abs2(X[0]*sin2(X[0]) + 0.1*X[0]) + abs2(X[1]*sin2(X[1]) + 0.1*X[1]);

    __ESBMC_assume(fobj < f_i );

    assert(fobj > f_i);
    return 0;
  }
