#pragma once

// class drive;



extern int TeamGoalPinCup; // TeamGoal 第一個分數需要的高度 之後每疊一次 TeamGoal 就加一次 PinCupHeight
extern int BlackGoalPinCup; // BlackGoal 第一個分數需要的高度
extern int DonwTime;
extern const int PinCupHeight; // 升降機每疊一個PinCup要升高的角度
extern const char* Score;
extern bool SCORE;
//! 後來發現Lift馬達旋轉角度跟升降機高度不是線性關係
void runCase(bool isLeft);
void runCase1();
void runCase2();
void runCase3();
void runCase4();
void skills();
// int FunScore(); 

/*

Lift 最高 Position : 2580
Claw 最大 Position : 不需要 

Team Goal 第一顆需要升到的 Position : 380
BlackGoal 第一顆需要升到的 Position : 770
一顆 Pin + Cup 的Postiton : 400
Buff 要多少 : 200

*/