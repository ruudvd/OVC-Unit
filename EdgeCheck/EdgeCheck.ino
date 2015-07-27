#include <core.h> // for pcDuino

//define tcrt5000 ir sensor
#define OpticalFL A3
#define OpticalFR A4
#define OpticalRL A5
#define OpticalRR A6

int OpticalTriggerLevel = 0; //set trigger level by init programm measurement

//init optical sensors
int OpticalDefaultLevel; //measure start level


//edge detection for front of the robot
boolean EdgeCheck()
{
  if (analogRead(OpticalFR) > OpticalTriggerLevel) //if robot is over edge it must stop
  {
#ifdef DEBUG
    Serial.println("Right Front Edge detected");
#endif
    return true;
  }
  else if (analogRead(OpticalFL) > OpticalTriggerLevel) //if robot is over edge it must stop
  {

#ifdef DEBUG
    Serial.println("Left Front Edge detected");
#endif
    return true;
  }
  else
  {
    return false;
  }
}
//edge detection for rear of the robot
boolean RearEdgeCheck()
{

  if (analogRead(OpticalRR) > OpticalTriggerLevel) //if robot is over edge it must stop
  {
#ifdef DEBUG
    Serial.println("Right Rear edge detected");
#endif
    return true;
  }
  else if (analogRead(OpticalRL) > OpticalTriggerLevel) //if robot is over edge it must stop
  {
#ifdef DEBUG
    Serial.println("Rear Left edge detected");
#endif
    return true;
  }
  else
  {
    return false;
  }
}
