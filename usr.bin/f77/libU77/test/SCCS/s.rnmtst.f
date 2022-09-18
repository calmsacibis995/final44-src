h41506
s 00009/00000/00010
d D 5.2 91/04/12 15:41:27 bostic 2 1
c new copyright; att/bsd/shared
e
s 00010/00000/00000
d D 5.1 90/06/25 14:07:08 bostic 1 0
c date and time created 90/06/25 14:07:08 by bostic
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
	program rnmtst
	integer rename
	external rename

	open(1, file="abc")
	close(1)
	call system ("ls -l abc def")
	write(*,*) "rename:", rename("abc", "def")
	call system ("ls -l abc def")
	end
E 1
