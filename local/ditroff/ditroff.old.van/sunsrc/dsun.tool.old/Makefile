CFLAGS=-O
YFLAGS=-d
DIR=

SOURCE = dev.h dsun.c graph.c fixpoint.c

NSFILES = dsun.tool.o handle_input.o page_control.o display.o init_page_buf.o init_screen.o  outc.o scroll.o graph.tool.o fixpoint.o

CFILES = dsun.tool.c  handle_input.c page_control.c display.c init_page_buf.c init_screen.c  outc.c scroll.c graph.tool.c fixpoint.c

all:	$(DIR)dsun.tool 

$(DIR)dsun.tool:	$(NSFILES)
	cc $(CFLAGS) -o $(DIR)dsun.tool $(NSFILES)  \
		-lm -lsuntool -lsunwindow -lpixrect 

dsun.o:	dev.h dsun.c

coryprint: 
	cat ${CFILES} | rsh cory -l marsh
dsun.tool.o:	defs.h dsun.tool.hs_h dev.h dsun.tool.c

fixpoint.o: fixpoint.h

graph.o: fixpoint.h

graph.tool.o: fixpoint.h

ctags:
	ctags ${CFILES}

list:
	lpr -p -Pucbvax $(SOURCE) makefile

clean:
	rm -f *.o
