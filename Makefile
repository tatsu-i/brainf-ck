CC            = gcc
CFLAGS        = -g #-O4 -Wall -I/usr/local/include
DEST          = /usr/local/bin
LDFLAGS       = #-L/usr/local/lib
LIBS          = -lm
OBJS          = bf.o
PROGRAM       = bf

all:            $(PROGRAM)

$(PROGRAM):     $(OBJS)
	                $(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

clean:;         rm -f *.o *~ $(PROGRAM)

install:        $(PROGRAM)
	                install -s $(PROGRAM) $(DEST)

