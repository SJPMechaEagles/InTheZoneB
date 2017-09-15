#ifndef _BASICM_H_
#define _BASICM_H_
#include <API.h>
#include "ports.h"

void setSpeedLeft(char speedLeft);
void setSpeedRight(char speedRight);
void setMotors(char speedLeft, char speedRight);
void liftDown(char liftSpeed);
void liftUp(char liftSpeed);
void clawLeftOpen(char clawSpeed);
void clawRightOpen(char clawSpeed);
void clawRightClose(char clawSpeed);
void clawLeftClose(char clawSpeed);
#endif
