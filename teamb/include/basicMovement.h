#ifndef _BASICM_H_
#define _BASICM_H_
#include <API.h>
#include "ports.h"

void setSpeedLeft(int speedLeft);
void setSpeedRight(int speedRight);
void setMotors(int speedLeft, int speedRight);
void mobileLift(int speedLeft, int speedRight);
bool turningLeft();
bool turningRight();
bool turningLeftAndRight();
bool drivingThreshold();
struct controller_values getControllerValues();

struct controller_values {
  int stickLX;
  int stickLY;
  int stickRX;
  int stickRY;
};

#endif
