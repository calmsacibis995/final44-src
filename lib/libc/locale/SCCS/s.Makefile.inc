h56263
s 00000/00000/00013
d D 8.1 93/06/04 12:44:47 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00005/00008
d D 5.5 93/06/02 20:17:51 bostic 5 4
c add rest of Paul Borman's routines
e
s 00002/00002/00011
d D 5.4 93/05/27 13:37:17 bostic 4 3
c put a backward compatible ctype in place, for old binaries
e
s 00008/00002/00005
d D 5.3 93/05/26 20:33:33 bostic 3 2
c rune support from Paul Borman
c move all of the ctype routines/man pages from libc/gen into libc/locale
e
s 00001/00000/00006
d D 5.2 93/03/02 17:46:43 bostic 2 1
c BSDI just gave us a setlocale man page
e
s 00006/00000/00000
d D 5.1 91/02/18 10:40:26 donn 1 0
c date and time created 91/02/18 10:40:26 by donn
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

# locale sources
.PATH: ${.CURDIR}/${MACHINE}/locale ${.CURDIR}/locale

D 3
SRCS+=	lconv.c localeconv.c setlocale.c
I 2
MAN3+=	setlocale.0
E 3
I 3
D 4
SRCS+=	ansi.c euc.c frune.c isctype.c lconv.c localeconv.c mbrune.c \
	none.c rune.c setlocale.c table.c utf2.c
E 4
I 4
SRCS+=	ansi.c ctype.c euc.c frune.c isctype.c lconv.c localeconv.c \
	mbrune.c none.c rune.c setlocale.c table.c utf2.c
E 4

D 5
MAN3+=	ctype.0
MAN3+=	isalnum.0 isalpha.0 isascii.0 isblank.0 iscntrl.0 isdigit.0 \
	isgraph.0 islower.0 isprint.0 ispunct.0 isspace.0 isupper.0 \
	isxdigit.0 toascii.0 tolower.0 toupper.0
MAN3+=	multibyte.0 setlocale.0
E 5
I 5
MAN3+=	ctype.0 isalnum.0 isalpha.0 isascii.0 isblank.0 iscntrl.0 \
	isdigit.0 isgraph.0 islower.0 isprint.0 ispunct.0 isspace.0 \
	isupper.0 isxdigit.0 mbrune.0 multibyte.0 rune.0 setlocale.0 \
	toascii.0 tolower.0 toupper.0
MAN4+=	euc.0 utf2.0
E 5
E 3
E 2
E 1
