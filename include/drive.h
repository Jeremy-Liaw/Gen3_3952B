#pragma once
#include "vex.h"

using namespace vex;
double to180(double Input);

class drive{
  public: 
    motor_group LMotor;
    motor_group RMotor;
    inertial DriveIMU;

    double StraightKp;
    double StraightKi;
    double StraightKd;
    double StraightKc;
    double TurnKp;
    double TurnKi;
    double TurnKd;
    double SwingKp;
    double SwingKi;
    double SwingKd;
    int Maxvolt;
    drive(motor_group LMotorInput, motor_group RMotorInput,inertial IMUInput);//建構子
    // 原地旋轉
    void turn(double Goal,int Timeout);
    void turn(double Goal,double Kd,int Timeout);
    void turn(double Goal,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt);
    // 直走一段距離

    void goStraight(double Goal, int TimeOut);
    void goStraight(double Goal, int TimeOut, double DegTar);
    void goStraight(double Goal, double Kd, int TimeOut, double DegTar);
    void goStraight(double Goal,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt,double DegTar);   
    // 單輪轉
    void swingLift(double Goal, int TimeOut);
    void swingLift(double Goal,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt);    
    void swingRight(double Goal, int TimeOut);
    void swingRight(double Goal,double Kp,double Ki,double Kd,int TimeOut,int MaxVolt);    
    // 遙控程式
    void controlMove();
    void stop();
};
