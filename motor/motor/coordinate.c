#include <stdio.h>
#include <math.h>
#include "coordinate.h"

volatile const double len_AB = 15;
volatile const double len_BC = 15;
volatile const double len_CT = 15;

void calculate_angles(double CT_angle, double Tx, double Ty, double servo[3]){

    volatile double Cx = Tx - cos(CT_angle)*len_CT;
    volatile double Cy = Ty - sin(CT_angle)*len_CT;

    volatile double len_AC = sqrt( (pow(Cx, 2) + pow(Cy, 2)) );
    volatile double AC_angle = atan( Cy/Cx );

    volatile double sp = (len_AB + len_BC + len_AC)/2; //semiparameter for surface
	
	if(sp > len_AB | sp > len_BC | sp > len_AC){
		return; //TODO Error message? Set arm to default or do nothing
	}
	
    volatile double surf = sqrt( sp*(sp-len_AB)*(sp-len_BC)*(sp-len_AC) ); //The surface for the points ABC+

	//double test = 2*surf/(len_AB*len_AC);
    volatile double A = asin( 2*surf/(len_AB*len_AC) );
    volatile double B = asin( 2*surf/(len_AB*len_BC) );
    //double C = asin( 2*S/(len_AC/len_BC) );
	
    servo[0] = AC_angle + A;
    servo[1] = B;
    servo[2] = CT_angle - servo[1] - servo[0];
}
