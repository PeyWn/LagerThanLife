#include "motor_com.h"
#include <stdexcept>
#include <iostream>

MotorCom::MotorCom(string motor_interface) : com(motor_interface) {}

DRIVE_STATUS MotorCom::get_drive_status(){
    com.send_msg(GET_DRIVE_STATUS);

    int status = com.read_msg();
    status &= 0x0F; //Mask out lower 4 bits
    return static_cast<DRIVE_STATUS>(status);
}

pair<TURN_STATUS, int> MotorCom::get_turn_status(){
    com.send_msg(GET_TURN_STATUS);
    cout << "Sent" << endl;

    int status = com.read_msg();
    status &= 0x0F; //Mask out lower 4 bits

    TURN_STATUS direction;
    int speed;

    if(status == 0){
        //0000, not turning
        direction = NONE;
        speed = 0;
    }
    else if((status >> 3) == 0){
        //right
        direction = RIGHT;
        speed = status;
    }
    else{
        //direction
        direction = LEFT;
        speed = status - 7;
    }

    return make_pair(direction, speed);
}

bool MotorCom::arm_active(){
    com.send_msg(GET_ARM_STATUS);

    int status = com.read_msg();
    status &= 0x0F; //Mask out lower 4 bits
    return (status == 1);
}

void MotorCom::drive(DRIVE_STATUS direction){
    int msg = DRIVE; //ID, top 4 bits
    msg += direction;

    com.send_msg(msg);
}

void MotorCom::turn(TURN_STATUS direction, int speed){
    if(speed < 0 || speed > 7){
        throw invalid_argument("Speed not within bounds.");
    }

    int msg = TURN;

    int parameter;

    if(direction == NONE || speed == 0){
        //None
        parameter = 0;
    }
    else if(direction == RIGHT){
        //Right
        parameter = speed;
    }
    else{
        //Left
        parameter = 7 + speed;
    }

    msg += parameter;

    com.send_msg(msg);
}

void MotorCom::set_arm_speed(int speed){
    if(speed < 0 || speed > 15){
        throw invalid_argument("Speed not withing bounds.");
    }

    int msg = CONFIGURE_ARM;
    msg += speed;

    com.send_msg(msg);
}

void MotorCom::perform_arm_macro(ARM_MACRO move){
    int msg = ARM_PERFROM_MACRO;
    msg += move;

    com.send_msg(msg);
}

void MotorCom::control_claw(bool close){
    int msg = CONTROL_CLAW;

    if(!close){
        msg += 1;
    }

    com.send_msg(msg);
}

void MotorCom::move_arm(ARM_DIRECTION direction){
    int msg = MANUAL_ARM_CONTROL;
    msg += direction;

    com.send_msg(msg);
}

void MotorCom::stop_arm(ARM_DIRECTION direction){
    int msg = MANUAL_ARM_CONTROL;
    msg += direction + 1;

    com.send_msg(msg);
}