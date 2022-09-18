h39852
s 00018/00013/00366
d D 7.9 92/06/05 15:22:14 hibler 9 8
c merge latest Utah hp300 code including 68040 support
e
s 00002/00002/00377
d D 7.8 92/04/20 23:32:42 mckusick 8 7
c sigstack becomes osigstack
e
s 00005/00005/00374
d D 7.7 91/04/20 17:43:53 karels 7 6
c fix includes; use __CONCAT; execv now only for hpux
e
s 00002/00002/00377
d D 7.6 90/12/16 16:36:37 bostic 6 5
c kernel reorg
e
s 00041/00026/00350
d D 7.5 90/12/05 19:04:43 mckusick 5 4
c update from Mike Hibler for new VM and other machine support
e
s 00003/00004/00373
d D 7.4 90/06/22 18:02:15 hibler 4 3
c setuid and setgid can now use "standard" routines
e
s 00002/00002/00375
d D 7.3 90/06/08 18:20:03 mckusick 3 2
c creat => ocreat
e
s 00002/00002/00375
d D 7.2 90/05/25 15:36:59 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00377/00000/00000
d D 7.1 90/05/08 22:18:42 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 5
 * from: Utah $Hdr: hpux_sysent.c 1.14 89/08/14$
E 5
I 5
D 9
 * from: Utah $Hdr: hpux_sysent.c 1.1 90/07/09$
E 9
I 9
 * from: Utah $Hdr: hpux_sysent.c 1.18 92/01/20$
E 9
E 5
 *
 *	%W% (Berkeley) %G%
 */

/*
 * System call switch table.
 */

D 6
#include "param.h"
#include "systm.h"
E 6
I 6
D 7
#include "sys/param.h"
#include "sys/systm.h"
E 7
I 7
#include "param.h"
#include "systm.h"
E 7
E 6

int	nosys(),notimp();

/* 1.1 processes and protection */
int	getpid();
int	hpuxgetdomainname(), hpuxsetdomainname();
D 7
int	fork(),rexit(),execv(),execve();
E 7
I 7
int	fork(),rexit(),hpuxexecv(),execve();
E 7
int	getuid(),getgid(),getgroups(),setgroups();
I 4
int	setuid(),setgid();
E 4

/* 1.2 memory management */

/* 1.3 signals */
D 8
int	sigstack();
E 8
I 8
int	osigstack();
E 8
/* sigreturn is not HPUX, but we need it to make signals work */
int	sigreturn();

/* 1.4 timing and statistics */
int	gettimeofday(),settimeofday();
int	getitimer(),setitimer();

/* 1.5 descriptors */
int	dup2(),close();
int	select();

/* 1.6 resource controls */

/* 1.7 system operation support */
int	sync();

/* 2.2 file system */
int	chdir(),chroot();
int	mkdir(),rmdir(),getdirentries();
D 3
int	creat(),mknod(),unlink();
E 3
I 3
int	ocreat(),mknod(),unlink();
E 3
int	chown(),fchown(),chmod(),fchmod();
int	link(),symlink(),readlink(),rename();
int	lseek(),truncate(),ftruncate(),saccess(),fsync();

/* 2.3 communications */
int	pipe();

int	umask();		/* XXX */

/* 2.4 processes */

/* 2.5 terminals */

/* HPUX junk */
D 5
int	hpuxwait(),hpuxdup(),hpuxuname(),hpuxulimit();
E 5
I 5
int	hpuxwait(),hpuxdup(),hpuxutssys(),hpuxulimit();
E 5
int	hpuxadvise(), hpuxstat(), hpuxfstat(), hpuxlstat();
int	hpuxsigvec(), hpuxsigblock(), hpuxsigsetmask();
int	hpuxsigpause(), hpuxkill(), hpuxptrace();
int	hpuxopen(), hpuxfcntl(), hpuxread(), hpuxwrite();
int	hpuxreadv(), hpuxwritev(), hpuxioctl();
int	hpuxnetioctl(), hpuxrtprio();
int	hpuxgetcontext();
int	hpuxlockf(), hpuxgetpgrp2(), hpuxsetpgrp2();
I 5
int     hpuxsetresuid(), hpuxsetresgid();
int	hpuxsigprocmask(), hpuxsigaction(), hpuxsigpending(), hpuxsigsuspend();
E 5
D 2
int	hpuxwait3();
E 2
I 2
int	hpuxwait3(), hpuxwaitpid();
I 5
D 9
int	hpuxgetaccess();
E 9
I 9
int	hpuxgetaccess(), hpuxsysconf();
E 9
E 5
E 2
#ifdef SYSVSHM
int	hpuxshmctl(),hpuxshmget(),hpuxshmat(),hpuxshmdt();
#endif
int	hpuxsemctl(),hpuxsemget(),hpuxsemop();

/*
 * Old 4.2 compatibility routines.
 * Still needed for HP-UX?
 */
D 7
#define	compat(n, name)	n, o/**/name
E 7
I 7
#define	compat(n, name)	n, __CONCAT(o,name)
E 7

int	ohpuxtime();		/* now use gettimeofday */
int	ohpuxstime();		/* now use settimeofday */
int	ohpuxalarm();		/* now use setitimer */
int	ohpuxutime();		/* now use utimes */
int	ohpuxpause();		/* now use sigpause */
int	ohpuxnice();		/* now use setpriority,getpriority */
int	ohpuxftime();		/* now use gettimeofday */
int	ohpuxtimes();		/* now use getrusage */
int	ohpuxstat();		/* now use stat */
int	ohpuxfstat();		/* now use fstat */
int	ohpuxssig();		/* now use sigvec, etc */
int	ohpuxgtty();		/* now use hpuxioctl */
int	ohpuxstty();		/* now use hpuxioctl */
int	ohpuxsetpgrp();		/* SYS5 style setpgrp */
D 4
int	ohpuxsetuid();		/* now use setreuid */
int	ohpuxsetgid();		/* now use setregid */
E 4

/* BEGIN JUNK */
int	profil();		/* 'cuz sys calls are interruptible */
int	vfork();		/* awaiting fork w/ copy on write */
int	obreak();		/* awaiting new sbrk */
/* END JUNK */

/*
 * Reserved/unimplemented system calls in the range 0-150 inclusive
 * are reserved for use in future Berkeley releases.
 * Additional system calls implemented in vendor and other
 * redistributions should be placed in the reserved range at the end
 * of the current calls.
 */
struct sysent hpuxsysent[] = {
	0, nosys,			/*   0 = out of range */
	1, rexit,			/*   1 = exit */
	0, fork,			/*   2 = fork */
	3, hpuxread,			/*   3 = read */
	3, hpuxwrite,			/*   4 = write */
	3, hpuxopen,			/*   5 = open */
	1, close,			/*   6 = close */
	1, hpuxwait,			/*   7 = HPUX style wait */
D 3
	2, creat,			/*   8 = creat */
E 3
I 3
	2, ocreat,			/*   8 = ocreat */
E 3
	2, link,			/*   9 = link */
	1, unlink,			/*  10 = unlink */
D 7
	2, execv,			/*  11 = execv */
E 7
I 7
	2, hpuxexecv,			/*  11 = execv */
E 7
	1, chdir,			/*  12 = chdir */
	compat(1,hpuxtime),		/*  13 = old time */
	3, mknod,			/*  14 = mknod */
	2, chmod,			/*  15 = chmod */
	3, chown,			/*  16 = chown; now 3 args */
	1, obreak,			/*  17 = old break */
	compat(2,hpuxstat),		/*  18 = old stat */
	3, lseek,			/*  19 = lseek */
	0, getpid,			/*  20 = getpid */
	3, notimp,			/*  21 = mount */
	1, notimp,			/*  22 = umount */
D 4
	compat(1,hpuxsetuid),		/*  23 = HPUX old setuid */
E 4
I 4
	1, setuid,			/*  23 = setuid */
E 4
	0, getuid,			/*  24 = getuid */
	compat(1,hpuxstime),		/*  25 = old stime */
	4, hpuxptrace,			/*  26 = ptrace */
	compat(1,hpuxalarm),		/*  27 = old alarm */
	compat(2,hpuxfstat),		/*  28 = old fstat */
	compat(0,hpuxpause),		/*  29 = opause */
	compat(2,hpuxutime),		/*  30 = old utime */
	compat(2,hpuxstty),		/*  31 = HPUX style stty */
	compat(2,hpuxgtty),		/*  32 = HPUX style gtty */
	2, saccess,			/*  33 = access */
	compat(1,hpuxnice),		/*  34 = old nice */
	compat(1,hpuxftime),		/*  35 = old ftime */
	0, sync,			/*  36 = sync */
	2, hpuxkill,			/*  37 = HPUX style kill */
	2, hpuxstat,			/*  38 = HPUX style stat */
	compat(1,hpuxsetpgrp),		/*  39 = HPUX style old setpgrp */
	2, hpuxlstat,			/*  40 = HPUX style lstat */
	1, hpuxdup,			/*  41 = HPUX style dup */
	0, pipe,			/*  42 = pipe */
	compat(1,hpuxtimes),		/*  43 = old times */
	4, profil,			/*  44 = profil */
	4, notimp,			/*  45 = ki_syscall */
D 4
	compat(1,hpuxsetgid),		/*  46 = HPUX old setgid */
E 4
I 4
	1, setgid,			/*  46 = setgid */
E 4
	0, getgid,			/*  47 = getgid */
	compat(2,hpuxssig),		/*  48 = old sig */
	0, nosys,			/*  49 = reserved for USG */
	0, nosys,			/*  50 = reserved for USG */
	1, notimp,			/*  51 = acct */
	0, nosys,			/*  52 = old set phys addr */
	0, nosys,			/*  53 = old lock in core */
	3, hpuxioctl,			/*  54 = HPUX ioctl */
	4, notimp,			/*  55 = reboot */
	2, symlink,			/*  56 = symlink */
D 5
	3, hpuxuname,			/*  57 = HPUX uname */
E 5
I 5
	3, hpuxutssys,			/*  57 = HPUX utssys */
E 5
	3, readlink,			/*  58 = readlink */
	3, execve,			/*  59 = execve */
	1, umask,			/*  60 = umask */
	1, chroot,			/*  61 = chroot */
	3, hpuxfcntl,			/*  62 = fcntl (swapped with fstat) */
	2, hpuxulimit,			/*  63 = HPUX ulimit */
	0, nosys,			/*  64 = nosys */
	0, nosys,			/*  65 = nosys */
	0, vfork,			/*  66 = vfork */
I 9
	/* XXX hp-ux has 0 arguments, don't blame me! */
E 9
	0, hpuxread,			/*  67 = old vread */
	0, hpuxwrite,			/*  68 = old vwrite */
	0, nosys,			/*  69 = nosys */
	0, nosys,			/*  70 = nosys */
	0, nosys,			/*  71 = nosys */
	0, nosys,			/*  72 = nosys */
	0, nosys,			/*  73 = nosys */
	3, notimp,			/*  74 = mprotect */
	0, nosys,			/*  75 = nosys */
	0, nosys,			/*  76 = nosys */
	0, nosys,			/*  77 = nosys */
	0, nosys,			/*  78 = nosys */
	2, getgroups,			/*  79 = getgroups */
	2, setgroups,			/*  80 = setgroups */
	1, hpuxgetpgrp2,		/*  81 = HPUX getpgrp2 */
	2, hpuxsetpgrp2,		/*  82 = HPUX setpgrp2 */
	3, setitimer,			/*  83 = setitimer */
	3, hpuxwait3,			/*  84 = wait3 */
D 9
	1, notimp,			/*  85 = swapon */
E 9
I 9
	5, notimp,			/*  85 = swapon */
E 9
	2, getitimer,			/*  86 = getitimer */
	0, nosys,			/*  87 = nosys */
	0, nosys,			/*  88 = nosys */
	0, nosys,			/*  89 = nosys */
	2, dup2,			/*  90 = dup2 */
D 9
	2, nosys,			/*  91 = nosys */
E 9
I 9
	0, nosys,			/*  91 = nosys */
E 9
	2, hpuxfstat,			/*  92 = fstat (swapped with fcntl) */
	5, select,			/*  93 = select */
	0, nosys,			/*  94 = nosys */
	1, fsync,			/*  95 = fsync */
	0, nosys,			/*  96 = nosys */
	3, nosys,			/*  97 = nosys */
	2, nosys,			/*  98 = nosys */
	2, nosys,			/*  99 = nosys */
	0, nosys,			/* 100 = nosys */
	0, nosys,			/* 101 = nosys */
	0, nosys,			/* 102 = nosys */
	1, sigreturn,			/* 103 = sigreturn (not HPUX) */
	2, nosys,			/* 104 = nosys */
	0, nosys,			/* 105 = nosys */
	0, nosys,			/* 106 = nosys */
	0, nosys,			/* 107 = nosys */
	3, hpuxsigvec,			/* 108 = sigvec */
	1, hpuxsigblock,		/* 109 = sigblock */
	1, hpuxsigsetmask,		/* 110 = sigsetmask */
	1, hpuxsigpause,		/* 111 = sigpause */
D 8
	2, sigstack,			/* 112 = sigstack */
E 8
I 8
	2, osigstack,			/* 112 = sigstack */
E 8
	0, nosys,			/* 113 = nosys */
	0, nosys,			/* 114 = nosys */
	0, nosys,			/* 115 = nosys */
	2, gettimeofday,		/* 116 = gettimeofday */
	0, nosys,			/* 117 = nosys */
	0, nosys,			/* 118 = nosys */
	3, notimp,			/* 119 = hpib_io_stub */
	3, hpuxreadv,			/* 120 = readv */
	3, hpuxwritev,			/* 121 = writev */
	2, settimeofday,		/* 122 = settimeofday */
	3, fchown,			/* 123 = fchown */
	2, fchmod,			/* 124 = fchmod */
	0, nosys,			/* 125 = nosys */
D 5
	3, notimp,			/* 126 = setresuid */
	3, notimp,			/* 127 = setresgid */
E 5
I 5
	3, hpuxsetresuid,		/* 126 = setresuid */
	3, hpuxsetresgid,		/* 127 = setresgid */
E 5
	2, rename,			/* 128 = rename */
	2, truncate,			/* 129 = truncate */
	2, ftruncate,			/* 130 = ftruncate */
	0, nosys,			/* 131 = nosys */
D 9
	1, notimp,			/* 132 = sysconf */
E 9
I 9
	1, hpuxsysconf,			/* 132 = sysconf */
E 9
	0, nosys,			/* 133 = nosys */
	0, nosys,			/* 134 = nosys */
	0, nosys,			/* 135 = nosys */
	2, mkdir,			/* 136 = mkdir */
	1, rmdir,			/* 137 = rmdir */
	0, nosys,			/* 138 = nosys */
	0, nosys,			/* 139 = internal (4.2 sigreturn) */
	0, nosys,			/* 140 = nosys */
	0, nosys,			/* 141 = nosys */
	0, nosys,			/* 142 = nosys */
	0, nosys,			/* 143 = nosys */
	0, nosys,			/* 144 = nosys */
	0, nosys,			/* 145 = nosys */
	0, nosys,			/* 146 = nosys */
	0, nosys,			/* 147 = nosys */
	0, nosys,			/* 148 = nosys */
	0, nosys,			/* 149 = nosys */
	0, nosys,			/* 150 = nosys */
	/*
	 * HPUX specific syscalls
	 */
	3, notimp,			/* 151 = privgrp */
	2, hpuxrtprio,			/* 152 = rtprio */
	1, notimp,			/* 153 = plock */
I 9
	/* XXX this is gone in 7.0 */
E 9
	2, hpuxnetioctl,		/* 154 = BSD networking */
	4, hpuxlockf,			/* 155 = HPUX lockf */
	3, hpuxsemget,			/* 156 = semget */
	4, hpuxsemctl,			/* 157 = semctl */
	3, hpuxsemop,			/* 158 = semop */
	2, notimp,			/* 159 = msgget */
	3, notimp,			/* 160 = msgctl */
	4, notimp,			/* 161 = msgsnd */
	5, notimp,			/* 162 = msgrcv */
#ifdef SYSVSHM
	3, hpuxshmget,			/* 163 = shmget */
	3, hpuxshmctl,			/* 164 = shmctl */
	3, hpuxshmat,			/* 165 = shmat */
	1, hpuxshmdt,			/* 166 = shmdt */
#else
	3, notimp,			/* 163 = shmget */
	3, notimp,			/* 164 = shmctl */
	3, notimp,			/* 165 = shmat */
	1, notimp,			/* 166 = shmdt */
#endif
	1, hpuxadvise,			/* 167 = m68020_advise */
D 9
	0, notimp,			/* 168 = dux_notconfigured */
E 9
I 9
	2, notimp,			/* 168 = nsp_init */
E 9
	3, notimp,			/* 169 = cluster */
	4, notimp,			/* 170 = mkrnod */
	0, nosys,			/* 171 = nosys */
D 9
	0, notimp,			/* 172 = dux_notconfigured */
E 9
I 9
	0, notimp,			/* 172 = unsp_open */
E 9
	0, nosys,			/* 173 = nosys */
	3, hpuxgetcontext,		/* 174 = getcontext */
	0, nosys,			/* 175 = nosys */
	0, nosys,			/* 176 = nosys */
	0, nosys,			/* 177 = nosys */
	0, notimp,			/* 178 = lsync */
	0, nosys,			/* 179 = nosys */
	0, notimp,			/* 180 = mysite */
D 9
	0, notimp,			/* 181 = returnzero */
E 9
I 9
	1, notimp,			/* 181 = sitels */
E 9
	0, nosys,			/* 182 = nosys */
	0, nosys,			/* 183 = nosys */
D 9
	0, nosys,			/* 184 = nosys */
E 9
I 9
	4, notimp,			/* 184 = dskless_stats */
E 9
	0, nosys,			/* 185 = nosys */
D 5
	3, nosys,			/* 186 = setacl */
	3, nosys,			/* 187 = fsetacl */
	3, nosys,			/* 188 = getacl */
	3, nosys,			/* 189 = fgetacl */
	6, nosys,			/* 190 = getaccess */
	0, nosys,			/* 191 = getaudid */
	1, nosys,			/* 192 = setaudid */
	0, nosys,			/* 193 = getaudproc */
	1, nosys,			/* 194 = setaudproc */
	2, nosys,			/* 195 = getevent */
	2, nosys,			/* 196 = setevent */
	1, nosys,			/* 197 = audwrite */
	1, nosys,			/* 198 = audswitch */
	4, nosys,			/* 199 = audctl */
E 5
I 5
	3, notimp,			/* 186 = setacl */
	3, notimp,			/* 187 = fsetacl */
	3, notimp,			/* 188 = getacl */
	3, notimp,			/* 189 = fgetacl */
	6, hpuxgetaccess,		/* 190 = getaccess */
	0, notimp,			/* 191 = getaudid */
	1, notimp,			/* 192 = setaudid */
	0, notimp,			/* 193 = getaudproc */
	1, notimp,			/* 194 = setaudproc */
	2, notimp,			/* 195 = getevent */
	2, notimp,			/* 196 = setevent */
	1, notimp,			/* 197 = audwrite */
	1, notimp,			/* 198 = audswitch */
	4, notimp,			/* 199 = audctl */
E 5
D 2
	3, nosys,			/* 200 = waitpid */
E 2
I 2
	3, hpuxwaitpid,			/* 200 = waitpid */
E 2
	0, nosys,			/* 201 = nosys */
D 5
	2, nosys,			/* 202 = netioctl */
E 5
I 5
D 9
	2, notimp,			/* 202 = netioctl */
E 9
I 9
	0, nosys,			/* 202 = nosys */
E 9
E 5
	6, nosys,			/* 203 = nosys */
	0, nosys,			/* 204 = nosys */
	0, nosys,			/* 205 = nosys */
	9, nosys,			/* 206 = nosys */
	0, nosys,			/* 207 = nosys */
	0, nosys,			/* 208 = nosys */
	6, nosys,			/* 209 = nosys */
	5, nosys,			/* 210 = nosys */
	0, nosys,			/* 211 = nosys */
	0, nosys,			/* 212 = nosys */
	0, nosys,			/* 213 = nosys */
	0, nosys,			/* 214 = nosys */
	0, nosys,			/* 215 = nosys */
	0, nosys,			/* 216 = nosys */
	0, nosys,			/* 217 = nosys */
	0, nosys,			/* 218 = nosys */
	0, nosys,			/* 219 = nosys */
	4, nosys,			/* 220 = nosys */
D 9
	10, nosys,			/* 221 = nosys */
E 9
I 9
	10,nosys,			/* 221 = nosys */
E 9
	0, nosys,			/* 222 = nosys */
	0, nosys,			/* 223 = nosys */
	0, nosys,			/* 224 = nosys */
	2, notimp,			/* 225 = pathconf */
	2, notimp,			/* 226 = fpathconf */
	0, nosys,			/* 227 = nosys */
	0, nosys,			/* 228 = nosys */
	0, notimp,			/* 229 = async_daemon */
	3, notimp,			/* 230 = nfs_fcntl */
	4, getdirentries,		/* 231 = getdirentries */
	2, hpuxgetdomainname,		/* 232 = getdomainname */
	2, notimp,			/* 233 = nfs_getfh */
	4, notimp,			/* 234 = vfsmount */
	1, notimp,			/* 235 = nfs_svc */
	2, hpuxsetdomainname,		/* 236 = setdomainname */
D 9
	0, notimp,			/* 237 = statfs */
	0, notimp,			/* 238 = fstatfs */
E 9
I 9
	2, notimp,			/* 237 = statfs */
	2, notimp,			/* 238 = fstatfs */
E 9
D 5
	3, notimp,			/* 239 = sigaction */
	3, notimp,			/* 240 = sigprocmask */
	1, notimp,			/* 241 = sigpending */
	1, notimp,			/* 242 = sigsuspend */
E 5
I 5
	3, hpuxsigaction,		/* 239 = sigaction */
	3, hpuxsigprocmask,		/* 240 = sigprocmask */
	1, hpuxsigpending,		/* 241 = sigpending */
	1, hpuxsigsuspend,		/* 242 = sigsuspend */
I 9
	4, notimp,			/* 243 = fsctl */
	0, nosys,			/* 244 = nosys */
	3, notimp,			/* 245 = pstat */
E 9
E 5
};
int	hpuxnsysent = sizeof (hpuxsysent) / sizeof (hpuxsysent[0]);

E 1
