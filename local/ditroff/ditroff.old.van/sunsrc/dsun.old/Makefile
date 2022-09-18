CFLAGS=-O
YFLAGS=-d
DIR=

SOURCE = dev.h dsun.c graph.c fixpoint.c

SFILES = dsun.o graph.o fixpoint.o
NSFILES = dsun.tool.o graph.tool.o fixpoint.o

all:	$(DIR)dsun $(DIR)dsun.tool

$(DIR)dsun.tool:	$(NSFILES)
	cc $(CFLAGS) -o $(DIR)dsun.tool $(NSFILES) -lm -lsuntool -lsunwindow -lpixrect libcore.a

$(DIR)dsun:	$(SFILES)
	cc $(CFLAGS) -o $(DIR)dsun $(SFILES) -lm libcore.a

dsun.o:	dev.h dsun.c

dsun.tool.o:	dev.h dsun.tool.c

fixpoint.o: fixpoint.h

graph.o: fixpoint.h

graph.tool.o: fixpoint.h

list:
	lpr -p -Pucbvax $(SOURCE) makefile

clean:
	rm -f *.o
