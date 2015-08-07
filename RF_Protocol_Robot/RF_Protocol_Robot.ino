#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

const int drivingSpeed = 150;
const int turningTime = 50;
const int drivingTime = 250;
const int robotId = 1;
const int broadcastId = 9;

boolean debug = true;

int IN_ReceiverID = 0;
int IN_SenderID = 0;
int IN_MessageID = 0;
int IN_Value1 = 0;
int IN_Value2 = 0;
int IN_Value3 = 0;
int IN_Checksum = 0;

int OUT_ReceiverID = 0;
#define OUT_SenderID 1
int OUT_MessageID = 0;
int OUT_Value1 = 0;
int OUT_Value2 = 0;
int OUT_Value3 = 0;
int OUT_Checksum = 0;

#define ENL 3 //analog PWM port Left
#define MotorL4 4 //digital port IN1
#define MotorL5 5 //digital port IN2
//RIGHT motor
#define ENR 8 //analog PWM port Right
#define MotorR6 6 //digital port IN3
#define MotorR7 7 //digital port IN4

long IN_Raw_Value;

char Message[8];

RCSwitch mySwitch = RCSwitch();

void setup () {
  Serial.begin(9600);
  mySwitch.enableReceive(0);

  pinMode (ENL, OUTPUT);
  pinMode (MotorL4, OUTPUT);
  pinMode (MotorL5, OUTPUT);
  pinMode (ENR, OUTPUT);
  pinMode (MotorR6, OUTPUT);
  pinMode (MotorR7, OUTPUT);

  stopDriving();
}

void loop() {

  if (mySwitch.available()) {
    Serial.print("Received message: ");
    Serial.println( mySwitch.getReceivedValue() );
    readMessage();

    if (IN_Checksum == calculateChecksum(IN_ReceiverID, IN_SenderID, IN_MessageID, IN_Value1, IN_Value2, IN_Value3)) { //Message is valid
      Serial.print("Message ");
      Serial.print(Message);
      Serial.println(" is a valid message");

      if (IN_ReceiverID == robotId || IN_ReceiverID == broadcastId) { //Message is send to this robot

        switch (IN_MessageID)  { //Command type
            
          case 0: //Ping
            break;
          case 1: //Battery status
            break;
          case 2: //Go to Home
            break;
          case 3: //GoTo <location>
            break;
          case 4: //Move <direction> <amount>
            handleMove();
            break;
          case 5: //Not used yet
            break;
          case 6: //Not used yet
            break;
          case 7: //Not used yet
            break;
          case 8: //Acknowledge
            break;
          case 9: //STOP
            break;
        }

      } else {
        logMessage("Message is not for this robot");
      }
    } else {
      logMessage("Message is not valid");
      resetMessage();
    }
    mySwitch.resetAvailable();
  }
}

/**
 * Handles the 'move <direction> <amount>'-command.
 *
 * <direction>:
 *
 * 0 - Straigt forward
 * 1 - Backwards
 * 2 - Right
 * 3 - Left
 *
 * <amount>: amount in centimeters to drive.
 *
 * distance in cm = 2 x (amount +1)
 */
void handleMove() {
  logMessage("MessageID: Drive");

  switch (IN_Value1)  {

    case 0: //drive forward
      logMessage("Value1: Forward");
      driveForTime(HIGH, LOW, HIGH, LOW);
      break;

    case 1: //drive reverse
      logMessage("Value1: Reverse");
      driveForTime(LOW, HIGH, LOW, HIGH);
      break;

    case 2: //drive right
      logMessage("Value1: Right");
      driveForTime(LOW, LOW, LOW, HIGH, turningTime, turningTime);
      break;

    case 3: //drive left
      logMessage("Value1: Left");
      driveForTime(LOW, HIGH, LOW, LOW, turningTime, turningTime);
      break;
  }
}

/**
 * Calculates the checksum for the given parameters. The checksum is equal
 * to the modulo of 8 of the total sum of all parameters.
 *
 * checksum = (sum(parameters) % 8)
 */
int calculateChecksum(int ReceiverID, int SenderID, int MessageID, int Value1, int Value2, int Value3) {
  int sum = (ReceiverID + SenderID + MessageID + Value1 + Value2 + Value3);
  int modulo = (sum % 8);
  return modulo;
}

void sendMessage() {
  Serial.println(OUT_ReceiverID + OUT_SenderID + OUT_MessageID + OUT_Value1 + OUT_Value2 + OUT_Value3 + OUT_Checksum);
}

/**
 * Sets all values with the new received message
 */
void readMessage() {

  IN_Raw_Value = mySwitch.getReceivedValue();
  String stringmessage = String(IN_Raw_Value);
  stringmessage.toCharArray(Message, 8);

  IN_ReceiverID = Message[0] - '0';
  IN_SenderID = Message[1] - '0';
  IN_MessageID = Message[2]  - '0';
  IN_Value1 = Message[3]  - '0';
  IN_Value2 = Message[4]  - '0';
  IN_Value3 = Message[5]  - '0';
  IN_Checksum = Message[6]  - '0';
}

/**
 * Sets all values to 0
 */
void resetMessage() {
  IN_Raw_Value = 00000000;
  readMessage();
}

/**
 * Sets motor states according to parameter values with default driving speed and driving time
 * @param ml4 moter left first port state
 * @param ml5 moter left second port state
 * @param mr6 moter right first port state
 * @param mr7 moter right second port state
 */
void driveForTime(int ml4, int ml5, int mr6, int mr7) {
  driveForTime(ml4, ml5, mr6, mr7, drivingTime);
}

/**
 * Sets motor states according to parameter values with variable driving time
 * @param ml4 moter left first port state
 * @param ml5 moter left second port state
 * @param mr6 moter right first port state
 * @param mr7 moter right second port state
 * @param delayTime time to drive
 */
void driveForTime(int ml4, int ml5, int mr6, int mr7, int delayTime) {
  driveForTime(ml4, ml5, mr6, mr7, drivingSpeed, drivingSpeed, delayTime);
}

/**
 * Sets motor states according to parameter values with default driving speed
 * @param ml4 moter left first port state
 * @param ml5 moter left second port state
 * @param mr6 moter right first port state
 * @param mr7 moter right second port state
 * @param speedL moter left speed
 * @param speedL moter right speed
 * @param delayTime time to drive
 */
void driveForTime(int ml4, int ml5, int mr6, int mr7, int speedL, int speedR) {
  driveForTime(ml4, ml5, mr6, mr7, speedL, speedR);
}

/**
 * Sets motor states according to parameter values with variable driving speed
 * @param ml4 moter left first port state
 * @param ml5 moter left second port state
 * @param mr6 moter right first port state
 * @param mr7 moter right second port state
 * @param speedL moter left speed
 * @param speedL moter right speed
 * @param delayTime time to drive
 */
void driveForTime(int ml4, int ml5, int mr6, int mr7, int speedL, int speedR, int delayTime) {
  drive(ml4, ml5, mr6, mr7, speedL, speedR);
  delay(delayTime);
  stopDriving();
}

/**
 * Sets motor states according to parameter values with default driving speed
 * @param ml4 moter left first port state
 * @param ml5 moter left second port state
 * @param mr6 moter right first port state
 * @param mr7 moter right second port state
 */
void drive(int ml4, int ml5, int mr6, int mr7) {
  drive(ml4, ml5, mr6, mr7, drivingSpeed, drivingSpeed);
}

/**
 * Sets motor states according to parameter values
 * @param ml4 moter left first port state
 * @param ml5 moter left second port state
 * @param mr6 moter right first port state
 * @param mr7 moter right second port state
 */
void drive(int ml4, int ml5, int mr6, int mr7, int speedL, int speedR) {
  digitalWrite(ENL, speedL);
  digitalWrite(ENR, speedR);
  digitalWrite(MotorL4, ml4);
  digitalWrite(MotorL5, ml5);
  digitalWrite(MotorR6, mr6);
  digitalWrite(MotorR7, mr7);
}

/**
 * Stops the motors
 */
void stopDriving() {
  drive(LOW, LOW, LOW, LOW, 0, 0);
}

/**
 * Log a message when debugging is enabled
 */
void logMessage(String message) {
  if (debug) {
    Serial.println(message);
  }
}


