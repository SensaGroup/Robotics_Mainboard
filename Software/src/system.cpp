#include "system.h"

unsigned long sys_time = 0;                     // system time since the match started
bool match_started = false;                     // true if the match started
bool jumper_pulled = false;                     // jumper status

// helper functions
void set_match_started(void)        { match_started = true; }
unsigned long get_sys_time(void)    { return sys_time;      }

// set the jumper_pulled to true
static void pull_jumper() { jumper_pulled = true; }

/*
 * Function:        static void init_jumper(void)
 * Description:     setup the jumper
 */
static void init_jumper(void) {
    pinMode(PIN_JUMPER, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_JUMPER), pull_jumper, CHANGE);
} // end of init_jumper(...)

/*
 * Function:        static void init_switches()
 * Description:     setup all the switches
 */
static void init_switches() {
    //pinMode(PIN_TACTIC1, INPUT);
    //pinMode(PIN_TACTIC2, INPUT);
    pinMode(PIN_SIDE,    INPUT);
} // end of init_switches()

// helper functions to read the switches
//int get_tactic1(void)   { return digitalRead(PIN_TACTIC1);  }
//int get_tactic2(void)   { return digitalRead(PIN_TACTIC2);  }
int get_side(void)      { return digitalRead(PIN_SIDE);     }

/*
 * Function:        static void timer_isr(void)
 * Description:     timer interrupt function
 */
static void timer_isr(void) {
    if(match_started) {

        sys_time++;

        if(sys_time == 90000) {
            // match end
        }

    }
}

/*
 * Function:        static void init_timer(void) 
 * Description:     init the timer
 */
static void init_timer(void) {
    Timer3.initialize(1000);
    Timer3.attachInterrupt(timer_isr);
} // end of init_timer()

/*
 * Function:        void init_system(void)
 * Description:     init the system
 */
void init_system(void) {

    bool fucked = false;

    Serial.begin(115200);

    init_can();

    if(!init_actuator()) {
        Serial.println("Actuator is fucked...");
        fucked = true;
    }

    actuator_stepper_move(1, STEPPER_FORWARD, SCP_LEFT_STEPPER_ID);
    actuator_stepper_move(1, STEPPER_FORWARD, SCP_RIGHT_STEPPER_ID);

    if(!init_nrf()) {
        Serial.println("NRF is fucked...");
        fucked = true;
    }

    init_detection();
    init_timer();
    init_jumper();
    init_switches();

    if(fucked) {
        Serial.println("Something is totally fucked so let's not continue...");
        while(1);
    } 

    Serial.println("Ready... waiting for jumper...");
    
    // wait for jumper to be pulled, loop while it is not pulled
    //while(!jumper_pulled);

} // end of init_system