/*
 * init_arm.h
 *
 * Created: 2017-11-04 17:23:08
 *  Author: Jesper
 */ 

/* Initializes input and output of avr, sets direction of IO ports. */ 
void init_IO();

/* Writes angular limits to every servo */ 
void set_limits(void);

/* Writes GLOBAL_TORQUE_LIMIT to all servos */ 
void set_torque(void);

/* Writes in control table for return delay level to 2 for all servos */ 
void set_status_return_level(void);

/* Sets control table for return delay time to 10us (2*transmission) for all servos */ 
void set_return_delay_time(void);