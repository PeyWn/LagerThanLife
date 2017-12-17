#include "transmission.h"
#include "globals.h"
#include "commands.h"

/* Servo that contains position of entire axis
NOTE that axis are 0-indexed */
int AXIS_POS_SERVO[] = {1, 2, 4, 6, 7, 8};
int AXIS_POS_MIN[] = {CW_LIMIT_1, CW_LIMIT_2, CW_LIMIT_4,
CW_LIMIT_6, CW_LIMIT_7, CW_LIMIT_8};
int AXIS_POS_MAX[] = {CCW_LIMIT_1, CCW_LIMIT_2, CCW_LIMIT_4,
CCW_LIMIT_6, CCW_LIMIT_7, CCW_LIMIT_8};

void stop_arm(){
    for(int i = 0; i < NUMBER_OF_AXIS; ++i){
        stop_axis(i);
        _delay_ms(100);
    }
}

void stop_axis(int id){
    //Figure out which servo to read from
    int servo_id = AXIS_POS_SERVO[id];

    //Read pos from servo
    int pos = get_servo_pos(servo_id);

    //Move axis to pos
    move_axis(id, pos, SPEED_2);
}

void grab_ware()
{
	grab();
}

void release_ware()
{
	release();
}

void go_home()
{
	go_home_pos();
}

void pick_up_ware()
{
	pickup_standard();
}

void put_down_ware()
{
	putdown_standard();
}

void axis_fwd(int axis){
    move_axis(axis, AXIS_POS_MIN[axis], SPEED_MANUAL);
}

void axis_back(int axis){
    move_axis(axis, AXIS_POS_MAX[axis], SPEED_MANUAL);
}
