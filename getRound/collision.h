struct block{
  int posX;
  int posY;
  int active;
  int type;
  int width;
  int height;
  unsigned char *image;
};

struct game{
  int mundo;
  int nivel;
  struct block obstaculo[3];
  unsigned char *hint; 
  char *label;
  int win [3];
};

unsigned char enter_Door[]={
  RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
  RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED
};

unsigned char exit_Door[]={
  GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
  GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN
};

unsigned char player1[]={
BLACK,BLACK,WHITE,WHITE,BLACK,
BLACK,BLACK,BLACK,WHITE,BLACK,
BLACK,BLACK,BLACK,BLACK,WHITE,
WHITE,BLACK,BLACK,BLACK,WHITE,
WHITE,WHITE,WHITE,BLACK,WHITE,
BLACK,WHITE,WHITE,BLACK,WHITE,
BLACK,BLACK,WHITE,WHITE,BLACK,
BLACK,BLACK,BLACK,WHITE,WHITE,
BLACK,BLACK,BLACK,WHITE,BLACK,
BLACK,WHITE,BLACK,BLACK,WHITE,
BLACK,BLACK,WHITE,BLACK,BLACK,
WHITE,BLACK,BLACK,WHITE,BLACK
};

unsigned char heart[]={
BLACK,RED,BLACK,RED,BLACK,
RED,BLACK,RED,BLACK,RED,
RED,BLACK,BLACK,BLACK,RED,
BLACK,RED,BLACK,RED,BLACK,
BLACK,BLACK,RED,BLACK,BLACK
};

unsigned char pixel[]={
BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,
BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,
BLACK,WHITE,WHITE,WHITE,WHITE,BLACK,
WHITE,BLACK,WHITE,WHITE,BLACK,WHITE,
BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,
BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,
BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,
BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,
BLACK,WHITE,BLACK,BLACK,WHITE,BLACK
};

unsigned char tottem1[]={
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLUE,BLACK,BLUE,BLUE,BLACK,BLUE,
BLACK,BLUE,BLUE,BLUE,BLUE,BLACK,
BLACK,BLACK,CYAN,CYAN,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLUE,BLACK,BLUE,BLUE,BLACK,BLUE,
BLACK,BLUE,BLUE,BLUE,BLUE,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK
};

unsigned char tottem2[]={
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLUE,BLACK,BLUE,BLUE,BLACK,BLUE,
BLACK,BLUE,BLUE,BLUE,BLUE,BLACK,
BLACK,BLACK,GREEN,GREEN,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLUE,BLACK,BLUE,BLUE,BLACK,BLUE,
BLACK,BLUE,BLUE,BLUE,BLUE,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK
};

unsigned char tottem3[]={
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLUE,BLACK,BLUE,BLUE,BLACK,BLUE,
BLACK,BLUE,BLUE,BLUE,BLUE,BLACK,
BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLUE,BLACK,BLUE,BLUE,BLACK,BLUE,
BLACK,BLUE,BLUE,BLUE,BLUE,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK,
BLACK,BLACK,BLUE,BLUE,BLACK,BLACK
};

unsigned char walls[] ={
WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,
WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,
WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,
WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,
WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,
WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,
WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,
WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,
WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,
WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE,WHITE, WHITE

};
unsigned char hint1[]={
  BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
  BLACK,CYAN,BLACK,GREEN,BLACK,WHITE,BLACK,
  BLACK,CYAN,BLACK,GREEN,BLACK,WHITE,BLACK,
  BLACK,CYAN,BLACK,GREEN,BLACK,WHITE,BLACK,
  BLACK,CYAN,BLACK,GREEN,BLACK,WHITE,BLACK,
  BLACK,CYAN,BLACK,GREEN,BLACK,WHITE,BLACK,
  BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK
};

void renderBlock(block _block){
  if(_block.active)
     VGA.writeArea(_block.posX,_block.posY, _block.width, _block.height, _block.image);
};

int PointInRectangle(int x,int y,int x1,int y1,int x2,int y2){
        return ((( (x) >= (x1)) && ((y) >= (y1))) && (((x) <= (x2)) && ((y) <= (y2))));
};


void print_text(int x, int y, char * msg){
      VGA.setColor(WHITE);
      VGA.printtext(x, y, msg);
}

void print_number(int x, int y, int msg){
      char snum[5];
      itoa (msg, snum, 10);
      VGA.setColor(WHITE);
      VGA.printtext(x, y, snum);
}

int Interaction(block s1, block s2)
{
        return (PointInRectangle(s1.posX+1,            s1.posY+1,               s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY + s2.height-1)  ||
                PointInRectangle(s1.posX + s1.width-1, s1.posY + s1.height-1,   s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY + s2.height-1)  ||
                PointInRectangle(s1.posX+1,            s1.posY + s1.height-1,   s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY +  s2.height-1) ||
                PointInRectangle(s1.posX + s1.width-1, s1.posY+1,               s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY +  s2.height-1));
};

int Collision(block s1, block s2)
{
	return (PointInRectangle(s1.posX,           s1.posY,            s2.posX, s2.posY, s2.posX+s2.width, s2.posY+s2.height) ||
		PointInRectangle(s1.posX+s1.width,  s1.posY+s1.height,  s2.posX, s2.posY, s2.posX+s2.width, s2.posY+s2.height) ||
		PointInRectangle(s1.posX,           s1.posY+s1.height,  s2.posX, s2.posY, s2.posX+s2.width, s2.posY+s2.height) ||
		PointInRectangle(s1.posX+s1.width,  s1.posY,            s2.posX, s2.posY, s2.posX+s2.width, s2.posY+s2.height));
}


void init_block(block* _block, int type, int x, int y, int width, int height, int active){
  _block->posX = x;
  _block->posY = y;
  switch(type){
    case 1 : _block->image = player1; break;
    case 2 : _block->image = pixel; break;
    case 3 : _block->image = walls; break;
    case 4 : _block->image = exit_Door; break;
    case 5 : _block->image = enter_Door; break;
    case 6 : _block->image = tottem1; break;
    case 7 : _block->image = heart; break;
    case 8 : _block->image = tottem2; break;
    case 9 : _block->image = tottem3; break;
    default : break;
  }
  _block->active = active;
  _block->width = width;
  _block->height = height;
  _block->type = type;
}

void init_game(game* _game, int mundo, int nivel){
 _game->mundo = mundo;
 _game->nivel = nivel;
 switch(mundo){
   case 0:
     if(nivel == 0){
       _game->label = "1-1";
       _game->hint = hint1;
       _game->win[0] = 1;
       _game->win[1] = 2;
       _game->win[2] = 0;
       init_block(&_game->obstaculo[0], 6, 60, 30, 6, 14 , 1);
       init_block(&_game->obstaculo[1], 8, 90, 80, 6, 14 , 1);
       init_block(&_game->obstaculo[2], 9, 120, 50, 6, 14 , 1);
       
     }else if(nivel == 1){
       _game->label = "1-2";
       _game->hint = hint1;
       _game->win[0] = 2;
       _game->win[1] = 0;
       _game->win[2] = 1;
       init_block(&_game->obstaculo[0], 6, 60, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[1], 8, 90, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[2], 9, 120, 26, 6, 14 , 1);
       
     }else{
       _game->label = "1-3";
       _game->hint = hint1;
       _game->win[0] = 2;
       _game->win[1] = 1;
       _game->win[2] = 0;
       init_block(&_game->obstaculo[0], 6, 40, 20, 6, 14 , 1);
       init_block(&_game->obstaculo[1], 8, 75, 50, 6, 14 , 1);
       init_block(&_game->obstaculo[2], 9, 100, 90, 6, 14 , 1);
     }
     break;
   case 1:
     if(nivel == 0){
       _game->label = "2-1";
       _game->hint = hint1;
       _game->win[0] = 2;
       _game->win[1] = 0;
       _game->win[2] = 1;
       init_block(&_game->obstaculo[0], 6, 60, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[1], 8, 90, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[2], 9, 120, 26, 6, 14 , 1);
     }else if(nivel == 1){
       _game->label = "2-2";
       _game->hint = hint1;
       _game->win[0] = 2;
       _game->win[1] = 0;
       _game->win[2] = 1;
       init_block(&_game->obstaculo[0], 6, 60, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[1], 8, 90, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[2], 9, 120, 26, 6, 14 , 1);
     }else{
       _game->label = "2-3";
       _game->hint = hint1;
       _game->win[0] = 2;
       _game->win[1] = 0;
       _game->win[2] = 1;
       init_block(&_game->obstaculo[0], 6, 60, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[1], 8, 90, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[2], 9, 120, 26, 6, 14 , 1);
     }
     break;
   case 2:
     if(nivel == 0){
       _game->label = "3-1";
       _game->hint = hint1;
       _game->win[0] = 2;
       _game->win[1] = 0;
       _game->win[2] = 1;
       init_block(&_game->obstaculo[0], 6, 60, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[1], 8, 90, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[2], 9, 120, 26, 6, 14 , 1);
     }else if(nivel == 1){
       _game->label = "3-2";
       _game->hint = hint1;
       _game->win[0] = 2;
       _game->win[1] = 0;
       _game->win[2] = 1;
       init_block(&_game->obstaculo[0], 6, 60, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[1], 8, 90, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[2], 9, 120, 26, 6, 14 , 1);
     }else{
       _game->label = "3-3";
       _game->hint = hint1;
       _game->win[0] = 2;
       _game->win[1] = 0;
       _game->win[2] = 1;
       init_block(&_game->obstaculo[0], 6, 60, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[1], 8, 90, 26, 6, 14 , 1);
       init_block(&_game->obstaculo[2], 9, 120, 26, 6, 14 , 1);
     }
     break;
 }
};


