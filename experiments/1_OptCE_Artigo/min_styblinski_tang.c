#define p 10000

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = 50;

    float fobj;    
    int x1;
    float X1;

    x1 = nondet_int();
    X1 = (float) nondet_float();
     
     //-----------------------------------------------------------       
     // Restrictions

          __ESBMC_assume( (x1>=-5*p)&& (x1<=5*p) );
          __ESBMC_assume( (x2>=-5*p)&& (x2<=5*p) );
          __ESBMC_assume( X1 == (float) x1/p );
          __ESBMC_assume( X2 == (float) x2/p );
    //-----------------------------------------------------------  

    fobj = 0.5*( (x1*x1*x1*x1 -16*x1*x1 +5*x1) + (x2*x2*x2*x2 -16*x2*x2 +5*x2));

    __ESBMC_assume(fobj < f_i );

    assert(fobj > f_i);
    return 0;
  }
