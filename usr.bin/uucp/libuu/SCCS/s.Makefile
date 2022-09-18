h57428
s 00000/00000/00013
d D 8.1 93/06/06 22:10:10 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00012
d D 5.3 91/04/30 17:10:59 bostic 3 2
c don't build profiled version
e
s 00002/00000/00010
d D 5.2 91/03/21 15:31:20 bostic 2 1
c don't install the library anywhere
e
s 00010/00000/00000
d D 5.1 91/03/02 13:14:10 bostic 1 0
c date and time created 91/03/02 13:14:10 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

LIB=	uu
CFLAGS+=-I${.CURDIR}/../includes
SRCS=	anlwrk.c anyread.c cfgets.c chkpth.c cpmv.c expfile.c gename.c \
	getargs.c getprm.c getpwinfo.c gnxseq.c lastpart.c logent.c \
	mailst.c prefix.c setline.c subdir.c sysacct.c systat.c ulockf.c \
	uucpdefs.c uucpname.c versys.c xqt.c
I 3
NOPROFILE=noprofile
E 3

I 2
install:

E 2
.include <bsd.lib.mk>
E 1
