#ifndef COMMANDS_H_
#define COMMANDS_H_

/*
 Stop all movement of the arm
 */
void stop_arm();

/*
Stop the movement of the given axis

id - id of the axis to stop movement on, an integer between 0 and 5.
*/
void stop_axis(int id);

/*
Close the claw of the robot arm
*/
void grab_ware();

/*
Open the claw of the robot arm
*/
void release_ware();

/*
Move the arm to the home position.
*/
void go_home();

/*
Move the arm forward and close the claw to pick up a ware.
Then goes back to the home position.
*/
void pick_up_ware();

/*
Move the arm forward and open the claw to put down a ware.
Then goes back to the home position.
*/
void put_down_ware();

/*
Move the given axis fwd.

axis - the id of the axis to move. 0-indexed
*/
void axis_fwd(int axis);

/*
Move the given axis back.

axis - the id of the axis to move. 0-indexed
*/
void axis_back(int axis);

#endif /* COMMANDS_H_ */