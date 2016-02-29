#include "VGA.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

unsigned char wallAboveBelow[] ={
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN
};

unsigned char wallLeftRight[] ={
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN
};

struct Sprite
{
  int posX;
  int posY;
  int width;
  int height;
  unsigned char *image;
};

struct Sprite WallAbove;
struct Sprite WallBelow;
struct Sprite WallLeft;
struct Sprite WallRight;

void InitWallAbove(){
  WallAbove.posX = 1;
  WallAbove.posY = 1;
  WallAbove.width = 158;  
  WallAbove.height = 1;
  WallAbove.image = wallAboveBelow;
};

void InitWallBelow(){
  WallBelow.posX = 1;
  WallBelow.posY = 117;
  WallBelow.width = 158;  
  WallBelow.height = 1;
  WallBelow.image = wallAboveBelow;
};

void InitWallLeft(){
  WallLeft.posX = 1;
  WallLeft.posY = 1;
  WallLeft.width = 1;  
  WallLeft.height = 117;
  WallLeft.image = wallLeftRight;
};

void InitWallRight(){
  WallRight.posX = 150;
  WallRight.posY = 1;
  WallRight.width = 1;  
  WallRight.height = 117;
  WallRight.image = wallLeftRight;
};

void setup()
{ 
  
  InitWallAbove();
  InitWallBelow();
  InitWallLeft();
  InitWallRight();
  
  VGA.begin(VGAWISHBONESLOT(9),CHARMAPWISHBONESLOT(10));
  Serial.begin(9600);
  VGA.setBackgroundColor(BLACK);
  
  VGA.writeArea(WallAbove.posX,WallAbove.posY,WallAbove.width, WallAbove.height, WallAbove.image);
  VGA.writeArea(WallBelow.posX,WallBelow.posY,WallBelow.width, WallBelow.height, WallBelow.image);
  VGA.writeArea(WallLeft.posX,WallLeft.posY,WallLeft.width, WallLeft.height, WallLeft.image);
  VGA.writeArea(WallRight.posX,WallRight.posY,WallRight.width, WallRight.height, WallRight.image);
  //VGA.clear();
};

void loop()
{
};


