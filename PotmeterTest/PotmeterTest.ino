#include <core.h>

int Poort1 = 8;
int Poort2 = 9;
int Poort3 = 10;
int Poort4 = 11;
int SpeedMeter = 0;
int DirectionMeter = 1;
int SpeedValue = 15;
int DirectionValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode (Poort1, OUTPUT);
  pinMode (Poort2, OUTPUT);
  pinMode (Poort3, OUTPUT);
  pinMode (Poort4, OUTPUT);
  pinMode (DirectionMeter, INPUT);
  pinMode (SpeedMeter, INPUT);
  digitalWrite (Poort1, LOW);
  digitalWrite (Poort2, LOW);
  digitalWrite (Poort3, LOW);
  digitalWrite (Poort4, LOW);
}

void loop() {
  SpeedValue = analogRead(SpeedMeter);
  DirectionValue = analogRead(DirectionValue);
  
  //analogWrite ();
  //analogWrite ();
  Serial.print("Speed: ");
  Serial.print(SpeedValue);
  Serial.print(", Direction:  ");
  Serial.print(DirectionValue);
  Serial.println();
}
