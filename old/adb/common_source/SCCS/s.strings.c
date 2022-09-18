h36344
s 00008/00001/00075
d D 5.2 91/04/04 18:02:00 bostic 2 1
c new copyright; att/bsd/shared
e
s 00076/00000/00000
d D 5.1 89/01/16 20:24:49 bostic 1 0
c new version from Chris Torek
e
u
U
t
T
I 2
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
#endif /* not lint */
E 2

/*
 * adb - readonly data
 */

#ifndef lint
char VERSION[] = "\nVERSION VM/VAX4.3	DATE %G%\n";
#endif

char	BADMOD[] = "bad modifier";
char	BADCOM[] = "bad command";
char	BADSYM[] = "symbol not found";
char	BADLOC[] = "automatic variable not found";
char	NOCFN[] = "c routine not found";
char	NOMATCH[] = "cannot locate value";
char	NOBKPT[] = "no breakpoint set";
char	NOADR[] = "address expected";
char	NOPCS[] = "no process";
char	BADVAR[] = "bad variable";
char	EXBKPT[] = "too many breakpoints";
char	ADDRWRAP[] = "address wrap around";
char	BADEQ[] = "unexpected `='";
char	BADWAIT[] = "wait error: process disappeared!";
char	ENDPCS[] = "process terminated";
char	NOFORK[] = "try again";
char	BADSYN[] = "syntax error";
char	NOEOR[] = "newline expected";
char	SZBKPT[] = "bkpt: command too long";
char	LONGFIL[] = "filename too long";
char	NOTOPEN[] = "cannot open";
char	TOODEEP[] = "$<< nesting too deep";

char	*syscalls[] = {
	"indir", "exit", "fork", "read",
	"write", "open", "close", "owait",
	"creat", "link", "unlink", "execv",
	"chdir", "otime", "mknod", "chmod",
	"chown", "obreak", "ostat", "lseek",
	"getpid", "mount", "umount", "osetuid",
	"getuid", "ostime", "ptrace", "oalarm",
	"ofstat", "opause", "outime", "ostty",
	"ogtty", "access", "onice", "oftime",
	"sync", "kill", "stat", "osetpgrp",
	"lstat", "dup", "pipe", "otimes",
	"profil", 0, "osetgid", "getgid",
	"osig", 0, 0, "acct",
	"ophys", "olock", "ioctl", "reboot",
	"ompxchan", "symlink", "readlink", "execve",
	"umask", "chroot", "fstat", 0,
	"getpagesize", "mremap", "vfork", "ovread",
	"ovwrite", "sbrk", "sstk", "mmap",
	"ovadvise", "munmap", "mprotect", "madvise",
	"vhangup", "ovlimit", "mincore", "getgroups",
	"setgroups", "getpgrp", "setpgrp", "setitimer",
	"wait", "swapon", "getitimer", "gethostname",
	"sethostname", "getdtablesize", "dup2", "getdopt",
	"fcntl", "select", "setdopt", "fsync",
	"setpriority", "socket", "connect", "accept",
	"getpriority", "send", "recv", "osocketaddr",
	"bind", "setsockopt", "listen", "ovtimes",
	"sigvec", "sigblock", "sigsetmask", "sigpause",
	"sigstack", "recvmsg", "sendmsg", "vtrace",
	"gettimeofday", "getrusage", "getsockopt", "resuba",
	"readv", "writev", "settimeofday", "fchown",
	"fchmod", "recvfrom", "setreuid", "setregid",
	"rename", "truncate", "ftruncate", "flock",
	0, "sendto", "shutdown", "socketpair",
	"mkdir", "rmdir", "utimes", 0,
	0, "getpeername", "gethostid", "sethostid",
	"getrlimit", "setrlimit", "killpg", 0,
	"quota", "qquota", "getsockname",
};
int	nsys = sizeof(syscalls) / sizeof(*syscalls);
E 1
