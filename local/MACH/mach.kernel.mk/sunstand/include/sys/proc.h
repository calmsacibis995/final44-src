/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	proc.h,v $
 * Revision 2.2  89/07/12  00:13:35  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)proc.h 2.32 88/02/08 SMI; from UCB 4.24 83/07/01	*/

#ifndef	_sys_proc_h
#define	_sys_proc_h

/*
 * One structure allocated per active
 * process. It contains all data needed
 * about the process while the
 * process may be swapped out.
 * Other per process data (user.h)
 * is swapped with the process.
 */
struct	proc {
	struct	proc *p_link;	/* linked list of running processes */
	struct	proc *p_rlink;
	struct	proc *p_nxt;	/* linked list of allocated proc slots */
	struct	proc **p_prev;	/* also zombies, and free procs */
	struct	as *p_as;	/* address space description */
	struct	segu_data *p_useg;
				/* information required to map the u area */
	char	p_usrpri;	/* user-priority based on p_cpu and p_nice */
	char	p_pri;		/* priority, negative is high */
	char	p_cpu;		/* (decayed) cpu usage solely for scheduling */
	char	p_stat;
	char	p_time;		/* seconds resident (for scheduling) */
	char	p_nice;		/* nice for cpu usage */
	char	p_slptime;	/* seconds since last block (sleep) */
	char	p_cursig;
	int	p_sig;		/* signals pending to this process */
	int	p_sigmask;	/* current signal mask */
	int	p_sigignore;	/* signals being ignored */
	int	p_sigcatch;	/* signals being caught by user */
	int	p_flag;
	short	p_uid;		/* user id, used to direct tty signals */
	short	p_suid;		/* saved (effective) user id from exec */
	short	p_sgid;		/* saved (effective) group id from exec */
	short	p_pgrp;		/* name of process group leader */
	short	p_pid;		/* unique process id */
	short	p_ppid;		/* process id of parent */
	u_short	p_xstat;	/* Exit status for wait */
	short	p_cpticks;	/* ticks of cpu time, used for p_pctcpu */
	struct	ucred *p_cred;  /* Process credentials */
	struct	rusage *p_ru;	/* mbuf holding exit information */
	size_t	p_tsize;	/* size of text (clicks) */
	size_t	p_dsize;	/* size of data space (clicks) */
	size_t	p_ssize;	/* copy of stack size (clicks) */
	size_t 	p_rssize; 	/* current resident set size in clicks */
	size_t	p_maxrss;	/* copy of u.u_limit[MAXRSS] */
	size_t	p_swrss;	/* resident set size before last swap */
	caddr_t p_wchan;	/* event process is awaiting */
	long	p_pctcpu;	/* (decayed) %cpu for this process */
	struct	proc *p_pptr;	/* pointer to process structure of parent */
	struct	proc *p_cptr;	/* pointer to youngest living child */
	struct	proc *p_osptr;	/* pointer to older sibling processes */
	struct	proc *p_ysptr;	/* pointer to younger siblings */
	struct	proc *p_tptr;	/* pointer to process structure of tracer */
	struct	itimerval p_realtimer;
	short	p_idhash;	/* hashed based on p_pid for kill+exit+... */
	short	p_swlocks;	/* number of swap vnode locks held */
#ifdef	sun386
	struct	v86dat *p_v86;	/* pointer to v86 structure */
#endif	sun386
};

#define	PIDHSZ		64
#define	PIDHASH(pid)	((pid) & (PIDHSZ - 1))

#ifdef	KERNEL
short	pidhash[PIDHSZ];
struct	proc *pfind();
struct	proc *proc, *procNPROC;	/* the proc table itself */
struct  proc *freeproc, *zombproc, *allproc;
			/* lists of procs in various states */
int	nproc;

#define	NQS	32		/* 32 run queues */
struct	prochd {
	struct	proc *ph_link;	/* linked list of running processes */
	struct	proc *ph_rlink;
} qs[NQS];
int	whichqs;		/* bit mask summarizing non-empty qs's */
#endif	KERNEL

/* stat codes */
#define	SSLEEP	1		/* awaiting an event */
#define	SWAIT	2		/* (abandoned state) */
#define	SRUN	3		/* running */
#define	SIDL	4		/* intermediate state in process creation */
#define	SZOMB	5		/* has exited, waiting for parent to pick up status */
#define	SSTOP	6		/* stopped */

/* flag codes */
#define	SLOAD	0x0000001	/* in core */
#define	SSYS	0x0000002	/* swapper or pager process */
#define	SLOCK	0x0000004	/* process being swapped out */
#define	SSWAP	0x0000008	/* save area flag */
#define	STRC	0x0000010	/* process is being traced */
#define	SWTED	0x0000020	/* parent has been told that this process stopped */
#define	SULOCK	0x0000040	/* user settable lock in core */
#define	SPAGE	0x0000080	/* process in page wait state XXX: never set */
#define	SKEEP	0x0000100	/* another flag to prevent swap out */
#define	SOMASK	0x0000200	/* restore old mask after taking signal */
#define	SWEXIT	0x0000400	/* working on exiting */
#define	SPHYSIO	0x0000800	/* doing physical i/o (bio.c) */
#define	SVFORK	0x0001000	/* process resulted from vfork() */
#define	SVFDONE	0x0002000	/* another vfork flag */
#define	SNOVM	0x0004000	/* no vm, parent in a vfork() */
#define	SPAGI	0x0008000	/* init data space on demand, from inode */
#define	SSEQL	0x0010000	/* user warned of sequential vm behavior */
#define	SUANOM	0x0020000	/* user warned of random vm behavior */
#define	STIMO	0x0040000	/* timing out during sleep */
#define	SPGLDR	0x0080000	/* process is session process group leader */
#define	STRACNG	0x0100000	/* process is tracing another process */
#define	SOWEUPC	0x0200000	/* owe process an addupc() call at next ast */
#define	SSEL	0x0400000	/* selecting; wakeup/waiting danger */
#define	SLOGIN	0x0800000	/* a login process (legit child of init) */
#define	SFAVORD	0x2000000	/* favored treatment in swapout and pageout */
#define SLKDONE 0x4000000	/* record-locking has been done */
#define STRCSYS 0x8000000       /* tracing system calls */

#endif	_sys_proc_h
