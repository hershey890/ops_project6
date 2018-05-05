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
  Serial.println("transmitter setup ran");
	imu_setup();
  Serial.println("imu setup ran");
}

void loop()
{
	imu_loop();
  
  IMU_X *= 100;
  IMU_Y *= 100;
  float forward = map(IMU_Y, -100, 100, 10, 60);
  float scaleLR = map(IMU_X, -100, 100, -forward, forward); //add/sub from the forward to adjust the 
  //left/right values

  if (IMU_Y <= -10) {
    int transmitVal = (forward + scaleLR) * 100 + (forward - scaleLR);
    sending(transmitVal);
  }
  else if (IMU_Y > -10 && IMU_Y < 10) //stop code
    sending(3535);
  else if (IMU_Y >= 10) {
    int transmitVal = (forward - scaleLR) * 100 + (forward + scaleLR);
    sending(transmitVal);
  }

  printXYZ();
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
