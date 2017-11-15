#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "advancedMovement.h"
#include "sensors.h"
#include "controller.h"

extern Gyro gyro;

void operatorControl()
{
	int mode = 1;

	if (mode == 0) {
		while (1) {
			drive(MODE_ARCADE_DRIVE);
			delay(20);
		}
	} else if(mode == 1) {
		startLifterLoop();
		while (1) {
			drive(MODE_TANK_DRIVE);
			//turn 90 degs if button 8 L/R is pressed
			changeTurnSpeed();
			int steps = 0;
			steps = getEncoderSteps(IME_LEFT_MOTOR);
			printf("Encoder step: %d.\n", steps);
			printf("Potentiometer reading: %d\n", analogRead(POTENTIOMETER_PORT));
			printf("Gyroscope heading: %d.\n", gyroGet(gyro));
			delay(50);
		}
		stopLifterLoop();
	} else if(mode == 2) {
		while(1){
			printf("Gyroscope heading: %d.\n", gyroGet(gyro));
			if(joystickGetDigital(MAIN_JOYSTICK, 7, JOY_RIGHT)) {
				autonomousTest(gyro);
			}
			delay(200);
		}
	}
}
