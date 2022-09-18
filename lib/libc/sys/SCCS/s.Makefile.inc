h07602
s 00002/00002/00108
d D 8.3 94/10/24 10:08:37 mckusick 46 45
c unwhiteout => undelete to be more general
e
s 00002/00002/00108
d D 8.2 94/07/28 03:38:37 pendry 45 44
c changes for whiteouts and union filesystem
e
s 00000/00000/00110
d D 8.1 93/06/17 07:17:20 bostic 44 43
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00006/00105
d D 5.36 93/06/16 16:29:55 mckusick 43 41
c __indir => __syscall
e
s 00000/00000/00111
d R 8.1 93/06/16 11:11:21 mckusick 42 41
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00002/00108
d D 5.35 93/06/16 11:00:59 mckusick 41 39
c deprecate syscall
e
s 00000/00000/00110
d R 8.1 93/06/04 15:25:16 bostic 40 39
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00004/00105
d D 5.34 93/06/04 15:24:58 mckusick 39 37
c add indir.2 manual page
e
s 00000/00000/00109
d R 8.1 93/06/04 13:13:03 bostic 38 37
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00003/00103
d D 5.33 93/06/02 15:12:08 hibler 37 36
c add mlock/munlock
e
s 00002/00002/00104
d D 5.32 93/05/31 17:05:43 mckusick 36 35
c add ktrace man page
e
s 00001/00002/00105
d D 5.31 93/05/31 09:53:11 bostic 35 34
c delete sem_lock, sem_wakeup, they're not going to make it
e
s 00006/00004/00101
d D 5.30 93/05/25 15:13:50 mckusick 34 32
c add [f]pathconf
e
s 00003/00003/00102
d R 5.30 93/05/25 14:58:12 mckusick 33 32
c add [f]pathconf
e
s 00005/00006/00100
d D 5.29 93/05/25 14:54:22 mckusick 32 31
c update to reflect lseek, {g,s}etrlimit [f]truncate become STD
e
s 00034/00038/00072
d D 5.28 93/05/04 12:52:14 bostic 31 30
c add __sysctl, moving sysctl to ../gen/sysctl.c
e
s 00005/00007/00105
d D 5.27 93/04/04 13:29:57 mckusick 30 29
c {get,set}hostid goes to compat-43; getkerninfo goes away;
c {get,set}hostname and getpagesize go to gen
e
s 00004/00004/00108
d D 5.26 93/03/02 23:26:28 mckusick 29 28
c add sysctl
e
s 00009/00009/00103
d D 5.25 93/02/26 18:14:19 mckusick 28 27
c add manual pages for sigpending and revoke
e
s 00005/00006/00107
d D 5.24 93/02/10 11:17:32 bostic 27 26
c move setuid.3 -> setuid.2
e
s 00000/00019/00113
d D 5.23 93/02/04 19:01:20 ralph 26 25
c remove special case for mips since gcc is available now
e
s 00001/00000/00131
d D 5.22 93/02/03 15:34:13 mckusick 25 24
c seruid and setrgid move to compat-43; setuid.3 moves to setuid.2
e
s 00001/00001/00130
d D 5.21 92/07/12 12:52:00 heideman 24 23
c add __indir
e
s 00002/00002/00129
d D 5.20 92/07/09 16:11:55 mckusick 23 22
c add padding stubs for lseek, truncate, and ftruncate
e
s 00003/00003/00128
d D 5.19 92/07/09 14:25:04 mckusick 22 21
c move setreuid to compat-43; eliminate setregid
e
s 00004/00001/00127
d D 5.18 92/06/23 17:54:08 mckusick 21 20
c mmap needs a glue file to provide compatibility with GCC 1.X and GCC 2.X
e
s 00002/00001/00126
d D 5.17 92/05/27 23:05:25 mckusick 20 19
c add __ftruncate.o __getrlimit.o __lseek.o __setrlimit.o __truncate.o
e
s 00002/00002/00125
d D 5.16 92/05/19 12:14:45 mckusick 19 18
c get rid of deprecated async_daemon()
e
s 00001/00001/00126
d D 5.15 92/05/16 14:27:25 mckusick 18 17
c add indir syscall entry point
e
s 00002/00002/00125
d D 5.14 92/04/23 16:25:53 bostic 17 16
c need a sigstack man page
e
s 00002/00002/00125
d D 5.13 92/04/13 19:26:22 mckusick 16 15
c sigstack => sigaltstack
e
s 00026/00003/00101
d D 5.12 92/04/13 18:34:48 marc 15 13
c mips support, lfs syscalls, semaphore syscalls
e
s 00001/00000/00104
d R 5.12 91/11/12 09:42:35 bostic 14 13
c add revoke(2)
e
s 00017/00014/00088
d D 5.11 91/06/23 13:08:48 bostic 13 12
c add object files for rest of mmap calls
e
s 00008/00007/00094
d D 5.10 91/05/28 10:16:28 bostic 12 10
c add mmap.2, munmap.2, mprotect.2, msync.2, madvise.2, mincore.2
e
s 00003/00001/00100
d D 5.9.1.1 91/05/07 16:07:24 bostic 11 10
c branch for the 2nd network distribution
e
s 00002/00002/00099
d D 5.9 91/05/07 14:07:34 bostic 10 8
c can't add ret/rts to SYSCALL, expected to fall through; add RSYSCALL
e
s 00003/00001/00100
d D 5.8.1.1 91/05/07 11:06:03 bostic 9 8
c branch for the 2nd network distribution
e
s 00021/00008/00080
d D 5.8 91/04/28 15:29:06 bostic 8 7
c create PSEUDO printf's, just like ASM
e
s 00002/00002/00086
d D 5.7 91/04/28 14:26:54 bostic 7 6
c ret is machine specific, add in SYS.h as necessary
e
s 00002/00002/00086
d D 5.6 91/02/24 13:19:12 bostic 6 5
c exec family (except for exect) are now machine-independent
e
s 00001/00002/00087
d D 5.5 91/02/22 14:35:07 bostic 5 4
c a little less verbose, please
e
s 00002/00002/00087
d D 5.4 91/02/19 14:57:43 bostic 4 3
c rename setpgrp to setpgid, add setpgrp compat call, update man page
e
s 00001/00001/00088
d D 5.3 90/09/05 11:12:05 bostic 3 2
c BLDASM should depend on SYS.h
e
s 00004/00004/00085
d D 5.2 90/07/01 17:00:02 bostic 2 1
c add sigaction.2 sigprocmask.2 sigsuspend.2
e
s 00089/00000/00000
d D 5.1 90/06/23 16:23:42 bostic 1 0
c date and time created 90/06/23 16:23:42 by bostic
e
u
U
f b 
t
T
I 1
#	%W% (Berkeley) %G%

I 11
# Missing: profil.0, ptrace.0

E 11
# sys sources
.PATH: ${.CURDIR}/${MACHINE}/sys ${.CURDIR}/sys

# modules with non-default implementations on at least one architecture:
D 6
SRCS+=	Ovfork.s _exit.s _getlogin.s brk.s cerror.s execl.s execle.s exect.s \
	execv.s fork.s pipe.s ptrace.s reboot.s sbrk.s setlogin.s \
E 6
I 6
D 8
SRCS+=	Ovfork.s _exit.s _getlogin.s brk.s cerror.s exect.s \
	fork.s pipe.s ptrace.s reboot.s sbrk.s setlogin.s \
E 6
	sigpending.s sigprocmask.s sigreturn.s sigsuspend.s syscall.s
E 8
I 8
SRCS+=	Ovfork.s brk.s cerror.s exect.s fork.s pipe.s ptrace.s reboot.s \
	sbrk.s setlogin.s sigpending.s sigprocmask.s sigreturn.s \
	sigsuspend.s syscall.s
E 8

I 21
# glue to provide compatibility between GCC 1.X and 2.X
D 23
SRCS+=	mmap.c
E 23
I 23
D 32
SRCS+=	__ftruncate.c __lseek.c mmap.c __truncate.c
E 32
I 32
SRCS+=	ftruncate.c lseek.c mmap.c truncate.c
E 32
E 23

E 21
# modules with default implementations on all architectures:
D 8
BLDASM=	accept.o access.o acct.o adjtime.o async_daemon.o bind.o chdir.o \
E 8
I 8
D 19
ASM=	accept.o access.o acct.o adjtime.o async_daemon.o bind.o chdir.o \
E 19
I 19
D 31
ASM=	accept.o access.o acct.o adjtime.o bind.o chdir.o \
E 19
E 8
	chflags.o chmod.o chown.o chroot.o close.o connect.o dup.o dup2.o \
	execve.o fchdir.o fchflags.o fchmod.o fchown.o fcntl.o flock.o \
D 13
	fstat.o fstatfs.o fsync.o ftruncate.o getdirentries.o getdtablesize.o \
	getegid.o geteuid.o getfh.o getfsstat.o getgid.o getgroups.o \
	gethostid.o gethostname.o getitimer.o getkerninfo.o getpagesize.o \
	getpeername.o getpgrp.o getpid.o getppid.o getpriority.o getrlimit.o \
	getrusage.o getsockname.o getsockopt.o gettimeofday.o getuid.o \
	ioctl.o kill.o ktrace.o link.o listen.o lseek.o lstat.o mkdir.o \
	mkfifo.o mknod.o mmap.o mount.o nfssvc.o open.o profil.o quotactl.o \
	read.o readlink.o readv.o recvfrom.o recvmsg.o rename.o revoke.o \
	rmdir.o select.o sendmsg.o sendto.o setegid.o seteuid.o setgid.o \
D 4
	setgroups.o sethostid.o sethostname.o setitimer.o setpgrp.o \
E 4
I 4
	setgroups.o sethostid.o sethostname.o setitimer.o setpgid.o \
E 4
	setpriority.o setregid.o setreuid.o setrlimit.o setsid.o setsockopt.o \
	settimeofday.o setuid.o shutdown.o sigaction.o sigstack.o socket.o \
	socketpair.o stat.o statfs.o swapon.o symlink.o sync.o truncate.o \
	umask.o unlink.o unmount.o utimes.o vadvise.o wait4.o write.o writev.o
E 13
I 13
	fstat.o fstatfs.o fsync.o ftruncate.o getdirentries.o \
	getdtablesize.o getegid.o geteuid.o getfh.o getfsstat.o getgid.o \
D 30
	getgroups.o gethostid.o gethostname.o getitimer.o getkerninfo.o \
	getpagesize.o getpeername.o getpgrp.o getpid.o getppid.o \
E 30
I 30
	getgroups.o getitimer.o \
	getpeername.o getpgrp.o getpid.o getppid.o \
E 30
	getpriority.o getrlimit.o getrusage.o getsockname.o getsockopt.o \
D 15
	gettimeofday.o getuid.o ioctl.o kill.o ktrace.o link.o listen.o \
E 15
I 15
D 18
	gettimeofday.o getuid.o ioctl.o kill.o ktrace.o \
E 18
I 18
	gettimeofday.o getuid.o indir.o ioctl.o kill.o ktrace.o \
E 18
	lfs_bmapv.o lfs_markv.o lfs_segclean.o lfs_segwait.o \
	link.o listen.o \
E 15
	lseek.o lstat.o madvise.o mincore.o mkdir.o mkfifo.o mknod.o \
D 21
	mmap.o mount.o mprotect.o msync.o munmap.o nfssvc.o open.o \
E 21
I 21
	mount.o mprotect.o msync.o munmap.o nfssvc.o open.o \
E 21
	profil.o quotactl.o read.o readlink.o readv.o recvfrom.o recvmsg.o \
	rename.o revoke.o rmdir.o select.o sendmsg.o sendto.o setegid.o \
D 30
	seteuid.o setgid.o setgroups.o sethostid.o sethostname.o \
E 30
I 30
	seteuid.o setgid.o setgroups.o \
E 30
D 22
	setitimer.o setpgid.o setpriority.o setregid.o setreuid.o \
E 22
I 22
	setitimer.o setpgid.o setpriority.o \
E 22
	setrlimit.o setsid.o setsockopt.o settimeofday.o setuid.o \
D 16
	shutdown.o sigaction.o sigstack.o socket.o socketpair.o stat.o \
E 16
I 16
	shutdown.o sigaction.o sigaltstack.o socket.o socketpair.o stat.o \
E 16
D 29
	statfs.o swapon.o symlink.o sync.o truncate.o umask.o unlink.o \
D 15
	unmount.o utimes.o vadvise.o wait4.o write.o writev.o
E 15
I 15
	unmount.o utimes.o vadvise.o wait4.o write.o writev.o \
E 29
I 29
	statfs.o swapon.o symlink.o sync.o sysctl.o truncate.o umask.o \
	unlink.o unmount.o utimes.o vadvise.o wait4.o write.o writev.o \
E 29
D 20
	sem_lock.o sem_wakeup.o 
E 20
I 20
	sem_lock.o sem_wakeup.o \
E 31
I 31
ASM=	accept.o access.o acct.o adjtime.o bind.o chdir.o chflags.o chmod.o \
	chown.o chroot.o close.o connect.o dup.o dup2.o execve.o fchdir.o \
D 34
	fchflags.o fchmod.o fchown.o fcntl.o flock.o fstat.o fstatfs.o \
D 32
	fsync.o ftruncate.o getdirentries.o getdtablesize.o getegid.o \
E 32
I 32
	fsync.o getdirentries.o getdtablesize.o getegid.o \
E 34
I 34
	fchflags.o fchmod.o fchown.o fcntl.o flock.o fpathconf.o fstat.o \
	fstatfs.o fsync.o getdirentries.o getdtablesize.o getegid.o \
E 34
E 32
	geteuid.o getfh.o getfsstat.o getgid.o getgroups.o getitimer.o \
	getpeername.o getpgrp.o getpid.o getppid.o getpriority.o \
	getrlimit.o getrusage.o getsockname.o getsockopt.o gettimeofday.o \
D 43
	getuid.o indir.o ioctl.o kill.o ktrace.o lfs_bmapv.o lfs_markv.o \
E 43
I 43
	getuid.o ioctl.o kill.o ktrace.o lfs_bmapv.o lfs_markv.o \
E 43
D 32
	lfs_segclean.o lfs_segwait.o link.o listen.o lseek.o lstat.o \
E 32
I 32
	lfs_segclean.o lfs_segwait.o link.o listen.o lstat.o \
E 32
D 37
	madvise.o mincore.o mkdir.o mkfifo.o mknod.o mount.o mprotect.o \
D 34
	msync.o munmap.o nfssvc.o open.o profil.o quotactl.o read.o \
E 34
I 34
	msync.o munmap.o nfssvc.o open.o pathconf.o profil.o quotactl.o read.o \
E 37
I 37
	madvise.o mincore.o mkdir.o mkfifo.o mknod.o mlock.o mount.o \
	mprotect.o msync.o munlock.o munmap.o nfssvc.o open.o \
	pathconf.o profil.o quotactl.o read.o \
E 37
E 34
	readlink.o readv.o recvfrom.o recvmsg.o rename.o revoke.o rmdir.o \
	select.o sendmsg.o sendto.o setegid.o seteuid.o setgid.o \
	setgroups.o setitimer.o setpgid.o setpriority.o setrlimit.o \
	setsid.o setsockopt.o settimeofday.o setuid.o shutdown.o \
	sigaction.o sigaltstack.o socket.o socketpair.o stat.o statfs.o \
D 32
	swapon.o symlink.o sync.o truncate.o umask.o unlink.o unmount.o \
E 32
I 32
D 45
	swapon.o symlink.o sync.o umask.o unlink.o unmount.o \
E 45
I 45
D 46
	swapon.o symlink.o sync.o umask.o unlink.o unmount.o unwhiteout.o \
E 46
I 46
	swapon.o symlink.o sync.o umask.o undelete.o unlink.o unmount.o \
E 46
E 45
E 32
D 35
	utimes.o vadvise.o wait4.o write.o writev.o sem_lock.o \
D 32
	sem_wakeup.o __sysctl.o \
E 31
D 23
	__ftruncate.o __getrlimit.o __lseek.o __setrlimit.o __truncate.o
E 23
I 23
D 24
	__getrlimit.o __setrlimit.o
E 24
I 24
	__getrlimit.o __indir.o __setrlimit.o
E 32
I 32
	sem_wakeup.o __sysctl.o __indir.o
E 35
I 35
D 43
	utimes.o vadvise.o wait4.o write.o writev.o __sysctl.o __indir.o
E 43
I 43
	utimes.o vadvise.o wait4.o write.o writev.o __syscall.o __sysctl.o
E 43
E 35
E 32
E 24
E 23
E 20
E 15
E 13

D 8
OBJS+=	${BLDASM}
POBJS+=	${BLDASM:.o=.po}
CLEANFILES+=${BLDASM} ${BLDASM:.o=.po}
E 8
I 8
PSEUDO=	_exit.o _getlogin.o
E 8

D 3
${BLDASM}: /usr/include/sys/syscall.h
E 3
I 3
D 8
${BLDASM}: ${.CURDIR}/${MACHINE}/SYS.h /usr/include/sys/syscall.h
E 8
I 8
OBJS+=	${ASM} ${PSEUDO}
POBJS+=	${ASM:.o=.po} ${PSEUDO:.o=.po}
CLEANFILES+=${ASM} ${PSEUDO} ${POBJS} 

${ASM}: ${.CURDIR}/${MACHINE}/SYS.h /usr/include/sys/syscall.h
I 15
D 26
.if (${MACHINE} != "mips")
E 26
E 15
E 8
E 3
D 5
	@echo creating ${.PREFIX}.o
E 5
I 5
	@echo creating ${.PREFIX}.o ${.PREFIX}.po
E 5
D 7
	@printf '#include "SYS.h"\nSYSCALL(${.PREFIX})\nret\n' | \
E 7
I 7
D 10
	@printf '#include "SYS.h"\nSYSCALL(${.PREFIX})\n' | \
E 10
I 10
	@printf '#include "SYS.h"\nRSYSCALL(${.PREFIX})\n' | \
E 10
E 7
	    ${CPP} ${CFLAGS:M-[ID]*} ${AINC} | ${AS} -o ${.PREFIX}.o
	@${LD} -x -r ${.PREFIX}.o
	@mv a.out ${.PREFIX}.o
D 5
	@echo creating ${.PREFIX}.po
E 5
D 7
	@printf '#include "SYS.h"\nSYSCALL(${.PREFIX})\nret\n' | \
E 7
I 7
D 10
	@printf '#include "SYS.h"\nSYSCALL(${.PREFIX})\n' | \
E 10
I 10
	@printf '#include "SYS.h"\nRSYSCALL(${.PREFIX})\n' | \
E 10
I 8
	    ${CPP} -DPROF ${CFLAGS:M-[ID]*} ${AINC} | ${AS} -o ${.PREFIX}.po
	@${LD} -x -r ${.PREFIX}.po
	@mv a.out ${.PREFIX}.po
I 15
D 26
.else
	@echo creating ${.PREFIX}.o
	@printf '#include "SYS.h"\nSYSCALL(${.PREFIX})\n' > ${.PREFIX}.s
	@${AS} ${CFLAGS:M-[ID]*} ${AINC} -o ${.PREFIX}.o ${.PREFIX}.s
	@rm -f ${.PREFIX}.s
	@${LD} -x -r ${.PREFIX}.o
	@mv a.out ${.PREFIX}.o
.endif
E 26
E 15

${PSEUDO}: ${.CURDIR}/${MACHINE}/SYS.h /usr/include/sys/syscall.h
I 15
D 26
.if (${MACHINE} != "mips")
E 26
E 15
	@echo creating ${.PREFIX}.o ${.PREFIX}.po
	@printf '#include "SYS.h"\nPSEUDO(${.PREFIX},${.PREFIX:S/_//})\n' | \
	    ${CPP} ${CFLAGS:M-[ID]*} ${AINC} | ${AS} -o ${.PREFIX}.o
	@${LD} -x -r ${.PREFIX}.o
	@mv a.out ${.PREFIX}.o
	@printf '#include "SYS.h"\nPSEUDO(${.PREFIX},${.PREFIX:S/_//})\n' | \
E 8
E 7
	    ${CPP} -DPROF ${CFLAGS:M-[ID]*} ${AINC} | ${AS} -o ${.PREFIX}.po
	@${LD} -x -r ${.PREFIX}.po
	@mv a.out ${.PREFIX}.po
I 15
D 26
.else
	@echo creating ${.PREFIX}.o
	@printf '#include "SYS.h"\nPSEUDO(${.PREFIX},${.PREFIX:S/_//})\n' > \
		${.PREFIX}.s
	@${AS} ${CFLAGS:M-[ID]*} ${AINC} -o ${.PREFIX}.o ${.PREFIX}.s
	@rm -f ${.PREFIX}.s
	@${LD} -x -r ${.PREFIX}.o
	@mv a.out ${.PREFIX}.o
.endif
E 26
E 15

I 9
# Missing: profil.0, ptrace.0

E 9
D 19
MAN2+=	accept.0 access.0 acct.0 adjtime.0 async_daemon.0 bind.0 brk.0 \
E 19
I 19
D 31
MAN2+=	accept.0 access.0 acct.0 adjtime.0 bind.0 brk.0 \
E 19
	chdir.0 chflags.0 chmod.0 chown.0 chroot.0 close.0 connect.0 \
	dup.0 execve.0 _exit.0 fcntl.0 flock.0 fork.0 fsync.0 \
	getdirentries.0 getdtablesize.0 getfh.0 getfsstat.0 getgid.0 \
D 30
	getgroups.0 gethostid.0 gethostname.0 getitimer.0 getlogin.0 \
	getpagesize.0 getpeername.0 getpgrp.0 getpid.0 getpriority.0 \
E 30
I 30
	getgroups.0 getitimer.0 getlogin.0 \
	getpeername.0 getpgrp.0 getpid.0 getpriority.0 \
E 30
D 28
	getrlimit.0 getrusage.0 getsockname.0 getsockopt.0 \
	gettimeofday.0 getuid.0 intro.0 ioctl.0 kill.0 link.0 listen.0 \
D 12
	lseek.0 mkdir.0 mkfifo.0 mknod.0 mount.0 nfssvc.0 open.0 pipe.0 \
D 9
D 11
	profil.0 ptrace.0 quotactl.0 read.0 readlink.0 reboot.0 recv.0 \
E 11
I 11
	quotactl.0 read.0 readlink.0 reboot.0 recv.0 \
E 11
E 9
I 9
	quotactl.0 read.0 readlink.0 reboot.0 recv.0 \
E 9
D 4
	rename.0 rmdir.0 select.0 send.0 setgroups.0 setpgrp.0 \
E 4
I 4
	rename.0 rmdir.0 select.0 send.0 setgroups.0 setpgid.0 \
E 4
D 2
	setregid.0 setreuid.0 shutdown.0 sigreturn.0 \
	sigstack.0 socket.0 socketpair.0 stat.0 statfs.0 swapon.0 \
	symlink.0 sync.0 syscall.0 truncate.0 umask.0 unlink.0 utimes.0 \
	vfork.0 wait.0 write.0
E 2
I 2
	setregid.0 setreuid.0 shutdown.0 sigaction.0 sigprocmask.0 \
	sigreturn.0 sigstack.0 sigsuspend.0 socket.0 socketpair.0 \
	stat.0 statfs.0 swapon.0 symlink.0 sync.0 syscall.0 truncate.0 \
	umask.0 unlink.0 utimes.0 vfork.0 wait.0 write.0
E 12
I 12
	lseek.0 mkdir.0 mkfifo.0 mknod.0 madvise.0 mincore.0 mmap.0 mount.0 \
	mprotect.0 msync.0 munmap.0 nfssvc.0 open.0 pipe.0 profil.0 \
	ptrace.0 quotactl.0 read.0 readlink.0 reboot.0 recv.0 rename.0 \
E 28
I 28
	getrlimit.0 getrusage.0 getsockname.0 getsockopt.0 gettimeofday.0 \
	getuid.0 intro.0 ioctl.0 kill.0 link.0 listen.0 lseek.0 mkdir.0 \
	mkfifo.0 mknod.0 madvise.0 mincore.0 mmap.0 mount.0 mprotect.0 \
	msync.0 munmap.0 nfssvc.0 open.0 pipe.0 profil.0 ptrace.0 \
	quotactl.0 read.0 readlink.0 reboot.0 recv.0 rename.0 revoke.0 \
E 28
D 15
	rmdir.0 select.0 send.0 setgroups.0 setpgid.0 setregid.0 setreuid.0 \
E 15
I 15
D 22
	rmdir.0 select.0 send.0 setgroups.0 setpgid.0 setsid.0 setregid.0 \
D 17
	setreuid.0 \
E 15
D 16
	shutdown.0 sigaction.0 sigprocmask.0 sigreturn.0 sigstack.0 \
E 16
I 16
	shutdown.0 sigaction.0 sigprocmask.0 sigreturn.0 sigaltstack.0 \
E 17
I 17
	setreuid.0 shutdown.0 sigaction.0 sigprocmask.0 sigreturn.0 \
E 22
I 22
D 27
	rmdir.0 select.0 send.0 setgroups.0 setpgid.0 setsid.0 \
	shutdown.0 sigaction.0 sigprocmask.0 sigreturn.0 \
E 22
	sigaltstack.0 sigstack.0 \
E 17
E 16
	sigsuspend.0 socket.0 socketpair.0 stat.0 statfs.0 swapon.0 \
	symlink.0 sync.0 syscall.0 truncate.0 umask.0 unlink.0 utimes.0 \
	vfork.0 wait.0 write.0
E 27
I 27
	rmdir.0 select.0 send.0 setgroups.0 setpgid.0 setsid.0 setuid.0 \
D 28
	shutdown.0 sigaction.0 sigprocmask.0 sigreturn.0 sigaltstack.0 \
	sigstack.0 sigsuspend.0 socket.0 socketpair.0 stat.0 statfs.0 \
	swapon.0 symlink.0 sync.0 syscall.0 truncate.0 umask.0 unlink.0 \
	utimes.0 vfork.0 wait.0 write.0
E 28
I 28
	shutdown.0 sigaction.0 sigpending.0 sigprocmask.0 sigreturn.0 \
	sigaltstack.0 sigstack.0 sigsuspend.0 socket.0 socketpair.0  \
D 29
	stat.0 statfs.0 swapon.0 symlink.0 sync.0 syscall.0 truncate.0 \
	umask.0 unlink.0 utimes.0 vfork.0 wait.0 write.0
E 29
I 29
	stat.0 statfs.0 swapon.0 symlink.0 sync.0 syscall.0 sysctl.0 \
	truncate.0 umask.0 unlink.0 utimes.0 vfork.0 wait.0 write.0
E 31
I 31
MAN2+=	accept.0 access.0 acct.0 adjtime.0 bind.0 brk.0 chdir.0 chflags.0 \
	chmod.0 chown.0 chroot.0 close.0 connect.0 dup.0 execve.0 _exit.0 \
	fcntl.0 flock.0 fork.0 fsync.0 getdirentries.0 getdtablesize.0 \
	getfh.0 getfsstat.0 getgid.0 getgroups.0 getitimer.0 getlogin.0 \
	getpeername.0 getpgrp.0 getpid.0 getpriority.0 getrlimit.0 \
D 36
	getrusage.0 getsockname.0 getsockopt.0 gettimeofday.0 getuid.0 \
	intro.0 ioctl.0 kill.0 link.0 listen.0 lseek.0 mkdir.0 mkfifo.0 \
E 36
I 36
D 39
	getrusage.0 getsockname.0 getsockopt.0 gettimeofday.0 getuid.0 intro.0 \
	ioctl.0 kill.0 ktrace.0 link.0 listen.0 lseek.0 mkdir.0 mkfifo.0 \
E 36
D 34
	mknod.0 madvise.0 mincore.0 mmap.0 mount.0 mprotect.0 msync.0 \
E 34
I 34
D 37
	mknod.0 madvise.0 mincore.0 mmap.0 mount.0 mprotect.0 msync.0 munmap.0 \
E 37
I 37
	mknod.0 madvise.0 mincore.0 mlock.0 mmap.0 mount.0 mprotect.0 \
	msync.0 munmap.0 \
E 39
I 39
	getrusage.0 getsockname.0 getsockopt.0 gettimeofday.0 getuid.0 \
D 43
	indir.0 intro.0 ioctl.0 kill.0 ktrace.0 link.0 listen.0 lseek.0 \
E 43
I 43
	intro.0 ioctl.0 kill.0 ktrace.0 link.0 listen.0 lseek.0 \
E 43
	mkdir.0 mkfifo.0 mknod.0 madvise.0 mincore.0 mlock.0 mmap.0 \
	mount.0 mprotect.0 msync.0 munmap.0 \
E 39
E 37
	nfssvc.0 open.0 pathconf.0 pipe.0 profil.0 ptrace.0 quotactl.0 \
E 34
	munmap.0 nfssvc.0 open.0 pipe.0 profil.0 ptrace.0 quotactl.0 \
	read.0 readlink.0 reboot.0 recv.0 rename.0 revoke.0 rmdir.0 \
	select.0 send.0 setgroups.0 setpgid.0 setsid.0 setuid.0 shutdown.0 \
	sigaction.0 sigpending.0 sigprocmask.0 sigreturn.0 sigaltstack.0 \
	sigstack.0 sigsuspend.0 socket.0 socketpair.0 stat.0 statfs.0 \
D 41
	swapon.0 symlink.0 sync.0 syscall.0 truncate.0 umask.0 unlink.0 \
E 41
I 41
D 43
	swapon.0 symlink.0 sync.0 truncate.0 umask.0 unlink.0 \
E 43
I 43
	swapon.0 symlink.0 sync.0 syscall.0 truncate.0 umask.0 unlink.0 \
E 43
E 41
D 45
	utimes.0 vfork.0 wait.0 write.0
E 45
I 45
D 46
	unwhiteout.0 utimes.0 vfork.0 wait.0 write.0
E 46
I 46
	undelete.0 utimes.0 vfork.0 wait.0 write.0
E 46
E 45
E 31
E 29
E 28
E 27
E 12
E 2

MLINKS+=brk.2 sbrk.2
MLINKS+=dup.2 dup2.2
MLINKS+=chdir.2 fchdir.2
MLINKS+=chflags.2 fchflags.2
MLINKS+=chmod.2 fchmod.2
MLINKS+=chown.2 fchown.2
MLINKS+=getgid.2 getegid.2
D 30
MLINKS+=gethostid.2 sethostid.2
MLINKS+=gethostname.2 sethostname.2
E 30
MLINKS+=getitimer.2 setitimer.2
MLINKS+=getlogin.2 setlogin.2
MLINKS+=getpid.2 getppid.2
MLINKS+=getpriority.2 setpriority.2
MLINKS+=getrlimit.2 setrlimit.2
MLINKS+=getsockopt.2 setsockopt.2
MLINKS+=gettimeofday.2 settimeofday.2
MLINKS+=getuid.2 geteuid.2
I 39
D 41
MLINKS+=indir.2 _indir.2
E 41
I 41
D 43
MLINKS+=indir.2 __indir.2
MLINKS+=indir.2 syscall.2
E 43
E 41
E 39
MLINKS+=intro.2 errno.2
MLINKS+=lseek.2 seek.2
I 37
MLINKS+=mlock.2 munlock.2
E 37
MLINKS+=mount.2 unmount.2
I 34
MLINKS+=pathconf.2 fpathconf.2
E 34
MLINKS+=read.2 readv.2
MLINKS+=recv.2 recvfrom.2 recv.2 recvmsg.2
MLINKS+=send.2 sendmsg.2 send.2 sendto.2
I 25
MLINKS+=setuid.2 setegid.2 setuid.2 seteuid.2 setuid.2 setgid.2
E 25
MLINKS+=stat.2 fstat.2 stat.2 lstat.2
MLINKS+=statfs.2 fstatfs.2
I 43
MLINKS+=syscall.2 __syscall.2
E 43
MLINKS+=truncate.2 ftruncate.2
MLINKS+=wait.2 wait3.2 wait.2 wait4.2 wait.2 waitpid.2
MLINKS+=write.2 writev.2
E 1
