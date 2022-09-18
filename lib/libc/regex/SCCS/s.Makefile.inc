h34272
s 00000/00000/00014
d D 8.1 93/06/04 12:57:37 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00014/00000/00000
d D 5.1 92/08/06 12:02:03 bostic 1 0
c date and time created 92/08/06 12:02:03 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

# regex sources
.PATH: ${.CURDIR}/regex

CFLAGS+=-DPOSIX_MISTAKE

SRCS+=	regcomp.c regerror.c regexec.c regfree.c

MAN3+=	regex.0
MAN7+=	re_format.0

MLINKS+=regex.3 regcomp.3 regex.3 regexec.3 regex.3 regerror.3
MLINKS+=regexec.3 regfree.3
E 1
