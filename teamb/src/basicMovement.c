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

void setMobileLift(int speed) {
  motorSet(MOTOR_MLL, speed);
  motorSet(MOTOR_MLR, speed);
}

void setLifter(int speed) {
  motorSet(MOTOR_LBR, speed);
  motorSet(MOTOR_LBL, speed);
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
