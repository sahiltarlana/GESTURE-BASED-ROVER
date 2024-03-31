// ask_transmitter.pde
// -- mode: C++ --
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module
// Tested on Arduino Mega, Duemilanova, Uno, Due, Teensy, ESP-12

#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

//RH_ASK driver;
RH_ASK driver; // ESP8266 or ESP32: do not use pin 11 or 2



char prevMesg = 's'; // Initialize prevMesg with a default value
char msg;


void setup()
{
#ifdef RH_HAVE_SERIAL
    Serial.begin(9600);	  // Debugging only
#endif
    if (!driver.init())
#ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
#else
	;
#endif
}


void transmitMessage() {
  driver.send((uint8_t *)&msg, 1); // Send the character stored in msg
  driver.waitPacketSent();
  Serial.println("Message Transmitted: "); // Print a message indicating successful transmission
}


void loop()
{
  if(Serial.available() > 0) {
    prevMesg = Serial.read(); // Read a character from Serial and store it in prevMesg
    Serial.println(prevMesg);
    if(prevMesg == 'b' || prevMesg == 'f' || prevMesg == 's' || prevMesg == 'l' || prevMesg == 'r') {
        msg = prevMesg; // Store the received character in msg
    }
    Serial.println(msg);
    transmitMessage();
  }

  delay(10); // Delay for 1 second
}

