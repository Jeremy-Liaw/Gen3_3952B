#include "vex.h"  

int TeamGoalPinCup = 400; 
int BlackGoalPinCup = 800; 
int DonwTime = 5;
const int PinCupHeight = 450;
const char* Score = "BlackGoal";
bool SCORE = false;
/*

Lift 最高 Position : 2580
Claw 最大 Position : 不需要 

Team Goal 第一顆需要升到的 Position : 380
BlackGoal 第一顆需要升到的 Position : 770
一顆 Pin + Cup 的Postiton : 400
Buff 要多少 : 200

*/

void autoInit()
{
    printf("Auto Start\n");
    Claw.setPosition(0,deg);
    toggle.setPosition(0,deg);
    Claw.setVelocity(100,pct);
    toggle.setVelocity(75,pct);
    MyLift.DRLift.setVelocity(100,pct);
}

void autoStop()
{
    Claw.stop(hold);
    toggle.stop(hold);
    MyLift.stop();
    MyChassis.stop();
    printf("Auto Stop\n");
}
 
// int FunScore() {
//     int Buff = 200; // 額外增高
//     while(1) {
//         if(SCORE){
//             SCORE = false;
//             if(strcmp(Score,"TeamGoal") == 0) {
//                 Lift.spinTo(TeamGoalPinCup + Buff,deg); // 略高
//             } else if(strcmp(Score,"BlackGoal") == 0) {
//                 Lift.spinTo(BlackGoalPinCup + Buff,deg);
//             }
//             wait(DonwTime,sec); 
//             if(strcmp(Score,"TeamGoal") == 0) {
//                 Lift.spinTo(TeamGoalPinCup,deg);
//                 TeamGoalPinCup += PinCupHeight; // 疊了一顆
//             } else if(strcmp(Score,"BlackGoal") == 0) {
//                 Lift.spinTo(BlackGoalPinCup,deg);
//                 BlackGoalPinCup += PinCupHeight;
//             }
//             wait(2,sec);
//             Claw.spin(forward,-100,pct); // 開爪
//             wait(2,sec);
//             Claw.stop(hold);            
//         }
//         wait(20,msec);
//     }
// }
void runCase(bool isLeft) { 
    int rev = (isLeft) ? 1:-1;
    autoInit();
    toggle.spinFor(forward,360,deg,false);
    wait(2,sec);
    // 剩下交給明天的我
    autoStop();
}
void runCase1() { // 左邊
    runCase(true);
}
void runCase2() { // 右邊
    runCase(false);
}
void runCase3() {

}
void runCase4() {

}

void skills() {
    
}