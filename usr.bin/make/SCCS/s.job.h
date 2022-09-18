h49504
s 00014/00014/00193
d D 8.2 95/04/28 17:08:10 christos 6 5
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00205
d D 8.1 93/06/06 15:15:38 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00015/00191
d D 5.4 93/05/24 14:45:42 bostic 4 3
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00001/00011/00205
d D 5.3 90/06/01 17:08:28 bostic 3 2
c new copyright notice
e
s 00024/00014/00192
d D 5.2 90/03/11 15:38:57 bostic 2 1
c add Berkeley specific copyright notice
e
s 00206/00000/00000
d D 5.1 90/03/11 15:27:33 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * job.h --
 *	Definitions pertaining to the running of jobs in parallel mode.
 *	Exported from job.c for the use of remote-execution modules.
 *
 * Copyright (c) 1988, 1989 by the Regents of the University of California
E 2
I 2
/*
D 5
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
E 2
 * Copyright (c) 1988, 1989 by Adam de Boor
E 5
I 5
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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
D 2
 *	"$Id: job.h,v 1.1 89/11/14 13:44:21 adam Exp $ SPRITE (Berkeley)"
E 2
I 2
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

/*-
 * job.h --
 *	Definitions pertaining to the running of jobs in parallel mode.
 *	Exported from job.c for the use of remote-execution modules.
E 2
 */
#ifndef _JOB_H_
#define _JOB_H_

#define TMPPAT	"/tmp/makeXXXXX"

/*
 * The SEL_ constants determine the maximum amount of time spent in select
 * before coming out to see if a child has finished. SEL_SEC is the number of
 * seconds and SEL_USEC is the number of micro-seconds 
 */
#define SEL_SEC		0
#define SEL_USEC	500000


/*-
 * Job Table definitions. 
 *
 * Each job has several things associated with it:
 *	1) The process id of the child shell
 *	2) The graph node describing the target being made by this job
 *	3) A LstNode for the first command to be saved after the job
 *	   completes. This is NILLNODE if there was no "..." in the job's
 *	   commands.
 *	4) An FILE* for writing out the commands. This is only
 *	   used before the job is actually started.
 *	5) A union of things used for handling the shell's output. Different
 *	   parts of the union are used based on the value of the usePipes
 *	   flag. If it is true, the output is being caught via a pipe and
 *	   the descriptors of our pipe, an array in which output is line
 *	   buffered and the current position in that buffer are all
 *	   maintained for each job. If, on the other hand, usePipes is false,
 *	   the output is routed to a temporary file and all that is kept
 *	   is the name of the file and the descriptor open to the file.
 *	6) An identifier provided by and for the exclusive use of the
 *	   Rmt module.
 *	7) A word of flags which determine how the module handles errors,
 *	   echoing, etc. for the job 
 *
 * The job "table" is kept as a linked Lst in 'jobs', with the number of
 * active jobs maintained in the 'nJobs' variable. At no time will this
 * exceed the value of 'maxJobs', initialized by the Job_Init function. 
 *
 * When a job is finished, the Make_Update function is called on each of the
 * parents of the node which was just remade. This takes care of the upward
 * traversal of the dependency graph.
 */
#define JOB_BUFSIZE	1024
typedef struct Job {
    int       	pid;	    /* The child's process ID */
    GNode    	*node;      /* The target the child is making */
    LstNode 	tailCmds;   /* The node of the first command to be
			     * saved when the job has been run */
    FILE 	*cmdFILE;   /* When creating the shell script, this is
			     * where the commands go */
D 4
    char    	*rmtID;     /* ID returned from Rmt module */
E 4
I 4
    int    	rmtID;     /* ID returned from Rmt module */
E 4
    short      	flags;	    /* Flags to control treatment of job */
#define	JOB_IGNERR	0x001	/* Ignore non-zero exits */
#define	JOB_SILENT	0x002	/* no output */
#define JOB_SPECIAL	0x004	/* Target is a special one. i.e. run it locally
				 * if we can't export it and maxLocal is 0 */
#define JOB_IGNDOTS	0x008  	/* Ignore "..." lines when processing
				 * commands */
#define JOB_REMOTE	0x010	/* Job is running remotely */  
#define JOB_FIRST	0x020	/* Job is first job for the node */
#define JOB_REMIGRATE	0x040	/* Job needs to be remigrated */
#define JOB_RESTART	0x080	/* Job needs to be completely restarted */
#define JOB_RESUME	0x100	/* Job needs to be resumed b/c it stopped,
				 * for some reason */
#define JOB_CONTINUING	0x200	/* We are in the process of resuming this job.
				 * Used to avoid infinite recursion between
				 * JobFinish and JobRestart */
    union {
	struct {
	    int	  	op_inPipe;	/* Input side of pipe associated
					 * with job's output channel */
	    int   	op_outPipe;	/* Output side of pipe associated with
					 * job's output channel */
	    char  	op_outBuf[JOB_BUFSIZE + 1];
	    	  	    	    	/* Buffer for storing the output of the
					 * job, line by line */
	    int   	op_curPos;	/* Current position in op_outBuf */
	}   	    o_pipe;	    /* data used when catching the output via
				     * a pipe */
	struct {
	    char  	of_outFile[sizeof(TMPPAT)+2];
	    	  	    	    	/* Name of file to which shell output
					 * was rerouted */
	    int	    	of_outFd;	/* Stream open to the output
					 * file. Used to funnel all
					 * from a single job to one file
					 * while still allowing
					 * multiple shell invocations */
	}   	    o_file;	    /* Data used when catching the output in
				     * a temporary file */
    }       	output;	    /* Data for tracking a shell's output */
} Job;

#define outPipe	  	output.o_pipe.op_outPipe
#define inPipe	  	output.o_pipe.op_inPipe
#define outBuf		output.o_pipe.op_outBuf
#define curPos		output.o_pipe.op_curPos
#define outFile		output.o_file.of_outFile
#define outFd	  	output.o_file.of_outFd


/*-
 * Shell Specifications:
 * Each shell type has associated with it the following information:
 *	1) The string which must match the last character of the shell name
 *	   for the shell to be considered of this type. The longest match
 *	   wins.
 *	2) A command to issue to turn off echoing of command lines
 *	3) A command to issue to turn echoing back on again
 *	4) What the shell prints, and its length, when given the echo-off
 *	   command. This line will not be printed when received from the shell
 *	5) A boolean to tell if the shell has the ability to control
 *	   error checking for individual commands.
 *	6) The string to turn this checking on.
 *	7) The string to turn it off.
 *	8) The command-flag to give to cause the shell to start echoing
 *	   commands right away.
 *	9) The command-flag to cause the shell to Lib_Exit when an error is
 *	   detected in one of the commands.
 *
 * Some special stuff goes on if a shell doesn't have error control. In such
 * a case, errCheck becomes a printf template for echoing the command,
 * should echoing be on and ignErr becomes another printf template for
 * executing the command while ignoring the return status. If either of these
 * strings is empty when hasErrCtl is FALSE, the command will be executed
 * anyway as is and if it causes an error, so be it.
 */
typedef struct Shell {
    char	  *name;	/* the name of the shell. For Bourne and C
				 * shells, this is used only to find the
				 * shell description when used as the single
				 * source of a .SHELL target. For user-defined
				 * shells, this is the full path of the shell.
				 */
    Boolean 	  hasEchoCtl;	/* True if both echoOff and echoOn defined */
    char          *echoOff;	/* command to turn off echo */
    char          *echoOn;	/* command to turn it back on again */
    char          *noPrint;	/* command to skip when printing output from
				 * shell. This is usually the command which
				 * was executed to turn off echoing */
    int           noPLen;	/* length of noPrint command */
    Boolean	  hasErrCtl;	/* set if can control error checking for
				 * individual commands */
    char	  *errCheck;	/* string to turn error checking on */
    char	  *ignErr;	/* string to turn off error checking */
    /*
     * command-line flags 
     */
    char          *echo;	/* echo commands */
    char          *exit;	/* exit on error */
}               Shell;


extern char 	*targFmt;   	/* Format string for banner that separates
				 * output from multiple jobs. Contains a
				 * single %s where the name of the node being
				 * made should be put. */
extern GNode	*lastNode;  	/* Last node for which a banner was printed.
				 * If Rmt module finds it necessary to print
				 * a banner, it should set this to the node
				 * for which the banner was printed */
extern int  	nJobs;	    	/* Number of jobs running (local and remote) */
extern int  	nLocal;	    	/* Number of jobs running locally */
extern Lst  	jobs;	    	/* List of active job descriptors */
extern Lst  	stoppedJobs;	/* List of jobs that are stopped or didn't
				 * quite get started */
extern Boolean	jobFull;    	/* Non-zero if no more jobs should/will start*/

D 4
/*
 * These functions should be used only by an intelligent Rmt module, hence
 * their names do *not* include an underscore as they are not fully exported,
 * if you see what I mean.
 */
extern void 	JobDoOutput(/* job, final? */);	/* Funnel output from
			     	    	    	 * job->outPipe to the screen,
						 * filtering out echo-off
						 * strings etc. */
extern void 	JobFinish(/* job, status */);	/* Finish out a job. If
			    	    	    	 * status indicates job has
						 * just stopped, not finished,
						 * the descriptor is placed on
						 * the stoppedJobs list. */
E 4
I 4
D 6
void		JobFlagForMigration __P((int));
void		Job_AbortAll __P((void));
void		Job_CatchChildren __P((Boolean));
void		Job_CatchOutput __P((void));
Boolean		Job_CheckCommands __P((GNode *,
		    void (*abortProc )(const char *, ...)));
Boolean		Job_Empty __P((void));
int		Job_End __P((void));
Boolean		Job_Full __P((void));
void		Job_Init __P((int, int));
void		Job_Make __P((GNode *));
ReturnStatus	Job_ParseShell __P((char *));
void		Job_Touch __P((GNode *, Boolean));
void		Job_Wait __P((void));
E 6
I 6

void Job_Touch __P((GNode *, Boolean));
Boolean Job_CheckCommands __P((GNode *, void (*abortProc )(char *, ...)));
void Job_CatchChildren __P((Boolean));
void Job_CatchOutput __P((void));
void Job_Make __P((GNode *));
void Job_Init __P((int, int));
Boolean Job_Full __P((void));
Boolean Job_Empty __P((void));
ReturnStatus Job_ParseShell __P((char *));
int Job_End __P((void));
void Job_Wait __P((void));
void Job_AbortAll __P((void));
void JobFlagForMigration __P((int));
E 6

E 4
#endif /* _JOB_H_ */
E 1
