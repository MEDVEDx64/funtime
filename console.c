#include <malloc.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"

#define CONMAX 0x1000

char *constr = NULL;

void constart(const char *mesg)
{
    if(constr != NULL)
    {
        free(constr);
        constr = NULL;
    }
    constr = (char*)malloc(CONMAX);
    def_prog_mode();
    endwin();
    if(mesg != NULL) printf("%s\n", mesg);
    fflush(stdout);
    if(scanf("%s", constr));
    reset_prog_mode();
}

char *conget()
{
    return constr;
}

void confree()
{
    if(constr != NULL)
        free(constr);
}
