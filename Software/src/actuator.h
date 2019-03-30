#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "can.h"
#include <Servo.h>

#define ACTUATOR_CAN_ID 0xD4

#define RELAY1_PIN 8
#define RELAY2_PIN 9

bool    init_actuator(void);
uint8_t actuator_read_switch(uint8_t _switch);
uint8_t actuator_move_hbridge(int a, int b, byte num);
uint8_t actuator_break_hbridge(byte num);
uint8_t actuator_hbridge_timed(int dir, int achieve, int time, byte num);
uint8_t actuator_stepper_enable(byte status, byte num);
uint8_t actuator_stepper_rpm(int rpm, byte num);
uint8_t actuator_stepper_move(unsigned int steps, int dir, int num);

uint8_t actuator_relay_toggle(byte num);
uint8_t actuator_update_servo(int num, int pos);
uint8_t actuator_update_valves(uint8_t num, uint8_t status);
uint8_t actuator_read_bin(uint8_t num);

#endif