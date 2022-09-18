h30489
s 00014/00003/00169
d D 7.4 88/09/14 20:08:43 bostic 13 12
c add Berkeley specific header
e
s 00031/00031/00141
d D 7.3 88/08/27 15:49:27 karels 12 11
c rm 4.1 compat; start 4.3 compat: {send,recv}{,msg}; set up for wait4
e
s 00001/00001/00171
d D 7.2 87/07/10 16:59:18 mckusick 11 10
c syscall #65 changes from mremap to msync
e
s 00001/00001/00171
d D 7.1 86/06/05 00:08:37 mckusick 10 9
c 4.3BSD release version
e
s 00006/00002/00166
d D 6.6 86/02/02 21:03:10 karels 9 8
c sync with init_sysent.c
e
s 00023/00023/00145
d D 6.5 85/07/08 12:52:38 bloom 8 6
c upgrade for 4.3
e
s 00021/00021/00147
d R 6.5 85/07/08 10:44:37 bloom 7 6
c cleanup to make agree with current usage
e
s 00001/00001/00167
d D 6.4 85/06/09 11:13:36 mckusick 6 5
c 140 becomes adjtime
e
s 00007/00001/00161
d D 6.3 85/06/08 14:44:44 mckusick 5 4
c Add copyright
e
s 00001/00001/00161
d D 6.2 84/08/24 16:55:23 mckusick 4 3
c add `signal' as a system call
e
s 00000/00000/00162
d D 6.1 83/07/29 06:37:54 sam 3 2
c 4.2 distribution
e
s 00002/00008/00160
d D 4.2 83/05/21 15:39:12 sam 2 1
c cleanup
e
s 00168/00000/00000
d D 4.1 82/11/13 23:16:32 sam 1 0
c date and time created 82/11/13 23:16:32 by sam
e
u
U
t
T
I 1
D 2

E 2
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 10
 * Copyright (c) 1982 Regents of the University of California.
E 10
I 10
D 12
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 12
I 12
D 13
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 12
E 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
 * Copyright (c) 1982, 1986, 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 13
 *
 *	%W% (Berkeley) %G%
 */
E 5

/*
 * System call names.
 */
char *syscallnames[] = {
	"indir",		/*   0 = indir */
	"exit",			/*   1 = exit */
	"fork",			/*   2 = fork */
	"read",			/*   3 = read */
	"write",		/*   4 = write */
	"open",			/*   5 = open */
	"close",		/*   6 = close */
D 12
	"old wait",		/*   7 = old wait */
E 12
I 12
	"wait4",		/*   7 = wait4 */
E 12
D 8
	"old creat",		/*   8 = old creat */
	"old link",		/*   9 = link */
E 8
I 8
	"creat",		/*   8 = creat */
	"link",			/*   9 = link */
E 8
	"unlink",		/*  10 = unlink */
	"execv",		/*  11 = execv */
	"chdir",		/*  12 = chdir */
D 12
	"old time",		/*  13 = old time */
E 12
I 12
	"#13",			/*  13 = old time */
E 12
	"mknod",		/*  14 = mknod */
	"chmod",		/*  15 = chmod */
	"chown",		/*  16 = chown; now 3 args */
	"old break",		/*  17 = old break */
D 8
	"stat",			/*  18 = stat */
E 8
I 8
D 12
	"old stat",		/*  18 = old stat */
E 12
I 12
	"#18",			/*  18 = old stat */
E 12
E 8
	"lseek",		/*  19 = lseek */
	"getpid",		/*  20 = getpid */
	"mount",		/*  21 = mount */
D 8
	"old umount",		/*  22 = umount */
E 8
I 8
	"umount",		/*  22 = umount */
E 8
D 12
	"old setuid",		/*  23 = old setuid */
E 12
I 12
	"#23",			/*  23 = old setuid */
E 12
	"getuid",		/*  24 = getuid */
D 12
	"old stime",		/*  25 = old stime */
E 12
I 12
	"#25",			/*  25 = old stime */
E 12
	"ptrace",		/*  26 = ptrace */
D 12
	"old alarm",		/*  27 = old alarm */
D 8
	"fstat",		/*  28 = fstat */
	"old pause",		/*  29 = opause */
E 8
I 8
	"old fstat",		/*  28 = old fstat */
	"old pause",		/*  29 = old pause */
E 8
	"old utime",		/*  30 = old utime */
D 8
	"old stty",		/*  31 = old stty */
	"old gtty",		/*  32 = old gtty */
E 8
I 8
	"old stty - nosys",	/*  31 = old stty */
	"old gtty - nosys",	/*  32 = old gtty */
E 12
I 12
	"recvmsg",		/*  27 = recvmsg */
	"sendmsg",		/*  28 = sendmsg */
	"#29",			/*  29 = old pause */
	"#30",			/*  30 = old utime */
	"#31",			/*  31 = old stty */
	"#32",			/*  32 = old gtty */
E 12
E 8
	"access",		/*  33 = access */
D 12
	"old nice",		/*  34 = old nice */
	"old ftime",		/*  35 = old ftime */
E 12
I 12
	"#34",			/*  34 = old nice */
	"#35",			/*  35 = old ftime */
E 12
	"sync",			/*  36 = sync */
D 8
	"old kill",		/*  37 = old kill */
	"#38 -- 4.1a select",	/*  38 = nosys */
E 8
I 8
	"kill",			/*  37 = kill */
	"stat",			/*  38 = stat */
E 8
D 12
	"old setpgrp",		/*  39 = old setpgrp */
E 12
I 12
	"#39",			/*  39 = old setpgrp */
E 12
	"lstat",		/*  40 = lstat */
	"dup",			/*  41 = dup */
	"pipe",			/*  42 = pipe */
D 12
	"old times",		/*  43 = old times */
E 12
I 12
	"#43",			/*  43 = old times */
E 12
D 8
	"old profil - nosys",	/*  44 = old profil */
E 8
I 8
	"profil",		/*  44 = profil */
E 8
	"#45",			/*  45 = nosys */
D 12
	"old setgid",		/*  46 = old setgid */
E 12
I 12
	"#46",			/*  46 = old setgid */
E 12
	"getgid",		/*  47 = getgid */
D 12
	"old signal",		/*  48 = old sig */
E 12
I 12
	"#48",			/*  48 = old sig */
E 12
	"#49",			/*  49 = reserved for USG */
	"#50",			/*  50 = reserved for USG */
	"acct",			/*  51 = turn acct off/on */
D 12
	"old phys - nosys",	/*  52 = old set phys addr */
	"old lock - nosys",	/*  53 = old lock in core */
E 12
I 12
	"#52",			/*  52 = old set phys addr */
	"#52",			/*  53 = old lock in core */
E 12
	"ioctl",		/*  54 = ioctl */
	"reboot",		/*  55 = reboot */
D 12
	"old mpx - nosys",	/*  56 = old mpxchan */
E 12
I 12
	"#56",			/*  56 = old mpxchan */
E 12
	"symlink",		/*  57 = symlink */
	"readlink",		/*  58 = readlink */
	"execve",		/*  59 = execve */
	"umask",		/*  60 = umask */
	"chroot",		/*  61 = chroot */
D 8
	"#62",			/*  62 = nosys */
E 8
I 8
	"fstat",		/*  62 = fstat */
E 8
D 12
	"#63",			/*  63 = used internally */
E 12
I 12
	"#63",			/*  63 = unused */
E 12
	"getpagesize",		/*  64 = getpagesize */
D 11
	"mremap",		/*  65 = mremap */
E 11
I 11
	"msync",		/*  65 = msync */
E 11
	"vfork",		/*  66 = vfork */
D 12
	"old vread - read",	/*  67 = old vread */
	"old vwrite - write",	/*  68 = old vwrite */
E 12
I 12
	"#67",			/*  67 = old vread */
	"#68",			/*  68 = old vwrite */
E 12
	"sbrk",			/*  69 = sbrk */
	"sstk",			/*  70 = sstk */
	"mmap",			/*  71 = mmap */
	"old vadvise",		/*  72 = old vadvise */
	"munmap",		/*  73 = munmap */
	"mprotect",		/*  74 = mprotect */
	"madvise",		/*  75 = madvise */
	"vhangup",		/*  76 = vhangup */
D 12
	"old vlimit",		/*  77 = old vlimit */
E 12
I 12
	"#77",			/*  77 = old vlimit */
E 12
	"mincore",		/*  78 = mincore */
	"getgroups",		/*  79 = getgroups */
	"setgroups",		/*  80 = setgroups */
	"getpgrp",		/*  81 = getpgrp */
	"setpgrp",		/*  82 = setpgrp */
	"setitimer",		/*  83 = setitimer */
D 8
	"#84",			/*  84 = nosys */
	"old swapon",		/*  85 = old swapon */
E 8
I 8
D 12
	"wait",			/*  84 = wait */
E 12
I 12
	"old wait",		/*  84 = wait */
E 12
	"swapon",		/*  85 = swapon */
E 8
	"getitimer",		/*  86 = getitimer */
	"gethostname",		/*  87 = gethostname */
	"sethostname",		/*  88 = sethostname */
	"getdtablesize",	/*  89 = getdtablesize */
	"dup2",			/*  90 = dup2 */
	"getdopt",		/*  91 = getdopt */
D 8
	"wrap",			/*  92 = wrap */
E 8
I 8
	"fcntl",		/*  92 = fcntl */
E 8
	"select",		/*  93 = select */
	"setdopt",		/*  94 = setdopt */
	"fsync",		/*  95 = fsync */
	"setpriority",		/*  96 = setpriority */
	"socket",		/*  97 = socket */
	"connect",		/*  98 = connect */
	"accept",		/*  99 = accept */
	"getpriority",		/* 100 = getpriority */
D 12
	"send",			/* 101 = send */
	"recv",			/* 102 = recv */
E 12
I 12
	"old send",		/* 101 = send */
	"old recv",		/* 102 = recv */
E 12
D 8
	"socketaddr",		/* 103 = socketaddr */
E 8
I 8
	"sigreturn",		/* 103 = sigreturn */
E 8
	"bind",			/* 104 = bind */
D 8
	"#105",			/* 105 = nosys */
E 8
I 8
	"setsockopt",		/* 105 = setsockopt */
E 8
	"listen",		/* 106 = listen */
	"old vtimes",		/* 107 = old vtimes */
	"sigvec",		/* 108 = sigvec */
	"sigblock",		/* 109 = sigblock */
	"sigsetmask",		/* 110 = sigsetmask */
	"sigpause",		/* 111 = sigpause */
	"sigstack",		/* 112 = sigstack */
D 12
	"recvmsg",		/* 113 = recvmsg */
	"sendmsg",		/* 114 = sendmsg */
E 12
I 12
	"old recvmsg",		/* 113 = recvmsg */
	"old sendmsg",		/* 114 = sendmsg */
E 12
#ifdef TRACE
D 8
	"vtrace",		/* 115 = vtrace */
E 8
I 8
	"old vtrace",		/* 115 = old vtrace */
E 8
#else
	"#115",			/* 115 = nosys */
#endif
	"gettimeofday",		/* 116 = gettimeofday */
	"getrusage",		/* 117 = getrusage */
D 8
	"#118",			/* 118 = nosys */
E 8
I 8
	"getsockopt",		/* 118 = getsockopt */
I 9
#ifdef vax
E 9
E 8
	"resuba",		/* 119 = resuba */
I 9
#else
	"#119",			/* 119 = nosys */
#endif
E 9
	"readv",		/* 120 = readv */
	"writev",		/* 121 = writev */
	"settimeofday",		/* 122 = settimeofday */
	"fchown",		/* 123 = fchown */
	"fchmod",		/* 124 = fchmod */
	"recvfrom",		/* 125 = recvfrom */
	"setreuid",		/* 126 = setreuid */
	"setregid",		/* 127 = setregid */
	"rename",		/* 128 = rename */
	"truncate",		/* 129 = truncate */
	"ftruncate",		/* 130 = ftruncate */
	"flock",		/* 131 = flock */
D 8
	"portal",		/* 132 = portal */
E 8
I 8
D 12
	"old portal - nosys",	/* 132 = old portal */
E 12
I 12
	"#132",			/* 132 = old portal */
E 12
E 8
	"sendto",		/* 133 = sendto */
	"shutdown",		/* 134 = shutdown */
	"socketpair",		/* 135 = socketpair */
	"mkdir",		/* 136 = mkdir */
	"rmdir",		/* 137 = rmdir */
	"utimes",		/* 138 = utimes */
D 8
	"getdprop",		/* 139 = getdprop */
E 8
I 8
D 9
	"old getdprop - nosys",	/* 139 = old getdprop */
E 9
I 9
	"4.2 sigreturn",	/* 139 = old 4.2 sigreturn */
E 9
E 8
D 6
	"revoke",		/* 140 = revoke */
E 6
I 6
	"adjtime",		/* 140 = adjtime */
E 6
D 8
	"unmount",		/* 141 = unmount */
E 8
I 8
	"getpeername",		/* 141 = getpeername */
E 8
	"gethostid",		/* 142 = gethostid */
	"sethostid",		/* 143 = sethostid */
	"getrlimit",		/* 144 = getrlimit */
	"setrlimit",		/* 145 = setrlimit */
	"killpg",		/* 146 = killpg */
D 2
#ifdef MUSH
	"mu_msg",		/* 147 = mu_msg */
#else
E 2
D 4
	"#147",			/* 147 = nosys */
E 4
I 4
D 9
	"signal",		/* 147 = signal */
E 9
I 9
	"#147",			/* 147 = nosys */
E 9
E 4
D 2
#endif
#ifdef QUOTA
	"setquota",		/* 148 = quota */
E 2
I 2
	"setquota",		/* 148 = setquota */
E 2
D 8
	"qquota",		/* 149 = qquota */
E 8
I 8
	"quota",		/* 149 = quota */
E 8
D 2
#endif
E 2
I 2
	"getsockname",		/* 150 = getsockname */
E 2
};
E 1
