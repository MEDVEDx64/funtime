#include <cursedimage/cursedimage.h>
#include <string.h>
#include "global.h"
#include "image.h"
#include "gui.h"

cursedimage *img = NULL;
char *cfname = NULL;

int offsetx = 0;
int offsety = 0;

int loadi(const char *fn)
{
    if(!strcmp(fn, ".")) return 0;
    cursedimage *tmp = cursed_imgload(fn);
    if(tmp == NULL)
    {
        pushmessage("Can`t read the file.", COL_WR);
        return 1;
    }

    cursed_imgfree(img);
    img = tmp;

    if(cfname != NULL)
    {
        free(cfname);
        cfname = NULL;
    }
    cfname = (char*)malloc(strlen(fn));
    strcpy(cfname, fn);

    pushmessage("Success.", COL_WG);
    return 0;
}

int savei(const char *fn)
{
    if(fn != NULL)
    {
        if(!strcmp(fn, ".")) return 0;
    }

    if(img == NULL)
    {
        pushmessage("Nothing to save!", COL_KY);
        return 1;
    }

    if(fn == NULL)
    {
        if(cursed_imgsave(cfname, img))
        {
            pushmessage("No file name specified.", COL_WR);
            return 1;
        }
    }
    else
    {
        if(cursed_imgsave(fn, img))
        {
            pushmessage("Can`t write the file.", COL_WR);
            return 1;
        }
        if(cfname != NULL)
        {
            free(cfname);
            cfname = NULL;
        }
        cfname = (char*)malloc(strlen(fn));
        strcpy(cfname, fn);
    }

    pushmessage("Success.", COL_WG);
    return 0;
}

void drawimglayer(void *where)
{
    cursed_blit(img, (cursedimage*)where, offsetx, offsety);
}

unsigned int getiw() { if(img != NULL) return img->width;  else return 0; }
unsigned int getih() { if(img != NULL) return img->height; else return 0; }

char *getfn() { return cfname; }

void fnreset()
{
    if(cfname != NULL) { free(cfname);
        cfname = NULL; }
}

void imgmove(char to)
{
    if(to&DIR_UP) offsety--;
    if(to&DIR_DOWN) offsety++;
    if(to&DIR_LEFT) offsetx--;
    if(to&DIR_RIGHT) offsetx++;
}

int getoffsetx() { return offsetx; }
int getoffsety() { return offsety; }
