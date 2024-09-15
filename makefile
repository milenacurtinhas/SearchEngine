CC = gcc
CFLAGS = -I./include -Wall -O2 -g
LIBS := -lm
OBJDIR = objects
SRCDIR = src

OBJECTS = $(OBJDIR)/reading.o $(OBJDIR)/TST.o $(OBJDIR)/graphTST.o
ALL_OBJECTS = $(shell find . -type f -name "*.o" -print) 

all: trab3

$(OBJDIR):
	mkdir -p $(OBJDIR)
	
trab3: $(OBJDIR) $(OBJECTS) client.c
	$(CC) $(CFLAGS) -o trab3 client.c $(OBJECTS) $(LIBS)

$(OBJDIR)/reading.o: $(SRCDIR)/reading.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/reading.c -o $(OBJDIR)/reading.o

$(OBJDIR)/TST.o: $(SRCDIR)/TST.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/TST.c -o $(OBJDIR)/TST.o

$(OBJDIR)/graphTST.o: $(SRCDIR)/graphTST.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/graphTST.c -o $(OBJDIR)/graphTST.o

clean:
	rm -f trab3 $(OBJDIR)/*.o 
	rm -rf $(OBJDIR)
	rm -f *.bin
	rm -f *.txt