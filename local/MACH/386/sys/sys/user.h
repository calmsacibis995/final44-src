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
 * $Log:	user.h,v $
 * Revision 2.15  89/08/09  09:13:53  jsb
 * 	Remove unused fields from struct utask.
 * 	[89/07/14            dbg]
 * 
 * Revision 2.14  89/07/14  15:39:37  rvb
 * 	New Signal Handling from Olivetti.
 * 	[89/07/10            rvb]
 * 
 * Revision 2.13  89/04/22  15:32:48  gm0w
 * 	Removed MACH_VFS changes.  Created user indentity structure
 * 	from [ug]ids, groups and pag for use in network filesystem
 * 	operations requiring additional authentication semantics.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.12  89/03/09  22:09:58  rpd
 * 	More cleanup.
 * 
 * Revision 2.11  89/02/28  11:09:38  mrt
 * 	Replaced the cr_ruid field in ucred which had been acidently
 * 	deleted.
 * 	[89/02/28            mrt]
 * 
 * Revision 2.10  89/02/27  21:04:26  mrt
 * 	Made most items in uthread, utask and user structures
 * 	unconditional. uu_cdir and uu_rdir are still conditional
 * 	on MACH_VFS which is defined to be true outside of the kernel.
 * 	Thus the uthread structure outside the kernel will only be
 * 	valid for MACH_VFS kernels. 
 * 	[89/02/27            mrt]
 * 
 * Revision 2.9  89/02/25  17:58:06  gm0w
 * 	Got rid of MACH conditional and all non-MACH code.
 * 	Made ROMP_DUALCALL, MACH_VFS, MACH_AFS conditionals 
 * 	always true outside of the kernel. Made VICE always
 * 	false outside of kernel for X75 compatibility- must be changed.
 * 	[89/02/14            mrt]
 * 
 * Revision 2.8  89/01/28  14:16:57  jsb
 * 	MACH_AFS: Added cr_pag to struct ucred so that we don't have to store
 * 	the pag in the group list.
 * 	[89/01/26  12:37:52  jsb]
 * 
 * Revision 2.7  89/01/23  22:29:42  af
 * 	Mips: signal trampoline like balance
 * 	[89/01/10            af]
 * 
 * Revision 2.6  89/01/18  01:20:45  jsb
 * 	Vnode support, including support for credentials.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.5  88/08/24  02:51:39  mwyoung
 * 	Condensed CS conditionals.
 * 	[88/08/22  22:29:29  mwyoung]
 * 	
 * 	Adjusted include file references.
 * 	[88/08/17  02:27:11  mwyoung]
 *
 * 16-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Add values for stack start, end, and direction of growth, so we
 *	can handle limit changes.
 *
 * 28-Apr-88  David Golub (dbg) at Carnegie-Mellon University
 *	Move u_rpause and u_rfs from thread to task U-area - they are
 *	both global process state.
 *
 * 20-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added URPW_* resource pause flag bit definitions (renamed and
 *	moved from <sys/fs.h>).
 *	[ V5.1(XF23) ]
 *
 * 11-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Move controlling terminal information to proc structure.
 *	[ V5.1(XF23) ]
 *
 *  7-Mar-88  David Kirschen (kirschen) at Encore Computer Corporation
 *      Optimize u-area references for the multimax
 *
 * 26-Feb-88  David Kirschen (kirschen) at Encore Computer Corporation
 *      Add include of param.h for NGROUPS, etc.
 *
 * 25-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Rather than have "u" expand to current_thread()->u_address, have
 *	it expand to the constant U_ADDRESS which is updated by load_context
 *	when the thread changes.  If "u" is defined, then user.h won't define
 *	it.
 *
 * 06-Jan-88  Jay Kistler (jjk) at Carnegie Mellon University
 *	VICE: Removed Fid typedef as it is no longer used anywhere and 
 *	it was causing name conflicts outside the kernel.
 *
 * 19-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Eliminated conditionals, purged history.
 *
 * 10-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Move UMODE_* bit definitions to <sys/syscall.h>.
 *	[ V5.1(XF18) ]
 *
 * 03-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS: Add new RFS_EROOT definition.
 *	[ V5.1(F2) ]
 *
 * 27-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC: Added new u_maxuprc field to allow the maximum
 *	number of processes per user ID to vary for a process tree.
 *	[ V5.1(F1) ]
 *
 * 18-Oct-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  added u_rfs definition.
 *	[V1(1)]
 *
 * 07-Sep-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC:  added modes field and symbol definitions.
 *	[V1(1)]
 *
 * 03-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RPAUSE:  added resource pause field and symbol definitions.
 *	[V1(1)]
 *
 * 22-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  added u_syscode definition.
 *	[V1(1)]
 *
 * 14-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded to 4.2BSD.  Carried over changes below.
 *	[V1(1)]
 *
 * 28-Jul-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed to include errno.h from include directory (V3.05c).
 *
 * 22-Jun-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_AID:  added u_aid field to record new process account ID
 *	(V3.05a).
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)user.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_USER_H_
#define _SYS_USER_H_

#ifdef	KERNEL
#include <mach_rfs.h>
#include <vice.h>
#endif	KERNEL

#include <mach/boolean.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/namei.h>
#include <machine/pcb.h>

#ifdef	KERNEL
#include <kern/lock.h>
#else	KERNEL
#ifndef	_KERN_LOCK_H_
#define _KERN_LOCK_H_
typedef int simple_lock_data_t;
#endif	_KERN_LOCK_H_
#endif	KERNEL

/*
 * Per process structure containing data that
 * isn't needed in core when the process is swapped out.
 */

#define MAXCOMLEN	16		/* <= MAXNAMLEN, >= sizeof(ac_comm) */

#if	(defined(KERNEL) || defined(SHOW_UTT))
/*
 *	Per-thread U area.
 *
 *	It is likely that this structure contains no fields that must be
 *	saved between system calls.
 */
struct uthread {
	int	*uu_ar0;		/* address of users saved R0 */

/* syscall parameters, results and catches */
	/* if the size of uu_arg changes, update RT_MAX_ARGS in vicermt.h */
	int	uu_arg[8];		/* arguments to current system call */
	int	*uu_ap;			/* pointer to arglist */
	label_t	uu_qsave;		/* for non-local gotos on interrupts */
	union {				/* syscall return values */
		struct	{
			int	R_val1;
			int	R_val2;
		} u_rv;
#define r_val1	u_rv.R_val1
#define r_val2	u_rv.R_val2
		off_t	r_off;
		time_t	r_time;
	} uu_r;
	char	uu_error;		/* return error code */
	char	uu_eosys;		/* special action on end of syscall */
	struct fs *uu_rpsfs;		/* resource pause file system */
	char	uu_rpswhich;		/* resource pause operation selection */
#define URPW_FNOSPC	0x01		/* - low on fragments */
#define URPW_INOSPC	0x02		/* - low on inodes */
#define URPW_QNOSPC	0x04		/* - out of quota */
#define URPW_POLL	0x40		/* - poll until available */
#define URPW_NOTIFY	0x80		/* - pause in progress */
	u_char	uu_rpause;		/* resource pause flags: */
#define URPS_AGAIN	01		/* - no child processes available */
#define URPS_NOMEM	02		/* - no memory available */
#define URPS_NFILE	04		/* - file table overflow */
#define URPS_NOSPC	010		/* - no space on device */

	short	uu_rfscode;		/* MACH_RFS call number */
	short	uu_rfsncnt;		/* MACH_RFS namei() call count */

	/* ITC VICE remote file system support */
	short	uu_rmt_code;		/* remote file system call number */
	short	uu_rmt_ncnt;		/* remote file system namei() 
					   call count */
	char	uu_rmt_requested;	/* For namei, iget, etc: caller
					   can deal with remote files */
	u_char  uu_rmt_follow1 /*:1*/;	/* Follow symbolic link if it is last
					   component of first pathname of
					   a system call */
	u_char  uu_rmt_follow2 /*:1*/;	/* ... of second pathname ... */
	struct	buf *uu_rmt_path_buf;	/* buffer containing the pathname
					   looked up during the namei */
	char	*uu_rmt_path;		/* pointer into uu_rmt_path_buf to the
					   uninterpreted part of the path */
					/* Block for BOGUS namei communication*/
	struct	rmt_saved_data *uu_rmt_saved_data;

/* namei & co. */
	struct unameicache {		/* last successful directory search */
		int nc_prevoffset;	/* offset at which last entry found */
		ino_t nc_inumber;	/* inum of cached directory */
		dev_t nc_dev;		/* dev of cached directory */
		time_t nc_time;		/* time stamp for cache entry */
	} uu_ncache;
	struct	nameidata uu_nd;

/* thread exception handling */
	int	uu_code;			/* ``code'' to trap */
	char uu_cursig;				/* p_cursig for exc. */
	int  uu_sig;				/* p_sig for exc. */
};

/*
 *	Per-task U area - global process state.
 */
struct utask {
	struct	proc *uu_procp;		/* pointer to proc structure */
	char	uu_comm[MAXCOMLEN + 1];

/* 1.1 - processes and protection */
#if	ibmrt
	char	uu_calltype;	/* ROMP_DUALCALL 0 - old calling sequence */
#endif	ibmrt
	struct identity *uu_identity;	/* user identity */

/* 1.2 - memory management */
	size_t	uu_tsize;		/* text size (clicks) */
	size_t	uu_dsize;		/* data size (clicks) */
	size_t	uu_ssize;		/* stack size (clicks) */
	caddr_t	uu_text_start;		/* text starting address */
	caddr_t	uu_data_start;		/* data starting address */
	caddr_t	uu_stack_start;		/* stack starting address */
	caddr_t	uu_stack_end;		/* stack ending address */
	boolean_t uu_stack_grows_up;	/* stack grows at high end? */
	time_t	uu_outime;		/* user time at last sample */

/* 1.3 - signal management */
	int	(*uu_signal[NSIG+1])();	/* disposition of signals */
	int	uu_sigmask[NSIG+1];	/* signals to be blocked */
#ifdef	i386
	int	(*uu_sigreturn)();
#endif	i386
#ifdef	multimax
	int	(*uu_sigcatch)();	/* used as a way not to do tramp. */
#endif	multimax
#if	defined(balance) || defined(mips)
	int	(*uu_sigtramp)();	/* signal trampoline code */
#endif	defined(balance) || defined(mips)
	int	uu_sigonstack;		/* signals to take on sigstack */
	int	uu_sigintr;		/* signals that interrupt syscalls */
	int	uu_oldmask;		/* saved mask from before sigpause */
	struct	sigstack uu_sigstack;	/* sp & on stack state variable */

/* 1.4 - descriptor management */
	struct	file *uu_ofile[NOFILE];	/* file structures for open files */
	char	uu_pofile[NOFILE];	/* per-process flags of open files */
	int	uu_lastfile;		/* high-water mark of uu_ofile */
#define UF_EXCLOSE 	0x1		/* auto-close on exec */
#define UF_MAPPED 	0x2		/* mapped from device */

	struct	inode *uu_cdir;		/* current directory */
	struct	inode *uu_rdir;		/* root directory of current process */
	short	uu_cmask;		/* mask for file creation */

/* 1.5 - timing and statistics */
	struct	rusage uu_ru;		/* stats for this proc */
	struct	rusage uu_cru;		/* sum of stats for reaped children */
	struct	itimerval uu_timer[3];
	struct	timeval uu_start;
	short	uu_acflag;

	struct uuprof {			/* profile arguments */
		simple_lock_data_t *pr_lock;	/* lock for thread updating */
		short	*pr_base;	/* buffer base */
		unsigned pr_size;	/* buffer size */
		unsigned pr_off;	/* pc offset */
		unsigned pr_scale;	/* pc scaling */
	} uu_prof;
	short	uu_aid;			/* account id -- OBSOLETE delete soon */
	u_short	uu_maxuprc;		/* max processes per UID (per tree) */
	u_char	uu_rpause;		/* resource pause flags: */
#define URPS_AGAIN	01		/* - no child processes available */
#define URPS_NOMEM	02		/* - no memory available */
#define URPS_NFILE	04		/* - file table overflow */
#define URPS_NOSPC	010		/* - no space on device */
	/* MACH_RFS support */
	char	uu_rfs;			/* remote syscall state bits: */
#define URFS_CDIR	01		/* - current directory is remote */
#define URFS_RDIR	02		/* - root directory is remote */
#define URFS_EROOT	04		/* - reject accesses above root */

/* 1.6 - resource controls */
	struct	rlimit uu_rlimit[RLIM_NLIMITS];
	struct	quota *uu_quota;	/* user's quota structure */
	int	uu_qflags;		/* per process quota flags */

	char	uu_modes;		/* process modes: */
	/* VICE stuff */
	struct  urmtWd {		/* Current directory-new file system */
	    dev_t dev;			/* Mounted file system of the cwd */
	    long fid[3];		/* Vice II file identifier for cwd */
	} uu_rmtWd;
	struct  file *uu_textfile;	/* file object for a text segment */
	dev_t	uu_rmt_dev;		/* Venus is listening on this device */
	long	uu_rmt_pag;		/* Process authentication group */
};

#endif	(defined(KERNEL) || defined(SHOW_UTT))

struct	user {
	struct	pcb u_pcb;
	struct	proc *u_procp;		/* pointer to proc structure */
	int	*u_ar0;			/* address of users saved R0 */
	char	u_comm[MAXCOMLEN + 1];

/* syscall parameters, results and catches */
	/* if the size of uu_arg changes, update RT_MAX_ARGS in vicermt.h */
	int	u_arg[8];		/* arguments to current system call */
	int	*u_ap;			/* pointer to arglist */
	label_t	u_qsave;		/* for non-local gotos on interrupts */
	union {				/* syscall return values */
		struct	{
			int	R_val1;
			int	R_val2;
		} u_rv;
#define r_val1	u_rv.R_val1
#define r_val2	u_rv.R_val2
		off_t	r_off;
		time_t	r_time;
	} u_r;
	char	u_error;		/* return error code */
	char	u_eosys;		/* special action on end of syscall */

/* 1.1 - processes and protection */
#if	ibmrt
	char	u_calltype;	/* 0 == old calling sequence ROMP_DUALCALL */
#endif	ibmrt

	struct identity *u_identity;	/* user identity */

/* 1.2 - memory management */
	size_t	u_tsize;		/* text size (clicks) */
	size_t	u_dsize;		/* data size (clicks) */
	size_t	u_ssize;		/* stack size (clicks) */
	caddr_t	u_text_start;		/* text starting address */
	caddr_t	u_data_start;		/* data starting address */
	caddr_t	u_stack_start;		/* stack starting address */
	caddr_t	u_stack_end;		/* stack ending address */
	int	u_stack_grows_up;	/* stack grows at high end? */
	time_t	u_outime;		/* user time at last sample */

/* 1.3 - signal management */
	int	(*u_signal[NSIG+1])();	/* disposition of signals */
	int	u_sigmask[NSIG+1];	/* signals to be blocked */
#ifdef	i386
	int	(*u_sigreturn)();
#endif	i386
#ifdef	multimax
	int	(*u_sigcatch)();	/* used as a way not to do tramp. */
#endif	multimax
#if	defined(balance) || defined(mips)
	int	(*u_sigtramp)();	/* signal trampoline code */
#endif	defined(balance) || defined(mips)
	int	u_sigonstack;		/* signals to take on sigstack */
	int	u_sigintr;		/* signals that interrupt syscalls */
	int	u_oldmask;		/* saved mask from before sigpause */
	int	u_code;			/* ``code'' to trap */
	struct	sigstack u_sigstack;	/* sp & on stack state variable */
#define u_onstack	u_sigstack.ss_onstack
#define u_sigsp		u_sigstack.ss_sp

/* 1.4 - descriptor management */
	struct	file *u_ofile[NOFILE];	/* file structures for open files */
	char	u_pofile[NOFILE];	/* per-process flags of open files */
	int	u_lastfile;		/* high-water mark of u_ofile */
#define UF_EXCLOSE 	0x1		/* auto-close on exec */
#define UF_MAPPED 	0x2		/* mapped from device */
	struct	inode *u_cdir;		/* current directory */
	struct	inode *u_rdir;		/* root directory of current process */
#define u_ttyp	u_procp->p_ttyp		/* controlling tty pointer */
#define u_ttyd	u_procp->p_ttyd		/* controlling tty dev */
	short	u_cmask;		/* mask for file creation */

/* 1.5 - timing and statistics */
	struct	rusage u_ru;		/* stats for this proc */
	struct	rusage u_cru;		/* sum of stats for reaped children */
	struct	itimerval u_timer[3];
	int	u_XXX[3];
	struct	timeval u_start;
	short	u_acflag;

	struct uprof {			/* profile arguments */
		short	*pr_base;	/* buffer base */
		unsigned pr_size;	/* buffer size */
		unsigned pr_off;	/* pc offset */
		unsigned pr_scale;	/* pc scaling */
	} u_prof;
	short	u_aid;			/* account id -- OBSOLETE to be removed soon*/
	u_short	u_maxuprc;		/* max processes per UID (per tree) */
	struct fs *u_rpsfs;		/* resource pause file system */
	char	u_rpswhich;		/* resource pause operation selection */
#define URPW_FNOSPC	0x01		/* - low on fragments */
#define URPW_INOSPC	0x02		/* - low on inodes */
#define URPW_QNOSPC	0x04		/* - out of quota */
#define URPW_POLL	0x40		/* - poll until available */
#define URPW_NOTIFY	0x80		/* - pause in progress */
	u_char	u_rpause;		/* resource pause flags: */
#define URPS_AGAIN	01		/* - no child processes available */
#define URPS_NOMEM	02		/* - no memory available */
#define URPS_NFILE	04		/* - file table overflow */
#define URPS_NOSPC	010		/* - no space on device */
	char	u_modes;		/* process modes: */
	/* MACH_RFS support */
	char	u_rfs;			/* remote syscall state bits: */
#define URFS_CDIR	01		/* - current directory is remote */
#define URFS_RDIR	02		/* - root directory is remote */
#define URFS_EROOT	04		/* - reject accesses above root */
	short	u_rfscode;		/* remote file system call number */
	short	u_rfsncnt;		/* RFS namei() call count*/
	/* ITC VICE remote file system support */
	short	u_rmt_code;		/* remote file system call number */
	short	u_rmt_ncnt;		/* RFS namei() call count */
	struct  rmtWd {			/* Current directory-new file system */
	    dev_t dev;			/* Mounted file system of the cwd */
	    long fid[3];		/* Vice II file identifier for cwd */
	} u_rmtWd;
	struct  file *u_textfile;	/* file object for a text segment */
	char	u_rmt_requested;	/* For namei, iget, etc: caller
					   can deal with remote files */
	u_char u_rmt_follow1 /*:1*/;	/* Follow symbolic link if it is last
					   component of first pathname of
					   a system call */
	u_char u_rmt_follow2 /*:1*/;	/* ... of second pathname ... */
	dev_t	u_rmt_dev;		/* Venus is listening on this device */
	struct	buf *u_rmt_path_buf;	/* buffer containing the pathname
					   looked up during the namei */
	char	*u_rmt_path;		/* pointer into u_rmt_path_buf to the
					   uninterpreted part of the path */
	long	u_rmt_pag;		/* Process authentication group */
					/* Block for BOGUS namei communication */
	struct	rmt_saved_data *u_rmt_saved_data;

/* 1.6 - resource controls */
	struct	rlimit u_rlimit[RLIM_NLIMITS];
	struct	quota *u_quota;		/* user's quota structure */
	int	u_qflags;		/* per process quota flags */

/* namei & co. */
	struct nameicache {		/* last successful directory search */
		int nc_prevoffset;	/* offset at which last entry found */
		ino_t nc_inumber;	/* inum of cached directory */
		dev_t nc_dev;		/* dev of cached directory */
		time_t nc_time;		/* time stamp for cache entry */
	} u_ncache;
	struct	nameidata u_nd;

	int	u_stack[1];
};


/* identity of user */
struct identity {
	u_short	id_ref;			/* reference count */
	uid_t	id_uid;			/* effective user id */
	uid_t	id_ruid;		/* real user id */
	gid_t	id_gid;			/* effective group id */
	gid_t	id_rgid;		/* real group id */
	gid_t	id_groups[NGROUPS];	/* groups, 0 terminated */
	long	id_pag;			/* AFS process authentication group */
};

#ifdef	KERNEL
extern struct identity *alloc_identity();
extern struct identity *change_identity();
extern struct identity *copy_identity();
extern struct identity *root_identity;
#endif	KERNEL

/* u_eosys values */
#define JUSTRETURN	1
#define RESTARTSYS	2
#define NORMALRETURN	3

/* u_error codes */
#include <sys/errno.h>

#ifdef	KERNEL
#include <kern/thread.h>

#ifndef	u
#ifdef	multimax
extern struct u_address	active_uareas[NCPUS];
#define u       (active_uareas[cpu_number()])
#else	multimax
#ifdef	balance
#define u	(*(struct u_address *) 0x40)
#else	balance
#define u	(current_thread()->u_address)
#endif	balance
#endif	multimax
#endif	u

#define u_pcb		uthread->uu_pcb
#define u_procp		utask->uu_procp
#define u_ar0		uthread->uu_ar0
#define u_comm		utask->uu_comm
#define u_calltype	utask->uu_calltype	/* ROMP_DUALCALL */

#define u_arg		uthread->uu_arg
#define u_ap		uthread->uu_ap
#define u_qsave		uthread->uu_qsave
#define u_r		uthread->uu_r
#define u_error		uthread->uu_error
#define u_eosys		uthread->uu_eosys

#define u_identity	utask->uu_identity
#define u_uid		utask->uu_identity->id_uid
#define u_gid		utask->uu_identity->id_gid
#define u_groups	utask->uu_identity->id_groups
#define u_ruid		utask->uu_identity->id_ruid
#define u_rgid		utask->uu_identity->id_rgid

#define u_tsize		utask->uu_tsize
#define u_dsize		utask->uu_dsize
#define u_ssize		utask->uu_ssize
#define u_text_start	utask->uu_text_start
#define u_data_start	utask->uu_data_start
#define u_stack_start	utask->uu_stack_start
#define u_stack_end	utask->uu_stack_end
#define u_stack_grows_up utask->uu_stack_grows_up
#define u_outime	utask->uu_outime

#define u_signal	utask->uu_signal
#ifdef	i386
#define	u_sigreturn	utask->uu_sigreturn
#endif	i386
#ifdef	multimax
#define u_sigcatch	utask->uu_sigcatch
#endif	multimax
#if	defined(balance) || defined(mips)
#define u_sigtramp	utask->uu_sigtramp
#endif	defined(balance) || defined(mips)
#define u_sigmask	utask->uu_sigmask
#define u_sigonstack	utask->uu_sigonstack
#define u_sigintr	utask->uu_sigintr
#define u_oldmask	utask->uu_oldmask
#define u_code		uthread->uu_code
#define u_sigstack	utask->uu_sigstack

#define u_onstack	u_sigstack.ss_onstack
#define u_sigsp		u_sigstack.ss_sp

#define u_ofile		utask->uu_ofile
#define u_pofile	utask->uu_pofile
#define u_lastfile	utask->uu_lastfile
#define u_cdir		utask->uu_cdir
#define u_rdir		utask->uu_rdir
#undef	u_ttyp
#undef	u_ttyd
#define u_ttyp		utask->uu_procp->p_ttyp
#define u_ttyd		utask->uu_procp->p_ttyd
#define u_cmask		utask->uu_cmask

#define u_ru		utask->uu_ru
#define u_cru		utask->uu_cru
#define u_timer		utask->uu_timer
#define u_XXX		utask->uu_XXX
#define u_start		utask->uu_start
#define u_acflag	utask->uu_acflag

#define u_prof		utask->uu_prof

#define u_aid		utask->uu_aid    /* OBSOLETE to be removed soon */
#define u_maxuprc	utask->uu_maxuprc
#define u_rpsfs		uthread->uu_rpsfs
#define u_rpswhich	uthread->uu_rpswhich
#define u_rpause	utask->uu_rpause
#define u_modes		utask->uu_modes
#if	MACH_RFS
#define u_rfs		utask->uu_rfs
#define u_rfscode	uthread->uu_rfscode
#define u_rfsncnt	uthread->uu_rfsncnt
#endif	MACH_RFS
#if	VICE
#define u_rmt_code	uthread->uu_rmt_code
#define u_rmt_ncnt	uthread->uu_rmt_ncnt
#define u_rmtWd		utask->uu_rmtWd
#define u_textfile	utask->uu_textfile
#define u_rmt_requested	uthread->uu_rmt_requested
#define u_rmt_follow1	uthread->uu_rmt_follow1
#define u_rmt_follow2	uthread->uu_rmt_follow2
#define u_rmt_dev	utask->uu_rmt_dev
#define u_rmt_path_buf	uthread->uu_rmt_path_buf
#define u_rmt_path	uthread->uu_rmt_path
#define u_rmt_pag	utask->uu_rmt_pag
#define u_rmt_saved_data uthread->uu_rmt_saved_data
#endif	VICE

#define u_rlimit	utask->uu_rlimit
#define u_quota		utask->uu_quota
#define u_qflags	utask->uu_qflags

#define u_ncache	uthread->uu_ncache
#define u_nd		uthread->uu_nd

#define u_sig		uthread->uu_sig
#define u_cursig	uthread->uu_cursig

#endif	KERNEL
#endif	_SYS_USER_H_
