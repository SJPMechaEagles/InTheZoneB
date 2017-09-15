#include "advancedMovement.h"

const int JOYSTICK_THRESHOLD = 15;

void moveSteps(int steps, int speed) {
  //uses an integrated encoder to move for a certain number of steps.
  setMotors(speed, speed);
  int start = getEncoderSteps(IME_LEFT_MOTOR);
  while (getEncoderSteps(IME_LEFT_MOTOR) - start < steps)
  {
    //waits until count >= steps
  }
  setMotors(0, 0);
}

void arcadeControl(int stickX, int stickY) {
  //
  if (abs(stickX) > JOYSTICK_THRESHOLD || abs(stickY) > JOYSTICK_THRESHOLD){
    int left = stickY + stickX;
    int right = stickY - stickX;

    setSpeedLeft(left);
    setSpeedRight(right);
  } else {
    setMotors(0, 0);
  }
}

void clawControl() {
	//claw
	if(joystickGetDigital(MAIN_JOYSTICK, 5, JOY_UP)) {
		clawLeftOpen(50);
	} else if(joystickGetDigital(MAIN_JOYSTICK, 6, JOY_UP)){
		clawRightOpen(50);
	} else if(joystickGetDigital(MAIN_JOYSTICK, 5, JOY_DOWN)) {
		clawLeftClose(50);
	} else if(joystickGetDigital(MAIN_JOYSTICK, 6, JOY_DOWN)) {
		clawRightClose(50);
	} else if(joystickGetDigital(MAIN_JOYSTICK, 7, JOY_LEFT)) {
		clawRightOpen(50);
		clawLeftOpen(50);
	} else if(joystickGetDigital(MAIN_JOYSTICK, 7, JOY_RIGHT)) {
		clawRightClose(50);
		clawLeftClose(50);
	} else {
		clawRightOpen(0);
		clawLeftOpen(0);
	}
}

void lifterControl() {
	//lifter
	if (joystickGetDigital(MAIN_JOYSTICK, 7, JOY_UP)) {
		liftUp(50);
	} else if (joystickGetDigital(MAIN_JOYSTICK, 7, JOY_DOWN)){
		liftDown(50);
	} else {
		liftDown(0);
	}
}
