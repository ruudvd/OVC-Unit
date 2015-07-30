//This Arduino file reads a voltage and sends the value to the Master (a Raspberry PI 2) via I2C.

#include <Wire.h>  // The wire.h library is needed for I2C communication
#define SLAVE_ADDRESS 0x40   // This is the address needed for I2C communication
#define VoltPort = A1;  // This defines the port which reads the voltage level
int VoltVar = 0;  // This variable stores the voltage level
  
void setup()
{
  Serial.begin(9600);  // OPTIONAL: This starts a serial communication. Start the serial monitor to see what the program does
 
  Wire.begin(SLAVE_ADDRESS);  // Start communication on the defined address
}

void loop()
{
  // First we read an analog value. The input is between 0 V and 5 V.
  // The arduino can read 1024 values from 0 to 1023 where 0 V = 0 and 5 V = 1023.
  VoltVar = analogRead(VoltPort);  // Read the analog port and write it to a variable
  
  Serial.print("Speed = ");  // SERIAL MONITOR: Print the speed
  Serial.print(Speed);
  
  Wire.onRequest(sendData);  // Start the void on the bottom of page
  
  delay(250);  // A delay of 250ms, the result is that data is sended about 4 times a second
}

void sendData()  
{
  // On I2C you can only send data as a 'char array'. The analogread stores data as an integer.
  // First thing to do is to convert the integer into a char array.
  // For more information about data types check the link and search for Data Types https://www.arduino.cc/en/Reference/HomePage 
  String datastring = String(VoltVar);  // Convert the integer voltage to a string and save it in a variable
  
  // The largest number we want to send is 1023 (4 numbers).
  char data[5] = "9999";  // Make a char array of length 5. You can store 4 numbers and need a 5th place for a 'null-terminate'. This marks the end of an array.
  datastring.toCharArray(data, datastring.length()+1);  // Convert the datastring to a char array. The length is our data, added by 1 (for the null-terminate).
  Wire.write(data);  // Write the data over I2C 
}
