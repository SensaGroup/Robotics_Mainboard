#ifndef NRF_H
#define NRF_H

#include <SPI.h>
#include "RF24.h"

#define PIN_NRF_CS 48
#define PIN_NRF_CE 47

#define MY_NRF_ID 53

bool init_nrf(void);
bool nrf_send(unsigned char ID, unsigned char task_ID, unsigned char status);
void nrf_read_process(void);

#endif