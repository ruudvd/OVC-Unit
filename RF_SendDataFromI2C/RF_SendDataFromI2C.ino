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
  Serial.println("Start");  // Print the received text message

}

void loop() {
  Wire.onReceive(receiveData);  // Start the void on the bottom of page
  Wire.onRequest(request);  // Start the void on the bottom of page

}

void sendViaRf(long message) {
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

    char bufferMessage[TextMessage.length() + 1]; // make this at least big enough for the whole string
    TextMessage.toCharArray(bufferMessage, sizeof(bufferMessage)); //Create a char array
    long rawMessage = atol(bufferMessage); //Convert char array to long

    Serial.print("RF converted message: ");  // Print the received text message
    Serial.println(rawMessage);  // Print the received text message
    sendViaRf(rawMessage);
  }
  TextMessage = "";  // Reset the text message
}

void request()
{
  Serial.println("REQUESTED"); // Inform user that data is sent.
  // On I2C you can only send data as a 'char array'. The analogread stores data as an integer.
  // First thing to do is to convert the integer into a char array.
  // For more information about data types check the link and search for Data Types https://www.arduino.cc/en/Reference/HomePage
  String datastring = String(1111);  // Convert the integer voltage to a string and save it in a variable

  // The largest number we want to send is 1023 (4 numbers).
  char data[5] = "9999";  // Make a char array of length 5. You can store 4 numbers and need a 5th place for a 'null-terminate'. This marks the end of an array.
  datastring.toCharArray(data, datastring.length() + 1); // Convert the datastring to a char array. The length is our data, added by 1 (for the null-terminate).
  Wire.write(data);  // Write the data over I2C
  Serial.println("  =>  Voltage is sent"); // Inform user that data is sent.
}
