#include <Arduino.h>
#include "system.h"

void init_detection() {
    pinMode(PIN_TACTIC2, INPUT);
    pinMode(PIN_TACTIC1, OUTPUT);
    digitalWrite(PIN_TACTIC1, HIGH);
}
void set_direction(uint8_t dir) {
    digitalWrite(PIN_TACTIC1, dir);
}
byte get_detection() {  
    return(digitalRead(PIN_TACTIC2));
}