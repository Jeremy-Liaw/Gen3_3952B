#include "vex.h"

int DRlift()
{
  while(1) {
    if(Controller.ButtonR1.pressing()) {
      Lift.spin(forward, 100, pct);
    } else if(Controller.ButtonR2.pressing()) {
      Lift.spin(reverse, 100, pct);
    } else {
      Lift.stop(hold);
    }
    wait(20,msec);
  }
  return 0; 
}

int rachet() //TODO 不要手動開合，不好用
{
  while(1) {
    if(Controller.ButtonL2.pressing()) {
      Claw.spin(forward, 30, pct);
    } else if(Controller.ButtonL1.pressing()) {
      Claw.spin(reverse,100, pct);
    } else {
      Claw.stop(hold);
    }
    wait(20,msec);
  }
  return 0;
}