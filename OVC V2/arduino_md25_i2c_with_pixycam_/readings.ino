byte getSoft() 
{                                             // Function that gets the software version
  Wire.beginTransmission(MD25ADDRESS);                      // Send byte to read software version as a single byte
  Wire.write(SOFTWAREREG);
  Wire.endTransmission();

  Wire.requestFrom(MD25ADDRESS, 1);                         // request 1 byte form MD25
  while (Wire.available() < 1);                             // Wait for it to arrive
  byte software = Wire.read();                            // Read it in

  return (software);
}

void volts() 
{                                              // Function to read and display battery volts as a single byte
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

