#include <stdio.h>
#include <math.h>
#include "coordinate.h"

#define len_AB 15
#define len_BC 15
#define len_CT 15

double calculate_angels(double CT_angle, int Tx, int Ty){

    double Cx = Tx + cos(CT_angle)*len_CT;
    double Cy = Ty + sin(CT_angle)*len_CT;

    double len_AC = sqrt( (pow(Cx, 2) + pow(Cy, 2)) );
    double AC_angle = atan( Cy/Cx );

    double s = (len_AB + len_BC + len_AC)/2;
    double S = sqr( s*(s-len_AB)(s-len_BC)(s-len_AC) );

    double A = asin( 2S/(len_AB*len_AC) );
    double B = asin( 2S/(len_AB*len_BC) );
    double C = asin( 2S/(len_AC/len_BC) );

    double servo[2];
    servo[0] = ac_angle + A;
    servo[1] = B;
    servo[2] = t_angle - servo_B - servo_A;

    return(servo);
}
