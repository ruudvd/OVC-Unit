#include <Wire.h>  
#define SLAVE_ADDRESS 0x40   // Define the i2c address

int number = 947;
  
void setup()
{
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS); 

}

void loop()
{
  // READ DATA
  Wire.onRequest(sendData);
  Serial.println(number);
  delay(250);
}

void sendData()
{
  String datastring = String(number);
  char data[5] = "2000";
  datastring.toCharArray(data, datastring.length()+1);
  Wire.write(data); 
}

