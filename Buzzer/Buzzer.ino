//Example Code for KY-006

int buzzer = 8 ;// setting controls the digital IO foot buzzer
void setup ()
{
  pinMode (buzzer, OUTPUT) ;// set the digital IO pin mode, OUTPUT out of Wen
}
void loop ()
{
    digitalWrite (buzzer, HIGH) ;// send voice
    delay (10) ;// Delay 1ms
    digitalWrite (buzzer, LOW) ;// do not send voice
    delay (1000) ;// delay ms
}
