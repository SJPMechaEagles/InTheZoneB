#include "basicMovement.h"


void setSpeedLeft(int speedLeft) {
  motorSet(MOTOR_L, speedLeft);
}

void setSpeedRight(int speedRight) {
  motorSet(MOTOR_R, speedRight);
}

void setMotors(int speedLeft, int speedRight) {
  setSpeedLeft(speedLeft);
  setSpeedRight(speedRight);
}

void setMobileLift(int speed) {
  motorSet(MOTOR_MLL, speed);
  motorSet(MOTOR_MLR, speed);
}

void setCone(int speed) {
  motorSet(MOTOR_CLAW, speed);
}

void setClaw(int speed) {
  motorSet(MOTOR_CL, speed);
}

void setLifter(int speed) {
  //sets scissor lifter speed, right side is mirrored
  //left side is slower, so reduce the speed on the right side
  motorSet(MOTOR_LFL, speed);
  motorSet(MOTOR_LBL, speed);
  motorSet(MOTOR_LFR, speed);
  motorSet(MOTOR_LBR, speed);
}

void setLifterSide(bool leftSide, int speed) {
  if (leftSide) {
    motorSet(MOTOR_LFL, speed);
    motorSet(MOTOR_LBL, speed);
  } else {
    motorSet(MOTOR_LFR, speed);
    motorSet(MOTOR_LBR, speed);
  }
}

bool isGreaterThanThreshold(int joyX, int joyY) {
  if (abs(joyX) >= JOYSTICK_THRESHOLD || abs(joyY) >= JOYSTICK_THRESHOLD) {
    return true;
  } else {
    return false;
  }
}

struct controller_values getControllerValues() {
  int stickLX = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_LEFT_X);
  int stickLY = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_LEFT_Y);
  int stickRX = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_X);
  int stickRY = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_Y);
  struct controller_values vals;
  vals.stickLX = stickLX;
  vals.stickLY = stickLY;
  vals.stickRX = stickRX;
  vals.stickRY = stickRY;
  return vals;
}

int usePowerCurve(int joystick) {
  int offset = FRICTION_THRESHOLD;
  if (joystick < 0) {
    offset = -FRICTION_THRESHOLD;
  }
  //offset is the minimum speed to start moving
  //
  return pow(joystick/10 , 3) / 18 + offset;
}

struct controller_values remapControllerValues(struct controller_values vals) {
  vals.stickLX = usePowerCurve(vals.stickLX);
  vals.stickLY = usePowerCurve(vals.stickLY);
  vals.stickRX = usePowerCurve(vals.stickRX);
  vals.stickRY = usePowerCurve(vals.stickRY);
  return vals;
}
