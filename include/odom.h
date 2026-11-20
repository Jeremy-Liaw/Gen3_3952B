#pragma once
#include "vex.h"

using namespace vex;

class odom {
    private:
        int HorWheel;
        int StrWheel;
        int Pose;
    public:
        int X;
        int Y;
        int Heading;
        
        void update();
};


