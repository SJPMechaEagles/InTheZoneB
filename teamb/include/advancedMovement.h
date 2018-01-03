#ifndef _ADVANCED_MOVEMENT_H_
#define _ADVANCED_MOVEMENT_H_

#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "sensors.h"
#include "controller.h"
#include "math.h"

#define MODE_TANK_DRIVE 0
#define MODE_ARCADE_DRIVE 1
#define MODE_DUAL_ARCADE_DRIVE 2
#define MAX_DRIVE_SPEED 127
#define GYRO_TURN_SPEED 60
#define GYRO_TURN_SPEED_MIN 28
#define GYRO_TURN_SPEED_MIN_FAST 40


//Moves the robot a set distance at a set speed
void moveSteps(int steps, int speed);
void raiseLifter();
void lowerLifter();
void raiseMobileLift();
void lowerMobileLift();
//Allows the user to change the drive speed of the robot between fast and slow
void changeDriveSpeed();
//Main drive code; Utilizes modes
void drive(int mode);

//Creates a constant loop for the mobile goal lifter so that the user
//can turn and lift at the same time; Also changes the slower turn speed
//based on the state of the lifter
void mobileGoalLifterLoop(void * parameter);
void scissorLifterLoop(void * parameter);
//Begins the loop
void startLifterLoop();
//Ends the loop
void stopLifterLoop();

//Returns the bigger integer of a and b
int max(int a, int b);
//Turns the robot a set number of degrees at the designated speed, slowing
//down the robot when it approaches the designated angle for increased accuracy
void gyroTurn(int degrees, Gyro gyro, int minSpeed);

//Autonomous code, for testing and for match use
void autonomousTest(Gyro gyro);

#endif
