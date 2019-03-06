#define p 10

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = -1.64112;

    float fobj;    
    int x1,x2;
    float X1,X2;

    x1 = nondet_int();
    X1 = (float) nondet_float();
    x2 = nondet_int();
    X2 = (float) nondet_float();
     
     //-----------------------------------------------------------       
     // Restrictions

          __CPROVER_assume( (x1>=-110)&& (x1<=-90 ) );
          __CPROVER_assume( (x2>=-210)&& (x2<=-190 ) );
          __CPROVER_assume( X1 == (float) x1/p );
          __CPROVER_assume( X2 == (float) x2/p );
    //-----------------------------------------------------------  

    fobj = sin2(X1+X2) + (X1-X2)*(X1-X2) -1.5*X1 + 2.5*X2 + 1;

    __CPROVER_assume(fobj < f_i );

    __CPROVER_assert(fobj > f_i, "");
    return 0;
  }
