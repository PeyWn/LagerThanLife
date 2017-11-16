/*
 * globals.h
 *
 * Created: 11/8/2017 8:37:16 PM
 *  Author: jesjo430
 */ 

#include "../../lib/avr_util.h"
#include <util/delay.h>

#define F_CPU 16000000 // Avr system clock @ 16Mhz. 
#define DIRECTION_PORT PORTD // Direction port D4 on AVR.

#define NUMBER_OF_MOTORS 8

#define RECEIVE 0 // Definition used when setting half duplex UART direction.
#define TRANSMIT 1 // Definition used when setting half duplex UART direction.

#define PING 0x01
#define READ_DATE 0x02
#define WRITE_DATA 0x03
#define REG_WRITE 0x04
#define ACTION 0x05
#define RESET 0x06
#define SYNC_WRITE 0x07

#define GOAL_POSITION_ADDRESS 0x1E 
#define MOVING_SPEED_ADDRESS 0x20
#define TORQUE_ENABLE_ADDRESS 0x18
#define CW_ANGLE_LIMIT_ADDRESS 0x06
#define CCW_ANGLE_LIMIT_ADDRESS 0x08
#define MAX_TORQUE_ADDRESS 0x22
#define STATUS_RETURN_LEVEL_ADDRESS 0x10
#define RETURN_DELAY_TIME_ADDRESS 0x05
#define LED_ADDRESS 0x19

#define SPEED_0 0x0f
#define SPEED_1 0x1f
#define SPEED_2 0x2f
#define SPEED_3 0x3f
#define SPEED_4 0x4f
#define SPEED_5 0x5f

#define GLOBAL_TORQUE_LIMIT 0x3FF

volatile extern int error1;
volatile extern int error2;
volatile extern int error3;
volatile extern int error4;
volatile extern int error5;
volatile extern int error6;
volatile extern int error7;
volatile extern int error8;

#define CW_LIMIT_1 0x0
#define CCW_LIMIT_1 0x3ff

#define CW_LIMIT_2 0x0
#define CCW_LIMIT_2 0x3ff
#define CW_LIMIT_3 (0x3ff-CCW_LIMIT_2)
#define CCW_LIMIT_3 (0x3ff-CW_LIMIT_2)

#define CW_LIMIT_4 0x0
#define CCW_LIMIT_4 0x3ff
#define CW_LIMIT_5 (0x3ff-CCW_LIMIT_4)
#define CCW_LIMIT_5 (0x3ff-CW_LIMIT_4)

#define CW_LIMIT_6 0xC0
#define CCW_LIMIT_6 0x2ff

#define CW_LIMIT_7 0x0
#define CCW_LIMIT_7 0x3ff

#define CW_LIMIT_8 0x0
#define CCW_LIMIT_8 0x1ff