/**

    Funtime
    Cursed Image pseudo-graphic editor
    MEDVEDx64, 2012.10.26
    GPL.

**/

#include <cursedimage/cursedimage.h>
#include "console.h"
#include "global.h"
#include "image.h"
#include "brush.h"
#include "draw.h"
#include "gui.h"

int isrunning = 1;

#define IMGCHECK if(img == NULL) break;

int main(int argc, char *argv[])
{
    if(cursed_init(0)) return 1;
    if(argc > 1) loadi(argv[1]);

    cursedimage *buffer = NULL;
    int manual = 0;

    /* Main loop */
    while(isrunning)
    {
        /* Drawing */
        draw();

        /* Manual input handling */
        if(manual)
        {
            manual = 0;
            img->image[cursed_get_addr(
                brush_getx(), brush_gety(), img->width)].sym = getch();
            continue;
        }

        /* Keypress proccessing */
        char ch = getch();
        switch(ch)
        {
            case 10: IMGCHECK manual = 1; pushmessage("Press a key...", COL_WB); break; /** return **/
            case 113: isrunning = 0; break; /** q **/
            case 3: brushmove(DIR_UP); break; /** up arrow **/
            case 2: brushmove(DIR_DOWN); break; /** down arrow **/
            case 4: brushmove(DIR_LEFT); break; /** left arrow **/
            case 5: brushmove(DIR_RIGHT); break; /** right arrow **/
            case 81: imgmove(DIR_UP); break; /** shift + up arrow **/
            case 80: imgmove(DIR_DOWN); break; /** shift + down arrow **/
            case -119: imgmove(DIR_LEFT); break; /** shift + left arrow **/
            case -110: imgmove(DIR_RIGHT); break; /** shift + right arrow **/
            case 105: /** i **/
                constart("Open a file:");
                loadi(conget());
                break;
            case 111: /** o **/
                constart("Save to file:");
                savei(conget());
                break;
            case 108: savei(NULL); break; /** l **/
            /* Painting */
            case 32: cursed_img_modify(img, brush_getx(), /** Space **/
                        brush_gety(), getbrush().sym, getbrush().colorpair); break;
            case 99: IMGCHECK img->image[cursed_get_addr(brush_getx(), brush_gety(), /** c **/
                                img->width)].colorpair = getbrush().colorpair; break;
            case 118: IMGCHECK img->image[cursed_get_addr(brush_getx(), brush_gety(), /** v **/
                                img->width)].sym = getbrush().sym; break;
            /* Color/symbol picking */
            case 122: constart("Input brush symbol:"); /** z ***/
                        setbrushsym(*conget());
                        break;
            case 120: constart("Input colorpair:"); /** x **/
                        setbrushcol(atoi(conget()));
                        break;
            /* Resolution setup */
            case 115: constart("Set up a new resolution (w):"); /** s **/
                        unsigned int nw = atoi(conget());
                        constart("Set up a new resolution (h):");
                        unsigned int nh = atoi(conget());
                        if(img == NULL) img = cursed_blank(nw, nh); else
                        cursed_setres(img, nw, nh);
                        break;
            /* Rectangle */
            case 114: IMGCHECK constart("Rectangle (w):"); /** r **/
                        unsigned int rw = atoi(conget());
                        constart("Rectangle (h):");
                        unsigned int rh = atoi(conget());
                        cursed_rect(img, brush_getx(), brush_gety(),
                                    rw, rh, getbrush().sym, getbrush().colorpair); break;
            case 116: IMGCHECK constart("Input text (without spaces or tabs):"); /** t **/
                        int i; for(i = 0; i < strlen(conget()); i++)
                        {
                            unsigned int addr = cursed_get_addr(
                                brush_getx(), brush_gety(), img->width);
                            if(addr+i < CURSED_BODY_CHARS(img))
                                img->image[addr+i].sym = conget()[i];
                        }
                        break;
            /* Panel visibility toggling */
            case 112: togglepanel(); break; /** p **/
            /* New image */
            case 110: cursed_imgfree(img); /** n **/
                        fnreset(); break;
            /* Cut/copy/paste features */
            case 49: IMGCHECK constart("Area to be cutted (w):"); /** 1 **/
                        rw = atoi(conget());
                        constart("Area to be cutted (h):");
                        rh = atoi(conget());
                        cursed_imgfree(buffer);
                        buffer = cursed_blank(rw,rh);
                        cursed_blit_rect(img,buffer,0,0,brush_getx(),brush_gety(),rw,rh);
                        cursed_rect(img,brush_getx(),brush_gety(),rw,rh,
                                    CURSED_DEFAULT_SYM,CURSED_DEFAULT_COLORPAIR);
                        pushmessage("Cut", COL_WB);
                        break;
            case 50: IMGCHECK constart("Area to be copied (w):"); /** 2 **/
                        rw = atoi(conget());
                        constart("Area to be copied (h):");
                        rh = atoi(conget());
                        cursed_imgfree(buffer);
                        buffer = cursed_blank(rw,rh);
                        cursed_blit_rect(img,buffer,0,0,brush_getx(),brush_gety(),rw,rh);
                        pushmessage("Copy", COL_WB);
                        break;
            case 51: IMGCHECK
                        if(buffer == NULL)
                        {
                            pushmessage("Nothing to paste.", COL_KY);
                            break;
                        }
                        cursed_blit(buffer,img,brush_getx(),brush_gety());
                        pushmessage("Paste", COL_WB);
                        break;
            /* Erasing */
            case 101: cursed_img_modify(img, brush_getx(), /** e **/
                            brush_gety(), CURSED_DEFAULT_SYM, CURSED_DEFAULT_COLORPAIR); break;
        }

        brushcheck(img);
    }

    cursed_quit();
    cursed_imgfree(buffer);
    cursed_imgfree(img);
    return 0;
}
