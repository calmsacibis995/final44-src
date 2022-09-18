h64654
s 00007/00004/00301
d D 7.3 92/06/05 15:22:09 hibler 3 2
c merge latest Utah hp300 code including 68040 support
e
s 00016/00004/00301
d D 7.2 90/12/05 19:04:46 mckusick 2 1
c update from Mike Hibler for new VM and other machine support
e
s 00305/00000/00000
d D 7.1 90/05/08 22:18:41 mckusick 1 0
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
D 2
 * from: Utah $Hdr: hpux_syscalls.c 1.8 89/08/23$
E 2
I 2
D 3
 * from: Utah $Hdr: hpux_syscalls.c 1.1 90/07/09$
E 3
I 3
 * from: Utah $Hdr: hpux_syscalls.c 1.10 92/01/20$
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

#ifdef HPUXCOMPAT

/*
 * HPUX System call names.
 */
char *hpuxsyscallnames[] = {
	"indir",		/*   0 = indir */
	"exit",			/*   1 = exit */
	"fork",			/*   2 = fork */
	"read",			/*   3 = read */
	"write",		/*   4 = write */
	"open",			/*   5 = open */
	"close",		/*   6 = close */
	"wait",			/*   7 = old wait */
	"creat",		/*   8 = creat */
	"link",			/*   9 = link */
	"unlink",		/*  10 = unlink */
	"execv",		/*  11 = execv */
	"chdir",		/*  12 = chdir */
	"old time",		/*  13 = old time */
	"mknod",		/*  14 = mknod */
	"chmod",		/*  15 = chmod */
	"chown",		/*  16 = chown; now 3 args */
	"old break",		/*  17 = old break */
	"old stat",		/*  18 = old stat */
	"lseek",		/*  19 = lseek */
	"getpid",		/*  20 = getpid */
	"mount",		/*  21 = mount */
	"umount",		/*  22 = umount */
	"old setuid",		/*  23 = old setuid */
	"getuid",		/*  24 = getuid */
	"old stime",		/*  25 = old stime */
	"ptrace",		/*  26 = ptrace */
	"old alarm",		/*  27 = old alarm */
	"old fstat",		/*  28 = old fstat */
	"old pause",		/*  29 = old pause */
	"old utime",		/*  30 = old utime */
	"old stty",		/*  31 = old stty */
	"old gtty",		/*  32 = old gtty */
	"access",		/*  33 = access */
	"old nice",		/*  34 = old nice */
	"old ftime",		/*  35 = old ftime */
	"sync",			/*  36 = sync */
	"kill",			/*  37 = kill */
	"stat",			/*  38 = stat */
	"old setpgrp",		/*  39 = old setpgrp */
	"lstat",		/*  40 = lstat */
	"dup",			/*  41 = dup */
	"pipe",			/*  42 = pipe */
	"old times",		/*  43 = old times */
	"profil",		/*  44 = profil */
	"ki_syscall",		/*  45 = ki_syscall */
	"old setgid",		/*  46 = old setgid */
	"getgid",		/*  47 = getgid */
	"old signal",		/*  48 = old sig */
	"#49",			/*  49 = reserved for USG */
	"#50",			/*  50 = reserved for USG */
	"acct",			/*  51 = turn acct off/on */
	"old phys - nosys",	/*  52 = old set phys addr */
	"old lock - nosys",	/*  53 = old lock in core */
	"ioctl",		/*  54 = ioctl */
	"reboot",		/*  55 = reboot */
D 3
	"old mpx - nosys",	/*  56 = old mpxchan */
E 3
I 3
	"symlink",		/*  56 = symlink */
E 3
D 2
	"uname",		/*  57 = uname */
E 2
I 2
	"utssys",		/*  57 = utssys */
E 2
	"readlink",		/*  58 = readlink */
	"execve",		/*  59 = execve */
	"umask",		/*  60 = umask */
	"chroot",		/*  61 = chroot */
	"fcntl",		/*  62 = fcntl */
	"ulimit",		/*  63 = ulimit */
	"#64",			/*  64 = nosys */
	"#65",			/*  65 = nosys */
	"vfork",		/*  66 = vfork */
	"old vread - read",	/*  67 = old vread */
	"old vwrite - write",	/*  68 = old vwrite */
	"#69",			/*  69 = nosys */
	"#70",			/*  70 = nosys */
	"#71",			/*  71 = nosys */
	"#72",			/*  72 = nosys */
	"#73",			/*  73 = nosys */
	"mprotect",		/*  74 = mprotect */
	"#75",			/*  75 = nosys */
	"#76",			/*  76 = nosys */
	"#77",			/*  77 = nosys */
	"#78",			/*  78 = nosys */
	"getgroups",		/*  79 = getgroups */
	"setgroups",		/*  80 = setgroups */
	"getpgrp2",		/*  81 = getpgrp2 */
	"setpgrp2",		/*  82 = setpgrp2 */
	"setitimer",		/*  83 = setitimer */
	"wait3",		/*  84 = wait3 */
	"swapon",		/*  85 = swapon */
	"getitimer",		/*  86 = getitimer */
	"#87",			/*  87 = nosys */
	"#88",			/*  88 = nosys */
	"#89",			/*  89 = nosys */
	"dup2",			/*  90 = dup2 */
	"#91",			/*  91 = nosys */
	"fstat",		/*  92 = fstat */
	"select",		/*  93 = select */
	"#94",			/*  94 = nosys */
	"fsync",		/*  95 = fsync */
	"#96",			/*  96 = nosys */
	"#97",			/*  97 = nosys */
	"#98",			/*  98 = nosys */
	"#99",			/*  99 = nosys */
	"#100",			/* 100 = nosys */
	"#101",			/* 101 = nosys */
	"#102",			/* 102 = nosys */
	"sigreturn",		/* 103 = BSD sigreturn */
	"#104",			/* 104 = nosys */
	"#105",			/* 105 = nosys */
	"#106",			/* 106 = nosys */
	"#107",			/* 107 = nosys */
	"sigvec",		/* 108 = sigvec */
	"sigblock",		/* 109 = sigblock */
	"sigsetmask",		/* 110 = sigsetmask */
	"sigpause",		/* 111 = sigpause */
	"sigstack",		/* 112 = sigstack */
	"#113",			/* 113 = nosys */
	"#114",			/* 114 = nosys */
	"#115",			/* 115 = nosys */
	"gettimeofday",		/* 116 = gettimeofday */
	"#117",			/* 117 = nosys */
	"#118",			/* 118 = nosys */
	"hpib_io_stub",		/* 119 = hpib_io_stub */
	"readv",		/* 120 = readv */
	"writev",		/* 121 = writev */
	"settimeofday",		/* 122 = settimeofday */
	"fchown",		/* 123 = fchown */
	"fchmod",		/* 124 = fchmod */
	"#125",			/* 125 = nosys */
	"setresuid",		/* 126 = setresuid */
	"setresgid",		/* 127 = setresgid */
	"rename",		/* 128 = rename */
	"truncate",		/* 129 = truncate */
	"ftruncate",		/* 130 = ftruncate */
	"#131",			/* 131 = nosys */
	"sysconf",		/* 132 = sysconf */
	"#133",			/* 133 = nosys */
	"#134",			/* 134 = nosys */
	"#135",			/* 135 = nosys */
	"mkdir",		/* 136 = mkdir */
	"rmdir",		/* 137 = rmdir */
	"utimes",		/* 138 = utimes */
	"#139",			/* 139 = nosys */
	"#140",			/* 140 = nosys */
	"#141",			/* 141 = nosys */
	"#142",			/* 142 = nosys */
	"#143",			/* 143 = nosys */
	"#144",			/* 144 = nosys */
	"#145",			/* 145 = nosys */
	"#146",			/* 146 = nosys */
	"#147",			/* 147 = nosys */
	"#148",			/* 148 = nosys */
	"#149",			/* 149 = nosys */
	"#150",			/* 150 = nosys */
	/*
	 * HPUX specific syscalls
	 */
	"privgrp",			/* 151 = privgrp */
	"rtprio",			/* 152 = rtprio */
	"plock",			/* 153 = plock */
	"netioctl",			/* 154 = netioctl */
	"lockf",			/* 155 = lockf */
	"semget",			/* 156 = semget */
	"semctl",			/* 157 = semctl */
	"semop",			/* 158 = semop */
	"msgget",			/* 159 = msgget */
	"msgctl",			/* 160 = msgctl */
	"msgsnd",			/* 161 = msgsnd */
	"msgrcv",			/* 162 = msgrcv */
	"shmget",			/* 163 = shmget */
	"shmctl",			/* 164 = shmctl */
	"shmat",			/* 165 = shmat */
	"shmdt",			/* 166 = shmdt */
	"m68020_advise",		/* 167 = m68020_advise */
	"#168",				/* 168 = nosys */
	"cluster",			/* 169 = cluster */
	"mkrnod",			/* 170 = mkrnod */
	"#171",				/* 171 = nosys */
	"#172",				/* 172 = nosys */
	"#173",				/* 173 = nosys */
	"getcontext",			/* 174 = getcontext */
	"#175",				/* 175 = nosys */
	"#176",				/* 176 = nosys */
	"#177",				/* 177 = nosys */
	"lsync",			/* 178 = lsync */
	"#179",				/* 179 = nosys */
	"mysite",			/* 180 = mysite */
	"returnzero",			/* 181 = returnzero */
	"#182",				/* 182 = nosys */
	"#183",				/* 183 = nosys */
	"#184",				/* 184 = nosys */
	"#185",				/* 185 = nosys */
	"setacl",			/* 186 = setacl */
	"fsetacl",			/* 187 = fsetacl */
	"getacl",			/* 188 = getacl */
	"fgetacl",			/* 189 = fgetacl */
	"getaccess",			/* 190 = getaccess */
	"getaudid",			/* 191 = getaudid */
	"setaudid",			/* 192 = setaudid */
	"getaudproc",			/* 193 = getaudproc */
	"setaudproc",			/* 194 = setaudproc */
	"getevent",			/* 195 = getevent */
	"setevent",			/* 196 = setevent */
	"audwrite",			/* 197 = audwrite */
	"audswitch",			/* 198 = audswitch */
	"audctl",			/* 199 = audctl */
	"waitpid",			/* 200 = waitpid */
	"#201",				/* 201 = nosys */
D 3
	"netioctl",			/* 202 = netioctl */
E 3
I 3
	"#202",				/* 202 = nosys */
E 3
	"#203",				/* 203 = nosys */
	"#204",				/* 204 = nosys */
	"#205",				/* 205 = nosys */
	"#206",				/* 206 = nosys */
	"#207",				/* 207 = nosys */
	"#208",				/* 208 = nosys */
	"#209",				/* 209 = nosys */
	"#210",				/* 210 = nosys */
	"#211",				/* 211 = nosys */
	"#212",				/* 212 = nosys */
	"#213",				/* 213 = nosys */
	"#214",				/* 214 = nosys */
	"#215",				/* 215 = nosys */
	"#216",				/* 216 = nosys */
	"#217",				/* 217 = nosys */
	"#218",				/* 218 = nosys */
	"#219",				/* 219 = nosys */
	"#220",				/* 220 = nosys */
	"#221",				/* 221 = nosys */
	"#222",				/* 222 = nosys */
	"#223",				/* 223 = nosys */
	"#224",				/* 224 = nosys */
	"pathconf",			/* 225 = pathconf */
	"fpathconf",			/* 226 = fpathconf */
	"#227",				/* 227 = nosys */
	"#228",				/* 228 = nosys */
	"async_daemon",			/* 229 = aync_daemon */
	"nfs_fcntl",			/* 230 = nfs_fcntl */
	"getdirentries",		/* 231 = getdirentries */
	"getdomainname",		/* 232 = getdomainname */
	"nfs_getfh",			/* 233 = nfs_getfh */
	"vfsmount",			/* 234 = vfsmount */
	"nfs_svc",			/* 235 = nfs_svc */
D 3
	"fstatfs",			/* 236 = setdomainname */
E 3
I 3
	"setdomainname",		/* 236 = setdomainname */
E 3
	"statfs",			/* 237 = statfs */
	"fstatfs",			/* 238 = fstatfs */
	"sigaction",			/* 239 = sigaction */
	"sigprocmask",			/* 240 = sigprocmask */
	"sigpending",			/* 241 = sigpending */
	"sigsuspend",			/* 242 = sigsuspend */
I 3
	"fsctl",			/* 243 = fsctl */
	"#244",				/* 244 = nosys */
	"pstat",			/* 245 = pstat */
E 3
};

char *hpuxbsdipcnames[] = {
	"socket",
	"listen",
	"bind",
	"accept",
	"connect",
	"recv",
	"send",
	"shutdown",
	"getsockname",
	"setsockopt",
	"sendto",
	"recvfrom",
	"getpeername",
	"0x3FB",
	"0x3FC",
	"0x3FD",
	"0x3FE",
	"0x3FF",
	"0x400",
	"0x401",
	"0x402",
	"0x403",
	"0x404",
	"0x405",
	"0x406",
	"0x407",
	"0x408",
	"0x409",
	"0x40A",
	"getsockopt",
	"0x40C",
	"0x40D"
};
#endif
E 1
