h19471
s 00009/00000/00041
d D 5.2 91/04/12 15:41:22 bostic 2 1
c new copyright; att/bsd/shared
e
s 00041/00000/00000
d D 5.1 90/06/25 14:06:55 bostic 1 0
c date and time created 90/06/25 14:06:55 by bostic
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
	common/sig/whoami
	character*6 whoami
	integer fork, getpid, wait, tick
	external trap

	call signal(2, trap, -1)
	call signal(3, trap, -1)
	call signal(6, trap, -1)
	call signal(8, trap, -1)
	call signal(15, trap, -1)

	tick = 1
	id = fork()
	if (id .eq. 0) then
	    whoami = "child"
	    write(*,*) "child:", getpid()
	    call flush(6)
   10	    call sleep(1)
	    write(*,'(1x,i2,$)') tick
	    call flush(6)
	    tick = tick + 1
	    goto 10
	else
	    whoami = "parent"
	    call sleep(5)
	    write(*,*) "\nparent:", id
	    call flush(6)
	    istat = kill(id, 15)
	    write(*,*) "\nkill status:", istat
	    call flush(6)
	    iwait = wait(isw)
	    write(*,*) iwait, isw
	endif
	end

	subroutine trap(num)
	common/sig/whoami
	character*6 whoami
	write(*,*) "\ntrap:", whoami, num
	stop
	end
E 1
