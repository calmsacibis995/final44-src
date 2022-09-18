# Copyright (c) 1984, 19885, 1986, 1987 AT&T
# 	All Rights Reserved
# 
# THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.
# 
# The copyright notice above does not evidence any
# actual or intended publication of such source code.

# Version 1.1: December 1, 1987

YFLAGS = -d
CFLAGS = -g

OFILES = b.o main.o parse.o proctab.o tran.o lib.o run.o 

SOURCE = awk.h awk.g.y awk.lx.l b.c main.c maketab.c parse.c lib.c run.c tran.c

a.out:	awk.g.o awk.lx.o $(OFILES) $(ALLOC) awk.h
	cc $(CFLAGS) awk.g.o awk.lx.o $(OFILES) $(ALLOC)  -lm

$(OFILES) awk.lx.o:	awk.h prevy.tab.h 

awk.g.o:	awk.h

y.tab.h:	awk.g.o

prevy.tab.h:	y.tab.h
	-cmp -s y.tab.h prevy.tab.h || (cp y.tab.h prevy.tab.h; echo change maketab)

proctab.c:	maketab
	./maketab >proctab.c

maketab:	prevy.tab.h maketab.c
	cc maketab.c -o maketab

bundle:
	@bundle README $(SOURCE) makefile

profile:
	make 'CFLAGS=-p'

clean:
	rm -f a.out *.o y.tab.[ch] prevy.tab.h maketab proctab.c

install:	a.out
	cp a.out /usr/bin/awk
	strip /usr/bin/awk
