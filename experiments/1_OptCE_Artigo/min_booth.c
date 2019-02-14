#define p 10000

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = 45;

    float fobj;    
    int x1;
    float X1;

    x1 = nondet_int();
    X1 = (float) nondet_float();
     
     //-----------------------------------------------------------       
     // Restrictions

          __CPROVER_assume( (x1>=-10*p)&& (x1<=10*p) );
          __CPROVER_assume( (x2>=-10*p)&& (x2<=10*p) );
          __CPROVER_assume( X1 == (float) x1/p );
          __CPROVER_assume( X2 == (float) x2/p );
    //-----------------------------------------------------------  

    fobj = (x1 + 2*x2 -7)*(x1 + 2*x2 -7) + (2*x1 + x2 -5)*(2*x1 + x2 -5);

    __CPROVER_assume(fobj < f_i );

    __CPROVER_assert(fobj > f_i, "");
    return 0;
  }