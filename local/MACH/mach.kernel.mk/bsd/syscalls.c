/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	syscalls.c,v $
 * Revision 2.11  91/06/25  17:03:18  mbj
 * 	Synchronized with init_sysent.c.
 * 
 * Revision 2.10  91/04/02  11:05:48  mbj
 * 	Put in i386 where vax is tested.  They use the same svc
 * 	numbering.
 * 	[90/08/14            rvb]
 * 
 * Revision 2.9  90/08/30  10:59:12  bohman
 * 	Changes for mac2.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.8  89/07/11  13:12:55  jjc
 * 	Changed "#ifdef sun3" into "if defined(sun3) || defined(sun4)".
 * 	[89/05/06            jjc]
 * 
 * Revision 2.7  89/05/30  10:35:46  rvb
 * 	Added syscalls for Mips/Ultrix
 * 	[89/05/30  08:25:10  rvb]
 * 
 * Revision 2.6  89/04/22  15:21:37  gm0w
 * 	Removed MACH_VFS names for old syscalls.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.5  89/03/09  19:31:29  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  14:58:59  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/09  04:33:22  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.2  89/01/18  00:41:44  jsb
 * 	Make this file reflect reality (as defined by init_sysent.c).
 * 	This was long overdue!
 * 	[89/01/16            jsb]
 * 
 * 20-Aug-87  Peter King (king) at NeXT
 *	Added syscalls relevant to MACH_VFS and SUN_RPC
 *
 *  1-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 28-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Added VMTP.
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merge VICE changes -- include vice.h and change to #if VICE.
 *
 * 22-Jan-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	romp: added getfpemulator syscall for fp compatibility.
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  added syscalls for ITC/Andrew remote file system.
 *
 * 27-Jul-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	romp: added exect syscall for debuggers on the RT.
 *
 */ 
 
#include <vice.h>
#include <mach_vmtp.h>
#include <quota.h>
#include <sun_rpc.h>

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)syscalls.c	7.1 (Berkeley) 6/5/86
 */


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
	"old wait",		/*   7 = old wait */
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
	"old stty - nosys",	/*  31 = old stty */
	"old gtty - nosys",	/*  32 = old gtty */
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
	"#45",			/*  45 = nosys */
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
	"old mpx - nosys",	/*  56 = old mpxchan */
	"symlink",		/*  57 = symlink */
	"readlink",		/*  58 = readlink */
	"execve",		/*  59 = execve */
	"umask",		/*  60 = umask */
	"chroot",		/*  61 = chroot */
	"fstat",		/*  62 = fstat */
	"#63",			/*  63 = used internally */
	"getpagesize",		/*  64 = getpagesize */
	"mremap",		/*  65 = mremap */
	"vfork",		/*  66 = vfork */
	"old vread - read",	/*  67 = old vread */
	"old vwrite - write",	/*  68 = old vwrite */
	"sbrk",			/*  69 = sbrk */
	"sstk",			/*  70 = sstk */
	"mmap",			/*  71 = mmap */
	"old vadvise",		/*  72 = old vadvise */
	"munmap",		/*  73 = munmap */
	"mprotect",		/*  74 = mprotect */
	"madvise",		/*  75 = madvise */
	"vhangup",		/*  76 = vhangup */
	"old vlimit",		/*  77 = old vlimit */
	"mincore",		/*  78 = mincore */
	"getgroups",		/*  79 = getgroups */
	"setgroups",		/*  80 = setgroups */
	"getpgrp",		/*  81 = getpgrp */
	"setpgrp",		/*  82 = setpgrp */
	"setitimer",		/*  83 = setitimer */
	"wait",			/*  84 = wait */
	"swapon",		/*  85 = swapon */
	"getitimer",		/*  86 = getitimer */
	"gethostname",		/*  87 = gethostname */
	"sethostname",		/*  88 = sethostname */
	"getdtablesize",	/*  89 = getdtablesize */
	"dup2",			/*  90 = dup2 */
	"getdopt",		/*  91 = getdopt */
	"fcntl",		/*  92 = fcntl */
	"select",		/*  93 = select */
	"setdopt",		/*  94 = setdopt */
	"fsync",		/*  95 = fsync */
	"setpriority",		/*  96 = setpriority */
	"socket",		/*  97 = socket */
	"connect",		/*  98 = connect */
	"accept",		/*  99 = accept */
	"getpriority",		/* 100 = getpriority */
	"send",			/* 101 = send */
	"recv",			/* 102 = recv */
	"sigreturn",		/* 103 = sigreturn */
	"bind",			/* 104 = bind */
	"setsockopt",		/* 105 = setsockopt */
	"listen",		/* 106 = listen */
	"old vtimes",		/* 107 = old vtimes */
	"sigvec",		/* 108 = sigvec */
	"sigblock",		/* 109 = sigblock */
	"sigsetmask",		/* 110 = sigsetmask */
	"sigpause",		/* 111 = sigpause */
	"sigstack",		/* 112 = sigstack */
	"recvmsg",		/* 113 = recvmsg */
	"sendmsg",		/* 114 = sendmsg */
#ifdef	TRACE
	"old vtrace",		/* 115 = old vtrace */
#else
	"#115",			/* 115 = nosys */
#endif
	"gettimeofday",		/* 116 = gettimeofday */
	"getrusage",		/* 117 = getrusage */
	"getsockopt",		/* 118 = getsockopt */
#if	defined(vax) || defined(i386)
	"resuba",		/* 119 = resuba */
#else
	"#119",			/* 119 = nosys */
#endif
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
	"old portal - nosys",	/* 132 = old portal */
	"sendto",		/* 133 = sendto */
	"shutdown",		/* 134 = shutdown */
	"socketpair",		/* 135 = socketpair */
	"mkdir",		/* 136 = mkdir */
	"rmdir",		/* 137 = rmdir */
	"utimes",		/* 138 = utimes */
	"4.2 sigreturn",	/* 139 = old 4.2 sigreturn */
	"adjtime",		/* 140 = adjtime */
	"getpeername",		/* 141 = getpeername */
	"gethostid",		/* 142 = gethostid */
	"sethostid",		/* 143 = sethostid */
	"getrlimit",		/* 144 = getrlimit */
	"setrlimit",		/* 145 = setrlimit */
	"killpg",		/* 146 = killpg */
	"#147",			/* 147 = nosys */
	"setquota",		/* 148 = setquota */
	"quota",		/* 149 = quota */
	"getsockname",		/* 150 = getsockname */
	/*
	 * Syscalls 151-180 inclusive are reserved for vendor-specific
	 * system calls.  (This includes various calls added for compatibity
	 * with other Unix variants.)
	 */
#define	GENERIC	1
#ifdef	ibmrt
#undef	GENERIC
	"exect",		/* 151 = exect */
	"#152",			/* 152 */
	"getfpemulator",	/* 153 = getfpemulator */
	"iopen",		/* 154 = iopen */
	"iread",		/* 155 = iread */
	"iwrite",		/* 156 = iwrite */
	"iinc",			/* 157 = iinc */
	"idec",			/* 158 = idec */
	"pioctl",		/* 159 = pioctl */
	"setpag",		/* 160 = setpag */
	"icreate",		/* 161 = icreate */
	"#162",			/* 162 */
	"#163",			/* 163 */
	"#164",			/* 164 */
	"#165",			/* 165 */
	"#166",			/* 166 */
	"getfloatstate",	/* 167 = getfloatstate */
	"setfloatstate",	/* 168 = setfloatstate */
	"nfs_svc",		/* 169 = nfs_svc */
	"getdirentries",	/* 170 = getdirentries */
	"statfs",		/* 171 = statfs */
	"fstatfs",		/* 172 = fstatfs */
	"unmount",		/* 173 = unmount */
	"async_daemon",		/* 174 = async_daemon */
	"nfs_getfh",		/* 175 = getfh */
	"getdomainname",	/* 176 = getdomainname */
	"setdomainname",	/* 177 = setdomainname */
	"quotactl",		/* 178 = quotactl */
	"exportfs",		/* 179 = exportfs */
	"vfsmount",		/* 180 = mount */
#endif	ibmrt
#ifdef	sun
#undef	GENERIC
	"#151",			/* 151 */
	"#152",			/* 152 */
	"#153",			/* 153 */
	"#154",			/* 154 */
	"nfs_svc",		/* 155 = nfs_svc */
	"getdirentries",	/* 156 = getdirentries */
	"statfs",		/* 157 = statfs */
	"fstatfs",		/* 158 = fstatfs */
	"unmount",		/* 159 = unmount */
	"async_daemon",		/* 160 = async_daemon */
	"nfs_getfh",		/* 161 = getfh */
	"getdomainname",	/* 162 = getdomainname */
	"setdomainname",	/* 163 = setdomainname */
	"#164",			/* 164 */
	"quotactl",		/* 165 = quotactl */
	"exportfs",		/* 166 = exportfs */
	"vfsmount",		/* 167 = mount */
	"pioctl",		/* 168 = pioctl */
	"setpag",		/* 169 = setpag */
	"icreate",		/* 170 = icreate */
	"iopen",		/* 171 = iopen */
	"iread",		/* 172 = iread */
	"iwrite",		/* 173 = iwrite */
	"iinc",			/* 174 = iinc */
	"idec",			/* 175 = idec */
	"#176",			/* 176 */
	"#177",			/* 177 */
	"#178",			/* 178 */
	"#179",			/* 179 */
	"afs_call",		/* 180 = afs_call */
#endif	sun
#if	defined(vax) || defined(i386)
#undef	GENERIC
	"icreate",		/* 151 = icreate */
	"iopen",		/* 152 = iopen */
	"iread",		/* 153 = iread */
	"iwrite",		/* 154 = iwrite */
	"iinc",			/* 155 = iinc */
	"idec",			/* 156 = idec */
	"pioctl",		/* 157 = pioctl */
	"setpag",		/* 158 = setpag */
	"nfs_svc",		/* 159 = nfs_svc */
	"statfs",		/* 160 = statfs */
	"fstatfs",		/* 161 = fstatfs */
	"unmount",		/* 162 = unmount */
	"async_daemon",		/* 163 = async_daemon */
	"getdirentries",	/* 164 = getdirentries */
	"nfs_getfh",		/* 165 = getfh */
	"quotactl",		/* 166 = quotactl */
	"exportfs",		/* 167 = exportfs */
	"vfsmount",		/* 168 = mount */
	"getdomainname",	/* 169 = getdomainname */
	"setdomainname",	/* 170 = setdomainname */
	"pioctl",		/* 171 = pioctl */
	"setpag",		/* 172 = setpag */
	"icreate",		/* 173 = icreate */
	"iopen",		/* 174 = iopen */
	"iread",		/* 175 = iread */
	"iwrite",		/* 176 = iwrite */
	"iinc",			/* 177 = iinc */
	"idec",			/* 178 = idec */
	"afs_call",		/* 179 = afs_call */
	"#180",			/* 180 */
#endif	defined(vax) || defined(i386)
#if	defined(balance)
#undef	GENERIC
	"getdirentries",	/* 151 = getdirentries */
	"tmp_ctl",		/* 152 = tmp_ctl */
	"universe",		/* 153 = universe */
	"#154",			/* 154 */
	"nfs_svc",		/* 155 = nfs_svc */
	"#156",			/* 156 */
	"statfs",		/* 157 = statfs */
	"fstatfs",		/* 158 = fstatfs */
	"unmount",		/* 159 = unmount */
	"async_daemon",		/* 160 = async_daemon */
	"nfs_getfh",		/* 161 = getfh */
	"getdomainname",	/* 162 = getdomainname */
	"setdomainname",	/* 163 = setdomainname */
	"#164",			/* 164 */
	"quotactl",		/* 165 = quotactl */
	"exportfs",		/* 166 = exportfs */
	"vfsmount",		/* 167 = mount */
	"pioctl",		/* 168 = pioctl */
	"setpag",		/* 169 = setpag */
	"icreate",		/* 170 = icreate */
	"iopen",		/* 171 = iopen */
	"iread",		/* 172 = iread */
	"iwrite",		/* 173 = iwrite */
	"iinc",			/* 174 = iinc */
	"idec",			/* 175 = idec */
	"#176",			/* 176 */
	"#177",			/* 177 */
	"#178",			/* 178 */
	"#179",			/* 179 */
	"afs_call",		/* 180 = afs_call */
#endif	defined(balance)
#ifdef	mips
#undef	GENERIC
	"sysmips",		/* 151 = sysmips */
	"#152",			/* 152 = cacheflush */
	"#153",			/* 153 = cachectl */
	"#154",			/* 154 = debug */
	"#155",			/* 155 = nosys */
	"#156",			/* 156 = nosys */
	"#157",			/* 157 = old nfs_mount */
	"nfs_svc",		/* 158 = nfs_svc */
	"getdirentries",	/* 159 = getdirentries */
	"statfs",		/* 160 = statfs */
	"fstatfs",		/* 161 = fstatfs */
	"unmount",		/* 162 = unmount */
	"async_daemon",		/* 163 = async_daemon */
	"nfs_getfh",		/* 164 = get file handle */
	"getdomainname",	/* 165 = getdomainname */
	"setdomainname",	/* 166 = setdomainname */
	"#167",			/* 167 = old pcfs_mount */
	"quotactl",		/* 168 = quotactl */
	"exportfs",		/* 169 = exportfs */
	"vfsmount",		/* 170 = mount */
	"#171",			/* 171 = mipshwconf */
#ifdef PMAX
	/* Ultrix system calls that Umips doesn't have or are incompatible */
	"msgctl",		/* 172 = msgctl */
	"msgget",		/* 173 = msgget */
	"msgrcv",		/* 174 = msgrcv */
	"msgsnd",		/* 175 = msgsnd */
	"semctl",		/* 176 = semctl */
	"semget",		/* 177 = semget */
	"semop",		/* 178 = semop */
	"uname",		/* 179 = uname */
	"smsys",		/* 180 = shared memory */
#else	PMAX
	"#172",			/* 172 */
	"#173",			/* 173 */
	"#174",			/* 174 */
	"#175",			/* 175 */
	"#176",			/* 176 */
	"#177",			/* 177 */
	"#178",			/* 178 */
	"#179",			/* 179 */
	"#180",			/* 180 */
#endif	PMAX
#endif	mips
#ifdef	multimax
#undef	GENERIC
	"old_mapfrcounter",	/* 151 = old_mapfrcounter */
	"mapfrcounter",		/* 152 = mapfrcounter */
	"#153",			/* 153 */
	"#154",			/* 154 */
	"nfs_svc",		/* 155 = nfs_svc */
	"getdirentries",	/* 156 = getdirentries */
	"statfs",		/* 157 = statfs */
	"fstatfs",		/* 158 = fstatfs */
	"unmount",		/* 159 = unmount */
	"async_daemon",		/* 160 = async_daemon */
	"nfs_getfh",		/* 161 = getfh */
	"getdomainname",	/* 162 = getdomainname */
	"setdomainname",	/* 163 = setdomainname */
	"#164",			/* 164 */
	"quotactl",		/* 165 = quotactl */
	"exportfs",		/* 166 = exportfs */
	"vfsmount",		/* 167 = mount */
	"pioctl",		/* 168 = pioctl */
	"setpag",		/* 169 = setpag */
	"icreate",		/* 170 = icreate */
	"iopen",		/* 171 = iopen */
	"iread",		/* 172 = iread */
	"iwrite",		/* 173 = iwrite */
	"iinc",			/* 174 = iinc */
	"idec",			/* 175 = idec */
	"#176",			/* 176 */
	"#177",			/* 177 */
	"#178",			/* 178 */
	"#179",			/* 179 */
	"afs_call",		/* 180 = afs_call */
#endif	multimax
#ifdef	luna
#undef	GENERIC
#ifdef	luna88k
	"sysomron",		/* 151 = sysomron functions (luna88k) */
#else	luna88k
	"#151",			/* 151 */
#endif	luna88k
	"#152",			/* 152 */
	"#153",			/* 153 */
	"#154",			/* 154 */
	"nfs_svc",		/* 155 = nfs_svc */
	"getdirentries",	/* 156 = getdirentries */
	"statfs",		/* 157 = statfs */
	"fstatfs",		/* 158 = fstatfs */
	"unmount",		/* 159 = unmount */
	"async_daemon",		/* 160 = async_daemon */
	"nfs_getfh",		/* 161 = getfh */
	"getdomainname",	/* 162 = getdomainname */
	"setdomainname",	/* 163 = setdomainname */
	"#164",			/* 164 */
	"quotactl",		/* 165 = quotactl */
	"exportfs",		/* 166 = exportfs */
	"vfsmount",		/* 167 = mount */
	"pioctl",		/* 168 = pioctl */
	"setpag",		/* 169 = setpag */
	"icreate",		/* 170 = icreate */
	"iopen",		/* 171 = iopen */
	"iread",		/* 172 = iread */
	"iwrite",		/* 173 = iwrite */
	"iinc",			/* 174 = iinc */
	"idec",			/* 175 = idec */
	"#176",			/* 176 */
	"#177",			/* 177 */
	"#178",			/* 178 */
	"#179",			/* 179 */
	"afs_call",		/* 180 = afs_call */
#endif	luna
#ifdef	GENERIC
	"#151",			/* 151 */
	"#152",			/* 152 */
	"#153",			/* 153 */
	"#154",			/* 154 */
	"nfs_svc",		/* 155 = nfs_svc */
	"getdirentries",	/* 156 = getdirentries */
	"statfs",		/* 157 = statfs */
	"fstatfs",		/* 158 = fstatfs */
	"unmount",		/* 159 = unmount */
	"async_daemon",		/* 160 = async_daemon */
	"nfs_getfh",		/* 161 = getfh */
	"getdomainname",	/* 162 = getdomainname */
	"setdomainname",	/* 163 = setdomainname */
	"#164",			/* 164 */
	"quotactl",		/* 165 = quotactl */
	"exportfs",		/* 166 = exportfs */
	"vfsmount",		/* 167 = mount */
	"pioctl",		/* 168 = pioctl */
	"setpag",		/* 169 = setpag */
	"icreate",		/* 170 = icreate */
	"iopen",		/* 171 = iopen */
	"iread",		/* 172 = iread */
	"iwrite",		/* 173 = iwrite */
	"iinc",			/* 174 = iinc */
	"idec",			/* 175 = idec */
	"#176",			/* 176 */
	"#177",			/* 177 */
	"#178",			/* 178 */
	"#179",			/* 179 */
	"afs_call",		/* 180 = afs_call */
#endif	GENERIC
#ifdef	PMAX
	"plock",		/* 181 = plock */
	"#182",			/* 182 = lockf (future) */
	"ustat",		/* 183 = ustat */
	"getmnt",		/* 184 = getmnt */
	"smount",		/* 185 = mount */
	"umount",		/* 186 = umount */
	"sigpending",		/* 187 = sigpending */
	"setsid",		/* 188 = setsid */
	"waitpid",		/* 189 = waitpid */
#else	PMAX
#ifdef	ibmrt
	"afs_call",		/* 181 = afs_call */
#else	ibmrt
	"#181",			/* 181 */
#endif	ibmrt
	"invoke",		/* 182 = invoke */
	"recvreq",		/* 183 = recvreq */
	"sendreply",		/* 184 = sendreply */
	"forward",		/* 185 = forward */
	"probeentity",		/* 186 = probeentity */
	"getreply",		/* 187 = getreply */
	"#188",			/* 188 */
	"#189",			/* 189 */
#endif	PMAX
#ifdef	PMAX
	"iopen",		/* 190 = iopen */
	"iread",		/* 191 = iread */
	"iwrite",		/* 192 = iwrite */
	"iinc",			/* 193 = iinc */
	"idec",			/* 194 = idec */
	"pioctl",		/* 195 = pioctl */
	"setpag",		/* 196 = setpag */
	"icreate",		/* 197 = icreate */
	"afs_call",		/* 198 = afs_call */
#else	PMAX
	"#190",			/* 190 */
	"#191",			/* 191 */
	"#192",			/* 192 */
	"#193",			/* 193 */
	"#194",			/* 194 */
	"#195",			/* 195 */
	"#196",			/* 196 */
	"#197",			/* 197 */
	"#198",			/* 198 */
#endif	PMAX
	"#199",			/* 199 */
	"#200",			/* 200 */
	"#201",			/* 201 */
	"#202",			/* 202 */
	"#203",			/* 203 */
	"#204",			/* 204 */
	"#205",			/* 205 */
	"#206",			/* 206 */
	"#207",			/* 207 */
	"#208",			/* 208 */
	"#209",			/* 209 */
	"#210",			/* 210 */
	"#211",			/* 211 */
	"#212",			/* 212 */
	"#213",			/* 213 */
	"#214",			/* 214 */
	"#215",			/* 215 */
	"#216",			/* 216 */
	"#217",			/* 217 */
	"#218",			/* 218 */
	"#219",			/* 219 */
	"#220",			/* 220 */
	"#221",			/* 221 */
	"#222",			/* 222 */
	"#223",			/* 223 */
	/* standardized afs system call numbers */
	"pioctl",		/* 224 = pioctl */
	"setpag",		/* 225 = setpag */
	"iopen",		/* 226 = iopen */
	"icreate",		/* 227 = icreate */
	"iread",		/* 228 = iread */
	"iwrite",		/* 229 = iwrite */
	"iinc",			/* 230 = iinc */
	"idec",			/* 231 = idec */
	"afs_call",		/* 232 = afs_call */
#ifdef	PMAX
	"#233",			/* 233 */
	"#234",			/* 234 */
	"#235",			/* 235 */
	"#236",			/* 236 */
	"#237",			/* 237 */
	"#238",			/* 238 */
	"#239",			/* 239 */
	"#240",			/* 240 */
	"#241",			/* 241 */
	"#242",			/* 242 */
	"#243",			/* 243 */
	"#244",			/* 244 */
	"#245",			/* 245 */
	"#246",			/* 246 */
	"#247",			/* 247 */
	"#248",			/* 248 */
	"#249",			/* 249 */
	"#250",			/* 250 */
	"#251",			/* 251 */
	"audcntl",		/* 252 audcntl */
	"audgen",		/* 253 audgen */
	"startcpu",		/* 254 startcpu */
	"stopcpu",		/* 255 stopcpu */
	"getsysinfo",		/* 256 = getsysinfo */
	"setsysinfo",		/* 257 = setsysinfo */
#endif	PMAX
#ifdef	vax
	"#233",			/* 233 */
	"#234",			/* 234 */
	"#235",			/* 235 */
	"#236",			/* 236 */
	"#237",			/* 237 */
	"#238",			/* 238 */
	"#239",			/* 239 */
	"#240",			/* 240 */
	"#241",			/* 241 */
	"#242",			/* 242 */
	"#243",			/* 243 */
	"#244",			/* 244 */
	"#245",			/* 245 */
	"#246",			/* 246 */
	"#247",			/* 247 */
	"#248",			/* 248 */
	"#249",			/* 249 */
	"#250",			/* 250 */
	"#251",			/* 251 */
	"#252",			/* 252 */
	"#253",			/* 253 */
	"#254",			/* 254 */
	"#255",			/* 255 */
	"getsysinfo",		/* 256 = getsysinfo */
	"setsysinfo",		/* 257 = setsysinfo */
#endif	vax
};
