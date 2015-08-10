/*****************************************************
*        Arduino example for MD25                    *
*    MD25 is controlled using I2C                    *
*            is controlled using serial              *
*                                                    *
*              By James Henderson 2012               *
*            Edited by Ruud van Dommelen 2015        *
*****************************************************/
#include <Wire.h>

void setup()
{
  Wire.begin();
  Serial.begin(9600);                                       // Begin serial
  Serial.println("start programm");
  encodeReset();                                            // Cals a function that resets the encoder values to 0
  delay(50);
  SpeedControlReset();
  delay(50);                                                // Wait for everything to power up
}

void loop() 
{
  DistanceDrive(3000);
  delay(1000);
  Turn(90, 0);
  delay(1000);
}



