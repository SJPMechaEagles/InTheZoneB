#include "basicMovement.h"

void setSpeedLeft(int speedLeft){
  motorSet(MOTOR_FL, speedLeft);
  motorSet(MOTOR_BL, speedLeft);
}

void setSpeedRight(int speedRight){
  motorSet(MOTOR_FR, speedRight);
  motorSet(MOTOR_BR, speedRight);
}

void setMotors(int speedLeft, int speedRight){
  setSpeedLeft(speedLeft);
  setSpeedRight(speedRight);
}
