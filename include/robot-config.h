#pragma once
using namespace vex;

class drive;
class Lift;

extern competition Competition;
extern controller Controller;
extern brain Brain;
extern motor LBMotor;
extern motor LFMotor;
extern motor RFMotor;
extern motor RBMotor;
extern motor LLift;
extern motor RLift;
extern motor Claw;
extern bumper bpAuto;
extern inertial IMU;
extern motor LToggle;
extern motor RToggle; 
extern motor_group toggle;
extern Lift MyLift;
extern drive MyChassis;

void  vexcodeInit( void );
