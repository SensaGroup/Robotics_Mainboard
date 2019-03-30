#include "actuator.h"
#include "mechanism.h"

Servo servo_1;  uint8_t servo1_current;
Servo servo_2;  uint8_t servo2_current;
Servo servo_3;  uint8_t servo3_current;
Servo servo_4;  uint8_t servo4_current;

uint8_t valve_pins[6]   = {36, 35, 34, 33, 32, 31};
uint8_t bin_pins[2]     = { A4, A5};
/*
 servo_1.write(0);
    delay(1000);
    servo_1.write(180);
    */

void move_servo_1(int pos) {
    servo_1.write(pos);
}
void move_servo_2(int pos) {
    servo_2.write(pos);
}
void move_servo_3(int pos) {
    servo_3.write(pos);
}
void move_servo_4(int pos) {
    servo_4.write(pos);
}

/*
 * Function:    bool init_actuator(void)
 * Description: init all actuators + can bus board
 */
bool init_actuator(void) {

    // setup main board relays
    pinMode(RELAY1_PIN, OUTPUT); digitalWrite(RELAY1_PIN, LOW);
    pinMode(RELAY2_PIN, OUTPUT); digitalWrite(RELAY2_PIN, LOW);

    // attach all servos
    servo_1.attach(10); servo_2.attach(11); servo_3.attach(12); servo_4.attach(13);
    move_servo_1(0);
    delay(1000);
    move_servo_1(180);
    
    // setup inputs and valve connectors
    for(int i=0; i<6; i++) {
        pinMode(valve_pins[i], OUTPUT);
        digitalWrite(valve_pins[i], LOW);

        pinMode(bin_pins[i], INPUT);
    }

    pinMode(A0, OUTPUT);    // dir right
    pinMode(A1, OUTPUT);    // step right
    pinMode(A2, OUTPUT);    // dir left
    pinMode(A3, OUTPUT);    // step left

    // setup the actuator board
    byte ping_data[8] = {'P', 1, 0, 0, 0, 0, 0, 0};

    can_send(ACTUATOR_CAN_ID, ping_data);

    if(can_wait_for_finish() == 0xff) {
        return true;
    } else {
        return false;
    }
} // end of init_actuator(...)

/*
 * Function:        uint8_t actuator_relay_toggle(byte num)
 * Description:     toggle the relay
 * Parameters:      byte num    - which relay
 */
uint8_t actuator_relay_toggle(byte num) {

    byte using_pin;

    if(num == 1) {
        using_pin = RELAY1_PIN;
    } else {
        using_pin = RELAY2_PIN;
    }

    digitalWrite(using_pin, !digitalRead(using_pin));

    return 0;

} // end of actuator_relay_toggle(...)

/*
 * Function:        uint8_t actuator_update_servo(byte num, uint8_t pos) 
 * Description:     update the servos
 * Parameters:      byte num    - which servo
 *                  uint8_t pos - the position
 */
uint8_t actuator_update_servo(int num, int pos) {

    switch(num) {
        case 1:
            servo_1.write(pos);
            break;
        case 2:
            servo_2.write(pos);
            break;
        case 3:
            servo_3.write(pos);
            break;
        case 4:
            servo_4.write(pos);
            break;
    }

    return 0;

} // end of actuator_update_servo(...)

/*
 * Function:        uint8_t actuator_update_valves(uint8_t num, uint8_t status)
 * Description:     update the valves
 * Parameters:      uint8_t num         - which conn/valve
 *                  uint8_t status      - ON/OFF
 */
uint8_t actuator_update_valves(uint8_t num, uint8_t status) {
    digitalWrite(valve_pins[num-1], status);
} // end of actuator_update_valves(...)

/*
 * Function:        uint8_t actuator_read_bin(uint8_t num)
 * Description:     read the binary sensors
 * Parameters:      uint8_t num         - which binary sensor
 */
uint8_t actuator_read_bin(uint8_t num) {
    return digitalRead(bin_pins[num-1]);
} // end of actuator_read_bin(...)

/*
 * Function:        uint8_t actuator_read_switch(uint8_t _switch)
 * Description:     read the switches from the actuator board
 */
uint8_t actuator_read_switch(uint8_t _switch) {

    // 1 - 8
    byte switch_data[8] = {'S', _switch, 0, 0, 0, 0, 0, 0};

    can_send(ACTUATOR_CAN_ID, switch_data);
    return can_wait_for_finish();

} // end of actuator_read_switch(...)

/*
 * Function:        uint8_t actuator_move_hbridge(int a, int b, byte num)
 * Description:     start the hbridge
 * Parameters:      int a       - pwm on A channel
 *                  int b       - pwm on B channel
 *                  byte num    - which motor
 */
uint8_t actuator_move_hbridge(int a, int b, byte num) {

    byte hbridge_data[8] = {'H', 'M', (byte)(a >> 8), (byte)(a & 0xFF), (byte)(b >> 8), (byte)(b & 0xFF), num};

    can_send(ACTUATOR_CAN_ID, hbridge_data);
    return can_wait_for_finish();

} // end of actuator_move_hbridge(...)

/* 
 * Function:        uint8_t actuator_break_hbridge(byte num)
 * Description:     break the motor on hbridge
 * Parameters:      byte num        - which motor
 */
uint8_t actuator_break_hbridge(byte num) {

    byte hbridge_data[8] = {'H','B', num, 0, 0, 0, 0, 0};

    can_send(ACTUATOR_CAN_ID, hbridge_data);
    return can_wait_for_finish();

} // end of actuator_break_hbridge(...)

/* 
 * Function:        uint8_t actuator_hbridge_timed(int dir, int achieve, int time, byte num)
 * Description:     time the hbridge 
 * Parameters:      int dir         - direction
 *                  int achieve     - the achievement
 *                  byte num        - the motor
 */
uint8_t actuator_hbridge_timed(int dir, int achieve, int time, byte num) {
    
    byte _num;
    
    if(num == 0) { _num = 'T'; } else { _num = 't'; }

    byte hbridge_data[8] = {'H', _num, (byte)(dir >> 8), (byte)(dir & 0xFF), (byte)(achieve >> 8), (byte)(achieve & 0xFF), (byte)(time >> 8), (byte)(time & 0xFF)};

    can_send(ACTUATOR_CAN_ID, hbridge_data);
    return can_wait_for_finish();

} // end of actuator_hbridge_timed(...)

/* 
 * Function:        uint8_t actuator_stepper_enable(byte status, byte num)
 * Description:     enable stepper
 * Parameters:      byte status - enable/disable
 *                  byte num    - which stepper
 */
uint8_t actuator_stepper_enable(byte status, byte num) {

    byte stepper_data[8] = {'s', 'E', status, num, 0, 0, 0, 0}; 

    can_send(ACTUATOR_CAN_ID, stepper_data);
    return can_wait_for_finish();

} // end of actuator_stepper_enable(...)

/* 
 * Function:        uint8_t actuator_stepper_rpm(int rpm, byte num) 
 * Description:     set the rpm 
 * Parameters:      int rpm     - setup the rpm
 *                  byte num    - which stepper
 */
uint8_t actuator_stepper_rpm(int rpm, byte num) {

    byte stepper_data[8] = {'s', 'R', (byte)(rpm >> 8), (byte)(rpm & 0xFF), num};

    can_send(ACTUATOR_CAN_ID, stepper_data);
    return can_wait_for_finish();

} // end of actuator_stepper_rpm(...)

/* 
 * Function:        uint8_t actuator_stepper_move(int steps, byte dir, byte num)
 * Description:     move the stepper
 * Parameters:      int steps   - the couple of steps
 *                  byte dir    - the direction
 *                  byte num    - which stepper
 */
uint8_t actuator_stepper_move(unsigned int steps, int dir, int num) {

    int pin_step, pin_dir;

    if(num == SCP_LEFT_STEPPER_ID) {
        pin_step = A3; pin_dir = A2;
    } else if(num == SCP_RIGHT_STEPPER_ID){
        pin_step = A1; pin_dir = A0;
    }


    if(dir == 1) {
        // forward
        digitalWrite(pin_dir, LOW);

    } else {
        // backward
        digitalWrite(pin_dir, HIGH);

    }

    for(unsigned int i=0; i<steps; i++) {

        digitalWrite(pin_step, HIGH);
        _delay_us(700);
        digitalWrite(pin_step, LOW);
        _delay_us(700);

    }

} // end of actuator_stepper_move(...)
