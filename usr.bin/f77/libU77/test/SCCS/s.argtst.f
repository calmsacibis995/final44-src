h41446
s 00009/00000/00011
d D 5.2 91/04/12 15:41:18 bostic 2 1
c new copyright; att/bsd/shared
e
s 00011/00000/00000
d D 5.1 90/06/25 14:06:47 bostic 1 0
c date and time created 90/06/25 14:06:47 by bostic
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
	character*16 arg, env
	n = iargc()
	call getarg(0, arg)
	write(*,*) "name:", arg
	if (n .gt. 0) then
	  do 100 i=1, n
	  call getarg(i, arg)
	  call getenv(arg, env)
  100	  write(*,*) i, arg, env
	endif
	end
E 1
