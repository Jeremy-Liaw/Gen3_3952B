/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       DeanL                                                     */
/*    Created:      2026/8/18 下午1:49:42                                       */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"   

using namespace vex;

int AutoEnd = 3;
int AutoMode = 0;
bool StrAuto = false;
int LiftPos = 0; // 升降機位置
void callBackbp() {
  AutoMode = (AutoMode + 1) % AutoEnd;
}
void pre_auton(void) {
  vexcodeInit();
  bpAuto.pressed(callBackbp);
  while(!StrAuto){  // 顯示內容 隊名 電池電量 自動模式 IMU 馬達溫度(要有過熱警告) 硬體是否斷線
    brainScreen(AutoMode);
    if(Brain.Screen.pressing()) {
      while(Brain.Screen.pressing()) {}
      AutoMode = (AutoMode + 1) % AutoEnd;
    }
    Brain.Screen.render();
    wait(10,msec);
  }
}

void autonomous(void) {
  StrAuto = true;
  Brain.Screen.clearScreen(); // 自動程式開始，螢幕停止更新，所以也要清空螢幕
  switch(AutoMode) {
    case 0:
      runCase1();
      break;
    case 1:
      runCase2();
      break;
    case 2:
      skills();
      break;
    case 3:
      runCase4();
      break;
  }
}
// !---------------------------------------PID測試----------------------------------------------------------
void usercontrol(void) {
  StrAuto = true;
  Brain.Screen.clearScreen();
  task liftTask(DRlift);
  task rachetTask(rachet);
  task toggleTask(Toggle);
  while (1) {
    MyChassis.controlMove(); // 底盤遙控  之後要加遙控曲線
    wait(20, msec);
  }



}
// !---------------------------------------PID測試----------------------------------------------------------
int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  printf("Program Start\n");
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}
