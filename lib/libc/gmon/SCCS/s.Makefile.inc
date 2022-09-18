h36927
s 00000/00000/00011
d D 8.1 93/06/04 12:11:08 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00010
d D 5.2 93/06/01 23:54:14 bostic 2 1
c move moncontrol.3 here from man/man3/
e
s 00010/00000/00000
d D 5.1 92/07/10 17:24:06 mckusick 1 0
c date and time created 92/07/10 17:24:06 by mckusick
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

# gmon sources
.PATH: ${.CURDIR}/gmon

SRCS+=	gmon.c mcount.c
I 2
MAN3+=	moncontrol.0
E 2

# mcount cannot be compiled with profiling
mcount.po: mcount.o
	cp mcount.o mcount.po
E 1
