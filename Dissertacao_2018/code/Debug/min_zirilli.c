#define p 10000
#define nv 2 
#define nr 2 

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = 6.91026 -1e-05-0 -1e-05-0.001024 -1e-05-0.001024 -0.0001-0.001024 -0.001-0.001024 -0.01-0.001024 -0.1-0.001024 -1-0.001024 -10-0.001024 -1e-05-0.001034 -1e-05-0.001044 -1e-05-0.001054 -1e-05;

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
     
        int lim[4] = {-4*p, 4*p, -4*p, 4*p}; 

        for (i = 0; i < nv; i++) {
            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );
            __ESBMC_assume( X[i] == (float) x[i]/p  ); 
        }
     
        //-----------------------------------------------------------  

    fobj = 0.25*X[0]*X[0]*X[0]*X[0] -0.5*X[0]*X[0] + 0.1*X[0] + 0.5*X[1]*X[1];

    __CPROVER_assume(fobj < f_i );

    __CPROVER_assert(fobj > f_i,"");
    return 0;
  }
