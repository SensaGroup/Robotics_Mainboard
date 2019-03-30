#include <Arduino.h>
#include "system.h"

void setup()
{
  
    init_system();
/*
    push_out_right();
    delay(1000);
    push_out_right();
    delay(1000);
    push_out_right();
    delay(1000);
    pull_back_right();
    pull_back_right();
    pull_back_right();*/
    servo_grab(SCP_LEFT_STEPPER_ID);
}


void loop()
{  

    
}
