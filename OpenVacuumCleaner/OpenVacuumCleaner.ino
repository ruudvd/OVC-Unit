/**************************************************************************************************************
   ___  ____  _____ _   _  __     ___    ____ _   _ _   _ __  __    ____ _     _____    _    _   _ _____ ____
  / _ \|  _ \| ____| \ | | \ \   / / \  / ___| | | | | | |  \/  |  / ___| |   | ____|  / \  | \ | | ____|  _ \
 | | | | |_) |  _| |  \| |  \ \ / / _ \| |   | | | | | | | |\/| | | |   | |   |  _|   / _ \ |  \| |  _| | |_) |
 | |_| |  __/| |___| |\  |   \ V / ___ \ |___| |_| | |_| | |  | | | |___| |___| |___ / ___ \| |\  | |___|  _ <
  \___/|_|   |_____|_| \_|    \_/_/   \_\____|\___/ \___/|_|  |_|  \____|_____|_____/_/   \_\_| \_|_____|_| \_\

 Huijbregts Innovation Center => www.hg-hic.eu
 Project: Open Vacuum Cleaner (OVC)
 Coded by: Ruud
 ______________________________________________________________________________________________________________
 Descripton:

***************************************************************************************************************/
#include <core.h> // for pcDuino

//debug mode
#define DEBUG 1 // put // in front to disable debug mode

//test drive modus
#define TESTDRIVE 1 // put testdrive modus (enable motors)

//enable ultrasonic
//#define UltraSonic 1 //disable ultrasonic sensor on the front of the robot

//state machine variables
unsigned int state = 0;//initialize state for state machine(default = 0)

void setup()
{
  initprogramm(); //init all ports
}

void loop()
{
  switch (state)
  {
    case 0: 

      Drive(1);
      DriveCheck();
      break;
    case 1: //start driving forward
      Serial.println("case1");
      break;
  }

}

