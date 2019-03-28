#include <Arduino.h>
#include "lidar.h"
#include "can.h"

/*
 * Function:        bool init_lidar(void) 
 * Description:     init lidar
 * Parameters:      x
 */
bool init_lidar(void) {

    byte ping_data[8] = {'P', 1, 0, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, ping_data);
    if(can_wait_for_finish() == 0xff) {
        return true;
    } else {
        return false;
    }

} // end of init_lidar()

/*
 * Function:        uint8_t lidar_turnon(void) 
 * Description:     turn on lidar
 * Parameters:      x
 */
uint8_t lidar_turnon(void) {

    byte lidar_data[8] = {'c', 'S', 1, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

} // end of lidar_turnon()

/*
 * Function:        uint8_t lidar_turnoff(void)
 * Description:     lidar turn off
 * Parameters:      x
 */
uint8_t lidar_turnoff(void) {

    byte lidar_data[8] = {'c', 'S', 0, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

} // end of lidar_turnoff()

/*
 * Function:        uint8_t lidar_range(uint8_t range_in_cm)
 * Description:     set the range 
 * Parameters:      uint8_t range_in_cm - set the range on which it will detect
 */
uint8_t lidar_range(uint8_t range_in_cm) {

    byte lidar_data[8] = {'s', 'R', range_in_cm, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

} // end of lidar_range(...)

/*
 * Function:    uint8_t lidar_speed(uint8_t speed) 
 * Description: set the lidar speed (the speed of the motor)
 * Parameters:  uint8_t speed - the speed 
 * Warning:     not making a change for now... it is preset
 */
uint8_t lidar_speed(uint8_t speed) {

    byte lidar_data[8] = {'s', 'S', speed, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

} // end of lidar_speed(...)

/*
 * Function:        uint8_t lidar_direction(uint8_t dir)
 * Description:     set the lidars direction, dependent on which side the robot will be moving
 * Parameters:      uint8_t dir - the direction we are going
 */
uint8_t lidar_direction(uint8_t dir) {

    // 1 -> FORWARD 0 -> BACKWARD

    byte lidar_data[8] = {'s', 'D', dir, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

} // end of lidar_direction(...)

/*
 * Function:    uint8_t lidar_detected(void)   
 * Description: check if the lidar has detected
 * Parameters:  x
 */
uint8_t lidar_detected(void) {

    byte lidar_data[8] = {'r', 0, 0, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

} // end of lidar_detected(...)
