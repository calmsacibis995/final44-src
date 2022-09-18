CFLAGS=-O
YFLAGS=-d
DIR=

SOURCE = dsun.c graph.c fixpoint.c

HFILES = defs.h dev.h fixpoint.h framebuf.h

NSFILES = dsun.tool.o handle_input.o page_control.o display.o init_page_buf.o init_screen.o  outc.o scroll.o graph.tool.o fixpoint.o

CFILES = display.c dsun.tool.c fixpoint.c graph.tool.c handle_input.c \
	init_page_buf.c init_screen.c  outc.c page_control.c scroll.c 

all:	$(DIR)dsun.tool 

$(DIR)dsun.tool:	$(NSFILES)
	cc $(CFLAGS) -o $(DIR)dsun.tool $(NSFILES)  \
		-lm -lsuntool -lsunwindow -lpixrect 

dsun.o:	dev.h dsun.c

print: 
	lpr $(HFILES) ${CFILES} 

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
