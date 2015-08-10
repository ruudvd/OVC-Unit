/*****************************************************
*        Arduino example for MD25                    *
*    MD25 is controlled using I2C                    *
*            is controlled using serial              *
*                                                    *
*              By James Henderson 2012               *
*            Edited by Ruud van Dommelen 2015        *
*****************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Pixy.h>

Pixy pixy;

#define CMD                 (byte)0x00                        // Values of 0 eing sent using write have to be cast as a byte to stop them being misinterperted as NULL
// This is a but with arduino 1
#define MD25ADDRESS         0x58                             // Address of the MD25
#define SOFTWAREREG         0x0D                              // Byte to read the software version
#define SPEED1              (byte)0x00                        // Byte to send speed to first motor
#define SPEED2              0x01                              // Byte to send speed to second motor
#define ENCODERONE          0x02                              // Byte to read motor encoder 1
#define ENCODERTWO          0x06                              // Byte to read motor encoder 2
#define VOLTREAD            0x0A                              // Byte to read battery volts
#define RESETENCODERS       0x20
#define CURRENTREADLEFT     0x0B
#define CURRENTREADRIGHT    0x0C



void setup()
{
  Wire.begin();
  Serial.begin(115200);                                       // Begin serial
  pixy.init();
  Serial.println("start programm");
  delay(100);                                               // Wait for everything to power up
  //encodeReset();                                            // Cals a function that resets the encoder values to 0
}

void loop() {
  uint16_t blocks;
  blocks = pixy.getBlocks();

  if (blocks)
  {
    int block1x = pixy.blocks[0].x;

    Serial.print("block 1 = ");
    Serial.println(block1x);
    //volts();
    if (block1x < 140)
    {
      Drive(98, 158);
      Serial.println("left");
    }
    else if (block1x > 160)
    {
      Drive(158, 98);
      Serial.println("right");
    }
    else if (140 < block1x < 150)
    {
      Drive(123, 133);
      Serial.println("lower speed left");
    }
    else if (150 < block1x < 160)
    {
      Drive(133, 123);
      Serial.println("lower speed right");
    }
  }

}



