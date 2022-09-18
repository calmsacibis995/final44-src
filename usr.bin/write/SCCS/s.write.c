h59237
s 00024/00047/00253
d D 8.2 95/04/27 16:55:36 bostic 24 23
c make write(1) use the err*(3) and warn*(3) functions
c rindex -> strrchr
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00005/00005/00295
d D 8.1 93/06/06 22:27:47 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00299
d D 4.22 90/06/01 18:36:21 bostic 22 21
c new copyright notice
e
s 00001/00001/00309
d D 4.21 90/05/15 19:54:30 bostic 21 20
c string.h is ANSI C include file
e
s 00002/00002/00308
d D 4.20 89/11/25 20:39:50 leres 20 19
c Move getlogin() declaration to do_write() where it's needed.
e
s 00008/00007/00302
d D 4.19 89/11/25 20:34:45 leres 19 18
c Need to determine our login name before we reopen() stdout.
e
s 00000/00001/00309
d D 4.18 89/11/24 03:27:49 leres 18 17
c Don't need to include paths.h.
e
s 00026/00027/00284
d D 4.17 89/11/22 11:55:31 bostic 17 16
c minor cleanups, catch HUP as well as INT
e
s 00261/00198/00050
d D 4.16 89/11/21 11:46:39 bostic 16 15
c new version from Jef Poskanzer and Craig Leres
e
s 00005/00005/00243
d D 4.15 89/05/11 13:47:54 bostic 15 14
c file reorg, pathnames.h, paths.h
e
s 00006/00005/00242
d D 4.14 89/03/05 21:58:03 bostic 14 13
c add pathnames.h
e
s 00004/00002/00243
d D 4.13 86/03/13 18:40:46 mckusick 13 12
c setgid to group "write" so that terminals need not be world writable
e
s 00006/00012/00239
d D 4.12 86/02/04 15:35:06 karels 12 11
c more grot
e
s 00029/00018/00222
d D 4.11 86/02/04 15:28:02 karels 11 10
c (once more?) look for writable terminal if first found isn't writable;
c if root, still look for writable terminal before barging in, but use first
c if none are writable
e
s 00003/00002/00237
d D 4.10 85/06/07 14:59:21 lepreau 10 9
c allow superuser to do anything
e
s 00054/00024/00185
d D 4.9 85/06/07 03:08:54 serge 9 8
c print visible representations of non printable characters
e
s 00001/00001/00208
d D 4.8 83/07/01 23:58:28 wnj 8 7
c include problems
e
s 00002/00002/00207
d D 4.7 83/03/01 21:58:24 leres 7 6
c Changed ^G's to \007's
e
s 00004/00001/00205
d D 4.6 82/07/14 21:24:24 kre 6 5
c indicate if write fails (usually since other end hung up).
e
s 00043/00043/00163
d D 4.5 82/03/15 04:25:01 root 5 4
c machine independent
e
s 00003/00002/00203
d D 4.4 82/01/27 10:16:01 root 4 3
c Changed notification of write message to include the system name
e
s 00008/00000/00197
d D 4.3 80/12/10 18:27:23 erics 3 2
c Check whether writer has write permission turned on
e
s 00002/00000/00195
d D 4.2 80/11/10 20:18:04 eric 2 1
c fix to bug when adding delete ttys lines
e
s 00195/00000/00000
d D 4.1 80/10/01 17:29:40 bill 1 0
c date and time created 80/10/01 17:29:40 by bill
e
u
U
t
T
I 9
D 16
#ifndef	lint
E 9
I 1
D 5
static char *sccsid = "%W% (Berkeley) %G%";
E 5
I 5
static char *sccsid = "%W% %G%";
I 9
#endif
E 16
E 9
E 5
/*
D 16
 * write to another user
E 16
I 16
D 23
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 *
 * This code is derived from software contributed to Berkeley by
 * Jef Poskanzer and Craig Leres of the Lawrence Berkeley Laboratory.
 *
D 22
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 22
I 22
 * %sccs.include.redist.c%
E 22
E 16
 */

D 15
#include <stdio.h>
I 9
#include <ctype.h>
E 15
E 9
D 16
#include <sys/types.h>
#include <sys/stat.h>
E 16
I 16
#ifndef lint
D 23
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 23
I 23
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 23
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
E 16
D 15
#include <signal.h>
#include <utmp.h>
E 15
I 15
#include <sys/signal.h>
I 16
#include <sys/stat.h>
#include <sys/file.h>
E 16
E 15
D 8
#include <time.h>
E 8
I 8
#include <sys/time.h>
I 24

#include <err.h>
E 24
I 14
D 15
#include "pathnames.h"
E 15
I 15
#include <utmp.h>
D 16
#include <stdio.h>
E 16
#include <ctype.h>
D 18
#include <paths.h>
E 18
I 16
#include <pwd.h>
#include <stdio.h>
D 21
#include <strings.h>
E 21
I 21
#include <string.h>
E 21
E 16
E 15
E 14
E 8
I 4
D 5
#include <whoami.h>
E 5
E 4

D 5
#define NMAX sizeof(ubuf.ut_name)
#define LMAX sizeof(ubuf.ut_line)
E 5
I 5
D 16
#define	NMAX	sizeof(ubuf.ut_name)
#define	LMAX	sizeof(ubuf.ut_line)
E 16
I 16
D 17
#define STRCPY(s1, s2) \
    { (void)strncpy(s1, s2, sizeof(s1)); s1[sizeof(s1) - 1] = '\0'; }
E 17
I 17
extern int errno;
E 17
E 16
E 5

D 16
char	*strcat();
char	*strcpy();
struct	utmp ubuf;
int	signum[] = {SIGHUP, SIGINT, SIGQUIT, 0};
D 9
char	me[10]	= "???";
E 9
I 9
char	me[NMAX + 1]	= "???";
E 9
char	*him;
char	*mytty;
char	histty[32];
I 11
char	ttybuf[32];
E 11
char	*histtya;
char	*ttyname();
char	*rindex();
int	logcnt;
int	eof();
int	timout();
FILE	*tf;
char	*getenv();
E 16
I 16
D 17
int uid;					/* myuid */
E 16

E 17
main(argc, argv)
D 5
char *argv[];
E 5
I 5
	int argc;
D 16
	char *argv[];
E 16
I 16
	char **argv;
E 16
E 5
{
D 16
	struct stat stbuf;
	register i;
	register FILE *uf;
	int c1, c2;
D 5
	long	clock = time( 0 );
E 5
I 5
	long clock = time(0);
I 10
	int suser = getuid() == 0;
I 11
	int nomesg = 0;
E 11
E 10
E 5
	struct tm *localtime();
	struct tm *localclock = localtime( &clock );
E 16
I 16
D 17
	extern int errno;
E 17
	register char *cp;
D 17
	char tty[MAXPATHLEN];
	int msgsok, myttyfd;
E 17
	time_t atime;
D 17
	char *mytty, *getlogin(), *ttyname();
E 17
I 17
	uid_t myuid;
	int msgsok, myttyfd;
D 20
	char tty[MAXPATHLEN], *mytty, *getlogin(), *ttyname();
E 20
I 20
	char tty[MAXPATHLEN], *mytty, *ttyname();
E 20
E 17
	void done();
E 16

D 5
	if(argc < 2) {
E 5
I 5
D 16
	if (argc < 2) {
E 5
D 9
		printf("usage: write user [ttyname]\n");
E 9
I 9
		fprintf(stderr, "Usage: write user [ttyname]\n");
E 16
I 16
D 17
	/* check that sender has write enabled. */
E 17
I 17
	/* check that sender has write enabled */
E 17
	if (isatty(fileno(stdin)))
		myttyfd = fileno(stdin);
	else if (isatty(fileno(stdout)))
		myttyfd = fileno(stdout);
	else if (isatty(fileno(stderr)))
		myttyfd = fileno(stderr);
D 24
	else {
		(void)fprintf(stderr, "write: can't find your tty\n");
E 16
E 9
		exit(1);
	}
D 16
	him = argv[1];
D 5
	if(argc > 2)
E 5
I 5
	if (argc > 2)
E 5
		histtya = argv[2];
D 14
	if ((uf = fopen("/etc/utmp", "r")) == NULL) {
D 9
		printf("cannot open /etc/utmp\n");
E 9
I 9
		perror("write: Can't open /etc/utmp");
E 14
I 14
	if ((uf = fopen(_PATH_UTMP, "r")) == NULL) {
		fprintf(stderr, "write: can't read %s\n", _PATH_UTMP);
E 14
I 12
		if (histtya == 0)
			exit(10);
E 12
E 9
		goto cont;
	}
	mytty = ttyname(2);
	if (mytty == NULL) {
D 9
		printf("Can't find your tty\n");
E 9
I 9
		fprintf(stderr, "write: Can't find your tty\n");
E 16
I 16
	if (!(mytty = ttyname(myttyfd))) {
		(void)fprintf(stderr, "write: can't find your tty's name\n");
E 16
E 9
		exit(1);
	}
I 3
D 5
	if (stat (mytty, &stbuf) < 0) {
		printf ("Can't stat your tty\n");
		exit (1);
E 5
I 5
D 16
	if (stat(mytty, &stbuf) < 0) {
D 9
		printf("Can't stat your tty\n");
E 9
I 9
		perror("write: Can't stat your tty");
E 16
I 16
	if (cp = rindex(mytty, '/'))
E 24
I 24
	else
		errx(1, "can't find your tty");
	if (!(mytty = ttyname(myttyfd)))
		errx(1, "can't find your tty's name");
	if (cp = strrchr(mytty, '/'))
E 24
		mytty = cp + 1;
	if (term_chk(mytty, &msgsok, &atime, 1))
E 16
E 9
		exit(1);
I 16
D 24
	if (!msgsok) {
		(void)fprintf(stderr,
		    "write: you have write permission turned off.\n");
		exit(1);
E 16
E 5
	}
E 24
I 24
	if (!msgsok)
		errx(1, "you have write permission turned off");
E 24
D 10
	if ((stbuf.st_mode&02) == 0) {
E 10
I 10
D 11
	if (!suser && (stbuf.st_mode&02) == 0) {
E 11
I 11
D 13
	if ((stbuf.st_mode&02) == 0) {
E 13
I 13
D 16
	if ((stbuf.st_mode&020) == 0) {
E 13
E 11
E 10
D 5
		printf ("You have write permission turned off.\n");
		exit (1);
E 5
I 5
D 9
		printf("You have write permission turned off.\n");
E 9
I 9
		fprintf(stderr,
			"write: You have write permission turned off\n");
E 9
D 11
		exit(1);
E 11
I 11
		if (!suser)
E 16
I 16

D 17
	uid = getuid();
E 17
I 17
	myuid = getuid();
E 17

	/* check args */
	switch (argc) {
	case 2:
D 17
		search_utmp(argv[1], tty, mytty);
		do_write(tty, mytty);
E 17
I 17
		search_utmp(argv[1], tty, mytty, myuid);
		do_write(tty, mytty, myuid);
E 17
		break;
	case 3:
		if (!strncmp(argv[2], "/dev/", 5))
			argv[2] += 5;
D 24
		if (utmp_chk(argv[1], argv[2])) {
			(void)fprintf(stderr,
			    "write: %s is not logged in on %s.\n",
E 24
I 24
		if (utmp_chk(argv[1], argv[2]))
			errx(1, "%s is not logged in on %s",
E 24
			    argv[1], argv[2]);
E 16
D 24
			exit(1);
E 11
E 5
D 16
	}
E 3
	mytty = rindex(mytty, '/') + 1;
	if (histtya) {
D 14
		strcpy(histty, "/dev/");
E 14
I 14
		strcpy(histty, _PATH_DEV);
E 14
		strcat(histty, histtya);
	}
	while (fread((char *)&ubuf, sizeof(ubuf), 1, uf) == 1) {
I 2
		if (ubuf.ut_name[0] == '\0')
			continue;
E 2
		if (strcmp(ubuf.ut_line, mytty)==0) {
D 5
			for(i=0; i<NMAX; i++) {
E 5
I 5
			for (i=0; i<NMAX; i++) {
E 5
				c1 = ubuf.ut_name[i];
D 5
				if(c1 == ' ')
E 5
I 5
				if (c1 == ' ')
E 5
					c1 = 0;
				me[i] = c1;
D 5
				if(c1 == 0)
E 5
I 5
				if (c1 == 0)
E 5
					break;
			}
E 16
		}
E 24
D 5
		if(him[0] != '-' || him[1] != 0)
		for(i=0; i<NMAX; i++) {
E 5
I 5
D 9
		if (him[0] != '-' || him[1] != 0)
E 9
I 9
D 16
		if (him[0] == '-' && him[1] == 0)
			goto nomat;
E 9
		for (i=0; i<NMAX; i++) {
E 5
			c1 = him[i];
			c2 = ubuf.ut_name[i];
D 5
			if(c1 == 0)
				if(c2 == 0 || c2 == ' ')
E 5
I 5
			if (c1 == 0)
				if (c2 == 0 || c2 == ' ')
E 5
					break;
D 5
			if(c1 != c2)
E 5
I 5
			if (c1 != c2)
E 5
				goto nomat;
E 16
I 16
		if (term_chk(argv[2], &msgsok, &atime, 1))
			exit(1);
D 17
		if (uid && !msgsok) {
E 17
I 17
D 24
		if (myuid && !msgsok) {
E 17
			(void)fprintf(stderr,
			    "write: %s has messages disabled on %s\n",
E 24
I 24
		if (myuid && !msgsok)
			errx(1, "%s has messages disabled on %s",
E 24
			    argv[1], argv[2]);
D 24
			exit(1);
E 16
		}
E 24
I 11
D 16
		if (histtya && strncmp(histtya, ubuf.ut_line,
		    sizeof(ubuf.ut_line)))
			continue;
E 11
		logcnt++;
D 11
		if (histty[0]==0) {
			strcpy(histty, "/dev/");
			strcat(histty, ubuf.ut_line);
E 11
I 11
		if (histty[0]==0 || nomesg && histtya == 0) {
D 14
			strcpy(ttybuf, "/dev/");
E 14
I 14
			strcpy(ttybuf, _PATH_DEV);
E 14
			strcat(ttybuf, ubuf.ut_line);
			if (histty[0]==0)
				strcpy(histty, ttybuf);
			if (access(ttybuf, 0) < 0 || stat(ttybuf, &stbuf) < 0 ||
D 13
			    (stbuf.st_mode&02) == 0)
E 13
I 13
			    (stbuf.st_mode&020) == 0)
E 13
				nomesg++;
			else {
				strcpy(histty, ttybuf);
				nomesg = 0;
			}
E 11
		}
	nomat:
		;
	}
D 12
cont:
E 12
I 12
	fclose(uf);
E 12
D 11
	if (logcnt==0 && histty[0]=='\0') {
E 11
I 11
	if (logcnt==0) {
E 11
D 9
		printf("%s not logged in.\n", him);
E 9
I 9
D 12
		fprintf(stderr, "write: %s not logged in\n", him);
E 12
I 12
		fprintf(stderr, "write: %s not logged in%s\n", him,
			histtya ? " on that tty" : "");
E 16
I 16
D 17
		do_write(argv[2], mytty);
E 17
I 17
		do_write(argv[2], mytty, myuid);
E 17
		break;
	default:
		(void)fprintf(stderr, "usage: write user [tty]\n");
E 16
E 12
E 9
		exit(1);
	}
D 9
	fclose(uf);
E 9
I 9
D 12
	if (uf != NULL)
		fclose(uf);
E 12
E 9
D 16
	if (histtya==0 && logcnt > 1) {
D 9
		printf("%s logged more than once\nwriting to %s\n", him, histty+5);
E 9
I 9
		fprintf(stderr,
		"write: %s logged in more than once ... writing to %s\n",
			him, histty+5);
E 9
	}
D 5
	if(histty[0] == 0) {
E 5
I 5
D 11
	if (histty[0] == 0) {
E 11
I 11
D 12
	if (logcnt == 0) {
E 11
E 5
		printf(him);
D 5
		if(logcnt)
E 5
I 5
D 11
		if (logcnt)
E 5
			printf(" not on that tty\n"); else
E 11
I 11
		if (histtya)
			printf(" not on that tty\n");
		else
E 11
			printf(" not logged in\n");
		exit(1);
	}
E 12
I 12
cont:
E 12
	if (access(histty, 0) < 0) {
D 9
		printf("No such tty\n");
E 9
I 9
		fprintf(stderr, "write: No such tty\n");
E 9
		exit(1);
	}
	signal(SIGALRM, timout);
	alarm(5);
D 11
	if ((tf = fopen(histty, "w")) == NULL)
		goto perm;
E 11
I 11
	if ((tf = fopen(histty, "w")) == NULL) {
		fprintf(stderr, "write: Permission denied\n");
		exit(1);
	}
E 11
	alarm(0);
D 11
	if (fstat(fileno(tf), &stbuf) < 0)
		goto perm;
D 10
	if ((stbuf.st_mode&02) == 0)
E 10
I 10
	if (!suser && (stbuf.st_mode&02) == 0)
E 10
		goto perm;
E 11
	sigs(eof);
D 5
	fprintf(tf, "\r\nMessage from ");
#ifdef interdata
	fprintf(tf, "(Interdata) " );
#endif
D 4
	fprintf(tf, "%s on %s at %d:%02d ...\r\n"
	       , me, mytty , localclock -> tm_hour , localclock -> tm_min );
E 4
I 4
	fprintf(tf, "%s!%s on %s at %d:%02d ...\r\n"
	       , sysname , me, mytty , localclock -> tm_hour , localclock -> tm_min );
E 5
I 5
	{ char hostname[32];
	  gethostname(hostname, sizeof (hostname));
D 9
	  fprintf(tf, "\r\nMessage from ");
D 7
	  fprintf(tf, "%s!%s on %s at %d:%02d ...\r\n",
E 7
I 7
	  fprintf(tf, "%s!%s on %s at %d:%02d ...\r\n\007\007\007",
E 7
	      hostname, me, mytty, localclock->tm_hour, localclock->tm_min);
	}
E 9
I 9
	  fprintf(tf,
	      "\r\nMessage from %s@%s on %s at %d:%02d ...\r\n\007\007\007",
	      me, hostname, mytty, localclock->tm_hour, localclock->tm_min);
E 9
E 5
E 4
	fflush(tf);
I 9
	}
E 9
D 5
	for(;;) {
E 5
I 5
	for (;;) {
E 5
D 9
		char buf[128];
		i = read(0, buf, 128);
E 9
I 9
		char buf[BUFSIZ];
		register char *bp;
		i = read(0, buf, sizeof buf);
E 9
D 5
		if(i <= 0)
E 5
I 5
		if (i <= 0)
E 5
			eof();
D 5
		if(buf[0] == '!') {
E 5
I 5
		if (buf[0] == '!') {
E 5
			buf[i] = 0;
			ex(buf);
			continue;
E 16
I 16
	done();
	/* NOTREACHED */
}

/*
 * utmp_chk - checks that the given user is actually logged in on
 *     the given tty
 */
utmp_chk(user, tty)
	char *user, *tty;
{
	struct utmp u;
	int ufd;

	if ((ufd = open(_PATH_UTMP, O_RDONLY)) < 0)
		return(0);	/* ignore error, shouldn't happen anyway */

	while (read(ufd, (char *) &u, sizeof(u)) == sizeof(u))
		if (strncmp(user, u.ut_name, sizeof(u.ut_name)) == 0 &&
		    strncmp(tty, u.ut_line, sizeof(u.ut_line)) == 0) {
			(void)close(ufd);
			return(0);
E 16
		}
D 6
		write(fileno(tf), buf, i);
E 6
I 6
D 9
		if (write(fileno(tf), buf, i) != i) {
D 7
			printf("\n\7Write failed (%s logged out?)\n", him);
E 7
I 7
			printf("\n\007Write failed (%s logged out?)\n", him);
E 7
			exit(1);
E 9
I 9
D 16
		for (bp = buf; --i >= 0; bp++) {
			if (*bp == '\n')
				putc('\r', tf);
E 16

D 16
			if (!isascii(*bp)) {
				putc('M', tf);
				putc('-', tf);
				*bp = toascii(*bp);
			}
E 16
I 16
	(void)close(ufd);
	return(1);
}
E 16

D 16
			if (isprint(*bp) ||
			    *bp == ' ' || *bp == '\t' || *bp == '\n') {
				putc(*bp, tf);
			} else {
				putc('^', tf);
				putc(*bp ^ 0100, tf);
			}
E 16
I 16
/*
 * search_utmp - search utmp for the "best" terminal to write to
 *
 * Ignores terminals with messages disabled, and of the rest, returns
 * the one with the most recent access time.  Returns as value the number
 * of the user's terminals with messages enabled, or -1 if the user is
 * not logged in at all.
 *
 * Special case for writing to yourself - ignore the terminal you're
 * writing from, unless that's the only terminal with messages enabled.
 */
D 17
search_utmp(user, tty, mytty)
E 17
I 17
search_utmp(user, tty, mytty, myuid)
E 17
	char *user, *tty, *mytty;
I 17
	uid_t myuid;
E 17
{
	struct utmp u;
	time_t bestatime, atime;
	int ufd, nloggedttys, nttys, msgsok, user_is_me;
	char atty[UT_LINESIZE + 1];
E 16

D 16
			if (*bp == '\n')
				fflush(tf);
E 16
I 16
D 24
	if ((ufd = open(_PATH_UTMP, O_RDONLY)) < 0) {
		perror("utmp");
		exit(1);
	}
E 24
I 24
	if ((ufd = open(_PATH_UTMP, O_RDONLY)) < 0)
		err(1, "%s", _PATH_UTMP);
E 24
E 16

D 16
			if (ferror(tf) || feof(tf)) {
				printf("\n\007Write failed (%s logged out?)\n",
					him);
				exit(1);
E 16
I 16
	nloggedttys = nttys = 0;
	bestatime = 0;
	user_is_me = 0;
	while (read(ufd, (char *) &u, sizeof(u)) == sizeof(u))
		if (strncmp(user, u.ut_name, sizeof(u.ut_name)) == 0) {
			++nloggedttys;
D 17
			STRCPY(atty, u.ut_line);
E 17
I 17
			(void)strncpy(atty, u.ut_line, UT_LINESIZE);
			atty[UT_LINESIZE] = '\0';
E 17
			if (term_chk(atty, &msgsok, &atime, 0))
				continue;	/* bad term? skip */
D 17
			if (uid && !msgsok)
E 17
I 17
			if (myuid && !msgsok)
E 17
				continue;	/* skip ttys with msgs off */
			if (strcmp(atty, mytty) == 0) {
				user_is_me = 1;
				continue;	/* don't write to yourself */
E 16
			}
I 16
			++nttys;
			if (atime > bestatime) {
				bestatime = atime;
				(void)strcpy(tty, atty);
			}
E 16
E 9
		}
I 16

	(void)close(ufd);
D 24
	if (nloggedttys == 0) {
		(void)fprintf(stderr, "write: %s is not logged in\n", user);
		exit(1);
E 16
E 6
D 5
		if ( buf[ i - 1 ] == '\n' )
		    write( fileno( tf ) , "\r" , 1 );
E 5
I 5
D 9
		if (buf[i-1] == '\n')
			write(fileno(tf), "\r", 1);
E 9
E 5
	}
E 24
I 24
	if (nloggedttys == 0)
		errx(1, "%s is not logged in", user);
E 24
I 16
	if (nttys == 0) {
		if (user_is_me) {		/* ok, so write to yourself! */
			(void)strcpy(tty, mytty);
			return;
		}
D 24
		(void)fprintf(stderr,
		    "write: %s has messages disabled\n", user);
		exit(1);
	} else if (nttys > 1) {
		(void)fprintf(stderr,
		    "write: %s is logged in more than once; writing to %s\n",
E 24
I 24
		errx(1, "%s has messages disabled", user);
	} else if (nttys > 1)
		warnx("%s is logged in more than once; writing to %s",
E 24
		    user, tty);
D 24
	}
E 24
E 16
D 5

E 5
D 11
perm:
D 9
	printf("Permission denied\n");
E 9
I 9
	fprintf(stderr, "write: Permission denied\n");
E 9
	exit(1);
E 11
}

D 16
timout()
E 16
I 16
/*
 * term_chk - check that a terminal exists, and get the message bit
 *     and the access time
 */
term_chk(tty, msgsokP, atimeP, showerror)
	char *tty;
	int *msgsokP, showerror;
	time_t *atimeP;
E 16
{
I 16
	struct stat s;
	char path[MAXPATHLEN];
E 16

D 9
	printf("Timeout opening their tty\n");
E 9
I 9
D 16
	fprintf(stderr, "write: Timeout opening their tty\n");
E 9
	exit(1);
E 16
I 16
	(void)sprintf(path, "/dev/%s", tty);
	if (stat(path, &s) < 0) {
		if (showerror)
D 17
			(void)fprintf(stderr, "write: %s: %s\n",
			    path, strerror(errno));
E 17
I 17
D 24
			(void)fprintf(stderr,
			    "write: %s: %s\n", path, strerror(errno));
E 24
I 24
			warn("%s", path);
E 24
E 17
		return(1);
	}
	*msgsokP = (s.st_mode & (S_IWRITE >> 3)) != 0;	/* group write bit */
	*atimeP = s.st_atime;
	return(0);
E 16
}

D 16
eof()
E 16
I 16
/*
 * do_write - actually make the connection
 */
D 17
do_write(tty, mytty)
E 17
I 17
do_write(tty, mytty, myuid)
E 17
	char *tty, *mytty;
I 17
	uid_t myuid;
E 17
E 16
{
I 16
	register char *login, *nows;
	register struct passwd *pwd;
	time_t now, time();
D 20
	char path[MAXPATHLEN], host[MAXHOSTNAMELEN], line[512];
E 20
I 20
	char *getlogin(), path[MAXPATHLEN], host[MAXHOSTNAMELEN], line[512];
E 20
	void done();
E 16

I 19
	/* Determine our login name before the we reopen() stdout */
	if ((login = getlogin()) == NULL)
		if (pwd = getpwuid(myuid))
			login = pwd->pw_name;
		else
			login = "???";

E 19
D 16
	fprintf(tf, "EOF\r\n");
	exit(0);
E 16
I 16
	(void)sprintf(path, "/dev/%s", tty);
D 24
	if ((freopen(path, "w", stdout)) == NULL) {
D 19
		(void)fprintf(stderr,
		    "write: %s: %s\n", path, strerror(errno));
E 19
I 19
		(void)fprintf(stderr, "write: %s: %s\n", path, strerror(errno));
E 19
		exit(1);
	}
E 24
I 24
	if ((freopen(path, "w", stdout)) == NULL)
		err(1, "%s", path);
E 24

D 17
	/* catch ^C. */
E 17
	(void)signal(SIGINT, done);
I 17
	(void)signal(SIGHUP, done);
E 17

D 17
	/* print greeting. */
E 17
I 17
	/* print greeting */
E 17
D 19
	if ((login = getlogin()) == NULL)
D 17
		if (pwd = getpwuid(getuid()))
E 17
I 17
		if (pwd = getpwuid(myuid))
E 17
			login = pwd->pw_name;
		else
			login = "???";
E 19
	if (gethostname(host, sizeof(host)) < 0)
		(void)strcpy(host, "???");
	now = time((time_t *)NULL);
	nows = ctime(&now);
	nows[16] = '\0';
	(void)printf("\r\n\007\007\007Message from %s@%s on %s at %s ...\r\n",
D 17
	    login, host, mytty, nows  + 11);
E 17
I 17
	    login, host, mytty, nows + 11);
E 17

	while (fgets(line, sizeof(line), stdin) != NULL)
D 17
		massage_fputs(line);
E 17
I 17
		wr_fputs(line);
E 17
E 16
}

D 16
ex(bp)
D 5
char *bp;
E 5
I 5
	char *bp;
E 16
I 16
/*
 * done - cleanup and exit
 */
void
done()
E 16
E 5
{
D 16
	register i;

	sigs(SIG_IGN);
	i = fork();
D 5
	if(i < 0) {
E 5
I 5
	if (i < 0) {
E 5
		printf("Try again\n");
		goto out;
	}
D 5
	if(i == 0) {
E 5
I 5
	if (i == 0) {
I 13
		fclose(tf);		/* Close his terminal */
		setgid(getgid());	/* Give up effective group privs */
E 13
E 5
		sigs((int (*)())0);
D 5
		execl(getenv("SHELL") ? getenv("SHELL") : "/bin/sh", "sh", "-c", bp+1, 0);
E 5
I 5
		execl(getenv("SHELL") ?
D 14
		    getenv("SHELL") : "/bin/sh", "sh", "-c", bp+1, 0);
E 14
I 14
		    getenv("SHELL") : _PATH_BSHELL, "sh", "-c", bp+1, 0);
E 14
E 5
		exit(0);
	}
D 5
	while(wait((int *)NULL) != i)
E 5
I 5
	while (wait((int *)NULL) != i)
E 5
		;
	printf("!\n");
out:
	sigs(eof);
E 16
I 16
	(void)printf("EOF\r\n");
	exit(0);
E 16
}

D 16
sigs(sig)
D 5
int (*sig)();
E 5
I 5
	int (*sig)();
E 16
I 16
/*
D 17
 * massage_fputs - like fputs(), but makes control characters visible and
E 17
I 17
 * wr_fputs - like fputs(), but makes control characters visible and
E 17
 *     turns \n into \r\n
 */
D 17
massage_fputs(s)
E 17
I 17
wr_fputs(s)
E 17
	register char *s;
E 16
E 5
{
D 16
	register i;
E 16
I 16
	register char c;
E 16

D 5
	for(i=0;signum[i];i++)
		signal(signum[i],sig);
E 5
I 5
D 16
	for (i=0; signum[i]; i++)
		signal(signum[i], sig);
E 16
I 16
#define	PUTC(c)	if (putchar(c) == EOF) goto err;

	for (; *s != '\0'; ++s) {
		c = toascii(*s);
		if (c == '\n') {
			PUTC('\r');
			PUTC('\n');
		} else if (!isprint(c) && !isspace(c) && c != '\007') {
			PUTC('^');
			PUTC(c^0x40);	/* DEL to ?, others to alpha */
		} else
			PUTC(c);
	}
	return;

D 24
err:	(void)fprintf(stderr, "write: %s\n", strerror(errno));
	exit(1);
E 24
I 24
err:	err(1, NULL);
E 24
#undef PUTC
E 16
E 5
}
E 1
