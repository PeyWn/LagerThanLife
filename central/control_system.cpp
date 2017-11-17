/*-----------------in main-------------------*/

if(line_state == 1 && central_state == DRIVING)
	follow_line(&sensor, &motor);

/*----------------in control_system.c--------*/

#include <ctime>

bool initialized = false;
double line_pos;	    // line position (right => negative)
double old_line_pos; 	// old position for delta error

double p_error;		// proportional error
double i_error;		// integrating error
double d_error;		// delta error for derivating term

const double
	K_p = 1,		// idea is for 1 to be max correction of 7 in turn setting
	K_i = 0,
	K_d = 0;

clock_t last_sample_time;	 	// time since last sampling

const float sample_time = 30;	// time between runs (sampling => new turn value)
const int 	max_turn 	= 7;

/* get a value between -7 and +7 from lineposition exactly error*/
line_pos;

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
	return (int)round(-(K_p*p_error + K_i*i_error + K_d*d_error), 0);
}

double update_error(){
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

/* sample and run control_system if time is up */
bool follow_line(struct *sensor, struct *motor){
	/* return false if not run */
	if(!is_sampling_time)
		return false;

	update_error();
	turn_value();
}
