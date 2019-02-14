#define p 10000

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = 46;

    float fobj;    
    int x1;
    float X1;

    x1 = nondet_int();
    X1 = (float) nondet_float();
     
     //-----------------------------------------------------------       
     // Restrictions

          __ESBMC_assume( (x1>=-1*p)&& (x1<=1*p) );
          __ESBMC_assume( (x2>=-1*p)&& (x2<=1*p) );
          __ESBMC_assume( X1 == (float) x1/p );
          __ESBMC_assume( X2 == (float) x2/p );
    //-----------------------------------------------------------  

    fobj = -0.1*(cos2(5*PI*x1) + cos2(5*PI*x2)) +(x1*x1 + x2*x2);

    __ESBMC_assume(fobj < f_i );

    assert(fobj > f_i);
    return 0;
  }
