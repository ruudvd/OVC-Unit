#include <Wire.h>  
#define SLAVE_ADDRESS 0x40   // Define the i2c address
char input;
String woord = "";

void setup()
{
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
}

void loop()
{
  Wire.onReceive(receiveData);
  delay(250);
}

void receiveData(int byteCount)
{
  while(Wire.available()) 
  {
    input = Wire.read();
    woord += input;
  }
  Serial.println(woord);
  woord = "";
}
