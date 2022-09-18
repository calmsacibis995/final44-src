h50432
s 00003/00004/00833
d D 8.2 95/04/28 12:49:07 bostic 31 30
c remove gtty/stty calls from msgs
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00005/00832
d D 8.1 93/06/06 15:39:10 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00836
d D 5.10 93/05/19 14:47:35 bostic 29 28
c include  unistd.h for truncate prototype
e
s 00003/00001/00833
d D 5.9 93/02/25 08:55:43 bostic 28 26
c fseek doesn't work if open is in pure append mode (optimization in
c new stdio, probably).  Fix msgs; bug report 4.4BSD-alpha/usr.bin/0.
e
s 00001/00001/00833
d R 5.9 93/02/24 19:49:26 bostic 27 26
c fseek doesn't do anything in stdio if the open was in pure append
c mode (which seems reasonable).  Fix msgs.
c from Tod Oace  <tod@vision.intel.com>  (503)696-4802
e
s 00009/00013/00825
d D 5.8 91/02/04 17:49:09 torek 26 25
c get various declarations from <foo.h> headers; avoid longjmp problems
e
s 00021/00018/00817
d D 5.7 91/01/29 09:50:20 bostic 25 24
c lint fixes from Guy Harris, getting it to run under SunOS
c it's going away, but it might as well go away clean.
e
s 00003/00001/00832
d D 5.6 90/05/29 20:05:58 bostic 24 23
c don't use gets
e
s 00008/00007/00825
d D 5.5 90/05/06 17:07:15 bostic 23 22
c written by Bill Joy and David Wasley; add Berkeley copyright
e
s 00013/00014/00819
d D 5.4 89/05/11 10:02:18 bostic 22 21
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00832
d D 5.3 86/08/07 11:40:36 bloom 21 20
c don't use a closed file pointer
e
s 00009/00004/00824
d D 5.2 86/04/10 09:20:24 bloom 20 19
c use ioctl for getting window size
e
s 00014/00001/00814
d D 5.1 85/06/04 15:28:54 dist 19 18
c Add copyright
e
s 00001/00004/00814
d D 4.16 84/09/17 11:14:21 ralph 18 17
c don't call setbuf.
e
s 00018/00006/00800
d D 4.15 84/04/11 14:32:19 ralph 17 16
c don't update .msgsrc if nextmsg is out of bounds.
e
s 00003/00001/00803
d D 4.14 84/02/22 10:24:00 ralph 16 15
c clearerr() if interrupt so next messgage is fully printed.
e
s 00002/00001/00802
d D 4.13 83/12/08 17:40:49 leres 15 14
c Force msgs to wait for Mail after a suspend and later resume by only
c using longjmp() if we're not "mailing".
e
s 00008/00001/00795
d D 4.12 83/09/12 16:34:18 ralph 14 13
c fixes signals used by more so msgs can continue when -p used.
e
s 00005/00010/00791
d D 4.11 83/07/21 11:44:44 sam 13 12
c fix fix from leres
e
s 00001/00000/00800
d D 4.10 83/07/20 03:11:14 sam 12 11
c SIGTSTP fix
e
s 00002/00002/00798
d D 4.9 83/07/02 00:33:51 sam 11 10
c include fix
e
s 00001/00000/00799
d D 4.8 83/06/27 21:18:58 layer 10 9
c '-' command now takes you back to last displayed message
e
s 00003/00003/00796
d D 4.7 83/05/18 11:13:57 ralph 9 7
c checks lower bound so msgs 1 doesn't take forever when firstmsg == 2000
e
s 00003/00003/00796
d R 4.7 83/05/18 10:50:35 ralph 8 7
c checks lower bound so msgs 1 doesn't take forever when firstmsg == 2000
e
s 00009/00000/00790
d D 4.6 83/05/06 21:16:42 leres 7 5
c Always update the .msgsrc file
e
s 00009/00000/00790
d R 4.6 83/05/06 20:56:07 leres 6 5
c Make sure the .msgsrc file always gets updated
e
s 00027/00000/00763
d D 4.5 83/04/17 18:49:59 leres 5 4
c Prompt again after ^Z suspension
e
s 00002/00002/00761
d D 4.4 82/10/29 18:10:19 mckusick 4 3
c <sys/dir.h> becomes <dir.h>; jkf's fix to make '!' a non local msgs indicator
e
s 00001/00001/00762
d D 4.3 82/10/29 16:07:01 mckusick 3 2
c jkf's fix to include '@' as non local msgs indicator
e
s 00011/00008/00752
d D 4.2 82/05/19 10:36:04 rrh 2 1
c Upgrade to new directory abstraction
e
s 00760/00000/00000
d D 4.1 82/05/19 10:14:32 rrh 1 0
c date and time created 82/05/19 10:14:32 by rrh
e
u
U
t
T
I 19
D 23
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 23
I 23
/*-
D 30
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
 * %sccs.include.redist.c%
E 23
 */

E 19
I 1
#ifndef lint
I 19
D 30
char copyright[] =
D 23
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 23
I 23
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 23
 All rights reserved.\n";
E 30
I 30
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 30
D 23
#endif not lint
E 23
I 23
#endif /* not lint */
E 23

#ifndef lint
E 19
D 11
static char sccsid[] = "%W% %G%";
E 11
I 11
static char sccsid[] = "%W% (Berkeley) %G%";
E 11
D 19
#endif lint
E 19
I 19
D 23
#endif not lint
E 23
I 23
#endif /* not lint */
E 23

E 19
/*
 * msgs - a user bulletin board program
 *
 * usage:
 *	msgs [fhlopq] [[-]number]	to read messages
 *	msgs -s				to place messages
 *	msgs -c [-days]			to clean up the bulletin board
 *
 * prompt commands are:
 *	y	print message
 *	n	flush message, go to next message
 *	q	flush message, quit
 *	p	print message, turn on 'pipe thru more' mode
 *	P	print message, turn off 'pipe thru more' mode
 *	-	reprint last message
 *	s[-][<num>] [<filename>]	save message
 *	m[-][<num>]	mail with message in temp mbox
 *	x	exit without flushing this message
I 17
 *	<num>	print message number <num>
E 17
 */

#define V7		/* will look for TERM in the environment */
#define OBJECT		/* will object to messages without Subjects */
/* #define REJECT	/* will reject messages without Subjects
			   (OBJECT must be defined also) */
/* #define UNBUFFERED	/* use unbuffered output */

D 22
#include <stdio.h>
E 22
D 2
#include <sys/types.h>
E 2
I 2
#include <sys/param.h>
E 2
D 26
#include <signal.h>
I 25
#include <string.h>
E 26
E 25
D 4
#include <sys/dir.h>
E 4
I 4
D 11
#include <dir.h>
E 11
I 11
#include <sys/dir.h>
I 31
#include <sys/ioctl.h>
E 31
E 11
E 4
#include <sys/stat.h>
#include <ctype.h>
I 26
#include <errno.h>
E 26
#include <pwd.h>
D 26
#include <sgtty.h>
E 26
I 13
#include <setjmp.h>
I 26
D 31
#include <sgtty.h>
E 31
#include <signal.h>
E 26
E 13
D 22
#include "msgs.h"
E 22
I 22
#include <stdio.h>
I 26
#include <stdlib.h>
#include <string.h>
I 31
#include <termios.h>
E 31
#include <time.h>
I 29
#include <unistd.h>
E 29
E 26
#include "pathnames.h"
E 22

#define CMODE	0666		/* bounds file creation mode */
#define NO	0
#define YES	1
#define SUPERUSER	0	/* superuser uid */
#define DAEMON		1	/* daemon uid */
#define NLINES	24		/* default number of lines/crt screen */
#define NDAYS	21		/* default keep time for messages */
#define DAYS	*24*60*60	/* seconds/day */
D 22
#define TEMP	"/tmp/msgXXXXXX"
E 22
#define MSGSRC	".msgsrc"	/* user's rc file */
#define BOUNDS	"bounds"	/* message bounds file */
#define NEXT	"Next message? [yq]"
#define MORE	"More? [ynq]"
#define NOMORE	"(No more) [q] ?"

typedef	char	bool;

I 26
FILE	*msgsrc;
E 26
FILE	*newmsg;
char	*sep = "-";
char	inbuf[BUFSIZ];
char	fname[128];
char	cmdbuf[128];
char	subj[128];
char	from[128];
char	date[128];
char	*ptr;
char	*in;
bool	local;
bool	ruptible;
bool	totty;
bool	seenfrom;
bool	seensubj;
bool	blankline;
bool	printing = NO;
bool	mailing = NO;
bool	quitit = NO;
bool	sending = NO;
bool	intrpflg = NO;
I 5
D 25
bool	tstpflag = NO;
E 25
E 5
int	uid;
int	msg;
int	prevmsg;
int	lct;
int	nlines;
D 20
int	Lpp = NLINES;
E 20
I 20
int	Lpp = 0;
E 20
time_t	t;
time_t	keep;
D 31
struct	sgttyb	otty;
E 31

D 26
char	*ctime();
I 25
char	*getenv();
E 26
char	*mktemp();
E 25
char	*nxtfld();
D 25
int	onintr();
I 5
int	onsusp();
E 25
I 25
void	onintr();
void	onsusp();
E 25
E 5
D 26
off_t	ftell();
FILE	*popen();
struct	passwd	*getpwuid();
I 25
time_t	time();
E 26
E 25

D 26
extern	int	errno;

E 26
/* option initialization */
bool	hdrs = NO;
bool	qopt = NO;
bool	hush = NO;
D 25
bool	send = NO;
E 25
I 25
bool	send_msg = NO;
E 25
bool	locomode = NO;
D 25
bool	pause = NO;
E 25
I 25
bool	use_pager = NO;
E 25
bool	clean = NO;
bool	lastcmd = NO;
I 13
jmp_buf	tstpbuf;
E 13

main(argc, argv)
int argc; char *argv[];
{
	bool newrc, already;
	int rcfirst = 0;		/* first message to print (from .rc) */
D 9
	int rcback = 0;			/* amount to back off of rcfirst*/
E 9
I 9
	int rcback = 0;			/* amount to back off of rcfirst */
E 9
	int firstmsg, nextmsg, lastmsg = 0;
	int blast = 0;
D 26
	FILE *bounds, *msgsrc;
E 26
I 26
	FILE *bounds;
E 26

D 18
#ifndef UNBUFFERED
	char obuf[BUFSIZ];
	setbuf(stdout, obuf);
#else
E 18
I 18
#ifdef UNBUFFERED
E 18
	setbuf(stdout, NULL);
#endif

D 31
	gtty(fileno(stdout), &otty);
E 31
	time(&t);
	setuid(uid = getuid());
	ruptible = (signal(SIGINT, SIG_IGN) == SIG_DFL);
	if (ruptible)
		signal(SIGINT, SIG_DFL);

	argc--, argv++;
	while (argc > 0) {
		if (isdigit(argv[0][0])) {	/* starting message # */
			rcfirst = atoi(argv[0]);
		}
		else if (isdigit(argv[0][1])) {	/* backward offset */
			rcback = atoi( &( argv[0][1] ) );
		}
		else {
			ptr = *argv;
			while (*ptr) switch (*ptr++) {

			case '-':
				break;

			case 'c':
				if (uid != SUPERUSER && uid != DAEMON) {
					fprintf(stderr, "Sorry\n");
					exit(1);
				}
				clean = YES;
				break;

			case 'f':		/* silently */
				hush = YES;
				break;

			case 'h':		/* headers only */
				hdrs = YES;
				break;

			case 'l':		/* local msgs only */
				locomode = YES;
				break;

			case 'o':		/* option to save last message */
				lastcmd = YES;
				break;

			case 'p':		/* pipe thru 'more' during long msgs */
D 25
				pause = YES;
E 25
I 25
				use_pager = YES;
E 25
				break;

			case 'q':		/* query only */
				qopt = YES;
				break;

			case 's':		/* sending TO msgs */
D 25
				send = YES;
E 25
I 25
				send_msg = YES;
E 25
				break;

			default:
				fprintf(stderr,
					"usage: msgs [fhlopq] [[-]number]\n");
				exit(1);
			}
		}
		argc--, argv++;
	}

	/*
	 * determine current message bounds
	 */
D 22
	sprintf(fname, "%s/%s", USRMSGS, BOUNDS);
E 22
I 22
	sprintf(fname, "%s/%s", _PATH_MSGS, BOUNDS);
E 22
	bounds = fopen(fname, "r");

	if (bounds != NULL) {
		fscanf(bounds, "%d %d\n", &firstmsg, &lastmsg);
		fclose(bounds);
		blast = lastmsg;	/* save upper bound */
	}

	if (clean)
		keep = t - (rcback? rcback : NDAYS) DAYS;

	if (clean || bounds == NULL) {	/* relocate message bounds */
D 2
		struct direct dirent;
E 2
I 2
		struct direct *dp;
E 2
		struct stat stbuf;
		bool seenany = NO;
I 2
		DIR	*dirp;
E 2

D 2
		FILE *d = fopen(USRMSGS, "r");
		if (d == NULL) {
E 2
I 2
D 22
		dirp = opendir(USRMSGS);
E 22
I 22
		dirp = opendir(_PATH_MSGS);
E 22
		if (dirp == NULL) {
E 2
D 22
			perror(USRMSGS);
E 22
I 22
			perror(_PATH_MSGS);
E 22
			exit(errno);
		}

		firstmsg = 32767;
		lastmsg = 0;

D 2
		while (fread(&dirent, sizeof dirent, 1, d) == 1) {
			register char *cp = dirent.d_name;
E 2
I 2
		for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)){
			register char *cp = dp->d_name;
E 2
			register int i = 0;

D 2
			if (dirent.d_ino == 0)
E 2
I 2
			if (dp->d_ino == 0)
E 2
				continue;
I 2
			if (dp->d_namlen == 0)
				continue;
E 2

			if (clean)
D 22
				sprintf(inbuf, "%s/%s", USRMSGS, cp);
E 22
I 22
				sprintf(inbuf, "%s/%s", _PATH_MSGS, cp);
E 22

			while (isdigit(*cp))
				i = i * 10 + *cp++ - '0';
			if (*cp)
				continue;	/* not a message! */

			if (clean) {
				if (stat(inbuf, &stbuf) != 0)
					continue;
				if (stbuf.st_mtime < keep
				    && stbuf.st_mode&S_IWRITE) {
					unlink(inbuf);
					continue;
				}
			}

			if (i > lastmsg)
				lastmsg = i;
			if (i < firstmsg)
				firstmsg = i;
			seenany = YES;
		}
D 2
		fclose(d);
E 2
I 2
		closedir(dirp);
E 2

		if (!seenany) {
			if (blast != 0)	/* never lower the upper bound! */
				lastmsg = blast;
			firstmsg = lastmsg + 1;
		}
		else if (blast > lastmsg)
			lastmsg = blast;

D 25
		if (!send) {
E 25
I 25
		if (!send_msg) {
E 25
			bounds = fopen(fname, "w");
			if (bounds == NULL) {
				perror(fname);
				exit(errno);
			}
			chmod(fname, CMODE);
			fprintf(bounds, "%d %d\n", firstmsg, lastmsg);
			fclose(bounds);
		}
	}

D 25
	if (send) {
E 25
I 25
	if (send_msg) {
E 25
		/*
D 22
		 * Send mode - place msgs in USRMSGS
E 22
I 22
		 * Send mode - place msgs in _PATH_MSGS
E 22
		 */
		bounds = fopen(fname, "w");
		if (bounds == NULL) {
			perror(fname);
			exit(errno);
		}

		nextmsg = lastmsg + 1;
D 22
		sprintf(fname, "%s/%d", USRMSGS, nextmsg);
E 22
I 22
		sprintf(fname, "%s/%d", _PATH_MSGS, nextmsg);
E 22
		newmsg = fopen(fname, "w");
		if (newmsg == NULL) {
			perror(fname);
			exit(errno);
		}
		chmod(fname, 0644);

		fprintf(bounds, "%d %d\n", firstmsg, nextmsg);
		fclose(bounds);

		sending = YES;
		if (ruptible)
			signal(SIGINT, onintr);

		if (isatty(fileno(stdin))) {
			ptr = getpwuid(uid)->pw_name;
			printf("Message %d:\nFrom %s %sSubject: ",
				nextmsg, ptr, ctime(&t));
			fflush(stdout);
			fgets(inbuf, sizeof inbuf, stdin);
			putchar('\n');
			fflush(stdout);
			fprintf(newmsg, "From %s %sSubject: %s\n",
				ptr, ctime(&t), inbuf);
			blankline = seensubj = YES;
		}
		else
			blankline = seensubj = NO;
		for (;;) {
			fgets(inbuf, sizeof inbuf, stdin);
			if (feof(stdin) || ferror(stdin))
				break;
			blankline = (blankline || (inbuf[0] == '\n'));
			seensubj = (seensubj || (!blankline && (strncmp(inbuf, "Subj", 4) == 0)));
			fputs(inbuf, newmsg);
		}
#ifdef OBJECT
		if (!seensubj) {
			printf("NOTICE: Messages should have a Subject field!\n");
#ifdef REJECT
			unlink(fname);
#endif
			exit(1);
		}
#endif
		exit(ferror(stdin));
	}
	if (clean)
		exit(0);

	/*
	 * prepare to display messages
	 */
	totty = (isatty(fileno(stdout)) != 0);
D 25
	pause = pause && totty;
E 25
I 25
	use_pager = use_pager && totty;
E 25

	sprintf(fname, "%s/%s", getenv("HOME"), MSGSRC);
	msgsrc = fopen(fname, "r");
	if (msgsrc) {
		newrc = NO;
		fscanf(msgsrc, "%d\n", &nextmsg);
		fclose(msgsrc);
D 17
		if (!rcfirst)
E 17
I 17
		if (nextmsg > lastmsg+1) {
			printf("Warning: bounds have been reset (%d, %d)\n",
				firstmsg, lastmsg);
D 21
			ftruncate(fileno(msgsrc), 0);
E 21
I 21
D 25
			truncate(fname, 0);
E 25
I 25
			truncate(fname, (off_t)0);
E 25
E 21
			newrc = YES;
		}
		else if (!rcfirst)
E 17
			rcfirst = nextmsg - rcback;
	}
D 17
	else {
E 17
I 17
	else
E 17
		newrc = YES;
D 17
		nextmsg = 0;
	}
E 17
D 28
	msgsrc = fopen(fname, "a");
E 28
I 28
	msgsrc = fopen(fname, "r+");
	if (msgsrc == NULL)
		msgsrc = fopen(fname, "w");
E 28
	if (msgsrc == NULL) {
		perror(fname);
		exit(errno);
	}
D 9
	if (rcfirst)
		firstmsg = rcfirst;
E 9
I 9
D 17
	if (rcfirst && rcfirst > firstmsg)
		firstmsg = rcfirst;		/* don't set below first msg */
E 17
I 17
	if (rcfirst) {
		if (rcfirst > lastmsg+1) {
			printf("Warning: the last message is number %d.\n",
				lastmsg);
			rcfirst = nextmsg;
		}
		if (rcfirst > firstmsg)
			firstmsg = rcfirst;	/* don't set below first msg */
	}
E 17
E 9
	if (newrc) {
		nextmsg = firstmsg;
		fseek(msgsrc, 0L, 0);
		fprintf(msgsrc, "%d\n", nextmsg);
		fflush(msgsrc);
	}

#ifdef V7
	if (totty) {
D 20
		if (tgetent(inbuf, getenv("TERM")) <= 0
		    || (Lpp = tgetnum("li")) <= 0) {
			Lpp = NLINES;
E 20
I 20
		struct winsize win;
		if (ioctl(fileno(stdout), TIOCGWINSZ, &win) != -1)
			Lpp = win.ws_row;
		if (Lpp <= 0) {
			if (tgetent(inbuf, getenv("TERM")) <= 0
			    || (Lpp = tgetnum("li")) <= 0) {
				Lpp = NLINES;
			}
E 20
		}
	}
#endif
	Lpp -= 6;	/* for headers, etc. */

	already = NO;
	prevmsg = firstmsg;
	printing = YES;
	if (ruptible)
		signal(SIGINT, onintr);

	/*
	 * Main program loop
	 */
	for (msg = firstmsg; msg <= lastmsg; msg++) {

D 22
		sprintf(fname, "%s/%d", USRMSGS, msg);
E 22
I 22
		sprintf(fname, "%s/%d", _PATH_MSGS, msg);
E 22
		newmsg = fopen(fname, "r");
		if (newmsg == NULL)
			continue;

		gfrsub(newmsg);		/* get From and Subject fields */
		if (locomode && !local) {
			fclose(newmsg);
			continue;
		}

		if (qopt) {	/* This has to be located here */
			printf("There are new messages.\n");
			exit(0);
		}

		if (already && !hdrs)
			putchar('\n');
D 26
		already = YES;
E 26

		/*
		 * Print header
		 */
I 5
D 25
again:
E 25
D 13
		tstpflag = NO;
E 13
		if (totty)
			signal(SIGTSTP, onsusp);
I 13
		(void) setjmp(tstpbuf);
I 26
		already = YES;
E 26
E 13
E 5
		nlines = 2;
		if (seenfrom) {
			printf("Message %d:\nFrom %s %s", msg, from, date);
			nlines++;
		}
		if (seensubj) {
			printf("Subject: %s", subj);
			nlines++;
		}
		else {
			if (seenfrom) {
				putchar('\n');
				nlines++;
			}
			while (nlines < 6
			    && fgets(inbuf, sizeof inbuf, newmsg)
			    && inbuf[0] != '\n') {
				fputs(inbuf, stdout);
				nlines++;
			}
		}

		lct = linecnt(newmsg);
		if (lct)
			printf("(%d%slines) ", lct, seensubj? " " : " more ");

		if (hdrs) {
			printf("\n-----\n");
			fclose(newmsg);
			continue;
		}

		/*
		 * Ask user for command
		 */
		if (totty)
			ask(lct? MORE : (msg==lastmsg? NOMORE : NEXT));
		else
			inbuf[0] = 'y';
I 5
		if (totty)
			signal(SIGTSTP, SIG_DFL);
D 13
		/*
		 * Loop if we've been suspended
		 */
		if (tstpflag)
			goto again;
E 13
E 5
cmnd:
		in = inbuf;
		switch (*in) {
			case 'x':
			case 'X':
				exit(0);

			case 'q':
			case 'Q':
				quitit = YES;
				printf("--Postponed--\n");
				exit(0);
				/* intentional fall-thru */
			case 'n':
			case 'N':
				if (msg >= nextmsg) sep = "Flushed";
I 10
				prevmsg = msg;
E 10
				break;

			case 'p':
			case 'P':
D 25
				pause = (*in++ == 'p');
E 25
I 25
				use_pager = (*in++ == 'p');
E 25
				/* intentional fallthru */
			case '\n':
			case 'y':
			default:
				if (*in == '-') {
					msg = prevmsg-1;
					sep = "replay";
					break;
				}
				if (isdigit(*in)) {
					msg = next(in);
					sep = in;
					break;
				}

				prmesg(nlines + lct + (seensubj? 1 : 0));
				prevmsg = msg;

		}

		printf("--%s--\n", sep);
		sep = "-";
		if (msg >= nextmsg) {
			nextmsg = msg + 1;
			fseek(msgsrc, 0L, 0);
			fprintf(msgsrc, "%d\n", nextmsg);
			fflush(msgsrc);
		}
		if (newmsg)
			fclose(newmsg);
		if (quitit)
			break;
	}

I 7
	/*
	 * Make sure .rc file gets updated
	 */
	if (--msg >= nextmsg) {
		nextmsg = msg + 1;
		fseek(msgsrc, 0L, 0);
		fprintf(msgsrc, "%d\n", nextmsg);
		fflush(msgsrc);
	}
E 7
	if (already && !quitit && lastcmd && totty) {
		/*
		 * save or reply to last message?
		 */
		msg = prevmsg;
		ask(NOMORE);
		if (inbuf[0] == '-' || isdigit(inbuf[0]))
			goto cmnd;
	}
	if (!(already || hush || qopt))
		printf("No new messages.\n");
	exit(0);
}

prmesg(length)
int length;
{
D 25
	FILE *outf, *inf;
	int c;
E 25
I 25
	FILE *outf;
E 25

D 25
	if (pause && length > Lpp) {
E 25
I 25
	if (use_pager && length > Lpp) {
E 25
I 14
		signal(SIGPIPE, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
E 14
D 22
		sprintf(cmdbuf, PAGE, Lpp);
E 22
I 22
		sprintf(cmdbuf, _PATH_PAGER, Lpp);
E 22
		outf = popen(cmdbuf, "w");
		if (!outf)
			outf = stdout;
		else
D 25
			setbuf(outf, NULL);
E 25
I 25
			setbuf(outf, (char *)NULL);
E 25
	}
	else
		outf = stdout;

	if (seensubj)
		putc('\n', outf);

D 14
	while (fgets(inbuf, sizeof inbuf, newmsg))
E 14
I 14
	while (fgets(inbuf, sizeof inbuf, newmsg)) {
E 14
		fputs(inbuf, outf);
I 14
D 16
		if (ferror(outf))
E 16
I 16
		if (ferror(outf)) {
			clearerr(outf);
E 16
			break;
I 16
		}
E 16
	}
E 14

	if (outf != stdout) {
		pclose(outf);
I 14
		signal(SIGPIPE, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
E 14
	}
	else {
		fflush(stdout);
	}

	/* trick to force wait on output */
D 31
	stty(fileno(stdout), &otty);
E 31
I 31
	tcdrain(fileno(stdout));
E 31
}

I 25
void
E 25
onintr()
{
	signal(SIGINT, onintr);
	if (mailing)
		unlink(fname);
	if (sending) {
		unlink(fname);
		puts("--Killed--");
		exit(1);
	}
	if (printing) {
		putchar('\n');
		if (hdrs)
			exit(0);
		sep = "Interrupt";
		if (newmsg)
			fseek(newmsg, 0L, 2);
		intrpflg = YES;
	}
I 5
}

/*
 * We have just gotten a susp.  Suspend and prepare to resume.
 */
I 25
void
E 25
onsusp()
{
D 13
	tstpflag = YES;
E 13
I 13

E 13
	signal(SIGTSTP, SIG_DFL);
I 12
	sigsetmask(0);
E 12
	kill(0, SIGTSTP);
D 13

	/* the pc stops here */

E 13
	signal(SIGTSTP, onsusp);
I 13
D 15
	longjmp(tstpbuf);
E 15
I 15
	if (!mailing)
D 25
		longjmp(tstpbuf);
E 25
I 25
		longjmp(tstpbuf, 0);
E 25
E 15
E 13
E 5
}

linecnt(f)
FILE *f;
{
	off_t oldpos = ftell(f);
	int l = 0;
	char lbuf[BUFSIZ];

	while (fgets(lbuf, sizeof lbuf, f))
		l++;
	clearerr(f);
	fseek(f, oldpos, 0);
	return (l);
}

next(buf)
char *buf;
{
	int i;
	sscanf(buf, "%d", &i);
	sprintf(buf, "Goto %d", i);
	return(--i);
}

ask(prompt)
char *prompt;
{
	char	inch;
	int	n, cmsg;
	off_t	oldpos;
	FILE	*cpfrom, *cpto;

	printf("%s ", prompt);
	fflush(stdout);
	intrpflg = NO;
D 24
	gets(inbuf);
E 24
I 24
	(void) fgets(inbuf, sizeof inbuf, stdin);
	if ((n = strlen(inbuf)) > 0 && inbuf[n - 1] == '\n')
		inbuf[n - 1] = '\0';
E 24
	if (intrpflg)
		inbuf[0] = 'x';

	/*
	 * Handle 'mail' and 'save' here.
	 */
	if ((inch = inbuf[0]) == 's' || inch == 'm') {
		if (inbuf[1] == '-')
			cmsg = prevmsg;
		else if (isdigit(inbuf[1]))
			cmsg = atoi(&inbuf[1]);
		else
			cmsg = msg;
D 22
		sprintf(fname, "%s/%d", USRMSGS, cmsg);
E 22
I 22
		sprintf(fname, "%s/%d", _PATH_MSGS, cmsg);
E 22

		oldpos = ftell(newmsg);

		cpfrom = fopen(fname, "r");
		if (!cpfrom) {
			printf("Message %d not found\n", cmsg);
			ask (prompt);
			return;
		}

		if (inch == 's') {
			in = nxtfld(inbuf);
			if (*in) {
				for (n=0; in[n] > ' '; n++) { /* sizeof fname? */
					fname[n] = in[n];
				}
				fname[n] = NULL;
			}
			else
				strcpy(fname, "Messages");
		}
		else {
D 22
			strcpy(fname, TEMP);
E 22
I 22
			strcpy(fname, _PATH_TMP);
E 22
			mktemp(fname);
D 22
			sprintf(cmdbuf, MAIL, fname);
E 22
I 22
			sprintf(cmdbuf, _PATH_MAIL, fname);
E 22
			mailing = YES;
		}
		cpto = fopen(fname, "a");
		if (!cpto) {
			perror(fname);
			mailing = NO;
			fseek(newmsg, oldpos, 0);
			ask(prompt);
			return;
		}

		while (n = fread(inbuf, 1, sizeof inbuf, cpfrom))
			fwrite(inbuf, 1, n, cpto);

		fclose(cpfrom);
		fclose(cpto);
		fseek(newmsg, oldpos, 0);	/* reposition current message */
		if (inch == 's')
			printf("Message %d saved in \"%s\"\n", cmsg, fname);
		else {
			system(cmdbuf);
			unlink(fname);
			mailing = NO;
		}
		ask(prompt);
	}
}

gfrsub(infile)
FILE *infile;
{
	off_t frompos;

	seensubj = seenfrom = NO;
	local = YES;
	subj[0] = from[0] = date[0] = NULL;

	/*
	 * Is this a normal message?
	 */
	if (fgets(inbuf, sizeof inbuf, infile)) {
		if (strncmp(inbuf, "From", 4)==0) {
			/*
			 * expected form starts with From
			 */
			seenfrom = YES;
			frompos = ftell(infile);
			ptr = from;
			in = nxtfld(inbuf);
			if (*in) while (*in && *in > ' ') {
D 3
				if (*in == ':')
E 3
I 3
D 4
				if (*in == ':' || *in == '@')
E 4
I 4
				if (*in == ':' || *in == '@' || *in == '!')
E 4
E 3
					local = NO;
				*ptr++ = *in++;
				/* what about sizeof from ? */
			}
			*ptr = NULL;
			if (*(in = nxtfld(in)))
				strncpy(date, in, sizeof date);
			else {
				date[0] = '\n';
				date[1] = NULL;
			}
		}
		else {
			/*
			 * not the expected form
			 */
			fseek(infile, 0L, 0);
			return;
		}
	}
	else
		/*
		 * empty file ?
		 */
		return;

	/*
	 * look for Subject line until EOF or a blank line
	 */
	while (fgets(inbuf, sizeof inbuf, infile)
	    && !(blankline = (inbuf[0] == '\n'))) {
		/*
		 * extract Subject line
		 */
		if (!seensubj && strncmp(inbuf, "Subj", 4)==0) {
			seensubj = YES;
			frompos = ftell(infile);
			strncpy(subj, nxtfld(inbuf), sizeof subj);
		}
	}
	if (!blankline)
		/*
		 * ran into EOF
		 */
		fseek(infile, frompos, 0);

	if (!seensubj)
		/*
		 * for possible use with Mail
		 */
		strncpy(subj, "(No Subject)\n", sizeof subj);
}

char *
nxtfld(s)
char *s;
{
	if (*s) while (*s && *s > ' ') s++;	/* skip over this field */
	if (*s) while (*s && *s <= ' ') s++;	/* find start of next field */
	return (s);
}
E 1
