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

void transmit_startbits();
void write_byte(int id, int address, int byte, int mode);
void write_word(int id, int address, int word, int mode);
void write_long(int id, int address, int word1, int word2, int mode);
void move_single_axis(int id, int pos, int speed, char mode);
void send_action();
void move_double_axis(int id1, int id2, int pos, int speed);
void torque_enable(int id);