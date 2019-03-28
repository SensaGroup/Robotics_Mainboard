#include "actuator.h"

Servo servo_1;  uint8_t servo1_current;
Servo servo_2;  uint8_t servo2_current;
Servo servo_3;  uint8_t servo3_current;
Servo servo_4;  uint8_t servo4_current;

uint8_t valve_pins[6]   = {36, 35, 34, 33, 32, 31};
uint8_t bin_pins[6]     = {A0, A1, A2, A3, A4, A5};

bool init_actuator(void) {

    pinMode(RELAY1_PIN, OUTPUT); digitalWrite(RELAY1_PIN, LOW);
    pinMode(RELAY2_PIN, OUTPUT); digitalWrite(RELAY2_PIN, LOW);

    servo_1.attach(10); servo_2.attach(11); servo_3.attach(12); servo_4.attach(13);

    for(int i=0; i<6; i++) {
        pinMode(valve_pins[i], OUTPUT);
        digitalWrite(valve_pins[i], LOW);

        pinMode(bin_pins[i], INPUT);
    }

    byte ping_data[8] = {'P', 1, 0, 0, 0, 0, 0, 0};

    can_send(ACTUATOR_CAN_ID, ping_data);
   // Serial.println("Sent...");
    //Serial.println(can_wait_for_finish());
    //return true;
    if(can_wait_for_finish() == 0xff) {
        return true;
    } else {
        return false;
    }
}

uint8_t actuator_read_switch(uint8_t _switch) {

    // 1 - 8
    byte switch_data[8] = {'S', _switch, 0, 0, 0, 0, 0, 0};

    can_send(ACTUATOR_CAN_ID, switch_data);
    return can_wait_for_finish();

}

uint8_t actuator_move_hbridge(int a, int b, byte num) {

    byte hbridge_data[8] = {'H', 'M', (byte)(a >> 8), (byte)(a & 0xFF), (byte)(b >> 8), (byte)(b & 0xFF), num};

    can_send(ACTUATOR_CAN_ID, hbridge_data);
    return can_wait_for_finish();
}

uint8_t actuator_break_hbridge(byte num) {

    byte hbridge_data[8] = {'H','B', num, 0, 0, 0, 0, 0};

    can_send(ACTUATOR_CAN_ID, hbridge_data);
    return can_wait_for_finish();

}

uint8_t actuator_hbridge_timed(int dir, int achieve, int time, byte num) {
    
    byte _num;
    
    if(num == 0) { _num = 'T'; } else { _num = 't'; }

    byte hbridge_data[8] = {'H', _num, (byte)(dir >> 8), (byte)(dir & 0xFF), (byte)(achieve >> 8), (byte)(achieve & 0xFF), (byte)(time >> 8), (byte)(time & 0xFF)};

    can_send(ACTUATOR_CAN_ID, hbridge_data);
    return can_wait_for_finish();

}

uint8_t actuator_stepper_enable(byte status, byte num) {

    byte stepper_data[8] = {'s', 'E', status, num, 0, 0, 0, 0}; 

    can_send(ACTUATOR_CAN_ID, stepper_data);
    return can_wait_for_finish();

}

uint8_t actuator_stepper_rpm(int rpm, byte num) {

    byte stepper_data[8] = {'s', 'R', (byte)(rpm >> 8), (byte)(rpm & 0xFF), num};

    can_send(ACTUATOR_CAN_ID, stepper_data);
    return can_wait_for_finish();

}

uint8_t actuator_stepper_move(int steps, byte dir, byte num) {

    byte stepper_data[8] = {'s', 'M', (byte)(steps >> 8), (byte)(steps & 0xFF), dir, num};

    can_send(ACTUATOR_CAN_ID, stepper_data);
    Serial.print("sent...");
    return can_wait_for_finish();
}

uint8_t actuator_relay_toggle(byte num) {

    byte using_pin;

    if(num == 1) {
        using_pin = RELAY1_PIN;
    } else {
        using_pin = RELAY2_PIN;
    }

    digitalWrite(using_pin, !digitalRead(using_pin));

    return 0;

}

uint8_t actuator_update_servo(byte num, uint8_t pos) {

    switch(num) {
        case 1:
            servo_1.write(pos);
            servo1_current = pos;
            break;
        case 2:
            servo_2.write(pos);
            servo2_current = pos;
            break;
        case 3:
            servo_3.write(pos);
            servo3_current = pos;
            break;
        case 4:
            servo_3.write(pos);
            servo3_current = pos;
            break;
    }

    return 0;

}

uint8_t actuator_update_valves(uint8_t num, uint8_t status) {
    digitalWrite(valve_pins[num-1], status);
}

uint8_t actuator_read_bin(uint8_t num) {
    return digitalRead(bin_pins[num-1]);
}