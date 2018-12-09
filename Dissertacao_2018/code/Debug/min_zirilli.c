#define p 10
#define nv 2 
#define nr 2 

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = 0 -1e-05-0.35 -1e-05-0.35 -1e-05;

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
     
        int lim[4] = {-4*p, 0*p, 0*p, 4*p}; 

        for (i = 0; i < nv; i++) {
            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );
            __ESBMC_assume( X[i] == (float) x[i]/p  ); 
        }
     
        //-----------------------------------------------------------  

    fobj = 0.25*X[0]*X[0]*X[0]*X[0] -0.5*X[0]*X[0] + 0.1*X[0] + 0.5*X[1]*X[1];

    __ESBMC_assume(fobj < f_i );

    assert(fobj > f_i);
    return 0;
  }