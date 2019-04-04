#ifndef DETECTION_H
#define DETECTION_H

#include <Arduino.h>

void init_detection();
void set_direction(uint8_t dir);
byte get_detection();

#endif