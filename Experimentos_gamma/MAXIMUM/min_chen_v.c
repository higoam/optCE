#define p 100000

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = -2000;

    float fobj;    
    int x1,x2;
    float X1,X2;

    x1 = nondet_int();
    X1 = (float) nondet_float();
    x2 = nondet_int();
    X2 = (float) nondet_float();
     
     //-----------------------------------------------------------       
     // Restrictions

          __CPROVER_assume( (x1>=-10*p)&& (x1<=10*p) );
          __CPROVER_assume( (x2>=-10*p)&& (x2<=10*p) );
          __CPROVER_assume( X1 == (float) x1/p );
          __CPROVER_assume( X2 == (float) x2/p );
    //-----------------------------------------------------------  

    fobj = -((0.001)/( 0.001*0.001 + (X1 -0.4*X2 -0.1)*(X1 -0.4*X2 -0.1)))  -((0.001)/( 0.001*0.001 + (2*X1 +X2 -1.5)*(2*X1 +X2 -1.5)));

    __CPROVER_assume(fobj < f_i );

    __CPROVER_assert(fobj > f_i, "");
    return 0;
  }
