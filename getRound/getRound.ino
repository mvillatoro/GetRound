#include "VGA.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

unsigned char wallabove[] ={
GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN
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

void InitWallAbove(){
  WallAbove.posX = 0;
  WallAbove.PosY = 0;
  WallAbove.width = 10;  
  WallAbove.height = 1;
  WallAbove.image = wallabove;
};

void initData
{
  InitWallAbove();
  
    VGA.begin(VGAWISHBONESLOT(9),CHARMAPWISHBONESLOT(10));
  Serial.begin(9600);
  VGA.setBackgroundColor(BLACK);
  
  VGA.writeArea(WallAbove.posX,WallAbove.posY,WallAbove.width, WallAbove.height, WallAbove.image);
};

void setup()
{ 
};

void loop()
{
};


