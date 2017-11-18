﻿/*
 * transmisison.h
 *
 * Created: 11/9/2017 11:38:56 AM
 *  Author: jesjo430
 */ 

#include <stdio.h>
#include <string.h>
#include "uart_arm.h"
#include "globals.h"

/* Transmits 0xff 0xff to indicate beginning of packet */ 
void transmit_startbytes();

/* Reads one byte of data from servo with given id, returns char with the data */  
char read_byte(int id, int address);

/* Writes given data in control table of given servo id at given address. 
mode indicates instruction type */
void write_byte(int id, int address, int byte, int mode);

/* Reads two bytes of data from control table of servo with given id at given address 
mode determines with what instruction type */ 
int read_word(int id, int address);

/* Writes two bytes in control table of servo with given id at given address.
Mode determines with which instruction */
void write_word(int id, int address, int word, int mode);

/* Writes four bytes in control table of servo with given id at given address.
Mode determines with which instruction */
void write_long(int id, int address, int word1, int word2, int mode);

/* Changes goal position in control table of servo with given id to given pos with 
given speed. Mode indicates with which instruction type */ 
void move_single_axis(int id, int pos, int speed, char mode);

/* Sends instruction Action to servo with given id */ 
void send_action();

/* Changes goal position in control table of servo with given id's to given pos with
given speed. Uses instruction REG_WRITE and send ACTION when done writing */
void move_double_axis(int id1, int id2, int pos, int speed);

/* Writes 1 to control table of servo with given id */ 
void torque_enable(int id);

/* Writes 0 to all NUMBER_OF_MOTORS control table on address torque_enable */ 
void torque_disable_all(int id);

/* Transmits instruction PING to servo with given id and updates error globals */ 
void update_error_var(int id);

/* Sets all servos to strictly coded positions */  
void go_home_pos(void);

/* Sets all servos to strictly coded positions */  
void go_pos_front(void);

/* Shrinks the claw size of robot aka servo #8. */ 
void grab(void);

/* Opens the claw of the robot aka servo #8 */ 
void release(void);

/* Picks up object in front of platform and returns to home position, is_working during function */ 
void pickup_standard_front(void);

/* Puts down object in front of platform and returns to home position, is_working during function */
void putdown_standard_front(void);

/* Disables torque of all servos */  
void emergency_stop(void);