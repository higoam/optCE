
    #include <stdio.h> 
    #include <stdlib.h> 
    #include "math2.h" 

  int main(int argc, char *argv[ ]) {

    float fobj,X1,X2;
    X1 = atof(argv[1]);
    X2 = atof(argv[2]);


    fobj = -(sin2(X1 -X2/8)*sin2(X1 -X2/8) + sin2(X2 + X1/8)*sin2(X2 + X1/8))/(sqrt2((X1 -8.6998)*(X1 -8.6998) + (X2-6.7665)*(X2-6.7665) + 1));



    printf("%f", fobj);

    return 0;
  }