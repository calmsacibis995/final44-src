h48395
s 00004/00004/00148
d D 5.7 90/03/15 21:55:35 mckusick 7 6
c update for separate machine compilation
e
s 00042/00038/00110
d D 5.6 90/03/11 18:17:17 bostic 6 5
c major reorganization; add installation of man pages
e
s 00009/00009/00139
d D 5.5 89/07/02 20:18:20 mckusick 5 4
c add exportfs, getfh, and nfssvc
e
s 00003/00003/00145
d D 5.4 89/06/06 23:54:35 mckusick 4 3
c umount => unmount
e
s 00061/00049/00087
d D 5.3 89/06/06 23:45:39 mckusick 3 2
c add fchdir, chflags, fchflags, getdirentries, statfs, fstatfs, getfsstat
e
s 00044/00001/00092
d D 5.2 89/03/29 12:27:48 bostic 2 1
c add manual pages
e
s 00089/00000/00000
d D 5.1 89/03/07 21:05:06 bostic 1 0
c date and time created 89/03/07 21:05:06 by bostic
e
u
U
t
T
I 1
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
#	%W% (Berkeley) %G%
#
D 6
VPATH=	../../machine.sys
E 6
I 6
VPATH=	${MACHINE}
E 6
DEFS=	-DSYSLIBC_SCCS
D 6
FLAGS=	${DEFS} -I.
E 6
I 6
FLAGS=	-I${MACHINE} ${DEFS}
E 6
SRCS=	Ovadvise.s Ovfork.s _exit.s accept.s access.s acct.s adjtime.s \
D 3
	bind.s brk.s cerror.s chdir.s chmod.s chown.s chroot.s close.s \
	connect.s creat.s dup.s dup2.s execl.s execle.s exect.s execv.s \
	execve.s fchmod.s fchown.s fcntl.s flock.s fork.s fstat.s \
	fsync.s ftruncate.s getdtablesize.s getegid.s geteuid.s getgid.s \
	getgroups.s gethostid.s gethostname.s getitimer.s getlogname.s \
	getpagesize.s getpeername.s getpgrp.s getpid.s getppid.s \
	getpriority.s getrlimit.s getrusage.s getsockname.s getsockopt.s \
	gettimeofday.s getuid.s ioctl.s kill.s killpg.s ktrace.s link.s \
	listen.s lseek.s lstat.s mkdir.s mknod.s mmap.s mount.s open.s \
	pipe.s profil.s ptrace.s quota.s read.s readlink.s readv.s \
	reboot.s recvfrom.s recvmsg.s rename.s rmdir.s sbrk.s select.s \
	sendmsg.s sendto.s setgroups.s sethostid.s sethostname.s \
	setitimer.s setlogname.s setpgrp.s setpriority.s setquota.s \
	setregid.s setreuid.s setrlimit.s setsid.s setsockopt.s \
	settimeofday.s shutdown.s sigblock.s sigpause.s sigreturn.s \
	sigsetmask.s sigstack.s sigvec.s socket.s socketpair.s stat.s \
	swapon.s symlink.s sync.s syscall.s truncate.s umask.s umount.s \
	unlink.s utimes.s vhangup.s wait4.s write.s writev.s
E 3
I 3
D 6
	bind.s brk.s cerror.s chdir.s chflags.s chmod.s chown.s \
	chroot.s close.s connect.s creat.s dup.s dup2.s execl.s \
D 5
	execle.s exect.s execv.s execve.s fchdir.s fchflags.s \
E 5
I 5
	execle.s exect.s execv.s execve.s exportfs.s fchdir.s fchflags.s \
E 6
I 6
	async_daemon.s bind.s brk.s cerror.s chdir.s chflags.s chmod.s \
	chown.s chroot.s close.s connect.s dup.s dup2.s execl.s \
	execle.s exect.s execv.s execve.s fchdir.s fchflags.s \
E 6
E 5
	fchmod.s fchown.s fcntl.s flock.s fork.s fstat.s fstatfs.s \
	fsync.s ftruncate.s getdirentries.s getdtablesize.s getegid.s \
D 5
	geteuid.s getfsstat.s getgid.s getgroups.s gethostid.s \
E 5
I 5
	geteuid.s getfh.s getfsstat.s getgid.s getgroups.s gethostid.s \
E 5
D 6
	gethostname.s getitimer.s getlogname.s getpagesize.s \
E 6
I 6
	gethostname.s getitimer.s getkerninfo.s _getlogin.s getpagesize.s \
E 6
	getpeername.s getpgrp.s getpid.s getppid.s getpriority.s \
	getrlimit.s getrusage.s getsockname.s getsockopt.s \
D 6
	gettimeofday.s getuid.s ioctl.s kill.s killpg.s ktrace.s \
	link.s listen.s lseek.s lstat.s mkdir.s mknod.s mmap.s \
E 6
I 6
	gettimeofday.s getuid.s ioctl.s kill.s ktrace.s \
	link.s listen.s lseek.s lstat.s mkdir.s mkfifo.s mknod.s mmap.s \
E 6
D 5
	mount.s open.s pipe.s profil.s ptrace.s quota.s read.s \
E 5
I 5
	mount.s nfssvc.s open.s pipe.s profil.s ptrace.s quota.s read.s \
E 5
	readlink.s readv.s reboot.s recvfrom.s recvmsg.s rename.s \
	rmdir.s sbrk.s select.s sendmsg.s sendto.s setgroups.s \
D 6
	sethostid.s sethostname.s setitimer.s setlogname.s setpgrp.s \
E 6
I 6
	sethostid.s sethostname.s setitimer.s setlogin.s setpgrp.s \
E 6
	setpriority.s setquota.s setregid.s setreuid.s setrlimit.s \
D 6
	setsid.s setsockopt.s settimeofday.s shutdown.s sigblock.s \
	sigpause.s sigreturn.s sigsetmask.s sigstack.s sigvec.s \
E 6
I 6
	setsid.s setsockopt.s settimeofday.s shutdown.s sigaction.s \
	sigsuspend.s sigreturn.s sigpending.s sigprocmask.s sigstack.s \
E 6
	socket.s socketpair.s stat.s statfs.s swapon.s symlink.s \
D 4
	sync.s syscall.s truncate.s umask.s umount.s unlink.s \
E 4
I 4
	sync.s syscall.s truncate.s umask.s unlink.s unmount.s \
E 4
	utimes.s vhangup.s wait4.s write.s writev.s
E 3
OBJS=	Ovadvise.o Ovfork.o _exit.o accept.o access.o acct.o adjtime.o \
D 3
	bind.o brk.o cerror.o chdir.o chmod.o chown.o chroot.o close.o \
	connect.o creat.o dup.o dup2.o execl.o execle.o exect.o execv.o \
	execve.o fchmod.o fchown.o fcntl.o flock.o fork.o fstat.o \
	fsync.o ftruncate.o getdtablesize.o getegid.o geteuid.o getgid.o \
	getgroups.o gethostid.o gethostname.o getitimer.o getlogname.o \
	getpagesize.o getpeername.o getpgrp.o getpid.o getppid.o \
	getpriority.o getrlimit.o getrusage.o getsockname.o getsockopt.o \
	gettimeofday.o getuid.o ioctl.o kill.o killpg.o ktrace.o link.o \
	listen.o lseek.o lstat.o mkdir.o mknod.o mmap.o mount.o open.o \
	pipe.o profil.o ptrace.o quota.o read.o readlink.o readv.o \
	reboot.o recvfrom.o recvmsg.o rename.o rmdir.o sbrk.o select.o \
	sendmsg.o sendto.o setgroups.o sethostid.o sethostname.o \
	setitimer.o setlogname.o setpgrp.o setpriority.o setquota.o \
	setregid.o setreuid.o setrlimit.o setsid.o setsockopt.o \
	settimeofday.o shutdown.o sigblock.o sigpause.o sigreturn.o \
	sigsetmask.o sigstack.o sigvec.o socket.o socketpair.o stat.o \
	swapon.o symlink.o sync.o syscall.o truncate.o umask.o umount.o \
	unlink.o utimes.o vhangup.o wait4.o write.o writev.o
I 2
MAN=	accept.0 access.0 acct.0 adjtime.0 bind.0 brk.0 chdir.0 chmod.0 \
	chown.0 chroot.0 close.0 connect.0 creat.0 dup.0 execve.0 exit.0 \
	fcntl.0 flock.0 fork.0 fsync.0 getdtablesize.0 getgid.0 getgroups.0 \
	gethostid.0 gethostname.0 getitimer.0 getpagesize.0 getpeername.0 \
	getpgrp.0 getpid.0 getpriority.0 getrlimit.0 getrusage.0 \
	getsockname.0 getsockopt.0 gettimeofday.0 getuid.0 intro.0 ioctl.0 \
	kill.0 killpg.0 link.0 listen.0 lseek.0 mkdir.0 mknod.0 mount.0 \
	open.0 pipe.0 profil.0 ptrace.0 quota.0 read.0 readlink.0 reboot.0 \
	recv.0 rename.0 rmdir.0 select.0 send.0 setgroups.0 setpgrp.0 \
	setquota.0 setregid.0 setreuid.0 shutdown.0 sigblock.0 sigpause.0 \
	sigreturn.0 sigsetmask.0 sigstack.0 sigvec.0 socket.0 socketpair.0 \
	stat.0 swapon.0 symlink.0 sync.0 syscall.0 truncate.0 umask.0 \
	unlink.0 utimes.0 vfork.0 vhangup.0 wait.0 write.0
E 3
I 3
D 6
	bind.o brk.o cerror.o chdir.o chflags.o chmod.o chown.o \
	chroot.o close.o connect.o creat.o dup.o dup2.o execl.o \
D 5
	execle.o exect.o execv.o execve.o fchdir.o fchflags.o \
E 5
I 5
	execle.o exect.o execv.o execve.o exportfs.o fchdir.o fchflags.o \
E 6
I 6
	async_daemon.o bind.o brk.o cerror.o chdir.o chflags.o chmod.o \
	chown.o chroot.o close.o connect.o dup.o dup2.o execl.o \
	execle.o exect.o execv.o execve.o fchdir.o fchflags.o \
E 6
E 5
	fchmod.o fchown.o fcntl.o flock.o fork.o fstat.o fstatfs.o \
	fsync.o ftruncate.o getdtablesize.o getdirentries.o getegid.o \
D 5
	geteuid.o getfsstat.o getgid.o getgroups.o gethostid.o \
E 5
I 5
	geteuid.o getfh.o getfsstat.o getgid.o getgroups.o gethostid.o \
E 5
D 6
	gethostname.o getitimer.o getlogname.o getpagesize.o \
E 6
I 6
	gethostname.o getitimer.o getkerninfo.o _getlogin.o getpagesize.o \
E 6
	getpeername.o getpgrp.o getpid.o getppid.o getpriority.o \
	getrlimit.o getrusage.o getsockname.o getsockopt.o \
D 6
	gettimeofday.o getuid.o ioctl.o kill.o killpg.o ktrace.o \
	link.o listen.o lseek.o lstat.o mkdir.o mknod.o mmap.o \
E 6
I 6
	gettimeofday.o getuid.o ioctl.o kill.o ktrace.o \
	link.o listen.o lseek.o lstat.o mkdir.o mkfifo.o mknod.o mmap.o \
E 6
D 5
	mount.o open.o pipe.o profil.o ptrace.o quota.o read.o \
E 5
I 5
	mount.o nfssvc.o open.o pipe.o profil.o ptrace.o quota.o read.o \
E 5
	readlink.o readv.o reboot.o recvfrom.o recvmsg.o rename.o \
	rmdir.o sbrk.o select.o sendmsg.o sendto.o setgroups.o \
D 6
	sethostid.o sethostname.o setitimer.o setlogname.o setpgrp.o \
E 6
I 6
	sethostid.o sethostname.o setitimer.o setlogin.o setpgrp.o \
E 6
	setpriority.o setquota.o setregid.o setreuid.o setrlimit.o \
D 6
	setsid.o setsockopt.o settimeofday.o shutdown.o sigblock.o \
	sigpause.o sigreturn.o sigsetmask.o sigstack.o sigvec.o \
E 6
I 6
	setsid.o setsockopt.o settimeofday.o shutdown.o sigaction.o \
	sigsuspend.o sigreturn.o sigpending.o sigprocmask.o sigstack.o \
E 6
	socket.o socketpair.o stat.o statfs.o swapon.o symlink.o \
D 4
	sync.o syscall.o truncate.o umask.o umount.o unlink.o \
E 4
I 4
	sync.o syscall.o truncate.o umask.o unlink.o unmount.o \
E 4
	utimes.o vhangup.o wait4.o write.o writev.o
D 6
MAN=	accept.0 access.0 acct.0 adjtime.0 bind.0 brk.0 chdir.0 \
	chflags.0 chmod.0 chown.0 chroot.0 close.0 connect.0 creat.0 \
D 5
	dup.0 execve.0 exit.0 fcntl.0 flock.0 fork.0 fsync.0 \
	getdtablesize.0 getdirentries.0 getfsstat.0 getgid.0 \
E 5
I 5
	dup.0 execve.0 exit.0 exportfs.0 fcntl.0 flock.0 fork.0 fsync.0 \
E 6
I 6
MAN=	accept.0 access.0 acct.0 adjtime.0 async_daemon.0 bind.0 brk.0 \
	chdir.0 \
	chflags.0 chmod.0 chown.0 chroot.0 close.0 connect.0 \
	dup.0 execve.0 exit.0 fcntl.0 flock.0 fork.0 fsync.0 \
E 6
	getdtablesize.0 getdirentries.0 getfh.0 getfsstat.0 getgid.0 \
E 5
D 6
	getgroups.0 gethostid.0 gethostname.0 getitimer.0 getpagesize.0 \
E 6
I 6
	getgroups.0 gethostid.0 gethostname.0 getitimer.0 \
	getlogin.0 getpagesize.0 \
E 6
	getpeername.0 getpgrp.0 getpid.0 getpriority.0 getrlimit.0 \
	getrusage.0 getsockname.0 getsockopt.0 gettimeofday.0 \
D 6
	getuid.0 intro.0 ioctl.0 kill.0 killpg.0 link.0 listen.0 \
D 5
	lseek.0 mkdir.0 mknod.0 mount.0 open.0 pipe.0 profil.0 \
E 5
I 5
	lseek.0 mkdir.0 mknod.0 mount.0 nfssvc.0 open.0 pipe.0 profil.0 \
E 6
I 6
	getuid.0 intro.0 ioctl.0 kill.0 link.0 listen.0 lseek.0 \
	mkdir.0 mkfifo.0 mknod.0 mount.0 nfssvc.0 open.0 pipe.0 profil.0 \
E 6
E 5
	ptrace.0 quota.0 read.0 readlink.0 reboot.0 recv.0 rename.0 \
	rmdir.0 select.0 send.0 setgroups.0 setpgrp.0 setquota.0 \
D 6
	setregid.0 setreuid.0 shutdown.0 sigblock.0 sigpause.0 \
	sigreturn.0 sigsetmask.0 sigstack.0 sigvec.0 socket.0 \
E 6
I 6
	setregid.0 setreuid.0 shutdown.0 \
	sigreturn.0 sigstack.0 socket.0 \
E 6
	socketpair.0 stat.0 statfs.0 swapon.0 symlink.0 sync.0 \
	syscall.0 truncate.0 umask.0 unlink.0 utimes.0 vfork.0 \
	vhangup.0 wait.0 write.0
E 3
MDIR=	${DESTDIR}/usr/man/cat2
E 2
TAGSFILE=tags

.s.o:
D 6
	@/lib/cpp ${FLAGS} -DPROF $*.s | ${AS} -o $*.o
E 6
I 6
	@${CPP} ${FLAGS} -DPROF $< | ${AS} -o $*.o
E 6
	@-ld -x -o profiled/$*.o -r $*.o
D 6
	/lib/cpp ${FLAGS} $*.s | ${AS} -o $*.o
E 6
I 6
	${CPP} ${FLAGS} $< | ${AS} -o $*.o
E 6
	@-ld -x -r $*.o
D 7
	@mv a.out $*.o
E 7
I 7
	@mv ${OBJDIR}a.out ${OBJDIR}$*.o
E 7

all: ${OBJS}
I 6
	cd ../library; rm -f ${OBJS}
I 7
	cd ${OBJDIR}.; ln ${OBJS} ../library
E 7
	cd ../profiled; rm -f ${OBJS}
D 7
	ln ${OBJS} ../library
	cd profiled; ln ${OBJS} ../../profiled
E 7
I 7
	cd ${OBJDIR}./profiled; ln ${OBJS} ../../profiled
E 7
E 6

D 2
link: ${OBJS}
E 2
I 2
D 6
link: ${OBJS} installman
E 2
	cd ../../library; rm -f ${OBJS}
	cd ../../profiled; rm -f ${OBJS}
	ln ${OBJS} ../../library
	cd profiled; ln ${OBJS} ../../../profiled

E 6
clean:
D 7
	rm -f *.o profiled/* a.out core
E 7
I 7
	rm -f ${OBJDIR}*.o profiled/* ${OBJDIR}a.out core
E 7

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep ${FLAGS} ${SRCS}

lint:

tags: ${SRCS}
I 6
	rm -f ${TAGSFILE}
E 6
	(P=`pwd`; \
D 6
	egrep "^ENTRY(.*)|^SYSCALL(.*)" ${SRCS} | /bin/sed \
E 6
I 6
	egrep "^ENTRY(.*)|^SYSCALL(.*)" ${SRCS} | sed \
E 6
"s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 $$P/\1 /^\2(\3\4$$/;" \
		>> ${TAGSFILE})

I 2
D 6
installman: ${MAN}
E 6
I 6
install: ${MAN}
E 6
	install -c -o bin -g bin -m 444 ${MAN} ${MDIR}
	rm -f ${MDIR}/dup2.0; ln ${MDIR}/dup.0 ${MDIR}/dup2.0
	rm -f ${MDIR}/errno.0; ln ${MDIR}/intro.0 ${MDIR}/errno.0
I 3
	rm -f ${MDIR}/fchdir.0; ln ${MDIR}/chdir.0 ${MDIR}/fchdir.0
	rm -f ${MDIR}/fchflags.0; ln ${MDIR}/chflags.0 ${MDIR}/fchflags.0
E 3
	rm -f ${MDIR}/fchmod.0; ln ${MDIR}/chmod.0 ${MDIR}/fchmod.0
	rm -f ${MDIR}/fchown.0; ln ${MDIR}/chown.0 ${MDIR}/fchown.0
	rm -f ${MDIR}/fstat.0; ln ${MDIR}/stat.0 ${MDIR}/fstat.0
I 3
	rm -f ${MDIR}/fstatfs.0; ln ${MDIR}/statfs.0 ${MDIR}/fstatfs.0
E 3
	rm -f ${MDIR}/ftruncate.0; ln ${MDIR}/truncate.0 ${MDIR}/ftruncate.0
	rm -f ${MDIR}/getegid.0; ln ${MDIR}/getgid.0 ${MDIR}/getegid.0
	rm -f ${MDIR}/geteuid.0; ln ${MDIR}/getuid.0 ${MDIR}/geteuid.0
	rm -f ${MDIR}/getppid.0; ln ${MDIR}/getpid.0 ${MDIR}/getppid.0
	rm -f ${MDIR}/lstat.0; ln ${MDIR}/stat.0 ${MDIR}/lstat.0
	rm -f ${MDIR}/readv.0; ln ${MDIR}/read.0 ${MDIR}/readv.0
	rm -f ${MDIR}/recvfrom.0; ln ${MDIR}/recv.0 ${MDIR}/recvfrom.0
	rm -f ${MDIR}/recvmsg.0; ln ${MDIR}/recv.0 ${MDIR}/recvmsg.0
	rm -f ${MDIR}/sbrk.0; ln ${MDIR}/brk.0 ${MDIR}/sbrk.0
	rm -f ${MDIR}/seek.0; ln ${MDIR}/lseek.0 ${MDIR}/seek.0
	rm -f ${MDIR}/sendmsg.0; ln ${MDIR}/send.0 ${MDIR}/sendmsg.0
	rm -f ${MDIR}/sendto.0; ln ${MDIR}/send.0 ${MDIR}/sendto.0
	rm -f ${MDIR}/sethostid.0; ln ${MDIR}/gethostid.0 ${MDIR}/sethostid.0
	rm -f ${MDIR}/sethostname.0; ln ${MDIR}/gethostname.0 ${MDIR}/sethostname.0
I 6
	rm -f ${MDIR}/setlogin.0; ln ${MDIR}/getlogin.0 ${MDIR}/setlogin.0
E 6
	rm -f ${MDIR}/setitimer.0; ln ${MDIR}/getitimer.0 ${MDIR}/setitimer.0
	rm -f ${MDIR}/setpriority.0; ln ${MDIR}/getpriority.0 ${MDIR}/setpriority.0
	rm -f ${MDIR}/setrlimit.0; ln ${MDIR}/getrlimit.0 ${MDIR}/setrlimit.0
	rm -f ${MDIR}/setsockopt.0; ln ${MDIR}/getsockopt.0 ${MDIR}/setsockopt.0
	rm -f ${MDIR}/settimeofday.0; ln ${MDIR}/gettimeofday.0 ${MDIR}/settimeofday.0
D 4
	rm -f ${MDIR}/umount.0; ln ${MDIR}/mount.0 ${MDIR}/umount.0
E 4
I 4
	rm -f ${MDIR}/unmount.0; ln ${MDIR}/mount.0 ${MDIR}/unmount.0
E 4
	rm -f ${MDIR}/wait3.0; ln ${MDIR}/wait.0 ${MDIR}/wait3.0
I 6
	rm -f ${MDIR}/waitpid.0; ln ${MDIR}/wait.0 ${MDIR}/waitpid.0
	rm -f ${MDIR}/wait4.0; ln ${MDIR}/wait.0 ${MDIR}/wait4.0
E 6
	rm -f ${MDIR}/writev.0; ln ${MDIR}/write.0 ${MDIR}/writev.0
E 2
E 1
