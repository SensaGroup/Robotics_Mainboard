#include <Arduino.h>
#include "mechanism.h"

// STEPPER
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





// SERVOS
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


void servo_front_left_out() { move_servo_2(SERVO_FRONT_LEFT_OUT_POS); } void servo_front_left_in() { move_servo_2(SERVO_FRONT_LEFT_IN_POS); }
void servo_front_right_out() {  move_servo_3(SERVO_FRONT_RIGHT_OUT_POS); } void servo_front_right_in() { move_servo_2(SERVO_FRONT_RIGHT_IN_POS); }


// SWITCHES
uint8_t switch_front_left_servo()       { return actuator_read_bin(1); }
uint8_t switch_front_right_servo()      { return actuator_read_bin(2); }
uint8_t switch_front_left()             { return actuator_read_bin(3); }
uint8_t switch_front_right()            { return actuator_read_bin(4); }

uint8_t switch_lift_up()                { return actuator_read_bin(5); }
uint8_t switch_lift_center()            { return actuator_read_bin(6); }
uint8_t switch_lift_down()              { return actuator_read_bin(7); }

void lift_up() {
    actuator_move_hbridge(LIFT_SPEED, 0, 1);
    while(switch_lift_up() != LIFT_UP_DETECTED);
    actuator_break_hbridge(1);
}

void lift_down() {
    actuator_move_hbridge(0, LIFT_SPEED, 1);
    while(switch_lift_up() != LIFT_DOWN_DETECTED);
    actuator_break_hbridge(1);
}

void lift_center() {
    if(switch_lift_up() == LIFT_UP_DETECTED) {
        actuator_move_hbridge(0, LIFT_SPEED, 1);
    } else if(switch_lift_down() == LIFT_DOWN_DETECTED) {
        actuator_move_hbridge(LIFT_SPEED, 0, 1);
    }
    while(switch_lift_center() != LIFT_CENTER_DETECTED);
    actuator_break_hbridge(1);
}



