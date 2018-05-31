#include "motor.h"
#include "receiver.h"
#define LED1 4

void setup()
{
  Serial.begin(9600);
  motor m;
  //Set motors to coast
  m.leftStop();
  m.rightStop();
  receiver_setup();
}

int val;

int right = 0, left = 0;

int straight_max_speed = 250;
int turning_max_speed = 250;

void loop()
{
  val = 0;
  motor m;
  receiving(val);
  int dir = val/100;
  int pwr = val%100;
  int power;
  if(dir%2 == 0)
    power = map(pwr, 0, 99, 0, straight_max_speed);
  else
    power = map(pwr, 0, 99, 0, turning_max_speed);
  switch(dir) {
    case 1:
      m.leftForward(power);
      m.rightForward(power);
      break;
    case 2:
      m.rightForward(power);
      m.leftBackward(power);
      break;
    case 3:
      m.rightBackward(power);
      m.leftBackward(power);
      break;
    case 4:
      m.leftForward(power);
      m.rightBackward(power);
      break;
    default:
      m.leftStop();
      m.rightStop();
  }
}
