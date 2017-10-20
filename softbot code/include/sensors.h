#ifndef _SENSORS_H_
#define _SENSORS_H_
#include <API.h>
#include "ports.h"

int getEncoderSteps(int side);
void resetEncoderSteps(int side);
int getGyroscopeValue(Gyro gyro);
void resetGyroscopeValue();

int getUltraSonicValue();
void initUltraSonic();
#endif
