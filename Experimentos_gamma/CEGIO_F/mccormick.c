
    #include <stdio.h> 
    #include <stdlib.h> 
    #include "math2.h" 

  int main(int argc, char *argv[ ]) {

    float fobj,X1,X2;
    X1 = atof(argv[1]);
    X2 = atof(argv[2]);


    fobj = sin2(X1+X2) + (X1-X2)*(X1-X2) -1.5*X1 + 2.5*X2 + 1;



    printf("%f", fobj);

    return 0;
  }
