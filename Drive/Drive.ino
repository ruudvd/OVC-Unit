#include <core.h> // for pcDuino

// Drive function for vacuum cleaner.

//Previous Drive command
unsigned int prevDriveCommand;

//defines for motors (L298N motor driver 1X):
//LEFT motor
#define ENL A1 //analog PWM port Left
#define MotorL1 1 //digital port IN1
#define MotorL2 2 //digital port IN2
//RIGHT motor
#define ENR A2 //analog PWM port Right
#define MotorR3 3 //digital port IN3
#define MotorR4 4 //digital port IN4

void Drive(int DriveCommand)
{
  /*
    DriveCommand    Modus
    0               Stop
    1               Drive Forward
    2               Drive Reverse
    3               Turn Left on own axle
    4               Turn Left reverse left wheel only
    5               Turn Right on own axle
    6               Turn Right reverse right wheel only
  */

  // define default motor speeds
  const unsigned int MotorSpeed = 200; //motor speed for driving
  const unsigned int TurnSpeed = 200; //turn speed for turning
  //variables for motor direction and speed
  unsigned int IN1 = LOW; //Left1
  unsigned int IN2 = LOW; //Left2
  unsigned int IN3 = LOW; //Right1
  unsigned int IN4 = LOW; //Right2
  unsigned int MotorSpeedLeft = 0;
  unsigned int MotorSpeedRight = 0;

  switch (DriveCommand)
  {
    case 0: //stop
      IN1 = LOW; //set motors to IN1 = IN2 => fast motor stop (motors must be enabled for fast motor stop
      IN2 = LOW;
      IN3 = LOW;
      IN4 = LOW;
      MotorSpeedLeft = 0; //disable Left motor
      MotorSpeedRight = 0; //disable Right motor
      break;

    case 1: //drive forward
      MotorSpeedLeft = MotorSpeed; //PWM Left motor
      MotorSpeedRight = MotorSpeed; //PWM Right motor
      IN1 = HIGH; //set motors to IN1 = HIGH IN2 = LOW => drive forward
      IN2 = LOW;
      IN3 = HIGH;
      IN4 = LOW;
      break;

    case 2: //drive reverse
      MotorSpeedLeft = MotorSpeed; //PWM Left motor
      MotorSpeedRight = MotorSpeed; //PWM Right motor
      IN1 = LOW; //set motors to IN1 = LOW IN2 = HIGH => drive reverse
      IN2 = HIGH;
      IN3 = LOW;
      IN4 = HIGH;
      break;

    case 3: //turn left on own axle
      MotorSpeedLeft = TurnSpeed; //PWM turn Left motor
      MotorSpeedRight = TurnSpeed; //PWM turn Right motor
      IN1 = LOW; //put left in reverse
      IN2 = HIGH;
      IN3 = HIGH; //put right in forward
      IN4 = LOW;
      break;

    case 4: //turn left reverse left wheel only
      MotorSpeedLeft = TurnSpeed; //PWM turn Left motor
      MotorSpeedRight = 0; //PWM turn Right motor
      IN1 = LOW; //put left in reverse
      IN2 = HIGH;
      IN3 = LOW; //put right in stop
      IN4 = LOW;
      break;

    case 5: //turn right on own axle
      MotorSpeedLeft = TurnSpeed; //PWM turn Left motor
      MotorSpeedRight = TurnSpeed; //PWM turn Right motor
      IN1 = HIGH; //put left in forward
      IN2 = LOW;
      IN3 = LOW; //put right in reverse
      IN4 = HIGH;
      break;

    case 6: //turn right reverse right wheel only
      MotorSpeedLeft = TurnSpeed; //PWM turn Left motor
      MotorSpeedRight = TurnSpeed; //PWM turn Right motor
      IN1 = LOW; //put left in forward
      IN2 = LOW;
      IN3 = LOW; //put right motor in stop
      IN4 = HIGH;
      break;
    default:  //else stop the motors
      {
        DriveCommand = 0;
      }
  }
#ifdef TESTDRIVE
  // write values to motors controller
  digitalWrite(MotorL1, IN1);
  digitalWrite(MotorL2, IN2);
  digitalWrite(MotorR3, IN3);
  digitalWrite(MotorR4, IN4);
  analogWrite(ENL, MotorSpeedLeft);
  analogWrite(ENR, MotorSpeedRight);
#endif

#ifdef DEBUG
  char* Message[] = {"STOP driving", "driving forward", "driving reverse", "turn left on own axle", "turn left reverse left wheel only", "turn right on own axle", "turn right reverse right wheel only"};
  if (DriveCommand != prevDriveCommand)
  {
    Serial.println(Message[DriveCommand]);
    prevDriveCommand = DriveCommand;
  }
#endif

}




