#include "advancedMovement.h"

static TaskHandle mobileLifterTask;
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

/*void raiseLifter() {
  while(getRawPot(LIFTER_POTENTIOMETER_R) >= 0) {
    setLifter(MAX_DRIVE_SPEED);
  }
}

void lowerLifter() {
  while(getRawPot(LIFTER_POTENTIOMETER_R) >= 0) {
    setLifter(-MAX_DRIVE_SPEED);
  }
} */

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

void tankDrive(int speedLeft, int speedRight) {
  setMotors(-speedLeft, speedRight);
}

void drive() {
  struct controller_values controller = getControllerValues();
  if(!isGreaterThanThreshold(controller.stickLY, controller.stickLX) &&
    !isGreaterThanThreshold(controller.stickRY, controller.stickRX)) {
    setMotors(0, 0);
    return;
  }
  //controller = remapControllerValues(controller);

  tankDrive(controller.stickLY,controller.stickRY);
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

void startLoops() {
  mobileLifterTask = taskCreate(mobileGoalLifterLoop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void stopLoops() {
  taskDelete(mobileLifterTask);
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
}
