h29738
s 00000/00000/00010
d D 8.1 93/06/11 15:56:58 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00000/00000
d D 5.1 91/05/08 21:58:38 bostic 1 0
c date and time created 91/05/08 21:58:38 by bostic
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
.PATH:	../../../stand
NOPROFILE=noprofile

.include <bsd.lib.mk>

E 1
