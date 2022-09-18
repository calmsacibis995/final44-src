h44149
s 00061/00018/00867
d D 8.4 95/04/28 17:08:13 christos 38 37
c Updated to the latest version from the NetBSD source
e
s 00078/00034/00807
d D 8.3 94/03/19 15:52:23 christos 37 36
c fix OBJDIR, add MACHINE_ARCH, fix varargs functions
e
s 00003/00001/00838
d D 8.2 94/01/02 14:59:04 bostic 36 35
c In case $MAKEOBJDIR is not a directory or we cannot stat it, then we
c restore the path to .
c From: christos@deshaw.com (Christos Zoulas)
e
s 00005/00005/00834
d D 8.1 93/06/06 15:15:58 bostic 35 34
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00837
d D 5.34 93/05/24 19:03:35 bostic 34 33
c merge in rev 5.28->5.29
e
s 00001/00001/00838
d D 5.33 93/05/24 19:02:50 bostic 33 32
c merge in rev 5.27->5.28
e
s 00002/00002/00837
d D 5.32 93/05/24 19:01:47 bostic 32 31
c merge in rev 5.26->5.27
e
s 00001/00001/00838
d D 5.31 93/05/24 19:00:17 bostic 31 30
c merge rev 5.25->5.26
e
s 00119/00046/00720
d D 5.30 93/05/24 14:45:45 bostic 30 29
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00001/00002/00765
d D 5.29 92/01/08 15:13:22 bostic 29 28
c getopt returns an int
e
s 00001/00001/00766
d D 5.28 91/10/17 14:55:37 bostic 28 27
c option flag precedence typo; bug report net2/usr.bin/0
e
s 00002/00001/00765
d D 5.27 91/07/27 15:01:11 karels 27 26
c don't try to cd to "obj" unless it's a directory, or a symlink to a directory
e
s 00001/00001/00765
d D 5.26 91/07/20 10:43:58 bostic 26 25
c don't go into an infinite loop on "make -"
e
s 00007/00002/00759
d D 5.25 91/04/01 15:58:40 bostic 25 24
c don't allow -d random, so "make -d file" fails.
e
s 00001/00003/00760
d D 5.24 91/02/02 18:26:35 torek 24 23
c get errno from <errno.h>
e
s 00001/00001/00762
d D 5.23 90/10/11 11:04:42 bostic 23 22
c use EOF, not -1
e
s 00001/00000/00762
d D 5.22 90/06/28 20:41:29 trent 22 21
c reset optind before getopt() -- fixes 'make -k clean' failure
e
s 00001/00011/00761
d D 5.21 90/06/01 17:08:52 bostic 21 20
c new copyright notice
e
s 00006/00002/00766
d D 5.20 90/05/21 13:11:25 bostic 20 19
c allow arguments both before and after variable assignments (*sigh*)
e
s 00002/00002/00766
d D 5.19 90/05/08 20:46:50 bostic 19 18
c remove -v
e
s 00016/00010/00752
d D 5.18 90/05/03 11:22:06 bostic 18 17
c minor cleanup, wire .depend directly into make program -- necessary
c so that the depend file gets read at the right time and doesn't set the .MAIN
c target.
e
s 00008/00004/00754
d D 5.17 90/03/21 21:01:37 bostic 17 16
c don't stick null arguments into the environment
e
s 00000/00003/00758
d D 5.16 90/03/21 10:52:49 bostic 16 15
c remove DEBUG_PARSE, never used
e
s 00004/00006/00757
d D 5.15 90/03/19 12:33:47 bostic 15 14
c rename .PMAKE variable as .MAKE, PMAKE environmental value to MAKE
e
s 00028/00031/00735
d D 5.14 90/03/19 11:24:51 bostic 14 13
c move -p to -dg1 and -dg2; delete -W (noWarnings) flag; move -J to -j;
c move -d* to -dA; comment out -L, -P, and -S, for later deletion
e
s 00090/00030/00676
d D 5.13 90/03/19 10:04:44 bostic 13 12
c Str_BreakString -> brk_string, delete Str_FreeVec; add emalloc, enomem
c add object directory, as specified by MAKEOBJDIR/_PATH_OBJDIR, and CURDIR variable
e
s 00002/00001/00704
d D 5.12 90/03/12 21:18:56 bostic 12 11
c add MACHINE global variable
e
s 00034/00020/00671
d D 5.11 90/03/12 17:35:18 bostic 11 10
c minor reformatting, make VARARGS stuff right
e
s 00047/00154/00644
d D 5.10 90/03/12 12:19:55 bostic 10 9
c rework to always be "make".  Deleted -M, -B, -C, -v.  Partial deletion
c of .NULL.  Never remove leading components in file search.  # is always a
c comment.  Print usage line, not message.  Make vararg'd routines right.
e
s 00510/00576/00288
d D 5.9 90/03/12 11:18:06 bostic 9 8
c going to change main, so reformat to KNF
e
s 00008/00054/00856
d D 5.8 90/03/12 10:42:29 bostic 8 7
c remove rmt.c module, most of remote support, including .EXPORT,
c .EXPORTSAME, .NOEXPORT, -X and -x
e
s 00000/00004/00910
d D 5.7 90/03/12 09:54:59 bostic 7 6
c wire in DEF_OLD_VARS, still needs more work (oldVars variable)
e
s 00000/00009/00914
d D 5.6 90/03/12 09:07:24 bostic 6 5
c remove SYSV and is68k ifdef's
e
s 00002/00005/00921
d D 5.5 90/03/12 09:04:40 bostic 5 4
c remove Sprite ifdef's
e
s 00013/00115/00913
d D 5.4 90/03/12 08:52:36 bostic 4 3
c remove directory locking, including the -l flag
e
s 00000/00004/01028
d D 5.3 90/03/12 08:42:39 bostic 3 2
c redo system makefile configuration for BSD
e
s 00032/00015/01000
d D 5.2 90/03/11 15:39:00 bostic 2 1
c add Berkeley specific copyright notice
e
s 01015/00000/00000
d D 5.1 90/03/11 15:27:34 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 2
/*
D 35
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 35
I 35
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 35
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
D 21
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
E 21
I 21
 * %sccs.include.redist.c%
E 21
 */

#ifndef lint
D 35
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 35
I 35
static char copyright[] =
"%Z% Copyright (c) 1988, 1989, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 35
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
/*-
 * main.c --
 *	The main file for this entire program. Exit routines etc
 *	reside here.
 *
D 2
 * Copyright (c) 1988, 1989 by the Regents of the University of California
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any non-commercial purpose
 * and without fee is hereby granted, provided that the above copyright
 * notice appears in all copies.  The University of California,
 * Berkeley Softworks and Adam de Boor make no representations about
 * the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
 *
E 2
 * Utility functions defined in this file:
D 9
 *	Main_ParseArgLine   	Takes a line of arguments, breaks them and
 *	    	  	    	treats them as if they were given when first
 *	    	  	    	invoked. Used by the parse module to implement
 *	    	  	    	the .MFLAGS target.
E 9
I 9
 *	Main_ParseArgLine	Takes a line of arguments, breaks them and
 *				treats them as if they were given when first
 *				invoked. Used by the parse module to implement
 *				the .MFLAGS target.
E 9
 *
D 9
 *	Error	  	    	Print a tagged error message. The global
 *	    	  	    	MAKE variable must have been defined. This
 *	    	  	    	takes a format string and two optional
 *	    	  	    	arguments for it.
E 9
I 9
 *	Error			Print a tagged error message. The global
 *				MAKE variable must have been defined. This
 *				takes a format string and two optional
 *				arguments for it.
E 9
 *
D 9
 *	Fatal	  	    	Print an error message and exit. Also takes
 *	    	  	    	a format string and two arguments.
E 9
I 9
 *	Fatal			Print an error message and exit. Also takes
 *				a format string and two arguments.
E 9
 *
D 9
 *	Punt	  	    	Aborts all jobs and exits with a message. Also
 *	    	  	    	takes a format string and two arguments.
E 9
I 9
 *	Punt			Aborts all jobs and exits with a message. Also
 *				takes a format string and two arguments.
E 9
 *
D 9
 *	Finish	  	    	Finish things up by printing the number of
 *	    	  	    	errors which occured, as passed to it, and
 *	    	  	    	exiting.
E 9
I 9
 *	Finish			Finish things up by printing the number of
 *				errors which occured, as passed to it, and
 *				exiting.
E 9
 */
D 2
#ifndef lint
static char     *rcsid = "$Id: main.c,v 1.67 89/11/14 13:44:02 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

I 30
#include <sys/types.h>
#include <sys/time.h>
E 30
D 5
#include    <stdio.h>
#ifdef Sprite
#include    <stdlib.h>
#endif /* Sprite */
E 5
D 9
#include    <sys/types.h>
#include    <sys/signal.h>
#include    <sys/stat.h>
D 5
#include    <fcntl.h>
E 5
#include    <sys/errno.h>
I 5
#include    <fcntl.h>
E 5
#include    <ctype.h>
I 5
#include    <stdio.h>
E 5
#include    "make.h"
E 9
I 9
D 12
#include <sys/types.h>
E 12
I 12
#include <sys/param.h>
I 30
#include <sys/resource.h>
E 30
E 12
#include <sys/signal.h>
#include <sys/stat.h>
I 38
#include <sys/utsname.h>
E 38
I 24
#include <errno.h>
E 24
D 10
#include <sys/errno.h>
E 10
#include <fcntl.h>
D 13
#include <ctype.h>
E 13
#include <stdio.h>
I 30
#if __STDC__
#include <stdarg.h>
#else
E 30
I 10
#include <varargs.h>
I 30
#endif
E 30
E 10
#include "make.h"
I 30
#include "hash.h"
#include "dir.h"
#include "job.h"
E 30
I 13
#include "pathnames.h"
E 13
E 9

D 10
extern int errno;

E 10
I 9
#ifndef	DEFMAXLOCAL
#define	DEFMAXLOCAL DEFMAXJOBS
#endif	DEFMAXLOCAL
E 9

D 9
#ifndef DEFMAXLOCAL
#define DEFMAXLOCAL DEFMAXJOBS
#endif  DEFMAXLOCAL
E 9
I 9
#define	MAKEFLAGS	".MAKEFLAGS"
E 9

D 9
#define MAKEFLAGS  	".MAKEFLAGS"
E 9
I 9
D 10
static char		*progName;	/* Our invocation name */
E 10
Lst			create;		/* Targets to be made */
time_t			now;		/* Time at start of make */
GNode			*DEFAULT;	/* .DEFAULT node */
Boolean			allPrecious;	/* .PRECIOUS given on line by itself */
E 9

D 9
static char 	  	*progName;  	/* Our invocation name */
D 4
static Boolean	  	lockSet;    	/* TRUE if we set the lock file */
E 4
Lst			create;	    	/* Targets to be made */
time_t			now;	    	/* Time at start of make */
GNode			*DEFAULT;   	/* .DEFAULT node */
Boolean	    	    	allPrecious;	/* .PRECIOUS given on line by itself */

static int              printGraph;	/* -p flag */
static Boolean          noBuiltins;	/* -r flag */
D 4
static Boolean	  	noLocking;      /* -l flag */
E 4
static Lst  	    	makefiles;  	/* List of makefiles to read (in
E 9
I 9
D 14
static int		printGraph;	/* -p flag */
E 14
static Boolean		noBuiltins;	/* -r flag */
D 11
static Lst		makefiles;	/* List of makefiles to read (in
E 9
					 * order) */
E 11
I 11
static Lst		makefiles;	/* ordered list of makefiles to read */
E 11
D 9
int		    	maxJobs;	/* -J argument */
static int  	  	maxLocal;  	/* -L argument */
Boolean	    	  	debug;	    	/* -d flag */
Boolean	  	  	amMake; 	/* -M flag */
Boolean	    	  	noWarnings; 	/* -W flag */
Boolean	    	    	noExecute;  	/* -n flag */
Boolean	    	    	keepgoing;  	/* -k flag */
Boolean			queryFlag;  	/* -q flag */
Boolean			touchFlag;  	/* -t flag */
Boolean			usePipes;   	/* !-P flag */
Boolean			backwards;  	/* -B flag */
E 9
I 9
int			maxJobs;	/* -J argument */
static int		maxLocal;	/* -L argument */
I 30
Boolean			compatMake;	/* -B argument */
E 30
Boolean			debug;		/* -d flag */
D 10
Boolean			amMake;		/* -M flag */
E 10
D 14
Boolean			noWarnings;	/* -W flag */
E 14
Boolean			noExecute;	/* -n flag */
Boolean			keepgoing;	/* -k flag */
Boolean			queryFlag;	/* -q flag */
Boolean			touchFlag;	/* -t flag */
Boolean			usePipes;	/* !-P flag */
D 10
Boolean			backwards;	/* -B flag */
E 10
E 9
Boolean			ignoreErrors;	/* -i flag */
D 9
Boolean			beSilent;   	/* -s flag */
Boolean	    	    	sysVmake;   	/* -v flag */
D 8
Boolean			oldVars;    	/* -V flag */
E 8
I 8
Boolean			oldVars;    	/* variable substitution style */
E 8
Boolean	    	    	checkEnvFirst;	/* -e flag */
D 8
static Boolean	  	XFlag=FALSE;   	/* -X flag given */
static Boolean	  	xFlag=FALSE;	/* -x flag given */
Boolean	    	  	noExport;   	/* Set TRUE if shouldn't export */
E 8
static Boolean	  	jobsRunning;	/* TRUE if the jobs might be running */
E 9
I 9
Boolean			beSilent;	/* -s flag */
D 10
Boolean			sysVmake;	/* -v flag */
E 10
Boolean			oldVars;	/* variable substitution style */
Boolean			checkEnvFirst;	/* -e flag */
static Boolean		jobsRunning;	/* TRUE if the jobs might be running */
E 9

D 9
static Boolean	    	ReadMakefile();
E 9
I 9
static Boolean		ReadMakefile();
I 30
static void		usage();
E 30
E 9

I 13
D 37
static char *curdir;			/* if chdir'd for an architecture */
E 37
I 37
static char *curdir;			/* startup directory */
static char *objdir;			/* where we chdir'ed to */
E 37

E 13
D 10
/*
 * Initial value for optind when parsing args. Different getopts start it
 * differently...
 */
D 9
static int  	initOptInd;
E 9
I 9
static int	initOptInd;
E 9

D 8
#ifdef CAN_EXPORT
D 4
#define OPTSTR "BCD:I:J:L:MPSVWXd:ef:iklnp:qrstvxh"
E 4
I 4
#define OPTSTR "BCD:I:J:L:MPSVWXd:ef:iknp:qrstvxh"
E 4
#else
D 4
#define OPTSTR "BCD:I:J:L:MPSVWd:ef:iklnp:qrstvh"
E 4
I 4
#define OPTSTR "BCD:I:J:L:MPSVWd:ef:iknp:qrstvh"
E 4
#endif

E 8
D 9
static char 	    *help[] = {
"-B	    	Be as backwards-compatible with make as possible without\n\
E 9
I 9
static char	*help[] = {
"-B		Be as backwards-compatible with make as possible without\n\
E 9
		being make.",
D 9
"-C	    	Cancel any current indications of compatibility.",
E 9
I 9
"-C		Cancel any current indications of compatibility.",
E 9
"-D<var>	Define the variable <var> with value 1.",
"-I<dir>	Specify another directory in which to search for included\n\
		makefiles.",
"-J<num>	Specify maximum overall concurrency.",
"-L<num>	Specify maximum local concurrency.",
"-M		Be Make as closely as possible.",
"-P		Don't use pipes to catch the output of jobs, use files.",
D 9
"-S	    	Turn off the -k flag (see below).",
E 9
I 9
"-S		Turn off the -k flag (see below).",
E 9
D 8
#ifndef POSIX
"-V		Use old-style variable substitution.",
#endif
E 8
"-W		Don't print warning messages.",
D 8
#ifdef CAN_EXPORT
"-X		Turn off exporting of commands.",
#endif
E 8
D 9
"-d<flags>  	Turn on debugging output.",
E 9
I 9
"-d<flags>	Turn on debugging output.",
E 9
"-e		Give environment variables precedence over those in the\n\
		makefile(s).",
"-f<file>	Specify a(nother) makefile to read",
"-i		Ignore errors from executed commands.",
"-k		On error, continue working on targets that do not depend on\n\
		the one for which an error was detected.",
D 4
#ifdef DONT_LOCK
"-l	    	Turn on locking of the current directory.",
#else
"-l	    	Turn off locking of the current directory.",
#endif
E 4
D 9
"-n	    	Don't execute commands, just print them.",
"-p<num>    	Tell when to print the input graph: 1 (before processing),\n\
E 9
I 9
"-n		Don't execute commands, just print them.",
"-p<num>	Tell when to print the input graph: 1 (before processing),\n\
E 9
		2 (after processing), or 3 (both).",
D 9
"-q	    	See if anything needs to be done. Exits 1 if so.",
"-r	    	Do not read the system makefile for pre-defined rules.",
"-s	    	Don't print commands as they are executed.",
"-t	    	Update targets by \"touching\" them (see touch(1)).",
D 4
"-v	    	Be compatible with System V make. Implies -B, -V and no\n\
		directory locking.",
E 4
I 4
D 8
"-v	    	Be compatible with System V make. Implies -B, -V.",
E 4
#ifdef CAN_EXPORT
"-x	    	Allow exportation of commands.",
#endif
E 8
I 8
"-v	    	Be compatible with System V make. Implies -B.",
E 9
I 9
"-q		See if anything needs to be done. Exits 1 if so.",
"-r		Do not read the system makefile for pre-defined rules.",
"-s		Don't print commands as they are executed.",
"-t		Update targets by \"touching\" them (see touch(1)).",
"-v		Be compatible with System V make. Implies -B.",
E 9
E 8
D 3
"System configuration information:",
SYSPATHDOC,
SHELLDOC,
SYSMKDOC,
E 3
};


E 10
/*-
D 10
 *----------------------------------------------------------------------
E 10
 * MainParseArgs --
 *	Parse a given argument vector. Called from main() and from
 *	Main_ParseArgLine() when the .MAKEFLAGS target is used.
 *
 *	XXX: Deal with command line overriding .MAKEFLAGS in makefile
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Various global and local flags will be set depending on the flags
 *	given
D 10
 *----------------------------------------------------------------------
E 10
 */
static void
D 9
MainParseArgs (argc, argv)
    int		  argc;	      /* Number of arguments in argv */
    char	  **argv;     /* The arguments themselves */
E 9
I 9
MainParseArgs(argc, argv)
	int argc;
	char **argv;
E 9
{
D 9
    register int  i;
    register char *cp;
    extern int	optind;
    extern char	*optarg;
    char    	c;
E 9
I 9
	extern int optind;
	extern char *optarg;
D 29
	register int i;
E 29
D 30
	register char *cp;
D 29
	char c;
E 29
I 29
	int c;
E 30
I 30
D 34
	char c;
E 34
I 34
D 37
	int c;
E 37
I 37
D 38
	char c;
E 38
I 38
	int c;
E 38
E 37
E 34
E 30
E 29
E 9

I 22
	optind = 1;	/* since we're called more than once */
E 22
D 9
    optind = initOptInd;
E 9
I 9
D 10
	optind = initOptInd;
	while((c = getopt(argc, argv,
	    "BCD:I:J:L:MPSWd:ef:iknp:qrstvh")) != -1) {
E 10
I 10
D 14
	while((c = getopt(argc, argv, "D:I:J:L:PSWd:ef:iknp:qrstv")) != -1) {
E 14
I 14
D 19
	while((c = getopt(argc, argv, "D:I:d:ef:ij:knqrstv")) != -1) {
E 19
I 19
D 20
	while((c = getopt(argc, argv, "D:I:d:ef:ij:knqrst")) != -1) {
E 20
I 20
D 23
rearg:	while((c = getopt(argc, argv, "D:I:d:ef:ij:knqrst")) != -1) {
E 23
I 23
D 30
rearg:	while((c = getopt(argc, argv, "D:I:d:ef:ij:knqrst")) != EOF) {
E 30
I 30
#ifdef notyet
# define OPTFLAGS "BD:I:L:PSd:ef:ij:knqrst"
#else
# define OPTFLAGS "D:I:d:ef:ij:knqrst"
#endif
D 34
rearg:	while((c = getopt(argc, argv, OPTFLAGS)) != EOF) {
E 34
I 34
D 38
rearg:	while ((c = getopt(argc, argv, OPTFLAGS)) != EOF) {
E 38
I 38
rearg:	while((c = getopt(argc, argv, OPTFLAGS)) != EOF) {
E 38
E 34
E 30
E 23
E 20
E 19
E 14
E 10
		switch(c) {
D 10
		case 'B':
			backwards = TRUE;
			Var_Append(MAKEFLAGS, "-B", VAR_GLOBAL);
			break;
		case 'C':
			backwards = sysVmake = amMake = FALSE;
			Var_Append(MAKEFLAGS, "-C", VAR_GLOBAL);
			break;
E 10
		case 'D':
			Var_Set(optarg, "1", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, "-D", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'I':
			Parse_AddIncludeDir(optarg);
			Var_Append(MAKEFLAGS, "-I", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
D 14
		case 'J':
			maxJobs = atoi(optarg);
			Var_Append(MAKEFLAGS, "-J", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
E 14
I 14
D 30
#ifdef notdef
E 30
I 30
#ifdef notyet
		case 'B':
			compatMake = TRUE;
			break;
E 30
E 14
		case 'L':
			maxLocal = atoi(optarg);
			Var_Append(MAKEFLAGS, "-L", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
D 10
		case 'M':
			amMake = TRUE;
			Var_Append(MAKEFLAGS, "-M", VAR_GLOBAL);
			break;
E 10
		case 'P':
			usePipes = FALSE;
			Var_Append(MAKEFLAGS, "-P", VAR_GLOBAL);
			break;
		case 'S':
			keepgoing = FALSE;
			Var_Append(MAKEFLAGS, "-S", VAR_GLOBAL);
			break;
D 14
		case 'W':
			noWarnings = TRUE;
			Var_Append(MAKEFLAGS, "-W", VAR_GLOBAL);
			break;
E 14
I 14
#endif
E 14
		case 'd': {
			char *modules = optarg;
E 9

D 8
    while((c = getopt(argc, argv, OPTSTR)) != -1) {
E 8
I 8
D 9
    while((c = getopt(argc, argv, "BCD:I:J:L:MPSWd:ef:iknp:qrstvh")) != -1) {
E 8
	switch(c) {
	    case 'B':
D 8
		backwards = oldVars = TRUE;
E 8
I 8
		backwards = TRUE;
E 8
		Var_Append(MAKEFLAGS, "-B", VAR_GLOBAL);
		break;
	    case 'C':
D 8
		oldVars = backwards = sysVmake = amMake = FALSE;
E 8
I 8
		backwards = sysVmake = amMake = FALSE;
E 8
		Var_Append(MAKEFLAGS, "-C", VAR_GLOBAL);
		break;
	    case 'D':
		Var_Set(optarg, "1", VAR_GLOBAL);
		Var_Append(MAKEFLAGS, "-D", VAR_GLOBAL);
		Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
		break;
	    case 'I':
		Parse_AddIncludeDir(optarg);
		Var_Append(MAKEFLAGS, "-I", VAR_GLOBAL);
		Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
		break;
	    case 'J':
		maxJobs = atoi(optarg);
		Var_Append(MAKEFLAGS, "-J", VAR_GLOBAL);
		Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
		break;
	    case 'L':
		maxLocal = atoi(optarg);
		Var_Append(MAKEFLAGS, "-L", VAR_GLOBAL);
		Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
		break;
	    case 'M':
		amMake = TRUE;
		Var_Append(MAKEFLAGS, "-M", VAR_GLOBAL);
		break;
	    case 'P':
		usePipes = FALSE;
		Var_Append(MAKEFLAGS, "-P", VAR_GLOBAL);
		break;
	    case 'S':
		keepgoing = FALSE;
		Var_Append(MAKEFLAGS, "-S", VAR_GLOBAL);
		break;
D 8
	    case 'V':
		oldVars = TRUE;
		Var_Append(MAKEFLAGS, "-V", VAR_GLOBAL);
		break;
E 8
	    case 'W':
		noWarnings = TRUE;
		Var_Append(MAKEFLAGS, "-W", VAR_GLOBAL);
		break;
D 8
	    case 'X':
		XFlag = TRUE;
		Var_Append(MAKEFLAGS, "-X", VAR_GLOBAL);
		break;
E 8
	    case 'd':
	    {
		char	*modules = optarg;

		while (*modules) {
		    switch (*modules) {
			case 's':
			    debug |= DEBUG_SUFF;
			    break;
			case 'm':
			    debug |= DEBUG_MAKE;
			    break;
			case 'j':
			    debug |= DEBUG_JOB;
			    break;
			case 't':
			    debug |= DEBUG_TARG;
			    break;
			case 'd':
			    debug |= DEBUG_DIR;
			    break;
			case 'v':
			    debug |= DEBUG_VAR;
			    break;
			case 'c':
			    debug |= DEBUG_COND;
			    break;
			case 'p':
			    debug |= DEBUG_PARSE;
			    break;
			case 'r':
			    debug |= DEBUG_RMT;
			    break;
			case 'a':
			    debug |= DEBUG_ARCH;
			    break;
			case '*':
			    debug = ~0;
			    break;
		    }
		    modules++;
E 9
I 9
D 14
			while (*modules) {
E 14
I 14
			for (; *modules; ++modules)
E 14
				switch (*modules) {
D 14
				case '*':
E 14
I 14
				case 'A':
E 14
					debug = ~0;
					break;
				case 'a':
					debug |= DEBUG_ARCH;
					break;
				case 'c':
					debug |= DEBUG_COND;
					break;
				case 'd':
					debug |= DEBUG_DIR;
					break;
I 30
				case 'f':
					debug |= DEBUG_FOR;
					break;
E 30
I 14
				case 'g':
					if (modules[1] == '1') {
						debug |= DEBUG_GRAPH1;
						++modules;
					}
					else if (modules[1] == '2') {
						debug |= DEBUG_GRAPH2;
						++modules;
					}
					break;
E 14
				case 'j':
					debug |= DEBUG_JOB;
					break;
				case 'm':
					debug |= DEBUG_MAKE;
					break;
D 16
				case 'p':
					debug |= DEBUG_PARSE;
					break;
E 16
D 14
				case 'r':
					debug |= DEBUG_RMT;
					break;
E 14
				case 's':
					debug |= DEBUG_SUFF;
					break;
				case 't':
					debug |= DEBUG_TARG;
					break;
				case 'v':
					debug |= DEBUG_VAR;
					break;
I 25
				default:
					(void)fprintf(stderr,
				"make: illegal argument to d option -- %c\n",
					    *modules);
					usage();
E 25
				}
D 14
				++modules;
			}
E 14
			Var_Append(MAKEFLAGS, "-d", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
E 9
		}
D 9
		Var_Append(MAKEFLAGS, "-d", VAR_GLOBAL);
		Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
		break;
	    }
	    case 'e':
		checkEnvFirst = TRUE;
		Var_Append(MAKEFLAGS, "-e", VAR_GLOBAL);
		break;
	    case 'f':
		(void)Lst_AtEnd(makefiles, (ClientData)optarg);
		break;
	    case 'i':
		ignoreErrors = TRUE;
		Var_Append(MAKEFLAGS, "-i", VAR_GLOBAL);
		break;
	    case 'k':
		keepgoing = TRUE;
		Var_Append(MAKEFLAGS, "-k", VAR_GLOBAL);
		break;
D 4
	    case 'l':
#ifdef DONT_LOCK
		noLocking = FALSE;
#else
		noLocking = TRUE;
#endif
		Var_Append(MAKEFLAGS, "-l", VAR_GLOBAL);
		break;
E 4
	    case 'n':
		noExecute = TRUE;
		Var_Append(MAKEFLAGS, "-n", VAR_GLOBAL);
		break;
	    case 'p':
		printGraph = atoi(optarg);
		break;
	    case 'q':
		queryFlag = TRUE;
		Var_Append(MAKEFLAGS, "-q", VAR_GLOBAL); /* Kind of
							  * nonsensical, wot?
							  */
		break;
	    case 'r':
		noBuiltins = TRUE;
		Var_Append(MAKEFLAGS, "-r", VAR_GLOBAL);
		break;
	    case 's':
		beSilent = TRUE;
		Var_Append(MAKEFLAGS, "-s", VAR_GLOBAL);
		break;
	    case 't':
		touchFlag = TRUE;
		Var_Append(MAKEFLAGS, "-t", VAR_GLOBAL);
		break;
	    case 'v':
D 4
		sysVmake = oldVars = backwards = noLocking = TRUE;
E 4
I 4
D 8
		sysVmake = oldVars = backwards = TRUE;
E 8
I 8
		sysVmake = backwards = TRUE;
E 8
E 4
		Var_Append(MAKEFLAGS, "-v", VAR_GLOBAL);
		break;
	    case 'h':
	    case '?':
	    {
		int 	i;
E 9
I 9
		case 'e':
			checkEnvFirst = TRUE;
			Var_Append(MAKEFLAGS, "-e", VAR_GLOBAL);
			break;
		case 'f':
			(void)Lst_AtEnd(makefiles, (ClientData)optarg);
			break;
		case 'i':
			ignoreErrors = TRUE;
			Var_Append(MAKEFLAGS, "-i", VAR_GLOBAL);
			break;
I 14
		case 'j':
			maxJobs = atoi(optarg);
D 37
			Var_Append(MAKEFLAGS, "-J", VAR_GLOBAL);
E 37
I 37
			Var_Append(MAKEFLAGS, "-j", VAR_GLOBAL);
E 37
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
E 14
		case 'k':
			keepgoing = TRUE;
			Var_Append(MAKEFLAGS, "-k", VAR_GLOBAL);
			break;
		case 'n':
			noExecute = TRUE;
			Var_Append(MAKEFLAGS, "-n", VAR_GLOBAL);
			break;
D 14
		case 'p':
			printGraph = atoi(optarg);
			break;
E 14
		case 'q':
			queryFlag = TRUE;
			/* Kind of nonsensical, wot? */
			Var_Append(MAKEFLAGS, "-q", VAR_GLOBAL);
			break;
		case 'r':
			noBuiltins = TRUE;
			Var_Append(MAKEFLAGS, "-r", VAR_GLOBAL);
			break;
		case 's':
			beSilent = TRUE;
			Var_Append(MAKEFLAGS, "-s", VAR_GLOBAL);
			break;
		case 't':
			touchFlag = TRUE;
			Var_Append(MAKEFLAGS, "-t", VAR_GLOBAL);
			break;
D 10
		case 'v':
			sysVmake = backwards = TRUE;
			Var_Append(MAKEFLAGS, "-v", VAR_GLOBAL);
			break;
		case 'h':
		case '?': {
			int i;
E 9

D 9
		for (i = 0; i < sizeof(help)/sizeof(help[0]); i++) {
		    printf("%s\n", help[i]);
E 9
I 9
			for (i = 0; i < sizeof(help)/sizeof(help[0]); i++)
				(void)printf("%s\n", help[i]);
			exit(c == '?' ? -1 : 0);
E 10
I 10
		default:
		case '?':
			usage();
E 10
E 9
		}
D 9
		exit(c == '?' ? -1 : 0);
	    }
E 9
I 9
D 10
		}
E 10
E 9
	}
D 9
    }
E 9

D 9
    /*
     * Take care of encompassing compatibility levels...
     */
    if (amMake) {
	backwards = TRUE;
    }
D 8
    if (backwards) {
	oldVars = TRUE;
    }
E 8
I 8
    oldVars = TRUE;
E 9
I 9
D 10
	/* Take care of encompassing compatibility levels... */
	if (amMake)
		backwards = TRUE;
E 10
	oldVars = TRUE;
E 9
E 8

D 9
    /*
     * See if the rest of the arguments are variable assignments and perform
     * them if so. Else take them to be targets and stuff them on the end
     * of the "create" list.
     */
    for (i = optind; i < argc; i++) {
	if (Parse_IsVar (argv[i])) {
	    Parse_DoVar(argv[i], VAR_CMD);
	} else {
	    if (argv[i][0] == 0) {
		Punt("Bogus argument in MainParseArgs");
	    }
	    (void)Lst_AtEnd (create, (ClientData)argv[i]);
E 9
I 9
	/*
	 * See if the rest of the arguments are variable assignments and
	 * perform them if so. Else take them to be targets and stuff them
	 * on the end of the "create" list.
	 */
D 10
	for (i = optind; i < argc; i++) {
		if (Parse_IsVar (argv[i])) {
			Parse_DoVar(argv[i], VAR_CMD);
		} else {
			if (argv[i][0] == 0) {
E 10
I 10
D 20
	for (argv += optind; *argv; ++argv)
E 20
I 20
	for (argv += optind, argc -= optind; *argv; ++argv, --argc)
E 20
		if (Parse_IsVar(*argv))
			Parse_DoVar(*argv, VAR_CMD);
		else {
D 26
			if (!**argv)
E 26
I 26
D 28
			if (!*argv[0] || *argv[0] == '-' && !*argv[1])
E 28
I 28
D 30
			if (!*argv[0] || *argv[0] == '-' && !(*argv)[1])
E 30
I 30
D 31
			if (!**argv)
E 31
I 31
D 33
			if (!*argv[0] || *argv[0] == '-' && !*argv[1])
E 33
I 33
D 37
			if (!*argv[0] || *argv[0] == '-' && !(*argv)[1])
E 37
I 37
			if (!**argv)
E 37
E 33
E 31
E 30
E 28
E 26
E 10
D 17
				Punt("Bogus argument in MainParseArgs");
E 17
I 17
				Punt("illegal (null) argument.");
I 20
			if (**argv == '-') {
D 37
				optind = 0;
E 37
I 37
				if ((*argv)[1])
					optind = 0;     /* -flag... */
				else
					optind = 1;     /* - */
E 37
				goto rearg;
			}
E 20
E 17
D 10
			}
			(void)Lst_AtEnd (create, (ClientData)argv[i]);
E 10
I 10
D 38
			(void)Lst_AtEnd(create, (ClientData)*argv);
E 38
I 38
			(void)Lst_AtEnd(create, (ClientData)strdup(*argv));
E 38
E 10
		}
E 9
D 10
	}
E 10
D 9
    }
E 9
}
D 4

E 4
I 4

E 4
/*-
D 9
 *----------------------------------------------------------------------
E 9
 * Main_ParseArgLine --
 *  	Used by the parse module when a .MFLAGS or .MAKEFLAGS target
 *	is encountered and by main() when reading the .MAKEFLAGS envariable.
 *	Takes a line of arguments and breaks it into its
 * 	component words and passes those words and the number of them to the
 *	MainParseArgs function.
 *	The line should have all its leading whitespace removed.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Only those that come from the various arguments.
D 10
 *-----------------------------------------------------------------------
E 10
 */
void
D 9
Main_ParseArgLine (line)
    char    	  *line;      /* Line to fracture */
E 9
I 9
Main_ParseArgLine(line)
	char *line;			/* Line to fracture */
E 9
{
D 9
    char    	  **argv;     /* Manufactured argument vector */
    int     	  argc;	      /* Number of arguments in argv */
E 9
I 9
	char **argv;			/* Manufactured argument vector */
	int argc;			/* Number of arguments in argv */
E 9

D 9
    if (line == NULL) return;
    while (*line == ' ') line++;
E 9
I 9
	if (line == NULL)
		return;
D 10
	while (*line == ' ')
		++line;
E 10
I 10
D 30
	for (; *line == ' '; ++line);
E 30
I 30
	for (; *line == ' '; ++line)
		continue;
E 30
I 17
	if (!*line)
		return;
E 17
E 10
E 9

D 9
    argv = Str_BreakString (line, " \t", "\n", &argc);

    MainParseArgs(argc, argv);

    Str_FreeVec(argc, argv);
E 9
I 9
D 11
	argv = Str_BreakString (line, " \t", "\n", &argc);
E 11
I 11
D 13
	argv = Str_BreakString(line, " \t", "\n", &argc);
E 13
I 13
D 38
	argv = brk_string(line, &argc);
E 38
I 38
	argv = brk_string(line, &argc, TRUE);
E 38
E 13
E 11
	MainParseArgs(argc, argv);
D 13
	Str_FreeVec(argc, argv);
E 13
E 9
}
D 4

E 4
I 4

E 4
/*-
D 4
 *-----------------------------------------------------------------------
 * MainUnlock --
 *	Unlock the current directory. Called as an ExitHandler.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The locking file LOCKFILE is removed.
 *
 *-----------------------------------------------------------------------
 */
static void
MainUnlock ()
{
    (void)unlink (LOCKFILE);
}

/*-
E 4
D 9
 *----------------------------------------------------------------------
E 9
 * main --
 *	The main function, for obvious reasons. Initializes variables
 *	and a few modules, then parses the arguments give it in the
 *	environment and on the command line. Reads the system makefile
 *	followed by either Makefile, makefile or the file given by the
 *	-f argument. Sets the .MAKEFLAGS PMake variable based on all the
 *	flags it has received by then uses either the Make or the Compat
 *	module to create the initial list of targets.
 *
 * Results:
 *	If -q was given, exits -1 if anything was out-of-date. Else it exits
 *	0.
 *
 * Side Effects:
 *	The program exits when done. Targets are created. etc. etc. etc.
D 10
 *
 *----------------------------------------------------------------------
E 10
 */
I 30
int
E 30
D 9
main (argc, argv)
    int           argc;
    char          **argv;
E 9
I 9
main(argc, argv)
	int argc;
	char **argv;
E 9
{
D 9
    Lst             targs;     	/* list of target nodes to create. Passed to
				 * Make_Init */
    Boolean         outOfDate; 	/* FALSE if all targets up to date */
    char    	    *cp;
    extern int	    optind;
E 9
I 9
D 10
	extern int optind;
E 10
	Lst targs;	/* target nodes to create -- passed to Make_Init */
D 30
	Boolean outOfDate; 	/* FALSE if all targets up to date */
I 13
	struct stat sb;
D 17
	char *path, *getenv();
E 17
I 17
	char *p, *path, *getenv();
E 30
I 30
	Boolean outOfDate = TRUE; 	/* FALSE if all targets up to date */
	struct stat sb, sa;
D 37
	char *p, *path, *pwd, *getenv();
E 37
I 37
D 38
	char *p, *path, *pwd, *getenv(), *getwd();
E 38
I 38
	char *p, *p1, *path, *pwd, *getenv(), *getwd();
E 38
	char mdpath[MAXPATHLEN + 1];
	char obpath[MAXPATHLEN + 1];
	char cdpath[MAXPATHLEN + 1];
I 38
	struct utsname utsname;
    	char *machine = getenv("MACHINE");
E 38
E 37
E 30
E 17
E 13
D 10
	char *cp;
E 10
E 9

I 13
	/*
I 30
	 * Find where we are and take care of PWD for the automounter...
I 37
	 * All this code is so that we know where we are when we start up
	 * on a different machine with pmake.
E 37
	 */
D 37
	curdir = emalloc((u_int)MAXPATHLEN + 1);
	if (!getwd(curdir)) {
E 37
I 37
	curdir = cdpath;
D 38
	if (getwd(curdir) == NULL) {
E 37
		(void)fprintf(stderr, "make: %s.\n", curdir);
E 38
I 38
	if (getcwd(curdir, MAXPATHLEN) == NULL) {
		(void)fprintf(stderr, "make: %s.\n", strerror(errno));
E 38
		exit(2);
	}

	if (stat(curdir, &sa) == -1) {
	    (void)fprintf(stderr, "make: %s: %s.\n",
			  curdir, strerror(errno));
	    exit(2);
	}

	if ((pwd = getenv("PWD")) != NULL) {
	    if (stat(pwd, &sb) == 0 && sa.st_ino == sb.st_ino &&
		sa.st_dev == sb.st_dev) 
		(void) strcpy(curdir, pwd);
	}

I 38
	/*
	 * Get the name of this type of MACHINE from utsname
	 * so we can share an executable for similar machines.
	 * (i.e. m68k: amiga hp300, mac68k, sun3, ...)
	 *
	 * Note that while MACHINE is decided at run-time,
	 * MACHINE_ARCH is always known at compile time.
	 */
    	if (!machine) {
	    if (uname(&utsname)) {
		    perror("make: uname");
		    exit(2);
	    }
	    machine = utsname.machine;
	}
E 38

	/*
E 30
	 * if the MAKEOBJDIR (or by default, the _PATH_OBJDIR) directory
	 * exists, change into it and build there.  Once things are
	 * initted, have to add the original directory to the search path,
	 * and modify the paths for the Makefiles apropriately.  The
	 * current directory is also placed as a variable for make scripts.
	 */
D 37
	if (!(path = getenv("MAKEOBJDIR")))
E 37
I 37
	if (!(path = getenv("MAKEOBJDIR"))) {
E 37
		path = _PATH_OBJDIR;
I 37
D 38
		(void) sprintf(mdpath, "%s.%s", path, MACHINE);
E 38
I 38
		(void) sprintf(mdpath, "%s.%s", path, machine);
E 38
	}
	else
		(void) strncpy(mdpath, path, MAXPATHLEN + 1);
E 37
D 27
	if (!lstat(path, &sb)) {
E 27
I 27
D 30
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode) &&
	    lstat(path, &sb) == 0) {
E 27
		if (S_ISDIR(sb.st_mode))
			curdir = "..";
		else {
			curdir = emalloc((u_int)MAXPATHLEN + 1);
			if (!getwd(curdir)) {
				(void)fprintf(stderr, "make: %s.\n", curdir);
				exit(2);
			}
		}
E 30
I 30
	
D 32
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {

E 32
I 32
D 37
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode) &&
	    lstat(path, &sb) == 0) {
E 32
E 30
		if (chdir(path)) {
D 24
			extern int errno;

E 24
			(void)fprintf(stderr, "make: %s: %s.\n",
			    path, strerror(errno));
			exit(2);
E 37
I 37
	if (stat(mdpath, &sb) == 0 && S_ISDIR(sb.st_mode)) {

		if (chdir(mdpath)) {
			(void)fprintf(stderr, "make warning: %s: %s.\n",
				      mdpath, strerror(errno));
			objdir = curdir;
E 37
		}
I 30
D 37
		if (path[0] != '/') {
			char cwd[MAXPATHLEN];
			(void) sprintf(cwd, "%s/%s", curdir, path);
			setenv("PWD", cwd, 1);
E 37
I 37
		else {
			if (mdpath[0] != '/') {
				(void) sprintf(obpath, "%s/%s", curdir, mdpath);
				objdir = obpath;
			}
			else
				objdir = mdpath;
E 37
		}
D 37
		else
			setenv("PWD", path, 1);
E 37
E 30
	}
I 30
D 36
	else 
E 36
I 36
	else {
E 36
D 37
		setenv("PWD", curdir, 1);
I 36
		path = ".";
E 37
I 37
		if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {

			if (chdir(path)) {
				(void)fprintf(stderr, "make warning: %s: %s.\n",
					      path, strerror(errno));
				objdir = curdir;
			}
			else {
				if (path[0] != '/') {
					(void) sprintf(obpath, "%s/%s", curdir,
						       path);
					objdir = obpath;
				}
				else
					objdir = obpath;
			}
		}
		else
			objdir = curdir;
E 37
	}
E 36
E 30

I 37
	setenv("PWD", objdir, 1);

E 37
E 13
I 9
D 11
	create = Lst_Init (FALSE);
E 11
I 11
	create = Lst_Init(FALSE);
E 11
	makefiles = Lst_Init(FALSE);
	beSilent = FALSE;		/* Print commands as executed */
	ignoreErrors = FALSE;		/* Pay attention to non-zero returns */
	noExecute = FALSE;		/* Execute all commands */
	keepgoing = FALSE;		/* Stop on error */
	allPrecious = FALSE;		/* Remove targets when interrupted */
	queryFlag = FALSE;		/* This is not just a check-run */
	noBuiltins = FALSE;		/* Read the built-in rules */
	touchFlag = FALSE;		/* Actually update targets */
	usePipes = TRUE;		/* Catch child output in pipes */
	debug = 0;			/* No debug verbosity, please. */
D 14
	noWarnings = FALSE;		/* Print warning messages */
E 14
D 10
	sysVmake = FALSE;		/* Don't be System V compatible */
E 10
	jobsRunning = FALSE;
E 9

D 9
    create = Lst_Init (FALSE);
    makefiles = Lst_Init(FALSE);

    beSilent = FALSE;	      	/* Print commands as executed */
    ignoreErrors = FALSE;     	/* Pay attention to non-zero returns */
    noExecute = FALSE;	      	/* Execute all commands */
    keepgoing = FALSE;	      	/* Stop on error */
    allPrecious = FALSE;      	/* Remove targets when interrupted */
    queryFlag = FALSE;	      	/* This is not just a check-run */
    noBuiltins = FALSE;	      	/* Read the built-in rules */
    touchFlag = FALSE;	      	/* Actually update targets */
    usePipes = TRUE;	      	/* Catch child output in pipes */
D 4
#ifndef DONT_LOCK
    noLocking = FALSE;	      	/* Lock the current directory against other
				 * pmakes */
#else
    noLocking = TRUE;
#endif /* DONT_LOCK */
E 4
    debug = 0;	      	    	/* No debug verbosity, please. */
    noWarnings = FALSE;	    	/* Print warning messages */
    sysVmake = FALSE;	    	/* Don't be System V compatible */

    jobsRunning = FALSE;

    maxJobs = DEFMAXJOBS;     	/* Set the default maximum concurrency */
    maxLocal = DEFMAXLOCAL;   	/* Set the default local max concurrency */
E 9
I 9
	maxJobs = DEFMAXJOBS;		/* Set default max concurrency */
	maxLocal = DEFMAXLOCAL;		/* Set default local max concurrency */
I 30
#ifdef notyet
	compatMake = FALSE;		/* No compat mode */
#else
	compatMake = TRUE;		/* No compat mode */
#endif
E 30
E 9
    
I 30

E 30
D 9
    /*
     * Deal with disagreement between different getopt's as to what
     * the initial value of optind should be by simply saving the
     * damn thing.
     */
    initOptInd = optind;
    
    /*
     * See what the user calls us. If s/he calls us (yuck) "make", then
     * act like it. Otherwise act like our normal, cheerful self.
     */
    cp = rindex (argv[0], '/');
    if (cp != (char *)NULL) {
	cp += 1;
    } else {
	cp = argv[0];
    }
    progName = cp;
E 9
I 9
	/*
D 10
	 * Deal with disagreement between different getopt's as to what
	 * the initial value of optind should be by simply saving the
	 * damn thing.
	 */
	initOptInd = optind;
E 9

D 9
    if (strcmp (cp, "make") == 0) {
	amMake = TRUE;	      	/* Be like make */
	backwards = TRUE;     	/* Do things the old-fashioned way */
D 8
	oldVars = TRUE;	      	/* Same with variables */
E 8
    } else if (strcmp(cp, "smake") == 0 || strcmp(cp, "vmake") == 0) {
D 4
	sysVmake = oldVars = backwards = noLocking = TRUE;
E 4
I 4
D 8
	sysVmake = oldVars = backwards = TRUE;
E 8
I 8
	sysVmake = backwards = TRUE;
E 8
E 4
    } else {
	amMake = FALSE;
	backwards = FALSE;    	/* Do things MY way, not MAKE's */
D 7
#ifdef DEF_OLD_VARS
E 7
D 8
	oldVars = TRUE;
E 8
D 7
#else
	oldVars = FALSE;      	/* don't substitute for undefined variables */
#endif
E 7
    }
E 9
I 9
	/*
	 * See what the user calls us. If s/he calls us (yuck) "make", then
	 * act like it. Otherwise act like our normal, cheerful self.
	 */
	cp = rindex (argv[0], '/');
	if (cp != (char *)NULL) {
		cp += 1;
	} else {
		cp = argv[0];
	}
	progName = cp;
E 9

D 9
    /*
     * Initialize the parsing, directory and variable modules to prepare
     * for the reading of inclusion paths and variable settings on the
     * command line 
     */
    Dir_Init ();		/* Initialize directory structures so -I flags
E 9
I 9
	if (strcmp (cp, "make") == 0) {
		amMake = TRUE;		/* Be like make */
		backwards = TRUE;	/* Do things the old-fashioned way */
	} else if (strcmp(cp, "smake") == 0 || strcmp(cp, "vmake") == 0) {
		sysVmake = backwards = TRUE;
	} else {
		amMake = FALSE;
		backwards = FALSE;	/* Do things MY way, not MAKE's */
	}

	/*
E 10
	 * Initialize the parsing, directory and variable modules to prepare
	 * for the reading of inclusion paths and variable settings on the
	 * command line
	 */
	Dir_Init();		/* Initialize directory structures so -I flags
E 9
				 * can be processed correctly */
D 9
    Parse_Init ();		/* Need to initialize the paths of #include
E 9
I 9
	Parse_Init();		/* Need to initialize the paths of #include
E 9
				 * directories */
D 9
    Var_Init ();		/* As well as the lists of variables for
E 9
I 9
	Var_Init();		/* As well as the lists of variables for
E 9
				 * parsing arguments */
I 38
        str_init();
E 38
D 30

E 30
I 13
D 37
	if (curdir) {
E 37
I 37
	if (objdir != curdir)
E 37
		Dir_AddDir(dirSearchPath, curdir);
D 37
		Var_Set(".CURDIR", curdir, VAR_GLOBAL);
D 30
	} else
		Var_Set(".CURDIR", ".", VAR_GLOBAL);
E 30
I 30
	}
	Var_Set(".OBJDIR", path, VAR_GLOBAL);
E 37
I 37
	Var_Set(".CURDIR", curdir, VAR_GLOBAL);
	Var_Set(".OBJDIR", objdir, VAR_GLOBAL);
E 37
E 30

E 13
D 9
    /*
     * Initialize various variables.
     *	.PMAKE gets how we were executed.
     *	MAKE also gets this name, for compatibility
     *	.MAKEFLAGS gets set to the empty string just in case.
     *  MFLAGS also gets initialized empty, for compatibility.
     */
    Var_Set (".PMAKE", argv[0], VAR_GLOBAL);
    Var_Set ("MAKE", argv[0], VAR_GLOBAL);
    Var_Set (MAKEFLAGS, "", VAR_GLOBAL);
    Var_Set ("MFLAGS", "", VAR_GLOBAL);
E 9
I 9
	/*
	 * Initialize various variables.
D 15
	 *	.PMAKE gets how we were executed.
E 15
	 *	MAKE also gets this name, for compatibility
	 *	.MAKEFLAGS gets set to the empty string just in case.
	 *	MFLAGS also gets initialized empty, for compatibility.
	 */
D 15
	Var_Set(".PMAKE", argv[0], VAR_GLOBAL);
E 15
	Var_Set("MAKE", argv[0], VAR_GLOBAL);
	Var_Set(MAKEFLAGS, "", VAR_GLOBAL);
	Var_Set("MFLAGS", "", VAR_GLOBAL);
I 37
D 38
#ifdef MACHINE
E 37
I 12
D 13
	Var_Set ("MACHINE", MACHINE, VAR_GLOBAL);
E 13
I 13
	Var_Set("MACHINE", MACHINE, VAR_GLOBAL);
I 37
#endif
E 38
I 38
	Var_Set("MACHINE", machine, VAR_GLOBAL);
E 38
#ifdef MACHINE_ARCH
	Var_Set("MACHINE_ARCH", MACHINE_ARCH, VAR_GLOBAL);
#endif
E 37
E 13
E 12
E 9

D 9
    /*
     * First snag any flags out of the PMAKE environment variable.
     * (Note this is *not* MAKEFLAGS since /bin/make uses that and it's in
     * a different format).
     */
E 9
I 9
	/*
D 15
	 * First snag any flags out of the PMAKE environment variable.
E 15
I 15
	 * First snag any flags out of the MAKE environment variable.
E 15
	 * (Note this is *not* MAKEFLAGS since /bin/make uses that and it's
	 * in a different format).
	 */
E 9
#ifdef POSIX
D 9
    Main_ParseArgLine(getenv("MAKEFLAGS"));
E 9
I 9
	Main_ParseArgLine(getenv("MAKEFLAGS"));
E 9
#else
D 9
    Main_ParseArgLine (getenv("PMAKE"));
E 9
I 9
D 15
	Main_ParseArgLine(getenv("PMAKE"));
E 15
I 15
	Main_ParseArgLine(getenv("MAKE"));
E 15
E 9
#endif
    
D 9
    MainParseArgs (argc, argv);
E 9
I 9
	MainParseArgs(argc, argv);
E 9

D 9
    /*
D 4
     * If the user didn't tell us not to lock the directory, attempt to create
     * the lock file. Complain if we can't, otherwise set up an exit handler
     * to remove the lock file...
     */
    if (!noLocking) {
	int	  	oldMask;    /* Previous signal mask */
	int	  	lockID;     /* Stream ID of opened lock file */
	
#ifndef SYSV
	oldMask = sigblock(sigmask(SIGINT));
#else
	oldMask = sighold(SIGINT);
#endif
	
	lockID = open (LOCKFILE, O_CREAT | O_EXCL, 0666);
	if (lockID < 0 && errno == EEXIST) {
	    /*
	     * Find out who owns the file. If the user who called us
	     * owns it, then we ignore the lock file. Note that we also
	     * do not install an exit handler to remove the file -- if the
	     * lockfile is there from a previous make, it'll still be there
	     * when we leave.
	     */
	    struct stat   fsa;    /* Attributes of the lock file */

	    (void) stat (LOCKFILE,  &fsa);
	    if (fsa.st_uid == getuid()) {
		Error ("Lockfile owned by you -- ignoring it");
		lockSet = FALSE;
	    } else {
		char  	lsCmd[40];
		(void)sprintf (lsCmd, "ls -l %s", LOCKFILE);
		(void)system(lsCmd);
		Fatal ("This directory is already locked (%s exists)",
		       LOCKFILE);
	    }
	} else if (lockID < 0) {
	    Fatal ("Could not create lock file %s", LOCKFILE);
	} else {
	    extern exit();

	    lockSet = TRUE;
#ifdef sun
	    on_exit(MainUnlock);
#endif
	    /* (void) Proc_SetExitHandler (MainUnlock, (ClientData)0); */
	    signal(SIGINT, exit);
	    (void)close (lockID);
	}
	
#ifndef SYSV
	(void) sigsetmask(oldMask);
#else 
	(void) sigrelse(SIGINT);
#endif
    }

    /*
E 4
     * Initialize archive, target and suffix modules in preparation for
     * parsing the makefile(s) 
     */
    Arch_Init ();
    Targ_Init ();
    Suff_Init ();
E 9
I 9
	/*
	 * Initialize archive, target and suffix modules in preparation for
	 * parsing the makefile(s)
	 */
	Arch_Init();
	Targ_Init();
	Suff_Init();
E 9

D 9
    DEFAULT = NILGNODE;
E 9
I 9
	DEFAULT = NILGNODE;
	(void)time(&now);
E 9

D 9
    now = time(0);
E 9
I 9
	/*
	 * Set up the .TARGETS variable to contain the list of targets to be
	 * created. If none specified, make the variable empty -- the parser
	 * will fill the thing in with the default or .MAIN target.
	 */
	if (!Lst_IsEmpty(create)) {
		LstNode ln;
E 9

D 9
    /*
     * Set up the .TARGETS variable to contain the list of targets to be
     * created. If none specified, make the variable empty -- the parser
     * will fill the thing in with the default or .MAIN target.
     */
    if (!Lst_IsEmpty(create)) {
	LstNode	ln;
E 9
I 9
		for (ln = Lst_First(create); ln != NILLNODE;
		    ln = Lst_Succ(ln)) {
			char *name = (char *)Lst_Datum(ln);
E 9

D 9
	for (ln = Lst_First(create); ln != NILLNODE; ln = Lst_Succ(ln)) {
	    char    *name = (char *)Lst_Datum(ln);
E 9
I 9
			Var_Append(".TARGETS", name, VAR_GLOBAL);
		}
	} else
		Var_Set(".TARGETS", "", VAR_GLOBAL);
E 9

D 9
	    Var_Append(".TARGETS", name, VAR_GLOBAL);
	}
    } else {
	Var_Set(".TARGETS", "", VAR_GLOBAL);
    }
E 9
I 9
	/*
	 * Read in the built-in rules first, followed by the specified makefile,
	 * if it was (makefile != (char *) NULL), or the default Makefile and
	 * makefile, in that order, if it wasn't.
	 */
D 11
	 if (!noBuiltins && !ReadMakefile (DEFSYSMK))
		Fatal ("Could not open system rules (%s)", DEFSYSMK);
E 11
I 11
D 13
	 if (!noBuiltins && !ReadMakefile(DEFSYSMK))
		Fatal("make: no system rules (%s).", DEFSYSMK);
E 13
I 13
	 if (!noBuiltins && !ReadMakefile(_PATH_DEFSYSMK))
		Fatal("make: no system rules (%s).", _PATH_DEFSYSMK);
E 13
E 11
E 9

D 9
    /*
     * Read in the built-in rules first, followed by the specified makefile,
     * if it was (makefile != (char *) NULL), or the default Makefile and
     * makefile, in that order, if it wasn't. 
     */
    if (!noBuiltins && !ReadMakefile (DEFSYSMK)) {
	Fatal ("Could not open system rules (%s)", DEFSYSMK);
    }
E 9
I 9
	if (!Lst_IsEmpty(makefiles)) {
		LstNode ln;
E 9

D 9
    if (!Lst_IsEmpty(makefiles)) {
	LstNode	ln = Lst_Find(makefiles, (ClientData)NULL, ReadMakefile);

	if (ln != NILLNODE) {
	    Fatal ("Cannot open %s", (char *)Lst_Datum(ln));
	}
    } else {
E 9
I 9
		ln = Lst_Find(makefiles, (ClientData)NULL, ReadMakefile);
		if (ln != NILLNODE)
D 11
			Fatal ("Cannot open %s", (char *)Lst_Datum(ln));
E 11
I 11
			Fatal("make: cannot open %s.", (char *)Lst_Datum(ln));
E 11
D 10
	} else {
E 9
#ifdef POSIX
D 9
	if (!ReadMakefile("makefile")) {
	    (void)ReadMakefile("Makefile");
	}
E 9
I 9
		if (!ReadMakefile("makefile"))
			(void)ReadMakefile("Makefile");
E 9
#else
D 9
	if (!ReadMakefile ((amMake || sysVmake) ? "makefile" : "Makefile")) {
	    (void) ReadMakefile ((amMake||sysVmake) ? "Makefile" : "makefile");
	}
E 9
I 9
		if (!ReadMakefile((amMake || sysVmake) ?
		    "makefile" : "Makefile"))
			(void)ReadMakefile((amMake||sysVmake) ?
			    "Makefile" : "makefile");
E 9
#endif
D 9
    }
E 9
I 9
	}
E 10
I 10
	} else if (!ReadMakefile("makefile"))
		(void)ReadMakefile("Makefile");
E 10
E 9

I 18
	(void)ReadMakefile(".depend");

E 18
D 8
    /*
     * Figure "noExport" out based on the current mode. Since exporting each
     * command in make mode is rather inefficient, we only export if the -x
     * flag was given. In regular mode though, we only refuse to export if
     * -X was given. In case the operative flag was given in the environment,
     * however, the opposite one may be given on the command line and cancel
     * the action.
     */
    if (amMake) {
	noExport = !xFlag || XFlag;
    } else {
	noExport = XFlag && !xFlag;
    }
    
E 8
D 9
    Var_Append ("MFLAGS", Var_Value(MAKEFLAGS, VAR_GLOBAL), VAR_GLOBAL);
E 9
I 9
D 11
	Var_Append ("MFLAGS", Var_Value(MAKEFLAGS, VAR_GLOBAL), VAR_GLOBAL);
E 11
I 11
D 38
	Var_Append("MFLAGS", Var_Value(MAKEFLAGS, VAR_GLOBAL), VAR_GLOBAL);
E 38
I 38
	Var_Append("MFLAGS", Var_Value(MAKEFLAGS, VAR_GLOBAL, &p1), VAR_GLOBAL);
	if (p1)
	    free(p1);
E 38
E 11
E 9

D 9
    /*
     * Install all the flags into the PMAKE envariable.
     */
E 9
I 9
D 15
	/* Install all the flags into the PMAKE envariable. */
E 15
I 15
	/* Install all the flags into the MAKE envariable. */
I 17
D 30
	if ((p = Var_Value(MAKEFLAGS, VAR_GLOBAL)) && *p)
E 30
I 30
D 38
	if (((p = Var_Value(MAKEFLAGS, VAR_GLOBAL)) != NULL) && *p)
E 38
I 38
	if (((p = Var_Value(MAKEFLAGS, VAR_GLOBAL, &p1)) != NULL) && *p)
E 38
E 30
E 17
E 15
E 9
#ifdef POSIX
D 9
    setenv("MAKEFLAGS", Var_Value(MAKEFLAGS, VAR_GLOBAL));
E 9
I 9
D 17
	setenv("MAKEFLAGS", Var_Value(MAKEFLAGS, VAR_GLOBAL));
E 17
I 17
		setenv("MAKEFLAGS", p, 1);
E 17
E 9
#else
D 9
    setenv("PMAKE", Var_Value(MAKEFLAGS, VAR_GLOBAL));
E 9
I 9
D 15
	setenv("PMAKE", Var_Value(MAKEFLAGS, VAR_GLOBAL));
E 15
I 15
D 17
	setenv("MAKE", Var_Value(MAKEFLAGS, VAR_GLOBAL));
E 17
I 17
		setenv("MAKE", p, 1);
E 17
E 15
E 9
#endif
I 38
	if (p1)
	    free(p1);
E 38

D 9
    /*
     * For compatibility, look at the directories in the VPATH variable
     * and add them to the search path, if the variable is defined. The
     * variable's value is in the same format as the PATH envariable, i.e.
     * <directory>:<directory>:<directory>...
     */
    if (Var_Exists ("VPATH", VAR_CMD)) {
	char	  *vpath;
	char	  *path;
	char  	  *cp;
	char  	  savec;
	static char VPATH[] = "${VPATH}";   /* GCC stores string constants in
					     * read-only memory, but Var_Subst
					     * will want to write this thing,
					     * so store it in an array */
	
	vpath = Var_Subst (VPATH, VAR_CMD, FALSE);

	path = vpath;
	do {
	    /*
	     * Skip to end of directory
	     */
	    for (cp = path; *cp != ':' && *cp != '\0'; cp++) {
		continue;
	    }
	    /*
	     * Save terminator character to figure out when to stop
	     */
	    savec = *cp;
	    *cp = '\0';
	    /*
	     * Add directory to search path
	     */
	    Dir_AddDir (dirSearchPath, path);
	    *cp = savec;
	    path = cp + 1;
	} while (savec == ':');
	free((Address)vpath);
    }
	    
    /*
     * Now that all search paths have been read for suffixes et al, it's
     * time to add the default search path to their lists...
     */
    Suff_DoPaths();

    /*
     * Print the initial graph, if the user requested it
     */
    if (printGraph & 1) {
	Targ_PrintGraph (1);
    }
D 8

    Rmt_Init();
E 8

    /*
     * Have now read the entire graph and need to make a list of targets to
     * create. If none was given on the command line, we consult the parsing
     * module to find the main target(s) to create.
     */
    if (Lst_IsEmpty (create)) {
	targs = Parse_MainName ();
    } else {
	targs = Targ_FindList (create, TARG_CREATE);
    }

    if (!amMake) {
E 9
	/*
D 9
	 * Initialize job module before traversing the graph, now that any
	 * .BEGIN and .END targets have been read. This is done only if the
	 * -q flag wasn't given (to prevent the .BEGIN from being executed
	 * should it exist).
E 9
I 9
	 * For compatibility, look at the directories in the VPATH variable
	 * and add them to the search path, if the variable is defined. The
	 * variable's value is in the same format as the PATH envariable, i.e.
	 * <directory>:<directory>:<directory>...
E 9
	 */
D 9
	if (!queryFlag) {
	    if (maxLocal == -1) {
		maxLocal = maxJobs;
	    }
	    Job_Init (maxJobs, maxLocal);
	    jobsRunning = TRUE;
E 9
I 9
D 11
	if (Var_Exists ("VPATH", VAR_CMD)) {
E 11
I 11
	if (Var_Exists("VPATH", VAR_CMD)) {
E 11
		char *vpath, *path, *cp, savec;
		/*
		 * GCC stores string constants in read-only memory, but
		 * Var_Subst will want to write this thing, so store it
		 * in an array
		 */
		static char VPATH[] = "${VPATH}";

D 11
		vpath = Var_Subst (VPATH, VAR_CMD, FALSE);
E 11
I 11
D 30
		vpath = Var_Subst(VPATH, VAR_CMD, FALSE);
E 30
I 30
		vpath = Var_Subst(NULL, VPATH, VAR_CMD, FALSE);
E 30
E 11
		path = vpath;
		do {
			/* skip to end of directory */
D 11
			for (cp = path; *cp != ':' && *cp != '\0'; cp++) {
				continue;
			}
E 11
I 11
D 30
			for (cp = path; *cp != ':' && *cp != '\0'; cp++);
E 30
I 30
			for (cp = path; *cp != ':' && *cp != '\0'; cp++)
				continue;
E 30
E 11
			/* Save terminator character so know when to stop */
			savec = *cp;
			*cp = '\0';
			/* Add directory to search path */
			Dir_AddDir(dirSearchPath, path);
			*cp = savec;
			path = cp + 1;
		} while (savec == ':');
		(void)free((Address)vpath);
E 9
	}
D 9
	
E 9
I 9

E 9
	/*
D 9
	 * Traverse the graph, checking on all the targets 
E 9
I 9
	 * Now that all search paths have been read for suffixes et al, it's
	 * time to add the default search path to their lists...
E 9
	 */
D 9
	outOfDate = Make_Run (targs);
    } else {
E 9
I 9
	Suff_DoPaths();

D 14
	/* Print the initial graph, if the user requested it */
	if (printGraph & 1)
E 14
I 14
	/* print the initial graph, if the user requested it */
	if (DEBUG(GRAPH1))
E 14
		Targ_PrintGraph(1);

E 9
	/*
D 9
	 * Compat_Init will take care of creating all the targets as well
	 * as initializing the module.
E 9
I 9
	 * Have now read the entire graph and need to make a list of targets
	 * to create. If none was given on the command line, we consult the
	 * parsing module to find the main target(s) to create.
E 9
	 */
D 9
	Compat_Run(targs);
    }
E 9
I 9
	if (Lst_IsEmpty(create))
		targs = Parse_MainName();
	else
D 11
		targs = Targ_FindList (create, TARG_CREATE);
E 11
I 11
		targs = Targ_FindList(create, TARG_CREATE);
E 11

D 10
	if (!amMake) {
E 10
I 10
/*
 * this was original amMake -- want to allow parallelism, so put this
 * back in, eventually.
 */
D 30
	if (0) {
E 30
I 30
	if (!compatMake) {
E 30
E 10
		/*
		 * Initialize job module before traversing the graph, now that
		 * any .BEGIN and .END targets have been read.  This is done
		 * only if the -q flag wasn't given (to prevent the .BEGIN from
		 * being executed should it exist).
		 */
		if (!queryFlag) {
			if (maxLocal == -1)
				maxLocal = maxJobs;
D 11
			Job_Init (maxJobs, maxLocal);
E 11
I 11
			Job_Init(maxJobs, maxLocal);
E 11
			jobsRunning = TRUE;
		}

		/* Traverse the graph, checking on all the targets */
		outOfDate = Make_Run(targs);
	} else
		/*
		 * Compat_Init will take care of creating all the targets as
		 * well as initializing the module.
		 */
		Compat_Run(targs);
E 9
    
I 38
	Lst_Destroy(targs, NOFREE);
	Lst_Destroy(makefiles, NOFREE);
	Lst_Destroy(create, (void (*) __P((ClientData))) free);

E 38
D 9
    /*
     * Print the graph now it's been processed if the user requested it
     */
    if (printGraph & 2) {
	Targ_PrintGraph (2);
    }
E 9
I 9
D 14
	/* Print the graph now it's been processed if the user requested it */
	if (printGraph & 2)
E 14
I 14
	/* print the graph now it's been processed if the user requested it */
	if (DEBUG(GRAPH2))
E 14
		Targ_PrintGraph(2);
E 9

I 38
	Suff_End();
        Targ_End();
	Arch_End();
	str_end();
	Var_End();
	Parse_End();
	Dir_End();

E 38
D 9
    if (queryFlag && outOfDate) {
	exit (1);
    } else {
	exit (0);
    }
E 9
I 9
	if (queryFlag && outOfDate)
D 11
		exit (1);
E 11
I 11
D 30
		exit(1);
E 30
I 30
		return(1);
E 30
E 11
	else
D 30
		exit(0);
E 30
I 30
		return(0);
E 30
E 9
}
D 4

E 4
I 4

E 4
/*-
D 9
 *-----------------------------------------------------------------------
E 9
 * ReadMakefile  --
 *	Open and parse the given makefile.
 *
 * Results:
 *	TRUE if ok. FALSE if couldn't open file.
 *
 * Side Effects:
 *	lots
D 9
 *-----------------------------------------------------------------------
E 9
 */
static Boolean
D 9
ReadMakefile (fname)
    char          *fname;     /* makefile to read */
E 9
I 9
ReadMakefile(fname)
	char *fname;		/* makefile to read */
E 9
{
I 13
	extern Lst parseIncPath, sysIncPath;
	FILE *stream;
	char *name, path[MAXPATHLEN + 1];

E 13
D 9
    if (strcmp (fname, "-") == 0) {
	Parse_File ("(stdin)", stdin);
	Var_Set("MAKEFILE", "", VAR_GLOBAL);
	return (TRUE);
    } else {
	FILE *	  stream;
	extern Lst parseIncPath, sysIncPath;
	
	stream = fopen (fname, "r");
    
	if (stream == (FILE *) NULL) {
	    /*
	     * Look in -I directories...
	     */
	    char    *name = Dir_FindFile(fname, parseIncPath);
E 9
I 9
D 10
	if (strcmp (fname, "-") == 0) {
E 10
I 10
D 11
	if (!strcmp (fname, "-")) {
E 11
I 11
	if (!strcmp(fname, "-")) {
E 11
E 10
		Parse_File("(stdin)", stdin);
		Var_Set("MAKEFILE", "", VAR_GLOBAL);
	} else {
I 18
D 30
		if (stream = fopen(fname, "r"))
E 30
I 30
		if ((stream = fopen(fname, "r")) != NULL)
E 30
			goto found;
E 18
D 13
		extern Lst parseIncPath, sysIncPath;
		FILE *stream;
E 9

D 9
	    if (name == NULL) {
E 9
I 9
		stream = fopen(fname, "r");
		if (stream == (FILE *) NULL) {
			/* Look in -I directories... */
			char *name;

			name = Dir_FindFile(fname, parseIncPath);
			if (name == NULL) {
				/*
				 * Last-ditch: look in system include
				 * directories.
				 */
				name = Dir_FindFile(fname, sysIncPath);
				if (name == NULL)
					return(FALSE);
			}
			stream = fopen(name, "r");
			if (stream == (FILE *)NULL)
				/* Better safe than sorry... */
E 13
I 13
		/* if we've chdir'd, rebuild the path name */
D 37
		if (curdir && *fname != '/') {
E 37
I 37
		if (curdir != objdir && *fname != '/') {
E 37
			(void)sprintf(path, "%s/%s", curdir, fname);
D 18
			fname = path;
E 18
I 18
D 30
			if (stream = fopen(path, "r")) {
E 30
I 30
			if ((stream = fopen(path, "r")) != NULL) {
E 30
				fname = path;
				goto found;
			}
E 18
		}
D 18
		if (!(stream = fopen(fname, "r"))) {
			/* look in -I and system include directories. */
			if (!(name = Dir_FindFile(fname, parseIncPath)) &&
			    !(name = Dir_FindFile(fname, sysIncPath)) ||
			    !(stream = fopen(name, "r")))
E 13
				return(FALSE);
			fname = name;
		}
E 18
I 18
		/* look in -I and system include directories. */
		name = Dir_FindFile(fname, parseIncPath);
		if (!name)
			name = Dir_FindFile(fname, sysIncPath);
		if (!name || !(stream = fopen(name, "r")))
			return(FALSE);
		fname = name;
E 18
E 9
		/*
D 9
		 * Last-ditch: look in system include directories.
E 9
I 9
D 13
		 * Set the MAKEFILE variable desired by System V fans -- the
		 * placement of the setting here means it gets set to the
		 * last makefile specified, as it is set by SysV make...
E 13
I 13
		 * set the MAKEFILE variable desired by System V fans -- the
		 * placement of the setting here means it gets set to the last
		 * makefile specified, as it is set by SysV make.
E 13
E 9
		 */
D 9
		name = Dir_FindFile(fname, sysIncPath);
		if (name == NULL) {
		    return (FALSE);
		}
	    }
	    stream = fopen(name, "r");
	    if (stream == (FILE *)NULL) {
		/* Better safe than sorry... */
		return(FALSE);
	    }
	    fname = name;
E 9
I 9
D 18
		Var_Set("MAKEFILE", fname, VAR_GLOBAL);
E 18
I 18
found:		Var_Set("MAKEFILE", fname, VAR_GLOBAL);
E 18
		Parse_File(fname, stream);
		(void)fclose(stream);
E 9
	}
D 9
	/*
	 * Set the MAKEFILE variable desired by System V fans -- the placement
	 * of the setting here means it gets set to the last makefile
	 * specified, as it is set by SysV make...
	 */
	Var_Set("MAKEFILE", fname, VAR_GLOBAL);
	Parse_File (fname, stream);
	fclose (stream);
	return (TRUE);
    }
E 9
I 9
	return(TRUE);
E 9
}
D 4

E 4
I 4

E 4
/*-
D 9
 *-----------------------------------------------------------------------
E 9
 * Error --
D 10
 *	Print an error message given its format and 0, 1, 2 or 3 arguments.
E 10
I 10
 *	Print an error message given its format.
E 10
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The message is printed.
D 9
 *
 *-----------------------------------------------------------------------
E 9
 */
D 10
/*VARARGS1*/
E 10
I 10
/* VARARGS */
E 10
void
D 9
Error (fmt, arg1, arg2, arg3)
    char    	  *fmt;	    	    /* Format string */
    int	    	  arg1,	    	    /* First optional argument */
		  arg2,	    	    /* Second optional argument */
		  arg3;	    	    /* Third optional argument */
E 9
I 9
D 10
Error(fmt, arg1, arg2, arg3)
	char *fmt;			/* format string */
	int arg1, arg2, arg3;		/* optional arguments */
E 10
I 10
D 30
Error(va_alist)
E 30
I 30
#if __STDC__
D 38
Error(const char *fmt, ...)
E 38
I 38
Error(char *fmt, ...)
E 38
#else
D 37
Error(fmt, va_alist)
	char *fmt;
E 37
I 37
Error(va_alist)
E 37
E 30
	va_dcl
I 30
#endif
E 30
E 10
E 9
{
D 9
    static char   estr[BSIZE];	    /* output string */
E 9
I 9
D 10
	static char estr[BSIZE];	/* output string */
E 10
I 10
	va_list ap;
D 30
	char *fmt;
E 10
E 9

E 30
I 30
#if __STDC__
	va_start(ap, fmt);
#else
I 37
	char *fmt;

E 37
E 30
D 9
    sprintf (estr, "%s: ", Var_Value(".PMAKE", VAR_GLOBAL));
    sprintf (&estr[strlen (estr)], fmt, arg1, arg2, arg3);
    (void) strcat (estr, "\n");

    fputs (estr, stderr);
    fflush (stderr);
E 9
I 9
D 10
	(void)sprintf(estr, "%s: ", Var_Value(".PMAKE", VAR_GLOBAL));
	(void)sprintf(&estr[strlen(estr)], fmt, arg1, arg2, arg3);
	(void)strcat(estr, "\n");
	(void)fputs(estr, stderr);
E 10
I 10
	va_start(ap);
I 37
	fmt = va_arg(ap, char *);
E 37
D 30
	fmt = va_arg(ap, char *);
E 30
I 30
#endif
E 30
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 10
	(void)fflush(stderr);
E 9
}
D 4

E 4
I 4

E 4
/*-
D 9
 *-----------------------------------------------------------------------
E 9
 * Fatal --
 *	Produce a Fatal error message. If jobs are running, waits for them
 *	to finish.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The program exits
D 9
 *-----------------------------------------------------------------------
E 9
 */
D 10
/* VARARGS1 */
E 10
I 10
/* VARARGS */
E 10
void
D 9
Fatal (fmt, arg1, arg2)
    char          *fmt;	      	  /* format string */
    int           arg1;	      	  /* first optional argument */
    int           arg2;	      	  /* second optional argument */
E 9
I 9
D 10
Fatal(fmt, arg1, arg2)
	char *fmt;		/* format string */
	int arg1, arg2;		/* optional arguments */
E 10
I 10
D 30
Fatal(va_alist)
E 30
I 30
#if __STDC__
D 38
Fatal(const char *fmt, ...)
E 38
I 38
Fatal(char *fmt, ...)
E 38
#else
D 37
Fatal(fmt, va_alist)
	char *fmt;
E 37
I 37
Fatal(va_alist)
E 37
E 30
	va_dcl
I 30
#endif
E 30
E 10
E 9
{
I 11
	va_list ap;
D 30
	char *fmt;

E 30
I 30
#if __STDC__
	va_start(ap, fmt);
#else
I 37
	char *fmt;

E 37
	va_start(ap);
I 37
	fmt = va_arg(ap, char *);
E 37
#endif
E 30
E 11
D 9
    if (jobsRunning) {
	Job_Wait();
    }
E 9
I 9
	if (jobsRunning)
		Job_Wait();
E 9
D 11
    
D 9
    Error (fmt, arg1, arg2);
E 9
I 9
D 10
	Error(fmt, arg1, arg2);
E 10
I 10
	Error(va_alist);
E 11
E 10
E 9

I 11
D 30
	va_start(ap);
	fmt = va_arg(ap, char *);
E 30
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	(void)fflush(stderr);

E 11
D 9
    if (printGraph & 2) {
	Targ_PrintGraph(2);
    }
    exit (2);			/* Not 1 so -q can distinguish error */
E 9
I 9
D 14
	if (printGraph & 2)
E 14
I 14
	if (DEBUG(GRAPH2))
E 14
		Targ_PrintGraph(2);
	exit(2);		/* Not 1 so -q can distinguish error */
E 9
}
D 4

E 4
I 4

E 4
/*
D 9
 *-----------------------------------------------------------------------
E 9
 * Punt --
 *	Major exception once jobs are being created. Kills all jobs, prints
 *	a message and exits.
 *
 * Results:
 *	None 
 *
 * Side Effects:
 *	All children are killed indiscriminately and the program Lib_Exits
D 9
 *-----------------------------------------------------------------------
E 9
 */
D 10
/* VARARGS1 */
E 10
I 10
/* VARARGS */
E 10
void
D 9
Punt (fmt, arg1, arg2)
    char          *fmt;	/* format string */
    int           arg1;	/* optional argument */
    int	    	  arg2;	/* optional second argument */
E 9
I 9
D 10
Punt(fmt, arg1, arg2)
	char *fmt;		/* format string */
	int arg1, arg2;		/* optional arguments */
E 10
I 10
D 30
Punt(va_alist)
E 30
I 30
#if __STDC__
D 38
Punt(const char *fmt, ...)
E 38
I 38
Punt(char *fmt, ...)
E 38
#else
D 37
Punt(fmt, va_alist)
	char *fmt;
E 37
I 37
Punt(va_alist)
E 37
E 30
	va_dcl
I 30
#endif
E 30
E 10
E 9
{
D 9
    Error (fmt, arg1, arg2);

    DieHorribly();
E 9
I 9
D 10
	Error(fmt, arg1, arg2);
E 10
I 10
D 11
	Error(va_alist);
E 11
I 11
	va_list ap;
D 30
	char *fmt;

I 17
	(void)fprintf(stderr, "make: ");
E 30
I 30
#if __STDC__
	va_start(ap, fmt);
#else
I 37
	char *fmt;

E 37
E 30
E 17
	va_start(ap);
I 37
	fmt = va_arg(ap, char *);
E 37
D 30
	fmt = va_arg(ap, char *);
E 30
I 30
#endif
I 37

E 37
	(void)fprintf(stderr, "make: ");
E 30
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	(void)fflush(stderr);

E 11
E 10
	DieHorribly();
E 9
}
D 4

E 4
I 4

E 4
/*-
D 9
 *-----------------------------------------------------------------------
E 9
 * DieHorribly --
 *	Exit without giving a message.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	A big one...
D 9
 *-----------------------------------------------------------------------
E 9
 */
void
DieHorribly()
{
D 9
    if (jobsRunning) {
	Job_AbortAll ();
    }
    if (printGraph & 2) {
	Targ_PrintGraph(2);
    }
    
    exit (2);			/* Not 1, so -q can distinguish error */
E 9
I 9
	if (jobsRunning)
		Job_AbortAll();
D 14
	if (printGraph & 2)
E 14
I 14
	if (DEBUG(GRAPH2))
E 14
		Targ_PrintGraph(2);
	exit(2);		/* Not 1, so -q can distinguish error */
E 9
}
D 4

E 4
I 4

E 4
/*
D 9
 *-----------------------------------------------------------------------
E 9
 * Finish --
 *	Called when aborting due to errors in child shell to signal
 *	abnormal exit. 
 *
 * Results:
 *	None 
 *
 * Side Effects:
 *	The program exits
D 9
 * -----------------------------------------------------------------------
E 9
 */
void
D 9
Finish (errors)
    int             errors;	/* number of errors encountered in Make_Make */
E 9
I 9
Finish(errors)
	int errors;	/* number of errors encountered in Make_Make */
E 9
{
D 9
    Fatal ("%d error%s", errors, errors == 1 ? "" : "s");
E 9
I 9
	Fatal("%d error%s", errors, errors == 1 ? "" : "s");
I 10
}

I 13
/*
 * emalloc --
 *	malloc, but die on error.
 */
char *
emalloc(len)
D 38
	u_int len;
E 38
I 38
	size_t len;
E 38
{
D 24
	extern int errno;
E 24
D 30
	char *p, *malloc();
E 30
I 30
	char *p;
E 30

D 38
	if (!(p = malloc(len)))
E 38
I 38
	if ((p = (char *) malloc(len)) == NULL)
E 38
		enomem();
	return(p);
}

/*
 * enomem --
 *	die when out of memory.
 */
I 30
void
E 30
enomem()
{
	(void)fprintf(stderr, "make: %s.\n", strerror(errno));
	exit(2);
}

/*
 * usage --
 *	exit with usage message
 */
I 30
static void
E 30
E 13
usage()
{
	(void)fprintf(stderr,
D 14
"usage: make [-PSWeiknqrstvh] [-D define] [-I include] [-J max_target] \n\t\
[-L max_local] [-d debug] [-f file] [-p #]\n");
E 14
I 14
D 19
"usage: make [-eiknqrstv] [-D variable] [-d flags] [-f makefile ]\n\t\
E 19
I 19
D 25
"usage: make [-eiknqrst] [-D variable] [-d flags] [-f makefile ]\n\t\
E 19
[-I directory] [-j max_jobs] [variable=value]\n");
E 25
I 25
"usage: make [-eiknqrst] [-D variable] [-d flags] [-f makefile ]\n\
            [-I directory] [-j max_jobs] [variable=value]\n");
E 25
E 14
	exit(2);
I 38
}


int
PrintAddr(a, b)
    ClientData a;
    ClientData b;
{
    printf("%lx ", (unsigned long) a);
    return b ? 0 : 0;
E 38
E 10
E 9
}
D 6

#if defined(SYSV) || defined(is68k) && !defined(PROF)

exit(status)
{
D 4
    if (lockSet) {
	MainUnlock();
    }
E 4
    _cleanup();
    _exit(status);
}
#endif /* System V */
E 6
E 1
