#include <Wire.h>  
#define SLAVE_ADDRESS 0x40   // Define the i2c address
char input;
String woord = "";
String replystr = "";
char replychar[0];

void setup()
{
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
}
  
void loop()
{
  Wire.onReceive(receiveData);
  Wire.onRequest(confirm);
  delay(250);
}

void receiveData(int byteCount)
{
  while(Wire.available()) 
  {
    input = Wire.read();
    woord += input;
  }
  Serial.print("Ik ontvang: ");
  Serial.println(woord);
  woord = "";
}

  void confirm()
{
  replystr = "Received: ";
  replystr = replystr + woord;
  Serial.print("Ik verstuur: ");
  Serial.println(replystr);
  replystr.toCharArray(replychar, replystr.length()+1);
  Wire.write(replychar); 
}
