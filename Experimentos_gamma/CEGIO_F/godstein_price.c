
    #include <stdio.h> 
    #include <stdlib.h> 
    #include "math2.h" 

  int main(int argc, char *argv[ ]) {

    float fobj,X1,X2;
    X1 = atof(argv[1]);
    X2 = atof(argv[2]);


    fobj = (1 + (X1 + X2 + 1)*(X1 + X2 + 1)*(19 -14*X1 +3*X1*X1 -14*X2 +6*X1*X2 +3*X2*X2))*(30 + (2*X1 -3*X2)*(2*X1 -3*X2)*(18 -32*X1 +12*X1*X1 + 48*X2 -36*X1*X2 +27*X2*X2));



    printf("%f", fobj);

    return 0;
  }
