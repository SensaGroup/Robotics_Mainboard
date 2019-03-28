#ifndef NRF_H
#define NRF_H

#include <SPI.h>
#include "RF24.h"

#define PIN_NRF_CS 48
#define PIN_NRF_CE 47

#define MY_NRF_ID 53

bool init_nrf(void);
bool nrf_send(byte ID, byte task_ID, byte status);
byte nrf_process(void);

#endif