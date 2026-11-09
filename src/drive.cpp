#include "vex.h"    
#include "drive.h"
using namespace vex;


double GoalSKp = 5.3; // 預設值
double GoalSKi = 0.01;
double GoalSKd = 15;

double GoalTKp = 4;
double GoalTKi = 0.04;
double GoalTKd = 30;

drive::drive(motor_group LMotorInput, motor_group RMotorInput,inertial IMUInput)://建構子 drive::drive 同名
  LMotor(LMotorInput),
  RMotor(RMotorInput),
  IMU(IMUInput)
{

}

void drive::turn(double Goal,int Maxvolt) // 多載(可以用多種方呼叫函式(分別輸入不同參數))
{
  turn( Goal,GoalTKp,GoalTKi,GoalTKd,3000,Maxvolt);
}
void drive::turn(double Goal,double Kd,int Timeout){ // 多載(可以用多種方呼叫函式(分別輸入不同參數))
  turn( Goal,GoalTKp,GoalTKi,Kd,Timeout,12 );
}
void drive::turn(double Goal,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt){
  double LastError = 0; // 上次誤差
  double AddError = 0;  //累積誤差
  int SettleCounter = 0; // 判斷到目標時間
  int TimeCount = 0; // 計時器
  printf("-------------------------\n");
  printf("turn to Goal = %.2f Deg\n",Goal);
  while(true){
    double Error = Goal - IMU.heading(); // 距離目標還有幾度
    // printf("error = %.2f, IMU = %.2f\n",Error,IMU.heading());
    Error = to180(Error); // 將角度縮減-180到180度
    if(fabs(Error) < 15){ // 計算 I 如果角度一直停留在很接近的角度，就需要增加速度 
      AddError += Error;
    }
    else if((Error > 0 && LastError < 0) || (Error < 0 && LastError > 0)){ // 如果轉過 0 度時要將累積誤差歸零(方向不同)
      AddError = 0;
    }
    else{ // 遠離目標角 累積誤差歸零
      AddError = 0;
    }
    double Speed = (Error * Kp + (Error - LastError) * Kd + AddError * Ki) * 12 / 100; // 計算速度
    if(Speed > MaxVolt)Speed = MaxVolt; // 限速
    if(Speed <-MaxVolt)Speed =-MaxVolt;

    LastError = Error;
    LMotor.spin(forward, Speed,volt);
    RMotor.spin(forward,-Speed,volt);
    if(fabs(Error) < 1.5){ // 如果發現角度距離目標很近 透過累積 SettleCounter 判斷是否真的達到目標(在目標停留很久)
      SettleCounter+=10;
    }
    else{
      SettleCounter = 0;
    }
    TimeCount+=10; // 計時器增加
    if(SettleCounter > 100){ // 發現真的到目標就可以離開迴圈
      printf("success! error =  %.2f Deg,spend %.1f s\n",Error,TimeCount/1000.0);
      printf("Kp = %.1f, Ki = %.1f, Kd = %.1f\n",Kp,Ki,Kd);
      printf("---------------------------------------------------------------------------------\n");
      LMotor.stop(brake);
      RMotor.stop(brake);
      break;
    }
    if(TimeCount >= TimeOut){ // 超時
      printf("overtime! error = %.2f Deg,spend %.1f s\n",Error,TimeCount/1000.0);
      printf("Kp = %.1f, Ki = %.1f, Kd = %.1f\n",Kp,Ki,Kd);
      printf("---------------------------------------------------------------------------------\n");
      LMotor.stop(brake);
      RMotor.stop(brake);
      break;
    }
    wait(10,msec);
  }
}

// 增加的功能：角度自訂 (如果想走弧線可以自己設定角度)
// 如果 DegTaar 填入 -9999 代表不改變角度，保持原本的角度
void drive::goStraight(double Goal,int Maxvolt,int TimeOut) // 加上 drive 可以把在 class 內宣告過的方法在外面編輯 (畫面更節儉)
{
  goStraight(Goal,-9999,GoalTKp,GoalTKi,GoalTKd,TimeOut,Maxvolt);
}
void drive::goStraight(double Goal,double DegTar,double Kd,int TimeOut)
{
  goStraight(Goal,DegTar,GoalTKp,GoalTKi,Kd,TimeOut,12);
}
void drive::goStraight(double Goal,double DegTar,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt)
{
  double AddError = 0; // 累積誤差
  double LastError = 0; // 上次誤差
  int SettleCounter = 0; // 判斷到目標時間
  int TimeCount = 0; // 計時器
  double KeepDeg = 0;
  if (DegTar == -9999){ KeepDeg = IMU.heading(); }
  else{ KeepDeg = DegTar; }
  LMotor.resetPosition();
  RMotor.resetPosition();
  printf("-------------------------\n");
  printf("go to dis = %.2f Inch\n",Goal);
  while(true){
    double AveDeg = (LMotor.position(deg) + RMotor.position(deg)) / 2; // 馬達平均旋轉角度
    double CurrentDistance = (AveDeg / 360) * (3.14159 * 2.75) * (36.0 / 48.0); // 單位換算 角度換英吋 
    // (AveDeg / 360)馬達圈數 (36.0 / 48.0)換成輪子的圈數 (3.14159 * 2.75)輪子轉一圈的距離
    double Error = Goal - CurrentDistance; // 到目標還有多遠
    double HeadingError = KeepDeg - IMU.heading(); // 車子角度的誤差
    HeadingError = to180(HeadingError); // 將角度縮減-180到180度
    double Correction = HeadingError * 0.2; // 乘上常數降低速度
    if(fabs(Error) < 2) { 
      AddError += Error;
    } else if((Error > 0 && LastError < 0) || (Error < 0 && LastError > 0)){ 
      AddError = 0;
    } else { 
      AddError = 0;
    }
    double Speed = (Error * Kp + AddError * Ki + (Error - LastError) * Kd) * 12 / 100;
    if(Speed > MaxVolt) Speed = MaxVolt; // 限速
    if(Speed <-MaxVolt) Speed =-MaxVolt;
    LastError = Error;
    RMotor.spin(forward,Speed - Correction,volt);
    LMotor.spin(forward,Speed + Correction,volt);

    if(fabs(Error) < 1){ // 判斷是否在目標
      SettleCounter+=10;
    }
    else{
      SettleCounter = 0;
    }
    TimeCount+=10; // 計時器增加
    if(SettleCounter > 100){ // 到目標了
      printf("success! Error =  %.2f Inch,spend %.1f s\n",Error,TimeCount/1000.0);
      printf("Kp = %.1f, Ki = %.1f, Kd = %.1f\n",Kp,Ki,Kd);
      printf("---------------------------------------------------------------------------------\n");
      break;
    }
    if(TimeCount >= TimeOut){ // 超時
      printf("overtime! Error = %.2f Inch,spend %.1f s\n",Error,TimeCount/1000.0);
      printf("Kp = %.1f, Ki = %.1f, Kd = %.1f\n",Kp,Ki,Kd);
      printf("---------------------------------------------------------------------------------\n");
      break;
    }
    wait(10,msec);
  }
}

void drive::swingLift(double Goal) 
{
  swingLift(Goal,GoalSKp,GoalSKi,GoalSKd,8000,12);
}
void drive::swingLift(double Goal,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt) 
{
  double LastError = 0; 
  double AddError = 0;  
  int SettleCounter = 0; 
  int TimeCount = 0; 
  printf("Goal = %.2f Deg\n",Goal);
  printf("-------------------------\n");
  while(true){
    double Error = Goal - IMU.heading(); 
    Error = to180(Error); 
    if(fabs(Error) < 15){
      AddError += Error;
    }
    else if((Error > 0 && LastError < 0) || (Error < 0 && LastError > 0)){
      AddError = 0;
    }
    else{ 
      AddError = 0;
    }
    double Speed = (Error * Kp + (Error - LastError) * Kd + AddError * Ki) * 12 / 100; 
    if(Speed > MaxVolt)Speed = MaxVolt; 
    if(Speed <-MaxVolt)Speed =-MaxVolt;

    LastError = Error;
    LMotor.spin(forward,Speed,volt);
    RMotor.stop(hold);
    if(fabs(Error) < 1){ 
      SettleCounter+=10;
    }
    else{
      SettleCounter = 0;
    }
    TimeCount+=10; 
    if(SettleCounter > 100){

      printf("success! error =  %.2f Deg,spend %.1f s\n",Error,TimeCount/1000.0);
      printf("Kp = %.1f, Ki = %.1f, Kd = %.1f\n",Kp,Ki,Kd);
      printf("---------------------------------------------------------------------------------\n");
      break;
    }
    if(TimeCount >= TimeOut){ 
      printf("overtime! error = %.2f Deg,spend %.1f s\n",Error,TimeCount/1000.0);
      printf("Kp = %.1f, Ki = %.1f, Kd = %.1f\n",Kp,Ki,Kd);
      printf("---------------------------------------------------------------------------------\n");
      break;
    }
    wait(10,msec);
  }
}
void drive::swingRight(double Goal) 
{
  swingRight(Goal,GoalSKp,GoalSKi,GoalSKd,8000,12);
}
void drive::swingRight(double Goal,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt) 
{
  double LastError = 0; 
  double AddError = 0;  
  int SettleCounter = 0; 
  int TimeCount = 0; 
  printf("Goal = %.2f Deg\n",Goal);
  printf("-------------------------\n");
  while(true){
    double Error = Goal - IMU.heading(); 
    Error = to180(Error); 
    if(fabs(Error) < 15){
      AddError += Error;
    }
    else if((Error > 0 && LastError < 0) || (Error < 0 && LastError > 0)){
      AddError = 0;
    }
    else{ 
      AddError = 0;
    }
    double Speed = (Error * Kp + (Error - LastError) * Kd + AddError * Ki) * 12 / 100; 
    if(Speed > MaxVolt)Speed = MaxVolt; 
    if(Speed <-MaxVolt)Speed =-MaxVolt;

    LastError = Error;
    LMotor.stop(hold);
    RMotor.spin(forward,Speed,volt);
    if(fabs(Error) < 1){ 
      SettleCounter+=10;
    }
    else{
      SettleCounter = 0;
    }
    TimeCount+=10; 
    if(SettleCounter > 100){
      printf("success! error =  %.2f Deg,spend %.1f s\n",Error,TimeCount/1000.0);
      printf("Kp = %.1f, Ki = %.1f, Kd = %.1f\n",Kp,Ki,Kd);
      printf("---------------------------------------------------------------------------------\n");
      break;
    }
    if(TimeCount >= TimeOut){ 
      printf("overtime! error = %.2f Deg,spend %.1f s\n",Error,TimeCount/1000.0);
      printf("Kp = %.1f, Ki = %.1f, Kd = %.1f\n",Kp,Ki,Kd);
      printf("---------------------------------------------------------------------------------\n");
      break;
    }
    wait(10,msec);
  } 
}

void drive::controlMove() {
  double P3 = deadband(Controller.Axis3.position(),5); // -100 ~ +100
  double P1 = deadband(Controller.Axis1.position() * 0.9,5);
  LMotor.spin(fwd, toVolt(P3+P1), volt);
  RMotor.spin(fwd, toVolt(P3-P1), volt);
}

void drive::stop() {
  LMotor.stop();
  RMotor.stop();
}