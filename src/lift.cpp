#include "vex.h"
  
Lift::Lift(motor_group LiftInput):
 DRLift(LiftInput)
{
    LiftHeight = 0; 
    TargetDeg = 0;
}


void Lift::LiftTo() { // Dr4B 不適合用追角度的方法控制
    const int offset = 500;
    const int MaxDeg = 3000; // 最大角度
    int HeightError = 0;
    while(true){
        if (TargetDeg > MaxDeg) {
            TargetDeg = MaxDeg;
        } else if (TargetDeg < 0) {
            TargetDeg = 0;
        }
        HeightError = TargetDeg - DRLift.position(deg); // 計算誤差
        int buff = 0;
        if(HeightError < 0) {
            buff = 50;
        }
        double output = toVolt((HeightError * 0.8) + buff);
        DRLift.spin(forward,output,volt);
        if (abs(HeightError) < offset) {
            DRLift.stop(hold);
        }
        wait(20,msec);
    }
}
void Lift::controlLift() {
    while (true) {
        if(Controller.ButtonL1.pressing()) {
            DRLift.spin(forward,12,volt);
            DRLift.setStopping(hold);
        } else if(Controller.ButtonL2.pressing()) {
            DRLift.spin(forward,-3,volt);
            DRLift.setStopping(coast);
        } else if(DRLift.position(deg) < 300) {
            DRLift.stop(coast);
        } else {
            DRLift.stop();
        }
        wait(20,msec);
    }
}

void Lift::Score() {

}
void Lift::stop() {
    DRLift.stop(hold);
}
