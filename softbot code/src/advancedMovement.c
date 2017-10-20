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
  //drive
  if (abs(stickX) + abs(stickY) > JOYSTICK_THRESHOLD){
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
  if(joystickGetDigital(MAIN_JOYSTICK, 7, JOY_LEFT)) {
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

void moveUntilObstacle() {
  while(1){
    if(getUltraSonicValue() >= 10){
      setMotors(50,50);
    } else {
      setMotors(0,0);
      break;
    }
  }
}

void turnGyro(int turnDegrees, int power, Gyro gyro) {
  int direction;
  if (turnDegrees >= 0) {
    direction = 1; //d = left
  } else {
    direction = -1; //d = right
  }

  int initialVal = getGyroscopeValue(gyro);
  for (int i = 0; i <= 20; ++ i) {
    int difference = abs(getGyroscopeValue(gyro) - initialVal);
    if(difference < turnDegrees) {
      //turn with power and the rotation
      setMotors(-power * direction, -power * direction);
    } else {
      setMotors(0,0);
      break;
    }
    delay(60);
  }
}
