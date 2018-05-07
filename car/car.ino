#include "motor.h"
#include "receiver.h"
#define LED1 4

float rfValue = 0;
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

void LED();

void loop()
{
  motor m;
  LED();
  
  right = rfValue/100 - 10;
  left = int(rfValue)%100 - 10;

  if (right == 25 && left == 25) { //stop
    m.rightStop();
    m.leftStop();
  }
  else if (right < 25 || left < 25) { //forward
    right = ((right * -1) * 10 + 250)/n;
    left = ((left * -1) * 10 + 250)/n;
    m.leftForward(right);
    m.rightForward(left);
  }
  else if (right > 25 || left > 25) { //reverse
    right = (right * 10 - 250)/n;
    left = (left * 10 - 250)/n;
    m.leftBackward(right);
    m.rightBackward(right);
  }
}

void LED() {
  if(receiving(rfValue)){
    Serial.println(rfValue);
    digitalWrite(LED, HIGH);  
  }
  else {
    Serial.println("N");
    digitalWrite(LED1, LOW);
  }
}
