h30891
s 00001/00001/00560
d D 8.6 95/05/04 15:43:09 bostic 15 14
c Chris didn't compile it before he sent it off
e
s 00001/00000/00560
d D 8.5 95/05/04 15:40:24 bostic 14 13
c optarg/optind moved to unistd.h
e
s 00009/00005/00551
d D 8.4 95/04/28 12:42:14 bostic 13 12
c unspecified changes!! From: Chris Torek <torek@BSDI.COM>
e
s 00062/00101/00494
d D 8.3 94/04/16 13:39:24 bostic 12 11
c Empty fields were not being output for unpairable lines.
c ex: printf "bar b\nbar.ugh bu\n" > f1; printf "bar.ugh 99\n" > f2
c join -a1 -e FOO -o 1.1 1.2 2.2 f1 f2 put out "bar b\nbar.ugh bu 99"
c not "bar b FOO\nbar.ugh bu 99"
c From: henry@zoo.toronto.edu (Henry Spencer)
c lots of KNF, prettiness police, use err(3)
e
s 00001/00001/00594
d D 8.2 94/01/03 10:06:44 bostic 11 10
c rename fgetline -> fgetln
e
s 00005/00005/00590
d D 8.1 93/06/06 14:52:10 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00004/00584
d D 5.6 93/03/04 14:42:52 bostic 9 8
c rework fgetline(3) to be 8-bit clean; it no longer replaces \n with \0
e
s 00002/00002/00586
d D 5.5 92/10/16 17:03:07 bostic 8 7
c wrong init value for pushbool
c ex: echo > a; date > b; join a b; would core dump
e
s 00018/00015/00570
d D 5.4 92/04/06 19:06:45 bostic 7 6
c If I had brains, I'd be a fuckin' menace.
e
s 00005/00005/00580
d D 5.3 91/11/26 15:48:16 marc 6 5
c fileno is a #define macro - rename to filenum
e
s 00002/00002/00583
d D 5.2 91/11/18 16:16:34 bostic 5 4
c fix Steve Haymans organization
e
s 00525/00171/00060
d D 5.1 91/11/18 14:07:18 bostic 4 3
c integrate Steve Hayman's version; now POSIX 1003.2 D11.2 compliant
e
s 00017/00001/00214
d D 4.3 91/04/17 17:54:46 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00001/00214
d D 4.2 83/06/30 14:03:53 sam 2 1
c correct usage, from sun
e
s 00215/00000/00000
d D 4.1 80/10/01 17:27:12 bill 1 0
c date and time created 80/10/01 17:27:12 by bill
e
u
U
t
T
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
E 3
I 3
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
D 12
 * Copyright (c) 1991, 1993
E 12
I 12
 * Copyright (c) 1991, 1993, 1994
E 12
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 4
 * %sccs.include.proprietary.c%
E 4
I 4
 * This code is derived from software contributed to Berkeley by
D 5
 * Steve Hayman of Indiana University, Michiro Hikida and David
 * Goodenough.
E 5
I 5
 * Steve Hayman of the Computer Science Department, Indiana University,
 * Michiro Hikida and David Goodenough.
E 5
 *
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
D 10
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
D 12
"%Z% Copyright (c) 1991, 1993\n\
E 12
I 12
"%Z% Copyright (c) 1991, 1993, 1994\n\
E 12
	The Regents of the University of California.  All rights reserved.\n";
E 10
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 3
D 4
/*	join F1 F2 on stuff */
E 4
I 4
D 7
#include <sys/types.h>
E 7
I 7
#include <sys/param.h>
I 9

#include <ctype.h>
I 12
#include <err.h>
E 12
E 9
E 7
#include <errno.h>
D 9
#include <stdlib.h>
E 9
#include <stdio.h>
I 9
#include <stdlib.h>
E 9
#include <string.h>
I 14
#include <unistd.h>
E 14
D 9
#include <ctype.h>
E 9
E 4

D 4
#include	<stdio.h>
#define F1 0
#define F2 1
#define	NFLD	20	/* max field per line */
#define comp() cmp(ppi[F1][j1],ppi[F2][j2])
E 4
I 4
/*
 * There's a structure per input file which encapsulates the state of the
 * file.  We repeatedly read lines from each file until we've read in all
 * the consecutive lines from the file with a common join field.  Then we
 * compare the set of lines with an equivalent set from the other file.
 */
typedef struct {
	char *line;		/* line */
	u_long linealloc;	/* line allocated count */
	char **fields;		/* line field(s) */
	u_long fieldcnt;	/* line field(s) count */
	u_long fieldalloc;	/* line field(s) allocated count */
} LINE;
E 4

D 4
FILE *f[2];
char buf[2][BUFSIZ];	/*input lines */
char *ppi[2][NFLD];	/* pointers to fields in lines */
char *s1,*s2;
int	j1	= 1;	/* join of this field of file 1 */
int	j2	= 1;	/* join of this field of file 2 */
int	olist[2*NFLD];	/* output these fields */
int	olistf[2*NFLD];	/* from these files */
int	no;	/* number of entries in olist */
int	sep1	= ' ';	/* default field separator */
int	sep2	= '\t';
char*	null	= "";
int	unpub1;
int	unpub2;
int	aflg;
E 4
I 4
typedef struct {
	FILE *fp;		/* file descriptor */
	u_long joinf;		/* join field (-1, -2, -j) */
	int unpair;		/* output unpairable lines (-a) */
	int number;		/* 1 for file 1, 2 for file 2 */
E 4

I 4
	LINE *set;		/* set of lines with same field */
I 7
	int pushbool;		/* if pushback is set */
E 7
	u_long pushback;	/* line on the stack */
	u_long setcnt;		/* set count */
	u_long setalloc;	/* set allocated count */
} INPUT;
D 8
INPUT input1 = { NULL, 0, 0, 1, NULL, -1, 0, 0, },
      input2 = { NULL, 0, 0, 1, NULL, -1, 0, 0, };
E 8
I 8
INPUT input1 = { NULL, 0, 0, 1, NULL, 0, 0, 0, },
      input2 = { NULL, 0, 0, 2, NULL, 0, 0, 0, };
E 8

typedef struct {
D 6
	u_long	fileno;		/* file number */
E 6
I 6
	u_long	filenum;	/* file number */
E 6
	u_long	fieldno;	/* field number */
} OLIST;
OLIST *olist;			/* output field list */
u_long olistcnt;		/* output field list count */
u_long olistalloc;		/* output field allocated count */

int joinout = 1;		/* show lines with matched join fields (-v) */
int needsep;			/* need separator character */
D 12
int showusage = 1;		/* show usage for usage err() calls */
E 12
int spans = 1;			/* span multiple delimiters (-t) */
char *empty;			/* empty field replacement string (-e) */
char *tabchar = " \t";		/* delimiter characters (-t) */

int  cmp __P((LINE *, u_long, LINE *, u_long));
D 12
void enomem __P((void));
void err __P((const char *, ...));
E 12
void fieldarg __P((char *));
void joinlines __P((INPUT *, INPUT *));
void obsolete __P((char **));
D 12
void outfield __P((LINE *, u_long));
E 12
I 12
void outfield __P((LINE *, u_long, int));
E 12
void outoneline __P((INPUT *, LINE *));
void outtwoline __P((INPUT *, LINE *, INPUT *, LINE *));
void slurp __P((INPUT *));
void usage __P((void));

int
E 4
main(argc, argv)
D 4
char *argv[];
E 4
I 4
	int argc;
	char *argv[];
E 4
{
D 4
	int i;
	int n1, n2;
	long top2, bot2;
	long ftell();
E 4
I 4
D 12
	register INPUT *F1, *F2;
E 12
I 12
	INPUT *F1, *F2;
E 12
	int aflag, ch, cval, vflag;
	char *end;
E 4

D 4
	while (argc > 1 && argv[1][0] == '-') {
		if (argv[1][1] == '\0')
E 4
I 4
	F1 = &input1;
	F2 = &input2;

	aflag = vflag = 0;
	obsolete(argv);
	while ((ch = getopt(argc, argv, "\01a:e:j:1:2:o:t:v:")) != EOF) {
		switch (ch) {
D 12
		case '\01':
E 12
I 12
		case '\01':		/* See comment in obsolete(). */
E 12
			aflag = 1;
			F1->unpair = F2->unpair = 1;
E 4
			break;
D 4
		switch (argv[1][1]) {
E 4
I 4
		case '1':
			if ((F1->joinf = strtol(optarg, &end, 10)) < 1)
D 12
				err("-1 option field number less than 1");
E 12
I 12
				errx(1, "-1 option field number less than 1");
E 12
			if (*end)
D 12
				err("illegal field number -- %s", optarg);
E 12
I 12
				errx(1, "illegal field number -- %s", optarg);
E 12
			--F1->joinf;
			break;
		case '2':
			if ((F2->joinf = strtol(optarg, &end, 10)) < 1)
D 12
				err("-2 option field number less than 1");
E 12
I 12
				errx(1, "-2 option field number less than 1");
E 12
			if (*end)
D 12
				err("illegal field number -- %s", optarg);
E 12
I 12
				errx(1, "illegal field number -- %s", optarg);
E 12
			--F2->joinf;
			break;
E 4
		case 'a':
D 4
			switch(argv[1][2]) {
			case '1':
				aflg |= 1;
E 4
I 4
			aflag = 1;
			switch(strtol(optarg, &end, 10)) {
			case 1:
				F1->unpair = 1;
E 4
				break;
D 4
			case '2':
				aflg |= 2;
E 4
I 4
			case 2:
				F2->unpair = 1;
E 4
				break;
			default:
D 4
				aflg |= 3;
E 4
I 4
D 12
				err("-a option file number not 1 or 2");
E 12
I 12
				errx(1, "-a option file number not 1 or 2");
E 12
				break;
E 4
			}
I 4
			if (*end)
D 12
				err("illegal file number -- %s", optarg);
E 12
I 12
				errx(1, "illegal file number -- %s", optarg);
E 12
E 4
			break;
		case 'e':
D 4
			null = argv[2];
			argv++;
			argc--;
E 4
I 4
			empty = optarg;
E 4
			break;
D 4
		case 't':
			sep1 = sep2 = argv[1][2];
E 4
I 4
		case 'j':
			if ((F1->joinf = F2->joinf =
			    strtol(optarg, &end, 10)) < 1)
D 12
				err("-j option field number less than 1");
E 12
I 12
				errx(1, "-j option field number less than 1");
E 12
			if (*end)
D 12
				err("illegal field number -- %s", optarg);
E 12
I 12
				errx(1, "illegal field number -- %s", optarg);
E 12
			--F1->joinf;
			--F2->joinf;
E 4
			break;
		case 'o':
D 4
			for (no = 0; no < 2*NFLD; no++) {
				if (argv[2][0] == '1' && argv[2][1] == '.') {
					olistf[no] = F1;
					olist[no] = atoi(&argv[2][2]);
				} else if (argv[2][0] == '2' && argv[2][1] == '.') {
					olist[no] = atoi(&argv[2][2]);
					olistf[no] = F2;
				} else
					break;
				argc--;
				argv++;
			}
E 4
I 4
			fieldarg(optarg);
E 4
			break;
D 4
		case 'j':
			if (argv[1][2] == '1')
				j1 = atoi(argv[2]);
			else if (argv[1][2] == '2')
				j2 = atoi(argv[2]);
			else
				j1 = j2 = atoi(argv[2]);
			argc--;
			argv++;
E 4
I 4
		case 't':
			spans = 0;
			if (strlen(tabchar = optarg) != 1)
D 12
				err("illegal tab character specification");
E 12
I 12
				errx(1, "illegal tab character specification");
E 12
E 4
			break;
I 4
		case 'v':
			vflag = 1;
			joinout = 0;
D 12
			switch(strtol(optarg, &end, 10)) {
E 12
I 12
			switch (strtol(optarg, &end, 10)) {
E 12
			case 1:
				F1->unpair = 1;
				break;
			case 2:
				F2->unpair = 1;
				break;
			default:
D 12
				err("-v option file number not 1 or 2");
E 12
I 12
				errx(1, "-v option file number not 1 or 2");
E 12
				break;
			}
			if (*end)
D 12
				err("illegal file number -- %s", optarg);
E 12
I 12
				errx(1, "illegal file number -- %s", optarg);
E 12
			break;
		case '?':
		default:
			usage();
E 4
		}
D 4
		argc--;
		argv++;
E 4
	}
D 4
	for (i = 0; i < no; i++)
		olist[i]--;	/* 0 origin */
	if (argc != 3)
D 2
		error("usage: join [-j1 x -j2 y] [-o list] file1 file2");
E 2
I 2
error("usage: join [-an] [-estring] [-j1 x -j2 y] [-o list] [-tc] file1 file2");
E 2
	j1--;
	j2--;	/* everyone else believes in 0 origin */
	s1 = ppi[F1][j1];
	s2 = ppi[F2][j2];
	if (argv[1][0] == '-')
		f[F1] = stdin;
	else if ((f[F1] = fopen(argv[1], "r")) == NULL)
		error("can't open %s", argv[1]);
	if ((f[F2] = fopen(argv[2], "r")) == NULL)
		error("can't open %s", argv[2]);
E 4
I 4
	argc -= optind;
	argv += optind;
E 4

D 4
#define get1() n1=input(F1)
#define get2() n2=input(F2)
	get1();
	bot2 = ftell(f[F2]);
	get2();
	while(n1>0 && n2>0 || aflg!=0 && n1+n2>0) {
		if(n1>0 && n2>0 && comp()>0 || n1==0) {
			if(aflg&2) output(0, n2);
			bot2 = ftell(f[F2]);
			get2();
		} else if(n1>0 && n2>0 && comp()<0 || n2==0) {
			if(aflg&1) output(n1, 0);
			get1();
		} else /*(n1>0 && n2>0 && comp()==0)*/ {
			while(n2>0 && comp()==0) {
				output(n1, n2);
				top2 = ftell(f[F2]);
				get2();
			}
			fseek(f[F2], bot2, 0);
			get2();
			get1();
			for(;;) {
				if(n1>0 && n2>0 && comp()==0) {
					output(n1, n2);
					get2();
				} else if(n1>0 && n2>0 && comp()<0 || n2==0) {
					fseek(f[F2], bot2, 0);
					get2();
					get1();
				} else /*(n1>0 && n2>0 && comp()>0 || n1==0)*/{
					fseek(f[F2], top2, 0);
					bot2 = top2;
					get2();
					break;
				}
			}
E 4
I 4
	if (aflag && vflag)
D 12
		err("-a and -v options mutually exclusive");
E 12
I 12
		errx(1, "the -a and -v options are mutually exclusive");
E 12

	if (argc != 2)
		usage();
D 12
	showusage = 0;
E 12

	/* Open the files; "-" means stdin. */
	if (!strcmp(*argv, "-"))
		F1->fp = stdin;
	else if ((F1->fp = fopen(*argv, "r")) == NULL)
D 12
		err("%s: %s", *argv, strerror(errno));
E 12
I 12
		err(1, "%s", *argv);
E 12
	++argv;
	if (!strcmp(*argv, "-"))
		F2->fp = stdin;
	else if ((F2->fp = fopen(*argv, "r")) == NULL)
D 12
		err("%s: %s", *argv, strerror(errno));
E 12
I 12
		err(1, "%s", *argv);
E 12
	if (F1->fp == stdin && F2->fp == stdin)
D 12
		err("only one input file may be stdin");
E 12
I 12
		errx(1, "only one input file may be stdin");
E 12

	slurp(F1);
	slurp(F2);
	while (F1->setcnt && F2->setcnt) {
		cval = cmp(F1->set, F1->joinf, F2->set, F2->joinf);
		if (cval == 0) {
			/* Oh joy, oh rapture, oh beauty divine! */
			if (joinout)
				joinlines(F1, F2);
			slurp(F1);
			slurp(F2);
		} else if (cval < 0) {
			/* File 1 takes the lead... */
			if (F1->unpair)
				joinlines(F1, NULL);
			slurp(F1);
		} else {
			/* File 2 takes the lead... */
			if (F2->unpair)
				joinlines(F2, NULL);
			slurp(F2);
E 4
		}
	}
D 4
	return(0);
E 4
I 4

	/*
	 * Now that one of the files is used up, optionally output any
	 * remaining lines from the other file.
	 */
	if (F1->unpair)
		while (F1->setcnt) {
			joinlines(F1, NULL);
			slurp(F1);
		}
	if (F2->unpair)
		while (F2->setcnt) {
			joinlines(F2, NULL);
			slurp(F2);
		}
	exit(0);
E 4
}

D 4
input(n)		/* get input line and split into fields */
E 4
I 4
void
slurp(F)
	INPUT *F;
E 4
{
D 4
	register int i, c;
	char *bp;
	char **pp;
E 4
I 4
D 12
	register LINE *lp, *lastlp;
	LINE tmp;
E 12
I 12
	LINE *lp, *lastlp, tmp;
E 12
	size_t len;
	int cnt;
D 7
	char *bp, *fieldp, *token;
E 7
I 7
	char *bp, *fieldp;
E 7
E 4

D 4
	bp = buf[n];
	pp = ppi[n];
	if (fgets(bp, BUFSIZ, f[n]) == NULL)
		return(0);
	for (i = 0; ; i++) {
		if (sep1 == ' ')	/* strip multiples */
			while ((c = *bp) == sep1 || c == sep2)
				bp++;	/* skip blanks */
		else
			c = *bp;
		if (c == '\n' || c == '\0')
E 4
I 4
	/*
	 * Read all of the lines from an input file that have the same
	 * join field.
	 */
	F->setcnt = 0;
	for (lastlp = NULL;; ++F->setcnt, lastlp = lp) {
		/*
		 * If we're out of space to hold line structures, allocate
		 * more.  Initialize the structure so that we know that this
		 * is new space.
		 */
		if (F->setcnt == F->setalloc) {
			cnt = F->setalloc;
D 7
			F->setalloc += 100;
E 7
I 7
			F->setalloc += 50;
E 7
			if ((F->set = realloc(F->set,
			    F->setalloc * sizeof(LINE))) == NULL)
D 12
				enomem();
D 7
			bzero(F->set + cnt, 100 * sizeof(LINE *));
E 7
I 7
			bzero(F->set + cnt, 50 * sizeof(LINE));
E 12
I 12
				err(1, NULL);
			memset(F->set + cnt, 0, 50 * sizeof(LINE));
I 13

			/* re-set lastlp in case it moved */
			if (lastlp != NULL)
D 15
				lastp = &F->set[F->setcnt - 1];
E 15
I 15
				lastlp = &F->set[F->setcnt - 1];
E 15
E 13
E 12
E 7
		}
			
		/*
		 * Get any pushed back line, else get the next line.  Allocate
		 * space as necessary.  If taking the line from the stack swap
D 7
		 * the two structures so that we don't lose the allocated space.
		 * This could be avoided by doing another level of indirection,
E 7
I 7
		 * the two structures so that we don't lose space allocated to
		 * either structure.  This could be avoided by doing another
		 * level of indirection, but it's probably okay as is.
E 7
		 * but it's probably okay as is.
		 */
		lp = &F->set[F->setcnt];
D 7
		if (F->pushback != -1) {
E 7
I 7
		if (F->pushbool) {
E 7
			tmp = F->set[F->setcnt];
			F->set[F->setcnt] = F->set[F->pushback];
			F->set[F->pushback] = tmp;
D 7
			F->pushback = -1;
E 7
I 7
			F->pushbool = 0;
E 7
			continue;
		}
D 11
		if ((bp = fgetline(F->fp, &len)) == NULL)
E 11
I 11
		if ((bp = fgetln(F->fp, &len)) == NULL)
E 11
			return;
D 9
		if (lp->linealloc <= len) {
E 9
I 9
		if (lp->linealloc <= len + 1) {
E 9
D 7
			lp->linealloc += 100;
			if ((lp->line = realloc(lp->line,
			    lp->linealloc * sizeof(char))) == NULL)
E 7
I 7
D 13
			lp->linealloc += MAX(100, len + 1);
E 13
I 13
			lp->linealloc += MAX(100, len + 1 - lp->linealloc);
E 13
			if ((lp->line =
			    realloc(lp->line, lp->linealloc)) == NULL)
E 7
D 12
				enomem();
E 12
I 12
				err(1, NULL);
E 12
		}
D 7
		bcopy(bp, lp->line, len);
E 7
I 7
D 9
		bcopy(bp, lp->line, len + 1);
E 9
I 9
D 12
		bcopy(bp, lp->line, len);
E 12
I 12
		memmove(lp->line, bp, len);
E 12

		/* Replace trailing newline, if it exists. */
		if (bp[len - 1] == '\n')
			lp->line[len - 1] = '\0';
		else
			lp->line[len] = '\0';
E 9
		bp = lp->line;
E 7

		/* Split the line into fields, allocate space as necessary. */
D 7
		token = bp;
E 7
		lp->fieldcnt = 0;
D 7
		while ((fieldp = strsep(&token, tabchar)) != NULL) {
E 7
I 7
		while ((fieldp = strsep(&bp, tabchar)) != NULL) {
E 7
			if (spans && *fieldp == '\0')
				continue;
			if (lp->fieldcnt == lp->fieldalloc) {
D 7
				lp->fieldalloc += 100;
E 7
I 7
				lp->fieldalloc += 50;
E 7
				if ((lp->fields = realloc(lp->fields,
				    lp->fieldalloc * sizeof(char *))) == NULL)
D 12
					enomem();
E 12
I 12
					err(1, NULL);
E 12
			}
			lp->fields[lp->fieldcnt++] = fieldp;
		}

		/* See if the join field value has changed. */
		if (lastlp != NULL && cmp(lp, F->joinf, lastlp, F->joinf)) {
I 7
			F->pushbool = 1;
E 7
			F->pushback = F->setcnt;
E 4
			break;
D 4
		*pp++ = bp;	/* record beginning */
		while ((c = *bp) != sep1 && c != '\n' && c != sep2 && c != '\0')
			bp++;
		*bp++ = '\0';	/* mark end by overwriting blank */
			/* fails badly if string doesn't have \n at end */
E 4
I 4
		}
E 4
	}
D 4
	*pp = 0;
	return(i);
E 4
}

D 4
output(on1, on2)	/* print items from olist */
int on1, on2;
E 4
I 4
int
cmp(lp1, fieldno1, lp2, fieldno2)
	LINE *lp1, *lp2;
	u_long fieldno1, fieldno2;
E 4
{
D 4
	int i;
	char *temp;
E 4
I 4
D 13
	if (lp1->fieldcnt < fieldno1)
		return (lp2->fieldcnt < fieldno2 ? 0 : 1);
	if (lp2->fieldcnt < fieldno2)
E 13
I 13
	if (lp1->fieldcnt <= fieldno1)
		return (lp2->fieldcnt <= fieldno2 ? 0 : 1);
	if (lp2->fieldcnt <= fieldno2)
E 13
		return (-1);
	return (strcmp(lp1->fields[fieldno1], lp2->fields[fieldno2]));
}
E 4

D 4
	if (no <= 0) {	/* default case */
		printf("%s", on1? ppi[F1][j1]: ppi[F2][j2]);
		for (i = 0; i < on1; i++)
			if (i != j1)
				printf("%c%s", sep1, ppi[F1][i]);
		for (i = 0; i < on2; i++)
			if (i != j2)
				printf("%c%s", sep1, ppi[F2][i]);
		printf("\n");
	} else {
		for (i = 0; i < no; i++) {
			temp = ppi[olistf[i]][olist[i]];
			if(olistf[i]==F1 && on1<=olist[i] ||
			   olistf[i]==F2 && on2<=olist[i] ||
			   *temp==0)
				temp = null;
			printf("%s", temp);
			if (i == no - 1)
				printf("\n");
			else
				printf("%c", sep1);
E 4
I 4
void
joinlines(F1, F2)
D 12
	register INPUT *F1, *F2;
E 12
I 12
	INPUT *F1, *F2;
E 12
{
D 12
	register int cnt1, cnt2;
E 12
I 12
	int cnt1, cnt2;
E 12

	/*
	 * Output the results of a join comparison.  The output may be from
	 * either file 1 or file 2 (in which case the first argument is the
	 * file from which to output) or from both.
	 */
	if (F2 == NULL) {
		for (cnt1 = 0; cnt1 < F1->setcnt; ++cnt1)
			outoneline(F1, &F1->set[cnt1]);
		return;
	}
	for (cnt1 = 0; cnt1 < F1->setcnt; ++cnt1)
		for (cnt2 = 0; cnt2 < F2->setcnt; ++cnt2)
			outtwoline(F1, &F1->set[cnt1], F2, &F2->set[cnt2]);
}

void
outoneline(F, lp)
	INPUT *F;
D 12
	register LINE *lp;
E 12
I 12
	LINE *lp;
E 12
{
D 12
	register int cnt;
E 12
I 12
	int cnt;
E 12

	/*
	 * Output a single line from one of the files, according to the
	 * join rules.  This happens when we are writing unmatched single
	 * lines.  Output empty fields in the right places.
	 */
	if (olist)
		for (cnt = 0; cnt < olistcnt; ++cnt) {
D 6
			if (olist[cnt].fileno == F->number)
E 6
I 6
			if (olist[cnt].filenum == F->number)
E 6
D 12
				outfield(lp, olist[cnt].fieldno);
E 12
I 12
				outfield(lp, olist[cnt].fieldno, 0);
			else
				outfield(lp, 0, 1);
E 12
E 4
		}
I 4
	else
		for (cnt = 0; cnt < lp->fieldcnt; ++cnt)
D 12
			outfield(lp, cnt);
E 12
I 12
			outfield(lp, cnt, 0);
E 12
	(void)printf("\n");
	if (ferror(stdout))
D 12
		err("stdout: %s", strerror(errno));
E 12
I 12
		err(1, "stdout");
E 12
	needsep = 0;
}

void
outtwoline(F1, lp1, F2, lp2)
D 12
	register INPUT *F1, *F2;
	register LINE *lp1, *lp2;
E 12
I 12
	INPUT *F1, *F2;
	LINE *lp1, *lp2;
E 12
{
D 12
	register int cnt;
E 12
I 12
	int cnt;
E 12

	/* Output a pair of lines according to the join list (if any). */
	if (olist)
		for (cnt = 0; cnt < olistcnt; ++cnt)
D 6
			if (olist[cnt].fileno == 1)
E 6
I 6
			if (olist[cnt].filenum == 1)
E 6
D 12
				outfield(lp1, olist[cnt].fieldno);
E 12
I 12
				outfield(lp1, olist[cnt].fieldno, 0);
E 12
D 6
			else /* if (olist[cnt].fileno == 2) */
E 6
I 6
			else /* if (olist[cnt].filenum == 2) */
E 6
D 12
				outfield(lp2, olist[cnt].fieldno);
E 12
I 12
				outfield(lp2, olist[cnt].fieldno, 0);
E 12
	else {
		/*
		 * Output the join field, then the remaining fields from F1
		 * and F2.
		 */
D 12
		outfield(lp1, F1->joinf);
E 12
I 12
		outfield(lp1, F1->joinf, 0);
E 12
		for (cnt = 0; cnt < lp1->fieldcnt; ++cnt)
			if (F1->joinf != cnt)
D 12
				outfield(lp1, cnt);
E 12
I 12
				outfield(lp1, cnt, 0);
E 12
		for (cnt = 0; cnt < lp2->fieldcnt; ++cnt)
			if (F2->joinf != cnt)
D 12
				outfield(lp2, cnt);
E 12
I 12
				outfield(lp2, cnt, 0);
E 12
E 4
	}
I 4
	(void)printf("\n");
	if (ferror(stdout))
D 12
		err("stdout: %s", strerror(errno));
E 12
I 12
		err(1, "stdout");
E 12
	needsep = 0;
E 4
}

D 4
error(s1, s2, s3, s4, s5)
char *s1;
E 4
I 4
void
D 12
outfield(lp, fieldno)
E 12
I 12
outfield(lp, fieldno, out_empty)
E 12
	LINE *lp;
	u_long fieldno;
I 12
	int out_empty;
E 12
E 4
{
D 4
	fprintf(stderr, "join: ");
	fprintf(stderr, s1, s2, s3, s4, s5);
	fprintf(stderr, "\n");
E 4
I 4
	if (needsep++)
		(void)printf("%c", *tabchar);
	if (!ferror(stdout))
D 12
		if (lp->fieldcnt < fieldno) {
E 12
I 12
		if (lp->fieldcnt < fieldno || out_empty) {
E 12
			if (empty != NULL)
				(void)printf("%s", empty);
		} else {
			if (*lp->fields[fieldno] == '\0')
				return;
			(void)printf("%s", lp->fields[fieldno]);
		}
	if (ferror(stdout))
D 12
		err("stdout: %s", strerror(errno));
E 12
I 12
		err(1, "stdout");
E 12
}

/*
 * Convert an output list argument "2.1, 1.3, 2.4" into an array of output
 * fields.
 */
void
fieldarg(option)
	char *option;
{
	u_long fieldno;
	char *end, *token;

D 13
	while ((token = strsep(&option, " \t")) != NULL) {
E 13
I 13
	while ((token = strsep(&option, ", \t")) != NULL) {
E 13
		if (*token == '\0')
			continue;
		if (token[0] != '1' && token[0] != '2' || token[1] != '.')
D 12
			err("malformed -o option field");
E 12
I 12
			errx(1, "malformed -o option field");
E 12
		fieldno = strtol(token + 2, &end, 10);
		if (*end)
D 12
			err("malformed -o option field");
E 12
I 12
			errx(1, "malformed -o option field");
E 12
		if (fieldno == 0)
D 12
			err("field numbers are 1 based");
E 12
I 12
			errx(1, "field numbers are 1 based");
E 12
		if (olistcnt == olistalloc) {
			olistalloc += 50;
			if ((olist = realloc(olist,
			    olistalloc * sizeof(OLIST))) == NULL)
D 12
				enomem();
E 12
I 12
				err(1, NULL);
E 12
		}
D 6
		olist[olistcnt].fileno = token[0] - '0';
E 6
I 6
		olist[olistcnt].filenum = token[0] - '0';
E 6
		olist[olistcnt].fieldno = fieldno - 1;
		++olistcnt;
	}
}

void
obsolete(argv)
	char **argv;
{
	int len;
	char **p, *ap, *t;

D 12
	while (ap = *++argv) {
E 12
I 12
	while ((ap = *++argv) != NULL) {
E 12
		/* Return if "--". */
		if (ap[0] == '-' && ap[1] == '-')
			return;
		switch (ap[1]) {
		case 'a':
			/* 
			 * The original join allowed "-a", which meant the
			 * same as -a1 plus -a2.  POSIX 1003.2, Draft 11.2
			 * only specifies this as "-a 1" and "a -2", so we
			 * have to use another option flag, one that is
			 * unlikely to ever be used or accidentally entered
			 * on the command line.  (Well, we could reallocate
			 * the argv array, but that hardly seems worthwhile.)
			 */
			if (ap[2] == '\0')
				ap[1] = '\01';
			break;
		case 'j':
			/*
			 * The original join allowed "-j[12] arg" and "-j arg".
			 * Convert the former to "-[12] arg".  Don't convert
			 * the latter since getopt(3) can handle it.
			 */
			switch(ap[2]) {
			case '1':
				if (ap[3] != '\0')
					goto jbad;
				ap[1] = '1';
				ap[2] = '\0';
				break;
			case '2':
				if (ap[3] != '\0')
					goto jbad;
				ap[1] = '2';
				ap[2] = '\0';
				break;
			case '\0':
				break;
			default:
D 12
jbad:				err("illegal option -- %s", ap);
E 12
I 12
jbad:				errx(1, "illegal option -- %s", ap);
E 12
				usage();
			}
			break;
		case 'o':
			/*
D 12
			 * The original join allowed "-o arg arg".  Convert to
			 * "-o arg -o arg".
E 12
I 12
			 * The original join allowed "-o arg arg".
			 * Convert to "-o arg -o arg".
E 12
			 */
			if (ap[2] != '\0')
				break;
			for (p = argv + 2; *p; ++p) {
D 12
				if (p[0][0] != '1' && p[0][0] != '2' ||
				    p[0][1] != '.')
E 12
I 12
				if (p[0][0] != '1' &&
				    p[0][0] != '2' || p[0][1] != '.')
E 12
					break;
				len = strlen(*p);
				if (len - 2 != strspn(*p + 2, "0123456789"))
					break;
				if ((t = malloc(len + 3)) == NULL)
D 12
					enomem();
E 12
I 12
					err(1, NULL);
E 12
				t[0] = '-';
				t[1] = 'o';
D 12
				bcopy(*p, t + 2, len + 1);
E 12
I 12
				memmove(t + 2, *p, len + 1);
E 12
				*p = t;
			}
			argv = p - 1;
			break;
		}
	}
}

void
D 12
enomem()
{
	showusage = 0;
	err("%s", strerror(errno));
}

void
E 12
usage()
{
	(void)fprintf(stderr, "%s%s\n",
	    "usage: join [-a fileno | -v fileno ] [-e string] [-1 field] ",
	    "[-2 field]\n            [-o list] [-t char] file1 file2");
E 4
	exit(1);
D 12
}

D 4
cmp(s1, s2)
char *s1, *s2;
E 4
I 4
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
E 4
{
D 4
	return(strcmp(s1, s2));
E 4
I 4
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "join: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	if (showusage)
		usage();
	exit(1);
	/* NOTREACHED */
E 12
E 4
}
E 1
