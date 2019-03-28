#include <Arduino.h>
#include "positions.h"

struct odometry_position starter_pos;
struct goto_fields goto_pos[30];

static void choose_side(uint8_t side, uint8_t table) {
    switch(side) {
        case YELLOW:
            if(table == TABLE1) {
                starter_pos = yellow_table_one_starter;
                memcpy(&goto_pos, &yellow_table_one, sizeof(yellow_table_one));
            } else {
                starter_pos = yellow_table_two_starter;
                memcpy(&goto_pos, &yellow_table_two, sizeof(yellow_table_two));
            }

            break;

        case PURPLE:
            if(table == TABLE1) {
                starter_pos = purple_table_one_starter;
                memcpy(&goto_pos, &purple_table_one, sizeof(purple_table_one));
            } else {
                starter_pos = yellow_table_two_starter;
                memcpy(&goto_pos, &purple_table_two, sizeof(purple_table_two));
            }

            break;

    }
}

uint8_t active_state = TACTIC_ONE;
uint8_t status;
int g_current, g_next = 0;
int o_current, o_next = 0;

void robot(uint8_t side, uint8_t table) {

    choose_side(side, table);

    odometry_set_position(starter_pos.x, starter_pos.y, starter_pos.angle);

    delay(200);

    while(1) {
        switch(active_state) {

            case COLLISION:
                
                delay(200);

				while(goto_pos[g_current].callback() == 1)
					delay(10);

				active_state = TACTIC_ONE;
				g_next = g_current;

				delay(1000);
                break;

            case TACTIC_ONE:
                for(g_current=g_next; g_current < int((sizeof(goto_pos)/sizeof(goto_pos)[0])); g_current++) {


					Serial.println("Going to: ");
					Serial.print(g_current);

					status = odometry_goto(goto_pos[g_current].goto_position.x,
								           goto_pos[g_current].goto_position.y,
								           goto_pos[g_current].speed,
								           goto_pos[g_current].direction,
								           goto_pos[g_current].callback);

					if(status == ODOMETRY_FAIL) {
						active_state = COLLISION;
						break;
					}

					if(goto_pos[g_current].callback_end != NULL)
						goto_pos[g_current].callback_end();

					if(g_current == (sizeof(goto_pos)/sizeof(goto_pos)[0]) - 1) {
						odometry_end_match();
						while(1);
					}
                    
                break;
            }
        }
    } // end of while(1)

}