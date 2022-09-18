h18810
s 00005/00005/00104
d D 8.1 93/06/06 22:25:15 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00108
d D 5.11 90/06/01 18:35:35 bostic 17 16
c new copyright notice
e
s 00089/00073/00030
d D 5.10 89/06/29 17:37:18 bostic 16 15
c new version from Michael Fischbein.
e
s 00003/00002/00100
d D 5.9 89/06/26 21:28:35 karels 15 14
c don't print garbage host on guess
e
s 00000/00001/00102
d D 5.8 89/05/11 13:47:23 bostic 14 13
c remove pathnames.h
e
s 00002/00001/00101
d D 5.7 89/03/05 21:55:27 bostic 13 12
c add pathnames.h, _PATH_UTMP
e
s 00002/00001/00100
d D 5.6 89/03/03 09:20:34 bostic 12 11
c add sys/types.h for pwd.h
e
s 00004/00002/00097
d D 5.5 88/08/29 08:40:05 bostic 11 10
c if not logged in, but on a valid tty, didn't get the name right
e
s 00003/00003/00096
d D 5.4 88/04/20 10:49:47 bostic 10 9
c report utmp file name if can't open; bug report 4.2BSD/bin/176
e
s 00059/00064/00040
d D 5.3 87/04/06 14:49:55 karels 9 8
c reformat to standards; guess if not logged in
e
s 00064/00053/00040
d D 5.2 86/12/10 16:41:00 bostic 8 7
c general cleanup
e
s 00015/00002/00078
d D 5.1 85/05/02 14:49:27 dist 7 6
c 
e
s 00001/00001/00079
d D 4.6 83/08/19 16:19:33 sam 6 5
c incorrect max login name size
e
s 00013/00005/00067
d D 4.5 83/05/23 00:03:07 sam 5 4
c utmp format changed; show host for remote logins now
e
s 00010/00008/00062
d D 4.4 82/03/15 04:24:00 root 4 3
c machine independent
e
s 00001/00003/00069
d D 4.3 81/03/11 18:49:31 toy 3 2
c print machine!name, not (machine) name
e
s 00006/00003/00066
d D 4.2 80/11/01 14:54:39 bill 2 1
c Have who reflect identity of the system.
e
s 00069/00000/00000
d D 4.1 80/10/01 17:29:35 bill 1 0
c date and time created 80/10/01 17:29:35 by bill
e
u
U
t
T
I 7
/*
D 15
 * Copyright (c) 1980 Regents of the University of California.
E 15
I 15
D 16
 * Copyright (c) 1980, 1989 Regents of the University of California.
E 15
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 16
I 16
D 18
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
 * This code is derived from software contributed to Berkeley by
 * Michael Fischbein.
 *
D 17
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
E 17
I 17
 * %sccs.include.redist.c%
E 17
E 16
 */

E 7
I 5
#ifndef lint
E 5
I 1
D 7
static char *sccsid = "%W% (Berkeley) %G%";
I 5
#endif
E 7
I 7
D 18
char copyright[] =
D 15
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 15
I 15
D 16
"%Z% Copyright (c) 1980, 1989 Regents of the University of California.\n\
E 16
I 16
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 16
E 15
 All rights reserved.\n";
E 18
I 18
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 18
D 16
#endif not lint
E 16
I 16
#endif /* not lint */
E 16

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 16
#endif not lint
E 16
I 16
#endif /* not lint */
E 16

E 7
E 5
D 16
/*
 * who
 */

E 16
D 8
#include <stdio.h>
E 8
I 8
D 9
#include <sys/param.h>
E 9
I 9
D 12
#include <stdio.h>
E 12
I 12
#include <sys/types.h>
E 12
E 9
E 8
D 16
#include <utmp.h>
E 16
I 16
#include <sys/file.h>
#include <sys/time.h>
E 16
#include <pwd.h>
I 16
#include <utmp.h>
E 16
I 12
#include <stdio.h>
E 12
I 8
D 9
#include <stdio.h>
#include <strings.h>
E 9
E 8
I 2
D 4
#include <whoami.h>
E 4
D 16
#include <ctype.h>
E 16
I 13
D 14
#include "pathnames.h"
E 14
E 13
E 2

D 8
#define NMAX sizeof(utmp.ut_name)
#define LMAX sizeof(utmp.ut_line)
I 5
#define	HMAX sizeof(utmp.ut_host)
E 8
I 8
D 9
#define NMAX	sizeof(utmp.ut_name)
#define LMAX	sizeof(utmp.ut_line)
#define HMAX	sizeof(utmp.ut_host)
E 9
I 9
D 16
#define NMAX sizeof(utmp.ut_name)
#define LMAX sizeof(utmp.ut_line)
#define	HMAX sizeof(utmp.ut_host)
E 9
E 8
E 5

D 4
struct utmp utmp;
struct passwd *pw;
struct passwd *getpwuid();
E 4
I 4
D 8
struct	utmp utmp;
struct	passwd *pw;
struct	passwd *getpwuid();
char	hostname[32];
E 8
I 8
D 9
static struct utmp	utmp;		/* read buffer */
E 9
I 9
struct	utmp utmp;
struct	passwd *pw;
struct	passwd *getpwuid();
E 9
E 8
E 4

D 4
char *ttyname(), *rindex(), *ctime(), *strcpy();
E 4
I 4
D 8
char	*ttyname(), *rindex(), *ctime(), *strcpy();

E 4
main(argc, argv)
D 4
char **argv;
E 4
I 4
	int argc;
	char **argv;
E 8
I 8
D 9
main(argc,argv)
int	argc;
char	**argv;
E 9
I 9
char	*ttyname(), *rindex(), *ctime(), *strcpy();

E 16
main(argc, argv)
	int argc;
	char **argv;
E 9
E 8
E 4
{
D 8
	register char *tp, *s;
	register FILE *fi;
	extern char _sobuf[];
E 8
I 8
D 9
	register FILE	*fp;			/* utmp file pointer */
	register char	*tp,			/* tty name */
			*fname;			/* utmp file name */
	struct passwd	*pw,			/* user passwd structure */
			*getpwuid();
	char	hostname[MAXHOSTNAMELEN],	/* host name */
		*ttyname();
	uid_t	getuid();
	long	time();
E 9
I 9
D 16
	register char *tp, *s;
	register FILE *fi;
E 16
I 16
	register char *p;
	struct utmp usr;
	struct passwd *pw;
	FILE *ufp, *file();
	char *t, *rindex(), *strcpy(), *strncpy(), *ttyname();
	time_t time();
E 16
E 9
E 8

D 8
	setbuf(stdout, _sobuf);
	s = "/etc/utmp";
	if(argc == 2)
		s = argv[1];
D 5
	if (argc==3) {
E 5
I 5
	if (argc == 3) {
E 5
		tp = ttyname(0);
		if (tp)
			tp = rindex(tp, '/') + 1;
		else {	/* no tty - use best guess from passwd file */
			pw = getpwuid(getuid());
D 6
			strcpy(utmp.ut_name, pw?pw->pw_name: "?");
E 6
I 6
			strncpy(utmp.ut_name, pw ? pw->pw_name : "?", NMAX);
E 6
			strcpy(utmp.ut_line, "tty??");
			time(&utmp.ut_time);
			putline();
			exit(0);
		}
E 8
I 8
D 9
	switch(argc) {
		case 2:
			fname = argv[1];
			break;
		case 3:
			if (!(tp = ttyname(0))) {
				/*
				 * no tty -- use best guess from passwd file.
				 * next line is a kludge, but as of now getuid
				 * returns a "uid_t" and getpwuid takes an int.
				 */
				pw = getpwuid((int)getuid());
				strncpy(utmp.ut_name,pw ? pw->pw_name : "?",NMAX);
				strcpy(utmp.ut_line,"tty??");
				time(&utmp.ut_time);
				putline();
				exit(0);
			}
			tp = rindex(tp,'/') + 1;
			if (gethostname(hostname,sizeof(hostname)) == -1) {
				perror("gethostname");
				exit(1);
			}
		case 1:
			fname = "/etc/utmp";
			break;
		default:
			fputs("usage: who [ utmp_file ]\nor who am i\n",stderr);
			exit(1);
E 9
I 9
D 13
	s = "/etc/utmp";
E 13
I 13
D 16
	s = _PATH_UTMP;
E 13
	if(argc == 2)
		s = argv[1];
	if (argc == 3) {
		tp = ttyname(0);
		if (tp)
			tp = rindex(tp, '/') + 1;
		else {	/* no tty - use best guess from passwd file */
D 10
			strcpy(utmp.ut_line, "tty??");
E 10
I 10
			(void)strcpy(utmp.ut_line, "tty??");
E 10
			guess();
			exit(0);
		}
E 9
E 8
	}
D 8
	if ((fi = fopen(s, "r")) == NULL) {
		puts("who: cannot open utmp");
E 8
I 8
D 9
	if (!(fp = fopen(fname,"r"))) {
		perror(fname);
E 9
I 9
D 10
	if ((fi = fopen(s, "r")) == NULL) {
		puts("who: cannot open utmp");
E 10
I 10
	if (!(fi = fopen(s, "r"))) {
		fprintf(stderr, "who: cannot read %s.\n", s);
E 16
I 16
	switch (argc) {
	case 1:					/* who */
		ufp = file(_PATH_UTMP);
		/* only entries with both name and line fields */
		while (fread((char *)&usr, sizeof(usr), 1, ufp) == 1)
			if (*usr.ut_name && *usr.ut_line)
				output(&usr);
		break;
	case 2:					/* who utmp_file */
		ufp = file(argv[1]);
		/* all entries */
		while (fread((char *)&usr, sizeof(usr), 1, ufp) == 1)
			output(&usr);
		break;
	case 3:					/* who am i */
		ufp = file(_PATH_UTMP);

		/* search through the utmp and find an entry for this tty */
		if (p = ttyname(0)) {
			/* strip any directory component */
			if (t = rindex(p, '/'))
				p = t + 1;
			while (fread((char *)&usr, sizeof(usr), 1, ufp) == 1)
				if (usr.ut_name && !strcmp(usr.ut_line, p)) {
					output(&usr);
					exit(0);
				}
			/* well, at least we know what the tty is */
			(void)strncpy(usr.ut_line, p, UT_LINESIZE);
		} else
			(void)strcpy(usr.ut_line, "tty??");
		pw = getpwuid(getuid());
		(void)strncpy(usr.ut_name, pw ? pw->pw_name : "?", UT_NAMESIZE);
		(void)time(&usr.ut_time);
		*usr.ut_host = '\0';
		output(&usr);
		break;
	default:
		(void)fprintf(stderr, "usage: who [ file ]\n       who am i\n");
E 16
E 10
E 9
E 8
		exit(1);
	}
D 8
	while (fread((char *)&utmp, sizeof(utmp), 1, fi) == 1) {
E 8
I 8
D 9
	while (fread((char *)&utmp,sizeof(utmp),1,fp) == 1)
E 9
I 9
D 16
	while (fread((char *)&utmp, sizeof(utmp), 1, fi) == 1) {
E 9
E 8
D 5
		if(argc==3) {
E 5
I 5
		if (argc == 3) {
E 5
I 2
D 4
			static char myname[]=sysname;
E 4
I 4
D 8
			gethostname(hostname, sizeof (hostname));
E 4
E 2
			if (strcmp(utmp.ut_line, tp))
				continue;
D 2
#ifdef vax
			printf("(Vax) ");
#endif
E 2
I 2
D 3
			if (islower(*myname))
				*myname = toupper(*myname);
			printf("(%s) ",myname);
E 3
I 3
D 4
			printf("%s!",myname);
E 4
I 4
			printf("%s!", hostname);
E 4
E 3
E 2
			putline();
			exit(0);
E 8
I 8
D 9
			if (!strcmp(utmp.ut_line,tp)) {
				printf("%s!",hostname);
				putline();
				exit(0);
			}
E 8
		}
D 5
		if(utmp.ut_name[0] == '\0' && argc==1)
E 5
I 5
D 8
		if (utmp.ut_name[0] == '\0' && argc == 1)
E 5
			continue;
		putline();
	}
E 8
I 8
		else if (argc != 1 || *utmp.ut_name)
E 9
I 9
			if (strcmp(utmp.ut_line, tp))
				continue;
E 9
D 11
			putline();
E 11
I 11
			if (!utmp.ut_name[0])
				guess();
			else
				putline();
E 11
I 9
			exit(0);
		}
		if (utmp.ut_name[0] == '\0' && argc == 1)
			continue;
		putline();
	}
	if (argc == 3) {
		strncpy(utmp.ut_line, tp, sizeof(utmp.ut_line));
		guess();
	}
E 16
	exit(0);
E 9
E 8
}

D 16
putline()
E 16
I 16
output(up)
	struct utmp *up;
E 16
{
D 8
	register char *cbuf;
E 8
I 8
D 9
	register char	*cbuf;
	char	*ctime();
E 9
I 9
D 16
	register char *cbuf;
E 16
I 16
	char *ctime();
E 16
E 9
E 8

D 5
	printf("%-*.*s %-*.*s", NMAX, NMAX, utmp.ut_name, LMAX, LMAX, utmp.ut_line);
E 5
I 5
D 8
	printf("%-*.*s %-*.*s",
		NMAX, NMAX, utmp.ut_name,
		LMAX, LMAX, utmp.ut_line);
E 5
	cbuf = ctime(&utmp.ut_time);
D 5
	printf("%.12s\n", cbuf+4);
E 5
I 5
	printf("%.12s", cbuf+4);
	if (utmp.ut_host[0])
		printf("\t(%.*s)", HMAX, utmp.ut_host);
E 8
I 8
D 9
	cbuf = ctime(&utmp.ut_time) + 4;
	printf("%-*.*s %-*.*s%.12s",NMAX,NMAX,utmp.ut_name,LMAX,LMAX,utmp.ut_line,cbuf);
	if (*utmp.ut_host)
		printf("\t(%.*s)",HMAX,utmp.ut_host);
E 9
I 9
D 16
	printf("%-*.*s %-*.*s",
		NMAX, NMAX, utmp.ut_name,
		LMAX, LMAX, utmp.ut_line);
	cbuf = ctime(&utmp.ut_time);
	printf("%.12s", cbuf+4);
	if (utmp.ut_host[0])
		printf("\t(%.*s)", HMAX, utmp.ut_host);
E 9
E 8
	putchar('\n');
E 16
I 16
	(void)printf("%-*.*s %-*.*s", UT_NAMESIZE, UT_NAMESIZE, up->ut_name,
	    UT_LINESIZE, UT_LINESIZE, up->ut_line);
	(void)printf("%.12s", ctime(&up->ut_time) + 4);
	if (*up->ut_host)
		printf("\t(%.*s)", UT_HOSTSIZE, up->ut_host);
	(void)putchar('\n');
E 16
I 9
}

D 16
guess()
E 16
I 16
FILE *
file(name)
	char *name;
E 16
{
D 11

E 11
D 16
	pw = getpwuid(getuid());
	strncpy(utmp.ut_name, pw ? pw->pw_name : "?", NMAX);
	time(&utmp.ut_time);
I 15
	utmp.ut_host[0] = '\0';
E 15
	putline();
E 16
I 16
	extern int errno;
	FILE *ufp;
	char *strerror();

	if (!(ufp = fopen(name, "r"))) {
		(void)fprintf(stderr, "who: %s: %s.\n", name, strerror(errno));
		exit(1);
	}
	return(ufp);
E 16
E 9
E 5
}
E 1
