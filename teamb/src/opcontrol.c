#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "advancedMovement.h"
#include "sensors.h"
#include "controller.h"

extern Gyro gyro;


void operatorControl()
{
	//Mode 0: Tank Drive
	//Mode 1: Testing
	int mode = 0;


	if(mode == 0) {
		startLoops();
		while (1) {
			/*int steps = 0;
			steps = getEncoderSteps(IME_RIGHT_MOTOR);
			printf("Encoder step: %d.\n", steps);*/
			//printf("Mobile potentiometer  reading: %d\n", analogRead(MOBILE_POTENTIOMETER));
			//printf("Gyroscope heading: %d.\n", gyroGet(gyro));
			drive();
			delay(200);
		}
		stopLoops();
	} else if(mode == 1) {
	}
}
