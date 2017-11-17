#include "control_system.h"

ControlSystem::ControlSystem(SensorCom * Sensor, MotorCom * Motor){
	sensor = Sensor;
	motor  = motor;
}

/* check sampling time and set initialize flag*/
bool is_sampling_time(){
	if(initialized){
		clock_t current_time = clock();
		return (current_time - last_sample_time) >= sample_time ? true : false;
	}
	else{
		last_sample_time 	= clock();
		initialized 		= true;
		return true;	// first sampling
	}
}

/* return +/- 1 as direction of arg double val */
double normalize(double val){
	return val/abs(val);
}

/* the real control_system regulation */
int turn_value(){
	// round off to closest integer
	return (int)round(-(K_P*p_error + K_I*i_error + K_D*d_error), 0);
}

/*	local function:
	the heart of the control-system, computes the error variables
	for the P-, I-, D- parameters.									*/
double sample_line_position(){
	/* negative error for line is to the right
	   => positive correction, which is positive
	   turn  									 */
	old_line_pos = line_pos;
	line_pos     = max_turn * normalize(sensor->get_line_position());

	/* PROPORTIONAL TERM */
	p_error = line_pos;

	/* INTEGRATING TERM */
	i_error = i_error + line_pos;
	i_error = abs(i_error) > max_i_error ? old_i_error : i_error;

	/* DERIVATING TERM */
	d_error = line_pos - old_line_pos;
}

/* 	sample and run control_system if time is up
	return false */
bool run(SensorCom *sensor, MotorCom *motor){

	/* return false if it's not sampling time */
	if(!is_sampling_time)
		return false;

	sensor->getLineState();
	sensor->getLineCenter();

	if(line_state == 1 && central_state == DRIVING)
		return false;

	update_error();
	turn_value();
}
