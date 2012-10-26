#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

extern cursedimage *img;
int loadi(const char *fn);
int savei(const char *fn);
void drawimglayer(void *where);
unsigned int getiw();
unsigned int getih();
char *getfn();
void fnreset();
void imgmove(char to);
int getoffsetx();
int getoffsety();

#endif // IMAGE_H_INCLUDED
