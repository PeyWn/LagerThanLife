#include <stdio.h>
#include "uart_arm.h"
#include "globals.h"
#include "receive.h"

void receive_status_packet(Packet *data)
{   
    data->start1 = receive();
    data->start2 = receive();
    data->id     = receive();
    data->len    = receive();    // length: #params + 2
    data->error  = receive();

    for(int i = 0; i < data->len - 2; i++){
        data->params[i] = receive();
    }
    data->checksum = receive();
}

int get_servo_pos(int id){
    flush_UDR1_receive();
    Packet data;
    char pos_l, pos_h;
    
    send_read_msg(id, PRESENT_POS_ADDRESS, 2);
    receive_status_packet(&data);
    pos_l = data.params[0];
    
    pos_h = data.params[1];
    
    int pos = ((pos_h<<8) | pos_l);

    return pos;
}
