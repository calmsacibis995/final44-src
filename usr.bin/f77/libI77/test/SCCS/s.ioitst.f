h09064
s 00009/00000/00037
d D 5.2 91/04/12 15:55:22 bostic 2 1
c new copyright; att/bsd/shared
e
s 00037/00000/00000
d D 5.1 90/06/25 13:56:06 bostic 1 0
c date and time created 90/06/25 13:56:06 by bostic
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
	program ioitst

	character*80 buf
	logical ioinit, iok, ictl, izro, iap
	integer ftell
	external ioinit, ftell

	if (iargc() .ge. 1) then
		call getarg(1, buf)
		ictl = (buf(1:1) .eq. 'T')
	else
		ictl = .true.
	endif

	if (iargc() .ge. 2) then
		call getarg(2, buf)
		izro = (buf(1:1) .eq. 'T')
	else
		izro = .false.
	endif

	if (iargc() .ge. 3) then
		call getarg(3, buf)
		iap = (buf(1:1) .eq. 'T')
	else
		iap = .false.
	endif

	iok = ioinit(ictl, izro, iap, "FORT", .true.)
	write(*,*) "ioinit returned", iok, "pos", ftell(10)

   10	read(10,"(i3,a)",end=999) line, buf
	write(6, "('0',i3,a)") line, buf(:lnblnk(buf))
	goto 10

  999	write(6, "(f6.2)") 0.0
	end
E 1
