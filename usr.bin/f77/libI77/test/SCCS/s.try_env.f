h65374
s 00009/00000/00018
d D 5.2 91/04/12 15:55:25 bostic 2 1
c new copyright; att/bsd/shared
e
s 00018/00000/00000
d D 5.1 90/06/25 13:56:22 bostic 1 0
c date and time created 90/06/25 13:56:22 by bostic
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
c		test overriding file names from program with
c			environment variables
c		formatted, seq
	write(8,8000) 8
8000	format('sample line ',i5)
	open(9,file='subdir/frmt.d')
	write(9,8000) 9
c		unform, seq
	open(10,form='unformatted')
	write(10) 10
	open(11,file='unfr.dat',form='unformatted')
	write(11) 11
c		direct
	open(12,access='direct',form='formatted',recl=20)
	write(12,8000,rec=3) 12
	open(13,file='dirct',access='direct',form='unformatted',recl=8)
	write(13,rec=3) 127, 16*127
	end
E 1
