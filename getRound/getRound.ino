#include "VGA.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "collision.h"

//Variables
int windowx = VGA.getHSize();
int windowy = VGA.getVSize();
struct block wall[5];
int steps =0;
int d =0;
int fps = 0;
int playerPosX = 50;
int playerPosY = 100;

void init_field(){
  //bloque, tipo, posx, posy, height, base, active
  init_block(&wall[0], 3, 40, 0, 30*4, 2, 1);
  init_block(&wall[1], 3, 40, windowy-4, 30*4, 2, 1);
  init_block(&wall[2], 3, windowx-10, 0, 2, 29*4, 1);
  init_block(&wall[3], 3, 40, 0, 2, 29*4, 1);
  init_block(&wall[4], 1, playerPosX, playerPosY, 6, 10 , 1);
};

void render_field(){
    for(int x = 0; x < 5; x++)
      renderBlock(wall[x]);
};

void setup(){  
  VGA.begin(VGAWISHBONESLOT(9),CHARMAPWISHBONESLOT(10));
  Serial.begin(9600);
  VGA.setBackgroundColor(BLACK);
  init_field();
  
  //VGA.clear();
};

void play(){
    //  if (PlayingSound) {
    //     AudioFillBuffer();
    // }
    // if(fps == 500000){
    //   t++;
    //   fps=0;
    // }
    if(d > 200000){
      //manage_input();
      VGA.clear();
      render_field();
      // render_score();
      // move_snake(direction);
      steps++;
      // if(steps == 5*4){
      //   generate_manzanitas();
      //   steps=0;
      // }
      d=0;
      // if(score >= 100)
      //   state=1;
      doStuff();
      init_block(&wall[4], 1, playerPosX, playerPosY, 6, 10 , 1);
    }
    d++;
    fps++;
}

void doStuff()
{
  if(digitalRead(FPGA_BTN_0))
  {
    playerPosX = playerPosX - 2; 
  }
	
  if(digitalRead(FPGA_BTN_1))
  {
    playerPosX = playerPosX + 2;
  }
 
  if(digitalRead(FPGA_BTN_2))
  {
    playerPosY = playerPosY + 2;     
  }
  if(digitalRead(FPGA_BTN_3))
  {
    playerPosY = playerPosY -2;     
  }
};

void loop()
{
  play();
};


