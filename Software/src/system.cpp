#include "system.h"

unsigned long sys_time = 0;                     // system time since the match started
bool match_started = false;                     // true if the match started
bool jumper_pulled = false;                     // jumper status


void set_match_started(void)        { match_started = true; }
unsigned long get_sys_time(void)    { return sys_time;      }



static void pull_jumper() { jumper_pulled = true; }
static void init_jumper(void) {
    pinMode(PIN_JUMPER, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_JUMPER), pull_jumper, CHANGE);
}





static void init_switches() {
    pinMode(PIN_TACTIC1, INPUT);
    pinMode(PIN_TACTIC2, INPUT);
    pinMode(PIN_SIDE,    INPUT);
}


int get_tactic1(void)   { return digitalRead(PIN_TACTIC1);  }
int get_tactic2(void)   { return digitalRead(PIN_TACTIC2);  }
int get_side(void)      { return digitalRead(PIN_SIDE);     }





static void timer_isr(void) {
    if(match_started) {
        sys_time++;

        if(sys_time == 90000) {
            // match end
        }

    }
}

static void init_timer(void) {
    Timer3.initialize(1000);
    Timer3.attachInterrupt(timer_isr);
}

void init_system(void) {

    Serial.begin(115200);

    init_can();

    if(!init_actuator()) {
        Serial.println("Actuator is fucked...");
        while(1);
    }

   /* if(!init_lidar()) {
        Serial.println("Lidar is fucked...");
        while(1);
    }*/

    /*if(!init_nrf()) {
        Serial.println("NRF is fucked...");
        while(1);
    }*/

    init_timer();
    init_jumper();
    init_switches();

    //init_display();

    Serial.println("Ready... waiting for jumper...");
    // wait for jumper to be pulled, loop while it is not pulled
    //while(!jumper_pulled);

}