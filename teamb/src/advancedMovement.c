#include "advancedMovement.h"

const int THRESHOLD = 15;

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
  int stickLX = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_LEFT_X);
  int stickLY = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_LEFT_Y);
  int stickRX = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_X);
  int stickRY = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_Y);

  if(!(greaterThanThreshold(stickLX, stickLY) || greaterThanThreshold(stickRX, stickRY))) {
    setMotors(0, 0);
    return;
  }

  if (mode == MODE_TANK_DRIVE) {
    tankDrive(stickLY, stickRY);
  } else if (mode == MODE_ARCADE_DRIVE) {
    arcadeControl(stickRX, stickRY);
  }
}

bool greaterThanThreshold(int joyX, int joyY) {
  printf("%d\n", abs(joyX));
  if (abs(joyX) >= THRESHOLD || abs(joyY) >= THRESHOLD) {
    return true;
  } else {
    return false;
  }
}
