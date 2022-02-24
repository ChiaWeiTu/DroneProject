/*
 * EEPROM Clear
 Sets all of the bytes of the EEPROM to 0.
 */

#include <EEPROM.h>

void setup() {
  // initialize the LED pin as an output.
  pinMode(13, OUTPUT);
  

   // Iterate through each byte of the EEPROM storage.
   //set i to EEPROM.length() or 4096 bytes


  for (int i = 0 ; i <EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }

  
}

void loop() {
 
}
