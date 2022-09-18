h62349
s 00009/00000/00026
d D 5.2 91/04/12 15:41:31 bostic 2 1
c new copyright; att/bsd/shared
e
s 00026/00000/00000
d D 5.1 90/06/25 14:07:19 bostic 1 0
c date and time created 90/06/25 14:07:19 by bostic
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
	external fpe
	integer signal
	isave = signal(8, 0, 1)
	write(*,*) "1", signal(8, 0, 0)
	write(*,*) "0", signal(8, fpe, -1)
	write(*,*) "addr fpe", signal(8, 0, isave)
	write(*,*) isave, signal(8, fpe, -1)
	x = 1/x
	write(*,*) "Back again"
	z = 1/z
	write(*,*) "Saved again"
	end

	subroutine fpe(flag)
	call signal(8, fpe, -1)
c	call sigset()
	write(*,*) "Hi there sports fans!"
	call flush(6)
	return
	end

	subroutine sigset()
	external fpe
	call signal(8, fpe, -1)
	return
	end
E 1
