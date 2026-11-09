#include "vex.h"  
void autoInit()
{

}

void autoStop()
{

}

void runCase(bool isLeft) {
    
}
void runCase1() { // 左邊
    autoInit();
    runCase(true);
    autoStop();
}
void runCase2() { // 右邊
    autoInit();
    runCase(false);
    autoStop();
}
void runCase3() {
    MyChassis.turn(270,12);
    autoStop();
}
void runCase4() {
    MyChassis.turn(180,12);
    autoStop();
}

void skills() {
    
}