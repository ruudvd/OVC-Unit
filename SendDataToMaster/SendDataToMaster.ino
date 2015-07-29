#include <Wire.h>  
#define SLAVE_ADDRESS 0x40   // Define the i2c address
char getal[5] = "985";

void setup()
{
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS); 

}

void loop()
{
  // READ DATA
  Wire.onRequest(sendData);
  Serial.println(getal);
  delay(250);
}

void sendData()
{
  Wire.write(getal); 
}

