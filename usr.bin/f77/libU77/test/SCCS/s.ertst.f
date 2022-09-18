h54932
s 00009/00000/00020
d D 5.2 91/04/12 15:41:22 bostic 2 1
c new copyright; att/bsd/shared
e
s 00020/00000/00000
d D 5.1 90/06/25 14:06:54 bostic 1 0
c date and time created 90/06/25 14:06:54 by bostic
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
	character*39 errno
	character*32 gerror
	external gerror

	do 100 i = 0, 36
	call serrno(i)
	write(errno,'("[",i3,"] ",a,":")') ierrno(), gerror()
	call perror(errno)
  100	continue

	do 200 i = 99, 123
	call serrno(i)
	write(errno,'("[",i3,"] ",a,":")') ierrno(), gerror()
	call perror(errno)
  200	continue

	write(**,*) "-----"
	call serrno(-1)
	call perror("Last line          ")
	end
E 1
