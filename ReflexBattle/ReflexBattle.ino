#include "userDef.h"
#include "sound.h"
#include <Microduino_Number.h>    //引用数码管库
#include <Microduino_ColorLED.h>  //引用彩灯库
#include <Microduino_Key.h>       //按键库

ColorLED strip = ColorLED(NUMPIXELS, PIN); //将ColorLED类命名为strip，并定义彩灯数量和彩灯引脚号

SoftwareSerial mySerial(PIN_NUMLED_RX, PIN_NUMLED_TX); 
Number NumLed(2, &mySerial);    

DigitalKey key_1(6);
DigitalKey key_2(8);

void setup() {
  NumLed.begin();   //数码管初始化
  strip.begin();    //彩灯初始化
  key_1.begin();    //按键1初始化
  key_2.begin();    //按键2初始化
}

byte P1_color = 0;  //玩家1彩灯颜色
byte P2_color = 0;  //玩家2彩灯颜色
byte P1_score = 0;  //玩家1分数
byte P2_score = 0;  //玩家2分数

void loop() {
  //游戏准备开始，熄灭所有与彩灯
  strip.setBrightness(0);
  strip.show();
  delay(1);
  //两玩家按键同时按下游戏开始，在此之前数码管闪烁
  while (key_1.readVal() != KEY_PRESSED || key_2.readVal() != KEY_PRESSED) {
    NumLed.turnOff(ALL);
    delay(100);
    NumLed.setNumber(0, P1_score, 0);
    NumLed.setNumber(1, P2_score, 0);
    NumLed.show();
    delay(100);
  }
  //两玩家分数清零，发出提示音
  P1_score = 0;
  P2_score = 0;
  NumLed.setNumber(0, P1_score, 0);
  NumLed.setNumber(1, P2_score, 0);
  NumLed.show();
  buzzerTinkle();
  buzzerTinkle();
  delay(2000);

  //游戏开始
  //任意玩家到达9分前重复执行反应快程序
  while (P1_score < 9 && P2_score < 9) {
    //为两个玩家分别随机选择一个彩灯号码
    P1_color = random(1, 4);
    P2_color = random(1, 4);
    strip.setBrightness(NORMAL_BRIGHTNESS);//彩灯设为标准亮度
    ColorLed_refresh(P1_color, P2_color);//刷新彩灯显示

    if (P1_color == P2_color) {
      //如果两灯颜色一样，则等待任意玩家按下
      while (key_1.readVal() != KEY_PRESSED && key_2.readVal() != KEY_PRESSED);
      //给先按下的玩家加分，并把另一名玩家的彩灯色号设为0（熄灭）
      if (key_1.readVal() == KEY_PRESSED) {
        P1_score++;
        P2_color = 0;
      }
      else {
        P2_score++;
        P1_color = 0;
      }
      //刷新数码管分数显示
      NumLed.setNumber(0, P1_score, 0);
      NumLed.setNumber(1, P2_score, 0);
      NumLed.show();

      strip.setBrightness(HIGHT_BRIGHTNESS);//彩灯设为高亮度
      ColorLed_refresh(P1_color, P2_color);//刷新彩灯显示（着重显示得分玩家彩灯）
      buzzerTinkle();//提示音
      delay(500);//所有显示停留半秒
    }
    else {
      //如果两灯颜色不一样，则等待1秒后重新换颜色
      for (int a = 0; a < 1000; a++) {
        delay(1);
        //在1秒中内重复1000次检测是否有人违反规则提前按下
        if (key_1.readVal() == KEY_PRESSED || key_2.readVal() == KEY_PRESSED) {
          buzzerAlarm();//警报音
          a = 0;
        }
      }
    }
  }
  //游戏结束，播放音乐
  playMusic();
}
//彩灯刷新函数（根据两个灯的色号切换颜色）
void ColorLed_refresh(byte _P1, byte _P2) {
  switch (_P1) {
    case 1:
      strip.setPixelColor(0, COLOR_RED);//COLOR_RED
      break;
    case 2:
      strip.setPixelColor(0, COLOR_GREEN);//COLOR_GREEN
      break;
    case 3:
      strip.setPixelColor(0, COLOR_BLUE);//COLOR_BLUE
      break;
    default:
      strip.setPixelColor(0, COLOR_NONE);//COLOR_NONE
      break;
  }
  switch (_P2) {
    case 1:
      strip.setPixelColor(1, COLOR_RED);//COLOR_RED
      break;
    case 2:
      strip.setPixelColor(1, COLOR_GREEN);//COLOR_GREEN
      break;
    case 3:
      strip.setPixelColor(1, COLOR_BLUE);//COLOR_BLUE
      break;
    default:
      strip.setPixelColor(1, COLOR_NONE);//COLOR_NONE
      break;
  }
  strip.show();
  delay(1);
}
