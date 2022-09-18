h31596
s 00009/00000/00004
d D 5.2 91/04/12 15:55:24 bostic 2 1
c new copyright; att/bsd/shared
e
s 00004/00000/00000
d D 5.1 90/06/25 13:56:17 bostic 1 0
c date and time created 90/06/25 13:56:17 by bostic
e
u
U
t
T
I 2
C
C Copyright (c) 1980 The Regents of the University of California.
C All rights reserved.
C
C %sccs.include.proprietary.f%
C
C	%W% (Berkeley) %G%
C

E 2
I 1
	program pe
	x = 123.456
	write(*,'(3pe8.1,5x,0pe9.5e0)') x, 123456789e14
	end
E 1
