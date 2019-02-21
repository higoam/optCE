#define p 1

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = 13;

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

    fobj = -(sin2(X1 -X2/8)*sin2(X1 -X2/8) + sin2(X2 + X1/8)*sin2(X2 + X1/8))/(sqrt2((X1 -8.6998)*(X1 -8.6998) + (X2-6.7665)*(X2-6.7665) + 1));

    __CPROVER_assume(fobj < f_i );

    __CPROVER_assert(fobj > f_i, "");
    return 0;
  }