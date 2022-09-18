h63781
s 00009/00000/00019
d D 5.2 91/04/12 15:41:20 bostic 2 1
c new copyright; att/bsd/shared
e
s 00019/00000/00000
d D 5.1 90/06/25 14:06:50 bostic 1 0
c date and time created 90/06/25 14:06:50 by bostic
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
	integer chdir, unlink, access, ier(8)
	write(*,*) "moving to /tmp"
	ier(1) = chdir("/tmp")
	call system("pwd")
	open(1, file="scratch")
	close(1)
	write(*,*) "linking"
	ier(2) = link("scratch", "temp")
	ier(3) = access("scratch", " ")
	ier(4) = access("temp", " ")
	call system("ls -il scratch temp")
	write(*,*) "unlinking"
	ier(5) = unlink("scratch")
	ier(6) = unlink("temp")
	ier(7) = access("scratch", " ")
	ier(8) = access("temp", " ")
	call system("ls scratch temp")
	write(*,*) ier
	end
E 1
