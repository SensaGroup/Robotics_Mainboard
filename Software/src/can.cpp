#include "can.h"

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>

// CAN0 INT and CS
#define CAN0_INT 49                              // Set INT to pin 2
MCP_CAN CAN0(53);                               // Set CS to pin 10

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

bool init_can(void) {

    // Initialize MCP2515 running at 16MHz with a baudrate of 100kb/s and the masks and filters disabled.
    if(CAN0.begin(MCP_ANY, CAN_100KBPS, MCP_16MHZ) == CAN_OK) {
        Serial.println("MCP2515 Initialized Successfully!");
    } else {
        Serial.println("Error Initializing MCP2515...");
        return false;
    }

    CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted

    pinMode(CAN0_INT, INPUT);

    return true;

}

void can_send(uint32_t ID, byte *data) {
    CAN0.sendMsgBuf(ID, 0, 8, data);
}

void can_return_data(byte *data) {
    
    while(digitalRead(CAN0_INT));

    CAN0.readMsgBuf(&rxId, &len, rxBuf);

    for(int i=0; i<8; i++) {
        data[i] = rxBuf[i];
    }
}

uint8_t can_wait_for_finish(void) {

    while(1) {
        while(digitalRead(CAN0_INT));

        CAN0.readMsgBuf(&rxId, &len, rxBuf);
        
        Serial.println(rxId);
        if(rxId == 0x04) {
        
            for(int i=0; i<len; i++) {
                Serial.print(rxBuf[i]);
            }
        
            Serial.println();

            return rxBuf[0];
        
        }
    }

    return 0;
}

