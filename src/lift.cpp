#include "vex.h"

Lift::Lift(motor_group LiftInput):
 DRLift(LiftInput)
{
    LiftHeight = 0; 
    TargetDeg = 0;
}
void Lift::SetLift(bool Dir, int DirTime) {
    TaskDir = Dir;
    TaskDirTime = DirTime;
    LiftStar = true;
}
void Lift::controlLift() {
    if(Controller.ButtonL1.pressing()) {
        DRLift.spin(forward,12,volt);
        DRLift.setStopping(hold);
    } else if(Controller.ButtonL2.pressing()) {
        DRLift.spin(forward,-1.5,volt);
        DRLift.setStopping(coast);
    } else if(DRLift.position(deg) < 300) {
        DRLift.stop(coast);
    } else {
        DRLift.stop();
    }
    wait(20,msec);
}
void Lift::Score() {

}
void Lift::stop() {
    DRLift.stop(hold);
}
