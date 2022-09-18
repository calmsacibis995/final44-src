h37800
s 00069/00026/00092
d D 8.4 95/04/28 10:07:04 bostic 20 19
c POSIX.2 compliance
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00116
d D 8.3 94/04/02 09:56:01 pendry 19 18
c add 1994 copyright
e
s 00007/00006/00111
d D 8.2 94/04/01 01:58:30 pendry 18 17
c prettyness police
e
s 00005/00005/00112
d D 8.1 93/05/31 14:38:20 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00115
d D 5.8 93/05/15 11:34:09 ralph 16 15
c fix pointer type to match sys_signame type.
e
s 00011/00015/00106
d D 5.7 93/04/29 12:21:24 bostic 15 14
c use err/warn(3), lint for 4.4BSD freeze
e
s 00002/00002/00119
d D 5.6 93/03/15 09:59:05 torek 14 13
c quiet down the warnings
e
s 00003/00004/00118
d D 5.5 91/08/04 14:12:45 bostic 13 12
c put signal names into C library (gen/siglist.c); missed one
e
s 00011/00012/00111
d D 5.4 91/08/02 11:50:16 bostic 12 11
c put signal names into C library (gen/siglist.c)
e
s 00001/00001/00122
d D 5.3 91/07/01 13:03:29 bostic 11 10
c 29 is now SIGINFO
e
s 00001/00001/00122
d D 5.2 91/06/19 16:56:59 bostic 10 9
c typo
e
s 00040/00024/00083
d D 5.1 91/06/17 16:22:53 bostic 9 8
c minor wordsmithing; cleanup kill code for consistency and better error
c messages
e
s 00002/00002/00105
d D 4.7 91/02/25 07:39:10 bostic 8 7
c ANSI fixes
e
s 00001/00011/00106
d D 4.6 90/05/31 20:31:09 bostic 7 6
c new copyright notice
e
s 00100/00058/00017
d D 4.5 88/07/21 17:37:03 bostic 6 5
c rewritten from scratch by Steve Sellgren; add Berkeley header
e
s 00001/00001/00074
d D 4.4 86/04/20 02:26:28 lepreau 5 4
c allow negative pids to match kernel code.
e
s 00008/00008/00067
d D 4.3 85/06/07 13:51:06 serge 4 2
c updated signal names;  allow kill -0
e
s 00008/00008/00067
d R 4.3 85/02/14 15:50:38 serge 3 2
c updated signal names;  allow kill -0
e
s 00037/00003/00038
d D 4.2 80/10/10 00:48:08 bill 2 1
c kill -NMAE
e
s 00041/00000/00000
d D 4.1 80/10/01 17:27:13 bill 1 0
c date and time created 80/10/01 17:27:13 by bill
e
u
U
t
T
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 6
static	char *sccsid = "%W% (Berkeley) %G%";
E 6
E 2
/*
D 6
 * kill - send signal to process
E 6
I 6
D 17
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 17
I 17
D 19
 * Copyright (c) 1988, 1993
E 19
I 19
 * Copyright (c) 1988, 1993, 1994
E 19
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 7
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
 */

I 6
#ifndef lint
D 17
char copyright[] =
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 17
I 17
static char copyright[] =
D 19
"%Z% Copyright (c) 1988, 1993\n\
E 19
I 19
"%Z% Copyright (c) 1988, 1993, 1994\n\
E 19
	The Regents of the University of California.  All rights reserved.\n";
E 17
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 6
D 15
#include <signal.h>
E 15
I 15
#include <ctype.h>
#include <err.h>
E 15
I 9
#include <errno.h>
I 15
#include <signal.h>
E 15
E 9
I 6
#include <stdio.h>
I 8
#include <stdlib.h>
#include <string.h>
E 8
E 6
I 2
D 15
#include <ctype.h>
E 15
E 2

I 2
D 6
char *signm[] = { 0,
"HUP", "INT", "QUIT", "ILL", "TRAP", "IOT", "EMT", "FPE",	/* 1-8 */
D 4
"KILL", "BUS", "SEGV", "SYS", "PIPE", "ALRM", "TERM", 0,	/* 9-16 */
"STOP", "TSTP", "CONT", "CHLD", "TTIN", "TTOU", "TINT", "XCPU",	/* 17-24 */
"XFSZ", 0, 0, 0, 0, 0, 0, 0,					/* 25-31 */
E 4
I 4
"KILL", "BUS", "SEGV", "SYS", "PIPE", "ALRM", "TERM", "URG",	/* 9-16 */
"STOP", "TSTP", "CONT", "CHLD", "TTIN", "TTOU", "IO", "XCPU",	/* 17-24 */
"XFSZ", "VTALRM", "PROF", "WINCH", 0, "USR1", "USR2", 0,	/* 25-31 */
E 4
};
E 6
I 6
D 12
static char *signals[] = {
	"hup", "int", "quit", "ill", "trap", "iot",		/*  1 - 6  */
	"emt", "fpe", "kill", "bus", "segv", "sys",		/*  7 - 12 */
	"pipe", "alrm",  "term", "urg", "stop", "tstp",		/* 13 - 18 */
	"cont", "chld", "ttin", "ttou", "io", "xcpu",		/* 19 - 24 */
D 11
	"xfsz", "vtalrm", "prof", "winch", "29", "usr1",	/* 25 - 30 */
E 11
I 11
	"xfsz", "vtalrm", "prof", "winch", "info", "usr1",	/* 25 - 30 */
E 11
	"usr2", NULL,						/* 31 - 32 */
D 9
	};
E 9
I 9
};
E 12
I 12
void nosig __P((char *));
D 20
void printsig __P((FILE *));
E 20
I 20
void printsignals __P((FILE *));
int signame_to_signum __P((char *));
E 20
void usage __P((void));
E 12
E 9
E 6

I 15
int
E 15
E 2
main(argc, argv)
D 6
char **argv;
E 6
I 6
	int argc;
D 15
	char **argv;
E 15
I 15
	char *argv[];
E 15
E 6
{
D 6
	register signo, pid, res;
	int errlev;
	extern char *sys_errlist[];
	extern errno;
E 6
I 6
D 9
	register int numsig;
E 9
I 9
D 18
	register int errors, numsig, pid;
E 9
D 14
	register char **p;
E 14
I 14
D 16
	register char *const *p;
E 16
I 16
	register const char *const *p;
E 18
I 18
	const char *const *p;
	int errors, numsig, pid;
E 18
E 16
E 14
D 9
	int errors;
E 9
I 9
	char *ep;
E 9
E 6

D 6
	errlev = 0;
	if (argc <= 1) {
	usage:
D 2
		printf("usage: kill [ -signo ] pid ...\n");
E 2
I 2
		printf("usage: kill [ -sig ] pid ...\n");
		printf("for a list of signals: kill -l\n");
E 2
		exit(2);
E 6
I 6
	if (argc < 2)
		usage();

D 20
	if (!strcmp(*++argv, "-l")) {
D 9
		printsig();
E 9
I 9
		printsig(stdout);
E 20
I 20
	numsig = SIGTERM;

	argc--, argv++;
	if (!strcmp(*argv, "-l")) {
		argc--, argv++;
		if (argc > 1)
			usage();
		if (argc == 1) {
			if (!isdigit(**argv))
				usage();
			numsig = strtol(*argv, &ep, 10);
			if (!*argv || *ep)
				errx(1, "illegal signal number: %s", *argv);
			if (numsig >= 128)
				numsig -= 128;
			if (numsig <= 0 || numsig >= NSIG)
				nosig(*argv);
			printf("%s\n", sys_signame[numsig]);
			exit(0);
		}
		printsignals(stdout);
E 20
E 9
		exit(0);
E 6
	}
D 6
	if (*argv[1] == '-') {
D 2
		signo = atoi(argv[1]+1);
E 2
I 2
		if (argv[1][1] == 'l') {
D 4
			for (signo = 1; signo <= NSIG; signo++) {
E 4
I 4
			for (signo = 0; signo <= NSIG; signo++) {
E 4
				if (signm[signo])
					printf("%s ", signm[signo]);
				if (signo == 16)
					printf("\n");
E 6
I 6

D 20
	numsig = SIGTERM;
	if (**argv == '-') {
E 20
I 20
	if (!strcmp(*argv, "-s")) {
		argc--, argv++;
		if (argc < 1) {
			warnx("option requires an argument -- s");
			usage();
		}
		if (strcmp(*argv, "0")) {
			if ((numsig = signame_to_signum(*argv)) < 0)
				nosig(*argv);
		} else
			numsig = 0;
		argc--, argv++;
	} else if (**argv == '-') {
E 20
		++*argv;
		if (isalpha(**argv)) {
D 20
			if (!strncasecmp(*argv, "sig", 3))
				*argv += 3;
D 12
			for (p = signals;; ++p) {
E 12
I 12
D 13
			for (p = sys_signame;; ++p) {
E 12
				if (!*p)
D 9
					goto error;
E 9
I 9
					nosig(*argv);
E 13
I 13
			for (numsig = NSIG, p = sys_signame + 1; --numsig; ++p)
E 13
E 9
				if (!strcasecmp(*p, *argv)) {
D 12
					numsig = p - signals + 1;
E 12
I 12
					numsig = p - sys_signame;
E 12
					break;
				}
E 6
D 13
			}
E 13
I 13
			if (!numsig)
E 20
I 20
			if ((numsig = signame_to_signum(*argv)) < 0)
E 20
				nosig(*argv);
E 13
D 6
			printf("\n");
			exit(0);
		} else if (isdigit(argv[1][1])) {
			signo = atoi(argv[1]+1);
D 4
			if (signo < 1 || signo > NSIG) {
E 4
I 4
			if (signo < 0 || signo > NSIG) {
E 4
				printf("kill: %s: number out of range\n",
				    argv[1]);
				exit(1);
			}
		} else {
			char *name = argv[1]+1;
D 4
			for (signo = 1; signo <= NSIG; signo++)
			if (signm[signo] && !strcmp(signm[signo], name))
				goto foundsig;
E 4
I 4
			for (signo = 0; signo <= NSIG; signo++)
				if (signm[signo] && !strcmp(signm[signo], name))
					goto foundsig;
E 4
			printf("kill: %s: unknown signal; kill -l lists signals\n", name);
E 6
I 6
D 9
		}
		else if (isdigit(**argv)) {
			numsig = atoi(*argv);
E 9
I 9
		} else if (isdigit(**argv)) {
			numsig = strtol(*argv, &ep, 10);
D 15
			if (!*argv || *ep) {
				(void)fprintf(stderr,
				    "kill: illegal signal number %s\n", *argv);
				exit(1);
			}
E 15
I 15
			if (!*argv || *ep)
				errx(1, "illegal signal number: %s", *argv);
E 15
E 9
D 20
			if (numsig <= 0 || numsig > NSIG)
E 20
I 20
			if (numsig <= 0 || numsig >= NSIG)
E 20
D 9
				goto error;
		}
		else {
error:			printf("kill: unknown signal %s; valid signals:\n", *argv);
			printsig();
E 6
			exit(1);
D 6
foundsig:
			;
E 6
		}
E 9
I 9
				nosig(*argv);
		} else
			nosig(*argv);
E 9
E 2
D 6
		argc--;
		argv++;
	} else
		signo = SIGTERM;
	argv++;
	while (argc > 1) {
D 5
		if (**argv<'0' || **argv>'9')
E 5
I 5
		if (!(isdigit(**argv) || **argv == '-'))
E 5
			goto usage;
		res = kill(pid = atoi(*argv), signo);
		if (res<0) {
			printf("%u: %s\n", pid, sys_errlist[errno]);
			errlev = 1;
E 6
I 6
D 20
		++argv;
E 20
I 20
		argc--, argv++;
E 20
	}

D 20
	if (!*argv)
E 20
I 20
	if (argc == 0)
E 20
		usage();

D 20
	for (errors = 0; *argv; ++argv) {
E 20
I 20
	for (errors = 0; argc; argc--, argv++) {
E 20
D 9
		if (!isdigit(**argv))
			usage();
E 9
I 9
		pid = strtol(*argv, &ep, 10);
		if (!*argv || *ep) {
D 15
			(void)fprintf(stderr,
			    "kill: illegal process id %s\n", *argv);
			continue;
		}
E 9
D 10
		if (kill(atoi(*argv), numsig) == -1) {
E 10
I 10
		if (kill(pid, numsig) == -1) {
E 10
D 9
			perror(*argv);
E 9
I 9
			(void)fprintf(stderr,
			    "kill: %s: %s\n", *argv, strerror(errno));
E 15
I 15
			warnx("illegal process id: %s", *argv);
			errors = 1;
		} else if (kill(pid, numsig) == -1) {
			warn("%s", *argv);
E 15
E 9
			errors = 1;
E 6
		}
D 6
		argc--;
		argv++;
E 6
	}
I 20

E 20
D 6
	return(errlev);
E 6
I 6
	exit(errors);
}

I 20
int
signame_to_signum(sig)
	char *sig;
{
	int n;

	if (!strncasecmp(sig, "sig", 3))
		sig += 3;
	for (n = 1; n < NSIG; n++) {
		if (!strcasecmp(sys_signame[n], sig))
			return (n);
	}
	return (-1);
}

E 20
I 12
void
E 12
D 8
static
E 8
D 9
printsig()
E 9
I 9
nosig(name)
	char *name;
E 9
{
I 9
D 18
	(void)fprintf(stderr,
	    "kill: unknown signal %s; valid signals:\n", name);
E 18
I 18

	warnx("unknown signal %s; valid signals:", name);
E 18
D 20
	printsig(stderr);
E 20
I 20
	printsignals(stderr);
E 20
	exit(1);
}

I 12
void
E 12
D 20
printsig(fp)
E 20
I 20
printsignals(fp)
E 20
	FILE *fp;
{
I 12
D 18
	register int cnt;
E 12
E 9
D 14
	register char **p;
E 14
I 14
D 16
	register char *const *p;
E 16
I 16
	register const char *const *p;
E 18
I 18
D 20
	const char *const *p;
	int cnt;
E 20
I 20
	int n;
E 20
E 18
E 16
E 14

D 12
	for (p = signals; *p; ++p) {
E 12
I 12
D 20
	for (cnt = NSIG, p = sys_signame + 1; --cnt; ++p) {
E 12
D 9
		printf("%s ", *p);
E 9
I 9
		(void)fprintf(fp, "%s ", *p);
E 9
D 12
		if ((p - signals) == NSIG / 2 - 1)
E 12
I 12
		if (cnt == NSIG / 2)
E 20
I 20
	for (n = 1; n < NSIG; n++) {
		(void)fprintf(fp, "%s", sys_signame[n]);
		if (n == (NSIG / 2) || n == (NSIG - 1))
E 20
E 12
D 9
			printf("\n");
E 9
I 9
			(void)fprintf(fp, "\n");
I 20
		else
			(void)fprintf(fp, " ");
E 20
E 9
	}
D 9
	printf("\n");
E 9
I 9
D 20
	(void)fprintf(fp, "\n");
E 20
E 9
}

I 12
void
E 12
D 8
static
E 8
usage()
{
I 18

E 18
D 9
	printf("usage: kill [-l] [-sig] pid ...\n");
	exit(2);
E 9
I 9
D 20
	(void)fprintf(stderr, "usage: kill [-l] [-sig] pid ...\n");
E 20
I 20
	(void)fprintf(stderr, "usage: kill [-s signal_name] pid ...\n");
	(void)fprintf(stderr, "       kill -l [exit_status]\n");
	(void)fprintf(stderr, "       kill -signal_name pid ...\n");
	(void)fprintf(stderr, "       kill -signal_number pid ...\n");
E 20
	exit(1);
E 9
E 6
}
E 1
