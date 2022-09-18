h29968
s 00000/00000/00010
d D 8.1 93/06/04 12:53:09 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00003/00006
d D 5.3 92/07/07 11:54:16 torek 3 2
c single precision float <-> quad, for gcc2 (for sparc)
e
s 00005/00005/00004
d D 5.2 92/06/02 13:34:53 bostic 2 1
c new version from Chris Torek
e
s 00009/00000/00000
d D 5.1 92/06/02 10:29:46 bostic 1 0
c date and time created 92/06/02 10:29:46 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
# GCC quad support
SRCS+=	adddi3.c anddi3.c ashldi3.c ashrdi3.c bdiv.c cmpdi2.c divdi3.c \
	fixdfdi.c fixunsdfdi.c floatdidf.c iordi3.c lshldi3.c lshrdi3.c \
	moddi3.c muldi3.c negdi2.c one_cmpldi2.c subdi3.c ucmpdi2.c \
	udivdi3.c umoddi3.c xordi3.c
E 2
I 2
# Quad support
SRCS+=	adddi3.c anddi3.c ashldi3.c ashrdi3.c cmpdi2.c divdi3.c fixdfdi.c \
D 3
	fixunsdfdi.c floatdidf.c floatunsdidf.c iordi3.c lshldi3.c \
	lshrdi3.c moddi3.c muldi3.c negdi2.c notdi2.c qdivrem.c subdi3.c \
	ucmpdi2.c udivdi3.c umoddi3.c xordi3.c
E 3
I 3
	fixsfdi.c fixunsdfdi.c fixunssfdi.c floatdidf.c floatdisf.c \
	floatunsdidf.c iordi3.c lshldi3.c lshrdi3.c moddi3.c muldi3.c \
	negdi2.c notdi2.c qdivrem.c subdi3.c ucmpdi2.c udivdi3.c umoddi3.c \
	xordi3.c
E 3
E 2

.PATH: ${.CURDIR}/${MACHINE}/quad ${.CURDIR}/quad
E 1
