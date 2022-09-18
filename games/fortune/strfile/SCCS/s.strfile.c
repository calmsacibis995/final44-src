h53936
s 00005/00005/00425
d D 8.1 93/05/31 17:02:22 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00012/00428
d D 5.12 91/04/08 17:55:16 bostic 12 11
c new copyright; att/bsd/shared
e
s 00002/00002/00438
d D 5.11 89/12/15 11:38:43 bostic 11 10
c sp may be NULL; add endian.h for ntohl(), htonl()
e
s 00002/00000/00438
d D 5.10 89/09/07 09:24:26 bostic 10 9
c seed the random number generator
e
s 00024/00014/00414
d D 5.9 89/09/07 08:08:40 bostic 9 8
c do everything in network order
e
s 00012/00005/00416
d D 5.8 89/09/06 16:51:10 bostic 8 7
c change obscene files to be rotated on disk
e
s 00000/00004/00421
d D 5.7 89/09/06 11:36:58 bostic 7 6
c rip out old debug breakpoint statements
e
s 00002/00002/00423
d D 5.6 89/09/05 20:51:00 bostic 6 5
c make exits consistent
e
s 00064/00092/00361
d D 5.5 89/09/05 19:55:57 bostic 5 4
c add getopt, remove %-, remove -v, lint
e
s 00029/00001/00424
d D 5.4 89/09/05 16:46:55 bostic 4 3
c add Berkeley specific copyright notices
e
s 00006/00007/00419
d D 5.3 89/09/05 16:35:50 bostic 3 2
c remove random number stuff; lint cleanups
e
s 00152/00130/00274
d D 5.2 89/09/05 15:53:14 bostic 2 1
c new distribution from Ken Arnold
e
s 00404/00000/00000
d D 5.1 86/12/09 13:53:41 bostic 1 0
c date and time created 86/12/09 13:53:41 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */
E 2
I 2
D 4
/* $Header: strfile.c,v 1.19 89/05/05 16:07:46 arnold Exp $ */
E 4
I 4
D 12
/*
E 12
I 12
/*-
E 12
D 13
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software contributed to Berkeley by
 * Ken Arnold.
 *
D 12
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
 */

#ifndef lint
D 13
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 13
I 13
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 13
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4
E 2

I 11
# include	<machine/endian.h>
E 11
I 3
# include	<sys/param.h>
D 11
# include	<sys/types.h>
E 11
E 3
D 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

E 2
# include	<stdio.h>
# include	<ctype.h>
I 2
D 3
# include	<sys/types.h>
# include	<sys/param.h>
E 3
E 2
# include	"strfile.h"
I 2
D 3
# include	"random.h"
E 3
E 2

I 2
# ifndef MAXPATHLEN
# define	MAXPATHLEN	1024
# endif	/* MAXPATHLEN */

E 2
/*
 *	This program takes a file composed of strings seperated by
 * lines starting with two consecutive delimiting character (default
 * character is '%') and creates another file which consists of a table
 * describing the file (structure from "strfile.h"), a table of seek
D 5
 * pointers to the start of the strings, and the strings, each terinated
E 5
I 5
 * pointers to the start of the strings, and the strings, each terminated
E 5
 * by a null byte.  Usage:
 *
D 5
 *	% strfile [ - ] [ -cC ] [ -sv ] [ -oir ] sourcefile [ datafile ]
E 5
I 5
D 8
 *	% strfile [-iorsv] [ -cC ] sourcefile [ datafile ]
E 8
I 8
 *	% strfile [-iorsx] [ -cC ] sourcefile [ datafile ]
E 8
E 5
 *
D 5
 *	- - Give a usage summary useful for jogging the memory
E 5
 *	c - Change delimiting character from '%' to 'C'
 *	s - Silent.  Give no summary of data processed at the end of
 *	    the run.
D 8
 *	v - Verbose.  Give summary of data processed.  (Default)
E 8
 *	o - order the strings in alphabetic order
 *	i - if ordering, ignore case 
 *	r - randomize the order of the strings
I 8
 *	x - set rotated bit
E 8
 *
 *		Ken Arnold	Sept. 7, 1978 --
 *
D 5
 *	Added method to indicate dividers.  A "%-" will cause the address
 * to be added to the structure in one of the pointer elements.
 *
 *		Ken Arnold	Nov., 1984 --
 *
E 5
 *	Added ordering options.
 */

# define	TRUE	1
# define	FALSE	0

D 2
# define	DELIM_CH	'-'
E 2
I 2
# define	STORING_PTRS	(Oflag || Rflag)
# define	CHUNKSIZE	512
E 2

I 2
#ifdef lint
# define	ALWAYS	atoi("1")
#else
# define	ALWAYS	1
#endif
# define	ALLOC(ptr,sz)	if (ALWAYS) { \
			if (ptr == NULL) \
				ptr = malloc((unsigned int) (CHUNKSIZE * sizeof *ptr)); \
			else if (((sz) + 1) % CHUNKSIZE == 0) \
				ptr = realloc((void *) ptr, ((unsigned int) ((sz) + CHUNKSIZE) * sizeof *ptr)); \
			if (ptr == NULL) { \
				fprintf(stderr, "out of space\n"); \
				exit(1); \
			} \
		} else

#ifdef NO_VOID
# define	void	char
#endif

E 2
typedef struct {
	char	first;
D 2
	long	pos;
E 2
I 2
	off_t	pos;
E 2
} STR;

char	*Infile		= NULL,		/* input file name */
D 2
	Outfile[100]	= "",		/* output file name */
E 2
I 2
	Outfile[MAXPATHLEN] = "",	/* output file name */
E 2
D 5
	Delimch		= '%',		/* delimiting character */
	*Usage[]	= {		/* usage summary */
       "usage:	strfile [ - ] [ -cC ] [ -sv ] [ -oir ] inputfile [ datafile ]",
       "	- - Give this usage summary",
       "	c - Replace delimiting character with 'C'",
       "	s - Silent.  Give no summary",
       "	v - Verbose.  Give summary.  (default)",
       "	o - order strings alphabetically",
       "	i - ignore case in ordering",
       "	r - randomize the order of the strings",
       "	Default \"datafile\" is inputfile.dat",
D 2
	NULL
E 2
	};
E 5
I 5
	Delimch		= '%';		/* delimiting character */
E 5

int	Sflag		= FALSE;	/* silent run flag */
int	Oflag		= FALSE;	/* ordering flag */
int	Iflag		= FALSE;	/* ignore case flag */
int	Rflag		= FALSE;	/* randomize order flag */
I 8
int	Xflag		= FALSE;	/* set rotated bit */
E 8
D 2
int	Delim		= 0;		/* current delimiter number */
E 2
I 2
D 9
int	Num_pts		= 0;		/* number of pointers/strings */
E 9
I 9
long	Num_pts		= 0;		/* number of pointers/strings */
E 9
E 2

D 2
long	*Seekpts;
E 2
I 2
off_t	*Seekpts;
E 2

FILE	*Sort_1, *Sort_2;		/* pointers for sorting */

STRFILE	Tbl;				/* statistics table */

STR	*Firstch;			/* first chars of each string */

D 2
char	*fgets(), *malloc(), *strcpy(), *strcat();
E 2
I 2
char	*fgets(), *strcpy(), *strcat();
E 2

D 2
long	ftell();
E 2
I 2
void	*malloc(), *realloc();
E 2

I 2
/*
 * main:
 *	Drive the sucker.  There are two main modes -- either we store
 *	the seek pointers, if the table is to be sorted or randomized,
 *	or we write the pointer directly to the file, if we are to stay
 *	in file order.  If the former, we allocate and re-allocate in
 *	CHUNKSIZE blocks; if the latter, we just write each pointer,
 *	and then seek back to the beginning to write in the table.
 */
E 2
main(ac, av)
int	ac;
char	**av;
{
	register char		*sp, dc;
D 2
	register long		*lp;
	register unsigned int	curseek;	/* number of strings */
	register long		*seekpts, li;	/* table of seek pointers */
E 2
	register FILE		*inf, *outf;
I 2
D 9
	register off_t		last_off, length, pos;
E 2
	register int		first;
E 9
I 9
	register off_t		last_off, length, pos, *p;
	register int		first, cnt;
E 9
	register char		*nsp;
	register STR		*fp;
	static char		string[257];

	getargs(ac, av);		/* evalute arguments */
D 2

	/*
	 * initial counting of input file
	 */

E 2
	dc = Delimch;
	if ((inf = fopen(Infile, "r")) == NULL) {
		perror(Infile);
D 6
		exit(-1);
E 6
I 6
		exit(1);
E 6
	}
D 2
	for (curseek = 0; (sp = fgets(string, 256, inf)) != NULL; )
		if (*sp++ == dc && (*sp == dc || *sp == DELIM_CH))
			curseek++;
	curseek++;
E 2

D 2
	/*
	 * save space at begginning of file for tables
	 */

E 2
	if ((outf = fopen(Outfile, "w")) == NULL) {
		perror(Outfile);
D 6
		exit(-1);
E 6
I 6
		exit(1);
E 6
	}
I 2
	if (!STORING_PTRS)
		(void) fseek(outf, sizeof Tbl, 0);
E 2

	/*
D 2
	 * Allocate space for the pointers, adding one to the end so the
	 * length of the final string can be calculated.
E 2
I 2
	 * Write the strings onto the file
E 2
	 */
D 2
	++curseek;
	seekpts = (long *) malloc(sizeof *seekpts * curseek);	/* NOSTRICT */
	if (seekpts == NULL) {
		perror("calloc");
		exit(-1);
	}
	if (Oflag) {
		Firstch = (STR *) malloc(sizeof *Firstch * curseek);
		if (Firstch == NULL) {
			perror("calloc");
			exit(-1);
		}
	}
E 2

D 2
	(void) fseek(outf, (long) (sizeof Tbl + sizeof *seekpts * curseek), 0);
	(void) fseek(inf, (long) 0, 0);		/* goto start of input */

	/*
	 * write the strings onto the file
	 */

E 2
	Tbl.str_longlen = 0;
	Tbl.str_shortlen = (unsigned int) 0xffffffff;
D 2
	lp = seekpts;
E 2
I 2
	Tbl.str_delim = dc;
I 9
	Tbl.str_version = VERSION;
E 9
E 2
	first = Oflag;
D 2
	*seekpts = ftell(outf);
	fp = Firstch;
E 2
I 2
	add_offset(outf, ftell(inf));
	last_off = 0;
E 2
	do {
I 2
D 7
		if (Num_pts > 508)
			atoi("1");
E 7
E 2
		sp = fgets(string, 256, inf);
D 2
		if (sp == NULL ||
		    (*sp == dc && (sp[1] == dc || sp[1] == DELIM_CH))) {
			putc('\0', outf);
			*++lp = ftell(outf);
			li = ftell(outf) - lp[-1] - 1;
			if (Tbl.str_longlen < li)
				Tbl.str_longlen = li;
			if (Tbl.str_shortlen > li)
				Tbl.str_shortlen = li;
			if (sp && sp[1] == DELIM_CH && Delim < MAXDELIMS)
				Tbl.str_delims[Delim++] = lp - seekpts;
E 2
I 2
D 5
		if (sp == NULL || (sp[0] == dc && sp[1] == dc)) {
E 5
I 5
		if (sp == NULL || sp[0] == dc && sp[1] == '\n') {
E 5
			pos = ftell(inf);
D 5
			add_offset(outf, pos);
E 5
D 11
			length = pos - last_off - strlen(sp);
E 11
I 11
			length = pos - last_off - (sp ? strlen(sp) : 0);
E 11
			last_off = pos;
I 5
			if (!length)
				continue;
			add_offset(outf, pos);
E 5
			if (Tbl.str_longlen < length)
				Tbl.str_longlen = length;
			if (Tbl.str_shortlen > length)
				Tbl.str_shortlen = length;
E 2
			first = Oflag;
		}
D 5
		else {
			if (first) {
				for (nsp = sp; !isalnum(*nsp); nsp++)
					continue;
I 2
				ALLOC(Firstch, Num_pts);
				fp = &Firstch[Num_pts - 1];
E 2
				if (Iflag && isupper(*nsp))
					fp->first = tolower(*nsp);
				else
					fp->first = *nsp;
D 2
				fp->pos = *lp;
				fp++;
E 2
I 2
				fp->pos = Seekpts[Num_pts - 1];
E 2
				first = FALSE;
			}
E 5
I 5
		else if (first) {
			for (nsp = sp; !isalnum(*nsp); nsp++)
				continue;
			ALLOC(Firstch, Num_pts);
			fp = &Firstch[Num_pts - 1];
			if (Iflag && isupper(*nsp))
				fp->first = tolower(*nsp);
			else
				fp->first = *nsp;
			fp->pos = Seekpts[Num_pts - 1];
			first = FALSE;
E 5
D 2
			fputs(sp, outf);
E 2
		}
	} while (sp != NULL);

	/*
	 * write the tables in
	 */

	(void) fclose(inf);
D 2
	Tbl.str_numstr = curseek - 1;
E 2
I 2
D 9
	Tbl.str_numstr = Num_pts - 1;
E 9
E 2

	if (Oflag)
D 2
		do_order(seekpts, outf);
E 2
I 2
		do_order();
E 2
	else if (Rflag)
D 2
		randomize(seekpts);
E 2
I 2
		randomize();
E 2

I 8
	if (Xflag)
		Tbl.str_flags |= STR_ROTATED;

E 8
D 2
	(void) fseek(outf, (long) 0, 0);
E 2
I 2
D 9
	(void) fseek(outf, (off_t) 0, 0);
E 2
	(void) fwrite((char *) &Tbl, sizeof Tbl, 1, outf);
D 2
	(void) fwrite((char *) seekpts, sizeof *seekpts, curseek, outf);
E 2
I 2
	if (STORING_PTRS)
		(void) fwrite((char *) Seekpts, sizeof *Seekpts, (int) Num_pts, outf);
E 2
	(void) fclose(outf);

E 9
	if (!Sflag) {
D 2
		printf("\"%s\" converted to \"%s\"\n", Infile, Outfile);
		if (curseek == 0)
E 2
I 2
		printf("\"%s\" created\n", Outfile);
		if (Num_pts == 2)
E 2
			puts("There was 1 string");
		else
D 2
			printf("There were %u strings\n", curseek - 1);
E 2
I 2
D 3
			printf("There were %u strings\n", Num_pts - 1);
E 2
		printf("Longest string: %u byte%s\n", Tbl.str_longlen,
E 3
I 3
			printf("There were %d strings\n", Num_pts - 1);
		printf("Longest string: %lu byte%s\n", Tbl.str_longlen,
E 3
		       Tbl.str_longlen == 1 ? "" : "s");
D 3
		printf("Shortest string: %u byte%s\n", Tbl.str_shortlen,
E 3
I 3
		printf("Shortest string: %lu byte%s\n", Tbl.str_shortlen,
E 3
		       Tbl.str_shortlen == 1 ? "" : "s");
	}
I 9

	(void) fseek(outf, (off_t) 0, 0);
	Tbl.str_version = htonl(Tbl.str_version);
	Tbl.str_numstr = htonl(Num_pts - 1);
	Tbl.str_longlen = htonl(Tbl.str_longlen);
	Tbl.str_shortlen = htonl(Tbl.str_shortlen);
	Tbl.str_flags = htonl(Tbl.str_flags);
	(void) fwrite((char *) &Tbl, sizeof Tbl, 1, outf);
	if (STORING_PTRS) {
		for (p = Seekpts, cnt = Num_pts; cnt--; ++p)
			*p = htonl(*p);
		(void) fwrite((char *) Seekpts, sizeof *Seekpts, (int) Num_pts, outf);
	}
	(void) fclose(outf);
E 9
	exit(0);
I 2
D 9
	/* NOTREACHED */
E 9
E 2
}

/*
 *	This routine evaluates arguments from the command line
 */
D 5
getargs(ac, av)
register int	ac;
register char	**av;
E 5
I 5
getargs(argc, argv)
int	argc;
char	**argv;
E 5
{
D 5
	register char	*sp;
	register int	i;
	register int	bad, j;
E 5
I 5
	extern char	*optarg;
	extern int	optind;
	int	ch;
E 5

D 5
	bad = 0;
	for (i = 1; i < ac; i++)
		if (*av[i] == '-' && av[i][1]) {
			for (sp = &av[i][1]; *sp; sp++)
				switch (*sp) {
				  case 'c': /* new delimiting char */
					if ((Delimch = *++sp) == '\0') {
						--sp;
						Delimch = *av[++i];
					}
D 2
					if (Delimch <= 0 || Delimch > '~' ||
					    Delimch == DELIM_CH) {
E 2
I 2
					if (!isascii(Delimch)) {
E 2
						printf("bad delimiting character: '\\%o\n'",
						       Delimch);
						bad++;
					}
					break;
				  case 's':	/* silent */
					Sflag++;
					break;
				  case 'v':	/* verbose */
					Sflag = 0;
					break;
				  case 'o':	/* order strings */
					Oflag++;
					break;
				  case 'i':	/* ignore case in ordering */
					Iflag++;
					break;
				  case 'r':	/* ignore case in ordering */
					Rflag++;
					break;
				  default:	/* unknown flag */
					bad++;
					printf("bad flag: '%c'\n", *sp);
					break;
				}
E 5
I 5
D 8
	while ((ch = getopt(argc, argv, "c:iors")) != EOF)
E 8
I 8
	while ((ch = getopt(argc, argv, "c:iorsx")) != EOF)
E 8
		switch(ch) {
		case 'c':			/* new delimiting char */
			Delimch = *optarg;
			if (!isascii(Delimch)) {
				printf("bad delimiting character: '\\%o\n'",
				       Delimch);
			}
			break;
		case 'i':			/* ignore case in ordering */
			Iflag++;
			break;
		case 'o':			/* order strings */
			Oflag++;
			break;
D 8
		case 'r':			/* ignore case in ordering */
E 8
I 8
		case 'r':			/* randomize pointers */
E 8
			Rflag++;
			break;
		case 's':			/* silent */
			Sflag++;
			break;
I 8
		case 'x':			/* set the rotated bit */
			Xflag++;
			break;
E 8
		case '?':
		default:
			usage();
E 5
		}
D 5
		else if (*av[i] == '-') {
			for (j = 0; Usage[j]; j++)
				puts(Usage[j]);
			exit(0);
		}
		else if (Infile)
			(void) strcpy(Outfile, av[i]);
		else
			Infile = av[i];
E 5
I 5
	argv += optind;

	if (*argv) {
		Infile = *argv;
		if (*++argv)
			(void) strcpy(Outfile, *argv);
	}
E 5
	if (!Infile) {
D 5
		bad++;
E 5
		puts("No input file name");
I 5
		usage();
E 5
	}
D 5
	if (*Outfile == '\0' && !bad) {
E 5
I 5
	if (*Outfile == '\0') {
E 5
		(void) strcpy(Outfile, Infile);
		(void) strcat(Outfile, ".dat");
	}
D 5
	if (bad) {
		puts("use \"strfile -\" to get usage");
		exit(-1);
	}
E 5
I 5
}

usage()
{
	(void) fprintf(stderr,
D 8
	    "strfile [-iors] [-c char] sourcefile [datafile]\n");
E 8
I 8
	    "strfile [-iorsx] [-c char] sourcefile [datafile]\n");
E 8
	exit(1);
E 5
}

/*
I 2
 * add_offset:
 *	Add an offset to the list, or write it out, as appropriate.
 */
add_offset(fp, off)
FILE	*fp;
off_t	off;
{
D 9
	if (!STORING_PTRS)
		fwrite(&off, 1, sizeof off, fp);
	else {
E 9
I 9
	off_t net;

	if (!STORING_PTRS) {
		net = htonl(off);
		fwrite(&net, 1, sizeof net, fp);
	} else {
E 9
		ALLOC(Seekpts, Num_pts + 1);
		Seekpts[Num_pts] = off;
	}
	Num_pts++;
}

/*
E 2
 * do_order:
 *	Order the strings alphabetically (possibly ignoring case).
 */
D 2
do_order(seekpts, outf)
long	*seekpts;
FILE	*outf;
E 2
I 2
do_order()
E 2
{
	register int	i;
D 2
	register long	*lp;
E 2
I 2
	register off_t	*lp;
E 2
	register STR	*fp;
	extern int	cmp_str();

D 2
	(void) fflush(outf);
	Sort_1 = fopen(Outfile, "r");
	Sort_2 = fopen(Outfile, "r");
	Seekpts = seekpts;
	qsort((char *) Firstch, Tbl.str_numstr, sizeof *Firstch, cmp_str);
E 2
I 2
	Sort_1 = fopen(Infile, "r");
	Sort_2 = fopen(Infile, "r");
	qsort((char *) Firstch, (int) Tbl.str_numstr, sizeof *Firstch, cmp_str);
E 2
	i = Tbl.str_numstr;
D 2
	lp = seekpts;
E 2
I 2
	lp = Seekpts;
E 2
	fp = Firstch;
	while (i--)
		*lp++ = fp++->pos;
	(void) fclose(Sort_1);
	(void) fclose(Sort_2);
	Tbl.str_flags |= STR_ORDERED;
}

/*
 * cmp_str:
 *	Compare two strings in the file
 */
I 2
char *
unctrl(c)
char c;
{
	static char	buf[3];

	if (isprint(c)) {
		buf[0] = c;
		buf[1] = '\0';
	}
	else if (c == 0177) {
		buf[0] = '^';
		buf[1] = '?';
	}
	else {
		buf[0] = '^';
		buf[1] = c + 'A' - 1;
	}
	return buf;
}

E 2
cmp_str(p1, p2)
STR	*p1, *p2;
{
	register int	c1, c2;
I 2
	register int	n1, n2;
E 2

I 2
# define	SET_N(nf,ch)	(nf = (ch == '\n'))
# define	IS_END(ch,nf)	(ch == Delimch && nf)

E 2
	c1 = p1->first;
	c2 = p2->first;
	if (c1 != c2)
		return c1 - c2;

	(void) fseek(Sort_1, p1->pos, 0);
	(void) fseek(Sort_2, p2->pos, 0);

I 2
	n1 = FALSE;
	n2 = FALSE;
E 2
	while (!isalnum(c1 = getc(Sort_1)) && c1 != '\0')
D 2
		continue;
E 2
I 2
		SET_N(n1, c1);
E 2
	while (!isalnum(c2 = getc(Sort_2)) && c2 != '\0')
D 2
		continue;
E 2
I 2
		SET_N(n2, c2);
E 2

D 2
	while (c1 != '\0' && c2 != '\0') {
E 2
I 2
	while (!IS_END(c1, n1) && !IS_END(c2, n2)) {
E 2
		if (Iflag) {
			if (isupper(c1))
				c1 = tolower(c1);
			if (isupper(c2))
				c2 = tolower(c2);
		}
		if (c1 != c2)
			return c1 - c2;
I 2
D 7
		if (c1 == '\n' || c2 == '\n')
			atoi("1");
E 7
		SET_N(n1, c1);
		SET_N(n2, c2);
E 2
		c1 = getc(Sort_1);
		c2 = getc(Sort_2);
	}
I 2
	if (IS_END(c1, n1))
		c1 = 0;
	if (IS_END(c2, n2))
		c2 = 0;
E 2
	return c1 - c2;
}

/*
 * randomize:
 *	Randomize the order of the string table.  We must be careful
 *	not to randomize across delimiter boundaries.  All
 *	randomization is done within each block.
 */
D 2
randomize(seekpts)
register long	*seekpts;
E 2
I 2
randomize()
E 2
{
D 2
	register int	cnt, i, j, start;
	register long	tmp;
	register long	*origsp;
E 2
I 2
	register int	cnt, i;
	register off_t	tmp;
	register off_t	*sp;
	extern time_t	time();
E 2

I 10
	srandom((int)(time((time_t *) NULL) + getpid()));

E 10
	Tbl.str_flags |= STR_RANDOM;
D 2
	srnd(time((long *) NULL) + getpid());
	origsp = seekpts;
	for (j = 0; j <= Delim; j++) {
E 2
I 2
	cnt = Tbl.str_numstr;
E 2

D 2
		/*
		 * get the starting place for the block
		 */
E 2
I 2
	/*
	 * move things around randomly
	 */
E 2

D 2
		if (j == 0)
			start = 0;
		else
			start = Tbl.str_delims[j - 1];

		/*
		 * get the ending point
		 */

		if (j == Delim)
			cnt = Tbl.str_numstr;
		else
			cnt = Tbl.str_delims[j];

		/*
		 * move things around randomly
		 */

		for (seekpts = &origsp[start]; cnt > start; cnt--, seekpts++) {
			i = rnd(cnt - start);
			tmp = seekpts[0];
			seekpts[0] = seekpts[i];
			seekpts[i] = tmp;
		}
E 2
I 2
	for (sp = Seekpts; cnt > 0; cnt--, sp++) {
D 3
		i = rnd((long) cnt);
E 3
I 3
		i = random() % cnt;
E 3
		tmp = sp[0];
		sp[0] = sp[i];
		sp[i] = tmp;
E 2
	}
}
E 1
