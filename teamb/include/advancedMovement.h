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

int max(int a, int b);
void moveSteps(int steps, int speed);
void drive(int mode);
void mobileGoalLiftTest();
void mobileGoalLifterLoop(void * parameter);
void startLifterLoop();
void stopLifterLoop();
void gyroTurn(int degrees, Gyro gyro);
void autonomousTest(Gyro gyro);
void changeTurnSpeed();
#endif
