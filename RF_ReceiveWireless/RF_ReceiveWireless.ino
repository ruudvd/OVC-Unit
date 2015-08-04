/*
  Simple example for receiving

  http://code.google.com/p/rc-switch/
*/


#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#define buzzer 8

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
  pinMode (buzzer, OUTPUT) ;// set the digital IO pin mode, OUTPUT out of Wen
  Serial.print("Started");
}

void loop() {
  if (mySwitch.available()) {

    int value = mySwitch.getReceivedValue();

    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );

      digitalWrite (buzzer, HIGH) ;// send voice
      delay (10) ;// Delay 1ms
      digitalWrite (buzzer, LOW) ;// do not send voice
    }
    mySwitch.resetAvailable();
  }
}
