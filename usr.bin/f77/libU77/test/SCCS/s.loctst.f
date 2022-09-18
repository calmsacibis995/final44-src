h35283
s 00009/00000/00005
d D 5.2 91/04/12 15:41:26 bostic 2 1
c new copyright; att/bsd/shared
e
s 00005/00000/00000
d D 5.1 90/06/25 14:07:03 bostic 1 0
c date and time created 90/06/25 14:07:03 by bostic
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
	common/blah/i,j,k
	double precision d
	equivalence (d,i),(x,i)
	write(*,*) loc(i), loc(d), loc(x), loc(z)
	end
E 1
