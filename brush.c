#include <cursedimage/cursedimage.h>
#include "global.h"
#include "brush.h"
#include "image.h"

int brushx = 0;
int brushy = 0;

int brush_getx() {return brushx;}
int brush_gety() {return brushy;}

#define D_STILL 15

void brushmove(char to)
{
    if(img == NULL) return;
    if(to == DIR_UP && brushy) brushy--;
    if(to == DIR_DOWN && brushy < getih()-1) brushy++;
    if(to == DIR_LEFT && brushx) brushx--;
    if(to == DIR_RIGHT && brushx < getiw()-1) brushx++;
}

void drawbrushlayer(void *where)
{
    if(img == NULL) return;
    //cursedimage *wh = where;
    unsigned int addr = cursed_get_addr(brushx, brushy, img->width);
    cursed_img_modify((cursedimage*)where, getoffsetx()+brush_getx(), getoffsety()+brush_gety(),
                      img->image[addr].sym, img->image[addr].colorpair|COL_KW);
}

cursedchar cbrush = { 0, 'X' };

void setbrushcol(char col)
{
    cbrush.colorpair = col;
}

void setbrushsym(char sym)
{
    cbrush.sym = sym;
}

cursedchar getbrush() { return cbrush; }

void brushcheck(void *where)
{
    cursedimage *wh = where;
    if(where == NULL)
    {
        brushx = 0;
        brushy = 0;
        return;
    }
    if(brushx >= wh->width) brushx = wh->width-1;
    if(brushy >= wh->height) brushy = wh->height-1;
}
