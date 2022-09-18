h46032
s 00009/00000/00013
d D 5.2 91/04/12 15:41:30 bostic 2 1
c new copyright; att/bsd/shared
e
s 00013/00000/00000
d D 5.1 90/06/25 14:07:18 bostic 1 0
c date and time created 90/06/25 14:07:18 by bostic
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
	integer signal
	external trap
	isav = signal(8, 0, 1)
	write(*,*) "1", signal(8, 0, 0)
	write(*,*) "0", signal(8, trap, -1)
	write(*,*) "addr", signal(8, 0, isav)
	write(*,*) isav, signal(8, trap, -1)
	x = 1.0/x
	end

	subroutine trap(isig)
	write(*,*) "Here I am."
	end
E 1
