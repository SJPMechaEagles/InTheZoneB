#include "advancedMovement.h"

static TaskHandle lifterLoop;
static int turnSpeedToggle = 0;
static double turningMultiplier = 0.333;
static bool lifterIsRaised = true;
static int gyroTurnSpeed = 45;

void moveSteps(int steps, int speed){
  int start = getEncoderSteps(IME_LEFT_MOTOR);
  while (abs(getEncoderSteps(IME_LEFT_MOTOR) - start) < steps)
  {
    //waits until count >= steps
    setMotors(speed, -speed);
  }
  setMotors(0, 0);
}

void arcadeControl(int stickX, int stickY)
{
  int left = stickY + stickX;
  int right = stickY - stickX;

  setSpeedRight(right);
  setSpeedLeft(left);
}

void tankDrive(int speedLeft, int speedRight) {
  setMotors(speedLeft, -speedRight);
}

void drive(int mode) {
  struct controller_values controller = getControllerValues();
  if( !greaterThanThreshold(controller.stickLY, controller.stickLX) &&
    !greaterThanThreshold(controller.stickRY, controller.stickRX) ) {
    setMotors(0, 0);
    return;
  }

  if (mode == MODE_TANK_DRIVE) {
    if ( turnSpeedToggle%2 == 1 && turning(controller.stickLY, controller.stickRY) ) {
        //slow down turning based on the state of the lifter
        //if it is enabled.
        tankDrive(controller.stickLY*turningMultiplier,
          controller.stickRY*turningMultiplier);
    } else {
      tankDrive(controller.stickLY,controller.stickRY);
    }
  } else if (mode == MODE_ARCADE_DRIVE) {
    arcadeControl(controller.stickRY, controller.stickRX);
  }
}

void mobileGoalLifterLoop(void * parameter) {
  while (1) {
    if (joystickGetDigital(MAIN_JOYSTICK, 6, JOY_UP)) {
      while (getRawPot(POTENTIOMETER_PORT) >= 1300) {
        mobileLift(127, 127);
      }
      lifterIsRaised = true;
      turningMultiplier = 0.667;
    } else if (joystickGetDigital(MAIN_JOYSTICK, 6, JOY_DOWN)) {
      while (getRawPot(POTENTIOMETER_PORT) <= 2700) {
        mobileLift(-127, -127);
      }
      lifterIsRaised = false;
      //turn solwer when lifter down
      turningMultiplier = 0.333;
    } else {
      mobileLift(0, 0);
    }
    delay(20);
  }
}

// Test method in case potentiometer messes up
void mobileGoalLiftTest() {
  if (joystickGetDigital(MAIN_JOYSTICK, 7, JOY_UP)) {
    mobileLift(100, 100);
  } else if (joystickGetDigital(MAIN_JOYSTICK, 7, JOY_DOWN)) {
    mobileLift(-100,-100);
  } else {
    mobileLift(0,0);
  }
}

void startLifterLoop() {
  lifterLoop = taskCreate(mobileGoalLifterLoop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void stopLifterLoop() {
  taskDelete(lifterLoop);
}

void gyroTurnLeft(int degrees, Gyro gyro) {
  //to stop early due to inertia
  if (degrees < 60) {
    degrees *= 0.53;
  } else {
    degrees -= 27;
  }

  int initial = getGyroscopeValue(gyro);
  while (abs(initial - getGyroscopeValue(gyro)) <= degrees) {
    setMotors(-gyroTurnSpeed, -gyroTurnSpeed);
  }
  setMotors(0, 0);
}

void gyroTurnRight(int degrees, Gyro gyro) {
  //to stop early due to inertia
  if (degrees < 70) {
    degrees *= 0.53;
  } else {
    degrees -= 27;
  }
  int initial = getGyroscopeValue(gyro);
  while (abs(initial - getGyroscopeValue(gyro)) <= degrees) {
    setMotors(gyroTurnSpeed, gyroTurnSpeed);
  }
  setMotors(0, 0);
}

void autonomousTest(Gyro gyro) {
  gyroTurnRight(45, gyro);
  gyroTurnLeft(90, gyro);
  moveSteps(1000, 50);
  gyroTurnLeft(67.5, gyro);
  moveSteps(1000, -50);
}

void changeTurnSpeed() {
  if (joystickGetDigital(MAIN_JOYSTICK, 5, JOY_UP)) {
    turnSpeedToggle++;
    wait(150);
  }
}
