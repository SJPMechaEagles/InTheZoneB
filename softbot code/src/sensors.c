#include "sensors.h"
Ultrasonic sonar;
Gyro gyro;

int getUltraSonicValue() {
  //int distance = ultrasonicGet(sonar);
  return ultrasonicGet(sonar);
}

void initUltraSonic() {
  sonar = ultrasonicInit(SONAR_PORT_ORANGE, SONAR_PORT_YELLOW);
}

int getGyroscopeValue(Gyro gyro) {
  return gyroGet(gyro);
}

void resetGyroscopeValue() {
  gyroReset(gyro);
}
