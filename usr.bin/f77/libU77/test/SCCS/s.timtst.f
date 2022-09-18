h39427
s 00009/00000/00007
d D 5.2 91/04/12 15:41:35 bostic 2 1
c new copyright; att/bsd/shared
e
s 00007/00000/00000
d D 5.1 90/06/25 14:07:28 bostic 1 0
c date and time created 90/06/25 14:07:28 by bostic
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
	character*24 ctime, fdate
	integer time, tl(9), tgm(9)
	write(*,*) ctime(time()), fdate()
	call ltime(time(), tl)
	call gmtime(time(), tgm)
	write(*,*) tl, tgm
	end
E 1
