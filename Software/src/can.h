#ifndef CAN_H
#define CAN_H

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>

bool init_can(void);
void can_send(uint32_t ID, byte *data);
uint8_t can_wait_for_finish(void);
void can_return_data(byte *data);

#endif