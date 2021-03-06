#ifndef GLOBALS_H
#define GLOBALS_H

#include <util/delay.h>
#include "../../lib/avr_util.h"

#define F_CPU 16000000 // Avr system clock @ 16Mhz.
#define DIRECTION_PORT PORTD // Direction port D4 on AVR.

#define NUMBER_OF_MOTORS 8
#define NUMBER_OF_AXIS 6

#define RECEIVE 0 // Definition used when setting half duplex UART direction.
#define TRANSMIT 1 // Definition used when setting half duplex UART direction.

/* Instructions for AX-12 servos */
#define PING 0x01
#define READ_DATA 0x02
#define WRITE_DATA 0x03
#define REG_WRITE 0x04
#define ACTION 0x05
#define RESET 0x06
#define SYNC_WRITE 0x07

/* Control table addresses for AX-12 servos */
#define GOAL_POSITION_ADDRESS 0x1E
#define MOVING_SPEED_ADDRESS 0x20
#define TORQUE_ENABLE_ADDRESS 0x18
#define CW_ANGLE_LIMIT_ADDRESS 0x06
#define CCW_ANGLE_LIMIT_ADDRESS 0x08
#define MAX_TORQUE_ADDRESS 0x22
#define STATUS_RETURN_LEVEL_ADDRESS 0x10
#define RETURN_DELAY_TIME_ADDRESS 0x05
#define LED_ADDRESS 0x19
#define ID_ADDRESS 0x03
#define PRESENT_POS_ADDRESS 0x24

/* Global speeds for servo movements */
#define SPEED_0 0x3f
#define SPEED_1 0x4f
#define SPEED_2 0x5f
#define SPEED_3 0x6f
#define SPEED_4 0x7f
#define SPEED_5 0x8f
#define SPEED_MANUAL 0x1f;
#define SPEED_MAX 0x3ff

/* Globals values for control table*/
#define GLOBAL_TORQUE_LIMIT 0x3FF

#define STEPS_PER_TICK 10

volatile extern int front_pos[6];
volatile extern	int home_pos[6];

/* Angular limits for each AX-12 servo */
#define CW_LIMIT_1 0x0
#define CCW_LIMIT_1 0x3ff
#define CW_LIMIT_2 222
#define CCW_LIMIT_2 803
#define CW_LIMIT_3 (0x3ff-CCW_LIMIT_2)
#define CCW_LIMIT_3 (0x3ff-CW_LIMIT_2)
#define CW_LIMIT_4 210
#define CCW_LIMIT_4 830
#define CW_LIMIT_5 (0x3ff-CCW_LIMIT_4)
#define CCW_LIMIT_5 (0x3ff-CW_LIMIT_4)
#define CW_LIMIT_6 210
#define CCW_LIMIT_6 793
#define CW_LIMIT_7 0x0
#define CCW_LIMIT_7 0x3ff
#define CW_LIMIT_8 0x0
#define CCW_LIMIT_8 0x1ff

volatile extern bool do_stop;
volatile extern bool do_pickup;
volatile extern bool do_putdown;

#endif
