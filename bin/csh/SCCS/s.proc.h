h55666
s 00002/00002/00073
d D 8.1 93/05/31 16:42:50 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00075
d D 5.8 93/05/22 19:06:47 christos 13 12
c Fixed gcc -Wall warnings
e
s 00001/00001/00074
d D 5.7 91/07/19 17:31:23 christos 12 11
c stdio based version; brace glob fix; builtin prototypes
e
s 00002/00002/00073
d D 5.6 91/06/24 21:53:45 christos 11 10
c change process index and maxindex to ints.
e
s 00000/00001/00075
d D 5.5 91/06/09 18:39:56 christos 10 9
c replaced PNULL def with NULL
e
s 00039/00048/00037
d D 5.4 91/06/04 13:31:56 bostic 9 8
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00005/00004/00080
d D 5.3 91/04/04 18:17:56 bostic 8 7
c new copyright; att/bsd/shared
e
s 00001/00001/00083
d D 5.2 85/06/06 13:10:03 edward 7 6
c cleaning up after bozos
e
s 00007/00001/00077
d D 5.1 85/06/04 11:12:16 dist 6 5
c Add copyright
e
s 00001/00005/00077
d D 4.5 84/12/13 14:40:29 edward 5 4
c performance
e
s 00002/00002/00080
d D 4.4 83/02/09 14:18:02 sam 4 3
c cleanups from sun
e
s 00004/00004/00078
d D 4.3 83/02/03 09:13:13 sam 3 2
c use high precision time calls
e
s 00001/00003/00081
d D 4.2 82/12/30 17:35:46 sam 2 1
c finally works (updated for 4.1c and merged with sun)
e
s 00084/00000/00000
d D 4.1 80/10/09 12:41:42 bill 1 0
c date and time created 80/10/09 12:41:42 by bill
e
u
U
t
T
I 1
D 5
/* %M% %I% %G% */
E 5
I 5
D 6
/* %W% (Berkeley) %G% */
E 6
I 6
D 8
/*
 * Copyright (c) 1980 Regents of the University of California.
D 7
 * All rights reserved.  The Berkeley software License Agreement
E 7
I 7
 * All rights reserved.  The Berkeley Software License Agreement
E 7
 * specifies the terms and conditions for redistribution.
E 8
I 8
/*-
D 14
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * %sccs.include.redist.c%
E 8
 *
 *	%W% (Berkeley) %G%
 */
E 6
E 5

/*
D 9
 * C shell - process structure declarations
 */

/*
E 9
 * Structure for each process the shell knows about:
 *	allocated and filled by pcreate.
 *	flushed by pflush; freeing always happens at top level
 *	    so the interrupt level has less to worry about.
 *	processes are related to "friends" when in a pipeline;
 *	    p_friends links makes a circular list of such jobs
 */
D 9
struct process	{
	struct	process *p_next;	/* next in global "proclist" */
	struct	process	*p_friends;	/* next in job list (or self) */
	struct	directory *p_cwd;	/* cwd of the job (only in head) */
	short	unsigned p_flags;	/* various job status flags */
	char	p_reason;		/* reason for entering this state */
	char	p_index;		/* shorthand job index */
D 4
	short	p_pid;
	short	p_jobid;		/* pid of job leader */
E 4
I 4
	int	p_pid;
	int	p_jobid;		/* pid of job leader */
E 4
	/* if a job is stopped/background p_jobid gives its pgrp */
D 3
	time_t	p_btime;		/* begin time */
	time_t	p_etime;		/* end time */
	long	p_stime;		/* system cpu time */
	long	p_utime;		/* user cpu time */
E 3
I 3
	struct	timeval p_btime;	/* begin time */
	struct	timeval p_etime;	/* end time */
E 3
D 2
#ifdef VMUNIX
	struct	vtimes p_vtimes;
#endif
E 2
I 2
	struct	rusage p_rusage;
I 3
D 5
	long	p_utime;	/* XXX */
	long	p_stime;	/* XXX */
E 5
E 3
E 2
	char	*p_command;		/* first PMAXLEN chars of command */
E 9
I 9
struct process {
    struct process *p_next;	/* next in global "proclist" */
    struct process *p_friends;	/* next in job list (or self) */
    struct directory *p_cwd;	/* cwd of the job (only in head) */
    short unsigned p_flags;	/* various job status flags */
    char    p_reason;		/* reason for entering this state */
D 11
    char    p_index;		/* shorthand job index */
E 11
I 11
    int     p_index;		/* shorthand job index */
E 11
    int     p_pid;
    int     p_jobid;		/* pid of job leader */
    /* if a job is stopped/background p_jobid gives its pgrp */
    struct timeval p_btime;	/* begin time */
    struct timeval p_etime;	/* end time */
    struct rusage p_rusage;
    Char   *p_command;		/* first PMAXLEN chars of command */
E 9
};

/* flag values for p_flags */
D 9
#define	PRUNNING	(1<<0)		/* running */
#define	PSTOPPED	(1<<1)		/* stopped */
#define	PNEXITED	(1<<2)		/* normally exited */
#define	PAEXITED	(1<<3)		/* abnormally exited */
#define	PSIGNALED	(1<<4)		/* terminated by a signal != SIGINT */
E 9
I 9
#define	PRUNNING	(1<<0)	/* running */
#define	PSTOPPED	(1<<1)	/* stopped */
#define	PNEXITED	(1<<2)	/* normally exited */
#define	PAEXITED	(1<<3)	/* abnormally exited */
#define	PSIGNALED	(1<<4)	/* terminated by a signal != SIGINT */
E 9

#define	PALLSTATES	(PRUNNING|PSTOPPED|PNEXITED|PAEXITED|PSIGNALED|PINTERRUPTED)
D 9
#define	PNOTIFY		(1<<5)		/* notify async when done */
#define	PTIME		(1<<6)		/* job times should be printed */
#define	PAWAITED	(1<<7)		/* top level is waiting for it */
#define	PFOREGND	(1<<8)		/* started in shells pgrp */
#define	PDUMPED		(1<<9)		/* process dumped core */
#define	PDIAG		(1<<10)		/* diagnostic output also piped out */
#define	PPOU		(1<<11)		/* piped output */
#define	PREPORTED	(1<<12)		/* status has been reported */
#define	PINTERRUPTED	(1<<13)		/* job stopped via interrupt signal */
#define	PPTIME		(1<<14)		/* time individual process */
#define	PNEEDNOTE	(1<<15)		/* notify as soon as practical */
E 9
I 9
#define	PNOTIFY		(1<<5)	/* notify async when done */
#define	PTIME		(1<<6)	/* job times should be printed */
#define	PAWAITED	(1<<7)	/* top level is waiting for it */
#define	PFOREGND	(1<<8)	/* started in shells pgrp */
#define	PDUMPED		(1<<9)	/* process dumped core */
D 12
#define	PDIAG		(1<<10)	/* diagnostic output also piped out */
E 12
I 12
#define	PERR		(1<<10)	/* diagnostic output also piped out */
E 12
#define	PPOU		(1<<11)	/* piped output */
#define	PREPORTED	(1<<12)	/* status has been reported */
#define	PINTERRUPTED	(1<<13)	/* job stopped via interrupt signal */
#define	PPTIME		(1<<14)	/* time individual process */
#define	PNEEDNOTE	(1<<15)	/* notify as soon as practical */
E 9

D 10
#define	PNULL		(struct process *)0
E 10
#define	PMAXLEN		80

/* defines for arguments to pprint */
#define	NUMBER		01
#define	NAME		02
#define	REASON		04
#define	AMPERSAND	010
#define	FANCY		020
D 9
#define	SHELLDIR	040		/* print shell's dir if not the same */
#define	JOBDIR		0100		/* print job's dir if not the same */
E 9
I 9
#define	SHELLDIR	040	/* print shell's dir if not the same */
#define	JOBDIR		0100	/* print job's dir if not the same */
E 9
#define	AREASON		0200

D 9
struct	process	proclist;		/* list head of all processes */
bool	pnoprocesses;			/* pchild found nothing to wait for */
E 9
I 9
struct process proclist;	/* list head of all processes */
bool    pnoprocesses;		/* pchild found nothing to wait for */
E 9

D 9
struct	process *pholdjob;		/* one level stack of current jobs */
E 9
I 9
struct process *pholdjob;	/* one level stack of current jobs */
E 9

D 9
struct	process *pcurrjob;		/* current job */
struct	process	*pcurrent;		/* current job in table */
struct	process *pprevious;		/* previous job in table */
E 9
I 9
struct process *pcurrjob;	/* current job */
struct process *pcurrent;	/* current job in table */
struct process *pprevious;	/* previous job in table */
E 9

D 9
short	pmaxindex;			/* current maximum job index */
D 5

bool	timesdone;			/* shtimes buffer full ? */
E 5

int	psigint();
struct	process	*pgetcurr();
struct	process	*plookup();
struct	process *pfind();
E 9
I 9
D 11
short   pmaxindex;		/* current maximum job index */
E 11
I 11
int    pmaxindex;		/* current maximum job index */
E 11
E 9
E 1
