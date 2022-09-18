h32968
s 00009/00000/00004
d D 5.2 91/04/12 15:41:36 bostic 2 1
c new copyright; att/bsd/shared
e
s 00004/00000/00000
d D 5.1 90/06/25 14:07:29 bostic 1 0
c date and time created 90/06/25 14:07:29 by bostic
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
	program ttnam
	character*19 ttynam
	write(*,*) ttynam(6), ":", ttynam(1), ":"
	end
E 1
