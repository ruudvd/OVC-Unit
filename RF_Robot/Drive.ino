/**
 * Enable the motors to drive at a certain speed. Speed value of 128 stops the motors,
 * a value of 255 isfull forward and a value of 0 is full reverse
 *
 * @param leftSpeed Speed of the left motor.
 * @param rightSpeed Speed of the left motor
 */
void Drive(int leftSpeed, int rightSpeed)
{
  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 2 at speed value stored in x
  Wire.write(SPEED2);
  Wire.write(rightSpeed);
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);                    // Drive motor 1 at speed value stored in x
  Wire.write(SPEED1);
  Wire.write(leftSpeed);
  Wire.endTransmission();
}

/**
 * Stops the motors instantly.
 */
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

/**
 * Drive straight forward for a certain distance
 *
 * @param distance Distance in milimeters
 */
void DistanceDrive(int distance) //drive a distance straight in mm
{
  int EncCalc = PPT * (distance / ( PI * WheelDiameter));
  encodeReset();
  Serial.println(EncCalc);
  do {                                                       // Start loop to drive motors forward
    Drive(DriveSpeed, DriveSpeed);
    encoder1();                                             // Calls a function that reads and displays value of encoder 1 to LCD03
    encoder2();                                             // Calls a function that reads and displays value of encoder 2 to LCD03
  } while (EncCalc > encoder2() || EncCalc > encoder1() );
  stopMotor();
}


/**
 * Turn for a certain angle
 *
 * @param degree Angle degree
 * @param dir Direction to turn. 1 is right, 0 is left.
 */
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

void encodeReset() {                                       // This function resets the encoder values to 0
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(CMD);
  Wire.write(0x20);                                         // Putting the value 0x20 to reset encoders
  Wire.endTransmission();
  delay(100);
}

long encoder1() {                                           // Function to read and display value of encoder 1 as a long
  Wire.beginTransmission(MD25ADDRESS);                      // Send byte to get a reading from encoder 1
  Wire.write(ENCODERONE);
  Wire.endTransmission();

  Wire.requestFrom(MD25ADDRESS, 4);                         // Request 4 bytes from MD25
  while (Wire.available() < 4);                             // Wait for 4 bytes to arrive
  long poss1 = Wire.read();                                 // First byte for encoder 1, HH.
  poss1 <<= 8;
  poss1 += Wire.read();                                     // Second byte for encoder 1, HL
  poss1 <<= 8;
  poss1 += Wire.read();                                     // Third byte for encoder 1, LH
  poss1 <<= 8;
  poss1  += Wire.read();                                    // Fourth byte for encoder 1, LL
  Serial.println();
  Serial.print("Encoder 1 = ");
  Serial.println(poss1, DEC);
  delay(50);                                                // Wait for everything to make sure everything is sent

  return (poss1);
}

long encoder2() {                                           // Function to read and display velue of encoder 2 as a long
  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(ENCODERTWO);
  Wire.endTransmission();

  Wire.requestFrom(MD25ADDRESS, 4);                         // Request 4 bytes from MD25
  while (Wire.available() < 4);                             // Wait for 4 bytes to become available
  long poss2 = Wire.read();
  poss2 <<= 8;
  poss2 += Wire.read();
  poss2 <<= 8;
  poss2 += Wire.read();
  poss2 <<= 8;
  poss2  += Wire.read();

  Serial.print("Encoder 2 = ");
  Serial.println(poss2, DEC);
  delay(50);                                                // Wait to make sure everything is sent

  return (poss2);
}

void volts()
{ // Function to read and display battery volts as a single byte
  Wire.beginTransmission(MD25ADDRESS);                      // Send byte to read volts
  Wire.write(VOLTREAD);
  Wire.endTransmission();

  Wire.requestFrom(MD25ADDRESS, 1);
  while (Wire.available() < 1);
  int batteryVolts = Wire.read();

  Serial.print("Battery v = ");
  Serial.print(batteryVolts / 10, DEC);                     // Print batery volts / 10 to give you the number of whole volts
  Serial.print(".");                                        // As arduino has truncates floating point numbers we print a . here to act as a decimal point
  Serial.print(batteryVolts % 10, DEC);                     // Prints Battery volts % 10 to give us the

  delay(50);                                                // Wait to make sure everything is sent
}
