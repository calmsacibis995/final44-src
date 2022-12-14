h49852
s 00046/00039/02596
d D 8.3 95/04/28 17:08:07 christos 23 22
c Updated to the latest version from the NetBSD source
e
s 00003/00000/02632
d D 8.2 94/03/19 15:51:21 christos 22 21
c eat leading spaces from cmd
e
s 00002/00002/02630
d D 8.1 93/06/06 15:15:27 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/02629
d D 5.20 93/05/24 18:29:59 bostic 20 19
c merge in rev 5.15->5.16
e
s 00004/00003/02626
d D 5.19 93/05/24 18:26:57 bostic 19 18
c merge in rev 5.16->5.17
e
s 00059/00042/02570
d D 5.18 93/05/24 14:45:37 bostic 18 17
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00001/00001/02611
d D 5.17 91/10/26 23:38:49 torek 17 16
c signal.h is not sys/signal.h
e
s 00004/00002/02608
d D 5.16 91/07/21 16:32:31 bostic 16 15
c don't unlink directories; from Christos Zoulas
e
s 00001/00001/02609
d D 5.15 91/03/01 15:07:22 bostic 15 14
c ANSI
e
s 00003/00003/02607
d D 5.14 91/01/10 17:16:53 bostic 14 13
c little better error messages
e
s 00001/00011/02609
d D 5.13 90/06/01 17:08:16 bostic 13 12
c new copyright notice
e
s 00005/00008/02615
d D 5.12 90/05/28 12:53:34 bostic 12 11
c sys_errlist -> strerror(3)
e
s 00003/00003/02620
d D 5.11 90/03/19 16:23:56 bostic 11 10
c rename DONTCARE as OPTIONAL
e
s 00004/00006/02619
d D 5.10 90/03/19 09:56:08 bostic 10 9
c replace malloc with emalloc; Str_Concat -> str_concat;
c Str_BreakString -> brk_string, no longer need Str_FreeVec
e
s 00014/00015/02611
d D 5.9 90/03/17 14:27:16 bostic 9 8
c add pathnames.h, redefining some paths
e
s 00011/00008/02615
d D 5.8 90/03/12 12:19:45 bostic 8 7
c rework to always be "make".  Deleted -M, -B, -C, -v.  Partial deletion
c of .NULL.  Never remove leading components in file search.  # is always a
c comment.  Print usage line, not message.  Make vararg'd routines right.
e
s 00036/00093/02587
d D 5.7 90/03/12 10:42:10 bostic 7 6
c remove rmt.c module, most of remote support, including .EXPORT,
c .EXPORTSAME, .NOEXPORT, -X and -x
e
s 00002/00010/02678
d D 5.6 90/03/12 09:31:20 bostic 6 5
c remove sparc #ifdef's
e
s 00000/00037/02688
d D 5.5 90/03/12 09:30:10 bostic 5 4
c Remove NEED_FD_SET, FD_SETSIZE, NO_WAIT3, NO_VFORK, LIBTOC
e
s 00000/00008/02725
d D 5.4 90/03/12 09:07:17 bostic 4 3
c remove SYSV and is68k ifdef's
e
s 00003/00027/02730
d D 5.3 90/03/12 09:04:32 bostic 3 2
c remove Sprite ifdef's
e
s 00026/00015/02731
d D 5.2 90/03/11 15:38:43 bostic 2 1
c add Berkeley specific copyright notice
e
s 02746/00000/00000
d D 5.1 90/03/11 15:27:28 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * job.c --
 *	handle the creation etc. of our child processes.
 *
 * Copyright (c) 1988, 1989 by the Regents of the University of California
E 2
I 2
/*
D 21
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
E 2
 * Copyright (c) 1988, 1989 by Adam de Boor
E 21
I 21
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 * Copyright (c) 1989 by Berkeley Softworks
I 2
 * All rights reserved.
E 2
 *
D 2
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any non-commercial purpose
 * and without fee is hereby granted, provided that the above copyright
 * notice appears in all copies.  The University of California,
 * Berkeley Softworks and Adam de Boor make no representations about
 * the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
E 2
 *
I 2
D 13
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*-
 * job.c --
 *	handle the creation etc. of our child processes.
 *
E 2
 * Interface:
 *	Job_Make  	    	Start the creation of the given target.
 *
 *	Job_CatchChildren   	Check for and handle the termination of any
 *	    	  	    	children. This must be called reasonably
 *	    	  	    	frequently to keep the whole make going at
 *	    	  	    	a decent clip, since job table entries aren't
 *	    	  	    	removed until their process is caught this way.
 *	    	  	    	Its single argument is TRUE if the function
 *	    	  	    	should block waiting for a child to terminate.
 *
 *	Job_CatchOutput	    	Print any output our children have produced.
 *	    	  	    	Should also be called fairly frequently to
 *	    	  	    	keep the user informed of what's going on.
 *	    	  	    	If no output is waiting, it will block for
 *	    	  	    	a time given by the SEL_* constants, below,
 *	    	  	    	or until output is ready.
 *
 *	Job_Init  	    	Called to intialize this module. in addition,
 *	    	  	    	any commands attached to the .BEGIN target
 *	    	  	    	are executed before this function returns.
 *	    	  	    	Hence, the makefile must have been parsed
 *	    	  	    	before this function is called.
 *
 *	Job_Full  	    	Return TRUE if the job table is filled.
 *
 *	Job_Empty 	    	Return TRUE if the job table is completely
 *	    	  	    	empty.
 *
 *	Job_ParseShell	    	Given the line following a .SHELL target, parse
 *	    	  	    	the line as a shell specification. Returns
 *	    	  	    	FAILURE if the spec was incorrect.
 *
 *	Job_End	  	    	Perform any final processing which needs doing.
 *	    	  	    	This includes the execution of any commands
 *	    	  	    	which have been/were attached to the .END
 *	    	  	    	target. It should only be called when the
 *	    	  	    	job table is empty.
 *
 *	Job_AbortAll	    	Abort all currently running jobs. It doesn't
 *	    	  	    	handle output or do anything for the jobs,
 *	    	  	    	just kills them. It should only be called in
 *	    	  	    	an emergency, as it were.
 *
 *	Job_CheckCommands   	Verify that the commands for a target are
 *	    	  	    	ok. Provide them if necessary and possible.
 *
 *	Job_Touch 	    	Update a target without really updating it.
 *
 *	Job_Wait  	    	Wait for all currently-running jobs to finish.
 */
D 2
#ifndef lint
static char     *rcsid = "$Id: job.c,v 1.97 89/11/14 13:43:51 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

D 9
#include    <stdio.h>
#include    <string.h>
#include    <sys/types.h>
#include    <sys/signal.h>
#include    <sys/stat.h>
#include    <fcntl.h>
#include    <sys/file.h>
#include    <sys/time.h>
#include    <sys/wait.h>
#include    <ctype.h>
#include    <errno.h>
E 9
I 9
D 18
#include "make.h"
E 18
I 18
#include <sys/types.h>
I 23
#include <sys/signal.h>
E 23
D 19
#include <sys/signal.h>
E 19
E 18
D 17
#include <sys/signal.h>
E 17
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/wait.h>
I 17
D 18
#include <signal.h>
E 18
E 17
D 19
#include <fcntl.h>
E 19
I 19
D 23

E 19
#include <errno.h>
E 23
I 19
#include <fcntl.h>
D 23
#include <signal.h>
E 23
I 23
#include <errno.h>
E 23
E 19
#include <stdio.h>
I 12
#include <string.h>
I 18
D 19
#include <signal.h>
E 19
I 19
D 23

E 23
I 23
#include <signal.h>
E 23
E 19
#include "make.h"
#include "hash.h"
#include "dir.h"
E 18
E 12
#include "job.h"
#include "pathnames.h"

E 9
extern int  errno;
D 9
#include    "make.h"
#include    "job.h"
E 9

/*
D 5
 * Some systems define the fd_set we use, but not the macros to deal with it
 * (SunOS 3.5, e.g.)
 */
#ifndef FD_SET

# ifdef NEED_FD_SET
/*
 * Then there are the systems that don't even define fd_set...
 */
#  ifndef	FD_SETSIZE
#  define	FD_SETSIZE	256
#  endif
#  ifndef NBBY
#  define NBBY 8
#  endif

typedef long	fd_mask;
#define NFDBITS	(sizeof(fd_mask) * NBBY)	/* bits per mask */
#ifndef howmany
#define	howmany(x, y)	((unsigned int)(((x)+((y)-1)))/(unsigned int)(y))
#endif

typedef	struct fd_set {
	fd_mask	fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} fd_set;

# endif /* NEED_FD_SET */

#define	FD_SET(n, p)	((p)->fds_bits[(n)/NFDBITS] |= (1 << ((n) % NFDBITS)))
#define	FD_CLR(n, p)	((p)->fds_bits[(n)/NFDBITS] &= ~(1 << ((n) % NFDBITS)))
#define	FD_ISSET(n, p)	((p)->fds_bits[(n)/NFDBITS] & (1 << ((n) % NFDBITS)))
#define FD_ZERO(p)	bzero((char *)(p), sizeof(*(p)))

#endif /* FD_SET */


/*
E 5
 * error handling variables 
 */
D 18
int         	errors = 0;	    /* number of errors reported */
int  	    	aborting = 0;	    /* why is the make aborting? */
E 18
I 18
static int     	errors = 0;	    /* number of errors reported */
static int    	aborting = 0;	    /* why is the make aborting? */
E 18
#define ABORT_ERROR	1   	    /* Because of an error */
#define ABORT_INTERRUPT	2   	    /* Because it was interrupted */
#define ABORT_WAIT	3   	    /* Waiting for jobs to finish */


/*
 * post-make command processing. The node postCommands is really just the
 * .END target but we keep it around to avoid having to search for it
 * all the time.
 */
static GNode   	  *postCommands;    /* node containing commands to execute when
				     * everything else is done */
static int     	  numCommands; 	    /* The number of commands actually printed
				     * for a target. Should this number be
				     * 0, no shell will be executed. */


/*
 * Return values from JobStart.
 */
#define JOB_RUNNING	0   	/* Job is running */
#define JOB_ERROR 	1   	/* Error in starting the job */
#define JOB_FINISHED	2   	/* The job is already finished */
#define JOB_STOPPED	3   	/* The job is stopped */

/*
 * tfile is the name of a file into which all shell commands are put. It is
 * used over by removing it before the child shell is executed. The XXXXX in
 * the string are replaced by the pid of the make process in a 5-character
 * field with leading zeroes. 
 */
static char     tfile[] = TMPPAT;


/*
 * Descriptions for various shells.
 */
static Shell    shells[] = {
    /*
     * CSH description. The csh can do echo control by playing
     * with the setting of the 'echo' shell variable. Sadly,
     * however, it is unable to do error control nicely.
     */
{
    "csh",
    TRUE, "unset verbose", "set verbose", "unset verbose", 10,
    FALSE, "echo \"%s\"\n", "csh -c \"%s || exit 0\"",
    "v", "e",
},
    /*
     * SH description. Echo control is also possible and, under
     * sun UNIX anyway, one can even control error checking.
     */
{
    "sh",
    TRUE, "set -", "set -v", "set -", 5,
D 3
#if (defined(sun) && !defined(Sprite)) || defined(SYSV)
    TRUE, "set -e", "set +e",
#else
E 3
    FALSE, "echo \"%s\"\n", "sh -c '%s || exit 0'\n",
D 3
#endif
E 3
    "v", "e",
},
    /*
     * UNKNOWN.
     */
{
    (char *)0,
    FALSE, (char *)0, (char *)0, (char *)0, 0,
    FALSE, (char *)0, (char *)0,
    (char *)0, (char *)0,
}
};
D 18
Shell       	*commandShell = &shells[DEFSHELL]; /* this is the shell to
E 18
I 18
static Shell 	*commandShell = &shells[DEFSHELL];/* this is the shell to
E 18
						   * which we pass all
						   * commands in the Makefile.
						   * It is set by the
						   * Job_ParseShell function */
D 18
char        	*shellPath = (char *) NULL,	  /* full pathname of
E 18
I 18
static char   	*shellPath = (char *) NULL,	  /* full pathname of
E 18
						   * executable image */
               	*shellName;	      	      	  /* last component of shell */


static int  	maxJobs;    	/* The most children we can run at once */
static int  	maxLocal;    	/* The most local ones we can have */
D 18
int  	    	nJobs;	    	/* The number of children currently running */
int  	    	nLocal;    	/* The number of local children */
Lst  	    	jobs;		/* The structures that describe them */
Boolean	    	jobFull;    	/* Flag to tell when the job table is full. It
E 18
I 18
D 23
static int     	nJobs;	    	/* The number of children currently running */
static int  	nLocal;    	/* The number of local children */
static Lst     	jobs;		/* The structures that describe them */
static Boolean	jobFull;    	/* Flag to tell when the job table is full. It
E 23
I 23
int     	nJobs;	    	/* The number of children currently running */
int  		nLocal;    	/* The number of local children */
Lst     	jobs;		/* The structures that describe them */
Boolean		jobFull;    	/* Flag to tell when the job table is full. It
E 23
E 18
				 * is set TRUE when (1) the total number of
				 * running jobs equals the maximum allowed or
				 * (2) a job can only be run locally, but
				 * nLocal equals maxLocal */
#ifndef RMT_WILL_WATCH
static fd_set  	outputs;    	/* Set of descriptors of pipes connected to
				 * the output channels of children */
#endif

D 18
GNode 	    	*lastNode;	/* The node for which output was most recently
E 18
I 18
D 23
static GNode   	*lastNode;	/* The node for which output was most recently
E 23
I 23
GNode   	*lastNode;	/* The node for which output was most recently
E 23
E 18
				 * produced. */
D 18
char 	    	*targFmt;   	/* Format string to use to head output from a
E 18
I 18
D 23
static char    	*targFmt;   	/* Format string to use to head output from a
E 23
I 23
char    	*targFmt;   	/* Format string to use to head output from a
E 23
E 18
				 * job when it's not the most-recent job heard
				 * from */
#define TARG_FMT  "--- %s ---\n" /* Default format */

/*
 * When JobStart attempts to run a job remotely but can't, and isn't allowed
 * to run the job locally, or when Job_CatchChildren detects a job that has
 * been migrated home, the job is placed on the stoppedJobs queue to be run
 * when the next job finishes. 
 */
D 18
Lst  	    stoppedJobs;	/* Lst of Job structures describing
E 18
I 18
D 23
static Lst    stoppedJobs;	/* Lst of Job structures describing
E 23
I 23
Lst		stoppedJobs;	/* Lst of Job structures describing
E 23
E 18
				 * jobs that were stopped due to concurrency
				 * limits or migration home */


I 18
#if defined(USE_PGRP) && defined(SYSV)
#define KILL(pid,sig)	killpg (-(pid),(sig))
#else
E 18
D 4
#if defined(USE_PGRP) && defined(SYSV)
#define KILL(pid,sig)	killpg(-(pid),(sig))
#else
E 4
# if defined(USE_PGRP)
D 18
#define KILL(pid,sig)	killpg((pid),(sig))
E 18
I 18
#define KILL(pid,sig)	killpg ((pid),(sig))
E 18
# else
D 18
#define KILL(pid,sig)	kill((pid),(sig))
E 18
I 18
#define KILL(pid,sig)	kill ((pid),(sig))
E 18
# endif
I 18
#endif
E 18
D 4
#endif
E 4

D 18
static void JobRestart();
static int  JobStart();
static void JobInterrupt();
E 18
I 18
D 23
static int JobCondPassSig __P((Job *, int));
E 23
I 23
static int JobCondPassSig __P((ClientData, ClientData));
E 23
static void JobPassSig __P((int));
D 23
static int JobCmpPid __P((Job *, int));
static int JobPrintCommand __P((char *, Job *));
static int JobSaveCommand __P((char *, GNode *));
E 23
I 23
static int JobCmpPid __P((ClientData, ClientData));
static int JobPrintCommand __P((ClientData, ClientData));
static int JobSaveCommand __P((ClientData, ClientData));
E 23
static void JobFinish __P((Job *, union wait));
static void JobExec __P((Job *, char **));
static void JobMakeArgv __P((Job *, char **));
static void JobRestart __P((Job *));
static int JobStart __P((GNode *, int, Job *));
static void JobDoOutput __P((Job *, Boolean));
static Shell *JobMatchShell __P((char *));
static void JobInterrupt __P((int));
E 18
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobCondPassSig --
 *	Pass a signal to a job if the job is remote or if USE_PGRP
 *	is defined.
 *
 * Results:
 *	=== 0
 *
 * Side Effects:
 *	None, except the job may bite it.
 *
 *-----------------------------------------------------------------------
 */
static int
D 23
JobCondPassSig(job, signo)
    Job	    	*job;	    /* Job to biff */
    int	    	signo;	    /* Signal to send it */
E 23
I 23
JobCondPassSig(jobp, signop)
    ClientData	    	jobp;	    /* Job to biff */
    ClientData	    	signop;	    /* Signal to send it */
E 23
{
I 23
    Job	*job = (Job *) jobp;
    int	signo = *(int *) signop;
E 23
#ifdef RMT_WANTS_SIGNALS
    if (job->flags & JOB_REMOTE) {
	(void)Rmt_Signal(job, signo);
    } else {
	KILL(job->pid, signo);
    }
#else
    /*
     * Assume that sending the signal to job->pid will signal any remote
     * job as well.
     */
    KILL(job->pid, signo);
#endif
    return(0);
}

/*-
 *-----------------------------------------------------------------------
 * JobPassSig --
 *	Pass a signal on to all remote jobs and to all local jobs if
 *	USE_PGRP is defined, then die ourselves.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	We die by the same signal.
 *	
 *-----------------------------------------------------------------------
 */
static void
JobPassSig(signo)
    int	    signo;	/* The signal number we've received */
{
    int	    mask;
    
D 23
    Lst_ForEach(jobs, JobCondPassSig, (ClientData)signo);
E 23
I 23
    Lst_ForEach(jobs, JobCondPassSig, (ClientData)(long)signo);
E 23

    /*
     * Deal with proper cleanup based on the signal received. We only run
     * the .INTERRUPT target if the signal was in fact an interrupt. The other
     * three termination signals are more of a "get out *now*" command.
     */
    if (signo == SIGINT) {
	JobInterrupt(TRUE);
    } else if ((signo == SIGHUP) || (signo == SIGTERM) || (signo == SIGQUIT)) {
	JobInterrupt(FALSE);
    }
    
    /*
     * Leave gracefully if SIGQUIT, rather than core dumping.
     */
    if (signo == SIGQUIT) {
D 18
	Finish();
E 18
I 18
	Finish(0);
E 18
    }
    
    /*
     * Send ourselves the signal now we've given the message to everyone else.
     * Note we block everything else possible while we're getting the signal.
     * This ensures that all our jobs get continued when we wake up before
     * we take any other signal.
     */
    mask = sigblock(0);
    (void) sigsetmask(~0 & ~(1 << (signo-1)));
    signal(signo, SIG_DFL);

    kill(getpid(), signo);

D 23
    Lst_ForEach(jobs, JobCondPassSig, (ClientData)SIGCONT);
E 23
I 23
    signo = SIGCONT;
    Lst_ForEach(jobs, JobCondPassSig, (ClientData) &signo);
E 23

    sigsetmask(mask);
    signal(signo, JobPassSig);

}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobCmpPid  --
 *	Compare the pid of the job with the given pid and return 0 if they
 *	are equal. This function is called from Job_CatchChildren via
 *	Lst_Find to find the job descriptor of the finished job.
 *
 * Results:
 *	0 if the pid's match
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static int
JobCmpPid (job, pid)
D 23
    int             pid;	/* process id desired */
    Job            *job;	/* job to examine */
E 23
I 23
    ClientData        job;	/* job to examine */
    ClientData        pid;	/* process id desired */
E 23
{
D 23
    return (pid - job->pid);
E 23
I 23
    return ( *(int *) pid - ((Job *) job)->pid);
E 23
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobPrintCommand  --
 *	Put out another command for the given job. If the command starts
 *	with an @ or a - we process it specially. In the former case,
 *	so long as the -s and -n flags weren't given to make, we stick
 *	a shell-specific echoOff command in the script. In the latter,
 *	we ignore errors for the entire job, unless the shell has error
 *	control.
 *	If the command is just "..." we take all future commands for this
 *	job to be commands to be executed once the entire graph has been
 *	made and return non-zero to signal that the end of the commands
 *	was reached. These commands are later attached to the postCommands
 *	node and executed by Job_End when all things are done.
 *	This function is called from JobStart via Lst_ForEach.
 *
 * Results:
 *	Always 0, unless the command was "..."
 *
 * Side Effects:
 *	If the command begins with a '-' and the shell has no error control,
 *	the JOB_IGNERR flag is set in the job descriptor.
 *	If the command is "..." and we're not ignoring such things,
 *	tailCmds is set to the successor node of the cmd.
 *	numCommands is incremented if the command is actually printed.
 *-----------------------------------------------------------------------
 */
static int
D 23
JobPrintCommand (cmd, job)
    char     	  *cmd;	    	    /* command string to print */
    Job           *job;	    	    /* job for which to print it */
E 23
I 23
JobPrintCommand (cmdp, jobp)
    ClientData    cmdp;	    	    /* command string to print */
    ClientData    jobp;	    	    /* job for which to print it */
E 23
{
    Boolean	  noSpecials;	    /* true if we shouldn't worry about
				     * inserting special commands into
				     * the input stream. */
    Boolean       shutUp = FALSE;   /* true if we put a no echo command
				     * into the command file */
    Boolean	  errOff = FALSE;   /* true if we turned error checking
				     * off before printing the command
				     * and need to turn it back on */
    char       	  *cmdTemplate;	    /* Template to use when printing the
				     * command */
    char    	  *cmdStart;	    /* Start of expanded command */
    LstNode 	  cmdNode;  	    /* Node for replacing the command */
I 23
    char     	  *cmd = (char *) cmdp;
    Job           *job = (Job *) jobp;	
E 23

    noSpecials = (noExecute && ! (job->node->type & OP_MAKE));

    if (strcmp (cmd, "...") == 0) {
I 18
	job->node->type |= OP_SAVE_CMDS; 
E 18
	if ((job->flags & JOB_IGNDOTS) == 0) {
	    job->tailCmds = Lst_Succ (Lst_Member (job->node->commands,
						  (ClientData)cmd));
	    return (1);
	}
	return (0);
    }

#define DBPRINTF(fmt, arg) if (DEBUG(JOB)) printf (fmt, arg); fprintf (job->cmdFILE, fmt, arg)

    numCommands += 1;

    /*
     * For debugging, we replace each command with the result of expanding
     * the variables in the command.
     */
    cmdNode = Lst_Member (job->node->commands, (ClientData)cmd);
D 18
    cmdStart = cmd = Var_Subst (cmd, job->node, FALSE);
E 18
I 18
    cmdStart = cmd = Var_Subst (NULL, cmd, job->node, FALSE);
E 18
    Lst_Replace (cmdNode, (ClientData)cmdStart);

    cmdTemplate = "%s\n";

    /*
     * Check for leading @' and -'s to control echoing and error checking.
     */
    while (*cmd == '@' || *cmd == '-') {
	if (*cmd == '@') {
	    shutUp = TRUE;
	} else {
	    errOff = TRUE;
	}
	cmd++;
    }

I 22
    while (isspace((unsigned char) *cmd))
	cmd++;

E 22
    if (shutUp) {
	if (! (job->flags & JOB_SILENT) && !noSpecials &&
	    commandShell->hasEchoCtl) {
		DBPRINTF ("%s\n", commandShell->echoOff);
	} else {
	    shutUp = FALSE;
	}
    }

    if (errOff) {
	if ( ! (job->flags & JOB_IGNERR) && !noSpecials) {
	    if (commandShell->hasErrCtl) {
		/*
		 * we don't want the error-control commands showing
		 * up either, so we turn off echoing while executing
		 * them. We could put another field in the shell
		 * structure to tell JobDoOutput to look for this
		 * string too, but why make it any more complex than
		 * it already is?
		 */
		if (! (job->flags & JOB_SILENT) && !shutUp &&
		    commandShell->hasEchoCtl) {
			DBPRINTF ("%s\n", commandShell->echoOff);
			DBPRINTF ("%s\n", commandShell->ignErr);
			DBPRINTF ("%s\n", commandShell->echoOn);
		} else {
		    DBPRINTF ("%s\n", commandShell->ignErr);
		}
	    } else if (commandShell->ignErr &&
		       (*commandShell->ignErr != '\0'))
	    {
		/*
		 * The shell has no error control, so we need to be
		 * weird to get it to ignore any errors from the command.
		 * If echoing is turned on, we turn it off and use the
		 * errCheck template to echo the command. Leave echoing
		 * off so the user doesn't see the weirdness we go through
		 * to ignore errors. Set cmdTemplate to use the weirdness
		 * instead of the simple "%s\n" template.
		 */
		if (! (job->flags & JOB_SILENT) && !shutUp &&
		    commandShell->hasEchoCtl) {
			DBPRINTF ("%s\n", commandShell->echoOff);
			DBPRINTF (commandShell->errCheck, cmd);
			shutUp = TRUE;
		}
		cmdTemplate = commandShell->ignErr;
		/*
		 * The error ignoration (hee hee) is already taken care
		 * of by the ignErr template, so pretend error checking
		 * is still on.
		 */
		errOff = FALSE;
	    } else {
		errOff = FALSE;
	    }
	} else {
	    errOff = FALSE;
	}
    }
    
    DBPRINTF (cmdTemplate, cmd);
    
    if (errOff) {
	/*
	 * If echoing is already off, there's no point in issuing the
	 * echoOff command. Otherwise we issue it and pretend it was on
	 * for the whole command...
	 */
	if (!shutUp && !(job->flags & JOB_SILENT) && commandShell->hasEchoCtl){
	    DBPRINTF ("%s\n", commandShell->echoOff);
	    shutUp = TRUE;
	}
	DBPRINTF ("%s\n", commandShell->errCheck);
    }
    if (shutUp) {
	DBPRINTF ("%s\n", commandShell->echoOn);
    }
    return (0);
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobSaveCommand --
 *	Save a command to be executed when everything else is done.
 *	Callback function for JobFinish...
 *
 * Results:
 *	Always returns 0
 *
 * Side Effects:
 *	The command is tacked onto the end of postCommands's commands list.
 *
 *-----------------------------------------------------------------------
 */
static int
JobSaveCommand (cmd, gn)
D 23
    char    *cmd;
    GNode   *gn;
E 23
I 23
    ClientData   cmd;
    ClientData   gn;
E 23
{
D 18
    cmd = Var_Subst (cmd, gn, FALSE);
E 18
I 18
D 23
    cmd = Var_Subst (NULL, cmd, gn, FALSE);
E 18
    (void)Lst_AtEnd (postCommands->commands, (ClientData)cmd);
E 23
I 23
    cmd = (ClientData) Var_Subst (NULL, (char *) cmd, (GNode *) gn, FALSE);
    (void)Lst_AtEnd (postCommands->commands, cmd);
E 23
    return (0);
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobFinish  --
 *	Do final processing for the given job including updating
 *	parents and starting new jobs as available/necessary. Note
 *	that we pay no attention to the JOB_IGNERR flag here.
 *	This is because when we're called because of a noexecute flag
 *	or something, jstat.w_status is 0 and when called from
 *	Job_CatchChildren, the status is zeroed if it s/b ignored.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Some nodes may be put on the toBeMade queue.
 *	Final commands for the job are placed on postCommands.
 *
 *	If we got an error and are aborting (aborting == ABORT_ERROR) and
 *	the job list is now empty, we are done for the day.
 *	If we recognized an error (errors !=0), we set the aborting flag
 *	to ABORT_ERROR so no more jobs will be started.
 *-----------------------------------------------------------------------
 */
/*ARGSUSED*/
D 18
void
E 18
I 18
static void
E 18
JobFinish (job, status)
    Job           *job;	      	  /* job to finish */
    union wait	  status;     	  /* sub-why job went away */
{
    Boolean 	  done;

    if ((WIFEXITED(status) &&
D 8
	  (((status.w_retcode != 0) && !(job->flags & JOB_IGNERR)) ||
	   !backwards)) ||
E 8
I 8
	  (((status.w_retcode != 0) && !(job->flags & JOB_IGNERR)))) ||
E 8
	(WIFSIGNALED(status) && (status.w_termsig != SIGCONT)))
    {
	/*
	 * If it exited non-zero and either we're doing things our
	 * way or we're not ignoring errors, the job is finished.
D 3
	 * Similarly, if the shell died because of a signal (the
	 * conditional on SIGCONT is to handle the mapping of Sprite
	 * signal semantics whereby wait will return a signal
	 * termination with SIGCONT being the signal to indicate that the
	 * child has resumed), the job is also finished. In these
E 3
I 3
	 * Similarly, if the shell died because of a signal
	 * the job is also finished. In these
E 3
	 * cases, finish out the job's output before printing the exit
	 * status...
	 */
	if (usePipes) {
#ifdef RMT_WILL_WATCH
	    Rmt_Ignore(job->inPipe);
#else
	    FD_CLR(job->inPipe, &outputs);
#endif /* RMT_WILL_WATCH */
	    if (job->outPipe != job->inPipe) {
		(void)close (job->outPipe);
	    }
	    JobDoOutput (job, TRUE);
	    (void)close (job->inPipe);
	} else {
	    (void)close (job->outFd);
	    JobDoOutput (job, TRUE);
	}

	if (job->cmdFILE != NULL && job->cmdFILE != stdout) {
	    fclose(job->cmdFILE);
	}
	done = TRUE;
D 8
    } else if (backwards && WIFEXITED(status) && status.w_retcode != 0) {
E 8
I 8
    } else if (WIFEXITED(status) && status.w_retcode != 0) {
E 8
	/*
	 * Deal with ignored errors in -B mode. We need to print a message
	 * telling of the ignored error as well as setting status.w_status
	 * to 0 so the next command gets run. To do this, we set done to be
	 * TRUE if in -B mode and the job exited non-zero. Note we don't
	 * want to close down any of the streams until we know we're at the
	 * end.
	 */
	done = TRUE;
    } else {
	/*
	 * No need to close things down or anything.
	 */
	done = FALSE;
    }
    
    if (done ||
	WIFSTOPPED(status) ||
	(WIFSIGNALED(status) && (status.w_termsig == SIGCONT)) ||
	DEBUG(JOB))
    {
	FILE	  *out;
	
D 8
	if (backwards && !usePipes && (job->flags & JOB_IGNERR)) {
E 8
I 8
	if (!usePipes && (job->flags & JOB_IGNERR)) {
E 8
	    /*
	     * If output is going to a file and this job is ignoring
	     * errors, arrange to have the exit status sent to the
	     * output file as well.
	     */
	    out = fdopen (job->outFd, "w");
	} else {
	    out = stdout;
	}

	if (WIFEXITED(status)) {
	    if (status.w_retcode != 0) {
		if (usePipes && job->node != lastNode) {
		    fprintf (out, targFmt, job->node->name);
		    lastNode = job->node;
		}
		fprintf (out, "*** Error code %d%s\n", status.w_retcode,
			 (job->flags & JOB_IGNERR) ? " (ignored)" : "");

		if (job->flags & JOB_IGNERR) {
		    status.w_status = 0;
		}
	    } else if (DEBUG(JOB)) {
		if (usePipes && job->node != lastNode) {
		    fprintf (out, targFmt, job->node->name);
		    lastNode = job->node;
		}
		fprintf (out, "*** Completed successfully\n");
	    }
	} else if (WIFSTOPPED(status)) {
	    if (usePipes && job->node != lastNode) {
		fprintf (out, targFmt, job->node->name);
		lastNode = job->node;
	    }
	    if (! (job->flags & JOB_REMIGRATE)) {
		fprintf (out, "*** Stopped -- signal %d\n", status.w_stopsig);
	    }
	    job->flags |= JOB_RESUME;
	    (void)Lst_AtEnd(stoppedJobs, (ClientData)job);
	    fflush(out);
	    return;
	} else if (status.w_termsig == SIGCONT) {
	    /*
	     * If the beastie has continued, shift the Job from the stopped
	     * list to the running one (or re-stop it if concurrency is
	     * exceeded) and go and get another child.
	     */
	    if (job->flags & (JOB_RESUME|JOB_REMIGRATE|JOB_RESTART)) {
		if (usePipes && job->node != lastNode) {
		    fprintf (out, targFmt, job->node->name);
		    lastNode = job->node;
		}
		fprintf (out, "*** Continued\n");
	    }
	    if (! (job->flags & JOB_CONTINUING)) {
		JobRestart(job);
	    } else {
		Lst_AtEnd(jobs, (ClientData)job);
		nJobs += 1;
		if (! (job->flags & JOB_REMOTE)) {
		    nLocal += 1;
		}
		if (nJobs == maxJobs) {
		    jobFull = TRUE;
		    if (DEBUG(JOB)) {
			printf("Job queue is full.\n");
		    }
		}
	    }
	    fflush(out);
	    return;
	} else {
	    if (usePipes && job->node != lastNode) {
		fprintf (out, targFmt, job->node->name);
		lastNode = job->node;
	    }
	    fprintf (out, "*** Signal %d\n", status.w_termsig);
	}

	fflush (out);
    }

    /*
     * Now handle the -B-mode stuff. If the beast still isn't finished,
     * try and restart the job on the next command. If JobStart says it's
     * ok, it's ok. If there's an error, this puppy is done.
     */
D 8
    if (backwards && (status.w_status == 0) &&
E 8
I 8
    if ((status.w_status == 0) &&
E 8
	!Lst_IsAtEnd (job->node->commands))
    {
	switch (JobStart (job->node,
			  job->flags & JOB_IGNDOTS,
			  job))
	{
	    case JOB_RUNNING:
		done = FALSE;
		break;
	    case JOB_ERROR:
		done = TRUE;
		status.w_retcode = 1;
		break;
	    case JOB_FINISHED:
		/*
		 * If we got back a JOB_FINISHED code, JobStart has already
		 * called Make_Update and freed the job descriptor. We set
		 * done to false here to avoid fake cycles and double frees.
		 * JobStart needs to do the update so we can proceed up the
		 * graph when given the -n flag..
		 */
		done = FALSE;
		break;
	}
    } else {
	done = TRUE;
    }
		

    if (done &&
	(aborting != ABORT_ERROR) &&
	(aborting != ABORT_INTERRUPT) &&
	(status.w_status == 0))
    {
	/*
	 * As long as we aren't aborting and the job didn't return a non-zero
	 * status that we shouldn't ignore, we call Make_Update to update
	 * the parents. In addition, any saved commands for the node are placed
	 * on the .END target.
	 */
	if (job->tailCmds != NILLNODE) {
	    Lst_ForEachFrom (job->node->commands, job->tailCmds,
			     JobSaveCommand,
			     (ClientData)job->node);
	}
	job->node->made = MADE;
	Make_Update (job->node);
	free((Address)job);
    } else if (status.w_status) {
	errors += 1;
	free((Address)job);
    }

    while (!errors && !jobFull && !Lst_IsEmpty(stoppedJobs)) {
	JobRestart((Job *)Lst_DeQueue(stoppedJobs));
    }

    /*
     * Set aborting if any error.
     */
    if (errors && !keepgoing && (aborting != ABORT_INTERRUPT)) {
	/*
	 * If we found any errors in this batch of children and the -k flag
	 * wasn't given, we set the aborting flag so no more jobs get
	 * started.
	 */
	aborting = ABORT_ERROR;
    }
    
    if ((aborting == ABORT_ERROR) && Job_Empty()) {
	/*
	 * If we are aborting and the job table is now empty, we finish.
	 */
	(void) unlink (tfile);
	Finish (errors);
    }
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * Job_Touch --
 *	Touch the given target. Called by JobStart when the -t flag was
 *	given
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The data modification of the file is changed. In addition, if the
 *	file did not exist, it is created.
 *-----------------------------------------------------------------------
 */
void
Job_Touch (gn, silent)
    GNode         *gn;	      	/* the node of the file to touch */
    Boolean 	  silent;   	/* TRUE if should not print messages */
{
    int		  streamID;   	/* ID of stream opened to do the touch */
    struct timeval times[2];	/* Times for utimes() call */
D 18
    struct stat attr;        /* Attributes of the file */
E 18

D 11
    if (gn->type & (OP_JOIN|OP_USE|OP_EXEC|OP_DONTCARE)) {
E 11
I 11
    if (gn->type & (OP_JOIN|OP_USE|OP_EXEC|OP_OPTIONAL)) {
E 11
	/*
D 11
	 * .JOIN, .USE, .ZEROTIME and .DONTCARE targets are "virtual" targets
E 11
I 11
	 * .JOIN, .USE, .ZEROTIME and .OPTIONAL targets are "virtual" targets
E 11
	 * and, as such, shouldn't really be created.
	 */
	return;
    }
    
    if (!silent) {
	printf ("touch %s\n", gn->name);
    }

    if (noExecute) {
	return;
    }

    if (gn->type & OP_ARCHV) {
	Arch_Touch (gn);
    } else if (gn->type & OP_LIB) {
	Arch_TouchLib (gn);
    } else {
	char	*file = gn->path ? gn->path : gn->name;

	times[0].tv_sec = times[1].tv_sec = now;
	times[0].tv_usec = times[1].tv_usec = 0;
	if (utimes(file, times) < 0){
	    streamID = open (file, O_RDWR | O_CREAT, 0666);

	    if (streamID >= 0) {
		char	c;

		/*
		 * Read and write a byte to the file to change the
		 * modification time, then close the file.
		 */
		if (read(streamID, &c, 1) == 1) {
		    lseek(streamID, 0L, L_SET);
		    write(streamID, &c, 1);
		}
		
		(void)close (streamID);
D 12
	    } else {
		extern char *sys_errlist[];

		printf("*** couldn't touch %s: %s", file, sys_errlist[errno]);
	    }
E 12
I 12
	    } else
		printf("*** couldn't touch %s: %s", file, strerror(errno));
E 12
	}
    }
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * Job_CheckCommands --
 *	Make sure the given node has all the commands it needs. 
 *
 * Results:
 *	TRUE if the commands list is/was ok.
 *
 * Side Effects:
 *	The node will have commands from the .DEFAULT rule added to it
 *	if it needs them.
 *-----------------------------------------------------------------------
 */
Boolean
Job_CheckCommands (gn, abortProc)
    GNode          *gn;	    	    /* The target whose commands need
				     * verifying */
D 18
    void    	  (*abortProc)();   /* Function to abort with message */
E 18
I 18
D 23
    void    	  (*abortProc) __P((const char *, ...));   
E 23
I 23
    void    	  (*abortProc) __P((char *, ...));   
E 23
			/* Function to abort with message */
E 18
{
    if (OP_NOP(gn->type) && Lst_IsEmpty (gn->commands) &&
	(gn->type & OP_LIB) == 0) {
	/*
	 * No commands. Look for .DEFAULT rule from which we might infer
	 * commands 
	 */
	if ((DEFAULT != NILGNODE) && !Lst_IsEmpty(DEFAULT->commands)) {
I 23
	    char *p1;
E 23
	    /*
	     * Make only looks for a .DEFAULT if the node was never the
	     * target of an operator, so that's what we do too. If
	     * a .DEFAULT was given, we substitute its commands for gn's
	     * commands and set the IMPSRC variable to be the target's name
	     * The DEFAULT node acts like a transformation rule, in that
	     * gn also inherits any attributes or sources attached to
	     * .DEFAULT itself.
	     */
	    Make_HandleUse(DEFAULT, gn);
D 23
	    Var_Set (IMPSRC, Var_Value (TARGET, gn), gn);
E 23
I 23
	    Var_Set (IMPSRC, Var_Value (TARGET, gn, &p1), gn);
	    if (p1)
		free(p1);
E 23
	} else if (Dir_MTime (gn) == 0) {
	    /*
	     * The node wasn't the target of an operator we have no .DEFAULT
	     * rule to go on and the target doesn't already exist. There's
	     * nothing more we can do for this branch. If the -k flag wasn't
	     * given, we stop in our tracks, otherwise we just don't update
	     * this node's parents so they never get examined. 
	     */
D 11
	    if (gn->type & OP_DONTCARE) {
E 11
I 11
	    if (gn->type & OP_OPTIONAL) {
E 11
D 14
		printf ("Can't figure out how to make %s (ignored)\n",
E 14
I 14
		printf ("make: don't know how to make %s (ignored)\n",
E 14
			gn->name);
	    } else if (keepgoing) {
D 14
		printf ("Can't figure out how to make %s (continuing)\n",
E 14
I 14
		printf ("make: don't know how to make %s (continuing)\n",
E 14
			gn->name);
		return (FALSE);
	    } else {
D 14
		(*abortProc) ("Can't figure out how to make %s. Stop",
E 14
I 14
		(*abortProc) ("make: don't know how to make %s. Stop",
E 14
			     gn->name);
		return(FALSE);
	    }
	}
    }
    return (TRUE);
}
#ifdef RMT_WILL_WATCH
/*-
 *-----------------------------------------------------------------------
 * JobLocalInput --
 *	Handle a pipe becoming readable. Callback function for Rmt_Watch
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	JobDoOutput is called.
 *	
 *-----------------------------------------------------------------------
 */
/*ARGSUSED*/
static void
JobLocalInput(stream, job)
    int	    stream; 	/* Stream that's ready (ignored) */
    Job	    *job;   	/* Job to which the stream belongs */
{
    JobDoOutput(job, FALSE);
}
#endif /* RMT_WILL_WATCH */
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobExec --
 *	Execute the shell for the given job. Called from JobStart and
 *	JobRestart.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	A shell is executed, outputs is altered and the Job structure added
 *	to the job table.
 *
 *-----------------------------------------------------------------------
 */
static void
JobExec(job, argv)
    Job	    	  *job; 	/* Job to execute */
    char    	  **argv;
{
    int	    	  cpid;	    	/* ID of new child */
    
    if (DEBUG(JOB)) {
	int 	  i;
	
	printf("Running %s %sly\n", job->node->name,
	       job->flags&JOB_REMOTE?"remote":"local");
	printf("\tCommand: ");
	for (i = 0; argv[i] != (char *)NULL; i++) {
	    printf("%s ", argv[i]);
	}
	printf("\n");
    }
    
    /*
     * Some jobs produce no output and it's disconcerting to have
     * no feedback of their running (since they produce no output, the
     * banner with their name in it never appears). This is an attempt to
     * provide that feedback, even if nothing follows it.
     */
    if ((lastNode != job->node) && (job->flags & JOB_FIRST) &&
	!(job->flags & JOB_SILENT))
    {
	printf(targFmt, job->node->name);
	lastNode = job->node;
    }
    
#ifdef RMT_NO_EXEC
    if (job->flags & JOB_REMOTE) {
	goto jobExecFinish;
    }
#endif /* RMT_NO_EXEC */

    if ((cpid =  vfork()) == -1) {
	Punt ("Cannot fork");
    } else if (cpid == 0) {

	/*
	 * Must duplicate the input stream down to the child's input and
	 * reset it to the beginning (again). Since the stream was marked
	 * close-on-exec, we must clear that bit in the new input.
	 */
	(void) dup2(fileno(job->cmdFILE), 0);
	fcntl(0, F_SETFD, 0);
	lseek(0, 0, L_SET);
	
	if (usePipes) {
	    /*
	     * Set up the child's output to be routed through the pipe
	     * we've created for it.
	     */
	    (void) dup2 (job->outPipe, 1);
	} else {
	    /*
	     * We're capturing output in a file, so we duplicate the
	     * descriptor to the temporary file into the standard
	     * output.
	     */
	    (void) dup2 (job->outFd, 1);
	}
	/*
	 * The output channels are marked close on exec. This bit was
	 * duplicated by the dup2 (on some systems), so we have to clear
	 * it before routing the shell's error output to the same place as
	 * its standard output.
	 */
	fcntl(1, F_SETFD, 0);
	(void) dup2 (1, 2);

#ifdef USE_PGRP
	/*
	 * We want to switch the child into a different process family so
	 * we can kill it and all its descendants in one fell swoop,
	 * by killing its process family, but not commit suicide.
	 */
	
D 4
#if defined(SYSV)
	(void) setpgrp();
#else
E 4
	(void) setpgrp(0, getpid());
D 4
#endif
E 4
#endif USE_PGRP

D 7
	if (job->flags & JOB_REMOTE) {
	    Rmt_Exec (shellPath, argv, FALSE);
	} else {
	    (void) execv (shellPath, argv);
	}

E 7
I 7
	(void) execv (shellPath, argv);
E 7
	(void) write (2, "Could not execute shell\n",
		 sizeof ("Could not execute shell"));
	_exit (1);
    } else {
	job->pid = cpid;

	if (usePipes && (job->flags & JOB_FIRST) ) {
	    /*
	     * The first time a job is run for a node, we set the current
	     * position in the buffer to the beginning and mark another
	     * stream to watch in the outputs mask
	     */
	    job->curPos = 0;
	    
#ifdef RMT_WILL_WATCH
	    Rmt_Watch(job->inPipe, JobLocalInput, job);
#else
	    FD_SET(job->inPipe, &outputs);
#endif /* RMT_WILL_WATCH */
	}

	if (job->flags & JOB_REMOTE) {
D 7
	    job->rmtID = (char *)Rmt_LastID(job->pid);
E 7
I 7
D 18
	    job->rmtID = (char *)0;
E 18
I 18
	    job->rmtID = 0;
E 18
E 7
	} else {
	    nLocal += 1;
	    /*
	     * XXX: Used to not happen if CUSTOMS. Why?
	     */
	    if (job->cmdFILE != stdout) {
		fclose(job->cmdFILE);
		job->cmdFILE = NULL;
	    }
	}
    }

I 18
#ifdef RMT_NO_EXEC
E 18
jobExecFinish:    
I 18
#endif
E 18
    /*
     * Now the job is actually running, add it to the table.
     */
    nJobs += 1;
    (void)Lst_AtEnd (jobs, (ClientData)job);
    if (nJobs == maxJobs) {
	jobFull = TRUE;
    }
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobMakeArgv --
 *	Create the argv needed to execute the shell for a given job.
 *	
 *
 * Results:
 *
 * Side Effects:
 *
 *-----------------------------------------------------------------------
 */
static void
JobMakeArgv(job, argv)
    Job	    	  *job;
    char	  **argv;
{
    int	    	  argc;
    static char	  args[10]; 	/* For merged arguments */
    
    argv[0] = shellName;
    argc = 1;

    if ((commandShell->exit && (*commandShell->exit != '-')) ||
	(commandShell->echo && (*commandShell->echo != '-')))
    {
	/*
	 * At least one of the flags doesn't have a minus before it, so
	 * merge them together. Have to do this because the *(&(@*#*&#$#
	 * Bourne shell thinks its second argument is a file to source.
	 * Grrrr. Note the ten-character limitation on the combined arguments.
	 */
	(void)sprintf(args, "-%s%s",
		      ((job->flags & JOB_IGNERR) ? "" :
		       (commandShell->exit ? commandShell->exit : "")),
		      ((job->flags & JOB_SILENT) ? "" :
		       (commandShell->echo ? commandShell->echo : "")));

	if (args[1]) {
	    argv[argc] = args;
	    argc++;
	}
    } else {
	if (!(job->flags & JOB_IGNERR) && commandShell->exit) {
	    argv[argc] = commandShell->exit;
	    argc++;
	}
	if (!(job->flags & JOB_SILENT) && commandShell->echo) {
	    argv[argc] = commandShell->echo;
	    argc++;
	}
    }
    argv[argc] = (char *)NULL;
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobRestart --
D 7
 *	Restart a job that stopped for some reason. If the job stopped
 *	because it migrated home again, we tell the Rmt module to
 *	find a new home for it and make it runnable if Rmt_ReExport
 *	succeeded (if it didn't and the job may be run locally, we
 *	simply resume it). If the job didn't run and can now, we run it.
E 7
I 7
 *	Restart a job that stopped for some reason. 
E 7
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	jobFull will be set if the job couldn't be run.
 *
 *-----------------------------------------------------------------------
 */
static void
JobRestart(job)
    Job 	  *job;    	/* Job to restart */
{
    if (job->flags & JOB_REMIGRATE) {
	if (DEBUG(JOB)) {
	    printf("Remigrating %x\n", job->pid);
	}
D 7
	if (!Rmt_ReExport(job->pid)) {
	    if (DEBUG(JOB)) {
		printf("Couldn't migrate...");
	    }
	    if (nLocal != maxLocal) {
E 7
I 7
	if (nLocal != maxLocal) {
E 7
		/*
		 * Job cannot be remigrated, but there's room on the local
		 * machine, so resume the job and note that another
		 * local job has started.
		 */
		if (DEBUG(JOB)) {
		    printf("resuming on local machine\n");
	        }
		KILL(job->pid, SIGCONT);
		nLocal +=1;
		job->flags &= ~(JOB_REMIGRATE|JOB_RESUME);
D 7
	    } else {
E 7
I 7
	} else {
E 7
		/*
		 * Job cannot be restarted. Mark the table as full and
		 * place the job back on the list of stopped jobs.
		 */
		if (DEBUG(JOB)) {
		    printf("holding\n");
		}
		(void)Lst_AtFront(stoppedJobs, (ClientData)job);
		jobFull = TRUE;
		if (DEBUG(JOB)) {
		    printf("Job queue is full.\n");
		}
		return;
D 7
	    }
	} else {
	    /*
	     * Clear out the remigrate and resume flags. If MIGRATE was set,
	     * leave that around for JobFinish to see so it doesn't print out
	     * that the job was continued.
	     */
	    job->flags &= ~(JOB_REMIGRATE|JOB_RESUME);
E 7
	}
	
	(void)Lst_AtEnd(jobs, (ClientData)job);
	nJobs += 1;
	if (nJobs == maxJobs) {
	    jobFull = TRUE;
	    if (DEBUG(JOB)) {
		printf("Job queue is full.\n");
	    }
	}
    } else if (job->flags & JOB_RESTART) {
	/*
	 * Set up the control arguments to the shell. This is based on the
	 * flags set earlier for this job. If the JOB_IGNERR flag is clear,
	 * the 'exit' flag of the commandShell is used to cause it to exit
	 * upon receiving an error. If the JOB_SILENT flag is clear, the
	 * 'echo' flag of the commandShell is used to get it to start echoing
	 * as soon as it starts processing commands. 
	 */
	char	  *argv[4];
	
	JobMakeArgv(job, argv);
	
	if (DEBUG(JOB)) {
	    printf("Restarting %s...", job->node->name);
	}
D 7
	if ((job->node->type&OP_NOEXPORT) ||
#ifdef RMT_NO_EXEC
	    !Rmt_Export(shellPath, argv, job)
#else
	    !Rmt_Begin(shellPath, argv, job->node)
#endif
	    )
	{
D 6
	    if (
#ifdef sparc	    	    /* KLUDGE */
		(job->node->type & OP_M68020) ||
#endif
		((nLocal >= maxLocal) && ! (job->flags & JOB_SPECIAL)))
E 6
I 6
	    if (((nLocal >= maxLocal) && ! (job->flags & JOB_SPECIAL)))
E 6
	    {
E 7
I 7
	if (((nLocal >= maxLocal) && ! (job->flags & JOB_SPECIAL))) {
E 7
		/*
		 * Can't be exported and not allowed to run locally -- put it
		 * back on the hold queue and mark the table full
		 */
		if (DEBUG(JOB)) {
		    printf("holding\n");
		}
		(void)Lst_AtFront(stoppedJobs, (ClientData)job);
		jobFull = TRUE;
		if (DEBUG(JOB)) {
		    printf("Job queue is full.\n");
		}
		return;
D 7
	    } else {
E 7
I 7
	} else {
E 7
		/*
		 * Job may be run locally.
		 */
		if (DEBUG(JOB)) {
		    printf("running locally\n");
		}
		job->flags &= ~JOB_REMOTE;
D 7
	    }
	} else {
	    /*
	     * Can be exported. Hooray!
	     */
	    if (DEBUG(JOB)) {
		printf("exporting\n");
	    }
	    job->flags |= JOB_REMOTE;
E 7
	}
	JobExec(job, argv);
    } else {
	/*
	 * The job has stopped and needs to be restarted. Why it stopped,
	 * we don't know...
	 */
	if (DEBUG(JOB)) {
	    printf("Resuming %s...", job->node->name);
	}
	if (((job->flags & JOB_REMOTE) ||
	     (nLocal < maxLocal) ||
D 7
	     (((job->flags & JOB_SPECIAL) ||
	       (job->node->type & OP_NOEXPORT)) &&
E 7
I 7
	     (((job->flags & JOB_SPECIAL)) &&
E 7
	      (maxLocal == 0))) &&
	    (nJobs != maxJobs))
	{
	    /*
	     * If the job is remote, it's ok to resume it as long as the
	     * maximum concurrency won't be exceeded. If it's local and
	     * we haven't reached the local concurrency limit already (or the
	     * job must be run locally and maxLocal is 0), it's also ok to
	     * resume it.
	     */
	    Boolean error;
	    extern int errno;
D 12
	    extern char *sys_errlist[];
E 12
	    union wait status;
	    
#ifdef RMT_WANTS_SIGNALS
	    if (job->flags & JOB_REMOTE) {
		error = !Rmt_Signal(job, SIGCONT);
	    } else
#endif	/* RMT_WANTS_SIGNALS */
		error = (KILL(job->pid, SIGCONT) != 0);

	    if (!error) {
		/*
		 * Make sure the user knows we've continued the beast and
		 * actually put the thing in the job table.
		 */
		job->flags |= JOB_CONTINUING;
		status.w_termsig = SIGCONT;
		JobFinish(job, status);
		
		job->flags &= ~(JOB_RESUME|JOB_CONTINUING);
		if (DEBUG(JOB)) {
		    printf("done\n");
		}
	    } else {
D 12
		Error("couldn't resume %s: %s", job->node->name,
		      sys_errlist[errno]);
E 12
I 12
		Error("couldn't resume %s: %s",
		    job->node->name, strerror(errno));
E 12
		status.w_status = 0;
		status.w_retcode = 1;
		JobFinish(job, status);
	    }
	} else {
	    /*
	     * Job cannot be restarted. Mark the table as full and
	     * place the job back on the list of stopped jobs.
	     */
	    if (DEBUG(JOB)) {
		printf("table full\n");
	    }
	    (void)Lst_AtFront(stoppedJobs, (ClientData)job);
	    jobFull = TRUE;
	    if (DEBUG(JOB)) {
		printf("Job queue is full.\n");
	    }
	}
    }
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobStart  --
 *	Start a target-creation process going for the target described
 *	by the graph node gn. 
 *
 * Results:
 *	JOB_ERROR if there was an error in the commands, JOB_FINISHED
 *	if there isn't actually anything left to do for the job and
 *	JOB_RUNNING if the job has been started.
 *
 * Side Effects:
 *	A new Job node is created and added to the list of running
 *	jobs. PMake is forked and a child shell created.
 *-----------------------------------------------------------------------
 */
static int
JobStart (gn, flags, previous)
    GNode         *gn;	      /* target to create */
D 23
    short	  flags;      /* flags for the job to override normal ones.
E 23
I 23
    int	  	   flags;      /* flags for the job to override normal ones.
E 23
			       * e.g. JOB_SPECIAL or JOB_IGNDOTS */
    Job 	  *previous;  /* The previous Job structure for this node,
			       * if any. */
{
    register Job  *job;       /* new job descriptor */
    char	  *argv[4];   /* Argument vector to shell */
D 18
    char          args[5];    /* arguments to shell */
E 18
    static int    jobno = 0;  /* job number of catching output in a file */
    Boolean	  cmdsOK;     /* true if the nodes commands were all right */
    Boolean 	  local;      /* Set true if the job was run locally */
    Boolean 	  noExec;     /* Set true if we decide not to run the job */

    if (previous != (Job *)NULL) {
	previous->flags &= ~ (JOB_FIRST|JOB_IGNERR|JOB_SILENT|JOB_REMOTE);
	job = previous;
    } else {
D 10
	job = (Job *) malloc (sizeof (Job));
E 10
I 10
	job = (Job *) emalloc (sizeof (Job));
E 10
	if (job == (Job *)NULL) {
	    Punt("JobStart out of memory");
	}
	flags |= JOB_FIRST;
    }

    job->node = gn;
    job->tailCmds = NILLNODE;

    /*
     * Set the initial value of the flags for this job based on the global
     * ones and the node's attributes... Any flags supplied by the caller
     * are also added to the field.
     */
    job->flags = 0;
    if (Targ_Ignore (gn)) {
	job->flags |= JOB_IGNERR;
    }
    if (Targ_Silent (gn)) {
	job->flags |= JOB_SILENT;
    }
    job->flags |= flags;

    /*
     * Check the commands now so any attributes from .DEFAULT have a chance
     * to migrate to the node
     */
D 8
    if (!backwards || (job->flags & JOB_FIRST)) {
E 8
I 8
    if (job->flags & JOB_FIRST) {
E 8
	cmdsOK = Job_CheckCommands(gn, Error);
    } else {
	cmdsOK = TRUE;
    }
    
    /*
     * If the -n flag wasn't given, we open up OUR (not the child's)
     * temporary file to stuff commands in it. The thing is rd/wr so we don't
     * need to reopen it to feed it to the shell. If the -n flag *was* given,
     * we just set the file to be stdout. Cute, huh?
     */
    if ((gn->type & OP_MAKE) || (!noExecute && !touchFlag)) {
	/*
	 * We're serious here, but if the commands were bogus, we're
	 * also dead...
	 */
	if (!cmdsOK) {
	    DieHorribly();
	}
	
	job->cmdFILE = fopen (tfile, "w+");
	if (job->cmdFILE == (FILE *) NULL) {
	    Punt ("Could not open %s", tfile);
	}
	fcntl(fileno(job->cmdFILE), F_SETFD, 1);
	/*
	 * Send the commands to the command file, flush all its buffers then
	 * rewind and remove the thing.
	 */
	noExec = FALSE;

D 8
	if (backwards) {
E 8
I 8
	/*
	 * used to be backwards; replace when start doing multiple commands
	 * per shell.
	 */
D 18
	if (1) {
E 18
I 18
	if (compatMake) {
E 18
E 8
	    /*
	     * Be compatible: If this is the first time for this node,
	     * verify its commands are ok and open the commands list for
	     * sequential access by later invocations of JobStart.
	     * Once that is done, we take the next command off the list
	     * and print it to the command file. If the command was an
	     * ellipsis, note that there's nothing more to execute.
	     */
	    if ((job->flags&JOB_FIRST) && (Lst_Open(gn->commands) != SUCCESS)){
		cmdsOK = FALSE;
	    } else {
		LstNode	ln = Lst_Next (gn->commands);
		    
		if ((ln == NILLNODE) ||
		    JobPrintCommand ((char *)Lst_Datum (ln), job))
		{
		    noExec = TRUE;
		    Lst_Close (gn->commands);
		}
		if (noExec && !(job->flags & JOB_FIRST)) {
		    /*
		     * If we're not going to execute anything, the job
		     * is done and we need to close down the various
		     * file descriptors we've opened for output, then
		     * call JobDoOutput to catch the final characters or
		     * send the file to the screen... Note that the i/o streams
		     * are only open if this isn't the first job.
		     * Note also that this could not be done in
		     * Job_CatchChildren b/c it wasn't clear if there were
		     * more commands to execute or not...
		     */
		    if (usePipes) {
#ifdef RMT_WILL_WATCH
			Rmt_Ignore(job->inPipe);
#else
			FD_CLR(job->inPipe, &outputs);
#endif
			if (job->outPipe != job->inPipe) {
			    (void)close (job->outPipe);
			}
			JobDoOutput (job, TRUE);
			(void)close (job->inPipe);
		    } else {
			(void)close (job->outFd);
			JobDoOutput (job, TRUE);
		    }
		}
	    }
	} else {
	    /*
	     * We can do all the commands at once. hooray for sanity
	     */
	    numCommands = 0;
	    Lst_ForEach (gn->commands, JobPrintCommand, (ClientData)job);
	    
	    /*
	     * If we didn't print out any commands to the shell script,
	     * there's not much point in executing the shell, is there?
	     */
	    if (numCommands == 0) {
		noExec = TRUE;
	    }
	}
    } else if (noExecute) {
	/*
	 * Not executing anything -- just print all the commands to stdout
	 * in one fell swoop. This will still set up job->tailCmds correctly.
	 */
	if (lastNode != gn) {
	    printf (targFmt, gn->name);
	    lastNode = gn;
	}
	job->cmdFILE = stdout;
	/*
	 * Only print the commands if they're ok, but don't die if they're
	 * not -- just let the user know they're bad and keep going. It
	 * doesn't do any harm in this case and may do some good.
	 */
	if (cmdsOK) {
	    Lst_ForEach(gn->commands, JobPrintCommand, (ClientData)job);
	}
	/*
	 * Don't execute the shell, thank you.
	 */
	noExec = TRUE;
    } else {
	/*
	 * Just touch the target and note that no shell should be executed.
	 * Set cmdFILE to stdout to make life easier. Check the commands, too,
	 * but don't die if they're no good -- it does no harm to keep working
	 * up the graph.
	 */
	job->cmdFILE = stdout;
    	Job_Touch (gn, job->flags&JOB_SILENT);
	noExec = TRUE;
    }

    /*
     * If we're not supposed to execute a shell, don't. 
     */
    if (noExec) {
	/*
	 * Unlink and close the command file if we opened one
	 */
	if (job->cmdFILE != stdout) {
	    (void) unlink (tfile);
	    fclose(job->cmdFILE);
	} else {
	    fflush (stdout);
	}

	/*
	 * We only want to work our way up the graph if we aren't here because
	 * the commands for the job were no good.
	 */
	if (cmdsOK) {
	    if (aborting == 0) {
		if (job->tailCmds != NILLNODE) {
		    Lst_ForEachFrom(job->node->commands, job->tailCmds,
				    JobSaveCommand,
				    (ClientData)job->node);
		}
		Make_Update(job->node);
	    }
	    free((Address)job);
	    return(JOB_FINISHED);
	} else {
	    free((Address)job);
	    return(JOB_ERROR);
	}
    } else {
	fflush (job->cmdFILE);
	(void) unlink (tfile);
    }

    /*
     * Set up the control arguments to the shell. This is based on the flags
     * set earlier for this job.
     */
    JobMakeArgv(job, argv);

    /*
     * If we're using pipes to catch output, create the pipe by which we'll
     * get the shell's output. If we're using files, print out that we're
     * starting a job and then set up its temporary-file name. This is just
     * tfile with two extra digits tacked on -- jobno.
     */
D 8
    if (!backwards || (job->flags & JOB_FIRST)) {
E 8
I 8
    if (job->flags & JOB_FIRST) {
E 8
	if (usePipes) {
	    int fd[2];
	    (void) pipe(fd); 
	    job->inPipe = fd[0];
	    job->outPipe = fd[1];
	    (void)fcntl (job->inPipe, F_SETFD, 1);
	    (void)fcntl (job->outPipe, F_SETFD, 1);
	} else {
	    printf ("Remaking `%s'\n", gn->name);
	    fflush (stdout);
	    sprintf (job->outFile, "%s%02d", tfile, jobno);
	    jobno = (jobno + 1) % 100;
	    job->outFd = open(job->outFile,O_WRONLY|O_CREAT|O_APPEND,0600);
	    (void)fcntl (job->outFd, F_SETFD, 1);
	}
    }

D 7
    if (!(gn->type & OP_NOEXPORT)) {
#ifdef RMT_NO_EXEC
	local = !Rmt_Export(shellPath, argv, job);
#else
	local = !Rmt_Begin (shellPath, argv, gn);
#endif /* RMT_NO_EXEC */
	if (!local) {
	    job->flags |= JOB_REMOTE;
	}
    } else {
	local = TRUE;
    }
E 7
I 7
    local = TRUE;
E 7

D 6
    if (local && (
#ifdef sparc	/* KLUDGE */
	(gn->type & OP_M68020) ||
#endif
	((nLocal >= maxLocal) &&
E 6
I 6
    if (local && (((nLocal >= maxLocal) &&
E 6
	 !(job->flags & JOB_SPECIAL) &&
D 7
	 (!(gn->type & OP_NOEXPORT) || (maxLocal != 0)))))
E 7
I 7
	 (maxLocal != 0))))
E 7
    {
	/*
	 * The job can only be run locally, but we've hit the limit of
	 * local concurrency, so put the job on hold until some other job
	 * finishes. Note that the special jobs (.BEGIN, .INTERRUPT and .END)
	 * may be run locally even when the local limit has been reached
	 * (e.g. when maxLocal == 0), though they will be exported if at
D 7
	 * all possible. In addition, any target marked with .NOEXPORT will
	 * be run locally if maxLocal is 0.
E 7
I 7
	 * all possible. 
E 7
	 */
	jobFull = TRUE;
	
	if (DEBUG(JOB)) {
	    printf("Can only run job locally.\n");
	}
	job->flags |= JOB_RESTART;
	(void)Lst_AtEnd(stoppedJobs, (ClientData)job);
    } else {
	if ((nLocal >= maxLocal) && local) {
	    /*
	     * If we're running this job locally as a special case (see above),
	     * at least say the table is full.
	     */
	    jobFull = TRUE;
	    if (DEBUG(JOB)) {
		printf("Local job queue is full.\n");
	    }
	}
	JobExec(job, argv);
    }
    return(JOB_RUNNING);
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobDoOutput  --
 *	This function is called at different times depending on
 *	whether the user has specified that output is to be collected
 *	via pipes or temporary files. In the former case, we are called
 *	whenever there is something to read on the pipe. We collect more
 *	output from the given job and store it in the job's outBuf. If
 *	this makes up a line, we print it tagged by the job's identifier,
 *	as necessary.
 *	If output has been collected in a temporary file, we open the
 *	file and read it line by line, transfering it to our own
 *	output channel until the file is empty. At which point we
 *	remove the temporary file.
 *	In both cases, however, we keep our figurative eye out for the
 *	'noPrint' line for the shell from which the output came. If
 *	we recognize a line, we don't print it. If the command is not
 *	alone on the line (the character after it is not \0 or \n), we
 *	do print whatever follows it.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	curPos may be shifted as may the contents of outBuf.
 *-----------------------------------------------------------------------
 */
D 18
void
E 18
I 18
static void
E 18
JobDoOutput (job, finish)
    register Job   *job;	  /* the job whose output needs printing */
    Boolean	   finish;	  /* TRUE if this is the last time we'll be
				   * called for this job */
{
    Boolean       gotNL = FALSE;  /* true if got a newline */
    register int  nr;	      	  /* number of bytes read */
    register int  i;	      	  /* auxiliary index into outBuf */
    register int  max;	      	  /* limit for i (end of current data) */
    int		  nRead;      	  /* (Temporary) number of bytes read */

D 18
    char          c;		  /* character after noPrint string */
E 18
    FILE      	  *oFILE;	  /* Stream pointer to shell's output file */
    char          inLine[132];

    
    if (usePipes) {
	/*
	 * Read as many bytes as will fit in the buffer.
	 */
end_loop:
	
	nRead = read (job->inPipe, &job->outBuf[job->curPos],
			 JOB_BUFSIZE - job->curPos);
	if (nRead < 0) {
	    if (DEBUG(JOB)) {
		perror("JobDoOutput(piperead)");
	    }
	    nr = 0;
	} else {
	    nr = nRead;
	}

	/*
	 * If we hit the end-of-file (the job is dead), we must flush its
	 * remaining output, so pretend we read a newline if there's any
	 * output remaining in the buffer.
	 * Also clear the 'finish' flag so we stop looping.
	 */
	if ((nr == 0) && (job->curPos != 0)) {
	    job->outBuf[job->curPos] = '\n';
	    nr = 1;
	    finish = FALSE;
	} else if (nr == 0) {
	    finish = FALSE;
	}
	
	/*
	 * Look for the last newline in the bytes we just got. If there is
	 * one, break out of the loop with 'i' as its index and gotNL set
	 * TRUE. 
	 */
	max = job->curPos + nr;
	for (i = job->curPos + nr - 1; i >= job->curPos; i--) {
	    if (job->outBuf[i] == '\n') {
		gotNL = TRUE;
		break;
	    } else if (job->outBuf[i] == '\0') {
		/*
		 * Why?
		 */
		job->outBuf[i] = ' ';
	    }
	}
	
	if (!gotNL) {
	    job->curPos += nr;
	    if (job->curPos == JOB_BUFSIZE) {
		/*
		 * If we've run out of buffer space, we have no choice
		 * but to print the stuff. sigh. 
		 */
		gotNL = TRUE;
		i = job->curPos;
	    }
	}
	if (gotNL) {
	    /*
	     * Need to send the output to the screen. Null terminate it
	     * first, overwriting the newline character if there was one.
	     * So long as the line isn't one we should filter (according
	     * to the shell description), we print the line, preceeded
	     * by a target banner if this target isn't the same as the
	     * one for which we last printed something.
	     * The rest of the data in the buffer are then shifted down
	     * to the start of the buffer and curPos is set accordingly. 
	     */
	    job->outBuf[i] = '\0';
	    if (i >= job->curPos) {
		register char	*cp, *ecp;

		cp = job->outBuf;
		if (commandShell->noPrint) {
		    ecp = Str_FindSubstring(job->outBuf,
					    commandShell->noPrint);
		    while (ecp != (char *)NULL) {
			if (cp != ecp) {
			    *ecp = '\0';
			    if (job->node != lastNode) {
				printf (targFmt, job->node->name);
				lastNode = job->node;
			    }
			    /*
			     * The only way there wouldn't be a newline after
			     * this line is if it were the last in the buffer.
			     * however, since the non-printable comes after it,
			     * there must be a newline, so we don't print one.
			     */
			    printf ("%s", cp);
			}
			cp = ecp + commandShell->noPLen;
			if (cp != &job->outBuf[i]) {
			    /*
			     * Still more to print, look again after skipping
			     * the whitespace following the non-printable
			     * command....
			     */
			    cp++;
			    while (*cp == ' ' || *cp == '\t' || *cp == '\n') {
				cp++;
			    }
			    ecp = Str_FindSubstring (cp,
						     commandShell->noPrint);
			} else {
			    break;
			}
		    }
		}

		/*
		 * There's still more in that thar buffer. This time, though,
		 * we know there's no newline at the end, so we add one of
		 * our own free will.
		 */
		if (*cp != '\0') {
		    if (job->node != lastNode) {
			printf (targFmt, job->node->name);
			lastNode = job->node;
		    }
		    printf ("%s\n", cp);
		}

		fflush (stdout);
	    }
	    if (i < max - 1) {
D 18
		bcopy (&job->outBuf[i + 1], /* shift the remaining */
		       job->outBuf,        /* characters down */
		       max - (i + 1));
E 18
I 18
		/* shift the remaining characters down */
		memcpy ( job->outBuf, &job->outBuf[i + 1], max - (i + 1));
E 18
		job->curPos = max - (i + 1);
		
	    } else {
		/*
		 * We have written everything out, so we just start over
		 * from the start of the buffer. No copying. No nothing.
		 */
		job->curPos = 0;
	    }
	}
	if (finish) {
	    /*
	     * If the finish flag is true, we must loop until we hit
	     * end-of-file on the pipe. This is guaranteed to happen eventually
	     * since the other end of the pipe is now closed (we closed it
	     * explicitly and the child has exited). When we do get an EOF,
	     * finish will be set FALSE and we'll fall through and out.
	     */
	    goto end_loop;
	}
    } else {
	/*
	 * We've been called to retrieve the output of the job from the
	 * temporary file where it's been squirreled away. This consists of
	 * opening the file, reading the output line by line, being sure not
	 * to print the noPrint line for the shell we used, then close and
	 * remove the temporary file. Very simple.
	 *
	 * Change to read in blocks and do FindSubString type things as for
	 * pipes? That would allow for "@echo -n..."
	 */
	oFILE = fopen (job->outFile, "r");
	if (oFILE != (FILE *) NULL) {
	    printf ("Results of making %s:\n", job->node->name);
	    while (fgets (inLine, sizeof(inLine), oFILE) != NULL) {
		register char	*cp, *ecp, *endp;

		cp = inLine;
		endp = inLine + strlen(inLine);
		if (endp[-1] == '\n') {
		    *--endp = '\0';
		}
		if (commandShell->noPrint) {
		    ecp = Str_FindSubstring(cp, commandShell->noPrint);
		    while (ecp != (char *)NULL) {
			if (cp != ecp) {
			    *ecp = '\0';
			    /*
			     * The only way there wouldn't be a newline after
			     * this line is if it were the last in the buffer.
			     * however, since the non-printable comes after it,
			     * there must be a newline, so we don't print one.
			     */
			    printf ("%s", cp);
			}
			cp = ecp + commandShell->noPLen;
			if (cp != endp) {
			    /*
			     * Still more to print, look again after skipping
			     * the whitespace following the non-printable
			     * command....
			     */
			    cp++;
			    while (*cp == ' ' || *cp == '\t' || *cp == '\n') {
				cp++;
			    }
			    ecp = Str_FindSubstring(cp, commandShell->noPrint);
			} else {
			    break;
			}
		    }
		}

		/*
		 * There's still more in that thar buffer. This time, though,
		 * we know there's no newline at the end, so we add one of
		 * our own free will.
		 */
		if (*cp != '\0') {
		    printf ("%s\n", cp);
		}
	    }
	    fclose (oFILE);
	    (void) unlink (job->outFile);
	}
    }
    fflush(stdout);
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * Job_CatchChildren --
 *	Handle the exit of a child. Called from Make_Make.
 *
 * Results:
 *	none.
 *
 * Side Effects:
 *	The job descriptor is removed from the list of children.
 *
 * Notes:
 *	We do waits, blocking or not, according to the wisdom of our
 *	caller, until there are no more children to report. For each
 *	job, call JobFinish to finish things off. This will take care of
 *	putting jobs on the stoppedJobs queue.
 *
 *-----------------------------------------------------------------------
 */
void
Job_CatchChildren (block)
    Boolean	  block;    	/* TRUE if should block on the wait. */
{
    int    	  pid;	    	/* pid of dead child */
    register Job  *job;	    	/* job descriptor for dead child */
    LstNode       jnode;    	/* list element for finding job */
    union wait	  status;   	/* Exit/termination status */

    /*
     * Don't even bother if we know there's no one around.
     */
    if (nLocal == 0) {
	return;
    }
    
D 15
    while ((pid = wait3(&status, (block?0:WNOHANG)|WUNTRACED,
E 15
I 15
    while ((pid = wait3((int *)&status, (block?0:WNOHANG)|WUNTRACED,
E 15
			(struct rusage *)0)) > 0)
    {
D 3
	if (DEBUG(JOB)) {
#ifdef Sprite
	    printf("Process %x exited or stopped.\n", pid);
#else
E 3
I 3
	if (DEBUG(JOB))
E 3
	    printf("Process %d exited or stopped.\n", pid);
D 3
#endif /* Sprite */
	}
E 3
	    

D 23
	jnode = Lst_Find (jobs, (ClientData)pid, JobCmpPid);
E 23
I 23
	jnode = Lst_Find (jobs, (ClientData)&pid, JobCmpPid);
E 23

	if (jnode == NILLNODE) {
	    if (WIFSIGNALED(status) && (status.w_termsig == SIGCONT)) {
D 23
		jnode = Lst_Find(stoppedJobs, (ClientData)pid, JobCmpPid);
E 23
I 23
		jnode = Lst_Find(stoppedJobs, (ClientData) &pid, JobCmpPid);
E 23
		if (jnode == NILLNODE) {
D 3
#ifdef Sprite
		    Error("Resumed child (%x) not in table", pid);
#else
E 3
		    Error("Resumed child (%d) not in table", pid);
D 3
#endif /* Sprite */
E 3
		    continue;
		}
		job = (Job *)Lst_Datum(jnode);
		(void)Lst_Remove(stoppedJobs, jnode);
	    } else {
D 3
#ifdef Sprite
		Error ("Child (%x) not in table?", pid);
#else
E 3
		Error ("Child (%d) not in table?", pid);
D 3
#endif /* Sprite */
E 3
		continue;
	    }
	} else {
	    job = (Job *) Lst_Datum (jnode);
	    (void)Lst_Remove (jobs, jnode);
	    nJobs -= 1;
	    if (jobFull && DEBUG(JOB)) {
		printf("Job queue is no longer full.\n");
	    }
	    jobFull = FALSE;
D 7
	
	    if (job->flags & JOB_REMOTE) {
		Rmt_Done (job->rmtID);
	    } else {
		nLocal -= 1;
	    }
E 7
I 7
	    nLocal -= 1;
E 7
	}

	JobFinish (job, status);
    }
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * Job_CatchOutput --
 *	Catch the output from our children, if we're using
 *	pipes do so. Otherwise just block time until we get a
 *	signal (most likely a SIGCHLD) since there's no point in
 *	just spinning when there's nothing to do and the reaping
 *	of a child can wait for a while. 
 *
 * Results:
 *	None 
 *
 * Side Effects:
 *	Output is read from pipes if we're piping.
 * -----------------------------------------------------------------------
 */
void
Job_CatchOutput ()
{
    int           	  nfds;
    struct timeval	  timeout;
    fd_set           	  readfds;
    register LstNode	  ln;
    register Job   	  *job;
I 18
#ifdef RMT_WILL_WATCH
E 18
    int	    	  	  pnJobs;   	/* Previous nJobs */
I 18
#endif
E 18

    fflush(stdout);
#ifdef RMT_WILL_WATCH
    pnJobs = nJobs;

    /*
     * It is possible for us to be called with nJobs equal to 0. This happens
     * if all the jobs finish and a job that is stopped cannot be run
     * locally (eg if maxLocal is 0) and cannot be exported. The job will
     * be placed back on the stoppedJobs queue, Job_Empty() will return false,
     * Make_Run will call us again when there's nothing for which to wait.
     * nJobs never changes, so we loop forever. Hence the check. It could
     * be argued that we should sleep for a bit so as not to swamp the
     * exportation system with requests. Perhaps we should.
     *
     * NOTE: IT IS THE RESPONSIBILITY OF Rmt_Wait TO CALL Job_CatchChildren
     * IN A TIMELY FASHION TO CATCH ANY LOCALLY RUNNING JOBS THAT EXIT.
     * It may use the variable nLocal to determine if it needs to call
     * Job_CatchChildren (if nLocal is 0, there's nothing for which to
     * wait...)
     */
    while (nJobs != 0 && pnJobs == nJobs) {
	Rmt_Wait();
    }
#else
    if (usePipes) {
	readfds = outputs;
	timeout.tv_sec = SEL_SEC;
	timeout.tv_usec = SEL_USEC;

D 18
	if ((nfds = select (FD_SETSIZE, &readfds, (int *) 0, (int *) 0, &timeout)) < 0)
E 18
I 18
	if ((nfds = select (FD_SETSIZE, &readfds, (fd_set *) 0, (fd_set *) 0, &timeout)) < 0)
E 18
	{
	    return;
	} else {
	    if (Lst_Open (jobs) == FAILURE) {
		Punt ("Cannot open job table");
	    }
	    while (nfds && (ln = Lst_Next (jobs)) != NILLNODE) {
		job = (Job *) Lst_Datum (ln);
		if (FD_ISSET(job->inPipe, &readfds)) {
		    JobDoOutput (job, FALSE);
		    nfds -= 1;
		}
	    }
	    Lst_Close (jobs);
	}
    }
#endif /* RMT_WILL_WATCH */
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * Job_Make --
 *	Start the creation of a target. Basically a front-end for
 *	JobStart used by the Make module.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Another job is started.
 *
 *-----------------------------------------------------------------------
 */
void
Job_Make (gn)
    GNode   *gn;
{
    (void)JobStart (gn, 0, (Job *)NULL);
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * Job_Init --
 *	Initialize the process module
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	lists and counters are initialized
 *-----------------------------------------------------------------------
 */
void
Job_Init (maxproc, maxlocal)
    int           maxproc;  /* the greatest number of jobs which may be
			     * running at one time */
    int	    	  maxlocal; /* the greatest number of local jobs which may
			     * be running at once. */
{
    GNode         *begin;     /* node for commands to do at the very start */

D 3
#ifdef Sprite
    sprintf (tfile, "/tmp/make%05x", getpid());
#else
E 3
    sprintf (tfile, "/tmp/make%05d", getpid());
D 3
#endif /* Sprite */
E 3

    jobs =  	  Lst_Init (FALSE);
    stoppedJobs = Lst_Init(FALSE);
    maxJobs = 	  maxproc;
    maxLocal = 	  maxlocal;
    nJobs = 	  0;
    nLocal = 	  0;
    jobFull = 	  FALSE;

    aborting = 	  0;
    errors = 	  0;

    lastNode =	  NILGNODE;

    if (maxJobs == 1) {
	/*
	 * If only one job can run at a time, there's no need for a banner,
	 * no is there?
	 */
	targFmt = "";
    } else {
	targFmt = TARG_FMT;
    }
    
    if (shellPath == (char *) NULL) {
	/*
	 * The user didn't specify a shell to use, so we are using the
	 * default one... Both the absolute path and the last component
	 * must be set. The last component is taken from the 'name' field
	 * of the default shell description pointed-to by commandShell.
D 9
	 * All default shells are located in DEFSHELLDIR.
E 9
I 9
	 * All default shells are located in _PATH_DEFSHELLDIR.
E 9
	 */
	shellName = commandShell->name;
D 9
	shellPath = Str_Concat (DEFSHELLDIR, shellName, STR_ADDSLASH);
E 9
I 9
D 10
	shellPath = Str_Concat (_PATH_DEFSHELLDIR, shellName, STR_ADDSLASH);
E 10
I 10
	shellPath = str_concat (_PATH_DEFSHELLDIR, shellName, STR_ADDSLASH);
E 10
E 9
    }

    if (commandShell->exit == (char *)NULL) {
	commandShell->exit = "";
    }
    if (commandShell->echo == (char *)NULL) {
	commandShell->echo = "";
    }

    /*
     * Catch the four signals that POSIX specifies if they aren't ignored.
     * JobPassSig will take care of calling JobInterrupt if appropriate.
     */
    if (signal (SIGINT, SIG_IGN) != SIG_IGN) {
	signal (SIGINT, JobPassSig);
    }
    if (signal (SIGHUP, SIG_IGN) != SIG_IGN) {
	signal (SIGHUP, JobPassSig);
    }
    if (signal (SIGQUIT, SIG_IGN) != SIG_IGN) {
	signal (SIGQUIT, JobPassSig);
    }
    if (signal (SIGTERM, SIG_IGN) != SIG_IGN) {
	signal (SIGTERM, JobPassSig);
    }
    /*
     * There are additional signals that need to be caught and passed if
     * either the export system wants to be told directly of signals or if
     * we're giving each job its own process group (since then it won't get
     * signals from the terminal driver as we own the terminal)
     */
#if defined(RMT_WANTS_SIGNALS) || defined(USE_PGRP)
    if (signal (SIGTSTP, SIG_IGN) != SIG_IGN) {
	signal (SIGTSTP, JobPassSig);
    }
    if (signal (SIGTTOU, SIG_IGN) != SIG_IGN) {
	signal (SIGTTOU, JobPassSig);
    }
    if (signal (SIGTTIN, SIG_IGN) != SIG_IGN) {
	signal (SIGTTIN, JobPassSig);
    }
    if (signal (SIGWINCH, SIG_IGN) != SIG_IGN) {
	signal (SIGWINCH, JobPassSig);
    }
#endif
    
    begin = Targ_FindNode (".BEGIN", TARG_NOCREATE);

    if (begin != NILGNODE) {
	JobStart (begin, JOB_SPECIAL, (Job *)0);
	while (nJobs) {
	    Job_CatchOutput();
#ifndef RMT_WILL_WATCH
	    Job_CatchChildren (!usePipes);
#endif /* RMT_WILL_WATCH */
	}
    }
    postCommands = Targ_FindNode (".END", TARG_CREATE);
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * Job_Full --
 *	See if the job table is full. It is considered full if it is OR
 *	if we are in the process of aborting OR if we have
 *	reached/exceeded our local quota. This prevents any more jobs
 *	from starting up.
 *
 * Results:
 *	TRUE if the job table is full, FALSE otherwise
 * Side Effects:
 *	None.
 *-----------------------------------------------------------------------
 */
Boolean
Job_Full ()
{
    return (aborting || jobFull);
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * Job_Empty --
 *	See if the job table is empty.  Because the local concurrency may
 *	be set to 0, it is possible for the job table to become empty,
 *	while the list of stoppedJobs remains non-empty. In such a case,
 *	we want to restart as many jobs as we can.
 *
 * Results:
 *	TRUE if it is. FALSE if it ain't.
 *
 * Side Effects:
 *	None.
 *
 * -----------------------------------------------------------------------
 */
Boolean
Job_Empty ()
{
    if (nJobs == 0) {
	if (!Lst_IsEmpty(stoppedJobs) && !aborting) {
	    /*
	     * The job table is obviously not full if it has no jobs in
	     * it...Try and restart the stopped jobs.
	     */
	    jobFull = FALSE;
	    while (!jobFull && !Lst_IsEmpty(stoppedJobs)) {
		JobRestart((Job *)Lst_DeQueue(stoppedJobs));
	    }
	    return(FALSE);
	} else {
	    return(TRUE);
	}
    } else {
	return(FALSE);
    }
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobMatchShell --
 *	Find a matching shell in 'shells' given its final component.
 *
 * Results:
 *	A pointer to the Shell structure.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Shell *
JobMatchShell (name)
    char	  *name;      /* Final component of shell path */
{
    register Shell *sh;	      /* Pointer into shells table */
    Shell	   *match;    /* Longest-matching shell */
    register char *cp1,
		  *cp2;
    char	  *eoname;

    eoname = name + strlen (name);

    match = (Shell *) NULL;

    for (sh = shells; sh->name != NULL; sh++) {
	for (cp1 = eoname - strlen (sh->name), cp2 = sh->name;
	     *cp1 != '\0' && *cp1 == *cp2;
	     cp1++, cp2++) {
		 continue;
	}
	if (*cp1 != *cp2) {
	    continue;
	} else if (match == (Shell *) NULL ||
		   strlen (match->name) < strlen (sh->name)) {
		       match = sh;
	}
    }
    return (match == (Shell *) NULL ? sh : match);
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * Job_ParseShell --
 *	Parse a shell specification and set up commandShell, shellPath
 *	and shellName appropriately.
 *
 * Results:
 *	FAILURE if the specification was incorrect.
 *
 * Side Effects:
 *	commandShell points to a Shell structure (either predefined or
 *	created from the shell spec), shellPath is the full path of the
 *	shell described by commandShell, while shellName is just the
 *	final component of shellPath.
 *
 * Notes:
 *	A shell specification consists of a .SHELL target, with dependency
 *	operator, followed by a series of blank-separated words. Double
 *	quotes can be used to use blanks in words. A backslash escapes
 *	anything (most notably a double-quote and a space) and
 *	provides the functionality it does in C. Each word consists of
 *	keyword and value separated by an equal sign. There should be no
 *	unnecessary spaces in the word. The keywords are as follows:
 *	    name  	    Name of shell.
 *	    path  	    Location of shell. Overrides "name" if given
 *	    quiet 	    Command to turn off echoing.
 *	    echo  	    Command to turn echoing on
 *	    filter	    Result of turning off echoing that shouldn't be
 *	    	  	    printed.
 *	    echoFlag	    Flag to turn echoing on at the start
 *	    errFlag	    Flag to turn error checking on at the start
 *	    hasErrCtl	    True if shell has error checking control
 *	    check 	    Command to turn on error checking if hasErrCtl
 *	    	  	    is TRUE or template of command to echo a command
 *	    	  	    for which error checking is off if hasErrCtl is
 *	    	  	    FALSE.
 *	    ignore	    Command to turn off error checking if hasErrCtl
 *	    	  	    is TRUE or template of command to execute a
 *	    	  	    command so as to ignore any errors it returns if
 *	    	  	    hasErrCtl is FALSE.
 *
 *-----------------------------------------------------------------------
 */
ReturnStatus
Job_ParseShell (line)
    char	  *line;  /* The shell spec */
{
    char    	  **words;
    int	    	  wordCount;
    register char **argv;
    register int  argc;
    char    	  *path;
    Shell   	  newShell;
    Boolean 	  fullSpec = FALSE;

    while (isspace (*line)) {
	line++;
    }
D 10
    words = Str_BreakString (line, " \t", "\n", &wordCount);
E 10
I 10
D 23
    words = brk_string (line, &wordCount);
E 23
I 23
    words = brk_string (line, &wordCount, TRUE);
E 23
E 10

D 18
    bzero ((Address)&newShell, sizeof(newShell));
E 18
I 18
    memset ((Address)&newShell, 0, sizeof(newShell));
E 18
    
    /*
     * Parse the specification by keyword
     */
    for (path = (char *)NULL, argc = wordCount - 1, argv = words + 1;
	 argc != 0;
	 argc--, argv++) {
	     if (strncmp (*argv, "path=", 5) == 0) {
		 path = &argv[0][5];
	     } else if (strncmp (*argv, "name=", 5) == 0) {
		 newShell.name = &argv[0][5];
	     } else {
		 if (strncmp (*argv, "quiet=", 6) == 0) {
		     newShell.echoOff = &argv[0][6];
		 } else if (strncmp (*argv, "echo=", 5) == 0) {
		     newShell.echoOn = &argv[0][5];
		 } else if (strncmp (*argv, "filter=", 7) == 0) {
		     newShell.noPrint = &argv[0][7];
		     newShell.noPLen = strlen(newShell.noPrint);
		 } else if (strncmp (*argv, "echoFlag=", 9) == 0) {
		     newShell.echo = &argv[0][9];
		 } else if (strncmp (*argv, "errFlag=", 8) == 0) {
		     newShell.exit = &argv[0][8];
		 } else if (strncmp (*argv, "hasErrCtl=", 10) == 0) {
		     char c = argv[0][10];
		     newShell.hasErrCtl = !((c != 'Y') && (c != 'y') &&
					    (c != 'T') && (c != 't'));
		 } else if (strncmp (*argv, "check=", 6) == 0) {
		     newShell.errCheck = &argv[0][6];
		 } else if (strncmp (*argv, "ignore=", 7) == 0) {
		     newShell.ignErr = &argv[0][7];
		 } else {
		     Parse_Error (PARSE_FATAL, "Unknown keyword \"%s\"",
				  *argv);
D 10
		     Str_FreeVec (wordCount, words);
E 10
		     return (FAILURE);
		 }
		 fullSpec = TRUE;
	     }
    }

    if (path == (char *)NULL) {
	/*
	 * If no path was given, the user wants one of the pre-defined shells,
	 * yes? So we find the one s/he wants with the help of JobMatchShell
	 * and set things up the right way. shellPath will be set up by
	 * Job_Init.
	 */
	if (newShell.name == (char *)NULL) {
	    Parse_Error (PARSE_FATAL, "Neither path nor name specified");
D 10
	    Str_FreeVec (wordCount, words);
E 10
	    return (FAILURE);
	} else {
	    commandShell = JobMatchShell (newShell.name);
	    shellName = newShell.name;
	}
    } else {
	/*
	 * The user provided a path. If s/he gave nothing else (fullSpec is
	 * FALSE), try and find a matching shell in the ones we know of.
	 * Else we just take the specification at its word and copy it
	 * to a new location. In either case, we need to record the
	 * path the user gave for the shell.
	 */
	shellPath = path;
D 18
	path = rindex (path, '/');
E 18
I 18
	path = strrchr (path, '/');
E 18
	if (path == (char *)NULL) {
	    path = shellPath;
	} else {
	    path += 1;
	}
	if (newShell.name != (char *)NULL) {
	    shellName = newShell.name;
	} else {
	    shellName = path;
	}
	if (!fullSpec) {
	    commandShell = JobMatchShell (shellName);
	} else {
D 10
	    commandShell = (Shell *) malloc(sizeof(Shell));
E 10
I 10
	    commandShell = (Shell *) emalloc(sizeof(Shell));
E 10
	    *commandShell = newShell;
	}
    }

    if (commandShell->echoOn && commandShell->echoOff) {
	commandShell->hasEchoCtl = TRUE;
    }
    
    if (!commandShell->hasErrCtl) {
	if (commandShell->errCheck == (char *)NULL) {
	    commandShell->errCheck = "";
	}
	if (commandShell->ignErr == (char *)NULL) {
	    commandShell->ignErr = "%s\n";
	}
    }
    
    /*
     * Do not free up the words themselves, since they might be in use by the
     * shell specification...
     */
    free (words);
    return SUCCESS;
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * JobInterrupt --
 *	Handle the receipt of an interrupt.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	All children are killed. Another job will be started if the
 *	.INTERRUPT target was given.
 *-----------------------------------------------------------------------
 */
static void
JobInterrupt (runINTERRUPT)
    int	    runINTERRUPT;   	/* Non-zero if commands for the .INTERRUPT
				 * target should be executed */
{
    LstNode 	  ln;		/* element in job table */
    Job           *job;	    	/* job descriptor in that element */
    GNode         *interrupt;	/* the node describing the .INTERRUPT target */
I 20
D 23
    struct stat sb;
E 23
E 20
D 16
    
E 16
I 16
D 18
    struct stat sb;

E 18
I 18
    
E 18
E 16
    aborting = ABORT_INTERRUPT;

    (void)Lst_Open (jobs);
    while ((ln = Lst_Next (jobs)) != NILLNODE) {
	job = (Job *) Lst_Datum (ln);

	if (!Targ_Precious (job->node)) {
	    char  	*file = (job->node->path == (char *)NULL ?
				 job->node->name :
				 job->node->path);
D 16
	    if (unlink (file) == 0) {
E 16
I 16
D 18
	    if (!stat(file, &sb) && S_ISREG(sb.st_mode) &&
		unlink(file) == 0) {
E 18
I 18
D 20
	    if (unlink (file) == 0) {
E 20
I 20
D 23
	    if (!stat(file, &sb) && S_ISREG(sb.st_mode) &&
		unlink (file) == 0) {
E 23
I 23
	    struct stat st;
	    if (!noExecute && lstat(file, &st) != -1 && !S_ISDIR(st.st_mode) && 
		unlink(file) != -1) {
E 23
E 20
E 18
E 16
		Error ("*** %s removed", file);
	    }
	}
#ifdef RMT_WANTS_SIGNALS
	if (job->flags & JOB_REMOTE) {
	    /*
	     * If job is remote, let the Rmt module do the killing.
	     */
	    if (!Rmt_Signal(job, SIGINT)) {
		/*
		 * If couldn't kill the thing, finish it out now with an
		 * error code, since no exit report will come in likely.
		 */
		union wait status;

		status.w_status = 0;
		status.w_retcode = 1;
		JobFinish(job, status);
	    }
	} else if (job->pid) {
	    KILL(job->pid, SIGINT);
	}
#else
	if (job->pid) {
	    KILL(job->pid, SIGINT);
	}
#endif /* RMT_WANTS_SIGNALS */
    }
    Lst_Close (jobs);

    if (runINTERRUPT && !touchFlag) {
	interrupt = Targ_FindNode (".INTERRUPT", TARG_NOCREATE);
	if (interrupt != NILGNODE) {
	    ignoreErrors = FALSE;

	    JobStart (interrupt, JOB_IGNDOTS, (Job *)0);
	    while (nJobs) {
		Job_CatchOutput();
#ifndef RMT_WILL_WATCH
		Job_CatchChildren (!usePipes);
#endif /* RMT_WILL_WATCH */
	    }
	}
    }
    (void) unlink (tfile);
    exit (0);
}
D 7

E 7
I 7

E 7
/*
 *-----------------------------------------------------------------------
 * Job_End --
 *	Do final processing such as the running of the commands
 *	attached to the .END target. 
 *
 * Results:
 *	Number of errors reported.
 *
 * Side Effects:
 *	The process' temporary file (tfile) is removed if it still
 *	existed.
 *-----------------------------------------------------------------------
 */
int
Job_End ()
{
    if (postCommands != NILGNODE && !Lst_IsEmpty (postCommands->commands)) {
	if (errors) {
	    Error ("Errors reported so .END ignored");
	} else {
	    JobStart (postCommands, JOB_SPECIAL | JOB_IGNDOTS,
		       (Job *)0);

	    while (nJobs) {
		Job_CatchOutput();
#ifndef RMT_WILL_WATCH
		Job_CatchChildren (!usePipes);
#endif /* RMT_WILL_WATCH */
	    }
	}
    }
    (void) unlink (tfile);
    return(errors);
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * Job_Wait --
 *	Waits for all running jobs to finish and returns. Sets 'aborting'
 *	to ABORT_WAIT to prevent other jobs from starting.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Currently running jobs finish.
 *
 *-----------------------------------------------------------------------
 */
void
Job_Wait()
{
    aborting = ABORT_WAIT;
    while (nJobs != 0) {
	Job_CatchOutput();
#ifndef RMT_WILL_WATCH
	Job_CatchChildren(!usePipes);
#endif /* RMT_WILL_WATCH */
    }
    aborting = 0;
}
D 7

E 7
I 7

E 7
/*-
 *-----------------------------------------------------------------------
 * Job_AbortAll --
 *	Abort all currently running jobs without handling output or anything.
 *	This function is to be called only in the event of a major
 *	error. Most definitely NOT to be called from JobInterrupt.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	All children are killed, not just the firstborn
 *-----------------------------------------------------------------------
 */
void
Job_AbortAll ()
{
    LstNode           	ln;		/* element in job table */
    Job            	*job;	/* the job descriptor in that element */
    int     	  	foo;
    
    aborting = ABORT_ERROR;
    
    if (nJobs) {

	(void)Lst_Open (jobs);
	while ((ln = Lst_Next (jobs)) != NILLNODE) {
	    job = (Job *) Lst_Datum (ln);

	    /*
	     * kill the child process with increasingly drastic signals to make
	     * darn sure it's dead. 
	     */
#ifdef RMT_WANTS_SIGNALS
	    if (job->flags & JOB_REMOTE) {
		Rmt_Signal(job, SIGINT);
		Rmt_Signal(job, SIGKILL);
	    } else {
		KILL(job->pid, SIGINT);
		KILL(job->pid, SIGKILL);
	    }
#else
	    KILL(job->pid, SIGINT);
	    KILL(job->pid, SIGKILL);
#endif /* RMT_WANTS_SIGNALS */
	}
    }
    
    /*
     * Catch as many children as want to report in at first, then give up
     */
D 18
    while (wait3(&foo, WNOHANG, (struct rusage *)0) > 0) {
	;
    }
E 18
I 18
    while (wait3(&foo, WNOHANG, (struct rusage *)0) > 0)
	continue;
E 18
    (void) unlink (tfile);
}
E 1
