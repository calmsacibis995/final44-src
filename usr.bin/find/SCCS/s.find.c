h41831
s 00014/00006/00162
d D 8.5 94/08/05 16:29:21 mckusick 50 49
c proper semantics for adding -print (from cgd)
e
s 00002/00000/00166
d D 8.4 94/07/28 03:38:42 pendry 49 48
c changes for whiteouts and union filesystem
e
s 00002/00002/00164
d D 8.3 94/04/01 09:53:13 bostic 48 47
c setting errno and then not exiting isn't safe
e
s 00013/00007/00153
d D 8.2 94/04/01 07:33:19 bostic 47 46
c POSIX 1003.2B/D9 symbolic links
e
s 00002/00002/00158
d D 8.1 93/06/06 14:38:48 bostic 46 45
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00008/00151
d D 5.7 93/05/01 11:51:34 bostic 45 44
c use library err/warn(3) functions; lint, prettiness police
e
s 00000/00007/00159
d D 5.6 92/06/01 12:21:37 elan 44 43
c Added -Hh options.
e
s 00002/00000/00164
d D 5.5 92/05/05 10:55:09 bostic 43 42
c flush stdout so error messages in the right place
e
s 00000/00002/00164
d D 5.4 91/12/27 10:41:50 bostic 42 41
c delete extra extern function declaratoins
e
s 00002/00001/00164
d D 5.3 91/05/25 16:29:19 bostic 41 40
c a little too enthusiastic... don't exit on unreadable directories
e
s 00008/00065/00157
d D 5.2 91/05/24 15:17:07 bostic 40 39
c return to the original find syntax (newsyntax.c -> main.c, delete
c oldsyntax.c; create extern.h for ANSI prototypes; create true error routine;
c make NEW macro a real routine
e
s 00006/00000/00216
d D 5.1 91/05/23 19:01:50 bostic 39 38
c follow symbolic links if they are specified as command line args
e
s 00008/00000/00208
d D 4.37 91/04/27 13:37:39 bostic 38 37
c add -X flag to make the world safe for xargs
e
s 00007/00057/00201
d D 4.36 91/03/10 11:37:01 bostic 37 36
c ANSI, error routine; use new fts routines which set errno correctly
c so there's lots less work to do here.
e
s 00005/00005/00253
d D 4.35 90/11/15 13:02:57 bostic 36 35
c use getchar() for queryuser function; lots of minor lint
e
s 00055/00019/00203
d D 4.34 90/11/15 12:30:54 bostic 35 34
c if not exec/ok-ing a file, and no stat(2) information is needed,
c can build file names for files in unsearchable (but readable) directories.
c make status variables consistent; lint; change fts routine names
e
s 00001/00000/00221
d D 4.33 90/09/11 11:44:42 bostic 34 33
c postorder find fails because of a missing `break'
c test case is "find -d /tmp user root".
e
s 00002/00001/00219
d D 4.32 90/07/01 17:09:45 bostic 33 32
c -a wasn't getting discarded completely; test case is:
c find /tmp '(' -fstype local -o -prune ')' -a -print
e
s 00009/00003/00211
d D 4.31 90/07/01 00:52:05 bostic 32 31
c don't handle "exec foo -a {} \;" as old syntax because of the "-a"
e
s 00001/00001/00213
d D 4.30 90/06/17 00:06:11 bostic 31 30
c delete FTS_MULTIPLE
e
s 00000/00012/00214
d D 4.29 90/05/22 15:00:46 bostic 30 29
c fts now has flag to keep from crossing mount points
e
s 00010/00009/00216
d D 4.28 90/05/20 12:56:32 bostic 29 28
c rename fts fields
e
s 00001/00001/00224
d D 4.27 90/05/15 19:55:19 bostic 28 27
c string.h is ANSI C include file
e
s 00020/00006/00205
d D 4.26 90/05/12 15:29:36 bostic 27 26
c new syntax
e
s 00180/01026/00031
d D 4.25 90/04/16 17:22:12 bostic 26 25
c new version derived from Cimarron Taylor's
e
s 00003/00161/01054
d D 4.24 90/03/06 11:06:33 bostic 25 24
c pull out fast database code, rename as list
e
s 00001/00003/01214
d D 4.23 89/05/05 10:02:24 bostic 24 23
c fast find doesn't find last file; bug report tahoe/usr.bin/16
e
s 00025/00025/01192
d D 4.22 89/05/04 13:47:52 jak 23 22
c added find.h to remove magic numbers shared by find.c and code.c,
c uses register variables a little better, uses perror, editted comments
e
s 00007/00013/01210
d D 4.21 89/05/03 17:20:43 bostic 22 21
c file system reorg, pathnames.h; keep passwd/group files open
e
s 00003/00003/01220
d D 4.20 87/09/28 16:50:42 bostic 21 20
c init globflag; bug report 4.3BSD/usr.bin/91
e
s 00007/00002/01216
d D 4.19 87/08/18 14:42:48 marc 20 19
c Add -follow so find can follow symbolic linked directories.
e
s 00004/00000/01214
d D 4.18 87/05/06 19:20:25 bostic 19 18
c speed up find -d; bug report 4.3BSD/bin/32
e
s 00002/00001/01212
d D 4.17 86/01/31 14:00:35 mckusick 18 17
c compiler bug fix unmasks coding error? (from torek)
e
s 00002/00001/01211
d D 4.16 85/11/27 05:39:37 lepreau 17 16
c portability nit
e
s 00001/00003/01211
d D 4.15 85/09/07 20:04:36 bloom 16 15
c fix precedence problem
e
s 00012/00001/01202
d D 4.14 85/08/29 09:20:50 bloom 15 14
c fix problem with -ls reading symbolic links
e
s 00011/00016/01192
d D 4.13 85/08/16 19:10:17 mckusick 14 13
c changes to avoid depending on vfork semantics (from guy@sun)
e
s 00386/00023/00822
d D 4.12 85/06/07 01:14:25 serge 13 12
c added -nouser, -nogroup, -ls, and -xdev options
e
s 00036/00018/00809
d D 4.11 85/02/11 12:30:01 mckusick 12 11
c faster globbing (from jaw)
e
s 00000/00000/00827
d D 4.10 84/06/27 10:47:20 mckusick 11 9
i 10
c merge in ralph's branch
e
s 00002/00001/00674
d D 4.7.1.1 84/06/27 10:45:47 mckusick 10 7
c added "-type s" for sockets; fix pathname buffer size (from ralph)
e
s 00004/00006/00822
d D 4.9 83/07/21 11:22:12 mckusick 9 8
c move database to /usr/lib/find; restrict database to /usr
e
s 00154/00001/00674
d D 4.8 83/07/20 19:43:34 mckusick 8 7
c add code to do special case quickly
e
s 00002/00001/00673
d D 4.7 82/08/02 16:50:04 mckusick 7 6
c peter's addition of the soft link `-type l' flag.
e
s 00029/00070/00645
d D 4.6 82/05/12 00:41:05 mckusick 6 5
c update to new fs, need to close directories on deep recursion.
e
s 00001/00001/00714
d D 4.5 82/03/31 11:48:52 root 5 4
c use lstat
e
s 00001/00001/00714
d D 4.4 81/07/03 23:23:03 root 4 3
c fix to -group # usage (ala previous -user # fix)
e
s 00008/00002/00707
d D 4.3 81/07/03 23:19:52 wnj 3 2
c prevent interrupt and quit from killing parent while executing sub-commands
e
s 00001/00001/00708
d D 4.2 81/07/02 00:07:40 root 2 1
c fix to -name bug
e
s 00709/00000/00000
d D 4.1 80/10/01 17:26:36 bill 1 0
c date and time created 80/10/01 17:26:36 by bill
e
u
U
f b 
t
T
I 13
D 26
#ifndef	lint
E 13
I 1
static char *sccsid = "%W% (Berkeley) %G%";
I 13
#endif
E 26
I 26
/*-
D 40
 * Copyright (c) 1990 The Regents of the University of California.
E 40
I 40
D 46
 * Copyright (c) 1991 The Regents of the University of California.
E 40
 * All rights reserved.
E 46
I 46
D 47
 * Copyright (c) 1991, 1993
E 47
I 47
 * Copyright (c) 1991, 1993, 1994
E 47
 *	The Regents of the University of California.  All rights reserved.
E 46
 *
 * This code is derived from software contributed to Berkeley by
 * Cimarron D. Taylor of the University of California, Berkeley.
 *
 * %sccs.include.redist.c%
 */
E 26
E 13
I 8

E 8
D 9
/*	find	COMPILE:	cc -o find -s -O -i find.c -lS	*/
I 8

E 9
E 8
D 22
#include <stdio.h>
E 22
D 6
#include <sys/types.h>
E 6
I 6
D 26
#include <sys/param.h>
E 6
#include <sys/dir.h>
E 26
I 26
#ifndef lint
D 40
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 40
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 35
#include <sys/types.h>
E 35
I 35
D 40
#include <sys/param.h>
E 40
I 40
#include <sys/types.h>
E 40
E 35
E 26
#include <sys/stat.h>
I 35
D 45
#include <sys/errno.h>
E 45
I 45

#include <err.h>
#include <errno.h>
E 45
I 37
D 40
#include <time.h>
E 40
E 37
E 35
I 26
#include <fts.h>
E 26
I 22
#include <stdio.h>
D 25
#include "pathnames.h"
E 25
I 25
D 26
#include <paths.h>
E 26
I 26
D 28
#include <strings.h>
E 28
I 28
D 35
#include <string.h>
E 28
#include <errno.h>
E 35
D 37
#include "find.h"
E 37
I 35
#include <string.h>
#include <stdlib.h>
I 45

E 45
I 37
#include "find.h"
E 37
E 35
E 26
E 25
E 22
I 13

E 13
D 26
#define A_DAY	86400L /* a day full of seconds */
#define EQ(x, y)	(strcmp(x, y)==0)
E 26
I 26
D 40
FTS *tree;			/* pointer to top of FTS hierarchy */
time_t now;			/* time find was run */
D 30
dev_t curdev = (dev_t)-1;	/* device number of current tree */
E 30
D 35
int ftsoptions;			/* options passed to ftsopen() */
I 27
int deprecated;			/* old or new syntax */
E 27
int depth;			/* set by -depth option */
int output_specified;		/* one of -print, -ok or -exec was specified */
E 35
I 35
				/* options for the ftsopen(3) call */
int ftsoptions = FTS_NOSTAT|FTS_PHYSICAL;
int isdeprecated;		/* using deprecated syntax */
int isdepth;			/* do directories on post-order visit */
int isoutput;			/* user specified output operator */
int isrelative;			/* can do -exec/ok on relative path */
I 38
int isxargs;			/* don't permit xargs delimiting chars */
E 38
D 37
int isstopdnx;			/* don't read unsearchable directories */
E 37
E 35
D 30
int xdev;			/* set by -xdev option */
E 30
E 26

D 26
int	Randlast;
D 10
char	Pathname[200];
E 10
I 10
char	Pathname[MAXPATHLEN+1];
E 10

I 13
#define MAXNODES	100

E 13
struct anode {
	int (*F)();
	struct anode *L, *R;
D 13
} Node[100];
E 13
I 13
} Node[MAXNODES];
E 13
int Nn;  /* number of nodes */
char	*Fname;
long	Now;
int	Argc,
	Ai,
	Pi;
char	**Argv;
/* cpio stuff */
int	Cpio;
short	*Buf, *Dbuf, *Wp;
int	Bufsize = 5120;
int	Wct = 2560;

long	Newer;

I 13
int	Xdev = 1;	/* true if SHOULD cross devices (file systems) */
I 20
int	follow;		/* true if SHOULD descend symlinked directories */
E 20
struct	stat Devstat;	/* stats of each argument path's file system */

E 13
struct stat Statb;

struct	anode	*exp(),
		*e1(),
		*e2(),
		*e3(),
		*mk();
char	*nxtarg();
D 13
char	Home[128];
E 13
I 13
char	Home[MAXPATHLEN + 1];
E 13
long	Blocks;
char *rindex();
char *sbrk();
D 8
main(argc, argv) char *argv[];
E 8
I 8

E 26
D 25
/*
D 9
 * SEE ALSO:	find.squeeze, find.bigram.c, find.code.c
E 9
I 9
D 23
 * SEE ALSO:	updatedb, bigram.c, code.c
E 9
 *		Usenix ;login:, February/March, 1983, p. 8.
E 23
I 23
 * SEE ALSO:	code.c, updatedb, bigram.c
 *		Usenix ;login:, Vol 8, No 1, February/March, 1983, p. 8.
E 23
 *
 * REVISIONS: 	James A. Woods, Informatics General Corporation,
 *		NASA Ames Research Center, 6/81.
 *
 *		The second form searches a pre-computed filelist
 *		(constructed nightly by /usr/lib/crontab) which is
D 9
 *		compressed by find.squeeze (v.i.z.)  The effect of
E 9
I 9
 *		compressed by updatedb (v.i.z.)  The effect of
E 9
 *			find <name>
 *		is similar to
 *			find / +0 -name "*<name>*" -print
 *		but much faster.
 *
 *		8/82 faster yet + incorporation of bigram coding -- jaw
 *
 *		1/83 incorporate glob-style matching -- jaw
 */
#define	AMES	1

E 25
main(argc, argv)
	int argc;
D 26
	char *argv[];
E 26
I 26
	char **argv;
E 26
E 8
{
D 26
	struct anode *exlist;
	int paths;
	register char *cp, *sp = 0;
I 13
#ifdef	SUID_PWD
E 13
	FILE *pwd, *popen();
I 13
#endif
E 26
I 26
	PLAN *plan;
D 27
	char **paths, **find_getpaths();
E 27
I 27
	char **p, **paths;
E 27
	PLAN *find_formplan();
	time_t time();
I 35
	void newsyntax(), oldsyntax();
E 35
    
D 27
	(void)time(&now);	/* initialize the time-of-day */
E 27
I 27
	(void)time(&now);			/* initialize the time-of-day */
E 27
E 26
E 13

I 8
D 25
#ifdef  AMES
	if (argc < 2) {
E 25
I 25
D 26
	if (argc < 3) {
E 25
		fprintf(stderr,
D 25
			"Usage: find name, or find path-list predicate-list\n");
E 25
I 25
			"usage: find path-list predicate-list\n");
E 25
		exit(1);
	}
D 25
	if (argc == 2) {
		fastfind(argv[1]);
		exit(0);
	}
#endif
E 25
E 8
	time(&Now);
I 22
	setpassent(1);
	setgroupent(1);
E 22
I 13
#ifdef	SUID_PWD
E 13
	pwd = popen("pwd", "r");
D 13
	fgets(Home, 128, pwd);
E 13
I 13
	fgets(Home, sizeof Home, pwd);
E 13
	pclose(pwd);
	Home[strlen(Home) - 1] = '\0';
I 13
#else
	if (getwd(Home) == NULL) {
		fprintf(stderr, "find: Can't get current working directory\n");
		exit(1);
	}
#endif
E 13
	Argc = argc; Argv = argv;
	if(argc<3) {
usage:		fprintf(stderr, "Usage: find path-list predicate-list\n");
		exit(1);
	}
	for(Ai = paths = 1; Ai < (argc-1); ++Ai, ++paths)
		if(*Argv[Ai] == '-' || EQ(Argv[Ai], "(") || EQ(Argv[Ai], "!"))
			break;
	if(paths == 1) /* no path-list */
		goto usage;
	if(!(exlist = exp())) { /* parse and compile the arguments */
		fprintf(stderr, "find: parsing error\n");
		exit(1);
	}
	if(Ai<argc) {
		fprintf(stderr, "find: missing conjunction\n");
		exit(1);
	}
	for(Pi = 1; Pi < paths; ++Pi) {
		sp = 0;
		chdir(Home);
		strcpy(Pathname, Argv[Pi]);
		if(cp = rindex(Pathname, '/')) {
			sp = cp + 1;
			*cp = '\0';
			if(chdir(*Pathname? Pathname: "/") == -1) {
				fprintf(stderr, "find: bad starting directory\n");
				exit(2);
			}
			*cp = '/';
		}
		Fname = sp? sp: Pathname;
I 13
		if (!Xdev)
			stat(Pathname, &Devstat);
E 13
		descend(Pathname, Fname, exlist); /* to find files that match  */
	}
	if(Cpio) {
		strcpy(Pathname, "TRAILER!!!");
		Statb.st_size = 0;
		cpio();
		printf("%D blocks\n", Blocks*10);
	}
	exit(0);
}

/* compile time functions:  priority is  exp()<e1()<e2()<e3()  */

struct anode *exp() { /* parse ALTERNATION (-o)  */
	int or();
	register struct anode * p1;

	p1 = e1() /* get left operand */ ;
	if(EQ(nxtarg(), "-o")) {
		Randlast--;
		return(mk(or, p1, exp()));
	}
	else if(Ai <= Argc) --Ai;
	return(p1);
}
struct anode *e1() { /* parse CONCATENATION (formerly -a) */
	int and();
	register struct anode * p1;
	register char *a;

	p1 = e2();
	a = nxtarg();
	if(EQ(a, "-a")) {
And:
		Randlast--;
		return(mk(and, p1, e1()));
	} else if(EQ(a, "(") || EQ(a, "!") || (*a=='-' && !EQ(a, "-o"))) {
		--Ai;
		goto And;
	} else if(Ai <= Argc) --Ai;
	return(p1);
}
struct anode *e2() { /* parse NOT (!) */
	int not();

	if(Randlast) {
		fprintf(stderr, "find: operand follows operand\n");
		exit(1);
	}
	Randlast++;
	if(EQ(nxtarg(), "!"))
		return(mk(not, e3(), (struct anode *)0));
	else if(Ai <= Argc) --Ai;
	return(e3());
}
struct anode *e3() { /* parse parens and predicates */
	int exeq(), ok(), glob(),  mtime(), atime(), user(),
		group(), size(), perm(), links(), print(),
D 13
		type(), ino(), cpio(), newer();
E 13
I 13
D 20
		type(), ino(), cpio(), newer(),
E 20
I 20
		type(), ino(), cpio(), newer(), 
E 20
		nouser(), nogroup(), ls(), dummy();
E 13
	struct anode *p1;
	int i;
D 17
	register char *a, *b, s;
E 17
I 17
	register char *a, *b;
	register int s;
E 17

	a = nxtarg();
	if(EQ(a, "(")) {
		Randlast--;
		p1 = exp();
		a = nxtarg();
		if(!EQ(a, ")")) goto err;
		return(p1);
	}
	else if(EQ(a, "-print")) {
		return(mk(print, (struct anode *)0, (struct anode *)0));
	}
I 13
	else if (EQ(a, "-nouser")) {
		return (mk(nouser, (struct anode *)0, (struct anode *)0));
	}
	else if (EQ(a, "-nogroup")) {
		return (mk(nogroup, (struct anode *)0, (struct anode *)0));
	}
	else if (EQ(a, "-ls")) {
		return (mk(ls, (struct anode *)0, (struct anode *)0));
	}
	else if (EQ(a, "-xdev")) {
		Xdev = 0;
		return (mk(dummy, (struct anode *)0, (struct anode *)0));
	}
I 20
	else if (EQ(a, "-follow")) {
		follow=1;
		return mk(dummy, (struct anode *)0, (struct anode *)0);
	}
E 20
E 13
	b = nxtarg();
	s = *b;
	if(s=='+') b++;
	if(EQ(a, "-name"))
		return(mk(glob, (struct anode *)b, (struct anode *)0));
	else if(EQ(a, "-mtime"))
		return(mk(mtime, (struct anode *)atoi(b), (struct anode *)s));
	else if(EQ(a, "-atime"))
		return(mk(atime, (struct anode *)atoi(b), (struct anode *)s));
	else if(EQ(a, "-user")) {
D 13
		if((i=getunum("/etc/passwd", b)) == -1) {
E 13
I 13
		if((i=getuid(b)) == -1) {
E 13
D 2
			if(gmatch(b, "[0-9][0-9]*"))
E 2
I 2
			if(gmatch(b, "[0-9]*"))
E 2
				return mk(user, (struct anode *)atoi(b), (struct anode *)s);
			fprintf(stderr, "find: cannot find -user name\n");
			exit(1);
		}
		return(mk(user, (struct anode *)i, (struct anode *)s));
	}
	else if(EQ(a, "-inum"))
		return(mk(ino, (struct anode *)atoi(b), (struct anode *)s));
	else if(EQ(a, "-group")) {
D 13
		if((i=getunum("/etc/group", b)) == -1) {
E 13
I 13
		if((i=getgid(b)) == -1) {
E 13
D 4
			if(gmatch(b, "[0-9][0-9]*"))
E 4
I 4
			if(gmatch(b, "[0-9]*"))
E 4
				return mk(group, (struct anode *)atoi(b), (struct anode *)s);
			fprintf(stderr, "find: cannot find -group name\n");
			exit(1);
		}
		return(mk(group, (struct anode *)i, (struct anode *)s));
	} else if(EQ(a, "-size"))
		return(mk(size, (struct anode *)atoi(b), (struct anode *)s));
	else if(EQ(a, "-links"))
		return(mk(links, (struct anode *)atoi(b), (struct anode *)s));
	else if(EQ(a, "-perm")) {
		for(i=0; *b ; ++b) {
			if(*b=='-') continue;
			i <<= 3;
			i = i + (*b - '0');
		}
		return(mk(perm, (struct anode *)i, (struct anode *)s));
	}
	else if(EQ(a, "-type")) {
		i = s=='d' ? S_IFDIR :
		    s=='b' ? S_IFBLK :
		    s=='c' ? S_IFCHR :
D 7
		    s=='f' ? 0100000 :
E 7
I 7
		    s=='f' ? S_IFREG :
		    s=='l' ? S_IFLNK :
I 10
		    s=='s' ? S_IFSOCK :
E 10
E 7
		    0;
		return(mk(type, (struct anode *)i, (struct anode *)0));
	}
	else if (EQ(a, "-exec")) {
		i = Ai - 1;
		while(!EQ(nxtarg(), ";"));
		return(mk(exeq, (struct anode *)i, (struct anode *)0));
	}
	else if (EQ(a, "-ok")) {
		i = Ai - 1;
		while(!EQ(nxtarg(), ";"));
		return(mk(ok, (struct anode *)i, (struct anode *)0));
	}
	else if(EQ(a, "-cpio")) {
		if((Cpio = creat(b, 0666)) < 0) {
			fprintf(stderr, "find: cannot create < %s >\n", s);
			exit(1);
		}
		Buf = (short *)sbrk(512);
		Wp = Dbuf = (short *)sbrk(5120);
		return(mk(cpio, (struct anode *)0, (struct anode *)0));
	}
	else if(EQ(a, "-newer")) {
		if(stat(b, &Statb) < 0) {
			fprintf(stderr, "find: cannot access < %s >\n", b);
			exit(1);
		}
		Newer = Statb.st_mtime;
		return mk(newer, (struct anode *)0, (struct anode *)0);
	}
err:	fprintf(stderr, "find: bad option < %s >\n", a);
	exit(1);
}
struct anode *mk(f, l, r)
int (*f)();
struct anode *l, *r;
{
I 13
	if (Nn >= MAXNODES) {
		fprintf(stderr, "find: Too many options\n");
		exit(1);
	}
E 26
I 26
	if (argc < 2)
		usage();
D 27
    
E 27
I 27

	paths = argv;
E 27
D 31
	ftsoptions = FTS_MULTIPLE|FTS_NOSTAT|FTS_PHYSICAL;
E 31
I 31
D 35
	ftsoptions = FTS_NOSTAT|FTS_PHYSICAL;
E 35
E 31
E 26

E 13
D 26
	Node[Nn].F = f;
	Node[Nn].L = l;
	Node[Nn].R = r;
	return(&(Node[Nn++]));
E 26
I 26
D 27
	paths = find_getpaths(&argv);		/* places to start search */
E 27
I 27
	/*
D 32
	 * if arguments start with an option, it's new syntax; otherwise,
	 * if has a "-option" anywhere it must be old syntax.
E 32
I 32
	 * if arguments start with an option, treat it like new syntax;
	 * otherwise, if has a "-option" anywhere (which isn't an argument
	 * to another command) treat it as old syntax.
E 32
	 */
	if (argv[1][0] != '-')
D 32
		for (p = argv + 1; *p; ++p)
E 32
I 32
		for (p = argv + 1; *p; ++p) {
			if (!strcmp(*p, "exec") || !strcmp(*p, "ok")) {
				while (p[1] && strcmp(*++p, ";"));
				continue;
			}
E 32
			if (**p == '-') {
D 35
				deprecated = 1;
E 35
I 35
				isdeprecated = 1;
E 35
				oldsyntax(&argv);
				break;
			}
I 32
		}
E 32
D 35
	if (!deprecated)
E 35
I 35
	if (!isdeprecated)
E 35
		newsyntax(argc, &argv);
    
E 27
	plan = find_formplan(argv);		/* execution plan */
	find_execute(plan, paths);
E 26
}

E 40
D 26
char *nxtarg() { /* get next arg from command line */
	static strikes = 0;

	if(strikes==3) {
		fprintf(stderr, "find: incomplete statement\n");
		exit(1);
	}
	if(Ai>=Argc) {
		strikes++;
		Ai = Argc + 1;
		return("");
	}
	return(Argv[Ai++]);
}

/* execution time functions */
and(p)
register struct anode *p;
E 26
I 26
/*
 * find_formplan --
 *	process the command line and create a "plan" corresponding to the
 *	command arguments.
 */
PLAN *
find_formplan(argv)
	char **argv;
E 26
{
D 26
	return(((*p->L->F)(p->L)) && ((*p->R->F)(p->R))?1:0);
}
or(p)
register struct anode *p;
{
	 return(((*p->L->F)(p->L)) || ((*p->R->F)(p->R))?1:0);
}
not(p)
register struct anode *p;
{
	return( !((*p->L->F)(p->L)));
}
glob(p)
register struct { int f; char *pat; } *p; 
{
	return(gmatch(Fname, p->pat));
}
D 13
print()
E 13
I 13
print(p)
struct anode *p;
E 13
{
	puts(Pathname);
	return(1);
}
mtime(p)
register struct { int f, t, s; } *p; 
{
	return(scomp((int)((Now - Statb.st_mtime) / A_DAY), p->t, p->s));
}
atime(p)
register struct { int f, t, s; } *p; 
{
	return(scomp((int)((Now - Statb.st_atime) / A_DAY), p->t, p->s));
}
user(p)
register struct { int f, u, s; } *p; 
{
	return(scomp(Statb.st_uid, p->u, p->s));
}
I 13
nouser(p)
struct anode *p;
{
	char *getname();
E 26
I 26
	PLAN *plan, *tail, *new;
D 27
	int i;
E 27
D 36
	PLAN *c_print(), *find_create(), *find_squish_not(), *find_squish_or();
	PLAN *find_squish_paren();
E 36
I 36
D 42
	PLAN *c_print(), *find_create(), *not_squish(), *or_squish();
	PLAN *paren_squish();
E 42
E 36
E 26

D 26
	return (getname(Statb.st_uid) == NULL);
}
E 13
ino(p)
register struct { int f, u, s; } *p;
{
	return(scomp((int)Statb.st_ino, p->u, p->s));
}
group(p)
register struct { int f, u; } *p; 
{
	return(p->u == Statb.st_gid);
}
I 13
nogroup(p)
struct anode *p;
{
	char *getgroup();

	return (getgroup(Statb.st_gid) == NULL);
}
E 13
links(p)
register struct { int f, link, s; } *p; 
{
	return(scomp(Statb.st_nlink, p->link, p->s));
}
size(p)
register struct { int f, sz, s; } *p; 
{
	return(scomp((int)((Statb.st_size+511)>>9), p->sz, p->s));
}
perm(p)
register struct { int f, per, s; } *p; 
{
	register i;
	i = (p->s=='-') ? p->per : 07777; /* '-' means only arg bits */
	return((Statb.st_mode & i & 07777) == p->per);
}
type(p)
register struct { int f, per, s; } *p;
{
	return((Statb.st_mode&S_IFMT)==p->per);
}
exeq(p)
register struct { int f, com; } *p;
{
	fflush(stdout); /* to flush possible `-print' */
	return(doex(p->com));
}
ok(p)
struct { int f, com; } *p;
{
	char c;  int yes;
	yes = 0;
	fflush(stdout); /* to flush possible `-print' */
	fprintf(stderr, "< %s ... %s > ?   ", Argv[p->com], Pathname);
	fflush(stderr);
	if((c=getchar())=='y') yes = 1;
	while(c!='\n') c = getchar();
	if(yes) return(doex(p->com));
	return(0);
}

#define MKSHORT(v, lv) {U.l=1L;if(U.c[0]) U.l=lv, v[0]=U.s[1], v[1]=U.s[0]; else U.l=lv, v[0]=U.s[0], v[1]=U.s[1];}
union { long l; short s[2]; char c[4]; } U;
long mklong(v)
short v[];
{
	U.l = 1;
	if(U.c[0] /* VAX */)
		U.s[0] = v[1], U.s[1] = v[0];
	else
		U.s[0] = v[0], U.s[1] = v[1];
	return U.l;
}
D 13
cpio()
E 13
I 13
cpio(p)
struct anode *p;
E 13
{
#define MAGIC 070707
	struct header {
		short	h_magic,
			h_dev,
			h_ino,
			h_mode,
			h_uid,
			h_gid,
			h_nlink,
			h_rdev;
		short	h_mtime[2];
		short	h_namesize;
		short	h_filesize[2];
		char	h_name[256];
	} hdr;
	register ifile, ct;
	static long fsz;
	register i;

	hdr.h_magic = MAGIC;
	strcpy(hdr.h_name, !strncmp(Pathname, "./", 2)? Pathname+2: Pathname);
	hdr.h_namesize = strlen(hdr.h_name) + 1;
	hdr.h_uid = Statb.st_uid;
	hdr.h_gid = Statb.st_gid;
	hdr.h_dev = Statb.st_dev;
	hdr.h_ino = Statb.st_ino;
	hdr.h_mode = Statb.st_mode;
	MKSHORT(hdr.h_mtime, Statb.st_mtime);
	hdr.h_nlink = Statb.st_nlink;
	fsz = hdr.h_mode & S_IFREG? Statb.st_size: 0L;
	MKSHORT(hdr.h_filesize, fsz);
	hdr.h_rdev = Statb.st_rdev;
	if(EQ(hdr.h_name, "TRAILER!!!")) {
		bwrite((short *)&hdr, (sizeof hdr-256)+hdr.h_namesize);
		for(i = 0; i < 10; ++i)
			bwrite(Buf, 512);
		return;
	}
	if(!mklong(hdr.h_filesize))
		return;
	if((ifile = open(Fname, 0)) < 0) {
cerror:
		fprintf(stderr, "find: cannot copy < %s >\n", hdr.h_name);
		return;
	}
	bwrite((short *)&hdr, (sizeof hdr-256)+hdr.h_namesize);
	for(fsz = mklong(hdr.h_filesize); fsz > 0; fsz -= 512) {
		ct = fsz>512? 512: fsz;
		if(read(ifile, (char *)Buf, ct) < 0)
			goto cerror;
		bwrite(Buf, ct);
	}
	close(ifile);
	return;
}
D 13
newer()
E 13
I 13
newer(p)
struct anode *p;
E 13
{
	return Statb.st_mtime > Newer;
}
I 13
ls(p)
struct anode *p;
{
	list(Pathname, &Statb);
	return (1);
}
dummy(p)
struct anode *p;
{
	/* dummy */
	return (1);
}
E 13

/* support functions */
scomp(a, b, s) /* funny signed compare */
register a, b;
register char s;
{
	if(s == '+')
		return(a > b);
	if(s == '-')
		return(a < (b * -1));
	return(a == b);
}

doex(com)
{
	register np;
	register char *na;
	static char *nargv[50];
	static ccode;
I 13
D 14
	register int w, pid, (*sigint)(), (*sigquit)(), cantexec;
E 14
I 14
	register int w, pid, omask;
E 14
E 13

	ccode = np = 0;
	while (na=Argv[com++]) {
I 13
		if(np >= sizeof nargv / sizeof *nargv - 1) break;
E 13
		if(strcmp(na, ";")==0) break;
		if(strcmp(na, "{}")==0) nargv[np++] = Pathname;
		else nargv[np++] = na;
	}
	nargv[np] = 0;
	if (np==0) return(9);
D 3
	if(fork()) /*parent*/ wait(&ccode);
	else { /*child*/
E 3
I 3
D 13
	if(fork()) /*parent*/ {
#include <signal.h>
		int (*old)() = signal(SIGINT, SIG_IGN);
		int (*oldq)() = signal(SIGQUIT, SIG_IGN);
		wait(&ccode);
		signal(SIGINT, old);
		signal(SIGQUIT, oldq);
	} else { /*child*/
E 13
I 13
D 14
	/*
	 * This is a kludge, but the alternative is to reserve
	 * some exit code (e.g. 0xff) to denote inability to exec.
	 */
	cantexec = 0;
E 14
	switch (pid = vfork()) {
	case -1:
		perror("find: Can't fork");
		exit(1);
		break;

	case 0:
E 13
E 3
		chdir(Home);
		execvp(nargv[0], nargv, np);
D 13
		exit(1);
E 13
I 13
D 14
		cantexec = 1;	/* XXX */
		_exit(1);
E 14
I 14
		write(2, "find: Can't execute ", 20);
		perror(nargv[0]);
		/*
		 * Kill ourselves; our exit status will be a suicide
		 * note indicating we couldn't do the "exec".
		 */
		kill(getpid(), SIGUSR1);
E 14
		break;

	default:
D 14
		sigint = signal(SIGINT, SIG_IGN);
		sigquit = signal(SIGQUIT, SIG_IGN);
E 14
I 14
		omask = sigblock(sigmask(SIGINT)|sigmask(SIGQUIT));
E 14
		while ((w = wait(&ccode)) != pid && w != -1)
			;
D 14
		signal(SIGQUIT, sigquit);
		signal(SIGINT, sigint);
		if (cantexec) {	/* XXX */
			fprintf(stderr, "find: Can't execute ");
			perror(nargv[0]);
E 14
I 14
		(void) sigsetmask(omask);
		if ((ccode & 0177) == SIGUSR1)
E 14
			exit(1);
D 14
		}
E 14
		return (ccode != 0 ? 0 : 1);
E 13
	}
D 13
	return(ccode ? 0:1);
E 13
}

getunum(f, s) char *f, *s; { /* find user/group name and return number */
	register i;
	register char *sp;
	register c;
	char str[20];
	FILE *pin;

	i = -1;
	pin = fopen(f, "r");
	c = '\n'; /* prime with a CR */
	do {
		if(c=='\n') {
			sp = str;
			while((c = *sp++ = getc(pin)) != ':')
				if(c == EOF) goto RET;
			*--sp = '\0';
			if(EQ(str, s)) {
				while((c=getc(pin)) != ':')
					if(c == EOF) goto RET;
				sp = str;
				while((*sp = getc(pin)) != ':') sp++;
				*sp = '\0';
				i = atoi(str);
				goto RET;
			}
E 26
I 26
	/*
	 * for each argument in the command line, determine what kind of node
	 * it is, create the appropriate node type and add the new plan node
	 * to the end of the existing plan.  The resulting plan is a linked
	 * list of plan nodes.  For example, the string:
	 *
	 *	% find . -name foo -newer bar -print
	 *
	 * results in the plan:
	 *
	 *	[-name foo]--> [-newer bar]--> [-print]
	 *
	 * in this diagram, `[-name foo]' represents the plan node generated
	 * by c_name() with an argument of foo and `-->' represents the
	 * plan->next pointer.
	 */
D 45
	for (plan = NULL; *argv;) {
E 45
I 45
	for (plan = tail = NULL; *argv;) {
E 45
D 33
		new = find_create(&argv);
E 33
I 33
		if (!(new = find_create(&argv)))
			continue;
E 33
		if (plan == NULL)
			tail = plan = new;
		else {
			tail->next = new;
			tail = new;
E 26
		}
D 26
	} while((c = getc(pin)) != EOF);
 RET:
	fclose(pin);
	return(i);
}

descend(name, fname, exlist)
D 6
struct anode *exlist;
char *name, *fname;
E 6
I 6
	struct anode *exlist;
	char *name, *fname;
E 6
{
D 6
	int	dir = 0, /* open directory */
		offset,
		dsize,
		entries,
		dirsize;
	struct direct dentry[BUFSIZ / sizeof (struct direct)];
E 6
I 6
	DIR	*dir = NULL;
E 6
	register struct direct	*dp;
D 6
	register char *c1, *c2;
	int i;
E 6
I 6
	register char *c1;
E 6
	int rv = 0;
	char *endofname;

D 5
	if(stat(fname, &Statb)<0) {
E 5
I 5
D 6
	if(lstat(fname, &Statb)<0) {
E 6
I 6
D 20
	if (lstat(fname, &Statb)<0) {
E 20
I 20
	if ((follow?stat(fname, &Statb):lstat(fname, &Statb))<0) {
E 20
E 6
E 5
		fprintf(stderr, "find: bad status < %s >\n", name);
		return(0);
E 26
	}
D 26
	(*exlist->F)(exlist);
D 13
	if((Statb.st_mode&S_IFMT)!=S_IFDIR)
E 13
I 13
	if((Statb.st_mode&S_IFMT)!=S_IFDIR ||
	   !Xdev && Devstat.st_dev != Statb.st_dev)
E 13
		return(1);

I 19
	if (Statb.st_nlink == 2 && exlist->F == and &&
		exlist->L->F == type && ((int) (exlist->L->L)) == S_IFDIR)
			return(1);

E 19
D 6
	for(c1 = name; *c1; ++c1);
	if(*(c1-1) == '/')
E 6
I 6
	for (c1 = name; *c1; ++c1);
	if (*(c1-1) == '/')
E 6
		--c1;
	endofname = c1;
D 6
	dirsize = Statb.st_size;
E 6

D 6
	if(chdir(fname) == -1)
E 6
I 6
	if (chdir(fname) == -1)
E 6
		return(0);
D 6
	for(offset=0 ; offset < dirsize ; offset += BUFSIZ) { /* each block */
		dsize = BUFSIZ<(dirsize-offset)? BUFSIZ: (dirsize-offset);
		if(!dir) {
			if((dir=open(".", 0))<0) {
				fprintf(stderr, "find: cannot open < %s >\n",
					name);
				rv = 0;
				goto ret;
E 6
I 6
	if ((dir = opendir(".")) == NULL) {
		fprintf(stderr, "find: cannot open < %s >\n", name);
		rv = 0;
		goto ret;
	}
	for (dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
		if ((dp->d_name[0]=='.' && dp->d_name[1]=='\0') ||
		    (dp->d_name[0]=='.' && dp->d_name[1]=='.' && dp->d_name[2]=='\0'))
			continue;
		c1 = endofname;
		*c1++ = '/';
		strcpy(c1, dp->d_name);
		Fname = endofname+1;
		if(!descend(name, Fname, exlist)) {
			*endofname = '\0';
			chdir(Home);
			if(chdir(Pathname) == -1) {
				fprintf(stderr, "find: bad directory tree\n");
				exit(1);
E 6
			}
E 26
I 26
    
	/*
	 * if the user didn't specify one of -print, -ok or -exec, then -print
D 50
	 * is assumed so we add a -print node on the end.  It is possible that
	 * the user might want the -print someplace else on the command line,
	 * but there's no way to know that.
E 50
I 50
	 * is assumed so we bracket the current expression with parens, if
	 * necessary, and add a -print node on the end.
E 50
	 */
D 35
	if (!output_specified) {
E 35
I 35
	if (!isoutput) {
E 35
D 50
		new = c_print();
		if (plan == NULL)
E 50
I 50
		if (plan == NULL) {
			new = c_print();
E 50
			tail = plan = new;
D 50
		else {
E 50
I 50
		} else {
			new = c_openparen();
			new->next = plan;
			plan = new;
			new = c_closeparen();
E 50
			tail->next = new;
			tail = new;
I 50
			new = c_print();
			tail->next = new;
			tail = new;
E 50
E 26
D 6
			if(offset) lseek(dir, (long)offset, 0);
			if(read(dir, (char *)dentry, dsize)<0) {
				fprintf(stderr, "find: cannot read < %s >\n",
					name);
				rv = 0;
				goto ret;
			}
			if(dir > 10) {
				close(dir);
				dir = 0;
			}
		} else 
			if(read(dir, (char *)dentry, dsize)<0) {
				fprintf(stderr, "find: cannot read < %s >\n",
					name);
				rv = 0;
				goto ret;
			}
		for(dp=dentry, entries=dsize>>4; entries; --entries, ++dp) { /* each directory entry */
			if(dp->d_ino==0
			|| (dp->d_name[0]=='.' && dp->d_name[1]=='\0')
			|| (dp->d_name[0]=='.' && dp->d_name[1]=='.' && dp->d_name[2]=='\0'))
				continue;
			c1 = endofname;
			*c1++ = '/';
			c2 = dp->d_name;
			for(i=0; i<14; ++i)
				if(*c2)
					*c1++ = *c2++;
				else
					break;
			*c1 = '\0';
			if(c1 == endofname) { /* ?? */
				rv = 0;
				goto ret;
			}
			Fname = endofname+1;
			if(!descend(name, Fname, exlist)) {
				*endofname = '\0';
				chdir(Home);
				if(chdir(Pathname) == -1) {
					fprintf(stderr, "find: bad directory tree\n");
					exit(1);
				}
			}
E 6
		}
	}
D 26
	rv = 1;
ret:
	if(dir)
D 6
		close(dir);
E 6
I 6
		closedir(dir);
E 6
	if(chdir("..") == -1) {
		*endofname = '\0';
		fprintf(stderr, "find: bad directory <%s>\n", name);
		rv = 1;
	}
	return(rv);
}
E 26
I 26
    
	/*
	 * the command line has been completely processed into a search plan
	 * except for the (, ), !, and -o operators.  Rearrange the plan so
	 * that the portions of the plan which are affected by the operators
	 * are moved into operator nodes themselves.  For example:
	 *
	 *	[!]--> [-name foo]--> [-print]
	 *
	 * becomes
	 *
	 *	[! [-name foo] ]--> [-print]
	 *
	 * and
	 *
	 *	[(]--> [-depth]--> [-name foo]--> [)]--> [-print]
	 *
	 * becomes
	 *
	 *	[expr [-depth]-->[-name foo] ]--> [-print]
	 *
	 * operators are handled in order of precedence.
	 */
E 26

D 26
gmatch(s, p) /* string match as in glob */
register char *s, *p;
{
	if (*s=='.' && *p!='.') return(0);
	return amatch(s, p);
E 26
I 26
D 36
	plan = find_squish_paren(plan);		/* ()'s */
	plan = find_squish_not(plan);		/* !'s */
	plan = find_squish_or(plan);		/* -o's */
E 36
I 36
	plan = paren_squish(plan);		/* ()'s */
	plan = not_squish(plan);		/* !'s */
	plan = or_squish(plan);			/* -o's */
E 36
D 45
	return(plan);
E 45
I 45
	return (plan);
E 45
E 26
}
D 26

amatch(s, p)
register char *s, *p;
{
	register cc;
	int scc, k;
	int c, lc;

	scc = *s;
	lc = 077777;
	switch (c = *p) {

	case '[':
		k = 0;
		while (cc = *++p) {
			switch (cc) {

			case ']':
				if (k)
					return(amatch(++s, ++p));
				else
					return(0);

			case '-':
D 13
				k |= lc <= scc & scc <= (cc=p[1]);
E 13
I 13
D 18
				k |= lc <= scc && scc <= (cc=p[1]);
E 18
I 18
				cc = p[1];
				k |= lc <= scc && scc <= cc;
E 18
E 13
			}
			if (scc==(lc=cc)) k++;
		}
		return(0);

	case '?':
	caseq:
		if(scc) return(amatch(++s, ++p));
		return(0);
	case '*':
		return(umatch(s, ++p));
	case 0:
		return(!scc);
	}
	if (c==scc) goto caseq;
	return(0);
}

umatch(s, p)
register char *s, *p;
{
	if(*p==0) return(1);
	while(*s)
		if (amatch(s++, p)) return(1);
	return(0);
}

bwrite(rp, c)
register short *rp;
register c;
{
	register short *wp = Wp;

	c = (c+1) >> 1;
	while(c--) {
		if(!Wct) {
again:
			if(write(Cpio, (char *)Dbuf, Bufsize)<0) {
				Cpio = chgreel(1, Cpio);
				goto again;
			}
			Wct = Bufsize >> 1;
			wp = Dbuf;
			++Blocks;
		}
		*wp++ = *rp++;
		--Wct;
	}
	Wp = wp;
}
chgreel(x, fl)
{
	register f;
	char str[22];
	FILE *devtty;
	struct stat statb;
	extern errno;

	fprintf(stderr, "find: errno: %d, ", errno);
	fprintf(stderr, "find: can't %s\n", x? "write output": "read input");
	fstat(fl, &statb);
	if((statb.st_mode&S_IFMT) != S_IFCHR)
		exit(1);
again:
	fprintf(stderr, "If you want to go on, type device/file name %s\n",
		"when ready");
D 22
	devtty = fopen("/dev/tty", "r");
E 22
I 22
	devtty = fopen(_PATH_TTY, "r");
E 22
	fgets(str, 20, devtty);
	str[strlen(str) - 1] = '\0';
	if(!*str)
		exit(1);
	close(fl);
	if((f = open(str, x? 1: 0)) < 0) {
		fprintf(stderr, "That didn't work");
		fclose(devtty);
		goto again;
	}
	return f;
}
I 8
D 25

#ifdef	AMES
/*
 * 'fastfind' scans a file list for the full pathname of a file
 * given only a piece of the name.  The list has been processed with
 * with "front-compression" and bigram coding.  Front compression reduces
 * space by a factor of 4-5, bigram coding by a further 20-25%.
 * The codes are:
 *
 *	0-28	likeliest differential counts + offset to make nonnegative 
D 23
 *	30	escape code for out-of-range count to follow in next word
D 9
 *	128-255 bigram codes, (128 most common, as determined by 'find.squeeze')
E 9
I 9
 *	128-255 bigram codes, (128 most common, as determined by 'updatedb')
E 9
 *	32-127  single character (printable) ascii residue
E 23
I 23
 *	30	switch code for out-of-range count to follow in next word
 *	128-255 bigram codes (128 most common, as determined by 'updatedb')
 *	32-127  single character (printable) ascii residue (ie, literal)
E 23
 *
 * A novel two-tiered string search technique is employed: 
 *
 * First, a metacharacter-free subpattern and partial pathname is
 * matched BACKWARDS to avoid full expansion of the pathname list.
 * The time savings is 40-50% over forward matching, which cannot efficiently
 * handle overlapped search patterns and compressed path residue.
 *
 * Then, the actual shell glob-style regular expression (if in this form)
 * is matched against the candidate pathnames using the slower routines
 * provided in the standard 'find'.
 */

I 23
#include "find.h"

E 23
D 9
#define	FCODES 	"/etc/find.codes"
E 9
I 9
D 22
#define	FCODES 	"/usr/lib/find/find.codes"
E 22
E 9
#define	YES	1
#define	NO	0
D 23
#define	OFFSET	14
#define	ESCCODE	30
E 23

fastfind ( pathpart )	
	char pathpart[];
{
	register char *p, *s;
	register int c; 
	char *q, *index(), *patprep();
D 13
	int i, count, globflag;
E 13
I 13
D 23
	int i, count = 0, globflag;
E 23
I 23
	int count = 0, found = NO, globflag;
E 23
E 13
	FILE *fp, *fopen();
	char *patend, *cutoff;
D 23
	char path[1024];
	char bigram1[128], bigram2[128];
	int found = NO;
E 23
I 23
	char path[MAXPATHLEN];
	char bigram1[NBG], bigram2[NBG];
E 23

D 22
	if ( (fp = fopen ( FCODES, "r" )) == NULL ) {
D 13
		fprintf ( "find: can't open %s\n", FCODES );
E 13
I 13
		fprintf ( stderr, "find: can't open %s\n", FCODES );
E 22
I 22
	if ( (fp = fopen ( _PATH_FCODES, "r" )) == NULL ) {
D 23
		fprintf ( stderr, "find: can't open %s\n", _PATH_FCODES );
E 23
I 23
		perror( _PATH_FCODES );
E 23
E 22
E 13
		exit ( 1 );
	}
D 23
	for ( i = 0; i < 128; i++ ) 
		bigram1[i] = getc ( fp ),  bigram2[i] = getc ( fp );
E 23
I 23
	for ( c = 0, p = bigram1, s = bigram2; c < NBG; c++ ) 
		p[c] = getc ( fp ),  s[c] = getc ( fp );
E 23
D 21
	
	if ( index ( pathpart, '*' ) || index ( pathpart, '?' ) || index ( pathpart, '[' ) )
		globflag = YES;
E 21
I 21

D 23
	globflag = index ( pathpart, '*' ) || index ( pathpart, '?' ) ||
		index ( pathpart, '[' );
E 21
	patend = patprep ( pathpart );
E 23
I 23
	p = pathpart;
	globflag = index ( p, '*' ) || index ( p, '?' ) || index ( p, '[' );
	patend = patprep ( p );
E 23

D 23
	c = getc ( fp );
	for ( ; ; ) {
E 23
I 23
D 24
	for ( c = getc ( fp ); ; ) {
E 24
I 24
	for ( c = getc ( fp ); c != EOF; ) {
E 24
E 23

D 23
		count += ( (c == ESCCODE) ? getw ( fp ) : c ) - OFFSET;
E 23
I 23
		count += ( (c == SWITCH) ? getw ( fp ) : c ) - OFFSET;
E 23

D 23
		for ( p = path + count; (c = getc ( fp )) > ESCCODE; )	/* overlay old path */
			if ( c < 0200 )	
E 23
I 23
		for ( p = path + count; (c = getc ( fp )) > SWITCH; )	/* overlay old path */
			if ( c < PARITY )	
E 23
				*p++ = c;
D 23
			else		/* bigrams are parity-marked */
				*p++ = bigram1[c & 0177],  *p++ = bigram2[c & 0177];
E 23
I 23
			else {			/* bigrams are parity-marked */
				c &= PARITY-1;
				*p++ = bigram1[c], *p++ = bigram2[c];
			}
E 23
D 24
		if ( c == EOF )
			break;
E 24
		*p-- = NULL;
D 23
		cutoff = ( found ? path : path + count);
E 23
I 23
		cutoff = ( found ? path : path + count );
E 23

		for ( found = NO, s = p; s >= cutoff; s-- ) 
			if ( *s == *patend ) {		/* fast first char check */
				for ( p = patend - 1, q = s - 1; *p != NULL; p--, q-- )
					if ( *q != *p )
						break;
				if ( *p == NULL ) {	/* success on fast match */
					found = YES;
					if ( globflag == NO || amatch ( path, pathpart ) )
						puts ( path );
					break;
				}
			}
	}
}

/*
D 12
    extract first glob-free subpattern for fast pre-match;
    prepend NULL for backwards match; return end of pattern
E 12
I 12
    extract last glob-free subpattern in name for fast pre-match;
    prepend '\0' for backwards match; return end of new pattern
E 12
*/
static char globfree[100];

char *
D 12
patprep ( p )
	register char *p;
E 12
I 12
patprep ( name )
	char *name;
E 12
{
I 12
	register char *p, *endmark;
E 12
	register char *subp = globfree;

D 12
	while ( *p == '*' || *p == '?' )
		p++;
	if ( *p == '[' ) {
		while ( *p != ']' && *p != NULL )
			p++;
		p++;
	}
	*subp++ = NULL;
	if ( *p != NULL )		/* copy first noglob string */
		while ( *p != '*' && *p != '?' && *p != '[' && *p != NULL &&
		      subp < (globfree + sizeof(globfree)) )
E 12
I 12
	*subp++ = '\0';
	p = name + strlen ( name ) - 1;
	/*
	   skip trailing metacharacters (and [] ranges)
	*/
	for ( ; p >= name; p-- )
		if ( index ( "*?", *p ) == 0 )
			break;
	if ( p < name )
		p = name;
	if ( *p == ']' )
		for ( p--; p >= name; p-- )
			if ( *p == '[' ) {
				p--;
				break;
			}
	if ( p < name )
		p = name;
	/*
	   if pattern has only metacharacters,
	   check every path (force '/' search)
	*/
	if ( (p == name) && index ( "?*[]", *p ) != 0 )
		*subp++ = '/';					
	else {				
		for ( endmark = p; p >= name; p-- )
			if ( index ( "]*?", *p ) != 0 )
				break;
		for ( ++p; (p <= endmark) && subp < (globfree + sizeof ( globfree )); )
E 12
			*subp++ = *p++;
D 12
	else				/* pattern has noglob chars only */
		*subp++ = '/';		/* ... check every path */
	*subp = NULL;
E 12
I 12
	}
	*subp = '\0';
E 12
	return ( --subp );
}
#endif
E 25
I 13

/* rest should be done with nameserver or database */

#include <pwd.h>
#include <grp.h>
#include <utmp.h>

struct	utmp utmp;
#define	NMAX	(sizeof (utmp.ut_name))
#define SCPYN(a, b)	strncpy(a, b, NMAX)

#define NUID	64
#define NGID	300

struct ncache {
	int	uid;
	char	name[NMAX+1];
} nc[NUID];
char	outrangename[NMAX+1];
int	outrangeuid = -1;
char	groups[NGID][NMAX+1];
char	outrangegroup[NMAX+1];
int	outrangegid = -1;

E 26
I 26
 
I 40
FTS *tree;			/* pointer to top of FTS hierarchy */

E 40
E 26
/*
D 26
 * This function assumes that the password file is hashed
 * (or some such) to allow fast access based on a name key.
 * If this isn't true, duplicate the code for getgroup().
E 26
I 26
 * find_execute --
 *	take a search plan and an array of search paths and executes the plan
 *	over all FTSENT's returned for the given search paths.
E 26
 */
I 40
D 47
void
E 47
I 47
int
E 47
E 40
D 26
char *
getname(uid)
E 26
I 26
find_execute(plan, paths)
	PLAN *plan;		/* search plan */
	char **paths;		/* array of pathnames to traverse */
E 26
{
D 26
	register struct passwd *pw;
	struct passwd *getpwent();
	register int cp;
D 16
#ifndef	NO_PW_STAYOPEN
E 16
D 22
	extern int _pw_stayopen;
E 22

D 22
	_pw_stayopen = 1;
D 16
#endif
E 16

E 22
D 16
#if	((NUID) & ((NUID) - 1) != 0)
E 16
I 16
#if	(((NUID) & ((NUID) - 1)) != 0)
E 16
	cp = uid % (NUID);
#else
	cp = uid & ((NUID) - 1);
#endif
	if (uid >= 0 && nc[cp].uid == uid && nc[cp].name[0])
		return (nc[cp].name);
	pw = getpwuid(uid);
	if (!pw)
		return (0);
	nc[cp].uid = uid;
	SCPYN(nc[cp].name, pw->pw_name);
	return (nc[cp].name);
}

char *
getgroup(gid)
{
	register struct group *gr;
	static init;
	struct group *getgrent();

	if (gid >= 0 && gid < NGID && groups[gid][0])
		return (&groups[gid][0]);
	if (gid >= 0 && gid == outrangegid)
		return (outrangegroup);
rescan:
	if (init == 2) {
		if (gid < NGID)
			return (0);
		setgrent();
		while (gr = getgrent()) {
			if (gr->gr_gid != gid)
				continue;
			outrangegid = gr->gr_gid;
			SCPYN(outrangegroup, gr->gr_name);
			endgrent();
			return (outrangegroup);
		}
		endgrent();
		return (0);
E 26
I 26
D 35
	FTSENT *entry;		/* current fts entry */
E 35
I 35
	register FTSENT *entry;
E 35
	PLAN *p;
I 47
	int rval;
E 47
    
D 35
	if (!(tree = ftsopen(paths, ftsoptions, NULL))) {
E 35
I 35
D 37
	/*
	 * If need stat info, might as well quit when the directory isn't
	 * searchable.
	 */
	if (!(ftsoptions & FTS_NOSTAT))
		isstopdnx = 1;

E 37
D 40
	if (!(tree = fts_open(paths, ftsoptions, (int (*)())NULL))) {
E 35
D 37
		(void)fprintf(stderr, "find: ftsopen: %s.\n", strerror(errno));
E 37
I 37
		error("ftsopen", errno);
E 37
		exit(1);
E 26
	}
E 40
I 40
D 47
	if (!(tree = fts_open(paths, ftsoptions, (int (*)())NULL)))
E 47
I 47
	if ((tree = fts_open(paths, ftsoptions, (int (*)())NULL)) == NULL)
E 47
D 45
		err("ftsopen: %s", strerror(errno));
E 45
I 45
		err(1, "ftsopen");
E 45
E 40
D 26
	if (init == 0)
		setgrent(), init = 1;
	while (gr = getgrent()) {
		if (gr->gr_gid < 0 || gr->gr_gid >= NGID) {
			if (gr->gr_gid == gid) {
				outrangegid = gr->gr_gid;
				SCPYN(outrangegroup, gr->gr_name);
				return (outrangegroup);
			}
E 26
I 26
D 35
	while (entry = ftsread(tree)) {
E 35
I 35

D 47
	while (entry = fts_read(tree)) {
E 35
D 29
		switch(entry->info) {
E 29
I 29
		switch(entry->fts_info) {
E 47
I 47
	for (rval = 0; (entry = fts_read(tree)) != NULL;) {
		switch (entry->fts_info) {
E 47
E 29
D 37
		case FTS_DNR:
			(void)fprintf(stderr,
D 29
			    "find: %s: unable to read.\n", entry->path);
E 29
I 29
			    "find: %s: unable to read.\n", entry->fts_path);
E 29
E 26
			continue;
D 26
		}
		if (groups[gr->gr_gid][0])
E 26
I 26
D 35
		case FTS_DNX:
			(void)fprintf(stderr,
E 35
I 35
		case FTS_DNX: {
			/*
			 * If can't search the directory, but able to read it,
			 * and don't need stat information or to exec/ok the
			 * file, use the fts_children list.
			 */
			register char *t;

			if (isstopdnx)
				goto srcherr;
			errno = 0;
			entry = fts_children(tree);
			if (errno)
				goto srcherr;
			for (t = entry->fts_path; *t; ++t);
			*t = '/';
			for (; entry; entry = entry->fts_link) {
				(void)bcopy(entry->fts_name, t + 1,
				    entry->fts_namelen + 1);
				for (p = plan; p && (p->eval)(p, entry);
				    p = p->next);
			}
			continue;

srcherr:		(void)fprintf(stderr,
E 35
D 29
			    "find: %s: unable to search.\n", entry->path);
E 29
I 29
			    "find: %s: unable to search.\n", entry->fts_path);
E 29
E 26
			continue;
I 35
		}
E 35
D 26
		SCPYN(groups[gr->gr_gid], gr->gr_name);
		if (gr->gr_gid == gid)
			return (&groups[gid][0]);
	}
	init = 2;
	goto rescan;
}
E 26
I 26
		case FTS_ERR:
			(void)fprintf(stderr,
D 29
			    "find: %s: %s.\n", entry->path, strerror(errno));
E 29
I 29
			    "find: %s: %s.\n", entry->fts_path,
			    strerror(errno));
E 29
			continue;
E 37
		case FTS_D:
D 35
			if (depth)
E 35
I 35
			if (isdepth)
E 35
				continue;
			break;
D 37
		case FTS_DC:
			(void)fprintf(stderr,
D 29
			    "find: directory cycle: %s.\n", entry->path);
E 29
I 29
			    "find: directory cycle: %s.\n", entry->fts_path);
E 29
			continue;
E 37
		case FTS_DP:
D 35
			if (!depth)
E 35
I 35
			if (!isdepth)
E 35
				continue;
I 34
			break;
I 37
		case FTS_DNR:
		case FTS_ERR:
E 37
E 34
		case FTS_NS:
I 43
			(void)fflush(stdout);
I 47
D 48
			errno = entry->fts_errno;
E 47
E 43
D 37
			if (!(ftsoptions & FTS_NOSTAT)) {
				(void)fprintf(stderr,
D 29
				    "find: can't stat: %s.\n", entry->path);
E 29
I 29
				    "find: can't stat: %s.\n", entry->fts_path);
E 29
				continue;
			}
			break;
E 37
I 37
D 40
			error(entry->fts_path, errno);
E 40
I 40
D 41
			err("%s: %s", entry->fts_path, strerror(errno));
E 41
I 41
D 45
			(void)fprintf(stderr, "find: %s: %s\n", 
			    entry->fts_path, strerror(errno));
E 45
I 45
			warn("%s", entry->fts_path);
E 48
I 48
			warnx("%s: %s",
			    entry->fts_path, strerror(entry->fts_errno));
E 48
I 47
			rval = 1;
E 47
E 45
E 41
E 40
			continue;
I 50
#ifdef FTS_W
E 50
I 49
		case FTS_W:
			continue;
I 50
#endif /* FTS_W */
E 50
E 49
I 39
D 44
		case FTS_SL:
			if (entry->fts_level == FTS_ROOTLEVEL) {
				(void)fts_set(tree, entry, FTS_FOLLOW);
				continue;
			}
			break;
E 44
E 39
E 37
		}
E 26
D 44

E 44
I 38
#define	BADCH	" \t\n\\'\""
		if (isxargs && strpbrk(entry->fts_path, BADCH)) {
I 43
			(void)fflush(stdout);
E 43
D 45
			(void)fprintf(stderr,
			    "find: illegal path: %s\n", entry->fts_path);
E 45
I 45
			warnx("%s: illegal path", entry->fts_path);
I 47
			rval = 1;
E 47
E 45
			continue;
		}
		 
E 38
D 26
int
getuid(username)
	char *username;
{
	register struct passwd *pw;
	struct passwd *getpwnam();
D 22
#ifndef	NO_PW_STAYOPEN
	extern int _pw_stayopen;

	_pw_stayopen = 1;
#endif
E 22

	pw = getpwnam(username);
	if (pw != NULL)
		return (pw->pw_uid);
	else
		return (-1);
}

int
getgid(groupname)
	char *groupname;
{
	register struct group *gr;
	struct group *getgrnam();

	gr = getgrnam(groupname);
	if (gr != NULL)
		return (gr->gr_gid);
	else
		return (-1);
}

#define permoffset(who)		((who) * 3)
#define permission(who, type)	((type) >> permoffset(who))
#define kbytes(bytes)		(((bytes) + 1023) / 1024)

list(file, stp)
	char *file;
	register struct stat *stp;
{
	char pmode[32], uname[32], gname[32], fsize[32], ftime[32];
	char *getname(), *getgroup(), *ctime();
	static long special[] = { S_ISUID, 's', S_ISGID, 's', S_ISVTX, 't' };
	static time_t sixmonthsago = -1;
#ifdef	S_IFLNK
	char flink[MAXPATHLEN + 1];
#endif
	register int who;
	register char *cp;
	time_t now;

	if (file == NULL || stp == NULL)
		return (-1);

	time(&now);
	if (sixmonthsago == -1)
		sixmonthsago = now - 6L*30L*24L*60L*60L;

	switch (stp->st_mode & S_IFMT) {
#ifdef	S_IFDIR
	case S_IFDIR:	/* directory */
		pmode[0] = 'd';
		break;
#endif
#ifdef	S_IFCHR
	case S_IFCHR:	/* character special */
		pmode[0] = 'c';
		break;
#endif
#ifdef	S_IFBLK
	case S_IFBLK:	/* block special */
		pmode[0] = 'b';
		break;
#endif
#ifdef	S_IFLNK
	case S_IFLNK:	/* symbolic link */
		pmode[0] = 'l';
		break;
#endif
#ifdef	S_IFSOCK
	case S_IFSOCK:	/* socket */
		pmode[0] = 's';
		break;
#endif
#ifdef	S_IFREG
	case S_IFREG:	/* regular */
#endif
	default:
		pmode[0] = '-';
		break;
	}

	for (who = 0; who < 3; who++) {
		if (stp->st_mode & permission(who, S_IREAD))
			pmode[permoffset(who) + 1] = 'r';
		else
			pmode[permoffset(who) + 1] = '-';

		if (stp->st_mode & permission(who, S_IWRITE))
			pmode[permoffset(who) + 2] = 'w';
		else
			pmode[permoffset(who) + 2] = '-';

		if (stp->st_mode & special[who * 2])
			pmode[permoffset(who) + 3] = special[who * 2 + 1];
		else if (stp->st_mode & permission(who, S_IEXEC))
			pmode[permoffset(who) + 3] = 'x';
		else
			pmode[permoffset(who) + 3] = '-';
	}
	pmode[permoffset(who) + 1] = '\0';

	cp = getname(stp->st_uid);
	if (cp != NULL)
		sprintf(uname, "%-9.9s", cp);
	else
		sprintf(uname, "%-9d", stp->st_uid);

	cp = getgroup(stp->st_gid);
	if (cp != NULL)
		sprintf(gname, "%-9.9s", cp);
	else
		sprintf(gname, "%-9d", stp->st_gid);

	if (pmode[0] == 'b' || pmode[0] == 'c')
		sprintf(fsize, "%3d,%4d",
			major(stp->st_rdev), minor(stp->st_rdev));
	else {
		sprintf(fsize, "%8ld", stp->st_size);
#ifdef	S_IFLNK
		if (pmode[0] == 'l') {
D 15
			who = readlink(file, flink, sizeof flink - 1);
E 15
I 15
			/*
			 * Need to get the tail of the file name, since we have
			 * already chdir()ed into the directory of the file
			 */
			cp = rindex(file, '/');
			if (cp == NULL)
				cp = file;
			else
				cp++;
			who = readlink(cp, flink, sizeof flink - 1);
E 15
			if (who >= 0)
				flink[who] = '\0';
I 15
			else
				flink[0] = '\0';
E 26
I 26
D 30
		/* always keep curdev up to date, -fstype uses it. */
D 29
		if (xdev && curdev != entry->statb.st_dev &&
E 29
I 29
		if (xdev && curdev != entry->fts_statb.st_dev &&
E 29
D 27
		    ftsset(tree, entry, FTS_SKIP)) {
E 27
I 27
		    curdev != -1 && ftsset(tree, entry, FTS_SKIP)) {
E 27
			(void)fprintf(stderr, "find: %s: %s.\n",
D 29
			    entry->path, strerror(errno));
E 29
I 29
			    entry->fts_path, strerror(errno));
E 29
			exit(1);
E 26
E 15
		}
D 26
#endif
	}
E 26

E 30
D 26
	cp = ctime(&stp->st_mtime);
	if (stp->st_mtime < sixmonthsago || stp->st_mtime > now)
		sprintf(ftime, "%-7.7s %-4.4s", cp + 4, cp + 20);
	else
		sprintf(ftime, "%-12.12s", cp + 4);
E 26
I 26
		/*
D 47
		 * call all the functions in the execution plan until one is
E 47
I 47
		 * Call all the functions in the execution plan until one is
E 47
		 * false or all have been executed.  This is where we do all
		 * the work specified by the user on the command line.
		 */
		for (p = plan; p && (p->eval)(p, entry); p = p->next);
E 26
D 30

D 26
	printf("%5lu %4ld %s %2d %s%s%s %s %s%s%s\n",
		stp->st_ino,				/* inode #	*/
#ifdef	S_IFSOCK
		(long) kbytes(dbtob(stp->st_blocks)),	/* kbytes       */
#else
		(long) kbytes(stp->st_size),		/* kbytes       */
#endif
		pmode,					/* protection	*/
		stp->st_nlink,				/* # of links	*/
		uname,					/* owner	*/
		gname,					/* group	*/
		fsize,					/* # of bytes	*/
		ftime,					/* modify time	*/
		file,					/* name		*/
#ifdef	S_IFLNK
		(pmode[0] == 'l') ? " -> " : "",
		(pmode[0] == 'l') ? flink  : ""		/* symlink	*/
#else
		"",
		""
#endif
	);

	return (0);
E 26
I 26
D 29
		curdev = entry->statb.st_dev;
E 29
I 29
		curdev = entry->fts_statb.st_dev;
E 30
E 29
	}
D 35
	(void)ftsclose(tree);
E 35
I 35
D 47
	(void)fts_close(tree);
E 47
I 47
	if (errno)
		err(1, "fts_read");
	return (rval);
E 47
E 35
E 26
}
E 13
E 8
E 1
