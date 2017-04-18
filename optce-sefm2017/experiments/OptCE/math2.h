
#define PI 	3.14159265358979323846
#define PI_2   	1.57079632679489661923


	float abs2(float num){
		float b = -1;
	
		if(num*b>0){
			num = num*b;	
		}
		
		return num;
	}

	float sqrt2(float val)
	{
		float r = val/10;
		float dx;
		float diff;
		float min_tol = 0.00001;
		int i, flag = 0;

		if ( val == 0 ) r = 0;
		else {
			for (i = 0; i < 20; ++i)
			if (!flag){
					dx = ( val - ( r*r ) ) / ( 2.0*r );
					r = r + dx;
					diff = val - ( r*r );
					if ( abs2( diff ) <= min_tol ) flag = 1;
				}
				else r = r;
		}
		return r;
	}

	float floor2( float x ){
		int y = (int)x;    

		if (x >= 0){
			return (float)y;
		}
		else{
			if((float)y == x){
				return (float)y;
			}else{
				return (float)y - 1.0; 
			}		    
		}
	}

	float cos2(float rad){

		float r;

		float graus = 180/PI;
		float aux = rad*graus;
		int n = aux/360;
		rad = rad - n*2*PI;

		if(rad<0) rad = rad + 2*PI; 														

	 	if(rad>PI_2 && rad<=PI)
	 		r = PI-rad;
	 	else if(rad>PI && rad<=(PI_2+PI))
	 		r = rad-PI;
	 	else if(rad>(PI_2+PI) && rad<=(2*PI))
	 		r = (2*PI)-rad;
		else
			r = rad;

		float result = (1 - 0.5*r*r + 0.041666667*r*r*r*r - 0.001388889*r*r*r*r*r*r + 0.000024802*r*r*r*r*r*r*r*r - 0.000000276*r*r*r*r*r*r*r*r*r*r + 0.000000002*r*r*r*r*r*r*r*r*r*r*r*r);

		if( (rad>PI_2)&&(rad<(PI_2+PI)) )
	 		result = result * -1;
	
		return result;
	}	

	float sin2(float rad){

		float r;
		float graus = 180/PI;
		float aux = rad*graus;
		int n = aux/360;		
		rad = rad - n*2*PI;

		if(rad<0) rad = rad + 2*PI;

	 	if(rad>PI_2 && rad<=PI)
	 		r = PI-rad;
	 	else if(rad>PI && rad<=(PI_2+PI))
	 		r = rad-PI;
	 	else if(rad>(PI_2+PI) && rad<=(2*PI))
	 		r = (2*PI)-rad;
		else
			r = rad;

		float result = (r - 0.166666667*r*r*r + 0.008333333*r*r*r*r*r - 0.000198413*r*r*r*r*r*r*r + 0.000002756*r*r*r*r*r*r*r*r*r - 0.000000025*r*r*r*r*r*r*r*r*r*r*r);

		if( (rad>(PI))&&(rad<(2*PI)) ) 
	 		result = result * -1;
	
		return result; 
	}

