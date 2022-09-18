h50768
s 00000/00000/00006
d D 8.1 93/06/06 15:57:11 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00009/00006
d D 5.2 93/04/30 16:29:05 bostic 2 1
c integrate
e
s 00015/00000/00000
d D 5.1 93/04/30 13:30:02 muller 1 0
c date and time created 93/04/30 13:30:02 by muller
e
u
U
t
T
I 1
D 2
#       Copyright (c) 1991 Keith Muller.
#       Copyright (c) 1991 The Regents of the University of California.
#       All rights reserved.                                           
#                           
#       This code is derived from software contributed to Berkeley by
#       Keith Muller of the University of California, San Diego.     
#
E 2
#	%W% (Berkeley) %G%
D 2
#
#	Makefile for pr
E 2

PROG=	pr
SRCS=	pr.c egetopt.c

.include <bsd.prog.mk>
E 1
