#include "advancedMovement.h"

static TaskHandle lifterLoop;
static int driveSpeedToggle = 0;
static double driveMultiplier = 0.333;
static bool lifterIsRaised = true;


void moveSteps(int steps, int speed) {
  int start = getEncoderSteps(IME_LEFT_MOTOR);
  while (abs(getEncoderSteps(IME_LEFT_MOTOR) - start) < steps)
  {
    setMotors(speed, -speed);
  }
  setMotors(0, 0);
}

void raiseMobileLift()
{
  while (getRawPot(POTENTIOMETER_PORT) >= 1350) {
    setMobileLift(MAX_DRIVE_SPEED);
  }
}
void lowerMobileLift()
{
  while (getRawPot(POTENTIOMETER_PORT) <= 2550) {
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

void mobileGoalLifterLoop(void * parameter) {
  while (1) {
    if (joystickGetDigital(MAIN_JOYSTICK, 6, JOY_UP)) {
      while (getRawPot(POTENTIOMETER_PORT) >= 1350) {
        setMobileLift(127);
      }
      lifterIsRaised = true;
      driveMultiplier = 0.667;
    } else if (joystickGetDigital(MAIN_JOYSTICK, 6, JOY_DOWN)) {
      while (getRawPot(POTENTIOMETER_PORT) <= 2550) {
        setMobileLift(-127);
      }
      lifterIsRaised = false;
      driveMultiplier = 0.333;
    } else {
      setMobileLift(0);
    }
    delay(20);
  }
}

void startLifterLoop() {
  lifterLoop = taskCreate(mobileGoalLifterLoop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void stopLifterLoop() {
  taskDelete(lifterLoop);
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
  /*
  New autonomous: turn less after the robot acquires the mobile goal, go away
  from the goal, then go straight at the 20-point zone. (0 degree angle of incidence)
  */
  moveSteps(2350,50);
  //raises lifter
  raiseMobileLift();
  //there's resistence
  gyroTurn(193, gyro, GYRO_TURN_SPEED_MIN_FAST);
  moveSteps(3400,127);
  //get the goal out
  lowerMobileLift();
  moveSteps(200,-127);
  //move the lifter out of the way
  raiseMobileLift();
}
