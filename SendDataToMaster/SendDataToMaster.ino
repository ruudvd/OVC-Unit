#include <Wire.h>  
#define SLAVE_ADDRESS 0x40   // Define the i2c address
#define ENL 9
#define MotorL1 2
#define MotorL2 3
#define ENR 10
#define MotorR3 4
#define MotorR4 5
int PotentioInput = A7;
int Potentio = 0;
int SpeedInput = A1;
int Speed = 0;
  
void setup()
{
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  pinMode (ENL, OUTPUT);
  pinMode (MotorL1, OUTPUT);
  pinMode (MotorL2, OUTPUT);
  pinMode (ENR, OUTPUT);
  pinMode (MotorR3, OUTPUT);
  pinMode (MotorR4, OUTPUT);
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, LOW);
  digitalWrite(MotorR3, LOW);
  digitalWrite(MotorR4, LOW); 
}

void loop()
{
  // READ DATA
  Speed = analogRead(SpeedInput);
  Serial.print("Speed = ");
  Serial.print(Speed);
  //Wire.onRequest(sendData);
  if(Speed > 500){
   analogWrite(ENL, 200);
   analogWrite(ENR, 200);
   digitalWrite(MotorL1, HIGH);
   digitalWrite(MotorL2, LOW);
   digitalWrite(MotorR3, HIGH);
   digitalWrite(MotorR4, LOW);
  }
  else{
   analogWrite(ENL, 0);
   analogWrite(ENR, 0);
   digitalWrite(MotorL1, LOW);
   digitalWrite(MotorL2, LOW);
   digitalWrite(MotorR3, LOW);
   digitalWrite(MotorR4, LOW); 
  }
  delay(500);
  Serial.print(", Potentio = ");
  Potentio = analogRead(PotentioInput);
  Serial.println(Potentio);
  Wire.onRequest(sendPotentio);
  //delay(500);
}

void sendData()
{
  String datastring = String(Speed);
  char data[5] = "2000";
  datastring.toCharArray(data, datastring.length()+1);
  Wire.write(data); 
}

void sendPotentio()
{
  String datastring = String(Potentio);
  char data[5] = "2000";
  datastring.toCharArray(data, datastring.length()+1);
  Wire.write(data); 
}

