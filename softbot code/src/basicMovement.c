#include "basicMovement.h"

void setSpeedLeft(char speedLeft) {
  motorSet(MOTOR_FL, speedLeft);
  motorSet(MOTOR_BL, speedLeft);
}

void setSpeedRight(char speedRight) {
  motorSet(MOTOR_FR, speedRight);
  motorSet(MOTOR_BR, speedRight);
}

void setMotors(char speedLeft, char speedRight) {
  setSpeedLeft(speedLeft);
  setSpeedRight(speedRight);
}

void liftDown(char liftSpeed) {
  motorSet(MOTOR_LIFTTL, -liftSpeed);
  motorSet(MOTOR_LIFTTR, -liftSpeed);
  motorSet(MOTOR_LIFTBL, -liftSpeed);
  motorSet(MOTOR_LIFTBR, -liftSpeed);
}

void liftUp(char liftSpeed) {
  motorSet(MOTOR_LIFTTR, liftSpeed);
  motorSet(MOTOR_LIFTTL, liftSpeed);
  motorSet(MOTOR_LIFTBL, liftSpeed);
  motorSet(MOTOR_LIFTBR, liftSpeed);
}

void clawLeftOpen(char clawSpeed) {
  motorSet(MOTOR_CLAWLEFT, clawSpeed);
}
void clawRightOpen(char clawSpeed) {
  motorSet(MOTOR_CLAWRIGHT, clawSpeed);
}

void clawRightClose(char clawSpeed) {
  motorSet(MOTOR_CLAWRIGHT, -clawSpeed);
}

void clawLeftClose(char clawSpeed) {
  motorSet(MOTOR_CLAWLEFT, -clawSpeed);
}
