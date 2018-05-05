#include "sensor_fusion.h"
#include "IMU.h"
#include "transmitter.h"

extern float IMU_X;
extern float IMU_Y;
extern float IMU_Z;

float x_calib = 0;
float y_calib = 0;
float z_calib = 0;

int getLeft(int val) {
  return (val/256);
}

int getRight(int val) {
  return (val % 256);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  transmitter_setup();
  imu_setup();
  float x_sum = 0;
  float y_sum = 0;
  float z_sum = 0;
  for(int i = 0; i < 100; i++) {
    imu_loop();
    x_sum += IMU_X;
    y_sum += IMU_Y;
    z_sum += IMU_Z;
  }
  x_calib = x_sum/100;
  y_calib = y_sum/100;
  z_calib = z_sum/100;
}
float abc = 0;
void loop() {
  imu_loop();
  /*Serial.print("X ");
  Serial.print((int)((IMU_X - x_calib) * 100));
  Serial.print(" ");
  Serial.print("Y ");
  Serial.print((int)((IMU_Y - y_calib) * 100));
  Serial.print(" ");*/
  int x = (int)((IMU_X - x_calib) * 100);
  int y = (int)((IMU_Y - y_calib) * 100);
  int sending_data = 0;
  int left_move = 128;
  int right_move = 128;
  if(x > 0) {
    if(x < 10) {
      left_move = 128;
    } else if(x >= 90) {
      left_move = 255;
    } else {
      left_move = floor((x-10)*1.6) + 128;
    }
  } else {
    x = x * -1;
    if(x < 10) {
      right_move = 128;
    } else if(x >= 90) {
      right_move = 255;
    } else {
      right_move = floor((x-10)*1.6) + 128;
    }
  }
  int remaining = 256 - max(left_move, right_move);
  int power = 0;
  if(y > 10 && y < 90) {
    power = floor(remaining * (y-10)/80.0);
  } else if (y > -90 && y < -10) {
    power = floor(remaining * (y+10)/80.0);
  } else if (y > 90) {
    power = remaining;
  } else if (y < -90) {
    power = remaining * -1;
  }
  left_move -= power;
  right_move -= power;
  sending_data = left_move * 256;
  sending_data += right_move;
  /*Serial.print("Left: ");
  Serial.print((getLeft((int)sending_data)));
  Serial.print(" ");
  Serial.print("Right: ");
  Serial.println((getRight((int)sending_data)));*/
  Serial.println(sizeof(int));
}
  
