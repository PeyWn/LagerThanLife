#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

#include <ctime>
#include "sensor_com.h"
#include "motor_com.h"

using namespace std;

class ControlSystem{
private:
    /*-----FIELDS-------------------------------------------------------------------------------*/
    SensorCom  *sensor;
    MotorCom   *motor;

    bool        initialized = false;

    LINE_STATE  line_state;
    double      line_pos;       // line position (right => negative)
    double      old_line_pos;   // old position for delta error

    double      p_error;        // proportional error
    double      i_error;        // integrating error
    double      d_error;        // delta error for derivating term

    clock_t last_sample_time;   // time since last sampling

    /*-----CONSTANTS----------------------------------------------------------------------------*/
    const float  SAMPLE_TIME = 50;          // time [ms] between samplings
    const float  MAX_TURN    = 7;           // maximum turn-speed possible in motor-unit
    const float  MAX_I_ERROR = MAX_TURN;    // integral anti-windup constant
    const float  SENSOR_MAX  = 127;

    /* idea is for 1 to be max correction of 7 in turn setting */
    const double    K_P = 1,
	                K_I = 0 * (SAMPLE_TIME/50), // scales by time
	                K_D = 0 / (SAMPLE_TIME*50); // scales by time

    /*-----FUNCTIONS----------------------------------------------------------------------------*/

    /*
    Evaluate if time to sample:
        Set initialized flag if not initialized and return true. Otherwise: compute time since last
        sampling and return true if value is greater than SAMPLING_TIME, false otherwise.
    Params:
        only uses private class-variales
    Return:
        if it is time to sample (bool)                                                          */
    bool is_sampling_time();

    /*
    Sample line position:
        Requests value from sensor-unit via the sensor-class-pointer and computes the errors
        p_error, i_error and d_error. Anti-windup is used for the integrating i_error by
        saturating at MAX_I_ERROR. d_error is computed as the change of error since last
        sampling.
    Return:
        only stores errors in p_error, i_error, d_error                                         */
    void sample_line_position(float line_center);

    /*
    Output of the PID-controller:
        Compute turn-value based on errors stored in local variables p-, d- and i_error. The
        turn value is the negative sum of errors p_error, i_error, d_error each scaled with the
        gains K_P, K_I and K_D respectively. The resulting value is saturated at the MAX_TURN
        value -- meant to correspond to the maximum possible turn-speed that can be set in the
        motor-unit.
    Return:
        the correcting speed-setting that motor-unit should be set to.                          */
    int turn_value();

    /*
    Set turn speed of the robot-platform:
        sends a command to the motor-unit for setting the turn-speed of the wheels
        (left/right)                                                                            */
    void set_turn_speed(int turn_speed);

    /*
    Normalize a scalar
    Params:
        double val -- scalar to normalize
    Return:
        the normalized value (double)                                                           */
    double normalize(double val);

    /*
    Saturation of a value
    Params:
        double val -- value to be saturated
        double max -- max-value to saturate at
    Return:
        saturated value (double)                                                                */
    double  saturate(double val, double max);

public:

    /*
    Constructor for the ControlSystem class:
        initialize a new object of the ControlSystem class.
    Params:
        SensorCom *sensor -- pointer for communicating with the sensor-unit
        MotorCom *motor -- pointer for communication with the motor-unit
    Return:
        new instance of the ControlSystem class                                                 */
    ControlSystem(MotorCom *motor);

    /*
    Run one iteration of the control-system:
        Sample sensor-value if it is time to sample. Compute errors if the line_state is
        correct and correct the error by setting the turn-speed of the robot platform.
    Return:
        whether a sampling->correction was done by the control-system or not (bool)             */
    bool run(float line_center);
};

#endif
