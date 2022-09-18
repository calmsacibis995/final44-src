h17738
s 00005/00005/01334
d D 8.1 93/05/31 17:01:41 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00083/00058/01256
d D 5.14 92/06/20 15:49:08 bostic 14 13
c off_t's are quad's, now, prototype the world
e
s 00002/00012/01312
d D 5.13 91/04/08 17:55:13 bostic 13 12
c new copyright; att/bsd/shared
e
s 00005/00004/01319
d D 5.12 89/12/15 11:43:16 bostic 12 11
c overflow in fortune buffer; add "e" to getopt string; add endian.h for
c ntohl and htonl
e
s 00014/00011/01309
d D 5.11 89/09/07 16:20:44 bostic 11 10
c make error messages standard
e
s 00007/00000/01313
d D 5.10 89/09/07 08:09:12 bostic 10 9
c do everything in network order
e
s 00022/00008/01291
d D 5.9 89/09/06 16:51:27 bostic 9 8
c change obscene files to be rotated on disk
e
s 00083/00105/01216
d D 5.8 89/09/05 20:47:40 bostic 8 7
c use getopt, minor lint
e
s 00012/00000/01309
d D 5.7 89/09/05 20:27:06 bostic 7 6
c don't write the disk
e
s 00001/00004/01308
d D 5.6 89/09/05 20:08:45 bostic 6 5
c add pathnames.h
e
s 00026/00001/01283
d D 5.5 89/09/05 16:43:24 bostic 5 4
c add Berkeley specific copyright notices
e
s 00010/00012/01274
d D 5.4 89/09/05 16:35:52 bostic 4 3
c remove random number stuff; lint cleanups
e
s 01174/00140/00112
d D 5.3 89/09/05 15:55:50 bostic 3 2
c new distribution from Ken Arnold
e
s 00009/00002/00243
d D 5.2 86/12/09 14:13:31 bostic 2 1
c bug report 4.3BSD/games/7
e
s 00245/00000/00000
d D 5.1 86/12/09 13:51:27 bostic 1 0
c date and time created 86/12/09 13:51:27 by bostic
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */
E 3
I 3
D 5
/* $Header: fortune.c,v 1.40 88/08/18 11:41:50 arnold Exp $ */
E 5
I 5
D 13
/*
E 13
I 13
/*-
E 13
D 15
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * This code is derived from software contributed to Berkeley by
 * Ken Arnold.
 *
D 13
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
 */

#ifndef lint
D 15
char copyright[] =
"%Z% Copyright (c) 1986 The Regents of the University of California.\n\
 All rights reserved.\n";
E 15
I 15
static char copyright[] =
"%Z% Copyright (c) 1986, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 15
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5
E 3

I 12
D 14
# include	<machine/endian.h>
E 14
E 12
D 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

# include	<sys/types.h>
E 3
D 4
# include	<stdio.h>
D 3
# include	<sys/file.h>
E 3
I 3
# include	<assert.h>
E 4
# include	<sys/param.h>
D 12
# include	<sys/types.h>
E 12
# include	<sys/stat.h>
# include	<sys/dir.h>
I 4
D 14
# include	<stdio.h>
E 14
I 14

# include	<fcntl.h>
E 14
# include	<assert.h>
I 14
# include	<unistd.h>
# include	<stdio.h>
# include	<ctype.h>
# include	<stdlib.h>
# include	<string.h>
E 14
E 4
E 3
# include	"strfile.h"
I 6
# include	"pathnames.h"
E 6
I 3
D 4
# include	"random.h"
E 4
E 3

I 3
D 14
#ifdef	SYSV
# include	<dirent.h>

# define	NO_LOCK
# define	REGCMP
# ifdef	NO_REGEX
#	undef	 NO_REGEX
# endif	/* NO_REGEX */
# define	index	strchr
# define	rindex	strrchr
#endif	/* SYSV */

#ifndef NO_REGEX
# include	<ctype.h>
#endif	/* NO_REGEX */

# ifndef NO_LOCK
# include	<sys/file.h>
# endif	/* NO_LOCK */

# ifndef F_OK
/* codes for access() */
# define	F_OK		0	/* does file exist */
# define	X_OK		1	/* is it executable by caller */
# define	W_OK		2	/* writable by caller */
# define	R_OK		4	/* readable by caller */
# endif	/* F_OK */

E 14
E 3
# define	TRUE	1
# define	FALSE	0
# define	bool	short

# define	MINW	6		/* minimum wait if desired */
# define	CPERS	20		/* # of chars for each sec */
# define	SLEN	160		/* # of chars in short fortune */

D 3
# define	FORTFILE	"/usr/games/lib/fortunes.dat"
E 3
I 3
D 14
# define	POS_UNKNOWN	((unsigned long) -1)	/* pos for file unknown */
E 14
I 14
# define	POS_UNKNOWN	((off_t) -1)	/* pos for file unknown */
E 14
# define	NO_PROB		(-1)		/* no prob specified for file */
E 3
D 6

D 3
bool	Wflag		= FALSE,	/* wait desired after fortune */
	Sflag		= FALSE,	/* short fortune desired */
	Lflag		= FALSE,	/* long fortune desired */
	Oflag		= FALSE,	/* offensive fortunes only */
	Aflag		= FALSE;	/* any fortune allowed */
E 3
I 3
# ifndef FORTDIR
# define	FORTDIR		"/usr/games/lib/fortune"
# endif	/* FORTDIR */
E 6
E 3

D 3
char	*Fortfile	= FORTFILE,	/* fortune database */
	*Usage[]	= {
       "usage:  fortune [ - ] [ -wsloa ] [ file ]",
E 3
I 3
# ifdef DEBUG
# define	DPRINTF(l,x)	if (Debug >= l) fprintf x; else
# undef		NDEBUG
D 14
# else	/* DEBUG */
E 14
I 14
# else
E 14
# define	DPRINTF(l,x)
# define	NDEBUG	1
D 14
# endif	/* DEBUG */
E 14
I 14
# endif
E 14

typedef struct fd {
	int		percent;
	int		fd, datfd;
D 14
	unsigned long	pos;
E 14
I 14
	off_t		pos;
E 14
	FILE		*inf;
	char		*name;
	char		*path;
	char		*datfile, *posfile;
	bool		read_tbl;
	bool		was_pos_file;
	STRFILE		tbl;
	int		num_children;
	struct fd	*child, *parent;
	struct fd	*next, *prev;
} FILEDESC;

bool	Found_one;			/* did we find a match? */
bool	Find_files	= FALSE;	/* just find a list of proper fortune files */
bool	Wait		= FALSE;	/* wait desired after fortune */
bool	Short_only	= FALSE;	/* short fortune desired */
bool	Long_only	= FALSE;	/* long fortune desired */
bool	Offend		= FALSE;	/* offensive fortunes only */
bool	All_forts	= FALSE;	/* any fortune allowed */
bool	Equal_probs	= FALSE;	/* scatter un-allocted prob equally */
#ifndef NO_REGEX
bool	Match		= FALSE;	/* dump fortunes matching a pattern */
#endif
#ifdef DEBUG
bool	Debug = FALSE;			/* print debug messages */
#endif

char	*Fortbuf = NULL;			/* fortune buffer for -m */
D 8
char	*Usage[]	= {
# ifdef	NO_REGEX
       "usage:  fortune [ - ] [ -fwsloa ] [ [N%] file/dir/\"all\" ]",
# else	/* NO_REGEX */
       "usage:  fortune [ - ] [ -fwsloai ] [ -m pattern ] [ [N%] file/dir/\"all\" ]",
# endif	/* NO_REGEX */
E 3
       "	- - give this summary of usage",
D 3
       "	w - have program wait after printing message in order",
       "	    to give time to read",
       "	s - short fortune only",
       "	l - long fortune only",
E 3
I 3
       "	f - list fortune files",
       "	w - wait after printing message in order to give time to read",
       "	s - short fortunes only",
       "	l - long fortunes only",
E 3
       "	o - offensive fortunes only",
D 3
       "	a - any fortune",
       "		Mail suggested fortunes to \"fortune\"",
E 3
I 3
       "	a - any fortune, regular or offensive",
# ifndef NO_REGEX
       "	m - print fortunes which match a pattern",
       "	i - ignore case in matching patterns",
# endif	/* NO_REGEX */
       "		Mail suggested fortunes to \"fortune@berkeley.edu\"",
E 3
	NULL
	};
E 8

D 3
long	Seekpts[2];			/* seek pointers to fortunes */
E 3
I 3
int	Fort_len = 0;
E 3

D 3
FILE	*Inf;				/* input file */
E 3
I 3
off_t	Seekpts[2];			/* seek pointers to fortunes */
E 3

D 3
STRFILE	Tbl;				/* input table */
E 3
I 3
FILEDESC	*File_list = NULL,	/* Head of file list */
		*File_tail = NULL;	/* Tail of file list */
FILEDESC	*Fortfile;		/* Fortune file to use */
E 3

D 3
time_t	time();
E 3
I 3
STRFILE		Noprob_tbl;		/* sum of data for all no prob files */
E 3

I 3
D 14
char	*do_malloc(), *copy(), *off_name();
E 14
I 14
int	 add_dir __P((FILEDESC *));
int	 add_file __P((int,
	    char *, char *, FILEDESC **, FILEDESC **, FILEDESC *));
void	 all_forts __P((FILEDESC *, char *));
char	*copy __P((char *, u_int));
void	 display __P((FILEDESC *));
void	 do_free __P((void *));
void	*do_malloc __P((u_int));
int	 form_file_list __P((char **, int));
int	 fortlen __P((void));
void	 get_fort __P((void));
void	 get_pos __P((FILEDESC *));
void	 get_tbl __P((FILEDESC *));
void	 getargs __P((int, char *[]));
void	 init_prob __P((void));
int	 is_dir __P((char *));
int	 is_fortfile __P((char *, char **, char **, int));
int	 is_off_name __P((char *));
int	 max __P((int, int));
FILEDESC *
	 new_fp __P((void));
char	*off_name __P((char *));
void	 open_dat __P((FILEDESC *));
void	 open_fp __P((FILEDESC *));
FILEDESC *
	 pick_child __P((FILEDESC *));
void	 print_file_list __P((void));
void	 print_list __P((FILEDESC *, int));
void	 sum_noprobs __P((FILEDESC *));
void	 sum_tbl __P((STRFILE *, STRFILE *));
void	 usage __P((void));
void	 zero_tbl __P((STRFILE *));
E 14

D 14
FILEDESC	*pick_child(), *new_fp();

extern char	*malloc(), *index(), *rindex(), *strcpy(), *strcat();

extern time_t	time();

#ifndef NO_REGEX
char	*conv_pat();
E 14
I 14
#ifndef	NO_REGEX
char	*conv_pat __P((char *));
int	 find_matches __P((void));
void	 matches_in_list __P((FILEDESC *));
int	 maxlen_in_list __P((FILEDESC *));
E 14
#endif

#ifndef NO_REGEX
#ifdef REGCMP
# define	RE_COMP(p)	(Re_pat = regcmp(p, NULL))
# define	BAD_COMP(f)	((f) == NULL)
# define	RE_EXEC(p)	regex(Re_pat, (p))

char	*Re_pat;

char	*regcmp(), *regex();
#else
# define	RE_COMP(p)	(p = re_comp(p))
# define	BAD_COMP(f)	((f) != NULL)
# define	RE_EXEC(p)	re_exec(p)

D 14
char	*re_comp();
#ifdef SYSV
char	*re_exec();
#else
int	re_exec();
E 14
#endif
#endif
D 14
#endif
E 14

I 14
int
E 14
E 3
main(ac, av)
int	ac;
char	*av[];
{
I 8
#ifdef	OK_TO_WRITE_DISK
E 8
D 3
	register char	c;
	register int	nchar = 0;
	register int	i;
E 3
I 3
	int	fd;
I 8
#endif	/* OK_TO_WRITE_DISK */
E 8
D 9
	char	line[BUFSIZ];
E 9
E 3

	getargs(ac, av);
D 3
	if ((Inf = fopen(Fortfile, "r+")) == NULL) {
		perror(Fortfile);
		exit(-1);
	}
	fread((char *) &Tbl, sizeof Tbl, 1, Inf);	/* NOSTRICT */
	if (Tbl.str_longlen <= SLEN && Lflag) {
		puts("Sorry, no long strings in this file");
		exit(0);
	}
	if (Tbl.str_shortlen > SLEN && Sflag) {
		puts("Sorry, no short strings in this file");
		exit(0);
	}
E 3

D 3
	/*
	 * initialize the pointer to the first -o fortune if need be.
	 */
	if (Tbl.str_delims[2] == 0)
		Tbl.str_delims[2] = Tbl.str_delims[0];
E 3
I 3
#ifndef NO_REGEX
	if (Match)
		exit(find_matches() != 0);
#endif
E 3

D 2
	do {
E 2
I 2
D 3
	for (;;) {
E 2
		getfort();
D 2
	} while ((Sflag && !is_short()) || (Lflag && !is_long()));
E 2
I 2
		if (Sflag && !is_short())
			continue;
		if (Lflag && !is_long())
			continue;
		break;
	}
E 3
I 3
	init_prob();
D 4
	srnd((long) (time((time_t *) NULL) + getpid()));
E 4
I 4
	srandom((int)(time((time_t *) NULL) + getpid()));
E 4
	do {
		get_fort();
	} while ((Short_only && fortlen() > SLEN) ||
		 (Long_only && fortlen() <= SLEN));
E 3
E 2

D 3
	fseek(Inf, Seekpts[0], 0);
	while (c = getc(Inf)) {
		nchar++;
		putchar(c);
E 3
I 3
D 9
	open_fp(Fortfile);
	(void) fseek(Fortfile->inf, Seekpts[0], 0);
	for (Fort_len = 0; fgets(line, sizeof line, Fortfile->inf) != NULL &&
			   !STR_ENDSTRING(line, Fortfile->tbl);
	     Fort_len++)
		fputs(line, stdout);
	(void) fflush(stdout);
E 9
I 9
	display(Fortfile);
E 9

I 7
#ifdef	OK_TO_WRITE_DISK
E 7
	if ((fd = creat(Fortfile->posfile, 0666)) < 0) {
		perror(Fortfile->posfile);
		exit(1);
E 3
	}
D 3
	fflush(stdout);
	fseek(Inf, 0L, 0);
E 3
#ifdef	LOCK_EX
	/*
	 * if we can, we exclusive lock, but since it isn't very
	 * important, we just punt if we don't have easy locking
	 * available.
	 */
D 3
	flock(fileno(Inf), LOCK_EX);
#endif	LOCK_EX
	fwrite(&Tbl, 1, sizeof Tbl, Inf);
E 3
I 3
	(void) flock(fd, LOCK_EX);
#endif	/* LOCK_EX */
	write(fd, (char *) &Fortfile->pos, sizeof Fortfile->pos);
	if (!Fortfile->was_pos_file)
		(void) chmod(Fortfile->path, 0666);
E 3
#ifdef	LOCK_EX
D 3
	flock(fileno(Inf), LOCK_UN);
#endif	LOCK_EX
	if (Wflag)
		sleep(max((int) nchar / CPERS, MINW));
E 3
I 3
	(void) flock(fd, LOCK_UN);
#endif	/* LOCK_EX */
I 7
#endif	/* OK_TO_WRITE_DISK */
E 7
	if (Wait) {
		if (Fort_len == 0)
			(void) fortlen();
		sleep((unsigned int) max(Fort_len / CPERS, MINW));
	}
E 3
	exit(0);
I 3
	/* NOTREACHED */
I 9
}

I 14
void
E 14
display(fp)
FILEDESC	*fp;
{
	register char	*p, ch;
	char	line[BUFSIZ];

	open_fp(fp);
D 14
	(void) fseek(fp->inf, Seekpts[0], 0);
E 14
I 14
	(void) fseek(fp->inf, (long)Seekpts[0], 0);
E 14
	for (Fort_len = 0; fgets(line, sizeof line, fp->inf) != NULL &&
	    !STR_ENDSTRING(line, fp->tbl); Fort_len++) {
		if (fp->tbl.str_flags & STR_ROTATED)
			for (p = line; ch = *p; ++p)
				if (isupper(ch))
					*p = 'A' + (ch - 'A' + 13) % 26;
				else if (islower(ch))
					*p = 'a' + (ch - 'a' + 13) % 26;
		fputs(line, stdout);
	}
	(void) fflush(stdout);
E 9
E 3
}

/*
D 3
 * is_short:
 *	Return TRUE if fortune is "short".
E 3
I 3
 * fortlen:
 *	Return the length of the fortune.
E 3
 */
I 14
int
E 14
D 3
is_short()
E 3
I 3
fortlen()
E 3
{
	register int	nchar;
I 3
	char		line[BUFSIZ];
E 3

D 3
	if (!(Tbl.str_flags & (STR_RANDOM | STR_ORDERED)))
		return (Seekpts[1] - Seekpts[0] <= SLEN);
	fseek(Inf, Seekpts[0], 0);
	nchar = 0;
	while (getc(Inf))
		nchar++;
	return (nchar <= SLEN);
E 3
I 3
	if (!(Fortfile->tbl.str_flags & (STR_RANDOM | STR_ORDERED)))
		nchar = (Seekpts[1] - Seekpts[0] <= SLEN);
	else {
		open_fp(Fortfile);
D 14
		(void) fseek(Fortfile->inf, Seekpts[0], 0);
E 14
I 14
		(void) fseek(Fortfile->inf, (long)Seekpts[0], 0);
E 14
		nchar = 0;
		while (fgets(line, sizeof line, Fortfile->inf) != NULL &&
		       !STR_ENDSTRING(line, Fortfile->tbl))
			nchar += strlen(line);
	}
	Fort_len = nchar;
	return nchar;
E 3
}

/*
D 3
 * is_long:
 *	Return TRUE if fortune is "long".
 */
is_long()
{
	register int	nchar;

	if (!(Tbl.str_flags & (STR_RANDOM | STR_ORDERED)))
		return (Seekpts[1] - Seekpts[0] > SLEN);
	fseek(Inf, Seekpts[0], 0);
	nchar = 0;
	while (getc(Inf))
		nchar++;
	return (nchar > SLEN);
}

/*
E 3
 *	This routine evaluates the arguments on the command line
 */
I 14
void
E 14
D 8
getargs(ac, av)
register int	ac;
register char	*av[];
E 8
I 8
getargs(argc, argv)
register int	argc;
register char	**argv;
E 8
{
D 8
	register int	i;
	register char	*sp;
	register int	j;
D 3
	register short	bad = 0;
E 3
I 3
	register short	bad;
E 8
	register int	ignore_case;
# ifndef NO_REGEX
	register char	*pat;
# endif	/* NO_REGEX */
I 8
	extern char *optarg;
	extern int optind;
	int ch;
E 8
E 3

I 3
	ignore_case = FALSE;
D 8
	bad = FALSE;
E 8
	pat = NULL;
E 3
D 8
	for (i = 1; i < ac; i++)  {
D 3
		if (av[i][0] != '-') {
			setuid(getuid());
			setgid(getgid());
			Fortfile = av[i];
		}
E 3
I 3
		if (av[i][0] != '-')
E 8
I 8

# ifdef DEBUG
D 12
	while ((ch = getopt(argc, argv, "aDfilm:osw")) != EOF)
E 12
I 12
	while ((ch = getopt(argc, argv, "aDefilm:osw")) != EOF)
E 12
#else
D 12
	while ((ch = getopt(argc, argv, "afilm:osw")) != EOF)
E 12
I 12
	while ((ch = getopt(argc, argv, "aefilm:osw")) != EOF)
E 12
#endif /* DEBUG */
		switch(ch) {
		case 'a':		/* any fortune */
			All_forts++;
E 8
			break;
E 3
D 8
		else if (av[i][1] == '\0') {
			j = 0;
			while (Usage[j] != NULL)
				puts(Usage[j++]);
			exit(0);
			/* NOTREACHED */
		}
		else
			for (sp = &av[i][1]; *sp != '\0'; sp++)
				switch (*sp) {
I 3
				  case 'f':	/* find fortune files */
					Find_files++;
					break;
E 3
				  case 'w':	/* give time to read */
D 3
					Wflag++;
E 3
I 3
					Wait++;
E 3
					break;
				  case 's':	/* short ones only */
D 3
					Sflag++;
I 2
					Lflag = 0;
E 3
I 3
					Short_only++;
					Long_only = FALSE;
E 3
E 2
					break;
				  case 'l':	/* long ones only */
D 3
					Lflag++;
I 2
					Sflag = 0;
E 3
I 3
					Long_only++;
					Short_only = FALSE;
E 3
E 2
					break;
				  case 'o':	/* offensive ones only */
D 3
					Oflag++;
E 3
I 3
					Offend++;
E 3
					break;
				  case 'a':	/* any fortune */
D 3
					Aflag++;
					/*
					 * initialize the random number
					 * generator; throw away the first
					 * few numbers to avoid any non-
					 * randomness in startup
					 */
					srnd(time(NULL) + getpid());
					for (j = 0; j < 20; j++)
						(void) rnd(100);
E 3
I 3
					All_forts++;
E 3
					break;
I 3
				  case 'm':	/* dump out the fortunes */
# ifdef	NO_REGEX
				  case 'i':
					fprintf(stderr,
						"can't match fortunes on this system (Sorry)\n");
					bad++;
# else	/* NO_REGEX */
					Match++;
					if (sp[1]) {
						pat = ++sp;
						while (*sp)
							sp++;
					}
					else if (i + 1 < ac)
						pat = av[++i];
					else {
						fprintf(stderr,
							"must give pattern\n");
						bad++;
						break;
					}
					break;
				  case 'i':
					ignore_case++;
					break;
				  case 'e':
					Equal_probs++;
					break;
E 8
# ifdef DEBUG
D 8
				  case 'D':
					Debug++;
					break;
E 8
I 8
		case 'D':
			Debug++;
			break;
E 8
# endif /* DEBUG */
I 8
		case 'e':
			Equal_probs++;	/* scatter un-allocted prob equally */
			break;
		case 'f':		/* find fortune files */
			Find_files++;
			break;
		case 'l':		/* long ones only */
			Long_only++;
			Short_only = FALSE;
			break;
		case 'o':		/* offensive ones only */
			Offend++;
			break;
		case 's':		/* short ones only */
			Short_only++;
			Long_only = FALSE;
			break;
		case 'w':		/* give time to read */
			Wait++;
			break;
# ifdef	NO_REGEX
		case 'i':			/* case-insensitive match */
		case 'm':			/* dump out the fortunes */
			(void) fprintf(stderr,
			    "fortune: can't match fortunes on this system (Sorry)\n");
			exit(0);
# else	/* NO_REGEX */
		case 'm':			/* dump out the fortunes */
			Match++;
			pat = optarg;
			break;
		case 'i':			/* case-insensitive match */
			ignore_case++;
			break;
E 8
# endif	/* NO_REGEX */
E 3
D 8
				  default:
D 3
					printf("unknown flag: '%c'\n", *sp);
E 3
I 3
					fprintf(stderr, "unknown flag: '%c'\n",
						*sp);
E 3
					bad++;
					break;
				}
	}
I 3
	if (!bad && !form_file_list(&av[i], ac - i))
E 8
I 8
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (!form_file_list(argv, argc))
E 8
		exit(1);	/* errors printed through form_file_list() */
#ifdef DEBUG
	if (Debug >= 1)
		print_file_list();
#endif /* DEBUG */
	if (Find_files) {
		print_file_list();
		exit(0);
	}

# ifndef NO_REGEX
	if (pat != NULL) {
		if (ignore_case)
			pat = conv_pat(pat);
		if (BAD_COMP(RE_COMP(pat))) {
#ifndef REGCMP
			fprintf(stderr, "%s\n", pat);
#else	/* REGCMP */
			fprintf(stderr, "bad pattern: %s\n", pat);
#endif	/* REGCMP */
D 8
			bad++;
E 8
		}
	}
# endif	/* NO_REGEX */
D 8

E 3
	if (bad) {
		printf("use \"%s -\" to get usage\n", av[0]);
		exit(-1);
	}
E 8
}

/*
D 3
 * getfort:
 *	Get the fortune data file's seek pointer for the next fortune.
E 3
I 3
 * form_file_list:
 *	Form the file list from the file specifications.
E 3
 */
I 14
int
E 14
D 3
getfort()
E 3
I 3
form_file_list(files, file_cnt)
register char	**files;
register int	file_cnt;
E 3
{
D 3
	register int	fortune;
E 3
I 3
	register int	i, percent;
	register char	*sp;
E 3

I 3
	if (file_cnt == 0)
		if (Find_files)
			return add_file(NO_PROB, FORTDIR, NULL, &File_list,
					&File_tail, NULL);
		else
			return add_file(NO_PROB, "fortunes", FORTDIR,
					&File_list, &File_tail, NULL);
	for (i = 0; i < file_cnt; i++) {
		percent = NO_PROB;
		if (!isdigit(files[i][0]))
			sp = files[i];
		else {
			percent = 0;
			for (sp = files[i]; isdigit(*sp); sp++)
				percent = percent * 10 + *sp - '0';
			if (percent > 100) {
				fprintf(stderr, "percentages must be <= 100\n");
				return FALSE;
			}
			if (*sp == '.') {
				fprintf(stderr, "percentages must be integers\n");
				return FALSE;
			}
			/*
			 * If the number isn't followed by a '%', then
			 * it was not a percentage, just the first part
			 * of a file name which starts with digits.
			 */
			if (*sp != '%') {
				percent = NO_PROB;
				sp = files[i];
			}
			else if (*++sp == '\0') {
				if (++i >= file_cnt) {
					fprintf(stderr, "percentages must precede files\n");
					return FALSE;
				}
				sp = files[i];
			}
		}
		if (strcmp(sp, "all") == 0)
			sp = FORTDIR;
		if (!add_file(percent, sp, NULL, &File_list, &File_tail, NULL))
			return FALSE;
	}
	return TRUE;
}

/*
 * add_file:
 *	Add a file to the file list.
 */
I 14
int
E 14
add_file(percent, file, dir, head, tail, parent)
int		percent;
register char	*file;
char		*dir;
FILEDESC	**head, **tail;
FILEDESC	*parent;
{
	register FILEDESC	*fp;
	register int		fd;
	register char		*path, *offensive;
D 4
	register int		len;
E 4
	register bool		was_malloc;
	register bool		isdir;

	if (dir == NULL) {
		path = file;
		was_malloc = FALSE;
	}
	else {
		path = do_malloc((unsigned int) (strlen(dir) + strlen(file) + 2));
		(void) strcat(strcat(strcpy(path, dir), "/"), file);
		was_malloc = TRUE;
	}
	if ((isdir = is_dir(path)) && parent != NULL) {
		if (was_malloc)
			free(path);
		return FALSE;	/* don't recurse */
	}
	offensive = NULL;
	if (!isdir && parent == NULL && (All_forts || Offend) &&
	    !is_off_name(path)) {
		offensive = off_name(path);
		was_malloc = TRUE;
		if (Offend) {
			if (was_malloc)
				free(path);
			path = offensive;
			file = off_name(file);
		}
	}

	DPRINTF(1, (stderr, "adding file \"%s\"\n", path));
over:
	if ((fd = open(path, 0)) < 0) {
		/*
		 * This is a sneak.  If the user said -a, and if the
		 * file we're given isn't a file, we check to see if
		 * there is a -o version.  If there is, we treat it as
		 * if *that* were the file given.  We only do this for
		 * individual files -- if we're scanning a directory,
		 * we'll pick up the -o file anyway.
		 */
		if (All_forts && offensive != NULL) {
			path = offensive;
			if (was_malloc)
				free(path);
			offensive = NULL;
			was_malloc = TRUE;
			DPRINTF(1, (stderr, "\ttrying \"%s\"\n", path));
			file = off_name(file);
			goto over;
		}
		if (dir == NULL && file[0] != '/')
			return add_file(percent, file, FORTDIR, head, tail,
					parent);
		if (parent == NULL)
			perror(path);
		if (was_malloc)
			free(path);
		return FALSE;
	}

	DPRINTF(2, (stderr, "path = \"%s\"\n", path));

	fp = new_fp();
	fp->fd = fd;
	fp->percent = percent;
	fp->name = file;
	fp->path = path;
	fp->parent = parent;

	if ((isdir && !add_dir(fp)) ||
	    (!isdir &&
	     !is_fortfile(path, &fp->datfile, &fp->posfile, (parent != NULL))))
	{
		if (parent == NULL)
			fprintf(stderr,
				"fortune:%s not a fortune file or directory\n",
				path);
		free((char *) fp);
		if (was_malloc)
			free(path);
		do_free(fp->datfile);
		do_free(fp->posfile);
		do_free(offensive);
		return FALSE;
	}
E 3
	/*
D 3
	 * Make sure all values are in range.
E 3
I 3
	 * If the user said -a, we need to make this node a pointer to
	 * both files, if there are two.  We don't need to do this if
	 * we are scanning a directory, since the scan will pick up the
	 * -o file anyway.
E 3
	 */
I 3
	if (All_forts && parent == NULL && !is_off_name(path))
		all_forts(fp, offensive);
	if (*head == NULL)
		*head = *tail = fp;
	else if (fp->percent == NO_PROB) {
		(*tail)->next = fp;
		fp->prev = *tail;
		*tail = fp;
	}
	else {
		(*head)->prev = fp;
		fp->next = *head;
		*head = fp;
	}
I 7
#ifdef	OK_TO_WRITE_DISK
E 7
	fp->was_pos_file = (access(fp->posfile, W_OK) >= 0);
I 7
#endif	/* OK_TO_WRITE_DISK */
E 7
E 3

D 3
	if (Tbl.str_delims[1] >= Tbl.str_delims[0])
		Tbl.str_delims[1] = 0;
	if (Tbl.str_delims[2] >= Tbl.str_numstr)
		Tbl.str_delims[2] = Tbl.str_delims[0];
E 3
I 3
	return TRUE;
}
E 3

D 3
	if (Aflag) {
		if (rnd(Tbl.str_numstr) < Tbl.str_delims[0])
			fortune = Tbl.str_delims[1]++;
E 3
I 3
/*
 * new_fp:
 *	Return a pointer to an initialized new FILEDESC.
 */
FILEDESC *
new_fp()
{
	register FILEDESC	*fp;

	fp = (FILEDESC *) do_malloc(sizeof *fp);
	fp->datfd = -1;
	fp->pos = POS_UNKNOWN;
	fp->inf = NULL;
	fp->fd = -1;
	fp->percent = NO_PROB;
	fp->read_tbl = FALSE;
	fp->next = NULL;
	fp->prev = NULL;
	fp->child = NULL;
	fp->parent = NULL;
	fp->datfile = NULL;
	fp->posfile = NULL;
	return fp;
}

/*
 * off_name:
 *	Return a pointer to the offensive version of a file of this name.
 */
char *
off_name(file)
char	*file;
{
	char	*new;

	new = copy(file, (unsigned int) (strlen(file) + 2));
	return strcat(new, "-o");
}

/*
 * is_off_name:
 *	Is the file an offensive-style name?
 */
I 14
int
E 14
is_off_name(file)
char	*file;
{
	int	len;

	len = strlen(file);
	return (len >= 3 && file[len - 2] == '-' && file[len - 1] == 'o');
}

/*
 * all_forts:
 *	Modify a FILEDESC element to be the parent of two children if
 *	there are two children to be a parent of.
 */
I 14
void
E 14
all_forts(fp, offensive)
register FILEDESC	*fp;
char			*offensive;
{
	register char		*sp;
	register FILEDESC	*scene, *obscene;
	register int		fd;
	auto char		*datfile, *posfile;

	if (fp->child != NULL)	/* this is a directory, not a file */
		return;
	if (!is_fortfile(offensive, &datfile, &posfile, FALSE))
		return;
	if ((fd = open(offensive, 0)) < 0)
		return;
	DPRINTF(1, (stderr, "adding \"%s\" because of -a\n", offensive));
	scene = new_fp();
	obscene = new_fp();
	*scene = *fp;

	fp->num_children = 2;
	fp->child = scene;
	scene->next = obscene;
	obscene->next = NULL;
	scene->child = obscene->child = NULL;
	scene->parent = obscene->parent = fp;

	fp->fd = -1;
	scene->percent = obscene->percent = NO_PROB;

	obscene->fd = fd;
	obscene->inf = NULL;
	obscene->path = offensive;
	if ((sp = rindex(offensive, '/')) == NULL)
		obscene->name = offensive;
	else
		obscene->name = ++sp;
	obscene->datfile = datfile;
	obscene->posfile = posfile;
	obscene->read_tbl = FALSE;
I 7
#ifdef	OK_TO_WRITE_DISK
E 7
	obscene->was_pos_file = (access(obscene->posfile, W_OK) >= 0);
I 7
#endif	/* OK_TO_WRITE_DISK */
E 7
}

/*
 * add_dir:
 *	Add the contents of an entire directory.
 */
I 14
int
E 14
add_dir(fp)
register FILEDESC	*fp;
{
	register DIR		*dir;
#ifdef SYSV
	register struct dirent	*dirent;	/* NIH, of course! */
#else
	register struct direct	*dirent;
#endif
	auto FILEDESC		*tailp;
	auto char		*name;

	(void) close(fp->fd);
	fp->fd = -1;
	if ((dir = opendir(fp->path)) == NULL) {
		perror(fp->path);
		return FALSE;
	}
	tailp = NULL;
	DPRINTF(1, (stderr, "adding dir \"%s\"\n", fp->path));
	fp->num_children = 0;
	while ((dirent = readdir(dir)) != NULL) {
		if (dirent->d_namlen == 0)
			continue;
		name = copy(dirent->d_name, dirent->d_namlen);
		if (add_file(NO_PROB, name, fp->path, &fp->child, &tailp, fp))
			fp->num_children++;
E 3
		else
D 3
			fortune = Tbl.str_delims[2]++;
E 3
I 3
			free(name);
E 3
	}
D 3
	else if (Oflag)
		fortune = Tbl.str_delims[2]++;
E 3
I 3
	if (fp->num_children == 0) {
D 11
		fprintf(stderr, "fortune:%s:No fortune files in directory\n", fp->path);
E 11
I 11
		(void) fprintf(stderr,
		    "fortune: %s: No fortune files in directory.\n", fp->path);
E 11
		return FALSE;
	}
	return TRUE;
}

/*
 * is_dir:
 *	Return TRUE if the file is a directory, FALSE otherwise.
 */
I 14
int
E 14
is_dir(file)
char	*file;
{
	auto struct stat	sbuf;

	if (stat(file, &sbuf) < 0)
		return FALSE;
	return (sbuf.st_mode & S_IFDIR);
}

/*
 * is_fortfile:
 *	Return TRUE if the file is a fortune database file.  We try and
 *	exclude files without reading them if possible to avoid
 *	overhead.  Files which start with ".", or which have "illegal"
 *	suffixes, as contained in suflist[], are ruled out.
 */
I 8
/* ARGSUSED */
I 14
int
E 14
E 8
is_fortfile(file, datp, posp, check_for_offend)
D 14
char	*file;
char	**datp, **posp;
E 14
I 14
char	*file, **datp, **posp;
E 14
int	check_for_offend;
{
	register int	i;
	register char	*sp;
	register char	*datfile;
	static char	*suflist[] = {	/* list of "illegal" suffixes" */
				"dat", "pos", "c", "h", "p", "i", "f",
				"pas", "ftn", "ins.c", "ins,pas",
				"ins.ftn", "sml",
				NULL
			};

	DPRINTF(2, (stderr, "is_fortfile(%s) returns ", file));

	/*
	 * Preclude any -o files for offendable people, and any non -o
	 * files for completely offensive people.
	 */
	if (check_for_offend && !All_forts) {
		i = strlen(file);
		if (Offend ^ (file[i - 2] == '-' && file[i - 1] == 'o'))
			return FALSE;
	}

	if ((sp = rindex(file, '/')) == NULL)
		sp = file;
E 3
	else
D 3
		fortune = Tbl.str_delims[1]++;
E 3
I 3
		sp++;
	if (*sp == '.') {
		DPRINTF(2, (stderr, "FALSE (file starts with '.')\n"));
		return FALSE;
	}
	if ((sp = rindex(sp, '.')) != NULL) {
		sp++;
		for (i = 0; suflist[i] != NULL; i++)
			if (strcmp(sp, suflist[i]) == 0) {
				DPRINTF(2, (stderr, "FALSE (file has suffix \".%s\")\n", sp));
				return FALSE;
			}
	}
E 3

D 3
	fseek(Inf, (long)(sizeof Seekpts[0]) * fortune + sizeof Tbl, 0);
	fread((char *) Seekpts, (sizeof Seekpts[0]), 2, Inf);
E 3
I 3
	datfile = copy(file, (unsigned int) (strlen(file) + 4)); /* +4 for ".dat" */
	strcat(datfile, ".dat");
	if (access(datfile, R_OK) < 0) {
		free(datfile);
		DPRINTF(2, (stderr, "FALSE (no \".dat\" file)\n"));
		return FALSE;
	}
	if (datp != NULL)
		*datp = datfile;
	else
		free(datfile);
I 7
#ifdef	OK_TO_WRITE_DISK
E 7
	if (posp != NULL) {
		*posp = copy(file, (unsigned int) (strlen(file) + 4)); /* +4 for ".dat" */
		(void) strcat(*posp, ".pos");
	}
I 7
#endif	/* OK_TO_WRITE_DISK */
E 7
	DPRINTF(2, (stderr, "TRUE\n"));
	return TRUE;
E 3
}

I 3
/*
 * copy:
 *	Return a malloc()'ed copy of the string
 */
char *
copy(str, len)
char		*str;
unsigned int	len;
{
	char	*new, *sp;

	new = do_malloc(len + 1);
	sp = new;
	do {
		*sp++ = *str;
	} while (*str++);
	return new;
}

/*
 * do_malloc:
 *	Do a malloc, checking for NULL return.
 */
D 14
char *
E 14
I 14
void *
E 14
do_malloc(size)
unsigned int	size;
{
D 14
	char	*new;
E 14
I 14
	void	*new;
E 14

	if ((new = malloc(size)) == NULL) {
D 11
		fprintf(stderr, "fortune:Out of space\n");
E 11
I 11
		(void) fprintf(stderr, "fortune: out of memory.\n");
E 11
		exit(1);
	}
	return new;
}

/*
 * do_free:
 *	Free malloc'ed space, if any.
 */
I 14
void
E 14
do_free(ptr)
D 14
char	*ptr;
E 14
I 14
void	*ptr;
E 14
{
	if (ptr != NULL)
		free(ptr);
}

/*
 * init_prob:
 *	Initialize the fortune probabilities.
 */
I 14
void
E 14
init_prob()
{
	register FILEDESC	*fp, *last;
	register int		percent, num_noprob, frac;

	/*
	 * Distribute the residual probability (if any) across all
	 * files with unspecified probability (i.e., probability of 0)
	 * (if any).
	 */

	percent = 0;
	num_noprob = 0;
	for (fp = File_tail; fp != NULL; fp = fp->prev)
		if (fp->percent == NO_PROB) {
			num_noprob++;
			if (Equal_probs)
				last = fp;
		}
		else
			percent += fp->percent;
	DPRINTF(1, (stderr, "summing probabilities:%d%% with %d NO_PROB's",
		    percent, num_noprob));
	if (percent > 100) {
D 11
		fprintf(stderr, "fortune:Probabilities sum to %d%%!\n",
			percent);
E 11
I 11
		(void) fprintf(stderr,
		    "fortune: probabilities sum to %d%%!\n", percent);
E 11
		exit(1);
	}
	else if (percent < 100 && num_noprob == 0) {
D 11
		fprintf(stderr,
			"fortune:No place to put residual probability (%d%%)\n",
			percent);
E 11
I 11
		(void) fprintf(stderr,
		    "fortune: no place to put residual probability (%d%%)\n",
		    percent);
E 11
		exit(1);
	}
	else if (percent == 100 && num_noprob != 0) {
D 11
		fprintf(stderr,
D 4
			"fortune:No probability left to put in residual files\n",
			percent);
E 4
I 4
		    "fortune:No probability left to put in residual files\n");
E 11
I 11
		(void) fprintf(stderr,
		    "fortune: no probability left to put in residual files\n");
E 11
E 4
		exit(1);
	}
	percent = 100 - percent;
	if (Equal_probs)
		if (num_noprob != 0) {
			if (num_noprob > 1) {
				frac = percent / num_noprob;
				DPRINTF(1, (stderr, ", frac = %d%%", frac));
				for (fp = File_list; fp != last; fp = fp->next)
					if (fp->percent == NO_PROB) {
						fp->percent = frac;
						percent -= frac;
					}
			}
			last->percent = percent;
			DPRINTF(1, (stderr, ", residual = %d%%", percent));
		}
	else {
		DPRINTF(1, (stderr,
			    ", %d%% distributed over remaining fortunes\n",
			    percent));
	}
	DPRINTF(1, (stderr, "\n"));

#ifdef DEBUG
	if (Debug >= 1)
		print_file_list();
#endif
}

/*
 * get_fort:
 *	Get the fortune data file's seek pointer for the next fortune.
 */
I 14
void
E 14
get_fort()
{
	register FILEDESC	*fp;
	register int		choice;
I 4
D 14
	long random();
E 14
E 4

	if (File_list->next == NULL || File_list->percent == NO_PROB)
		fp = File_list;
	else {
D 4
		choice = rnd(100L);
E 4
I 4
		choice = random() % 100;
E 4
		DPRINTF(1, (stderr, "choice = %d\n", choice));
		for (fp = File_list; fp->percent != NO_PROB; fp = fp->next)
			if (choice < fp->percent)
				break;
			else {
				choice -= fp->percent;
				DPRINTF(1, (stderr,
					    "    skip \"%s\", %d%% (choice = %d)\n",
					    fp->name, fp->percent, choice));
			}
			DPRINTF(1, (stderr,
				    "using \"%s\", %d%% (choice = %d)\n",
				    fp->name, fp->percent, choice));
	}
	if (fp->percent != NO_PROB)
		get_tbl(fp);
	else {
		if (fp->next != NULL) {
			sum_noprobs(fp);
D 4
			choice = rnd((long) Noprob_tbl.str_numstr);
E 4
I 4
			choice = random() % Noprob_tbl.str_numstr;
E 4
			DPRINTF(1, (stderr, "choice = %d (of %d) \n", choice,
				    Noprob_tbl.str_numstr));
			while (choice >= fp->tbl.str_numstr) {
				choice -= fp->tbl.str_numstr;
				fp = fp->next;
				DPRINTF(1, (stderr,
					    "    skip \"%s\", %d (choice = %d)\n",
					    fp->name, fp->tbl.str_numstr,
					    choice));
			}
			DPRINTF(1, (stderr, "using \"%s\", %d\n", fp->name,
				    fp->tbl.str_numstr));
		}
		get_tbl(fp);
	}
	if (fp->child != NULL) {
		DPRINTF(1, (stderr, "picking child\n"));
		fp = pick_child(fp);
	}
	Fortfile = fp;
	get_pos(fp);
	open_dat(fp);
	(void) lseek(fp->datfd,
		     (off_t) (sizeof fp->tbl + fp->pos * sizeof Seekpts[0]), 0);
	read(fp->datfd, Seekpts, sizeof Seekpts);
I 10
	Seekpts[0] = ntohl(Seekpts[0]);
	Seekpts[1] = ntohl(Seekpts[1]);
E 10
}

/*
 * pick_child
 *	Pick a child from a chosen parent.
 */
FILEDESC *
pick_child(parent)
FILEDESC	*parent;
{
	register FILEDESC	*fp;
	register int		choice;

	if (Equal_probs) {
D 4
		choice = rnd((long) parent->num_children);
E 4
I 4
		choice = random() % parent->num_children;
E 4
		DPRINTF(1, (stderr, "    choice = %d (of %d)\n",
			    choice, parent->num_children));
		for (fp = parent->child; choice--; fp = fp->next)
			continue;
		DPRINTF(1, (stderr, "    using %s\n", fp->name));
		return fp;
	}
	else {
		get_tbl(parent);
D 4
		choice = rnd((long) parent->tbl.str_numstr);
E 4
I 4
		choice = random() % parent->tbl.str_numstr;
E 4
		DPRINTF(1, (stderr, "    choice = %d (of %d)\n",
			    choice, parent->tbl.str_numstr));
		for (fp = parent->child; choice >= fp->tbl.str_numstr;
		     fp = fp->next) {
			choice -= fp->tbl.str_numstr;
			DPRINTF(1, (stderr, "\tskip %s, %d (choice = %d)\n",
				    fp->name, fp->tbl.str_numstr, choice));
		}
		DPRINTF(1, (stderr, "    using %s, %d\n", fp->name,
			    fp->tbl.str_numstr));
		return fp;
	}
}

/*
 * sum_noprobs:
 *	Sum up all the noprob probabilities, starting with fp.
 */
I 14
void
E 14
sum_noprobs(fp)
register FILEDESC	*fp;
{
	static bool	did_noprobs = FALSE;

	if (did_noprobs)
		return;
	zero_tbl(&Noprob_tbl);
	while (fp != NULL) {
		get_tbl(fp);
		sum_tbl(&Noprob_tbl, &fp->tbl);
		fp = fp->next;
	}
	did_noprobs = TRUE;
}

I 14
int
E 14
E 3
max(i, j)
register int	i, j;
{
	return (i >= j ? i : j);
}
I 3

/*
 * open_fp:
 *	Assocatiate a FILE * with the given FILEDESC.
 */
I 14
void
E 14
open_fp(fp)
FILEDESC	*fp;
{
	if (fp->inf == NULL && (fp->inf = fdopen(fp->fd, "r")) == NULL) {
		perror(fp->path);
		exit(1);
	}
}

/*
 * open_dat:
 *	Open up the dat file if we need to.
 */
I 14
void
E 14
open_dat(fp)
FILEDESC	*fp;
{
	if (fp->datfd < 0 && (fp->datfd = open(fp->datfile, 0)) < 0) {
		perror(fp->datfile);
		exit(1);
	}
}

/*
 * get_pos:
 *	Get the position from the pos file, if there is one.  If not,
 *	return a random number.
 */
I 14
void
E 14
get_pos(fp)
FILEDESC	*fp;
{
I 8
#ifdef	OK_TO_WRITE_DISK
E 8
	int	fd;
I 8
#endif /* OK_TO_WRITE_DISK */
E 8

	assert(fp->read_tbl);
	if (fp->pos == POS_UNKNOWN) {
I 7
#ifdef	OK_TO_WRITE_DISK
E 7
		if ((fd = open(fp->posfile, 0)) < 0 ||
		    read(fd, &fp->pos, sizeof fp->pos) != sizeof fp->pos)
D 4
			fp->pos = rnd(fp->tbl.str_numstr);
E 4
I 4
			fp->pos = random() % fp->tbl.str_numstr;
E 4
		else if (fp->pos >= fp->tbl.str_numstr)
			fp->pos %= fp->tbl.str_numstr;
		if (fd >= 0)
			(void) close(fd);
I 7
#else
		fp->pos = random() % fp->tbl.str_numstr;
#endif /* OK_TO_WRITE_DISK */
E 7
	}
	if (++(fp->pos) >= fp->tbl.str_numstr)
		fp->pos -= fp->tbl.str_numstr;
D 14
	DPRINTF(1, (stderr, "pos for %s is %d\n", fp->name, fp->pos));
E 14
I 14
	DPRINTF(1, (stderr, "pos for %s is %qd\n", fp->name, fp->pos));
E 14
}

/*
 * get_tbl:
 *	Get the tbl data file the datfile.
 */
I 14
void
E 14
get_tbl(fp)
FILEDESC	*fp;
{
	auto int		fd;
	register FILEDESC	*child;

	if (fp->read_tbl)
		return;
	if (fp->child == NULL) {
		if ((fd = open(fp->datfile, 0)) < 0) {
			perror(fp->datfile);
			exit(1);
		}
		if (read(fd, (char *) &fp->tbl, sizeof fp->tbl) != sizeof fp->tbl) {
D 11
			fprintf(stderr, "fortune:%s corrupted\n", fp->path);
E 11
I 11
			(void)fprintf(stderr,
			    "fortune: %s corrupted\n", fp->path);
E 11
			exit(1);
		}
I 10
		/* fp->tbl.str_version = ntohl(fp->tbl.str_version); */
		fp->tbl.str_numstr = ntohl(fp->tbl.str_numstr);
		fp->tbl.str_longlen = ntohl(fp->tbl.str_longlen);
		fp->tbl.str_shortlen = ntohl(fp->tbl.str_shortlen);
		fp->tbl.str_flags = ntohl(fp->tbl.str_flags);
E 10
		(void) close(fd);
	}
	else {
		zero_tbl(&fp->tbl);
		for (child = fp->child; child != NULL; child = child->next) {
			get_tbl(child);
			sum_tbl(&fp->tbl, &child->tbl);
		}
	}
	fp->read_tbl = TRUE;
}

/*
 * zero_tbl:
 *	Zero out the fields we care about in a tbl structure.
 */
I 14
void
E 14
zero_tbl(tp)
register STRFILE	*tp;
{
	tp->str_numstr = 0;
	tp->str_longlen = 0;
	tp->str_shortlen = -1;
}

/*
 * sum_tbl:
 *	Merge the tbl data of t2 into t1.
 */
I 14
void
E 14
sum_tbl(t1, t2)
register STRFILE	*t1, *t2;
{
	t1->str_numstr += t2->str_numstr;
	if (t1->str_longlen < t2->str_longlen)
		t1->str_longlen = t2->str_longlen;
	if (t1->str_shortlen > t2->str_shortlen)
		t1->str_shortlen = t2->str_shortlen;
}

#define	STR(str)	((str) == NULL ? "NULL" : (str))

/*
 * print_file_list:
 *	Print out the file list
 */
I 14
void
E 14
print_file_list()
{
	print_list(File_list, 0);
}

/*
 * print_list:
 *	Print out the actual list, recursively.
 */
I 14
void
E 14
print_list(list, lev)
register FILEDESC	*list;
int			lev;
{
	while (list != NULL) {
		fprintf(stderr, "%*s", lev * 4, "");
		if (list->percent == NO_PROB)
			fprintf(stderr, "___%%");
		else
			fprintf(stderr, "%3d%%", list->percent);
		fprintf(stderr, " %s", STR(list->name));
		DPRINTF(1, (stderr, " (%s, %s, %s)\n", STR(list->path),
			    STR(list->datfile), STR(list->posfile)));
		putc('\n', stderr);
		if (list->child != NULL)
			print_list(list->child, lev + 1);
		list = list->next;
	}
}

#ifndef	NO_REGEX
/*
 * conv_pat:
 *	Convert the pattern to an ignore-case equivalent.
 */
char *
conv_pat(orig)
register char	*orig;
{
	register char		*sp;
	register unsigned int	cnt;
	register char		*new;

	cnt = 1;	/* allow for '\0' */
	for (sp = orig; *sp != '\0'; sp++)
		if (isalpha(*sp))
			cnt += 4;
		else
			cnt++;
	if ((new = malloc(cnt)) == NULL) {
		fprintf(stderr, "pattern too long for ignoring case\n");
		exit(1);
	}

	for (sp = new; *orig != '\0'; orig++) {
		if (islower(*orig)) {
			*sp++ = '[';
			*sp++ = *orig;
			*sp++ = toupper(*orig);
			*sp++ = ']';
		}
		else if (isupper(*orig)) {
			*sp++ = '[';
			*sp++ = *orig;
			*sp++ = tolower(*orig);
			*sp++ = ']';
		}
		else
			*sp++ = *orig;
	}
	*sp = '\0';
	return new;
}

/*
 * find_matches:
 *	Find all the fortunes which match the pattern we've been given.
 */
I 14
int
E 14
find_matches()
{
	Fort_len = maxlen_in_list(File_list);
	DPRINTF(2, (stderr, "Maximum length is %d\n", Fort_len));
D 12
	Fortbuf = do_malloc((unsigned int) Fort_len);
E 12
I 12
	/* extra length, "%\n" is appended */
	Fortbuf = do_malloc((unsigned int) Fort_len + 10);
E 12

	Found_one = FALSE;
	matches_in_list(File_list);
	return Found_one;
	/* NOTREACHED */
}

/*
 * maxlen_in_list
 *	Return the maximum fortune len in the file list.
 */
I 14
int
E 14
maxlen_in_list(list)
FILEDESC	*list;
{
	register FILEDESC	*fp;
	register int		len, maxlen;

	maxlen = 0;
	for (fp = list; fp != NULL; fp = fp->next) {
		if (fp->child != NULL) {
			if ((len = maxlen_in_list(fp->child)) > maxlen)
				maxlen = len;
		}
		else {
			get_tbl(fp);
			if (fp->tbl.str_longlen > maxlen)
				maxlen = fp->tbl.str_longlen;
		}
	}
	return maxlen;
}

/*
 * matches_in_list
 *	Print out the matches from the files in the list.
 */
I 14
void
E 14
matches_in_list(list)
FILEDESC	*list;
{
	register char		*sp;
	register FILEDESC	*fp;
	int			in_file;

	for (fp = list; fp != NULL; fp = fp->next) {
		if (fp->child != NULL) {
			matches_in_list(fp->child);
			continue;
		}
		DPRINTF(1, (stderr, "searching in %s\n", fp->path));
		open_fp(fp);
		sp = Fortbuf;
		in_file = FALSE;
		while (fgets(sp, Fort_len, fp->inf) != NULL)
			if (!STR_ENDSTRING(sp, fp->tbl))
				sp += strlen(sp);
			else {
				*sp = '\0';
				if (RE_EXEC(Fortbuf)) {
D 11
					printf("%c%c", fp->tbl.str_delim, fp->tbl.str_delim);
E 11
I 11
					printf("%c%c", fp->tbl.str_delim,
					    fp->tbl.str_delim);
E 11
					if (!in_file) {
						printf(" (%s)", fp->name);
						Found_one = TRUE;
						in_file = TRUE;
					}
					putchar('\n');
					(void) fwrite(Fortbuf, 1, (sp - Fortbuf), stdout);
				}
				sp = Fortbuf;
			}
	}
}
# endif	/* NO_REGEX */
I 8

I 14
void
E 14
usage()
{
	(void) fprintf(stderr, "fortune [-a");
#ifdef	DEBUG
	(void) fprintf(stderr, "D");
#endif	/* DEBUG */
	(void) fprintf(stderr, "f");
#ifndef	NO_REGEX
	(void) fprintf(stderr, "i");
#endif	/* NO_REGEX */
	(void) fprintf(stderr, "losw]");
#ifndef	NO_REGEX
	(void) fprintf(stderr, " [-m pattern]");
#endif	/* NO_REGEX */
	(void) fprintf(stderr, "[ [#%%] file/directory/all]\n");
	exit(1);
}
E 8
E 3
E 1
