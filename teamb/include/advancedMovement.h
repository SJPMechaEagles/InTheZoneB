#ifndef _ADVANCED_MOVEMENT_H_
#define _ADVANCED_MOVEMENT_H_

#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "sensors.h"
#include "controller.h"
#include "math.h"

#define MAX_DRIVE_SPEED 60
#define GYRO_TURN_SPEED 60
#define GYRO_TURN_SPEED_MIN 28
#define GYRO_TURN_SPEED_MIN_FAST 40


//Moves the robot a set distance at a set speed
void moveSteps(int steps, int speed);
void raiseMobileLift();
void lowerMobileLift();

//Main drive code
void drive();

//Creates a constant loop for the mobile goal lifter so that the user
//can turn and lift at the same time; Also changes the slower turn speed
//based on the state of the lifter
void mobileGoalLifterLoop(void * parameter);
//Begins the loops
void startLoops();
//Ends the loops
void stopLoops();

//Returns the bigger integer of a and b
int max(int a, int b);
//Turns the robot a set number of degrees at the designated speed, slowing
//down the robot when it approaches the designated angle for increased accuracy
void gyroTurn(int degrees, Gyro gyro, int minSpeed);

//Autonomous code, for testing and for match use
void autonomousTest(Gyro gyro);

#endif
