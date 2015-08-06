#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

int IN_ReceiverID = 0;
int IN_SenderID = 0;
int IN_MessageID = 0;
int IN_Value1 = 0;
int IN_Value2 = 0;
int IN_Value3 = 0;
int IN_Checksum = 0;

int OUT_ReceiverID = 0;
#define OUT_SenderID 1
int OUT_MessageID = 0;
int OUT_Value1 = 0;
int OUT_Value2 = 0;
int OUT_Value3 = 0;
int OUT_Checksum = 0;

long IN_Raw_Value;

char Message[8];

RCSwitch mySwitch = RCSwitch();

void setup (){
  Serial.begin(9600);
  mySwitch.enableReceive(0);
}

void loop(){

  if (mySwitch.available()){
    Serial.print("Received ");
    Serial.println( mySwitch.getReceivedValue() );
    readMessage();

    if (IN_Checksum == calculateChecksum(IN_ReceiverID,IN_SenderID,IN_MessageID,IN_Value1,IN_Value2,IN_Value3)){
      Serial.print("Message ");
      Serial.print(Message);
      Serial.println(" = valid.");
    }  
    else {
      Serial.println("Message ");
      Serial.println(Message);
      Serial.println(" = invaled.");
      resetMessage();
    }
    mySwitch.resetAvailable();
  }
}

int calculateChecksum(int ReceiverID,int SenderID,int MessageID,int Value1,int Value2,int Value3) {
  int sum = (ReceiverID + SenderID + MessageID + Value1 + Value2 + Value3);
  Serial.println(sum);
  int modulo = (sum % 8);
  return modulo;
}

void sendMessage() {
  Serial.println(OUT_ReceiverID + OUT_SenderID + OUT_MessageID + OUT_Value1 + OUT_Value2 + OUT_Value3 + OUT_Checksum);
}

void readMessage(){

  IN_Raw_Value = mySwitch.getReceivedValue();
  String stringmessage = String(IN_Raw_Value);
  stringmessage.toCharArray(Message, 8);

  IN_ReceiverID = Message[0] - '0';
  IN_SenderID = Message[1] - '0';
  IN_MessageID = Message[2]  - '0';
  IN_Value1 = Message[3]  - '0';
  IN_Value2 = Message[4]  - '0';
  IN_Value3 = Message[5]  - '0';
  IN_Checksum = Message[6]  - '0';
}

void resetMessage(){
  IN_Raw_Value = 00000000;
  readMessage();
}



