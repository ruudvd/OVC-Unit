void Drive(int l, int r)
{
  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in x
  Wire.write(SPEED2);
  Wire.write(r);
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in x
  Wire.write(SPEED1);
  Wire.write(l);
  Wire.endTransmission();
}

void stopMotor() {                                          // Function to stop motors
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED2);
  Wire.write(StopSpeed);                                    // Sends a value of 128 to motor 2 this value stops the motor
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED1);
  Wire.write(StopSpeed);
  Wire.endTransmission();
}

void DistanceDrive(int d) //drive a distance straight in mm
{
  int EncCalc = PPT * (d / ( PI * WheelDiameter));
  encodeReset();
  Serial.println(EncCalc);
  do {                                                       // Start loop to drive motors forward
    Drive(DriveSpeed, DriveSpeed);
    encoder1();                                             // Calls a function that reads and displays value of encoder 1 to LCD03
    encoder2();                                             // Calls a function that reads and displays value of encoder 2 to LCD03
  } while (EncCalc > encoder2() || EncCalc > encoder1() );
  stopMotor();
}

void Turn(int degree, int dir)
{
  unsigned int TurnCalc = PPT * (( (degree * PI * WheelWidth) / 360) / (PI * WheelDiameter));
  encodeReset();
  Serial.println(TurnCalc);
  if (dir == 1)
  {
    do {                                                       // Start loop to drive motors forward
      Drive(128 + TurnConst, 128 - TurnConst);
      encoder1();                                             // Calls a function that reads and displays value of encoder 1 to LCD03
      encoder2();                                             // Calls a function that reads and displays value of encoder 2 to LCD03
    } while (TurnCalc >= encoder1() || -TurnCalc <= encoder2());
  }
  else if (dir == 0)
  {
    do {                                                       // Start loop to drive motors forward
      Drive(128 - TurnConst, 128 + TurnConst);
      encoder1();                                             // Calls a function that reads and displays value of encoder 1 to LCD03
      encoder2();                                             // Calls a function that reads and displays value of encoder 2 to LCD03
    } while (TurnCalc >= encoder2() || -TurnCalc <= encoder1());
  }
  stopMotor();
}

void SpeedControlReset() {                                       // This function disables the speedcontrol
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(CMD);
  Wire.write(0x30);                                         // Putting the value 0x30 to disable speed control
  Wire.endTransmission();
  delay(100);
}

void SpeedControlEnable()
{ // This function enables the speedcontrol
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(CMD);
  Wire.write(0x31);                                         // Putting the value 0x31 to enable speed control
  Wire.endTransmission();
  delay(100);
}





