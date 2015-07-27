#include <core.h> // for pcDuino

boolean Turn(int d, int a)
{
  //function to turn robot based on time
  int TurnConstantRight = 8;
  int TurnConstantLeft = 8;

  unsigned long time = millis();

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
  else  if (EdgeCheck())
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
  }
  else if (d == 1) // if d is 1 turn right
  {
#ifdef DEBUG
    Serial.println("Turn ");
    Serial.println(a);
    Serial.println(" Degrees");
#endif
    while ((millis() <= time + (TurnConstantRight * a))) //&& !RearEdgeCheck() && !EdgeCheck)
    {
      Serial.println("Turning Right");
      Drive(5);
    }
#ifdef DEBUG
    Serial.println("Finished");
#endif
    Drive(0);
    return true;
  }
  else if (d == 0) // if d is 1 turn right
  {
#ifdef DEBUG
    Serial.println("Turn ");
    Serial.println(a);
    Serial.println(" Degrees");
#endif
    while ((millis() <= time + (TurnConstantLeft * a))) //&& !RearEdgeCheck() && !EdgeCheck)
    {
      Serial.println("Turning Left");
      Drive(3);
    }
#ifdef DEBUG
    Serial.println("Finished");
#endif
    Drive(0);
    return true;
  }
}
