h50516
s 00008/00005/00234
d D 8.5 95/05/04 15:37:54 bostic 39 38
c optarg/optind moved to unistd.h
e
s 00002/00002/00237
d D 8.4 95/04/28 17:36:36 bostic 38 37
c use memmove, not memcpy
e
s 00018/00010/00221
d D 8.3 95/04/28 17:35:54 bostic 37 36
c You may have already done the same (does the Alpha have alignment
c constraints? I think it does...).  I also changed it to use the libc
c err, instead of its own, and fixed most of the `gcc -Wall' complaints.
c The important changes are to memcpy the pointers from db->get and db->seq.
c From: Chris Torek <torek@BSDI.COM>
e
s 00001/00001/00230
d D 8.2 93/09/30 06:58:28 pendry 36 35
c fix malloc buffer overrun problem.
e
s 00005/00005/00226
d D 8.1 93/06/06 14:39:01 bostic 35 34
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00002/00230
d D 5.25 92/03/06 13:51:41 bostic 34 33
c last change broke loose matching
e
s 00061/00051/00171
d D 5.24 91/07/27 17:59:14 bostic 33 32
c finger really didn't need its own hashing scheme
e
s 00022/00019/00200
d D 5.23 91/07/27 15:58:20 bostic 32 31
c Welcome to the Wonderful World of ANSI!
e
s 00005/00004/00214
d D 5.22 90/06/29 15:19:43 edward 31 30
c do network fingers in argument order (instead of reverse order)
e
s 00000/00001/00218
d D 5.21 90/06/24 23:27:29 bostic 30 29
c don't need pathnames.h, just paths.h
e
s 00001/00011/00218
d D 5.20 90/06/01 16:49:24 bostic 29 28
c new copyright notice
e
s 00000/00000/00229
d D 5.19 90/02/07 08:25:11 bostic 28 27
x 24
c exclude sccs changes to remove contrib line from copyright
e
s 00004/00008/00222
d D 5.18 89/09/01 08:57:32 bostic 27 26
c don't display meta/control chars; bug report 4.3BSD/usr.bin/213
e
s 00035/00033/00195
d D 5.17 89/08/11 13:49:56 edward 26 25
c use fread() on /etc/utmp; no more ARGIGNORE
e
s 00023/00023/00205
d D 5.16 89/05/11 15:53:50 bostic 25 24
c can't set ARGIGNORE since each argument may match multiple entries in
c the password file -- have to have new data structure to keep track of what
c args have been satisfied
e
s 00000/00003/00228
d D 5.15 89/05/08 11:35:58 bostic 24 23
c clean up copyright notice
e
s 00050/00098/00181
d D 5.14 89/05/07 01:02:50 edward 23 22
c show last login time if more recent than current logins,
c cleaned up, speeded up, put people in hash table, separate login info
c from personal info
e
s 00203/01006/00076
d D 5.13 89/05/06 13:51:55 bostic 22 21
c Tony Nardo (trn@warper.jhuapl.edu) reworked the original, I
c redid his stuff; should handle multiple logons right.
e
s 00016/00023/01066
d D 5.12 89/05/04 09:27:20 bostic 21 20
c file system reorg, pathnames.h; fix pw_stayopen
e
s 00017/00006/01072
d D 5.11 88/09/20 16:56:56 bostic 20 19
c written by Earl Cohen; add Berkeley specific header
e
s 00002/00002/01076
d D 5.10 87/04/26 13:12:55 bostic 19 18
c "finger" format suggestion; bug report 4.2BSD/ucb/68
e
s 00002/00004/01076
d D 5.9 86/08/17 12:06:24 sam 18 17
c flush hostname before connect to signify host lookup completed
e
s 00001/00001/01079
d D 5.8 86/03/13 20:29:23 mckusick 17 16
c setgid to group "write" so that terminals need not be world writable
e
s 00013/00003/01067
d D 5.7 85/12/11 16:47:28 bloom 16 15
c map control characters to ^X to avoid trojan horses in .plan and .profile
e
s 00001/00001/01069
d D 5.6 85/10/21 12:10:20 bloom 15 14
c use static if variable used outside of block
e
s 00002/00001/01068
d D 5.5 85/10/20 22:31:55 sam 14 13
c update for revised hostent structure
e
s 00001/00000/01068
d D 5.4 85/10/09 11:42:16 bloom 13 12
c close the socket for remote fingers
e
s 00008/00000/01060
d D 5.3 85/08/28 15:53:26 bloom 12 11
c support for 5 digit phone numbers (3-1234)
e
s 00005/00002/01055
d D 5.2 85/08/28 14:39:54 edward 11 10
c don't open pw file if only doing net finger
e
s 00013/00001/01044
d D 5.1 85/05/31 09:11:36 dist 10 9
c Add copyright
e
s 00811/01235/00234
d D 4.9 85/04/09 14:15:57 edward 9 8
c print rlogin hostname, office address more tolerant, and rework
e
s 00001/00004/01468
d D 4.8 84/09/17 10:46:03 ralph 8 7
c don't call setbuf.
e
s 00002/00002/01470
d D 4.7 84/07/21 03:03:34 lepreau 7 6
c Missing return: just lucky before
e
s 00099/00002/01373
d D 4.6 84/05/11 22:12:11 sam 6 5
c add netfinger mods from rws@mit
e
s 00001/00001/01374
d D 4.5 83/09/16 09:17:39 ralph 5 4
c increased buffer size for long names in decode().
e
s 00003/00002/01372
d D 4.4 83/07/02 00:54:45 sam 4 3
c include fixes
e
s 00002/00000/01372
d D 4.3 82/12/13 19:28:42 shannon 3 2
c zero pointer bug
e
s 00016/00011/01356
d D 4.2 82/10/23 21:19:58 mckusick 2 1
c no amount of work would help this program
e
s 01367/00000/00000
d D 4.1 80/10/01 17:26:39 bill 1 0
c date and time created 80/10/01 17:26:39 by bill
e
u
U
t
T
I 10
/*
D 20
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 20
I 20
D 22
 * Copyright (c) 1980 The Regents of the University of California.
E 22
I 22
D 35
 * Copyright (c) 1989 The Regents of the University of California.
E 22
 * All rights reserved.
E 35
I 35
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 35
 *
I 22
D 24
 * This code is derived from software contributed to Berkeley by
 * Tony Nardo of the Johns Hopkins University/Applied Physics Lab.
 *
E 24
E 22
D 29
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
D 22
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 22
I 22
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 29
I 29
 * %sccs.include.redist.c%
E 29
E 22
E 20
 */

E 10
I 4
#ifndef lint
I 10
D 35
char copyright[] =
D 20
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 20
I 20
D 22
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 22
I 22
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 22
E 20
 All rights reserved.\n";
E 35
I 35
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 35
D 20
#endif not lint
E 20
I 20
#endif /* not lint */
E 20

#ifndef lint
E 10
E 4
I 1
D 9
static char *sccsid = "%W% (Berkeley) %G%";
E 9
I 9
static char sccsid[] = "%W% (Berkeley) %G%";
E 9
I 4
D 10
#endif
E 10
I 10
D 20
#endif not lint
E 20
I 20
#endif /* not lint */
E 20
E 10
E 4

D 9
/*  This is a finger program.  It prints out useful information about users
 *  by digging it up from various system files.  It is not very portable
 *  because the most useful parts of the information (the full user name,
 *  office, and phone numbers) are all stored in the VAX-unused gecos field
 *  of /etc/passwd, which, unfortunately, other UNIXes use for other things.
E 9
I 9
/*
D 22
 * This is a finger program.  It prints out useful information about users
 * by digging it up from various system files.  It is not very portable
 * because the most useful parts of the information (the full user name,
 * office, and phone numbers) are all stored in the VAX-unused gecos field
 * of /etc/passwd, which, unfortunately, other UNIXes use for other things.
E 22
I 22
 * Finger prints out information about users.  It is not portable since
 * certain fields (e.g. the full user name, office, and phone numbers) are
 * extracted from the gecos field of the passwd file which other UNIXes
 * may not have or may use for other things.
E 22
E 9
 *
D 9
 *  There are three output formats, all of which give login name, teletype
 *  line number, and login time.  The short output format is reminiscent
 *  of finger on ITS, and gives one line of information per user containing
 *  in addition to the minimum basic requirements (MBR), the full name of
 *  the user, his idle time and office location and phone number.  The
 *  quick style output is UNIX who-like, giving only name, teletype and
 *  login time.  Finally, the long style output give the same information
 *  as the short (in more legible format), the home directory and shell
 *  of the user, and, if it exits, a copy of the file .plan in the users
 *  home directory.  Finger may be called with or without a list of people
 *  to finger -- if no list is given, all the people currently logged in
 *  are fingered.
E 9
I 9
D 22
 * There are three output formats, all of which give login name, teletype
 * line number, and login time.  The short output format is reminiscent
 * of finger on ITS, and gives one line of information per user containing
 * in addition to the minimum basic requirements (MBR), the full name of
 * the user, his idle time and office location and phone number.  The
 * quick style output is UNIX who-like, giving only name, teletype and
 * login time.  Finally, the long style output give the same information
 * as the short (in more legible format), the home directory and shell
 * of the user, and, if it exits, a copy of the file .plan in the users
 * home directory.  Finger may be called with or without a list of people
 * to finger -- if no list is given, all the people currently logged in
 * are fingered.
E 9
 *
D 9
 *  The program is validly called by one of the following:
E 9
I 9
 * The program is validly called by one of the following:
E 9
 *
 *	finger			{short form list of users}
 *	finger -l		{long form list of users}
 *	finger -b		{briefer long form list of users}
 *	finger -q		{quick list of users}
 *	finger -i		{quick list of users with idle times}
 *	finger namelist		{long format list of specified users}
 *	finger -s namelist	{short format list of specified users}
 *	finger -w namelist	{narrow short format list of specified users}
 *
D 9
 *  where 'namelist' is a list of users login names.
 *  The other options can all be given after one '-', or each can have its
 *  own '-'.  The -f option disables the printing of headers for short and
 *  quick outputs.  The -b option briefens long format outputs.  The -p
 *  option turns off plans for long format outputs.
E 9
I 9
 * where 'namelist' is a list of users login names.
 * The other options can all be given after one '-', or each can have its
 * own '-'.  The -f option disables the printing of headers for short and
 * quick outputs.  The -b option briefens long format outputs.  The -p
 * option turns off plans for long format outputs.
E 22
I 22
 * There are currently two output formats; the short format is one line
 * per user and displays login name, tty, login time, real name, idle time,
 * and office location/phone number.  The long format gives the same
 * information (in a more legible format) as well as home directory, shell,
 * mail info, and .plan/.project files.
E 22
E 9
 */

D 9
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sgtty.h>
#include	<utmp.h>
#include	<signal.h>
#include	<pwd.h>
#include	<stdio.h>
D 4
#include	<sccs.h>
E 4
#include	<lastlog.h>
D 4
#include	<time.h>
E 4
I 4
#include	<sys/time.h>
I 6
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>
E 9
I 9
D 22
#include <sys/types.h>
#include <sys/stat.h>
D 21
#include <utmp.h>
E 21
#include <sys/signal.h>
D 21
#include <pwd.h>
#include <stdio.h>
#include <lastlog.h>
#include <ctype.h>
E 21
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
I 21
#include <utmp.h>
#include <pwd.h>
E 22
I 22
#include <sys/param.h>
I 39

#include <db.h>
#include <err.h>
#include <errno.h>
E 39
D 32
#include <sys/file.h>
E 32
I 32
#include <fcntl.h>
D 39
#include <time.h>
E 39
#include <pwd.h>
D 39
#include <utmp.h>
#include <errno.h>
E 39
E 32
E 22
#include <stdio.h>
I 32
#include <stdlib.h>
#include <string.h>
I 33
D 39
#include <db.h>
I 37
#include <err.h>
E 39
I 39
#include <time.h>
#include <unistd.h>
#include <utmp.h>

E 39
E 37
E 33
E 32
D 22
#include <ctype.h>
E 22
I 22
#include "finger.h"
E 22
D 30
#include "pathnames.h"
E 30
E 21
E 9
E 6
E 4

I 33
DB *db;
E 33
D 9
struct	utmp	utmp;	/* for sizeof */
#define NMAX sizeof(utmp.ut_name)
#define LMAX sizeof(utmp.ut_line)
E 9
I 9
D 22
#define ASTERISK	'*'		/* ignore this in real name */
#define COMMA		','		/* separator in pw_gecos field */
#define COMMAND		'-'		/* command line flag char */
#define CORY		'C'		/* cory hall office */
#define EVANS		'E'		/* evans hall office */
#define SAMENAME	'&'		/* repeat login name in real name */
D 17
#define TALKABLE	0222		/* tty is writable if 222 mode */
E 17
I 17
#define TALKABLE	0220		/* tty is writable if 220 mode */
E 17
E 9

E 22
D 9
#define		ASTERISK	'*'	/* ignore this in real name */
#define		BLANK		' '	/* blank character (i.e. space) */
#define		CAPITALIZE	0137&	/* capitalize character macro */
#define		COMMA		','	/* separator in pw_gecos field */
#define		COMMAND		'-'	/* command line flag char */
#define		CORY		'C'	/* cory hall office */
#define		EVANS		'E'	/* evans hall office */
#define		LINEBREAK	012	/* line feed */
#define		NULLSTR		""	/* the null string, opposed to NULL */
#define		SAMENAME	'&'	/* repeat login name in real name */
#define		TALKABLE	0222	/* tty is writeable if 222 mode */
E 9
I 9
D 23
struct utmp user;
D 22
#define NMAX sizeof(user.ut_name)
#define LMAX sizeof(user.ut_line)
#define HMAX sizeof(user.ut_host)
E 22
I 22
PERSON *head;
E 23
time_t now;
D 23
int entries, lflag, sflag, mflag, pplan;
E 23
I 23
D 32
int lflag, sflag, mflag, pplan;
E 32
I 32
int entries, lflag, mflag, pplan, sflag;
E 32
E 23
char tbuf[1024];
I 32
D 33
PERSON *phead, *ptail, *htab[HSIZE];
E 33
E 32
E 22
E 9

I 32
static void loginlist __P((void));
static void userlist __P((int, char **));

I 37
int
E 37
E 32
D 9
struct  person  {			/* one for each person fingered */
	char		name[NMAX+1];	/* login name */
	char		tty[LMAX+1];	/* NULL terminated tty line */
	long		loginat;	/* time of login (possibly last) */
	long		idletime;	/* how long idle (if logged in) */
	short int	loggedin;	/* flag for being logged in */
	short int	writeable;	/* flag for tty being writeable */
	char		*realname;	/* pointer to full name */
	char		*office;	/* pointer to office name */
	char		*officephone;	/* pointer to office phone no. */
	char		*homephone;	/* pointer to home phone no. */
	char		*random;	/* for any random stuff in pw_gecos */
	struct  passwd	*pwd;		/* structure of /etc/passwd stuff */
	struct  person	*link;		/* link to next person */
E 9
I 9
D 22
struct person {			/* one for each person fingered */
	char *name;			/* name */
	char tty[LMAX+1];		/* null terminated tty line */
	char host[HMAX+1];		/* null terminated remote host name */
	long loginat;			/* time of (last) login */
	long idletime;			/* how long idle (if logged in) */
	char *realname;			/* pointer to full name */
	char *office;			/* pointer to office name */
	char *officephone;		/* pointer to office phone no. */
	char *homephone;		/* pointer to home phone no. */
	char *random;			/* for any random stuff in pw_gecos */
	struct passwd *pwd;		/* structure of /etc/passwd stuff */
	char loggedin;			/* person is logged in */
	char writable;			/* tty is writable */
	char original;			/* this is not a duplicate entry */
	struct person *link;		/* link to next person */
E 9
};

D 9
struct  passwd			*NILPWD = 0;
struct  person			*NILPERS = 0;
E 9
I 9
D 21
char LASTLOG[] = "/usr/adm/lastlog";	/* last login info */
char USERLOG[] = "/etc/utmp";		/* who is logged in */
E 21
char PLAN[] = "/.plan";			/* what plan file is */
char PROJ[] = "/.project";		/* what project file */
	
int unbrief = 1;			/* -b option default */
int header = 1;				/* -f option default */
int hack = 1;				/* -h option default */
int idle = 0;				/* -i option default */
int large = 0;				/* -l option default */
int match = 1;				/* -m option default */
int plan = 1;				/* -p option default */
int unquick = 1;			/* -q option default */
int small = 0;				/* -s option default */
int wide = 1;				/* -w option default */
E 9

D 9
int		persize		= sizeof( struct person );
int		pwdsize		= sizeof( struct passwd );
E 9
I 9
int unshort;
D 21
int lf;					/* LASTLOG file descriptor */
E 21
I 21
int lf;					/* _PATH_LASTLOG file descriptor */
E 21
struct person *person1;			/* list of people */
long tloc;				/* current time */
E 9

D 9
char		LASTLOG[]	= "/usr/adm/lastlog";	/* last login info */
char		USERLOG[]	= "/etc/utmp";		/* who is logged in */
D 8
char		outbuf[BUFSIZ];				/* output buffer */
E 8
D 7
char		*ctime();
E 7
I 7
char		*ctime(), *strcpy();
E 9
I 9
struct passwd *pwdcopy();
char *strcpy();
char *malloc();
char *ctime();
E 9
E 7

E 22
D 9
int		unbrief		= 1;		/* -b option default */
int		header		= 1;		/* -f option default */
int		hack		= 1;		/* -h option default */
int		idle		= 0;		/* -i option default */
int		large		= 0;		/* -l option default */
int		match		= 1;		/* -m option default */
int		plan		= 1;		/* -p option default */
int		unquick		= 1;		/* -q option default */
int		small		= 0;		/* -s option default */
int		wide		= 1;		/* -w option default */
E 9
I 9
main(argc, argv)
	int argc;
D 22
	register char **argv;
E 22
I 22
	char **argv;
E 22
{
D 22
	FILE *fp;
	register char *s;
E 22
I 22
D 32
	extern int optind;
E 32
	int ch;
D 32
	time_t time();
E 32
E 22
E 9

D 9
int		lf;
int		llopenerr;
E 9
I 9
D 22
	/* parse command line for (optional) arguments */
	while (*++argv && **argv == COMMAND)
		for (s = *argv + 1; *s; s++)
			switch (*s) {
			case 'b':
				unbrief = 0;
				break;
			case 'f':
				header = 0;
				break;
			case 'h':
				hack = 0;
				break;
			case 'i':
				idle = 1;
				unquick = 0;
				break;
			case 'l':
				large = 1;
				break;
			case 'm':
				match = 0;
				break;
			case 'p':
				plan = 0;
				break;
			case 'q':
				unquick = 0;
				break;
			case 's':
				small = 1;
				break;
			case 'w':
				wide = 0;
				break;
			default:
				fprintf(stderr, "Usage: finger [-bfhilmpqsw] [login1 [login2 ...] ]\n");
				exit(1);
			}
	if (unquick || idle)
		time(&tloc);
	/*
	 * *argv == 0 means no names given
	 */
	if (*argv == 0)
		doall();
	else
		donames(argv);
D 11
	print();
E 11
I 11
	if (person1)
		print();
E 22
I 22
	while ((ch = getopt(argc, argv, "lmps")) != EOF)
		switch(ch) {
		case 'l':
			lflag = 1;		/* long format */
			break;
		case 'm':
			mflag = 1;		/* force exact match of names */
			break;
		case 'p':
			pplan = 1;		/* don't show .plan/.project */
			break;
		case 's':
			sflag = 1;		/* short format */
			break;
		case '?':
		default:
			(void)fprintf(stderr,
			    "usage: finger [-lmps] [login ...]\n");
			exit(1);
		}
	argc -= optind;
	argv += optind;

	(void)time(&now);
	setpassent(1);
	if (!*argv) {
		/*
		 * Assign explicit "small" format if no names given and -l
		 * not selected.  Force the -s BEFORE we get names so proper
		 * screening will be done.
		 */
		if (!lflag)
			sflag = 1;	/* if -l not explicit, force -s */
		loginlist();
D 23
		if (!head)
E 23
I 23
		if (entries == 0)
E 23
			(void)printf("No one logged on.\n");
	} else {
D 26
		userlist(argv);
E 26
I 26
		userlist(argc, argv);
E 26
		/*
		 * Assign explicit "large" format if names given and -s not
		 * explicitly stated.  Force the -l AFTER we get names so any
		 * remote finger attempts specified won't be mishandled.
		 */
		if (!sflag)
			lflag = 1;	/* if -s not explicit, force -l */
	}
D 23
	if (head) {
E 23
I 23
D 33
	if (entries != 0) {
E 33
I 33
	if (entries)
E 33
E 23
		if (lflag)
			lflag_print();
		else
			sflag_print();
D 33
	}
E 33
E 22
E 11
D 37
	exit(0);
E 37
I 37
	return (0);
E 37
}
E 9

I 32
static void
E 32
D 9
long		tloc;				/* current time */



main( argc, argv )

    int		argc;
    char	*argv[];

E 9
I 9
D 22
doall()
E 22
I 22
loginlist()
E 22
E 9
{
D 9
	FILE			*fp,  *fopen();		/* for plans */
	struct  passwd		*getpwent();		/* read /etc/passwd */
	struct  person		*person1,  *p,  *pend;	/* people */
	struct  passwd		*pw;			/* temporary */
	struct  utmp		user;			/*   ditto   */
	char			*malloc();
	char			*s,  *pn,  *ln;
	char			c;
	char			*PLAN = "/.plan";	/* what plan file is */
	char			*PROJ = "/.project";	/* what project file */
	int			PLANLEN = strlen( PLAN );
	int			PROJLEN = strlen( PROJ );
	int			numnames = 0;
	int			orgnumnames;
	int			uf;
	int			usize = sizeof user;
	int			unshort;
	int			i, j;
	int			fngrlogin;
E 9
I 9
D 22
	register struct person *p;
	register struct passwd *pw;
	int uf;
	char name[NMAX + 1];
E 22
I 22
	register PERSON *pn;
I 33
	DBT data, key;
E 33
D 26
	register int fd;
E 26
I 26
D 27
	FILE *fp;
E 27
E 26
	struct passwd *pw;
D 23
	char name[UT_NAMESIZE + 1], *strdup(), *malloc();
E 23
I 23
	struct utmp user;
I 33
	int r, sflag;
E 33
	char name[UT_NAMESIZE + 1];
E 23
E 22
E 9

D 8
	setbuf( stdout, outbuf );			/* buffer output */

    /*  parse command line for (optional) arguments */
E 8
I 8
D 9
	/*  parse command line for (optional) arguments */
E 8

	i = 1;
	if(  strcmp( *argv, "sh" )  )  {
	    fngrlogin = 0;
	    while( i++ < argc  &&  (*++argv)[0] == COMMAND )  {
		for( s = argv[0] + 1; *s != NULL; s++ )  {
			switch  (*s)  {

			    case 'b':
				    unbrief = 0;
				    break;

			    case 'f':
				    header = 0;
				    break;

			    case 'h':
				    hack = 0;
				    break;

			    case 'i':
				    idle = 1;
				    unquick = 0;
				    break;

			    case 'l':
				    large = 1;
				    break;

			    case 'm':
				    match = 0;
				    break;

			    case 'p':
				    plan = 0;
				    break;

			    case 'q':
				    unquick = 0;
				    break;

			    case 's':
				    small = 1;
				    break;

			    case 'w':
				    wide = 0;
				    break;

			    default:
				fprintf( stderr, "finger: Usage -- 'finger [-bfhilmpqsw] [login1 [login2 ...] ]'\n" );
				exit( 1 );
			}
		}
	    }
E 9
I 9
D 22
	unshort = large;
D 21
	if ((uf = open(USERLOG, 0)) < 0) {
		fprintf(stderr, "finger: error opening %s\n", USERLOG);
E 21
I 21
	if ((uf = open(_PATH_UTMP, 0)) < 0) {
		fprintf(stderr, "finger: error opening %s\n", _PATH_UTMP);
E 22
I 22
D 26
	if ((fd = open(_PATH_UTMP, O_RDONLY, 0)) < 0) {
E 26
I 26
D 27
	if ((fp = fopen(_PATH_UTMP, "r")) == NULL) {
E 27
I 27
D 32
	if (!freopen(_PATH_UTMP, "r", stdin)) {
E 27
E 26
		(void)fprintf(stderr, "finger: can't read %s.\n", _PATH_UTMP);
E 22
E 21
		exit(2);
E 9
	}
E 32
I 32
	if (!freopen(_PATH_UTMP, "r", stdin))
D 37
		err("%s: %s", _PATH_UTMP, strerror(errno));
E 37
I 37
		err(1, "%s", _PATH_UTMP);
E 37
E 32
D 9
	else  {
	    fngrlogin = 1;
	}
	if( unquick )  {
	    time( &tloc );
	}
	else  {
	    if( idle )  {
		time( &tloc );
	    }
	}
E 9
I 9
D 22
	if (unquick) {
D 21
		extern _pw_stayopen;
E 21
E 9

D 9
    /*  i > argc means no login names given so get them by reading USERLOG */

	if(  (i > argc)  ||  fngrlogin  )  {
	    unshort = large;
	    if(  ( uf = open(USERLOG, 0) ) >= 0  )  {
		user.ut_name[0] = NULL;
		while( user.ut_name[0] == NULL )  {
		    if( read( uf, (char *) &user, usize ) != usize )  {
D 6
			printf( "\nNo one logged on\n" );
E 6
I 6
			printf( "No one logged on\n" );
E 6
			exit( 0 );
		    }
		}
		person1 = (struct person  *) malloc( persize );
		for( j = 0; j < NMAX; j++ )  {
		    person1->tty[j] = user.ut_line[j];
		    person1->name[j] = user.ut_name[j];
		}
		person1->name[NMAX] = NULL;
		person1->tty[NMAX] = NULL;
		person1->loginat = user.ut_time;
		person1->pwd = NILPWD;
		person1->loggedin = 1;
		numnames++;
		p = person1;
		while( read( uf, (char *) &user, usize ) == usize )  {
		    if( user.ut_name[0] == NULL )  continue;
		    p->link = (struct person  *) malloc( persize );
		    p = p->link;
		    for( j = 0; j < NMAX; j++ )  {
			p->tty[j] = user.ut_line[j];
			p->name[j] = user.ut_name[j];
		    }
		    p->name[NMAX] = NULL;
		    p->tty[NMAX] = NULL;
		    p->loginat = user.ut_time;
		    p->pwd = NILPWD;
		    p->loggedin = 1;
		    numnames++;
		}
		p->link = NILPERS;
		close( uf );
	    }
	    else  {
		fprintf( stderr, "finger: error opening %s\n", USERLOG );
		exit( 2 );
	    }

		/*  if we are doing it, read /etc/passwd for the useful info */

	    if( unquick )  {
E 9
		setpwent();
I 9
D 21
		_pw_stayopen = 1;
E 21
E 9
		fwopen();
D 9
		i = numnames;
		while(  ( (pw = getpwent()) != NILPWD )  &&  ( i > 0 )  )  {
		    p = person1;
		    do  {
			if( p->pwd == NILPWD )  {
			    if(  strcmp( p->name, pw->pw_name ) == 0  )  {
				p->pwd = (struct passwd  *) malloc( pwdsize );
				pwdcopy( p->pwd, pw );
				decode( p );
				i--;
			    }
			}
E 9
I 9
	}
	while (read(uf, (char *)&user, sizeof user) == sizeof user) {
		if (user.ut_name[0] == 0)
E 22
I 22
	name[UT_NAMESIZE] = NULL;
D 23
	while(read(fd, (char *)&user, sizeof(user)) == sizeof(user)) {
E 23
I 23
D 26
	while (read(fd, (char *)&user, sizeof(user)) == sizeof(user)) {
E 26
I 26
D 27
	while (fread((char *)&user, sizeof(user), 1, fp) == 1) {
E 27
I 27
	while (fread((char *)&user, sizeof(user), 1, stdin) == 1) {
E 27
E 26
E 23
		if (!user.ut_name[0])
E 22
			continue;
D 22
		if (person1 == 0)
			p = person1 = (struct person *) malloc(sizeof *p);
		else {
			p->link = (struct person *) malloc(sizeof *p);
E 9
			p = p->link;
E 22
I 22
D 23
		bcopy(user.ut_name, name, UT_NAMESIZE);
		if (!(pw = getpwnam(name)))
			continue;
		if (!(pn = (PERSON *)malloc((u_int)sizeof(PERSON)))) {
			(void)fprintf(stderr, "finger: out of space.\n");
			exit(1);
E 23
I 23
		if ((pn = find_person(user.ut_name)) == NULL) {
			bcopy(user.ut_name, name, UT_NAMESIZE);
			if ((pw = getpwnam(name)) == NULL)
				continue;
			pn = enter_person(pw);
E 23
E 22
D 9
		    }  while( p != NILPERS );
E 9
		}
I 9
D 22
		bcopy(user.ut_name, name, NMAX);
		name[NMAX] = 0;
		bcopy(user.ut_line, p->tty, LMAX);
		p->tty[LMAX] = 0;
		bcopy(user.ut_host, p->host, HMAX);
		p->host[HMAX] = 0;
		p->loginat = user.ut_time;
		p->pwd = 0;
		p->loggedin = 1;
		if (unquick && (pw = getpwnam(name))) {
			p->pwd = pwdcopy(pw);
			decode(p);
			p->name = p->pwd->pw_name;
		} else
			p->name = strcpy(malloc(strlen(name) + 1), name);
E 22
I 22
D 23
		++entries;
		pn->next = head;
		head = pn;
		utcopy(&user, pn);
		userinfo(pn, pw);
		find_idle_and_ttywrite(pn);
		pn->info = LOGGEDIN;
E 23
I 23
		enter_where(&user, pn);
E 23
E 22
	}
D 22
	if (unquick) {
E 9
		fwclose();
		endpwent();
D 9
	    }
E 9
	}
D 9

    /* get names from command line and check to see if they're  logged in */

	else  {
	    unshort = ( small == 1 ? 0 : 1 );
D 6
	    i++;
E 6
I 6
	    while (i <= argc && netfinger(*argv)) {
		i++;
		argv++;
	    }
	    if (i++ > argc)
E 9
I 9
	close(uf);
	if (person1 == 0) {
		printf("No one logged on\n");
E 9
D 11
		exit(0);
E 11
I 11
		return;
E 11
E 6
D 9
	    person1 = (struct person  *) malloc( persize );
	    strcpy(  person1->name, (argv++)[ 0 ]  );
	    person1->loggedin = 0;
	    person1->pwd = NILPWD;
	    numnames++;
	    p = person1;
	    while( i++ <= argc )  {
I 6
		if (netfinger(*argv)) {
		    argv++;
		    continue;
		}
E 6
		p->link = (struct person  *) malloc( persize );
		p = p->link;
		strcpy(  p->name, (argv++)[ 0 ]  );
		p->loggedin = 0;
		p->pwd = NILPWD;
		numnames++;
	    }
	    p->link = NILPERS;
	    pend = p;
E 9
I 9
	}
	p->link = 0;
E 22
I 22
D 26
	(void)close(fd);
E 26
I 26
D 27
	(void)fclose(fp);
E 27
E 26
I 23
D 33
	for (pn = phead; lflag && pn != NULL; pn = pn->next)
		enter_lastlog(pn);
E 33
I 33
	if (db && lflag)
		for (sflag = R_FIRST;; sflag = R_NEXT) {
I 37
			PERSON *tmp;

E 37
			r = (*db->seq)(db, &key, &data, sflag);
			if (r == -1)
D 37
				err("db seq: %s", strerror(errno));
E 37
I 37
				err(1, "db seq");
E 37
			if (r == 1)
				break;
D 37
			enter_lastlog(*(PERSON **)data.data);
E 37
I 37
D 38
			memcpy(&tmp, data.data, sizeof tmp);
E 38
I 38
			memmove(&tmp, data.data, sizeof tmp);
E 38
			enter_lastlog(tmp);
E 37
		}
E 33
E 23
E 22
}
E 9

I 32
static void
E 32
D 9
		/*  if we are doing it, read /etc/passwd for the useful info */
E 9
I 9
D 22
donames(argv)
E 22
I 22
D 26
#define	ARGIGNORE	(char *)0x01
I 25

E 25
userlist(argv)
E 22
	char **argv;
E 26
I 26
userlist(argc, argv)
D 32
	register argc;
E 32
I 32
	register int argc;
E 32
	register char **argv;
E 26
{
D 22
	register struct person *p;
E 22
I 22
D 23
	register PERSON *nethead, *p, *pn;
E 22
	register struct passwd *pw;
D 22
	int uf;
E 22
I 22
	register char **a1, **a2;
	int fd, dolocal, nelem;
	char **sargv, **arglist, *malloc(), *rindex(), *strcpy();
E 23
I 23
D 26
	register char **ap;
E 26
I 26
D 32
	register i;
E 32
I 32
D 33
	register int i;
E 33
E 32
E 26
	register PERSON *pn;
D 31
	PERSON *nethead;
E 31
I 31
D 33
	PERSON *nethead, **nettail;
E 33
I 33
	DBT data, key;
E 33
E 31
	struct utmp user;
	struct passwd *pw;
D 25
	int fd, dolocal, *index();
E 25
I 25
D 26
	int fd, dolocal, *used, *index();
E 26
I 26
D 33
	int dolocal, *used;
E 33
I 33
	int r, sflag, *used, *ip;
	char **ap, **nargv, **np, **p;
E 33
D 27
	FILE *fp;
E 27
D 32
	char *index();
E 32
E 26
E 25
E 23
E 22
E 9

I 26
D 32
	if (!(used = (int *)calloc((u_int)argc, (u_int)sizeof(int)))) {
		(void)fprintf(stderr, "finger: out of space.\n");
		exit(1);
	}
E 32
I 32
D 33
	if (!(used = calloc((u_int)argc, (u_int)sizeof(int))))
E 33
I 33
D 36
	if ((nargv = malloc(argc * sizeof(char *))) == NULL ||
E 36
I 36
	if ((nargv = malloc((argc+1) * sizeof(char *))) == NULL ||
E 36
	    (used = calloc(argc, sizeof(int))) == NULL)
E 33
D 37
		err("%s", strerror(errno));
E 37
I 37
		err(1, NULL);
E 37
E 32

E 26
D 9
	    orgnumnames = numnames;
	    if( unquick )  {
		setpwent();
		while(  ( pw = getpwent() ) != NILPWD  )  {
		    p = person1;
		    i = 0;
		    do  {
			if( strcmp( p->name, pw->pw_name ) == 0    ||
			    matchcmp( pw->pw_gecos, pw->pw_name, p->name ) )  {
			    if( p->pwd == NILPWD )  {
				p->pwd = (struct passwd  *) malloc( pwdsize );
				pwdcopy( p->pwd, pw );
			    }
			    else  {	/* handle multiple logins -- append new
					   "duplicate" entry to end of list */
				pend->link = (struct person  *) malloc(persize);
				pend = pend->link;
				pend->link = NILPERS;
				strcpy( pend->name, p->name );
				pend->pwd = (struct passwd  *) malloc(pwdsize);
				pwdcopy( pend->pwd, pw );
				numnames++;
			    }
			}
E 9
I 9
D 22
	/*
	 * get names from command line and check to see if they're
	 * logged in
	 */
	unshort = !small;
	for (; *argv != 0; argv++) {
		if (netfinger(*argv))
E 22
I 22
D 23
	/* suppress duplicates while it's still easy */
	for (a1 = argv; *a1; ++a1)
		for (a2 = a1 + 1; *a2; ++a2)
			if (!strcasecmp(*a1, *a2)) {
				*a1 = ARGIGNORE;
				break;
			}

E 23
D 33
	/* pull out all network requests */
D 23
	for (sargv = argv, dolocal = 0, nethead = NULL; *argv; ++argv) {
		if (!index(*argv, '@')) {
E 23
I 23
D 25
	for (ap = argv, dolocal = 0, nethead = NULL; *ap != NULL; ap++) {
E 25
I 25
D 26
	for (ap = argv, dolocal = 0, nethead = NULL; *ap; ap++) {
E 25
		if (!index(*ap, '@')) {
E 26
I 26
D 31
	for (i = 0, dolocal = 0, nethead = NULL; i < argc; i++) {
E 31
I 31
	for (i = 0, dolocal = 0, nettail = &nethead; i < argc; i++) {
E 31
		if (!index(argv[i], '@')) {
E 26
E 23
			dolocal = 1;
E 22
			continue;
D 22
		if (person1 == 0)
			p = person1 = (struct person *) malloc(sizeof *p);
		else {
			p->link = (struct person *) malloc(sizeof *p);
E 9
			p = p->link;
E 22
D 9
		    }  while( ++i < orgnumnames );
E 9
		}
D 9
		endpwent();
	    }
E 9
I 9
D 22
		p->name = *argv;
		p->loggedin = 0;
		p->original = 1;
		p->pwd = 0;
E 22
I 22
D 23
		if (!(pn = (PERSON *)malloc((u_int)sizeof(PERSON)))) {
			(void)fprintf(stderr, "finger: out of space.\n");
			exit(1);
		}
E 23
I 23
		pn = palloc();
E 23
D 31
		pn->next = nethead;
		nethead = pn;
E 31
I 31
		*nettail = pn;
		nettail = &pn->next;
E 31
D 23
		pn->name = *argv;
		*argv = ARGIGNORE;
E 23
I 23
D 26
		pn->name = *ap;
		*ap = ARGIGNORE;
E 26
I 26
		pn->name = argv[i];
		used[i] = -1;
E 26
E 23
E 22
	}
I 31
	*nettail = NULL;
E 33
I 33
	/* Pull out all network requests. */
	for (ap = p = argv, np = nargv; *p; ++p)
		if (index(*p, '@'))
			*np++ = *p;
		else
			*ap++ = *p;
E 33
E 31
I 11
D 22
	if (person1 == 0)
		return;
E 11
	p->link = 0;
E 22
I 22

D 33
	if (!dolocal)
E 33
I 33
	*np++ = NULL;
	*ap++ = NULL;

	if (!*argv)
E 33
		goto net;

I 25
D 26
	if (!(used = (int *)calloc((u_int)(ap - argv), (u_int)sizeof(int)))) {
		(void)fprintf(stderr, "finger: out of space.\n");
		exit(1);
	}

E 26
E 25
E 22
	/*
D 22
	 * if we are doing it, read /etc/passwd for the useful info
E 22
I 22
D 33
	 * traverse the list of possible login names and check the login name
E 33
I 33
	 * Traverse the list of possible login names and check the login name
E 33
D 23
	 * and real name against the name specified by the user.  Possible
	 * speedup would be to use getpwnam(3) if mflag set -- maybe not
	 * worthwhile, given that the default is the mflag off.
E 23
I 23
	 * and real name against the name specified by the user.
E 23
E 22
	 */
D 22
	if (unquick) {
		setpwent();
		if (!match) {
D 21
			extern _pw_stayopen;
E 9

D 9
		/*  Now get login information */

	    if(  ( uf = open(USERLOG, 0) ) >= 0  )  {
		while( read( uf, (char *) &user, usize ) == usize )  {
		    if( user.ut_name[0] == NULL )  continue;
		    p = person1;
		    do  {
			pw = p->pwd;
			if( pw == NILPWD )  {
			    i = ( strcmp( p->name, user.ut_name ) ? 0 : NMAX );
			}
			else  {
			    i = 0;
			    while(  (i < NMAX)  &&
				    ( pw->pw_name[i] == user.ut_name[i])  )  {
				if( pw->pw_name[i] == NULL )  {
				    i = NMAX;
				    break;
E 9
I 9
			_pw_stayopen = 1;
E 21
			for (p = person1; p != 0; p = p->link)
				if (pw = getpwnam(p->name))
					p->pwd = pwdcopy(pw);
		} else while ((pw = getpwent()) != 0) {
			for (p = person1; p != 0; p = p->link) {
				if (!p->original)
					continue;
				if (strcmp(p->name, pw->pw_name) != 0 &&
				    !matchcmp(pw->pw_gecos, pw->pw_name, p->name))
					continue;
				if (p->pwd == 0)
					p->pwd = pwdcopy(pw);
				else {
					struct person *new;
					/*
					 * handle multiple login names, insert
					 * new "duplicate" entry behind
					 */
					new = (struct person *)
						malloc(sizeof *new);
					new->pwd = pwdcopy(pw);
					new->name = p->name;
					new->original = 1;
					new->loggedin = 0;
					new->link = p->link;
					p->original = 0;
					p->link = new;
					p = new;
E 9
				}
D 9
				i++;
			    }
E 9
			}
D 9
			if( i == NMAX )  {
			    if( p->loggedin == 1 )  {
				pend->link = (struct person  *) malloc(persize);
				pend = pend->link;
				pend->link = NILPERS;
				strcpy( pend->name, p->name );
				for( j = 0; j < NMAX; j++ )  {
				    pend->tty[j] = user.ut_line[j];
				}
				pend->tty[ NMAX ] = NULL;
				pend->loginat = user.ut_time;
				pend->loggedin = 2;
				if(  pw == NILPWD  )  {
				    pend ->pwd = NILPWD;
				}
				else  {
				    pend->pwd = (struct passwd  *) malloc(pwdsize);
				    pwdcopy( pend->pwd, pw );
				}
				numnames++;
			    }
			    else  {
				if( p->loggedin != 2 )  {
				    for( j = 0; j < NMAX; j++ )  {
					p->tty[j] = user.ut_line[j];
				    }
				    p->tty[ NMAX ] = NULL;
				    p->loginat = user.ut_time;
				    p->loggedin = 1;
				}
			    }
			}
			p = p->link;
		    }  while( p != NILPERS );
E 9
		}
D 9
		fwopen();
		p = person1;
		while( p != NILPERS )  {
		    if( p->loggedin == 2 )  {
			p->loggedin = 1;
		    }
		    decode( p );
		    p = p->link;
E 9
I 9
		endpwent();
E 22
I 22
D 23
	nelem = argv - sargv + 1;
	if (!(arglist =
	    (char **)malloc((u_int)(nelem * sizeof(char *))))) {
		(void)fprintf(stderr, "finger: out of space.\n");
		exit(1);
E 22
	}
D 22
	/* Now get login information */
D 21
	if ((uf = open(USERLOG, 0)) < 0) {
		fprintf(stderr, "finger: error opening %s\n", USERLOG);
E 21
I 21
	if ((uf = open(_PATH_UTMP, 0)) < 0) {
		fprintf(stderr, "finger: error opening %s\n", _PATH_UTMP);
E 21
		exit(2);
	}
	while (read(uf, (char *)&user, sizeof user) == sizeof user) {
		if (*user.ut_name == 0)
			continue;
		for (p = person1; p != 0; p = p->link) {
			if (p->loggedin == 2)
E 22
I 22
	bcopy((char *)sargv, (char *)arglist, nelem * sizeof(char *));
	while (pw = getpwent()) {
		for (argv = sargv; *argv; ++argv) {
			if (*argv == ARGIGNORE)
E 23
I 23
D 25
	if (mflag)
		for (ap = argv; *ap != NULL; ap++) {
			if (*ap == ARGIGNORE)
E 23
E 22
				continue;
D 22
			if (strncmp(p->pwd ? p->pwd->pw_name : p->name,
				    user.ut_name, NMAX) != 0)
E 22
I 22
D 23
			if (strcasecmp(pw->pw_name, *argv) &&
			    (mflag || !match(pw, *argv)))
E 23
I 23
			if ((pw = getpwnam(*ap)) == NULL)
E 23
E 22
				continue;
D 22
			if (p->loggedin == 0) {
				bcopy(user.ut_line, p->tty, LMAX);
				p->tty[LMAX] = 0;
				bcopy(user.ut_host, p->host, HMAX);
				p->host[HMAX] = 0;
				p->loginat = user.ut_time;
				p->loggedin = 1;
			} else {	/* p->loggedin == 1 */
				struct person *new;
				new = (struct person *) malloc(sizeof *new);
				new->name = p->name;
				bcopy(user.ut_line, new->tty, LMAX);
				new->tty[LMAX] = 0;
				bcopy(user.ut_host, new->host, HMAX);
				new->host[HMAX] = 0;
				new->loginat = user.ut_time;
				new->pwd = p->pwd;
				new->loggedin = 1;
				new->original = 0;
				new->link = p->link;
				p->loggedin = 2;
				p->link = new;
				p = new;
E 22
I 22
D 23
			if (!(pn = (PERSON *)malloc((u_int)sizeof(PERSON)))) {
				(void)fprintf(stderr,
				    "finger: out of space.\n");
				exit(1);
E 22
			}
I 22
			++entries;
			pn->next = head;
			head = pn;
			userinfo(pn, pw);
			pn->info = FOUND;
			arglist[argv - sargv] = ARGIGNORE;
E 23
I 23
			enter_person(pw);
			*ap = ARGIGNORE;
		}
	else while (pw = getpwent())
		for (ap = argv; *ap != NULL; ap++) {
			if (*ap == ARGIGNORE)
				continue;
			if (strcasecmp(pw->pw_name, *ap) && !match(pw, *ap))
				continue;
			enter_person(pw);
			*ap = ARGIGNORE;
E 23
			/* don't break, may be listed multiple times */
E 22
E 9
		}
E 25
I 25
D 33
	if (mflag) {
D 26
		for (ap = argv; *ap; ap++)
			if (*ap != ARGIGNORE && (pw = getpwnam(*ap))) {
E 26
I 26
		for (i = 0; i < argc; i++)
			if (used[i] >= 0 && (pw = getpwnam(argv[i]))) {
E 33
I 33
	if (mflag)
		for (p = argv; *p; ++p)
D 37
			if (pw = getpwnam(*p))
E 37
I 37
			if ((pw = getpwnam(*p)) != NULL)
E 37
E 33
E 26
				enter_person(pw);
D 26
				used[ap - argv] = 1;
E 26
I 26
D 33
				used[i] = 1;
E 26
			}
	} else while (pw = getpwent())
D 26
		for (ap = argv; *ap; ap++)
			if (*ap != ARGIGNORE &&
			    (!strcasecmp(pw->pw_name, *ap) || match(pw, *ap))) {
E 26
I 26
		for (i = 0; i < argc; i++)
			if (used[i] >= 0 &&
			    (!strcasecmp(pw->pw_name, argv[i]) ||
			    match(pw, argv[i]))) {
E 26
				enter_person(pw);
D 26
				used[ap - argv] = 1;
E 26
I 26
				used[i] = 1;
E 26
			}
E 25
I 9
D 23
	}
E 23
D 22
	close(uf);
	if (unquick) {
		fwopen();
		for (p = person1; p != 0; p = p->link)
			decode(p);
E 9
		fwclose();
E 22
I 22

	/* list errors */
D 23
	for (; *arglist; ++arglist)
		if (*arglist != ARGIGNORE)
E 23
I 23
D 25
	for (ap = argv; *ap != NULL; ap++)
		if (*ap != ARGIGNORE)
E 25
I 25
D 26
	for (ap = argv; *ap; ap++)
		if (*ap != ARGIGNORE && !used[ap - argv])
E 26
I 26
	for (i = 0; i < argc; i++)
		if (!used[i])
E 26
E 25
E 23
			(void)fprintf(stderr,
D 23
			    "finger: %s: no such user.\n", *arglist);
E 23
I 23
D 26
			    "finger: %s: no such user.\n", *ap);
E 26
I 26
			    "finger: %s: no such user.\n", argv[i]);
E 26
E 23

	/* handle network requests */
net:	for (pn = nethead; pn; pn = pn->next) {
		netfinger(pn->name);
		if (pn->next || entries)
			putchar('\n');
E 33
I 33
			else
				(void)fprintf(stderr,
				    "finger: %s: no such user\n", *p);
	else {
D 37
		while (pw = getpwent())
E 37
I 37
		while ((pw = getpwent()) != NULL)
E 37
			for (p = argv, ip = used; *p; ++p, ++ip)
D 34
				if (!*ip && (!strcasecmp(pw->pw_name, *p) ||
				    match(pw, *p))) {
E 34
I 34
				if (match(pw, *p)) {
E 34
					enter_person(pw);
					*ip = 1;
				}
		for (p = argv, ip = used; *p; ++p, ++ip)
			if (!*ip)
				(void)fprintf(stderr,
				    "finger: %s: no such user\n", *p);
E 33
E 22
D 9
		close( uf );
	    }
	    else  {
		fprintf( stderr, "finger: error opening %s\n", USERLOG );
		exit( 2 );
	    }
E 9
	}
I 9
D 22
}
E 22
E 9

I 33
	/* Handle network requests. */
net:	for (p = nargv; *p;)
		netfinger(*p++);

E 33
D 9
    /* print out what we got */
E 9
I 9
D 22
print()
{
	register FILE *fp;
	register struct person *p;
	register char *s;
	register c;
E 22
I 22
D 23
	if (!head)
E 23
I 23
	if (entries == 0)
E 23
		return;
E 22
E 9

D 9
	if( header )  {
	    if( unquick )  {
		if( !unshort )  {
		    if( wide )  {
			printf(
"Login       Name              TTY Idle    When            Office\n" );
		    }
		    else  {
			printf(
"Login    TTY Idle    When            Office\n" );
		    }
E 9
I 9
	/*
D 22
	 * print out what we got
E 22
I 22
	 * Scan thru the list of users currently logged in, saving
	 * appropriate data whenever a match occurs.
E 22
	 */
D 22
	if (header) {
		if (unquick) {
			if (!unshort)
				if (wide)
					printf("Login       Name              TTY Idle    When            Office\n");
				else
					printf("Login    TTY Idle    When            Office\n");
		} else {
			printf("Login      TTY            When");
			if (idle)
				printf("             Idle");
			putchar('\n');
E 9
		}
E 22
I 22
D 26
	if ((fd = open(_PATH_UTMP, O_RDONLY, 0)) < 0) {
E 26
I 26
D 27
	if ((fp = fopen(_PATH_UTMP, "r")) == NULL) {
E 27
I 27
D 32
	if (!freopen(_PATH_UTMP, "r", stdin)) {
E 27
E 26
		(void)fprintf( stderr, "finger: can't read %s.\n", _PATH_UTMP);
		exit(1);
E 22
D 9
	    }
	    else  {
		printf( "Login      TTY            When" );
		if( idle )  {
		    printf( "             Idle" );
		}
		printf( "\n" );
	    }
E 9
	}
E 32
I 32
	if (!freopen(_PATH_UTMP, "r", stdin))
D 37
		err("%s: %s", _PATH_UTMP, strerror(errno));
E 37
I 37
		err(1, "%s", _PATH_UTMP);
E 37
E 32
D 9
	p = person1;
	do  {
	    if( unquick )  {
		if( unshort )  {
		    personprint( p );
		    if( p->pwd != NILPWD )  {
			if( hack )  {
			    s = malloc(strlen((p->pwd)->pw_dir) + PROJLEN + 1 );
			    strcpy(  s, (p->pwd)->pw_dir  );
			    strcat( s, PROJ );
			    if(  ( fp = fopen( s, "r") )  != NULL  )  {
				printf( "Project: " );
				while(  ( c = getc(fp) )  !=  EOF  )  {
				    if( c == LINEBREAK )  {
					break;
				    }
				    putc( c, stdout );
E 9
I 9
D 22
	for (p = person1; p != 0; p = p->link) {
		if (!unquick) {
			quickprint(p);
E 22
I 22
D 26
	while (read(fd, (char *)&user, sizeof(user)) == sizeof(user)) {
E 26
I 26
D 27
	while (fread((char *)&user, sizeof(user), 1, fp) == 1) {
E 27
I 27
	while (fread((char *)&user, sizeof(user), 1, stdin) == 1) {
E 27
E 26
		if (!user.ut_name[0])
E 22
			continue;
D 22
		}
		if (!unshort) {
			shortprint(p);
			continue;
		}
		personprint(p);
		if (p->pwd != 0) {
			if (hack) {
				s = malloc(strlen(p->pwd->pw_dir) +
					sizeof PROJ);
				strcpy(s, p->pwd->pw_dir);
				strcat(s, PROJ);
				if ((fp = fopen(s, "r")) != 0) {
					printf("Project: ");
					while ((c = getc(fp)) != EOF) {
						if (c == '\n')
							break;
D 16
						putchar(c);
E 16
I 16
						if (isprint(c) || isspace(c))
							putchar(c);
						else
							putchar(c ^ 100);
E 16
					}
					fclose(fp);
					putchar('\n');
E 22
I 22
D 23
		for (pn = head; pn; pn = pn->next) {
			if (strncasecmp(pn->name, user.ut_name, UT_NAMESIZE))
				continue;
			if (pn->info == LOGGEDIN) {
				if (!(p =
				    (PERSON *)malloc((u_int)sizeof(PERSON)))) {
					(void)fprintf(stderr,
					    "finger: out of space.\n");
					exit(1);
E 22
E 9
				}
D 9
				fclose( fp );
				printf( "\n" );
			    }
E 9
I 9
D 22
				free(s);
E 22
I 22
				++entries;
				p->name = pn->name;
				(void)strcpy(p->tty, pn->tty);
				/* link in so finds `real' entry first! */
				p->next = pn->next;
				pn->next = p;
				pn = p;
E 22
E 9
			}
D 9
			if( plan )  {
			    s = malloc( strlen( (p->pwd)->pw_dir ) + PLANLEN + 1 );
			    strcpy(  s, (p->pwd)->pw_dir  );
			    strcat( s, PLAN );
			    if(  ( fp = fopen( s, "r") )  == NULL  )  {
				printf( "No Plan.\n" );
			    }
			    else  {
				printf( "Plan:\n" );
				while(  ( c = getc(fp) )  !=  EOF  )  {
				    putc( c, stdout );
E 9
I 9
D 22
			if (plan) {
				s = malloc(strlen(p->pwd->pw_dir) +
					sizeof PLAN);
				strcpy(s, p->pwd->pw_dir);
				strcat(s, PLAN);
				if ((fp = fopen(s, "r")) == 0)
					printf("No Plan.\n");
				else {
					printf("Plan:\n");
					while ((c = getc(fp)) != EOF)
D 16
						putchar(c);
E 16
I 16
						if (isprint(c) || isspace(c))
							putchar(c);
						else
							putchar(c ^ 100);
E 16
					fclose(fp);
E 9
				}
D 9
				fclose( fp );
			    }
E 9
I 9
				free(s);
E 9
			}
E 22
I 22
			pn->info = LOGGEDIN;
			utcopy(&user, pn);
			find_idle_and_ttywrite(pn);
			/* don't break, may be listed multiple times... */
E 22
D 9
		    }
		    if( p->link != NILPERS )  {
			printf( "\n" );
		    }
E 9
		}
E 23
I 23
		if ((pn = find_person(user.ut_name)) == NULL)
			continue;
		enter_where(&user, pn);
E 23
D 9
		else  {
		    shortprint( p );
		}
	    }
	    else  {
		quickprint( p );
	    }
	    p = p->link;
	}  while( p != NILPERS );
	exit(0);
E 9
I 9
D 22
		if (p->link != 0)
			putchar('\n');
E 22
	}
E 9
D 22
}

D 9

/*  given a pointer to a pwd (pfrom) copy it to another one, allocating
 *  space for all the stuff in it.  Note: Only the useful (what the
 *  program currently uses) things are copied.
E 9
I 9
/*
 * Duplicate a pwd entry.
 * Note: Only the useful things (what the program currently uses) are copied.
E 9
 */
D 9

pwdcopy( pto, pfrom )		/* copy relevant fields only */

    struct  passwd		*pto,  *pfrom;
E 9
I 9
struct passwd *
pwdcopy(pfrom)
	register struct passwd *pfrom;
E 9
{
D 9
	pto->pw_name = malloc(  strlen( pfrom->pw_name ) + 1  );
	strcpy( pto->pw_name, pfrom->pw_name );
E 9
I 9
	register struct passwd *pto;

	pto = (struct passwd *) malloc(sizeof *pto);
#define savestr(s) strcpy(malloc(strlen(s) + 1), s)
	pto->pw_name = savestr(pfrom->pw_name);
E 9
	pto->pw_uid = pfrom->pw_uid;
D 9
	pto->pw_gecos = malloc(  strlen( pfrom->pw_gecos ) + 1  );
	strcpy( pto->pw_gecos, pfrom->pw_gecos );
	pto->pw_dir = malloc(  strlen( pfrom->pw_dir ) + 1  );
	strcpy( pto->pw_dir, pfrom->pw_dir );
	pto->pw_shell = malloc(  strlen( pfrom->pw_shell ) + 1  );
	strcpy( pto->pw_shell, pfrom->pw_shell );
E 9
I 9
	pto->pw_gecos = savestr(pfrom->pw_gecos);
	pto->pw_dir = savestr(pfrom->pw_dir);
	pto->pw_shell = savestr(pfrom->pw_shell);
#undef savestr
	return pto;
E 9
}

D 9

/*  print out information on quick format giving just name, tty, login time
 *  and idle time if idle is set.
E 9
I 9
/*
 * print out information on quick format giving just name, tty, login time
 * and idle time if idle is set.
E 9
 */
D 9

quickprint( pers )

    struct  person		*pers;
E 9
I 9
quickprint(pers)
	register struct person *pers;
E 9
{
D 9
	int			idleprinted;

	printf( "%-*.*s", NMAX, NMAX, pers->name );
	printf( "  " );
	if( pers->loggedin )  {
	    if( idle )  {
		findidle( pers );
		if( pers->writeable )  {
		    printf(  " %-*.*s %-16.16s", LMAX, LMAX, 
			pers->tty, ctime( &pers->loginat )  );
		}
		else  {
		    printf(  "*%-*.*s %-16.16s", LMAX, LMAX, 
			pers->tty, ctime( &pers->loginat )  );
		}
		printf( "   " );
		idleprinted = ltimeprint( &pers->idletime );
	    }
	    else  {
		printf(  " %-*.*s %-16.16s", LMAX, LMAX, 
		    pers->tty, ctime( &pers->loginat )  );
	    }
	}
	else  {
	    printf( "          Not Logged In" );
	}
	printf( "\n" );
E 9
I 9
	printf("%-*.*s  ", NMAX, NMAX, pers->name);
	if (pers->loggedin) {
		if (idle) {
			findidle(pers);
			printf("%c%-*s %-16.16s", pers->writable ? ' ' : '*',
				LMAX, pers->tty, ctime(&pers->loginat));
			ltimeprint("   ", &pers->idletime, "");
		} else
			printf(" %-*s %-16.16s", LMAX,
				pers->tty, ctime(&pers->loginat));
		putchar('\n');
	} else
		printf("          Not Logged In\n");
E 9
}

D 9

/*  print out information in short format, giving login name, full name,
 *  tty, idle time, login time, office location and phone.
E 9
I 9
/*
 * print out information in short format, giving login name, full name,
 * tty, idle time, login time, office location and phone.
E 9
 */
D 9

shortprint( pers )

    struct  person	*pers;

E 9
I 9
shortprint(pers)
	register struct person *pers;
E 9
{
D 9
	struct  passwd		*pwdt = pers->pwd;
	char			buf[ 26 ];
	int			i,  len,  offset,  dialup;
E 9
I 9
	char *p;
	char dialup;
E 9

D 9
	if( pwdt == NILPWD )  {
	    printf( "%-*.*s", NMAX, NMAX,  pers->name );
	    printf( "       ???\n" );
	    return;
E 9
I 9
	if (pers->pwd == 0) {
		printf("%-15s       ???\n", pers->name);
		return;
E 9
	}
D 9
	printf( "%-*.*s", NMAX, NMAX,  pwdt->pw_name );
E 9
I 9
	printf("%-*s", NMAX, pers->pwd->pw_name);
E 9
	dialup = 0;
D 9
	if( wide )  {
	    if(  strlen( pers->realname ) > 0  )  {
		printf( " %-20.20s", pers->realname );
	    }
	    else  {
		printf( "        ???          " );
	    }
E 9
I 9
	if (wide) {
		if (pers->realname)
			printf(" %-20.20s", pers->realname);
		else
			printf("        ???          ");
E 9
	}
D 9
	if( pers->loggedin )  {
	    if( pers->writeable )  {
		printf( "  " );
	    }
	    else  {
		printf( " *" );
	    }
	}
	else  {
	    printf( "  " );
	}
	if(  strlen( pers->tty ) > 0  )  {
	    strcpy( buf, pers->tty );
	    if(  (buf[0] == 't')  &&  (buf[1] == 't')  &&  (buf[2] == 'y')  )  {
		offset = 3;
		for( i = 0; i < 2; i++ )  {
		    buf[i] = buf[i + offset];
		}
	    }
	    if(  (buf[0] == 'd')  &&  pers->loggedin  )  {
		dialup = 1;
	    }
	    printf( "%-2.2s ", buf );
	}
	else  {
	    printf( "   " );
	}
D 2
	strcpy( buf, ctime( &pers->loginat ) );
E 2
I 2
	strcpy(buf, ctime(&pers->loginat));
E 2
	if( pers->loggedin )  {
	    stimeprint( &pers->idletime );
	    offset = 7;
	    for( i = 4; i < 19; i++ )  {
		buf[i] = buf[i + offset];
	    }
	    printf( " %-9.9s ", buf );
	}
D 2
	else  {
	    printf( " " );
	    offset = 4;
	    for( i = 0; i <22; i++ )  {
		buf[i] = buf[i + offset];
	    }
	    printf( "<%-12.12s>", buf );
	}
E 2
I 2
	else if (pers->loginat == 0)
	    printf(" < .  .  .  . >");
E 9
I 9
	putchar(' ');
	if (pers->loggedin && !pers->writable)
		putchar('*');
	else
		putchar(' ');
	if (*pers->tty) {
		if (pers->tty[0] == 't' && pers->tty[1] == 't' &&
		    pers->tty[2] == 'y') {
			if (pers->tty[3] == 'd' && pers->loggedin)
				dialup = 1;
			printf("%-2.2s ", pers->tty + 3);
		} else
			printf("%-2.2s ", pers->tty);
	} else
		printf("   ");
	p = ctime(&pers->loginat);
	if (pers->loggedin) {
		stimeprint(&pers->idletime);
		printf(" %3.3s %-5.5s ", p, p + 11);
	} else if (pers->loginat == 0)
		printf(" < .  .  .  . >");
E 9
	else if (tloc - pers->loginat >= 180 * 24 * 60 * 60)
D 9
	    printf( " <%-6.6s, %-4.4s>", buf+4, buf+20 );
E 9
I 9
		printf(" <%-6.6s, %-4.4s>", p + 4, p + 20);
E 9
	else
D 9
	    printf(" <%-12.12s>", buf+4);
E 2
	len = strlen( pers->homephone );
	if(  dialup  &&  (len > 0)  )  {
	    if( len == 8 )  {
		printf( "             " );
	    }
	    else  {
		if( len == 12 )  {
		    printf( "         " );
		}
		else {
		    for( i = 1; i <= 21 - len; i++ )  {
			printf( " " );
		    }
		}
	    }
	    printf( "%s", pers->homephone );
E 9
I 9
		printf(" <%-12.12s>", p + 4);
	if (dialup && pers->homephone)
		printf(" %20s", pers->homephone);
	else {
		if (pers->office)
			printf(" %-11.11s", pers->office);
		else if (pers->officephone || pers->homephone)
			printf("            ");
		if (pers->officephone)
			printf(" %s", pers->officephone);
		else if (pers->homephone)
			printf(" %s", pers->homephone);
E 9
	}
D 9
	else  {
	    if(  strlen( pers->office ) > 0  )  {
		printf( " %-11.11s", pers->office );
		if(  strlen( pers->officephone ) > 0  )  {
		    printf( " %8.8s", pers->officephone );
		}
		else  {
		    if( len == 8 )  {
			printf( " %8.8s", pers->homephone );
		    }
		}
	    }
	    else  {
		if(  strlen( pers->officephone ) > 0  )  {
		    printf( "             %8.8s", pers->officephone );
		}
		else  {
		    if( len == 8 )  {
			printf( "             %8.8s", pers->homephone );
		    }
		    else  {
			if( len == 12 )  {
			    printf( "         %12.12s", pers->homephone );
			}
		    }
		}
	    }
	}
	printf( "\n" );
E 9
I 9
	putchar('\n');
E 9
}

D 9

/*  print out a person in long format giving all possible information.
 *  directory and shell are inhibited if unbrief is clear.
E 9
I 9
/*
 * print out a person in long format giving all possible information.
 * directory and shell are inhibited if unbrief is clear.
E 9
 */
D 9

personprint( pers )

    struct  person	*pers;
E 9
I 9
personprint(pers)
	register struct person *pers;
E 9
{
D 9
	struct  passwd		*pwdt = pers->pwd;
	int			idleprinted;

	if( pwdt == NILPWD )  {
	    printf( "Login name: %-10s", pers->name );
	    printf( "			" );
	    printf( "In real life: ???\n");
	    return;
E 9
I 9
	if (pers->pwd == 0) {
		printf("Login name: %-10s\t\t\tIn real life: ???\n",
			pers->name);
		return;
E 9
	}
D 9
	printf( "Login name: %-10s", pwdt->pw_name );
	if( pers->loggedin )  {
	    if( pers->writeable )  {
		printf( "			" );
	    }
	    else  {
		printf( "	(messages off)	" );
	    }
E 9
I 9
	printf("Login name: %-10s", pers->pwd->pw_name);
	if (pers->loggedin && !pers->writable)
		printf("	(messages off)	");
	else
		printf("			");
	if (pers->realname)
		printf("In real life: %s", pers->realname);
	if (pers->office) {
		printf("\nOffice: %-.11s", pers->office);
		if (pers->officephone) {
			printf(", %s", pers->officephone);
			if (pers->homephone)
				printf("\t\tHome phone: %s", pers->homephone);
			else if (pers->random)
				printf("\t\t%s", pers->random);
		} else
			if (pers->homephone)
				printf("\t\t\tHome phone: %s", pers->homephone);
			else if (pers->random)
				printf("\t\t\t%s", pers->random);
	} else if (pers->officephone) {
		printf("\nPhone: %s", pers->officephone);
		if (pers->homephone)
			printf(", %s", pers->homephone);
		if (pers->random)
			printf(", %s", pers->random);
	} else if (pers->homephone) {
		printf("\nPhone: %s", pers->homephone);
		if (pers->random)
			printf(", %s", pers->random);
	} else if (pers->random)
		printf("\n%s", pers->random);
	if (unbrief) {
		printf("\nDirectory: %-25s", pers->pwd->pw_dir);
		if (*pers->pwd->pw_shell)
			printf("\tShell: %-s", pers->pwd->pw_shell);
E 9
	}
D 9
	else  {
	    printf( "			" );
	}
	if(  strlen( pers->realname ) > 0  )  {
	    printf( "In real life: %-s", pers->realname );
	}
	if(  strlen( pers->office ) > 0  )  {
	    printf( "\nOffice: %-.11s", pers->office );
	    if(  strlen( pers->officephone ) > 0  )  {
		printf( ", %s", pers->officephone );
		if(  strlen( pers->homephone ) > 0  )  {
		    printf( "		Home phone: %s", pers->homephone );
E 9
I 9
	if (pers->loggedin) {
		register char *ep = ctime(&pers->loginat);
		if (*pers->host) {
			printf("\nOn since %15.15s on %s from %s",
				&ep[4], pers->tty, pers->host);
			ltimeprint("\n", &pers->idletime, " Idle Time");
		} else {
			printf("\nOn since %15.15s on %-*s",
				&ep[4], LMAX, pers->tty);
			ltimeprint("\t", &pers->idletime, " Idle Time");
E 9
		}
D 9
		else  {
		    if(  strlen( pers->random ) > 0  )  {
			printf( "	%s", pers->random );
		    }
		}
	    }
	    else  {
		if(  strlen( pers->homephone ) > 0  )  {
		    printf("			Home phone: %s",pers->homephone);
		}
		if(  strlen( pers->random ) > 0  )  {
		    printf( "			%s", pers->random );
		}
	    }
	}
	else  {
	    if(  strlen( pers->officephone ) > 0  )  {
		printf( "\nPhone: %s", pers->officephone );
		if(  strlen( pers->homephone ) > 0  )  {
		    printf( "\n, %s", pers->homephone );
		    if(  strlen( pers->random ) > 0  )  {
			printf( ", %s", pers->random );
		    }
		}
		else  {
		    if(  strlen( pers->random ) > 0  )  {
			printf( "\n, %s", pers->random );
		    }
		}
	    }
	    else  {
		if(  strlen( pers->homephone ) > 0  )  {
		    printf( "\nPhone: %s", pers->homephone );
		    if(  strlen( pers->random ) > 0  )  {
			printf( ", %s", pers->random );
		    }
		}
		else  {
		    if(  strlen( pers->random ) > 0  )  {
			printf( "\n%s", pers->random );
		    }
		}
	    }
	}
	if( unbrief )  {
	    printf( "\n" );
	    printf( "Directory: %-25s", pwdt->pw_dir );
	    if(  strlen( pwdt->pw_shell ) > 0  )  {
		printf( "	Shell: %-s", pwdt->pw_shell );
	    }
	}
	if( pers->loggedin )  {
	    register char *ep = ctime( &pers->loginat );
	    printf("\nOn since %15.15s on %-*.*s	", &ep[4], LMAX, LMAX, pers->tty );
	    idleprinted = ltimeprint( &pers->idletime );
	    if( idleprinted )  {
		printf( " Idle Time" );
	    }
	}
I 2
	else if (pers->loginat == 0)
	    printf("\nNever logged in.");
E 9
I 9
	} else if (pers->loginat == 0)
		printf("\nNever logged in.");
E 9
	else if (tloc - pers->loginat > 180 * 24 * 60 * 60) {
D 9
	    register char *ep = ctime( &pers->loginat );
	    printf("\nLast login %10.10s, %4.4s on %.*s", ep, ep+20, LMAX, pers->tty);
E 9
I 9
		register char *ep = ctime(&pers->loginat);
		printf("\nLast login %10.10s, %4.4s on %s",
			ep, ep+20, pers->tty);
		if (*pers->host)
			printf(" from %s", pers->host);
	} else {
		register char *ep = ctime(&pers->loginat);
		printf("\nLast login %16.16s on %s", ep, pers->tty);
		if (*pers->host)
			printf(" from %s", pers->host);
E 9
	}
E 2
D 9
	else  {
	    register char *ep = ctime( &pers->loginat );
	    printf("\nLast login %16.16s on %.*s", ep, LMAX, pers->tty );
	}
	printf( "\n" );
E 9
I 9
	putchar('\n');
E 9
}

D 9

E 9
/*
 *  very hacky section of code to format phone numbers.  filled with
 *  magic constants like 4, 7 and 10.
 */
D 9

char  *phone( s, len )

    char		*s;
    int			len;
E 9
I 9
char *
phone(s, len, alldigits)
	register char *s;
	int len;
	char alldigits;
E 9
{
D 9
	char		*strsave();
	char		fonebuf[ 15 ];
	int		i;
E 9
I 9
	char fonebuf[15];
	register char *p = fonebuf;
	register i;
E 9

D 9
	switch(  len  )  {

	    case  4:
		fonebuf[ 0 ] = ' ';
		fonebuf[ 1 ] = 'x';
		fonebuf[ 2 ] = '2';
		fonebuf[ 3 ] = '-';
		for( i = 0; i <= 3; i++ )  {
		    fonebuf[ 4 + i ] = *s++;
		}
		fonebuf[ 8 ] = NULL;
		return( strsave( &fonebuf[0] ) );
E 9
I 9
	if (!alldigits)
		return (strcpy(malloc(len + 1), s));
	switch (len) {
	case 4:
		*p++ = ' ';
		*p++ = 'x';
		*p++ = '2';
		*p++ = '-';
		for (i = 0; i < 4; i++)
			*p++ = *s++;
E 9
		break;
I 12
	case 5:
		*p++ = ' ';
		*p++ = 'x';
		*p++ = *s++;
		*p++ = '-';
		for (i = 0; i < 4; i++)
			*p++ = *s++;
		break;
E 12
D 9

	    case  7:
		for( i = 0; i <= 2; i++ )  {
		    fonebuf[ i ] = *s++;
		}
		fonebuf[ 3 ] = '-';
		for( i = 0; i <= 3; i++ )  {
		    fonebuf[ 4 + i ] = *s++;
		}
		fonebuf[ 8 ] = NULL;
		return( strsave( &fonebuf[0] ) );
E 9
I 9
	case 7:
		for (i = 0; i < 3; i++)
			*p++ = *s++;
		*p++ = '-';
		for (i = 0; i < 4; i++)
			*p++ = *s++;
E 9
		break;
D 9

	    case 10:
		for( i = 0; i <= 2; i++ )  {
		    fonebuf[ i ] = *s++;
		}
		fonebuf[ 3 ] = '-';
		for( i = 0; i <= 2; i++ )  {
		    fonebuf[ 4 + i ] = *s++;
		}
		fonebuf[ 7 ] = '-';
		for( i = 0; i <= 3; i++ )  {
		    fonebuf[ 8 + i ] = *s++;
		}
		fonebuf[ 12 ] = NULL;
		return( strsave( &fonebuf[0] ) );
E 9
I 9
	case 10:
		for (i = 0; i < 3; i++)
			*p++ = *s++;
		*p++ = '-';
		for (i = 0; i < 3; i++)
			*p++ = *s++;
		*p++ = '-';
		for (i = 0; i < 4; i++)
			*p++ = *s++;
E 9
		break;
D 9

	    default:
		fprintf( stderr, "finger: error in phone numbering\n" );
		return( strsave(s) );
		break;
E 9
I 9
	case 0:
		return 0;
	default:
		return (strcpy(malloc(len + 1), s));
E 9
	}
I 9
	*p++ = 0;
	return (strcpy(malloc(p - fonebuf), fonebuf));
E 9
}

D 9

/*  decode the information in the gecos field of /etc/passwd
 *  another hacky section of code, but given the format the stuff is in...
E 9
I 9
/*
 * decode the information in the gecos field of /etc/passwd
E 9
 */
D 9

decode( pers )

    struct  person	*pers;

E 9
I 9
decode(pers)
	register struct person *pers;
E 9
{
D 9
	struct  passwd		*pwdt = pers->pwd;
D 5
	char			buffer[ 40 ],  *bp,  *gp,  *lp;
E 5
I 5
	char			buffer[ 256 ],  *bp,  *gp,  *lp;
E 5
	char			*phone();
	int			alldigits;
	int			len;
	int			i;
E 9
I 9
	char buffer[256];
	register char *bp, *gp, *lp;
	int alldigits;
	int hasspace;
	int len;
E 9

D 9
	pers->realname = NULLSTR;
	pers->office = NULLSTR;
	pers->officephone = NULLSTR;
	pers->homephone = NULLSTR;
	pers->random = NULLSTR;
	if(  pwdt != NILPWD )  {
	    gp = pwdt->pw_gecos;
	    bp = &buffer[ 0 ];
	    if( *gp == ASTERISK )  {
E 9
I 9
	pers->realname = 0;
	pers->office = 0;
	pers->officephone = 0;
	pers->homephone = 0;
	pers->random = 0;
	if (pers->pwd == 0)
		return;
	gp = pers->pwd->pw_gecos;
	bp = buffer;
	if (*gp == ASTERISK)
E 9
		gp++;
D 9
	    }
	    while(  (*gp != NULL)  &&  (*gp != COMMA)  )  {	/* name */
		if( *gp == SAMENAME )  {
		    lp = pwdt->pw_name;
		    *bp++ = CAPITALIZE(*lp++);
		    while( *lp != NULL )  {
			*bp++ = *lp++;
		    }
E 9
I 9
	while (*gp && *gp != COMMA)			/* name */
		if (*gp == SAMENAME) {
			lp = pers->pwd->pw_name;
			if (islower(*lp))
				*bp++ = toupper(*lp++);
			while (*bp++ = *lp++)
				;
			bp--;
			gp++;
		} else
			*bp++ = *gp++;
	*bp++ = 0;
	if ((len = bp - buffer) > 1)
		pers->realname = strcpy(malloc(len), buffer);
	if (*gp == COMMA) {				/* office */
		gp++;
		hasspace = 0;
		bp = buffer;
		while (*gp && *gp != COMMA) {
			*bp = *gp++;
			if (*bp == ' ')
				hasspace = 1;
			/* leave 5 for Cory and Evans expansion */
			if (bp < buffer + sizeof buffer - 6)
				bp++;
E 9
		}
D 9
		else  {
		    *bp++ = *gp;
		}
E 9
I 9
		*bp = 0;
		len = bp - buffer;
		bp--;			/* point to last character */
		if (hasspace || len == 0)
			len++;
		else if (*bp == CORY) {
			strcpy(bp, " Cory");
			len += 5;
		} else if (*bp == EVANS) {
			strcpy(bp, " Evans");
			len += 6;
		} else
			len++;
		if (len > 1)
			pers->office = strcpy(malloc(len), buffer);
	}
	if (*gp == COMMA) {				/* office phone */
E 9
		gp++;
D 9
	    }
	    *bp = NULL;
	    pers->realname = malloc( strlen( &buffer[0] ) + 1 );
	    strcpy( pers->realname, &buffer[0] );
	    if( *gp++ == COMMA )  {			/* office, supposedly */
E 9
I 9
		bp = buffer;
E 9
		alldigits = 1;
D 9
		bp = &buffer[ 0 ];
		while(  (*gp != NULL)  &&  (*gp != COMMA)  )  {
		    *bp = *gp++;
		    alldigits = alldigits && ('0' <= *bp) && (*bp <= '9');
		    bp++;
E 9
I 9
		while (*gp && *gp != COMMA) {
			*bp = *gp++;
			if (!isdigit(*bp))
				alldigits = 0;
			if (bp < buffer + sizeof buffer - 1)
				bp++;
E 9
		}
D 9
		*bp = NULL;
		len = strlen( &buffer[0] );
		if( buffer[ len - 1 ]  ==  CORY )  {
		    strcpy( &buffer[ len - 1 ], " Cory" );
		    pers->office = malloc( len + 5 );
		    strcpy( pers->office, &buffer[0] );
		}
		else  {
		    if( buffer[ len - 1 ] == EVANS )  {
			strcpy( &buffer[ len - 1 ], " Evans" );
			pers->office = malloc( len + 6 );
			strcpy( pers->office, &buffer[0] );
		    }
		    else  {
			if( buffer[ len - 1 ] == 'L' )  {
			    strcpy( &buffer[ len - 1 ], " LBL" );
			    pers->office = malloc( len + 4 );
			    strcpy( pers->office, &buffer[0] );
			}
			else  {
			    if( alldigits )  {
				if( len == 4 )  {
				    pers->officephone = phone(&buffer[0], len);
				}
				else  {
				    if(  (len == 7) || (len == 10)  )  {
					pers->homephone = phone(&buffer[0],len);
				    }
				}
			    }
			    else  {
				pers->random = malloc( len + 1 );
				strcpy( pers->random, &buffer[0] );
			    }
			}
		    }
		}
		if( *gp++ == COMMA )  {	    /* office phone, theoretically */
		    bp = &buffer[ 0 ];
		    alldigits = 1;
		    while(  (*gp != NULL)  &&  (*gp != COMMA)  )  {
E 9
I 9
		*bp = 0;
		pers->officephone = phone(buffer, bp - buffer, alldigits);
	}
	if (*gp == COMMA) {				/* home phone */
		gp++;
		bp = buffer;
		alldigits = 1;
		while (*gp && *gp != COMMA) {
E 9
			*bp = *gp++;
D 9
			alldigits = alldigits && ('0' <= *bp) && (*bp <= '9');
			bp++;
		    }
		    *bp = NULL;
		    len = strlen( &buffer[0] );
		    if( alldigits )  {
			if(  len != 4  )  {
			    if(  (len == 7) || (len == 10)  )  {
				pers->homephone = phone( &buffer[0], len );
			    }
			    else  {
				pers->random = malloc( len + 1 );
				strcpy( pers->random, &buffer[0] );
			    }
			}
			else  {
				pers->officephone = phone( &buffer[0], len );
			}
		    }
		    else  {
			pers->random = malloc( len + 1 );
			strcpy( pers->random, &buffer[0] );
		    }
		    if( *gp++ == COMMA )  {		/* home phone?? */
			bp = &buffer[ 0 ];
			alldigits = 1;
			    while(  (*gp != NULL)  &&  (*gp != COMMA)  )  {
				*bp = *gp++;
				alldigits = alldigits && ('0' <= *bp) &&
							(*bp <= '9');
E 9
I 9
			if (!isdigit(*bp))
				alldigits = 0;
			if (bp < buffer + sizeof buffer - 1)
E 9
				bp++;
D 9
			    }
			*bp = NULL;
			len = strlen( &buffer[0] );
			if( alldigits  &&  ( (len == 7) || (len == 10) )  )  {
			    if( *pers->homephone != NULL )  {
				pers->officephone = pers->homephone;
			    }
			    pers->homephone = phone( &buffer[0], len );
			}
			else  {
			    pers->random = malloc( strlen( &buffer[0] ) + 1 );
			    strcpy( pers->random, &buffer[0] );
			}
		    }
E 9
		}
D 9
	    }
	    if( pers->loggedin == 0 )  {
		findwhen( pers );
	    }
	    else  {
		findidle( pers );
	    }
E 9
I 9
		*bp = 0;
		pers->homephone = phone(buffer, bp - buffer, alldigits);
E 9
	}
I 9
	if (pers->loggedin)
		findidle(pers);
	else
		findwhen(pers);
E 9
}

D 9

/*  find the last log in of a user by checking the LASTLOG file.
 *  the entry is indexed by the uid, so this can only be done if
 *  the uid is known (which it isn't in quick mode)
E 9
I 9
/*
D 21
 * find the last log in of a user by checking the LASTLOG file.
E 21
I 21
 * find the last log in of a user by checking the _PATH_LASTLOG file.
E 21
 * the entry is indexed by the uid, so this can only be done if
 * the uid is known (which it isn't in quick mode)
E 9
 */

fwopen()
{
D 9
	if(  ( lf = open(LASTLOG, 0) ) >= 0  )  {
	    llopenerr = 0;
	}
	else  {
	    fprintf( stderr, "finger: lastlog open error\n" );
	    llopenerr = 1;
	}
E 9
I 9
D 21
	if ((lf = open(LASTLOG, 0)) < 0)
		fprintf(stderr, "finger: %s open error\n", LASTLOG);
E 21
I 21
	if ((lf = open(_PATH_LASTLOG, 0)) < 0)
		fprintf(stderr, "finger: %s open error\n", _PATH_LASTLOG);
E 21
E 9
}

D 9

findwhen( pers )

    struct  person	*pers;
E 9
I 9
findwhen(pers)
	register struct person *pers;
E 9
{
D 9
	struct  passwd		*pwdt = pers->pwd;
	struct  lastlog		ll;
	int			llsize = sizeof ll;
	int			i;
E 9
I 9
	struct lastlog ll;
	int i;
E 9

D 9
	if( !llopenerr )  {
	    lseek( lf, pwdt->pw_uid*llsize, 0 );
D 2
	    if( read( lf, (char *) &ll, llsize ) == llsize )  {
E 2
I 2
	    if ((i = read( lf, (char *) &ll, llsize )) == llsize) {
E 2
		    for( i = 0; i < LMAX; i++ )  {
			pers->tty[ i ] = ll.ll_line[ i ];
		    }
		    pers->tty[ LMAX ] = NULL;
		    pers->loginat = ll.ll_time;
	    }
	    else  {
D 2
		fprintf( stderr, "finger: lastlog read error\n" );
E 2
I 2
		if (i != 0)
			fprintf(stderr, "finger: lastlog read error\n");
E 2
		pers->tty[ 0 ] = NULL;
E 9
I 9
	if (lf >= 0) {
		lseek(lf, (long)pers->pwd->pw_uid * sizeof ll, 0);
		if ((i = read(lf, (char *)&ll, sizeof ll)) == sizeof ll) {
			bcopy(ll.ll_line, pers->tty, LMAX);
			pers->tty[LMAX] = 0;
			bcopy(ll.ll_host, pers->host, HMAX);
			pers->host[HMAX] = 0;
			pers->loginat = ll.ll_time;
		} else {
			if (i != 0)
				fprintf(stderr, "finger: %s read error\n",
D 21
					LASTLOG);
E 21
I 21
					_PATH_LASTLOG);
E 21
			pers->tty[0] = 0;
			pers->host[0] = 0;
			pers->loginat = 0L;
		}
	} else {
		pers->tty[0] = 0;
		pers->host[0] = 0;
E 9
		pers->loginat = 0L;
D 9
	    }
E 9
	}
D 9
	else  {
	    pers->tty[ 0 ] = NULL;
	    pers->loginat = 0L;
	}
E 9
}

D 9

E 9
fwclose()
{
D 9
	if( !llopenerr )  {
	    close( lf );
	}
E 9
I 9
	if (lf >= 0)
		close(lf);
E 9
}

D 9

/*  find the idle time of a user by doing a stat on /dev/histty,
 *  where histty has been gotten from USERLOG, supposedly.
E 9
I 9
/*
 * find the idle time of a user by doing a stat on /dev/tty??,
D 21
 * where tty?? has been gotten from USERLOG, supposedly.
E 21
I 21
 * where tty?? has been gotten from _PATH_UTMP, supposedly.
E 21
E 9
 */
D 9

findidle( pers )

    struct  person	*pers;
E 9
I 9
findidle(pers)
	register struct person *pers;
E 9
{
D 9
	struct  stat		ttystatus;
	struct  passwd		*pwdt = pers->pwd;
	char			buffer[ 20 ];
	char			*TTY = "/dev/";
	int			TTYLEN = strlen( TTY );
	int			i;
E 9
I 9
	struct stat ttystatus;
D 21
	static char buffer[20] = "/dev/";
E 21
I 21
	static char buffer[20] = _PATH_DEV;
E 21
	long t;
#define TTYLEN 5
E 9

D 9
	strcpy( &buffer[0], TTY );
	i = 0;
	do  {
	    buffer[ TTYLEN + i ] = pers->tty[ i ];
	}  while( ++i <= LMAX );
	if(  stat( &buffer[0], &ttystatus ) >= 0  )  {
	    time( &tloc );
	    if( tloc < ttystatus.st_atime )  {
		pers->idletime = 0L;
	    }
	    else  {
		pers->idletime = tloc - ttystatus.st_atime;
	    }
	    if(  (ttystatus.st_mode & TALKABLE) == TALKABLE  )  {
		pers->writeable = 1;
	    }
	    else  {
		pers->writeable = 0;
	    }
E 9
I 9
	strcpy(buffer + TTYLEN, pers->tty);
	buffer[TTYLEN+LMAX] = 0;
	if (stat(buffer, &ttystatus) < 0) {
		fprintf(stderr, "finger: Can't stat %s\n", buffer);
		exit(4);
E 9
	}
D 9
	else  {
	    fprintf( stderr, "finger: error STATing %s\n", &buffer[0] );
	    exit( 4 );
	}
E 9
I 9
	time(&t);
	if (t < ttystatus.st_atime)
		pers->idletime = 0L;
	else
		pers->idletime = t - ttystatus.st_atime;
	pers->writable = (ttystatus.st_mode & TALKABLE) == TALKABLE;
E 9
}

D 9

/*  print idle time in short format; this program always prints 4 characters;
 *  if the idle time is zero, it prints 4 blanks.
E 9
I 9
/*
 * print idle time in short format; this program always prints 4 characters;
 * if the idle time is zero, it prints 4 blanks.
E 9
 */
D 9

stimeprint( dt )

    long	*dt;
E 9
I 9
stimeprint(dt)
	long *dt;
E 9
{
D 9
	struct  tm		*gmtime();
	struct  tm		*delta;
E 9
I 9
	register struct tm *delta;
E 9

D 9
	delta = gmtime( dt );
	if( delta->tm_yday == 0 )  {
	    if( delta->tm_hour == 0 )  {
		if( delta->tm_min >= 10 )  {
		    printf( " %2.2d ", delta->tm_min );
		}
		else  {
		    if( delta->tm_min == 0 )  {
			printf( "    " );
		    }
		    else  {
			printf( "  %1.1d ", delta->tm_min );
		    }
		}
	    }
	    else  {
		if( delta->tm_hour >= 10 )  {
		    printf( "%3.3d:", delta->tm_hour );
		}
		else  {
		    printf( "%1.1d:%02.2d", delta->tm_hour, delta->tm_min );
		}
	    }
	}
	else  {
	    printf( "%3dd", delta->tm_yday );
	}
E 9
I 9
	delta = gmtime(dt);
	if (delta->tm_yday == 0)
		if (delta->tm_hour == 0)
			if (delta->tm_min == 0)
				printf("    ");
			else
				printf("  %2d", delta->tm_min);
		else
			if (delta->tm_hour >= 10)
				printf("%3d:", delta->tm_hour);
			else
				printf("%1d:%02d",
					delta->tm_hour, delta->tm_min);
	else
		printf("%3dd", delta->tm_yday);
E 9
}

D 9

/*  print idle time in long format with care being taken not to pluralize
 *  1 minutes or 1 hours or 1 days.
E 9
I 9
/*
 * print idle time in long format with care being taken not to pluralize
 * 1 minutes or 1 hours or 1 days.
 * print "prefix" first.
E 9
 */
D 9

ltimeprint( dt )

    long	*dt;
E 9
I 9
ltimeprint(before, dt, after)
	long *dt;
	char *before, *after;
E 9
{
D 9
	struct  tm		*gmtime();
	struct  tm		*delta;
	int			printed = 1;
E 9
I 9
	register struct tm *delta;
E 9

D 9
	delta = gmtime( dt );
	if( delta->tm_yday == 0 )  {
	    if( delta->tm_hour == 0 )  {
		if( delta->tm_min >= 10 )  {
		    printf( "%2d minutes", delta->tm_min );
		}
		else  {
		    if( delta->tm_min == 0 )  {
			if( delta->tm_sec > 10 )  {
			    printf( "%2d seconds", delta->tm_sec );
			}
			else  {
			    printed = 0;
			}
		    }
		    else  {
			if( delta->tm_min == 1 )  {
			    if( delta->tm_sec == 1 )  {
				printf( "%1d minute %1d second",
				    delta->tm_min, delta->tm_sec );
			    }
			    else  {
				printf( "%1d minute %d seconds",
				    delta->tm_min, delta->tm_sec );
			    }
			}
			else  {
			    if( delta->tm_sec == 1 )  {
				printf( "%1d minutes %1d second",
				    delta->tm_min, delta->tm_sec );
			    }
			    else  {
				printf( "%1d minutes %d seconds",
				    delta->tm_min, delta->tm_sec );
			    }
			}
		    }
		}
	    }
	    else  {
		if( delta->tm_hour >= 10 )  {
		    printf( "%2d hours", delta->tm_hour );
		}
		else  {
		    if( delta->tm_hour == 1 )  {
			if( delta->tm_min == 1 )  {
			    printf( "%1d hour %1d minute",
				delta->tm_hour, delta->tm_min );
			}
			else  {
			    printf( "%1d hour %2d minutes",
				delta->tm_hour, delta->tm_min );
			}
		    }
		    else  {
			if( delta->tm_min == 1 )  {
			    printf( "%1d hours %1d minute",
				delta->tm_hour, delta->tm_min );
			}
			else  {
			    printf( "%1d hours %2d minutes",
				delta->tm_hour, delta->tm_min );
			}
		    }
		}
	    }
	}
	else  {
		if( delta->tm_yday >= 10 )  {
		    printf( "%2d days", delta->tm_yday );
		}
		else  {
		    if( delta->tm_yday == 1 )  {
			if( delta->tm_hour == 1 )  {
			    printf( "%1d day %1d hour",
				delta->tm_yday, delta->tm_hour );
			}
			else  {
			    printf( "%1d day %2d hours",
				delta->tm_yday, delta->tm_hour );
			}
		    }
		    else  {
			if( delta->tm_hour == 1 )  {
			    printf( "%1d days %1d hour",
				delta->tm_yday, delta->tm_hour );
			}
			else  {
			    printf( "%1d days %2d hours",
				delta->tm_yday, delta->tm_hour );
			}
		    }
		}
	}
	return( printed );
E 9
I 9
	delta = gmtime(dt);
	if (delta->tm_yday == 0 && delta->tm_hour == 0 && delta->tm_min == 0 &&
	    delta->tm_sec <= 10)
		return (0);
	printf("%s", before);
	if (delta->tm_yday >= 10)
		printf("%d days", delta->tm_yday);
	else if (delta->tm_yday > 0)
		printf("%d day%s %d hour%s",
			delta->tm_yday, delta->tm_yday == 1 ? "" : "s",
			delta->tm_hour, delta->tm_hour == 1 ? "" : "s");
	else
		if (delta->tm_hour >= 10)
			printf("%d hours", delta->tm_hour);
		else if (delta->tm_hour > 0)
			printf("%d hour%s %d minute%s",
				delta->tm_hour, delta->tm_hour == 1 ? "" : "s",
				delta->tm_min, delta->tm_min == 1 ? "" : "s");
		else
			if (delta->tm_min >= 10)
				printf("%2d minutes", delta->tm_min);
			else if (delta->tm_min == 0)
				printf("%2d seconds", delta->tm_sec);
			else
				printf("%d minute%s %d second%s",
					delta->tm_min,
					delta->tm_min == 1 ? "" : "s",
					delta->tm_sec,
					delta->tm_sec == 1 ? "" : "s");
	printf("%s", after);
E 9
}

D 9

matchcmp( gname, login, given )

    char		*gname;
    char		*login;
    char		*given;
E 9
I 9
matchcmp(gname, login, given)
	register char *gname;
	char *login;
	char *given;
E 9
{
D 9
	char		buffer[ 20 ];
	char		c;
	int		flag,  i,  unfound;
E 9
I 9
	char buffer[100];
	register char *bp, *lp;
	register c;
E 9

D 9
	if( !match )  {
	    return( 0 );
	}
	else  {
	    if(  namecmp( login, given )  )  {
		return( 1 );
	    }
I 3
	    else if (*gname == '\0')
		return (0);
E 3
	    else  {
		if( *gname == ASTERISK )  {
		    gname++;
E 9
I 9
	if (*gname == ASTERISK)
		gname++;
	lp = 0;
	bp = buffer;
	for (;;)
		switch (c = *gname++) {
		case SAMENAME:
			for (lp = login; bp < buffer + sizeof buffer
					 && (*bp++ = *lp++);)
				;
			bp--;
			break;
		case ' ':
		case COMMA:
		case '\0':
			*bp = 0;
			if (namecmp(buffer, given))
				return (1);
			if (c == COMMA || c == 0)
				return (0);
			bp = buffer;
			break;
		default:
			if (bp < buffer + sizeof buffer)
				*bp++ = c;
E 9
		}
D 9
		flag = 1;
		i = 0;
		unfound = 1;
		while(  unfound  )  {
		    if( flag )  {
			c = *gname++;
			if( c == SAMENAME )  {
			    flag = 0;
			    c = *login++;
			}
			else  {
			    unfound = (*gname != COMMA)  &&  (*gname != NULL);
			}
		    }
		    else {
			c = *login++;
			if( c == NULL )  {
			    if(  (*gname == COMMA)  ||  (*gname == NULL)  )  {
				break;
			    }
			    else  {
				flag = 1;
				continue;
			    }
			}
		    }
		    if( c == BLANK )  {
			buffer[i++] = NULL;
			if(  namecmp( buffer, given )  )  {
			    return( 1 );
			}
			i = 0;
			flag = 1;
		    }
		    else  {
			buffer[ i++ ] = c;
		    }
		}
		buffer[i++] = NULL;
		if(  namecmp( buffer, given )  )  {
		    return( 1 );
		}
		else  {
		    return( 0 );
		}
	    }
	}
E 9
I 9
	/*NOTREACHED*/
E 9
}

D 9

namecmp( name1, name2 )

    char		*name1;
    char		*name2;
E 9
I 9
namecmp(name1, name2)
	register char *name1, *name2;
E 9
{
D 9
	char		c1,  c2;
E 9
I 9
	register c1, c2;
E 9

D 9
	c1 = *name1;
	if( (('A' <= c1) && (c1 <= 'Z')) || (('a' <= c1) && (c1 <= 'z')) )  {
	    c1 = CAPITALIZE( c1 );
E 9
I 9
	for (;;) {
		c1 = *name1++;
		if (islower(c1))
			c1 = toupper(c1);
		c2 = *name2++;
		if (islower(c2))
			c2 = toupper(c2);
		if (c1 != c2)
			break;
		if (c1 == 0)
			return (1);
E 9
	}
D 9
	c2 = *name2;
	if( (('A' <= c2) && (c2 <= 'Z')) || (('a' <= c2) && (c2 <= 'z')) )  {
	    c2 = CAPITALIZE( c2 );
E 9
I 9
	if (!c1) {
		for (name2--; isdigit(*name2); name2++)
			;
		if (*name2 == 0)
			return (1);
	} else if (!c2) {
		for (name1--; isdigit(*name1); name1++)
			;
		if (*name2 == 0)
			return (1);
E 9
	}
D 9
	while( c1 == c2 )  {
	    if( c1 == NULL )  {
		return( 1 );
	    }
	    c1 = *++name1;
	    if( (('A'<=c1) && (c1<='Z')) || (('a'<=c1) && (c1<='z')) )  {
		c1 = CAPITALIZE( c1 );
	    }
	    c2 = *++name2;
	    if( (('A'<=c2) && (c2<='Z')) || (('a'<=c2) && (c2<='z')) )  {
		c2 = CAPITALIZE( c2 );
	    }
	}
	if( *name1 == NULL )  {
	    while(  ('0' <= *name2)  &&  (*name2 <= '9')  )  {
		name2++;
	    }
	    if( *name2 == NULL )  {
		return( 1 );
	    }
	}
	else  {
	    if( *name2 == NULL )  {
		while(  ('0' <= *name1)  &&  (*name1 <= '9')  )  {
		    name1++;
		}
		if( *name1 == NULL )  {
		    return( 1 );
		}
	    }
	}
	return( 0 );
E 9
I 9
	return (0);
E 9
}

D 9

char  *strsave( s )

    char		*s;
{
	char		*malloc();
	char		*p;

	p = malloc( strlen( s ) + 1 );
D 7
	strcpy( p, s );
E 7
I 7
	return( strcpy( p, s ) );
E 7
I 6
}

E 9
netfinger(name)
D 9
char *name;
E 9
I 9
	char *name;
E 9
{
	char *host;
	char fname[100];
	struct hostent *hp;
	struct servent *sp;
D 9
	struct	sockaddr_in sin;
E 9
I 9
	struct sockaddr_in sin;
E 9
	int s;
	char *rindex();
	register FILE *f;
	register int c;
	register int lastc;

	if (name == NULL)
D 9
		return(0);
E 9
I 9
		return (0);
E 9
	host = rindex(name, '@');
	if (host == NULL)
D 9
		return(0);
E 9
I 9
		return (0);
E 9
	*host++ = 0;
	hp = gethostbyname(host);
	if (hp == NULL) {
		static struct hostent def;
		static struct in_addr defaddr;
I 14
D 15
		char *alist[1];
E 15
I 15
		static char *alist[1];
E 15
E 14
		static char namebuf[128];
		int inet_addr();

		defaddr.s_addr = inet_addr(host);
		if (defaddr.s_addr == -1) {
			printf("unknown host: %s\n", host);
D 9
			return(1);
E 9
I 9
			return (1);
E 9
		}
		strcpy(namebuf, host);
		def.h_name = namebuf;
D 14
		def.h_addr = (char *)&defaddr;
E 14
I 14
		def.h_addr_list = alist, def.h_addr = (char *)&defaddr;
E 14
		def.h_length = sizeof (struct in_addr);
		def.h_addrtype = AF_INET;
		def.h_aliases = 0;
		hp = &def;
	}
D 18
	printf("[%s]", hp->h_name);
E 18
	sp = getservbyname("finger", "tcp");
	if (sp == 0) {
		printf("tcp/finger: unknown service\n");
D 9
		return(1);
E 9
I 9
		return (1);
E 9
	}
	sin.sin_family = hp->h_addrtype;
	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
	sin.sin_port = sp->s_port;
	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
	if (s < 0) {
D 18
		fflush(stdout);
E 18
		perror("socket");
D 9
		return(1);
E 9
I 9
		return (1);
E 9
	}
I 18
D 19
	printf("[%s]", hp->h_name); fflush(stdout);
E 19
I 19
	printf("[%s]\n", hp->h_name);
	fflush(stdout);
E 19
E 18
	if (connect(s, (char *)&sin, sizeof (sin)) < 0) {
D 18
		fflush(stdout);
E 18
		perror("connect");
		close(s);
D 9
		return(1);
E 9
I 9
		return (1);
E 9
	}
D 18
	printf("\n");
E 18
I 18
D 19
	putchar('\n');
E 19
E 18
	if (large) write(s, "/W ", 3);
	write(s, name, strlen(name));
	write(s, "\r\n", 2);
	f = fdopen(s, "r");
	while ((c = getc(f)) != EOF) {
		switch(c) {
		case 0210:
		case 0211:
		case 0212:
		case 0214:
			c -= 0200;
			break;
		case 0215:
			c = '\n';
			break;
		}
D 16
		putchar(lastc = c);
E 16
I 16
		lastc = c;
		if (isprint(c) || isspace(c))
			putchar(c);
		else
			putchar(c ^ 100);
E 16
	}
	if (lastc != '\n')
		putchar('\n');
I 13
	(void)fclose(f);
E 13
D 9
	return(1);
E 9
I 9
	return (1);
E 22
I 22
D 26
	(void)close(fd);
E 26
I 26
D 27
	(void)fclose(fp);
E 27
E 26
D 23
	for (pn = head; pn; pn = pn->next)
		if (pn->info == FOUND)
			find_when(pn);
E 23
I 23
D 33
	for (pn = phead; pn != NULL; pn = pn->next)
		enter_lastlog(pn);
E 33
I 33
	if (db)
		for (sflag = R_FIRST;; sflag = R_NEXT) {
I 37
			PERSON *tmp;

E 37
			r = (*db->seq)(db, &key, &data, sflag);
			if (r == -1)
D 37
				err("db seq: %s", strerror(errno));
E 37
I 37
				err(1, "db seq");
E 37
			if (r == 1)
				break;
D 37
			enter_lastlog(*(PERSON **)data.data);
E 37
I 37
D 38
			memcpy(&tmp, data.data, sizeof tmp);
E 38
I 38
			memmove(&tmp, data.data, sizeof tmp);
E 38
			enter_lastlog(tmp);
E 37
		}
E 33
E 23
E 22
E 9
E 6
}
E 1
