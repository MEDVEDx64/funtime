#include <cursedimage/cursedimage.h>
#include "image.h"
#include "brush.h"
#include "draw.h"
#include "gui.h"

cursedimage *screen = NULL;
unsigned int pcols = 0;
unsigned int plines = 0;
int ispanel = 1;

void draw()
{
    /* Allocating screen space if it isn`t allocated yet */
    if(screen == NULL) screen = cursed_blank(COLS,LINES);
    if(!pcols || !plines)
    {
        pcols = COLS;
        plines = LINES;
    }

    /* Checking for w/h changes */
    if(COLS != pcols || LINES != plines)
    {
        if(COLS && LINES)
        {
            cursed_setres(screen, COLS, LINES);
            pcols = COLS;
            plines = LINES;
        }
    }

    /* Drawing the layers */
    cursed_rect(screen, 0, 0, screen->width,
                screen->height, '~', COL_BW);
    drawimglayer(screen);
    drawbrushlayer(screen);
    if(ispanel) drawguilayer(screen);
    drawmesglayer(screen);
    cursed_flip(screen,0);
}

void togglepanel()
{
    ispanel =! ispanel;
}
