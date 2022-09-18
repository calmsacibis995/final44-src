h01428
s 00001/00003/00354
d D 8.2 94/02/01 22:18:18 cgd 13 12
c get SLIOCGUNIT definition from <net/slip.h>, kill unneeded includes
e
s 00005/00005/00352
d D 8.1 93/06/06 14:05:53 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00026/00357
d D 5.7 92/07/15 11:40:19 karels 11 10
c check in for Mike K. by TK; guess they're working...
e
s 00002/00002/00381
d D 5.6 91/03/02 17:15:57 bostic 10 9
c ANSI
e
s 00001/00001/00382
d D 5.5 91/02/26 11:48:13 karels 9 8
c fix error string
e
s 00072/00048/00311
d D 5.4 91/02/13 12:18:31 karels 8 7
c now working, tested with termios; setuid(0) to allow privileged operations
c in slip.log{in,out}; use getlogin() rather than getenv("USER");
c allow "sliplogin hostname linename"
e
s 00018/00025/00341
d D 5.3 90/07/01 14:55:52 bostic 7 6
c put pathnames in pathnames.h, reorg include files
e
s 00229/00296/00137
d D 5.2 90/07/01 11:29:31 trent 6 5
c hybrid version of van's & old sliplogin (major cleanup)
e
s 00015/00001/00418
d D 5.1 90/06/25 18:09:55 bostic 5 4
c Berkeley copyright/header
e
s 00068/00061/00351
d D 1.4 90/02/06 10:28:03 sam 4 3
c for karels; switchover to new tty ioctls & session handling; DCD checking
e
s 00102/00014/00310
d D 1.3 89/06/30 10:15:36 karels 3 2
c william's changes
e
s 00042/00046/00282
d D 1.2 89/06/30 10:14:15 sam 2 1
c checked in for sam; converted to termios/BSD
e
s 00328/00000/00000
d D 1.1 89/06/08 17:19:38 sam 1 0
c date and time created 89/06/08 17:19:38 by sam
e
u
U
t
T
I 5
/*-
D 12
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * %sccs.include.redist.c%
 */

E 5
I 1
#ifndef lint
I 5
D 12
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 12
I 12
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 12
#endif /* not lint */

#ifndef lint
E 5
D 4
static char *sccsid = "@(#)sliplogin.c	1.3	MS/ACF	89/04/18";
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
I 5
#endif /* not lint */

E 5
D 6
/* from static char *sccsid = "@(#)sliplogin.c	1.3	MS/ACF	89/04/18"; */
E 4
D 5
#endif
E 5

E 6
/*
 * sliplogin.c
I 3
 * [MUST BE RUN SUID, SLOPEN DOES A SUSER()!]
E 3
 *
 * This program initializes its own tty port to be an async TCP/IP interface.
D 6
 * It merely sets up the SLIP module all by its lonesome on the STREAMS stack,
 * initializes the network interface, and pauses forever waiting for hangup.
E 6
I 6
 * It sets the line discipline to slip, invokes a shell script to initialize
 * the network interface, then pauses forever waiting for hangup.
E 6
 *
 * It is a remote descendant of several similar programs with incestuous ties:
 * - Kirk Smith's slipconf, modified by Richard Johnsson @ DEC WRL.
 * - slattach, probably by Rick Adams but touched by countless hordes.
 * - the original sliplogin for 4.2bsd, Doug Kingston the mover behind it.
D 6
 * - a simple slattach-like program used to test the STREAMS SLIP code.
E 6
 *
D 6
 * There are three basic forms of usage:
E 6
I 6
 * There are two forms of usage:
E 6
 *
 * "sliplogin"
D 8
 * Invoked simply as "sliplogin" and a realuid != 0, the program looks up
 * the uid in /etc/passwd, and then the username in the file /etc/hosts.slip.
 * If and entry is found, the line on fd0 is configured for SLIP operation
E 8
I 8
 * Invoked simply as "sliplogin", the program looks up the username
 * in the file /etc/slip.hosts.
 * If an entry is found, the line on fd0 is configured for SLIP operation
E 8
 * as specified in the file.
 *
D 8
 * "sliplogin IPhost1 </dev/ttyb"
E 8
I 8
 * "sliplogin IPhostlogin </dev/ttyb"
E 8
 * Invoked by root with a username, the name is looked up in the
D 8
 * /etc/hosts.slip file and if found fd0 is configured as in case 1.
E 8
I 8
 * /etc/slip.hosts file and if found fd0 is configured as in case 1.
E 8
D 6
 *
 * "sliplogin 192.100.1.1 192.100.1.2 255.255.255.0 < /dev/ttyb"
 * Finally, if invoked with a remote addr, local addr, and optionally
 * a net mask, the line on fd0 is setup as specified if the user is root.
 *
 * Doug Kingston 8810??		- logging + first pass at adding I_STR ioctl's
 * Rayan Zachariassen 881011	- version for SunOS STREAMS SLIP
E 6
 */

D 7
#include <sys/types.h>
E 7
I 6
#include <sys/param.h>
E 6
#include <sys/socket.h>
D 2
#include <sys/stropts.h>
E 2
D 6
#include <sys/termios.h>
E 6
D 2
#include <sys/ttold.h>
#include <sys/sockio.h>
E 2
I 2
D 8
#include <sys/ioctl.h>
E 8
I 7
#include <sys/signal.h>
E 7
E 2
#include <sys/file.h>
#include <sys/syslog.h>
D 6

D 2
#include <sys/slip.h>

E 2
#include <netinet/in.h>
#include <net/if.h>
I 3
#include <net/if_slvar.h>	/* XXX */
E 3

E 6
D 7
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
E 7
#include <netdb.h>
D 6

E 6
D 7
#include <signal.h>
D 6
#include <strings.h>
#include <pwd.h>
E 6
I 6
#include <string.h>
E 7
I 7

E 7
D 8
#if defined(BSD4_4)
#define TERMIOS
E 8
I 8
#if BSD >= 199006
#define POSIX
E 8
#endif
D 8
#ifdef TERMIOS
E 8
I 8
#ifdef POSIX
E 8
#include <sys/termios.h>
I 8
#include <sys/ioctl.h>
E 8
E 6
D 2
#ifdef BSD >= 43
E 2
#include <ttyent.h>
I 8
#else
#include <sgtty.h>
E 8
I 6
#endif
D 13
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_slvar.h>
E 13
I 13
#include <net/slip.h>
E 13
E 6
D 2
#endif
E 2

I 2
D 6
#define	SLIPIFNAME	"sl"
E 6
I 6
D 7
#ifndef ACCESSFILE
#define ACCESSFILE "/etc/slip.hosts"
#endif
#ifndef LOGINFILE
#define LOGINFILE "/etc/slip.login"
#define LOGOUTFILE "/etc/slip.logout"
#endif
E 7
I 7
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include "pathnames.h"
E 7
E 6

D 6
#define ADDR	1
#define MASK	2
E 6
D 7

E 7
E 2
D 3
#define	DCD_CHECK_INTERVAL 0	/* if > 0, time between automatic DCD checks */
E 3
I 3
D 4
#define	DCD_CHECK_INTERVAL 5	/* if > 0, time between automatic DCD checks */
E 4
I 4
D 6
#define	DCD_CHECK_INTERVAL 0	/* if > 0, time between automatic DCD checks */
E 4
E 3
#define	DCD_SETTLING_TIME 1	/* time between DCD change and status check */
E 6
I 6
int	unit;
D 7
int     slip_mode;
E 7
I 7
D 11
int	slip_mode;
E 11
E 7
int	speed;
I 8
int	uid;
E 8
char	loginargs[BUFSIZ];
D 8
char	loginfile[BUFSIZ];
char	logoutfile[BUFSIZ];
E 8
I 8
char	loginfile[MAXPATHLEN];
E 8
char	loginname[BUFSIZ];
E 6

D 6
int gotalarm = 0;
int timeleft = DCD_CHECK_INTERVAL;
E 6
I 6
D 11
struct slip_modes {
	char	*sm_name;
	int	sm_value;
}	 modes[] = {
	"normal",	0,              
	"compress",	SC_COMPRESS,   
	"noicmp",	SC_NOICMP,
	"autocomp",	SC_AUTOCOMP
};
E 6

E 11
D 4
void
alarm_handler()
{
D 3
	if (timeleft > DCD_SETTLING_TIME)
E 3
I 3
	/*if (timeleft > DCD_SETTLING_TIME)
E 3
		(void) alarm(timeleft-DCD_SETTLING_TIME);
D 3
	else
E 3
I 3
	else */
E 3
		(void) alarm(DCD_CHECK_INTERVAL);
	gotalarm = 1;
	timeleft = 0;
}

E 4
D 6
#if	defined(SIGDCD) && SIGDCD > 0
E 6
void
D 6
dcd_handler()
E 6
I 6
findid(name)
	char *name;
E 6
{
D 6
#if	DCD_SETTLING_TIME > 0
	timeleft = alarm(DCD_SETTLING_TIME);
#else
	gotalarm = 1;
#endif	/* DCD_SETTLING_TIME */
}
#endif
E 6
I 6
	FILE *fp;
	static char slopt[5][16];
	static char laddr[16];
	static char raddr[16];
	static char mask[16];
	char user[16];
	int i, j, n;
E 6

I 4
D 6
#if DCD_CHECK_INTERVAL > 0
void
alarm_handler()
{
#ifdef SIGDCD
	if (timeleft > DCD_SETTLING_TIME)
		(void) alarm(timeleft-DCD_SETTLING_TIME);
	else
#endif /* SIGDCD */
		(void) alarm(DCD_CHECK_INTERVAL);
	gotalarm = 1;
	timeleft = 0;
}
E 6
I 6
	(void)strcpy(loginname, name);
D 7
	if ((fp = fopen(ACCESSFILE, "r")) == NULL) {
		perror(ACCESSFILE);
		syslog(LOG_ERR, "%s: %m\n", ACCESSFILE);
		exit(3);
E 7
I 7
	if ((fp = fopen(_PATH_ACCESS, "r")) == NULL) {
		(void)fprintf(stderr, "sliplogin: %s: %s\n",
		    _PATH_ACCESS, strerror(errno));
		syslog(LOG_ERR, "%s: %m\n", _PATH_ACCESS);
		exit(1);
E 7
	}
	while (fgets(loginargs, sizeof(loginargs) - 1, fp)) {
E 6
D 7

E 7
E 4
D 6
/* Use TIOCMGET to test if DCD is low on the port of the passed descriptor */
E 6
I 6
		if (ferror(fp))
			break;
		n = sscanf(loginargs, "%15s%*[ \t]%15s%*[ \t]%15s%*[ \t]%15s%*[ \t]%15s%*[ \t]%15s%*[ \t]%15s%*[ \t]%15s%*[ \t]%15s\n",
                        user, laddr, raddr, mask, slopt[0], slopt[1], 
			slopt[2], slopt[3], slopt[4]);
		if (user[0] == '#' || isspace(user[0]))
			continue;
		if (strcmp(user, name) != 0)
			continue;
E 6

D 6
int
lowdcd(fd)
	int fd;
{
	int mbits;
E 6
I 6
D 11
		slip_mode = 0;
		for (i = 0; i < n - 4; i++) {
			for (j = 0; j < sizeof(modes)/sizeof(struct slip_modes);
				j++) {
				if (strcmp(modes[j].sm_name, slopt[i]) == 0) {
					slip_mode |= modes[j].sm_value;
					break;
				}
			}
		}
E 6

E 11
D 6
	if (ioctl(fd, TIOCMGET, (caddr_t)&mbits) < 0)
		return 1;	/* port is dead, we die */
	return !(mbits & TIOCM_CAR);
E 6
I 6
		/*
		 * we've found the guy we're looking for -- see if
		 * there's a login file we can use.  First check for
		 * one specific to this host.  If none found, try for
		 * a generic one.
		 */
D 7
		(void)sprintf(loginfile, "%s.%s", LOGINFILE, name);
E 7
I 7
		(void)sprintf(loginfile, "%s.%s", _PATH_LOGIN, name);
E 7
D 8
		if (access(loginfile, R_OK|X_OK)) {
E 8
I 8
		if (access(loginfile, R_OK|X_OK) != 0) {
E 8
D 7
			(void)strcpy(loginfile, LOGINFILE);
			(void)strcpy(logoutfile, LOGOUTFILE);
E 7
I 7
			(void)strcpy(loginfile, _PATH_LOGIN);
D 8
			(void)strcpy(logoutfile, _PATH_LOGOUT);
E 8
E 7
			if (access(loginfile, R_OK|X_OK)) {
				fputs("access denied - no login file\n",
				      stderr);
				syslog(LOG_ERR,
				       "access denied for %s - no %s\n",
D 7
				       name, LOGINFILE);
E 7
I 7
				       name, _PATH_LOGIN);
E 7
				exit(5);
			}
D 8
		} else
D 7
			(void)sprintf(logoutfile, "%s.%s", LOGOUTFILE, name);
E 7
I 7
			(void)sprintf(logoutfile, "%s.%s", _PATH_LOGOUT, name);
E 8
I 8
		}
E 8
E 7

		(void) fclose(fp);
		return;
	}
	(void)fprintf(stderr, "SLIP access denied for %s\n", name);
	syslog(LOG_ERR, "SLIP access denied for %s\n", name);
	exit(4);
	/* NOTREACHED */
E 6
}
I 4
D 6
#endif /* DCD_CHECK_INTERVAL > 0 */
E 6
E 4

I 3
D 4
/* Use TIOCMGET to test if DTR is low on the port of the passed descriptor */

int
lowdtr(fd)
	int fd;
{
	int mbits;

	if (ioctl(fd, TIOCMGET, (caddr_t)&mbits) < 0)
		return 1;	/* port is dead, we die */
	return ((mbits & TIOCM_DTR) == TIOCM_DTR);
}

E 4
E 3
D 6
char	*Accessfile = "/etc/hosts.slip";
E 6
I 6
char *
sigstr(s)
	int s;
{
	static char buf[32];
E 6

D 6
extern char *malloc(), *ttyname();
extern struct passwd *getpwuid();
E 6
I 6
	switch (s) {
	case SIGHUP:	return("HUP");
	case SIGINT:	return("INT");
	case SIGQUIT:	return("QUIT");
	case SIGILL:	return("ILL");
	case SIGTRAP:	return("TRAP");
	case SIGIOT:	return("IOT");
	case SIGEMT:	return("EMT");
	case SIGFPE:	return("FPE");
	case SIGKILL:	return("KILL");
	case SIGBUS:	return("BUS");
	case SIGSEGV:	return("SEGV");
	case SIGSYS:	return("SYS");
	case SIGPIPE:	return("PIPE");
	case SIGALRM:	return("ALRM");
	case SIGTERM:	return("TERM");
	case SIGURG:	return("URG");
	case SIGSTOP:	return("STOP");
	case SIGTSTP:	return("TSTP");
	case SIGCONT:	return("CONT");
	case SIGCHLD:	return("CHLD");
	case SIGTTIN:	return("TTIN");
	case SIGTTOU:	return("TTOU");
	case SIGIO:	return("IO");
	case SIGXCPU:	return("XCPU");
	case SIGXFSZ:	return("XFSZ");
	case SIGVTALRM:	return("VTALRM");
	case SIGPROF:	return("PROF");
	case SIGWINCH:	return("WINCH");
#ifdef SIGLOST
	case SIGLOST:	return("LOST");
#endif
	case SIGUSR1:	return("USR1");
	case SIGUSR2:	return("USR2");
	}
	(void)sprintf(buf, "sig %d", s);
	return(buf);
}
E 6

D 6
char	*dstaddr, *localaddr, *netmask;
I 3
int	slip_mode, unit;
E 3

I 3
struct slip_modes {
	char	*sm_name;
	int	sm_value;
}	 modes[] = {
	"normal",	0,		/* slip "standard" ala Rick Adams */
	"compress",	SC_COMPRESS,	/* Van Jacobsen's tcp header comp. */
	"noicmp",	SC_NOICMP,	/* Sam's(?) ICMP suppression */
} ;

D 4
/*
 * If we are uncerimoniously dumped, bitch
 */
E 4
void
E 6
I 6
D 10
int
E 10
I 10
void
E 10
E 6
D 4
hup_handler()
E 4
I 4
hup_handler(s)
	int s;
E 4
{
I 8
	char logoutfile[MAXPATHLEN];

	(void)sprintf(logoutfile, "%s.%s", _PATH_LOGOUT, loginname);
	if (access(logoutfile, R_OK|X_OK) != 0)
		(void)strcpy(logoutfile, _PATH_LOGOUT);
E 8
I 6
	if (access(logoutfile, R_OK|X_OK) == 0) {
D 8
		char logincmd[2*BUFSIZ+32];
E 8
I 8
		char logincmd[2*MAXPATHLEN+32];
E 8
E 6
D 4
syslog(LOG_NOTICE, "connection closed: process aborted %s%d: remote %s\n",
		SLIPIFNAME, unit, dstaddr);
E 4
I 4

D 6
	syslog(LOG_INFO,
	    "%s%d: connection closed: process aborted, sig %d, remote %s\n",
	    SLIPIFNAME, unit, s, dstaddr);
	if (close(0) < 0)
		syslog(LOG_ERR, "(hup) close: %m");
	else
		syslog(LOG_INFO, "(hup) close completed");
E 4
	exit(1) ;
E 6
I 6
D 8
		(void)sprintf(logincmd, "%s %d %d %s", logoutfile, unit, speed,
E 8
I 8
		(void) sprintf(logincmd, "%s %d %d %s", logoutfile, unit, speed,
E 8
			      loginargs);
D 8
		(void)system(logincmd);
E 8
I 8
		(void) system(logincmd);
E 8
	}
D 8
	(void)close(0);
E 8
I 8
	(void) close(0);
E 8
	syslog(LOG_INFO, "closed %s slip unit %d (%s)\n", loginname, unit,
	       sigstr(s));
	exit(1);
	/* NOTREACHED */
E 6
}

E 3
main(argc, argv)
	int argc;
	char *argv[];
{
D 2
	int	fd, s, unit;
E 2
I 2
D 3
	int	fd, s, unit, ldisc;
E 2
	struct	termios tios;
E 3
I 3
D 8
	int	fd, s, ldisc, odisc;
E 8
I 8
	int fd, s, ldisc, odisc;
E 8
I 6
	char *name;
D 8
#ifdef TERMIOS
E 6
	struct	termios tios, otios;
E 8
I 8
#ifdef POSIX
	struct termios tios, otios;
E 8
E 3
D 6
	struct	ifreq ifr;
E 6
I 6
#else
D 8
	struct	sgttyb tty, otty;
E 8
I 8
	struct sgttyb tty, otty;
E 8
#endif
	char logincmd[2*BUFSIZ+32];
	extern uid_t getuid();
E 6

I 6
	if ((name = strrchr(argv[0], '/')) == NULL)
		name = argv[0];
E 6
	s = getdtablesize();
	for (fd = 3 ; fd < s ; fd++)
D 6
		close(fd);
D 2

E 2
	openlog("sliplogin", LOG_PID, LOG_DAEMON);
D 2

E 2
	if (getuid() == 0) {
		if (argc <= 1) {
			fprintf(stderr, "Usage: %s loginname\n", argv[0]);
			fprintf(stderr, "   or: %s dstaddr localaddr [mask]\n",
					argv[0]);
E 6
I 6
		(void) close(fd);
	openlog(name, LOG_PID, LOG_DAEMON);
I 8
	uid = getuid();
E 8
	if (argc > 1) {
D 8
		if (argc > 2) {
			(void)fprintf(stderr, "Usage: %s loginname\n", argv[0]);
E 6
			exit(1);
D 6
		} else if (argc == 2) {
			findid(argv[1]);
			fprintf(stderr, "local %s remote %s mask %s\n",
				localaddr, dstaddr, netmask);
		} if (argc > 2) {
			if (argc < 3 || argc > 4) {
				fprintf(stderr,
					"Usage: %s dstaddr localaddr [mask]\n",
					argv[0]);
				exit(1);
			}
			dstaddr = argv[1];
			localaddr = argv[2];
			if (argc == 4)
				netmask = argv[3];
			else
				netmask = "default";
E 6
		}
E 8
I 6
		findid(argv[1]);

E 6
D 4
	} else
		findid((char *)0);
D 2

	/* ensure that the slip line is our controlling terminal */
E 2
I 2
D 3
	/* disassociate from current controlling terminal */
E 3
I 3
	/* ensure that the slip line is our controlling terminal */
E 3
E 2
	if ((fd = open("/dev/tty", O_RDONLY, 0)) >= 0) {
		(void) ioctl(fd, TIOCNOTTY, 0);
		(void) close(fd);
I 3
		fd = open(ttyname(0), O_RDWR, 0);
		if (fd >= 0)
E 4
I 4
		/*
		 * Disassociate from current controlling terminal, if any,
		 * and ensure that the slip line is our controlling terminal.
		 */
D 6
#if !defined(BSD) || BSD < 198810
E 6
I 6
D 8
#ifdef TERMIOS
		(void) setsid();
		(void) ioctl(0, TIOCSCTTY, (caddr_t)0);
E 8
I 8
#ifdef POSIX
		if (fork() > 0)
			exit(0);
		if (setsid() != 0)
			perror("setsid");
E 8
#else
E 6
		if ((fd = open("/dev/tty", O_RDONLY, 0)) >= 0) {
D 6
			(void) ioctl(fd, TIOCNOTTY, 0);
E 6
I 6
			extern char *ttyname();

			(void) ioctl(fd, TIOCNOTTY, (caddr_t)0);
E 6
E 4
			(void) close(fd);
I 4
			/* open slip tty again to acquire as controlling tty? */
			fd = open(ttyname(0), O_RDWR, 0);
			if (fd >= 0)
				(void) close(fd);
		}
E 4
		(void) setpgrp(0, getpid());
E 3
D 2
		fd = open(ttyname(0), O_RDWR, 0);
		if (fd >= 0)
			(void) close(fd);
		(void) setpgrp(0, getpid());
E 2
D 4
	}
E 4
I 4
D 6
#else
		(void) setsid();
		(void) ioctl(0, TIOCSCTTY, 0); /* not sure this will work */
E 6
#endif
I 8
		if (argc > 2) {
			if ((fd = open(argv[2], O_RDWR)) == -1) {
				perror(argv[2]);
				exit(2);
			}
			(void) dup2(fd, 0);
			if (fd > 2)
				close(fd);
		}
#ifdef TIOCSCTTY
		if (ioctl(0, TIOCSCTTY, (caddr_t)0) != 0)
			perror("ioctl (TIOCSCTTY)");
#endif
E 8
D 6
	} else
		findid((char *)0);
E 4
D 2

E 2
I 2
D 3
	/* ensure that the slip line is our new controlling terminal */
	(void) setpgrp(0, getpid());
	(void) ioctl(0, TIOCSCTTY, 0);
E 3
E 2
	fchmod(0, 0600);
E 6
I 6
	} else {
D 8
		extern char *getenv();
E 8
I 8
		extern char *getlogin();
E 8

D 8
		if ((name = getenv("USER")) == NULL) {
E 8
I 8
		if ((name = getlogin()) == NULL) {
E 8
			(void) fprintf(stderr, "access denied - no username\n");
D 8
			syslog(LOG_ERR, "access denied - no username\n");
E 8
I 8
			syslog(LOG_ERR, "access denied - getlogin returned 0\n");
E 8
			exit(1);
		}
		findid(name);
	}
	(void) fchmod(0, 0600);
	(void) fprintf(stderr, "starting slip login for %s\n", loginname);
D 8
#ifdef TERMIOS
E 8
I 8
#ifdef POSIX
E 8
E 6
D 2

	/* pop all streams modules */
	while (ioctl(0, I_POP, 0) == 0)
		continue;

E 2
	/* set up the line parameters */
D 2
	if (ioctl(0, TCGETS, (caddr_t)&tios) < 0) {
		syslog(LOG_ERR, "ioctl (TCGETS): %m");
E 2
I 2
D 4
	if (ioctl(0, TCGETA, (caddr_t)&tios) < 0) {
		syslog(LOG_ERR, "ioctl (TCGETA): %m");
E 4
I 4
D 8
	if (ioctl(0, TIOCGETA, (caddr_t)&tios) < 0) {
		syslog(LOG_ERR, "ioctl (TIOCGETA): %m");
E 8
I 8
	if (tcgetattr(0, &tios) < 0) {
		syslog(LOG_ERR, "tcgetattr: %m");
E 8
E 4
E 2
		exit(1);
	}
I 3
D 4
	otios = tios ;
E 3
	tios.c_cflag &= 0xf;	/* only save the speed */
	tios.c_cflag |= CS8|CREAD|HUPCL;
E 4
I 4
	otios = tios;
D 8
	tios.c_cflag = CS8|CREAD|HUPCL;
E 4
	tios.c_iflag = IGNBRK;
D 2
	if (ioctl(0, TCSETS, (caddr_t)&tios) < 0) {
		syslog(LOG_ERR, "ioctl (TCSETS): %m");
E 2
I 2
	tios.c_oflag = tios.c_lflag = 0;
D 4
	if (ioctl(0, TCSETA, (caddr_t)&tios) < 0) {
D 3
		syslog(LOG_ERR, "ioctl (TCSETA): %m");
E 3
I 3
		syslog(LOG_ERR, "ioctl (TCSETA) (1): %m");
E 4
I 4
	if (ioctl(0, TIOCSETA, (caddr_t)&tios) < 0) {
		syslog(LOG_ERR, "ioctl (TIOCSETA) (1): %m");
E 8
I 8
	cfmakeraw(&tios);
	tios.c_iflag &= ~IMAXBEL;
	if (tcsetattr(0, TCSAFLUSH, &tios) < 0) {
		syslog(LOG_ERR, "tcsetattr: %m");
E 8
E 4
E 3
E 2
		exit(1);
	}
I 8
	speed = cfgetispeed(&tios);
E 8
I 6
#else
	/* set up the line parameters */
	if (ioctl(0, TIOCGETP, (caddr_t)&tty) < 0) {
		syslog(LOG_ERR, "ioctl (TIOCGETP): %m");
		exit(1);
	}
	otty = tty;
	speed = tty.sg_ispeed;
	tty.sg_flags = RAW | ANYP;
	if (ioctl(0, TIOCSETP, (caddr_t)&tty) < 0) {
		syslog(LOG_ERR, "ioctl (TIOCSETP): %m");
		exit(1);
	}
#endif
E 6
I 3
	/* find out what ldisc we started with */
	if (ioctl(0, TIOCGETD, (caddr_t)&odisc) < 0) {
		syslog(LOG_ERR, "ioctl(TIOCGETD) (1): %m");
		exit(1);
	}
E 3
D 2

	/* push the SLIP module */
	if (ioctl(0, I_PUSH, "slip") < 0) {
		syslog(LOG_ERR, "ioctl (I_PUSH): %m");
E 2
I 2
	ldisc = SLIPDISC;
	if (ioctl(0, TIOCSETD, (caddr_t)&ldisc) < 0) {
D 3
		syslog(LOG_ERR, "ioctl(TIOCSETD): %m");
E 3
I 3
D 4
		syslog(LOG_ERR, "ioctl(TIOCSETD) (1): %m");
E 4
I 4
		syslog(LOG_ERR, "ioctl(TIOCSETD): %m");
E 4
E 3
E 2
		exit(1);
	}
D 2

E 2
	/* find out what unit number we were assigned */
D 2
	if (ioctl(0, SLIOGUNIT, (caddr_t)&unit) < 0) {
		syslog(LOG_ERR, "ioctl (SLIOGUNIT): %m");
E 2
I 2
D 8
	if (ioctl(0, TIOCGETD, (caddr_t)&unit) < 0) {
D 3
		syslog(LOG_ERR, "ioctl (TIOCGETD): %m");
E 3
I 3
		syslog(LOG_ERR, "ioctl (TIOCGETD) (2): %m");
E 8
I 8
	if (ioctl(0, SLIOCGUNIT, (caddr_t)&unit) < 0) {
D 9
		syslog(LOG_ERR, "ioctl (SLIOCGUNIT) (2): %m");
E 9
I 9
		syslog(LOG_ERR, "ioctl (SLIOCGUNIT): %m");
E 9
E 8
E 3
E 2
		exit(1);
	}
D 2

	syslog(LOG_NOTICE, "attaching slip%d: local %s remote %s mask %s\n",
		unit, localaddr, dstaddr, netmask);

E 2
I 2
D 4
	syslog(LOG_NOTICE, "attaching %s%d: local %s remote %s mask %s\n",
E 4
I 4
D 6
	syslog(LOG_INFO, "attaching %s%d: local %s remote %s mask %s\n",
E 4
		SLIPIFNAME, unit, localaddr, dstaddr, netmask);
#ifdef notdef
E 2
	/* set the local and remote interface addresses */
	s = socket(AF_INET, SOCK_DGRAM, 0);
D 2

E 2
	if (getuid() != 0 || argc == 4) {
		(void) sprintf(ifr.ifr_name, "%s%d", SLIPIFNAME, unit);
D 2
		in_getaddr(netmask, &ifr.ifr_addr);
E 2
I 2
		in_getaddr(netmask, &ifr.ifr_addr, MASK);
E 2
		if (ioctl(s, SIOCSIFNETMASK, (caddr_t)&ifr) < 0) {
			syslog(LOG_ERR, "ioctl (SIOCSIFNETMASK): %m");
E 6
I 6
	(void) signal(SIGHUP, hup_handler);
	(void) signal(SIGTERM, hup_handler);

	syslog(LOG_INFO, "attaching slip unit %d for %s\n", unit, loginname);
	(void)sprintf(logincmd, "%s %d %d %s", loginfile, unit, speed,
		      loginargs);
	/*
	 * aim stdout and errout at /dev/null so logincmd output won't
	 * babble into the slip tty line.
	 */
D 8
	(void)close(1);
	if ((fd = open("/dev/null", O_WRONLY, 0)) != 1) {
E 8
I 8
	(void) close(1);
D 10
	if ((fd = open("/dev/null", O_WRONLY)) != 1) {
E 10
I 10
	if ((fd = open(_PATH_DEVNULL, O_WRONLY)) != 1) {
E 10
E 8
		if (fd < 0) {
			syslog(LOG_ERR, "open /dev/null: %m");
E 6
			exit(1);
		}
I 6
D 8
		(void)dup2(fd, 1);
		(void)close(fd);
E 8
I 8
		(void) dup2(fd, 1);
		(void) close(fd);
E 8
E 6
	}
D 2

E 2
D 6
	(void) sprintf(ifr.ifr_name, "%s%d", SLIPIFNAME, unit);
D 2
	in_getaddr(dstaddr, &ifr.ifr_addr);
E 2
I 2
	in_getaddr(dstaddr, &ifr.ifr_addr, ADDR);
E 2
	if (ioctl(s, SIOCSIFDSTADDR, (caddr_t)&ifr) < 0) {
		syslog(LOG_ERR, "ioctl (SIOCSIFDSTADDR): %m");
		exit(1);
E 6
I 6
D 8
	(void)dup2(1,2);
E 8
I 8
	(void) dup2(1, 2);

	/*
	 * Run login and logout scripts as root (real and effective);
	 * current route(8) is setuid root, and checks the real uid
	 * to see whether changes are allowed (or just "route get").
	 */
	(void) setuid(0);
E 8
	if (s = system(logincmd)) {
		syslog(LOG_ERR, "%s login failed: exit status %d from %s",
		       loginname, s, loginfile);
		(void) ioctl(0, TIOCSETD, (caddr_t)&odisc);
		exit(6);
E 6
D 11
	}
D 2

E 2
D 6
	(void) sprintf(ifr.ifr_name, "%s%d", SLIPIFNAME, unit);
D 2
	in_getaddr(localaddr, &ifr.ifr_addr);
E 2
I 2
	in_getaddr(localaddr, &ifr.ifr_addr, ADDR);
E 2
	/* this has the side-effect of marking the interface up */
	if (ioctl(s, SIOCSIFADDR, (caddr_t)&ifr) < 0) {
		syslog(LOG_ERR, "ioctl (SIOCSIFADDR): %m");
		exit(1);
	}
I 2
#else
	/* XXX -- give up for now and just invoke ifconfig XXX */
	{ char cmd[256];
	  sprintf(cmd, "/sbin/ifconfig %s%d inet %s %s netmask %s",
	      SLIPIFNAME, unit, localaddr, dstaddr, netmask);
	  system(cmd);
	}
I 4
#endif
E 6
E 4
I 3
	if (ioctl(0, SLIOCSFLAGS, (caddr_t)&slip_mode) < 0) {
		syslog(LOG_ERR, "ioctl (SLIOCSFLAGS): %m");
		exit(1);
E 11
	}
E 3
D 4
#endif
E 4
E 2

D 6
	/* set up signal handlers */
#if	defined(SIGDCD) && SIGDCD > 0
	(void) signal(SIGDCD, dcd_handler);
#endif
	(void) sigblock(sigmask(SIGALRM));
D 4
	(void) signal(SIGALRM, alarm_handler);
	/* a SIGHUP will kill us */
E 4
I 3
	(void) signal(SIGHUP, hup_handler);
	(void) signal(SIGTERM, hup_handler);
E 3

I 4
#if DCD_CHECK_INTERVAL > 0
E 4
	/* timeleft = 60 * 60 * 24 * 365 ; (void) alarm(timeleft); */
I 4
	(void) signal(SIGALRM, alarm_handler);
E 4
I 3
	(void) alarm(DCD_CHECK_INTERVAL);
I 4
#endif
E 4
E 3

E 6
	/* twiddle thumbs until we get a signal */
D 6
	while (1) {
E 6
I 6
	while (1)
E 6
		sigpause(0);
I 4
D 6
#if DCD_CHECK_INTERVAL > 0
E 4
		(void) sigblock(sigmask(SIGALRM));
		if (gotalarm && lowdcd(0))
			break;
I 3
D 4
		if (gotalarm && lowdtr(0))
			break;
E 4
E 3
		gotalarm = 0;
I 4
#endif /* DCD_CHECK_INTERVAL > 0 */
E 4
	}
E 6

I 4
D 6
#ifdef notdef
E 4
D 3
	/* closing the descriptor should pop the slip module */
E 3
I 3
	if (lowdcd(0))
		syslog(LOG_NOTICE,
			"connection closed: loss of carrier %s%d: remote %s\n",
			SLIPIFNAME, unit, dstaddr);
D 4
	else if (lowdtr(0))
		syslog(LOG_NOTICE,
			"connection closed by foreign host %s%d: remote %s\n",
			SLIPIFNAME, unit, dstaddr);
E 4
I 4
#endif
E 4

	if (ioctl(0, TIOCSETD, (caddr_t)&odisc) < 0) {
		syslog(LOG_ERR, "ioctl(TIOCSETD) (2): %m");
		exit(1);
	}
D 4
	if (ioctl(0, TCSETA, (caddr_t)&otios) < 0) {
		syslog(LOG_ERR, "ioctl (TCSETA) (2): %m");
E 4
I 4
	if (ioctl(0, TIOCSETA, (caddr_t)&otios) < 0) {
		syslog(LOG_ERR, "ioctl (TIOCSETA) (2): %m");
		exit(1);
	}
	if (close(0) < 0) {
		syslog(LOG_ERR, "close: %m");
E 4
		exit(1);
	}
E 3
	exit(0);
}

findid(name)
	char *name;
{
	char buf[BUFSIZ];
	static char mode[16];
	static char laddr[16];
	static char raddr[16];
	static char mask[16];
	char user[16];
	FILE *fp;
	struct passwd *pw;
	int n;

	if (name == NULL && (pw = getpwuid(getuid())) == NULL) {
		fprintf(stderr, "Your UID (%d) is unknown\n", getuid());
		syslog(LOG_ERR, "UID (%d) is unknown\n", getuid());
		exit(1);
	} else if (name == NULL)
		name = pw->pw_name;
	if ((fp = fopen(Accessfile, "r")) == NULL) {
		perror(Accessfile);
		syslog(LOG_ERR, "%s: %m\n", Accessfile);
		exit(3);
	}
	while (fgets(buf, sizeof(buf) - 1, fp)) {
		if (ferror(fp))
			break;
		n = sscanf(buf, "%15s%*[ \t]%15s%*[ \t]%15s%*[ \t]%15s%*[ \t]%15s\n",
			user, mode, laddr, raddr, mask);
		if (user[0] == '#' || n != 5)
			continue;
		if (strcmp(user, name) == 0) {
D 3
			/* eventually deal with "mode" */
E 3
I 3
			char *p,*q; int val, i, domore;

			p = q = mode;	val = 0;
		loop:
			while (isalnum(*p)) p++;
			if(ispunct(*p) || *p == '\0') {
				if(ispunct(*p)) domore = 1; else domore = 0;
				*p++ = '\0' ; 
				for (i = 0; i <
					sizeof(modes)/sizeof(struct slip_modes)
					 ; i++) {
					if (strcmp(modes[i].sm_name, q) == 0) {
						val |= modes[i].sm_value ;
						break;
					} ;
}
				q = p;
				if(domore)goto loop;
			}

			slip_mode = val ;
E 3
			localaddr = laddr;
			dstaddr = raddr;
			netmask = mask;
			fclose(fp);
			return 0;
		}
		if (feof(fp))
			break;
	}
	fputs("SLIP access denied\n", stderr);
	syslog(LOG_ERR, "SLIP access denied for %s\n", name);
	exit(4);
}

D 2
in_getaddr(s, saddr)
E 2
I 2
in_getaddr(s, saddr, which)
E 2
	char *s;
	struct sockaddr *saddr;
I 2
	int which;
E 2
{
	register struct sockaddr_in *sin = (struct sockaddr_in *)saddr;
	struct hostent *hp;
	struct netent *np;
	int val;
	extern struct in_addr inet_makeaddr();
 
	bzero((caddr_t)saddr, sizeof *saddr);
D 2
	sin->sin_family = AF_INET;
E 2
I 2
	if (which == ADDR) {
		sin->sin_len = sizeof (*sin);
		sin->sin_family = AF_INET;
	} else
		sin->sin_len = 8;
E 2
	val = inet_addr(s);
	if (val != -1) {
		sin->sin_addr.s_addr = val;
		return;
	}
	hp = gethostbyname(s);
	if (hp) {
		sin->sin_family = hp->h_addrtype;
		bcopy(hp->h_addr, (char *)&sin->sin_addr, hp->h_length);
		return;
	}
	np = getnetbyname(s);
	if (np) {
		sin->sin_family = np->n_addrtype;
		sin->sin_addr = inet_makeaddr(np->n_net, INADDR_ANY);
		return;
	}
	fprintf(stderr, "sliplogin: %s: bad value\n", s);
	syslog(LOG_ERR, "%s: bad value\n", s);
	exit(1);
E 6
I 6
	/* NOTREACHED */
E 6
}
D 2

E 2
E 1
