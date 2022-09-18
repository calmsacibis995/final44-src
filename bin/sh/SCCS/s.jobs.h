h35960
s 00012/00016/00057
d D 8.2 95/05/04 17:59:51 christos 5 4
c 
e
s 00002/00002/00071
d D 8.1 93/05/31 15:19:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00071
d D 5.3 92/07/16 13:56:18 marc 3 2
c print (decompiled) body of function for hash -v (well, as well as can be done anyway...)
e
s 00001/00000/00070
d D 5.2 92/07/15 16:12:18 marc 2 1
c check for stopped jobs before exiting
e
s 00070/00000/00000
d D 5.1 91/03/07 20:27:35 bostic 1 0
c date and time created 91/03/07 20:27:35 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* Mode argument to forkshell.  Don't change FORK_FG or FORK_BG. */
#define FORK_FG 0
#define FORK_BG 1
#define FORK_NOJOB 2


/*
 * A job structure contains information about a job.  A job is either a
 * single process or a set of processes contained in a pipeline.  In the
 * latter case, pidlist will be non-NULL, and will point to a -1 terminated
 * array of pids.
 */

struct procstat {
	short pid;		/* process id */
	short status;		/* status flags (defined above) */
	char *cmd;		/* text of command being run */
};


/* states */
#define JOBSTOPPED 1		/* all procs are stopped */
#define JOBDONE 2		/* all procs are completed */


struct job {
	struct procstat ps0;	/* status of process */
	struct procstat *ps;	/* status or processes when more than one */
	short nprocs;		/* number of processes */
	short pgrp;		/* process group of this job */
	char state;		/* true if job is finished */
	char used;		/* true if this entry is in used */
	char changed;		/* true if status has changed */
#if JOBS
	char jobctl;		/* job running under job control */
#endif
};

extern short backgndpid;	/* pid of last background process */
I 2
extern int job_warning;		/* user was warned about stopped jobs */
E 2

D 5

#ifdef __STDC__
void setjobctl(int);
void showjobs(int);
struct job *makejob(union node *, int);
int forkshell(struct job *, union node *, int);
int waitforjob(struct job *);
I 3
char *commandtext(union node *);
E 3
#else
void setjobctl();
void showjobs();
struct job *makejob();
int forkshell();
int waitforjob();
I 3
char *commandtext();
E 3
#endif
E 5
I 5
void setjobctl __P((int));
int fgcmd __P((int, char **));
int bgcmd __P((int, char **));
int jobscmd __P((int, char **));
void showjobs __P((int));
int waitcmd __P((int, char **));
int jobidcmd __P((int, char **));
struct job *makejob __P((union node *, int));
int forkshell __P((struct job *, union node *, int));
int waitforjob __P((struct job *));
int stoppedjobs __P((void));
char *commandtext __P((union node *));
E 5

#if ! JOBS
#define setjobctl(on)	/* do nothing */
#endif
E 1
