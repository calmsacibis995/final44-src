h52167
s 00003/00000/00064
d D 8.4 95/01/09 18:16:17 cgd 7 6
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00012/00014/00052
d D 8.3 94/02/22 12:56:42 bostic 6 5
c ps(1) was having problem with the function declarations
c make them kernel specific
e
s 00003/00003/00063
d D 8.2 94/01/04 16:16:45 bostic 5 4
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00064
d D 8.1 93/06/02 19:55:05 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00001/00056
d D 7.3 92/07/08 00:46:43 torek 3 2
c new profiling stuff
e
s 00005/00003/00052
d D 7.2 92/06/19 23:28:07 mckusick 2 1
c add fields to save addr and ticks if we cannot process it at interrupt
e
s 00055/00000/00000
d D 7.1 91/05/09 20:39:36 bostic 1 0
c date and time created 91/05/09 20:39:36 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 5
#ifndef	_RESOURCEVAR_H_		/* tmp for user.h */
#define	_RESOURCEVAR_H_
E 5
I 5
D 6
#ifndef	_SYS_RESOURCEVAR_H_		/* tmp for user.h */
E 6
I 6
#ifndef	_SYS_RESOURCEVAR_H_
E 6
#define	_SYS_RESOURCEVAR_H_
E 5

/*
 * Kernel per-process accounting / statistics
 * (not necessarily resident except when running).
 */
struct pstats {
#define	pstat_startzero	p_ru
	struct	rusage p_ru;		/* stats for this proc */
	struct	rusage p_cru;		/* sum of stats for reaped children */
#define	pstat_endzero	pstat_startcopy

#define	pstat_startcopy	p_timer
	struct	itimerval p_timer[3];	/* virtual-time timers */

	struct uprof {			/* profile arguments */
D 3
		short	*pr_base;	/* buffer base */
E 3
I 3
		caddr_t	pr_base;	/* buffer base */
E 3
D 2
		unsigned pr_size;	/* buffer size */
		unsigned pr_off;	/* pc offset */
		unsigned pr_scale;	/* pc scaling */
E 2
I 2
		u_long	pr_size;	/* buffer size */
		u_long	pr_off;		/* pc offset */
		u_long	pr_scale;	/* pc scaling */
		u_long	pr_addr;	/* temp storage for addr until AST */
		u_long	pr_ticks;	/* temp storage for ticks until AST */
E 2
	} p_prof;
#define	pstat_endcopy	p_start
	struct	timeval p_start;	/* starting time */
};

/*
 * Kernel shareable process resource limits.  Because this structure
 * is moderately large but changes infrequently, it is normally
 * shared copy-on-write after forks.  If a group of processes
 * ("threads") share modifications, the PL_SHAREMOD flag is set,
 * and a copy must be made for the child of a new fork that isn't
 * sharing modifications to the limits.
 */
struct plimit {
	struct	rlimit pl_rlimit[RLIM_NLIMITS];
D 6
	int	p_lflags;		/* below */
E 6
I 6
#define	PL_SHAREMOD	0x01		/* modifications are shared */
	int	p_lflags;
E 6
	int	p_refcnt;		/* number of references */
};

D 6
/* pl_lflags: */
#define	PL_SHAREMOD	0x01		/* modifications are shared */

/* make copy of plimit structure */
struct	plimit *limcopy __P((struct plimit *lim));
I 3

/* add profiling ticks: in interrupt context, and from AST */
void	addupc_intr __P((struct proc *p, u_long pc, u_int ticks));
void	addupc_task __P((struct proc *p, u_long pc, u_int ticks));

E 6
/* add user profiling from AST */
D 6
#define	ADDUPROF(p)	addupc_task(p, (p)->p_stats->p_prof.pr_addr, \
			    (p)->p_stats->p_prof.pr_ticks)
E 6
I 6
#define	ADDUPROF(p)							\
	addupc_task(p,							\
	    (p)->p_stats->p_prof.pr_addr, (p)->p_stats->p_prof.pr_ticks)
E 6

I 6
#ifdef KERNEL
void	 addupc_intr __P((struct proc *p, u_long pc, u_int ticks));
void	 addupc_task __P((struct proc *p, u_long pc, u_int ticks));
I 7
void	 calcru __P((struct proc *p, struct timeval *up, struct timeval *sp,
	    struct timeval *ip));
E 7
struct plimit
	*limcopy __P((struct plimit *lim));
I 7
void	 ruadd __P((struct rusage *ru, struct rusage *ru2));
E 7
#endif
E 6
E 3
D 5
#endif	/* !_RESOURCEVAR_H_ */
E 5
I 5
#endif	/* !_SYS_RESOURCEVAR_H_ */
E 5
E 1
