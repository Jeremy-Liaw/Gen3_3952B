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
    task UpDownLiftTask(UpDownLift);
}

void autoStop()
{
    Claw.stop(coast);
    toggle.stop(coast);
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
    toggle.spinFor(forward,360,deg); // 轉 Toggle
    if(rev == 1) { // 轉到 Goal 的角度
        MyChassis.swingLift(37,500);   
    } else {
        MyChassis.swingRight(37,500);
    }
    // MyLift.SetLift(true,200);       // 同時升起升降機
    MyChassis.goStraight(15.5,35,700,-9999);// 走到 Goal
    wait(2,sec);    //TODO 開爪 只放一顆 Pin 不能直接降升降機 記得開爪
    // MyLift.SetLift(false,700);
    MyChassis.goStraight(-5,600); // 後退一點
    MyChassis.turn(-47,800);      // 轉到牆邊 Pin + Cup
    MyChassis.goStraight(7,1000); // 走到牆邊
    // 轉 Intake 吸牆邊 Pin + Cup
    autoStop();
}
void runCase1() { // 聯隊 Goal 在左邊
    runCase(true);
}
void runCase2() { // 聯隊 Goal 在右邊
    runCase(false);
}
void runCase3() {

}
void runCase4() {

}

void skills() {
    
}