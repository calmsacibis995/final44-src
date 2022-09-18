h38230
s 00009/00000/00009
d D 5.2 91/04/12 15:41:25 bostic 2 1
c new copyright; att/bsd/shared
e
s 00009/00000/00000
d D 5.1 90/06/25 14:07:00 bostic 1 0
c date and time created 90/06/25 14:07:00 by bostic
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
	character*50 path
	integer getcwd, chdir

	ier = getcwd(path)
	write(*,*) ier, path
	ier = chdir("..")
	ier = getcwd(path)
	write(*,*) ier, path
	end
E 1
