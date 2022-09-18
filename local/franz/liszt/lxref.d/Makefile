# makefile for lxref - lisp cross reference program
# to compile the lxref program, jkfmacs is required in /usr/lib/lisp

lxref:  lxref.o
	mv lxref.o lxref

lxref.o: lxref.l
	liszt -xrq lxref 

install: lxref
	-rm -f /usr/ucb/lxref
	mv lxref /usr/ucb

clean:
	-rm  lxref.o lxref lxref.x
