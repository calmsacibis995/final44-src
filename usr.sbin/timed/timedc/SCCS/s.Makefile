h62862
s 00000/00000/00011
d D 8.1 93/06/06 14:09:43 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 5.4 93/05/11 11:49:56 bostic 4 3
c put back in keywords ine
e
s 00002/00002/00009
d D 5.3 93/05/11 11:49:31 bostic 3 2
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00001/00000/00010
d D 5.2 90/05/11 16:12:10 bostic 2 1
c move to subdirectory
e
s 00010/00000/00000
d D 5.1 90/05/11 16:10:13 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
D 3
#	%W% (Berkeley) %G%
E 3
I 3
D 4
#	@(#)Makefile	5.2 (Berkeley) 5/11/90
E 4
I 4
#	%W% (Berkeley) %G%
E 4
E 3

PROG=	timedc
D 3
SRCS=	cmds.c cmdtab.c timedc.c byteorder.c measure.c cksum.${MACHINE}.c
E 3
I 3
SRCS=	cmds.c cmdtab.c timedc.c byteorder.c measure.c cksum.c
E 3
MAN8=	timedc.0
BINOWN=	root
BINMODE=4555
.PATH:	${.CURDIR}/../timed

I 2
.include "../../Makefile.inc"
E 2
.include <bsd.prog.mk>
E 1
