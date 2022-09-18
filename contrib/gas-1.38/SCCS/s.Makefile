h61973
s 00001/00000/00016
d D 6.3 93/05/26 10:06:32 bostic 3 2
c move into /usr/src/contrib, but still install in /usr/bin
e
s 00001/00000/00015
d D 6.2 92/07/22 12:24:09 bostic 2 1
c no man page
e
s 00015/00000/00000
d D 6.1 91/03/03 00:37:47 donn 1 0
c date and time created 91/03/03 00:37:47 by donn
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=		as
SRCS=		app.c append.c as.c atof-generic.c bignum-copy.c \
		expr.c flonum-const.c flonum-copy.c flonum-mult.c \
		frags.c hash.c hex-value.c input-file.c input-scrub.c \
		messages.c obstack.c output-file.c read.c subsegs.c \
		symbols.c version.c write.c xmalloc.c xrealloc.c
CFLAGS+=	-I$(.CURDIR) -I$(.CURDIR)/config \
		-DSIGTY=void -Derror=as_fatal
I 3
BINDIR=	/usr/bin
E 3
I 2
NOMAN=	noman
E 2
.PATH: $(.CURDIR)/config

.include "config/Makefile.$(MACHINE)"

.include <bsd.prog.mk>
E 1
