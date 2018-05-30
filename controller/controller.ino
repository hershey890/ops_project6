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
  int total;
  IMU_X *= 100; //forward orientation
  IMU_Y *= 100; //left/right orientation
  if(abs(IMU_X) > abs(IMU_Y)) {
    if(abs(IMU_X) < 15) {
      sending(0000);
    } else if(IMU_X < 0) {
      int dir = 400;
      int power = map(abs(IMU_X), 15, 100, 0, 99);
      total = dir + power;
    } else {
      int dir = 200;
      int power = map(abs(IMU_X), 15, 100, 0, 99);
      total = dir + power;
    }
  } else {
    if(abs(IMU_Y) < 15) {
      sending(0000);
    } else if(IMU_Y < 0) {
      int dir = 100;
      int power = map(abs(IMU_Y), 15, 100, 0, 99);
      total = dir + power;
    } else {
      int dir = 300;
      int power = map(abs(IMU_Y), 15, 100, 0, 99);
      total = dir + power;
    }
  }
  sending(total);
  Serial.println(total);
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
