#include "vex.h"
bool TaskDir = 0;   
bool LiftStar = false;  
int TaskDirTime = 0;

int rachet() // TODO: 不要手動開合，不好用
{
  while(1) {
    if(Controller.ButtonR2.pressing()) {
      Claw.spin(forward, -47.5, pct);
    } else if(Controller.ButtonR1.pressing() || Controller.ButtonL1.pressing()) {
      Claw.spin(forward,100, pct);
    } else {
      Claw.stop(coast);
    }
    wait(20,msec);
  }
  return 0;
}

int toggleSide() //* 開程式前要將 toggle 結構轉成直的
{
  while(1) 
  {
    float LModToggle = to90(LToggle.position(deg));
    float RModToggle = to90(RToggle.position(deg));
    if(Controller.ButtonY.pressing())
    {
      toggle.setVelocity(100,pct);
      toggle.spinFor(forward,180,deg,false);
      while(Controller.ButtonY.pressing()) {wait(20, msec);}
    } 
    else if(fabs(LModToggle) >= 10)
    {
      LToggle.spinFor(forward,-LModToggle,deg,false);
    } 
    else if(fabs(RModToggle) >= 10)
    {
      RToggle.spinFor(-RModToggle,deg,false);
    }
    wait(20, msec);
  }
  return 0;
}
int UpDownLift() {
    int time0 = Brain.Timer.time();
    bool first = true;
    while(1) {
      if(LiftStar) {
        if(first) {
          first = false;
          time0 = Brain.Timer.time();
          if(TaskDir)
            MyLift.DRLift.spin(forward,12,volt);
          else
            MyLift.DRLift.spin(forward,-1.5,volt);
        } else {
          if(Brain.Timer.time() - time0 >= TaskDirTime) {
              LiftStar = false;
              if(MyLift.DRLift.position(deg) < 300) {
                  MyLift.DRLift.stop(coast);
              } else {
                  MyLift.DRLift.stop(hold);
              }
          }          
        }
      } else {
        first = true;
      }
      wait(20,msec);
    }
}