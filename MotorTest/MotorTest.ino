#include <core.h>

#define ENL A1
#define MotorL1 2
#define MotorL2 3
#define ENR A2
#define MotorR3 4
#define MotorR4 5

void setup() {
  Serial.begin(115200);//begin serial communication (baudrate: 115200)
  Serial.println (" Start code ");  // attach output to driving motor ports.
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

void loop() {
  // put your main code here, to run repeatedly: 
 analogWrite(A1, LOW);
 analogWrite(A2, LOW);
 digitalWrite(MotorL1, LOW);
 digitalWrite(MotorL2, HIGH);
 digitalWrite(MotorR3, LOW);
 digitalWrite(MotorR4, HIGH);
 delay (1000);
 analogWrite(A1, HIGH);
 analogWrite(A2, HIGH);
 digitalWrite(MotorL1, HIGH);
 digitalWrite(MotorL2, LOW);
 digitalWrite(MotorR3, HIGH);  
 digitalWrite(MotorR4, LOW);
 delay(1000);
 }
