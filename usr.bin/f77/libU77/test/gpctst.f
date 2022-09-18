C
C Copyright (c) 1980 The Regents of the University of California.
C All rights reserved.
C
C This module is believed to contain source code proprietary to AT&T.
C Use and redistribution is subject to the Berkeley Software License
C Agreement and your Software Agreement with AT&T (Western Electric).
C
C	@(#)gpctst.f	5.2 (Berkeley) 4/12/91
C

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
