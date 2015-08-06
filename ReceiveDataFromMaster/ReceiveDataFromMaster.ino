// This Arduino file receives a text message from the Master (a Raspberry PI 2) via I2C.

#include <Wire.h>  // The wire.h library is needed for I2C communication
#define SLAVE_ADDRESS 0x40   // This is the address needed for I2C communication
char ReceivedData;  // Declare a character
String TextMessage = "";  // Declare an empty string

void setup()
{
  Serial.begin(9600);  // OPTIONAL: This starts a serial communication. Start the serial monitor to see what the program does
 
  Wire.begin(SLAVE_ADDRESS);  // Start communication on the defined address
}

void loop()
{
  Wire.onReceive(receiveData);  // Start the void on the bottom of page
  delay(250);  // A delay of 250ms, the result is that data is sended about 4 times a second
}

void receiveData(int byteCount)
{
  // On I2C you can only send data as a 'char'. We receive one character at a time so we have to concatenate them.
  while(Wire.available())  // As long as there is information comming, do:
  {
    ReceivedData = Wire.read();  // Read the incomming character
    TextMessage += ReceivedData;  // Add the character to the characters you got earlier (construct a string).
  }
  Serial.println(TextMessage);  // Print the received text message
  TextMessage = "";  // Reset the text message
}
