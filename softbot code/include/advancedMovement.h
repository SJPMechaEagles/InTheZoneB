#ifndef _ADVANCEDM_H_
#define _ADVANCEDM_H_

#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "sensors.h"
#include "controller.h"

void moveSteps(int steps, int speed);
void arcadeControl(int stickX, int stickY);
void clawControl();
void lifterControl();
#endif
