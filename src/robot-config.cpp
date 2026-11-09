#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen.
competition Competition;
controller Controller;

brain Brain;  // 底盤馬達 F = front， B = back
motor LFMotor = motor(PORT1, ratio6_1, true);
motor LBMotor = motor(PORT2, ratio6_1, true);   
motor RFMotor = motor(PORT10, ratio6_1, false);
motor RBMotor = motor(PORT9, ratio6_1, false);

motor LLift = motor(PORT3, ratio6_1, true);     // DR$B 升降機 
motor RLift = motor(PORT8, ratio6_1, false);
motor Claw = motor(PORT6, ratio18_1, true);
motor LToggle = motor(PORT14, ratio18_1, true); // Toggle 
motor RToggle = motor(PORT17, ratio18_1, false);

bumper bpAuto = bumper(Brain.ThreeWirePort.A);   // Limit Switch
inertial Inertial = inertial(PORT9);                 // Inertial 

motor_group Lift = motor_group(LLift,RLift);
motor_group toggle = motor_group(LToggle, RToggle);

drive MyChassis( motor_group(LBMotor,LFMotor), motor_group(RBMotor,RFMotor),inertial(PORT9));

void vexcodeInit( void ) {
  // nothing to initialize
}

