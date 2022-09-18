h59561
s 00009/00000/00024
d D 5.2 91/04/12 15:41:24 bostic 2 1
c new copyright; att/bsd/shared
e
s 00024/00000/00000
d D 5.1 90/06/25 14:06:58 bostic 1 0
c date and time created 90/06/25 14:06:58 by bostic
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
	integer getc, putc, fgetc, fputc, oer
	character c
	open(1,status='s')
	write(*,*) "Go"
   10	ier = getc(c)
	if (ier .eq. 0) then
	  oer = fputc(1,c)
	  goto 10
	else
	  call perror("end of getc/fputc test")
	  write(*,*) "ier=", ier, "oer=", oer
	endif

	rewind 1
	write(*,*) "Go"
   20	ier = fgetc(1, c)
	if (ier .eq. 0) then
	  oer = putc(c)
	  goto 20
	else
	  call perror("end of fgetc/putc test")
	  write(*,*) "ier=", ier, "oer=", oer
	endif
	end
E 1
