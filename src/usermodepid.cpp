/*
#include "vex.h"
#include "main.cpp"
//?                         可以直接在遙控器調整 PID 的程式
int AngGoal = 90;
int StrGoal = 100;
double List[3] = {1,0,0}; // Kp Ki Kd
int PIDmode = 0;
int TestMode = 0;
bool ReviseGoal = false;
void CallButtonA() {
  if(TestMode == 0) {
    MyChassis.IMU.resetHeading();
    wait(2,sec);
    MyChassis.turn(AngGoal,List[0],List[1],List[2],5000,12);
  } else {
    MyChassis.LMotor.resetPosition();
    MyChassis.RMotor.resetPosition();
    wait(2,sec);
    MyChassis.goStraight(StrGoal,List[0],List[1],List[2],8000,12);
  }
}
void CallButtonB() {
  MyChassis.LMotor.stop(coast);
  MyChassis.RMotor.stop(coast);
  printf("Motor Stop!\n");
}
void CallButtonX() { PIDmode =   (PIDmode + 1) % 3; }
void CallButtonY() { TestMode = (TestMode + 1) % 2; }
void CallButtonUp() {
  if(ReviseGoal){
  (TestMode == 0) ? AngGoal+=10 : StrGoal+=10; 
  } else {
    List[PIDmode] += 0.1;
  } 
}
void CallButtonDown() {
  if(ReviseGoal){
    (TestMode == 0) ? AngGoal-=10 : StrGoal-=10;  
  } else {
    List[PIDmode] -= 0.1;
  } 
}
void CallButtonR1() {
  ReviseGoal = !ReviseGoal;
}
void usercontrol(void) {
  char PIDword[3] = {'P','I','D'};
  const char* unit[2] = {"Deg", "Inch"};
  const char* Modeword[2] = {"Turn_Ang","Go_Str"};
  Controller.ButtonA.pressed(CallButtonA);  // 開始
  Controller.ButtonB.pressed(CallButtonB);  // 馬達停止
  Controller.ButtonX.pressed(CallButtonX);  // 切換模式 (直走轉彎)
  Controller.ButtonY.pressed(CallButtonY);  // 調整 PID 選項
  
  Controller.ButtonUp.pressed(CallButtonUp);     // PID/Goal 項目增加
  Controller.ButtonDown.pressed(CallButtonDown); // PID/Goal 項目減少

  Controller.ButtonR1.pressed(CallButtonR1); // 調整 Goal 值
  
  while (1) {
    Controller.Screen.setCursor(1,1);
    if(ReviseGoal){
      int Goalprint =((TestMode == 0) ? AngGoal : StrGoal);
      Controller.Screen.print("Goal = %d %s                   ",Goalprint,unit[TestMode]);
    } else {
      Controller.Screen.print("Test:%s, %c = %.1f             ",Modeword[TestMode],PIDword[PIDmode],List[PIDmode]);      
    }
    Controller.Screen.setCursor(2, 1);
    Controller.Screen.print("P:%.1f I:%.1f D:%.1f             ", List[0], List[1], List[2]);
    wait(10, msec);
  }
}
*/