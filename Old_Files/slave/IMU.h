/* Natasha Sarkar
 * IMU.h
 * OPS 2018
 * Project: Wireless Space Team
 */

#ifndef IMU_H
#define IMU_H

#include <stdint.h>
#include "sensor_fusion.h"

const int CE = 14;
const int CS = 15;
const int CHANNEL = 16;
const int INT_STATUS = 58;
const int PWR_MGMT_1 = 107;
const int MPU_CONFIG = 26;
const int GYRO_CONFIG = 27;
const int ACCEL = 59;
const int GYRO = 67;
//RF24 radio(CE, CS);
//Controller controller(&radio, CHANNEL, false);

void imu_setup();
void imu_loop();

#endif
