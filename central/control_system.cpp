#include "control_system.h"
#include "sensor_com.h"
#include <cmath>

ControlSystem::ControlSystem(SensorCom * Sensor, MotorCom * Motor){
	sensor = Sensor;
	motor  = Motor;
}

/* check sampling time and set initialize flag*/
bool ControlSystem::is_sampling_time(){
	if(initialized){
		clock_t current_time = clock();
		return (current_time - last_sample_time) >= SAMPLE_TIME ? true : false;
	}
	else{
		last_sample_time 	= clock();
		initialized 		= true;
		return true;	// do the first sampling
	}
}

/* normalize a double-value to be 0, -1 or +1 */
double ControlSystem::normalize(double val){
	double result = val == 0 ? 0 : val/fabs(val);
	return result;
}

/* the real control_system regulation */
int ControlSystem::turn_value(){
	// round off to closest integer
	return (int)round(-(K_P*p_error + K_I*i_error + K_D*d_error));
}

/*	local function:
	the heart of the control-system, computes the error variables
	for the P-, I-, D- parameters.

	max-saturation for i_error
		*/
double ControlSystem::sample_line_position(){
	/* negative error for line is to the right
	   => positive correction, which is positive
	   turn  									 */
	old_line_pos = line_pos;
	line_pos     = MAX_TURN * sensor->get_line_position() / SENSOR_MAX; //+7,-7

	/* PROPORTIONAL TERM */
	p_error = line_pos;

	/* INTEGRATING TERM */
	i_error = i_error + line_pos;
	double i_error_saturated = normalize(i_error)*MAX_I_ERROR
	i_error = (fabs(i_error) > MAX_I_ERROR) ? i_error_saturated : i_error;

	/* DERIVATING TERM */
	d_error = line_pos - old_line_pos;
}

void ControlSystem::set_turn_speed(int turn_speed){
	int dir = normalize(turn_speed);
	int spd = fabs(turn_speed);

	dir = 	(dir >  0) ? RIGHT : (dir == 0) ? NONE  : LEFT;

	/* send a command to motor-unit */
	motor->turn(dir, spd);
}

/* 	sample and run control_system if time is up
	return false */
bool ControlSystem::run(){
	return false;

	/* return false if it's not sampling time */
	if(!is_sampling_time)
		return false;

	line_state = sensor->getLineState();

	/* return false if not correct states */
	if(line_state != SINGLE)
		return false;

	sample_line_position();
	int turn_speed = turn_value();
	set_turn_speed(turn_speed);
}
