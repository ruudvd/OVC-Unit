/*
  Example for different sending methods

  http://code.google.com/p/rc-switch/

*/


#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

#include <Wire.h>  // The wire.h library is needed for I2C communication
#define SLAVE_ADDRESS 0x40   // This is the address needed for I2C communication
char ReceivedData;  // Declare a character
String TextMessage = "";  // Declare an empty string

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);

  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(10);

  Wire.begin(SLAVE_ADDRESS);  // Start communication on the defined address

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);

  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);

}

void loop() {
  Wire.onReceive(receiveData);  // Start the void on the bottom of page
}

void sendViaRf(int message) {
  mySwitch.send(message, 24);
}

void receiveData(int byteCount)
{
  // On I2C you can only send data as a 'char'. We receive one character at a time so we have to concatenate them.
  while (Wire.available()) // As long as there is information comming, do:
  {
    ReceivedData = Wire.read();  // Read the incomming character
    TextMessage += ReceivedData;  // Add the character to the characters you got earlier (construct a string).
  }
  Serial.println("Received from I2C: " + TextMessage);  // Print the received text message

  if (TextMessage.startsWith("RF:")) { //Command send via RF
    TextMessage.replace("RF:", "");
    Serial.println("RF message: " + TextMessage);  // Print the received text message

    long rawMessage = TextMessage.toInt();
    Serial.println("RF converted message: " + rawMessage);  // Print the received text message
    sendViaRf(rawMessage);
  }
  TextMessage = "";  // Reset the text message
}



