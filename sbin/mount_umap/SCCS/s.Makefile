h59996
s 00005/00001/00006
d D 8.3 94/03/27 11:50:07 bostic 6 5
c Jan-Simon Pendry's and my new mount code
e
s 00001/00001/00006
d D 8.2 94/01/12 13:55:22 pendry 5 4
c fix CFLAGS
e
s 00000/00000/00007
d D 8.1 93/06/05 11:04:45 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00006
d D 5.3 92/07/12 15:56:23 bostic 3 2
c put in key words
e
s 00002/00002/00005
d D 5.2 92/07/11 15:27:47 heideman 2 1
c minor changes
e
s 00007/00000/00000
d D 5.1 92/07/10 16:54:55 heideman 1 0
c date and time created 92/07/10 16:54:55 by heideman
e
u
U
t
T
I 1
D 3
#	@(#)Makefile	1.1 (Berkeley) 7/9/92
E 3
I 3
#	%W% (Berkeley) %G%
E 3

D 5
CFLAGS=	-I/sys
E 5
I 5
D 6
CFLAGS+=-I/sys
E 6
E 5
D 2
PROG=	mount_null
MAN8=	mount_null.0
E 2
I 2
PROG=	mount_umap
I 6
SRCS=	mount_umap.c getmntopts.c
E 6
MAN8=	mount_umap.0
I 6

MOUNT=	${.CURDIR}/../mount
CFLAGS+= -I/sys -I${MOUNT}
.PATH:	${MOUNT}
E 6
E 2

.include <bsd.prog.mk>
E 1
