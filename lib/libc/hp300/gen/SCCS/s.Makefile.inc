h00630
s 00001/00001/00008
d D 8.2 95/05/03 21:41:22 mckusick 4 3
c add sigsetjmp.s
e
s 00000/00000/00009
d D 8.1 93/06/04 12:24:46 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00008
d D 5.2 93/05/31 09:55:49 bostic 2 1
c add isinf.c to the CPU dependent Makefile
e
s 00008/00000/00000
d D 5.1 92/06/26 06:54:45 bostic 1 0
c date and time created 92/06/26 06:54:45 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

I 2
SRCS+=	isinf.c
E 2
D 4
SRCS+=	_setjmp.s alloca.s fabs.s ldexp.s modf.s setjmp.s
E 4
I 4
SRCS+=	_setjmp.s alloca.s fabs.s ldexp.s modf.s setjmp.s sigsetjmp.s
E 4
SRCS+=	adddf3.s addsf3.s ashlsi3.s ashrsi3.s cmpdf2.s cmpsf2.s divdf3.s \
	divsf3.s divsi3.s extendsfdf2.s fixdfsi.s fixunsdfsi.s \
	floatsidf.s lshlsi3.s lshrsi3.s modsi3.s muldf3.s mulsf3.s mulsi3.s \
	negdf2.s negsf2.s saveregs.c subdf3.s subsf3.s truncdfsf2.s udivsi3.s \
	umodsi3.s umulsi3.s
E 1
