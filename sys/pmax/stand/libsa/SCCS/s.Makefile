h50146
s 00001/00001/00012
d D 8.2 94/02/16 12:16:47 bostic 3 2
c force -O2 since boot is too large otherwise
c From: ralphc@pyramid.com (Ralph Campbell)
e
s 00000/00000/00013
d D 8.1 93/06/10 23:30:59 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00000/00000
d D 7.1 92/11/15 16:52:19 ralph 1 0
c date and time created 92/11/15 16:52:19 by ralph
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

LIB=	sa
SRCS=	alloc.c bcopy.c bzero.c close.c dev.c disklabel.c getfile.c \
	ioctl.c lseek.c open.c read.c ufs.c write.c \
	callvec.c devopen.c getenv.c gets.c strcat.c strcmp.c strcpy.c

.PATH:	../../../stand
NOPROFILE=noprofile

.include <bsd.lib.mk>

D 3
CFLAGS+=-I../../..
E 3
I 3
CFLAGS=-O2 -I/sys
E 3
E 1
