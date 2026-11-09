#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "TaskFuntion.h"
#include "robot-config.h"
#include "drive.h"
#include "tool.h"

#include "autons.h"
#include "screen.h"


extern int AutoEnd;
extern int LiftPos;
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)