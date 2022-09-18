h63749
s 00000/00000/00011
d D 8.1 93/06/10 21:47:13 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 5.5 93/05/24 22:50:50 mckusick 5 4
c change location of stand => stand.att
e
s 00001/00001/00010
d D 5.4 92/12/26 14:34:53 hibler 4 3
c need -I..
e
s 00001/00001/00010
d D 5.3 92/10/11 10:23:28 bostic 3 2
c make kernel includes standard
e
s 00001/00000/00010
d D 5.2 92/08/14 09:25:13 hibler 2 1
c make sure include files come from the /sys tree where possible
e
s 00010/00000/00000
d D 5.1 91/05/08 21:56:14 bostic 1 0
c date and time created 91/05/08 21:56:14 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

LIB=	sa
SRCS=	bmap.c close.c dev.c getfile.c gets.c ioctl.c lseek.c open.c \
	printf.c read.c stat.c sys.c write.c
D 5
.PATH:	../../../stand
E 5
I 5
.PATH:	../../../stand.att
E 5
NOPROFILE=noprofile

.include <bsd.lib.mk>

I 2
D 3
CFLAGS+=-I../../.. -I..
E 3
I 3
D 4
CFLAGS+=-I../../..
E 4
I 4
CFLAGS+=-I.. -I../../..
E 4
E 3
E 2
E 1
