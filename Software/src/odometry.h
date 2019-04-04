#ifndef ODOMETRY_H
#define ODOMETRY_H

#include <Arduino.h>
#include "can.h"

#define ODOMETRY_CAN_ID 0xC3

struct odometry_position
{
	int16_t x;
	int16_t y;
	int16_t angle;
	unsigned char state;
	int8_t current_speed;
};

enum odometry_states
{
	IDLE        = 'I',
	MOVING      = 'M',
	ROTATING    = 'R',
	STUCK       = 'S',
	ERROR       = 'E'
};

#define FORWARD								0
#define BACKWARD							1

#define ODOMETRY_SUCCESS					1
#define ODOMETRY_FAIL						0

#define HARD_STOP							1
#define SOFT_STOP							0

#define odometry_command_set_position       'I'
#define odometry_command_update_status      'P'
#define odometry_command_set_speed		    'V'
#define odometry_command_move_forward       'D'
#define odometry_command_rotate_for         'T'
#define odometry_command_set_angle          'A'
#define odometry_command_goto			    'G'
#define odometry_command_stop_hard		    'S'
#define odometry_command_stop_soft          's'
#define odometry_command_end_match		    'K'
#define odometry_command_ping               'H'

bool init_odometry(void);
uint8_t odometry_ping(void);
void odometry_set_position(int16_t x, int16_t y, int16_t angle);
void odometry_update_status(void);
void odometry_set_speed(uint8_t speed);
uint8_t odometry_move_forward(int16_t distance, uint8_t speed, uint8_t (*callback)());
uint8_t odometry_rotate_for(uint16_t angle, uint8_t (*callback)());
uint8_t odometry_set_angle(uint16_t angle, uint8_t (*callback)());
uint8_t odometry_goto(uint16_t x, uint16_t y, uint8_t speed, uint8_t direction, uint8_t (*callback)());
uint8_t odometry_stop(uint8_t type);
void odometry_end_match(void);
int16_t odometry_get_x(void);
int16_t odometry_get_y(void);
int16_t odometry_get_angle(void);
int8_t odometry_get_state(void);
int8_t odometry_get_current_speed(void);

#define COLLISION 1
//#define STUCK 2
#define TACTIC_ONE 3

#endif