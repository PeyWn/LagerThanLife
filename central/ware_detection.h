#include "motor_com.h"
using namespace std;

/* Turns and drives robot forward until both ware sensors sees ware, when that;
returns true
*/
bool center_ware(pair<bool, bool> sensor, MotorCom* wheels);
