h58637
s 00009/00000/00016
d D 5.2 91/04/12 15:41:28 bostic 2 1
c new copyright; att/bsd/shared
e
s 00016/00000/00000
d D 5.1 90/06/25 14:07:11 bostic 1 0
c date and time created 90/06/25 14:07:11 by bostic
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
	character*20 word1, word2
	integer ftell, fseek
	open(1, file="/usr/dict/words")
	iend = ftell(1)
	iseek1 = fseek(1, iend/2, 0)
	read(1,'(a)') word1
	iword = ftell(1)
	read(1,'(a)') word1
	rewind 1
	ibeg = ftell(1)
	iseek2 = fseek(1, iword, 0)
	read(1,'(a)') word2
	write(*,*) ibeg, iword, ftell(1), iend
	write(*,*) word1(:lnblnk(word1)), word2(:lnblnk(word2))
	write(*,*) "seek status", iseek1, iseek2, fseek(1, -1, 0)
	end
E 1
