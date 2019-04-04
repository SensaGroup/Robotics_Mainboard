#include <Arduino.h>
#include "odometry.h"


static void odometry_send_command_print(char val)   { Serial2.print(val); }
static void odometry_send_8bit(char val)            { Serial2.print(val); }
static int odometry_get_command(void)               { return Serial2.read(); }
static void odometry_send_16bit(int16_t val)        { Serial2.write((unsigned char)(val >> 8)); Serial2.write((unsigned char)(val & 0xFF)); }

// our monitoring odometry statuses
struct odometry_position position=
{
	.x     = 0,							// x coordinate
	.y     = 0,							// y coordinate
	.angle = 0,							// angle (in degrees 0-360)
	.state = IDLE,					    // state
    .current_speed = 0			        // the current speed (the speed it will try to reach (dependent on distance given))
};

/*
 * Function:        bool init_odometry(void)
 * Description:     send ping data to odometry
 */
bool init_odometry(void) {

    Serial2.begin(57600);

    return true;

} // end of init_odometry(...)

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

/*
 *	Function: 	 void odometry_set_position(int16_t x, int16_t y, int16_t angle)
 *  Description: updates the position of the robot (force update)
 */
void odometry_set_position(int16_t x, int16_t y, int16_t angle) {

	// sending the command status
	odometry_send_command_print(odometry_command_set_position);


	odometry_send_16bit(x);
	odometry_send_16bit(y);
	odometry_send_16bit(angle);

}

uint8_t odometry_ping(void) {

	odometry_send_command_print(odometry_command_ping);
	unsigned char confirm = odometry_get_command();

	if(confirm == 'H')
		return 1;
	else
		return 0;
}

/*
 *	Function: 	 void odometry_update_status(void)
 *  Description: updates the position struct with new data
 */
void odometry_update_status(void) {


	// sending the command status
  odometry_send_command_print(odometry_command_update_status);

	//status = odometry_get_command();


  //Serial1.write(odometry_get_command()); //write because it converts it to ASCII...
  position.state = odometry_get_command();
	Serial.write(position.state);
	Serial.print(" ");

//  Serial1.print((odometry_get_command() << 8) | odometry_get_command(), DEC);
  position.x = (odometry_get_command() << 8) | odometry_get_command();
	Serial.print(position.x);
	Serial.print(" ");

  //Serial1.print((odometry_get_command() << 8) | odometry_get_command(), DEC);
  position.y = (odometry_get_command() << 8) | odometry_get_command();
	Serial.print(position.y);
	Serial.println(" ");

  //Serial1.print((odometry_get_command() << 8) | odometry_get_command(), DEC);
  position.angle = (odometry_get_command() << 8) | odometry_get_command();
	//Serial1.print(position.angle);

  //Serial1.print(odometry_get_command(), DEC);
  //position.current_speed = odometry_get_command();

}

/*
 *	Function: 	 void odometry_set_speed(uint8_t speed)
 *  Description: updates the speed (by speed we mean the speed it will try to go with - it is dependent on the distance)
 *  Parameter:   uint8_t speed - the speed value
 */
void odometry_set_speed(uint8_t speed) {

	// sending the command status
	odometry_send_command_print(odometry_command_set_speed);

	// if its the same as last set, just skip all
	if(speed == position.current_speed) {
		return;
	}

	// send the speed
	odometry_send_8bit(speed);

	// update the status (we could have just the the position.current_speed, but its more assuring like this)
	odometry_update_status();

}

/*
 *	Function: 	 uint8_t odometry_move_forward(int16_t distance, uint8_t direction, uint8_t (*callback)(uint32_t start_time))
 *  Description: move the robot forward/backward at a determined distance
 *  Parameter:   int16_t distance - the distance in mm
 * 							 uint8_t direction - FORWARD/BACKWARD
 */
uint8_t odometry_move_forward(int16_t distance, uint8_t speed, uint8_t (*callback)()) {

	// sending the command status
	odometry_send_command_print(odometry_command_move_forward);

	odometry_send_16bit(distance);
	odometry_send_8bit(speed);


	return odometry_wait_until_done(callback);
}

/*
 *	Function: 	 uint8_t odometry_rotate_for(uint16_t angle, uint8_t (*callback)(uint32_t start_time))
 *  Description: rotate the robot for a certain degree
 *  Parameter:   int16_t angle - the angle we will rotate it for
 */
uint8_t odometry_rotate_for(uint16_t angle, uint8_t (*callback)()) {

	// sending the command status
	odometry_send_command_print(odometry_command_rotate_for);

	odometry_send_16bit(angle);

	return odometry_wait_until_done(callback);

}

/*
 *	Function: 	 uint8_t odometry_set_angle(uint16_t angle, uint8_t (*callback)(uint32_t start_time))
 *  Description: rotate the robot to a certain degree
 *  Parameter:   int16_t angle - the angle it will rotate to
 */
uint8_t odometry_set_angle(uint16_t angle, uint8_t (*callback)()) {

	// sending the command status
	odometry_send_command_print(odometry_command_set_angle);

	odometry_send_16bit(angle);

	return odometry_wait_until_done(callback);
}

/*
 *	Function: 	 uint8_t odometry_goto(uint16_t x, uint16_t y, uint16_t angle, uint8_t speed, uint8_t direction, uint8_t (*callback)(uint32_t start_time))
 *  Description: sends the robot into a specific coordinate in a direction at a defined speed
 *  Parameter:   self explanatory
 */
uint8_t odometry_goto(uint16_t x, uint16_t y, uint8_t speed, uint8_t direction, uint8_t (*callback)()) {

	odometry_set_speed(speed);

	// sending the command status
	odometry_send_command_print(odometry_command_goto);

	odometry_send_16bit(x);
	odometry_send_16bit(y);
	//odometry_send_16bit(angle);

	odometry_send_8bit(speed);
	odometry_send_8bit(direction);

	return odometry_wait_until_done(callback);
}

/*
 *	Function: 	 uint8_t odometry_stop(uint8_t (*callback)(uint32_t start_time))
 *  Description: stop the robot
 */
uint8_t odometry_stop(uint8_t type) {

	// sending the command status
	if(type == HARD_STOP) {
		odometry_send_command_print(odometry_command_stop_hard);
	} else if(type == SOFT_STOP) {
		odometry_send_command_print(odometry_command_stop_soft);
	}

	return ODOMETRY_SUCCESS;
}

/*
 *	Function: 	 void odometry_end_match(void)
 *  Description: blocking all wheels, stopping, turning off pwm and staying in while(1)
 */
void odometry_end_match(void) {

	// sending the command status
	odometry_send_command_print(odometry_command_end_match);

}



/*
 *  Description: return all data found in the struct
 */
int16_t odometry_get_x(void)                { return position.x; }
int16_t odometry_get_y(void)                { return position.y; }
int16_t odometry_get_angle(void)            { return position.angle; }
int8_t odometry_get_state(void)             { return position.state; }
int8_t odometry_get_current_speed(void)     { return position.current_speed; }