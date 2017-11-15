#ifndef _BASICM_H_
#define _BASICM_H_
#include <API.h>
#include "ports.h"

#define THRESHOLD 15

void setSpeedLeft(int speedLeft);
void setSpeedRight(int speedRight);
void setMotors(int speedLeft, int speedRight);
void mobileLift(int speedLeft, int speedRight);
bool turning(int joyX, int joyY);
bool greaterThanThreshold(int joyX, int joyY);
int usePowerCurve(int input);
struct controller_values getControllerValues();
struct controller_values remapControllerValues(struct controller_values vals);

struct controller_values {
  int stickLX;
  int stickLY;
  int stickRX;
  int stickRY;
};

#endif
