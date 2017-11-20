#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

#include <ctime>
#include "sensor_com.h"
#include "motor_com.h"

using namespace std;

class ControlSystem{
private:

	SensorCom * sensor;
	MotorCom  * motor;

        LINE_STATE  line_state;
	int 	    line_pos;	    	// line position (right => negative)
	double 	    old_line_pos;       // old position for delta error

	double 	p_error;		// proportional error
	double 	i_error;		// integrating error
	double 	d_error;		// delta error for derivating term

	clock_t last_sample_time;	// time since last sampling

	//---------------private constants-------------------------
	const float  SAMPLE_TIME = 50;			// time [ms] between samplings
	const int    MAX_TURN 	 = 7;			// maximum turn-setting
	const int    MAX_I_ERROR = MAX_TURN;	// integral anti-windup constant
	const int    SENSOR_MAX  = 127;

	/* idea is for 1 to be max correction of 7 in turn setting */
	const double	K_P = 4,
				 	K_I = 0,
					K_D = 0;

	bool 	initialized = false;

	/* -------------private functions----------------- */

	/* check sampling time and set initialize flag*/
	bool 	is_sampling_time();

	/* samples line position from sensor and computes error-values */
	double 	sample_line_position();

	/* return +/- 1 as direction of arg double val */
	double 	normalize(double val);

	/* limit value val to saturate at magnitude(val) = max_val */
	double ControlSystem::saturate(double val, double max);

	/* the real control_system regulation */
	int 	turn_value();

	/* send command to set turn-speed in motor-unit */
	void 	set_turn_speed(int turn_speed);

public:

	/* constructor */
	ControlSystem(SensorCom *sensor, MotorCom *motor);

	/*  sample and run control_system if:
			. it is time to sample
			. line_state is correct
		the function samples data from sensor
		and sends command to motor-unit

		Return false if nothing was changed    */
	bool run();

};

#endif
