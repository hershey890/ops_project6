#include "motor.h"
#include "receiver.h"
#define LED1 4

//float rfValue = 0;
int n = 3;

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

  if(receiving(rfValue)){
    Serial.println(rfValue);
    digitalWrite(LED1, HIGH);  
  }
  else {
    Serial.println("N");
    digitalWrite(LED1, LOW);
  }
  Serial.println(rfValue);
  
  right = rfValue/100 - 10;
  left = int(rfValue)%100 - 10;

  if (right == 25 && left == 25) { //stop
    m.rightStop();
    m.leftStop();
  }
  else if (right < 25 || left < 25) { //forward
    right = (250- 10 * right)/n;
    left = (250 - 10 * left)/n;
    m.leftForward(left);
    m.rightForward(right);
  }
  else if (right > 25 || left > 25) { //reverse
    right = (right * 10 - 250)/n;
    left = (left * 10 - 250)/n;
    m.leftBackward(left); 
    m.rightBackward(right);
  }
}
