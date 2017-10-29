#include "basicMovement.h"
#include "advancedMovement.h"

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

void mobileLift(int speedLeft, int speedRight) {
  motorSet(MOTOR_MLL, speedLeft);
  motorSet(MOTOR_MLR, speedRight);
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

bool turningRight(){
  struct controller_values controller_values = getControllerValues();
  if(abs(controller_values.stickLY) >= THRESHOLD && abs(controller_values.stickRY) <= THRESHOLD) {
    return true;
  } else {
    return false;
  }
}

bool turningLeft(){
  struct controller_values controller_values = getControllerValues();
  if(abs(controller_values.stickRY) >= THRESHOLD && abs(controller_values.stickLY) <= THRESHOLD){
    return true;
  } else {
    return false;
  }
}
bool turningLeftAndRight(){
  struct controller_values controller_values = getControllerValues();
  if(abs(controller_values.stickRY) >= THRESHOLD && abs(controller_values.stickLY) >= THRESHOLD){
    return true;
  } else {
    return false;
  }
}

bool drivingThreshold() {
  struct controller_values controller_values = getControllerValues();
  if(greaterThanThreshold(controller_values.stickLX, controller_values.stickLY) || greaterThanThreshold(controller_values.stickRX, controller_values.stickRY)){
    return true;
  } else {
    return false;
  }
}
