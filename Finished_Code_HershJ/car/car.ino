#include "motor.h"
#include "receiver.h"
#define LED1 4

int getLeft(int val) {
  return ((val >> 8)&255) - 128;
}

int getRight(int val) {
  return ((val % 256) & 255) - 128;
}

motor m;

void setup()
{
	Serial.begin(9600);
  //motor m;
  //Set motors to coast
  m.leftStop();
  m.rightStop();
  receiver_setup();
}

float speedl = 0;
float speedr = 0;
float proportion = 0.1;

void loop()
{
  int rfValue = 0x8080;
  motor m;
  int left = 0;
  int right = 0;
  //if(receiving(rfValue)) {
  receiving(rfValue);
  left = getLeft(rfValue);
  right = getRight(rfValue);
  Serial.print("left: ");
  Serial.print(speedl);
  Serial.print("right: ");
  Serial.println(speedr);
  //} else {
    //digitalWrite(LED_BUILTIN, HIGH);
  //}
  
  /*  left = (int)(rfValue)/100 - 10;
    if (left < 0)
      left = 0;
    if (left > 50)
      left = 50;
      
    right = (int)(rfValue)%100 - 10;
    if (right < 0)
      right = 0;
    if (right > 50)
      right = 50;*/
  delay(40); //
  /*
  Serial.print("right ");
  Serial.print(right);
  Serial.print("left ");
  Serial.println(left);
  */
  /*if (right == 25 && left == 25) { //stop
    m.rightStop();
    m.leftStop();
    //Serial.println("stop");
    //Serial.println(" S");
  }*/
  /*else if (right < 25 && left < 25) { //forward
    right = (250- 10 * right);
    left = (250 - 10 * left);
    //Serial.println("forward");
    
    Serial.print("forward");
    Serial.print(" ");
    Serial.print("right ");
    Serial.print(right);
    Serial.print("left ");
    Serial.println(left);
    
    //Serial.println(" F");
    m.leftForward(left);
    m.rightForward(right);
  }*/
  /*else if (right > 25 || left > 25) { //reverse
    right = (right * 10 - 250);
    left = (left * 10 - 250);
    //Serial.println("backward");
    
    Serial.print("backward");
    Serial.print(" ");
    Serial.print("right ");
    Serial.print(right);
    Serial.print("left ");
    Serial.println(left);
    
    //Serial.println(" B");
    m.leftBackward(left); 
    m.rightBackward(right);
  }*/
  speedl+=left*proportion;
  speedr+=right*proportion;
  if(speedl > 255 )
    speedl = 255;
  if(speedl < -255 )
    speedl = -255;
  if(speedr > 255 )
    speedr = 255;
  if(speedr < -255 )
    speedr = -255;
  if(left == 0 && speedl >= -15 && speedl <= 15) {
    speedl = 0;
    m.leftStop();
  }
  if(right == 0 && speedr >= -15 && speedr <= 15) {
    speedr = 0;
    m.rightStop();
  }
  if(speedl >= 0) {
    m.leftForward(speedl);
  } else if(speedl < 0) {
    m.leftBackward(-speedl);
  }
  if(speedr >= 0) {
    m.rightForward(speedr);
  } else if(speedr < 0) {
    m.rightBackward(-speedr);
  }
  digitalWrite(LED_BUILTIN, LOW);
}
