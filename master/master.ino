#include "transmitter.h"
#include <Wire.h>
#define button1 1
#define button2 4
#define button3 6

bool isRed = false;
bool isGreen = false;
bool isYellow = false;

bool redState = false;
bool yellowState = false;
bool greenState = false;

void setup() {
  // put your setup code here, to run once:
  wire.begin(104);
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  transmitter_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  float b1 = 1;
  float b2 = 2;
  float b3 = 3;
  Serial.println('A' + analogRead(button1));
  Serial.println('B' + analogRead(button2));
  Serial.println('C' + analogRead(button3));

 if(!redState && analogRead(button1) > 500) {
    sending(b1);
    isRed = true;
    redState = true;
    Serial.println(b1);
  } else if(isRed && analogRead(button1) <= 500) {
    sending(4);
    isRed = false;
    redState = false;
    Serial.println("4");
  }
  
  if(!yellowState && analogRead(button2) > 500) {
    sending(b2);
    isYellow = true;
    yellowState = true;
    Serial.println(b2);
  } else if(isYellow && analogRead(button2) <= 500) {
    sending(5);
    isYellow = false;
    yellowState = false;
    Serial.println("5");
  }
  
  if(!greenState && analogRead(button3) > 500) {
    sending(b3);
    isGreen = true;
    greenState = true;
    Serial.println(b3);
  } else if(isGreen && analogRead(button3) <= 500) {
    sending(6);
    isGreen = false;
    greenState = false;
    Serial.println("6");
  }
}
