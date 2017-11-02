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
			drive(MODE_ARCADE_DRIVE);
			changeTurnSpeed();
			printf("Potentiometer reading: %d\n", analogRead(POTENTIOMETER_PORT));
			printf("Gyroscope heading: %d.\n", gyroGet(gyro));
			int steps = 0;
			steps = getEncoderSteps(IME_LEFT_MOTOR);
			printf("Encoder step: %d.\n", steps);
			delay(100);
			}
		}
	stopLifterLoop();
}
