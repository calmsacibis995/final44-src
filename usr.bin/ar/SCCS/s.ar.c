h30539
s 00002/00002/00209
d D 8.3 94/04/02 10:03:29 pendry 23 22
c add 1994 copyright
e
s 00021/00022/00190
d D 8.2 94/04/01 04:59:43 pendry 22 21
c prettyness police
e
s 00005/00005/00207
d D 8.1 93/06/06 14:19:03 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00026/00186
d D 5.11 91/03/21 12:16:00 bostic 20 19
c rename -s option to -T (Sys V. compatibility)
e
s 00002/00003/00210
d D 5.10 91/03/12 09:54:13 bostic 19 18
c exit status cleanup
e
s 00006/00001/00207
d D 5.9 91/03/11 21:15:40 bostic 18 17
c add externals, minor cleanups
e
s 00003/00003/00205
d D 5.8 91/03/11 14:31:15 bostic 17 16
c change so that the command line file name is used for error/info messages
e
s 00028/00025/00180
d D 5.7 91/03/10 16:26:04 bostic 16 15
c add -s option which inserts/matches truncated member names
e
s 00166/00741/00039
d D 5.6 91/01/17 18:22:16 bostic 15 14
c new version
e
s 00003/00003/00777
d D 5.5 90/06/24 15:02:01 bostic 14 13
c `tmpnam' conflicts with ANSI function
e
s 00004/00004/00776
d D 5.4 89/05/08 13:00:23 bostic 13 12
c file system reorg and pathnames.h
e
s 00001/00001/00779
d D 5.3 87/10/22 09:48:10 bostic 12 11
c ANSI C; sprintf now returns an int.
e
s 00004/00004/00776
d D 5.2 85/04/23 14:40:45 dist 11 10
c fix copyright
e
s 00014/00002/00766
d D 5.1 85/04/23 14:38:50 dist 10 9
c add copyright
e
s 00002/00002/00766
d D 4.7 85/01/22 14:33:00 ralph 9 8
c fix sign-extend bug for large uid's.
e
s 00007/00008/00761
d D 4.6 84/02/17 16:48:45 ralph 8 7
c use maximum block size instead of BUFSIZ.
e
s 00020/00001/00749
d D 4.5 83/09/25 12:54:31 sam 7 6
c partial solution to long file name truncation problem; 
c from lepreau@utah-cs
e
s 00008/00004/00742
d D 4.4 83/06/10 23:13:07 sam 6 5
c modernize to new time and utimes stuff
e
s 00005/00004/00741
d D 4.3 83/05/23 18:39:01 sam 5 4
c clean crud
e
s 00008/00002/00737
d D 4.2 83/02/28 13:59:03 nicklin 4 3
c 
e
s 00000/00000/00739
d D 4.1 80/10/01 16:37:47 bill 3 2
c Define 4.1
e
s 00001/00001/00738
d D 3.2 80/08/17 01:54:12 bill 2 1
c newar.h->ar.h
e
s 00739/00000/00000
d D 3.1 80/08/15 01:55:03 bill 1 0
c date and time created 80/08/15 01:55:03 by bill
e
u
U
t
T
I 10
D 15
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
/*-
D 21
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 21
I 21
D 23
 * Copyright (c) 1990, 1993
E 23
I 23
 * Copyright (c) 1990, 1993, 1994
E 23
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
 * This code is derived from software contributed to Berkeley by
 * Hugh Smith at The University of Guelph.
 *
 * %sccs.include.redist.c%
E 15
 */

E 10
I 5
#ifndef lint
E 5
I 1
D 7
static	char sccsid[] = "%Z%%M% %I% %G%";
E 7
I 7
D 10
static	char sccsid[] = "%W% (Berkeley) %G%";
E 7
I 5
#endif
E 10
I 10
D 11
char copyright[] =
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
E 11
I 11
D 15
static char sccsid[] = "%W% (Berkeley) %G%";
E 11
#endif not lint

#ifndef lint
E 15
D 11
static char sccsid[] = "%W% (Berkeley) %G%";
E 11
I 11
D 21
char copyright[] =
D 15
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 15
I 15
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
E 15
 All rights reserved.\n";
E 21
I 21
static char copyright[] =
D 23
"%Z% Copyright (c) 1990, 1993\n\
E 23
I 23
"%Z% Copyright (c) 1990, 1993, 1994\n\
E 23
	The Regents of the University of California.  All rights reserved.\n";
E 21
E 11
D 15
#endif not lint
E 15
I 15
#endif /* not lint */
E 15
E 10
I 6

E 6
E 5
D 15
/*
 * ar - portable (ascii) format version
 */
E 15
I 15
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 15
D 6
#include <stdio.h>
E 6
D 8
#include <sys/types.h>
E 8
I 8
#include <sys/param.h>
E 8
D 15
#include <sys/stat.h>
I 6
#include <sys/time.h>
E 15
I 15
D 22
#include <sys/errno.h>
E 22
I 22

#include <ar.h>
E 22
#include <dirent.h>
I 22
#include <err.h>
#include <paths.h>
E 22
E 15
D 13

E 13
#include <stdio.h>
E 6
D 2
#include <newar.h>
E 2
I 2
D 22
#include <ar.h>
I 18
#include <string.h>
E 22
#include <stdlib.h>
E 18
I 13
D 15
#include "pathnames.h"
E 15
I 15
D 22
#include <paths.h>
E 22
I 22
#include <string.h>
#include <unistd.h>

E 22
#include "archive.h"
I 18
#include "extern.h"
E 18
E 15
E 13
E 2
D 8
#include <signal.h>
E 8

D 5
typedef	unsigned short ushort;
E 5
D 15
struct	stat	stbuf;
struct	ar_hdr	arbuf;
struct	lar_hdr {
	char	lar_name[16];
	long	lar_date;
D 5
	ushort	lar_uid;
	ushort	lar_gid;
	ushort	lar_mode;
E 5
I 5
	u_short	lar_uid;
	u_short	lar_gid;
	u_short	lar_mode;
E 5
	long	lar_size;
} larbuf;
E 15
I 15
CHDR chdr;
u_int options;
D 17
char *archive, *envtmp, *posname;
E 17
I 17
char *archive, *envtmp, *posarg, *posname;
I 18
D 22
static void badoptions(), usage();
E 22
I 22
static void badoptions __P((char *));
static void usage __P((void));
E 22
E 18
E 17
E 15

D 15
#define	SKIP	1
#define	IODD	2
#define	OODD	4
#define	HEAD	8

char	*man	=	{ "mrxtdpq" };
D 4
char	*opt	=	{ "uvnbail" };
E 4
I 4
char	*opt	=	{ "uvnbailo" };
E 4

int	signum[] = {SIGHUP, SIGINT, SIGQUIT, 0};
int	sigdone();
long	lseek();
int	rcmd();
int	dcmd();
int	xcmd();
int	tcmd();
int	pcmd();
int	mcmd();
int	qcmd();
int	(*comfun)();
char	flg[26];
char	**namv;
int	namc;
char	*arnam;
char	*ponam;
D 13
char	*tmpnam		=	{ "/tmp/vXXXXX" };
char	*tmp1nam	=	{ "/tmp/v1XXXXX" };
char	*tmp2nam	=	{ "/tmp/v2XXXXX" };
E 13
I 13
D 14
char	*tmpnam = _PATH_TMP1;
E 14
I 14
char	*tmp0nam = _PATH_TMP1;
E 14
char	*tmp1nam = _PATH_TMP2;
char	*tmp2nam = _PATH_TMP3;
E 13
char	*tfnam;
char	*tf1nam;
char	*tf2nam;
char	*file;
char	name[16];
int	af;
int	tf;
int	tf1;
int	tf2;
int	qf;
int	bastate;
D 8
char	buf[BUFSIZ];
E 8
I 8
char	buf[MAXBSIZE];
E 8
I 7
int	truncate;			/* ok to truncate argument filenames */
E 7
I 4
D 6
time_t	timep[2];
E 6
E 4

char	*trim();
char	*mktemp();
char	*ctime();

E 15
I 15
/*
 * main --
 *	main basically uses getopt to parse options and calls the appropriate
 *	functions.  Some hacks that let us be backward compatible with 4.3 ar
 *	option parsing and sanity checking.
 */
I 22
int
E 22
E 15
main(argc, argv)
D 15
char *argv[];
E 15
I 15
	int argc;
	char **argv;
E 15
{
D 15
	register i;
	register char *cp;
E 15
I 15
D 22
	extern int optind;
E 22
D 19
	int c, rval;
E 19
I 19
	int c;
E 19
	char *p;
D 22
	int (*fcall)(), append(), contents(), delete(), extract(),
	    move(), print(), replace();
E 22
I 22
	int (*fcall) __P((char **));
E 22
D 18
	char *rname();
E 18
E 15

D 15
	for(i=0; signum[i]; i++)
		if(signal(signum[i], SIG_IGN) != SIG_IGN)
			signal(signum[i], sigdone);
	if(argc < 3)
E 15
I 15
	if (argc < 3)
E 15
		usage();
D 15
	cp = argv[1];
	for(cp = argv[1]; *cp; cp++)
	switch(*cp) {
I 4
	case 'o':
E 4
	case 'l':
	case 'v':
	case 'u':
	case 'n':
	case 'a':
	case 'b':
	case 'c':
	case 'i':
		flg[*cp - 'a']++;
		continue;
E 15

D 15
	case 'r':
		setcom(rcmd);
		continue;

	case 'd':
		setcom(dcmd);
		continue;

	case 'x':
		setcom(xcmd);
		continue;

	case 't':
		setcom(tcmd);
		continue;

	case 'p':
		setcom(pcmd);
		continue;

	case 'm':
		setcom(mcmd);
		continue;

	case 'q':
		setcom(qcmd);
		continue;

	default:
		fprintf(stderr, "ar: bad option `%c'\n", *cp);
		done(1);
	}
	if(flg['l'-'a']) {
D 14
		tmpnam = "vXXXXX";
E 14
I 14
		tmp0nam = "vXXXXX";
E 14
		tmp1nam = "v1XXXXX";
		tmp2nam = "v2XXXXX";
	}
	if(flg['i'-'a'])
		flg['b'-'a']++;
	if(flg['a'-'a'] || flg['b'-'a']) {
		bastate = 1;
		ponam = trim(argv[2]);
		argv++;
		argc--;
		if(argc < 3)
			usage();
	}
	arnam = argv[2];
	namv = argv+3;
	namc = argc-3;
	if(comfun == 0) {
		if(flg['u'-'a'] == 0) {
			fprintf(stderr, "ar: one of [%s] must be specified\n", man);
			done(1);
E 15
I 15
	/*
	 * Historic versions didn't require a '-' in front of the options.
	 * Fix it, if necessary.
	*/
	if (*argv[1] != '-') {
D 22
		if (!(p = malloc((u_int)(strlen(argv[1]) + 2)))) {
			(void)fprintf(stderr, "ar: %s.\n", strerror(errno));
			exit(1);
E 15
		}
E 22
I 22
		if (!(p = malloc((u_int)(strlen(argv[1]) + 2))))
			err(1, NULL);
E 22
D 15
		setcom(rcmd);
E 15
I 15
		*p = '-';
		(void)strcpy(p + 1, argv[1]);
		argv[1] = p;
E 15
	}
D 15
	(*comfun)();
	done(notfound());
}
E 15

D 15
setcom(fun)
int (*fun)();
{

	if(comfun != 0) {
		fprintf(stderr, "ar: only one of [%s] allowed\n", man);
		done(1);
	}
	comfun = fun;
}

rcmd()
{
	register f;

	init();
	getaf();
	while(!getdir()) {
		bamatch();
		if(namc == 0 || match()) {
			f = stats();
			if(f < 0) {
				if(namc)
					fprintf(stderr, "ar: cannot open %s\n", file);
				goto cp;
			}
			if(flg['u'-'a'])
				if(stbuf.st_mtime <= larbuf.lar_date) {
					close(f);
					goto cp;
				}
			mesg('r');
			copyfil(af, -1, IODD+SKIP);
			movefil(f);
			continue;
E 15
I 15
D 16
	while ((c = getopt(argc, argv, "abcdilmopqrtuvx")) != EOF) {
E 16
I 16
D 20
	while ((c = getopt(argc, argv, "abcdilmopqrstuvx")) != EOF) {
E 20
I 20
	while ((c = getopt(argc, argv, "abcdilmopqrTtuvx")) != EOF) {
E 20
E 16
		switch(c) {
		case 'a':
			options |= AR_A;
			break;
		case 'b':
		case 'i':
			options |= AR_B;
			break;
		case 'c':
			options |= AR_C;
			break;
		case 'd':
			options |= AR_D;
			fcall = delete;
			break;
		case 'l':		/* not documented, compatibility only */
			envtmp = ".";
			break;
		case 'm':
			options |= AR_M;
			fcall = move;
			break;
		case 'o':
			options |= AR_O;
			break;
		case 'p':
			options |= AR_P;
			fcall = print;
			break;
		case 'q':
			options |= AR_Q;
			fcall = append;
			break;
		case 'r':
			options |= AR_R;
			fcall = replace;
			break;
I 16
D 20
		case 's':
			options |= AR_S;
E 20
I 20
		case 'T':
			options |= AR_TR;
E 20
			break;
E 16
		case 't':
			options |= AR_T;
			fcall = contents;
			break;
		case 'u':
			options |= AR_U;
			break;
		case 'v':
			options |= AR_V;
			break;
		case 'x':
			options |= AR_X;
			fcall = extract;
			break;
		default:
			usage();
E 15
		}
D 15
	cp:
		mesg('c');
		copyfil(af, tf, IODD+OODD+HEAD);
E 15
	}
D 15
	cleanup();
}
E 15

D 15
dcmd()
{
E 15
I 15
	argv += optind;
	argc -= optind;
E 15

D 15
	init();
	if(getaf())
		noar();
	while(!getdir()) {
		if(match()) {
			mesg('d');
			copyfil(af, -1, IODD+SKIP);
			continue;
		}
		mesg('c');
		copyfil(af, tf, IODD+OODD+HEAD);
E 15
I 15
	/* One of -dmpqrtx required. */
	if (!(options & (AR_D|AR_M|AR_P|AR_Q|AR_R|AR_T|AR_X))) {
D 22
		(void)fprintf(stderr,
		    "ar: one of options -dmpqrtx is required.\n");
E 22
I 22
		warnx("one of options -dmpqrtx is required");
E 22
		usage();
E 15
	}
D 15
	install();
}

xcmd()
{
	register f;
I 6
	struct timeval tv[2];
E 6

	if(getaf())
		noar();
	while(!getdir()) {
		if(namc == 0 || match()) {
			f = creat(file, larbuf.lar_mode & 0777);
			if(f < 0) {
				fprintf(stderr, "ar: %s cannot create\n", file);
				goto sk;
			}
			mesg('x');
			copyfil(af, f, IODD);
			close(f);
I 4
			if (flg['o'-'a']) {
D 6
				timep[0] = timep[1] = (time_t) larbuf.lar_date;
				utime(file, timep);
E 6
I 6
				tv[0].tv_sec = tv[1].tv_sec = larbuf.lar_date;
				tv[0].tv_usec = tv[1].tv_usec = 0;
				utimes(file, tv);
E 6
			}
E 4
			continue;
		}
	sk:
		mesg('c');
		copyfil(af, -1, IODD+SKIP);
		if (namc > 0  &&  !morefil())
			done(0);
E 15
I 15
D 16
	/* Only one of -a and -bi. */
E 16
I 16
	/* Only one of -a and -bi allowed. */
E 16
	if (options & AR_A && options & AR_B) {
D 22
		(void)fprintf(stderr,
		    "ar: only one of -a and -[bi] options allowed.\n");
E 22
I 22
		warnx("only one of -a and -[bi] options allowed");
E 22
		usage();
E 15
	}
D 15
}

pcmd()
{

	if(getaf())
		noar();
	while(!getdir()) {
		if(namc == 0 || match()) {
			if(flg['v'-'a']) {
				printf("\n<%s>\n\n", file);
				fflush(stdout);
			}
			copyfil(af, 1, IODD);
			continue;
E 15
I 15
	/* -ab require a position argument. */
	if (options & (AR_A|AR_B)) {
D 17
		if (!(posname = *argv++)) {
E 17
I 17
		if (!(posarg = *argv++)) {
E 17
D 22
			(void)fprintf(stderr,
			    "ar: no position operand specified.\n");
E 22
I 22
			warnx("no position operand specified");
E 22
			usage();
E 15
		}
D 15
		copyfil(af, -1, IODD+SKIP);
E 15
I 15
D 17
		posname = rname(posname);
E 17
I 17
		posname = rname(posarg);
E 17
E 15
	}
D 15
}
E 15
I 15
D 16
	/* -d only valid with -v. */
	if (options & AR_D && options & ~(AR_D|AR_V))
E 16
I 16
D 20
	/* -d only valid with -sv. */
	if (options & AR_D && options & ~(AR_D|AR_S|AR_V))
E 20
I 20
	/* -d only valid with -Tv. */
	if (options & AR_D && options & ~(AR_D|AR_TR|AR_V))
E 20
E 16
		badoptions("-d");
D 16
	/* -m only valid with -abiv. */
	if (options & AR_M && options & ~(AR_A|AR_B|AR_M|AR_V))
E 16
I 16
D 20
	/* -m only valid with -abisv. */
	if (options & AR_M && options & ~(AR_A|AR_B|AR_M|AR_S|AR_V))
E 20
I 20
	/* -m only valid with -abiTv. */
	if (options & AR_M && options & ~(AR_A|AR_B|AR_M|AR_TR|AR_V))
E 20
E 16
		badoptions("-m");
D 16
	/* -p only valid with -v. */
	if (options & AR_P && options & ~(AR_P|AR_V))
E 16
I 16
D 20
	/* -p only valid with -sv. */
	if (options & AR_P && options & ~(AR_P|AR_S|AR_V))
E 20
I 20
	/* -p only valid with -Tv. */
	if (options & AR_P && options & ~(AR_P|AR_TR|AR_V))
E 20
E 16
		badoptions("-p");
D 16
	/* -q only valid with -cv. */
	if (options & AR_Q && options & ~(AR_C|AR_Q|AR_V))
E 16
I 16
D 20
	/* -q only valid with -csv. */
	if (options & AR_Q && options & ~(AR_C|AR_Q|AR_S|AR_V))
E 20
I 20
	/* -q only valid with -cTv. */
	if (options & AR_Q && options & ~(AR_C|AR_Q|AR_TR|AR_V))
E 20
E 16
		badoptions("-q");
D 16
	/* -r only valid with -abcuv. */
	if (options & AR_R && options & ~(AR_A|AR_B|AR_C|AR_R|AR_U|AR_V))
E 16
I 16
D 20
	/* -r only valid with -abcusv. */
	if (options & AR_R && options & ~(AR_A|AR_B|AR_C|AR_R|AR_U|AR_S|AR_V))
E 20
I 20
	/* -r only valid with -abcuTv. */
	if (options & AR_R && options & ~(AR_A|AR_B|AR_C|AR_R|AR_U|AR_TR|AR_V))
E 20
E 16
		badoptions("-r");
D 16
	/* -t only valid with -v. */
	if (options & AR_T && options & ~(AR_T|AR_V))
E 16
I 16
D 20
	/* -t only valid with -sv. */
	if (options & AR_T && options & ~(AR_T|AR_S|AR_V))
E 20
I 20
	/* -t only valid with -Tv. */
	if (options & AR_T && options & ~(AR_T|AR_TR|AR_V))
E 20
E 16
		badoptions("-t");
D 16
	/* -x only valid with -ouv. */
	if (options & AR_X && options & ~(AR_O|AR_U|AR_V|AR_X))
E 16
I 16
D 20
	/* -x only valid with -ousv. */
	if (options & AR_X && options & ~(AR_O|AR_U|AR_S|AR_V|AR_X))
E 20
I 20
	/* -x only valid with -ouTv. */
	if (options & AR_X && options & ~(AR_O|AR_U|AR_TR|AR_V|AR_X))
E 20
E 16
		badoptions("-x");
E 15

D 15
mcmd()
{

	init();
	if(getaf())
		noar();
	tf2nam = mktemp(tmp2nam);
	close(creat(tf2nam, 0600));
	tf2 = open(tf2nam, 2);
	if(tf2 < 0) {
		fprintf(stderr, "ar: cannot create third temp\n");
		done(1);
E 15
I 15
	if (!(archive = *argv++)) {
D 22
		(void)fprintf(stderr, "ar: no archive specified.\n");
E 22
I 22
		warnx("no archive specified");
E 22
		usage();
E 15
	}
D 15
	while(!getdir()) {
		bamatch();
		if(match()) {
			mesg('m');
			copyfil(af, tf2, IODD+OODD+HEAD);
			continue;
		}
		mesg('c');
		copyfil(af, tf, IODD+OODD+HEAD);
	}
	install();
}
E 15

D 15
tcmd()
{

	if(getaf())
		noar();
	while(!getdir()) {
		if(namc == 0 || match()) {
			if(flg['v'-'a'])
				longt();
			printf("%s\n", trim(file));
		}
		copyfil(af, -1, IODD+SKIP);
E 15
I 15
	/* -dmqr require a list of archive elements. */
	if (options & (AR_D|AR_M|AR_Q|AR_R) && !*argv) {
D 22
		(void)fprintf(stderr, "ar: no archive members specified.\n");
E 22
I 22
		warnx("no archive members specified");
E 22
		usage();
E 15
	}
D 15
}
E 15

D 15
qcmd()
{
	register i, f;

	if (flg['a'-'a'] || flg['b'-'a']) {
		fprintf(stderr, "ar: abi not allowed with q\n");
		done(1);
	}
I 7
	truncate++;
E 7
	getqf();
	for(i=0; signum[i]; i++)
		signal(signum[i], SIG_IGN);
	lseek(qf, 0l, 2);
	for(i=0; i<namc; i++) {
		file = namv[i];
		if(file == 0)
			continue;
		namv[i] = 0;
		mesg('q');
		f = stats();
		if(f < 0) {
			fprintf(stderr, "ar: %s cannot open\n", file);
			continue;
		}
		tf = qf;
		movefil(f);
		qf = tf;
	}
E 15
I 15
D 19
	rval = (*fcall)(argv);
	exit(rval);
E 19
I 19
	exit((*fcall)(argv));
E 19
E 15
}

I 18
static void
E 18
D 15
init()
E 15
I 15
badoptions(arg)
	char *arg;
E 15
{
D 15

D 14
	tfnam = mktemp(tmpnam);
E 14
I 14
	tfnam = mktemp(tmp0nam);
E 14
	close(creat(tfnam, 0600));
	tf = open(tfnam, 2);
	if(tf < 0) {
		fprintf(stderr, "ar: cannot create temp file\n");
		done(1);
	}
	if (write(tf, ARMAG, SARMAG) != SARMAG)
		wrerr();
E 15
I 15
D 22
	(void)fprintf(stderr,
	    "ar: illegal option combination for %s.\n", arg);
E 22
I 22

	warnx("illegal option combination for %s", arg);
E 22
	usage();
E 15
}

I 18
static void
E 18
D 15
getaf()
{
	char mbuf[SARMAG];

	af = open(arnam, 0);
	if(af < 0)
		return(1);
	if (read(af, mbuf, SARMAG) != SARMAG || strncmp(mbuf, ARMAG, SARMAG)) {
		fprintf(stderr, "ar: %s not in archive format\n", arnam);
		done(1);
	}
	return(0);
}

getqf()
{
	char mbuf[SARMAG];

	if ((qf = open(arnam, 2)) < 0) {
		if(!flg['c'-'a'])
			fprintf(stderr, "ar: creating %s\n", arnam);
		if ((qf = creat(arnam, 0666)) < 0) {
			fprintf(stderr, "ar: cannot create %s\n", arnam);
			done(1);
		}
		if (write(qf, ARMAG, SARMAG) != SARMAG)
			wrerr();
	} else if (read(qf, mbuf, SARMAG) != SARMAG
		|| strncmp(mbuf, ARMAG, SARMAG)) {
		fprintf(stderr, "ar: %s not in archive format\n", arnam);
		done(1);
	}
}

E 15
usage()
{
I 22

E 22
D 4
	printf("usage: ar [%s][%s] archive files ...\n", opt, man);
E 4
I 4
D 15
	printf("usage: ar [%s][%s] archive files ...\n", man, opt);
E 4
	done(1);
}

noar()
{

	fprintf(stderr, "ar: %s does not exist\n", arnam);
	done(1);
}

sigdone()
{
	done(100);
}

done(c)
{

	if(tfnam)
		unlink(tfnam);
	if(tf1nam)
		unlink(tf1nam);
	if(tf2nam)
		unlink(tf2nam);
	exit(c);
}

notfound()
{
	register i, n;

	n = 0;
	for(i=0; i<namc; i++)
		if(namv[i]) {
			fprintf(stderr, "ar: %s not found\n", namv[i]);
			n++;
		}
	return(n);
}

morefil()
{
	register i, n;

	n = 0;
	for(i=0; i<namc; i++)
		if(namv[i])
			n++;
	return(n);
}

cleanup()
{
	register i, f;

I 7
	truncate++;
E 7
	for(i=0; i<namc; i++) {
		file = namv[i];
		if(file == 0)
			continue;
		namv[i] = 0;
		mesg('a');
		f = stats();
		if(f < 0) {
			fprintf(stderr, "ar: %s cannot open\n", file);
			continue;
		}
		movefil(f);
	}
	install();
}

install()
{
	register i;

	for(i=0; signum[i]; i++)
		signal(signum[i], SIG_IGN);
	if(af < 0)
		if(!flg['c'-'a'])
			fprintf(stderr, "ar: creating %s\n", arnam);
	close(af);
	af = creat(arnam, 0666);
	if(af < 0) {
		fprintf(stderr, "ar: cannot create %s\n", arnam);
		done(1);
	}
	if(tfnam) {
		lseek(tf, 0l, 0);
D 8
		while((i = read(tf, buf, BUFSIZ)) > 0)
E 8
I 8
		while((i = read(tf, buf, MAXBSIZE)) > 0)
E 8
			if (write(af, buf, i) != i)
				wrerr();
	}
	if(tf2nam) {
		lseek(tf2, 0l, 0);
D 8
		while((i = read(tf2, buf, BUFSIZ)) > 0)
E 8
I 8
		while((i = read(tf2, buf, MAXBSIZE)) > 0)
E 8
			if (write(af, buf, i) != i)
				wrerr();
	}
	if(tf1nam) {
		lseek(tf1, 0l, 0);
D 8
		while((i = read(tf1, buf, BUFSIZ)) > 0)
E 8
I 8
		while((i = read(tf1, buf, MAXBSIZE)) > 0)
E 8
			if (write(af, buf, i) != i)
				wrerr();
	}
}

/*
 * insert the file 'file'
 * into the temporary file
 */
movefil(f)
{
	char buf[sizeof(arbuf)+1];

D 12
	sprintf(buf, "%-16s%-12ld%-6u%-6u%-8o%-10ld%-2s",
E 12
I 12
	(void)sprintf(buf, "%-16s%-12ld%-6u%-6u%-8o%-10ld%-2s",
E 12
	   trim(file),
	   stbuf.st_mtime,
D 9
	   stbuf.st_uid,
	   stbuf.st_gid,
E 9
I 9
	   (u_short)stbuf.st_uid,
	   (u_short)stbuf.st_gid,
E 9
	   stbuf.st_mode,
	   stbuf.st_size,
	   ARFMAG);
	strncpy((char *)&arbuf, buf, sizeof(arbuf));
	larbuf.lar_size = stbuf.st_size;
	copyfil(f, tf, OODD+HEAD);
	close(f);
}

stats()
{
	register f;

	f = open(file, 0);
	if(f < 0)
		return(f);
	if(fstat(f, &stbuf) < 0) {
		close(f);
		return(-1);
	}
	return(f);
}

/*
 * copy next file
 * size given in arbuf
 */
copyfil(fi, fo, flag)
{
	register i, o;
	int pe;

	if(flag & HEAD) {
		for (i=sizeof(arbuf.ar_name)-1; i>=0; i--) {
			if (arbuf.ar_name[i]==' ')
				continue;
			else if (arbuf.ar_name[i]=='\0')
				arbuf.ar_name[i] = ' ';
			else
				break;
		}
		if (write(fo, (char *)&arbuf, sizeof arbuf) != sizeof arbuf)
			wrerr();
	}
	pe = 0;
	while(larbuf.lar_size > 0) {
D 8
		i = o = BUFSIZ;
E 8
I 8
		i = o = MAXBSIZE;
E 8
		if(larbuf.lar_size < i) {
			i = o = larbuf.lar_size;
			if(i&1) {
				buf[i] = '\n';
				if(flag & IODD)
					i++;
				if(flag & OODD)
					o++;
			}
		}
		if(read(fi, buf, i) != i)
			pe++;
		if((flag & SKIP) == 0)
			if (write(fo, buf, o) != o)
				wrerr();
D 8
		larbuf.lar_size -= BUFSIZ;
E 8
I 8
		larbuf.lar_size -= MAXBSIZE;
E 8
	}
	if(pe)
		phserr();
}

getdir()
{
	register char *cp;
	register i;

	i = read(af, (char *)&arbuf, sizeof arbuf);
	if(i != sizeof arbuf) {
		if(tf1nam) {
			i = tf;
			tf = tf1;
			tf1 = i;
		}
		return(1);
	}
	if (strncmp(arbuf.ar_fmag, ARFMAG, sizeof(arbuf.ar_fmag))) {
		fprintf(stderr, "ar: malformed archive (at %ld)\n", lseek(af, 0L, 1));
		done(1);
	}
	cp = arbuf.ar_name + sizeof(arbuf.ar_name);
	while (*--cp==' ')
		;
	*++cp = '\0';
	strncpy(name, arbuf.ar_name, sizeof(arbuf.ar_name));
	file = name;
	strncpy(larbuf.lar_name, name, sizeof(larbuf.lar_name));
	sscanf(arbuf.ar_date, "%ld", &larbuf.lar_date);
	sscanf(arbuf.ar_uid, "%hd", &larbuf.lar_uid);
	sscanf(arbuf.ar_gid, "%hd", &larbuf.lar_gid);
	sscanf(arbuf.ar_mode, "%ho", &larbuf.lar_mode);
	sscanf(arbuf.ar_size, "%ld", &larbuf.lar_size);
	return(0);
}

match()
{
	register i;

	for(i=0; i<namc; i++) {
		if(namv[i] == 0)
			continue;
		if(strcmp(trim(namv[i]), file) == 0) {
			file = namv[i];
			namv[i] = 0;
			return(1);
		}
	}
	return(0);
}

bamatch()
{
	register f;

	switch(bastate) {

	case 1:
		if(strcmp(file, ponam) != 0)
			return;
		bastate = 2;
		if(flg['a'-'a'])
			return;

	case 2:
		bastate = 0;
		tf1nam = mktemp(tmp1nam);
		close(creat(tf1nam, 0600));
		f = open(tf1nam, 2);
		if(f < 0) {
			fprintf(stderr, "ar: cannot create second temp\n");
			return;
		}
		tf1 = tf;
		tf = f;
	}
}

phserr()
{

	fprintf(stderr, "ar: phase error on %s\n", file);
}

mesg(c)
{

	if(flg['v'-'a'])
		if(c != 'c' || flg['v'-'a'] > 1)
			printf("%c - %s\n", c, file);
}

char *
trim(s)
char *s;
{
	register char *p1, *p2;

I 7
	/* Strip trailing slashes */
E 7
	for(p1 = s; *p1; p1++)
		;
	while(p1 > s) {
		if(*--p1 != '/')
			break;
		*p1 = 0;
	}
I 7

	/* Find last component of path; do not zap the path */
E 7
	p2 = s;
	for(p1 = s; *p1; p1++)
		if(*p1 == '/')
			p2 = p1+1;
I 7

	/*
	 * Truncate name if too long, only if we are doing an 'add'
	 * type operation. We only allow 15 cause rest of ar
	 * isn't smart enough to deal with non-null terminated
	 * names.  Need an exit status convention...
	 * Need yet another new archive format...
	 */
	if (truncate && strlen(p2) > sizeof(arbuf.ar_name) - 1) {
		fprintf(stderr, "ar: filename %s truncated to ", p2);
		*(p2 + sizeof(arbuf.ar_name) - 1) = '\0';
		fprintf(stderr, "%s\n", p2);
	}
E 7
	return(p2);
}

#define	IFMT	060000
#define	ISARG	01000
#define	LARGE	010000
#define	SUID	04000
#define	SGID	02000
#define	ROWN	0400
#define	WOWN	0200
#define	XOWN	0100
#define	RGRP	040
#define	WGRP	020
#define	XGRP	010
#define	ROTH	04
#define	WOTH	02
#define	XOTH	01
#define	STXT	01000

longt()
{
	register char *cp;

	pmode();
	printf("%3d/%1d", larbuf.lar_uid, larbuf.lar_gid);
	printf("%7ld", larbuf.lar_size);
	cp = ctime(&larbuf.lar_date);
	printf(" %-12.12s %-4.4s ", cp+4, cp+20);
}

int	m1[] = { 1, ROWN, 'r', '-' };
int	m2[] = { 1, WOWN, 'w', '-' };
int	m3[] = { 2, SUID, 's', XOWN, 'x', '-' };
int	m4[] = { 1, RGRP, 'r', '-' };
int	m5[] = { 1, WGRP, 'w', '-' };
int	m6[] = { 2, SGID, 's', XGRP, 'x', '-' };
int	m7[] = { 1, ROTH, 'r', '-' };
int	m8[] = { 1, WOTH, 'w', '-' };
int	m9[] = { 2, STXT, 't', XOTH, 'x', '-' };

int	*m[] = { m1, m2, m3, m4, m5, m6, m7, m8, m9};

pmode()
{
	register int **mp;

	for (mp = &m[0]; mp < &m[9];)
		select(*mp++);
}

select(pairp)
int *pairp;
{
	register int n, *ap;

	ap = pairp;
	n = *ap++;
	while (--n>=0 && (larbuf.lar_mode&*ap++)==0)
		ap++;
	putchar(*ap);
}

wrerr()
{
	perror("ar write error");
	done(1);
}
E 15
I 15
D 16
	(void)fprintf(stderr, "usage:  ar -d [-v] archive file ...\n");
	(void)fprintf(stderr, "\tar -m [-v] archive file ...\n");
	(void)fprintf(stderr, "\tar -m [-abiv] position archive file ...\n");
	(void)fprintf(stderr, "\tar -p [-v] archive [file ...]\n");
	(void)fprintf(stderr, "\tar -q [-cv] archive file ...\n");
	(void)fprintf(stderr, "\tar -r [-cuv] archive file ...\n");
	(void)fprintf(stderr, "\tar -r [-abciuv] position archive file ...\n");
	(void)fprintf(stderr, "\tar -t [-v] archive [file ...]\n");
	(void)fprintf(stderr, "\tar -x [-ouv] archive [file ...]\n");
E 16
I 16
D 20
	(void)fprintf(stderr, "usage:  ar -d [-sv] archive file ...\n");
	(void)fprintf(stderr, "\tar -m [-sv] archive file ...\n");
	(void)fprintf(stderr, "\tar -m [-abisv] position archive file ...\n");
	(void)fprintf(stderr, "\tar -p [-sv] archive [file ...]\n");
	(void)fprintf(stderr, "\tar -q [-csv] archive file ...\n");
	(void)fprintf(stderr, "\tar -r [-cusv] archive file ...\n");
	(void)fprintf(stderr, "\tar -r [-abciusv] position archive file ...\n");
	(void)fprintf(stderr, "\tar -t [-sv] archive [file ...]\n");
	(void)fprintf(stderr, "\tar -x [-ousv] archive [file ...]\n");
E 20
I 20
	(void)fprintf(stderr, "usage:  ar -d [-Tv] archive file ...\n");
	(void)fprintf(stderr, "\tar -m [-Tv] archive file ...\n");
	(void)fprintf(stderr, "\tar -m [-abiTv] position archive file ...\n");
	(void)fprintf(stderr, "\tar -p [-Tv] archive [file ...]\n");
	(void)fprintf(stderr, "\tar -q [-cTv] archive file ...\n");
	(void)fprintf(stderr, "\tar -r [-cuTv] archive file ...\n");
	(void)fprintf(stderr, "\tar -r [-abciuTv] position archive file ...\n");
	(void)fprintf(stderr, "\tar -t [-Tv] archive [file ...]\n");
	(void)fprintf(stderr, "\tar -x [-ouTv] archive [file ...]\n");
E 20
E 16
	exit(1);
}	
E 15
E 1
