h27773
s 00000/00000/00011
d D 8.1 93/06/04 12:58:15 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00000/00000
d D 5.1 92/06/02 13:39:04 bostic 1 0
c date and time created 92/06/02 13:39:04 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

all: mul divrem

MUL=	mul.c ../muldi3.c
mul: ${MUL}
	gcc -g -DSPARC_XXX ${MUL} -o $@

DIVREM=	divrem.c ../qdivrem.c
divrem: ${DIVREM}
	gcc -g -DSPARC_XXX ${DIVREM} -o $@
E 1
