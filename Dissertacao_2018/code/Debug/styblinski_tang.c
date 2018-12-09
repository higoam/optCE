
    #include <stdio.h> 
    #include <stdlib.h> 
    #include "math2.h" 

  int main(int argc, char *argv[ ]) {

    float fobj,x1,x2;
    x1 = atof(argv[1]);
    x2 = atof(argv[2]);


    fobj = 0.5*( (x1*x1*x1*x1 -16*x1*x1 +5*x1) + (x2*x2*x2*x2 -16*x2*x2 +5*x2));


    printf("%f", fobj);

    return 0;
  }
