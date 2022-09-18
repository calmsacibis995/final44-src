h56665
s 00001/00001/00002
d D 8.2 94/02/16 12:25:28 bostic 5 4
c add fabs.s; From: ralphc@pyramid.com (Ralph Campbell)
e
s 00000/00000/00003
d D 8.1 93/06/04 12:46:21 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00002
d D 5.3 93/03/08 18:45:07 ralph 3 2
c added isinf.s
e
s 00001/00001/00002
d D 5.2 92/07/26 21:35:36 ralph 2 1
c insque.s and remque.s removed since they don't seem to be used.
e
s 00003/00000/00000
d D 5.1 92/06/26 06:56:23 bostic 1 0
c date and time created 92/06/26 06:56:23 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
SRCS+=	_setjmp.s insque.s ldexp.s modf.s remque.s setjmp.s
E 2
I 2
D 3
SRCS+=	_setjmp.s ldexp.s modf.s setjmp.s
E 3
I 3
D 5
SRCS+=	_setjmp.s isinf.s ldexp.s modf.s setjmp.s
E 5
I 5
SRCS+=	_setjmp.s fabs.s isinf.s ldexp.s modf.s setjmp.s
E 5
E 3
E 2
E 1
