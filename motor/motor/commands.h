﻿/*
 * commands.c
 *
 * Created: 11/9/2017 11:38:56 AM
 *  Author: jesjo430
 */ 

#include <stdio.h>
#include <string.h>
#include "uart_arm.h"
#include "globals.h"

void move_singel(int id, int pos, int speed, char mode);
void move_double(int id1, int id2, int pos, int speed);