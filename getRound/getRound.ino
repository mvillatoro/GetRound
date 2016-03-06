#include "VGA.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "collision.h"

//Variables
int windowx = VGA.getHSize();
int windowy = VGA.getVSize();
struct block wall[4];
struct block player;
int steps =0;
int d =0;
int fps = 0;
int state = 0;


void init_field(){
  //bloque, tipo, posx, posy, height, base, active
  init_block(&wall[0], 3, 40, 0, 30*4, 2, 1);
  init_block(&wall[1], 3, 40, windowy-4, 30*4, 2, 1);
  init_block(&wall[2], 3, windowx-10, 0, 2, 29*4, 1);
  init_block(&wall[3], 3, 40, 0, 2, 29*4, 1);
  init_block(&player, 1, 50, 100, 6, 10 , 1);
};

void render_field(){
    for(int x = 0; x < 5; x++)
      renderBlock(wall[x]);
    renderBlock(player);
};


void setup(){  
  VGA.begin(VGAWISHBONESLOT(9),CHARMAPWISHBONESLOT(10));
  Serial.begin(9600);
  VGA.setBackgroundColor(BLACK);
  init_field();  
  //VGA.clear();
};

void play(){
      VGA.clear();
      render_field();
      renderBlock(player);
      movePlayer();
}

void movePlayer()
{
  if(digitalRead(FPGA_BTN_0))
  {
    if(!Collision(player,wall[2]))
      player.posX += 2;
  }
	
  if(digitalRead(FPGA_BTN_1))
  {
    if(!Collision(player,wall[3]))
      player.posX -= 2;
  }
 
  if(digitalRead(FPGA_BTN_2))
  {
    if(!Collision(player,wall[0]))
      player.posY -= 2;    
  }
  if(digitalRead(FPGA_BTN_3))
  {
    if(!Collision(player,wall[1]))
      player.posY += 2; 
  }
  
};

void render_page(void (*function)(),void (*game)(), int _fps ){
    //  if (PlayingSound) {
    //     AudioFillBuffer();
    // }
    if(d > _fps){
      VGA.clear();
      d=0;
      function();
      game();
    }
    d++;
    fps++;
}

void menu(){
  VGA.setBackgroundColor(WHITE);
  VGA.printtext(22, 30, "Menu");
  if(digitalRead(FPGA_BTN_0)){
    VGA.setBackgroundColor(BLACK);
    state = 1;
  }
}
void nan(){
  return;
}
void loop()
{
  //menu
  if(state == 0){
    render_page(&menu,nan,100000);
  }
  //Game
  if(state == 1){
    render_page(&play,nan,100000);
  }
  //win
  if(state == 2){
    VGA.clear();
  }
  //loose
  if(state == 3){
    VGA.clear();
  }
};
