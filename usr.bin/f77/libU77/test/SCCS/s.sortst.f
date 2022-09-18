h52675
s 00009/00000/00019
d D 5.2 91/04/12 15:41:31 bostic 2 1
c new copyright; att/bsd/shared
e
s 00019/00000/00000
d D 5.1 90/06/25 14:07:20 bostic 1 0
c date and time created 90/06/25 14:07:20 by bostic
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
	program tst
c to test various syslib routines
	external ntest
	character*10 num(10)
	do 10 i=1,10
	write(*,'(i2,": ",$)') i
   10	read(*,*) num(i)
	write(*,*) num
	call qsort(num, 10, 10, ntest)
	write(*,*) num
	end

	integer*2 function ntest(i1, i2)
	character*10 i1, i2
	ntest = 0
	if (lgt(i1,i2)) ntest = 1
	if (llt(i1,i2)) ntest = -1
	return
	end
E 1
