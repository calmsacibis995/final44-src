h61390
s 00008/00001/00016
d D 5.1 91/04/04 17:52:24 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00045/00010
d D 1.2 89/01/16 20:26:48 bostic 2 1
c new version from Chris Torek
e
s 00055/00000/00000
d D 1.1 86/02/25 16:04:46 sam 1 0
c date and time created 86/02/25 16:04:46 by sam
e
u
U
t
T
I 3
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 2
static	char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
D 3
#endif
E 3
I 3
#endif /* not lint */
E 3

#include "defs.h"
#include "optab.h"

struct optab optab[] = {
#define OP(a,b,c,d,e,f,g,h,i) {a,b,c,d,e,f,g,h,i}
D 2
#include "instrs"
0};

STRING systab[SYSSIZ] = {
	"indir",	"exit",		"fork",		"read",
	"write",	"open",		"close",	"owait",
	"creat",	"link",		"unlink",	"execv",
	"chdir",	"otime",	"mknod",	"chmod",
	"chown",	"obreak",	"ostat",	"lseek",
	"getpid",	"mount",	"umount",	"osetuid",
	"getuid",	"ostime",	"ptrace",	"oalarm",
	"ofstat",	"opause",	"outime",	"ostty",
	"ogtty",	"access",	"onice",	"oftime",
	"sync",		"kill",		"stat",		"osetpgrp",
	"lstat",	"dup",		"pipe",		"otimes",
	"profil",	0,		"osetgid",	"getgid",
	"osig",		0,		0,		"acct",
	"ophys",	"olock",	"ioctl",	"reboot",
	"ompxchan",	"symlink",	"readlink",	"execve",
	"umask",	"chroot",	"fstat",	0,
	"getpagesize",	"mremap",	"vfork",	"ovread",
	"ovwrite",	"sbrk",		"sstk",		"mmap",
	"ovadvise",	"munmap",	"mprotect",	"madvise",
	"vhangup",	"ovlimit",	"mincore",	"getgroups",
	"setgroups",	"getpgrp",	"setpgrp",	"setitimer",
	"wait",		"swapon",	"getitimer",	"gethostname",
	"sethostname",	"getdtablesize","dup2",		"getdopt",
	"fcntl",	"select",	"setdopt",	"fsync",
	"setpriority",	"socket",	"connect",	"accept",
	"getpriority",	"send",		"recv",		"osocketaddr",
	"bind",		"setsockopt",	"listen",	"ovtimes",
	"sigvec",	"sigblock",	"sigsetmask",	"sigpause",
	"sigstack",	"recvmsg",	"sendmsg",	"vtrace",
	"gettimeofday",	"getrusage",	"getsockopt",	"resuba",
	"readv",	"writev",	"settimeofday",	"fchown",
	"fchmod",	"recvfrom",	"setreuid",	"setregid",
	"rename",	"truncate",	"ftruncate",	"flock",
	0,		"sendto",	"shutdown",	"socketpair",
	"mkdir",	"rmdir",	"utimes",	0,
	0,		"getpeername",	"gethostid",	"sethostid",
	"getrlimit",	"setrlimit",	"killpg",	0,
	"quota",	"qquota",	"getsockname",
E 2
I 2
#include "instrs.adb"
	0
E 2
};

D 2
STRING	regname[] = { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
		"r8", "r9", "r10", "r11", "r12", "fp", "sp", "pc"};
E 2
I 2
char *regname[] = {
	"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
	"r8", "r9", "r10", "r11", "r12", "fp", "sp", "pc"
};
E 2
E 1
