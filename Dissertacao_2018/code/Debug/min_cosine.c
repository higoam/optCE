#define p 10
#define nv 2 
#define nr 2 

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = 1 -1e-05-0.2 -1e-05-0.2 -0.0001-0.2 -0.001-0.2 -0.01-0.2 -0.1-0.2 -1-0.2 -1e-05;

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
     
        int lim[4] = {0*p, 1*p, 0*p, 1*p}; 

        for (i = 0; i < nv; i++) {
            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );
            __ESBMC_assume( X[i] == (float) x[i]/p  ); 
        }
     
        //-----------------------------------------------------------  

    fobj = -0.1*(cos2(5*PI*X[0]) + cos2(5*PI*X[1])) +(X[0]*X[0] + X[1]*X[1]);

    __ESBMC_assume(fobj < f_i );

    assert(fobj > f_i);
    return 0;
  }
