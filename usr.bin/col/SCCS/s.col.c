h09542
s 00001/00000/00511
d D 8.5 95/05/04 15:34:07 bostic 10 9
c optarg/optind moved to unistd.h
e
s 00003/00000/00508
d D 8.4 95/04/28 12:40:46 bostic 9 8
c avoid extra newline if no input; From: Chris Torek <torek@BSDI.COM>
e
s 00002/00002/00506
d D 8.3 94/04/02 10:07:23 pendry 8 7
c add 1994 copyright
e
s 00042/00026/00466
d D 8.2 94/04/01 07:56:27 pendry 7 6
c prettyness police
e
s 00005/00005/00487
d D 8.1 93/06/06 14:28:01 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00489
d D 5.3 91/02/02 18:21:08 torek 5 4
c 08 and 09 are not octal constants! use 010 and 011
e
s 00007/00007/00485
d D 5.2 90/05/24 14:58:48 bostic 4 3
c gcc doesn't like naked numbers...
e
s 00434/00250/00058
d D 5.1 90/05/22 11:08:42 bostic 3 2
c new version from Michael Rendell
c Michael Rendell <michael@stretch.cs.mun.ca>
e
s 00000/00002/00308
d D 4.2 84/05/15 11:01:20 ralph 2 1
c get rid of useless setbuf()'s.
e
s 00310/00000/00000
d D 4.1 80/10/01 17:25:40 bill 1 0
c date and time created 80/10/01 17:25:40 by bill
e
u
U
t
T
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
# include <stdio.h>
# define PL 256
# define ESC '\033'
# define RLF '\013'
# define SI '\017'
# define SO '\016'
# define GREEK 0200
# define LINELN 800
E 3
I 3
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
D 8
 * Copyright (c) 1990, 1993
E 8
I 8
 * Copyright (c) 1990, 1993, 1994
E 8
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Michael Rendell of the Memorial University of Newfoundland.
 *
 * %sccs.include.redist.c%
 */
E 3

D 3
char *page[PL];
char lbuff [LINELN], *line;
int bflag, hflag, fflag;
int half;
int cp, lp;
int ll, llh, mustwr;
int pcp = 0;
char *pgmname;
char	*strcpy();
E 3
I 3
#ifndef lint
D 6
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
D 8
"%Z% Copyright (c) 1990, 1993\n\
E 8
I 8
"%Z% Copyright (c) 1990, 1993, 1994\n\
E 8
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */
E 3

D 3
main (argc, argv)
	int argc; char **argv;
{
	int i;
	int greek;
	register int c;
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3
D 2
	char fbuff[BUFSIZ];
E 2

D 2
	setbuf (stdout, fbuff);
E 2
D 3
	pgmname = argv[0];
E 3
I 3
D 7
#include <errno.h>
E 7
#include <ctype.h>
I 7
#include <err.h>
E 7
#include <string.h>
#include <stdio.h>
I 7
#include <stdlib.h>
I 10
#include <unistd.h>
E 10
E 7
E 3

D 3
	for (i = 1; i < argc; i++) {
		register char *p;
		if (*argv[i] != '-') {
			fprintf (stderr, "%s: bad option %s\n",
				pgmname, argv[i]);
			exit (2);
		}
		for (p = argv[i]+1; *p; p++) {
			switch (*p) {
			case 'b':
				bflag++;
				break;
E 3
I 3
#define	BS	'\b'		/* backspace */
#define	TAB	'\t'		/* tab */
#define	SPACE	' '		/* space */
#define	NL	'\n'		/* newline */
#define	CR	'\r'		/* carriage return */
D 4
#define	ESC	033		/* escape */
#define	SI	017		/* shift in to normal character set */
#define	SO	016		/* shift out to alternate character set */
#define	VT	013		/* vertical tab (aka reverse line feed) */
#define	RLF	07		/* ESC-07 reverse line feed */
#define	RHLF	08		/* ESC-08 reverse half-line feed */
#define	FHLF	09		/* ESC-09 forward half-line feed */
E 4
I 4
#define	ESC	'\033'		/* escape */
#define	SI	'\017'		/* shift in to normal character set */
#define	SO	'\016'		/* shift out to alternate character set */
#define	VT	'\013'		/* vertical tab (aka reverse line feed) */
D 5
#define	RLF	'\07'		/* ESC-07 reverse line feed */
#define	RHLF	'\08'		/* ESC-08 reverse half-line feed */
#define	FHLF	'\09'		/* ESC-09 forward half-line feed */
E 5
I 5
#define	RLF	'\007'		/* ESC-07 reverse line feed */
#define	RHLF	'\010'		/* ESC-010 reverse half-line feed */
#define	FHLF	'\011'		/* ESC-011 forward half-line feed */
E 5
E 4
E 3

D 3
			case 'h':
				hflag++;
				break;
E 3
I 3
/* build up at least this many lines before flushing them out */
#define	BUFFER_MARGIN		32
E 3

D 3
			case 'f':
				fflag++;
				break;
E 3
I 3
typedef char CSET;
E 3

D 3
			default:
				fprintf (stderr, "%s: bad option letter %c\n",
					pgmname, *p);
				exit (2);
			}
		}
	}
E 3
I 3
typedef struct char_str {
#define	CS_NORMAL	1
#define	CS_ALTERNATE	2
	short		c_column;	/* column character is in */
	CSET		c_set;		/* character set (currently only 2) */
	char		c_char;		/* character in question */
} CHAR;
E 3

D 3
	for (ll=0; ll<PL; ll++)
		page[ll] = 0;
E 3
I 3
typedef struct line_str LINE;
struct line_str {
	CHAR	*l_line;		/* characters on the line */
	LINE	*l_prev;		/* previous line */
	LINE	*l_next;		/* next line */
	int	l_lsize;		/* allocated sizeof l_line */
	int	l_line_len;		/* strlen(l_line) */
	int	l_needs_sort;		/* set if chars went in out of order */
	int	l_max_col;		/* max column in the line */
};
E 3

D 3
	cp = 0;
	ll = 0;
	greek = 0;
	mustwr = PL;
	line = lbuff;
E 3
I 3
D 7
LINE *alloc_line();
void *xmalloc();
E 7
I 7
LINE   *alloc_line __P((void));
void	dowarn __P((int));
void	flush_line __P((LINE *));
void	flush_lines __P((int));
void	flush_blanks __P((void));
void	free_line __P((LINE *));
void	usage __P((void));
void	wrerr __P((void));
void   *xmalloc __P((void *, size_t));
E 7
E 3

D 3
	while ((c = getchar()) != EOF) {
		switch (c) {
		case '\n':
			incr();
			incr();
			cp = 0;
			continue;
E 3
I 3
D 7
CSET last_set;			/* char_set of last char printed */
LINE *lines;
int compress_spaces;		/* if doing space -> tab conversion */
int fine;			/* if `fine' resolution (half lines) */
int max_bufd_lines;		/* max # lines to keep in memory */
int nblank_lines;		/* # blanks after last flushed line */
int no_backspaces;		/* if not to output any backspaces */
E 7
I 7
CSET	last_set;		/* char_set of last char printed */
LINE   *lines;
int	compress_spaces;	/* if doing space -> tab conversion */
int	fine;			/* if `fine' resolution (half lines) */
int	max_bufd_lines;		/* max # lines to keep in memory */
int	nblank_lines;		/* # blanks after last flushed line */
int	no_backspaces;		/* if not to output any backspaces */
E 7
E 3

D 3
		case '\0':
			continue;
E 3
I 3
#define	PUTC(ch) \
	if (putchar(ch) == EOF) \
		wrerr();
E 3

I 7
int
E 7
D 3
		case ESC:
			c = getchar();
			switch (c) {
			case '7':	/* reverse full line feed */
				decr();
				decr();
				break;
E 3
I 3
main(argc, argv)
	int argc;
	char **argv;
{
D 7
	extern int optind;
	extern char *optarg;
	register int ch;
E 7
I 7
	int ch;
E 7
	CHAR *c;
	CSET cur_set;			/* current character set */
	LINE *l;			/* current line */
	int extra_lines;		/* # of lines above first line */
	int cur_col;			/* current column */
	int cur_line;			/* line number of current position */
	int max_line;			/* max value of cur_line */
	int this_line;			/* line l points to */
	int nflushd_lines;		/* number of lines that were flushed */
	int adjust, opt, warned;
E 3

D 3
			case '8':	/* reverse half line feed */
				if (fflag)
					decr();
				else {
					if (--half < -1) {
						decr();
						decr();
						half += 2;
					}
				}
				break;

			case '9':	/* forward half line feed */
				if (fflag)
					incr();
				else {
					if (++half > 0) {
						incr();
						incr();
						half -= 2;
					}
				}
				break;
E 3
I 3
	max_bufd_lines = 128;
	compress_spaces = 1;		/* compress spaces into tabs */
	while ((opt = getopt(argc, argv, "bfhl:x")) != EOF)
		switch (opt) {
		case 'b':		/* do not output backspaces */
			no_backspaces = 1;
			break;
		case 'f':		/* allow half forward line feeds */
			fine = 1;
			break;
		case 'h':		/* compress spaces into tabs */
			compress_spaces = 1;
			break;
		case 'l':		/* buffered line count */
			if ((max_bufd_lines = atoi(optarg)) <= 0) {
				(void)fprintf(stderr,
				    "col: bad -l argument %s.\n", optarg);
				exit(1);
E 3
			}
D 3
			continue;
E 3
I 3
			break;
		case 'x':		/* do not compress spaces into tabs */
			compress_spaces = 0;
			break;
		case '?':
		default:
			usage();
		}
E 3

D 3
		case SO:
			greek = GREEK;
			continue;
E 3
I 3
	if (optind != argc)
		usage();
E 3

D 3
		case SI:
			greek = 0;
			continue;
E 3
I 3
	/* this value is in half lines */
	max_bufd_lines *= 2;
E 3

D 3
		case RLF:
			decr();
			decr();
			continue;
E 3
I 3
	adjust = cur_col = extra_lines = warned = 0;
	cur_line = max_line = nflushd_lines = this_line = 0;
	cur_set = last_set = CS_NORMAL;
	lines = l = alloc_line();
E 3

D 3
		case '\r':
			cp = 0;
E 3
I 3
	while ((ch = getchar()) != EOF) {
		if (!isgraph(ch)) {
			switch (ch) {
			case BS:		/* can't go back further */
				if (cur_col == 0)
					continue;
				--cur_col;
				continue;
			case CR:
				cur_col = 0;
				continue;
			case ESC:		/* just ignore EOF */
				switch(getchar()) {
				case RLF:
					cur_line -= 2;
					break;
				case RHLF:
					cur_line--;
					break;
				case FHLF:
					cur_line++;
					if (cur_line > max_line)
						max_line = cur_line;
				}
				continue;
			case NL:
				cur_line += 2;
				if (cur_line > max_line)
					max_line = cur_line;
				cur_col = 0;
				continue;
			case SPACE:
				++cur_col;
				continue;
			case SI:
				cur_set = CS_NORMAL;
				continue;
			case SO:
				cur_set = CS_ALTERNATE;
				continue;
			case TAB:		/* adjust column */
				cur_col |= 7;
				++cur_col;
				continue;
			case VT:
				cur_line -= 2;
				continue;
			}
E 3
			continue;
I 3
		}
E 3

D 3
		case '\t':
			cp = (cp + 8) & -8;
			continue;
E 3
I 3
		/* Must stuff ch in a line - are we at the right one? */
		if (cur_line != this_line - adjust) {
			LINE *lnew;
			int nmove;
E 3

D 3
		case '\b':
			if (cp > 0)
				cp--;
			continue;

		case ' ':
			cp++;
			continue;

		default:
			c &= 0177;
			if (c > 040 && c < 0177) {	/* if printable */
				outc(c | greek);
				cp++;
E 3
I 3
			adjust = 0;
			nmove = cur_line - this_line;
			if (!fine) {
				/* round up to next line */
				if (cur_line & 1) {
					adjust = 1;
					nmove++;
				}
E 3
			}
D 3
			continue;
E 3
I 3
			if (nmove < 0) {
				for (; nmove < 0 && l->l_prev; nmove++)
					l = l->l_prev;
				if (nmove) {
					if (nflushd_lines == 0) {
						/*
						 * Allow backup past first
						 * line if nothing has been
						 * flushed yet.
						 */
						for (; nmove < 0; nmove++) {
							lnew = alloc_line();
							l->l_prev = lnew;
							lnew->l_next = l;
							l = lines = lnew;
							extra_lines++;
						}
					} else {
						if (!warned++)
D 7
							warn(cur_line);
E 7
I 7
							dowarn(cur_line);
E 7
						cur_line -= nmove;
					}
				}
			} else {
				/* may need to allocate here */
				for (; nmove > 0 && l->l_next; nmove--)
					l = l->l_next;
				for (; nmove > 0; nmove--) {
					lnew = alloc_line();
					lnew->l_prev = l;
					l->l_next = lnew;
					l = lnew;
				}
			}
			this_line = cur_line + adjust;
			nmove = this_line - nflushd_lines;
			if (nmove >= max_bufd_lines + BUFFER_MARGIN) {
				nflushd_lines += nmove - max_bufd_lines;
				flush_lines(nmove - max_bufd_lines);
			}
E 3
		}
I 3
		/* grow line's buffer? */
		if (l->l_line_len + 1 >= l->l_lsize) {
			int need;

			need = l->l_lsize ? l->l_lsize * 2 : 90;
			l->l_line = (CHAR *)xmalloc((void *) l->l_line,
			    (unsigned) need * sizeof(CHAR));
			l->l_lsize = need;
		}
		c = &l->l_line[l->l_line_len++];
		c->c_char = ch;
		c->c_set = cur_set;
		c->c_column = cur_col;
		/*
		 * If things are put in out of order, they will need sorting
		 * when it is flushed.
		 */
		if (cur_col < l->l_max_col)
			l->l_needs_sort = 1;
		else
			l->l_max_col = cur_col;
		cur_col++;
E 3
	}
I 9
	if (max_line == 0)
		exit(0);	/* no lines, so just exit */

E 9
I 3
	/* goto the last line that had a character on it */
	for (; l->l_next; l = l->l_next)
		this_line++;
	flush_lines(this_line - nflushd_lines + extra_lines + 1);
E 3

D 3
	for (i=0; i<PL; i++)
		if (page[(mustwr+i)%PL] != 0)
			emit (page[(mustwr+i) % PL], mustwr+i-PL);
	emit (" ", (llh + 1) & -2);
E 3
I 3
	/* make sure we leave things in a sane state */
	if (last_set != CS_NORMAL)
		PUTC('\017');

	/* flush out the last few blank lines */
	nblank_lines = max_line - this_line;
	if (max_line & 1)
		nblank_lines++;
	else if (!nblank_lines)
		/* missing a \n on the last line? */
		nblank_lines = 2;
	flush_blanks();
E 3
	exit(0);
}

I 7
void
E 7
D 3
outc (c)
	register char c;
E 3
I 3
flush_lines(nflush)
	int nflush;
E 3
{
D 3
	if (lp > cp) {
		line = lbuff;
		lp = 0;
	}
E 3
I 3
	LINE *l;
E 3

D 3
	while (lp < cp) {
		switch (*line) {
		case '\0':
			*line = ' ';
			lp++;
			break;

		case '\b':
			lp--;
			break;

		default:
			lp++;
E 3
I 3
	while (--nflush >= 0) {
		l = lines;
		lines = l->l_next;
		if (l->l_line) {
			flush_blanks();
			flush_line(l);
E 3
		}
D 3
		line++;
E 3
I 3
		nblank_lines++;
		if (l->l_line)
			(void)free((void *)l->l_line);
		free_line(l);
E 3
	}
D 3
	while (*line == '\b') {
		line += 2;
	}
	if (bflag || *line == '\0' || *line == ' ')
		*line = c;
	else {
		register char c1, c2, c3;
		c1 = *++line;
		*line++ = '\b';
		c2 = *line;
		*line++ = c;
		while (c1) {
			c3 = *line;
			*line++ = c1;
			c1 = c2;
			c2 = c3;
		}
		lp = 0;
		line = lbuff;
	}
E 3
I 3
	if (lines)
		lines->l_prev = NULL;
E 3
}

D 3
store (lno)
E 3
I 3
/*
 * Print a number of newline/half newlines.  If fine flag is set, nblank_lines
 * is the number of half line feeds, otherwise it is the number of whole line
 * feeds.
 */
I 7
void
E 7
flush_blanks()
E 3
{
D 3
	char *malloc();
E 3
I 3
	int half, i, nb;
E 3

D 3
	lno %= PL;
	if (page[lno] != 0)
		free (page[lno]);
	page[lno] = malloc((unsigned)strlen(lbuff) + 2);
	if (page[lno] == 0) {
		fprintf (stderr, "%s: no storage\n", pgmname);
		exit (2);
E 3
I 3
	half = 0;
	nb = nblank_lines;
	if (nb & 1) {
		if (fine)
			half = 1;
		else
			nb++;
E 3
	}
D 3
	strcpy (page[lno],lbuff);
E 3
I 3
	nb /= 2;
	for (i = nb; --i >= 0;)
		PUTC('\n');
	if (half) {
		PUTC('\033');
		PUTC('9');
		if (!nb)
			PUTC('\r');
	}
	nblank_lines = 0;
E 3
}

D 3
fetch(lno)
E 3
I 3
/*
 * Write a line to stdout taking care of space to tab conversion (-h flag)
 * and character set shifts.
 */
I 7
void
E 7
flush_line(l)
	LINE *l;
E 3
{
D 3
	register char *p;
E 3
I 3
	CHAR *c, *endc;
	int nchars, last_col, this_col;
E 3

D 3
	lno %= PL;
	p = lbuff;
	while (*p)
		*p++ = '\0';
	line = lbuff;
	lp = 0;
	if (page[lno])
		strcpy (line, page[lno]);
}
emit (s, lineno)
	char *s;
	int lineno;
{
	static int cline = 0;
	register int ncp;
	register char *p;
	static int gflag = 0;
E 3
I 3
	last_col = 0;
	nchars = l->l_line_len;
E 3

D 3
	if (*s) {
		while (cline < lineno - 1) {
			putchar ('\n');
			pcp = 0;
			cline += 2;
E 3
I 3
	if (l->l_needs_sort) {
		static CHAR *sorted;
		static int count_size, *count, i, save, sorted_size, tot;

		/*
		 * Do an O(n) sort on l->l_line by column being careful to
		 * preserve the order of characters in the same column.
		 */
		if (l->l_lsize > sorted_size) {
			sorted_size = l->l_lsize;
			sorted = (CHAR *)xmalloc((void *)sorted,
			    (unsigned)sizeof(CHAR) * sorted_size);
E 3
		}
D 3
		if (cline != lineno) {
			putchar (ESC);
			putchar ('9');
			cline++;
E 3
I 3
		if (l->l_max_col >= count_size) {
			count_size = l->l_max_col + 1;
			count = (int *)xmalloc((void *)count,
			    (unsigned)sizeof(int) * count_size);
E 3
		}
D 3
		if (pcp)
			putchar ('\r');
		pcp = 0;
		p = s;
		while (*p) {
			ncp = pcp;
			while (*p++ == ' ') {
				if ((++ncp & 7) == 0 && hflag) {
					pcp = ncp;
					putchar ('\t');
E 3
I 3
D 7
		bzero((char *)count, sizeof(int) * l->l_max_col + 1);
E 7
I 7
		memset((char *)count, 0, sizeof(int) * l->l_max_col + 1);
E 7
		for (i = nchars, c = l->l_line; --i >= 0; c++)
			count[c->c_column]++;

		/*
		 * calculate running total (shifted down by 1) to use as
		 * indices into new line.
		 */
		for (tot = 0, i = 0; i <= l->l_max_col; i++) {
			save = count[i];
			count[i] = tot;
			tot += save;
		}

		for (i = nchars, c = l->l_line; --i >= 0; c++)
			sorted[count[c->c_column]++] = *c;
		c = sorted;
	} else
		c = l->l_line;
	while (nchars > 0) {
		this_col = c->c_column;
		endc = c;
		do {
			++endc;
		} while (--nchars > 0 && this_col == endc->c_column);

		/* if -b only print last character */
		if (no_backspaces)
			c = endc - 1;

		if (this_col > last_col) {
			int nspace = this_col - last_col;

			if (compress_spaces && nspace > 1) {
				int ntabs;

				ntabs = this_col / 8 - last_col / 8;
				nspace -= ntabs * 8;
				while (--ntabs >= 0)
					PUTC('\t');
			}
			while (--nspace >= 0)
				PUTC(' ');
			last_col = this_col;
		}
		last_col++;

		for (;;) {
			if (c->c_set != last_set) {
				switch (c->c_set) {
				case CS_NORMAL:
					PUTC('\017');
					break;
				case CS_ALTERNATE:
					PUTC('\016');
E 3
				}
I 3
				last_set = c->c_set;
E 3
			}
D 3
			if (!*--p)
E 3
I 3
			PUTC(c->c_char);
			if (++c >= endc)
E 3
				break;
D 3
			while (pcp < ncp) {
				putchar (' ');
				pcp++;
			}
			if (gflag != (*p & GREEK) && *p != '\b') {
				if (gflag)
					putchar (SI);
				else
					putchar (SO);
				gflag ^= GREEK;
			}
			putchar (*p & ~GREEK);
			if (*p++ == '\b')
				pcp--;
			else
				pcp++;
E 3
I 3
			PUTC('\b');
E 3
		}
	}
}

D 3
incr()
E 3
I 3
#define	NALLOC 64

static LINE *line_freelist;

LINE *
alloc_line()
E 3
{
D 3
	store (ll++);
	if (ll > llh)
		llh = ll;
	if (ll >= mustwr && page[ll%PL]) {
		emit (page[ll%PL], ll - PL);
		mustwr++;
		free (page[ll%PL]);
		page[ll%PL] = 0;
E 3
I 3
	LINE *l;
	int i;

	if (!line_freelist) {
		l = (LINE *)xmalloc((void *)NULL, sizeof(LINE) * NALLOC);
		line_freelist = l;
		for (i = 1; i < NALLOC; i++, l++)
			l->l_next = l + 1;
		l->l_next = NULL;
E 3
	}
D 3
	fetch (ll);
E 3
I 3
	l = line_freelist;
	line_freelist = l->l_next;

D 7
	bzero(l, sizeof(LINE));
	return(l);
E 7
I 7
	memset(l, 0, sizeof(LINE));
	return (l);
E 7
E 3
}

I 7
void
E 7
D 3
decr()
E 3
I 3
free_line(l)
	LINE *l;
E 3
{
I 7

E 7
D 3
	if (ll > mustwr - PL) {
		store (ll--);
		fetch (ll);
E 3
I 3
	l->l_next = line_freelist;
	line_freelist = l;
}

void *
xmalloc(p, size)
	void *p;
	size_t size;
{
D 7
	if (!(p = (void *)realloc(p, size))) {
		(void)fprintf(stderr, "col: %s.\n", strerror(ENOMEM));
		exit(1);
E 3
	}
I 3
	return(p);
E 7
I 7

	if (!(p = (void *)realloc(p, size)))
		err(1, NULL);
	return (p);
E 7
}

I 7
void
E 7
usage()
{
I 7

E 7
	(void)fprintf(stderr, "usage: col [-bfx] [-l nline]\n");
	exit(1);
}

I 7
void
E 7
wrerr()
{
I 7

E 7
	(void)fprintf(stderr, "col: write error.\n");
	exit(1);
}

D 7
warn(line)
E 7
I 7
void
dowarn(line)
E 7
	int line;
{
D 7
	(void)fprintf(stderr,
	    "col: warning: can't back up %s.\n", line < 0 ?
	    "past first line" : "-- line already flushed");
E 7
I 7

	warnx("warning: can't back up %s",
		line < 0 ? "past first line" : "-- line already flushed");
E 7
E 3
}
E 1
