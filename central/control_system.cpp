#include "control_system.h"
#include "sensor_com.h"
#include <iostream>
#include <cmath>

/*-----PRIVATE FUNCTIONS------------------------------------------------------------------------*/

bool ControlSystem::is_sampling_time(){
	if(initialized){
		clock_t current_time = clock();
		double diff_ms = ( (float)current_time - (float)last_sample_time) / CLOCKS_PER_SEC * 1000;
		if(diff_ms >= SAMPLE_TIME){
		    last_sample_time = current_time;
		    return true;
		}
		return false;
	}
	else{
		last_sample_time 	= clock();
		initialized 		= true;
		return true;	// do the first sampling
	}
}

int ControlSystem::turn_value(){
	// round off to closest integer
    int turn_value = round(-(K_P*p_error + K_I*i_error + K_D*d_error));
    
    turn_value = (int)saturate(turn_value, MAX_TURN);
	
	return turn_value;
}

void ControlSystem::sample_line_position(float line_center){
	/* negative error for line is to the right
	   => positive correction, which is positive
	   turn  									 */
	old_line_pos = line_pos;
	line_pos     = MAX_TURN * line_center / (float)SENSOR_MAX; //+7,-7
	
	/* PROPORTIONAL TERM */
	p_error = line_pos;

	/* INTEGRATING TERM */
	i_error = i_error + line_pos;
	double i_error_saturated = normalize(i_error)*MAX_I_ERROR;
	i_error = (fabs(i_error) > MAX_I_ERROR) ? i_error_saturated : i_error;

	/* DERIVATING TERM */
	d_error = line_pos - old_line_pos;
}

void ControlSystem::set_turn_speed(int turn_speed){
	int dir = normalize(turn_speed);
	int spd = fabs(turn_speed);
	TURN_STATUS turn = NONE;

	turn    = (dir >  0) ? RIGHT : (dir == 0) ? NONE  : LEFT;

	/* send a command to motor-unit */
	motor->turn(turn, spd);
}

double ControlSystem::normalize(double val){
	double result = val == 0 ? 0 : val/fabs(val);
	return result;
}

double ControlSystem::saturate(double val, double max){
	if(abs(val) > max){
		return max * normalize(val);
	}
	else{
		return val;
	}
}

/*-----PUBLIC FUNCTIONS-------------------------------------------------------------------------*/

ControlSystem::ControlSystem(MotorCom * motor_in){
	motor  = motor_in;
}

bool ControlSystem::run(float line_center){

	/* return false if it's not sampling time */
    if( !is_sampling_time() ){
	return false;
    }

    sample_line_position(line_center);
    int turn_speed = turn_value();
    set_turn_speed(turn_speed);

    return true;
}
