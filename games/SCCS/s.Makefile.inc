h21716
s 00000/00000/00009
d D 8.1 93/05/31 15:52:49 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00000
d D 5.1 90/05/11 12:59:21 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

BINOWN?=	games
.if defined(HIDEGAME)
BINDIR?=	/usr/games/hide
BINMODE?=	4700
.else
BINDIR?=	/usr/games
.endif
E 1
