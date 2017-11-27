/*
 * receive.c
 *
 * Created: 11/10/2017 9:42:17 AM
 *  Author: jesjo430
 */ 

#include <stdio.h>
#include "uart_arm.h"
#include "globals.h"
#include "receive.h"

Packet receive_status_packet()
{
    volatile Packet data;   // fragile packet <3
    
    volatile char test = 0;
    
    data.start1 = receive();
    
    test = 1;
    
    data.start2 = receive();
    data.id     = receive();
    data.len    = receive();    // length: #params + 2
    data.error  = receive();

    char temp[data.len];
    for(int i = 0; i < data.len - 2; i++){
        data.params[i] = receive();
    }
    data.checksum = receive();

	return data; 
}
