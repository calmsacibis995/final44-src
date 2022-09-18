h53590
s 00009/00000/00019
d D 5.2 91/04/12 15:55:24 bostic 2 1
c new copyright; att/bsd/shared
e
s 00019/00000/00000
d D 5.1 90/06/25 13:56:19 bostic 1 0
c date and time created 90/06/25 13:56:19 by bostic
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
	program trutst
	integer ftell
	external ftell

	rewind 1
	write(1,*) "This is line A."
	write(1,*) "This is line B."
	write(1,*) "This is line C."
	write(1,*) "This is line D."
	backspace 1
	endfile 1
	call system ("cat fort.1")
	write(*,*) "---"
	rewind 1
	write(1,*) "This is line E."
	write(1,*) "This is line F."
	close(1)
	call system ("cat fort.1")
	end
E 1
