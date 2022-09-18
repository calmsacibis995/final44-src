h53049
s 00001/00001/00018
d D 8.3 95/04/28 17:19:11 christos 6 5
c removed util.c
e
s 00008/00003/00011
d D 8.2 95/04/28 17:08:34 christos 5 4
c Updated to the latest version from the NetBSD source
e
s 00000/00000/00014
d D 8.1 93/06/06 15:17:50 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00013
d D 5.3 93/05/24 14:06:53 bostic 3 2
c add for.c
e
s 00001/00001/00013
d D 5.2 90/12/28 18:06:50 bostic 2 1
c replace hash.c; speedup/cleanup from Chris Torek
e
s 00014/00000/00000
d D 5.1 90/05/11 14:23:43 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
D 5
#	%W% (Berkeley) %G%
E 5
I 5
#	from: @(#)Makefile	5.2 (Berkeley) 12/28/90
#	$Id: Makefile,v 1.6 1994/06/30 05:33:39 cgd Exp $
E 5

PROG=	make
D 5
CFLAGS+=-I${.CURDIR}
E 5
I 5
CFLAGS+= -I${.CURDIR} -DPOSIX
E 5
D 2
SRCS=	arch.c buf.c compat.c cond.c dir.c hash.c job.c list.c main.c \
E 2
I 2
D 3
SRCS=	arch.c buf.c compat.c cond.c dir.c hash.c job.c main.c \
E 3
I 3
SRCS=	arch.c buf.c compat.c cond.c dir.c for.c hash.c job.c main.c \
E 3
E 2
D 5
	make.c parse.c str.c suff.c targ.c var.c
E 5
I 5
D 6
	make.c parse.c str.c suff.c targ.c var.c util.c
E 6
I 6
	make.c parse.c str.c suff.c targ.c var.c
E 6
E 5
SRCS+=	lstAppend.c lstAtEnd.c lstAtFront.c lstClose.c lstConcat.c \
	lstDatum.c lstDeQueue.c lstDestroy.c lstDupl.c lstEnQueue.c \
	lstFind.c lstFindFrom.c lstFirst.c lstForEach.c lstForEachFrom.c \
	lstInit.c lstInsert.c lstIsAtEnd.c lstIsEmpty.c lstLast.c \
	lstMember.c lstNext.c lstOpen.c lstRemove.c lstReplace.c lstSucc.c
.PATH:	${.CURDIR}/lst.lib
I 5

.if make(install)
SUBDIR+= PSD.doc
.endif
E 5

.include <bsd.prog.mk>
E 1
