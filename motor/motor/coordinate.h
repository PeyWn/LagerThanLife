
/*
This function calculates the servo angles using inverse kinematics for a 2D 3DOF system.

Variables:
CT_angle: One angle has to be set in the beginning, for this function it is the angle between point C and T 3/2 PI.

Tx: Target x
Ty: Target y

Returns a list "servo" of length 3 which contains servo A, B, C angles.

 */
int calculate_angles(double CT_angle, double Tx, double Ty, double servo[3]);



/*
This function converts angles into a number between 0 and 1023 that can be sent directly to
to the arm servos

The servo array should be the same as in calculating angles since the functions uses the radial value in the conversion calculation,

Returns 1 if the calculated value is a valid number that the servos can physically assume.
*/
int convert_angles(double servo[3]);

/*
The conversion equation for calculating angles
Input rads and a numerical offset for the servos (servos uses another coordinate system their 0 is approximately equal to 280 degrees)

Returns a double with the correspondning decimal value for the input radian
*/
double rad_to_dec(double rads, int offcet);
