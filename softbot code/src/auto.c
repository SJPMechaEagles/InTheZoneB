#pragma once
#include "main.h"
#include "advancedMovement.h"
#include "ports.h"

void autonomous() {
  //moveUntilObstacle();
  turnGyro(700, 60, gyro);
  setMotors(0,0);
}
