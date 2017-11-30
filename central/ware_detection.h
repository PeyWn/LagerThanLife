#include "motor_com.h"
using namespace std;

/* Turns and drives robot forward until both ware sensors sees ware, when that;
returns 1
*/
int center_ware(pair<bool, bool> sensor, MotorCom* wheels);
