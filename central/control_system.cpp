#include "control_system.h"
#include "sensor_com.h"

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
		return true;	// do the first sampling
	}
}

/* normalize a double-value to be 0, -1 or +1 */
double normalize(double val){
	double result = val == 0 ? 0 : val/abs(val);
	return result;
}

/* the real control_system regulation */
int turn_value(){
	// round off to closest integer
	return (int)round(-(K_P*p_error + K_I*i_error + K_D*d_error), 0);
}

/*	local function:
	the heart of the control-system, computes the error variables
	for the P-, I-, D- parameters.

	max-saturation for i_error
		*/
double sample_line_position(){
	/* negative error for line is to the right
	   => positive correction, which is positive
	   turn  									 */
	old_line_pos = line_pos;
	line_pos     = MAX_TURN * sensor->get_line_position() / SENSOR_MAX; //+7,-7

	/* PROPORTIONAL TERM */
	p_error = line_pos;

	/* INTEGRATING TERM */
	i_error = i_error + line_pos;
	i_error = (abs(i_error) > MAX_I_ERROR) ? old_i_error : i_error;

	/* DERIVATING TERM */
	d_error = line_pos - old_line_pos;
}

void set_turn_speed(int turn_speed){
	int dir = normalize(turn_speed);
	int spd = abs(turn_speed);

	dir = 	(dir >  0) ? RIGHT : (dir == 0) ? NONE  : LEFT;

	/* send a command to motor-unit */
	motor->turn(dir, spd);
}

/* 	sample and run control_system if time is up
	return false */
bool run(SensorCom *sensor, MotorCom *motor){
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
