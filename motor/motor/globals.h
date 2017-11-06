#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "../../lib/avr_util.h"

typedef struct
{
		   int STARTBIT_0,
			   STARTBIT_1,
			   ID,
			   LENGHT,
			   INSTRUCTION,
			   PARAMETERS[100],
			   CHECK_SUM;
}INSTRUCTION_PACKET;

typedef struct
{
           int STARTBIT_0,
               STARTBIT_1,
               ID,
			   LENGHT,
               ERROR,
      	       PARAMETER_1, //CHECK
       	       //...
  			   PARAMETER_N,
  			   CHECK_SUM;
}STATUS_PACKET;

#endif /* GLOBALS_H_ */
