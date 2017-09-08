#include "advancedMovement.h"

void moveSteps(int steps, int speed){
  setMotors(speed, speed);
  while (getEncoderSteps(IME_LEFT_MOTOR) < steps){

  }
  setMotors(0, 0);
}
