/* Natasha Sarkar
 * IMU.cpp
 * OPS 2018
 * Project: Wireless Space Team
 */

#include "IMU.h"
#include <Wire.h>
//#include <Wire\src\Wire.h>
#include "sensor_fusion.h"

unsigned long systime;

float IMU_X;
float IMU_Y;
float IMU_Z;

const int16_t x_offset = -91;
const int16_t y_offset = -74;
const int16_t z_offset = -65;

int32_t x = 0;
int32_t y = 0;
int32_t z = 0;

unsigned int ctr = 0;
	
const float GYRO_LSB = 16.4;
struct vector normal = {0, 0, 1};
struct vector filtered = {0, 0, 1};
	

void imu_setup() {
	Wire.begin();
	uint8_t config = 0;
	writeReg(PWR_MGMT_1, &config, sizeof(config));
	config = 0;
	writeReg(MPU_CONFIG, &config, sizeof(config));
	config = (0x3 << 3);
	writeReg(GYRO_CONFIG, &config, sizeof(config));
	readReg(GYRO_CONFIG, &config, sizeof(config));
	systime = millis();
	bool tuning_mode = false;
}

void imu_loop() {
  ctr++;
  uint8_t int_status;
  readReg(INT_STATUS, &int_status, 1);
  if(int_status & 1) {
    uint8_t raw_accel[6];
    uint8_t raw_gyro[6];
    readReg(ACCEL, raw_accel, sizeof(raw_accel));
    readReg(GYRO, raw_gyro, sizeof(raw_gyro));
    unsigned long temp = millis();
    float timediff = (temp - systime) / 1000.0;
    systime = temp;
    struct vector accel = {
      ((raw_accel[0] << 8) | raw_accel[1]),
      ((raw_accel[2] << 8) | raw_accel[3]),
      ((raw_accel[4] << 8) | raw_accel[5]),
    };

    vector_normalize(&accel, &accel);
    struct vector gyro = {
      ((raw_gyro[0] << 8) | raw_gyro[1]) - x_offset,
      ((raw_gyro[2] << 8) | raw_gyro[3]) - y_offset,
      ((raw_gyro[4] << 8) | raw_gyro[5]) - z_offset,
    };

    struct vector unit;
    float magnitude = vector_normalize(&gyro, &unit);
    float angle = magnitude * timediff * PI / 180 / GYRO_LSB;
    struct quaternion q;
    quaternion_create(&unit, -angle, &q);
    quaternion_rotate(&normal, &q, &normal);
    const float alpha = 0.9;
    quaternion_rotate(&filtered, &q, &filtered);
    vector_multiply(&filtered, alpha, &filtered);
    struct vector scaledA;
    vector_multiply(&accel, 1-alpha, &scaledA);
    vector_add(&filtered, &scaledA, &filtered);
    vector_normalize(&filtered, &filtered);

    IMU_X = filtered.x;
    IMU_Y = filtered.y;
    IMU_Z = filtered.z;
  }
}
