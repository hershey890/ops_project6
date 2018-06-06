
#include "motor.h"
#include "receiver.h"
#define LED1 4

float rfValue = 0;
const float scale = 0.5; //must be less than 1

void setup()
{
  Serial.begin(9600);
  motor m;
  //Set motors to coast
  m.leftStop();
  m.rightStop();
  receiver_setup();
}

int right = 0, left = 0;

void loop()
{
  float rfValue = 0;
  motor m;
  receiving(rfValue);
  //Serial.println(rfValue);
  
  left = (int)(rfValue)/100 - 10;
  if (left < 0)
    left = 0;
  if (left > 50)
    left = 50;
      
  right = (int)(rfValue)%100 - 10;
  if (right < 0)
    right = 0;
  if (right > 50)
    right = 50;
  delay(40); //
  
  /*Serial.print("right ");
  Serial.print(right);
  Serial.print("left ");
  Serial.println(left);*/
  
  if (right == 25 && left == 25) { //stop
    m.rightStop();
    m.leftStop();
    //Serial.println("stop");
    //Serial.println(" S");
  }
  else if (right < 25 && left < 25) { //forward
    right = (250- 10 * right);
    left = (250 - 10 * left);
    //Serial.println("forward");
    /*
    Serial.print("forward");
    Serial.print(" ");
    Serial.print("right ");
    Serial.print(right);
    Serial.print("left ");
    Serial.println(left);
    */
    //Serial.println(" F");
    m.leftForward(left * scale);
    m.rightForward(right * scale);
  }
  //else if (right > 25 || left > 25) { //reverse
  else if (right > 25 && left > 25) { //reverse
    right = (right * 10 - 250);
    left = (left * 10 - 250);
    //Serial.println("backward");
    /*
    Serial.print("backward");
    Serial.print(" ");
    Serial.print("right ");
    Serial.print(right);
    Serial.print("left ");
    Serial.println(left);
    */
    //Serial.println(" B");
    m.leftBackward(left * scale); 
    m.rightBackward(right * scale);
  }
  else if (right > 25 && left < 25) {
    left = (250- 10 * left);
    right = (right * 10 - 250);
    m.leftForward(left * scale);
    m.rightBackward(right * scale);
  }
  else if (right < 25 && left > 25) {
    right = (250- 10 * right);
    left = (left * 10 - 250);
    m.leftBackward(left * scale);
    m.rightForward(right * scale);
  }
}
