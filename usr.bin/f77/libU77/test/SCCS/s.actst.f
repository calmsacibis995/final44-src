h60015
s 00009/00000/00011
d D 5.2 91/04/12 15:41:17 bostic 2 1
c new copyright; att/bsd/shared
e
s 00011/00000/00000
d D 5.1 90/06/25 14:06:44 bostic 1 0
c date and time created 90/06/25 14:06:44 by bostic
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
	integer access
	write(*,*) "exist?", access("actst.f", " ")
	write(*,*) "execute?", access("actst.f", "x")
	write(*,*) "read?", access("actst.f", "r")
	write(*,*) "write?", access("actst.f", "w")
	write(*,*) "read/write?", access("actst.f", "rw")
	write(*,*) "read/write/exec?", access("actst.f", "rwx")
	write(*,*) "null name?", access(" ", "w")
	write(*,*) "bad arg?", access("actst.f", "zzz")
	write(*,*) "not exist?", access("XQIT%0XGE", " ")
	end
E 1
