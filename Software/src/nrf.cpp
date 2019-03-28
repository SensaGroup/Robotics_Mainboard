#include <Arduino.h>
#include "nrf.h"

RF24 radio(PIN_NRF_CS, PIN_NRF_CE);

//0xF0F0F0F0B4LL writing
//0xF0F0F0F0E9LL reading


byte sensa_code[5] = {0x53, 0x45, 0x4e, 0x53, 0x41};
const uint64_t pipes[2] = {0xF0F0F0F0B4LL, 0xF0F0F0F0E9LL};

byte data[8];                                // Data buffer for testing data transfer speeds

bool init_nrf(void) {
    
    if(!radio.begin())                       // Setup and configure rf radio
        return false;                     
              
    radio.setChannel(1);
    radio.setPALevel(RF24_PA_MAX);           // If you want to save power use "RF24_PA_MIN" but keep in mind that reduces the module's range
    radio.setDataRate(RF24_1MBPS);
    radio.setAutoAck(53);                     // Ensure autoACK is enabled
    radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
    
    radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
    
    radio.startListening();                  // Start listening
    radio.printDetails();                    // Dump the configuration of the rf unit for 

    for(int i = 0; i < 8; i++){
        data[i] = random(255);                //Load the buffer with random data
    }

    radio.powerUp();                         //Power up the radio

    return true;
}

bool nrf_send(byte ID, byte task_ID, byte status) {

    for(int i=0; i<5; i++) {
        data[i] = sensa_code[i];
    }
    
    data[5] = ID; data[6] = task_ID, data[7] = status; 

    if(!radio.writeFast(&data,8)){   //Write to the FIFO buffers        
        return false;
    }

    return true;
}

byte recv_data[8]; uint8_t recv_counter = 0;

byte nrf_process(void) {
    if(radio.available()) {
        while(radio.available()) {
            radio.read(&recv_data, 8);
            recv_counter++;
        }

        Serial.print("NRF recv: ");Serial.println(recv_counter);

        if(recv_counter == 8) {
            for(int i=0; i<5; i++) {
                if(recv_data[i] != sensa_code[i]) {
                    return;
                }
            }

            // passed the code
            if(recv_data[5] == MY_NRF_ID) {
                switch(recv_data[6]) {
                    case 's':
                        // its sex time
                        // do the sex
                        Serial.println("NRF: sexy time...");
                        break;
                }
            }
        }
    }
}