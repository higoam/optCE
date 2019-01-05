
    #include <stdio.h> 
    #include <stdlib.h> 
    #include "math2.h" 

  int main(int argc, char *argv[ ]) {

    float fobj,x1,x2;
    x1 = atof(argv[1]);
    x2 = atof(argv[2]);


    fobj = 7*x1*x1 -6*sqrt2(3)*x1*x2 + 13*x2*x2;


    printf("%f", fobj);

    return 0;
  }
