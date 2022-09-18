h40370
s 00001/00001/00019
d D 7.9 93/06/01 23:05:06 bostic 9 8
c unedit Makefile
e
s 00001/00001/00019
d D 7.8 92/11/17 13:45:53 bostic 8 7
c add /sys to include line
e
s 00009/00005/00011
d D 7.7 92/07/12 20:12:26 torek 7 6
c make min/max routines inlines; make machine specific routines possible
e
s 00005/00001/00011
d D 7.6 92/07/11 06:22:12 mckusick 6 5
c add mcount.c (not profiled)
e
s 00003/00003/00009
d D 7.5 92/06/24 09:19:36 bostic 5 4
c add strcmp.c
e
s 00003/00002/00009
d D 7.4 92/06/24 01:12:25 torek 4 3
c add random()
e
s 00000/00001/00011
d D 7.3 92/06/22 16:08:09 bostic 3 2
c build a profile version as well.
e
s 00001/00001/00011
d D 7.2 92/06/22 14:17:42 mckusick 2 1
c make with -g
e
s 00013/00000/00000
d D 7.1 92/06/20 16:57:19 mckusick 1 0
c date and time created 92/06/20 16:57:19 by mckusick
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

LIB=	kern
D 2
CFLAGS+=-I${.CURDIR}
E 2
I 2
D 8
CFLAGS+=-I${.CURDIR} -g
E 8
I 8
D 9
CFLAGS+= -I${.CURDIR} -I${.CURDIR}/.. -g
E 9
I 9
CFLAGS+= -I${.CURDIR} -I${.CURDIR}/..
E 9
E 8
E 2
SRCS=	adddi3.c anddi3.c ashldi3.c ashrdi3.c bcmp.c cmpdi2.c divdi3.c \
D 7
	ffs.c imax.c imin.c iordi3.c lmax.c lmin.c locc.c lshldi3.c \
D 6
	lshrdi3.c max.c min.c moddi3.c muldi3.c negdi2.c notdi2.c \
E 6
I 6
	lshrdi3.c max.c mcount.c min.c moddi3.c muldi3.c negdi2.c notdi2.c \
E 6
D 4
	qdivrem.c scanc.c skpc.c strcat.c strcpy.c strlen.c strncpy.c \
	subdi3.c ucmpdi2.c udivdi3.c ulmax.c ulmin.c umoddi3.c xordi3.c
E 4
I 4
D 5
	qdivrem.c random.c scanc.c skpc.c strcat.c strcpy.c strlen.c \
	strncpy.c subdi3.c ucmpdi2.c udivdi3.c ulmax.c ulmin.c umoddi3.c \
	xordi3.c
E 5
I 5
	qdivrem.c random.c scanc.c skpc.c strcat.c strcmp.c strcpy.c \
	strlen.c strncpy.c subdi3.c ucmpdi2.c udivdi3.c ulmax.c ulmin.c \
	umoddi3.c xordi3.c
E 7
I 7
	ffs.c iordi3.c locc.c lshldi3.c lshrdi3.c mcount.c moddi3.c \
	muldi3.c negdi2.c notdi2.c qdivrem.c random.c rindex.c scanc.c \
	skpc.c strcat.c strcmp.c strcpy.c strlen.c strncpy.c subdi3.c \
	ucmpdi2.c udivdi3.c umoddi3.c xordi3.c

.if exists(${.CURDIR}/${MACHINE}/Makefile.inc)
.PATH: ${.CURDIR}/${MACHINE}
.include "${.CURDIR}/${MACHINE}/Makefile.inc"
.endif
E 7
I 6

# mcount cannot be compiled with profiling
mcount.po: mcount.o
	cp mcount.o mcount.po
E 6
E 5
E 4
D 3
NOPROFILE=noprofile
E 3

.include <bsd.lib.mk>
E 1
