#ifndef _SENSORS_H_
#define _SENSORS_H_
#include <API.h>
#include "ports.h"

int getEncoderSteps(int side);
void resetEncoderSteps(int side);
int getGyroscopeValue(Gyro gyro);
void resetGyroscopeValue(Gyro gyro);
unsigned int get_potentiometer_position(const unsigned char port);

#endif
