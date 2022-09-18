h65251
s 00005/00005/00421
d D 8.1 93/06/05 11:22:05 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00424
d D 5.10 93/05/03 15:53:34 hibler 10 9
c fix a merge error in the last revision
e
s 00068/00013/00358
d D 5.9 93/05/03 15:48:52 hibler 9 8
c add flowcontrol option (F) and Annex support (A)
e
s 00010/00000/00361
d D 5.8 93/03/08 16:52:44 elan 8 7
c Added security hack that will clobber the arguments so that private
c information is not left around for the world to see.
e
s 00002/00001/00359
d D 5.7 93/02/27 10:27:28 bostic 7 6
c fix usage message
e
s 00004/00003/00356
d D 5.6 92/03/16 10:46:02 mckusick 6 5
c handle null's like newlines
e
s 00092/00049/00267
d D 5.5 92/03/09 23:01:54 mckusick 5 4
c latest version from Mike
e
s 00100/00045/00216
d D 5.4 92/03/09 23:00:53 karels 4 3
c checkin for Mike by Kirk
e
s 00039/00028/00222
d D 5.3 90/11/05 15:33:35 mckusick 3 2
c further attempts to get restart (from Mike)
e
s 00049/00016/00201
d D 5.2 90/10/20 18:13:28 mckusick 2 1
c update from Mike for restarting after hangup
e
s 00217/00000/00000
d D 5.1 90/10/20 17:26:27 mckusick 1 0
c date and time created 90/10/20 17:26:27 by mckusick
e
u
U
t
T
I 4

E 4
I 1
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 11
char copyright[] =
D 4
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
E 4
I 4
"%Z% Copyright (c) 1990, 1991 The Regents of the University of California.\n\
E 4
 All rights reserved.\n";
E 11
I 11
static char copyright[] =
"%Z% Copyright (c) 1990, 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 11
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
I 4
#if BSD >= 199006
#define POSIX
#endif
#ifdef POSIX
#include <sys/termios.h>
#include <sys/ioctl.h>
#else
E 4
D 2
#include <sys/signal.h>
E 2
I 2
#include <sgtty.h>
I 4
#endif
E 4
E 2
#include <sys/socket.h>
#include <sys/syslog.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_slvar.h>
D 2
#include <sgtty.h>
E 2
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
I 2
#include <signal.h>
E 2

#define DEFAULT_BAUD    B9600
int     speed = DEFAULT_BAUD;
I 9
#define	FC_NONE		0	/* flow control: none */
#define	FC_SW		1	/* flow control: software (XON/XOFF) */
#define	FC_HW		2	/* flow control: hardware (RTS/CTS) */
int	flowcontrol = FC_NONE;
char	*annex;
E 9
D 2
int     slipdisc = SLIPDISC;
E 2
I 2
int	hup;
I 5
int	logged_in;
int	wait_time = 60;		/* then back off */
#define	MAXTRIES	6	/* w/60 sec and doubling, takes an hour */
#define	PIDFILE		"/var/run/startslip.pid"

E 5
E 2
#ifdef DEBUG
int	debug = 1;
#undef LOG_ERR
#undef LOG_INFO
#define syslog fprintf
#define LOG_ERR stderr
#define LOG_INFO stderr
#else
int	debug = 0;
#endif
#define	printd	if (debug) printf

main(argc, argv)
	int argc;
	char **argv;
{
	extern char *optarg;
	extern int optind;
I 8
	char *cp, **ap;
E 8
D 2
	int ch;
E 2
I 2
	int ch, disc;
E 2
D 5
	int fd = -1, sighup();
D 4
	FILE *wfd;
E 4
I 4
	FILE *wfd = NULL;
E 5
I 5
	int fd = -1;
	void sighup();
	FILE *wfd = NULL, *pfd;
E 5
E 4
	char *dialerstring = 0, buf[BUFSIZ];
I 4
D 5
	int first = 1;
E 5
I 5
	int first = 1, tries = 0;
	int pausefirst = 0;
	int pid;
E 5
#ifdef POSIX
	struct termios t;
#else
E 4
	struct sgttyb sgtty;
D 4
	int first = 0;
E 4
I 4
#endif
E 4

D 4
	while ((ch = getopt(argc, argv, "ds:")) != EOF)
		switch(ch) {
E 4
I 4
D 5
	while ((ch = getopt(argc, argv, "ds:b:")) != EOF)
E 5
I 5
D 9
	while ((ch = getopt(argc, argv, "db:s:p:")) != EOF)
E 9
I 9
	while ((ch = getopt(argc, argv, "db:s:p:A:F:")) != EOF)
E 9
E 5
		switch (ch) {
E 4
		case 'd':
			debug = 1;
			break;
I 4
#ifdef POSIX
		case 'b':
			speed = atoi(optarg);
			break;
#endif
I 5
		case 'p':
			pausefirst = atoi(optarg);
			break;
E 5
E 4
		case 's':
			dialerstring = optarg;
			break;
I 9
		case 'A':
			annex = optarg;
			break;
		case 'F':
#ifdef POSIX
			if (strcmp(optarg, "none") == 0)
				flowcontrol = FC_NONE;
			else if (strcmp(optarg, "sw") == 0)
				flowcontrol = FC_SW;
			else if (strcmp(optarg, "hw") == 0)
				flowcontrol = FC_HW;
			else {
				(void)fprintf(stderr,
					"flow control: none, sw, hw\n");
				exit(1);
			}
			break;
#else
			(void)fprintf(stderr, "flow control not supported\n");
			exit(1);
#endif
E 9
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 3)
		usage();

	openlog("startslip", LOG_PID, LOG_DAEMON);

#if BSD <= 43
D 2
	if (debug == 0 && (fd = open("/dev/tty", 0))) {
E 2
I 2
	if (debug == 0 && (fd = open("/dev/tty", 0)) >= 0) {
E 2
		ioctl(fd, TIOCNOTTY, 0);
		close(fd);
I 4
		fd = -1;
E 4
	}
#endif

D 4
	signal(SIGHUP, sighup);
E 4
I 4
	if (debug)
		setbuf(stdout, NULL);
I 5
	
	if (pfd = fopen(PIDFILE, "r")) {
		pid = 0;
		fscanf(pfd, "%d", &pid);
		if (pid > 0)
			kill(pid, SIGUSR1);
		fclose(pfd);
	}
E 5
E 4
restart:
I 5
	logged_in = 0;
	if (++tries > MAXTRIES) {
		syslog(LOG_ERR, "exiting after %d tries\n", tries);
		/* ???
		if (first)
		*/
			exit(1);
	}

E 5
I 4
	/*
	 * We may get a HUP below, when the parent (session leader/
	 * controlling process) exits; ignore HUP until into new session.
	 */
	signal(SIGHUP, SIG_IGN);
E 4
I 2
	hup = 0;
E 2
D 4
	printd("restart\n");
	if (fd >= 0)
		close(fd);
D 3
	if (first)
E 3
I 3
	if (!first) {
		if (fork() > 0)
			exit(0);
		printd("(pid %d)\n", getpid());
#ifdef TIOCSCTTY
		if (setsid() == -1)
			perror("setsid");
E 4
I 4
D 5
	if (fork() > 0)
E 5
I 5
	if (fork() > 0) {
		if (pausefirst)
			sleep(pausefirst);
		if (first)
			printd("parent exit\n");
E 5
		exit(0);
I 5
	}
	pausefirst = 0;
E 5
#ifdef POSIX
	if (setsid() == -1)
		perror("setsid");
E 4
#endif
D 4
	} else
E 3
		sleep(2);
E 4
I 4
D 5
	printd("restart: pid %d: close", getpid());
E 5
I 5
	pid = getpid();
	printd("restart: pid %d: ", pid);
	if (pfd = fopen(PIDFILE, "w")) {
		fprintf(pfd, "%d\n", pid);
		fclose(pfd);
	}
E 5
	if (wfd) {
I 5
		printd("fclose, ");
E 5
		fclose(wfd);
		wfd == NULL;
	}
	if (fd >= 0) {
I 5
		printd("close, ");
E 5
		close(fd);
		sleep(5);
	}
D 5
	printd(", open");
E 5
I 5
	printd("open");
E 5
E 4
	if ((fd = open(argv[0], O_RDWR)) < 0) {
		perror(argv[0]);
D 5
		syslog(LOG_ERR, "startslip: open %s: %m\n", argv[0]);
E 5
I 5
		syslog(LOG_ERR, "open %s: %m\n", argv[0]);
E 5
		if (first)
			exit(1);
		else {
D 5
			sleep(5*60);
E 5
I 5
			sleep(wait_time * tries);
E 5
			goto restart;
		}
	}
D 4
	printd("open %d\n", fd);
E 4
I 4
	printd(" %d", fd);
E 4
I 3
#ifdef TIOCSCTTY
	if (ioctl(fd, TIOCSCTTY, 0) < 0)
		perror("ioctl (TIOCSCTTY)");
#endif
I 4
	signal(SIGHUP, sighup);
D 5
	sleep(2);		/* wait for flakey line to settle */
	if (hup)
		goto restart;
E 5
E 4
E 3
I 2
	if (debug) {
		if (ioctl(fd, TIOCGETD, &disc) < 0)
			perror("ioctl(TIOCSETD)");
D 4
		printf("disc was %d\n", disc);
E 4
I 4
		printf(" (disc was %d)", disc);
E 4
	}
	disc = TTYDISC;
	if (ioctl(fd, TIOCSETD, &disc) < 0) {
	        perror("ioctl(TIOCSETD)");
D 5
		syslog(LOG_ERR, "startslip: %s: ioctl (TIOCSETD 0): %m\n",
E 5
I 5
		syslog(LOG_ERR, "%s: ioctl (TIOCSETD 0): %m\n",
E 5
		    argv[0]);
	}
E 2
D 4
	if (dialerstring) {
		(void) write(fd, dialerstring, strlen(dialerstring));
		(void) write(fd, "\n", 1);
E 4
I 4
	printd(", ioctl");
#ifdef POSIX
	if (tcgetattr(fd, &t) < 0) {
		perror("tcgetattr");
D 5
		syslog(LOG_ERR, "startslip: %s: tcgetattr: %m\n", argv[0]);
E 5
I 5
		syslog(LOG_ERR, "%s: tcgetattr: %m\n", argv[0]);
E 5
	        exit(2);
E 4
	}
I 4
	cfmakeraw(&t);
I 5
	t.c_iflag &= ~IMAXBEL;
E 5
D 9
	t.c_cflag |= CRTSCTS;
E 9
I 9
	switch (flowcontrol) {
	case FC_HW:
		t.c_cflag |= (CRTS_IFLOW|CCTS_OFLOW);
		break;
	case FC_SW:
		t.c_iflag |= (IXON|IXOFF);
		break;
	case FC_NONE:
		t.c_cflag &= ~(CRTS_IFLOW|CCTS_OFLOW);
		t.c_iflag &= ~(IXON|IXOFF);
		break;
	}
E 9
	cfsetspeed(&t, speed);
D 5
	if (tcsetattr(fd, TCSANOW, &t) < 0) {
E 5
I 5
	if (tcsetattr(fd, TCSAFLUSH, &t) < 0) {
E 5
		perror("tcsetattr");
D 5
		syslog(LOG_ERR, "startslip: %s: tcsetattr: %m\n", argv[0]);
E 5
I 5
		syslog(LOG_ERR, "%s: tcsetattr: %m\n", argv[0]);
E 5
	        if (first) 
			exit(2);
		else {
D 5
			sleep(5*60);
E 5
I 5
			sleep(wait_time * tries);
E 5
			goto restart;
		}
	}
#else
E 4
	if (ioctl(fd, TIOCGETP, &sgtty) < 0) {
	        perror("ioctl (TIOCGETP)");
I 4
D 5
		syslog(LOG_ERR, "startslip: %s: ioctl (TIOCGETP): %m\n",
E 5
I 5
		syslog(LOG_ERR, "%s: ioctl (TIOCGETP): %m\n",
E 5
		    argv[0]);
E 4
	        exit(2);
	}
	sgtty.sg_flags = RAW | ANYP;
	sgtty.sg_erase = sgtty.sg_kill = 0377;
	sgtty.sg_ispeed = sgtty.sg_ospeed = speed;
	if (ioctl(fd, TIOCSETP, &sgtty) < 0) {
	        perror("ioctl (TIOCSETP)");
D 5
		syslog(LOG_ERR, "startslip: %s: ioctl (TIOCSETP): %m\n",
E 5
I 5
		syslog(LOG_ERR, "%s: ioctl (TIOCSETP): %m\n",
E 5
		    argv[0]);
D 4
	        exit(2);
E 4
I 4
	        if (first) 
			exit(2);
		else {
D 5
			sleep(5*60);
E 5
I 5
			sleep(wait_time * tries);
E 5
			goto restart;
		}
E 4
	}
D 4
	printd("ioctl\n");
E 4
I 4
#endif
I 5
	sleep(2);		/* wait for flakey line to settle */
	if (hup)
		goto restart;

	wfd = fdopen(fd, "w+");
	if (wfd == NULL) {
		syslog(LOG_ERR, "can't fdopen slip line\n");
		exit(10);
	}
	setbuf(wfd, (char *)0);
E 5
	if (dialerstring) {
		printd(", send dialstring");
D 5
		(void) write(fd, dialerstring, strlen(dialerstring));
		(void) write(fd, "\r", 1);
	}
E 5
I 5
		fprintf(wfd, "%s\r", dialerstring);
	} else
		putc('\r', wfd);
E 5
	printd("\n");

E 4
	/*
	 * Log in
	 */
D 2
	wfd = fdopen(fd, "w");
E 2
I 2
D 5
	wfd = fdopen(fd, "w+");
E 2
D 4
	printd("fdopen\n");
E 4
	if (wfd == NULL) {
		syslog(LOG_ERR, "startslip: can't fdopen slip line\n");
		exit(10);
	}
E 5
D 4
	putc('\n', wfd);
E 4
I 4
	printd("look for login: ");
D 5
	putc('\r', wfd);
E 4
	while (fflush(wfd), getline(buf, BUFSIZ, fd) != NULL) {
I 2
		if (hup != 0)
E 5
I 5
	for (;;) {
		if (getline(buf, BUFSIZ, fd) == 0 || hup) {
			sleep(wait_time * tries);
E 5
D 3
			goto restart;
E 3
I 3
D 4
			goto cleanup;
E 4
I 4
			goto restart;
I 5
		}
E 5
E 4
E 3
E 2
D 9
	        if (bcmp(&buf[1], "ogin:", 5) == 0) {
	                fprintf(wfd, "%s\r", argv[1]);
I 6
			printd("Sent login: %s\n", argv[1]);
E 6
	                continue;
	        }
	        if (bcmp(&buf[1], "assword:", 8) == 0) {
	                fprintf(wfd, "%s\r", argv[2]);
I 6
			printd("Sent password: %s\n", argv[2]);
E 6
D 5
	                fflush(wfd);
E 5
	                break;
	        }
E 9
I 9
		if (annex) {
			if (bcmp(buf, annex, strlen(annex)) == 0) {
				fprintf(wfd, "slip\r");
				printd("Sent \"slip\"\n");
				continue;
			}
			if (bcmp(&buf[1], "sername:", 8) == 0) {
				fprintf(wfd, "%s\r", argv[1]);
				printd("Sent login: %s\n", argv[1]);
				continue;
			}
			if (bcmp(&buf[1], "assword:", 8) == 0) {
D 10
				fprintf(wfd, "%s\r", pbuf);
				printd("Sent password: %s\n", pbuf);
E 10
I 10
				fprintf(wfd, "%s\r", argv[2]);
				printd("Sent password: %s\n", argv[2]);
E 10
				break;
			}
		} else {
			if (bcmp(&buf[1], "ogin:", 5) == 0) {
				fprintf(wfd, "%s\r", argv[1]);
				printd("Sent login: %s\n", argv[1]);
				continue;
			}
			if (bcmp(&buf[1], "assword:", 8) == 0) {
				fprintf(wfd, "%s\r", argv[2]);
				printd("Sent password: %s\n", argv[2]);
				break;
			}
		}
E 9
	}
I 8
	
	/*
	 * Security hack.  Do not want private information such as the
	 * password and possible phone number to be left around.
	 * So we clobber the arguments.
	 */
	for (ap = argv - optind + 1; ap < argv + 3; ap++)
		for (cp = *ap; *cp != 0; cp++)
			*cp = '\0';
E 8
D 4
	printd("login\n");
E 4
I 4
D 5
	printd("setd");
E 5
I 5

E 5
E 4
	/*
	 * Attach
	 */
I 5
	printd("setd");
E 5
D 2
	if (ioctl(fd, TIOCSETD, &slipdisc) < 0) {
E 2
I 2
	disc = SLIPDISC;
	if (ioctl(fd, TIOCSETD, &disc) < 0) {
E 2
	        perror("ioctl(TIOCSETD)");
D 2
		syslog(LOG_ERR, "startslip: %s: ioctl (TIOCSETD): %m\n",
E 2
I 2
D 5
		syslog(LOG_ERR, "startslip: %s: ioctl (TIOCSETD SLIP): %m\n",
E 5
I 5
		syslog(LOG_ERR, "%s: ioctl (TIOCSETD SLIP): %m\n",
E 5
E 2
		    argv[0]);
	        exit(1);
	}
D 2
	slipdisc = SC_COMPRESS;
	if (ioctl(fd, SLIOCSFLAGS, (caddr_t)&slipdisc) < 0) {
E 2
I 2
D 4
	printd("setd\n");
E 4
D 5
	disc = SC_COMPRESS;
	if (ioctl(fd, SLIOCSFLAGS, (caddr_t)&disc) < 0) {
E 2
	        perror("ioctl(SLIOCFLAGS)");
		syslog(LOG_ERR, "ioctl (SLIOCSFLAGS): %m");
		exit(1);
	}
E 5
D 2
	printd("setd\n");
E 2
D 3
	if (!first++) {
		if (fork() > 0)
			exit(0);
#ifdef TIOCSCTTY
		if (setsid() == -1)
			perror("setsid");
D 2
		if (ioctl(fd, TIOCSCTTY, 0) < 0)
			perror("ioctl (TIOCSCTTY)");
E 2
#endif
		if (debug == 0) {
			close(0);
			close(1);
			close(2);
I 2
			(void) open("/dev/null", O_RDWR);
			(void) dup2(0, 1);
			(void) dup2(0, 2);
E 2
		}
E 3
I 3
D 4
	if (!first++ && debug == 0) {
E 4
I 4
	if (first && debug == 0) {
E 4
		close(0);
		close(1);
		close(2);
		(void) open("/dev/null", O_RDWR);
		(void) dup2(0, 1);
		(void) dup2(0, 2);
E 3
	}
I 2
D 3
#ifdef TIOCSCTTY
	if (ioctl(fd, TIOCSCTTY, 0) < 0)
		perror("ioctl (TIOCSCTTY)");
#endif
E 3
E 2
	(void) system("ifconfig sl0 up");
I 4
	printd(", ready\n");
I 5
	if (!first)
		syslog(LOG_INFO, "reconnected (%d tries).\n", tries);
E 5
	first = 0;
I 5
	tries = 0;
	logged_in = 1;
E 5
E 4
D 2
	sigpause(0L);
E 2
I 2
D 3
	while (hup == 0)
E 3
I 3
	while (hup == 0) {
E 3
		sigpause(0L);
E 2
D 3
	printd("fclose\n");
E 3
I 3
D 4
		printd("sigpause return ");
E 4
I 4
		printd("sigpause return\n");
E 4
	}
D 4
cleanup:
	printd("close\n");
E 3
	fclose(wfd);
I 3
	close(fd);
E 3
I 2
#ifdef TIOCSCTTY
	if (fork() > 0)
		exit(0);
I 3
	printd("(pid %d)\n", getpid());
E 3
	if (setsid() == -1)
		perror("setsid");
	sleep(5);
#endif
E 4
E 2
	goto restart;
}

I 5
void
E 5
sighup()
{

I 2
	printd("hup\n");
E 2
D 3
	syslog(LOG_INFO, "startslip: hangup signal\n");
E 3
I 3
D 5
	if (hup == 0)
		syslog(LOG_INFO, "startslip: hangup signal\n");
E 5
I 5
	if (hup == 0 && logged_in)
		syslog(LOG_INFO, "hangup signal\n");
E 5
E 3
I 2
	hup = 1;
E 2
}

getline(buf, size, fd)
	char *buf;
	int size, fd;
{
	register int i;
I 3
	int ret;
E 3

	size--;
	for (i = 0; i < size; i++) {
I 2
		if (hup)
			return (0);
E 2
D 3
	        if (read(fd, &buf[i], 1) == 1) {
E 3
I 3
	        if ((ret = read(fd, &buf[i], 1)) == 1) {
E 3
	                buf[i] &= 0177;
I 4
D 5
			if (debug)
				fprintf(stderr, "Got %d: \"%s\"\n", i + 1, buf);
E 5
E 4
D 6
	                if (buf[i] == '\r')
E 6
I 6
	                if (buf[i] == '\r' || buf[i] == '\0')
E 6
	                        buf[i] = '\n';
	                if (buf[i] != '\n' && buf[i] != ':')
	                        continue;
	                buf[i + 1] = '\0';
D 6
			if (debug)
D 2
				fprintf(stderr, "Got %d: \"%s\"\n", i, buf);
E 2
I 2
				fprintf(stderr, "Got %d: \"%s\"\n", i + 1, buf);
E 6
I 6
			printd("Got %d: \"%s\"\n", i + 1, buf);
E 6
E 2
	                return (i+1);
	        }
D 3
	        perror("read");
I 2
		sleep(5*60);
E 2
	        i--;
E 3
I 3
D 5
		if (ret < 0) {
			perror("getline: read (sleeping)");
E 5
I 5
		if (ret <= 0) {
			if (ret < 0)
				perror("getline: read");
			else
				fprintf(stderr, "read returned 0\n");
E 5
			buf[i] = '\0';
D 5
			sleep(60);
E 5
			printd("returning 0 after %d: \"%s\"\n", i, buf);
			return (0);
		}
E 3
	}
D 2
	return(NULL);
E 2
I 2
	return (0);
E 2
}

usage()
{
D 4
	fprintf(stderr, "usage: startslip [-d] [-s string] dev user passwd\n");
E 4
I 4
D 5
	fprintf(stderr, "usage: startslip [-d] [-b baudrate] [-s dialstring]%s",
		" dev user passwd\n");
E 5
I 5
D 7
	fprintf(stderr, "usage: startslip [-d] [-s string] dev user passwd\n");
E 7
I 7
	(void)fprintf(stderr,
D 9
	    "usage: startslip [-d] [-b speed] [-s string] dev user passwd\n");
E 9
I 9
	    "usage: startslip [-d] [-b speed] [-s string] [-A annexname] [-F flowcontrol] dev user passwd\n");
E 9
E 7
E 5
E 4
	exit(1);
}
E 1
