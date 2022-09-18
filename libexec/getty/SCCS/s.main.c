h10850
s 00005/00005/00518
d D 8.1 93/06/20 08:39:13 bostic 32 31
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00003/00516
d D 5.22 93/06/20 08:38:59 bostic 31 29
c reset the cpu time limit when we exec
e
s 00005/00005/00514
d R 8.1 93/06/04 19:13:02 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00000/00491
d D 5.21 93/06/04 19:11:39 mckusick 29 27
c limit total running time for getty to prevent bad lines from forcing getty
c into an infinite loop
e
s 00005/00005/00486
d R 8.1 93/06/04 18:50:29 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00004/00489
d D 5.20 93/05/27 12:55:37 elan 27 26
c Convert to getcap(3) routines.
e
s 00030/00010/00463
d D 5.19 93/05/17 10:36:53 bostic 26 25
c ANSI C prototypes
e
s 00003/00002/00470
d D 5.18 92/03/29 12:26:26 bostic 25 24
c pass pointer to 0, not 0
e
s 00000/00001/00472
d D 5.17 91/09/26 15:46:00 bostic 24 23
c lint
e
s 00005/00003/00468
d D 5.16 91/03/27 12:20:25 william 23 22
c added no parity flage for 386 8-bit character display console
e
s 00001/00001/00470
d D 5.15 91/03/04 10:34:48 bostic 22 21
c automatic aggregate for pcc
e
s 00014/00008/00457
d D 5.14 91/02/25 17:03:06 bostic 21 20
c ANSI fixes (one real bug fix!)
e
s 00005/00003/00460
d D 5.13 91/01/21 09:43:06 bostic 20 19
c SCCS munges %M%
e
s 00033/00042/00430
d D 5.12 91/01/19 18:03:23 bostic 19 18
c minor cleanups and lint; use strftime(3); Berkeley specific copyright
e
s 00006/00001/00466
d D 5.11 90/06/29 16:03:02 marc 18 17
c sett system defaults
e
s 00006/00011/00461
d D 5.10 90/06/28 23:28:39 marc 17 16
c use login_tty(), call revoke, change tty mode to 600
e
s 00002/00003/00470
d D 5.9 90/05/30 09:23:55 mckusick 16 15
c optimization (4.3BSD-tahoe/libexec/4)
e
s 00014/00009/00459
d D 5.8 90/05/30 09:22:16 marc 15 14
c checked in for marc by mckusick
e
s 00004/00000/00464
d D 5.7 87/10/01 12:10:42 bostic 14 13
c '-' may not start login name; bug report 4.3BSD/bin/85
e
s 00004/00000/00460
d D 5.6 87/09/16 17:42:54 bostic 13 12
c ioctl mode cleanup; login fail logging; bug report 4.3BSD/etc/34
e
s 00005/00003/00455
d D 5.5 86/01/23 16:29:06 bloom 12 11
c don't do a vhangup if running xterm (from Jim Gettys)
e
s 00004/00000/00454
d D 5.4 85/11/30 11:59:39 mckusick 11 10
c hold DTR down for at least two seconds (from muller@nprdc.arpa)
e
s 00001/00001/00453
d D 5.3 85/09/18 00:01:31 eric 10 9
c facilities in syslog
e
s 00001/00001/00453
d D 5.2 85/09/17 23:27:34 eric 9 8
c facilities in syslog
e
s 00014/00002/00440
d D 5.1 85/04/29 12:06:11 dist 8 7
c Add copyright
e
s 00076/00021/00366
d D 4.7 85/04/01 13:46:26 ralph 7 6
c set up environment partially; do tty open.
e
s 00011/00000/00376
d D 4.6 83/12/13 14:59:07 ralph 6 5
c added %t for tty name to :im= string.
e
s 00001/00000/00375
d D 4.5 83/08/01 16:06:15 sam 5 4
c must flush output before sleep
e
s 00004/00000/00371
d D 4.4 83/07/09 18:34:29 sam 4 3
c allow output to be flushed before first prompt to handle open lines
e
s 00009/00008/00362
d D 4.3 83/07/07 09:26:04 sam 3 2
c forgotten flush
e
s 00043/00004/00327
d D 4.2 83/07/07 03:34:08 kre 2 1
c several fixes (buffered output, parity override bug,
c int's can happen in cbreak, ..)
e
s 00331/00000/00000
d D 4.1 83/07/06 00:10:13 sam 1 0
c date and time created 83/07/06 00:10:13 by sam
e
u
U
t
T
I 8
D 19
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 19
I 19
/*-
D 32
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 32
I 32
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 32
 *
 * %sccs.include.redist.c%
E 19
 */

E 8
I 1
#ifndef lint
D 8
static char sccsid[] = "%W% (Berkeley) %E%";
#endif
E 8
I 8
D 32
char copyright[] =
D 19
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 19
I 19
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 19
 All rights reserved.\n";
E 32
I 32
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 32
D 19
#endif not lint
E 19
I 19
#endif /* not lint */
E 19

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 19
#endif not lint
E 19
I 19
#endif /* not lint */
E 19
E 8

D 19
/*
 * getty -- adapt to terminal speed on dialup, and call login
 *
 * Melbourne getty, June 83, kre.
 */

E 19
I 15
#define USE_OLD_TTY
I 19

E 19
#include <sys/param.h>
D 21
#include <sys/signal.h>
#include <sys/file.h>
E 21
I 21
#include <sys/stat.h>
I 29
#include <sys/resource.h>
E 29
D 26
#include <signal.h>
#include <fcntl.h>
E 21
E 15
#include <sgtty.h>
I 21
#include <time.h>
E 26
I 26

E 26
E 21
D 15
#include <signal.h>
E 15
#include <ctype.h>
D 26
#include <setjmp.h>
I 7
#include <syslog.h>
I 19
#include <unistd.h>
E 26
E 19
D 15
#include <sys/file.h>
E 15
I 15
#include <ctype.h>
I 26
#include <fcntl.h>
#include <setjmp.h>
#include <sgtty.h>
#include <signal.h>
E 26
I 21
#include <stdlib.h>
E 21
I 19
#include <string.h>
I 26
#include <syslog.h>
#include <time.h>
#include <unistd.h>

E 26
E 19
E 15
E 7
#include "gettytab.h"
I 15
#include "pathnames.h"
I 26
#include "extern.h"
E 26
E 15

I 29
/*
 * Set the amount of running time that getty should accumulate
 * before deciding that something is wrong and exit.
 */
#define GETTY_TIMEOUT	60 /* seconds */

E 29
I 7
D 19
extern	char **environ;

E 19
E 7
struct	sgttyb tmode = {
	0, 0, CERASE, CKILL, 0
};
struct	tchars tc = {
	CINTR, CQUIT, CSTART,
	CSTOP, CEOF, CBRK,
};
struct	ltchars ltc = {
	CSUSP, CDSUSP, CRPRNT,
	CFLUSH, CWERASE, CLNEXT
};

D 19
int	crmod;
int	upper;
int	lower;
int	digit;
E 19
I 19
int crmod, digit, lower, upper;
E 19

D 15
char	hostname[32];
E 15
I 15
char	hostname[MAXHOSTNAMELEN];
E 15
char	name[16];
I 7
D 15
char	dev[] = "/dev/";
char	ctty[] = "/dev/console";
E 15
I 15
char	dev[] = _PATH_DEV;
E 15
char	ttyn[32];
E 7
char	*portselector();
I 7
char	*ttyname();
E 7

I 2
#define	OBUFSIZ		128
E 2
#define	TABBUFSIZ	512

char	defent[TABBUFSIZ];
D 27
char	defstrs[TABBUFSIZ];
E 27
char	tabent[TABBUFSIZ];
D 27
char	tabstrs[TABBUFSIZ];
E 27

char	*env[128];

char partab[] = {
	0001,0201,0201,0001,0201,0001,0001,0201,
	0202,0004,0003,0205,0005,0206,0201,0001,
	0201,0001,0001,0201,0001,0201,0201,0001,
	0001,0201,0201,0001,0201,0001,0001,0201,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0201
};

#define	ERASE	tmode.sg_erase
#define	KILL	tmode.sg_kill
#define	EOT	tc.t_eofc

jmp_buf timeout;

I 21
static void
E 21
dingdong()
{

	alarm(0);
	signal(SIGALRM, SIG_DFL);
	longjmp(timeout, 1);
}

I 2
jmp_buf	intrupt;

I 21
static void
E 21
interrupt()
{

	signal(SIGINT, interrupt);
	longjmp(intrupt, 1);
}

I 29
/*
 * Action to take when getty is running too long.
 */
void
D 31
timeoverrun()
E 31
I 31
timeoverrun(signo)
	int signo;
E 31
{

	syslog(LOG_ERR, "getty exiting due to excessive running time\n");
	exit(1);
}

E 29
I 26
static int	getname __P((void));
static void	oflush __P((void));
static void	prompt __P((void));
static void	putchr __P((int));
static void	putf __P((char *));
static void	putpad __P((char *));
static void	puts __P((char *));

int
E 26
E 2
main(argc, argv)
D 19
	char *argv[];
E 19
I 19
	int argc;
D 26
	char **argv;
E 26
I 26
	char *argv[];
E 26
E 19
{
I 19
D 26
	extern	char **environ;
E 26
I 26
	extern char **environ;
E 26
E 19
	char *tname;
	long allflags;
I 7
	int repcnt = 0;
I 29
	struct rlimit limit;
E 29
E 7

D 2
/*
E 2
	signal(SIGINT, SIG_IGN);
I 2
/*
E 2
	signal(SIGQUIT, SIG_DFL);
*/
I 7
D 9
	openlog("getty", LOG_ODELAY|LOG_CONS, 0);
E 9
I 9
	openlog("getty", LOG_ODELAY|LOG_CONS, LOG_AUTH);
E 9
E 7
	gethostname(hostname, sizeof(hostname));
	if (hostname[0] == '\0')
		strcpy(hostname, "Amnesiac");
I 29

	/*
	 * Limit running time to deal with broken or dead lines.
	 */
D 31
	signal(SIGXCPU, timeoverrun);
E 31
I 31
	(void)signal(SIGXCPU, timeoverrun);
E 31
	limit.rlim_max = RLIM_INFINITY;
	limit.rlim_cur = GETTY_TIMEOUT;
D 31
	setrlimit(RLIMIT_CPU, &limit);
E 31
I 31
	(void)setrlimit(RLIMIT_CPU, &limit);
E 31

E 29
I 7
	/*
	 * The following is a work around for vhangup interactions
	 * which cause great problems getting window systems started.
	 * If the tty line is "-", we do the old style getty presuming
	 * that the file descriptors are already set up for us. 
	 * J. Gettys - MIT Project Athena.
	 */
	if (argc <= 2 || strcmp(argv[2], "-") == 0)
D 12
		strcpy(ttyn, ttyname(0));
E 12
I 12
	    strcpy(ttyn, ttyname(0));
E 12
	else {
I 17
	    int i;

E 17
D 12
		strcpy(ttyn, dev);
		strncat(ttyn, argv[2], sizeof(ttyn)-sizeof(dev));
E 12
I 12
	    strcpy(ttyn, dev);
	    strncat(ttyn, argv[2], sizeof(ttyn)-sizeof(dev));
	    if (strcmp(argv[0], "+") != 0) {
E 12
		chown(ttyn, 0, 0);
D 17
		chmod(ttyn, 0622);
E 17
I 17
		chmod(ttyn, 0600);
		revoke(ttyn);
E 17
I 11
		/*
		 * Delay the open so DTR stays down long enough to be detected.
		 */
		sleep(2);
E 11
D 17
		while (open(ttyn, O_RDWR) != 0) {
E 17
I 17
		while ((i = open(ttyn, O_RDWR)) == -1) {
E 17
			if (repcnt % 10 == 0) {
D 10
				syslog(LOG_FAIL, "%s: %m", ttyn);
E 10
I 10
				syslog(LOG_ERR, "%s: %m", ttyn);
E 10
				closelog();
			}
			repcnt++;
			sleep(60);
		}
D 17
		signal(SIGHUP, SIG_IGN);
		vhangup();
		(void) open(ttyn, O_RDWR);
		close(0);
		dup(1);
		dup(0);
		signal(SIGHUP, SIG_DFL);
I 15
		if (ioctl(0, TIOCSCTTY, 0) < 0)
			 syslog(LOG_ERR, "TIOCSCTTY failed %m");
E 17
I 17
		login_tty(i);
E 17
E 15
I 12
	    }
E 12
	}

E 7
D 27
	gettable("default", defent, defstrs);
E 27
I 27
	gettable("default", defent);
E 27
	gendefaults();
	tname = "default";
	if (argc > 1)
		tname = argv[1];
	for (;;) {
D 24
		int ldisp = OTTYDISC;
E 24
I 13
D 25
		int off = 0;
E 25
I 25
		int off;
E 25
E 13

D 27
		gettable(tname, tabent, tabstrs);
E 27
I 27
		gettable(tname, tabent);
E 27
I 2
		if (OPset || EPset || APset)
			APset++, OPset++, EPset++;
E 2
		setdefaults();
D 25
		ioctl(0, TIOCFLUSH, 0);		/* clear out the crap */
E 25
I 25
		off = 0;
		ioctl(0, TIOCFLUSH, &off);	/* clear out the crap */
E 25
I 13
		ioctl(0, FIONBIO, &off);	/* turn off non-blocking mode */
D 19
		ioctl(0, FIOASYNC, &off);	/* ditto for asynchronous mode */
E 19
I 19
		ioctl(0, FIOASYNC, &off);	/* ditto for async mode */
E 19
E 13
		if (IS)
			tmode.sg_ispeed = speed(IS);
		else if (SP)
			tmode.sg_ispeed = speed(SP);
		if (OS)
			tmode.sg_ospeed = speed(OS);
		else if (SP)
			tmode.sg_ospeed = speed(SP);
		tmode.sg_flags = setflags(0);
		ioctl(0, TIOCSETP, &tmode);
		setchars();
		ioctl(0, TIOCSETC, &tc);
D 18
		ioctl(0, TIOCSETD, &ldisp);
E 18
		if (HC)
			ioctl(0, TIOCHPCL, 0);
I 7
		if (AB) {
			extern char *autobaud();

			tname = autobaud();
			continue;
		}
E 7
		if (PS) {
			tname = portselector();
			continue;
		}
		if (CL && *CL)
			putpad(CL);
		edithost(HE);
		if (IM && *IM)
			putf(IM);
		if (setjmp(timeout)) {
			tmode.sg_ispeed = tmode.sg_ospeed = 0;
			ioctl(0, TIOCSETP, &tmode);
			exit(1);
		}
		if (TO) {
			signal(SIGALRM, dingdong);
			alarm(TO);
		}
		if (getname()) {
I 7
			register int i;

			oflush();
E 7
			alarm(0);
			signal(SIGALRM, SIG_DFL);
I 14
			if (name[0] == '-') {
D 15
				puts("login names may not start with '-'.");
E 15
I 15
				puts("user names may not start with '-'.");
E 15
				continue;
			}
E 14
D 3
			if (!(upper||lower||digit))
E 3
I 3
			if (!(upper || lower || digit))
E 3
				continue;
			allflags = setflags(2);
			tmode.sg_flags = allflags & 0xffff;
			allflags >>= 16;
			if (crmod || NL)
				tmode.sg_flags |= CRMOD;
			if (upper || UC)
				tmode.sg_flags |= LCASE;
			if (lower || LC)
				tmode.sg_flags &= ~LCASE;
			ioctl(0, TIOCSETP, &tmode);
			ioctl(0, TIOCSLTC, &ltc);
			ioctl(0, TIOCLSET, &allflags);
D 7
			putchr('\n');
I 3
			oflush();
E 3
			makeenv(env);
E 7
I 2
			signal(SIGINT, SIG_DFL);
E 2
D 7
			execle(LO, "login", name, (char *)0, env);
E 7
I 7
			for (i = 0; environ[i] != (char *)0; i++)
				env[i] = environ[i];
			makeenv(&env[i]);
I 18

			/* 
			 * this is what login was doing anyway.
			 * soon we rewrite getty completely.
			 */
			set_ttydefaults(0);
I 31
			limit.rlim_max = RLIM_INFINITY;
			limit.rlim_cur = RLIM_INFINITY;
			(void)setrlimit(RLIMIT_CPU, &limit);
E 31
E 18
			execle(LO, "login", "-p", name, (char *) 0, env);
I 13
			syslog(LOG_ERR, "%s: %m", LO);
E 13
E 7
			exit(1);
		}
		alarm(0);
		signal(SIGALRM, SIG_DFL);
I 2
		signal(SIGINT, SIG_IGN);
E 2
		if (NX && *NX)
			tname = NX;
	}
}

I 26
static int
E 26
getname()
{
I 19
	register int c;
E 19
	register char *np;
D 19
	register c;
E 19
	char cs;

I 2
	/*
D 3
	 * interrupt may happen if we use CBREAK mode
E 3
I 3
	 * Interrupt may happen if we use CBREAK mode
E 3
	 */
	if (setjmp(intrupt)) {
		signal(SIGINT, SIG_IGN);
		return (0);
	}
	signal(SIGINT, interrupt);
E 2
	tmode.sg_flags = setflags(0);
	ioctl(0, TIOCSETP, &tmode);
	tmode.sg_flags = setflags(1);
	prompt();
I 4
	if (PF > 0) {
I 5
		oflush();
E 5
		sleep(PF);
		PF = 0;
	}
E 4
	ioctl(0, TIOCSETP, &tmode);
D 19
	crmod = 0;
	upper = 0;
	lower = 0;
	digit = 0;
E 19
I 19
	crmod = digit = lower = upper = 0;
E 19
	np = name;
	for (;;) {
I 2
		oflush();
E 2
D 19
		if (read(0, &cs, 1) <= 0)
E 19
I 19
		if (read(STDIN_FILENO, &cs, 1) <= 0)
E 19
			exit(0);
		if ((c = cs&0177) == 0)
			return (0);
D 3
		if (c==EOT)
E 3
I 3
		if (c == EOT)
E 3
			exit(1);
D 3
		if (c=='\r' || c=='\n' || np >= &name[16])
E 3
I 3
D 7
		if (c == '\r' || c == '\n' || np >= &name[16])
E 7
I 7
		if (c == '\r' || c == '\n' || np >= &name[sizeof name]) {
			putf("\r\n");
E 7
E 3
			break;
D 7

E 7
I 7
		}
E 7
D 3
		if (c>='a' && c <='z')
E 3
I 3
D 15
		if (c >= 'a' && c <= 'z')
E 15
I 15
		if (islower(c))
E 15
E 3
D 19
			lower++;
E 19
I 19
			lower = 1;
E 19
D 3
		else if (c>='A' && c<='Z') {
E 3
I 3
D 7
		else if (c >= 'A' && c <= 'Z') {
E 7
I 7
D 15
		else if (c >= 'A' && c <= 'Z')
E 15
I 15
		else if (isupper(c))
E 15
E 7
E 3
D 19
			upper++;
E 19
I 19
			upper = 1;
E 19
D 2
		} else if (c==ERASE) {
E 2
I 2
D 3
		} else if (c==ERASE || c=='#' || c=='\b') {
E 3
I 3
D 7
		} else if (c == ERASE || c == '#' || c == '\b') {
E 7
I 7
		else if (c == ERASE || c == '#' || c == '\b') {
E 7
E 3
E 2
			if (np > name) {
				np--;
				if (tmode.sg_ospeed >= B1200)
					puts("\b \b");
				else
					putchr(cs);
			}
			continue;
D 2
		} else if (c==KILL) {
E 2
I 2
D 3
		} else if (c==KILL || c=='@') {
E 3
I 3
		} else if (c == KILL || c == '@') {
E 3
E 2
			putchr(cs);
			putchr('\r');
			if (tmode.sg_ospeed < B1200)
				putchr('\n');
			/* this is the way they do it down under ... */
			else if (np > name)
				puts("                                     \r");
			prompt();
			np = name;
			continue;
D 7
		} else if (c == ' ')
			c = '_';
		else if (c >= '0' && c <= '9')
E 7
I 7
D 15
		} else if (c >= '0' && c <= '9')
E 15
I 15
		} else if (isdigit(c))
E 15
E 7
			digit++;
D 7
		if (IG && (c < ' ' || c > 0176))
E 7
I 7
		if (IG && (c <= ' ' || c > 0176))
E 7
			continue;
		*np++ = c;
		putchr(cs);
	}
I 2
	signal(SIGINT, SIG_IGN);
E 2
	*np = 0;
	if (c == '\r')
D 19
		crmod++;
E 19
I 19
		crmod = 1;
E 19
	if (upper && !lower && !LC || UC)
		for (np = name; *np; np++)
			if (isupper(*np))
				*np = tolower(*np);
	return (1);
}

static
short	tmspc10[] = {
	0, 2000, 1333, 909, 743, 666, 500, 333, 166, 83, 55, 41, 20, 10, 5, 15
};

I 26
static void
E 26
putpad(s)
	register char *s;
{
	register pad = 0;
	register mspc10;

	if (isdigit(*s)) {
		while (isdigit(*s)) {
			pad *= 10;
			pad += *s++ - '0';
		}
		pad *= 10;
		if (*s == '.' && isdigit(s[1])) {
			pad += s[1] - '0';
			s += 2;
		}
	}

	puts(s);
	/*
	 * If no delay needed, or output speed is
	 * not comprehensible, then don't try to delay.
	 */
	if (pad == 0)
		return;
	if (tmode.sg_ospeed <= 0 ||
	    tmode.sg_ospeed >= (sizeof tmspc10 / sizeof tmspc10[0]))
		return;

	/*
D 19
	 * Round up by a half a character frame,
	 * and then do the delay.
E 19
I 19
	 * Round up by a half a character frame, and then do the delay.
E 19
	 * Too bad there are no user program accessible programmed delays.
D 19
	 * Transmitting pad characters slows many
	 * terminals down and also loads the system.
E 19
I 19
	 * Transmitting pad characters slows many terminals down and also
	 * loads the system.
E 19
	 */
	mspc10 = tmspc10[tmode.sg_ospeed];
	pad += mspc10 / 2;
	for (pad /= mspc10; pad > 0; pad--)
		putchr(*PC);
}

I 26
static void
E 26
puts(s)
	register char *s;
{
D 19

E 19
	while (*s)
		putchr(*s++);
}

I 2
char	outbuf[OBUFSIZ];
int	obufcnt = 0;

I 26
static void
E 26
E 2
putchr(cc)
I 26
	int cc;
E 26
{
	char c;

	c = cc;
D 23
	c |= partab[c&0177] & 0200;
	if (OP)
		c ^= 0200;
E 23
I 23
	if (!NP) {
		c |= partab[c&0177] & 0200;
		if (OP)
			c ^= 0200;
	}
E 23
D 2
	write(1, &c, 1);
E 2
I 2
	if (!UB) {
		outbuf[obufcnt++] = c;
		if (obufcnt >= OBUFSIZ)
			oflush();
	} else
D 19
		write(1, &c, 1);
E 19
I 19
		write(STDOUT_FILENO, &c, 1);
E 19
}

I 26
static void
E 26
oflush()
{
	if (obufcnt)
D 19
		write(1, outbuf, obufcnt);
E 19
I 19
		write(STDOUT_FILENO, outbuf, obufcnt);
E 19
	obufcnt = 0;
E 2
}

I 26
static void
E 26
prompt()
{

	putf(LM);
	if (CO)
		putchr('\n');
}

I 26
static void
E 26
putf(cp)
	register char *cp;
{
I 6
D 7
	char *tp;
E 7
I 7
D 16
	char *ttyn, *slash;
E 16
I 16
D 19
	char *slash;
E 16
	char datebuffer[60];
E 19
E 7
E 6
	extern char editedhost[];
I 6
D 7
	extern char *ttyname();
E 7
I 7
D 16
	extern char *ttyname(), *rindex();
E 16
I 16
D 19
	extern char *rindex();
E 19
I 19
	time_t t;
D 20
	char *slash, db[100];
E 20
I 20
D 21
	char *fmt, *slash, db[100];
E 21
I 21
	char *slash, db[100];
E 21
E 20
E 19
E 16
E 7
E 6

	while (*cp) {
		if (*cp != '%') {
			putchr(*cp++);
			continue;
		}
		switch (*++cp) {

I 7
		case 't':
D 16
			ttyn = ttyname(0);
E 16
D 26
			slash = rindex(ttyn, '/');
E 26
I 26
			slash = strrchr(ttyn, '/');
E 26
			if (slash == (char *) 0)
				puts(ttyn);
			else
				puts(&slash[1]);
			break;

E 7
		case 'h':
			puts(editedhost);
I 6
			break;

D 7
		case 't':
			tp = ttyname(0);
			if (tp != (char *)0) {
				if (strncmp(tp, "/dev/", 5) == 0)
					tp += 5;
				puts(tp);
			}
E 7
I 7
D 21
		case 'd':
E 21
I 21
		case 'd': {
D 22
			char fmt[] = "%l:% %P on %A, %d %B %Y";
E 22
I 22
			static char fmt[] = "%l:% %P on %A, %d %B %Y";
E 22

			fmt[4] = 'M';		/* I *hate* SCCS... */
E 21
D 19
			get_date(datebuffer);
			puts(datebuffer);
E 19
I 19
			(void)time(&t);
D 20
			(void)strftime(db,
			    sizeof(db), "%l:%M%P on %A, %d %B %Y", &t);
E 20
I 20
D 21
						/* SCCS *likes* %M%... */
			fmt = "%l:% %P on %A, %d %B %Y";
			fmt[4] = 'M';
			(void)strftime(db, sizeof(db), fmt, &t);
E 21
I 21
			(void)strftime(db, sizeof(db), fmt, localtime(&t));
E 21
E 20
			puts(db);
E 19
E 7
E 6
			break;
I 21
		}
E 21

		case '%':
			putchr('%');
			break;
		}
		cp++;
	}
}
E 1
