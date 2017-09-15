#include "advancedMovement.h"

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
