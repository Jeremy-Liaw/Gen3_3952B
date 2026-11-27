#pragma one
#include "vex.h"

using namespace vex;

class Lift{
  public:
    double LiftHeight;     // 存目前高度
    double TargetDeg;   // 存目標高度
    motor_group DRLift;
    Lift(motor_group LiftInput);
    void SetLift(bool Dir, int DirTime); // 多工自動升降
    void controlLift(); // 遙控部分
    void Score();       // 給自動用 得分動作
    void stop();

};