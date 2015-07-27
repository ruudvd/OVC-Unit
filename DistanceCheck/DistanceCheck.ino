#include "HCSR04.h"
#include <core.h> // for pcDuino

#define TriggerPin 4
#define EchoPin 5
#define FrontDistance 6

HCSR04 ultrasonic(TriggerPin, EchoPin); //Trig, Echo
//define ultrasonic sensor
#define TriggerPin 4
#define EchoPin 5
#define FrontDistance 6

int cm;

boolean DistanceCheck()
{
  unsigned long cm;
  cm = ultrasonic.Ranging(CM); //CM of INCH

#ifdef UltraSonic
  if (cm <= FrontDistance)
  {
#ifdef DEBUG
    Serial.println("Distance Reached: ");
    Serial.print(cm);
#endif
    Drive(0);
    digitalWrite(13, HIGH);
    return true;
  }
  else
  {
    return false;
    digitalWrite(13, LOW);
  }
#endif

#ifndef UltraSonic
  return false;
#endif

}
