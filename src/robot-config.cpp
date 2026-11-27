#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen.
competition Competition;
controller Controller;

brain Brain;  // 底盤馬達 F = front， B = back
motor LFMotor = motor(PORT3, ratio6_1, true);
motor LBMotor = motor(PORT11, ratio6_1, true);   
motor RFMotor = motor(PORT8, ratio6_1, false);
motor RBMotor = motor(PORT20, ratio6_1, false);

motor LLift = motor(PORT12, ratio6_1, true);     // DR$B 升降機 
motor RLift = motor(PORT19, ratio6_1, false);
motor Claw = motor(PORT6, ratio18_1, false);  // 新車是 false 舊車是 ture
motor LToggle = motor(PORT2, ratio18_1, false); // Toggle 
motor RToggle = motor(PORT9, ratio18_1, true);

bumper bpAuto = bumper(Brain.ThreeWirePort.A);   // Limit Switch
inertial IMU = inertial(PORT18);                 // Inertial 

motor_group toggle = motor_group(LToggle, RToggle);

Lift MyLift(motor_group(LLift,RLift));
drive MyChassis( motor_group(LBMotor,LFMotor), motor_group(RBMotor,RFMotor),inertial(PORT18));

void vexcodeInit( void ) {
  // nothing to initialize
}

