#include <Arduino.h>
#include "odometry.h"

struct odometry_position position=
{
	.x     = 0,							// x coordinate
	.y     = 0,							// y coordinate
	.angle = 0,							// angle (in degrees 0-360)
	.state = IDLE,					// state
    .current_speed = 0			// the current speed (the speed it will try to reach (dependent on distance given))
};

bool init_odometry(void) {

    byte ping_data[8] = {odometry_command_ping, 1, 0, 0, 0, 0, 0, 0};

    can_send(ODOMETRY_CAN_ID, ping_data);
    if(can_wait_for_finish() == 0xff) {
        return true;
    } else {
        return false;
    }

}

static uint8_t odometry_wait_until_done(uint8_t (*callback)()) {
	delay(300);

	int counter = 0;

	while(counter <= 2) {
		odometry_update_status();
		
		if(position.state == 'I')
			counter++;

		if(callback != NULL) {
			if(callback() == 1) {
				return ODOMETRY_FAIL;
			}
		}

		delay(150);
	}

	Serial.println("Idling...");

	delay(200);
	return ODOMETRY_SUCCESS;
}

uint8_t odometry_set_position(int16_t x, int16_t y, int16_t angle) {

	byte odometry_data[8] = {odometry_command_set_position, (byte)(x >> 8), (byte)(x & 0xFF), (byte)(y >> 8), (byte)(y & 0xFF), (byte)(angle >> 8), (byte)(angle & 0xFF), 0};

    can_send(ODOMETRY_CAN_ID, odometry_data);
    return can_wait_for_finish();

}

void odometry_update_status(void) {

    byte odometry_status[8] = {NULL};

    byte odometry_data[8] = {odometry_command_update_status, 0, 0, 0, 0, 0, 0, 0};
    can_send(ODOMETRY_CAN_ID, odometry_data);

    can_return_data(odometry_status);

    position.state  = odometry_status[0];
    position.x      = (odometry_status[1] << 8) | odometry_status[1];
    position.y      = (odometry_status[2] << 8) | odometry_status[3];
    position.angle  = (odometry_status[4] << 8) | odometry_status[5];

}

uint8_t odometry_set_speed(uint8_t speed) {

    byte odometry_data[8] = {odometry_command_set_speed, (byte)(speed), 0, 0, 0, 0, 0, 0};

    position.current_speed = speed;

    can_send(ODOMETRY_CAN_ID, odometry_data);
    return can_wait_for_finish();

}

uint8_t odometry_move_forward(int16_t distance, uint8_t speed, uint8_t (*callback)()) {

    byte odometry_data[8] = {odometry_command_move_forward, (byte)(distance >> 8), (byte)(distance & 0xFF), (byte)(speed), 0, 0, 0, 0};

    can_send(ODOMETRY_CAN_ID, odometry_data);
    return odometry_wait_until_done(callback);

}

uint8_t odometry_rotate_for(uint16_t angle, uint8_t (*callback)()) {
    byte odometry_data[8] = {odometry_command_rotate_for, (byte)(angle >> 8), (byte)(angle & 0xFF), 0, 0, 0, 0, 0};

    can_send(ODOMETRY_CAN_ID, odometry_data);
    return odometry_wait_until_done(callback);
}

uint8_t odometry_set_angle(uint16_t angle, uint8_t (*callback)()) {
    byte odometry_data[8] = {odometry_command_set_angle, (byte)(angle >> 8), (byte)(angle & 0xFF), 0, 0, 0, 0, 0};

    can_send(ODOMETRY_CAN_ID, odometry_data);
    return odometry_wait_until_done(callback);
}

uint8_t odometry_goto(uint16_t x, uint16_t y, uint8_t speed, uint8_t direction, uint8_t (*callback)()) {
    byte odometry_data[8] = {odometry_command_goto, (byte)(x >> 8), (byte)(x & 0xFF), (byte)(y >> 8), (byte)(y & 0xFF), (byte)(speed), (byte)(direction), 0};

    can_send(ODOMETRY_CAN_ID, odometry_data);
    return odometry_wait_until_done(callback);
}

uint8_t odometry_stop(uint8_t type) {

    // sending the command status
	if(type == HARD_STOP) {
        byte odometry_data[8] = {odometry_command_stop_hard, 0, 0, 0, 0, 0, 0, 0};
        can_send(ODOMETRY_CAN_ID, odometry_data);
	} else if(type == SOFT_STOP) {
        byte odometry_data[8] = {odometry_command_stop_soft, 0, 0, 0, 0, 0, 0, 0};
        can_send(ODOMETRY_CAN_ID, odometry_data);
	}

	return ODOMETRY_SUCCESS;
}

 
uint8_t odometry_end_match(void) {

	byte odometry_data[8] = {odometry_command_end_match, 0, 0, 0, 0, 0, 0, 0};

    can_send(ODOMETRY_CAN_ID, odometry_data);

    return can_wait_for_finish();
}

int16_t odometry_get_x(void)                {       return position.x;                  }
int16_t odometry_get_y(void)                {       return position.y;                  }
int16_t odometry_get_angle(void)            {       return position.angle;              }
int8_t odometry_get_state(void)             {       return position.state;              }
int8_t odometry_get_current_speed(void)     {       return position.current_speed;      }