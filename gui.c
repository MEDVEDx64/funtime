#include <cursedimage/cursedimage.h>
#include <string.h>
#include <stdio.h>
#include "gui.h"
#include "image.h"
#include "brush.h"
#include "global.h"

#define PANEL_H 2
#define PANEL_COLOR COL_KW
#define COORD_TEXT_COLOR COL_WB
#define COORD_DIGIT_COLOR COL_KY
#define COORD_XOFFSET 2

void drawguilayer(void *where)
{
    cursedimage *_where = (cursedimage*)where;
    /* Draw a background panel */
    cursed_rect(_where, 0, _where->height-PANEL_H,
                _where->width, PANEL_H, CURSED_DEFAULT_SYM, PANEL_COLOR);
    /* string to be drawn */
    char imgnfo[0x1000];
    sprintf(imgnfo, "X:%d Y:%d W:%d H:%d", brush_getx(), brush_gety(),
            getiw(), getih());
    unsigned int len = strlen(imgnfo);
    /* Drawing the text */
    unsigned int i;
    for(i = 0; i < len; i++)
    {
        unsigned int addr = cursed_get_addr(
                _where->width-len-COORD_XOFFSET, _where->height-(PANEL_H-1), _where->width)+i;
        _where->image[addr].sym = imgnfo[i];
        /* ..with different colors! */
        if(imgnfo[i] >= '0' && imgnfo[i] <= '9')
            _where->image[addr].colorpair = COORD_DIGIT_COLOR;
        else if(imgnfo[i] == ' ')
            _where->image[addr].colorpair = PANEL_COLOR;
        else
            _where->image[addr].colorpair = COORD_TEXT_COLOR;
    }

    /* Current file name */
    if(getfn() != NULL)
    {
        for(i = 0; i < strlen(getfn()); i++)
            _where->image[cursed_get_addr(i, _where->height-PANEL_H,
                                _where->width)].sym = getfn()[i];
    }

    /* Current brush */
    _where->image[CURSED_BODY_CHARS(_where)-1] = getbrush();

    char ftver[] = "Funtime "FUNTIME_VERSION;
    for(i = 0; i < strlen(ftver); i++)
        _where->image[i+cursed_get_addr(
            0, _where->height-1, _where->width)].sym = ftver[i];
}

char *mesg = NULL;
char msgcol = COL_WB;

void pushmessage(const char *str, char col)
{
    mesg = (char*)malloc(strlen(str)+1);
    strcpy(mesg, str);
    msgcol = col;
}

void drawmesglayer(void *where)
{
    if(mesg == NULL) return;
    cursedimage *wh = where;
    unsigned int addr = cursed_get_addr(
        wh->width-strlen(mesg), wh->height-2, wh->width);
    int i; for (i = 0; i < strlen(mesg); i++)
    {
        wh->image[i+addr].colorpair = msgcol;
        wh->image[i+addr].sym = mesg[i];
    }

    if(mesg != NULL)
    {
        free(mesg);
        mesg = NULL;
    }
}
