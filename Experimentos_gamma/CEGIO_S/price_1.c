
    #include <stdio.h> 
    #include <stdlib.h> 
    #include "math2.h" 

  int main(int argc, char *argv[ ]) {

    float fobj,X1,X2;
    X1 = atof(argv[1]);
    X2 = atof(argv[2]);


    fobj = (abs2(X1)-5)*(abs2(X1)-5) + (abs2(X2)-5)*(abs2(X2)-5);



    printf("%f", fobj);

    return 0;
  }
