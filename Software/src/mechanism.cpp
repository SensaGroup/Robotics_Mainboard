#include <Arduino.h>
#include "mechanism.h"

void push_out_left(void) { 
    actuator_stepper_move(PACK_STEPS, STEPPER_FORWARD, SCP_LEFT_STEPPER_ID);
}

void pull_back_left(void) {
    actuator_stepper_move(PACK_STEPS, STEPPER_BACKWARD, SCP_LEFT_STEPPER_ID);
}

void push_out_right(void) { 
    actuator_stepper_move(PACK_STEPS, STEPPER_FORWARD, SCP_RIGHT_STEPPER_ID);
}

void pull_back_right(void) {
    actuator_stepper_move(PACK_STEPS, STEPPER_BACKWARD, SCP_RIGHT_STEPPER_ID);
}

void servo_grab_left(void) {
   move_servo_1(SERVO_GRAB_LEFT_POS);
}

void servo_grab_right(void) {
    move_servo_1(SERVO_GRAB_RIGHT_POS);
}

void servo_grab(int side) {
    if(side == SCP_LEFT_STEPPER_ID) {
        servo_grab_left();
    } else if(side == SCP_RIGHT_STEPPER_ID) {
        servo_grab_right();
    }
} 
