#ifndef NRF_H
#define NRF_H

#include <SPI.h>
#include "RF24.h"

#define PIN_NRF_CS 48
#define PIN_NRF_CE 47


bool init_nrf(void);
bool nrf_send(unsigned char ID, unsigned char task_ID, unsigned char status);
void nrf_read_process(void);

void Motor_start();
void Motor_stop();
void Led_start();
void Led_stop();

#endif