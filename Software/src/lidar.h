#ifndef LIDAR_H
#define LIDAR_H

#define LIDAR_CAN_ID 0xC4

bool    init_lidar(void);
uint8_t lidar_turnon(void);
uint8_t lidar_turnoff(void);
uint8_t lidar_range(uint8_t range_in_cm);
uint8_t lidar_speed(uint8_t speed);
uint8_t lidar_direction(uint8_t dir);
uint8_t lidar_detected(void);

#endif