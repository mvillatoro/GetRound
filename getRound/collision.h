
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
  WHITE,WHITE,
  WHITE,WHITE
};

void init_block(block* _block, int type, int x, int y, int width, int height){
  _block->posX = x;
  _block->posY = y;
  _block->image = player;
  _block->active = 1;
  _block->width = width;
  _block->height = height;
  _block->type = type;
}
int PointInRectangle(int x,int y,int x1,int y1,int x2,int y2){
        return ((( (x) >= (x1)) && ((y) >= (y1))) && (((x) <= (x2)) && ((y) <= (y2))));
}
int Collision(block s1, block s2)
{
        return (PointInRectangle(s1.posX+1,            s1.posY+1,               s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY + s2.height-1)  ||
                PointInRectangle(s1.posX + s1.width-1, s1.posY + s1.height-1,   s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY + s2.height-1)  ||
                PointInRectangle(s1.posX+1,            s1.posY + s1.height-1,   s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY +  s2.height-1) ||
                PointInRectangle(s1.posX + s1.width-1, s1.posY+1,               s2.posX+1, s2.posY+1,    s2.posX + s2.width-1,             s2.posY +  s2.height-1));
}
void init_block(block* _block, int type, int x, int y, int width, int height, int active){
  _block->posX = x;
  _block->posY = y;
  switch(type){
    case 1 : _block->image = pixel; break;
    case 2 : _block->image = manzana; break;
    case 3 : _block->image = obstaculo; break;
    default : break;
  }
  _block->active = active;
  _block->width = width;
  _block->height = height;
  _block->type = type;
}
