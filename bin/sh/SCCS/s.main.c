h61418
s 00007/00000/00324
d D 8.6 95/05/28 14:05:04 christos 15 14
c fixed FOO=1 . ./foo; echo $FOO where foo contained echo $FOO 
c I.e. variable assignments were not honored is the source command.
e
s 00002/00000/00322
d D 8.5 95/05/19 11:03:08 christos 14 13
c $ ); echo $? echoed 0,all other shells echo 2. 
c Now we set the exitstatus to 2 for all EXERROR errors. 
c Also I changed the exitstatus to 1 when a command is not found 
c to comply with historical practice.
e
s 00035/00017/00287
d D 8.4 95/05/04 17:59:54 christos 13 12
c 
e
s 00005/00004/00299
d D 8.3 95/04/27 14:19:31 bostic 12 11
c POSIX.2 (and common sense) dictates that the file specified by $ENV
c should not be sourced when running a setuid or setgid shell script.
c From: "J.T. Conklin" <jtc@sun-lamp.cs.berkeley.edu>
c NOTE: Dave Korn noted at a recent POSIX meeting that ENV should be ignored
c for all scripts, so this is likely to go further in the near future.
e
s 00028/00003/00275
d D 8.2 95/04/27 14:13:29 bostic 11 10
c POSIX.2 requires that the shell's dot builtin do a path search
c From: "J.T. Conklin" <jtc@sun-lamp.cs.berkeley.edu>
e
s 00005/00005/00273
d D 8.1 93/05/31 15:19:34 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00004/00275
d D 5.8 92/10/15 16:36:08 marc 9 8
c minor cleanups
e
s 00001/00001/00278
d D 5.7 92/07/16 10:08:18 marc 8 6
c always source ENV (posix, and correct anyway)
e
s 00001/00001/00278
d R 5.7 92/07/16 10:03:46 marc 7 6
c always source ENV (posix)
e
s 00002/00002/00277
d D 5.6 92/07/15 16:16:35 marc 6 5
c reset numeof after any command
e
s 00010/00034/00269
d D 5.5 92/07/15 16:12:17 marc 5 4
c check for stopped jobs before exiting
e
s 00000/00002/00303
d D 5.4 92/07/15 10:01:34 marc 4 3
c always include var.h
e
s 00013/00007/00292
d D 5.3 92/06/23 18:02:22 marc 3 2
c SHINIT and ENV.  fix -I bug (only check at top level)
e
s 00001/00001/00298
d D 5.2 91/03/13 18:42:08 marc 2 1
c wrong source
e
s 00299/00000/00000
d D 5.1 91/03/07 20:27:38 bostic 1 0
c date and time created 91/03/07 20:27:38 by bostic
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 10
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 11
D 13
#include <sys/stat.h>
E 13
#include <stdio.h>
E 11
#include <signal.h>
I 13
#include <sys/stat.h>
#include <unistd.h>
E 13
#include <fcntl.h>
I 13


E 13
#include "shell.h"
#include "main.h"
#include "mail.h"
#include "options.h"
#include "output.h"
#include "parser.h"
#include "nodes.h"
I 15
#include "expand.h"
E 15
#include "eval.h"
#include "jobs.h"
#include "input.h"
#include "trap.h"
D 4
#if ATTY
E 4
#include "var.h"
I 13
#include "show.h"
E 13
D 4
#endif
E 4
#include "memalloc.h"
#include "error.h"
#include "init.h"
#include "mystring.h"
I 11
#include "exec.h"
E 11

#define PROFILE 0

int rootpid;
int rootshell;
STATIC union node *curcmd;
STATIC union node *prevcmd;
extern int errno;
#if PROFILE
short profile_buf[16384];
extern int etext();
#endif

D 13
#ifdef __STDC__
STATIC void read_profile(char *);
char *getenv(char *);
#else
STATIC void read_profile();
char *getenv();
#endif
E 13
I 13
STATIC void read_profile __P((char *));
STATIC char *find_dot_file __P((char *));
E 13

D 13

E 13
/*
 * Main routine.  We initialize things, parse the arguments, execute
 * profiles if we're a login shell, and then call cmdloop to execute
 * commands.  The setjmp call sets up the location to jump to when an
 * exception occurs.  When an exception occurs the variable "state"
 * is used to figure out how far we had gotten.
 */

D 13
main(argc, argv)  char **argv; {
E 13
I 13
int
main(argc, argv)
	int argc;
	char **argv; 
{
E 13
	struct jmploc jmploc;
	struct stackmark smark;
	volatile int state;
	char *shinit;

#if PROFILE
	monitor(4, etext, profile_buf, sizeof profile_buf, 50);
#endif
	state = 0;
	if (setjmp(jmploc.loc)) {
		/*
		 * When a shell procedure is executed, we raise the
		 * exception EXSHELLPROC to clean up before executing
		 * the shell procedure.
		 */
I 14
		if (exception == EXERROR)
			exitstatus = 2;
E 14
		if (exception == EXSHELLPROC) {
			rootpid = getpid();
			rootshell = 1;
			minusc = NULL;
			state = 3;
		} else if (state == 0 || iflag == 0 || ! rootshell)
			exitshell(2);
		reset();
D 9
#if ATTY
E 9
		if (exception == EXINT
D 9
		 && (! attyset() || equal(termval(), "emacs"))) {
#else
		if (exception == EXINT) {
E 9
I 9
#if ATTY
		 && (! attyset() || equal(termval(), "emacs"))
E 9
#endif
I 9
		 ) {
E 9
			out2c('\n');
			flushout(&errout);
		}
		popstackmark(&smark);
		FORCEINTON;				/* enable interrupts */
		if (state == 1)
			goto state1;
		else if (state == 2)
			goto state2;
D 3
		else
E 3
I 3
		else if (state == 3)
E 3
			goto state3;
I 3
		else
			goto state4;
E 3
	}
	handler = &jmploc;
#ifdef DEBUG
	opentrace();
	trputs("Shell args:  ");  trargs(argv);
#endif
	rootpid = getpid();
	rootshell = 1;
	init();
	setstackmark(&smark);
	procargs(argc, argv);
	if (argv[0] && argv[0][0] == '-') {
		state = 1;
		read_profile("/etc/profile");
state1:
		state = 2;
		read_profile(".profile");
D 3
	} else if ((sflag || minusc) && (shinit = getenv("SHINIT")) != NULL) {
		state = 2;
		evalstring(shinit);
	}
E 3
I 3
	} 
E 3
state2:
	state = 3;
I 3
D 8
	if ((sflag || minusc) && (shinit = lookupvar("ENV")) != NULL &&
E 8
I 8
D 12
	if ((shinit = lookupvar("ENV")) != NULL &&
E 8
	     *shinit != '\0') {
		state = 3;
		read_profile(shinit);
E 12
I 12
	if (getuid() == geteuid() && getgid() == getegid()) {
		if ((shinit = lookupvar("ENV")) != NULL && *shinit != '\0') {
			state = 3;
			read_profile(shinit);
		}
E 12
	}
state3:
	state = 4;
E 3
	if (minusc) {
		evalstring(minusc);
	}
	if (sflag || minusc == NULL) {
D 3
state3:
E 3
I 3
state4:	/* XXX ??? - why isn't this before the "if" statement */
E 3
		cmdloop(1);
	}
#if PROFILE
	monitor(0);
#endif
	exitshell(exitstatus);
I 13
	/*NOTREACHED*/
	return 0;
E 13
}


/*
 * Read and execute commands.  "Top" is nonzero for the top level command
 * loop; it turns on prompting if the shell is interactive.
 */

void
D 13
cmdloop(top) {
E 13
I 13
cmdloop(top) 
	int top;
{
E 13
	union node *n;
	struct stackmark smark;
	int inter;
D 6
	int numeof;
E 6
I 6
	int numeof = 0;
E 6

	TRACE(("cmdloop(%d) called\n", top));
	setstackmark(&smark);
D 6
	numeof = 0;
E 6
	for (;;) {
		if (pendingsigs)
			dotrap();
		inter = 0;
		if (iflag && top) {
			inter++;
			showjobs(1);
			chkmail(0);
			flushout(&output);
		}
		n = parsecmd(inter);
D 5
#ifdef DEBUG
D 2
		/* BROKEN - FIX showtree(n); */
E 2
I 2
		/* showtree(n); */
E 2
#endif
E 5
I 5
		/* showtree(n); DEBUG */
E 5
		if (n == NEOF) {
D 3
			if (Iflag == 0 || numeof >= 50)
E 3
I 3
D 5
			if (Iflag == 0 || !top || numeof >= 50)
E 5
I 5
			if (!top || numeof >= 50)
E 5
E 3
				break;
D 5
			out2str("\nUse \"exit\" to leave shell.\n");
E 5
I 5
			if (!stoppedjobs()) {
				if (!Iflag)
					break;
				out2str("\nUse \"exit\" to leave shell.\n");
			}
E 5
			numeof++;
		} else if (n != NULL && nflag == 0) {
D 5
			if (inter) {
				INTOFF;
				if (prevcmd)
					freefunc(prevcmd);
				prevcmd = curcmd;
				curcmd = copyfunc(n);
				INTON;
			}
E 5
I 5
			job_warning = (job_warning == 2) ? 1 : 0;
I 6
			numeof = 0;
E 6
E 5
			evaltree(n, 0);
D 5
#ifdef notdef
			if (exitstatus)				      /*DEBUG*/
				outfmt(&errout, "Exit status 0x%X\n", exitstatus);
#endif
E 5
		}
		popstackmark(&smark);
	}
	popstackmark(&smark);		/* unnecessary */
}



/*
 * Read /etc/profile or .profile.  Return on error.
 */

STATIC void
read_profile(name)
	char *name;
	{
	int fd;

	INTOFF;
	if ((fd = open(name, O_RDONLY)) >= 0)
		setinputfd(fd, 1);
	INTON;
	if (fd < 0)
		return;
	cmdloop(0);
	popfile();
}



/*
 * Read a file containing shell functions.
 */

void
readcmdfile(name)
	char *name;
D 13
	{
E 13
I 13
{
E 13
	int fd;

	INTOFF;
	if ((fd = open(name, O_RDONLY)) >= 0)
		setinputfd(fd, 1);
	else
		error("Can't open %s", name);
	INTON;
	cmdloop(0);
	popfile();
}



/*
 * Take commands from a file.  To be compatable we should do a path
D 11
 * search for the file, but a path search doesn't make any sense.
E 11
I 11
 * search for the file, which is necessary to find sub-commands.
E 11
 */

I 11

D 13
static char *
find_dot_file(basename) char *basename; {
E 13
I 13
STATIC char *
find_dot_file(basename)
	char *basename;
{
E 13
	static char localname[FILENAME_MAX+1];
	char *fullname;
	char *path = pathval();
	struct stat statb;

	/* don't try this for absolute or relative paths */
	if( strchr(basename, '/'))
		return basename;

	while ((fullname = padvance(&path, basename)) != NULL) {
		strcpy(localname, fullname);
		stunalloc(fullname);
		if ((stat(fullname, &statb) == 0) && S_ISREG(statb.st_mode))
			return localname;
	}
	return basename;
}

E 11
D 13
dotcmd(argc, argv)  char **argv; {
E 13
I 13
int
dotcmd(argc, argv)  
	int argc;
	char **argv; 
{
I 15
	struct strlist *sp;
E 15
E 13
	exitstatus = 0;
I 15

	for (sp = cmdenviron; sp ; sp = sp->next)
		setvareq(savestr(sp->text), VSTRFIXED|VTEXTFIXED);

E 15
	if (argc >= 2) {		/* That's what SVR2 does */
D 11
		setinputfile(argv[1], 1);
		commandname = argv[1];
E 11
I 11
		char *fullname = find_dot_file(argv[1]);
I 15

E 15
		setinputfile(fullname, 1);
		commandname = fullname;
E 11
		cmdloop(0);
		popfile();
	}
	return exitstatus;
}


D 13
exitcmd(argc, argv)  char **argv; {
E 13
I 13
int
exitcmd(argc, argv)  
	int argc;
	char **argv; 
{
E 13
I 5
	if (stoppedjobs())
D 13
		return;
E 13
I 13
		return 0;
E 13
E 5
	if (argc > 1)
		exitstatus = number(argv[1]);
	exitshell(exitstatus);
I 13
	/*NOTREACHED*/
	return 0;
E 13
}
D 5


lccmd(argc, argv)  char **argv; {
	if (argc > 1) {
		defun(argv[1], prevcmd);
		return 0;
	} else {
		INTOFF;
		freefunc(curcmd);
		curcmd = prevcmd;
		prevcmd = NULL;
		INTON;
		evaltree(curcmd, 0);
		return exitstatus;
	}
}

E 5


#ifdef notdef
/*
 * Should never be called.
 */

void
exit(exitstatus) {
	_exit(exitstatus);
}
#endif
E 1
