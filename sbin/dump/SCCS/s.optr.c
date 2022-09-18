h45199
s 00005/00002/00507
d D 8.2 94/01/06 09:52:07 mckusick 28 27
c avoid null pointers (from cgd@vangogh)
e
s 00002/00002/00507
d D 8.1 93/06/05 10:52:50 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00508
d D 5.16 93/05/11 13:49:40 torek 26 25
c gcc lint
e
s 00020/00026/00489
d D 5.15 93/01/25 15:36:01 mckusick 25 24
c cleanups from leres@lbl
e
s 00005/00004/00510
d D 5.14 92/07/16 12:39:58 bostic 24 23
c fix the prototypes, minor cleanup to signal handlers
e
s 00011/00042/00503
d D 5.13 92/06/18 14:10:53 mckusick 23 22
c lint
e
s 00039/00037/00506
d D 5.12 91/07/29 17:11:42 bostic 22 21
c just inline the __STDC__ stuff, why make it complicated as well as ugly
e
s 00027/00024/00516
d D 5.11 91/07/29 15:49:34 torek 21 19
c ANSI varargs, for sparc among others
e
s 00027/00024/00516
d R 5.11 91/07/29 13:14:42 torek 20 19
c ANSI varargs, for sparc among others
e
s 00000/00001/00540
d D 5.10 91/07/23 21:09:51 mckusick 19 18
c delete unneeded include of dir.h
e
s 00011/00001/00530
d D 5.9 91/07/23 16:53:01 mckusick 18 17
c temporarily add ifdef sunos (includes) to assist Steve Romig in debugging
e
s 00005/00004/00526
d D 5.8 91/03/07 17:50:00 mckusick 17 16
c verified to be free of AT&T code
e
s 00002/00001/00528
d D 5.7 91/03/01 10:43:44 bostic 16 15
c use tzfile.h seconds #defines instead of our own
e
s 00014/00002/00515
d D 5.6 91/02/28 19:33:52 bostic 15 14
c ANSI; break #includes out of dump.h into separate files
e
s 00038/00038/00479
d D 5.5 91/02/28 18:50:49 mckusick 14 13
c KNF, misc global cleanups
e
s 00174/00129/00343
d D 5.4 91/02/23 16:15:54 torek 13 12
c fix gcc warnings; add quit() function to print message and abort;
c stop cheating on /etc/group functions; use varargs where needed;
c check for NULL return from malloc; use strdup instead of recreating it;
c do not loop forever if controlling tty disappears
e
s 00001/00000/00471
d D 5.3 90/02/15 13:28:18 mckusick 12 11
c need sys/time.h since dump.h no longer includes it
e
s 00048/00029/00423
d D 5.2 89/09/12 17:34:36 mckusick 11 10
c use pathnames.h; more explicit messages
e
s 00009/00001/00443
d D 5.1 85/06/05 08:46:10 dist 10 9
c Add copyright
e
s 00004/00004/00440
d D 1.9 85/05/28 13:59:31 mckusick 9 8
c be a bit less pedantical!
e
s 00005/00007/00439
d D 1.8 83/06/19 14:10:09 root 8 7
c strncmp -> strcmp to fix weirdness
e
s 00077/00044/00369
d D 1.7 83/06/12 16:15:18 sam 7 6
c new fstab format
e
s 00001/00001/00412
d D 1.6 83/02/11 12:58:28 sam 6 5
c merge from sun
e
s 00006/00001/00407
d D 1.5 82/01/04 16:14:54 mckusic 5 4
c formatting clean-up
e
s 00001/00001/00407
d D 1.4 80/12/18 00:52:46 wnj 4 3
c dump moans about ``Mount next tape'' unnecessarily; dump is rude
e
s 00009/00004/00399
d D 1.3 80/10/16 10:12:28 root 3 2
c Option 'w' tells only what to dump; 'W' tells most recent dump(s)
e
s 00010/00008/00393
d D 1.2 80/10/13 17:38:04 root 2 1
c added calls to fstab routines
e
s 00401/00000/00000
d D 1.1 80/10/13 17:30:28 root 1 0
c date and time created 80/10/13 17:30:28 by root
e
u
U
t
T
I 1
D 10
static	char *sccsid = "%W% (Berkeley) %G%";
E 10
I 10
D 17
/*
D 11
 * Copyright (c) 1980 Regents of the University of California.
E 11
I 11
 * Copyright (c) 1980, 1988 Regents of the University of California.
E 11
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 17
I 17
/*-
D 27
 * Copyright (c) 1980, 1988 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1980, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
 * %sccs.include.redist.c%
E 17
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 13
#endif not lint
E 13
I 13
#endif /* not lint */
E 13
E 10
I 5

I 18
D 25
#ifdef sunos
#include <stdio.h>
#include <ctype.h>
E 25
E 18
E 5
D 15
#include "dump.h"
E 15
I 15
#include <sys/param.h>
E 15
I 12
D 13
#include <sys/time.h>
E 13
I 13
#include <sys/wait.h>
I 18
D 25
#include <sys/stat.h>
E 25
#include <sys/time.h>
D 23
#include <sys/dir.h>
E 23
D 25
#else
#include <sys/param.h>
#include <sys/wait.h>
E 18
D 15
#include <errno.h>
E 15
I 15
D 19
#include <ufs/dir.h>
E 19
I 18
#include <stdio.h>
#endif
E 18
#include <signal.h>
#include <time.h>
E 25
I 25

#include <errno.h>
E 25
#include <fstab.h>
E 15
#include <grp.h>
D 21
#include <varargs.h>
E 21
I 15
D 25
#include <utmp.h>
I 16
#include <tzfile.h>
E 16
#include <errno.h>
E 25
I 25
#include <signal.h>
#include <stdio.h>
E 25
D 18
#include <stdio.h>
E 18
#ifdef __STDC__
D 25
#include <unistd.h>
E 25
#include <stdlib.h>
#include <string.h>
I 21
#include <stdarg.h>
D 25
#else
E 25
I 25
#endif
#include <tzfile.h>
#ifdef __STDC__
#include <unistd.h>
#endif
#include <utmp.h>
#ifndef __STDC__
E 25
#include <varargs.h>
E 21
#endif
I 25

E 25
#include "dump.h"
E 15
E 13
E 12
I 11
#include "pathnames.h"
E 11

I 13
D 25
static void alarmcatch();
static void sendmes();
E 25
I 25
void	alarmcatch __P((/* int, int */));
int	datesort __P((const void *, const void *));
static	void sendmes __P((char *, char *));
E 25

E 13
/*
D 13
 *	This is from /usr/include/grp.h
 *	That defined struct group, which conflicts
 *	with the struct group defined in param.h
 */
struct	Group { /* see getgrent(3) */
	char	*gr_name;
	char	*gr_passwd;
	int	gr_gid;
	char	**gr_mem;
};
struct	Group *getgrnam();
/*
E 13
D 11
 *	Query the operator; This fascist piece of code requires
 *	an exact response.
E 11
I 11
 *	Query the operator; This previously-fascist piece of code
 *	no longer requires an exact response.
E 11
 *	It is intended to protect dump aborting by inquisitive
 *	people banging on the console terminal to see what is
 *	happening which might cause dump to croak, destroying
 *	a large number of hours of work.
 *
 *	Every 2 minutes we reprint the message, alerting others
 *	that dump needs attention.
 */
D 25
int	timeout;
D 9
char	*attnmessage;		/* attemtion message */
E 9
I 9
char	*attnmessage;		/* attention message */
E 25
I 25
static	int timeout;
static	char *attnmessage;		/* attention message */
E 25
I 13

int
E 13
E 9
query(question)
	char	*question;
{
	char	replybuffer[64];
D 13
	int	back;
E 13
I 13
	int	back, errcount;
E 13
	FILE	*mytty;

D 11
	if ( (mytty = fopen("/dev/tty", "r")) == NULL){
		msg("fopen on /dev/tty fails\n");
E 11
I 11
D 13
	if ( (mytty = fopen(_PATH_TTY, "r")) == NULL){
		msg("fopen on %s fails\n", _PATH_TTY);
E 11
		abort();
	}
E 13
I 13
	if ((mytty = fopen(_PATH_TTY, "r")) == NULL)
		quit("fopen on %s fails: %s\n", _PATH_TTY, strerror(errno));
E 13
	attnmessage = question;
	timeout = 0;
	alarmcatch();
D 13
	for(;;){
		if ( fgets(replybuffer, 63, mytty) == NULL){
			if (ferror(mytty)){
				clearerr(mytty);
				continue;
			}
E 13
I 13
	back = -1;
	errcount = 0;
	do {
		if (fgets(replybuffer, 63, mytty) == NULL) {
			clearerr(mytty);
			if (++errcount > 30)	/* XXX	ugly */
				quit("excessive operator query failures\n");
E 13
D 11
		} else if ( (strcmp(replybuffer, "yes\n") == 0) ||
			    (strcmp(replybuffer, "Yes\n") == 0)){
E 11
I 11
		} else if (replybuffer[0] == 'y' || replybuffer[0] == 'Y') {
E 11
D 13
				back = 1;
				goto done;
E 13
I 13
			back = 1;
E 13
D 11
		} else if ( (strcmp(replybuffer, "no\n") == 0) ||
			    (strcmp(replybuffer, "No\n") == 0)){
E 11
I 11
		} else if (replybuffer[0] == 'n' || replybuffer[0] == 'N') {
E 11
D 13
				back = 0;
				goto done;
E 13
I 13
			back = 0;
E 13
		} else {
D 9
			msg("\"Yes\" or \"No\" ONLY!\n");
E 9
I 9
D 11
			msg("\"Yes\" or \"No\"?\n");
E 9
			alarmcatch();
E 11
I 11
D 13
			fprintf(stderr, "  DUMP: \"Yes\" or \"No\"?\n");
			fprintf(stderr,"  DUMP: %s: (\"yes\" or \"no\") ",
			    question);
E 13
I 13
			(void) fprintf(stderr,
			    "  DUMP: \"Yes\" or \"No\"?\n");
			(void) fprintf(stderr,
			    "  DUMP: %s: (\"yes\" or \"no\") ", question);
E 13
E 11
		}
D 13
	}
    done:
E 13
I 13
	} while (back < 0);

E 13
	/*
	 *	Turn off the alarm, and reset the signal to trap out..
	 */
D 23
	alarm(0);
E 23
I 23
	(void) alarm(0);
E 23
D 24
	if (signal(SIGALRM, sigalrm) == SIG_IGN)
E 24
I 24
	if (signal(SIGALRM, sig) == SIG_IGN)
E 24
		signal(SIGALRM, SIG_IGN);
D 23
	fclose(mytty);
E 23
I 23
	(void) fclose(mytty);
E 23
	return(back);
}
I 11

char lastmsg[100];

E 11
/*
 *	Alert the console operator, and enable the alarm clock to
 *	sleep for 2 minutes in case nobody comes to satisfy dump
 */
I 13
D 25
static void
E 25
I 25
void
E 25
E 13
alarmcatch()
{
D 11
	if (timeout)
		msgtail("\n");
	msg("NEEDS ATTENTION: %s: (\"yes\" or \"no\") ",
		attnmessage);
E 11
I 11
	if (notify == 0) {
		if (timeout == 0)
D 13
			fprintf(stderr,"  DUMP: %s: (\"yes\" or \"no\") ",
E 13
I 13
			(void) fprintf(stderr,
			    "  DUMP: %s: (\"yes\" or \"no\") ",
E 13
			    attnmessage);
		else
			msgtail("\7\7");
	} else {
		if (timeout) {
			msgtail("\n");
			broadcast("");		/* just print last msg */
		}
D 13
		fprintf(stderr,"  DUMP: %s: (\"yes\" or \"no\") ",
E 13
I 13
		(void) fprintf(stderr,"  DUMP: %s: (\"yes\" or \"no\") ",
E 13
		    attnmessage);
	}
E 11
	signal(SIGALRM, alarmcatch);
D 23
	alarm(120);
E 23
I 23
	(void) alarm(120);
E 23
	timeout = 1;
}
I 13

E 13
/*
 *	Here if an inquisitive operator interrupts the dump program
 */
I 13
void
E 13
D 24
interrupt()
E 24
I 24
interrupt(signo)
	int signo;
E 24
{
D 9
	msg("Interrupt received. Do >>>YOU<<< know what are you doing?\n");
	if (query("Do you really want to abort dump?"))
E 9
I 9
	msg("Interrupt received.\n");
	if (query("Do you want to abort dump?"))
E 9
D 24
		dumpabort();
E 24
I 24
		dumpabort(0);
E 24
D 11
	signal(SIGINT, interrupt);
E 11
}

/*
 *	The following variables and routines manage alerting
 *	operators to the status of dump.
 *	This works much like wall(1) does.
 */
D 13
struct	Group *gp;
E 13
I 13
struct	group *gp;
E 13

/*
 *	Get the names from the group entry "operator" to notify.
 */	
I 13
void
E 13
set_operators()
{
	if (!notify)		/*not going to notify*/
		return;
	gp = getgrnam(OPGRENT);
D 23
	endgrent();
E 23
I 23
	(void) endgrent();
E 23
D 13
	if (gp == (struct Group *)0){
D 11
		msg("No entry in /etc/group for %s.\n",
E 11
I 11
		msg("No group entry for %s.\n",
E 11
			OPGRENT);
E 13
I 13
	if (gp == NULL) {
		msg("No group entry for %s.\n", OPGRENT);
E 13
		notify = 0;
		return;
	}
}

D 25
struct tm *localtime();
E 25
struct tm *localclock;

/*
 *	We fork a child to do the actual broadcasting, so
 *	that the process control groups are not messed up
 */
I 13
void
E 13
broadcast(message)
	char	*message;
{
	time_t		clock;
	FILE	*f_utmp;
	struct	utmp	utmp;
D 23
	int	nusers;
E 23
	char	**np;
	int	pid, s;

I 13
	if (!notify || gp == NULL)
		return;

E 13
	switch (pid = fork()) {
	case -1:
		return;
	case 0:
		break;
	default:
		while (wait(&s) != pid)
			continue;
		return;
	}

D 13
	if (!notify || gp == 0)
D 4
		return;
E 4
I 4
		exit(0);
E 13
E 4
D 23
	clock = time(0);
E 23
I 23
	clock = time((time_t *)0);
E 23
	localclock = localtime(&clock);

D 11
	if((f_utmp = fopen("/etc/utmp", "r")) == NULL) {
		msg("Cannot open /etc/utmp\n");
E 11
I 11
D 13
	if((f_utmp = fopen(_PATH_UTMP, "r")) == NULL) {
		msg("Cannot open %s\n", _PATH_UTMP);
E 13
I 13
	if ((f_utmp = fopen(_PATH_UTMP, "r")) == NULL) {
		msg("Cannot open %s: %s\n", _PATH_UTMP, strerror(errno));
E 13
E 11
		return;
	}

D 23
	nusers = 0;
E 23
D 13
	while (!feof(f_utmp)){
E 13
I 13
	while (!feof(f_utmp)) {
E 13
D 23
		if (fread(&utmp, sizeof (struct utmp), 1, f_utmp) != 1)
E 23
I 23
		if (fread((char *) &utmp, sizeof (struct utmp), 1, f_utmp) != 1)
E 23
			break;
		if (utmp.ut_name[0] == 0)
			continue;
D 23
		nusers++;
E 23
D 13
		for (np = gp->gr_mem; *np; np++){
E 13
I 13
		for (np = gp->gr_mem; *np; np++) {
E 13
			if (strncmp(*np, utmp.ut_name, sizeof(utmp.ut_name)) != 0)
				continue;
			/*
			 *	Do not send messages to operators on dialups
			 */
			if (strncmp(utmp.ut_line, DIALUP, strlen(DIALUP)) == 0)
				continue;
#ifdef DEBUG
D 13
			msg("Message to %s at %s\n",
				utmp.ut_name, utmp.ut_line);
#endif DEBUG
E 13
I 13
			msg("Message to %s at %s\n", *np, utmp.ut_line);
#endif
E 13
			sendmes(utmp.ut_line, message);
		}
	}
D 13
	fclose(f_utmp);
E 13
I 13
	(void) fclose(f_utmp);
E 13
	Exit(0);	/* the wait in this same routine will catch this */
	/* NOTREACHED */
}

I 13
static void
E 13
sendmes(tty, message)
D 5
char *tty, *message;
E 5
I 5
	char *tty, *message;
E 5
{
	char t[50], buf[BUFSIZ];
	register char *cp;
D 11
	register int c, ch;
	int	msize;
E 11
I 11
	int lmsg = 1;
E 11
	FILE *f_tty;

D 11
	msize = strlen(message);
	strcpy(t, "/dev/");
E 11
I 11
D 13
	strcpy(t, _PATH_DEV);
E 11
	strcat(t, tty);
E 13
I 13
	(void) strcpy(t, _PATH_DEV);
	(void) strcat(t, tty);
E 13

D 13
	if((f_tty = fopen(t, "w")) != NULL) {
E 13
I 13
	if ((f_tty = fopen(t, "w")) != NULL) {
E 13
		setbuf(f_tty, buf);
D 11
		fprintf(f_tty, "\nMessage from the dump program to all operators at %d:%02d ...\r\n\n"
E 11
I 11
D 13
		fprintf(f_tty, "\n\07\07\07Message from the dump program to all operators at %d:%02d ...\r\n\n  DUMP: NEEDS ATTENTION: "
E 11
		       ,localclock->tm_hour
		       ,localclock->tm_min);
E 13
I 13
		(void) fprintf(f_tty,
		    "\n\
\7\7\7Message from the dump program to all operators at %d:%02d ...\r\n\n\
DUMP: NEEDS ATTENTION: ",
		    localclock->tm_hour, localclock->tm_min);
E 13
D 11
		for (cp = message, c = msize; c-- > 0; cp++) {
			ch = *cp;
			if (ch == '\n')
E 11
I 11
		for (cp = lastmsg; ; cp++) {
			if (*cp == '\0') {
				if (lmsg) {
					cp = message;
					if (*cp == '\0')
						break;
					lmsg = 0;
				} else
					break;
			}
			if (*cp == '\n')
E 11
D 13
				putc('\r', f_tty);
D 11
			putc(ch, f_tty);
E 11
I 11
			putc(*cp, f_tty);
E 13
I 13
				(void) putc('\r', f_tty);
			(void) putc(*cp, f_tty);
E 13
E 11
		}
D 13
		fclose(f_tty);
E 13
I 13
		(void) fclose(f_tty);
E 13
	}
}

/*
 *	print out an estimate of the amount of time left to do the dump
 */

time_t	tschedule = 0;

I 13
void
E 13
timeest()
{
	time_t	tnow, deltat;

D 23
	time (&tnow);
E 23
I 23
	(void) time((time_t *) &tnow);
E 23
D 13
	if (tnow >= tschedule){
E 13
I 13
	if (tnow >= tschedule) {
E 13
		tschedule = tnow + 300;
		if (blockswritten < 500)
			return;	
		deltat = tstart_writing - tnow +
D 14
			(((1.0*(tnow - tstart_writing))/blockswritten) * esize);
E 14
I 14
			(1.0 * (tnow - tstart_writing))
			/ blockswritten * tapesize;
E 14
		msg("%3.2f%% done, finished in %d:%02d\n",
D 14
			(blockswritten*100.0)/esize,
			deltat/3600, (deltat%3600)/60);
E 14
I 14
			(blockswritten * 100.0) / tapesize,
			deltat / 3600, (deltat % 3600) / 60);
E 14
	}
}

I 14
D 23
/*
 *	tapesize: total number of blocks estimated over all reels
 *	blockswritten:	blocks actually written, over all reels
 *	etapes:	estimated number of tapes to write
 *
 *	tsize:	blocks can write on this reel
 *	asize:	blocks written on this reel
 *	tapeno:	number of tapes written so far
 */
E 14
D 13
int blocksontape()
E 13
I 13
int
blocksontape()
E 13
{
D 14
	/*
	 *	esize: total number of blocks estimated over all reels
	 *	blockswritten:	blocks actually written, over all reels
	 *	etapes:	estimated number of tapes to write
	 *
	 *	tsize:	blocks can write on this reel
	 *	asize:	blocks written on this reel
	 *	tapeno:	number of tapes written so far
	 */
E 14
	if (tapeno == etapes)
D 13
		return(esize - (etapes - 1)*tsize);
	return(tsize);
E 13
I 13
D 14
		return (esize - (etapes - 1)*tsize);
E 14
I 14
		return (tapesize - (etapes - 1) * tsize);
E 14
	return (tsize);
E 13
}

E 23
D 13
	/* VARARGS1 */
	/* ARGSUSED */
msg(fmt, a1, a2, a3, a4, a5)
	char	*fmt;
I 5
	int	a1, a2, a3, a4, a5;
E 13
I 13
D 22
#ifdef lint

/* VARARGS1 */
void msg(fmt) char *fmt; { strcpy(lastmsg, fmt); }

/* VARARGS1 */
void msgtail(fmt) char *fmt; { fmt = fmt; }

void quit(fmt) char *fmt; { msg(fmt); dumpabort(); }

#else /* lint */

D 21
void
msg(va_alist)
	va_dcl
E 21
I 21
/*
 * We have three of these.  Yes, this is horribly ugly, but at least
 * we only have to go through it once.
 */
E 22
I 22
void
E 22
#if __STDC__
D 22
#define	MSG_FDECL(func)	void func(const char *fmt, ...)
#define	MSG_VDECL	va_list ap
#define	MSG_START	va_start(ap, fmt)
E 22
I 22
msg(const char *fmt, ...)
E 22
#else
D 22
#define MSG_FDECL(func)	void func(va_alist) va_dcl
#define	MSG_VDECL	char *fmt; va_list ap
#define	MSG_START	va_start(ap); fmt = va_arg(ap, char *)
E 22
I 22
msg(fmt, va_alist)
	char *fmt;
	va_dcl
E 22
#endif
D 22

MSG_FDECL(msg)
E 22
E 21
E 13
E 5
{
D 13
	fprintf(stderr,"  DUMP: ");
E 13
I 13
D 21
	va_list ap;
	char *fmt;
E 21
I 21
D 22
	MSG_VDECL;
E 22
I 22
	va_list ap;
E 22
E 21

	(void) fprintf(stderr,"  DUMP: ");
E 13
#ifdef TDEBUG
D 13
	fprintf(stderr,"pid=%d ", getpid());
E 13
I 13
	(void) fprintf(stderr, "pid=%d ", getpid());
E 13
#endif
D 13
	fprintf(stderr, fmt, a1, a2, a3, a4, a5);
	fflush(stdout);
	fflush(stderr);
I 11
	sprintf(lastmsg, fmt, a1, a2, a3, a4, a5);
E 13
I 13
D 21
	va_start(ap);
	fmt = va_arg(ap, char *);
E 21
I 21
D 22
	MSG_START;
E 22
I 22
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
E 22
E 21
	(void) vfprintf(stderr, fmt, ap);
D 22
	va_end(ap);
E 22
	(void) fflush(stdout);
	(void) fflush(stderr);
D 21
	va_start(ap);
	fmt = va_arg(ap, char *);
E 21
I 21
D 22
	MSG_START;
E 22
E 21
	(void) vsprintf(lastmsg, fmt, ap);
	va_end(ap);
E 13
E 11
}

D 13
	/* VARARGS1 */
	/* ARGSUSED */
msgtail(fmt, a1, a2, a3, a4, a5)
	char	*fmt;
I 5
	int	a1, a2, a3, a4, a5;
E 13
I 13
D 21
void
msgtail(va_alist)
	va_dcl
E 21
I 21
D 22
MSG_FDECL(msgtail)
E 22
I 22
void
#if __STDC__
msgtail(const char *fmt, ...)
#else
msgtail(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
E 22
E 21
E 13
E 5
{
D 13
	fprintf(stderr, fmt, a1, a2, a3, a4, a5);
E 13
I 13
D 21
	va_list ap;
	char *fmt;
E 21
I 21
D 22
	MSG_VDECL;
E 21

D 21
	va_start(ap);
	fmt = va_arg(ap, char *);
E 21
I 21
	MSG_START;
E 22
I 22
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
E 22
E 21
	(void) vfprintf(stderr, fmt, ap);
	va_end(ap);
E 13
}
I 13

D 21
void
quit(va_alist)
	va_dcl
E 21
I 21
D 22
MSG_FDECL(quit)
E 22
I 22
void
#if __STDC__
quit(const char *fmt, ...)
#else
quit(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
E 22
E 21
{
D 21
	va_list ap;
	char *fmt;
E 21
I 21
D 22
	MSG_VDECL;
E 22
I 22
	va_list ap;
E 22
E 21

	(void) fprintf(stderr,"  DUMP: ");
#ifdef TDEBUG
	(void) fprintf(stderr, "pid=%d ", getpid());
#endif
D 21
	va_start(ap);
	fmt = va_arg(ap, char *);
E 21
I 21
D 22
	MSG_START;
E 22
I 22
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
E 22
E 21
D 23
	vfprintf(stderr, fmt, ap);
E 23
I 23
	(void) vfprintf(stderr, fmt, ap);
E 23
	va_end(ap);
	(void) fflush(stdout);
	(void) fflush(stderr);
D 24
	dumpabort();
E 24
I 24
	dumpabort(0);
E 24
}
D 22

#endif /* lint */
E 22

E 13
/*
 *	Tell the operator what has to be done;
 *	we don't actually do it
 */

I 7
struct fstab *
allocfsent(fs)
	register struct fstab *fs;
{
	register struct fstab *new;
D 13
	register char *cp;
	char *malloc();
E 13

	new = (struct fstab *)malloc(sizeof (*fs));
D 13
	cp = malloc(strlen(fs->fs_file) + 1);
	strcpy(cp, fs->fs_file);
	new->fs_file = cp;
	cp = malloc(strlen(fs->fs_type) + 1);
	strcpy(cp, fs->fs_type);
	new->fs_type = cp;
	cp = malloc(strlen(fs->fs_spec) + 1);
	strcpy(cp, fs->fs_spec);
	new->fs_spec = cp;
E 13
I 13
	if (new == NULL ||
	    (new->fs_file = strdup(fs->fs_file)) == NULL ||
	    (new->fs_type = strdup(fs->fs_type)) == NULL ||
	    (new->fs_spec = strdup(fs->fs_spec)) == NULL)
		quit("%s\n", strerror(errno));
E 13
	new->fs_passno = fs->fs_passno;
	new->fs_freq = fs->fs_freq;
	return (new);
}

struct	pfstab {
	struct	pfstab *pf_next;
	struct	fstab *pf_fstab;
};

D 13
static	struct pfstab *table = NULL;
E 13
I 13
static	struct pfstab *table;
E 13

I 13
void
E 13
E 7
getfstab()
{
D 7
	register	struct	fstab	*dt;
D 2
			FILE	*fstabfile;
E 2
I 2
			struct	fstab	*fsp;
E 7
I 7
	register struct fstab *fs;
	register struct pfstab *pf;
E 7
E 2

D 7
	nfstab = 0;
E 7
D 2
	if ( (fstabfile = fopen(FSTAB, "r")) == NULL){
E 2
I 2
	if (setfsent() == 0) {
E 2
D 11
		msg("Can't open %s for dump table information.\n", FSTAB);
E 11
I 11
D 13
		msg("Can't open %s for dump table information.\n", _PATH_FSTAB);
E 13
I 13
		msg("Can't open %s for dump table information: %s\n",
		    _PATH_FSTAB, strerror(errno));
E 13
E 11
D 7
	} else {
		for (nfstab = 0, dt = fstab; nfstab < MAXFSTAB;){
D 2
			if (feof(fstabfile))
E 2
I 2
			if ( (fsp = getfsent()) == 0)
E 2
				break;
D 2
			fscanf(fstabfile, FSTABFMT, FSTABARG(dt));
			if (!strcmp(dt->fs_type, "rw") ||
			    !strcmp(dt->fs_type, "ro"))
				nfstab++, dt++;
E 2
I 2
			if (   (strcmp(fsp->fs_type, FSTAB_RW) == 0)
			    || (strcmp(fsp->fs_type, FSTAB_RO) == 0) ){
				*dt = *fsp;
				nfstab++; 
				dt++;
			}
E 2
		}
D 2
		fclose(fstabfile);
E 2
I 2
		endfsent();
E 7
I 7
		return;
E 7
E 2
	}
I 7
D 26
	while (fs = getfsent()) {
E 26
I 26
	while ((fs = getfsent()) != NULL) {
E 26
		if (strcmp(fs->fs_type, FSTAB_RW) &&
		    strcmp(fs->fs_type, FSTAB_RO) &&
		    strcmp(fs->fs_type, FSTAB_RQ))
			continue;
		fs = allocfsent(fs);
D 13
		pf = (struct pfstab *)malloc(sizeof (*pf));
E 13
I 13
		if ((pf = (struct pfstab *)malloc(sizeof (*pf))) == NULL)
			quit("%s\n", strerror(errno));
E 13
		pf->pf_fstab = fs;
		pf->pf_next = table;
		table = pf;
	}
D 23
	endfsent();
E 23
I 23
	(void) endfsent();
E 23
E 7
}

/*
D 7
 *	Search in the fstab for a file name.
 *	This file name can be either the special or the path file name.
E 7
I 7
 * Search in the fstab for a file name.
 * This file name can be either the special or the path file name.
E 7
 *
D 7
 *	The entries in the fstab are the BLOCK special names, not the
 *	character special names.
 *	The caller of fstabsearch assures that the character device
 *	is dumped (that is much faster)
E 7
I 7
 * The entries in the fstab are the BLOCK special names, not the
 * character special names.
 * The caller of fstabsearch assures that the character device
 * is dumped (that is much faster)
E 7
 *
D 7
 *	The file name can omit the leading '/'.
E 7
I 7
 * The file name can omit the leading '/'.
E 7
 */
D 7
struct	fstab	*fstabsearch(key)
	char	*key;
E 7
I 7
struct fstab *
fstabsearch(key)
	char *key;
E 7
{
D 7
	register	struct	fstab *dt;
			int	i;
			int	keylength;
			char	*rawname();
E 7
I 7
	register struct pfstab *pf;
	register struct fstab *fs;
I 28
	char *rn;
E 28
D 8
	register int i, keylength;
E 8
D 25
	char *rawname();
E 25
E 7

D 7
	keylength = min(strlen(key), sizeof (dt->fs_file));
	for (i = 0, dt = fstab; i < nfstab; i++, dt++){
		if (strncmp(dt->fs_file, key, keylength) == 0)
			return(dt);
		if (strncmp(dt->fs_spec, key, keylength) == 0)
			return(dt);
		if (strncmp(rawname(dt->fs_spec), key, keylength) == 0)
			return(dt);

E 7
I 7
D 13
	if (table == NULL)
		return ((struct fstab *)0);
D 8
	keylength = min(strlen(key), sizeof (table->pf_fstab->fs_file));
E 8
	for (pf = table; pf; pf = pf->pf_next) {
E 13
I 13
	for (pf = table; pf != NULL; pf = pf->pf_next) {
E 13
		fs = pf->pf_fstab;
D 8
		if (strncmp(fs->fs_file, key, keylength) == 0)
E 8
I 8
D 13
		if (strcmp(fs->fs_file, key) == 0)
E 13
I 13
		if (strcmp(fs->fs_file, key) == 0 ||
D 28
		    strcmp(fs->fs_spec, key) == 0 ||
		    strcmp(rawname(fs->fs_spec), key) == 0)
E 28
I 28
		    strcmp(fs->fs_spec, key) == 0)
			return (fs);
		rn = rawname(fs->fs_spec);
		if (rn != NULL && strcmp(rn, key) == 0)
E 28
E 13
E 8
			return (fs);
D 8
		if (strncmp(fs->fs_spec, key, keylength) == 0)
E 8
I 8
D 13
		if (strcmp(fs->fs_spec, key) == 0)
E 8
			return (fs);
D 8
		if (strncmp(rawname(fs->fs_spec), key, keylength) == 0)
E 8
I 8
		if (strcmp(rawname(fs->fs_spec), key) == 0)
E 8
			return (fs);
E 7
		if (key[0] != '/'){
E 13
I 13
		if (key[0] != '/') {
E 13
D 7
			if (   (dt->fs_spec[0] == '/')
			    && (strncmp(dt->fs_spec+1, key, keylength) == 0))
				return(dt);
			if (   (dt->fs_file[0] == '/')
			    && (strncmp(dt->fs_file+1, key, keylength) == 0))
				return(dt);
E 7
I 7
			if (*fs->fs_spec == '/' &&
D 8
			    strncmp(fs->fs_spec + 1, key, keylength) == 0)
E 8
I 8
			    strcmp(fs->fs_spec + 1, key) == 0)
E 8
				return (fs);
			if (*fs->fs_file == '/' &&
D 8
			    strncmp(fs->fs_file + 1, key, keylength) == 0)
E 8
I 8
			    strcmp(fs->fs_file + 1, key) == 0)
E 8
				return (fs);
E 7
		}
	}
D 7
	return(0);
E 7
I 7
D 13
	return (0);
E 13
I 13
	return (NULL);
E 13
E 7
}

/*
 *	Tell the operator what to do
 */
I 13
void
E 13
D 3
lastdump()
E 3
I 3
lastdump(arg)
D 13
	char	arg;		/* w ==> just what to do; W ==> most recent dumps */
E 13
I 13
	char	arg;	/* w ==> just what to do; W ==> most recent dumps */
E 13
E 3
{
D 14
			char	*lastname;
			char	*date;
	register	int	i;
			time_t	tnow;
	register	struct	fstab	*dt;
			int	dumpme;
	register	struct	idates	*itwalk;
E 14
I 14
	register int i;
	register struct fstab *dt;
	register struct dumpdates *dtwalk;
	char *lastname, *date;
D 25
	int dumpme, datesort();
E 25
I 25
	int dumpme;
E 25
	time_t tnow;
E 14

D 14
	int	idatesort();

E 14
D 23
	time(&tnow);
E 23
I 23
	(void) time(&tnow);
E 23
	getfstab();		/* /etc/fstab input */
D 14
	inititimes();		/* /etc/dumpdates input */
	qsort(idatev, nidates, sizeof(struct idates *), idatesort);
E 14
I 14
	initdumptimes();	/* /etc/dumpdates input */
D 23
	qsort(ddatev, nddates, sizeof(struct dumpdates *), datesort);
E 23
I 23
	qsort((char *) ddatev, nddates, sizeof(struct dumpdates *), datesort);
E 23
E 14

D 3
	fprintf(stdout, "Last dump(s) done (Dump '*' file systems):\n");
E 3
I 3
	if (arg == 'w')
D 13
		fprintf(stdout, "Dump these file systems:\n");
E 13
I 13
		(void) printf("Dump these file systems:\n");
E 13
	else
D 13
		fprintf(stdout, "Last dump(s) done (Dump '>' file systems):\n");
E 13
I 13
		(void) printf("Last dump(s) done (Dump '>' file systems):\n");
E 13
E 3
	lastname = "??";
D 13
	ITITERATE(i, itwalk){
E 13
I 13
D 14
	ITITERATE(i, itwalk) {
E 13
		if (strncmp(lastname, itwalk->id_name, sizeof(itwalk->id_name)) == 0)
E 14
I 14
	ITITERATE(i, dtwalk) {
		if (strncmp(lastname, dtwalk->dd_name,
		    sizeof(dtwalk->dd_name)) == 0)
E 14
			continue;
D 14
		date = (char *)ctime(&itwalk->id_ddate);
E 14
I 14
		date = (char *)ctime(&dtwalk->dd_ddate);
E 14
D 13
		date[16] = '\0';		/* blast away seconds and year */
E 13
I 13
		date[16] = '\0';	/* blast away seconds and year */
E 13
D 14
		lastname = itwalk->id_name;
		dt = fstabsearch(itwalk->id_name);
E 14
I 14
		lastname = dtwalk->dd_name;
		dt = fstabsearch(dtwalk->dd_name);
E 14
D 13
		dumpme = (  (dt != 0)
			 && (dt->fs_freq != 0)
			 && (itwalk->id_ddate < tnow - (dt->fs_freq*DAY)));
D 3
		fprintf(stdout,"%c %8s\t(%6s) Last dump: Level %c, Date %s\n",
			dumpme ? '*' : ' ',
E 3
I 3
		if ( (arg != 'w') || dumpme)
		  fprintf(stdout,"%c %8s\t(%6s) Last dump: Level %c, Date %s\n",
			dumpme && (arg != 'w') ? '>' : ' ',
E 3
			itwalk->id_name,
D 6
			dt ? dt->fs_file : 0,
E 6
I 6
			dt ? dt->fs_file : "",
E 6
			itwalk->id_incno,
			date
		    );
E 13
I 13
		dumpme = (dt != NULL &&
		    dt->fs_freq != 0 &&
D 14
		    itwalk->id_ddate < tnow - (dt->fs_freq * DAY));
E 14
I 14
D 16
		    dtwalk->dd_ddate < tnow - (dt->fs_freq * DAY));
E 16
I 16
		    dtwalk->dd_ddate < tnow - (dt->fs_freq * SECSPERDAY));
E 16
E 14
		if (arg != 'w' || dumpme)
			(void) printf(
			    "%c %8s\t(%6s) Last dump: Level %c, Date %s\n",
			    dumpme && (arg != 'w') ? '>' : ' ',
D 14
			    itwalk->id_name,
E 14
I 14
			    dtwalk->dd_name,
E 14
			    dt ? dt->fs_file : "",
D 14
			    itwalk->id_incno,
E 14
I 14
			    dtwalk->dd_level,
E 14
			    date);
E 13
	}
}

D 13
int	idatesort(p1, p2)
	struct	idates	**p1, **p2;
E 13
I 13
D 14
int	idatesort(a1, a2)
E 14
I 14
int
datesort(a1, a2)
E 14
D 25
	void *a1, *a2;
E 25
I 25
	const void *a1, *a2;
E 25
E 13
{
D 13
	int	diff;
E 13
I 13
D 14
	struct idates *d1 = *(struct idates **)a1, *d2 = *(struct idates **)a2;
E 14
I 14
	struct dumpdates *d1 = *(struct dumpdates **)a1;
	struct dumpdates *d2 = *(struct dumpdates **)a2;
E 14
	int diff;
E 13

D 13
	diff = strncmp((*p1)->id_name, (*p2)->id_name, sizeof((*p1)->id_name));
E 13
I 13
D 14
	diff = strncmp(d1->id_name, d2->id_name, sizeof(d1->id_name));
E 14
I 14
	diff = strncmp(d1->dd_name, d2->dd_name, sizeof(d1->dd_name));
E 14
E 13
	if (diff == 0)
D 13
		return ((*p2)->id_ddate - (*p1)->id_ddate);
E 13
I 13
D 14
		return (d2->id_ddate - d1->id_ddate);
E 13
	else
		return (diff);
E 14
I 14
		return (d2->dd_ddate - d1->dd_ddate);
	return (diff);
E 14
}
D 25

E 25
D 13
int max(a,b)
E 13
I 13
D 23
int max(a, b)
E 13
I 5
	int a, b;
E 5
{
D 13
	return(a>b?a:b);
E 13
I 13
	return (a > b ? a : b);
E 13
}
D 13
int min(a,b)
E 13
I 13
int min(a, b)
E 13
I 5
	int a, b;
E 5
{
D 13
	return(a<b?a:b);
E 13
I 13
	return (a < b ? a : b);
E 13
}
E 23
E 1
