
    #include <stdio.h> 
    #include <stdlib.h> 
    #include "math2.h" 

	int main(int argc, char *argv[ ]) {

		float fobj,x1,x2;
		x1 = atof(argv[1]);
		x2 = atof(argv[2]);


		fobj = x1*x1*x1*x1 + x2*x2*x2*x2;


		printf("%f", fobj);

		return 0;
	}
