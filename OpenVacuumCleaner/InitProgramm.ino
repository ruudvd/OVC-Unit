#include <core.h> // for pcDuino

//timer variables
unsigned long StartTime;

void initprogramm()
{
  Serial.begin(115200);//begin serial communication (baudrate: 9600)

  // attach output to driving motor ports.
  pinMode (ENL, OUTPUT);
  pinMode (MotorL1, OUTPUT);
  pinMode (MotorL2, OUTPUT);
  pinMode (ENR, OUTPUT);
  pinMode (MotorR3, OUTPUT);
  pinMode (MotorR4, OUTPUT);

  //attach tcrt5000 IR sensor
  pinMode (OpticalFL, INPUT);
  pinMode (OpticalFR, INPUT);
  pinMode (OpticalRL, INPUT);
  pinMode (OpticalRR, INPUT);

  OpticalDefaultLevel = (analogRead(OpticalFR) + analogRead(OpticalFL) + analogRead(OpticalRR) + analogRead(OpticalRL)) / 4;
  OpticalTriggerLevel = (OpticalDefaultLevel + 200);

#ifdef DEBUG
  printf("programm is started -------------");
  Serial.println("programm is started -------------");
  Serial.print("Optical Default Level = ");
  Serial.println(OpticalDefaultLevel);
  Serial.print("Current Distance = ");
  Serial.println(ultrasonic.Ranging(CM)); 
  Serial.println("Wait 2 seconds to start");

#endif
  delay(2000); //startup delay
}


