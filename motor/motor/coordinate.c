#include <stdio.h>
#include <math.h>
#include "coordinate.h"

#define len_AB 15
#define len_BC 15
#define len_CT 15

#define PI 3.1415

double calculate_angels(double CT_angle, int Tx, int Ty){

    double Cx = Tx + cos(CT_angle)*len_CT;
    double Cy = Ty + sin(CT_angle)*len_CT;

    double len_AC = sqrt( (pow(Cx, 2) + pow(Cy, 2)) );
    double AC_angle = atan( Cy/Cx );

    double sp = (len_AB + len_BC + len_AC)/2; //semiparameter for surface
    double surf = sqrt( (sp*(sp-len_AB)*(sp-len_BC)*(sp-len_AC)) ); //The surface for the points ABC+

    double A = asin( 2*surf/(len_AB*len_AC) );
    double B = asin( 2*surf/(len_AB*len_BC) );
    //double C = asin( 2*S/(len_AC/len_BC) );

    double servo[2];
    servo[0] = AC_angle + A;
    servo[1] = B;
    servo[2] = CT_angle - servo[1] - servo[0];

    return(*servo);
}
