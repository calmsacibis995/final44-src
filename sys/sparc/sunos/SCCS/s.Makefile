h36484
s 00000/00000/00007
d D 8.1 93/06/11 15:19:44 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00000/00000
d D 7.1 92/07/13 00:40:44 torek 1 0
c date and time created 92/07/13 00:40:44 by torek
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

sun_sysent.c sun_syscalls.c sun_syscall.h: makesyscalls.sh syscalls.master
	-mv -f sun_sysent.c sun_sysent.c.bak
	-mv -f sun_syscalls.c sun_syscalls.c.bak
	-mv -f sun_syscall.h sun_syscall.h.bak
	sh makesyscalls.sh syscalls.master
E 1
