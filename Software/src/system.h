#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include "actuator.h"
#include "TimerThree.h" 
#include "nrf.h"
#include "can.h"
#include "odometry.h"
#include "mechanism.h"
#include "detection.h"

#define PIN_JUMPER  3
#define PIN_TACTIC1 5
#define PIN_TACTIC2 6
#define PIN_SIDE    4

void init_system(void);
void set_match_started(void);
unsigned long get_sys_time(void);

int get_tactic1(void);
int get_tactic2(void);
int get_side(void);

struct goto_fields
{
	struct odometry_position goto_position;
	uint8_t speed;
	uint8_t direction;
	uint8_t	(*callback)();
	uint8_t (*callback_end)();
};


#endif