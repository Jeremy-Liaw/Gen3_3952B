#pragma one
#include "vex.h"

using namespace vex;

class Lift{
  public:
    double LiftHeight;     // 存目前高度
    double TargetDeg;   // 存目標高度
    motor_group DRLift;
    Lift(motor_group LiftInput);
    int LiftTo();      // 追高度
    int controlLift(); // 遙控部分
    void Score();       // 給自動用 得分動作
    void stop();

    static int controlLiftTask();
    static int LiftToTask();
};