#ifndef MECHANISM_H
#define MECHANISM_H

#include <Arduino.h>
#include "system.h"

#define SCP_LEFT_STEPPER_ID     1
#define SCP_RIGHT_STEPPER_ID    2

#define STEPPER_FORWARD         1
#define STEPPER_BACKWARD        0

#define PACK_STEPS              640

#define SERVO_GRAB_RIGHT_POS     180
#define SERVO_GRAB_LEFT_POS     0

void push_out_left(void);
void pull_back_left(void); 
void push_out_right(void);
void pull_back_right(void); 

void servo_grab(int side);

void move_servo_1(int pos);
void move_servo_2(int pos);
void move_servo_3(int pos);
void move_servo_4(int pos);

#endif