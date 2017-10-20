#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "advancedMovement.h"
#include "sensors.h"
#include "controller.h"

void autonomous();

void autonomousControl(unsigned char joystick, unsigned char buttonGroup, unsigned char button) {
  if(joystickGetDigital(joystick, buttonGroup, button)) {
    autonomous();
  }
}

void operatorControl() {
	while (1) {
		//driving
		int stickX = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_X);
		int stickY = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_Y);
		arcadeControl(stickY, stickX);
		lifterControl();
		clawControl();
		autonomousControl(MAIN_JOYSTICK, 8, JOY_RIGHT);
		int gyroValue = getGyroscopeValue(gyro);
		printf("%d\n", gyroValue);
		delay(60);
	}
}
