#include <Arduino.h>
#include "nrf.h"

RF24 radio(PIN_NRF_CS, PIN_NRF_CE);

const uint64_t pipes[][7] = {"sensa1", "sensa2"};

/*
 * Function:        bool init_nrf(void)
 * Description:     init the nrf
 */
bool init_nrf(void) {

    if(!radio.begin()) 
        return false;

    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_2MBPS);
    radio.setChannel(124);
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1, pipes[0]);

    randomSeed(analogRead(A0));

    return true;
    
} // end of init_nrf(...)

/*
 * Function:        bool nrf_send(unsigned char ID, unsigned char task_ID, unsigned char status)
 * Description:     send data with nrf
 */
bool nrf_send(unsigned char ID, unsigned char task_ID, unsigned char status) {

    unsigned char data[3] = { ID, task_ID, status };
    radio.stopListening();
    if(!radio.write(&data, sizeof(data)/sizeof(unsigned char))) {
        return false;
    }
    return true;
   
} // end of nrf_send(...)

/*
 * Function:        void nrf_read_process(void)
 * Description:     read process
 */
void nrf_read_process(void) {

    unsigned char ID; unsigned char task_ID; unsigned char status;

    radio.startListening();

    if(radio.available()) {
        
        Serial.println("Avaiable: "); Serial.print(radio.available());
        radio.read(&ID,         sizeof(unsigned char));
        radio.read(&task_ID,    sizeof(unsigned char));
        radio.read(&status,     sizeof(unsigned char));

    }

    Serial.println("ID: "); Serial.print(ID);
    Serial.print(" Task ID: "); Serial.print(task_ID);
    Serial.print(" Status: "); Serial.print(status);

    radio.stopListening();

} // end of nrf_read_process(...)