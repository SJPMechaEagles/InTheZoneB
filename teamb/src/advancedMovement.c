#include "advancedMovement.h"

static TaskHandle mobileLifterTask;
static TaskHandle scissorLifterTask;
static TaskHandle clawLoopTask;
static int driveSpeedToggle = 0;
static double driveMultiplier = 0.333;
static bool mobileLifterIsRaised = true;


void moveSteps(int steps, int speed) {
  int start = getEncoderSteps(IME_LEFT_MOTOR);
  while (abs(getEncoderSteps(IME_LEFT_MOTOR) - start) < steps)
  {
    setMotors(speed, -speed);
  }
  setMotors(0, 0);
}

void raiseLifter() {
  while(getRawPot(LIFTER_POTENTIOMETER) >= 0) {
    setLifter(MAX_DRIVE_SPEED);
  }
}

void lowerLifter() {
  while(getRawPot(LIFTER_POTENTIOMETER) >= 0) {
    setLifter(-MAX_DRIVE_SPEED);
  }
}

void raiseMobileLift()
{
  while (getRawPot(MOBILE_POTENTIOMETER) >= 1300) {
    setMobileLift(MAX_DRIVE_SPEED);
  }
}

void lowerMobileLift()
{
  while (getRawPot(MOBILE_POTENTIOMETER) <= 2800) {
    setMobileLift(-MAX_DRIVE_SPEED);
  }
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
  if(!isGreaterThanThreshold(controller.stickLY, controller.stickLX) &&
    !isGreaterThanThreshold(controller.stickRY, controller.stickRX)) {
    setMotors(0, 0);
    return;
  }
  //controller = remapControllerValues(controller);

  if (mode == MODE_TANK_DRIVE) {
    if (driveSpeedToggle == 1) {
        tankDrive(controller.stickLY*driveMultiplier,
          controller.stickRY*driveMultiplier);
    } else {
      tankDrive(controller.stickLY,controller.stickRY);
    }
  } else if (mode == MODE_ARCADE_DRIVE) {
    arcadeControl(controller.stickRY, controller.stickRX);
  }
}

void changeDriveSpeed() {
  if (joystickGetDigital(MAIN_JOYSTICK, 5, JOY_UP)) {
    driveSpeedToggle++;
    driveSpeedToggle = driveSpeedToggle % 2;
    wait(150);
  }
}

//lifts the mobile goal intake with a potentiometer
void mobileGoalLifterLoop(void * parameter) {
  while (1) {
    if (joystickGetDigital(MAIN_JOYSTICK, 6, JOY_UP)) {
      raiseMobileLift();
      mobileLifterIsRaised = true;
      driveMultiplier = 0.667;
    } else if (joystickGetDigital(MAIN_JOYSTICK, 6, JOY_DOWN)) {
      lowerMobileLift();
      mobileLifterIsRaised = false;
      driveMultiplier = 0.333;
    } else {
      setMobileLift(0);
    }
    delay(30);
  }
}

//lifts the main lifter
void scissorLifterLoop(void * parameter) {
  while (1) {
    if (joystickGetDigital(MAIN_JOYSTICK, 5, JOY_UP)) {
      setLifter(127);
    } else if (joystickGetDigital(MAIN_JOYSTICK, 5, JOY_DOWN)) {
      setLifter(-30);
    } else {
      setLifter(0);
    }
    delay(30);
  }
  if(getRawPot(LIFTER_POTENTIOMETER) < 650) {
    setLifter(90);
  }
}

void clawLoop(void * parameter) {
  while(1) {
    if(joystickGetDigital(MAIN_JOYSTICK, 7, JOY_UP)) {
      setCone(127);
    } else if(joystickGetDigital(MAIN_JOYSTICK, 7, JOY_DOWN)) {
      setCone(-127);
    } else {
      setCone(0);
    }
    if(joystickGetDigital(MAIN_JOYSTICK, 8, JOY_UP)) {
      setClaw(127);
    } else if(joystickGetDigital(MAIN_JOYSTICK, 8, JOY_DOWN)) {
      setClaw(-127);
    } else {
      setClaw(0);
    }
  }
}

void startLoops() {
  mobileLifterTask = taskCreate(mobileGoalLifterLoop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  scissorLifterTask = taskCreate(scissorLifterLoop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  clawLoopTask = taskCreate(clawLoop,TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void stopLoops() {
  taskDelete(mobileLifterTask);
  taskDelete(scissorLifterTask);
  clawLoopTask = taskCreate(clawLoop,TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

int max(int a, int b) {
  if (a > b) {return a;}
  return b;
}

void gyroTurn(int degrees, Gyro gyro, int minSpeed) {
  int direction;
  //postive direction means turning right (posiive degrees)
  if (degrees > 0) {
    direction = 1;
  } else {
    direction = -1;
  }
  degrees -= degrees / 10;
  int initial = getGyroscopeValue(gyro);
  int slowDown = 0;
  //turn while the difference is less than the target degrees
  while (abs(initial - getGyroscopeValue(gyro)) <= abs(degrees)) {
    //if less than 38 degs to target, slow down
    int degsRemaining = abs(degrees) - abs(initial - getGyroscopeValue(gyro));
    if (degsRemaining <= 38) {
      //slow down by a fraction of degrees remaining;
      slowDown += degsRemaining / 3;
    }
    setMotors(max(minSpeed, GYRO_TURN_SPEED - slowDown) * direction,
      max(minSpeed, GYRO_TURN_SPEED - slowDown) * direction);
    wait(20);

  }
  setMotors(0, 0);
}

void autonomousTest(Gyro gyro) {
  //lowers lift at start
  lowerMobileLift();
  moveSteps(2320,50);
  raiseMobileLift();
  //there's resistence - 170 deg intended
  gyroTurn(-183, gyro, GYRO_TURN_SPEED_MIN_FAST);
  moveSteps(2200,127);
  //slow down
  moveSteps(400,70);
  moveSteps(300,45);
  gyroTurn(-53, gyro, GYRO_TURN_SPEED_MIN_FAST);
  //run at the scoring zone
  moveSteps(1200,127);
  //get the mobile goal out and back out
  lowerMobileLift();
  moveSteps(200,-127);
  //move the lifter out of the way
  raiseMobileLift();
}
