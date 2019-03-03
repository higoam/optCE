#define p 1

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = 61;

    float f_c = 0;
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

    fobj = abs2(X1*sin2(X1) + 0.1*X1) + abs2(X2*sin2(X2) + 0.1*X2);

    __CPROVER_assume(fobj < f_i );

    float delta = (f_i-f_c)/5;
    if ((f_i-f_c) > 0.00001){
      while (f_c <= f_i){
        __CPROVER_assert(fobj > f_c, "");
        f_c += delta;
      }
    }

    return 0;
  }
