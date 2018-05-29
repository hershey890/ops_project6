#include "sensor_fusion.h"
#include "IMU.h"
#include "transmitter.h"

extern float IMU_X;
extern float IMU_Y;
extern float IMU_Z;

void printXYZ();

void setup()
{
	Serial.begin(9600);
  transmitter_setup();
	imu_setup();
}



void loop()
{
	imu_loop();
  printXYZ();
  
  IMU_X *= 100; //forward orientation
  IMU_Y *= 100; //left/right orientation
  
  float forward = map(IMU_Y, -100, 100, 10, 60);
  //the value that is being transmitted is in four digits _ _ _ _
  //the first two digits correspond to the left motor power, second two to the right motor power
  //10-35 (not incl 35) move forward
    //10 max forward, 34, min forward
  //3535 stop
  //second two digits: 36-60 move backward
    //36, min backward, 60 max backward
  float scaleLR = map(IMU_X, -100, 100, -forward, forward); //add/subtract from the forward value to adjust the left/right values

  if (IMU_Y <= -10) { //forward
    float transmitVal = (forward + scaleLR) * 100 + (forward - scaleLR);
    //IMU_X - negative -> turn left -> decrease motor right, increase motor left
       //scaleLR is negative -> first two digits decreased, second two digits increased
    //IMU_X - positive -> turn right -> increase motor right, decrease motor left
      //scaleLR is positive, -> first two digits increased, second two digits increased
    //Serial.println(transmitVal);
    sending(transmitVal);
  }
  //else if (IMU_Y > -15 && IMU_Y < 15){ //stop
  else if (IMU_Y > -15 && IMU_Y < 15 && IMU_X > -15 && IMU_X < 15){ //stop
    //Serial.println(3535);
    sending(3535);
  }
  else if (IMU_Y > -15 && IMU_Y < 15) {// && IMU_X < -15 || IMU_X > 15) { //rotating in place
    float transmitVal = (35 + IMU_X * .25) * 100 + (35 - IMU_X * .25);
    sending(transmitVal);
  }
  else if (IMU_Y >= 10) { //backward
    float transmitVal = (forward - scaleLR) * 100 + (forward + scaleLR);
    //Serial.println(transmitVal);
    sending(transmitVal);
  }
}



void printXYZ() {
	Serial.print("X ");
	Serial.print((int)(IMU_X * 100));
	Serial.print(" ");
	Serial.print("Y ");
	Serial.print((int)(IMU_Y * 100));
	Serial.print(" ");
	Serial.print("Z ");
	Serial.println((int)(IMU_Z * 100));
}
