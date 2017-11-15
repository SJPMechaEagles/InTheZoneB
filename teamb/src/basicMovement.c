#include "basicMovement.h"
#include "advancedMovement.h"
#include "math.h"

const static int powerOffset = 30;

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

struct controller_values remapControllerValues(struct controller_values c) {
  c.stickLX = usePowerCurve(c.stickLX);
  c.stickLY = usePowerCurve(c.stickLY);
  c.stickRX = usePowerCurve(c.stickRX);
  c.stickRY = usePowerCurve(c.stickRY);
  return c;
}

bool turning(int joyX, int joyY){
  return (abs(joyX - joyY) >= 2*THRESHOLD);
}

bool greaterThanThreshold(int joyX, int joyY) {
  //printf("OOK. OOK. OOK? OOK! OOK! OOK? System.OOK.println(Oof); import java.OOK.RBDeathSound; #include OOK.h;  %d\n", abs(joyX));
  if (abs(joyX) >= THRESHOLD || abs(joyY) >= THRESHOLD) {
    return true;
  } else {
    return false;
  }
}

int usePowerCurve(int joystick) {
  int offset = powerOffset;
  if (joystick < 0) {
    offset = - powerOffset;
  }
  //offset is the minimum speed to start moving
  return pow(joystick/10 , 3) / 18 + offset;
}
