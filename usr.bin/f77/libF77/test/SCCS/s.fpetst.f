h32747
s 00009/00000/00042
d D 5.2 91/04/12 15:56:19 bostic 2 1
c new copyright; att/bsd/shared
e
s 00042/00000/00000
d D 5.1 90/06/25 13:58:06 bostic 1 0
c date and time created 90/06/25 13:58:06 by bostic
e
u
U
t
T
I 2
C
C Copyright (c) 1991 The Regents of the University of California.
C All rights reserved.
C
C %sccs.include.proprietary.f%
C
C	%W% (Berkeley) %G%
C

E 2
I 1
	program fpetst
	character arg
	logical flag
	common /fpeflt/ flag

	call trpfpe(1, 1.2345d0)
	call traper(3)
	i = 10
	j = 0
	x = 10.
	y = 0.

	write (*,*) 
	call getarg (1, arg)
	if (arg .eq. '1') then
		write(*,*) 'testing integer overflow, flag=', flag
		k = inmax() + 10
		write (*,*) 'k=', k, 'flag=', flag
		stop('returned')
	else if (arg .eq. '2') then
		write(*,*) 'testing integer divide by 0, flag=', flag
		k = i / j
		write (*,*) 'k=', k, 'flag=', flag
		stop('returned')
	else if (arg .eq. '3') then
		write(*,*) 'testing floating overflow, flag=', flag
		z = flmax() * 10.
		write(*,*) 'z=', z, 'flag=', flag
		stop('returned')
	else if (arg .eq. '4') then
		write(*,*) 'testing floating divide by 0, flag=', flag
		z = x / y
		write(*,*) 'z=', z, 'flag=', flag
		stop('returned')
	else if (arg .eq. '5') then
		write(*,*) 'testing floating underflow, flag=', flag
		z = flmin() / 10.
		write(*,*) 'z=', z, 'flag=', flag
		stop('returned')
	endif
	write(*,*) 'what??'
	end
E 1
