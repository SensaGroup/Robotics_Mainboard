#include <Arduino.h>
#include "lidar.h"
#include "can.h"

bool init_lidar(void) {

    byte ping_data[8] = {'P', 1, 0, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, ping_data);
    if(can_wait_for_finish() == 0xff) {
        return true;
    } else {
        return false;
    }

}

uint8_t lidar_turnon(void) {

    byte lidar_data[8] = {'C', 'S', 1, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

}

uint8_t lidar_turnoff(void) {

    byte lidar_data[8] = {'C', 'S', 0, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

}

uint8_t lidar_range(uint8_t range_in_cm) {

    byte lidar_data[8] = {'s', 'R', range_in_cm, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

}

uint8_t lidar_speed(uint8_t speed) {

    byte lidar_data[8] = {'s', 'S', speed, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

}

uint8_t lidar_direction(uint8_t dir) {

    // 1 -> FORWARD 0 -> BACKWARD

    byte lidar_data[8] = {'s', 'D', dir, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

}

uint8_t lidar_detected(void) {

    byte lidar_data[8] = {'S', 0, 0, 0, 0, 0, 0, 0};

    can_send(LIDAR_CAN_ID, lidar_data);

    return can_wait_for_finish();

}
