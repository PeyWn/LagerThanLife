/*
 * receive.h
 *
 * Created: 11/10/2017 9:42:40 AM
 *  Author: jesjo430
 */ 
#ifndef RECEIVE_H_
#define RECEIVE_H_

/* status packet */
typedef struct Packet {
    char  start1;
    char  start2;
    char  id;
    char  len;
    char  error;
    char  params[10];
    char  checksum;
} Packet;

const Packet NO_STATUS_PACKET;

/* Reads incoming data, stores errors in globals and returns first received parameter */  
void receive_status_packet();

int get_servo_pos(int id);
#endif