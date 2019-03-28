#include <Arduino.h>
#include "positions.h"

// holder structures
struct odometry_position starter_pos;
struct goto_fields goto_pos[30];

/*
 * Function:    static void choose_side(uint8_t side, uint8_t table)
 * Description: depending on the side and the table it will choose what to put into the holder structures
 */
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
} // end of choose_side

uint8_t active_state = TACTIC_ONE;          // starter active state
uint8_t status;                             // return of the odometry function
int g_current, g_next = 0;                  // current pos

void robot(uint8_t side, uint8_t table) {

    // choose the side
    choose_side(side, table);

    // set our starting positon
    odometry_set_position(starter_pos.x, starter_pos.y, starter_pos.angle);

    delay(10);

    while(1) {
        switch(active_state) {
            // if we have COLLISION
            case COLLISION:
                
                delay(200);

                // wait while the callback function is returning 1
				while(goto_pos[g_current].callback() == 1)
					delay(10);

				active_state = TACTIC_ONE;      // set the active state back to TACTIC_ONE
				g_next = g_current;             // continue to the next pos

				delay(500);                    // wait a bit before continuing
                break;

            // we are doing tactic one
            case TACTIC_ONE:
                for(g_current=g_next; g_current < int((sizeof(goto_pos)/sizeof(goto_pos)[0])); g_current++) {   // going through the positions


					Serial.println("Going to: ");
					Serial.print(g_current);

                    // send it to odometry goto, maybe consider doing odometry_straight
					status = odometry_goto(goto_pos[g_current].goto_position.x,
								           goto_pos[g_current].goto_position.y,
								           goto_pos[g_current].speed,
								           goto_pos[g_current].direction,
								           goto_pos[g_current].callback);

                    // if the odometry status is at FAIL, we say we have a collision
					if(status == ODOMETRY_FAIL) {
						active_state = COLLISION;
						break;
					}

                    // if we have a callback function execute it
					if(goto_pos[g_current].callback_end != NULL)
						goto_pos[g_current].callback_end();

                    // if at last position odometry stop and while(1)
					if(g_current == (sizeof(goto_pos)/sizeof(goto_pos)[0]) - 1) {
						odometry_end_match();
						while(1);
					}
                }
                        
                break;
            
        }
    } // end of while(1)

}