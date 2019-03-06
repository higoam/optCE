#define p 1000

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = 2.9966;

    float fobj;    
    int x1,x2;
    float X1,X2;

    x1 = nondet_int();
    X1 = (float) nondet_float();
    x2 = nondet_int();
    X2 = (float) nondet_float();
     
     //-----------------------------------------------------------       
     // Restrictions

          __ESBMC_assume( (x1>=-1*p)&& (x1<=1*p) );
          __ESBMC_assume( (x2>=-1*p)&& (x2<=1*p) );
          __ESBMC_assume( X1 == (float) x1/p );
          __ESBMC_assume( X2 == (float) x2/p );
    //-----------------------------------------------------------  

    fobj = (1 + (X1 + X2 + 1)*(X1 + X2 + 1)*(19 -14*X1 +3*X1*X1 -14*X2 +6*X1*X2 +3*X2*X2))*(30 + (2*X1 -3*X2)*(2*X1 -3*X2)*(18 -32*X1 +12*X1*X1 + 48*X2 -36*X1*X2 +27*X2*X2));

    __ESBMC_assume(fobj < f_i );

    assert(fobj > f_i);
    return 0;
  }
