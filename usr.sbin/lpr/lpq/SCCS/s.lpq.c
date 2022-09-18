h37012
s 00006/00003/00141
d D 8.3 95/05/10 05:58:09 bostic 20 19
c Paul Vixie tested this and found some problems.
e
s 00051/00007/00093
d D 8.2 95/04/28 12:34:11 tef 19 18
c Added -a flag.
e
s 00004/00004/00096
d D 8.1 93/06/06 14:00:32 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00099
d D 5.11 92/09/16 10:53:00 elan 17 16
c copyright[] -> static
e
s 00004/00029/00096
d D 5.10 92/09/15 10:54:00 elan 16 15
c Added SCCS keywords.
e
s 00032/00006/00093
d D 5.9 92/09/01 11:10:21 elan 15 14
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00013/00000/00086
d D 5.8 92/07/21 10:29:55 bostic 14 13
c prototype lpr to fix quad's
e
s 00000/00001/00086
d D 5.7 91/03/02 15:02:42 bostic 13 12
c ANSI
e
s 00001/00011/00086
d D 5.6 90/06/01 18:45:21 bostic 12 11
c new copyright notice
e
s 00010/00005/00087
d D 5.5 88/06/30 17:59:56 bostic 11 10
c install approved copyright notice
e
s 00010/00004/00082
d D 5.4 88/05/05 18:08:07 bostic 10 9
c written by Ralph Campbell; add Berkeley specific header
e
s 00038/00161/00048
d D 5.3 87/04/30 18:00:05 bostic 9 8
c removed '+' argument, installed getopt
e
s 00001/00000/00208
d D 5.2 85/11/17 15:53:29 eric 8 7
c clean up logging
e
s 00013/00001/00195
d D 5.1 85/06/06 10:04:14 dist 7 6
c Add copyright
e
s 00001/00000/00195
d D 4.6 84/02/29 10:50:54 ralph 6 5
c fix exit code.
e
s 00004/00001/00191
d D 4.5 83/07/17 00:11:21 sam 5 4
c put sccs id's to some use
e
s 00020/00019/00172
d D 4.4 83/06/02 12:23:18 ralph 4 3
c made local variables static to improve separation between functions.
e
s 00006/00001/00185
d D 4.3 83/05/26 09:18:43 ralph 3 2
c fixed -P option so -Pprinter and -P printer both work.
e
s 00003/00001/00183
d D 4.2 83/05/13 11:52:34 ralph 2 1
c bug fixes and changes for lpc command.
e
s 00184/00000/00000
d D 4.1 83/04/29 11:28:54 ralph 1 0
c date and time created 83/04/29 11:28:54 by ralph
e
u
U
t
T
I 7
/*
D 16
 * Copyright (c) 1983 Regents of the University of California.
E 16
I 16
D 18
 * Copyright (c) 1983 The Regents of the University of California.
E 16
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 12
I 12
D 15
 * %sccs.include.redist.c%
E 15
I 15
D 16
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 16
 *
D 16
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 16
I 16
 * %sccs.include.redist.c%
E 16
E 15
E 12
E 11
E 10
 */

E 7
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
#ifndef lint
I 7
D 17
char copyright[] =
E 17
I 17
static char copyright[] =
E 17
D 15
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 15
I 15
D 16
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
E 16
I 16
D 18
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 16
E 15
 All rights reserved.\n";
E 18
I 18
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 18
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10

#ifndef lint
E 7
D 15
static char sccsid[] = "%W% (Berkeley) %G%";
E 15
I 15
D 16
static char sccsid[] = "@(#)lpq.c	5.9 (Berkeley) 8/6/92";
E 16
I 16
static char sccsid[] = "%W% (Berkeley) %G%";
E 16
E 15
D 7
#endif
E 7
I 7
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10
E 7

E 5
/*
 * Spool Queue examination program
 *
D 9
 * lpq [+[n]] [-Pprinter] [user...] [job...]
E 9
I 9
D 19
 * lpq [-l] [-Pprinter] [user...] [job...]
E 19
I 19
 * lpq [-a] [-l] [-Pprinter] [user...] [job...]
E 19
E 9
 *
I 19
 * -a show all non-null queues on the local machine
E 19
D 9
 * + means continually scan queue until empty
E 9
I 9
 * -l long output
E 9
 * -P used to identify printer as per lpr/lprm
 */

I 14
#include <sys/param.h>

#include <syslog.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
E 14
#include "lp.h"
I 14
#include "lp.local.h"
I 19
#include "pathnames.h"
E 19
E 14

I 15
int	 requ[MAXREQUESTS];	/* job number of spool entries */
int	 requests;		/* # of spool requests */
E 15
char	*user[MAXUSERS];	/* users to process */
D 15
int	users;			/* # of users in user array */
int	requ[MAXREQUESTS];	/* job number of spool entries */
int	requests;		/* # of spool requests */
E 15
I 15
int	 users;			/* # of users in user array */
E 15

I 20
static int ckqueue __P((char *));
E 20
I 14
void usage __P((void));

int
E 14
D 4
int	repeat;			/* + flag indicator */
int	slptime = 30;		/* pause between screen refereshes */
int	lflag;			/* long output option */
E 4
I 4
D 9
static int	repeat;		/* + flag indicator */
static int	slptime = 30;	/* pause between screen refereshes */
static int	lflag;		/* long output option */
E 4

/*
 * Termcap stuff for fancy display
 */
#ifdef TERMCAP
struct sgttyb sbuf;
D 4
unsigned ospeed;
int	dumb;			/* whether to use capabilities */
char	PC;			/* pad character for output */
char	*UP;			/* up one line */
char	*BC;			/* backspace character, other than \b */
char	*CM;			/* cursor motion */
char	*CL;			/* clear display */
char	*TI;			/* terminal init for CM */
char	*TE;			/* terminal clear for CM */
char	*SO;			/* stand out start */
char	*SE;			/* stand out end */
E 4
I 4
static unsigned ospeed;
static int	dumb;		/* whether to use capabilities */
static char	PC;		/* pad character for output */
static char	*UP;		/* up one line */
static char	*BC;		/* backspace character, other than \b */
static char	*CM;		/* cursor motion */
static char	*CL;		/* clear display */
static char	*TI;		/* terminal init for CM */
static char	*TE;		/* terminal clear for CM */
static char	*SO;		/* stand out start */
static char	*SE;		/* stand out end */
E 4

char	*tgetstr();
int	putch();		/* for tputs' */
#endif

E 9
main(argc, argv)
D 9
	char *argv[];
E 9
I 9
	register int	argc;
	register char	**argv;
E 9
{
D 9
	register char *arg;
	register int n;
E 9
I 9
	extern char	*optarg;
	extern int	optind;
D 19
	int	ch, lflag;		/* long output option */
E 19
I 19
	int	ch, aflag, lflag;
	char	*buf, *cp;
E 19
E 9

I 2
D 9
	name = argv[0];
	gethostname(host, sizeof(host));
E 9
I 9
	name = *argv;
	if (gethostname(host, sizeof(host))) {
		perror("lpq: gethostname");
		exit(1);
	}
E 9
I 8
	openlog("lpd", 0, LOG_LPR);
E 8

E 2
D 9
	while (--argc) {
		if ((arg = *++argv)[0] == '+') {
			if (arg[1] != '\0')
				if ((n = atoi(&arg[1])) > 0)
					slptime = n;
			repeat++;
		} else if (arg[0] == '-')
			switch (arg[1]) {
			case 'P':		/* printer name */
D 3
				printer = &arg[2];
E 3
I 3
				if (arg[2])
					printer = &arg[2];
				else if (argc > 1) {
					argc--;
					printer = *++argv;
				}
E 3
				break;

			case 'l':		/* long output */
				lflag++;
				break;

			default:
				usage();
		} else {
			if (isdigit(arg[0])) {
				if (requests >= MAXREQUESTS)
					fatal("too many requests");
				requ[requests++] = atoi(arg);
			} else {
				if (users >= MAXUSERS)
					fatal("too many users");
				user[users++] = arg;
			}
E 9
I 9
D 19
	lflag = 0;
	while ((ch = getopt(argc, argv, "lP:")) != EOF)
E 19
I 19
	aflag = lflag = 0;
	while ((ch = getopt(argc, argv, "alP:")) != EOF)
E 19
		switch((char)ch) {
I 19
		case 'a':
			++aflag;
			break;
E 19
		case 'l':			/* long output */
			++lflag;
			break;
		case 'P':		/* printer name */
			printer = optarg;
			break;
		case '?':
		default:
			usage();
E 9
		}
D 9
	}
E 9
I 9

E 9
D 19
	if (printer == NULL && (printer = getenv("PRINTER")) == NULL)
E 19
I 19
	if (!aflag && printer == NULL && (printer = getenv("PRINTER")) == NULL)
E 19
		printer = DEFLP;
D 2
	gethostname(host, sizeof(host));
E 2
D 9
#ifdef TERMCAP
	dumb = termcap();
#endif
E 9

D 9
	if (repeat) {
#ifdef TERMCAP
		if (TI)
			tputs(TI, 0, putch);
#endif
		do {
#ifdef TERMCAP
			if (!dumb) {
				tputs(CL, 0, putch);
				tputs(tgoto(CM, 0, 0), 0, putch);
			}
#endif
			if ((n = displayq(lflag)) > 0)
				sleep(slptime);
		} while (n > 0);
#ifdef TERMCAP
		if (!dumb) {
			standout(stdout, "Hit return to continue");
			while (getchar() != '\n');
			if (TE)
				tputs(TE, 0, putch);
E 9
I 9
	for (argc -= optind, argv += optind; argc; --argc, ++argv)
		if (isdigit(argv[0][0])) {
			if (requests >= MAXREQUESTS)
				fatal("too many requests");
			requ[requests++] = atoi(*argv);
E 9
		}
D 9
#endif
	} else
		displayq(lflag);
E 9
I 9
		else {
			if (users >= MAXUSERS)
				fatal("too many users");
			user[users++] = *argv;
		}

D 19
	displayq(lflag);
E 19
I 19
	if (aflag) {
		while (cgetnext(&buf, printcapdb) > 0) {
D 20
			if (ckqueue() <= 0) {
E 20
I 20
			if (ckqueue(buf) <= 0) {
E 20
				free(buf);
				continue;	/* no jobs */
			}
			for (cp = buf; *cp; cp++)
				if (*cp == '|' || *cp == ':') {
					*cp = '\0';
					break;
				}
			printer = buf;
			printf("%s:\n", printer);
			displayq(lflag);
			free(buf);
			printf("\n");
		}
	} else
		displayq(lflag);
E 19
E 9
I 6
	exit(0);
E 6
}

I 19
D 20
ckqueue()
E 20
I 20
static int
ckqueue(cap)
	char *cap;
E 20
{
	register struct dirent *d;
	DIR *dirp;
	char *spooldir;

D 20
	if (cgetstr(bp, "sd", &spooldir) == -1)
E 20
I 20
	if (cgetstr(cap, "sd", &spooldir) == -1)
E 20
		spooldir = _PATH_DEFSPOOL;
	if ((dirp = opendir(spooldir)) == NULL)
		return (-1);
	while ((d = readdir(dirp)) != NULL) {
		if (d->d_name[0] != 'c' || d->d_name[1] != 'f')
			continue;	/* daemon control files only */
		closedir(dirp);
		return (1);		/* found something */
	}
	closedir(dirp);
	return (0);
}

E 19
I 14
void
E 14
I 4
D 13
static
E 13
E 4
usage()
{
D 9
	printf("usage: lpq [-Pprinter] [-l] [+[n]] [user...] [job...]\n");
E 9
I 9
D 19
	puts("usage: lpq [-l] [-Pprinter] [user ...] [job ...]");
E 19
I 19
	puts("usage: lpq [-a] [-l] [-Pprinter] [user ...] [job ...]");
E 19
E 9
	exit(1);
}
D 9

/*
 * If we have the capability, print this in standout mode
 */
I 4
static
E 4
standout(f, s, a1, a2)
	FILE *f;
	char *s;
{
#ifdef TERMCAP
	if (SO)
		tputs(SO, 0, putch);
	fprintf(f, s, a1, a2);
	if (SO && SE)
		tputs(SE, 0, putch);
#else
	fprintf(f, s, a1, a2);
#endif
}

#ifdef TERMCAP
D 4
char *
E 4
I 4
static char *
E 4
capstrings[] = {
	"bc", "cl", "cm", "so", "se", "ti", "te", "up",
	0
};

D 4
char **
E 4
I 4
static char **
E 4
caps[] = {
	&BC, &CL, &CM, &SO, &SE, &TI, &TE, &UP,
};

/*
 * All we need from termcap is to clear screen and
 *   position cursor at the top; if these aren't available
 *   we say the terminal is dumb and let things scroll
 */
I 4
static
E 4
termcap()
{
	char *term, tbuf[BUFSIZ];
	static char buf[BUFSIZ/2];
	register short columns;
	char *bp = buf;
	register char **p, ***q, *cp;
D 4
	extern int SIZCOL;
E 4

	ioctl(0, TIOCGETP, (char *)&sbuf);
	ospeed = sbuf.sg_ospeed;
	if ((term = getenv("TERM")) != NULL && tgetent(tbuf, term) > 0) {
		for (p = capstrings, q = caps; *p != NULL; p++, q++)
			**q = tgetstr(*p, &bp);
		if ((cp = tgetstr("pc", &bp)) != NULL)
			PC = *cp;
D 4
		if ((columns = tgetnum("co")) >= 0)
			SIZCOL = columns-18;
E 4
	}
	return(CL == NULL || CM == NULL);
}

/*
 * Putchar writearound for tputs
 */
I 4
static
E 4
putch(c)
	char c;
{
	putchar(c);
}
#endif
E 9
E 1
