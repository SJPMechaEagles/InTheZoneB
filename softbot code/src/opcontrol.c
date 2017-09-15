#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "advancedMovement.h"
#include "sensors.h"
#include "controller.h"


void operatorControl() {
	while (1) {
		//driving
		int stickX = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_X);
		int stickY = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_Y);
		arcadeControl(stickY, stickX);
		lifterControl();
		clawControl();
		delay(20);
	}
}
