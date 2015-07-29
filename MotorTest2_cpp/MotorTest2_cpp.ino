#include <core.h>

int Poort1 = 2;
int Poort2 = 3;
int Poort3 = 4;
int Poort4 = 5;
int Analog1 = 9;
int Analog2 = 10;

void setup() {
  pinMode (Poort1, OUTPUT);
  pinMode (Poort2, OUTPUT);
  pinMode (Poort3, OUTPUT);
  pinMode (Poort4, OUTPUT);
  pinMode (Analog1, OUTPUT);
  pinMode (Analog2, OUTPUT);
  digitalWrite (Poort1, HIGH);
  digitalWrite (Poort2, LOW);
  digitalWrite (Poort3, HIGH);
  digitalWrite (Poort4, LOW);
  analogWrite (Analog1, 200);
  analogWrite (Analog2, 200);
}

void loop() {
}
