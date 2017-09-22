#include "sensors.h"

int getEncoderSteps(int side) {
    // Get IME tick count in the "counts" variable
    // (conversion to rotations varies depending on the motor type in use)
    int counts = 0;
    // Or if #define was used:
    imeGet(side, &counts);
    return counts;
}

void resetEncoderSteps(int side) {
  // Reset IME to zero
  imeReset(side);
}

int getGyroscopeValue(Gyro gyro) {
  return gyroGet(gyro);
}

void resetGyroscopeValue(Gyro gyro) {
  gyroReset(gyro);
}

unsigned int get_potentiometer_position(const unsigned char port) {
  unsigned int potValue = analogRead(port);
  return (250.0 / 4096.0) * potValue;
}
