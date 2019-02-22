
    #include <stdio.h> 
    #include <stdlib.h> 
    #include "math2.h" 

  int main(int argc, char *argv[ ]) {

    float fobj,X1,X2,X3,X4,X5,X6;
    X1 = atof(argv[1]);
    X2 = atof(argv[2]);
    X3 = atof(argv[3]);
    X4 = atof(argv[4]);
    X5 = atof(argv[5]);
    X6 = atof(argv[6]);


    fobj = 1000*( X4*(X4*4.70588235 +X5*( -2.35294118*cos2(X1 -X2) +9.41176471*sin2(X1 -X2)) +X6*( -2.35294118*cos2(X1 -X3) +9.4117647*sin2(X1 -X3)) ) ) + 1200*( X5*(X5*4.70588235 +X4*( -2.35294118*cos2(X2 -X1) +9.41176471*sin2(X2 -X1)) +X6*( -2.35294118*cos2(X2 -X3) +9.4117647*sin2(X2 -X3)) ) ) + 2000*( X6*(X6*4.70588235 +X4*( -2.35294118*cos2(X3 -X1) +9.41176471*sin2(X3 -X1)) +X5*( -2.35294118*cos2(X3 -X2) +9.4117647*sin2(X3 -X2)) ) + 1.8 );



    printf("%f", fobj);

    return 0;
  }
