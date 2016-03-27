#include "VGA.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "level.h"
#include "collision.h"

#include "SmallFS.h"
#include "cbuffer.h"

//Variables
int windowx = VGA.getHSize();
int windowy = VGA.getVSize();
struct block wall[4];
struct block player;
struct block door[2];
struct block obstaculo;
struct block lives[3];
struct game room[9];
int steps =0;
int d =0;
int fps = 0;
int state = 0;
int mundo = 1;
int nivel = 1;
int vidas = 3;
int win [3]= {0,0,0};
int win_cons= 0;
int indexRoom = 0;

//Botones:
int btn_A =  FPGA_GPIO_10;
int btn_B =  FPGA_GPIO_12;
int btn_L =  FPGA_GPIO_14;
int btn_R =  FPGA_GPIO_16;
int btn_U =  FPGA_GPIO_18;
int btn_D =  FPGA_GPIO_20;
int event = 0;

unsigned long Index = 0;
unsigned long TimerCount = 0;
unsigned long contador = 0;
volatile unsigned char PlayingSound;

SmallFSFile audiofile;

#define FRAME_SIZE  200
struct AudioData {
    unsigned char count;
    unsigned char sample[FRAME_SIZE];
};

CircularBuffer<AudioData, 2> audioBuffer;
AudioData currentData;

void DAC_SetOutput(unsigned char data)
{
    unsigned int level0 = ((unsigned int)data) << 8;
    unsigned int level1 = ((unsigned int)data) << 8;
    unsigned int level = (level1 << 16) | level0;    
    
    SIGMADELTADATA = level;
}

void SoundInit(void) 
{
    // Enable channel 0 and 1
    SIGMADELTACTL = 0x03;

    // Clear timer counter.
    TMR0CNT = 0;
 
    // Set up timer , no prescaler.
    TMR0CMP = 0;
    TMR0CTL = (0 << TCTLENA)| (1 << TCTLCCM)| (1 << TCTLDIR)| (1 << TCTLIEN);
 
    // Enable timer 0 interrupt on mask.
    INTRMASK |= (1 << INTRLINE_TIMER0);
 
    // Globally enable interrupts.
    INTRCTL = (1 << 0);
}

void SoundOff(void) 
{
    DAC_SetOutput(0);

    // Disable timer 0
    TMR0CTL &= ~(_BV(TCTLENA));
}

void AudioFillBuffer()
{
    int r;

    AudioData d;
    while (!audioBuffer.isFull()) {
        r = audiofile.read(&d.sample[0], FRAME_SIZE);
        if (r != 0) {
            d.count = r; // 1 sample per byte
            audioBuffer.push(d);
        } else {
            audiofile.seek(0, SEEK_SET);
        }
    }
}

void SoundPlay(const char *fileName) 
{    
    unsigned int sampleCount;
    unsigned int frameRate;
    
    audiofile = SmallFS.open(fileName);
    audiofile.read(&sampleCount, sizeof(unsigned int));
    audiofile.read(&frameRate, sizeof(unsigned int));
    
    Serial.print("Sample Count = ");
    Serial.println(sampleCount);

    Serial.print("Frame Rate = ");
    Serial.println(frameRate); 
    
    Index = 0;
    PlayingSound = 1;
    AudioFillBuffer();
    currentData = audioBuffer.pop();

    TMR0CNT = 0;
    TMR0CMP = (CLK_FREQ/frameRate) - 1;
    
    // Enable timer 0
    TMR0CTL |= 1 << TCTLENA;
}

void _zpu_interrupt ()
{
    if ( TMR0CTL & (1 << TCTLIF)) {
        unsigned char sample, hasData = 1;
        
        if (Index >= currentData.count) {
            if (audioBuffer.hasData()) {
                Index = 0;
                currentData = audioBuffer.pop();
            } else {
                hasData = 0;
            }
        }
        
        if (hasData) {
            sample = currentData.sample[Index];
            DAC_SetOutput(sample);
	    Index++;
	} else {
            SoundOff();
            PlayingSound = 0;
        }
        
        /* Clear the interrupt flag on timer register */
        TMR0CTL &= ~(1 << TCTLIF);
        TMR0CNT = 0;
    }
}

void init_field(){
  //bloque, tipo, posx, posy, height, base, active
  init_block(&wall[0], 3, 40, 0, 28*4, 2, 1);           //wall above 
  init_block(&wall[1], 3, 40, windowy-12, 30*4, 2, 1);   //wall bottom
  init_block(&wall[2], 3, windowx-10, 0, 2, 27*4, 1);   //wall right
  init_block(&wall[3], 3, 40, 0,  2, 27*4, 1);           //wall left
  init_block(&player , 1, 52,  windowy-22, 6, 10 , 1);
  init_block(&door[0], 5, 48,  windowy-12, 14, 2 , 1);   //enter
  init_block(&door[1], 4, 130, 2,   14, 2 , 1);   //exit
  init_block(&lives[0], 7, 2, 0, 5, 5 , 1);
  init_block(&lives[1], 7, 8, 0, 5, 5 , 1);
  init_block(&lives[2], 7, 14, 0, 5, 5 , 1);
  
};

void render_field(){
  for(int x = 0; x < 5; x++)
    renderBlock(wall[x]);
  renderBlock(player);  
  renderBlock(door[0]);
  renderBlock(door[1]);  
  renderBlock(obstaculo);
  for(int x = 0; x < 3; x++)
    renderBlock(room[indexRoom].obstaculo[x]);
  for(int x = 0; x < vidas; x++)
    renderBlock(lives[x]);
};

void initMusic(){
  SoundInit();

    // Configure sigma-delta output pin.
    // GPIO 0 and GPIO 1 are the outputs
    pinMode(FPGA_J2_6, OUTPUT);
    pinModePPS(FPGA_J2_6, HIGH);
    outputPinForFunction(FPGA_J2_6, 0);
    
    pinMode(FPGA_J2_7, OUTPUT);
    pinModePPS(FPGA_J2_7, HIGH);
    outputPinForFunction(FPGA_J2_7, 0);
    
    if (SmallFS.begin()<0) {
      Serial.println("No SmalLFS found, aborting.");
        
        while(1) {};
    }
    contador = 0;
    SoundPlay("tetris.snd");
}

void setup(){  
  VGA.begin(VGAWISHBONESLOT(9),CHARMAPWISHBONESLOT(10));
  Serial.begin(9600);
  VGA.setBackgroundColor(BLACK);
  init_field();
  initMusic(); // Inicializa Todo lo Musica
  SoundPlay("tetris.snd"); // Hace Sonar la cancion del Menu
  init_game(&room[0],0,0);
  init_game(&room[1],0,1);
  init_game(&room[2],0,2);
  init_game(&room[3],1,0);
  init_game(&room[4],1,1);
  init_game(&room[5],1,2);
  init_game(&room[6],2,0);
  init_game(&room[7],2,1);
  init_game(&room[8],2,2);
};


void play(){
  VGA.clear();
  render_field();
  renderBlock(player);
  movePlayer();
  VGA.setBackgroundColor(WHITE);
  VGA.printtext(0, 10, room[indexRoom].label);
  VGA.printtext(0, 20, "Hint:");
  VGA.writeArea(0,30,7,7,hint1);
  VGA.setBackgroundColor(BLACK);
}

void resetLevel(){
  init_field();
  room[indexRoom].obstaculo[0].active = 1;
  room[indexRoom].obstaculo[1].active = 1;
  room[indexRoom].obstaculo[2].active = 1;
  win[0] = 0 ;
  win[1] = 0 ;
  win[2] = 0 ;
  win_cons = 0;
}

void movePlayer()
{
 if(vidas==0){
   state = 3;
   return;
 }
 
 if(digitalRead(btn_R) || digitalRead(FPGA_BTN_0))
  {
    if(!Collision(player,wall[2]))
      player.posX += 2;
  }
	
  if(digitalRead(btn_L) || digitalRead(FPGA_BTN_1))
  {
    if(!Collision(player,wall[3]))
      player.posX -= 2;
  }
 
  if(digitalRead(btn_U) || digitalRead(FPGA_BTN_2))
  {
    if(!Collision(player,wall[0]))
      player.posY -= 2;    
  }
  if(digitalRead(btn_D) || digitalRead(FPGA_BTN_3))
  {
    if(!Collision(player,wall[1]))
      player.posY += 2; 
  }
  
  //int index = (mundo * nivel) - 1;
  
  if(Interaction(player,room[indexRoom].obstaculo[0]) && digitalRead(btn_A)){
    win[win_cons] = 0;
    win_cons++;
    room[indexRoom].obstaculo[0].active = 0;
  }
  
  if(Interaction(player,room[indexRoom].obstaculo[1]) && digitalRead(btn_A)){
    win[win_cons] = 1;
    win_cons++;
    room[indexRoom].obstaculo[1].active = 0;
  }
  
  if(Interaction(player,room[indexRoom].obstaculo[2]) && digitalRead(btn_A)){
    win[win_cons] = 2;
    win_cons++;
    room[indexRoom].obstaculo[2].active = 0;
  }
  
  if(Interaction(player,door[1]) && digitalRead(btn_A) && win_cons >= 3){
    int cur = indexRoom;
    if((win [0] == room[cur].win[0]) && (win [1] == room[cur].win[1]) && (win [2] == room[cur].win[2])){
      if((mundo * nivel) == 3){
        state = 2;
      }else if(nivel == 3){
        mundo++;
        nivel = 1;
        indexRoom++;
      }else{
        nivel++;
        indexRoom++;
      }
      resetLevel();
    }else{
      resetLevel();
      vidas--;
    }
  }
};

void gano(){
  VGA.setBackgroundColor(WHITE);
  VGA.printtext(32, 20, "WIN");
  VGA.setBackgroundColor(BLACK);
};

void perdio(){
  VGA.setBackgroundColor(WHITE);
  VGA.printtext(32, 20, "LOOSE");
  VGA.setBackgroundColor(BLACK);
};

void render_page(void (*function)(),void (*game)(), int _fps ){
    if(d > _fps){
      VGA.clear();
      d=0;
      function();
      game();
    }
    d++;
    fps++;
}
void reinit_game(){
  d =0;
  fps = 0;
  mundo = 1;
  nivel = 1;
  vidas = 3;
  win[0] = 0 ;
  win[1] = 0 ;
  win[2] = 0 ;
  win_cons = 0;
  indexRoom = 0;
};

void menu(){
  VGA.setBackgroundColor(WHITE);
  VGA.printtext(32, 20, "Menu");
  VGA.printtext(0, 30, "El Juego consiste");
  VGA.printtext(0, 40, "en ver el hint y ");
  VGA.printtext(0, 50, "descubrir el orden");
  VGA.printtext(0, 60, "en el que se");
  VGA.printtext(0, 70, "debe interactuar");
  VGA.printtext(0, 80, "con el cuarto.");
  if(digitalRead(btn_A)){
    VGA.setBackgroundColor(BLACK);
    state = 1;
    SoundPlay("guiletheme.snd"); // Hace sonar la cancion del juego
  }
}
void nan(){
  return;
}

void loop()
{
  if (PlayingSound) {
    AudioFillBuffer();
  }
  //menu
  if(state == 0){
    render_page(&menu,&nan,100000);
  }
  //Game
  if(state == 1){
    render_page(&play,&nan,100000);
  }
  //win
  if(state == 2){
    render_page(&gano,&nan,100000);
    if(digitalRead(btn_A)){
      state = 0;
      reinit_game();
    }
  }
  //loose
  if(state == 3){
    render_page(&perdio,&nan,100000);
    if(digitalRead(btn_A)){
      state = 0;
      reinit_game();
    }
  }
};
