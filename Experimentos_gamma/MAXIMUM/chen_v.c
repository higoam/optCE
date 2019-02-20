
    #include <stdio.h> 
    #include <stdlib.h> 
    #include "math2.h" 

  int main(int argc, char *argv[ ]) {

    float fobj,X1,X2;
    X1 = atof(argv[1]);
    X2 = atof(argv[2]);


    fobj = -((0.001)/( 0.001*0.001 + (X1 -0.4*X2 -0.1)*(X1 -0.4*X2 -0.1)))  -((0.001)/( 0.001*0.001 + (2*X1 +X2 -1.5)*(2*X1 +X2 -1.5)));



    printf("%f", fobj);

    return 0;
  }
