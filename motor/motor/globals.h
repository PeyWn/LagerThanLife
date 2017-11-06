#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "../../lib/avr_util.h"

typedef struct
{
    static int STARTBIT_0 = 0xFF,
	       STARTBIT_1 = 0xFF;
	   int ID,
	       LENGHT,
	       INSTRUCTION,
	       PARAMETER_1, //CHECK
	       //...
	       PARAMETER_N,
	       CHECK_SUM;
}INSTRUCTION_PACKET;

typedef struct
{
    static int STARTBIT_0 = 0xFF,
               STARTBIT_1 = 0xFF;
           int ID,
	       LENGHT,
               ERROR,
      	       PARAMETER_1, //CHECK
       	       //...
  	       PARAMETER_N,
  	       CHECK_SUM;
}STATUS_PACKET;

#endif /* GLOBALS_H_ */
