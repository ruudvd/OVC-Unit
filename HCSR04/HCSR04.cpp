/*
  HCSR04.cpp - Library for HC-SR04 Ultrasonic Ranging Module.library
	
  Created by iPrototype, based on library from ITead studio. 24 Jan, 2014.
  iprototype.nl
*/

#include "Arduino.h"
#include "HCSR04.h"

HCSR04::HCSR04(int TP, int EP)
{
   pinMode(TP,OUTPUT);
   pinMode(EP,INPUT);
   Trig_pin=TP;
   Echo_pin=EP;
}

long HCSR04::Timing()
{
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);
  duration = pulseIn(Echo_pin,HIGH,32000);
  return duration;
}

long HCSR04::Ranging()
{
  return this->Ranging(1);
}

long HCSR04::Ranging(int sys)
{
  duration = Timing();
  if(duration >= 32000 || duration == 0)
  	return -1;
  distacne_cm = duration /29 / 2 ;
  distance_inc = duration / 74 / 2;
  if (sys)
  	return distacne_cm;
  else
  	return distance_inc;
}