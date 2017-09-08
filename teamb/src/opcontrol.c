#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "advancedMovement.h"
#include "sensors.h"
#include "controller.h"


void operatorControl() {
	int mode = 1;
	if (mode == 0) {
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
	} else if (mode == 1) {
		printf("Start monitoring motor encoders.");
		int steps = 0;
		while (1) {
			steps = getEncoderSteps(IME_LEFT_MOTOR);
			printf("Encoder step: %d.\n", steps);
			delay(200);
		}
	} else if (mode == 2) {
		while(1) {
			if(joystickGetDigital(MAIN_JOYSTICK, 7, JOY_UP)) {
	      moveSteps(500, 80);
    	}
		}
	}
}
