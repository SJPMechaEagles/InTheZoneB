#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "advancedMovement.h"
#include "sensors.h"
#include "controller.h"

extern Gyro gyro;


void operatorControl()
{
	//Mode 0: Arcade Control
	//Mode 1: Tank Drive
	//Mode 2: Autonomous Test
	int mode = 2;

	if (mode == 0) {
		startLifterLoop();
		while (1) {
			drive(MODE_ARCADE_DRIVE);
			changeDriveSpeed();
			delay(60);
		}
		stopLifterLoop();
	} else if(mode == 1) {
		startLifterLoop();
		while (1) {
			drive(MODE_TANK_DRIVE);
			changeDriveSpeed();
			delay(60);
		}
		stopLifterLoop();
	} else if(mode == 2) {
		while(1) {
			int steps = 0;
			steps = getEncoderSteps(IME_LEFT_MOTOR);
			printf("Encoder step: %d.\n", steps);
			printf("Potentiometer  reading: %d\n", analogRead(POTENTIOMETER_PORT));
			printf("Gyroscope heading: %d.\n", gyroGet(gyro));
			if(joystickGetDigital(MAIN_JOYSTICK, 7, JOY_RIGHT)) {
				autonomousTest(gyro);
			}
			delay(200);
		}
	}
}
