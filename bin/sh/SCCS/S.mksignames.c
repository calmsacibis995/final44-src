h41000
s 00005/00005/00166
d D 8.1 93/05/31 15:19:55 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00171/00000/00000
d D 5.1 91/03/07 20:27:45 bostic 1 0
c date and time created 91/03/07 20:27:45 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 2
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 2
I 2
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 2
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * This program generates the signames.h and signames.c files.
 */
#include <stdio.h>
#include <signal.h>



struct sig {
	int signo;		/* signal number */
	char *name;		/* signal name (without leading "SIG") */
	char *mesg;		/* description */
};


struct sig sigtab[] = {
	SIGHUP, "HUP", "Hangup",
	SIGINT, "INT", "Interrupt",	/* normally don't print message */
	SIGQUIT, "QUIT", "Quit",
	SIGILL, "ILL", "Illegal instruction",
	SIGTRAP, "TRAP", "Trace/BPT trap",
#ifdef SIGABRT
	SIGABRT, "ABRT", "abort",
#endif
#if defined(SIGIOT) && (! defined(SIGABRT) || SIGABRT != SIGIOT)
	SIGIOT, "IOT", "abort",
#endif
#ifdef SIGEMT
	SIGEMT, "EMT", "EMT trap",
#endif
	SIGFPE, "FPE", "Floating exception",
	SIGKILL, "KILL", "Killed",
	SIGBUS, "BUS", "Bus error",
	SIGSEGV, "SEGV", "Memory fault",
	SIGSYS, "SYS", "Bad system call",
	SIGPIPE, "PIPE", "Broken pipe",	/* normally don't print message */
	SIGALRM, "ALRM", "Alarm call",
	SIGTERM, "TERM", "Terminated",
#ifdef SIGUSR1
	SIGUSR1, "USR1", "User signal 1",
#endif
#ifdef SIGUSR2
	SIGUSR2, "USR2", "User signal 2",
#endif
#ifdef SIGCLD
	SIGCLD, "CLD", NULL,
#endif
#if defined(SIGCHLD) && ! defined(SIGCLD)
	SIGCHLD, "CLD", NULL,
#endif
#ifdef SIGPWR
	SIGPWR, "PWR", "Power fail",
#endif
#ifdef SIGPOLL
	SIGPOLL, "POLL", "Poll",
#endif
	/* Now for the BSD signals */
#ifdef SIGURG
	SIGURG, "URG", NULL,
#endif
#ifdef SIGSTOP
	SIGSTOP, "STOP", "Stopped",
#endif
#ifdef SIGTSTP
	SIGTSTP, "TSTP", "Stopped",
#endif
#ifdef SIGCONT
	SIGCONT, "CONT", NULL,
#endif
#ifdef SIGTTIN
	SIGTTIN, "TTIN", "Stopped (input)",
#endif
#ifdef SIGTTOU
	SIGTTOU, "TTOU", "Stopped (output)",
#endif
#ifdef SIGIO
	SIGIO, "IO", NULL,
#endif
#ifdef SIGXCPU
	SIGXCPU, "XCPU", "Time limit exceeded",
#endif
#ifdef SIGXFSZ
	SIGXFSZ, "XFSZ", NULL,
#endif
#ifdef SIGVTALARM
	SIGVTALARM, "VTALARM", "Virtual alarm",
#endif
#ifdef SIGPROF
	SIGPROF, "PROF", "Profiling alarm",
#endif
#ifdef SIGWINCH
	SIGWINCH, "WINCH", NULL,
#endif
	0, NULL, NULL
};


#define MAXSIG 64


char *sigmesg[MAXSIG + 1];


char writer[] = "\
/*\n\
 * This file was generated by the mksignames program.\n\
 */\n\
\n";



main(argc, argv)  char **argv; {
	FILE *cfile, *hfile;	
	struct sig *sigp;
	int maxsig;
	int i;

	if ((cfile = fopen("signames.c", "w")) == NULL) {
		fputs("Can't create signames.c\n", stderr);
		exit(2);
	}
	if ((hfile = fopen("signames.h", "w")) == NULL) {
		fputs("Can't create signames.h\n", stderr);
		exit(2);
	}
	maxsig = 0;
	for (sigp = sigtab ; sigp->signo != 0 ; sigp++) {
		if (sigp->signo < 0 || sigp->signo > MAXSIG)
			continue;
		sigmesg[sigp->signo] = sigp->mesg;
		if (maxsig < sigp->signo)
			maxsig = sigp->signo;
	}

	fputs(writer, hfile);
	fprintf(hfile, "#define MAXSIG %d\n\n", maxsig);
	fprintf(hfile, "extern char *const sigmesg[MAXSIG+1];\n");

	fputs(writer, cfile);
	fprintf(cfile, "#include \"shell.h\"\n\n");
	fprintf(cfile, "char *const sigmesg[%d] = {\n", maxsig + 1);
	for (i = 0 ; i <= maxsig ; i++) {
		if (sigmesg[i] == NULL) {
			fprintf(cfile, "      0,\n");
		} else {
			fprintf(cfile, "      \"%s\",\n", sigmesg[i]);
		}
	}
	fprintf(cfile, "};\n");
	exit(0);
}
E 1
