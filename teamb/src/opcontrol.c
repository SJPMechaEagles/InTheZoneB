#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "advancedMovement.h"
#include "sensors.h"
#include "controller.h"


void operatorControl()
{
	int mode = 3;
	if (mode == 0) {
		while (1) {
			int stickX = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_X);
			int stickY = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_Y);
			arcadeControl(stickX, stickY);
			delay(20);
		}
	} else if (mode == 1) {
		printf("Start monitoring motor encoders.");
		int steps = 0;
		while (1)
		{
			steps = getEncoderSteps(IME_LEFT_MOTOR);
			printf("Encoder step: %d.\n", steps);
			delay(200);
		}
	} else if (mode == 2) {
		int heading;
		delay(1000);
		printf("Starting gyroscope.");
		while (1) {
			heading = getGyroscopeValue(gyro);
			printf("Gyroscope heading: %d.\n", heading);
			delay(200);
		}
	} else if(mode == 3) {
		startLifterLoop();
		while (1) {
			drive(MODE_TANK_DRIVE);
			if(joystickGetDigital(MAIN_JOYSTICK, 8, JOY_UP)) {
				autonomousTest(gyro);
			}
			printf("Potentiometer reading: %d\n", analogRead(POTENTIOMETER_PORT));
			printf("Gyroscope heading: %d.\n", getGyroscopeValue(gyro));
			delay(200);
		}
		stopLifterLoop();
		// Test mode
	}
}
