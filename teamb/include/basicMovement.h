#ifndef _BASICM_H_
#define _BASICM_H_
#include <API.h>
#include "ports.h"

void setSpeedLeft(int speedLeft);
void setSpeedRight(int speedRight);
void setMotors(int speedLeft, int speedRight);
void mobileLift(int speedLeft, int speedRight);

#endif
