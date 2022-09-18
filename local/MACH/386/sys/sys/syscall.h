/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	syscall.h,v $
 * Revision 2.11  89/08/02  09:09:59  jsb
 * 	Added entries for Multimax syscalls.
 * 	[89/08/01            mbj]
 * 
 * Revision 2.10  89/05/30  10:44:09  rvb
 * 	Additions for Ultrix/MIPS
 * 	[89/05/30  08:37:37  rvb]
 * 
 * Revision 2.9  89/05/11  14:58:43  gm0w
 * 	Fixed up ifdef/endif's for vax and i386 numbers.
 * 	[89/05/05            gm0w]
 * 
 * Revision 2.8  89/03/15  15:59:08  gm0w
 * 	Separated vax and i386 syscall numbers.
 * 
 * Revision 2.7  89/03/09  22:07:57  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  17:56:33  gm0w
 * 	Made CMUCS and MACH_VMTP defines done unconditionally.
 * 	Changed BALANCE to balance.
 * 	[89/02/14            mrt]
 * 
 * Revision 2.5  89/01/23  22:28:45  af
 * 	Add mips specific system calls
 * 	[89/01/10            af]
 * 	
 * 	Changes for I386 -- treat it like vax
 * 	[89/01/09            rvb]
 * 
 * Revision 2.4  89/01/18  01:19:30  jsb
 * 	Added NFS and AFS system calls.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.3  88/07/15  16:02:22  mja
 * Moved UMODE_* bit definitions to <sys/table.h>.
 * 
 * 10-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added getmodes()/setmodes() bit definitions and updated for
 *	more local system calls.
 *	[ V5.1(XF18) ]
 *
 * 22-Sep-86  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	At CMU CS, added local system calls.
 *
 * 22-Sep-86  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added changes for IBM RT.
 *
 */
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)syscall.h	5.4 (Berkeley) 4/3/86
 */

#ifndef	_SYS_SYSCALL_H_
#define _SYS_SYSCALL_H_

/* CMU system calls */
#define SYS_getmodes	(-9)
#define SYS_setmodes	(-8)
#define SYS_IPCAtrium	(-7)
#define SYS_table	(-6)
#define SYS_rpause	(-5)
#define SYS_xutimes	(-4)
				/* -3 is unused */
#define SYS_getaid	(-2)
#define SYS_setaid	(-1)

#define SYS_syscall	0
/* end CMU system calls */

#define SYS_exit	1
#define SYS_fork	2
#define SYS_read	3
#define SYS_write	4
#define SYS_open	5
#define SYS_close	6
				/*  7 is old: wait */
#define SYS_creat	8
#define SYS_link	9
#define SYS_unlink	10
#define SYS_execv	11
#define SYS_chdir	12
				/* 13 is old: time */
#define SYS_mknod	14
#define SYS_chmod	15
#define SYS_chown	16
				/* 17 is old: sbreak */
				/* 18 is old: stat */
#define SYS_lseek	19
#define SYS_getpid	20
#define SYS_mount	21
#define SYS_umount	22
				/* 23 is old: setuid */
#define SYS_getuid	24
				/* 25 is old: stime */
#define SYS_ptrace	26
				/* 27 is old: alarm */
				/* 28 is old: fstat */
				/* 29 is old: pause */
				/* 30 is old: utime */
				/* 31 is old: stty */
				/* 32 is old: gtty */
#define SYS_access	33
				/* 34 is old: nice */
				/* 35 is old: ftime */
#define SYS_sync	36
#define SYS_kill	37
#define SYS_stat	38
				/* 39 is old: setpgrp */
#define SYS_lstat	40
#define SYS_dup		41
#define SYS_pipe	42
				/* 43 is old: times */
#define SYS_profil	44
				/* 45 is unused */
				/* 46 is old: setgid */
#define SYS_getgid	47
				/* 48 is old: sigsys */
				/* 49 is unused */
				/* 50 is unused */
#define SYS_acct	51
				/* 52 is old: phys */
				/* 53 is old: syslock */
#define SYS_ioctl	54
#define SYS_reboot	55
				/* 56 is old: mpxchan */
#define SYS_symlink	57
#define SYS_readlink	58
#define SYS_execve	59
#define SYS_umask	60
#define SYS_chroot	61
#define SYS_fstat	62
				/* 63 is unused */
#define SYS_getpagesize 64
#define SYS_mremap	65
#ifdef	ibmrt
#define SYS_vfork	66
#endif
#ifdef	vax
				/* 66 is old: vfork */
#endif
				/* 67 is old: vread */
				/* 68 is old: vwrite */
#define SYS_sbrk	69
#define SYS_sstk	70
#define SYS_mmap	71
#ifdef	ibmrt
#define SYS_vadvise	72
#endif
#ifdef	vax
				/* 72 is old: vadvise */
#endif	vax
#define SYS_munmap	73
#define SYS_mprotect	74
#define SYS_madvise	75
#define SYS_vhangup	76
				/* 77 is old: vlimit */
#define SYS_mincore	78
#define SYS_getgroups	79
#define SYS_setgroups	80
#define SYS_getpgrp	81
#define SYS_setpgrp	82
#define SYS_setitimer	83
#define SYS_wait	84
#define SYS_swapon	85
#define SYS_getitimer	86
#define SYS_gethostname	87
#define SYS_sethostname	88
#define SYS_getdtablesize 89
#define SYS_dup2	90
#define SYS_getdopt	91
#define SYS_fcntl	92
#define SYS_select	93
#define SYS_setdopt	94
#define SYS_fsync	95
#define SYS_setpriority	96
#define SYS_socket	97
#define SYS_connect	98
#define SYS_accept	99
#define SYS_getpriority	100
#define SYS_send	101
#define SYS_recv	102
#define SYS_sigreturn	103
#define SYS_bind	104
#define SYS_setsockopt	105
#define SYS_listen	106
				/* 107 was vtimes */
#define SYS_sigvec	108
#define SYS_sigblock	109
#define SYS_sigsetmask	110
#define SYS_sigpause	111
#define SYS_sigstack	112
#define SYS_recvmsg	113
#define SYS_sendmsg	114
				/* 115 is old vtrace */
#define SYS_gettimeofday 116
#define SYS_getrusage	117
#define SYS_getsockopt	118
				/* 119 is old resuba */
#define SYS_readv	120
#define SYS_writev	121
#define SYS_settimeofday 122
#define SYS_fchown	123
#define SYS_fchmod	124
#define SYS_recvfrom	125
#define SYS_setreuid	126
#define SYS_setregid	127
#define SYS_rename	128
#define SYS_truncate	129
#define SYS_ftruncate	130
#define SYS_flock	131
				/* 132 is unused */
#define SYS_sendto	133
#define SYS_shutdown	134
#define SYS_socketpair	135
#define SYS_mkdir	136
#define SYS_rmdir	137
#define SYS_utimes	138
				/* 139 is unused */
#define SYS_adjtime	140
#define SYS_getpeername	141
#define SYS_gethostid	142
#define SYS_sethostid	143
#define SYS_getrlimit	144
#define SYS_setrlimit	145
#define SYS_killpg	146
				/* 147 is unused */
#define SYS_setquota	148
#define SYS_quota	149
#define SYS_getsockname	150

#ifdef	ibmrt
#define SYS_exect		151
#define SYS_getfpemulator	153
#define SYS_iopen		154
#define SYS_iread		155
#define SYS_iwrite		156
#define SYS_iinc		157
#define SYS_idec		158
#define SYS_pioctl		159
#define SYS_setpag		160
#define SYS_icreate		161
#define SYS_getfloatstate	167
#define SYS_setfloatstate	168
#define SYS_nfs_svc		169
#define SYS_getdirentries	170
#define SYS_statfs		171
#define SYS_fstatfs		172
#define SYS_unmount		173
#define SYS_async_daemon	174
#define SYS_nfs_getfh		175
#define SYS_getdomainname	176
#define SYS_setdomainname	177
#define SYS_quotactl		178
#define SYS_exportfs		179
#define SYS_vfsmount		180
#define SYS_afs_call		181
#endif	ibmrt

#ifdef	sun
#define SYS_nfs_svc		155
#define SYS_getdirentries	156
#define SYS_statfs		157
#define SYS_fstatfs		158
#define SYS_unmount		159
#define SYS_async_daemon	160
#define SYS_nfs_getfh		161
#define SYS_getdomainname	162
#define SYS_setdomainname	163
#define SYS_quotactl		165
#define SYS_exportfs		166
#define SYS_vfsmount		167
#define SYS_pioctl		168
#define SYS_setpag		169
#define SYS_icreate		170
#define SYS_iopen		171
#define SYS_iread		172
#define SYS_iwrite		173
#define SYS_iinc		174
#define SYS_idec		175
#define SYS_afs_call		180
#endif	sun

#ifdef	vax
#define SYS_nfs_svc		159
#define SYS_statfs		160
#define SYS_fstatfs		161
#define SYS_unmount		162
#define SYS_async_daemon	163
#define SYS_getdirentries	164
#define SYS_nfs_getfh		165
#define SYS_quotactl		166
#define SYS_exportfs		167
#define SYS_vfsmount		168
#define SYS_getdomainname	169
#define SYS_setdomainname	170
#define SYS_pioctl		171
#define SYS_setpag		172
#define SYS_icreate		173
#define SYS_iopen		174
#define SYS_iread		175
#define SYS_iwrite		176
#define SYS_iinc		177
#define SYS_idec		178
#define SYS_afs_call		179
#endif	vax

#ifdef	i386
#define SYS_nfs_svc		159
#define SYS_statfs		160
#define SYS_fstatfs		161
#define SYS_unmount		162
#define SYS_async_daemon	163
#define SYS_getdirentries	164
#define SYS_nfs_getfh		165
#define SYS_quotactl		166
#define SYS_exportfs		167
#define SYS_vfsmount		168
#define SYS_getdomainname	169
#define SYS_setdomainname	170
#define SYS_pioctl		171
#define SYS_setpag		172
#define SYS_icreate		173
#define SYS_iopen		174
#define SYS_iread		175
#define SYS_iwrite		176
#define SYS_iinc		177
#define SYS_idec		178
#define SYS_afs_call		179
#endif	i386

#if	balance
#define SYS_getdirentries	151
#define SYS_tmp_ctl		152
#define SYS_universe		153
#define SYS_nfs_svc		155
#define SYS_statfs		157
#define SYS_fstatfs		158
#define SYS_unmount		159
#define SYS_async_daemon	160
#define SYS_nfs_getfh		161
#define SYS_getdomainname	162
#define SYS_setdomainname	163
#define SYS_quotactl		165
#define SYS_exportfs		166
#define SYS_vfsmount		167
#define SYS_pioctl		168
#define SYS_setpag		169
#define SYS_icreate		170
#define SYS_iopen		171
#define SYS_iread		172
#define SYS_iwrite		173
#define SYS_iinc		174
#define SYS_idec		175
#define SYS_afs_call		180
#endif	balance

#ifdef	mips
#define SYS_sysmips		151
				/* 152 - 157 are old */
#define SYS_nfs_svc		158
#define SYS_getdirentries	159
#define SYS_statfs		160
#define SYS_fstatfs		161
#define SYS_unmount		162
#define SYS_async_daemon	163
#define SYS_nfs_getfh		164
#define SYS_getdomainname	165
#define SYS_setdomainname	166
				/* 167 is old pcfs_mount */
#define SYS_quotactl		168
#define SYS_exportfs		169
#define SYS_vfsmount		170
				/* 171 is old */
				/* 172 - 187 is ultrix junk */
				/* 188 - 189 unused */
#define SYS_iopen		190
#define SYS_iread		191
#define SYS_iwrite		192
#define SYS_iinc		193
#define SYS_idec		194
#define SYS_pioctl		195
#define SYS_setpag		196
#define SYS_icreate		197
#define SYS_afs_call		198

#endif	mips

#if	multimax
#define	SYS_old_mapfrcounter	151
#define	SYS_mapfrcounter	152
#define	SYS_nfs_svc		155
#define	SYS_getdirentries	156
#define	SYS_statfs		157
#define	SYS_fstatfs		158
#define	SYS_unmount		159
#define	SYS_async_daemon	160
#define	SYS_nfs_getfh		161
#define	SYS_getdomainname	162
#define	SYS_setdomainname	163
#define	SYS_quotactl		165
#define	SYS_exportfs		166
#define	SYS_vfsmount		167
#define	SYS_pioctl		168
#define	SYS_setpag		169
#define	SYS_icreate		170
#define	SYS_iopen		171
#define	SYS_iread		172
#define	SYS_iwrite		173
#define	SYS_iinc		174
#define	SYS_idec		175
#define	SYS_afs_call		180
#endif	multimax

#if	!defined(KERNEL) || MACH_VMTP
#define SYS_invoke		182
#define SYS_recvreq		183
#define SYS_sendreply		184
#define SYS_forward		185
#define SYS_probeentity		186
#define SYS_getreply		187
#endif	!defined(KERNEL) || MACH_VMTP

#endif	_SYS_SYSCALL_H_
