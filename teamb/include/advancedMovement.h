#ifndef _ADVANCED_MOVEMENT_H_
#define _ADVANCED_MOVEMENT_H_

#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "sensors.h"
#include "controller.h"

#define MODE_TANK_DRIVE 0
#define MODE_ARCADE_DRIVE 1
#define MODE_DUAL_ARCADE_DRIVE 2
#define THRESHOLD 15

void moveSteps(int steps, int speed);
void drive(int mode);
void mobileGoalLiftTest();
void mobileGoalLifterLoop(void * parameter);
void startLifterLoop();
void stopLifterLoop();
bool greaterThanThreshold(int joyX, int joyY);
void gyroTurnLeft(int degrees, Gyro gyro);
void gyroTurnRight(int degrees, Gyro gyro);
void autonomousTest(Gyro gyro);
void changeTurnSpeed();
#endif
