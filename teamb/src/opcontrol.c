#include "stdhead.h"
#include <API.h>

void operatorControl() {
	while (1) {
		int stickx = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_X);
		int sticky = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_Y);

		int left = sticky + stickx;
		int right = sticky - stickx;

		setSpeedRight(right);
		setSpeedLeft(left);

		delay(20);
		//y=2^ax a=0.55
	}
}
