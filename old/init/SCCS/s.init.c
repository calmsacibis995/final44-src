h61105
s 00016/00015/00571
d D 5.19 91/03/25 17:49:43 karels 35 34
c (part from william) clean up the #ifdefs in main (slightly),
c use howto from args if present on any machine, default to 0
e
s 00012/00005/00574
d D 5.18 90/06/26 10:04:12 karels 34 33
c ignore SIGTSTP, HUP in rc; open console for writing, too!; more cleanup
e
s 00023/00018/00556
d D 5.17 90/06/24 14:16:19 karels 33 32
c fix shutdown bug in last delta; revoke console so single() doesn't fail;
c attempt some cleanup of #ifdef mess
e
s 00017/00004/00557
d D 5.16 90/05/27 20:13:42 mckusick 32 31
c add hp300 support from Utah
e
s 00035/00017/00526
d D 5.15 90/05/27 20:02:45 marc 31 30
c checked in for marc by mckusick
e
s 00010/00009/00533
d D 5.14 89/04/02 14:17:12 bostic 30 29
c add pathnames.h
e
s 00001/00003/00541
d D 5.13 88/09/22 11:26:37 bostic 29 28
c use constants in utmp.h
e
s 00006/00030/00538
d D 5.12 88/09/20 15:26:43 bostic 28 27
c use logwtmp()
e
s 00006/00054/00562
d D 5.11 88/08/31 12:18:43 bostic 27 26
c use library version of rmut
e
s 00001/00000/00615
d D 5.10 88/01/10 12:27:48 bostic 26 24
c declare merge() externally; ANSI C fix
e
s 00001/00000/00615
d R 5.10 87/12/26 13:03:41 bostic 25 24
c declare merege() externally, ANSI C fix
e
s 00002/00002/00613
d D 5.9 87/04/13 17:59:43 lepreau 24 23
c trivial speedup
e
s 00005/00006/00610
d D 5.8 87/02/17 16:51:40 bostic 23 22
c check for null pointers; bug report 4.3BSD/etc/35
e
s 00005/00002/00611
d D 5.7 86/10/13 15:01:53 sam 22 21
c tahoe's first register variable is r12
e
s 00004/00002/00609
d D 5.6 86/05/26 22:12:07 karels 21 20
c consistency, use SIGTERM once then SIGKILL's, uniform logging (once)
e
s 00001/00001/00610
d D 5.5 85/09/17 19:16:55 eric 20 19
c facilities in syslog
e
s 00001/00001/00610
d D 5.4 85/08/30 09:45:45 karels 19 18
c lengthen space for getty/window commands (70->200)
e
s 00089/00038/00522
d D 5.3 85/06/08 12:20:10 bloom 18 17
c Dynamically allocate structures instead of fixed size array
c 	(from ks@purdue-ecn)
e
s 00030/00010/00530
d D 5.2 85/06/05 14:38:18 karels 17 16
c unblock signals before fork, window mgr changes from jg
e
s 00009/00002/00531
d D 5.1 85/05/28 14:24:33 dist 16 15
c add copyright
e
s 00123/00074/00410
d D 4.15 85/04/01 12:38:41 ralph 15 14
c changes to exec a command from /etc/ttys besides getty, let getty open tty.
e
s 00010/00000/00474
d D 4.14 84/12/23 17:02:27 sam 14 13
c after logout give port selectors an opportunity to detect DTR 
c transition; also after proper login reset error detection code; from brl
e
s 00021/00066/00453
d D 4.13 84/05/07 11:36:52 root 13 12
c uses new getttyent(3) routines.
e
s 00160/00152/00359
d D 4.12 83/06/12 01:39:07 sam 12 11
c ostensibly make it work with new signals; lots of reformatting done as well
e
s 00007/00000/00504
d D 4.11 83/05/22 23:57:45 sam 11 10
c utmp changed format
e
s 00025/00000/00479
d D 4.10 82/12/22 06:22:43 pugs 10 9
c sun boot arg flags
e
s 00008/00003/00471
d D 4.9 82/12/07 21:29:54 pugs 9 8
c fix error messages in dfork
e
s 00001/00001/00473
d D 4.8 82/05/12 18:04:35 sam 8 7
c lost keywords (argh)
e
s 00020/00007/00454
d D 4.7 82/05/12 18:03:15 sam 7 6
c letting console be controlling tty -- causes vhangup on conosle
e
s 00024/00000/00437
d D 4.6 82/02/26 14:05:51 root 6 5
c timeout when terminals crazy
e
s 00028/00010/00409
d D 4.5 81/04/26 23:31:16 wnj 5 4
c dont write null wtmp entries; print console message when terminals are not openable
e
s 00051/00005/00368
d D 4.4 81/02/28 22:58:26 wnj 4 3
c new shutdown style
e
s 00032/00006/00341
d D 4.3 80/10/13 19:18:16 bill 3 2
c dont hang when kill 1 and procs hung
e
s 00024/00008/00323
d D 4.2 80/10/11 23:41:42 bill 2 1
c auto reboot stuff; use getty not getty.vm
e
s 00331/00000/00000
d D 4.1 80/10/01 17:27:08 bill 1 0
c date and time created 80/10/01 17:27:08 by bill
e
u
U
t
T
I 16
D 17

E 17
/*
D 21
 * Copyright (c) 1980 Regents of the University of California.
E 21
I 21
 * Copyright (c) 1980,1986 Regents of the University of California.
E 21
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

E 16
I 11
#ifndef lint
E 11
I 3
D 7
static	char *sccsid = "%W% (Berkeley) %G%";
E 7
I 7
D 8
static	char *sccsid = "@(#)init.c	4.6 (Berkeley) 2/26/82";
E 8
I 8
D 16
static	char *sccsid = "%W% (Berkeley) %G%";
I 11
#endif
E 16
I 16
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 16

E 11
E 8
E 7
E 3
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
D 30
#include <signal.h>
E 30
#include <sys/types.h>
D 28
#include <utmp.h>
E 28
D 30
#include <setjmp.h>
E 30
I 30
#include <sys/file.h>
#include <sys/signal.h>
E 30
I 2
#include <sys/reboot.h>
I 30
#include <sys/syslog.h>
#include <sys/stat.h>
I 31
#include <sys/ioctl.h>
E 31
#include <setjmp.h>
E 30
I 28
#include <utmp.h>
E 28
I 4
#include <errno.h>
I 12
D 30
#include <sys/file.h>
E 30
I 13
#include <ttyent.h>
I 15
D 21
#include <syslog.h>
E 21
I 21
D 30
#include <sys/syslog.h>
E 21
I 18
#include <sys/stat.h>
E 30
I 30
#include "pathnames.h"
E 30
E 18
E 15
E 13
E 12
E 4
E 2

D 28
#define	LINSIZ	sizeof(wtmp.ut_line)
E 28
I 28
D 29
struct utmp ut;
#define	LINSIZ	sizeof(ut.ut_line)
E 29
E 28
I 13
D 15
#define	TTYSIZ	16
E 15
I 15
D 19
#define	CMDSIZ	70	/* max string length for getty or window command*/
E 19
I 19
#define	CMDSIZ	200	/* max string length for getty or window command*/
E 19
E 15
E 13
D 18
#define	TABSIZ	100
#define	ALL	p = &itab[0]; p < &itab[TABSIZ]; p++
E 18
I 18
#define	ALL	p = itab; p ; p = p->next
E 18
#define	EVER	;;
#define SCPYN(a, b)	strncpy(a, b, sizeof(a))
#define SCMPN(a, b)	strncmp(a, b, sizeof(a))
I 12
D 15
#define	mask(s)	(1 << ((s)-1))
E 15
E 12

D 30
char	shell[]	= "/bin/sh";
E 30
I 30
char	shell[]	= _PATH_BSHELL;
E 30
D 2
char	getty[]	 = "/etc/getty.vm";
E 2
I 2
D 15
char	getty[]	 = "/etc/getty";
E 15
E 2
char	minus[]	= "-";
D 30
char	runc[]	= "/etc/rc";
D 13
char	ifile[]	= "/etc/ttys";
E 13
D 18
char	utmp[]	= "/etc/utmp";
E 18
I 18
char	utmpf[]	= "/etc/utmp";
E 18
D 28
char	wtmpf[]	= "/usr/adm/wtmp";
E 28
char	ctty[]	= "/dev/console";
E 30
I 30
char	runc[]	= _PATH_RC;
D 31
char	utmpf[]	= _PATH_UTMP;
E 31
char	ctty[]	= _PATH_CONSOLE;
E 30
D 15
char	dev[]	= "/dev/";
E 15

D 28
struct utmp wtmp;
E 28
D 13
struct
{
	char	line[LINSIZ];
	char	comn;
	char	flag;
} line;
E 13
struct	tab
{
D 29
	char	line[LINSIZ];
E 29
I 29
	char	line[UT_LINESIZE];
E 29
D 13
	char	comn;
E 13
I 13
D 15
	char	comn[TTYSIZ];
E 15
I 15
	char	comn[CMDSIZ];
E 15
E 13
	char	xflag;
	int	pid;
I 15
	int	wpid;		/* window system pid for SIGHUP	*/
	char	wcmd[CMDSIZ];	/* command to start window system process */
E 15
I 6
	time_t	gettytime;
	int	gettycnt;
I 17
	time_t	windtime;
	int	windcnt;
E 17
E 6
D 18
} itab[TABSIZ];
E 18
I 18
	struct	tab *next;
} *itab;
E 18

int	fi;
int	mergflag;
char	tty[20];
D 3
jmp_buf	sjbuf;
E 3
I 3
jmp_buf	sjbuf, shutpass;
I 4
D 28
time_t	time0;
E 28
E 4
E 3

D 31
int	reset();
I 4
int	idle();
E 31
E 4
char	*strcpy(), *strcat();
long	lseek();
I 31
void	idle(), merge(), reset();
E 31

I 10
D 12
#ifndef sun
E 12
I 12
D 15
struct	sigvec rvec = { reset, mask(SIGHUP), 0 };
E 15
I 15
struct	sigvec rvec = { reset, sigmask(SIGHUP), 0 };
E 15

I 18
D 31

E 31
E 18
D 22
#ifdef vax
E 22
I 22
D 32
#if defined(vax) || defined(tahoe)
E 32
I 32
D 33
#if defined(vax) || defined(tahoe) || defined(hp300)
E 32
E 22
E 12
E 10
main()
E 33
I 33
main(argc, argv)
	char **argv;
E 33
{
I 35
	/* insure proper semantics for setjmp/longjmp */
	static int howto, oldhowto, started = 0;
E 35
I 22
#if defined(tahoe)
	register int r12;		/* make sure r11 gets bootflags */
#endif
I 33
#if defined(vax) || defined(tahoe) || defined(hp300)
I 35
	/* howto passed in high-order register XXX */
E 35
E 33
E 22
I 2
	register int r11;		/* passed thru from boot */
I 10
D 12
#else sun
E 12
I 12
D 33
#else
E 12
main(argc, argv)
	char **argv;
{
E 33
D 12
#endif sun
E 12
I 12
D 35
#endif
E 35
I 32
#ifdef __GNUC__
D 35
	/* insure proper semantics for setjmp/longjmp */
	static
#endif
E 32
E 12
E 10
D 31
	int howto, oldhowto;
E 31
I 31
D 33
	int howto, oldhowto, started;
E 33
I 33
	int howto, oldhowto, started = 0;
E 33
E 31

I 33
#if defined(vax) || defined(tahoe) || defined(hp300)
	/* howto passed in high-order register XXX */
E 33
I 4
D 28
	time0 = time(0);
E 28
I 10
D 12
#ifndef sun
E 12
I 12
D 22
#ifdef vax
E 22
I 22
D 32
#if defined(vax) || defined(tahoe)
E 32
I 32
#ifdef __GNUC__
E 35
#ifdef hp300
	asm("movl d7,%0" : "=rm" (howto));
#else
	asm("movl r11,%0" : "=rm" (howto));
#endif
#else
D 33
#if defined(vax) || defined(tahoe) || defined(hp300)
E 33
E 32
E 22
E 12
E 10
E 4
	howto = r11;
I 10
D 12
#else sun
E 12
I 12
D 33
#else
I 31
	howto = 0;
E 33
I 33
#endif /* __GNUC__ */
D 35
#else  /* defined(vax) || defined(tahoe) || defined(hp300) */
E 35
I 35
#else  /* vax || tahoe || hp300 */
E 35
	/* howto passed as argument */
I 35
	howto = 0;
#endif  /* ! (vax || tahoe || hp300) */

	/*
	 * We expect a single options argument from the kernel.
	 * If it is present, we ignore anything in registers from above.
	 */
E 35
E 33
E 31
E 12
	if (argc > 1 && argv[1][0] == '-') {
		char *cp;

I 32
		howto = 0;
E 32
D 31
		howto = 0;
E 31
		cp = &argv[1][1];
		while (*cp) switch (*cp++) {
D 35
		case 'a':
			howto |= RB_ASKNAME;
E 35
I 35
#ifdef notyet
		case 'f':
			howto |= RB_FASTBOOT;
E 35
			break;
I 35
#endif
E 35
		case 's':
			howto |= RB_SINGLE;
			break;
		}
D 33
	} else {
E 33
I 33
D 35
	} else
E 33
		howto = RB_SINGLE;
D 33
	}
E 33
D 12
#endif sun
E 10
E 2
	setjmp(sjbuf);
	signal(SIGTERM, reset);
E 12
I 12
#endif
E 35
I 35
	}
E 35
I 32
D 33
#endif /* !__GNUC__ */
E 33
E 32
I 31
	if (getuid() != 0)
		exit(1);
E 31
I 15
D 20
	openlog("init", LOG_CONS|LOG_ODELAY, 0);
E 20
I 20
	openlog("init", LOG_CONS|LOG_ODELAY, LOG_AUTH);
I 31
	if (setsid() < 0)
		syslog(LOG_ERR, "setsid failed (initial) %m");
E 31
E 20
E 15
	sigvec(SIGTERM, &rvec, (struct sigvec *)0);
E 12
I 4
	signal(SIGTSTP, idle);
E 4
D 34
	signal(SIGSTOP, SIG_IGN);
E 34
D 4
	signal(SIGTSTP, SIG_IGN);
E 4
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
D 12
	for(EVER) {
E 12
I 12
	(void) setjmp(sjbuf);
D 31
	for (EVER) {
E 31
I 31
D 33
	for (started = 0; ; ) {
E 33
I 33
	for (; ; ) {
E 33
E 31
E 12
I 2
		oldhowto = howto;
		howto = RB_SINGLE;
E 2
D 3
		shutdown();
E 3
I 3
D 31
		if (setjmp(shutpass) == 0)
E 31
I 31
		if (started && setjmp(shutpass) == 0)
E 31
			shutdown();
I 31
		started = 1;
E 31
E 3
D 2
		single();
		runcom();
E 2
I 2
		if (oldhowto & RB_SINGLE)
			single();
		if (runcom(oldhowto) == 0) 
			continue;
E 2
		merge();
		multiple();
	}
}

I 3
D 31
int	shutreset();
E 31
I 31
void	shutreset();
E 31

E 3
shutdown()
{
	register i;
D 18
	register struct tab *p;
E 18
I 18
	register struct tab *p, *p1;
E 18

D 18
	close(creat(utmp, 0644));
E 18
I 18
D 31
	close(creat(utmpf, 0644));
E 31
E 18
	signal(SIGHUP, SIG_IGN);
D 12
	for(ALL) {
E 12
I 12
D 18
	for (ALL) {
E 18
I 18
	for (p = itab; p ; ) {
E 18
E 12
		term(p);
D 18
		p->line[0] = 0;
E 18
I 18
		p1 = p->next;
		free(p);
		p = p1;
E 18
	}
I 18
	itab = (struct tab *)0;
E 18
D 3
	signal(SIGALRM, reset);
	alarm(60);
E 3
I 3
	signal(SIGALRM, shutreset);
I 21
	(void) kill(-1, SIGTERM);	/* one chance to catch it */
	sleep(5);
E 21
	alarm(30);
E 3
D 12
	for(i=0; i<5; i++)
E 12
I 12
	for (i = 0; i < 5; i++)
E 12
		kill(-1, SIGKILL);
D 12
	while(wait((int *)0) != -1)
E 12
I 12
	while (wait((int *)0) != -1)
E 12
		;
	alarm(0);
I 3
	shutend();
}

D 23
char shutfailm[] = "WARNING: Something is hung (wont die); ps axl advised\n";
E 23
I 23
D 31
char shutfailm[] = "WARNING: Something is hung (won't die); ps axl advised\n";
E 31
I 31
char shutfailm[] = "init: WARNING: something is hung (won't die); ps axl advised\n";
E 31
E 23

I 31
void
E 31
shutreset()
{
	int status;

	if (fork() == 0) {
		int ct = open(ctty, 1);
		write(ct, shutfailm, sizeof (shutfailm));
		sleep(5);
		exit(1);
	}
	sleep(5);
	shutend();
	longjmp(shutpass, 1);
}

shutend()
{
D 4
	register i;
E 4
I 4
D 32
	register i, f;
E 32
I 32
	register i;
E 32
E 4

I 4
	acct(0);
E 4
E 3
	signal(SIGALRM, SIG_DFL);
D 12
	for(i=0; i<10; i++)
E 12
I 12
	for (i = 0; i < 10; i++)
E 12
		close(i);
I 4
D 12
	f = open(wtmpf, 1);
E 12
I 12
D 28
	f = open(wtmpf, O_WRONLY|O_APPEND);
E 12
	if (f >= 0) {
D 12
		lseek(f, 0L, 2);
E 12
		SCPYN(wtmp.ut_line, "~");
		SCPYN(wtmp.ut_name, "shutdown");
I 11
		SCPYN(wtmp.ut_host, "");
E 11
		time(&wtmp.ut_time);
		write(f, (char *)&wtmp, sizeof(wtmp));
		close(f);
	}
D 12
	return(1);
E 12
I 12
	return (1);
E 28
I 28
	logwtmp("~", "shutdown", "");
E 28
E 12
E 4
}

single()
{
	register pid;
I 4
	register xpid;
I 33
	int fd;
E 33
D 28
	extern	errno;
E 28
I 28
	extern int errno;
E 28
E 4

I 4
D 12
   do {
E 4
	pid = fork();
	if(pid == 0) {
/*
		alarm(300);
*/
		signal(SIGTERM, SIG_DFL);
		signal(SIGHUP, SIG_DFL);
		signal(SIGALRM, SIG_DFL);
		open(ctty, 2);
		dup(0);
		dup(0);
		execl(shell, minus, (char *)0);
		exit(0);
	}
D 4
	while(wait((int *)0) != pid)
		;
E 4
I 4
	while((xpid = wait((int *)0)) != pid)
		if (xpid == -1 && errno == ECHILD)
			break;
   } while (xpid == -1);
E 12
I 12
	do {
		pid = fork();
		if (pid == 0) {
			signal(SIGTERM, SIG_DFL);
			signal(SIGHUP, SIG_DFL);
			signal(SIGALRM, SIG_DFL);
I 13
			signal(SIGTSTP, SIG_IGN);
I 31
			if (setsid() < 0)
				syslog(LOG_ERR, "setsid failed (single): %m");
E 31
E 13
D 33
			(void) open(ctty, O_RDWR);
I 31
			if (ioctl(0, TIOCSCTTY, 0) < 0)
E 33
I 33
			(void) revoke(ctty);
			if ((fd = open(ctty, O_RDWR)) < 0) {
				syslog(LOG_ERR, "open %s: %m", ctty);
				exit(1);
			}
			if (ioctl(fd, TIOCSCTTY, 0) < 0)
E 33
				syslog(LOG_ERR, "TIOCSCTTY failed: %m");
E 31
D 33
			dup2(0, 1);
			dup2(0, 2);
E 33
I 33
			dup2(fd, 0);
			dup2(fd, 1);
			dup2(fd, 2);
			if (fd > 2)
				close(fd);
E 33
			execl(shell, minus, (char *)0);
I 23
			perror(shell);
E 23
			exit(0);
		}
		while ((xpid = wait((int *)0)) != pid)
			if (xpid == -1 && errno == ECHILD)
				break;
	} while (xpid == -1);
E 12
E 4
}

D 2
runcom()
E 2
I 2
runcom(oldhowto)
	int oldhowto;
E 2
{
D 32
	register pid, f;
E 32
I 32
	register pid;
E 32
I 2
D 34
	int status;
E 34
I 34
	int fd, status;
E 34
E 2

	pid = fork();
D 12
	if(pid == 0) {
		open("/", 0);
		dup(0);
		dup(0);
E 12
I 12
	if (pid == 0) {
D 31
		(void) open("/", O_RDONLY);
E 31
I 31
D 34
		(void) open(ctty, O_RDONLY);
E 31
		dup2(0, 1);
		dup2(0, 2);
E 34
I 34
		signal(SIGTSTP, SIG_IGN);
		signal(SIGHUP, SIG_IGN);
		if ((fd = open(ctty, O_RDWR)) < 0)
			syslog(LOG_ERR, "open %s: %m", ctty);
		else {
			dup2(fd, 0);
			dup2(fd, 1);
			dup2(fd, 2);
			if (fd > 2)
				close(fd);
		}
E 34
I 31
		if (setsid() < 0)
			syslog(LOG_ERR, "setsid failed (runcom) %m");
		if (ioctl(0, TIOCSCTTY, 0) < 0) 
			syslog(LOG_ERR, "TIOCSCTTY failed (runcom) %m");
E 31
E 12
D 2
		execl(shell, shell, runc, (char *)0);
		exit(0);
E 2
I 2
		if (oldhowto & RB_SINGLE)
			execl(shell, shell, runc, (char *)0);
		else
			execl(shell, shell, runc, "autoboot", (char *)0);
		exit(1);
E 2
	}
D 2
	while(wait((int *)0) != pid)
E 2
I 2
D 12
	while(wait(&status) != pid)
E 12
I 12
	while (wait(&status) != pid)
E 12
E 2
		;
I 2
D 12
	if(status)
		return(0);
E 2
	f = open(wtmpf, 1);
E 12
I 12
	if (status)
		return (0);
D 28
	f = open(wtmpf, O_WRONLY|O_APPEND);
E 12
	if (f >= 0) {
D 12
		lseek(f, 0L, 2);
E 12
		SCPYN(wtmp.ut_line, "~");
		SCPYN(wtmp.ut_name, "reboot");
I 11
		SCPYN(wtmp.ut_host, "");
E 11
D 4
		time(&wtmp.ut_time);
E 4
I 4
		if (time0) {
			wtmp.ut_time = time0;
			time0 = 0;
		} else
			time(&wtmp.ut_time);
E 4
		write(f, (char *)&wtmp, sizeof(wtmp));
		close(f);
	}
E 28
I 28
	logwtmp("~", "reboot", "");
E 28
I 2
D 12
	return(1);
E 12
I 12
	return (1);
E 12
E 2
}

I 26
D 31
int merge();
E 31
E 26
D 12
setmerge()
{

	signal(SIGHUP, setmerge);
	mergflag = 1;
}

E 12
I 12
D 15
struct	sigvec	mvec = { merge, mask(SIGTERM), 0 };
E 15
I 15
struct	sigvec	mvec = { merge, sigmask(SIGTERM), 0 };
E 15
/*
 * Multi-user.  Listen for users leaving, SIGHUP's
 * which indicate ttys has changed, and SIGTERM's which
 * are used to shutdown the system.
 */
E 12
multiple()
{
I 31
	extern int errno;
E 31
	register struct tab *p;
	register pid;
I 18
	int omask;
E 18

D 12
loop:
	mergflag = 0;
	signal(SIGHUP, setmerge);
	for(EVER) {
E 12
I 12
	sigvec(SIGHUP, &mvec, (struct sigvec *)0);
	for (EVER) {
E 12
		pid = wait((int *)0);
D 12
		if(mergflag) {
			merge();
			goto loop;
		}
		if(pid == -1)
E 12
I 12
D 31
		if (pid == -1)
E 31
I 31
/* SHOULD FIX THIS IN THE KERNEL */
		if (pid == -1 && errno != EINTR)
E 31
E 12
			return;
I 18
D 23
		omask = sigblock(SIGHUP);
E 23
I 23
		omask = sigblock(sigmask(SIGHUP));
E 23
E 18
D 12
		for(ALL)
			if(p->pid == pid || p->pid == -1) {
E 12
I 12
D 15
		for (ALL)
E 15
I 15
		for (ALL) {
			/* must restart window system BEFORE emulator */
			if (p->wpid == pid || p->wpid == -1)
				wstart(p);
E 15
			if (p->pid == pid || p->pid == -1) {
I 15
				/* disown the window system */
				if (p->wpid)
					kill(p->wpid, SIGHUP);
E 15
E 12
D 27
				rmut(p);
E 27
I 27
				cleanutmp(p);
E 27
				dfork(p);
			}
I 15
		}
I 18
		sigsetmask(omask);
E 18
E 15
	}
}

I 12
/*
 * Merge current contents of ttys file
 * into in-core table of configured tty lines.
 * Entered as signal handler for SIGHUP.
 */
#define	FOUND	1
#define	CHANGE	2
I 15
#define WCHANGE 4
E 15

I 31
void
E 31
merge()
{
	register struct tab *p;
I 13
	register struct ttyent *t;
I 18
	register struct tab *p1;
E 18
E 13

D 13
	fi = open(ifile, 0);
	if (fi < 0)
		return;
E 13
	for (ALL)
		p->xflag = 0;
D 13
	while (rline()) {
E 13
I 13
	setttyent();
	while (t = getttyent()) {
		if ((t->ty_status & TTY_ON) == 0)
			continue;
D 15
		strcpy(tty, dev);
		strcat(tty, t->ty_name);
		if (access(tty, R_OK|W_OK) < 0)
			continue;
E 15
E 13
		for (ALL) {
D 13
			if (SCMPN(p->line, line.line))
E 13
I 13
			if (SCMPN(p->line, t->ty_name))
E 13
				continue;
			p->xflag |= FOUND;
D 13
			if (line.comn != p->comn) {
E 13
I 13
			if (SCMPN(p->comn, t->ty_getty)) {
E 13
				p->xflag |= CHANGE;
D 13
				p->comn = line.comn;
E 13
I 13
				SCPYN(p->comn, t->ty_getty);
E 13
			}
I 15
D 23
			if (SCMPN(p->wcmd, t->ty_window)) {
E 23
I 23
			if (SCMPN(p->wcmd, t->ty_window ? t->ty_window : "")) {
E 23
				p->xflag |= WCHANGE|CHANGE;
				SCPYN(p->wcmd, t->ty_window);
			}
E 15
			goto contin1;
		}
I 15

E 15
D 18
		for (ALL) {
			if (p->line[0] != 0)
				continue;
D 13
			SCPYN(p->line, line.line);
E 13
I 13
			SCPYN(p->line, t->ty_name);
E 13
			p->xflag |= FOUND|CHANGE;
D 13
			p->comn = line.comn;
E 13
I 13
			SCPYN(p->comn, t->ty_getty);
I 15
			if (strcmp(t->ty_window, "") != 0) {
				p->xflag |= WCHANGE;
				SCPYN(p->wcmd, t->ty_window);
			}
E 18
I 18
		/*
		 * Make space for a new one
		 */
		p1 = (struct tab *)calloc(1, sizeof(*p1));
		if (!p1) {
			syslog(LOG_ERR, "no space for '%s' !?!", t->ty_name);
E 18
E 15
E 13
			goto contin1;
		}
I 18
		/*
		 * Put new terminal at the end of the linked list.
		 */
		if (itab) {
			for (p = itab; p->next ; p = p->next)
				;
			p->next = p1;
		} else
			itab = p1;

		p = p1;
		SCPYN(p->line, t->ty_name);
		p->xflag |= FOUND|CHANGE;
		SCPYN(p->comn, t->ty_getty);
D 23
		if (strcmp(t->ty_window, "") != 0) {
E 23
I 23
		if (t->ty_window && strcmp(t->ty_window, "") != 0) {
E 23
			p->xflag |= WCHANGE;
			SCPYN(p->wcmd, t->ty_window);
		}
E 18
	contin1:
		;
	}
D 13
	close(fi);
E 13
I 13
	endttyent();
I 18
	p1 = (struct tab *)0;
E 18
E 13
	for (ALL) {
		if ((p->xflag&FOUND) == 0) {
			term(p);
D 18
			p->line[0] = 0;
E 18
I 15
			wterm(p);
I 18
			if (p1)
				p1->next = p->next;
			else
				itab = p->next;
			free(p);
			p = p1 ? p1 : itab;
		} else {
			/* window system should be started first */
			if (p->xflag&WCHANGE) {
				wterm(p);
				wstart(p);
			}
			if (p->xflag&CHANGE) {
				term(p);
				dfork(p);
			}
E 18
E 15
		}
I 15
D 18
		/* window system should be started first */
		if (p->xflag&WCHANGE) {
			wterm(p);
			wstart(p);
		}
E 15
		if (p->xflag&CHANGE) {
			term(p);
			dfork(p);
		}
E 18
I 18
		p1 = p;
E 18
	}
}

E 12
term(p)
D 12
register struct tab *p;
E 12
I 12
	register struct tab *p;
E 12
{

D 12
	if(p->pid != 0) {
E 12
I 12
	if (p->pid != 0) {
E 12
D 27
		rmut(p);
E 27
I 27
		cleanutmp(p);
E 27
		kill(p->pid, SIGKILL);
	}
	p->pid = 0;
I 15
	/* send SIGHUP to get rid of connections */
	if (p->wpid > 0)
		kill(p->wpid, SIGHUP);
E 15
}
D 23

D 13
rline()
{
	register c, i;

loop:
	c = get();
D 12
	if(c < 0)
E 12
I 12
	if (c < 0)
E 12
		return(0);
D 12
	if(c == 0)
E 12
I 12
	if (c == 0)
E 12
		goto loop;
	line.flag = c;
	c = get();
D 12
	if(c <= 0)
E 12
I 12
	if (c <= 0)
E 12
		goto loop;
	line.comn = c;
	SCPYN(line.line, "");
D 12
	for (i=0; i<LINSIZ; i++) {
E 12
I 12
	for (i = 0; i < LINSIZ; i++) {
E 12
		c = get();
D 12
		if(c <= 0)
E 12
I 12
		if (c <= 0)
E 12
			break;
		line.line[i] = c;
	}
D 12
	while(c > 0)
E 12
I 12
	while (c > 0)
E 12
		c = get();
D 12
	if(line.line[0] == 0)
E 12
I 12
	if (line.line[0] == 0)
E 12
		goto loop;
D 12
	if(line.flag == '0')
E 12
I 12
	if (line.flag == '0')
E 12
		goto loop;
	strcpy(tty, dev);
	strncat(tty, line.line, LINSIZ);
D 12
	if(access(tty, 06) < 0)
E 12
I 12
	if (access(tty, 06) < 0)
E 12
		goto loop;
D 12
	return(1);
E 12
I 12
	return (1);
E 12
}

get()
{
	char b;

D 12
	if(read(fi, &b, 1) != 1)
		return(-1);
	if(b == '\n')
		return(0);
	return(b);
E 12
I 12
	if (read(fi, &b, 1) != 1)
		return (-1);
	if (b == '\n')
		return (0);
	return (b);
E 12
}

E 13
D 12
#define	FOUND	1
#define	CHANGE	2

merge()
{
	register struct tab *p;

	fi = open(ifile, 0);
	if(fi < 0)
		return;
	for(ALL)
		p->xflag = 0;
	while(rline()) {
		for(ALL) {
			if (SCMPN(p->line, line.line))
				continue;
			p->xflag |= FOUND;
			if(line.comn != p->comn) {
				p->xflag |= CHANGE;
				p->comn = line.comn;
			}
			goto contin1;
		}
		for(ALL) {
			if(p->line[0] != 0)
				continue;
			SCPYN(p->line, line.line);
			p->xflag |= FOUND|CHANGE;
			p->comn = line.comn;
			goto contin1;
		}
	contin1:
		;
	}
	close(fi);
	for(ALL) {
		if((p->xflag&FOUND) == 0) {
			term(p);
			p->line[0] = 0;
		}
		if((p->xflag&CHANGE) != 0) {
			term(p);
			dfork(p);
		}
	}
}

E 12
I 7
#include <sys/ioctl.h>
E 23

E 7
dfork(p)
D 12
struct tab *p;
E 12
I 12
	struct tab *p;
E 12
{
	register pid;
I 6
	time_t t;
	int dowait = 0;
I 9
D 15
	extern char *sys_errlist[];
E 15
E 9
E 6

I 6
	time(&t);
	p->gettycnt++;
	if ((t - p->gettytime) >= 60) {
		p->gettytime = t;
		p->gettycnt = 1;
D 15
	} else {
		if (p->gettycnt >= 5) {
			dowait = 1;
			p->gettytime = t;
			p->gettycnt = 1;
		}
E 15
I 15
	} else if (p->gettycnt >= 5) {
		dowait = 1;
		p->gettytime = t;
		p->gettycnt = 1;
E 15
	}
E 6
	pid = fork();
D 12
	if(pid == 0) {
E 12
I 12
	if (pid == 0) {
E 12
I 7
D 15
		int oerrno, f;
		extern int errno;

E 15
		signal(SIGTERM, SIG_DFL);
		signal(SIGHUP, SIG_IGN);
I 17
		sigsetmask(0);	/* since can be called from masked code */
E 17
I 9
D 15
		strcpy(tty, dev);
		strncat(tty, p->line, LINSIZ);
E 15
E 9
E 7
I 6
		if (dowait) {
D 7
			int f = open("/dev/console", 1);
E 7
I 7
D 12
			f = open("/dev/console", 1);
E 12
I 12
D 15
			f = open("/dev/console", O_WRONLY);
E 12
E 7
			write(f, "init: ", 6);
			write(f, tty, strlen(tty));
			write(f, ": getty failing, sleeping\n\r", 27);
			close(f);
E 15
I 15
			syslog(LOG_ERR, "'%s %s' failing, sleeping", p->comn, p->line);
			closelog();
E 15
			sleep(30);
I 7
D 12
			if ((f = open("/dev/tty", 2)) >= 0) {
E 12
I 12
D 15
			if ((f = open("/dev/tty", O_RDWR)) >= 0) {
E 12
				ioctl(f, TIOCNOTTY, 0);
				close(f);
			}
E 15
E 7
		}
I 31
		if (setsid() < 0)
			syslog(LOG_ERR, "setsid failed(dfork) %m");
E 31
E 6
D 7
		signal(SIGTERM, SIG_DFL);
		signal(SIGHUP, SIG_IGN);
E 7
D 9
		strcpy(tty, dev);
		strncat(tty, p->line, LINSIZ);
E 9
D 15
		chown(tty, 0, 0);
		chmod(tty, 0622);
I 14
		/*
		 * Give port selectors an opportunity
		 * to see DTR transition.
		 */
		sleep(1);
E 14
D 5
		open(tty, 2);
E 5
I 5
D 12
		if (open(tty, 2) < 0) {
E 12
I 12
		if (open(tty, O_RDWR) < 0) {
E 12
			int repcnt = 0;
			do {
I 7
				oerrno = errno;
E 7
				if (repcnt % 10 == 0) {
D 7
					int f = open("/dev/console", 1);
E 7
I 7
D 12
					f = open("/dev/console", 1);
E 12
I 12
					f = open("/dev/console", O_WRONLY);
E 12
E 7
					write(f, "init: ", 6);
D 7
					write(f, tty, strlen(tty));
					write(f, ": cannot open\n\r", 15);
E 7
I 7
D 9
					errno = oerrno, perror(tty);
E 9
I 9
					write(f, tty, strlen(tty));
					write(f, ": ", 2);
					write(f, sys_errlist[oerrno],
						strlen(sys_errlist[oerrno]));
					write(f, "\n", 1);
E 9
E 7
					close(f);
I 7
					if ((f = open("/dev/tty", 2)) >= 0) {
						ioctl(f, TIOCNOTTY, 0);
						close(f);
					}
E 7
				}
				repcnt++;
				sleep(60);
D 12
			} while (open(tty, 2) < 0);
E 12
I 12
			} while (open(tty, O_RDWR) < 0);
E 12
			exit(0);	/* have wrong control tty, start over */
		}
E 5
		vhangup();
		signal(SIGHUP, SIG_DFL);
D 12
		open(tty, 2);
E 12
I 12
		(void) open(tty, O_RDWR);
E 12
		close(0);
		dup(1);
		dup(0);
D 13
		tty[0] = p->comn;
		tty[1] = 0;
E 13
I 13
		strncpy(tty, p->comn, sizeof(p->comn));
		tty[sizeof(p->comn)] = 0;
E 13
		execl(getty, minus, tty, (char *)0);
E 15
I 15
		execit(p->comn, p->line);
E 15
		exit(0);
	}
	p->pid = pid;
}

I 12
D 27
/*
 * Remove utmp entry.
 */
E 12
rmut(p)
E 27
I 27
cleanutmp(p)
E 27
D 12
register struct tab *p;
E 12
I 12
	register struct tab *p;
E 12
{
D 27
	register f;
I 5
	int found = 0;
I 18
	static unsigned utmpsize;
	static struct utmp *utmp;
	register struct utmp *u;
	int nutmp;
	struct stat statbf;
E 18
E 5

D 12
	f = open(utmp, 2);
	if(f >= 0) {
		while(read(f, (char *)&wtmp, sizeof(wtmp)) == sizeof(wtmp)) {
E 12
I 12
D 18
	f = open(utmp, O_RDWR);
E 18
I 18
	f = open(utmpf, O_RDWR);
E 18
	if (f >= 0) {
D 18
		while (read(f, (char *)&wtmp, sizeof(wtmp)) == sizeof(wtmp)) {
E 12
D 5
			if (SCMPN(wtmp.ut_line, p->line))
E 5
I 5
			if (SCMPN(wtmp.ut_line, p->line) || wtmp.ut_name[0]==0)
E 5
				continue;
			lseek(f, -(long)sizeof(wtmp), 1);
			SCPYN(wtmp.ut_name, "");
I 11
			SCPYN(wtmp.ut_host, "");
E 11
			time(&wtmp.ut_time);
			write(f, (char *)&wtmp, sizeof(wtmp));
I 5
			found++;
E 18
I 18
		fstat(f, &statbf);
		if (utmpsize < statbf.st_size) {
			utmpsize = statbf.st_size + 10 * sizeof(struct utmp);
			if (utmp)
				utmp = (struct utmp *)realloc(utmp, utmpsize);
			else
				utmp = (struct utmp *)malloc(utmpsize);
			if (!utmp)
				syslog(LOG_ERR, "utmp malloc failed");
		}
		if (statbf.st_size && utmp) {
			nutmp = read(f, utmp, statbf.st_size);
			nutmp /= sizeof(struct utmp);
			for (u = utmp ; u < &utmp[nutmp] ; u++) {
D 24
				if (SCMPN(u->ut_line, p->line) ||
				    u->ut_name[0]==0)
E 24
I 24
				if (u->ut_name[0] == 0 ||
				    SCMPN(u->ut_line, p->line))
E 24
					continue;
				lseek(f, ((long)u)-((long)utmp), L_SET);
				SCPYN(u->ut_name, "");
				SCPYN(u->ut_host, "");
				time(&u->ut_time);
				write(f, (char *)u, sizeof(*u));
				found++;
			}
E 18
E 5
		}
		close(f);
	}
D 5
	f = open(wtmpf, 1);
	if (f >= 0) {
		SCPYN(wtmp.ut_line, p->line);
		SCPYN(wtmp.ut_name, "");
		time(&wtmp.ut_time);
		lseek(f, (long)0, 2);
		write(f, (char *)&wtmp, sizeof(wtmp));
		close(f);
E 5
I 5
	if (found) {
D 12
		f = open(wtmpf, 1);
E 12
I 12
		f = open(wtmpf, O_WRONLY|O_APPEND);
E 12
		if (f >= 0) {
			SCPYN(wtmp.ut_line, p->line);
			SCPYN(wtmp.ut_name, "");
I 11
			SCPYN(wtmp.ut_host, "");
E 11
			time(&wtmp.ut_time);
D 12
			lseek(f, (long)0, 2);
E 12
			write(f, (char *)&wtmp, sizeof(wtmp));
			close(f);
		}
E 27
I 27
	if (logout(p->line)) {
D 31
		logwtmp(p->line);
E 31
I 31
		logwtmp(p->line, "", "");
E 31
E 27
I 14
		/*
		 * After a proper login force reset
		 * of error detection code in dfork.
		 */
		p->gettytime = 0;
I 17
		p->windtime = 0;
E 17
E 14
E 5
	}
}

I 31
void
E 31
reset()
{
I 12
D 31

E 31
E 12
	longjmp(sjbuf, 1);
I 4
}

I 12
jmp_buf	idlebuf;

I 31
void
E 31
idlehup()
{
D 31

E 31
	longjmp(idlebuf, 1);
}

I 31
void
E 31
E 12
idle()
{
	register struct tab *p;
	register pid;

D 12
	signal(SIGTSTP, idle);
E 12
I 12
	signal(SIGHUP, idlehup);
E 12
D 15
	for (;;) {
E 15
I 15
	for (EVER) {
E 15
D 12
		pid = wait((int *) 0);
		if (mergflag)
E 12
I 12
		if (setjmp(idlebuf))
E 12
			return;
D 12
		if (pid == -1)
			pause();
		else {
			for (ALL)
				if (p->pid == pid) {
					rmut(p);
					p->pid = -1;
				}
E 12
I 12
		pid = wait((int *) 0);
		if (pid == -1) {
			sigpause(0);
			continue;
E 12
		}
I 12
D 15
		for (ALL)
E 15
I 15
		for (ALL) {
			/* if window system dies, mark it for restart */
			if (p->wpid == pid)
				p->wpid = -1;
E 15
			if (p->pid == pid) {
D 27
				rmut(p);
E 27
I 27
				cleanutmp(p);
E 27
				p->pid = -1;
			}
I 15
		}
E 15
E 12
	}
I 15
}

wterm(p)
	register struct tab *p;
{
	if (p->wpid != 0) {
		kill(p->wpid, SIGKILL);
	}
	p->wpid = 0;
}

wstart(p)
	register struct tab *p;
{
D 17
	int npid = fork();
E 17
I 17
	register pid;
	time_t t;
	int dowait = 0;
E 17

D 17
	if (npid == 0) {
/*
E 17
I 17
	time(&t);
	p->windcnt++;
	if ((t - p->windtime) >= 60) {
		p->windtime = t;
		p->windcnt = 1;
	} else if (p->windcnt >= 5) {
		dowait = 1;
		p->windtime = t;
		p->windcnt = 1;
	}

	pid = fork();

	if (pid == 0) {
E 17
		signal(SIGTERM, SIG_DFL);
D 17
		signal(SIGHUP,  SIG_DFL);
		signal(SIGALRM, SIG_DFL);
		signal(SIGTSTP, SIG_IGN);
*/
E 17
I 17
		signal(SIGHUP,  SIG_IGN);
		sigsetmask(0);	/* since can be called from masked code */
		if (dowait) {
			syslog(LOG_ERR, "'%s %s' failing, sleeping", p->wcmd, p->line);
			closelog();
			sleep(30);
		}
I 31
		if (setsid() < 0)
			syslog(LOG_ERR, "setsid failed (window) %m");
E 31
E 17
		execit(p->wcmd, p->line);
		exit(0);
	}
D 17
	p->wpid = npid;
E 17
I 17
	p->wpid = pid;
E 17
}

D 17
#define NARGS	20	/* must be at lease 4 */
E 17
I 17
#define NARGS	20	/* must be at least 4 */
E 17
#define ARGLEN	512	/* total size for all the argument strings */

execit(s, arg)
	char *s;
	char *arg;	/* last argument on line */
{
	char *argv[NARGS], args[ARGLEN], *envp[1];
	register char *sp = s;
	register char *ap = args;
	register char c;
	register int i;

	/*
	 * First we have to set up the argument vector.
	 * "prog arg1 arg2" maps to exec("prog", "-", "arg1", "arg2"). 
	 */
	for (i = 1; i < NARGS - 2; i++) {
		argv[i] = ap;
		for (EVER) {
			if ((c = *sp++) == '\0' || ap >= &args[ARGLEN-1]) {
				*ap = '\0';
				goto done;
			}
			if (c == ' ') {
				*ap++ = '\0';
				while (*sp == ' ')
					sp++;
				if (*sp == '\0')
					goto done;
				break;
			}
			*ap++ = c;
		}
	}
done:
	argv[0] = argv[1];
	argv[1] = "-";
	argv[i+1] = arg;
	argv[i+2] = 0;
	envp[0] = 0;
	execve(argv[0], &argv[1], envp);
	/* report failure of exec */
	syslog(LOG_ERR, "%s: %m", argv[0]);
	closelog();
	sleep(10);	/* prevent failures from eating machine */
E 15
E 4
}
D 3


E 3
E 1
