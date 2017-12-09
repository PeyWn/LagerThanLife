/*
 * commands.h
 *
 * Created: 11/21/2017 11:24:12 AM
 *  Author: jesjo430
 */ 

 /*
 Stop all movement of the arm
 */
void stop_arm();

/*
Stop the movement of the given axis

id - id of the axis to stop moevement on, an integer between 0 and 5.
*/
void stop_axis(int id);

void grab_ware();
void release_ware();
void go_home();
void pick_up_ware();
void put_down_ware();

void axis_fwd(int axis);
void axis_back(int axis);