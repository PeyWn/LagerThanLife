/*  
    **** TESTS FOR SENSOR UNIT ****
*/

#include "globals.h"
#include <assert.h>

#define __ASSERT_USE_STDERR 

//line_center calculation
void run_tests(){
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
}