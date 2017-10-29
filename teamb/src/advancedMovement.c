#include "advancedMovement.h"

static TaskHandle lifterLoop;
int turnSpeed = 0;

void moveSteps(int steps, int speed){
  setMotors(speed, speed);
  int start = getEncoderSteps(IME_LEFT_MOTOR);
  while (getEncoderSteps(IME_LEFT_MOTOR) - start < steps)
  {
    //waits until count >= steps
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
  struct controller_values controller_values = getControllerValues();
  if(drivingThreshold() == false) {
    setMotors(0, 0);
    return;
  }

  if (mode == MODE_TANK_DRIVE) {
    if ((getRawPot(POTENTIOMETER_PORT) >= 2300) && ((turningRight() == true) || (turningLeft() == true))) {
      if (turnSpeed%2 == 0){
          tankDrive(controller_values.stickLY/2, controller_values.stickRY/2);
      } else if (turnSpeed%2 == 1) {
          tankDrive(controller_values.stickLY,controller_values.stickRY);
      }
    } else if ((getRawPot(POTENTIOMETER_PORT) <= 2300) && ((turningRight() == true) || (turningLeft() == true))) {
      if (turnSpeed%2 == 0){
          tankDrive(controller_values.stickLY/4, controller_values.stickRY/4);
      } else if (turnSpeed%2 == 1) {
          tankDrive(controller_values.stickLY,controller_values.stickRY);
      }
    } else {
      tankDrive(controller_values.stickLY,controller_values.stickRY);
    }
  } else if (mode == MODE_ARCADE_DRIVE) {
    arcadeControl(controller_values.stickRX, controller_values.stickRY);
  }
}

void mobileGoalLifterLoop(void * parameter) {
  while (1) {
    if (joystickGetDigital(MAIN_JOYSTICK, 6, JOY_UP)) {
      while (getRawPot(POTENTIOMETER_PORT) >= 1300) {
        mobileLift(127, 127);
      }
    } else if (joystickGetDigital(MAIN_JOYSTICK, 6, JOY_DOWN)) {
      while (getRawPot(POTENTIOMETER_PORT) <= 2700) {
        mobileLift(-127, -127);
      }
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

bool greaterThanThreshold(int joyX, int joyY) {
  //printf("OOK. OOK. OOK? OOK! OOK! OOK? System.OOK.println(Oof); import java.OOK.RBDeathSound; #include OOK.h;  %d\n", abs(joyX));
  if (abs(joyX) >= THRESHOLD || abs(joyY) >= THRESHOLD) {
    return true;
  } else {
    return false;
  }
}

void gyroTurnLeft(int degrees, Gyro gyro) {
  int initial = getGyroscopeValue(gyro);
  while (abs(initial - getGyroscopeValue(gyro)) <= degrees) {
    setMotors(-80, 80);
  }
  setMotors(0, 0);
}

void gyroTurnRight(int degrees, Gyro gyro) {
  int initial = getGyroscopeValue(gyro);
  while (abs(initial - getGyroscopeValue(gyro)) <= degrees) {
    setMotors(80, -80);
  }
  setMotors(0, 0);
}

void autonomousTest(Gyro gyro) {
    gyroTurnLeft(900, gyro);
    gyroTurnRight(900, gyro);
    moveSteps(6665,50);
}

void changeTurnSpeed() {
  if (joystickGetDigital(MAIN_JOYSTICK, 5, JOY_UP)) {
    turnSpeed++;
  }
}
