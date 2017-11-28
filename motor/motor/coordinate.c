#include <stdio.h>
#include <math.h>
#include "coordinate.h"

//The length between points
volatile const double len_AB = 15.5;
volatile const double len_BC = 15;
volatile const double len_CT = 15.5;

volatile const int Ax = 0;    //Servo 2&3 possition in the coordinate system
volatile const int Ay = 25;

volatile const double PI = 3.141593;

//Point A, B, C, T corresponds to servo 2&3, servo 4&5, servo 6 and the claw.


int calculate_angles(double CT_angle, double Tx, double Ty, double servo[3]){

    volatile double Cx = Tx - cos(CT_angle)*len_CT;
    volatile double Cy = Ty - sin(CT_angle)*len_CT;

    volatile double len_AC = sqrt( (pow((Cx-Ax), 2) + pow((Cy-Ay), 2)) );
    volatile double AC_angle = atan( (Cy-Ay)/(Cx-Ax) );

    volatile double sp = ((len_AB + len_BC + len_AC)*(0.5)); //semiparameter for surface
	
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
	
    servo[0] = AC_angle + A;   //Saves the radial angle for point A 
    servo[1] = B;              //Saves the radial angle for point B
    servo[2] = CT_angle - servo[1] - servo[0];    //Saves the radial angle for point C
	
    return convert_angles(servo);
    
}

int convert_angles(double servo[3]){
	
	volatile double test1 = servo[0]; 
	servo[0] = rad_to_dec(servo[0], 220);
	volatile double test2 = servo[0];
	
	if(servo[0] < 220){
		servo[0] = 220;
		return 0;
	}
	else if(servo[0] > 803){
		servo[0] = 803;
		return 0;
	}
	
	volatile double test3 = servo[1]; 
	servo[1] = 1023 - rad_to_dec(servo[1], 210);
	volatile double test4 = servo[1]; 
	
	if(servo[1] < 210){
		servo[1] = 210;
		return 0;
	}
	else if(servo[1] > 803){
		servo[1] = 803;
		return 0;
	}
	
	volatile double test5 = servo[2]; 
	servo[2] = rad_to_dec(servo[2], -90); //TODO test with -300 --> -90 (with or without the offset) 300 is roughly equals to ""turning" the servo coordinate system 90 degrrens clockwise.
	volatile double test6 = servo[2];
	
	if(servo[2] < 210){
		servo[2] = 210;
		return 0;
	}
	else if(servo[2] > 793){
		servo[2] = 793;
		return 0;
	}
	return 1;
}

double rad_to_dec(double rad, int offset){
	if(rad < 0){
		rad = -rad;
	}
	return (rad*1228)/(2*PI) + offset;
}
