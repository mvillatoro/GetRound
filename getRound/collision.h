struct block{
  int posX;
  int posY;
  int active;
  int type;
  int width;
  int height;
  unsigned char *image;
};

unsigned char player[]={
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

void renderBlock(block _block){
  if(_block.active)
     VGA.writeArea(_block.posX,_block.posY, _block.width, _block.height, _block.image);
};

int PointInRectangle(int x,int y,int x1,int y1,int x2,int y2){
        return ((( (x) >= (x1)) && ((y) >= (y1))) && (((x) <= (x2)) && ((y) <= (y2))));
};

int Collision(block s1, block s2)
{
        return (PointInRectangle(s1.posX+1,            s1.posY+1,               s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY + s2.height-1)  ||
                PointInRectangle(s1.posX + s1.width-1, s1.posY + s1.height-1,   s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY + s2.height-1)  ||
                PointInRectangle(s1.posX+1,            s1.posY + s1.height-1,   s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY +  s2.height-1) ||
                PointInRectangle(s1.posX + s1.width-1, s1.posY+1,               s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY +  s2.height-1));
};

int Collision(Sprite *s1, Sprite *s2)
{
	return (PointInRectangle(s1->x,           s1->y,            s2->x, s2->y, s2->x+s2->width, s2->y+s2->height) ||
		PointInRectangle(s1->x+s1->width, s1->y+s1->height, s2->x,s2->y,  s2->x+s2->width, s2->y+s2->height) ||
		PointInRectangle(s1->x,           s1->y+s1->height, s2->x, s2->y, s2->x+s2->width, s2->y+s2->height) ||
		PointInRectangle(s1->x+s1->width, s1->y, s2->x,     s2->y,        s2->x+s2->width, s2->y+s2->height));
}


void init_block(block* _block, int type, int x, int y, int width, int height, int active){
  _block->posX = x;
  _block->posY = y;
  switch(type){
    case 1 : _block->image = pixel; break;
    case 2 : _block->image = player; break;
    case 3 : _block->image = walls; break;
    default : break;
  }
  _block->active = active;
  _block->width = width;
  _block->height = height;
  _block->type = type;
}
