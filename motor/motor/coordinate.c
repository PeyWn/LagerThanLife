#include <stdio.h>
#include <math.h>
#include "coordinate.h"

volatile const double len_AB = 15.5;
volatile const double len_BC = 15;
volatile const double len_CT = 15.5;

volatile const int Ax = 0;
volatile const int Ay = 21;

volatile const double PI = 3.141593;

int calculate_angles(double CT_angle, double Tx, double Ty, double servo[3]){

    volatile double Cx = Tx - cos(CT_angle)*len_CT;
    volatile double Cy = Ty - sin(CT_angle)*len_CT;

    volatile double len_AC = sqrt( (pow((Cx-Ax), 2) + pow((Cy-Ay), 2)) );
    volatile double AC_angle = atan( (Cy-Ay)/(Cx-Ax) );

    volatile double sp = (len_AB + len_BC + len_AC)/2; //semiparameter for surface
	
	if(sp < len_AB || sp < len_BC || sp < len_AC){
		return 0; 
	}
	
    volatile double surf = sqrt( sp*(sp-len_AB)*(sp-len_BC)*(sp-len_AC) ); //The surface for the points ABC+

    volatile double A = asin( 2*surf/(len_AB*len_AC) );
    volatile double B = asin( 2*surf/(len_AB*len_BC) );
    volatile double C = asin( 2*surf/(len_AC/len_BC) );
	
	if (round((A+B+C)*(180/PI)) == 180){
		return 0;
	}
	
    servo[0] = AC_angle + A;
    servo[1] = B;
    servo[2] = CT_angle - servo[1] - servo[0];
	
	convert_angles(servo);
	return 1;
}

void convert_angles(double servo[3]){
	
	volatile double test1 = servo[0]; 
	servo[0] = rad_to_dec(servo[0], 256);
	volatile double test2 = servo[0];
	
	if(servo[0] < 256){
		servo[0] = 256;
		return 0;
	}
	else if(servo[0] > 765){
		servo[0] = 765;
		return 0;
	}
	
	volatile double test3 = servo[1]; 
	servo[1] = rad_to_dec(servo[1], 256);
	volatile double test4 = servo[1]; 
	
	if(servo[1] < 256){
		servo[1] = 256;
		return 0;
	}
	else if(servo[1] > 765){
		servo[1] = 765;
		return 0;
	}
	
	volatile double test5 = servo[2]; 
	servo[2] = 1023 - rad_to_dec(servo[2], 256);
	volatile double test6 = servo[2]; 
	
	if(servo[2] < 256){
		servo[2] = 256;
		return 0;
	}
	else if(servo[2] > 765){
		servo[2] = 765;
		return 0;
	}
}

double rad_to_dec(double rads, int offcet){
	if(rads < 0){
		rads = (2*PI) + rads;
	}
	return (rads*1023)/(2*PI) + offcet;
}
