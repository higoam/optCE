#define p 10000
#define nv 2
#define nr 2

#include "math2.h" 
#include <math.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_c = 0;
    float f_i = 0.000000 -1e-05 -1e-05 -1e-05 -1e-05 -1e-05;

    int i,j;
    int x[3];
    float X[2];
    float fobj;

    for (i = 0; i<2; i++){
      x[i] = nondet_int();
      X[i] = nondet_float();
    }
     
        //-----------------------------------------------------------       
        // Restrictions
     
        int lim[4] = {-2*p, 2*p, -2*p, 2*p};

        for (i = 0; i < nv; i++) {
            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );
            __ESBMC_assume( X[i] == (float) x[i]/p  ); 
        }
     
        //-----------------------------------------------------------  

    fobj = 100*(X[1] - (X[0]*X[0]))*(X[1] - (X[0]*X[0])) + ((1-X[0])*(1-X[0]));

    __ESBMC_assume(fobj < f_i );

    float delta = (f_i-f_c)/5;
    if ((f_i-f_c) > 0.00001){
      while (f_c <= f_i){
        assert(fobj > f_c);
        f_c += delta;
      }
    }

    return 0;
  }
