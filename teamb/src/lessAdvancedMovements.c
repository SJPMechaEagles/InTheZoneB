#include "lessAdvancedMovement.h"
static bool LEFT = true;
static bool RIGHT = false;
static bool target_pot_high = 2000;
static bool target_pot_low = 200;

//moves the lifter slowly and prevents tilting
void safelyLowerScissorLift() {
  setLifter(-30);
  int lifterAngleLeft;
  int lifterAngleRight;

  int stoppedLeft = false;
  int stoppedRight = false;
  while (!stoppedLeft || !stoppedRight) {
    //stop one side once it has reached the target
    if (lifterAngleLeft <= target_pot_low) {
      setLifterSide(LEFT, 0);
      stoppedLeft = true;
    }
    if (lifterAngleRight <= target_pot_low) {
      setLifterSide(RIGHT, 0);
      stoppedRight = true;
    }
  }
}

//moves the lifter slowly and prevents tilting
void safelyRaiseScissorLift() {
  setLifter(100);
  int lifterAngleLeft;
  int lifterAngleRight;

  int stoppedLeft = false;
  int stoppedRight = false;
  while (!stoppedLeft || !stoppedRight) {
    //stop one side once it has reached the target
    if (lifterAngleLeft >= target_pot_high) {
      setLifterSide(LEFT, 0);
      stoppedLeft = true;
    }
    if (lifterAngleRight >= target_pot_high) {
      setLifterSide(RIGHT, 0);
      stoppedRight = true;
    }
  }
}
