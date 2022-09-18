h07145
s 00026/00032/00368
d D 8.2 94/04/02 10:44:31 pendry 30 29
c prettyness police
e
s 00005/00005/00395
d D 8.1 93/06/06 14:53:43 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00040/00031/00360
d D 5.20 93/05/19 14:55:48 bostic 28 27
c lint, prettiness police
e
s 00023/00013/00368
d D 5.19 93/05/17 13:57:25 torek 27 26
c rm incorrect declaration of lseek; cleanup, prototype, pass -Wall
e
s 00005/00009/00376
d D 5.18 91/03/01 14:27:28 bostic 26 25
c ANSI
e
s 00001/00011/00384
d D 5.17 90/06/01 16:54:29 bostic 25 24
c new copyright notice
e
s 00008/00004/00387
d D 5.16 89/12/19 11:02:07 bostic 24 23
c make output line buffered if selecting only some of the entries
e
s 00003/00002/00388
d D 5.15 89/05/10 22:46:20 bostic 23 22
c file reorg, pathnames.h, paths.h
e
s 00036/00030/00354
d D 5.14 88/10/21 11:07:36 bostic 22 21
c I messed up kludge allowing getopt to handle -#
e
s 00011/00014/00373
d D 5.13 88/09/22 10:46:07 bostic 21 20
c use utmp.h UT_ defines
e
s 00016/00004/00371
d D 5.12 88/09/20 15:39:44 bostic 20 19
c fix to work with new wtmp stuff; notice date resets
e
s 00010/00005/00365
d D 5.11 88/06/29 21:50:46 bostic 19 18
c install approved copyright notice
e
s 00001/00001/00369
d D 5.10 88/01/03 01:00:18 bostic 18 17
c picked and dropped code a little too quickly...
e
s 00012/00006/00358
d D 5.9 87/11/30 10:47:14 bostic 17 16
c written by Howard Katseff; add Berkeley specific copyright
e
s 00090/00052/00274
d D 5.8 87/09/10 11:23:24 bostic 16 15
c allow "last p5" for compatibility, use allocated linked list of ttys,
c allow "/dev/ttyp5".
e
s 00220/00149/00106
d D 5.7 87/09/09 17:05:03 bostic 15 14
c increased TTYS to 500, read buffer to 1K; rewrote to require 
c flags for specifying hosts or ttys.  Changed to modify host arguments 
c a la login(1) if domain is same as current machine.
e
s 00002/00000/00253
d D 5.6 86/12/22 10:35:01 bostic 14 13
c fixed initialization problem in want()
e
s 00021/00004/00232
d D 5.5 86/12/10 05:58:35 bostic 13 12
c added hostname capability
e
s 00163/00141/00073
d D 5.4 86/12/09 22:14:52 bostic 12 11
c well, I started looking at this to add a flag to allow the use of a
c file other than /usr/adm/wtmp.  The code was pretty bad.  Don't diff
c this version against any of the previous ones.
e
s 00001/00000/00213
d D 5.3 86/05/15 01:55:51 lepreau 11 10
c fflush after signal: need when rsh'ed
e
s 00004/00000/00209
d D 5.2 86/03/21 05:52:45 lepreau 10 9
c apply ftp's bandaid to uucp too.
e
s 00014/00002/00195
d D 5.1 85/05/31 09:17:58 dist 9 8
c Add copyright
e
s 00004/00002/00193
d D 4.8 83/09/25 20:24:54 karels 8 7
c no logout time for reboot; minor format change
e
s 00004/00000/00191
d D 4.7 83/07/20 00:16:48 sam 7 6
c bandaid to allow ftp lookups
e
s 00001/00001/00190
d D 4.6 83/07/01 02:53:44 sam 6 5
c include fix
e
s 00011/00004/00180
d D 4.5 83/05/22 23:58:50 sam 5 4
c utmp changed format
e
s 00016/00004/00168
d D 4.4 83/04/28 18:07:58 dlw 4 3
c added -N option. DLW
e
s 00010/00003/00162
d D 4.3 81/02/28 23:00:33 wnj 3 2
c new reboot scheme
e
s 00004/00005/00161
d D 4.2 80/10/10 00:48:52 bill 2 1
c misc bug fixes
e
s 00166/00000/00000
d D 4.1 80/10/01 17:27:14 bill 1 0
c date and time created 80/10/01 17:27:14 by bill
e
u
U
t
T
I 9
/*
D 17
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 17
I 17
D 29
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
E 29
I 29
D 30
 * Copyright (c) 1987, 1993
E 30
I 30
 * Copyright (c) 1987, 1993, 1994
E 30
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
D 25
 * Redistribution and use in source and binary forms are permitted
D 19
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 19
I 19
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
E 19
E 17
 */

E 9
I 5
#ifndef lint
E 5
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 9
static	char *sccsid = "%W% (Berkeley) %G%";
I 5
#endif
E 9
I 9
D 29
char copyright[] =
D 17
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 17
I 17
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 17
 All rights reserved.\n";
E 29
I 29
static char copyright[] =
D 30
"%Z% Copyright (c) 1987, 1993\n\
E 30
I 30
"%Z% Copyright (c) 1987, 1993, 1994\n\
E 30
	The Regents of the University of California.  All rights reserved.\n";
E 29
D 17
#endif not lint
E 17
I 17
#endif /* not lint */
E 17

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 17
#endif not lint
E 17
I 17
#endif /* not lint */
E 17
E 9

E 5
E 2
D 28
/*
 * last
 */
E 28
D 15
#include <sys/types.h>
E 15
I 15
#include <sys/param.h>
E 15
D 12
#include <stdio.h>
#include <signal.h>
E 12
D 6
#include <stat.h>
E 6
I 6
#include <sys/stat.h>
I 12
D 27
#include <sys/file.h>
E 27
I 27

I 28
#include <err.h>
E 28
#include <fcntl.h>
I 28
#include <paths.h>
E 28
E 27
#include <signal.h>
I 27
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 27
#include <time.h>
I 28
#include <tzfile.h>
E 28
I 27
#include <unistd.h>
E 27
D 15
#include <pwd.h>
E 15
E 12
E 6
#include <utmp.h>
I 12
D 15
#include <strings.h>
E 15
D 27
#include <stdio.h>
E 27
I 23
D 28
#include <paths.h>
E 28
E 23
D 15
#include <ctype.h>
E 15
E 12

D 12
#define NMAX	sizeof(buf[0].ut_name)
#define LMAX	sizeof(buf[0].ut_line)
I 5
#define	HMAX	sizeof(buf[0].ut_host)
E 5
#define	SECDAY	(24*60*60)
E 12
I 12
D 15
#define MAXTTYS	200				/* max ttys last can handle */
#define SECDAY	(24*60*60)			/* seconds in a day */
#define NO	0				/* false/no */
#define YES	1				/* true/yes */
E 15
I 15
D 16
#define	MAXTTYS	500				/* max ttys last can handle */
E 16
D 28
#define	SECDAY	(24*60*60)			/* seconds in a day */
E 28
#define	NO	0				/* false/no */
#define	YES	1				/* true/yes */
E 15
E 12

D 12
#define	lineq(a,b)	(!strncmp(a,b,LMAX))
#define	nameq(a,b)	(!strncmp(a,b,NMAX))
I 5
#define	hosteq(a,b)	(!strncmp(a,b,HMAX))
E 12
I 12
D 15
static struct utmp	buf[500];		/* utmp read buffer */
#define HMAX	sizeof(buf[0].ut_host)		/* size of utmp host field */
#define LMAX	sizeof(buf[0].ut_line)		/* size of utmp tty field */
#define NMAX	sizeof(buf[0].ut_name)		/* size of utmp name field */
E 15
I 15
static struct utmp	buf[1024];		/* utmp read buffer */
E 15
E 12
E 5

D 12
#define MAXTTYS 256
E 12
I 12
D 15
#define lineq(a,b)	(!strncmp(a,b,LMAX))
#define nameq(a,b)	(!strncmp(a,b,NMAX))
#define hosteq(a,b)	(!strncmp(a,b,HMAX))
E 15
I 15
D 21
#define	HMAX	sizeof(buf[0].ut_host)		/* size of utmp host field */
#define	LMAX	sizeof(buf[0].ut_line)		/* size of utmp tty field */
#define	NMAX	sizeof(buf[0].ut_name)		/* size of utmp name field */
E 15
E 12

E 21
I 15
typedef struct arg {
	char	*name;				/* argument */
#define	HOST_TYPE	-2
#define	TTY_TYPE	-3
#define	USER_TYPE	-4
	int	type;				/* type of arg */
	struct arg	*next;			/* linked list pointer */
} ARG;
D 16
ARG	*head;					/* head of linked list */
E 16
I 16
ARG	*arglist;				/* head of linked list */
E 16

E 15
D 12
char	**argv;
int	argc;
I 4
int	nameargs;
E 12
I 12
typedef struct ttytab {
	long	logout;				/* log out time */
D 21
	char	tty[LMAX + 1];			/* terminal name */
E 21
I 21
	char	tty[UT_LINESIZE + 1];		/* terminal name */
E 21
D 16
} TTYS;
E 16
I 16
	struct ttytab	*next;			/* linked list pointer */
} TTY;
TTY	*ttylist;				/* head of linked list */
E 16
E 12
E 4

D 12
struct	utmp buf[128];
char	ttnames[MAXTTYS][LMAX+1];
long	logouts[MAXTTYS];
E 12
I 12
D 16
static TTYS	tab[MAXTTYS + 1];		/* tty table */
D 15
static char	**sargs;			/* start of selections args */
E 15
I 15
static long	maxrec;				/* records to display */
E 16
I 16
static long	currentout,			/* current logout value */
		maxrec;				/* records to display */
E 16
D 23
static char	*file = "/usr/adm/wtmp";	/* wtmp file */
E 23
I 23
static char	*file = _PATH_WTMP;		/* wtmp file */
E 23
E 15
E 12

I 27
void	 addarg __P((int, char *));
TTY	*addtty __P((char *));
void	 hostconv __P((char *));
void	 onintr __P((int));
char	*ttyconv __P((char *));
int	 want __P((struct utmp *, int));
void	 wtmp __P((void));

int
E 27
D 12
char	*ctime(), *strspl();
int	onintr();

main(ac, av)
	char **av;
E 12
I 12
D 15
main(argc,argv)
int	argc;
char	**argv;
E 15
I 15
main(argc, argv)
D 22
	int	argc;
	char	**argv;
E 22
I 22
	int argc;
D 28
	char **argv;
E 28
I 28
	char *argv[];
E 28
E 22
E 15
E 12
{
D 12
	register int i, k;
	int bl, wtmp;
	char *ct;
	register struct utmp *bp;
	long otime;
	struct stat stb;
	int print;
I 3
	char * crmsg = (char *)0;
	long crtime;
I 4
	long outrec = 0;
	long maxrec = 0x7fffffffL;
E 4
E 3
 
	time(&buf[0].ut_time);
	ac--, av++;
D 4
	argc = ac;
E 4
I 4
	nameargs = argc = ac;
E 4
	argv = av;
	for (i = 0; i < argc; i++) {
I 4
D 5
		if (argv[i][0] == '-' && argv[i][1] >= '0' && argv[i][1] <= '9')
		{
E 5
I 5
		if (argv[i][0] == '-' &&
		    argv[i][1] >= '0' && argv[i][1] <= '9') {
E 5
			maxrec = atoi(argv[i]+1);
			nameargs--;
E 12
I 12
D 15
	register struct utmp	*bp;		/* current structure */
	register TTYS	*T;			/* table entry */
	register long	maxrec = -1;		/* records to display */
	register int	indx;			/* array offsets */
	struct stat	stb;			/* stat of file for size */
	long	delta,				/* time difference */
		atol(), lseek(), time();
	int	bl,				/* reads to do */
		bytes,				/* bytes read */
		wtmp,				/* wtmp file descriptor */
		onintr();
	char	*ct,				/* ctime return */
		*crmsg,				/* crash message */
		*file,				/* user specified file */
		*asctime(), *ctime(), *strspl();
E 15
I 15
D 22
	extern int	optind;
	extern char	*optarg;
	int	ch;
D 16
	char	*malloc();
E 16
	long	atol();
I 16
	char	*ttyconv();
E 22
I 22
	extern int optind;
	extern char *optarg;
	int ch;
D 27
	long atol();
	char *p, *ttyconv();
E 27
I 27
	char *p;
E 27
E 22
E 16
E 15

I 22
	maxrec = -1;
E 22
D 15
	file = "/usr/adm/wtmp";
	for (--argc,sargs = argv = ++argv,indx = 0;indx < argc;++indx) {
		if (argv[indx][0] == '-' && isdigit(argv[indx][1])) {
			if ((maxrec = atol(argv[indx] + 1)) <= 0) {
				fputs("last: bad line count value.\n",stderr);
				exit(1);
E 15
I 15
	while ((ch = getopt(argc, argv, "0123456789f:h:t:")) != EOF)
D 28
		switch((char)ch) {
E 28
I 28
		switch (ch) {
E 28
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			/*
			 * kludge: last was originally designed to take
			 * a number after a dash.
			 */
D 22
			if (!maxrec)
				maxrec = atol(argv[optind - 1] + 1);
E 22
I 22
			if (maxrec == -1) {
				p = argv[optind - 1];
				if (p[0] == '-' && p[1] == ch && !p[2])
					maxrec = atol(++p);
				else
					maxrec = atol(argv[optind] + 1);
				if (!maxrec)
					exit(0);
			}
E 22
			break;
		case 'f':
			file = optarg;
			break;
		case 'h':
			hostconv(optarg);
			addarg(HOST_TYPE, optarg);
			break;
		case 't':
D 16
		{
			char	*mval, *strcpy();

			/*
			 * kludge -- we assume that all tty's end with
			 * a two character suffix.
			 */
			if (strlen(optarg) == 2) {
				/* either 6 for "ttyxx" or 8 for "console" */
				if (!(mval = malloc((u_int)8))) {
					fputs("last: malloc failure.\n", stderr);
					exit(1);
				}
				if (!strcmp(optarg, "co"))
					(void)strcpy(mval, "console");
				else {
					(void)strcpy(mval, "tty");
					(void)strcpy(mval + 3, optarg);
				}
				addarg(TTY_TYPE, mval);
E 15
			}
D 15
			++sargs;
E 12
			continue;
E 15
I 15
			else
				addarg(TTY_TYPE, optarg);
E 16
I 16
			addarg(TTY_TYPE, ttyconv(optarg));
E 16
			break;
E 15
D 16
		}
E 16
E 4
D 12
		if (strlen(argv[i])>2)
E 12
I 12
D 15
		if (!strncmp(argv[indx],"-f",2)) {
			if (argv[indx][2]) {
				file = argv[indx] + 2;
				++sargs;
			}
			else if (++indx == argc) {
				fputs("last: option requires an argument -- f\n",stderr);
				exit(1);
			}
			else {
				file = argv[indx];
				sargs += 2;
			}
E 12
			continue;
E 15
I 15
		case '?':
		default:
D 28
			fputs("usage: last [-#] [-f file] [-t tty] [-h hostname] [user ...]\n", stderr);
E 28
I 28
			(void)fprintf(stderr,
	"usage: last [-#] [-f file] [-t tty] [-h hostname] [user ...]\n");
E 28
			exit(1);
E 15
D 12
		if (!strcmp(argv[i], "~"))
E 12
I 12
		}
D 15
		if (strlen(argv[indx]) > 2)
E 12
			continue;
I 7
D 12
		if (!strcmp(argv[i], "ftp"))
E 12
I 12
		if (!strcmp(argv[indx],"~"))
E 12
			continue;
I 10
D 12
		if (!strcmp(argv[i], "uucp"))
E 12
I 12
		if (getpwnam(argv[indx]))
E 12
			continue;
E 10
E 7
D 12
		if (getpwnam(argv[i]))
			continue;
		argv[i] = strspl("tty", argv[i]);
E 12
I 12
		argv[indx] = strspl(argv[indx]);
E 12
	}
E 15
I 15
D 16
	for (argv += optind; *argv; ++argv)
E 16
I 16
D 24
	for (argv += optind; *argv; ++argv) {
E 24
I 24

	if (argc) {
		setlinebuf(stdout);
		for (argv += optind; *argv; ++argv) {
E 24
#define	COMPATIBILITY
#ifdef	COMPATIBILITY
D 24
		/* code to allow "last p5" to work */
		addarg(TTY_TYPE, ttyconv(*argv));
E 24
I 24
			/* code to allow "last p5" to work */
			addarg(TTY_TYPE, ttyconv(*argv));
E 24
#endif
E 16
D 24
		addarg(USER_TYPE, *argv);
E 24
I 24
			addarg(USER_TYPE, *argv);
		}
E 24
I 16
	}
E 16
	wtmp();
	exit(0);
}
E 15
D 12
	wtmp = open("/usr/adm/wtmp", 0);
	if (wtmp < 0) {
		perror("/usr/adm/wtmp");
E 12
I 12

D 15
	if ((wtmp = open(file,O_RDONLY,0)) < 0 || fstat(wtmp,&stb) == -1) {
E 15
I 15
/*
 * wtmp --
 *	read through the wtmp file
 */
I 27
void
E 27
D 26
static
E 26
wtmp()
{
D 30
	register struct utmp	*bp;		/* current structure */
D 16
	register TTYS	*T;			/* table entry */
E 16
I 16
	register TTY	*T;			/* tty list entry */
E 30
I 30
	struct utmp	*bp;			/* current structure */
	TTY	*T;				/* tty list entry */
E 30
E 16
	struct stat	stb;			/* stat of file for size */
D 27
	long	bl, delta,			/* time difference */
		lseek(), time();
E 27
I 27
	long	bl, delta;			/* time difference */
E 27
D 26
	int	bytes, wfd,
		onintr();
E 26
I 26
	int	bytes, wfd;
E 26
D 27
	char	*ct, *crmsg,
		*asctime(), *ctime(), *strcpy();
I 16
	TTY	*addtty();
I 26
	void	onintr();
E 27
I 27
	char	*ct, *crmsg;
E 27
E 26
E 16

D 28
	if ((wfd = open(file, O_RDONLY, 0)) < 0 || fstat(wfd, &stb) == -1) {
E 15
		perror(file);
E 12
		exit(1);
	}
E 28
I 28
	if ((wfd = open(file, O_RDONLY, 0)) < 0 || fstat(wfd, &stb) == -1)
		err(1, "%s", file);
E 28
D 12
	fstat(wtmp, &stb);
	bl = (stb.st_size + sizeof (buf)-1) / sizeof (buf);
	if (signal(SIGINT, SIG_IGN) != SIG_IGN) {
		signal(SIGINT, onintr);
		signal(SIGQUIT, onintr);
	}
	for (bl--; bl >= 0; bl--) {
		lseek(wtmp, bl * sizeof (buf), 0);
		bp = &buf[read(wtmp, buf, sizeof (buf)) / sizeof(buf[0]) - 1];
		for ( ; bp >= buf; bp--) {
			print = want(bp);
			if (print) {
				ct = ctime(&bp->ut_time);
D 5
				printf("%-*.*s  %-*.*s  %10.10s %5.5s ",
E 5
I 5
D 8
				printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s",
E 8
I 8
				printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s ",
E 8
E 5
				    NMAX, NMAX, bp->ut_name,
D 5
				    LMAX, LMAX, bp->ut_line, ct, 11+ct);
E 5
I 5
				    LMAX, LMAX, bp->ut_line,
				    HMAX, HMAX, bp->ut_host,
				    ct, 11+ct);
E 12
I 12
	bl = (stb.st_size + sizeof(buf) - 1) / sizeof(buf);

D 15
	time(&buf[0].ut_time);
	signal(SIGINT,onintr);
	signal(SIGQUIT,onintr);
E 15
I 15
	(void)time(&buf[0].ut_time);
	(void)signal(SIGINT, onintr);
	(void)signal(SIGQUIT, onintr);
E 15

D 16
	tab[MAXTTYS].logout = -1;		/* end flag value */
E 16
	while (--bl >= 0) {
D 15
		if (lseek(wtmp,(long)(bl * sizeof(buf)),L_SET) == -1 || (bytes = read(wtmp,(char *)buf,sizeof(buf))) == -1) {
			perror(file);
E 15
I 15
D 28
		if (lseek(wfd, (long)(bl * sizeof(buf)), L_SET) == -1 ||
		    (bytes = read(wfd, (char *)buf, sizeof(buf))) == -1) {
			fprintf(stderr, "last: %s: ", file);
			perror((char *)NULL);
E 15
			exit(1);
		}
E 28
I 28
		if (lseek(wfd, (off_t)(bl * sizeof(buf)), L_SET) == -1 ||
		    (bytes = read(wfd, buf, sizeof(buf))) == -1)
			err(1, "%s", file);
E 28
D 15
		for (bp = &buf[bytes / sizeof(buf[0]) - 1];bp >= buf;--bp) {
			if (lineq(bp->ut_line,"~")) {
				/*
				 * if the name is empty and the terminal
				 * line is '~', it's a shutdown of some
				 * sort; see utmp(5) for more info.
				 */
				for (T = tab;T->logout != -1;++T)
E 15
I 15
		for (bp = &buf[bytes / sizeof(buf[0]) - 1]; bp >= buf; --bp) {
			/*
			 * if the terminal line is '~', the machine stopped.
			 * see utmp(5) for more info.
			 */
D 20
			if (!strncmp(bp->ut_line, "~", LMAX)) {
E 20
I 20
			if (bp->ut_line[0] == '~' && !bp->ut_line[1]) {
E 20
D 16
				for (T = tab; T->logout != -1; ++T)
E 16
I 16
				/* everybody just logged out */
				for (T = ttylist; T; T = T->next)
E 16
E 15
					T->logout = -bp->ut_time;
D 15
				crmsg = nameq(bp->ut_name,"shutdown") ? "down " : "crash";
E 15
I 15
D 16
				crmsg = strncmp(bp->ut_name, "shutdown", NMAX)
				     ? "crash" : "down ";
E 16
I 16
				currentout = -bp->ut_time;
D 20
				crmsg = strncmp(bp->ut_name, "shutdown", NMAX) ? "crash" : "down ";
E 16
E 15
				if (!bp->ut_name[0])
D 15
					strcpy(bp->ut_name,"reboot");
				if (want(bp,NO)) {
E 15
I 15
					(void)strcpy(bp->ut_name, "reboot");
E 20
I 20
D 21
				crmsg = strncmp(bp->ut_name, "shutdown", NMAX) ? "crash" : "shutdown";
E 21
I 21
				crmsg = strncmp(bp->ut_name, "shutdown",
				    UT_NAMESIZE) ? "crash" : "shutdown";
E 21
				if (want(bp, NO)) {
					ct = ctime(&bp->ut_time);
D 21
					printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s \n", NMAX, NMAX, bp->ut_name, LMAX, LMAX, bp->ut_line, HMAX, HMAX, bp->ut_host, ct, ct + 11);
E 21
I 21
D 28
					printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s \n", UT_NAMESIZE, UT_NAMESIZE, bp->ut_name, UT_LINESIZE, UT_LINESIZE, bp->ut_line, UT_HOSTSIZE, UT_HOSTSIZE, bp->ut_host, ct, ct + 11);
E 28
I 28
				printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s \n",
					    UT_NAMESIZE, UT_NAMESIZE,
					    bp->ut_name, UT_LINESIZE,
					    UT_LINESIZE, bp->ut_line,
					    UT_HOSTSIZE, UT_HOSTSIZE,
					    bp->ut_host, ct, ct + 11);
E 28
E 21
D 22
					if (maxrec && !--maxrec)
E 22
I 22
					if (maxrec != -1 && !--maxrec)
E 22
						return;
				}
				continue;
			}
			/*
			 * if the line is '{' or '|', date got set; see
			 * utmp(5) for more info.
			 */
			if ((bp->ut_line[0] == '{' || bp->ut_line[0] == '|')
			    && !bp->ut_line[1]) {
E 20
				if (want(bp, NO)) {
E 15
					ct = ctime(&bp->ut_time);
D 15
					printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s \n",NMAX,NMAX,bp->ut_name,LMAX,LMAX,bp->ut_line,HMAX,HMAX,bp->ut_host,ct,ct + 11);
					if (maxrec != -1 && !--maxrec)
						exit(0);
E 15
I 15
D 21
					printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s \n", NMAX, NMAX, bp->ut_name, LMAX, LMAX, bp->ut_line, HMAX, HMAX, bp->ut_host, ct, ct + 11);
E 21
I 21
D 28
					printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s \n", UT_NAMESIZE, UT_NAMESIZE, bp->ut_name, UT_LINESIZE, UT_LINESIZE, bp->ut_line, UT_HOSTSIZE, UT_HOSTSIZE, bp->ut_host, ct, ct + 11);
E 28
I 28
				printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s \n",
				    UT_NAMESIZE, UT_NAMESIZE, bp->ut_name,
				    UT_LINESIZE, UT_LINESIZE, bp->ut_line,
				    UT_HOSTSIZE, UT_HOSTSIZE, bp->ut_host,
				    ct, ct + 11);
E 28
E 21
					if (maxrec && !--maxrec)
						return;
E 15
				}
				continue;
E 12
E 5
			}
D 12
			for (i = 0; i < MAXTTYS; i++) {
				if (ttnames[i][0] == 0) {
					strncpy(ttnames[i], bp->ut_line,
					    sizeof(bp->ut_line));
D 2
					otime = 0;
E 2
I 2
					otime = logouts[i];
E 2
					logouts[i] = bp->ut_time;
E 12
I 12
D 15
			for (T = tab;;) {
				if (T->logout <= 0) {
					bcopy(bp->ut_line,T->tty,LMAX);
E 15
I 15
D 16
			for (T = tab;;) {		/* find assoc. tty */
				if (T->logout <= 0) {	/* unused entry */
					bcopy(bp->ut_line, T->tty, LMAX);
E 16
I 16
			/* find associated tty */
			for (T = ttylist;; T = T->next) {
				if (!T) {
					/* add new one */
					T = addtty(bp->ut_line);
E 16
E 15
E 12
					break;
				}
D 12
				if (lineq(ttnames[i], bp->ut_line)) {
					otime = logouts[i];
					logouts[i] = bp->ut_time;
E 12
I 12
D 15
				if (lineq(T->tty,bp->ut_line))
E 15
I 15
D 21
				if (!strncmp(T->tty, bp->ut_line, LMAX))
E 21
I 21
				if (!strncmp(T->tty, bp->ut_line, UT_LINESIZE))
E 21
E 15
E 12
					break;
I 12
D 16
				if ((++T)->logout == -1) {
D 15
					fputs("last: too many terminals.\n",stderr);
E 15
I 15
					fputs("last: too many terminals.\n", stderr);
E 15
					exit(1);
E 12
				}
E 16
			}
D 12
			if (print) {
D 8
				if (otime == 0)
E 8
I 8
				if (lineq(bp->ut_line, "~"))
					printf("\n");
				else if (otime == 0)
E 8
					printf("  still logged in\n");
E 12
I 12
D 15
			if (bp->ut_name[0] && want(bp,YES)) {
E 15
I 15
			if (bp->ut_name[0] && want(bp, YES)) {
E 15
				ct = ctime(&bp->ut_time);
D 15
				printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s ",NMAX,NMAX,bp->ut_name,LMAX,LMAX,bp->ut_line,HMAX,HMAX,bp->ut_host,ct,ct + 11);
E 15
I 15
D 21
				printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s ", NMAX, NMAX, bp->ut_name, LMAX, LMAX, bp->ut_line, HMAX, HMAX, bp->ut_host, ct, ct + 11);
E 21
I 21
D 28
				printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s ", UT_NAMESIZE, UT_NAMESIZE, bp->ut_name, UT_LINESIZE, UT_LINESIZE, bp->ut_line, UT_HOSTSIZE, UT_HOSTSIZE, bp->ut_host, ct, ct + 11);
E 28
I 28
				printf("%-*.*s  %-*.*s %-*.*s %10.10s %5.5s ",
				UT_NAMESIZE, UT_NAMESIZE, bp->ut_name,
				UT_LINESIZE, UT_LINESIZE, bp->ut_line,
				UT_HOSTSIZE, UT_HOSTSIZE, bp->ut_host,
				ct, ct + 11);
E 28
E 21
E 15
				if (!T->logout)
					puts("  still logged in");
E 12
				else {
D 12
					long delta;
					if (otime < 0) {
						otime = -otime;
D 3
						printf("- crash");
E 3
I 3
						printf("- %s", crmsg);
E 3
					} else
						printf("- %5.5s",
						    ctime(&otime)+11);
					delta = otime - bp->ut_time;
E 12
I 12
					if (T->logout < 0) {
						T->logout = -T->logout;
D 15
						printf("- %s",crmsg);
E 15
I 15
						printf("- %s", crmsg);
E 15
					}
					else
D 15
						printf("- %5.5s",ctime(&T->logout)+11);
E 15
I 15
D 28
						printf("- %5.5s", ctime(&T->logout)+11);
E 28
I 28
						printf("- %5.5s",
						    ctime(&T->logout)+11);
E 28
E 15
					delta = T->logout - bp->ut_time;
E 12
D 28
					if (delta < SECDAY)
D 12
					    printf("  (%5.5s)\n",
						asctime(gmtime(&delta))+11);
E 12
I 12
D 15
						printf("  (%5.5s)\n",asctime(gmtime(&delta))+11);
E 15
I 15
						printf("  (%5.5s)\n", asctime(gmtime(&delta))+11);
E 28
I 28
					if (delta < SECSPERDAY)
						printf("  (%5.5s)\n",
						    asctime(gmtime(&delta))+11);
E 28
E 15
E 12
					else
D 12
					    printf(" (%ld+%5.5s)\n",
						delta / SECDAY,
						asctime(gmtime(&delta))+11);
E 12
I 12
D 15
						printf(" (%ld+%5.5s)\n",delta / SECDAY,asctime(gmtime(&delta))+11);
E 15
I 15
D 28
						printf(" (%ld+%5.5s)\n", delta / SECDAY, asctime(gmtime(&delta))+11);
E 28
I 28
						printf(" (%ld+%5.5s)\n",
						    delta / SECSPERDAY,
						    asctime(gmtime(&delta))+11);
E 28
E 15
E 12
				}
D 12
				fflush(stdout);
I 4
				if (++outrec >= maxrec)
E 12
I 12
				if (maxrec != -1 && !--maxrec)
E 12
D 15
					exit(0);
E 15
I 15
					return;
E 15
E 4
			}
D 2
			if (lineq(bp->ut_line, "~") ||
			    lineq(bp->ut_line, "tty~"))
				for (i = 0; *ttnames[i] && i < MAXTTYS; i++)
E 2
I 2
D 3
			if (!strcmp(bp->ut_name, "reboot"))
E 3
I 3
D 12
			if (lineq(bp->ut_line, "~")) {
E 3
				for (i = 0; i < MAXTTYS; i++)
E 2
					logouts[i] = -bp->ut_time;
I 3
				if (nameq(bp->ut_name, "shutdown"))
					crmsg = "down ";
				else
					crmsg = "crash";
			}
E 12
I 12
			T->logout = bp->ut_time;
E 12
E 3
		}
	}
	ct = ctime(&buf[0].ut_time);
D 12
	printf("\nwtmp begins %10.10s %5.5s \n", ct, ct + 11);
E 12
I 12
D 15
	printf("\nwtmp begins %10.10s %5.5s \n",ct,ct + 11);
E 12
	exit(0);
E 15
I 15
	printf("\nwtmp begins %10.10s %5.5s \n", ct, ct + 11);
E 15
}

D 15
onintr(signo)
D 12
	int signo;
E 12
I 12
int	signo;
E 15
I 15
/*
 * want --
 *	see if want this entry
 */
I 27
int
E 27
D 26
static
E 26
want(bp, check)
D 22
	register struct utmp	*bp;
	int	check;
E 22
I 22
D 30
	register struct utmp *bp;
E 30
I 30
	struct utmp *bp;
E 30
	int check;
E 22
E 15
E 12
{
D 12
	char *ct;
E 12
I 12
D 15
	char	*ct,
		*ctime();
E 15
I 15
D 22
	register ARG	*step;
E 22
I 22
D 30
	register ARG *step;
E 30
I 30
	ARG *step;
E 30
E 22
E 15
E 12

D 12
	if (signo == SIGQUIT)
		signal(SIGQUIT, onintr);
E 12
D 15
	ct = ctime(&buf[0].ut_time);
D 12
	printf("\ninterrupted %10.10s %5.5s \n", ct, ct + 11);
I 11
	fflush(stdout);
E 12
I 12
	printf("\ninterrupted %10.10s %5.5s \n",ct,ct + 11);
	fflush(stdout);			/* fix required for rsh */
E 12
E 11
	if (signo == SIGINT)
		exit(1);
}

D 12
want(bp)
	struct utmp *bp;
E 12
I 12
want(bp,check)
register struct utmp	*bp;
int	check;
E 12
{
D 12
	register char **av;
	register int ac;
E 12
I 12
D 13
	register char	**indx;
E 13
I 13
	register char	**indx,
			*C;
	register int	cnt;
E 13
E 12

E 15
D 3
	if (bp->ut_line[0] == '~')
E 3
I 3
D 12
	if (bp->ut_line[0] == '~' && bp->ut_name[0] == '\0')
E 3
		strcpy(bp->ut_name, "reboot");		/* bandaid */
I 7
	if (strncmp(bp->ut_line, "ftp", 3) == 0)
		bp->ut_line[3] = '\0';
I 10
	if (strncmp(bp->ut_line, "uucp", 4) == 0)
		bp->ut_line[4] = '\0';
E 10
E 7
	if (bp->ut_name[0] == 0)
		return (0);
D 4
	if (argc == 0)
E 4
I 4
	if (nameargs == 0)
E 4
		return (1);
	av = argv;
D 4
	for (ac = 0; ac < argc; ac++) {
E 4
I 4
	for (ac = 0; ac < argc; ac++, av++) {
		if (av[0][0] == '-')
			continue;
E 4
		if (nameq(*av, bp->ut_name) || lineq(*av, bp->ut_line))
			return (1);
E 12
I 12
D 13
	if (check) {
E 13
I 13
	if (check)
E 13
		/*
D 16
		 * when uucp and ftp log in over a network, the entry in the
		 * utmp file is the name plus their process id.  See etc/ftpd.c
		 * and usr.bin/uucp/uucpd.c for more information.
E 16
I 16
		 * when uucp and ftp log in over a network, the entry in
		 * the utmp file is the name plus their process id.  See
		 * etc/ftpd.c and usr.bin/uucp/uucpd.c for more information.
E 16
		 */
D 15
		if (!strncmp(bp->ut_line,"ftp",3))
E 15
I 15
D 16
		if (!strncmp(bp->ut_line, "ftp", 3))
E 16
I 16
		if (!strncmp(bp->ut_line, "ftp", sizeof("ftp") - 1))
E 16
E 15
			bp->ut_line[3] = '\0';
D 15
		else if (!strncmp(bp->ut_line,"uucp",4))
E 15
I 15
D 16
		else if (!strncmp(bp->ut_line, "uucp", 4))
E 16
I 16
		else if (!strncmp(bp->ut_line, "uucp", sizeof("uucp") - 1))
E 16
E 15
			bp->ut_line[4] = '\0';
E 12
D 4
		av++;
E 4
D 13
	}
E 13
D 12
	return (0);
E 12
I 12
D 15
	if (!*sargs)
E 15
I 15
D 16
	if (!head)
E 16
I 16
	if (!arglist)
E 16
E 15
D 30
		return(YES);
E 30
I 30
		return (YES);
E 30
I 13
D 15
	/*
	 * match hostname only, case independent;
	 * leave internet numbers alone
	 */
	if (!isdigit(*bp->ut_host)) {
		for (C = bp->ut_host,cnt = HMAX;*C != '.' && cnt--;++C)
			if (isupper(*C))
				*C = tolower(*C);
		if (*C == '.')
			*C = '\0';
		else
			C = NULL;
E 15
I 15

D 16
	for (step = head; step; step = step->next)
E 16
I 16
	for (step = arglist; step; step = step->next)
E 16
		switch(step->type) {
		case HOST_TYPE:
D 21
			if (!strncasecmp(step->name, bp->ut_host, HMAX))
E 21
I 21
			if (!strncasecmp(step->name, bp->ut_host, UT_HOSTSIZE))
E 21
D 30
				return(YES);
E 30
I 30
				return (YES);
E 30
			break;
		case TTY_TYPE:
D 21
			if (!strncmp(step->name, bp->ut_line, LMAX))
E 21
I 21
			if (!strncmp(step->name, bp->ut_line, UT_LINESIZE))
E 21
D 30
				return(YES);
E 30
I 30
				return (YES);
E 30
			break;
		case USER_TYPE:
D 21
			if (!strncmp(step->name, bp->ut_name, NMAX))
E 21
I 21
			if (!strncmp(step->name, bp->ut_name, UT_NAMESIZE))
E 21
D 30
				return(YES);
E 30
I 30
				return (YES);
E 30
			break;
E 15
	}
I 14
D 15
	else
		C = NULL;
E 14
E 13
	for (indx = sargs;*indx;++indx)
D 13
		if (nameq(*indx,bp->ut_name) || lineq(*indx,bp->ut_line))
E 13
I 13
		if (nameq(*indx,bp->ut_name) || lineq(*indx,bp->ut_line) || hosteq(*indx,bp->ut_host)) {
			if (C)
				*C = '.';
E 13
			return(YES);
I 13
		}
E 15
E 13
D 30
	return(NO);
E 30
I 30
	return (NO);
E 30
E 12
}

D 15
char *
D 12
strspl(left, right)
	char *left, *right;
E 12
I 12
strspl(str)
char	*str;
E 15
I 15
/*
 * addarg --
 *	add an entry to a linked list of arguments
 */
I 27
void
E 27
D 26
static
E 26
addarg(type, arg)
D 22
	int	type;
	char	*arg;
E 22
I 22
	int type;
	char *arg;
E 22
E 15
E 12
{
D 12
	char *res = (char *)malloc(strlen(left)+strlen(right)+1);
E 12
I 12
D 15
	register char	*res;
E 15
I 15
D 22
	register ARG	*cur;
E 15
	char	*malloc();
E 22
I 22
D 30
	register ARG *cur;
E 30
I 30
	ARG *cur;
E 30
D 27
	char *malloc();
E 27
E 22
E 12

D 12
	strcpy(res, left);
	strcat(res, right);
	return (res);
E 12
I 12
D 15
	if (!(res = malloc((u_int)(4 + strlen(str))))) {
		fputs("last: malloc failure.\n",stderr);
E 15
I 15
D 30
	if (!(cur = (ARG *)malloc((u_int)sizeof(ARG)))) {
		fputs("last: malloc failure.\n", stderr);
E 15
		exit(1);
	}
E 30
I 30
	if (!(cur = (ARG *)malloc((u_int)sizeof(ARG))))
		err(1, "malloc failure");
E 30
D 15
	strcpy(res,"tty");
	strcpy(res + 3,str);
	return(res);
E 15
I 15
D 16
	cur->next = head;
E 16
I 16
	cur->next = arglist;
E 16
	cur->type = type;
	cur->name = arg;
D 16
	head = cur;
E 16
I 16
	arglist = cur;
E 16
}

/*
I 16
 * addtty --
 *	add an entry to a linked list of ttys
 */
D 26
static TTY *
E 26
I 26
TTY *
E 26
addtty(ttyname)
D 22
	char	*ttyname;
E 22
I 22
	char *ttyname;
E 22
{
D 22
	register TTY	*cur;
	char	*malloc();
E 22
I 22
D 30
	register TTY *cur;
E 30
I 30
	TTY *cur;
E 30
D 27
	char *malloc();
E 27
E 22

D 30
	if (!(cur = (TTY *)malloc((u_int)sizeof(TTY)))) {
		fputs("last: malloc failure.\n", stderr);
		exit(1);
	}
E 30
I 30
	if (!(cur = (TTY *)malloc((u_int)sizeof(TTY))))
		err(1, "malloc failure");
E 30
	cur->next = ttylist;
	cur->logout = currentout;
D 21
	bcopy(ttyname, cur->tty, LMAX);
E 21
I 21
D 30
	bcopy(ttyname, cur->tty, UT_LINESIZE);
E 21
	return(ttylist = cur);
E 30
I 30
	memmove(cur->tty, ttyname, UT_LINESIZE);
	return (ttylist = cur);
E 30
}

/*
E 16
 * hostconv --
 *	convert the hostname to search pattern; if the supplied host name
 *	has a domain attached that is the same as the current domain, rip
 *	off the domain suffix since that's what login(1) does.
 */
I 27
void
E 27
D 26
static
E 26
hostconv(arg)
D 22
	char	*arg;
E 22
I 22
	char *arg;
E 22
{
D 22
	static int	first = 1;
	static char	*hostdot,
			name[MAXHOSTNAMELEN];
	char	*argdot, *index();
E 22
I 22
	static int first = 1;
	static char *hostdot, name[MAXHOSTNAMELEN];
D 28
	char *argdot, *index();
E 28
I 28
	char *argdot;
E 28
E 22

D 30
	if (!(argdot = index(arg, '.')))
E 30
I 30
	if (!(argdot = strchr(arg, '.')))
E 30
		return;
	if (first) {
		first = 0;
D 28
		if (gethostname(name, sizeof(name))) {
			perror("last: gethostname");
			exit(1);
		}
E 28
I 28
		if (gethostname(name, sizeof(name)))
			err(1, "gethostname");
E 28
D 30
		hostdot = index(name, '.');
E 30
I 30
		hostdot = strchr(name, '.');
E 30
	}
	if (hostdot && !strcasecmp(hostdot, argdot))
		*argdot = '\0';
I 16
}

/*
 * ttyconv --
 *	convert tty to correct name.
 */
D 26
static char *
E 26
I 26
char *
E 26
ttyconv(arg)
D 22
	char	*arg;
E 22
I 22
	char *arg;
E 22
{
D 22
	char	*mval,
		*malloc(), *strcpy();
E 22
I 22
D 27
	char *mval, *malloc(), *strcpy();
E 27
I 27
	char *mval;
E 27
E 22

	/*
	 * kludge -- we assume that all tty's end with
	 * a two character suffix.
	 */
	if (strlen(arg) == 2) {
		/* either 6 for "ttyxx" or 8 for "console" */
D 30
		if (!(mval = malloc((u_int)8))) {
			fputs("last: malloc failure.\n", stderr);
			exit(1);
		}
E 30
I 30
		if (!(mval = malloc((u_int)8)))
			err(1, "malloc failure");
E 30
D 18
		if (!strcmp(optarg, "co"))
E 18
I 18
		if (!strcmp(arg, "co"))
E 18
			(void)strcpy(mval, "console");
		else {
			(void)strcpy(mval, "tty");
			(void)strcpy(mval + 3, arg);
		}
D 30
		return(mval);
E 30
I 30
		return (mval);
E 30
	}
D 23
	if (!strncmp(arg, "/dev/", sizeof("/dev/") - 1))
E 23
I 23
	if (!strncmp(arg, _PATH_DEV, sizeof(_PATH_DEV) - 1))
E 23
D 30
		return(arg + 5);
	return(arg);
E 30
I 30
		return (arg + 5);
	return (arg);
E 30
E 16
}

/*
 * onintr --
 *	on interrupt, we inform the user how far we've gotten
 */
D 26
static
E 26
I 26
void
E 26
onintr(signo)
D 22
	int	signo;
E 22
I 22
	int signo;
E 22
{
D 22
	char	*ct, *ctime();
E 22
I 22
D 28
	char *ct, *ctime();
E 28
I 28
	char *ct;
E 28
E 22

	ct = ctime(&buf[0].ut_time);
	printf("\ninterrupted %10.10s %5.5s \n", ct, ct + 11);
	if (signo == SIGINT)
		exit(1);
	(void)fflush(stdout);			/* fix required for rsh */
E 15
E 12
}
E 1
