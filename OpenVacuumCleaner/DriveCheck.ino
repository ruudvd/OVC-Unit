#include <core.h> // for pcDuino

boolean DriveCheck()
{
  if (RearEdgeCheck()) //rear edge detected => go reverse and turn a bit
  {
    unsigned long time = millis();
#ifdef DEBUG
    Serial.println("Rear STOP detected ");
#endif
    Drive(0); //stop motors
    while ((millis() <= time + 2000) && !EdgeCheck())
    {
      Drive(1); //reverse
    }
    Turn(1, 90); //turn 90 degrees right
    return true;
  }
  else if (DistanceCheck()) //distance from front detected
  {
    unsigned long time = millis();
#ifdef DEBUG
    Serial.println("Front Distance STOP detected");
#endif
    Drive(0); //stop
    while ((millis() <= time + 2000) && !RearEdgeCheck()) //time + check rear sensors
    {
      Drive(2);//reverse
    }
    Turn(1, 90); //turn 90 degrees right


    return true;
  }
  else if (EdgeCheck())
  {
    unsigned long time = millis();
#ifdef DEBUG
    Serial.println("Front Edge detected");
#endif
    Drive(0);//stop motors
    while ((millis() <= (time + 2000)) && !RearEdgeCheck())
    {
      Drive(2);//reverse
    }
    Turn(1, 90); //turn 90 degrees right
    return true;
  }
  else
  {
    return false;
  }
}
