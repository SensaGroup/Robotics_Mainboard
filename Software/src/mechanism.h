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

// STEPPER
void push_out_left(void);
void pull_back_left(void); 
void push_out_right(void);
void pull_back_right(void); 


// SERVO
void servo_grab(int side);
void move_servo_1(int pos);
void move_servo_2(int pos);
void move_servo_3(int pos);
void move_servo_4(int pos);

void servo_front_left_out();
void servo_front_left_in();
void servo_front_right_out();
void servo_front_right_in();

#define SERVO_FRONT_LEFT_OUT_POS 150
#define SERVO_FRONT_LEFT_IN_POS  40  
#define SERVO_FRONT_RIGHT_OUT_POS 150
#define SERVO_FRONT_RIGHT_IN_POS  40  

// SWITCHES
uint8_t switch_front_left_servo();
uint8_t switch_front_right_servo();
uint8_t switch_front_left();
uint8_t switch_front_right();
uint8_t switch_lift_up();
uint8_t switch_lift_center();
uint8_t switch_lift_down();

// LIFT
#define LIFT_SPEED              5000

#define LIFT_UP_DETECTED        1
#define LIFT_CENTER_DETECTED    1
#define LIFT_DOWN_DETECTED      1

void lift_up();
void lift_down();
void lift_center();

#endif