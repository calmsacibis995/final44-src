h36600
s 00009/00000/00009
d D 5.2 91/04/12 15:41:19 bostic 2 1
c new copyright; att/bsd/shared
e
s 00009/00000/00000
d D 5.1 90/06/25 14:06:48 bostic 1 0
c date and time created 90/06/25 14:06:48 by bostic
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
	logical bit
	i = 0
	call bis(30, i)
	write(*,*) i, bit(30, i), bit(4, i)
	call bic(30, i)
	write(*,*) i, bit(0, i)
	call bis(0, i)
	write(*,*) i
	end
E 1
