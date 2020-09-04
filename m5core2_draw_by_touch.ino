#include <M5Core2.h>
#include <Fonts/EVA_20px.h>
#include <stdio.h>
#include <map>

enum {
  small = 0,
  midium,
  large,
  radius_threshold,
};

enum {
  black = 0,
  white,
  red,
  green,
  blue,
  yellow,
  purple,
  pink,
  color_threshold,
};

std::map<int, uint32_t> colorMap{
    {black, BLACK},
    {white, WHITE},
    {red, RED},
    {green, GREEN},
    {blue, BLUE},
    {yellow, YELLOW},
    {purple, PURPLE},
    {pink, PINK},
};

std::map<int, uint32_t> radiusMap{
    {small, 10},
    {midium, 15},
    {large, 25},
};

uint32_t color = black;
uint32_t radius = midium;

void toggleColor()
{
  color++;
  if(color >= color_threshold) color = 0;
  showCircleIcon();
}

void toggleRadius()
{
  radius++;
  if(radius >= radius_threshold) radius = 0;
  showCircleIcon();
}

void showCircleIcon()
{
  const int L = radiusMap[large];
  const int x = L + 2;
  const int y = L + 2;
  M5.Lcd.fillCircle(x, y, L + 2, WHITE); //reset
  if(color == white) M5.Lcd.drawCircle(x, y, radiusMap[radius], BLACK);
  else M5.Lcd.fillCircle(x, y, radiusMap[radius], colorMap[color]);
}

void touchsetup()
{
  showCircleIcon();
}

void setup() {
  M5.begin(true, true, true, true);
  Serial.begin(115200);
  M5.Lcd.fillScreen(WHITE);
  touchsetup();
}

void resetScreen()
{
  M5.Lcd.fillScreen(WHITE);
  showCircleIcon();
}

void loop() {
  TouchPoint_t pos= M5.Touch.getPressPoint();

  static bool isPressed = false;

  if(!M5.Touch.ispressed()) isPressed = false;

  if(pos.y > 1 && pos.x > 1){
    M5.Lcd.fillCircle(pos.x, pos.y, radiusMap[radius], colorMap[color]);
  }

  if(!isPressed){
    if(pos.y > 240){
      if(pos.x < 120){//btnA
        isPressed = true;
        toggleColor();
      }
      else if(pos.x > 240){ //btnC
        isPressed = true;
        resetScreen();
      }
      else if(pos.x >= 180 && pos.x <= 210){ //btnB
        isPressed = true;
        toggleRadius();
      }
    }
  }
  delay(10);
}