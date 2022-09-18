h00906
s 00002/00002/00684
d D 8.17 95/01/31 05:12:51 pendry 53 52
c update copyright dates
e
s 00010/00010/00676
d D 8.16 94/04/16 11:45:32 bostic 52 51
c delete potential matches if the -a flag isn't set after finding
c a match
e
s 00001/00001/00685
d D 8.15 94/03/18 06:21:16 bostic 51 50
c  redirection of 'man -w' has unexpected result
c From: Keith White <kwhite@csi.uottawa.ca>
e
s 00001/00001/00685
d D 8.14 94/02/08 10:14:26 pendry 50 49
c fix usage: message
e
s 00003/00001/00683
d D 8.13 94/01/02 10:37:26 bostic 49 48
c if only one argument, don't use it as a section
c fix from Tony Sanders at BSDI
e
s 00002/00003/00682
d D 8.12 94/01/02 10:36:39 bostic 48 47
c initialization not right in two places, lint cleanups
e
s 00147/00149/00538
d D 8.11 94/01/02 10:36:13 bostic 47 46
c convert to new <sys/queue.h> structures
e
s 00003/00005/00684
d D 8.10 94/01/02 10:35:47 bostic 46 45
c typo
e
s 00019/00044/00670
d D 8.9 94/01/02 10:35:06 bostic 45 44
c put built pages into the pathv[] list, so the man page order is
c preserved
e
s 00022/00059/00692
d D 8.8 94/01/02 10:34:12 bostic 44 43
c only manual() tests for f_all and returns if it's set -- the main
c loop calls manual for each user argument, so each page found is displayed
e
s 00014/00017/00737
d D 8.7 94/01/02 10:33:22 bostic 43 42
c typo, *ap should be **ap
c the fnmatch code was letting "man.conf.0" match when "man.0" was what was
c wanted
c reverse the direction of the review of what glob returned, it matters if
c you're only looking at the first one
e
s 00002/00001/00752
d D 8.6 94/01/02 10:32:21 bostic 42 41
c use GLOB_QUOTE, so you can escape magic characters in man.conf
e
s 00020/00007/00733
d D 8.5 94/01/02 10:31:40 bostic 41 40
c check machine subdirectories for sections even if they don't have a
c trailing slash; add support for old-style man.conf files that didn't have
c the _suffix keyword
e
s 00008/00004/00732
d D 8.4 94/01/02 10:30:34 bostic 40 39
c add a way to specify the config file (-C)
e
s 00511/00126/00225
d D 8.3 94/01/02 10:30:13 bostic 39 38
c rewrite man to make the configuration file more flexible
e
s 00001/00000/00350
d D 8.2 94/01/02 10:29:47 bostic 38 37
c argc needs to be decremented, as it's tested later
e
s 00005/00005/00345
d D 8.1 93/06/18 08:55:34 bostic 37 36
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00007/00337
d D 5.28 93/06/18 08:55:24 bostic 36 32
c always replace the ':' in the path
e
s 00005/00005/00343
d R 8.1 93/06/18 08:44:05 bostic 35 34
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00009/00336
d R 5.28 93/06/18 08:43:57 bostic 34 32
c always restore the ':' in the path
e
s 00005/00005/00340
d R 8.1 93/06/17 11:46:06 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00014/00330
d D 5.27 93/06/17 11:45:53 bostic 32 30
c `man tty 4' dumped core on the sparc
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00005/00005/00339
d R 8.1 93/06/06 15:23:31 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00005/00341
d D 5.26 92/07/06 12:57:10 bostic 30 29
c don't quit just because can't find one man page
e
s 00002/00002/00344
d D 5.25 92/02/12 17:02:31 bostic 29 28
c fix buffer overflow problem; example was really long MANPATH variable
e
s 00051/00004/00295
d D 5.24 90/07/21 10:31:41 bostic 28 27
c add the how flag (-h) which prints out the lines between the SYNOPSIS
c and DESCRIPTION headers
e
s 00001/00001/00298
d D 5.23 90/06/29 10:53:40 trent 27 26
c move a variable declaration
e
s 00016/00004/00283
d D 5.22 90/06/28 18:04:47 trent 26 25
c MANPATH subdirectories now specified by _config in man.conf
e
s 00001/00011/00286
d D 5.21 90/06/01 16:58:21 bostic 25 24
c new copyright notice
e
s 00060/00166/00237
d D 5.20 90/05/27 15:24:01 bostic 24 23
c new man version, with much more complicated configuration file
e
s 00133/00161/00270
d D 5.19 90/03/11 15:11:10 bostic 23 22
c add -m flag, configurable directory search path (/etc/man.config)
c add man.config man page, redo man(1) man page, now AT&T free.  Change '-'
c option to -c, other minor whacks
e
s 00005/00012/00426
d D 5.18 89/05/11 10:00:43 bostic 22 21
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00428
d D 5.17 88/06/29 19:42:47 bostic 21 20
c install approved copyright notice
e
s 00035/00034/00398
d D 5.16 88/06/17 11:38:25 bostic 20 19
c "man new foo" was broken; clean up logic in general, it was needlessly\convoluted
e
s 00006/00006/00426
d D 5.15 88/04/22 16:51:26 marc 19 18
c wasen't using users PAGER if it was "more"
e
s 00069/00043/00363
d D 5.14 88/04/22 16:37:42 bostic 18 17
c add -a flag, print all man pages; add getopt, required getopt to handle
c single dash; add routine jump, to handle old -k and -f flags;
e
s 00086/00064/00320
d D 5.13 88/03/28 11:30:46 bostic 17 15
c change to display multiple man pages; minor kernel normal form changes
e
s 00081/00063/00321
d R 5.13 88/03/28 11:24:58 bostic 16 15
c change to display multiple man pages; minor kernel normal form changes
e
s 00169/00179/00224
d D 5.12 88/01/14 16:54:05 bostic 15 14
c fix to find all section 1's before finding section 2's, etc. 
c fair amount of rewriting, I never did like its kludginess anyway
e
s 00006/00002/00397
d D 5.11 88/01/08 14:28:53 bostic 14 13
c don't truncate manpath in case usage is "man foo bar baz"
e
s 00011/00005/00388
d D 5.10 87/12/16 15:39:15 bostic 13 12
c add Berkeley headers
e
s 00001/00000/00392
d D 5.9 87/11/14 11:57:40 bostic 12 11
c put in standard illegal option message
e
s 00019/00011/00373
d D 5.8 87/10/29 11:43:43 bostic 11 8
c add the UNDOCUMENTED -w flag; it's useful when you're moving 
c man pages hither and yon.  It's NOT worth making "real".
e
s 00020/00012/00372
d R 5.8 87/10/26 16:10:45 bostic 10 8
c add the UNDOCUMENTED -w flag; it's useful when you're moving 
c man pages hither and yon.  It's NOT worth making "real".
e
s 00016/00012/00372
d R 5.8 87/10/26 16:06:18 bostic 9 8
c add the UNDOCUMENTED -w flag; it's useful when you're moving 
c man pages hither and yon.  It's NOT worth making "real".
e
s 00054/00030/00330
d D 5.7 87/07/26 18:48:18 bostic 8 6
c break "new" out into multiple directories, minor fixes
e
s 00056/00024/00336
d R 5.7 87/07/26 18:43:53 bostic 7 6
c break "cat.new" into multiple directories, minor fixes
e
s 00003/00003/00357
d D 5.6 87/07/20 08:06:25 bostic 6 5
c make -M and MANPATH work again; bug report 4.3BSD/ucb/104
e
s 00029/00003/00331
d D 5.5 87/07/05 19:49:48 bostic 5 4
c if PAGER is more, add the -s flag
e
s 00071/00017/00263
d D 5.4 87/07/03 17:06:06 bostic 4 3
c make new/old really work; section 1 is really 1, 6, 8, old, new
e
s 00002/00002/00278
d D 5.3 87/07/02 15:33:15 bostic 3 2
c fix old/new argv stuff
e
s 00096/00065/00184
d D 5.2 87/06/30 19:17:32 bostic 2 1
c make it really work
e
s 00249/00000/00000
d D 5.1 87/06/29 20:53:50 bostic 1 0
c date and time created 87/06/29 20:53:50 by bostic
e
u
U
t
T
I 1
/*
D 37
 * Copyright (c) 1987 Regents of the University of California.
D 13
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
 * All rights reserved.
E 37
I 37
D 52
 * Copyright (c) 1987, 1993
E 52
I 52
D 53
 * Copyright (c) 1987, 1993, 1994
E 53
I 53
 * Copyright (c) 1987, 1993, 1994, 1995
E 53
E 52
 *	The Regents of the University of California.  All rights reserved.
E 37
 *
D 25
 * Redistribution and use in source and binary forms are permitted
D 21
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 21
I 21
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 25
I 25
 * %sccs.include.redist.c%
E 25
E 21
E 13
 */

#ifndef lint
D 37
char copyright[] =
D 11
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 11
I 11
D 13
"@(#) Copyright (c) 1987 Regents of the University of California.\n\
E 13
I 13
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 13
E 11
 All rights reserved.\n";
E 37
I 37
static char copyright[] =
D 53
"%Z% Copyright (c) 1987, 1993\n\
E 53
I 53
"%Z% Copyright (c) 1987, 1993, 1994, 1995\n\
E 53
	The Regents of the University of California.  All rights reserved.\n";
E 37
D 13
#endif not lint
E 13
I 13
#endif /* not lint */
E 13

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 13
#endif not lint
E 13
I 13
#endif /* not lint */
E 13

#include <sys/param.h>
I 39
#include <sys/queue.h>
E 39
D 36
#include <sys/file.h>
I 23
#include <errno.h>
E 36
I 36

E 36
E 23
#include <ctype.h>
I 39
#include <err.h>
E 39
I 23
D 36
#include <string.h>
E 36
I 36
#include <errno.h>
#include <fcntl.h>
I 39
#include <fnmatch.h>
#include <glob.h>
#include <signal.h>
E 39
#include <stdio.h>
E 36
I 24
#include <stdlib.h>
I 36
#include <string.h>
#include <unistd.h>

I 39
#include "config.h"
E 39
E 36
E 24
E 23
I 22
#include "pathnames.h"
E 22

D 2
#define	DEF_PAGER	"more -s"	/* paging filter */
#define	DEF_PATH	"/usr/man"	/* default path */
#define	NO		0		/* no/false */
#define	YES		1		/* yes/true */
E 2
I 2
D 5
#define	DEF_PAGER	"more -s"
E 5
I 5
D 22
#define	DEF_PAGER	"/usr/ucb/more -s"
E 5
D 8
#define	DEF_PATH	"/usr/man:/usr/local/man"
E 8
I 8
#define	DEF_PATH	"/usr/man:/usr/new/man:/usr/local/man"
D 15

E 15
E 8
#define	LOCAL_PATH	"/usr/local/man"
D 15
#define	LOCAL_NAME	"local"
I 8

E 15
#define	NEW_PATH	"/usr/new/man"
D 15
#define	NEW_NAME	"new"
E 15

E 8
D 17
#define	NO		0
#define	YES		1
E 17
I 17
#define	NO	0
#define	YES	1
E 17
E 2

E 22
D 2
/*
 * See code for more info on this kludge; suffice it to say that the
 * local, new and old defines *have* to map into the dirlist array
 * correctly.  Notice also that cat1 is in array slot 1, etc. etc.
 * Continue to notice that it's also ordered for searching, i.e.
 * slots 1 - N are in the order you wish to search the directories.
 */
E 2
D 15
#define	NO_SECTION	0
D 2
#define	LOCAL_SECTION	9
#define	NEW_SECTION	10
#define	OLD_SECTION	11
#define	isname(x)	(x==LOCAL_SECTION || x==NEW_SECTION || x==OLD_SECTION)
static char	*machine,		/* machine type */
		*manpath,		/* search path */
		*pager,			/* pager */
		*dirlist[] = {		/* sub-directory list */
	"notused", 	"cat1",		"cat2",		"cat3",
	"cat4",		"cat5",		"cat6",		"cat7",
	"cat8",		"local",	"new",		"old",
	NULL,
E 2
I 2
#define	S_THREEF	9
D 8
#define	S_NEW		10
#define	S_OLD		11
E 8
I 8
#define	S_OLD		10
E 8

D 4
/* this array maps a character (ex: '4') to an offset in dirlist */
E 4
I 4
/* this array maps a character (ex: '4') to an offset in stanlist */
E 4
#define	secno(x)	(seclist[(int)(x - '0')])
static int	seclist[] = { -1, 1, 4, 5, 6, 7, 3, 8, 2, -1, -1 };

/* sub directory list, ordered for searching */
E 15
D 4
typedef struct something_meaningful {
E 4
I 4
D 17
typedef struct {
E 4
D 15
	char	*name,
		*msg;
E 15
I 15
	char	*name, *msg;
E 15
} DIR;

E 17
D 4
DIR	dirlist[] = {		/* sub-directory list */
E 4
I 4
D 15
DIR	stanlist[] = {		/* standard sub-directory list */
E 4
	"notused", "",		"cat1", "1st",		"cat8", "8th",
	"cat6", "6th",		"cat2", "2nd",		"cat3", "3rd",
	"cat4", "4th",		"cat5", "5th", 		"cat7", "7th",
D 4
	"cat3f", "3rd (F)",	"new", "new",		"old", "old",
E 4
I 4
D 8
	"cat3f", "3rd (F)",	"cat.new", "new",	"cat.old", "old",
E 4
	NULL, NULL,
E 8
I 8
	"cat3f", "3rd (F)",	"cat.old", "old",	NULL, NULL,
E 8
I 4
},	sec1list[] = {		/* section one list */
	"notused", "",		"cat1", "1st",		"cat8", "8th",
D 8
	"cat6", "6th",		"cat.new", "new",	"cat.old", "old",
	NULL, NULL,
E 8
I 8
	"cat6", "6th",		"cat.old", "old",	NULL, NULL,
E 8
E 4
E 2
};

I 4
static DIR	*dirlist;		/* list of directories to search */
E 15
E 4
D 2
static int	nomore;			/* don't use more */
E 2
I 2
D 11
static int	nomore;			/* copy file to stdout */
E 11
I 11
D 18
static int	nomore,			/* copy file to stdout */
		where;			/* just tell me where */
E 18
E 11
D 17
static char	*defpath,		/* default search path */
E 17
I 17
D 23
static char	*command,		/* command buffer */
		*defpath,		/* default search path */
E 17
		*locpath,		/* local search path */
		*machine,		/* machine type */
		*manpath,		/* current search path */
I 8
		*newpath,		/* new search path */
E 8
D 18
		*pager;			/* requested pager */
E 18
I 18
		*pager,			/* requested pager */
		how;			/* how to display */
E 23
I 23
D 39
extern int errno;
E 39
I 39
int f_all, f_where;
E 39
E 23
E 18
E 2

I 18
D 23
#define	ALL	0x1			/* show all man pages */
#define	CAT	0x2			/* copy file to stdout */
#define	WHERE	0x4			/* just tell me where */
E 23
I 23
D 24
char *command, *machine, *p_augment, *p_path, *pager, *progname;
E 24
D 28
int f_all, f_cat, f_where;
E 28
I 28
D 39
int f_all, f_cat, f_how, f_where;
E 28
I 24
char *command, *machine, *p_augment, *p_path, *pager, *progname;
I 26
D 27
char **arorder, *pathbuf;
E 27
I 27
extern char **arorder, *pathbuf;
E 39
I 39
D 45
static void	 build_page __P((char *, char *));
E 45
I 45
static void	 build_page __P((char *, char **));
E 45
static void	 cat __P((char *));
static char	*check_pager __P((char *));
D 47
static void	 cleanup __P((void));
E 47
I 47
static int	 cleanup __P((void));
E 47
static void	 how __P((char *));
static void	 jump __P((char **, char *, char *));
D 47
static int	 manual __P((char *, ENTRY *, glob_t *));
E 47
I 47
static int	 manual __P((char *, TAG *, glob_t *));
E 47
static void	 onsig __P((int));
static void	 usage __P((void));
E 39
E 27
E 26
E 24
E 23

I 39
int
E 39
E 18
main(argc, argv)
D 15
	int	argc;
D 2
	char	**argv;
E 2
I 2
	register char	**argv;
E 15
I 15
	int argc;
D 39
	register char **argv;
E 39
I 39
	char *argv[];
E 39
E 15
E 2
{
D 15
	int	section;
	char	**arg_start, **arg,
D 5
		*getenv();
E 5
I 5
		*getenv(), *malloc();
E 15
I 15
D 18
	char **arg_start, **arg, *getenv(), *malloc(), *strcpy();
E 18
I 18
	extern char *optarg;
	extern int optind;
D 24
	int ch;
D 23
	char *getenv(), *malloc();
E 23
I 23
	char *check_pager(), *config(), *getenv();
E 24
I 24
D 39
	int ch, res;
D 26
	char *section[2], *check_pager(), *getpath();
E 26
I 26
	char *section[2], *check_pager(), *getpath(), **getorder(), *tmp;
E 39
I 39
D 45
	ENTRY *defp, *defnewp, *intmpp;
E 45
I 45
D 47
	ENTRY *defp, *defnewp;
E 45
	ENTRY *section, *sectp, *sectnewp, *subp, *tp;
E 47
I 47
	TAG *defp, *defnewp, *section, *sectnewp, *subp;
	ENTRY *e_defp, *e_sectp, *e_subp, *ep;
E 47
	glob_t pg;
	size_t len;
	int ch, f_cat, f_how, found;
	char **ap, *cmd, *machine, *p, *p_add, *p_path, *pager, *slashp;
D 40
	char buf[MAXPATHLEN * 2];
E 40
I 40
	char *conffile, buf[MAXPATHLEN * 2];
E 40
E 39
E 26
E 24
E 23
E 18
E 15
E 5

I 40
D 48
	conffile = NULL;
E 48
E 40
D 18
	arg_start = argv;
	for (--argc, ++argv; argc && (*argv)[0] == '-'; --argc, ++argv)
		switch((*argv)[1]) {
		case 0:			/* just write to stdout */
			nomore = YES;
E 18
I 18
D 23
	while ((ch = getopt(argc, argv, "-M:P:afkw")) != EOF)
E 23
I 23
D 39
	progname = "man";
E 39
I 39
	f_cat = f_how = 0;
I 48
	conffile = p_add = p_path = NULL;
E 48
E 39
D 28
	while ((ch = getopt(argc, argv, "-acfkM:m:P:w")) != EOF)
E 28
I 28
D 40
	while ((ch = getopt(argc, argv, "-acfhkM:m:P:w")) != EOF)
E 40
I 40
	while ((ch = getopt(argc, argv, "-aC:cfhkM:m:P:w")) != EOF)
E 40
E 28
E 23
D 39
		switch((char)ch) {
E 39
I 39
		switch (ch) {
E 39
D 23
		case '-':
			how |= CAT;
E 23
I 23
		case 'a':
			f_all = 1;
E 23
E 18
			break;
I 40
		case 'C':
			conffile = optarg;
			break;
E 40
I 23
		case 'c':
D 39
		case '-':		/* deprecated */
E 39
I 39
		case '-':		/* Deprecated. */
E 39
			f_cat = 1;
			break;
I 28
		case 'h':
			f_how = 1;
			break;
E 28
		case 'm':
D 39
			p_augment = optarg;
E 39
I 39
			p_add = optarg;
E 39
			break;
E 23
		case 'M':
D 39
		case 'P':		/* backward compatibility */
E 39
I 39
		case 'P':		/* Backward compatibility. */
E 39
D 18
			if ((*argv)[2])
D 6
				manpath = *argv + 2;
E 6
I 6
				defpath = *argv + 2;
E 6
			else {
				if (argc < 2) {
					fprintf(stderr, "%s: missing path\n", *argv);
					exit(1);
				}
				--argc;
D 6
				manpath = *++argv;
E 6
I 6
				defpath = *++argv;
E 6
			}
E 18
I 18
D 23
			defpath = optarg;
E 23
I 23
			p_path = optarg;
E 23
E 18
			break;
I 18
D 23
		case 'a':
			how |= ALL;
			break;
E 18
		/*
D 17
		 * "man -f" and "man -k" are undocumented ways of calling
		 * whatis(1) and apropos(1).  Just strip out the flag
		 * argument and jump.
E 17
I 17
		 * "man -f" and "man -k" are backward contemptible,
		 * undocumented ways of calling whatis(1) and apropos(1).
D 18
		 * Just strip out the flag argument and jump.
E 18
E 17
		 */
E 23
I 23
D 24
			/*
			 * "man -f" and "man -k" are backward compatible,
			 * undocumented ways of calling whatis(1) and
			 * apropos(1).
			 */
E 24
I 24
		/*
D 39
		 * "man -f" and "man -k" are backward compatible, undocumented
		 * ways of calling whatis(1) and apropos(1).
E 39
I 39
		 * The -f and -k options are backward compatible,
		 * undocumented ways of calling whatis(1) and apropos(1).
E 39
		 */
E 24
E 23
		case 'f':
D 18
			for (arg = argv; arg[0] = arg[1]; ++arg);
			*arg_start = "whatis";
			execvp(*arg_start, arg_start);
			fputs("whatis: Command not found.\n", stderr);
			exit(1);
E 18
I 18
			jump(argv, "-f", "whatis");
D 23
			/*NOTREACHED*/
E 23
I 23
			/* NOTREACHED */
E 23
E 18
		case 'k':
D 18
			for (arg = argv; *arg = arg[1]; ++arg);
			*arg_start = "apropos";
			execvp(*arg_start, arg_start);
			fputs("apropos: Command not found.\n", stderr);
			exit(1);
E 18
I 18
			jump(argv, "-k", "apropos");
D 23
			/*NOTREACHED*/
E 18
I 15
		/*
		 * Deliberately undocumented; really only useful when
		 * you're moving man pages around.  Not worth adding.
		 */
E 23
I 23
			/* NOTREACHED */
E 23
E 15
I 11
		case 'w':
D 15
			/*
			 * Deliberately undocumented; really only useful when
			 * you're moving man pages around.  Not worth adding.
			 */
E 15
D 18
			where = YES;
E 18
I 18
D 23
			how |= WHERE | ALL;
E 23
I 23
			f_all = f_where = 1;
E 23
E 18
			break;
E 11
		case '?':
		default:
I 12
D 18
			fprintf(stderr, "man: illegal option -- %c\n", (*argv)[1]);
E 12
D 15
			usage();
E 15
I 15
			goto usage;
E 18
I 18
			usage();
E 18
E 15
		}
I 38
	argc -= optind;
E 38
I 18
	argv += optind;
E 18
D 15
	if (!argc)
		usage();
E 15

I 15
D 18
	if (!argc) {
usage:		fputs("usage: man [-] [-M path] [section] title ...\n", stderr);
		exit(1);
	}
E 18
I 18
	if (!*argv)
		usage();
E 18

E 15
D 18
	if (!nomore)
E 18
I 18
D 23
	if (!(how & CAT))
E 23
I 23
D 28
	if (!f_cat)
E 28
I 28
D 51
	if (!f_cat && !f_how)
E 51
I 51
	if (!f_cat && !f_how && !f_where)
E 51
E 28
E 23
E 18
		if (!isatty(1))
D 18
			nomore = YES;
E 18
I 18
D 23
			how |= CAT;
E 18
D 5
		else if (!(pager = getenv("PAGER")))
E 5
I 5
		else if (pager = getenv("PAGER")) {
D 15
			register char	*C;
E 15
I 15
			register char *p;
E 15

			/*
			 * if the user uses "more", we make it "more -s"
			 * watch out for PAGER = "mypager /usr/ucb/more"
			 */
D 15
			for (C = pager; *C && !isspace(*C); ++C);
			for (; C > pager && *C != '/'; --C);
			if (C != pager)
				++C;
E 15
I 15
			for (p = pager; *p && !isspace(*p); ++p);
			for (; p > pager && *p != '/'; --p);
			if (p != pager)
				++p;
E 15
			/* make sure it's "more", not "morex" */
D 15
			if (!strncmp(C, "more", 4) && (!C[4] || isspace(C[4]))) {
				C += 4;
E 15
I 15
D 19
			if (!strncmp(p, "more", 4) && (!p[4] || isspace(p[4]))) {
				p += 4;
E 19
I 19
			if (!strncmp(p, "more", 4) && (!p[4] || isspace(p[4]))){
				char *opager = pager;
E 19
E 15
				/*
D 15
				 * sizeof is 1 more than # of chars, so,
E 15
D 19
				 * allocate for the rest of the PAGER
				 * environment variable, a space, and the EOS.
E 19
I 19
				 * allocate space to add the "-s"
E 19
				 */
D 15
				if (!(pager = malloc((u_int)(strlen(C) + sizeof(DEF_PAGER) + 1)))) {
E 15
I 15
D 19
				if (!(pager = malloc((u_int)(strlen(p) + sizeof(DEF_PAGER) + 1)))) {
E 19
I 19
				if (!(pager = malloc((u_int)(strlen(opager) 
				    + sizeof("-s") + 1)))) {
E 19
E 15
					fputs("man: out of space.\n", stderr);
					exit(1);
				}
D 15
				(void)sprintf(pager, "%s %s", DEF_PAGER, C);
E 15
I 15
D 19
				(void)sprintf(pager, "%s %s", DEF_PAGER, p);
E 19
I 19
				(void)sprintf(pager, "%s %s", opager, "-s");
E 19
E 15
			}
		}
E 23
I 23
			f_cat = 1;
D 45
		else if (pager = getenv("PAGER"))
E 45
I 45
		else if ((pager = getenv("PAGER")) != NULL)
E 45
			pager = check_pager(pager);
E 23
		else
E 5
D 22
			pager = DEF_PAGER;
E 22
I 22
			pager = _PATH_PAGER;
I 23

E 23
E 22
D 39
	if (!(machine = getenv("MACHINE")))
E 39
I 39
	/* Read the configuration file. */
D 40
	config();
E 40
I 40
	config(conffile);
E 40

D 47
	/* If there's no _default list, create an empty one. */
	if ((defp = getlist("_default")) == NULL)
		defp = addlist("_default");

E 47
	/* Get the machine type. */
	if ((machine = getenv("MACHINE")) == NULL)
E 39
		machine = MACHINE;
D 2
	if (!manpath && !(manpath = getenv("MANPATH")))
		manpath = DEF_PATH;
	for (; *manpath && *manpath == ':'; ++manpath);
E 2
I 2
D 23
	if (!defpath && !(defpath = getenv("MANPATH")))
D 22
		defpath = DEF_PATH;
	locpath = LOCAL_PATH;
I 8
	newpath = NEW_PATH;
E 22
I 22
		defpath = _PATH_DEFAULT;
	locpath = _PATH_LOCAL;
	newpath = _PATH_NEW;
E 23
I 23

I 47
	/* If there's no _default list, create an empty one. */
	if ((defp = getlist("_default")) == NULL)
		defp = addlist("_default");

E 47
D 24
	if (!p_path && !(p_path = getenv("MANPATH")))
		p_path = config();
E 24
I 24
D 39
	/* see if checking in a specific section */
	if (argc > 1 && getsection(*argv)) {
		section[0] = *argv++;
		section[1] = (char *)NULL;
	} else {
		section[0] = "_default";
		section[1] = (char *)NULL;
E 39
I 39
	/*
	 * 1: If the user specified a MANPATH variable, or set the -M
	 *    option, we replace the _default list with the user's list,
	 *    appending the entries in the _subdir list and the machine.
	 */
	if (p_path == NULL)
		p_path = getenv("MANPATH");
	if (p_path != NULL) {
D 47
		while ((tp = defp->list.qe_next) != NULL) {
			free(tp->s);
			queue_remove(&defp->list, tp, ENTRY *, list);
E 47
I 47
		while ((e_defp = defp->list.tqh_first) != NULL) {
			free(e_defp->s);
			TAILQ_REMOVE(&defp->list, e_defp, q);
E 47
		}
		for (p = strtok(p_path, ":");
		    p != NULL; p = strtok(NULL, ":")) {
			slashp = p[strlen(p) - 1] == '/' ? "" : "/";
D 47
			subp = getlist("_subdir");
			if (subp != NULL)
				subp = subp->list.qe_next;
			for (; subp != NULL; subp = subp->list.qe_next) {
E 47
I 47
			e_subp = (subp = getlist("_subdir")) == NULL ?
			    NULL : subp->list.tqh_first;
			for (; e_subp != NULL; e_subp = e_subp->q.tqe_next) {
E 47
				(void)snprintf(buf, sizeof(buf), "%s%s%s{/%s,}",
D 47
				    p, slashp, subp->s, machine);
				if ((tp = malloc(sizeof(ENTRY))) == NULL ||
				    (tp->s = strdup(buf)) == NULL)
E 47
I 47
				    p, slashp, e_subp->s, machine);
				if ((ep = malloc(sizeof(ENTRY))) == NULL ||
				    (ep->s = strdup(buf)) == NULL)
E 47
					err(1, NULL);
D 47
				queue_enter_tail(&defp->list,
				    tp, ENTRY *, list);
E 47
I 47
				TAILQ_INSERT_TAIL(&defp->list, ep, q);
E 47
			}
		}
E 39
	}
E 24

E 23
E 22
E 8
D 15
	for (; *defpath && *defpath == ':'; ++defpath);
E 15
I 15
D 24
	man(argv);
E 24
I 24
D 26
	if (!p_path && !(p_path = getenv("MANPATH")) &&
	    !(p_path = getpath(section)) && !p_augment) {
E 26
I 26
D 39
	arorder = getorder();
	if (p_path || (p_path = getenv("MANPATH"))) {
		char buf[MAXPATHLEN], **av;
E 39
I 39
	/*
	 * 2: If the user did not specify MANPATH, -M or a section, rewrite
	 *    the _default list to include the _subdir list and the machine.
	 */
D 49
	if ((section = getlist(*argv)) != NULL)
E 49
I 49
	if (argv[1] == NULL)
		section = NULL;
	else if ((section = getlist(*argv)) != NULL)
E 49
		++argv;
	if (p_path == NULL && section == NULL) {
		defnewp = addlist("_default_new");
D 47
		if (defp->list.qe_next != NULL)
			defp = defp->list.qe_next;
		for (; defp != NULL; defp = defp->list.qe_next) {
			slashp = defp->s[strlen(defp->s) - 1] == '/' ? "" : "/";
			subp = getlist("_subdir");
			if (subp != NULL)
				subp = subp->list.qe_next;
			for (; subp != NULL; subp = subp->list.qe_next) {
E 47
I 47
		e_defp =
		    defp->list.tqh_first == NULL ? NULL : defp->list.tqh_first;
		for (; e_defp != NULL; e_defp = e_defp->q.tqe_next) {
			slashp =
			    e_defp->s[strlen(e_defp->s) - 1] == '/' ? "" : "/";
			e_subp = (subp = getlist("_subdir")) == NULL ?
			    NULL : subp->list.tqh_first;
			for (; e_subp != NULL; e_subp = e_subp->q.tqe_next) {
E 47
				(void)snprintf(buf, sizeof(buf), "%s%s%s{/%s,}",
D 47
				defp->s, slashp, subp->s, machine);
				if ((tp = malloc(sizeof(ENTRY))) == NULL ||
				    (tp->s = strdup(buf)) == NULL)
E 47
I 47
				e_defp->s, slashp, e_subp->s, machine);
				if ((ep = malloc(sizeof(ENTRY))) == NULL ||
				    (ep->s = strdup(buf)) == NULL)
E 47
					err(1, NULL);
D 47
				queue_enter_tail(&defnewp->list,
				    tp, ENTRY *, list);
E 47
I 47
				TAILQ_INSERT_TAIL(&defnewp->list, ep, q);
E 47
			}
		}
		defp = getlist("_default");
D 47
		while ((tp = defp->list.qe_next) != NULL) {
			free(tp->s);
			queue_remove(&defp->list, tp, ENTRY *, list);
E 47
I 47
		while ((e_defp = defp->list.tqh_first) != NULL) {
			free(e_defp->s);
			TAILQ_REMOVE(&defp->list, e_defp, q);
E 47
		}
		free(defp->s);
D 47
		queue_remove(&defp->tags, defp, ENTRY *, tags);
E 47
I 47
		TAILQ_REMOVE(&head, defp, q);
E 47
		defnewp = getlist("_default_new");
		free(defnewp->s);
		defnewp->s = "_default";
		defp = defnewp;
	}
E 39

D 32
		tmp = strtok(p_path, ":"); 
E 32
I 32
D 39
		tmp = strtok(p_path, ":");
E 32
		while (tmp) {
D 29
			(void)sprintf(buf, "%s/", tmp);
E 29
I 29
			(void)snprintf(buf, sizeof(buf), "%s/", tmp);
E 29
			for (av = arorder; *av; ++av)
D 32
                		cadd(buf, strlen(buf), *av);
D 29
			tmp = strtok((char *)NULL, ":"); 
E 29
I 29
			tmp = strtok(NULL, ":"); 
E 32
I 32
				cadd(buf, strlen(buf), *av);
			tmp = strtok(NULL, ":");
E 39
I 39
	/*
	 * 3: If the user set the -m option, insert the user's list before
	 *    whatever list we have, again appending the _subdir list and
	 *    the machine.
	 */
	if (p_add != NULL)
		for (p = strtok(p_add, ":"); p != NULL; p = strtok(NULL, ":")) {
			slashp = p[strlen(p) - 1] == '/' ? "" : "/";
D 47
			subp = getlist("_subdir");
			if (subp != NULL)
				subp = subp->list.qe_next;
			for (; subp != NULL; subp = subp->list.qe_next) {
E 47
I 47
			e_subp = (subp = getlist("_subdir")) == NULL ?
			    NULL : subp->list.tqh_first;
			for (; e_subp != NULL; e_subp = e_subp->q.tqe_next) {
E 47
				(void)snprintf(buf, sizeof(buf), "%s%s%s{/%s,}",
D 47
				    p, slashp, subp->s, machine);
				if ((tp = malloc(sizeof(ENTRY))) == NULL ||
				    (tp->s = strdup(buf)) == NULL)
E 47
I 47
				    p, slashp, e_subp->s, machine);
				if ((ep = malloc(sizeof(ENTRY))) == NULL ||
				    (ep->s = strdup(buf)) == NULL)
E 47
					err(1, NULL);
D 47
				queue_enter_head(&defp->list,
				    tp, ENTRY *, list);
E 47
I 47
				TAILQ_INSERT_HEAD(&defp->list, ep, q);
E 47
			}
E 39
E 32
E 29
		}
D 39
		p_path = pathbuf;
	} else if (!(p_path = getpath(section)) && !p_augment) {
E 26
		(void)fprintf(stderr,
D 26
		    "man: no place to search for those manual pages.\n");
E 26
I 26
			"man: no place to search for those manual pages.\n");
E 26
		exit(1);
E 39
I 39

	/*
	 * 4: If none of MANPATH, -M, or -m were specified, and a section was,
	 *    rewrite the section's paths (if they have a trailing slash) to
	 *    append the _subdir list and the machine.  This then becomes the
	 *    _default list.
	 */
	if (p_path == NULL && p_add == NULL && section != NULL) {
		sectnewp = addlist("_section_new");
D 47
		if ((sectp = section)->list.qe_next != NULL)
			sectp = sectp->list.qe_next;
D 41
		while (sectp != NULL) {
E 41
I 41
		for (; sectp != NULL; sectp = sectp->list.qe_next) {
E 41
			if (sectp->s[strlen(sectp->s) - 1] != '/') {
E 47
I 47
		for (e_sectp = section->list.tqh_first;
		    e_sectp != NULL; e_sectp = e_sectp->q.tqe_next) {
			if (e_sectp->s[strlen(e_sectp->s) - 1] != '/') {
E 47
D 41
				tp = sectp;
				sectp = sectp->list.qe_next;
				queue_remove(&section->list, tp, ENTRY *, list);
E 41
I 41
				(void)snprintf(buf, sizeof(buf),
D 47
				    "%s{/%s,}", sectp->s, machine);
				if ((tp = malloc(sizeof(ENTRY))) == NULL ||
				    (tp->s = strdup(buf)) == NULL)
E 47
I 47
				    "%s{/%s,}", e_sectp->s, machine);
				if ((ep = malloc(sizeof(ENTRY))) == NULL ||
				    (ep->s = strdup(buf)) == NULL)
E 47
					err(1, NULL);
E 41
D 47
				queue_enter_tail(&sectnewp->list,
				    tp, ENTRY *, list);
E 47
I 47
				TAILQ_INSERT_TAIL(&sectnewp->list, ep, q);
E 47
				continue;
			}
D 47
			subp = getlist("_subdir");
			if (subp != NULL)
				subp = subp->list.qe_next;
			for (; subp != NULL; subp = subp->list.qe_next) {
				(void)snprintf(buf, sizeof(buf),
				    "%s%s{/%s,}", sectp->s, subp->s, machine);
				if ((tp = malloc(sizeof(ENTRY))) == NULL ||
				    (tp->s = strdup(buf)) == NULL)
E 47
I 47
			e_subp = (subp = getlist("_subdir")) == NULL ?
			    NULL : subp->list.tqh_first;
			for (; e_subp != NULL; e_subp = e_subp->q.tqe_next) {
				(void)snprintf(buf, sizeof(buf), "%s%s{/%s,}",
				    e_sectp->s, e_subp->s, machine);
				if ((ep = malloc(sizeof(ENTRY))) == NULL ||
				    (ep->s = strdup(buf)) == NULL)
E 47
					err(1, NULL);
D 47
				queue_enter_tail(&sectnewp->list,
				    tp, ENTRY *, list);
E 47
I 47
				TAILQ_INSERT_TAIL(&sectnewp->list, ep, q);
E 47
			}
D 41
			sectp = sectp->list.qe_next;
E 41
		}
		sectnewp->s = section->s;
		defp = sectnewp;
D 47
		queue_remove(&section->tags, section, ENTRY *, tags);
E 47
I 47
		TAILQ_REMOVE(&head, section, q);
E 47
E 39
	}
E 24
I 23

I 24
D 39
	for (; *argv; ++argv) {
		if (p_augment)
			res = manual(p_augment, *argv);
		res = manual(p_path, *argv);
D 30
		if (res || f_where)
			continue;
		(void)fprintf(stderr,
		    "man: no entry for %s in the manual.\n", *argv);
		exit(1);
E 30
I 30
		if (!res && !f_where)
			(void)fprintf(stderr,
			    "man: no entry for %s in the manual.\n", *argv);
E 39
I 39
	/*
	 * 5: Search for the files.  Set up an interrupt handler, so the
	 *    temporary files go away.
	 */
	(void)signal(SIGINT, onsig);
I 47
	(void)signal(SIGHUP, onsig);
E 47

	memset(&pg, 0, sizeof(pg));
	for (found = 0; *argv; ++argv)
		if (manual(*argv, defp, &pg))
			found = 1;

D 46
	/*
	 * 7: If nothing found, we're done.
	 */
E 46
I 46
	/* 6: If nothing found, we're done. */
E 46
	if (!found) {
D 47
		cleanup();
E 47
I 47
		(void)cleanup();
E 47
		exit (1);
E 39
E 30
	}

E 24
E 23
I 17
D 20
	/* use system(3) in case someone's pager is "foo arg1 arg2" */
E 20
I 20
D 39
	/* use system(3) in case someone's pager is "pager arg1 arg2" */
E 20
	if (command)
		(void)system(command);
E 39
I 39
D 46
	/* 8: If it's simple, display it fast. */
E 46
I 46
	/* 7: If it's simple, display it fast. */
E 46
	if (f_cat) {
D 44
		found = 0;
E 44
		for (ap = pg.gl_pathv; *ap != NULL; ++ap) {
D 43
			if (*ap == '\0')
E 43
I 43
			if (**ap == '\0')
E 43
				continue;
			cat(*ap);
D 44
			if (!f_all) {
				found = 1;
				break;
			}
E 44
		}
D 44
		if (!found) {
			if (intmpp != NULL)
				intmpp = intmpp->list.qe_next;
			for (; intmpp != NULL; intmpp = intmpp->list.qe_next) {
				cat(intmpp->s);
				if (!f_all)
					break;
			}
		}
E 44
I 44
D 45
		if (intmpp != NULL)
			intmpp = intmpp->list.qe_next;
		for (; intmpp != NULL; intmpp = intmpp->list.qe_next)
			cat(intmpp->s);
E 45
E 44
D 47
		cleanup();
		exit (0);
E 47
I 47
		exit (cleanup());
E 47
	}
	if (f_how) {
D 44
		found = 0;
E 44
		for (ap = pg.gl_pathv; *ap != NULL; ++ap) {
D 43
			if (*ap == '\0')
E 43
I 43
			if (**ap == '\0')
E 43
				continue;
			how(*ap);
D 44
			if (!f_all) {
				found = 1;
				break;
			}
E 44
		}
D 44
		if (!found) {
			intmpp = getlist("_intmp");
			if (intmpp != NULL)
				intmpp = intmpp->list.qe_next;
			for (; intmpp != NULL; intmpp = intmpp->list.qe_next) {
				how(intmpp->s);
				if (!f_all)
					break;
			}
		}
E 44
I 44
D 45
		intmpp = getlist("_intmp");
		if (intmpp != NULL)
			intmpp = intmpp->list.qe_next;
		for (; intmpp != NULL; intmpp = intmpp->list.qe_next)
			how(intmpp->s);
E 45
E 44
D 47
		cleanup();
		exit (0);
E 47
I 47
		exit(cleanup());
E 47
	}
	if (f_where) {
		for (ap = pg.gl_pathv; *ap != NULL; ++ap) {
D 43
			if (*ap == '\0')
E 43
I 43
			if (**ap == '\0')
E 43
				continue;
			(void)printf("%s\n", *ap);
		}
D 45
		intmpp = getlist("_intmp");
		if (intmpp != NULL)
			intmpp = intmpp->list.qe_next;
		for (; intmpp != NULL; intmpp = intmpp->list.qe_next)
			(void)printf("%s\n", intmpp->s);
E 45
D 47
		cleanup();
		exit (0);
E 47
I 47
		exit(cleanup());
E 47
	}
		
	/*
D 46
	 * 9: We display things in a single command; build a list of things
E 46
I 46
	 * 8: We display things in a single command; build a list of things
E 46
	 *    to display.
	 */
D 44
	found = 0;
E 44
	for (ap = pg.gl_pathv, len = strlen(pager) + 1; *ap != NULL; ++ap) {
		if (**ap == '\0')
			continue;
		len += strlen(*ap) + 1;
D 44
		if (!f_all) {
			found = 1;
			break;
		}
E 44
	}
D 44
	if (!found) {
		intmpp = getlist("_intmp");
		if (intmpp != NULL)
			intmpp = intmpp->list.qe_next;
		for (; intmpp != NULL; intmpp = intmpp->list.qe_next) {
			len += strlen(intmpp->s);
			if (!f_all)
				break;
		}
	}
E 44
I 44
D 45
	intmpp = getlist("_intmp");
	if (intmpp != NULL)
		intmpp = intmpp->list.qe_next;
	for (; intmpp != NULL; intmpp = intmpp->list.qe_next)
		len += strlen(intmpp->s);
E 44

E 45
	if ((cmd = malloc(len)) == NULL) {
D 47
		cleanup();
		err(1, NULL);
E 47
I 47
		warn(NULL);
		(void)cleanup();
		exit(1);
E 47
	}
	p = cmd;
	len = strlen(pager);
	memmove(p, pager, len);
	p += len;
	*p++ = ' ';
D 44
	found = 0;
E 44
	for (ap = pg.gl_pathv; *ap != NULL; ++ap) {
		if (**ap == '\0')
			continue;
		len = strlen(*ap);
		memmove(p, *ap, len);
		p += len;
		*p++ = ' ';
D 44
		if (!f_all) {
			found = 1;
			break;
		}
E 44
	}
D 44
	if (!found) {
		intmpp = getlist("_intmp");
		if (intmpp != NULL)
			intmpp = intmpp->list.qe_next;
		for (; intmpp != NULL; intmpp = intmpp->list.qe_next) {
			len = strlen(intmpp->s);
			memmove(p, intmpp->s, len);
			p += len;
			*p++ = ' ';
		}
E 44
I 44
D 45
	intmpp = getlist("_intmp");
	if (intmpp != NULL)
		intmpp = intmpp->list.qe_next;
	for (; intmpp != NULL; intmpp = intmpp->list.qe_next) { 
		len = strlen(intmpp->s);
		memmove(p, intmpp->s, len);
		p += len;
		*p++ = ' ';
E 44
	}
E 45
	*p = '\0';

	/* Use system(3) in case someone's pager is "pager arg1 arg2". */
	(void)system(cmd);

D 47
	cleanup();
E 39
E 17
	exit(0);
E 47
I 47
	exit(cleanup());
E 47
}
E 15
E 2

I 17
D 24
typedef struct {
	char	*name, *msg;
} DIR;
E 17
I 4
D 15
	/* Gentlemen... start your kludges! */
E 15
I 15
static DIR	list1[] = {		/* section one list */
	"cat1", "1st",		"cat8", "8th",		"cat6", "6th",
	"cat.old", "old",	NULL, NULL,
},		list2[] = {		/* rest of the list */
	"cat2", "2nd",		"cat3", "3rd",		"cat4", "4th",
	"cat5", "5th", 		"cat7", "7th",		"cat3f", "3rd (F)",
	NULL, NULL,
},		list3[2];		/* single section */

E 24
D 23
static
E 23
I 23
/*
D 24
 * man --
 *	main loop to find the manual page and print it out.
 */
E 23
man(argv)
	char **argv;
{
D 23
	register char *p;
E 23
	DIR *section, *getsect();
	int res;

E 15
E 4
	for (; *argv; ++argv) {
D 15
		section = NO_SECTION;
E 15
I 2
D 6
		manpath = DEF_PATH;
E 6
I 6
D 23
		manpath = defpath;
I 15
		section = NULL;
E 15
E 6
I 4
D 8
		dirlist = stanlist;
E 8
E 4
E 2
		switch(**argv) {
D 2
		/*
		 * hardwired section numbers, fix here if they do; note,
		 * only works for single digits.
		 */
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8':
E 2
I 2
D 4
		/* hardwired section numbers, fix here if they change */
		case '1': case '2': case '4': case '5': case '6':
E 4
I 4
D 15
		/*
D 8
		 * Section 1 requests are really for section 1, 6, 8, new and
		 * old.  Since new and old aren't broken up into a directory
		 * of cat[1-8], we just pretend that they are a subdirectory
		 * of /usr/man.  Should be fixed -- make new and old full
		 * structures just like local is, get rid of "sec1list" and
		 * dirlist.
E 8
I 8
		 * Section 1 requests are really for section 1, 6, 8, in the
		 * standard, local and new directories and section old. Since
		 * old isn't broken up into a directory of cat[1-8], we just
		 * treat it like a subdirectory of the others.
E 8
		 */
D 8
		case '1':
			if (!(*argv)[1]) {
				dirlist = sec1list;
				goto numtest;
			}
			break;

		case '2': case '4': case '5': case '6':
E 8
I 8
		case '1': case '2': case '4': case '5': case '6':
E 8
E 4
		case '7': case '8':
E 2
			if (!(*argv)[1]) {
D 2
				section = (*argv)[0] - '0';
E 2
I 2
				section = secno((*argv)[0]);
				goto numtest;
E 15
I 15
		case 'l':				/* local */
I 20
			/* support the "{l,local,n,new}###"  syntax */
E 20
			for (p = *argv; isalpha(*p); ++p);
			if (!strncmp(*argv, "l", p - *argv) ||
			    !strncmp(*argv, "local", p - *argv)) {
I 20
				++argv;
E 20
				manpath = locpath;
D 20
				if (section = getsect(p))
					goto argtest;
E 20
I 20
				section = getsect(p);
E 20
E 15
			}
			break;
I 4
D 15

		/* sect. 3 requests are for either section 3, or section 3F. */
E 4
		case '3':
			if (!(*argv)[1]) {			/* "3" */
				section = secno((*argv)[0]);
numtest:			if (!*++argv) {
D 4
					fprintf(stderr, "man: what do you want from the %s section of the manual?\n", dirlist[section].msg);
E 4
I 4
					fprintf(stderr, "man: what do you want from the %s section of the manual?\n", stanlist[section].msg);
E 4
					exit(1);
				}
			}					/* "3[fF]" */
D 8
			if (((*argv)[1] == 'f'  || (*argv)[1] == 'F') && !(*argv)[2]) {
E 8
I 8
			else if (((*argv)[1] == 'f'  || (*argv)[1] == 'F') && !(*argv)[2]) {
E 8
				section = S_THREEF;
E 2
				if (!*++argv) {
D 2
					fprintf(stderr, "man: what do you want from section %d?\n", section);
E 2
I 2
D 4
					fprintf(stderr, "man: what do you want from the %s section of the manual?\n", dirlist[S_THREEF].msg);
E 4
I 4
					fprintf(stderr, "man: what do you want from the %s section of the manual?\n", stanlist[S_THREEF].msg);
E 4
E 2
					exit(1);
				}
E 15
I 15
		case 'n':				/* new */
			for (p = *argv; isalpha(*p); ++p);
			if (!strncmp(*argv, "n", p - *argv) ||
			    !strncmp(*argv, "new", p - *argv)) {
I 20
				++argv;
E 20
				manpath = newpath;
D 20
				if (section = getsect(p))
					goto argtest;
E 20
I 20
				section = getsect(p);
E 20
E 15
			}
			break;
I 4
		/*
D 8
		 * Requests for the local section can have subsection numbers
		 * appended to them, i.e. "local3" is really local/cat3.
E 8
I 8
D 15
		 * Requests for the new or local sections can have subsection
		 * numbers appended to them, i.e. "local3" is really
		 * local/cat3.
E 15
I 15
		 * old isn't really a separate section of the manual,
		 * and its entries are all in a single directory.
E 15
E 8
		 */
E 4
D 2
		/*
		 * backward compatibility: manl == local, mann == new,
		 * mano == old;
		 */
		case 'l':
			if (!*argv[1] || !strcmp(*argv, dirlist[LOCAL_SECTION])) {
				section = LOCAL_SECTION;
				goto argtest;
E 2
I 2
D 15
		case 'l':					/* local */
			if (!(*argv)[1])			/* "l" */
				section = NO_SECTION;		/* "l2" */
			else if (isdigit((*argv)[1]) && !(*argv)[2])
				section = secno((*argv)[1]);
			else {
				int	lex;
				lex = strcmp(LOCAL_NAME, *argv);
				if (!lex)			/* "local" */
					section = NO_SECTION;	/* "local2" */
				else if (lex < 0 && isdigit((*argv)[sizeof(LOCAL_NAME) - 1]) && !(*argv)[sizeof(LOCAL_NAME)])
					section = secno((*argv)[sizeof(LOCAL_NAME) - 1]);
				else
					break;
E 15
I 15
		case 'o':				/* old */
			for (p = *argv; isalpha(*p); ++p);
			if (!strncmp(*argv, "o", p - *argv) ||
			    !strncmp(*argv, "old", p - *argv)) {
I 20
				++argv;
E 20
				list3[0] = list1[3];
				section = list3;
D 20
				goto argtest;
E 20
E 15
E 2
			}
I 2
D 15
			if (!*++argv) {
				fputs("man: what do you want from the local section of the manual?\n", stderr);
				exit(1);
			}
			manpath = locpath;
E 15
E 2
			break;
D 2
		case 'n':
			if (!*argv[1] || !strcmp(*argv, dirlist[NEW_SECTION])) {
				section = NEW_SECTION;
				goto argtest;
E 2
I 2
D 15
		case 'n':					/* new */
D 3
			if (!*argv[1] || !strcmp(*argv, dirlist[S_NEW].name)) {
E 3
I 3
D 4
			if (!(*argv)[1] || !strcmp(*argv, dirlist[S_NEW].name)) {
E 4
I 4
D 8
			if (!(*argv)[1] || !strcmp(*argv, stanlist[S_NEW].msg)) {
E 4
E 3
				section = S_NEW;
				goto strtest;
E 8
I 8
			if (!(*argv)[1])			/* "n" */
				section = NO_SECTION;		/* "n2" */
			else if (isdigit((*argv)[1]) && !(*argv)[2])
				section = secno((*argv)[1]);
			else {
				int	lex;
				lex = strcmp(NEW_NAME, *argv);
				if (!lex)			/* "new" */
					section = NO_SECTION;	/* "new2" */
				else if (lex < 0 && isdigit((*argv)[sizeof(NEW_NAME) - 1]) && !(*argv)[sizeof(NEW_NAME)])
					section = secno((*argv)[sizeof(NEW_NAME) - 1]);
				else
					break;
E 8
E 2
			}
I 8
			if (!*++argv) {
				fputs("man: what do you want from the new section of the manual?\n", stderr);
E 15
I 15
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8':
D 20
			if (!(section = getsect(*argv)))
				break;
argtest:		if (!*++argv) {
				fprintf(stderr, "man: what do you want from the %s section of the manual?\n", section->msg);
E 15
				exit(1);
E 20
I 20
			if (section = getsect(*argv))
				++argv;
		}

E 23
I 23
		section = isdigit(**argv) ? getsect(*argv++) : NULL;
E 23
		if (*argv) {
D 23
			if (section)
				res = manual(section, *argv);
			else {
				res = manual(list1, *argv);
				if (!res || (how & ALL))
					res += manual(list2, *argv);
E 20
			}
I 20
			if (res || how&WHERE)
E 23
I 23
			if (p_augment)
				if (section)
					res = manual(p_augment, section, *argv);
				else {
					res = manual(p_augment, list1, *argv);
					if (!res || f_all)
						res += manual(p_augment, list2,
						    *argv);
				}
			if (p_path)
				if (section)
					res = manual(p_path, section, *argv);
				else {
					res = manual(p_path, list1, *argv);
					if (!res || f_all)
						res += manual(p_path, list2,
						    *argv);
				}
			if (res || f_where)
E 23
				continue;
E 20
D 15
			manpath = newpath;
E 8
			break;
D 2
		case 'o':
			if (!*argv[1] || !strcmp(*argv, dirlist[OLD_SECTION])) {
				section = OLD_SECTION;
argtest:			if (!*++argv) {
					fprintf(stderr, "man: what do you want from the %s section?\n", dirlist[section]);
E 2
I 2
		case 'o':					/* old */
D 3
			if (!*argv[1] || !strcmp(*argv, dirlist[S_OLD].name)) {
E 3
I 3
D 4
			if (!(*argv)[1] || !strcmp(*argv, dirlist[S_OLD].name)) {
E 4
I 4
			if (!(*argv)[1] || !strcmp(*argv, stanlist[S_OLD].msg)) {
E 4
E 3
				section = S_OLD;
D 8
strtest:			if (!*++argv) {
E 8
I 8
				if (!*++argv) {
E 8
D 4
					fprintf(stderr, "man: what do you want from the %s section of the manual?\n", dirlist[section].msg);
E 4
I 4
					fprintf(stderr, "man: what do you want from the %s section of the manual?\n", stanlist[section].msg);
E 4
E 2
					exit(1);
				}
			}
			break;
E 15
D 23
		}
I 8
D 15
		if (section == 1) {
			dirlist = sec1list;
			section = NO_SECTION;
		}
		else
			dirlist = stanlist;
E 8
I 4
		/*
		 * This is really silly, but I wanted to put out rational
		 * errors, not just "I couldn't find it."  This if statement
		 * knows an awful lot about what gets assigned to what in
		 * the switch statement we just passed through.  Sorry.
		 */
E 4
D 11
		if (!manual(section, *argv))
E 11
I 11
		if (!manual(section, *argv) && !where)
E 15
I 15

I 20
		fputs("man: ", stderr);
		if (*argv)
			fprintf(stderr, "no entry for %s in the ", *argv);
		else
			fputs("what do you want from the ", stderr);
E 23
I 23
			(void)fprintf(stderr,
			    "man: no entry for %s in the ", *argv);
		} else
			(void)fprintf(stderr,
			    "man: what do you want from the ");
E 23
E 20
D 17
		res = section ? manual(section, *argv) :
		    manual(list1, *argv) || manual(list2, *argv);
		if (!res && !where)
E 17
I 17
		if (section)
D 20
			res = manual(section, *argv);
		else {
			res = manual(list1, *argv);
D 18
			res += manual(list2, *argv);
E 18
I 18
			if (!res || (how & ALL))
				res += manual(list2, *argv);
E 18
		}
D 18
		if (!res && !where) {
E 18
I 18
		if (!res && !(how & WHERE)) {
E 18
E 17
E 15
E 11
D 2
			if (section == NO_SECTION)
				fprintf(stderr, "No manual entry for %s.\n", *argv);
			else if (isname(section))
				fprintf(stderr, "No entry for %s in the %s section of the manual.\n", *argv, dirlist[section]);
E 2
I 2
			if (manpath == locpath)
D 4
				fprintf(stderr, "No entry for %s in the %s section of the local manual.\n", *argv, dirlist[section].msg);
E 4
I 4
D 8
				fprintf(stderr, "No entry for %s in the %s section of the local manual.\n", *argv, stanlist[section].msg);
E 8
I 8
D 15
				if (section == NO_SECTION)
					fprintf(stderr, "No entry for %s in the local manual.\n", *argv);
E 15
I 15
				if (section)
					fprintf(stderr, "No entry for %s in the %s section of the local manual.\n", *argv, section->msg);
E 15
				else
D 15
					fprintf(stderr, "No entry for %s in the %s section of the local manual.\n", *argv, stanlist[section].msg);
E 15
I 15
					fprintf(stderr, "No entry for %s in the local manual.\n", *argv);
E 15
			else if (manpath == newpath)
D 15
				if (section == NO_SECTION)
					fprintf(stderr, "No entry for %s in the new manual.\n", *argv);
E 15
I 15
				if (section)
					fprintf(stderr, "No entry for %s in the %s section of the new manual.\n", *argv, section->msg);
E 15
				else
D 15
					fprintf(stderr, "No entry for %s in the %s section of the new manual.\n", *argv, stanlist[section].msg);
E 8
			else if (dirlist == sec1list)
				fprintf(stderr, "No entry for %s in the 1st section of the manual.\n", *argv);
E 4
			else if (section == NO_SECTION)
				fprintf(stderr, "No entry for %s in the manual.\n", *argv);
E 15
I 15
					fprintf(stderr, "No entry for %s in the new manual.\n", *argv);
			else if (section)
				fprintf(stderr, "No entry for %s in the %s section of the manual.\n", *argv, section->msg);
E 15
E 2
			else
D 2
				fprintf(stderr, "No entry for %s in section %d of the manual.\n", *argv, section);
E 2
I 2
D 4
				fprintf(stderr, "No entry for %s in the %s section of the manual.\n", *argv, dirlist[section].msg);
E 4
I 4
D 15
				fprintf(stderr, "No entry for %s in the %s section of the manual.\n", *argv, stanlist[section].msg);
E 15
I 15
				fprintf(stderr, "No entry for %s in the manual.\n", *argv);
I 17
			exit(1);
		}
E 20
I 20
D 23
			fprintf(stderr, "%s section of the ", section->msg);
		if (manpath == locpath)
			fputs("local ", stderr);
		else if (manpath == newpath)
			fputs("new ", stderr);
E 23
I 23
			(void)fprintf(stderr,
			    "%s section of the ", section->msg);
E 23
		if (*argv)
D 23
			fputs("manual.\n", stderr);
E 23
I 23
			(void)fprintf(stderr, "manual.\n");
E 23
		else
D 23
			fputs("manual?\n", stderr);
E 23
I 23
			(void)fprintf(stderr, "manual?\n");
E 23
		exit(1);
E 20
E 17
E 15
E 4
E 2
	}
D 15
	exit(0);
E 15
}

I 4
/*
E 24
 * manual --
D 17
 *	given a section number and a file name go through the directory
 *	list and find a file that matches.
E 17
I 17
D 23
 *	given a directory list and a file name find a file that
 *	matches; check ${directory}/${dir}/{file name} and
E 23
I 23
D 39
 *	given a path, a directory list and a file name, find a file
 *	that matches; check ${directory}/${dir}/{file name} and
E 23
 *	${directory}/${dir}/${machine}/${file name}.
E 39
I 39
 *	Search the manuals for the pages.
E 39
E 17
 */
E 4
D 23
static
manual(section, name)
E 23
I 23
D 24
manual(path, section, name)
E 24
I 24
D 39
manual(path, name)
E 24
	char *path, *name;
E 39
I 39
static int
D 47
manual(page, list, pg)
E 47
I 47
manual(page, tag, pg)
E 47
	char *page;
D 47
	ENTRY *list;
E 47
I 47
	TAG *tag;
E 47
	glob_t *pg;
E 39
E 23
D 15
	int	section;
	char	*name;
E 15
I 15
D 24
	DIR *section;
E 24
D 23
	char *name;
E 23
E 15
{
D 2
	register char	*beg, *end, **dir;
E 2
I 2
D 15
	register DIR	*dir;
	register char	*beg, *end;
E 2
	char	*index();
E 15
I 15
D 23
	register char *beg, *end;
E 23
I 23
D 24
	register char *end;
E 23
	register DIR *dp;
E 24
D 17
	char *index();
E 17
I 17
D 39
	register int res;
I 24
D 32
	register char *end;
E 32
I 32
	register char *cp;
E 32
E 24
D 23
	char fname[MAXPATHLEN + 1], *index();
E 23
I 23
	char fname[MAXPATHLEN + 1];
E 39
I 39
D 47
	ENTRY *listp, *missp, *sufp, *tp;
E 47
I 47
	ENTRY *ep, *e_sufp, *e_tag;
	TAG *missp, *sufp;
E 47
	int anyfound, cnt, found;
	char *p, buf[128];
E 39
E 23
E 17
E 15

D 17
	for (beg = manpath;; beg = end + 1) {
E 17
I 17
D 23
	for (beg = manpath, res = 0;; beg = end + 1) {
E 17
		if (end = index(beg, ':'))
E 23
I 23
D 32
	for (res = 0;; path = end + 1) {
D 24
		if (end = index(path, ':'))
E 24
I 24
		if (!*path)				/* foo: */
			break;
		if (end = index(path, ':')) {
			if (end == path + 1)		/* foo::bar */
E 32
I 32
D 39
	for (res = 0; path != NULL && *path != '\0'; path = cp) {
		if (cp = strchr(path, ':')) {
			if (cp == path + 1) {		/* foo::bar */
				++cp;
E 39
I 39
	anyfound = 0;
	buf[0] = '*';

	/* For each element in the list... */
D 47
	if (list != NULL)
		list = list->list.qe_next;
	for (listp = list; listp != NULL; listp = listp->list.qe_next) {
		(void)snprintf(buf, sizeof(buf), "%s/%s.*", listp->s, page);
E 47
I 47
D 48
	if (tag != NULL)
		e_tag = tag->list.tqh_first;
E 48
I 48
	e_tag = tag == NULL ? NULL : tag->list.tqh_first;
E 48
	for (; e_tag != NULL; e_tag = e_tag->q.tqe_next) {
		(void)snprintf(buf, sizeof(buf), "%s/%s.*", e_tag->s, page);
E 47
		if (glob(buf,
D 42
		    GLOB_APPEND | GLOB_NOSORT | GLOB_BRACE, NULL, pg)) {
E 42
I 42
		    GLOB_APPEND | GLOB_BRACE | GLOB_NOSORT | GLOB_QUOTE,
		    NULL, pg)) {
E 42
D 47
			cleanup();
			err(1, "globbing");
E 47
I 47
			warn("globbing");
			(void)cleanup();
			exit(1);
E 47
		}
		if (pg->gl_matchc == 0)
			continue;

		/* Find out if it's really a man page. */
D 43
		for (cnt = 1; cnt <= pg->gl_matchc; ++cnt) {
E 43
I 43
		for (cnt = pg->gl_pathc - pg->gl_matchc;
		    cnt < pg->gl_pathc; ++cnt) {
E 43

D 41
			/* Try the _suffix key words first. */
E 41
I 41
			/*
			 * Try the _suffix key words first.
			 *
			 * XXX
			 * Older versions of man.conf didn't have the suffix
			 * key words, it was assumed that everything was a .0.
			 * We just test for .0 first, it's fast and probably
			 * going to hit.
			 */
D 43
			if (!fnmatch("*.0",
			    pg->gl_pathv[pg->gl_pathc - cnt], 0))
E 43
I 43
			(void)snprintf(buf, sizeof(buf), "*/%s.0", page);
			if (!fnmatch(buf, pg->gl_pathv[cnt], 0))
E 43
D 52
				goto easy;
E 52
I 52
				goto next;
E 52

E 41
D 47
			sufp = getlist("_suffix");
			if (sufp != NULL)
				sufp = sufp->list.qe_next;
E 47
I 47
			e_sufp = (sufp = getlist("_suffix")) == NULL ?
			    NULL : sufp->list.tqh_first;
E 47
			for (found = 0;
D 47
			    sufp != NULL; sufp = sufp->list.qe_next) {
E 47
I 47
			    e_sufp != NULL; e_sufp = e_sufp->q.tqe_next) {
E 47
				(void)snprintf(buf,
D 43
				     sizeof(buf), "*%s", sufp->s);
				if (!fnmatch(buf,
				    pg->gl_pathv[pg->gl_pathc - cnt], 0)) {
E 43
I 43
D 47
				     sizeof(buf), "*/%s%s", page, sufp->s);
E 47
I 47
				     sizeof(buf), "*/%s%s", page, e_sufp->s);
E 47
				if (!fnmatch(buf, pg->gl_pathv[cnt], 0)) {
E 43
					found = 1;
					break;
				}
			}
D 52
			if (found) {
D 41
				anyfound = 1;
E 41
I 41
easy:				anyfound = 1;
E 41
				if (!f_all)
					break;
E 39
E 32
				continue;
E 24
E 23
D 32
			*end = '\0';
E 32
I 32
			}
E 52
I 52
			if (found)
				goto next;
E 52
D 39
			*cp = '\0';
E 32
D 4
		if (section == NO_SECTION) {
D 2
			/* notice the +1... */
			for (dir = dirlist + 1; *dir; ++dir)
				if (find(beg, *dir, name))
E 2
I 2
			for (dir = dirlist + 1; dir->name; ++dir)
E 4
I 4
D 15
		if (section == NO_SECTION)
			for (dir = dirlist; (++dir)->name;) {
E 4
				if (find(beg, dir->name, name))
E 2
D 14
					return(YES);
E 14
I 14
					goto found;
E 15
I 15
D 17
		for (dp = section; dp->name; ++dp)
			if (find(beg, dp->name, name)) {
				if (end)
					*end = ':';
				return(YES);
E 17
I 17
D 24
		for (dp = section; dp->name; ++dp) {
D 23
			(void)sprintf(fname, "%s/%s/%s.0", beg, dp->name, name);
E 23
I 23
			(void)sprintf(fname, "%s/%s/%s.0",
			    path, dp->name, name);
E 23
			if (access(fname, R_OK)) {
D 23
				(void)sprintf(fname, "%s/%s/%s/%s.0", beg,
E 23
I 23
				(void)sprintf(fname, "%s/%s/%s/%s.0", path,
E 23
				    dp->name, machine, name);
				if (access(fname, R_OK))
					continue;
E 17
E 15
E 14
D 4
		}
D 2
		else if (find(beg, dirlist[section], name))
E 2
I 2
		else if (find(beg, dirlist[section].name, name))
E 4
I 4
			}
I 17
D 18
			if (where)
E 18
I 18
D 23
			if (how & WHERE)
E 18
				printf("man: found in %s.\n", fname);
D 18
			else if (nomore)
E 18
I 18
			else if (how & CAT)
E 23
I 23
			if (f_where)
				(void)printf("man: found in %s.\n", fname);
			else if (f_cat)
E 23
E 18
				cat(fname);
			else
				add(fname);
I 18
D 23
			if (!(how & ALL))
E 23
I 23
			if (!f_all)
E 23
				return(1);
E 18
			res = 1;
E 24
		}
I 24
D 36
		(void)sprintf(fname, "%s/%s.0", path, name);
E 36
I 36
		(void)snprintf(fname, sizeof(fname), "%s/%s.0", path, name);
E 36
		if (access(fname, R_OK)) {
D 36
			(void)sprintf(fname, "%s/%s/%s.0", path, machine, name);
E 36
I 36
			(void)snprintf(fname, sizeof(fname),
			    "%s/%s/%s.0", path, machine, name);
E 36
D 32
			if (access(fname, R_OK))
E 32
I 32
			if (access(fname, R_OK)) {
D 36
				++cp;
E 36
I 36
				if (cp != NULL)
					*cp++ = ':';
E 39
I 39

			/* Try the _build key words next. */
D 47
			sufp = getlist("_build");
			if (sufp != NULL)
				sufp = sufp->list.qe_next;
E 47
I 47
			e_sufp = (sufp = getlist("_build")) == NULL ?
			    NULL : sufp->list.tqh_first;
E 47
			for (found = 0;
D 47
			    sufp != NULL; sufp = sufp->list.qe_next) {
				for (p = sufp->s;
E 47
I 47
			    e_sufp != NULL; e_sufp = e_sufp->q.tqe_next) {
				for (p = e_sufp->s;
E 47
				    *p != '\0' && !isspace(*p); ++p);
				if (*p == '\0')
					continue;
				*p = '\0';
				(void)snprintf(buf,
D 43
				     sizeof(buf), "*%s", sufp->s);
				if (!fnmatch(buf,
				    pg->gl_pathv[pg->gl_pathc - cnt], 0)) {
E 43
I 43
D 47
				     sizeof(buf), "*/%s%s", page, sufp->s);
E 47
I 47
				     sizeof(buf), "*/%s%s", page, e_sufp->s);
E 47
				if (!fnmatch(buf, pg->gl_pathv[cnt], 0)) {
E 43
D 45
					if (!f_where) {
E 45
I 45
					if (!f_where)
E 45
						build_page(p + 1,
D 43
						    pg->gl_pathv[pg->gl_pathc -
						    cnt]);
						pg->gl_pathv[pg->gl_pathc -
						    cnt] = "";
E 43
I 43
D 45
						    pg->gl_pathv[cnt]);
						pg->gl_pathv[cnt] = "";
E 43
					}
E 45
I 45
						    &pg->gl_pathv[cnt]);
E 45
					*p = ' ';
					found = 1;
					break;
				}
				*p = ' ';
			}
			if (found) {
D 52
				anyfound = 1;
				if (!f_all)
E 52
I 52
next:				anyfound = 1;
				if (!f_all) {
					/* Delete any other matches. */
					while (++cnt< pg->gl_pathc)
						pg->gl_pathv[cnt] = "";
E 52
					break;
I 52
				}
E 52
E 39
E 36
E 32
				continue;
I 32
			}
I 39

			/* It's not a man page, forget about it. */
D 43
			pg->gl_pathv[pg->gl_pathc - cnt] = "";
E 43
I 43
			pg->gl_pathv[cnt] = "";
E 43
E 39
E 32
		}

D 39
		if (f_where)
			(void)printf("man: found in %s.\n", fname);
		else if (f_cat)
			cat(fname);
I 28
		else if (f_how)
			how(fname);
E 28
		else
			add(fname);
		if (!f_all)
			return(1);
		res = 1;
E 24
E 17
D 14
		else if (find(beg, stanlist[section].name, name))
E 14
I 14
D 15
		else if (find(beg, stanlist[section].name, name)) {
found:			if (end)
				*end = ':';
E 14
E 4
E 2
			return(YES);
I 14
		}
E 15
E 14
D 32
		if (!end)
D 17
			return(NO);
E 17
I 17
D 24
			return(res);
E 24
I 24
			break;
E 24
E 17
I 14
		*end = ':';
E 32
I 32
D 36
		if (cp)
E 36
I 36
		if (cp != NULL)
E 36
			*cp++ = ':';
E 39
I 39
		if (anyfound && !f_all)
			break;
E 39
E 32
E 14
	}
D 23
	/*NOTREACHED*/
E 23
I 23
D 24
	/* NOTREACHED */
E 24
I 24
D 39
	return(res);
E 39
I 39

	/* If not found, enter onto the missing list. */
	if (!anyfound) {
		if ((missp = getlist("_missing")) == NULL)
			missp = addlist("_missing");
D 47
		if ((tp = malloc(sizeof(ENTRY))) == NULL ||
		    (tp->s = strdup(page)) == NULL) {
			cleanup();
			err(1, NULL);
E 47
I 47
		if ((ep = malloc(sizeof(ENTRY))) == NULL ||
		    (ep->s = strdup(page)) == NULL) {
			warn(NULL);
			(void)cleanup();
			exit(1);
E 47
		}
D 47
		queue_enter_tail(&missp->list, tp, ENTRY *, list);
E 47
I 47
		TAILQ_INSERT_TAIL(&missp->list, ep, q);
E 47
	}
	return (anyfound);
E 39
E 24
E 23
}

I 39
/* 
 * build_page --
 *	Build a man page for display.
 */
static void
D 45
build_page(fmt, path)
	char *fmt, *path;
E 45
I 45
build_page(fmt, pathp)
	char *fmt, **pathp;
E 45
{
	static int warned;
D 47
	ENTRY *intmpp, *tp;
E 47
I 47
	ENTRY *ep;
	TAG *intmpp;
E 47
	int fd;
	char buf[MAXPATHLEN], cmd[MAXPATHLEN], tpath[sizeof(_PATH_TMP)];

	/* Let the user know this may take awhile. */
	if (!warned) {
		warned = 1;
		warnx("Formatting manual page...");
	}

D 45
	/* Add an "in tmp" list. */
E 45
I 45
	/* Add a remove-when-done list. */
E 45
	if ((intmpp = getlist("_intmp")) == NULL)
		intmpp = addlist("_intmp");

	/* Move to the printf(3) format string. */
	for (; *fmt && isspace(*fmt); ++fmt);

	/*
D 45
	 * Get a temporary file and build a version of the file to display.
	 * Link the built file into the list.
E 45
I 45
	 * Get a temporary file and build a version of the file
	 * to display.  Replace the old file name with the new one.
E 45
	 */
	(void)strcpy(tpath, _PATH_TMP);
	if ((fd = mkstemp(tpath)) == -1) {
D 47
		cleanup();
		err(1, "%s", tpath);
E 47
I 47
		warn("%s", tpath);
		(void)cleanup();
		exit(1);
E 47
	}
	(void)snprintf(buf, sizeof(buf), "%s > %s", fmt, tpath);
D 45
	(void)snprintf(cmd, sizeof(cmd), buf, path);
E 45
I 45
	(void)snprintf(cmd, sizeof(cmd), buf, *pathp);
E 45
	(void)system(cmd);
	(void)close(fd);
D 45
	if ((tp = malloc(sizeof(ENTRY))) == NULL ||
	    (tp->s = strdup(tpath)) == NULL) {
E 45
I 45
	if ((*pathp = strdup(tpath)) == NULL) {
E 45
D 47
		cleanup();
		err(1, NULL);
E 47
I 47
		warn(NULL);
		(void)cleanup();
		exit(1);
E 47
	}
I 45

	/* Link the built file into the remove-when-done list. */
D 47
	if ((tp = malloc(sizeof(ENTRY))) == NULL) {
		cleanup();
		err(1, NULL);
E 47
I 47
	if ((ep = malloc(sizeof(ENTRY))) == NULL) {
		warn(NULL);
		(void)cleanup();
		exit(1);
E 47
	}
D 47
	tp->s = *pathp;
E 45
	queue_enter_tail(&intmpp->list, tp, ENTRY *, list);
E 47
I 47
	ep->s = *pathp;
	TAILQ_INSERT_TAIL(&intmpp->list, ep, q);
E 47
}

E 39
I 4
/*
I 28
 * how --
 *	display how information
 */
I 39
static void
E 39
how(fname)
	char *fname;
{
D 47
	register FILE *fp;
E 47
I 47
	FILE *fp;
E 47

D 47
	register int lcnt, print;
	register char *p;
	char buf[BUFSIZ];
E 47
I 47
	int lcnt, print;
	char *p, buf[256];
E 47

	if (!(fp = fopen(fname, "r"))) {
D 39
		(void)fprintf(stderr, "man: %s: %s\n", fname, strerror(errno));
		exit(1);
E 39
I 39
D 47
		cleanup();
		err(1, "%s", fname);
E 47
I 47
		warn("%s", fname);
		(void)cleanup();
		exit (1);
E 47
E 39
	}
#define	S1	"SYNOPSIS"
#define	S2	"S\bSY\bYN\bNO\bOP\bPS\bSI\bIS\bS"
#define	D1	"DESCRIPTION"
#define	D2	"D\bDE\bES\bSC\bCR\bRI\bIP\bPT\bTI\bIO\bON\bN"
	for (lcnt = print = 0; fgets(buf, sizeof(buf), fp);) {
		if (!strncmp(buf, S1, sizeof(S1) - 1) ||
		    !strncmp(buf, S2, sizeof(S2) - 1)) {
			print = 1;
			continue;
		} else if (!strncmp(buf, D1, sizeof(D1) - 1) ||
		    !strncmp(buf, D2, sizeof(D2) - 1))
			return;
		if (!print)
			continue;
		if (*buf == '\n')
			++lcnt;
		else {
			for(; lcnt; --lcnt)
				(void)putchar('\n');
			for (p = buf; isspace(*p); ++p);
			(void)fputs(p, stdout);
		}
	}
	(void)fclose(fp);
}
I 39

E 39
/*
E 28
D 17
 * find --
 *	given a directory path, a sub-directory and a file name,
 *	see if a file exists in ${directory}/${dir}/{file name}
 *	or in ${directory}/${dir}/${machine}/${file name}.
E 17
I 17
 * cat --
 *	cat out the file
E 17
 */
I 39
static void
E 39
E 4
D 23
static
E 23
D 17
find(beg, dir, name)
D 15
	char	*beg, *dir, *name;
E 15
I 15
	char *beg, *dir, *name;
E 17
I 17
cat(fname)
	char *fname;
E 17
E 15
{
D 15
	char	fname[MAXPATHLEN + 1];
E 15
I 15
D 17
	char fname[MAXPATHLEN + 1];
E 17
I 17
D 47
	register int fd, n;
	char buf[BUFSIZ];
E 47
I 47
	int fd, n;
	char buf[2048];
E 47
E 17
E 15

D 2
	(void)sprintf(fname, "%s/%s/%s", beg, dir, name);
E 2
I 2
D 17
	(void)sprintf(fname, "%s/%s/%s.0", beg, dir, name);
E 2
D 11
	if (!access(fname, R_OK)) {
		show(fname);
		return(YES);
E 11
I 11
	if (access(fname, R_OK)) {
		(void)sprintf(fname, "%s/%s/%s/%s.0", beg, dir, machine, name);
		if (access(fname, R_OK))
			return(NO);
E 17
I 17
D 28
	if (!(fd = open(fname, O_RDONLY, 0))) {
E 28
I 28
	if ((fd = open(fname, O_RDONLY, 0)) < 0) {
E 28
D 23
		perror("man: open");
E 23
I 23
D 39
		(void)fprintf(stderr, "man: %s: %s\n", fname, strerror(errno));
E 23
		exit(1);
E 39
I 39
D 47
		cleanup();
		err(1, "%s", fname);
E 47
I 47
		warn("%s", fname);
		(void)cleanup();
		exit(1);
E 47
E 39
E 17
E 11
	}
D 2
	(void)sprintf(fname, "%s/%s/%s/%s", beg, dir, machine, name);
E 2
I 2
D 11
	(void)sprintf(fname, "%s/%s/%s/%s.0", beg, dir, machine, name);
E 2
	if (!access(fname, R_OK)) {
E 11
I 11
D 17
	if (where)
		printf("man: found in %s.\n", fname);
	else
E 11
		show(fname);
D 11
		return(YES);
	}
	return(NO);
E 11
I 11
	return(!where);
E 17
I 17
	while ((n = read(fd, buf, sizeof(buf))) > 0)
D 39
		if (write(1, buf, n) != n) {
D 23
			perror("man: write");
E 23
I 23
			(void)fprintf(stderr,
			    "man: write: %s\n", strerror(errno));
E 23
			exit(1);
E 39
I 39
		if (write(STDOUT_FILENO, buf, n) != n) {
D 47
			cleanup();
			err(1, "write");
E 47
I 47
			warn("write");
			(void)cleanup();
			exit (1);
E 47
E 39
		}
	if (n == -1) {
D 23
		perror("man: read");
E 23
I 23
D 39
		(void)fprintf(stderr, "man: read: %s\n", strerror(errno));
E 23
		exit(1);
E 39
I 39
D 47
		cleanup();
		err(1, "read");
E 47
I 47
		warn("read");
		(void)cleanup();
		exit(1);
E 47
E 39
	}
	(void)close(fd);
E 17
E 11
}

I 4
/*
D 17
 * show --
 *	display the file
E 17
I 17
D 39
 * add --
 *	add a file name to the list for future paging
E 17
 */
E 4
D 23
static
E 23
D 17
show(fname)
E 17
I 17
add(fname)
E 17
D 15
	char	*fname;
E 15
I 15
	char *fname;
E 15
{
D 15
	register int	fd, n;
	char	buf[BUFSIZ];
E 15
I 15
D 17
	register int fd, n;
	char buf[BUFSIZ];
E 17
I 17
	static u_int buflen;
	static int len;
	static char *cp;
	int flen;
D 24
	char *malloc(), *realloc(), *strcpy();
E 24
E 17
E 15

D 17
	if (nomore) {
		if (!(fd = open(fname, O_RDONLY, 0))) {
			perror("man: open");
E 17
I 17
	if (!command) {
D 23
		if (!(command = malloc(buflen = 1024))) {
			fputs("man: out of space.\n", stderr);
E 17
			exit(1);
		}
E 23
I 23
		if (!(command = malloc(buflen = 1024)))
			enomem();
E 23
D 17
		while ((n = read(fd, buf, sizeof(buf))) > 0)
			if (write(1, buf, n) != n) {
				perror("man: write");
				exit(1);
			}
		if (n == -1) {
			perror("man: read");
E 17
I 17
		len = strlen(strcpy(command, pager));
		cp = command + len;
	}
	flen = strlen(fname);
	if (len + flen + 2 > buflen) {		/* +2 == space, EOS */
D 23
		if (!(command = realloc(command, buflen += 1024))) {
			fputs("man: out of space.\n", stderr);
E 17
			exit(1);
		}
E 23
I 23
		if (!(command = realloc(command, buflen += 1024)))
			enomem();
E 23
D 17
		(void)close(fd);
E 17
I 17
		cp = command + len;
E 17
	}
D 17
	else {
		/*
D 15
		 * use system(2) in case someone's pager is
E 15
I 15
		 * use system(3) in case someone's pager is
E 15
		 * "command arg1 arg2"
		 */
		(void)sprintf(buf, "%s %s", pager, fname);
		(void)system(buf);
	}
E 17
I 17
	*cp++ = ' ';
	len += flen + 1;			/* +1 = space */
	(void)strcpy(cp, fname);
	cp += flen;
E 17
}

I 4
/*
E 39
D 15
 * usage --
 *	print out a usage message and die
E 15
I 15
D 24
 * getsect --
 *	return a point to the section structure for a particular suffix
E 15
 */
E 4
D 15
static
usage()
E 15
I 15
D 23
static DIR *
E 23
I 23
DIR *
E 23
getsect(s)
	char *s;
E 15
{
D 15
	fputs("usage: man [-] [-M path] [section] title ...\n", stderr);
	exit(1);
E 15
I 15
	switch(*s++) {
	case '1':
		if (!*s)
			return(list1);
		break;
	case '2':
		if (!*s) {
			list3[0] = list2[0];
			return(list3);
		}
		break;
	/* sect. 3 requests are for either section 3, or section 3[fF]. */
	case '3':
		if (!*s) {
			list3[0] = list2[1];
			return(list3);
		}
		else if ((*s == 'f'  || *s == 'F') && !*++s) {
			list3[0] = list2[5];
			return(list3);
		}
		break;
	case '4':
		if (!*s) {
			list3[0] = list2[2];
			return(list3);
		}
		break;
	case '5':
		if (!*s) {
			list3[0] = list2[3];
			return(list3);
		}
		break;
	case '6':
		if (!*s) {
			list3[0] = list1[2];
			return(list3);
		}
		break;
	case '7':
		if (!*s) {
			list3[0] = list2[4];
			return(list3);
		}
		break;
	case '8':
		if (!*s) {
			list3[0] = list1[1];
			return(list3);
		}
I 23
		break;
E 23
	}
D 23
	return((DIR *)NULL);
E 23
I 23
	(void)fprintf(stderr, "man: unknown manual section.\n");
	exit(1);
	/* NOTREACHED */
E 23
I 18
}

/*
E 24
I 23
 * check_pager --
 *	check the user supplied page information
 */
D 39
char *
E 39
I 39
static char *
E 39
check_pager(name)
	char *name;
{
D 47
	register char *p;
D 24
	char *save, *malloc();
E 24
I 24
	char *save;
E 47
I 47
	char *p, *save;
E 47
E 24

	/*
	 * if the user uses "more", we make it "more -s"; watch out for
	 * PAGER = "mypager /usr/ucb/more"
	 */
	for (p = name; *p && !isspace(*p); ++p);
	for (; p > name && *p != '/'; --p);
	if (p != name)
		++p;

	/* make sure it's "more", not "morex" */
	if (!strncmp(p, "more", 4) && (!p[4] || isspace(p[4]))){
		save = name;
		/* allocate space to add the "-s" */
		if (!(name =
		    malloc((u_int)(strlen(save) + sizeof("-s") + 1))))
D 39
			enomem();
E 39
I 39
			err(1, NULL);
E 39
		(void)sprintf(name, "%s %s", save, "-s");
	}
	return(name);
}

/*
E 23
 * jump --
 *	strip out flag argument and jump
 */
I 39
static void
E 39
D 23
static
E 23
jump(argv, flag, name)
D 39
	char **argv, *name;
	register char *flag;
E 39
I 39
	char **argv, *flag, *name;
E 39
{
D 39
	register char **arg;
E 39
I 39
	char **arg;
E 39

	argv[0] = name;
	for (arg = argv + 1; *arg; ++arg)
		if (!strcmp(*arg, flag))
			break;
	for (; *arg; ++arg)
		arg[0] = arg[1];
	execvp(name, argv);
D 24
	fprintf(stderr, "%s: Command not found.\n", name);
E 24
I 24
	(void)fprintf(stderr, "%s: Command not found.\n", name);
E 24
	exit(1);
}

I 39
/* 
 * onsig --
 *	If signaled, delete the temporary files.
 */
static void
onsig(signo)
	int signo;
{
D 47
	cleanup();
E 47
I 47
	(void)cleanup();
E 47

D 47
	(void)signal(SIGINT, SIG_DFL);
	(void)kill(getpid(), SIGINT);
E 47
I 47
	(void)signal(signo, SIG_DFL);
	(void)kill(getpid(), signo);

	/* NOTREACHED */
	exit (1);
E 47
}

E 39
/*
I 39
 * cleanup --
 *	Clean up temporary files, show any error messages.
 */
D 47
static void
E 47
I 47
static int
E 47
cleanup()
{
D 47
	ENTRY *intmpp, *missp;
	int sverrno;
E 47
I 47
	TAG *intmpp, *missp;
	ENTRY *ep;
	int rval;
E 47

D 47
	sverrno = errno;
E 47
I 47
	rval = 0;
	ep = (missp = getlist("_missing")) == NULL ?
	    NULL : missp->list.tqh_first;
	if (ep != NULL)
		for (; ep != NULL; ep = ep->q.tqe_next) {
			warnx("no entry for %s in the manual.", ep->s);
			rval = 1;
		}
E 47

D 47
	missp = getlist("_missing");
	if (missp != NULL)
		missp = missp->list.qe_next;
	if (missp != NULL)
		for (; missp != NULL; missp = missp->list.qe_next)
			warnx("no entry for %s in the manual.", missp->s);

	intmpp = getlist("_intmp");
	if (intmpp != NULL)
		intmpp = intmpp->list.qe_next;
	for (; intmpp != NULL; intmpp = intmpp->list.qe_next)
		(void)unlink(intmpp->s);

	errno = sverrno;
E 47
I 47
	ep = (intmpp = getlist("_intmp")) == NULL ?
	    NULL : intmpp->list.tqh_first;
	for (; ep != NULL; ep = ep->q.tqe_next)
		(void)unlink(ep->s);
	return (rval);
E 47
}

/*
E 39
 * usage --
D 23
 *	print usage and die
E 23
I 23
 *	print usage message and die
E 23
 */
I 39
static void
E 39
D 23
static
E 23
usage()
{
D 23
	fputs("usage: man [-] [-a] [-M path] [section] title ...\n", stderr);
E 23
I 23
	(void)fprintf(stderr,
D 40
	    "usage: man [-ac] [-M path] [-m path] [section] title ...\n");
E 40
I 40
D 50
    "usage: man [-ac] [-C file] [-M path] [-m path] [section] title ...\n");
E 50
I 50
    "usage: man [-achw] [-C file] [-M path] [-m path] [section] title ...\n");
E 50
E 40
E 23
	exit(1);
E 18
E 15
}
E 1
