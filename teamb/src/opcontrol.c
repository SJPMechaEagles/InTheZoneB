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
	//Mode 3: Lifter Test
	int mode = 1;


	if (mode == 0) {
		startLoops();
		while (1) {
			drive(MODE_ARCADE_DRIVE);
			changeDriveSpeed();
			delay(60);
		}
		stopLoops();
	} else if(mode == 1) {
		startLoops();
		while (1) {
			/*int steps = 0;
			steps = getEncoderSteps(IME_RIGHT_MOTOR);
			printf("Encoder step: %d.\n", steps);
			printf("Mobile potentiometer  reading: %d\n", analogRead(MOBILE_POTENTIOMETER));
			printf("Claw potentiometer  reading: %d\n", analogRead(CLAW_POTENTIOMETER));*/
			printf("Lifter potentiometer  reading: %d\n", analogRead(LIFTER_POTENTIOMETER));
			//printf("Gyroscope heading: %d.\n", gyroGet(gyro));
			drive(MODE_TANK_DRIVE);
			if(joystickGetDigital(MAIN_JOYSTICK, 7, JOY_RIGHT)) {
				autonomousTest(gyro);
			}
			changeDriveSpeed();
			delay(100);
		}
		stopLoops();
	} else if(mode == 2) {
			while(1) {
				int steps = 0;
				steps = getEncoderSteps(IME_LEFT_MOTOR);
				printf("Encoder step: %d.\n", steps);
				printf("Mobile potentiometer  reading: %d\n", analogRead(MOBILE_POTENTIOMETER));
				printf("Claw potentiometer  reading: %d\n", analogRead(CLAW_POTENTIOMETER));
				printf("Lifter potentiometer  reading: %d\n", analogRead(LIFTER_POTENTIOMETER));
				printf("Gyroscope heading: %d.\n", gyroGet(gyro));
				if(joystickGetDigital(MAIN_JOYSTICK, 7, JOY_RIGHT)) {
					autonomousTest(gyro);
				}
				delay(200);
			}
	} else if(mode == 3) {
			while(1) {
				if(joystickGetDigital(MAIN_JOYSTICK, 8, JOY_UP)) {
					setLifter(127);
				} else if(joystickGetDigital(MAIN_JOYSTICK, 8, JOY_DOWN)) {
					setLifter(-127);
				} else {
					setLifter(0);
				}
				delay(300);
			}
	}
}
