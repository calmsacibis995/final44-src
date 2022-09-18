BINDIR	= /usr/local/bin
EQN	= deqn
DEVDIR	= "/usr/local/libdata/ditroff_font"
CFLAGS	= -O '-DDEVDIR=$(DEVDIR)'
YFLAGS	= -d

SOURCE	= e.y e.h diacrit.c eqnbox.c font.c fromto.c funny.c glob.c integral.c \
	io.c lex.c lookup.c mark.c matrix.c move.c over.c paren.c pile.c \
	shift.c size.c sqrt.c text.c

FILES	= e.o diacrit.o eqnbox.o font.o fromto.o funny.o glob.o integral.o \
	io.o lex.o lookup.o mark.o matrix.o move.o over.o paren.o \
	pile.o shift.o size.o sqrt.o text.o

eqn:	$(FILES)
	cc -n -o eqn $(CFLAGS) $(FILES) 

e.def e.o:	e.y
	yacc $(YFLAGS) e.y
	cc $(CFLAGS) -c y.tab.c
	/bin/rm y.tab.c
	mv y.tab.o e.o
	mv y.tab.h e.def

$(FILES):	e.h e.def dev.h

list:
	@pr TODO $(SOURCE) makefile

install:	$(BINDIR)/$(EQN)

$(BINDIR)/$(EQN):	eqn
	install -c -s eqn $(BINDIR)/$(EQN)

lint:
	lint -spb *.c

clean:
	/bin/rm -f *.o make.out eqn
