#ifndef LIDAR_H
#define LIDAR_H

#define LIDAR_CAN_ID 0xC4

bool    init_lidar(void);
uint8_t lidar_turnon(void);
uint8_t lidar_turnoff(void);
uint8_t lidar_range(int range_upper_in_cm, int range_lower_in_cm);
uint8_t lidar_direction(uint8_t dir);
uint8_t lidar_detected(void);

#endif