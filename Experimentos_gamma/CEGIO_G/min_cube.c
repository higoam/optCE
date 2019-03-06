#define p 1000

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = -0.0003;

    float fobj;    
    int x1,x2;
    float X1,X2;

    x1 = nondet_int();
    X1 = (float) nondet_float();
    x2 = nondet_int();
    X2 = (float) nondet_float();
     
     //-----------------------------------------------------------       
     // Restrictions

          __ESBMC_assume( (x1>=-2*p)&& (x1<=2*p) );
          __ESBMC_assume( (x2>=-2*p)&& (x2<=2*p) );
          __ESBMC_assume( X1 == (float) x1/p );
          __ESBMC_assume( X2 == (float) x2/p );
    //-----------------------------------------------------------  

    fobj = 100*(X2-X1*X1*X1)*(X2-X1*X1*X1) + (1-X1)*(1-X1);

    __ESBMC_assume(fobj < f_i );

    assert(fobj > f_i);
    return 0;
  }
