/*  
    **** TESTS FOR SENSOR UNIT ****
*/
#include <assert.h>

#include "globals.h"
#include "line_sensor.h"

void run_tests(){
    
    //Tests for line_center and line_state
    
    bool detected[11] = {0,0,0,0,0,0,0,0,0,0,0};
    assert(calc_line_state(detected, 0) == NONE_DOUBLE);

    detected[0] = 1;
    detected[1] = 1;
    detected[2] = 1;
    detected[3] = 1;
    detected[4] = 1;
    detected[5] = 1;
    detected[6] = 1;
    detected[7] = 1;
    detected[8] = 1;
    detected[9] = 1;
    detected[10] = 1;
    assert(calc_line_state(detected, 11) == CORNER);
    assert(calc_line_center(detected, 11) == 0);

    detected[0] = 0;
    detected[1] = 0;
    detected[2] = 0;
    detected[3] = 0;
    detected[4] = 0;
    detected[5] = 1;
    detected[6] = 0;
    detected[7] = 0;
    detected[8] = 0;
    detected[9] = 0;
    detected[10] = 0;
    assert(calc_line_state(detected, 1) == SINGLE);
    assert(calc_line_center(detected, 1) == 0);

    detected[0] = 0;
    detected[1] = 0;
    detected[2] = 0;
    detected[3] = 0;
    detected[4] = 0;
    detected[5] = 1;
    detected[6] = 1;
    detected[7] = 0;
    detected[8] = 0;
    detected[9] = 0;
    detected[10] = 0;
    assert(calc_line_state(detected, 2) == SINGLE);
    assert(calc_line_center(detected, 2) == 13);

    detected[0] = 1;
    detected[1] = 1;
    detected[2] = 1;
    detected[3] = 1;
    detected[4] = 0;
    detected[5] = 1;
    detected[6] = 0;
    detected[7] = 0;
    detected[8] = 0;
    detected[9] = 0;
    detected[10] = 0;
    assert(calc_line_state(detected, 5) == CORNER);
    assert(calc_line_center(detected, 5) == -71);

    detected[0] = 1;
    detected[1] = 1;
    detected[2] = 1;
    detected[3] = 1;
    detected[4] = 1;
    detected[5] = 1;
    detected[6] = 1;
    detected[7] = 0;
    detected[8] = 1;
    detected[9] = 1;
    detected[10] = 1;
    assert(calc_line_state(detected, 10) == CORNER);
    assert(calc_line_center(detected, 10) == -5);

    detected[0] = 1;
    detected[1] = 1;
    detected[2] = 1;
    detected[3] = 1;
    detected[4] = 0;
    detected[5] = 0;
    detected[6] = 0;
    detected[7] = 0;
    detected[8] = 0;
    detected[9] = 0;
    detected[10] = 0;
    assert(calc_line_state(detected, 4) == CORNER);
    assert(calc_line_center(detected, 4) == -89);

    detected[0] = 1;
    detected[1] = 1;
    detected[2] = 1;
    detected[3] = 0;
    detected[4] = 0;
    detected[5] = 0;
    detected[6] = 0;
    detected[7] = 1;
    detected[8] = 1;
    detected[9] = 1;
    detected[10] = 1;
    assert(calc_line_state(detected, 7) == NONE_DOUBLE);
    assert(calc_line_center(detected, 7) == 7);

    detected[0] = 0;
    detected[1] = 0;
    detected[2] = 0;
    detected[3] = 0;
    detected[4] = 1;
    detected[5] = 0;
    detected[6] = 0;
    detected[7] = 1;
    detected[8] = 1;
    detected[9] = 0;
    detected[10] = 0;
    assert(calc_line_state(detected, 3) == NONE_DOUBLE);
    assert(calc_line_center(detected, 3) == 34);
}