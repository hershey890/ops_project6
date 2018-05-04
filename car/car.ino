#include "motor.h"
#include "receiver.h"
//#include "printf.h"

#define LED 4

void setup()
{
	Serial.begin(9600);
  receiver_setup();
	motor m;
	//Set motors to coast
	m.leftCoast();
	m.rightCoast();
}

void loop()
{
  motor m;
  
  float rfValue = 0;
  if(receiving(rfValue)){
    Serial.println(rfValue);
    digitalWrite(LED, HIGH);  
  }

  //0-127 right motor forward
  //128-256 right motor back
  //257-383 left motor forward
  //384-512 left motor back
  //513 right stop
  //514 left stop
  //515 right coast
  //516 left coast

  if (rfValue >= 0 && rfValue <= 127){ //0-127, right motor
    float driveFrequency = rfValue*2;
    m.rightForward(driveFrequency);
  }
  else if (rfValue >= 128 && rfValue <= 256){//128-256 left motor
    float driveFrequency = (rfValue - 128)*2;
    m.leftForward(driveFrequency);
  }
  else if (rfValue == 257)//right stop
    m.rightStop();
  else if (rfValue == 258)//258 left stop
    m.leftStop();
  else if (rfValue == 259) //259 right coast
    m.leftCoast();
  else if (rfValue == 260) //260 left coast
    m.leftCoast();
}
