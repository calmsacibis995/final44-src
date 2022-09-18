h22166
s 00000/00000/00009
d D 8.1 93/05/31 17:43:21 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00000
d D 5.1 90/05/11 12:44:41 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	primes
SRCS=	pattern.c pr_tbl.c primes.c
NOMAN=	noman
DPADD=	${LIBM}
LDADD=	-lm

.include <bsd.prog.mk>
E 1
