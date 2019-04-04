#include <Arduino.h>
#include "nrf.h"

RF24 radio(PIN_NRF_CE, PIN_NRF_CS);

byte addresses[][6] = {"1Node", "2Node"};  //2 modes one is transmiter and second is receiver

/*
 * Function:        bool init_nrf(void)
 * Description:     init the nrf
 */
bool init_nrf(void) {

   // Initiate the radio object
  radio.begin();

  // Set the transmit power to lowest available to prevent power supply related issues
  radio.setPALevel(RF24_PA_MIN);

  // Set the speed of the transmission to the quickest available
  radio.setDataRate(RF24_2MBPS);

  // Use a channel unlikely to be used by Wifi, Microwave ovens etc
  radio.setChannel(124);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
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

void Motor_start()
{
  /*  sending two digits to receiver board
   *  firts digit:set witch modul is working,5-motor
   *  second digit:if ist 1 turn on motor and if its 0 turn off
   */
  unsigned char data = 51;//random(0, 254);
    
  // Ensure we have stopped listening (even if we're not) or we won't be able to transmit
  radio.stopListening(); 

  // Did we manage to SUCCESSFULLY transmit that (by getting an acknowledgement back from the other Arduino)?
  // Even we didn't we'll continue with the sketch, you never know, the radio fairies may help us
  if (!radio.write( &data, sizeof(unsigned char) )) {
    Serial.println("No acknowledgement of transmission - receiving radio device connected?");    
  }
  Serial.println(data);

  delay(1000);
}//end of Motor_start()

/*
    Function:     Motor_stop()
    Description:  Send data to stop motor
*/
void Motor_stop()
{
   /*  sending two digits to receiver board
   *  firts digit:set witch modul is working,5-motor
   *  second digit:if ist 1 turn on motor and if its 0 turn off
   */
  unsigned char data = 50;//random(0, 254);
    
  // Ensure we have stopped listening (even if we're not) or we won't be able to transmit
  radio.stopListening(); 

  // Did we manage to SUCCESSFULLY transmit that (by getting an acknowledgement back from the other Arduino)?
  // Even we didn't we'll continue with the sketch, you never know, the radio fairies may help us
  if (!radio.write( &data, sizeof(unsigned char) )) {
    Serial.println("No acknowledgement of transmission - receiving radio device connected?");    
  }
  Serial.println(data);

  // Now listen for a response

  // Try again 1s later
  delay(1000);
}//end of Motor_stop()

/*
    Function:     Led_start()
    Description:  Send data to start led
*/
void Led_start()
{
   /*  sending two digits to receiver board
   *  firts digit:set witch modul is working,4-LED
   *  second digit:if ist 1 turn on motor and if its 0 turn off
   */
  unsigned char data = 41;//random(0, 254);
    
  // Ensure we have stopped listening (even if we're not) or we won't be able to transmit
  radio.stopListening(); 

  // Did we manage to SUCCESSFULLY transmit that (by getting an acknowledgement back from the other Arduino)?
  // Even we didn't we'll continue with the sketch, you never know, the radio fairies may help us
  if (!radio.write( &data, sizeof(unsigned char) )) {
    Serial.println("No acknowledgement of transmission - receiving radio device connected?");    
  }
  Serial.println(data);

  // Now listen for a response

  // Try again 1s later
  delay(1000);
}//end of Led_start()

/*
    Function:     Led_stop()
    Description:  Send data to stop led
*/
void Led_stop()
{
   /*  sending two digits to receiver board
   *  firts digit:set witch modul is working,4-LED
   *  second digit:if ist 1 turn on motor and if its 0 turn off
   */
  unsigned char data = 40;//random(0, 254);
    
  // Ensure we have stopped listening (even if we're not) or we won't be able to transmit
  radio.stopListening(); 

  // Did we manage to SUCCESSFULLY transmit that (by getting an acknowledgement back from the other Arduino)?
  // Even we didn't we'll continue with the sketch, you never know, the radio fairies may help us
  if (!radio.write( &data, sizeof(unsigned char) )) {
    Serial.println("No acknowledgement of transmission - receiving radio device connected?");    
  }
  Serial.println(data);

  // Now listen for a response

  // Try again 1s later
  delay(1000);
}//end of Led_stop()