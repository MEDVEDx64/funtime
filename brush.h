#ifndef BRUSH_H_INCLUDED
#define BRUSH_H_INCLUDED

#include <cursedimage/cursedimage_file.h>

void brushmove(char to);
void drawbrushlayer(void *where);
int brush_getx();
int brush_gety();
void setbrushcol(char col);
void setbrushsym(char sym);
cursedchar getbrush();
void brushcheck(void *where);

#endif // BRUSH_H_INCLUDED
