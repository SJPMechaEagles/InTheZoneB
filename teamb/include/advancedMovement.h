#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "sensors.h"
#include "controller.h"

#define MODE_TANK_DRIVE 0
#define MODE_ARCADE_DRIVE 1
#define MODE_DUAL_ARCADE_DRIVE 2

void moveSteps(int steps, int speed);
void arcadeControl(int stickX, int stickY);
void tankDrive(int leftSpeed, int rightSpeed);
void drive(int mode);
void mobileGoalLift();
bool greaterThanThreshold(int joyX, int joyY);
