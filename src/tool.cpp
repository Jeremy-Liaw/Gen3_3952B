#include "vex.h"

double to180(double Input) { 
  Input = fmod(Input,360);
  if(Input > 180) return (Input - 360);      // 如果計算出的角度大於 180 代表向右轉太遠了 所以扣掉 360 讓他轉另一邊
  else if(Input < -180) return (Input + 360);// 如果計算出的角度小於 180 代表向左轉太遠了 所以加上 360 讓他轉另一邊
  else return Input;
}

double to90(double Input) { 
  Input = fmod(Input,180);
  if(Input > 90) return (Input - 180);      
  else if(Input < -90) return (Input + 180);
  else return Input;
}

float deadband(double Input, float Area) {
  return (fabs(Input) < Area) ? 0 : Input;
}

float toVolt(float Input) {
  return Input * 12.0 / 100.0;
}

double cmToInch(double Input) {
  return Input / 2.54;
}

double inchToCm(double Input) {
  return Input * 2.54;
}