#include "../../lib/avr_util.h"

#define F_CPU 16000000 // Avr system clock @ 16Mhz. 
#define DIRECTION_PORT PORTD // Direction port D4 on AVR.

#define RECEIVE 0 // Definition used when setting half duplex UART direction.
#define TRANSMIT 1 // Definition used when setting half duplex UART direction.

typedef char ID;
typedef char LENGTH;
typedef char INSTRUCTION;
typedef char PARAMETER;
typedef char CHECKSUM; 

#define PING 0x01
#define READ_DATE 0x02
#define WRITE_DATA 0x03
#define REG_WRITE 0x04
#define ACTION 0x05
#define RESET 0x06
#define SYNC_WRITE 0x07

#define GOAL_POSITION 0x1E 
#define MOVING_SPEED 0x20

#define GLOBAL_SERVO_SPEED 0x30   
