#pragma once
#include "vex.h"

using namespace vex;
double to180(double Input);

class drive{
  public: 
    motor_group LMotor;
    motor_group RMotor;
    inertial IMU;
    drive(motor_group LMotorInput, motor_group RMotorInput,inertial IMUInput);//建構子
    // 原地旋轉
    void turn(double Goal,int Maxvolt);
    void turn(double Goal,double Kd,int Timeout);
    void turn(double Goal,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt);
    // 直走一段距離
    void goStraight(double Goal, int Maxvolt, int TimeOut);
    void goStraight(double Goal, double DegTar, double Kd, int TimeOut);
    void goStraight(double Goal,double DegTar,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt);   
    // 單輪轉
    void swingLift(double Goal);
    void swingLift(double Goal,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt);    
    void swingRight(double Goal);
    void swingRight(double Goal,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt);    
    // 遙控程式
    void controlMove();
    void stop();
};
