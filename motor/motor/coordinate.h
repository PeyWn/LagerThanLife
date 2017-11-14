
/*
This function calculates the servo angles using inverse kinematics for a 2D 3DOF system.

Variables:
CT_angle: One angle has to be set in the beginning, for this function it is the angle between point C and T 3/2 PI.

Tx: Target x
Ty: Target y

Returns a list "servo" of length 3 which contains servo A, B, C angles.

 */
double calculate_angels(int len_AB, int len_BC, int len_CT, double T_angle, int Tx, int Ty);
