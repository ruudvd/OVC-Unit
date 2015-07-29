/*
  HCSR04.h - Library for HC-SR04 Ultrasonic Ranging Module.library
	
  Created by iPrototype, based on library from ITead studio. 24 Jan, 2014.
  iprototype.nl
*/

#ifndef HCSR04_h
#define HCSR04_h

#define CM 1
#define INCH 0

class HCSR04
{
  public:
    HCSR04(int TP, int EP);
    long Ranging();
    long Ranging(int sys);

    private:
    long Timing();
    int Trig_pin;
    int Echo_pin;
    long  duration,distacne_cm,distance_inc;
    
};

#endif