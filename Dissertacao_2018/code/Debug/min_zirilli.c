#define p 1  
#define nv 2 
#define nr 2 

#include "math2.h" 
#include <math.h>

    int nondet_int();
    double nondet_double();

    int main() {
    
    double f_i = -1.126;

    int i,j;
    int x[3];
    double X[2];
    double fobj;

    for (i = 0; i<2; i++){
      x[i] = nondet_int();
      X[i] = nondet_double();
    }
     
        //-----------------------------------------------------------       
        // Restrictions
     
        int lim[4] = {-5*p, 5*p, -5*p, 5*p}; 

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
