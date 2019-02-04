#define p 1

#include "math2.h" 
#include <math.h>
#include <stdio.h>

    int nondet_int();
    float nondet_float();

    int main() {
    
    float f_i = 10000;
    float Pg1, Pg2, Pg3;	

    int i,j;
    int x[4];
    float X[3];
    float fobj;

    for (i = 0; i<3; i++){
      x[i] = nondet_int();
      X[i] = nondet_float();
    }
     
        //-----------------------------------------------------------       
        // Restrictions

//            __ESBMC_assume( X[0] != X[1] ); 	
//            __ESBMC_assume( X[1] != X[2] ); 	

            __ESBMC_assume( x[0] >= -10 && x[0] <= 10 ); 	
            __ESBMC_assume( x[1] >= -10 && x[1] <= 10 ); 	
            __ESBMC_assume( x[2] >= -10 && x[2] <= 10 ); 	

            __ESBMC_assume( X[0] == (float) x[0]/p  ); 
            __ESBMC_assume( X[1] == (float) x[1]/p  ); 
            __ESBMC_assume( X[2] == (float) x[1]/p  ); 
     
	    __ESBMC_assume(  (X[0]>=-PI) && (X[0]<=+PI)  );
	    __ESBMC_assume(  (X[1]>=-PI) && (X[1]<=+PI)  );
	    __ESBMC_assume(  (X[2]>=-PI) && (X[2]<=+PI)  );

	    __ESBMC_assume(  (((X[0]-X[1])/0.1)>= -1) && (((X[0]-X[1])/0.1)<= 1)  );
	    __ESBMC_assume(  (((X[0]-X[2])/0.1)>= -1) && (((X[0]-X[2])/0.1)<= 1)  );
	    __ESBMC_assume(  (((X[1]-X[2])/0.1)>= -1) && (((X[1]-X[2])/0.1)<= 1)  );

	    Pg1 = ((X[0]-X[1])/(0.1)) + ((X[0]-X[2])/(0.1));		
	    Pg2 = ((X[1]-X[2])/(0.1)) + ((X[1]-X[0])/(0.1));		
	    Pg3 = ((X[2]-X[0])/(0.1)) + ((X[2]-X[1])/(0.1)) + 0.8;		

	    __ESBMC_assume(  (Pg1>=0) && (Pg1<=4)  );
	    __ESBMC_assume(  (Pg2>=0) && (Pg2<=4)  );
	    __ESBMC_assume(  (Pg3>=0) && (Pg3<=4)  );

        //-----------------------------------------------------------  

    fobj = 1000*Pg1 + 1200*Pg2 + 2000*Pg3;


    __ESBMC_assume(fobj < f_i );

    assert(fobj > f_i);
    return 0;
  }
