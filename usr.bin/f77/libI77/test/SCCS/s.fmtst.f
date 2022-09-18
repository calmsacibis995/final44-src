h34216
s 00009/00000/00006
d D 5.2 91/04/12 15:55:22 bostic 2 1
c new copyright; att/bsd/shared
e
s 00006/00000/00000
d D 5.1 90/06/25 13:56:03 bostic 1 0
c date and time created 90/06/25 13:56:03 by bostic
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
	real x(8)
	do 10 i=1,8
   10	x(i) = i
	write(*,1000) (i,x(i),i=1,8)
 1000	format (2("x(",i,")= ",f3.0," feet, "), "ta da")
	end
E 1
