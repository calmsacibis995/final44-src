h38110
s 00000/00000/00007
d D 8.1 93/06/11 15:04:38 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00000/00000
d D 7.1 93/03/09 23:59:39 utashiro 1 0
c date and time created 93/03/09 23:59:39 by utashiro
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

news_sysent.c news_syscalls.c news_syscall.h: makesyscalls.sh syscalls.master
	-mv -f news_sysent.c news_sysent.c.bak
	-mv -f news_syscalls.c news_syscalls.c.bak
	-mv -f news_syscall.h news_syscall.h.bak
	sh makesyscalls.sh syscalls.master
E 1
