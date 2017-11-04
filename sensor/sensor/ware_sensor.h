#ifndef WARE_SENSOR_H_
#define WARE_SENSOR_H_

/*
Read values from ware sensors and update ware_seen accordingly
*/
void update_ware_seen();

/*
Calibarete waresensor and write the values to array distance_blocked
*/
void calibrate_waresensor();

#endif /* WARE_SENSOR_H_ */