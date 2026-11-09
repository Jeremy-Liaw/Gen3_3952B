#pragma once
using namespace vex;

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
extern inertial Inertial;
extern motor LToggle;
extern motor RToggle; 
extern motor_group toggle;
extern motor_group Lift;

void  vexcodeInit( void );
