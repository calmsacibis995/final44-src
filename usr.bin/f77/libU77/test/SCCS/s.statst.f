h47318
s 00009/00000/00009
d D 5.2 91/04/12 15:41:32 bostic 2 1
c new copyright; att/bsd/shared
e
s 00009/00000/00000
d D 5.1 90/06/25 14:07:21 bostic 1 0
c date and time created 90/06/25 14:07:21 by bostic
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
	character*24 ctime
	integer stata(11), statb(11), i1, i2
	open(1, file='statst.f')
	i1 = stat('statst.f', stata)
	i2 = fstat(1, statb)
	write(*,*) i1, i2, ierrno()
	write(*,'(8r,2i12)') (stata(i),statb(i),i=1,8)
	write(*,'(a,2x,a)') (ctime(stata(i)), ctime(statb(i)), i=9,11)
	end
E 1
