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
  Wire.write(128);                                           // Sends a value of 128 to motor 2 this value stops the motor
  Wire.endTransmission();

  Wire.beginTransmission(MD25ADDRESS);
  Wire.write(SPEED1);
  Wire.write(128);
  Wire.endTransmission();
}
