h14124
s 00002/00002/00371
d D 8.3 94/04/02 10:09:48 pendry 41 40
c add 1994 copyright
e
s 00055/00068/00318
d D 8.2 94/04/02 08:23:15 pendry 40 39
c prettyness police
e
s 00005/00005/00381
d D 8.1 93/06/06 16:27:35 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00048/00043/00338
d D 5.26 91/07/06 14:08:07 karels 38 37
c only check wheel group if not kerberos; use stderr for errs;
c try to fix up error msgs; other kerberos cleanups
e
s 00002/00002/00379
d D 5.25 91/05/29 11:16:06 bostic 37 36
c use the default path from <paths.h>
e
s 00001/00001/00380
d D 5.24 91/03/01 18:39:34 bostic 36 35
c ANSI
e
s 00007/00025/00374
d D 5.23 90/11/06 10:14:52 karels 35 34
c back out part of last change: check current uid against login name
c (in case already su'ed)
e
s 00058/00024/00341
d D 5.22 90/08/25 10:24:42 karels 34 33
c sanitize syslog msgs, priorities; longer ticket lifetime;
c use new getlogin() (probably will log stuff from cron)
e
s 00034/00030/00331
d D 5.21 90/06/20 19:53:49 kfall 33 32
c fix non-root Kerberos su; add more info in syslog (su-ee plus su-er)
e
s 00001/00011/00360
d D 5.20 90/06/01 17:42:47 bostic 32 31
c new copyright notice
e
s 00014/00012/00357
d D 5.19 90/05/31 09:45:31 bostic 31 30
c make -l, -m mutually exclusive, rename -n as -K for consistency with
c rlogin and rsh; clean up the man page
e
s 00001/00000/00368
d D 5.18 90/05/18 08:44:25 bostic 30 29
c krb.h needs des.h
e
s 00001/00001/00367
d D 5.17 90/04/03 18:42:06 bostic 29 28
c Kerberos include files are in a subdirectory now
e
s 00017/00007/00351
d D 5.16 90/01/04 11:04:21 bostic 28 27
c ttyname may return a NULL
e
s 00147/00160/00211
d D 5.15 89/10/17 18:51:09 bostic 27 26
c break kerberos routine out, format changes, lint fixes
e
s 00160/00002/00211
d D 5.14 89/10/12 18:06:30 kfall 26 25
c add Kerberos to su, add -n flag to not use Kerb.
e
s 00007/00004/00206
d D 5.13 89/08/22 15:00:45 bostic 25 24
c use openlog so message get tagged correctly
e
s 00004/00003/00206
d D 5.12 89/03/05 21:53:10 bostic 24 23
c add pathnames.h
e
s 00013/00008/00196
d D 5.11 88/12/07 12:51:40 bostic 23 22
c change so that -m fails if non-standard shell and not root, rather
c than just running the non-standard shell
e
s 00001/00001/00203
d D 5.10 88/10/18 19:03:06 bostic 22 21
c forgot -m flag in usage statement
e
s 00013/00002/00191
d D 5.9 88/09/26 17:47:41 bostic 21 20
c use getusershell(3) instead of missing password as security flag
e
s 00049/00035/00144
d D 5.8 88/09/26 17:11:05 bostic 20 19
c add -m flag; completely redo the manual page.  Now 3 behaviors, default,
c which is the old hybrid, -m, which is "as me", i.e., don't change anything, and
c -l for the full login.
e
s 00053/00034/00126
d D 5.7 88/09/26 10:02:48 bostic 19 18
c preserve environment and use user's shell by default
e
s 00111/00138/00049
d D 5.6 88/09/13 10:55:13 bostic 18 17
c preserve priority; always exit 1 on error; use library versions of
c getenv(3), setenv(3); use getopt(3), add -l flag instead of ``-'';
c general cleanup, particularly in how environment handled; add Berkeley
c header, this contains no 32v code.
e
s 00001/00001/00186
d D 5.5 87/01/18 20:47:01 karels 17 16
c init USER on "su - root"
e
s 00005/00002/00182
d D 5.4 86/01/13 15:18:50 lepreau 16 15
c when logging, use pwuid->pw_name if getlogin() fails (ptys)
e
s 00004/00004/00180
d D 5.3 85/09/17 23:59:05 eric 15 14
c facilities in syslog
e
s 00002/00005/00182
d D 5.2 85/06/07 13:37:16 serge 14 13
c use syslog instead of writing to the console
e
s 00014/00002/00173
d D 5.1 85/05/02 14:48:51 dist 13 12
c 
e
s 00004/00006/00171
d D 4.10 85/03/12 11:15:13 ralph 12 11
c use syslog to log root su's.
e
s 00016/00014/00161
d D 4.9 84/03/22 11:17:59 ralph 11 9
c check group zero for any uid==0 (i.e., toor).
e
s 00011/00009/00166
d R 4.9 84/03/22 09:35:04 ralph 10 9
c check group zero for any uid==0 (i.e. toor).
e
s 00009/00011/00166
d D 4.8 84/02/01 11:26:30 ralph 9 8
c use group zero instead of /.suok
e
s 00026/00001/00151
d D 4.7 84/01/26 14:01:38 ralph 8 7
c added .suok file for list of users allowed to su root.
e
s 00002/00001/00150
d D 4.6 83/07/06 18:17:37 sam 7 6
c don't set USER, breaks sccs
e
s 00075/00034/00076
d D 4.5 83/05/23 18:36:36 sam 6 4
c cleanup after dlw; purge nice calls
e
s 00071/00033/00077
d R 4.5 83/05/23 01:18:45 sam 5 4
c mods from dlw
e
s 00028/00023/00082
d D 4.4 83/01/01 13:18:38 sam 4 3
c rewrite to use rename and file locking 
e
s 00001/00001/00104
d D 4.3 82/11/14 16:34:07 sam 3 2
c convert to 4.1c sys calls and directory layout
e
s 00002/00001/00103
d D 4.2 82/03/01 00:15:06 wnj 2 1
c group initialization
e
s 00104/00000/00000
d D 4.1 80/10/01 17:28:42 bill 1 0
c date and time created 80/10/01 17:28:42 by bill
e
u
U
t
T
I 13
/*
D 18
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 18
I 18
D 39
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 39
I 39
D 41
 * Copyright (c) 1988, 1993
E 41
I 41
 * Copyright (c) 1988, 1993, 1994
E 41
 *	The Regents of the University of California.  All rights reserved.
E 39
 *
D 32
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
D 25
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 25
I 25
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 32
I 32
 * %sccs.include.redist.c%
E 32
E 25
E 18
 */

E 13
I 4
#ifndef lint
E 4
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 6
static char *sccsid = "%W% (Berkeley) %I%";
E 6
I 6
D 13
static char *sccsid = "%W% (Berkeley) %G%";
E 6
I 4
#endif
E 13
I 13
D 39
char copyright[] =
D 18
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 18
I 18
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
E 18
 All rights reserved.\n";
E 39
I 39
static char copyright[] =
D 41
"%Z% Copyright (c) 1988, 1993\n\
E 41
I 41
"%Z% Copyright (c) 1988, 1993, 1994\n\
E 41
	The Regents of the University of California.  All rights reserved.\n";
E 39
D 18
#endif not lint
E 18
I 18
#endif /* not lint */
E 18

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 18
#endif not lint
E 18
I 18
#endif /* not lint */
E 18
E 13

E 4
E 2
D 18
#include <stdio.h>
#include <pwd.h>
I 9
#include <grp.h>
I 12
#include <syslog.h>
E 18
E 12
E 9
I 6
D 19
#include <sys/types.h>
E 19
I 19
#include <sys/param.h>
E 19
#include <sys/time.h>
#include <sys/resource.h>
I 18
D 40
#include <syslog.h>
#include <stdio.h>
#include <pwd.h>
E 40
I 40

#include <err.h>
#include <errno.h>
E 40
#include <grp.h>
I 40
#include <paths.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
E 40
I 27
#include <string.h>
I 40
#include <syslog.h>
E 40
I 28
#include <unistd.h>
E 28
E 27
I 24
D 37
#include "pathnames.h"
E 37
I 37
D 40
#include <paths.h>
E 40
E 37
E 24
E 18
E 6

I 26
D 27
#ifdef	KERBEROS
#include <krb.h>	
E 27
I 27
#ifdef KERBEROS
I 30
#include <kerberosIV/des.h>
E 30
D 29
#include <krb.h>
E 29
I 29
#include <kerberosIV/krb.h>
E 29
E 27
#include <netdb.h>
D 27
extern	char	*krb_err_txt[];
int	use_kerberos = 1;
int	kerno = 0;
char	lrealm[REALM_SZ], krbtkfile[MAXPATHLEN];
#define	MAXPWSIZE	128
E 27
I 27

E 27
D 31
#define	ARGSTR	"-flmn"
E 31
I 31
#define	ARGSTR	"-Kflm"
E 31
D 27
char	pw_buf[MAXPWSIZE];
E 27
I 27

int use_kerberos = 1;
E 27
#else
#define	ARGSTR	"-flm"
#endif

I 40
char   *ontty __P((void));
int	chshell __P((char *));

int
E 40
E 26
I 6
D 18
char	userbuf[16]	= "USER=";
char	homebuf[128]	= "HOME=";
char	shellbuf[128]	= "SHELL=";
char	pathbuf[128]	= "PATH=:/usr/ucb:/bin:/usr/bin";
char	*cleanenv[] = { userbuf, homebuf, shellbuf, pathbuf, 0, 0 };
char	*user = "root";
char	*shell = "/bin/sh";
int	fulllogin;
int	fastlogin;

extern char	**environ;
E 6
D 9
struct	passwd *pwd,*getpwnam();
E 9
I 9
struct	passwd *pwd;
E 9
char	*crypt();
char	*getpass();
I 6
char	*getenv();
I 16
char	*getlogin();
E 16
E 6

main(argc,argv)
E 18
I 18
main(argc, argv)
E 18
D 4
int	argc;
char	**argv;
E 4
I 4
	int argc;
D 6
	char **argv;
E 6
I 6
D 18
	char *argv[];
E 18
I 18
	char **argv;
E 18
E 6
E 4
{
D 4
	char *nptr;
E 4
I 4
D 6
	char *nptr = "root";
E 6
E 4
D 18
	char *password;
I 8
	char buf[1000];
	FILE *fp;
I 16
	register char *p;
E 18
I 18
	extern char **environ;
D 40
	extern int errno, optind;
D 19
	char *cleanenv[2];
E 19
	register struct passwd *pwd;
	register char *p, **g;
E 40
I 40
	struct passwd *pwd;
	char *p, **g, *user, *shell, *username, *cleanenv[2], *nargv[4], **np;
E 40
	struct group *gr;
I 19
D 40
	uid_t ruid, getuid();
E 40
I 40
	uid_t ruid;
E 40
E 19
D 20
	int ch, fulllogin, fastlogin, prio;
E 20
I 20
D 31
	int asme, ch, fulllogin, fastlogin, prio;
E 31
I 31
	int asme, ch, asthem, fastlogin, prio;
E 31
E 20
D 19
	char *user, *shell, *username, nbuf[50];
	char *crypt(), *getpass(), *getenv(), *getlogin(), *strcpy();
E 19
I 19
	enum { UNSET, YES, NO } iscsh = UNSET;
D 20
	char *user, *shell, *username, *cleanenv[2];
E 20
I 20
D 40
	char *user, *shell, *username, *cleanenv[2], *nargv[4], **np;
E 40
E 20
D 27
	char namebuf[50], shellbuf[MAXPATHLEN];
	char *crypt(), *getpass(), *getenv(), *getlogin(), *rindex(), *strcpy();
E 27
I 27
	char shellbuf[MAXPATHLEN];
D 28
	char *crypt(), *getpass(), *getenv(), *getlogin();
E 28
I 28
D 34
	char *crypt(), *getpass(), *getenv(), *getlogin(), *mytty();
E 34
I 34
D 40
	char *crypt(), *getpass(), *getenv(), *getlogin(), *ontty();
E 40
E 34
E 28
E 27
E 19
E 18
E 16
E 8
D 4
	int badsw = 0;
E 4
D 6
	char *shell = "/bin/sh";
E 6
D 4
	int niced = 0;
E 4

I 15
D 18
	openlog("su", LOG_ODELAY, LOG_AUTH);
E 18
I 18
D 19
	user = "root";
	shell = "/bin/sh";
E 19
D 20
	fulllogin = fastlogin = 0;
E 18
D 19

E 19
E 15
D 4
	if(argc > 1)
E 4
I 4
D 6
	if (argc > 1)
E 4
		nptr = argv[1];
D 4
	else {
		nptr = "root";
		nice(-4);
		niced = -4;
	}
	if((pwd=getpwnam(nptr)) == NULL) {
E 4
I 4
	if ((pwd = getpwnam(nptr)) == NULL) {
E 4
		printf("Unknown id: %s\n",nptr);
E 6
I 6
D 18
again:
	if (argc > 1 && strcmp(argv[1], "-f") == 0) {
		fastlogin++;
		argc--, argv++;
		goto again;
	}
	if (argc > 1 && strcmp(argv[1], "-") == 0) {
		fulllogin++;
		argc--, argv++;
		goto again;
	}
	if (argc > 1 && argv[1][0] != '-') {
		user = argv[1];
		argc--, argv++;
	}
E 18
I 18
	while ((ch = getopt(argc, argv, "-fl")) != EOF)
E 20
I 20
	np = &nargv[3];
	*np-- = NULL;
D 31
	asme = fulllogin = fastlogin = 0;
E 31
I 31
	asme = asthem = fastlogin = 0;
E 31
D 26
	while ((ch = getopt(argc, argv, "-flm")) != EOF)
E 26
I 26
	while ((ch = getopt(argc, argv, ARGSTR)) != EOF)
E 26
E 20
		switch((char)ch) {
I 31
#ifdef KERBEROS
		case 'K':
			use_kerberos = 0;
			break;
#endif
E 31
I 19
		case 'f':
			fastlogin = 1;
			break;
E 19
		case '-':
		case 'l':
D 31
			fulllogin = 1;
E 31
I 31
			asme = 0;
			asthem = 1;
E 31
			break;
I 20
		case 'm':
			asme = 1;
I 31
			asthem = 0;
E 31
			break;
I 26
D 27
#ifdef	KERBEROS
E 27
I 27
D 31
#ifdef KERBEROS
E 27
		case 'n':
			use_kerberos = 0;
			break;
#endif
E 31
E 26
E 20
D 19
		case 'f':
			fastlogin = 1;
			break;
E 19
		case '?':
		default:
D 22
			fprintf(stderr, "usage: su [-fl] [login]\n");
E 22
I 22
D 27
			fprintf(stderr, "usage: su [-flm] [login]\n");
E 27
I 27
			(void)fprintf(stderr, "usage: su [%s] [login]\n",
			    ARGSTR);
E 27
E 22
			exit(1);
		}
	argv += optind;

I 20
	errno = 0;
	prio = getpriority(PRIO_PROCESS, 0);
	if (errno)
		prio = 0;
	(void)setpriority(PRIO_PROCESS, 0, -2);
I 34
	openlog("su", LOG_CONS, 0);
E 34

D 34
	/* get current login name and shell */
E 20
E 18
D 8
	if (strcmp(user, "root") == 0)
E 8
I 8
D 11
	if (strcmp(user, "root") == 0) {
E 11
I 11
D 19
	if ((pwd = getpwuid(getuid())) == NULL) {
E 19
I 19
	if ((pwd = getpwuid(ruid = getuid())) == NULL) {
E 19
D 18
		fprintf(stderr, "Who are you?\n");
E 18
I 18
		fprintf(stderr, "su: who are you?\n");
E 18
		exit(1);
E 34
I 34
D 35
	/*
	 * Get current login name and shell.
	 * This code assumes the trustable (system call)
	 * version of getlogin (the old one was easily confused).
	 */
E 35
I 35
	/* get current login name and shell */
E 35
	ruid = getuid();
	username = getlogin();
D 35
	if (username == NULL || (pwd = getpwnam(username)) == NULL) {
		if (username)
			syslog(LOG_AUTH|LOG_ERR,
			    "su attempt by unknown user %s (uid %d) to %s%s",
			    username, ruid, user, ontty());
#ifdef notyet
		/*
		 * The following will happen regularly from cron, etc.
		 * unless such things do a setlogin().
		 */
		else
			syslog(LOG_AUTH|LOG_ERR,
			    "su attempt with null login name (uid %d) to %s%s",
			    ruid, user, ontty());
#endif
E 35
I 35
	if (username == NULL || (pwd = getpwnam(username)) == NULL ||
	    pwd->pw_uid != ruid)
E 35
		pwd = getpwuid(ruid);
D 35
		if (pwd == NULL) {
			fprintf(stderr, "su: who are you?\n");
			exit(1);
		}
		username = strdup(pwd->pw_name);
E 35
I 35
D 40
	if (pwd == NULL) {
		fprintf(stderr, "su: who are you?\n");
		exit(1);
E 35
E 34
	}
E 40
I 40
	if (pwd == NULL)
		errx(1, "who are you?");
E 40
I 35
	username = strdup(pwd->pw_name);
I 40
	if (username == NULL)
		err(1, NULL);
E 40
E 35
D 18
	strcpy(buf, pwd->pw_name);
E 18
I 18
D 19
	username = strcpy(nbuf, pwd->pw_name);
E 19
I 19
D 27
	username = strcpy(namebuf, pwd->pw_name);
E 27
I 27
D 34
	username = strdup(pwd->pw_name);
E 34
E 27
D 20
	if (!fulllogin)
E 20
I 20
	if (asme)
E 20
		if (pwd->pw_shell && *pwd->pw_shell)
			shell = strcpy(shellbuf,  pwd->pw_shell);
		else {
D 24
			shell = "/bin/sh";
E 24
I 24
			shell = _PATH_BSHELL;
E 24
			iscsh = NO;
		}
E 19

D 19
	if (*argv)
		user = *argv++;
E 19
I 19
D 20
	user = *argv ? *argv++ : "root";
E 20
I 20
D 26
	/* get target login information */
E 26
I 26
	/* get target login information, default to root */
E 26
	user = *argv ? *argv : "root";
E 20
E 19
E 18
	if ((pwd = getpwnam(user)) == NULL) {
D 18
		fprintf(stderr, "Unknown login: %s\n", user);
E 18
I 18
		fprintf(stderr, "su: unknown login %s\n", user);
E 18
		exit(1);
	}
D 18
	/*
	 * Only allow those in group zero to su to root.
	 */
	if (pwd->pw_uid == 0) {
E 11
I 9
		struct	group *gr;
		int i;
E 18

E 9
D 11
		/*
D 9
		 * Read the "/.suok" file for list of people who can su.
E 9
I 9
		 * Only allow those in group zero to su.
E 9
		 */
		if ((pwd = getpwuid(getuid())) == NULL) {
			fprintf(stderr, "Who are you?\n");
			exit(1);
		}
E 11
D 9
		if ((fp = fopen("/.suok", "r")) != NULL) {
			while ((fgets(buf, sizeof(buf), fp)) != NULL) {
				/* blast newline */
				buf[strlen(buf) - 1] = '\0';
				if (strcmp(pwd->pw_name, buf) == 0) {
					fclose(fp);
E 9
I 9
D 18
		if ((gr = getgrgid(0)) != NULL) {
			for (i = 0; gr->gr_mem[i] != NULL; i++)
D 11
				if (strcmp(pwd->pw_name, gr->gr_mem[i]) == 0)
E 11
I 11
				if (strcmp(buf, gr->gr_mem[i]) == 0)
E 11
E 9
					goto userok;
D 9
				}
			}
			fclose(fp);
E 9
D 11
			fprintf(stderr, "You do not have permission to su root\n");
E 11
I 11
			fprintf(stderr, "You do not have permission to su %s\n",
				user);
E 11
			exit(1);
E 18
I 18
D 38
	/* only allow those in group zero to su to root. */
D 19
	if (pwd->pw_uid == 0 && (gr = getgrgid(0)))
E 19
I 19
	if (pwd->pw_uid == 0 && (gr = getgrgid((gid_t)0)))
E 19
		for (g = gr->gr_mem;; ++g) {
			if (!*g) {
D 25
				fprintf(stderr, "su: you are not in the correct group to su %s.\n", user);
E 25
I 25
				(void)fprintf(stderr,
				    "su: you are not in the correct group to su %s.\n", user);
E 25
				exit(1);
			}
			if (!strcmp(username, *g))
				break;
E 18
		}
I 25
D 34
	openlog("su", LOG_CONS, 0);
E 34
E 25
D 18
	userok:
E 8
		setpriority(PRIO_PROCESS, 0, -2);
I 8
	}
E 18

E 38
I 26
D 27
#ifdef	KERBEROS
again:
	if (use_kerberos && ruid) {
		KTEXT_ST	ticket;
		AUTH_DAT	authdata;
		char		hostname[MAXHOSTNAMELEN];
		char		savehost[MAXHOSTNAMELEN];
		u_long		faddr;
		struct hostent	*hp;

		if (krb_get_lrealm(lrealm, 1) != KSUCCESS) {
			(void)fprintf(stderr, "Couldn't get local realm\n");
			use_kerberos = 0;
			goto again;
		}

		if (koktologin(username, lrealm, user) && !pwd->pw_uid) {
			(void)fprintf(stderr,
				"kerberos su: not in %s's ACL\n", user);
			use_kerberos = 0;
			goto again;
		}

		(void)sprintf(krbtkfile, "%s_%s_%d", TKT_ROOT, user, getuid());
		/* setuid(pwd->pw_uid); */

		if (read_pw_string(pw_buf, sizeof(pw_buf)-1,
		   "Kerberos password: ", 0)) {
			(void)fprintf(stderr, "error reading password\n");
			use_kerberos = 0;
			goto again;
		}

		p = pw_buf;
		setenv("KRBTKFILE", krbtkfile, 1);
		/* short lifetime for root tickets */
		if (setuid(0) < 0) {
			perror("setuid");
			use_kerberos = 0;
			goto again;
		}
		(void)unlink(krbtkfile);
		/* POLICY: short ticket lifetime for root */
		kerno = krb_get_pw_in_tkt(username,
			(pwd->pw_uid == 0 ? "root" : ""),
			lrealm, "krbtgt", lrealm,
			(pwd->pw_uid == 0 ? 2 : DEFAULT_TKT_LIFE),
			p);

		(void)bzero(p, strlen(p));
		if (kerno != KSUCCESS) {
			if (kerno == KDC_PR_UNKNOWN) {
				use_kerberos = 0;
				goto again;
E 27
I 27
	if (ruid) {
#ifdef KERBEROS
D 38
		if (!use_kerberos || kerberos(username, user, pwd->pw_uid))
E 38
I 38
	    if (!use_kerberos || kerberos(username, user, pwd->pw_uid))
E 38
#endif
I 38
	    {
		/* only allow those in group zero to su to root. */
		if (pwd->pw_uid == 0 && (gr = getgrgid((gid_t)0)))
			for (g = gr->gr_mem;; ++g) {
D 40
				if (!*g) {
					(void)fprintf(stderr,
			    "su: you are not in the correct group to su %s.\n",
E 40
I 40
				if (!*g)
					errx(1,
			    "you are not in the correct group to su %s.",
E 40
					    user);
D 40
					exit(1);
				}
				if (!strcmp(username, *g))
E 40
I 40
				if (strcmp(username, *g) == 0)
E 40
					break;
		}
E 38
		/* if target requires a password, verify it */
		if (*pwd->pw_passwd) {
			p = getpass("Password:");
			if (strcmp(pwd->pw_passwd, crypt(p, pwd->pw_passwd))) {
				fprintf(stderr, "Sorry\n");
D 33
				if (pwd->pw_uid == 0)
					syslog(LOG_AUTH|LOG_CRIT,
					    "BAD SU %s on %s", username,
D 28
					    ttyname(2));
E 28
I 28
					    mytty());
E 33
I 33
D 34
				syslog(LOG_AUTH|LOG_CRIT,
					"BAD SU %s on %s to %s", username,
					mytty(), user);
E 34
I 34
				syslog(LOG_AUTH|LOG_WARNING,
					"BAD SU %s to %s%s", username,
					user, ontty());
E 34
E 33
E 28
				exit(1);
E 27
			}
D 27
			printf("su: unable to su: %s\n",
				krb_err_txt[kerno]);
			syslog(LOG_NOTICE|LOG_AUTH,
				"su: BAD Kerberos SU: %s on %s: %s",
					username, ttyname(2), krb_err_txt[kerno]);
			use_kerberos = 0;
			goto again;
		} else if (chown(krbtkfile, pwd->pw_uid, -1) < 0) {
				perror("su: chown:");
				(void)unlink(krbtkfile);
				use_kerberos = 0;
				goto again;
E 27
		}
I 38
	    }
E 38
D 27

		setpriority(PRIO_PROCESS, 0, -2);

		if (gethostname(hostname, sizeof(hostname)) == -1) {
			fprintf(stderr, "couldn't get local hostname\n");
			dest_tkt();
			use_kerberos = 0;
			goto again;
		}

		(void) strncpy(savehost, krb_get_phost(hostname),
			sizeof(savehost));
		savehost[sizeof(savehost)-1] = 0;

		kerno = krb_mk_req(&ticket, "rcmd", savehost, lrealm, 33);

		if (kerno == KDC_PR_UNKNOWN) {
			printf("Warning: tgt not verified\n");
			syslog(LOG_NOTICE|LOG_AUTH,
				"su: %s on %s, tgt not verified",
				username, ttyname(2));
		} else if (kerno != KSUCCESS) {
			printf("Unable to use tgt: %s\n", krb_err_txt[kerno]);
			syslog(LOG_NOTICE|LOG_AUTH,
				"su: failed su: %s on %s: %s",
				username, ttyname(2), krb_err_txt[kerno]);
			dest_tkt();
			use_kerberos = 0;
			goto again;
		} else {
			if (!(hp = gethostbyname(hostname))) {
				printf("can't get addr of %s\n", hostname);
				dest_tkt();
				use_kerberos = 0;
				goto again;
			}
			(void) bcopy((char *)hp->h_addr, (char *) &faddr,
				sizeof(faddr));

			if ((kerno = krb_rd_req(&ticket, "rcmd", savehost,
				faddr, &authdata, "")) != KSUCCESS) {
				printf("unable to verify rcmd ticket: %s\n",
					krb_err_txt[kerno]);
				syslog(LOG_NOTICE|LOG_AUTH,
					"su: failed su: %s on %s: %s",
					    username, ttyname(2), krb_err_txt[kerno]);
				dest_tkt();
				use_kerberos = 0;
				goto again;
			}
		}

	} else
#endif

E 26
I 16
D 18
#define Getlogin()  (((p = getlogin()) && *p) ? p : buf)
E 16
E 8
D 11
	if ((pwd = getpwnam(user)) == NULL) {
		fprintf(stderr, "Unknown login: %s\n", user);
E 6
		exit(1);
	}
E 11
D 4
	if(pwd->pw_passwd[0] == '\0' || getuid() == 0)
E 4
I 4
	if (pwd->pw_passwd[0] == '\0' || getuid() == 0)
E 4
		goto ok;
	password = getpass("Password:");
D 4
	if(badsw || (strcmp(pwd->pw_passwd, crypt(password, pwd->pw_passwd)) != 0)) {
bad:
E 4
I 4
	if (strcmp(pwd->pw_passwd, crypt(password, pwd->pw_passwd)) != 0) {
E 4
D 6
		printf("Sorry\n");
E 6
I 6
		fprintf(stderr, "Sorry\n");
E 6
D 4
		if(pwd->pw_uid == 0) {
E 4
I 4
		if (pwd->pw_uid == 0) {
E 4
D 14
			FILE *console = fopen("/dev/console", "w");
			if (console != NULL) {
D 4
				fprintf(console, "BADSU: %s %s\r\n", getlogin(), ttyname(2));
E 4
I 4
				fprintf(console, "BADSU: %s %s\r\n",
E 14
I 14
D 15
			openlog("su", 0, 0);
			syslog(LOG_SECURITY, "BAD SU %s on %s",
E 15
I 15
			syslog(LOG_CRIT, "BAD SU %s on %s",
E 15
E 14
D 16
					getlogin(), ttyname(2));
E 16
I 16
					Getlogin(), ttyname(2));
E 18
I 18
D 19
	openlog("su", LOG_ODELAY, LOG_AUTH);

E 19
D 20
	errno = 0;
	prio = getpriority(PRIO_PROCESS, 0);
	if (errno)
		prio = 0;
	(void)setpriority(PRIO_PROCESS, 0, -2);

	if ((p = getlogin()) && *p)
		username = p;

D 19
	if (pwd->pw_passwd[0] && getuid()) {
E 19
I 19
	if (*pwd->pw_passwd && ruid) {
E 20
I 20
	/* if target requires a password, verify it */
	if (ruid && *pwd->pw_passwd) {
E 20
E 19
		p = getpass("Password:");
		if (strcmp(pwd->pw_passwd, crypt(p, pwd->pw_passwd))) {
			fprintf(stderr, "Sorry\n");
			if (pwd->pw_uid == 0)
D 19
				syslog(LOG_CRIT, "BAD SU %s on %s",
					username, ttyname(2));
E 19
I 19
D 20
				syslog(LOG_CRIT|LOG_AUTH, "su: BAD SU %s on %s",
				    username, ttyname(2));
E 20
I 20
D 25
				syslog(LOG_CRIT|LOG_AUTH, "su: BAD SU %s on %s", username, ttyname(2));
E 25
I 25
				syslog(LOG_AUTH|LOG_CRIT,
				    "BAD SU %s on %s", username, ttyname(2));
E 25
E 20
E 19
			exit(1);
E 18
E 16
E 4
D 14
				fclose(console);
			}
E 14
		}
E 27
D 18
		exit(2);
E 18
	}
I 19

D 20
	/* if target user has no password, or fulllogin, use their shell */
	if (!*pwd->pw_passwd || fulllogin)
E 20
I 20
D 21
	/* if not asme or target has no password, use their shell */
	if (!asme || !*pwd->pw_passwd)
E 21
I 21
D 23
	/* if not asme or target's shell isn't standard, use it */
	if (!asme || !chshell(pwd->pw_shell))
E 21
E 20
		if (pwd->pw_shell && *pwd->pw_shell) {
			shell = pwd->pw_shell;
			iscsh = UNSET;
		} else {
			shell = "/bin/sh";
			iscsh = NO;
E 23
I 23
	if (asme) {
		/* if asme and non-standard target shell, must be root */
D 40
		if (!chshell(pwd->pw_shell) && ruid) {
D 27
			fprintf(stderr, "su: Permission denied.\n");
E 27
I 27
D 33
			(void)fprintf(stderr, "su: permission denied.\n");
E 33
I 33
			(void)fprintf(stderr,
				"su: permission denied (shell).\n");
E 33
E 27
			exit(1);
E 23
		}
E 40
I 40
		if (!chshell(pwd->pw_shell) && ruid)
			errx(1, "permission denied (shell).");
E 40
I 23
D 27
	}
	else if (pwd->pw_shell && *pwd->pw_shell) {
E 27
I 27
	} else if (pwd->pw_shell && *pwd->pw_shell) {
E 27
		shell = pwd->pw_shell;
		iscsh = UNSET;
	} else {
D 24
		shell = "/bin/sh";
E 24
I 24
		shell = _PATH_BSHELL;
E 24
		iscsh = NO;
	}
E 23

I 20
	/* if we're forking a csh, we want to slightly muck the args */
E 20
	if (iscsh == UNSET) {
D 40
		if (p = rindex(shell, '/'))
E 40
I 40
		if (p = strrchr(shell, '/'))
E 40
			++p;
		else
			p = shell;
		iscsh = strcmp(p, "csh") ? NO : YES;
	}

I 20
	/* set permissions */
E 20
E 19
D 18
ok:
	endpwent();
D 4
	if(pwd->pw_uid == 0) {
E 4
I 4
	if (pwd->pw_uid == 0) {
E 4
D 12
		FILE *console = fopen("/dev/console", "w");
		if (console != NULL) {
D 4
			fprintf(console, "SU: %s %s\r\n", getlogin(), ttyname(2));
E 4
I 4
			fprintf(console, "SU: %s %s\r\n",
				getlogin(), ttyname(2));
E 4
			fclose(console);
		}
E 12
I 12
D 15
		openlog("su", 0, 0);
		syslog(LOG_SECURITY, "%s on %s", getlogin(), ttyname(2));
E 15
I 15
D 16
		syslog(LOG_NOTICE, "%s on %s", getlogin(), ttyname(2));
E 16
I 16
		syslog(LOG_NOTICE, "%s on %s", Getlogin(), ttyname(2));
E 16
E 15
		closelog();
E 12
	}
E 18
D 4
	setgid(pwd->pw_gid);
I 2
D 3
	inigrp(nptr, pwd->pw_gid);
E 3
I 3
	initgroups(nptr, pwd->pw_gid);
E 3
E 2
	setuid(pwd->pw_uid);
E 4
I 4
D 40
	if (setgid(pwd->pw_gid) < 0) {
		perror("su: setgid");
D 18
		exit(3);
E 18
I 18
		exit(1);
E 18
	}
D 6
	if (initgroups(nptr, pwd->pw_gid)) {
E 6
I 6
	if (initgroups(user, pwd->pw_gid)) {
E 6
D 27
		fprintf(stderr, "su: initgroups failed\n");
E 27
I 27
		(void)fprintf(stderr, "su: initgroups failed.\n");
E 27
D 18
		exit(4);
E 18
I 18
		exit(1);
E 18
	}
	if (setuid(pwd->pw_uid) < 0) {
		perror("su: setuid");
D 18
		exit(5);
E 18
I 18
		exit(1);
E 18
	}
E 40
I 40
	if (setgid(pwd->pw_gid) < 0)
		err(1, "setgid");
	if (initgroups(user, pwd->pw_gid))
		errx(1, "initgroups failed");
	if (setuid(pwd->pw_uid) < 0)
		err(1, "setuid");
E 40
E 4
D 19
	if (pwd->pw_shell && *pwd->pw_shell)
		shell = pwd->pw_shell;
I 18

E 19
E 18
D 6
	homeis(pwd->pw_dir);
	shellis(shell);
D 4
	nice(-niced);
E 4
	execl(shell, "su", 0);
	printf("No shell\n");
	exit(3);
E 6
I 6
D 20
	if (fulllogin) {
D 18
		cleanenv[4] = getenv("TERM");
E 18
I 18
		p = getenv("TERM");
		cleanenv[0] = "PATH=:/usr/ucb:/bin:/usr/bin";
		cleanenv[1] = NULL;
E 18
		environ = cleanenv;
E 20
I 20

	if (!asme) {
D 31
		if (fulllogin) {
E 31
I 31
		if (asthem) {
E 31
			p = getenv("TERM");
D 24
			cleanenv[0] = "PATH=:/usr/ucb:/bin:/usr/bin";
E 24
I 24
D 37
			cleanenv[0] = _PATH_SEARCHPATH;
E 37
I 37
			cleanenv[0] = _PATH_DEFPATH;
E 37
E 24
			cleanenv[1] = NULL;
			environ = cleanenv;
			(void)setenv("TERM", p, 1);
D 40
			if (chdir(pwd->pw_dir) < 0) {
				fprintf(stderr, "su: no directory\n");
				exit(1);
			}
E 40
I 40
			if (chdir(pwd->pw_dir) < 0)
				errx(1, "no directory");
E 40
		}
D 31
		if (fulllogin || pwd->pw_uid)
E 31
I 31
		if (asthem || pwd->pw_uid)
E 31
			(void)setenv("USER", pwd->pw_name, 1);
E 20
I 19
		(void)setenv("HOME", pwd->pw_dir, 1);
		(void)setenv("SHELL", shell, 1);
E 19
D 18
	}
D 7
	setenv("USER", pwd->pw_name, userbuf);
E 7
I 7
D 17
	if (strcmp(user, "root"))
E 17
I 17
	if (fulllogin || strcmp(user, "root") != 0)
E 17
		setenv("USER", pwd->pw_name, userbuf);
E 7
	setenv("SHELL", shell, shellbuf);
	setenv("HOME", pwd->pw_dir, homebuf);
	setpriority(PRIO_PROCESS, 0, 0);
	if (fastlogin) {
		*argv-- = "-f";
		*argv = "su";
	} else if (fulllogin) {
E 18
I 18
D 20
		(void)setenv("TERM", p, 1);
I 19
		(void)setenv("USER", pwd->pw_name, 1);
E 19
E 18
		if (chdir(pwd->pw_dir) < 0) {
D 18
			fprintf(stderr, "No directory\n");
			exit(6);
E 18
I 18
			fprintf(stderr, "su: no directory\n");
			exit(1);
E 18
		}
E 20
D 18
		*argv = "-su";
	} else
		*argv = "su";
	execv(shell, argv);
	fprintf(stderr, "No shell\n");
	exit(7);
E 6
}
E 18
I 18
D 19
		(void)setenv("USER", pwd->pw_name, 1);
E 19
	}
D 19
	else if (strcmp(user, "root"))
		(void)setenv("USER", pwd->pw_name, 1);
	(void)setenv("SHELL", shell, 1);
	(void)setenv("HOME", pwd->pw_dir, 1);
E 19
E 18

D 6
char	**environ;

homeis(hp)
	char *hp;
E 6
I 6
D 18
setenv(ename, eval, buf)
	char *ename, *eval, *buf;
E 6
{
	register char *cp, *dp;
	register char **ep = environ;
E 18
I 18
D 19
	--argv;
	if (fastlogin)
		*argv-- = "-f";
	*argv = fulllogin ? "-su" : "su";
E 19
I 19
D 20
	if (fastlogin && iscsh == YES)
		*--argv = "-f";
E 20
I 20
	if (iscsh == YES) {
		if (fastlogin)
			*np-- = "-f";
		if (asme)
			*np-- = "-m";
	}
E 20
E 19
E 18
D 6
	static char homebuf[128];
E 6

I 19
	/* csh strips the first character... */
D 20
	*--argv = fulllogin ? "-su" : iscsh == YES ? "_su" : "su";
E 20
I 20
D 31
	*np = fulllogin ? "-su" : iscsh == YES ? "_su" : "su";
E 31
I 31
	*np = asthem ? "-su" : iscsh == YES ? "_su" : "su";
E 31
E 20

E 19
I 6
D 18
	/*
	 * this assumes an environment variable "ename" already exists
	 */
E 6
	while (dp = *ep++) {
D 6
		for (cp = "HOME"; *cp == *dp && *cp; cp++, dp++)
E 6
I 6
		for (cp = ename; *cp == *dp && *cp; cp++, dp++)
E 6
			continue;
		if (*cp == 0 && (*dp == '=' || *dp == 0)) {
D 6
			strcpy(homebuf, "HOME=");
			strcat(homebuf, hp);
			*--ep = homebuf;
E 6
I 6
			strcat(buf, eval);
			*--ep = buf;
E 6
			return;
		}
	}
}
E 18
I 18
D 33
	if (pwd->pw_uid == 0)
D 19
		syslog(LOG_NOTICE, "%s on %s", username, ttyname(2));
E 19
I 19
D 25
		syslog(LOG_NOTICE|LOG_AUTH, "su: %s on %s",
E 25
I 25
D 27
		syslog(LOG_NOTICE|LOG_AUTH, "%s on %s",
E 25
		    username, ttyname(2));
E 27
I 27
D 28
		syslog(LOG_NOTICE|LOG_AUTH, "%s on %s", username, ttyname(2));
E 28
I 28
		syslog(LOG_NOTICE|LOG_AUTH, "%s on %s", username, mytty());
E 33
I 33
D 34
	syslog(LOG_NOTICE|LOG_AUTH, "%s on %s to %s", username, mytty(), user);
E 34
I 34
	if (ruid != 0)
		syslog(LOG_NOTICE|LOG_AUTH, "%s to %s%s",
		    username, user, ontty());
E 34
E 33
E 28
E 27
E 19
E 18

D 6
shellis(sp)
	char *sp;
E 6
I 6
D 18
char *
getenv(ename)
	char *ename;
E 6
{
	register char *cp, *dp;
	register char **ep = environ;
E 18
I 18
	(void)setpriority(PRIO_PROCESS, 0, prio);
E 18
D 6
	static char shellbuf[128];
E 6

D 18
	while (dp = *ep++) {
D 6
		for (cp = "SHELL"; *cp == *dp && *cp; cp++, dp++)
E 6
I 6
		for (cp = ename; *cp == *dp && *cp; cp++, dp++)
E 6
			continue;
D 6
		if (*cp == 0 && (*dp == '=' || *dp == 0)) {
			strcpy(shellbuf, "SHELL=");
			strcat(shellbuf, sp);
			*--ep = shellbuf;
			return;
		}
E 6
I 6
		if (*cp == 0 && (*dp == '=' || *dp == 0))
			return (*--ep);
E 6
	}
I 6
	return ((char *)0);
E 18
I 18
D 20
	execv(shell, argv);
E 20
I 20
	execv(shell, np);
E 20
D 19
	fprintf(stderr, "su: no shell\n");
E 19
I 19
D 27
	fprintf(stderr, "su: no shell.\n");
E 27
I 27
D 40
	(void)fprintf(stderr, "su: %s not found.\n", shell);
E 27
E 19
	exit(1);
E 40
I 40
	err(1, "%s", shell);
E 40
I 21
}

I 40
int
E 40
chshell(sh)
	char *sh;
{
D 27
	char *cp, *getusershell();
E 27
I 27
D 40
	register char *cp;
	char *getusershell();
E 40
I 40
	char *cp;
E 40
E 27

	while ((cp = getusershell()) != NULL)
D 40
		if (!strcmp(cp, sh))
E 40
I 40
		if (strcmp(cp, sh) == 0)
E 40
D 38
			return(1);
	return(0);
E 38
I 38
			return (1);
	return (0);
E 38
E 21
E 18
E 6
}
I 26

I 28
char *
D 34
mytty()
E 34
I 34
ontty()
E 34
{
D 40
	char *p, *ttyname();
E 40
I 40
	char *p;
E 40
I 34
	static char buf[MAXPATHLEN + 4];
E 34

D 34
	return((p = ttyname(STDERR_FILENO)) ? p : "UNKNOWN TTY");
E 34
I 34
	buf[0] = 0;
	if (p = ttyname(STDERR_FILENO))
D 40
		sprintf(buf, " on %s", p);
E 40
I 40
		snprintf(buf, sizeof(buf), " on %s", p);
E 40
	return (buf);
E 34
}

E 28
D 27
#ifdef	KERBEROS
int
E 27
I 27
#ifdef KERBEROS
kerberos(username, user, uid)
	char *username, *user;
	int uid;
{
	extern char *krb_err_txt[];
	KTEXT_ST ticket;
	AUTH_DAT authdata;
	struct hostent *hp;
D 40
	register char *p;
E 40
I 40
	char *p;
E 40
	int kerno;
	u_long faddr;
D 33
	char lrealm[REALM_SZ], krbtkfile[MAXPATHLEN], pw_buf[_PASSWORD_LEN];
E 33
I 33
	char lrealm[REALM_SZ], krbtkfile[MAXPATHLEN];
E 33
	char hostname[MAXHOSTNAMELEN], savehost[MAXHOSTNAMELEN];
I 28
D 34
	char *mytty();
E 34
I 34
D 36
	char *ontty();
E 36
I 36
D 40
	char *ontty(), *krb_get_phost();
E 40
I 40
	char *krb_get_phost();
E 40
E 36
E 34
E 28

D 38
	if (krb_get_lrealm(lrealm, 1) != KSUCCESS) {
		(void)fprintf(stderr, "su: couldn't get local realm.\n");
		return(1);
	}
E 38
I 38
	if (krb_get_lrealm(lrealm, 1) != KSUCCESS)
		return (1);
E 38
	if (koktologin(username, lrealm, user) && !uid) {
D 40
		(void)fprintf(stderr, "kerberos su: not in %s's ACL.\n", user);
E 40
I 40
		warnx("kerberos: not in %s's ACL.", user);
E 40
D 38
		return(1);
E 38
I 38
		return (1);
E 38
	}
	(void)sprintf(krbtkfile, "%s_%s_%d", TKT_ROOT, user, getuid());
D 33
	/* setuid(uid); */
E 33

D 33
	if (read_pw_string(pw_buf, sizeof(pw_buf) - 1,
	    "Kerberos password: ", 0)) {
		(void)fprintf(stderr, "su: error reading password.\n");
		return(1);
	}

E 33
	(void)setenv("KRBTKFILE", krbtkfile, 1);
I 38
	(void)krb_set_tkt_string(krbtkfile);
E 38
I 34
	/*
	 * Set real as well as effective ID to 0 for the moment,
	 * to make the kerberos library do the right thing.
	 */
E 34
D 33
	/* short lifetime for root tickets */
E 33
	if (setuid(0) < 0) {
D 40
		perror("su: setuid");
E 40
I 40
		warn("setuid");
E 40
D 38
		return(1);
E 38
I 38
		return (1);
E 38
	}
D 38
	(void)unlink(krbtkfile);
E 38
D 33
	/* POLICY: short ticket lifetime for root */
	kerno = krb_get_pw_in_tkt(username, (uid == 0 ? "root" : ""), lrealm,
	    "krbtgt", lrealm, (uid == 0 ? 2 : DEFAULT_TKT_LIFE), pw_buf);
E 33

D 33
	bzero(pw_buf, sizeof(pw_buf));
E 33
I 33
	/*
	 * Little trick here -- if we are su'ing to root,
	 * we need to get a ticket for "xxx.root", where xxx represents
	 * the name of the person su'ing.  Otherwise (non-root case),
	 * we need to get a ticket for "yyy.", where yyy represents
	 * the name of the person being su'd to, and the instance is null
	 *
D 34
	 * Also: POLICY: short ticket lifetime for root
E 34
I 34
	 * We should have a way to set the ticket lifetime,
	 * with a system default for root.
E 34
	 */
	kerno = krb_get_pw_in_tkt((uid == 0 ? username : user),
		(uid == 0 ? "root" : ""), lrealm,
D 34
	    	"krbtgt", lrealm, (uid == 0 ? 2 : DEFAULT_TKT_LIFE), 0);
E 34
I 34
	    	"krbtgt", lrealm, DEFAULT_TKT_LIFE, 0);
E 34
E 33

	if (kerno != KSUCCESS) {
D 33
		if (kerno == KDC_PR_UNKNOWN)
E 33
I 33
		if (kerno == KDC_PR_UNKNOWN) {
D 40
			fprintf(stderr, "principal unknown: %s.%s@%s\n",
E 40
I 40
			warnx("kerberos: principal unknown: %s.%s@%s",
E 40
				(uid == 0 ? username : user),
				(uid == 0 ? "root" : ""), lrealm);
E 33
D 38
			return(1);
E 38
I 38
			return (1);
E 38
I 33
		}
E 33
D 38
		(void)printf("su: unable to su: %s\n", krb_err_txt[kerno]);
E 38
I 38
D 40
		(void)fprintf(stderr, "su: unable to su: %s\n",
		    krb_err_txt[kerno]);
E 40
I 40
		warnx("kerberos: unable to su: %s", krb_err_txt[kerno]);
E 40
E 38
		syslog(LOG_NOTICE|LOG_AUTH,
D 28
		    "su: BAD Kerberos SU: %s on %s: %s", username, ttyname(2),
E 28
I 28
D 33
		    "su: BAD Kerberos SU: %s on %s: %s", username, mytty(),
E 28
		    krb_err_txt[kerno]);
E 33
I 33
D 34
		    "su: BAD Kerberos SU: %s on %s to %s: %s",
		    username, mytty(), user, krb_err_txt[kerno]);
E 34
I 34
D 38
		    "su: BAD Kerberos SU: %s to %s%s: %s",
E 38
I 38
		    "BAD Kerberos SU: %s to %s%s: %s",
E 38
		    username, user, ontty(), krb_err_txt[kerno]);
E 34
E 33
D 38
		return(1);
E 38
I 38
		return (1);
E 38
	}

	if (chown(krbtkfile, uid, -1) < 0) {
D 40
		perror("su: chown:");
E 40
I 40
		warn("chown");
E 40
		(void)unlink(krbtkfile);
D 38
		return(1);
E 38
I 38
		return (1);
E 38
	}

	(void)setpriority(PRIO_PROCESS, 0, -2);

	if (gethostname(hostname, sizeof(hostname)) == -1) {
D 38
		perror("su: hostname");
E 38
I 38
D 40
		perror("su: gethostname");
E 40
I 40
		warn("gethostname");
E 40
E 38
		dest_tkt();
D 38
		return(1);
E 38
I 38
		return (1);
E 38
	}

	(void)strncpy(savehost, krb_get_phost(hostname), sizeof(savehost));
	savehost[sizeof(savehost) - 1] = '\0';

	kerno = krb_mk_req(&ticket, "rcmd", savehost, lrealm, 33);

	if (kerno == KDC_PR_UNKNOWN) {
D 38
		(void)printf("Warning: tgt not verified.\n");
E 38
I 38
D 40
		(void)fprintf(stderr, "Warning: TGT not verified.\n");
E 40
I 40
		warnx("Warning: TGT not verified.");
E 40
E 38
D 33
		syslog(LOG_NOTICE|LOG_AUTH, "su: %s on %s, tgt not verified",
D 28
		    username, ttyname(2));
E 28
I 28
		    username, mytty());
E 33
I 33
		syslog(LOG_NOTICE|LOG_AUTH,
D 34
			"su: %s on %s to %s, TGT not verified",
		    	username, mytty(), user);
E 34
I 34
D 38
			"su: %s to %s%s, TGT not verified",
		    	username, user, ontty());
E 38
I 38
		    "%s to %s%s, TGT not verified (%s); %s.%s not registered?",
		    username, user, ontty(), krb_err_txt[kerno],
		    "rcmd", savehost);
E 38
E 34
E 33
E 28
	} else if (kerno != KSUCCESS) {
D 33
		(void)printf("Unable to use tgt: %s\n", krb_err_txt[kerno]);
		syslog(LOG_NOTICE|LOG_AUTH, "su: failed su: %s on %s: %s",
D 28
		    username, ttyname(2), krb_err_txt[kerno]);
E 28
I 28
		    username, mytty(), krb_err_txt[kerno]);
E 33
I 33
D 38
		(void)printf("Unable to use TGT: %s\n", krb_err_txt[kerno]);
D 34
		syslog(LOG_NOTICE|LOG_AUTH, "su: failed su: %s on %s to %s: %s",
		    username, mytty(), user, krb_err_txt[kerno]);
E 34
I 34
		syslog(LOG_NOTICE|LOG_AUTH, "su: failed su: %s to %s%s: %s",
E 38
I 38
D 40
		(void)fprintf(stderr, "Unable to use TGT: %s\n",
		    krb_err_txt[kerno]);
E 40
I 40
		warnx("Unable to use TGT: %s", krb_err_txt[kerno]);
E 40
		syslog(LOG_NOTICE|LOG_AUTH, "failed su: %s to %s%s: %s",
E 38
		    username, user, ontty(), krb_err_txt[kerno]);
E 34
E 33
E 28
		dest_tkt();
D 38
		return(1);
E 38
I 38
		return (1);
E 38
	} else {
		if (!(hp = gethostbyname(hostname))) {
D 38
			(void)printf("su: can't get addr of %s\n", hostname);
E 38
I 38
D 40
			(void)fprintf(stderr, "su: can't get addr of %s\n",
			    hostname);
E 40
I 40
			warnx("can't get addr of %s", hostname);
E 40
E 38
			dest_tkt();
D 38
			return(1);
E 38
I 38
			return (1);
E 38
		}
D 40
		(void)bcopy((char *)hp->h_addr, (char *)&faddr, sizeof(faddr));
E 40
I 40
		memmove((char *)&faddr, (char *)hp->h_addr, sizeof(faddr));
E 40

		if ((kerno = krb_rd_req(&ticket, "rcmd", savehost, faddr,
		    &authdata, "")) != KSUCCESS) {
D 38
			(void)printf("su: unable to verify rcmd ticket: %s\n",
E 38
I 38
D 40
			(void)fprintf(stderr,
			    "su: unable to verify rcmd ticket: %s\n",
E 40
I 40
			warnx("kerberos: unable to verify rcmd ticket: %s\n",
E 40
E 38
			    krb_err_txt[kerno]);
			syslog(LOG_NOTICE|LOG_AUTH,
D 33
			    "su: failed su: %s on %s: %s", username,
D 28
			    ttyname(2), krb_err_txt[kerno]);
E 28
I 28
			    mytty(), krb_err_txt[kerno]);
E 33
I 33
D 34
			    "su: failed su: %s on %s to %s: %s", username,
			    mytty(), user, krb_err_txt[kerno]);
E 34
I 34
D 38
			    "su: failed su: %s to %s%s: %s", username,
			    ontty(), user, krb_err_txt[kerno]);
E 38
I 38
			    "failed su: %s to %s%s: %s", username,
			     user, ontty(), krb_err_txt[kerno]);
E 38
E 34
E 33
E 28
			dest_tkt();
D 38
			return(1);
E 38
I 38
			return (1);
E 38
		}
	}
D 38
	return(0);
E 38
I 38
	return (0);
E 38
}

E 27
koktologin(name, realm, toname)
D 27
	char	*name, *realm, *toname;
E 27
I 27
	char *name, *realm, *toname;
E 27
{
D 27
	AUTH_DAT	kdata_st;
	AUTH_DAT	*kdata = &kdata_st;
E 27
I 27
D 40
	register AUTH_DAT *kdata;
E 40
I 40
	AUTH_DAT *kdata;
E 40
	AUTH_DAT kdata_st;
E 27

I 27
	kdata = &kdata_st;
E 27
D 40
	bzero((caddr_t) kdata, sizeof(*kdata));
E 40
I 40
	memset((char *)kdata, 0, sizeof(*kdata));
E 40
D 27
	strcpy(kdata->pname, name);
	strcpy(kdata->pinst, ((strcmp(toname, "root") == 0) ? "root" : ""));
	strcpy(kdata->prealm, realm);
E 27
I 27
	(void)strcpy(kdata->pname, name);
	(void)strcpy(kdata->pinst,
	    ((strcmp(toname, "root") == 0) ? "root" : ""));
	(void)strcpy(kdata->prealm, realm);
E 27
D 38
	return(kuserok(kdata, toname));
E 38
I 38
	return (kuserok(kdata, toname));
E 38
}
#endif
E 26
E 1
