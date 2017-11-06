/*
 * control_table.c
 *
 * Created: 2017-11-04 18:09:51
 *  Author: Jesper
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include "control_table.h"

/*

typedef struct
{
	int MODEL_NUMBER_L = 0x00,
		MODEL_NUMBER_H = 0x01,
		VERSION_FIRMWARE = 0x02,
		ID = 0x03,
		BAUD_RATE = 0x04,
		RETURN_DELAY_TIME = 0x05,
		CW_ANGLE_LIMIT_L = 0x06,
		CW_ANGLE_LIMIT_H = 0x07,
		CCW_ANGLE_LIMIT_L = 0x08,
		CCW_ANGLE_LIMIT_H = 0x09,
		HIGHEST_LIMIT_TEMP = 0x0B,
		LOWEST_LIMIT_VOLTAGE = 0x0C,
		HIGHEST_LIMIT_VOLTAGE = 0x0D,
		MAX_TORQUE_L = 0x0E,
		MAX_TORQUE_H = 0x0F,
		STATUS_RETURN_LEVEL = 0x10,
		ALARM_LED = 0x11,
		ALARM_SHUTDOWN = 0x12,
		DOWN_CALIBRATION_L = 0x14,
		DOWN_CALIBRATION_H = 0x15,
		UP_CALIBRATION_L = 0x16,
		UP_CALIBRATION_H = 0x17,
		TORQUE_ENABLE = 0x18,
		LED = 0x19,
		CW_COMPLIANCE_MARGIN = 0x1A,
		CCW_COMPLIANCE_MARGIN = 0x1B,
		CW_COMPLIANCE_SLOPE = 0x1C,
		CCW_COMPLIANCE_SLOPE = 0x1D,
		GOAL_POSITION_L = 0x1E,
		GOAL_POSITION_H = 0x1F,
		MOVING_SPEED_L = 0x20,
		MOVING_SPEED_H = 0x21,
		TORQUE_LIMIT_L = 0x22,
		TORQUE_LIMIT_H = 0x23,
		PRESENT_POSITION_L = 0x24,
		PRESENT_POSITION_H = 0x25,
		PRESENT_SPEED_L = 0x26,
		PRESENT_SPEED_H = 0x27,
		PRESENT_LOAD_L = 0x28,
		PRESENT_LOAD_H = 0x29,
		PRESENT_VOLTAGE = 0x2A,
		PRESSENT_TEMPERATURE = 0x2B,
		REGISTERED_INStruction = 0X2C,
		MOVING = 0x2E,
		LOCK = 0x2F,
		PUNCH_L = 0x30,
		PUNCH_H = 0x31;
}  CONTROL_TABLE_ADDRESSES;

typedef struct
{
	int MODEL_NUMBER_L = 0x0C,
		MODEL_NUMBER_H = 0x00,
		VERSION_FIRMWARE = nullptr,
		ID = 0x01,
		BAUD_RATE = 0x01,
		RETURN_DELAY_TIME = 0xFA,
		CW_ANGLE_LIMIT_L = 0x00,
		CW_ANGLE_LIMIT_H = 0x00,
		CCW_ANGLE_LIMIT_L = 0xFF,
		CCW_ANGLE_LIMIT_H = 0x03,
		HIGHEST_LIMIT_TEMP = 0x55,
		LOWEST_LIMIT_VOLTAGE = 0x3C,
		HIGHEST_LIMIT_VOLTAGE = 0xBE,
		MAX_TORQUE_L = 0xFF,
		MAX_TORQUE_H = 0x03,
		STATUS_RETURN_LEVEL = 0x02,
		ALARM_LED = 0x04,
		ALARM_SHUTDOWN = 0x04,
		DOWN_CALIBRATION_L = nullptr,
		DOWN_CALIBRATION_H = nullptr,
		UP_CALIBRATION_L = nullptr,
		UP_CALIBRATION_H = nullptr,
		TORQUE_ENABLE = 0x00,
		LED = 0x00,
		CW_COMPLIANCE_MARGIN = 0x00,
		CCW_COMPLIANCE_MARGIN = 0x00,
		CW_COMPLIANCE_SLOPE = 0x20,
		CCW_COMPLIANCE_SLOPE = 0x20,
		GOAL_POSITION_L = nullptr, //CHECK
		GOAL_POSITION_H = nullptr, //CHECK
		MOVING_SPEED_L = 0x00,
		MOVING_SPEED_H = 0x00,
		TORQUE_LIMIT_L = nullptr, //CHECK
		TORQUE_LIMIT_H = nullptr, //CHECK
		PRESENT_POSITION_L = nullptr,
		PRESENT_POSITION_H = nullptr,
		PRESENT_SPEED_L = nullptr,
		PRESENT_SPEED_H = nullptr,
		PRESENT_LOAD_L = nullptr,
		PRESENT_LOAD_H = nullptr,
		PRESENT_VOLTAGE = nullptr,
		PRESSENT_TEMPERATURE = nullptr,
		REGISTERED_INSTRUCTION = 0X00,
		MOVING = 0x00,
		LOCK = 0x00,
		PUNCH_L = 0x20,
		PUNCH_H = 0x00;
		
		
}  CONTROL_TABLE;
*/
