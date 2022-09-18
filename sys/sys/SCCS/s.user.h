h61839
s 00003/00003/00062
d D 8.2 93/09/23 15:29:31 bostic 73 72
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00063
d D 8.1 93/06/02 19:56:44 bostic 72 71
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00064
d D 7.22 93/04/27 15:07:00 mckusick 71 70
c kinfo_proc merged into user.h
e
s 00001/00000/00064
d D 7.21 92/06/19 23:28:26 mckusick 70 69
c add md_coredump
e
s 00001/00001/00063
d D 7.20 92/02/05 16:29:50 mckusick 69 67
c p_regs moves to p_md.md_regs
e
s 00001/00001/00063
d R 7.20 91/11/11 11:42:08 bostic 68 67
c make vm inclusion work for applications (I'm assuming it's going away)
e
s 00005/00006/00059
d D 7.19 91/05/04 15:18:01 karels 67 66
c rm ssave; fixed-address u. is gone
e
s 00034/00022/00031
d D 7.18 91/04/20 17:57:04 karels 66 65
c rm u.u_procp; change includes to mirror old for non-kernel;
c add kinfo_proc for core dumps, and redefinitions to fake out debuggers
e
s 00013/00057/00040
d D 7.17 91/03/17 15:34:12 karels 65 64
c more-or-less working with new proc & user structs
e
s 00001/00008/00096
d D 7.16 91/01/10 23:31:22 mckusick 64 63
c file descriptors are now allocated dynamically
e
s 00011/00013/00093
d D 7.15 90/12/05 15:58:54 mckusick 63 62
c update for new VM
e
s 00000/00009/00106
d D 7.14 90/12/05 15:57:06 bostic 62 61
c kernel reorganization
e
s 00000/00005/00115
d D 7.13 90/06/28 16:41:50 karels 61 60
c rm u.u_eosys values
e
s 00002/00016/00118
d D 7.12 90/06/22 17:16:27 mckusick 60 59
c eliminate u.u_error, u.u_r_val1, and other trash!
e
s 00004/00004/00130
d D 7.11 90/05/15 22:28:49 mckusick 59 58
c size_t => segsz_t for bostic
e
s 00003/00020/00131
d D 7.10 90/05/10 13:18:04 mckusick 58 57
c delete u_qsave, u_eosys, u_quota, and u_qflags;
c delete defines for u_ruid, u_rgid, u_groups, and u_ngroups;
c u_error becomes an int; add u_mmap for hp300 support
e
s 00000/00008/00151
d D 7.9 90/03/20 15:52:52 marc 57 56
c u_comm => p_comm, ttyp => session
e
s 00003/00002/00156
d D 7.8 90/01/04 17:19:35 karels 56 55
c signal updates
e
s 00002/00002/00156
d D 7.7 89/08/31 22:30:21 karels 55 54
c ruid and rgid move to the proc structure
e
s 00002/00001/00156
d D 7.6 89/06/06 19:31:17 mckusick 54 53
c move u_logname to a more logical location, add u_spare fields
e
s 00026/00018/00131
d D 7.5 89/05/09 16:35:12 mckusick 53 52
c merge in vnodes
e
s 00002/00001/00147
d D 7.4 89/05/01 23:17:27 kfall 52 51
c u_XXX -> u_logname (for set/get logname)
e
s 00001/00000/00147
d D 7.3 89/04/26 19:00:52 mckusick 51 50
c temporary hack until real credentials
e
s 00001/00001/00146
d D 7.2 89/04/25 14:22:43 mckusick 50 49
c ../machine => machine
e
s 00001/00001/00146
d D 7.1 86/06/04 23:31:20 mckusick 49 48
c 4.3BSD release version
e
s 00007/00001/00140
d D 6.10 85/06/08 15:12:06 mckusick 48 47
c Add copyright
e
s 00001/00000/00140
d D 6.9 85/03/11 20:35:47 mckusick 47 46
c need NORMALRETURN to distinguish JUSTRETURN used by sendsig()
e
s 00011/00011/00129
d D 6.8 85/03/07 21:59:03 karels 46 45
c shorten u_comm, add id types, add ofile high-water mark, add sigintr, cleanups
e
s 00001/00001/00139
d D 6.7 85/02/15 18:54:18 karels 45 44
c groups[] now shorts
e
s 00008/00004/00132
d D 6.6 84/08/28 17:28:52 bloom 44 43
c Change include paths.  No more ../h
e
s 00000/00024/00136
d D 6.5 84/07/21 17:24:41 sam 43 42
c remove a.out header from u. area
e
s 00001/00001/00159
d D 6.4 84/07/11 20:48:22 sam 42 41
c need more resolution on starting time for accounting
e
s 00019/00020/00141
d D 6.3 84/07/08 15:47:31 mckusick 41 40
c rework `namei' interface to eliminate global variables
e
s 00006/00000/00155
d D 6.2 83/11/21 01:36:51 mckusick 40 39
c add structure to cache single namei entries
e
s 00000/00000/00155
d D 6.1 83/07/29 06:14:52 sam 39 38
c 4.2 distribution
e
s 00002/00005/00153
d D 4.30 83/07/01 02:25:12 root 38 37
c purge #if sun's
e
s 00001/00003/00157
d D 4.29 83/06/20 20:57:53 root 37 36
c purge UF_EXLOCK and UF_SHLOCK
e
s 00008/00003/00152
d D 4.28 83/06/09 21:57:00 sam 36 35
c "final" sigvec interface?
e
s 00002/00001/00153
d D 4.27 83/06/02 15:52:36 sam 35 34
c new signals
e
s 00003/00002/00151
d D 4.26 83/05/21 16:02:58 sam 34 33
c add different max length on command string
e
s 00003/00000/00150
d D 4.25 83/05/18 02:42:32 sam 33 31
c sun changes
e
s 00001/00001/00149
d R 4.25 83/02/10 16:11:25 sam 32 31
c group id's are shorts, not ints
e
s 00006/00006/00144
d D 4.24 82/12/17 12:11:27 sam 31 30
c sun merge
e
s 00009/00003/00141
d D 4.23 82/12/09 18:55:21 sam 30 29
c put back profiling stuff and make flag names sane?
e
s 00002/00002/00142
d D 4.22 82/11/13 23:08:57 sam 29 28
c merge 4.1b and 4.1c
e
s 00011/00006/00133
d D 4.21 82/10/31 16:42:00 root 28 27
c UF_MAPPED and machine dependent pcb.h
e
s 00005/00003/00134
d D 4.20 82/09/12 03:19:40 root 27 26
c 
e
s 00002/00002/00135
d D 4.19 82/09/08 18:10:12 root 26 25
c label_t now structure
e
s 00001/00000/00136
d D 4.18 82/09/06 23:01:31 root 25 24
c more timer stuff
e
s 00063/00067/00073
d D 4.17 82/09/04 09:26:24 root 24 23
c begin cleanup
e
s 00004/00015/00136
d D 4.16 82/08/24 17:45:10 root 23 22
c NGROUPS -> 8, u.u_groups
e
s 00004/00007/00147
d D 4.15 82/08/08 18:15:05 sam 22 21
c expunge vrpages, added per-fd locking flags
e
s 00004/00001/00150
d D 4.14 82/07/16 16:37:17 kre 21 20
c added fields for quota & mush ... to use
e
s 00000/00004/00151
d D 4.13 82/06/25 21:33:10 wnj 20 19
c get rid of ../errno.h
e
s 00003/00002/00152
d D 4.12 82/04/19 19:27:01 mckusic 19 18
c merge in the new file system
e
s 00000/00001/00154
d D 4.11 82/03/27 22:04:55 wnj 18 17
c dont include assym.s
e
s 00002/00000/00153
d D 4.10 82/02/15 13:28:56 wnj 17 16
c new group stuff
e
s 00004/00000/00149
d D 4.9 81/11/29 22:14:41 wnj 16 15
c lint & wkend editing
e
s 00002/00000/00147
d D 4.8 81/04/28 03:02:49 root 15 14
c #ifdef notdef u.u_vsave
e
s 00001/00000/00146
d D 4.7 81/04/24 11:20:54 wnj 14 13
c add u.u_vsave
e
s 00003/00001/00143
d D 4.6 81/03/03 12:39:43 wnj 13 12
c s/cfcode/code/p
e
s 00002/00005/00142
d D 4.5 81/02/23 20:49:48 wnj 12 11
c put funny constants in assym.s; remove ISPORT
e
s 00001/00001/00146
d D 4.4 81/02/19 21:43:01 wnj 11 10
c %G%->%E%
e
s 00002/00001/00145
d D 4.3 81/02/01 00:41:56 wnj 10 9
c added EXCLOSE, ISPORT
e
s 00022/00009/00124
d D 4.2 81/01/26 22:23:44 kre 9 8
c altered u_exdata to be a union for #! file types
e
s 00000/00000/00133
d D 4.1 80/11/09 17:02:00 bill 8 6
c stamp for 4bsd
e
s 00000/00000/00133
d R 3.7 80/07/12 17:00:38 bill 7 6
c 
e
s 00001/00000/00132
d D 3.6 80/07/12 16:25:16 bill 6 5
c added u_limit
e
s 00001/00001/00131
d D 3.5 80/06/07 03:02:01 bill 5 4
c %H%->%G%
e
s 00001/00000/00131
d D 3.4 80/05/18 11:39:35 bill 4 3
c add SIMULATERTI
e
s 00007/00036/00124
d D 3.3 80/05/15 17:18:07 bill 3 2
c new fields for signals
e
s 00005/00003/00155
d D 3.2 80/04/30 17:24:22 bill 2 1
c field uniqueness crap
e
s 00158/00000/00000
d D 3.1 80/04/09 16:25:52 bill 1 0
c date and time created 80/04/09 16:25:52 by bill
e
u
U
t
T
I 19
D 22
/* @(#)user.h 2.1 3/25/82 */

E 22
E 19
I 1
D 5
/*	%M%	%I%	%H%	*/
E 5
I 5
D 11
/*	%M%	%I%	%G%	*/
E 11
I 11
D 48
/*	%M%	%I%	%E%	*/
E 48
I 48
/*
D 49
 * Copyright (c) 1982 Regents of the University of California.
E 49
I 49
D 53
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 49
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 53
I 53
D 66
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 66
I 66
D 72
 * Copyright (c) 1982, 1986, 1989, 1991 Regents of the University of California.
E 66
 * All rights reserved.
E 72
I 72
 * Copyright (c) 1982, 1986, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 72
E 53
 *
I 53
D 58
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 58
I 58
 * %sccs.include.redist.c%
E 58
 *
E 53
 *	%W% (Berkeley) %G%
 */
E 48
E 11
E 5

I 66
#include <machine/pcb.h>
E 66
D 24
#ifdef KERNEL
#include "../h/pcb.h"
#include "../h/dmap.h"
#include "../h/vtimes.h"
D 12
#ifdef FASTVAX
asm(".set U_ARG,120");
asm(".set U_QSAV,140");
#endif
E 12
I 12
D 18
#include "assym.s"
E 18
E 12
#else
E 24
D 28
#include <sys/pcb.h>
E 28
I 28
D 31
#ifdef vax
#include <vax/pcb.h>
#endif
#ifdef sun
#include <sun/pcb.h>
#endif
E 31
I 31
D 62
#ifdef KERNEL
D 50
#include "../machine/pcb.h"
E 50
I 50
#include "machine/pcb.h"
E 50
D 44
#include "../h/dmap.h"
I 36
#include "../h/time.h"
#include "../h/resource.h"
I 41
#include "../h/namei.h"
E 44
I 44
#include "dmap.h"
#include "time.h"
#include "resource.h"
#include "namei.h"
I 53
#include "ucred.h"
E 53
E 44
E 41
E 36
#else
E 62
D 65
#include <machine/pcb.h>
E 31
E 28
#include <sys/dmap.h>
E 65
I 65
#ifndef KERNEL
I 66
/* stuff that *used* to be included by user.h, or is now needed */
#include <errno.h>
E 66
E 65
I 31
D 36
#endif
E 36
E 31
D 24
#include <sys/vtimes.h>
#endif
E 24
I 24
D 38
#include <time.h>
#include <resource.h>
E 38
I 38
#include <sys/time.h>
#include <sys/resource.h>
I 66
#include <sys/ucred.h>
E 66
I 65
#include <sys/uio.h>
#endif
D 66
#include <machine/pcb.h>
#include <sys/signalvar.h>
E 66
#include <sys/resourcevar.h>
E 65
I 41
D 66
#include <sys/namei.h>
E 66
I 66
#include <sys/signalvar.h>
#include <vm/vm.h>		/* XXX */
D 71
#include <sys/kinfo_proc.h>
E 71
I 71
#include <sys/sysctl.h>
E 71
E 66
I 53
D 65
#include <sys/ucred.h>
E 65
E 53
E 41
E 38
I 36
D 62
#endif
E 62

I 66

E 66
E 36
E 24
/*
D 23
 * The user structure.
 * One allocated per process.
 * Contains all per process data
 * that doesn't need to be referenced
 * while the process is swapped.
 * The user block is UPAGES*NBPG bytes
 * long; resides at virtual user
 * loc 0x80000000-UPAGES*NBPG; contains the system
 * stack per user; is cross referenced
 * with the proc structure for the
 * same process.
E 23
I 23
D 67
 * Per process structure containing data that
 * isn't needed in core when the process is swapped out.
E 67
I 67
 * Per process structure containing data that isn't needed in core
 * when the process isn't running (esp. when swapped out).
 * This structure may or may not be at the same kernel address
 * in all processes.
E 67
E 23
 */
 
D 10
#define	EXCLOSE 01
E 10
I 9
D 34
#define	SHSIZE	32
E 34
I 34
D 43
#define	SHSIZE		32
E 43
D 46
#define	MAXCOMLEN	16		/* <= MAXNAMLEN, >= sizeof(a_comm) */
E 46
I 46
D 57
#define	MAXCOMLEN	16		/* <= MAXNAMLEN, >= sizeof(ac_comm) */
I 52
#define	MAXLOGNAME	12		/* >= UT_NAMESIZE */
E 52
E 46
E 34
E 9
 
E 57
D 23
struct	user
{
E 23
I 23
struct	user {
E 23
	struct	pcb u_pcb;
I 24
D 65
	struct	proc *u_procp;		/* pointer to proc structure */
	int	*u_ar0;			/* address of users saved R0 */
E 65
I 65
D 66
	struct	proc *u_procp;		/* pointer to proc structure XXX */
E 66
D 67
	label_t	u_ssave;		/* label variable for swapping XXX */
E 67
D 66
#define curproc	u.u_procp		/* XXX */
E 66
E 65
D 46
	char	u_comm[MAXNAMLEN + 1];
E 46
I 46
D 57
	char	u_comm[MAXCOMLEN + 1];
E 46

E 57
D 60
/* syscall parameters, results and catches */
E 24
D 27
	int	u_arg[5];		/* arguments to current system call */
E 27
I 27
	int	u_arg[8];		/* arguments to current system call */
E 27
I 24
	int	*u_ap;			/* pointer to arglist */
E 24
D 26
	label_t	u_qsav;			/* for non-local gotos on interrupts */
E 26
I 26
D 58
	label_t	u_qsave;		/* for non-local gotos on interrupts */
E 58
E 26
D 24
	char	u_segflg;		/* 0:user D; 1:system; 2:user I */
E 24
D 41
	char	u_error;		/* return error code */
E 41
D 24
	short	u_uid;			/* effective user id */
	short	u_gid;			/* effective group id */
I 17
D 23
	int	u_grps[NGRPS/(sizeof(int)*8)];
					/* group bit array */
E 23
I 23
	int	u_groups[NGROUPS];	/* groups, 0 terminated */
E 23
E 17
	short	u_ruid;			/* real user id */
	short	u_rgid;			/* real group id */
	struct	proc *u_procp;		/* pointer to proc structure */
	int	*u_ap;			/* pointer to arglist */
E 24
	union {				/* syscall return values */
		struct	{
D 2
			int	r_val1;
			int	r_val2;
		};
E 2
I 2
			int	R_val1;
			int	R_val2;
		} u_rv;
#define	r_val1	u_rv.R_val1
#define	r_val2	u_rv.R_val2
E 2
		off_t	r_off;
		time_t	r_time;
	} u_r;
I 41
D 58
	char	u_error;		/* return error code */
E 41
D 24
	caddr_t	u_base;			/* base address for IO */
	unsigned int u_count;		/* bytes remaining for IO */
	off_t	u_offset;		/* offset in file for IO */
D 22
	struct	inode *u_cdir;		/* pointer to inode of current directory */
E 22
I 22
	struct	inode *u_cdir;		/* current directory */
E 22
	struct	inode *u_rdir;		/* root directory of current process */
D 19
	char	u_dbuf[DIRSIZ];		/* current pathname component */
E 19
	caddr_t	u_dirp;			/* pathname pointer */
	struct	direct u_dent;		/* current directory entry */
	struct	inode *u_pdir;		/* inode of parent directory of dirp */
D 22
	struct	file *u_ofile[NOFILE];	/* pointers to file structures of open files */
E 22
I 22
	struct	file *u_ofile[NOFILE];	/* file structures for open files */
E 22
	char	u_pofile[NOFILE];	/* per-process flags of open files */
I 10
#define	EXCLOSE 01		/* auto-close on exec */
I 22
#define	RDLOCK	02		/* read lock present */
#define	WRLOCK	04		/* write lock present */
E 24
I 24
	char	u_eosys;		/* special action on end of syscall */
E 58
I 58
	int	u_error;		/* return error code */
E 60
E 58

D 65
/* 1.1 - processes and protection */
I 54
D 57
	char	u_logname[MAXLOGNAME];	/* login name, if available */
E 57
E 54
D 46
	short	u_uid;			/* effective user id */
	short	u_gid;			/* effective group id */
D 45
	int	u_groups[NGROUPS];	/* groups, 0 terminated */
E 45
I 45
	short	u_groups[NGROUPS];	/* groups, 0 terminated */
E 45
	short	u_ruid;			/* real user id */
	short	u_rgid;			/* real group id */
E 46
I 46
D 53
	uid_t	u_uid;			/* effective user id */
	uid_t	u_ruid;			/* real user id */
	gid_t	u_gid;			/* effective group id */
E 53
I 53
D 55
#define	u_ruid	u_cred->cr_ruid		/* real user id */
E 53
	gid_t	u_rgid;			/* real group id */
E 55
I 55
D 58
#define	u_ruid	u_procp->p_ruid		/* real user id - XXX */
#define	u_rgid	u_procp->p_rgid		/* real group id - XXX */
E 58
E 55
D 53
	gid_t	u_groups[NGROUPS];	/* groups, 0 terminated */
I 51
#define u_cred u_uid
E 53
I 53
#define u_cred u_nd.ni_cred
#define u_uid	u_cred->cr_uid		/* effective user id */
#define u_gid	u_cred->cr_gid		/* effective group id */
E 65
I 65
	struct	sigacts u_sigacts;	/* p_sigacts points here (use it!) */
D 66
	struct	pstats u_stats;		/* rusage, profiling & timers */
E 66
I 66
	struct	pstats u_stats;		/* p_stats points here (use it!) */
E 66
E 65
D 58
#define u_ngroups u_cred->cr_ngroups	/* number of group id's */
#define u_groups u_cred->cr_groups	/* list of effective grp id's */
E 58
E 53
E 51
E 46

D 65
/* 1.2 - memory management */
D 59
	size_t	u_tsize;		/* text size (clicks) */
	size_t	u_dsize;		/* data size (clicks) */
	size_t	u_ssize;		/* stack size (clicks) */
E 59
I 59
	segsz_t u_tsize;		/* text size (clicks) */
	segsz_t u_dsize;		/* data size (clicks) */
	segsz_t u_ssize;		/* stack size (clicks) */
E 59
D 63
	struct	dmap u_dmap;		/* disk map for data segment */
	struct	dmap u_smap;		/* disk map for stack segment */
D 53
	struct	dmap u_cdmap, u_csmap;	/* shadows of u_dmap, u_smap, for
					   use of parent during fork */
E 53
I 53
	struct	dmap u_cdmap;		/* temp data segment disk map */
	struct	dmap u_csmap;		/* temp stack segment disk map */
E 53
E 24
E 22
D 12
#define	ISPORT	02		/* is a port */
E 12
E 10
D 26
	label_t u_ssav;			/* label variable for swapping */
E 26
I 26
	label_t u_ssave;		/* label variable for swapping */
E 26
I 24
D 59
	size_t	u_odsize, u_ossize;	/* for (clumsy) expansion swaps */
E 59
I 59
	segsz_t u_odsize, u_ossize;	/* for (clumsy) expansion swaps */
E 63
I 63
	struct	dmap u_pad1[4];
	label_t	u_ssave;		/* label variable for swapping */
	caddr_t	u_taddr;		/* user virtual address of text */
	caddr_t	u_daddr;		/* user virtual address of data */
E 63
E 59
	time_t	u_outime;		/* user time at last sample */
I 58
D 63
	struct	mapmem *u_mmap;		/* list of mapped memory regions */
E 63
I 63
	caddr_t u_maxsaddr;		/* user VA at max stack growth */
E 63
E 58

/* 1.3 - signal management */
E 24
D 3
	int	u_signal[NSIG];		/* disposition of signals */
E 3
I 3
D 56
	int	(*u_signal[NSIG])();	/* disposition of signals */
E 56
I 56
	sig_t	u_signal[NSIG];		/* disposition of signals */
E 56
I 24
D 27
	int	u_sigmask[NSIG];	/* signals to be blocked */
E 27
I 27
D 35
	long	u_sigmask[NSIG];	/* signals to be blocked */
E 35
I 35
	int	u_sigmask[NSIG];	/* signals to be blocked */
I 36
	int	u_sigonstack;		/* signals to take on sigstack */
I 46
	int	u_sigintr;		/* signals that interrupt syscalls */
E 46
E 36
	int	u_oldmask;		/* saved mask from before sigpause */
E 35
E 27
E 24
E 3
D 13
	int	u_cfcode;		/* ``code'' to trap when CM faulted */
E 13
I 13
D 56
	int	u_code;			/* ``code'' to trap */
E 56
I 24
D 36
	caddr_t	u_sigstack;		/* 0 means no sigstack */
I 27
	int	u_onsigstack;
E 36
I 36
	struct	sigstack u_sigstack;	/* sp & on stack state variable */
#define	u_onstack	u_sigstack.ss_onstack
#define	u_sigsp		u_sigstack.ss_sp
I 56
D 60
#define	u_sig	u_arg[0]		/* for core dump/debugger XXX */
#define	u_code	u_arg[1]		/* for core dump/debugger XXX */
E 60
I 60
	int	u_sig;			/* for core dump/debugger XXX */
	int	u_code;			/* for core dump/debugger XXX */
E 60
E 56
E 36
E 27
E 24
D 28
/* on SIGILL code passes compatibility mode fault address  */
/* on SIGFPE code passes more specific kind of floating point fault */
E 28
E 13
D 24
	int	*u_ar0;			/* address of users saved R0 */
	struct uprof {			/* profile arguments */
		short	*pr_base;	/* buffer base */
		unsigned pr_size;	/* buffer size */
		unsigned pr_off;	/* pc offset */
		unsigned pr_scale;	/* pc scaling */
	} u_prof;
D 3
	char	u_intflg;		/* catch intr from sys */
E 3
I 3
	char	u_eosys;		/* special action on end of syscall */
E 3
	char	u_sep;			/* flag for I and D separation */
E 24
I 24

/* 1.4 - descriptor management */
D 64
	struct	file *u_ofile[NOFILE];	/* file structures for open files */
	char	u_pofile[NOFILE];	/* per-process flags of open files */
I 46
	int	u_lastfile;		/* high-water mark of u_ofile */
E 46
D 28
#define	EXCLOSE 01		/* auto-close on exec */
#define	RDLOCK	02		/* read lock present */
#define	WRLOCK	04		/* write lock present */
E 28
I 28
D 30
#define	EXCLOSE 	0x1		/* auto-close on exec */
D 29
#define	RDLOCK		0x2		/* read lock present */
#define	WRLOCK		0x4		/* write lock present */
E 29
I 29
#define	SHLOCK		0x2		/* shared lock present */
#define	EXLOCK		0x4		/* exclusive lock present */
E 30
I 30
#define	UF_EXCLOSE 	0x1		/* auto-close on exec */
D 37
#define	UF_SHLOCK	0x2		/* shared lock present */
#define	UF_EXLOCK	0x4		/* exclusive lock present */
E 30
E 29
#define	UF_MAPPED 	0x8
E 37
I 37
#define	UF_MAPPED 	0x2		/* mapped from device */
E 37
E 28
D 53
	struct	inode *u_cdir;		/* current directory */
	struct	inode *u_rdir;		/* root directory of current process */
E 53
I 53
#define u_cdir u_nd.ni_cdir		/* current directory */
#define u_rdir u_nd.ni_rdir		/* root directory of current process */
E 53
E 24
D 57
	struct	tty *u_ttyp;		/* controlling tty pointer */
	dev_t	u_ttyd;			/* controlling tty dev */
E 57
I 24
	short	u_cmask;		/* mask for file creation */
E 64
I 64
	long	u_pad2[82];
E 64

/* 1.5 - timing and statistics */
	struct	rusage u_ru;		/* stats for this proc */
	struct	rusage u_cru;		/* sum of stats for reaped children */
	struct	itimerval u_timer[3];
I 25
D 52
	int	u_XXX[3];
E 52
I 52
D 54
	char	u_logname[MAXLOGNAME];	/* login name, if available */
E 54
E 52
E 25
D 42
	time_t	u_start;
E 42
I 42
	struct	timeval u_start;
E 42
	short	u_acflag;

I 41
	struct uprof {			/* profile arguments */
		short	*pr_base;	/* buffer base */
		unsigned pr_size;	/* buffer size */
		unsigned pr_off;	/* pc offset */
		unsigned pr_scale;	/* pc scaling */
	} u_prof;

E 65
E 41
D 66
/* 1.6 - resource controls */
D 27
	struct	rlimit u_rlimit[5];
E 27
I 27
D 65
	struct	rlimit u_rlimit[RLIM_NLIMITS];
E 65
E 27
D 34
	struct	quota *u_quota;	/* user's quota structure */
E 34
I 34
D 58
	struct	quota *u_quota;		/* user's quota structure */
E 34
	int	u_qflags;		/* per process quota flags */
E 58

I 41
D 65
/* namei & co. */
D 53
	struct nameicache {		/* last successful directory search */
		int nc_prevoffset;	/* offset at which last entry found */
		ino_t nc_inumber;	/* inum of cached directory */
		dev_t nc_dev;		/* dev of cached directory */
		time_t nc_time;		/* time stamp for cache entry */
	} u_ncache;
E 53
	struct	nameidata u_nd;
E 65
I 65
	int	u_spare[1];
E 65

E 66
I 66
	/*
	 * Remaining fields only for core dump and/or ptrace--
	 * not valid at other times!
	 */
	struct	kinfo_proc u_kproc;	/* proc + eproc */
I 70
	struct	md_coredump u_md;	/* machine dependent glop */
E 70
E 66
I 54
D 65
	long	u_spare[8];
E 54
E 41
D 43
/* BEGIN TRASH */
D 41
	char	u_segflg;		/* 0:user D; 1:system; 2:user I */
	caddr_t	u_base;			/* base address for IO */
	unsigned int u_count;		/* bytes remaining for IO */
	off_t	u_offset;		/* offset in file for IO */
E 41
E 24
D 9
	struct {			/* header of executable file */
		int	ux_mag;		/* magic number */
		unsigned ux_tsize;	/* text size */
		unsigned ux_dsize;	/* data size */
		unsigned ux_bsize;	/* bss size */
		unsigned ux_ssize;	/* symbol table size */
		unsigned ux_entloc;	/* entry location */
		unsigned ux_unused;
		unsigned ux_relflg;
E 9
I 9
	union {
	   struct {			/* header of executable file */
		int	Ux_mag;		/* magic number */
		unsigned Ux_tsize;	/* text size */
		unsigned Ux_dsize;	/* data size */
		unsigned Ux_bsize;	/* bss size */
		unsigned Ux_ssize;	/* symbol table size */
		unsigned Ux_entloc;	/* entry location */
		unsigned Ux_unused;
		unsigned Ux_relflg;
	   } Ux_A;
	   char ux_shell[SHSIZE];	/* #! and name of interpreter */
E 9
	} u_exdata;
I 9
#define	ux_mag		Ux_A.Ux_mag
#define	ux_tsize	Ux_A.Ux_tsize
#define	ux_dsize	Ux_A.Ux_dsize
#define	ux_bsize	Ux_A.Ux_bsize
#define	ux_ssize	Ux_A.Ux_ssize
#define	ux_entloc	Ux_A.Ux_entloc
#define	ux_unused	Ux_A.Ux_unused
#define	ux_relflg	Ux_A.Ux_relflg
D 24

E 9
D 19
	char	u_comm[DIRSIZ];
E 19
I 19
	char	u_comm[MAXNAMLEN + 1];
E 19
	time_t	u_start;
	char	u_acflag;
	short	u_fpflag;		/* unused now, will be later */
	short	u_cmask;		/* mask for file creation */
	size_t	u_tsize;		/* text size (clicks) */
	size_t	u_dsize;		/* data size (clicks) */
	size_t	u_ssize;		/* stack size (clicks) */
	struct	vtimes u_vm;		/* stats for this proc */
	struct	vtimes u_cvm;		/* sum of stats for reaped children */
	struct	dmap u_dmap;		/* disk map for data segment */
	struct	dmap u_smap;		/* disk map for stack segment */
	struct	dmap u_cdmap, u_csmap;	/* shadows of u_dmap, u_smap, for
					   use of parent during fork */
	time_t	u_outime;		/* user time at last sample */
	size_t	u_odsize, u_ossize;	/* for (clumsy) expansion swaps */
D 22
	size_t	u_vrpages[NOFILE];	/* number vread pages hanging on fd */
E 22
I 6
	int	u_limit[8];		/* see <sys/limit.h> */
I 15
#ifdef notdef
E 15
I 14
	unsigned u_vsave;		/* saved previous fault page number */
I 15
#endif
E 15
E 14
E 6
D 21
	int	u_stack[1];
E 21
I 21
	struct	quota	*u_quota;	/* user's quota structure */
	int	u_qflags;		/* per process quota flags */
D 22
	int	u_pflags;		/* per process other sorts of flags */
E 21

E 22
I 21
	int	u_stack[1];
E 21
					/*
					 * kernel stack per user
					 * extends from u + UPAGES*512
					 * backward not to reach here
					 */
I 12
/* SHOULD INSTEAD GROW STACK BACKWARDS ABOVE u. TOWARDS A VIRTUAL HOLE */
E 24
I 24
D 41
	caddr_t	u_dirp;			/* pathname pointer */
	struct	direct u_dent;		/* current directory entry */
	struct	inode *u_pdir;		/* inode of parent directory of dirp */
E 41
/* END TRASH */
E 43
I 30
D 41
	struct uprof {			/* profile arguments */
		short	*pr_base;	/* buffer base */
		unsigned pr_size;	/* buffer size */
		unsigned pr_off;	/* pc offset */
		unsigned pr_scale;	/* pc scaling */
	} u_prof;
I 40
	struct nameicache {		/* last successful directory search */
		int nc_prevoffset;	/* offset at which last entry found */
		ino_t nc_inumber;	/* inum of cached directory */
		dev_t nc_dev;		/* dev of cached directory */
		time_t nc_time;		/* time stamp for cache entry */
	} u_ncache;
E 41
E 40
I 33
D 38
#ifdef sun
	int	u_lofault;		/* catch faults in locore.s */
#endif
E 38
E 33
E 30
I 27
	int	u_stack[1];
E 65
E 27
E 24
E 12
};

I 3
D 61
/* u_eosys values */
D 46
#define	JUSTRETURN	0
#define	RESTARTSYS	1
I 4
#define	SIMULATERTI	2
I 28
#define	REALLYRETURN	3
E 46
I 46
#define	JUSTRETURN	1
#define	RESTARTSYS	2
I 47
#define NORMALRETURN	3
E 47
E 46
E 28
E 4

E 61
E 3
D 66
/* u_error codes */
I 44
D 65
#ifdef KERNEL
#include "errno.h"
#else
E 65
I 65
#ifndef KERNEL
E 65
E 44
I 16
D 20
#ifdef KERNEL
#include "../errno.h"
#else
E 20
E 16
D 3
#define	EPERM	1
#define	ENOENT	2
#define	ESRCH	3
#define	EINTR	4
#define	EIO	5
#define	ENXIO	6
#define	E2BIG	7
#define	ENOEXEC	8
#define	EBADF	9
#define	ECHILD	10
#define	EAGAIN	11
#define	ENOMEM	12
#define	EACCES	13
#define	EFAULT	14
#define	ENOTBLK	15
#define	EBUSY	16
#define	EEXIST	17
#define	EXDEV	18
#define	ENODEV	19
#define	ENOTDIR	20
#define	EISDIR	21
#define	EINVAL	22
#define	ENFILE	23
#define	EMFILE	24
#define	ENOTTY	25
#define	ETXTBSY	26
#define	EFBIG	27
#define	ENOSPC	28
#define	ESPIPE	29
#define	EROFS	30
#define	EMLINK	31
#define	EPIPE	32
#define	EDOM	33
#define	ERANGE	34
E 3
I 3
#include <errno.h>
I 44
#endif
E 66
I 66
/*
D 73
 * Redefinitions to make the debuggers happy for now...
 * This subterfuge brought to you by coredump() and procxmt().
 * These fields are *only* valid at those times!
E 73
I 73
 * Redefinitions to make the debuggers happy for now...  This subterfuge
 * brought to you by coredump() and trace_req().  These fields are *only*
 * valid at those times!
E 73
 */
D 69
#define	U_ar0	u_kproc.kp_proc.p_regs	/* copy of curproc->p_regs */
E 69
I 69
#define	U_ar0	u_kproc.kp_proc.p_md.md_regs /* copy of curproc->p_md.md_regs */
E 69
#define	U_tsize	u_kproc.kp_eproc.e_vm.vm_tsize
#define	U_dsize	u_kproc.kp_eproc.e_vm.vm_dsize
#define	U_ssize	u_kproc.kp_eproc.e_vm.vm_ssize
#define	U_sig	u_sigacts.ps_sig
#define	U_code	u_sigacts.ps_code
E 66
E 44
I 16
D 20
#endif
E 20
E 16
E 3

D 67
#ifdef KERNEL
extern	struct user u;
D 63
extern	struct user swaputl;
extern	struct user forkutl;
extern	struct user xswaputl;
extern	struct user xswap2utl;
extern	struct user pushutl;
extern	struct user vfutl;
E 63
I 63
D 66
extern	struct user *swaputl;
extern	struct user *forkutl;
extern	struct user *xswaputl;
extern	struct user *xswap2utl;
extern	struct user *pushutl;
extern	struct user *vfutl;
E 63
#endif
E 66
I 66
#else
E 67
I 67
#ifndef KERNEL
E 67
#define	u_ar0	U_ar0
#define	u_tsize	U_tsize
#define	u_dsize	U_dsize
#define	u_ssize	U_ssize
#define	u_sig	U_sig
#define	u_code	U_code
#endif /* KERNEL */
E 66
E 1
