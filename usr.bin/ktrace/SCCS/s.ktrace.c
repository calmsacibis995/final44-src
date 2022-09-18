h17028
s 00026/00020/00130
d D 8.2 95/04/28 16:21:26 bostic 11 10
c ktrace is a kernel option, but the ktrace app reacts badly when it
c isn't compiled into the kernel.  also some knf changes.
c From: Adam Glass <glass@NetBSD.ORG>
e
s 00005/00005/00145
d D 8.1 93/06/06 14:53:19 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00149
d D 5.4 92/04/15 17:30:33 marc 9 8
c inherit flag wasen't set to zero after it was moved out of bss.  i don't know what was wrong wit it being bss, but oh well...
e
s 00002/00001/00148
d D 5.3 92/04/15 17:25:49 marc 8 7
c by default, not ALL trace points are enabled -- only a default set
e
s 00001/00000/00148
d D 5.2 91/03/05 19:17:50 marc 7 6
c -C was broken.
e
s 00094/00065/00054
d D 5.1 91/01/17 17:30:01 bostic 6 5
c KNF, lint, document all options, make man page consistent
e
s 00010/00020/00109
d D 1.5 90/06/29 00:37:27 marc 5 4
c textual change (facs -> trpoints)
e
s 00050/00036/00079
d D 1.4 90/03/07 16:15:10 marc 4 3
c reformating - inherit flag passed in trace flag.
e
s 00033/00019/00082
d D 1.3 88/12/21 19:04:32 marc 3 2
c changed interface, first "official" version
e
s 00021/00007/00080
d D 1.2 88/12/15 02:21:25 marc 2 1
c kernel tracing
e
s 00087/00000/00000
d D 1.1 88/12/14 16:21:49 marc 1 0
c date and time created 88/12/14 16:21:49 by marc
e
u
U
t
T
I 1
D 5
/*
E 5
I 5
/*-
E 5
D 10
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
D 10
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 6
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <sys/uio.h>
#include <sys/ktrace.h>
I 11

#include <err.h>
E 11
#include <stdio.h>
I 11
#include <unistd.h>

E 11
E 6
D 2
/*#include <time.h>*/
E 2
D 3
#include <sys/param.h>
#include <sys/file.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/ktrace.h>
#include <stdio.h>
E 3
I 3
#include "ktrace.h"
E 3

I 11
void no_ktrace __P((int));
void usage __P((void));

E 11
I 2
D 3
char	*tracefile = "trace.out";
E 3
I 3
D 6
#define USAGE \
D 4
 "usage: ktrace [-aci] [-f tracefile] [-t facilitystring] [-p pid] [-g pgid]\n\
	facilities: c = syscalls, n = namei, g = generic-i/o, a = everything\n"
E 4
I 4
D 5
 "usage: ktrace [-acid] [-f trfile] [-t trops] [-p pid] [-g pgid]\n\
E 5
I 5
 "usage: ktrace [-acid] [-f trfile] [-t trpoints] [-p pid] [-g pgid]\n\
E 5
	trops: c = syscalls, n = namei, g = generic-i/o, a = everything\n\
	ktrace -C (clear everthing)\n"
E 4
	
E 3

D 3
int	append;
E 3
I 3
char	*tracefile = DEF_TRACEFILE;
D 4
int	append, clear;
E 4
I 4
int	append, clear, descend, inherit;
E 4
E 3

E 6
E 2
main(argc, argv)
D 6
	char *argv[];
E 6
I 6
	int argc;
	char **argv;
E 6
{
D 11
	extern int optind;
	extern char *optarg;
E 11
D 2
	int ops = 0;
E 2
D 3
	int facs = KTRFAC_SYSCALL | KTRFAC_SYSRET | KTRFAC_NAMEI;
E 3
I 3
D 4
	int facs = DEF_FACS;
E 4
I 4
D 5
	int facs = ALL_FACS;
E 5
I 5
D 6
	int trpoints = ALL_POINTS;
E 5
E 4
E 3
I 2
	int ops = 0;
E 2
D 3
	int pid;
E 3
I 3
	int pid = 0;
E 3
	int ch;
E 6
I 6
	enum { NOTSET, CLEAR, CLEARALL } clear;
	int append, ch, fd, inherit, ops, pid, pidset, trpoints;
	char *tracefile;
E 6

D 2
	while ((ch = getopt(argc,argv,"cp:g:i")) != EOF)
E 2
I 2
D 3
	while ((ch = getopt(argc,argv,"acp:g:if:d")) != EOF)
E 3
I 3
D 4
	while ((ch = getopt(argc,argv,"acp:g:if:t:")) != EOF)
E 4
I 4
D 6
	while ((ch = getopt(argc,argv,"Cacdp:g:if:t:")) != EOF)
E 6
I 6
	clear = NOTSET;
D 9
	append = ops = pidset = 0;
E 9
I 9
	append = ops = pidset = inherit = 0;
E 9
D 8
	trpoints = ALL_POINTS;
E 8
I 8
	trpoints = DEF_POINTS;
E 8
	tracefile = DEF_TRACEFILE;
	while ((ch = getopt(argc,argv,"aCcdf:g:ip:t:")) != EOF)
E 6
E 4
E 3
E 2
		switch((char)ch) {
I 6
		case 'a':
			append = 1;
			break;
E 6
D 4
			case 'c':
D 3
				ops |= KTROP_CLEARFILE;
E 3
I 3
				clear = 1;
E 3
				break;
I 3
			case 't':
				facs = getfacs(optarg);
				if (facs < 0) {
					fprintf(stderr, 
					    "ktrace: unknown facility in %s\n",
				 	     optarg);
					exit(1);
				}
				break;
E 3
			case 'p':
				pid = atoi(optarg);
				break;
			case 'g':
				pid = -atoi(optarg);
				break;
			case 'i':
				ops |= KTROP_INHERITFLAG;
				break;
I 2
			case 'f':
				tracefile = optarg;
				break;
			case 'a':
				append++;
				break;
D 3
			case 'd':
				facs |= KTRFAC_GENIO;
				break;
E 3
E 2
			default:
				fprintf(stderr,"usage: \n",*argv);
				exit(-1);
E 4
I 4
		case 'C':
D 6
			clear = 2;
E 6
I 6
			clear = CLEARALL;
I 7
			pidset = 1;
E 7
E 6
			break;
		case 'c':
D 6
			clear = 1;
E 6
I 6
			clear = CLEAR;
E 6
			break;
		case 'd':
			ops |= KTRFLAG_DESCEND;
			break;
D 6
		case 't':
D 5
			facs = getfacs(optarg);
			if (facs < 0) {
E 5
I 5
			trpoints = getpoints(optarg);
			if (trpoints < 0) {
E 5
				fprintf(stderr, 
				    "ktrace: unknown facility in %s\n",
			 	     optarg);
				exit(1);
			}
E 6
I 6
		case 'f':
			tracefile = optarg;
E 6
			break;
D 6
		case 'p':
			pid = atoi(optarg);
			break;
E 6
		case 'g':
D 6
			pid = -atoi(optarg);
E 6
I 6
			pid = -rpid(optarg);
			pidset = 1;
E 6
			break;
		case 'i':
D 6
			inherit++;
E 6
I 6
			inherit = 1;
E 6
			break;
D 6
		case 'f':
			tracefile = optarg;
E 6
I 6
		case 'p':
			pid = rpid(optarg);
			pidset = 1;
E 6
			break;
D 6
		case 'a':
			append++;
E 6
I 6
		case 't':
			trpoints = getpoints(optarg);
			if (trpoints < 0) {
D 11
				(void)fprintf(stderr, 
				    "ktrace: unknown facility in %s\n", optarg);
E 11
I 11
				warnx("unknown facility in %s", optarg);
E 11
				usage();
			}
E 6
			break;
		default:
D 6
			fprintf(stderr,"usage: \n",*argv);
			exit(-1);
E 6
I 6
			usage();
E 6
E 4
		}
D 6
	argv += optind, argc -= optind;
E 6
I 6
	argv += optind;
	argc -= optind;
E 6
	
I 6
	if (pidset && *argv || !pidset && !*argv)
		usage();
			
E 6
I 4
	if (inherit)
D 5
		facs |= KTRFAC_INHERIT;
E 5
I 5
		trpoints |= KTRFAC_INHERIT;
E 5
E 4
D 3
	if ((ops&0x3) == KTROP_CLEARFILE) {
D 2
		ktrace("trace.out", ops, facs, -1);
E 2
I 2
		ktrace(tracefile, ops, facs, -1);
E 3
I 3
D 6
	if (clear) {			/* untrace something */
D 4
		ops |= pid ? KTROP_CLEAR : KTROP_CLEARFILE;
E 4
I 4
		if (clear == 2) {	/* -C */
E 6
I 6

I 11
	(void)signal(SIGSYS, no_ktrace);
E 11
	if (clear != NOTSET) {
		if (clear == CLEARALL) {
E 6
			ops = KTROP_CLEAR | KTRFLAG_DESCEND;
I 8
			trpoints = ALL_POINTS;
E 8
			pid = 1;
D 6
		} else {
E 6
I 6
		} else
E 6
			ops |= pid ? KTROP_CLEAR : KTROP_CLEARFILE;
D 6
		}
E 4
D 5
		if (ktrace(tracefile, ops, facs, pid) < 0) {
E 5
I 5
		if (ktrace(tracefile, ops, trpoints, pid) < 0) {
E 5
			perror("ktrace");
			exit(1);
		}
E 6
I 6

		if (ktrace(tracefile, ops, trpoints, pid) < 0)
D 11
			error(tracefile);
E 11
I 11
			err(1, tracefile);
E 11
E 6
E 3
E 2
		exit(0);
	}
D 2
	open("trace.out", O_WRONLY|O_CREAT, 0777);
E 2
I 2
D 3
	close(open(tracefile, O_WRONLY | O_CREAT, 0777));
E 3
I 3

D 6
	if (pid == 0 && !*argv) {	/* nothing to trace */
		fprintf(stderr, USAGE);
E 6
I 6
	if ((fd = open(tracefile, O_CREAT | O_WRONLY | (append ? 0 : O_TRUNC),
	    DEFFILEMODE)) < 0)
D 11
		error(tracefile);
E 11
I 11
		err(1, tracefile);
E 11
	(void)close(fd);

	if (*argv) { 
		if (ktrace(tracefile, ops, trpoints, getpid()) < 0)
D 11
			error();
E 11
I 11
			err(1, tracefile);
E 11
		execvp(argv[0], &argv[0]);
D 11
		error(argv[0]);
E 6
		exit(1);
E 11
I 11
		err(1, "exec of '%s' failed", argv[0]);
E 11
	}
D 6
			
	close(open(tracefile, O_WRONLY | O_CREAT, 0666));
E 3
	if (!append)
		close(open(tracefile, O_WRONLY | O_TRUNC));
E 2
	if (!*argv) {
D 2
		if (ktrace("trace.out", ops, facs, pid) < 0) {
E 2
I 2
D 5
		if (ktrace(tracefile, ops, facs, pid) < 0) {
E 5
I 5
		if (ktrace(tracefile, ops, trpoints, pid) < 0) {
E 5
E 2
			perror("ktrace");
			exit(1);
		}
	} else {
		pid = getpid();
D 2
		if (ktrace("trace.out", ops, facs, pid) < 0) {
E 2
I 2
D 5
		if (ktrace(tracefile, ops, facs, pid) < 0) {
E 5
I 5
		if (ktrace(tracefile, ops, trpoints, pid) < 0) {
E 5
E 2
			perror("ktrace");
			exit(1);
		}
		execvp(argv[0], &argv[0]);
		perror("ktrace: exec failed");
	}
E 6
I 6
	else if (ktrace(tracefile, ops, trpoints, pid) < 0)
D 11
		error(tracefile);
E 11
I 11
		err(1, tracefile);
E 11
E 6
D 3

E 3
	exit(0);
I 6
}

rpid(p)
	char *p;
{
	static int first;

	if (first++) {
D 11
		(void)fprintf(stderr,
		    "ktrace: only one -g or -p flag is permitted.\n");
E 11
I 11
		warnx("only one -g or -p flag is permitted.");
E 11
		usage();
	}
	if (!*p) {
D 11
		(void)fprintf(stderr, "ktrace: illegal process id.\n");
E 11
I 11
		warnx("illegal process id.");
E 11
		usage();
	}
	return(atoi(p));
}

D 11
error(name)
	char *name;
{
	(void)fprintf(stderr, "ktrace: %s: %s.\n", name, strerror(errno));
	exit(1);
}

E 11
I 11
void
E 11
usage()
{
	(void)fprintf(stderr,
"usage:\tktrace [-aCcid] [-f trfile] [-g pgid] [-p pid] [-t [acgn]\n\tktrace [-aCcid] [-f trfile] [-t [acgn] command\n");
	exit(1);
I 11
}

void
no_ktrace(sig)
        int sig;
{
        (void)fprintf(stderr,
"error:\tktrace() system call not supported in the running kernel\n\tre-compile kernel with 'options KTRACE'\n");
        exit(1);
E 11
E 6
}
E 1
