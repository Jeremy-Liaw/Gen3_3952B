#include "vex.h"

void drawMotor(int StrX, int StrY, int Buff) {
  Brain.Screen.setPenWidth(0); 
  for (int i = 0; i < 28; i++) {       
    for (int j = 0; j < 28; j++) {    
      int Color = MotorMap[i][j]; // 顏色地圖
      if (Color == 0) continue;
      switch (Color) {
        case 1: Brain.Screen.setFillColor(40); break;                    // 黃色
        case 2: Brain.Screen.setFillColor(color(60, 60, 60)); break;     // 深灰
        case 3: Brain.Screen.setFillColor(color(0, 0, 0)); break;        // 黑色
        case 4: Brain.Screen.setFillColor(color(120, 120, 120)); break;  // 淺灰
        case 5: Brain.Screen.setFillColor(color(240)); break;            // 藍色
        case 6: Brain.Screen.setFillColor(color(255, 255, 255)); break;  // 白色
        case 7: Brain.Screen.setFillColor(70); break;                    // 亮黃  
      }
      Brain.Screen.drawRectangle( StrX + j * Buff, StrY + i * Buff, Buff, Buff );// 縮放圖片需要畫矩陣才能一起放大
    }
  }
}

void drawMotorLink(int StrX, int StrY, int Buff, const char* Temper, int Angle, bool NotLink) {
  Brain.Screen.setPenWidth(0); 
  int R,G,B;
  if(Temper == "Green") {
    R = 34; G = 177; B = 76;
  } else if(Temper == "Yello") {
    R = 255; G = 194; B = 14;
  } else if(Temper == "Orange") {
    R = 255; G = 126; B = 0;
  }else if(Temper == "Red") {
    R = 237; G = 28; B = 36;
  }else if(Temper == "White") {
    R = 255; G = 255; B = 255;
  }

  int outW = 7, outH = 9;
  if (Angle == 90 || Angle == 270) {
    outW = 9;
    outH = 7;
  }

  for (int dy = 0; dy < outH; dy++) {
    for (int dx = 0; dx < outW; dx++) {
      int mapY = 0, mapX = 0;
      switch (Angle) {
        case 90:  // 朝右
          mapY = 8 - dx; mapX = dy; break;
        case 180: // 朝下 
          mapY = 8 - dy; mapX = 6 - dx; break;
        case 270: // 朝左 
          mapY = dx; mapX = 6 - dy; break;
        case 0:   // 朝上
        default:
          mapY = dy; mapX = dx; break;
      }
      int Color;
      if(NotLink) {
        Color = MotorNotLinkMap[mapY][mapX];
      } else {
        Color = MotorLinkMap[mapY][mapX];
      }
      
      switch (Color) {
        case 0: Brain.Screen.setFillColor(color(R, G, B)); break;       // 綠黃橙紅
        case 1: Brain.Screen.setFillColor(color(0, 0, 0)); break;       // 黑色 
        case 2: Brain.Screen.setFillColor(color(180, 180, 180)); break; // 灰色 
        case 3: Brain.Screen.setFillColor(color(237, 28, 36)); break;   // 紅色 
        case 4: Brain.Screen.setFillColor(color(255, 255, 255)); break; // 白色         
      }
      Brain.Screen.drawRectangle(StrX + dx * Buff, StrY + dy * Buff, Buff, Buff);    
    }
  }
}

void drawTeamGoal(int StrX, int StrY, int Buff, bool GrayScale) {
  Brain.Screen.setPenWidth(0);
  for (int y = 0; y < 27; y++) {
    for (int x = 0; x < 39; x++) {
      int ColorCode = TeamGoalMap[y][x];
      if (ColorCode == -1) continue;
      if(GrayScale) {
        switch (ColorCode) {
          case 0: Brain.Screen.setFillColor(color(0, 0, 0)); break;       // 黑
          case 1: Brain.Screen.setFillColor(color(140, 140, 140)); break;   // 鮮藍
          case 2: Brain.Screen.setFillColor(color(183, 183, 183)); break;  // 淺天藍
          case 3: Brain.Screen.setFillColor(color(154, 154, 154)); break;  // 中天藍
          case 4: Brain.Screen.setFillColor(color(111, 111, 111)); break;  // 藍色陰影
          case 5: Brain.Screen.setFillColor(color(105, 105, 105)); break;  // 深藍陰影
          case 6: Brain.Screen.setFillColor(color(170, 170, 170)); break;  // 明亮淺藍
          case 7: Brain.Screen.setFillColor(color(116, 116, 116)); break;  // 橘黃齒輪
          case 8: Brain.Screen.setFillColor(color(120, 120, 120)); break; // 立柱灰
        }
      } else {
        switch (ColorCode) {
          case 0: Brain.Screen.setFillColor(color(0, 0, 0)); break;       // 黑
          case 1: Brain.Screen.setFillColor(color(0, 183, 239)); break;   // 鮮藍
          case 2: Brain.Screen.setFillColor(color(82, 212, 255)); break;  // 淺天藍
          case 3: Brain.Screen.setFillColor(color(71, 178, 214)); break;  // 中天藍
          case 4: Brain.Screen.setFillColor(color(11, 140, 184)); break;  // 藍色陰影
          case 5: Brain.Screen.setFillColor(color(23, 128, 166)); break;  // 深藍陰影
          case 6: Brain.Screen.setFillColor(color(53, 206, 252)); break;  // 明亮淺藍
          case 7: Brain.Screen.setFillColor(color(214, 122, 13)); break;  // 橘黃齒輪
          case 8: Brain.Screen.setFillColor(color(120, 120, 120)); break; // 立柱灰
        }
      }
      
      Brain.Screen.drawRectangle(StrX + x * Buff, StrY + y * Buff, Buff, Buff);
    }
  }
}
void drawCchannel(int StrX, int StrY, int Buff) {
  Brain.Screen.setPenWidth(0);
  for(int i = 0; i<68; i++) { 
    for(int j = 0; j<11; j++) {
      int ColorCode = CchannelMap[i][j];
      switch (ColorCode){
        case 0: Brain.Screen.setFillColor(color(226, 235, 246)); break;
        case 1: Brain.Screen.setFillColor(color(180, 180, 180)); break;
        case 2: Brain.Screen.setFillColor(color(255, 255, 255)); break;
      }
      Brain.Screen.drawRectangle(StrX + j * Buff, StrY + i * Buff, Buff, Buff);
    }
  }
}
int time0;
int count = 0;
void  brainScreen(int AutoMode) {
  time0 = Brain.Timer.time(sec);
  // 分隔線
  // Brain.Screen.setPenWidth(1);
  // Brain.Screen.setPenColor(purple);
  Brain.Screen.setFillColor(transparent);
  // for(int i = 0; i*20 < 479; i++) {
  //   Brain.Screen.drawLine(i * 20,0,i * 20,239); //畫直線
  // }
  // for(int i = 0; i*20 < 239; i++) {
  //   Brain.Screen.drawLine(0,i * 20,479,i * 20); //畫橫線
  // }
  // 外框
  Brain.Screen.drawRectangle(450,60,29,180,color(180,180,180)); // 灰色底
  Brain.Screen.setPenColor(white);
  Brain.Screen.setPenWidth(2);
  Brain.Screen.drawRectangle(1,1,477,237); // 螢幕框
  Brain.Screen.drawLine(0,40,479,40);
  Brain.Screen.drawRectangle(20,60,200,160); // 左半欄位
  Brain.Screen.drawLine(20,160,220,160); // 左半欄位中間那條線
  Brain.Screen.drawRectangle(259,144,58,46); // 底盤馬達框
  Brain.Screen.drawRectangle(258,143,61,49,white); // 底盤馬達框

  Brain.Screen.drawLine(360,60,480,60); // 右邊橫線
  Brain.Screen.drawLine(360,120,480,120);
  Brain.Screen.drawLine(360,180,480,180);
  Brain.Screen.drawLine(360,60,360,240); // 右邊框直線
  

  //第一行 y = 25
  Brain.Screen.setFont(mono20);
  Brain.Screen.printAt(10,25,"[3952B]");
  // 電量
  Brain.Screen.printAt(220,25,"power: [");
  Brain.Screen.setPenWidth(0);
  int C = Brain.Battery.capacity() * 12.0 / 10.0; // 將馬達 0 ~ 100 電轉換成 0 ~ 120 度的顏色
  for(int i = 0; i<Brain.Battery.capacity() / 10; i++) {
    Brain.Screen.drawRectangle(i * 10 + 300,13,7,15,C);
  }// 430
  Brain.Screen.printAt(400,25,"]+ ");
  Brain.Screen.setPenColor(C);
  Brain.Screen.printAt(425,25,"%d%%",Brain.Battery.capacity());
  Brain.Screen.setPenColor(white);
  // 左半框框
  // 自動
  Brain.Screen.setFont(mono20);
  Brain.Screen.printAt(65,85,"[Auto Mode]");
  Brain.Screen.setFont(mono15);
  Brain.Screen.printAt(65,115,"Team Goal at ?");
  int GoalX, GrayX, GoalY = 125;
  Brain.Screen.setFont(mono20);
  bool light = true;
  if(AutoMode == 0) { // 左邊
    GoalX = 41; GrayX = 161;
    Brain.Screen.printAt(90,145," Left  ");
    light = true;
  } else if(AutoMode == 1) { // 右邊
    GoalX = 161; GrayX = 41;
    Brain.Screen.printAt(95,145,"Right ");
    light = true;
  } else if(AutoMode == 2) {
    Brain.Screen.setPenColor(red);
    Brain.Screen.printAt(95,145,"Skill ");
    Brain.Screen.setPenColor(white);
    GoalX = 161; GrayX = 41;
    light = false;
  }
  drawTeamGoal(GoalX,GoalY,1,false);// 正常
  drawTeamGoal(GrayX,GoalY,1,light); // 灰階
  // IMU
  bool LinkIMU = Inertial.installed();
  Brain.Screen.setFont(mono15);
  Brain.Screen.printAt(100,180,"[IMU]");
  Brain.Screen.printAt(35,203,"state:[");
  if(LinkIMU) { // 有連接
    if(time0 - 0 <= 2) {
      Brain.Screen.setPenColor(white);
      Brain.Screen.printAt(95,203,"Loading... ]");
    } else {
      Brain.Screen.setPenColor(green);
      Brain.Screen.printAt(95,203,"%.2f (deg)   ",Inertial.heading());
      Brain.Screen.setPenColor(white);
      Brain.Screen.printAt(195,203,"]");
    }  
  } else { // 沒連接
    Brain.Screen.setPenColor(red);
    Brain.Screen.printAt(95,203,"Not Link!   ");
    Brain.Screen.setPenColor(white);
    Brain.Screen.printAt(170,203,"]  ");
  }
  // 右半馬達
  drawMotor(262,70,2);
  int ChassisXY[4][2] = {{260,145},{290,145},{260,170},{290,170}};
  motor m[4] = {LFMotor,RFMotor,LBMotor,RBMotor};
  for(int i = 0; i<4; i++) { // 判斷連接 溫度 輸出
    bool Link = m[i].installed();
    int Temperature = m[i].temperature();
    int face = 0;
    char *Temp;
    int x,y;
    if(Temperature <= 40) {
      Temp = "Green";
    } else if (Temperature <= 50) {
      Temp = "Orange";
    } else if (Temperature <= 60) {
      Temp = "Orange";
    } else if (Temperature <= 70) {
      Temp = "Red";
    } else {
      Temp = "White"; 
    }
    if(i % 2 == 0) {
      face = 90; 
    } else {
      face = 270; 
    }
    drawMotorLink(ChassisXY[i][0], ChassisXY[i][1], 3, Temp, face, !Link);
    Brain.Screen.setFont(mono12);
    Brain.Screen.setFillColor(transparent);
    Brain.Screen.printAt(245,218,"[Chassis motor]");
  }//27 21
  // 升降 Toggle 夾子
  Brain.Screen.setFont(mono15);
  Brain.Screen.printAt(370,85,"DR4B");
  Brain.Screen.printAt(370,105,"Motor");
  Brain.Screen.printAt(370,145,"Toggle");
  Brain.Screen.printAt(370,165,"Motor");
  Brain.Screen.printAt(370,205,"Intake");
  Brain.Screen.printAt(370,225,"Motor");
  int MotorListY[5] = {66,93,126,153,185};
  motor m2[5] = {LLift,RLift,LToggle,RToggle,Claw};
  int j = 0;
  for(int i = 0; i<5; i++) {
    bool Link = m2[i].installed();
    int Temperature = m2[i].temperature();
    char *Temp;
    int x,y;
    if(Temperature <= 40) {
      Temp = "Green";
    } else if (Temperature <= 50) {
      Temp = "Yello";
    } else if (Temperature <= 60) {
      Temp = "Orange";
    } else if (Temperature <= 70) {
      Temp = "Red";
    } else {
      Temp = "White"; 
    }
    drawMotorLink(451, MotorListY[i], 3, Temp, 270, !Link);
    Brain.Screen.setFillColor(white);
    if(j % 2 == 0) {
      Brain.Screen.setPenColor(blue);
      Brain.Screen.printAt(440,MotorListY[i] + 15,"L");
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.printAt(440,MotorListY[i] + 15,"R");
    }
    j++;
  }
  Brain.Screen.setPenColor(white);
}