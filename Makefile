OBJS=brush.o console.o draw.o gui.o image.o main.o
CFLAGS=-s -O2
LIBS=-lncurses -lcursedimage
funtime: $(OBJS)
	$(CC) $(LIBS) -o $@ $(OBJS)
