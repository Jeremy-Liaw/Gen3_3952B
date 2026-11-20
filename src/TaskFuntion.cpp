#include "vex.h"

int rachet() // TODO: 不要手動開合，不好用
{
  while(1) {
    if(Controller.ButtonR2.pressing()) {
      Claw.spin(forward, -47.5, pct);
    } else if(Controller.ButtonR1.pressing()) {
      Claw.spin(forward,100, pct);
    } else {
      Claw.stop(hold);
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
      toggle.spinFor(forward,-180,deg,false);
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