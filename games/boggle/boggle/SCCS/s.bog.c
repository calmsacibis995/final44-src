h16032
s 00001/00000/00645
d D 8.2 95/05/04 15:26:56 bostic 4 3
c optarg/optind moved unitsd.h
e
s 00005/00005/00640
d D 8.1 93/06/11 14:44:25 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00176/00188/00469
d D 5.2 93/06/11 14:43:52 bostic 2 1
c integrate into 4.4BSD
e
s 00657/00000/00000
d D 5.1 93/06/10 11:09:44 bostic 1 0
c date and time created 93/06/10 11:09:44 by bostic
e
u
U
t
T
I 1
D 2
/* vi: set tabstop=4 : */

/*
 * bog - the game of boggle
E 2
I 2
/*-
D 3
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
E 2
 *
D 2
 * 6-Mar-89     changed loaddict() to use a large buffer and check for overflow,
 *              minor cleanup
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Barry Brachman.
 *
 * %sccs.include.redist.c%
E 2
 */

D 2
#include "bog.h"
E 2
I 2
#ifndef lint
D 3
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 3
I 3
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 3
#endif /* not lint */
E 2

I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
#include <ctype.h>
I 2
#include <err.h>
E 2
#include <stdio.h>
I 2
#include <stdlib.h>
#include <time.h>
I 4
#include <unistd.h>
E 4
E 2

D 2
char *version = "bog V1.3 brachman@ubc.csnet 6-Mar-89";
E 2
I 2
#include "bog.h"
#include "extern.h"
E 2

I 2
static int	compar __P((const void *, const void *));

E 2
struct dictindex dictindex[26];

/*
 * Cube position numbering:
 *
 *	0 1 2 3
 *	4 5 6 7
 *	8 9 A B
 *	C D E F
 */
static int adjacency[16][16] = {
D 2
/*    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
E 2
I 2
/*        0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
E 2
	{ 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },		/* 0 */
	{ 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },		/* 1 */
	{ 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },		/* 2 */
	{ 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },		/* 3 */
	{ 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },		/* 4 */
	{ 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0 },		/* 5 */
	{ 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0 },		/* 6 */
	{ 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0 },		/* 7 */
	{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0 },		/* 8 */
	{ 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0 },		/* 9 */
	{ 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 },		/* A */
	{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1 },		/* B */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0 },		/* C */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0 },		/* D */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1 },		/* E */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0 }		/* F */
};

static int letter_map[26][16];

char board[17];
int wordpath[MAXWORDLEN + 1];
int wordlen;		/* Length of last word returned by nextword() */
int usedbits;

char *pword[MAXPWORDS], pwords[MAXPSPACE], *pwordsp;
int npwords;

char *mword[MAXMWORDS], mwords[MAXMSPACE], *mwordsp;
int nmwords;

int ngames = 0;
int tnmwords = 0, tnpwords = 0;

D 2
#ifdef TIMER
E 2
#include <setjmp.h>
D 2

E 2
jmp_buf env;
D 2
#endif TIMER
E 2

long start_t;

D 2
static FILE *dictfp = (FILE *) NULL;
E 2
I 2
static FILE *dictfp;
E 2

int batch;
int debug;
int minlength;
int reuse;
int tlimit;

D 2
char *batchword(), *getline();

long atol();
long random();

E 2
I 2
int
E 2
main(argc, argv)
D 2
int argc;
char **argv;
E 2
I 2
	int argc;
	char *argv[];
E 2
{
D 2
	int done, i, selfuse, sflag;
	char *bspec, *p;
E 2
	long seed;
D 2
	FILE *opendict();
E 2
I 2
	int ch, done, i, selfuse, sflag;
	char *bspec, *p;
E 2

D 2
	debug = 0;
	bspec = (char *) NULL;
	reuse = 0;
	batch = 0;
	selfuse = 0;
E 2
I 2
	batch = debug = reuse = selfuse = sflag = 0;
	bspec = NULL;
E 2
	minlength = 3;
	tlimit = 180;		/* 3 minutes is standard */
D 2
	sflag = 0;
E 2

D 2
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'b':
				batch = 1;
				break;
			case 'd':
				debug = 1;
				break;
			case 's':
				sflag = 1;
				seed = atol(&argv[i][2]);
				break;
			case 't':
				if ((tlimit = atoi(&argv[i][2])) < 1) {
					(void) fprintf(stderr, "Bad time limit\n");
					exit(1);
				}
				break;
			case 'w':
				if ((minlength = atoi(&argv[i][2])) < 3) {
					(void) fprintf(stderr, "Min word length must be > 2\n");
					exit(1);
				}
				break;
			default:
				usage();
				/*NOTREACHED*/
			}
E 2
I 2
	while ((ch = getopt(argc, argv, "bds:t:w:")) != EOF)
		switch(ch) {
		case 'b':
			batch = 1;
			break;
		case 'd':
			debug = 1;
			break;
		case 's':
			sflag = 1;
			seed = atol(optarg);
			break;
		case 't':
			if ((tlimit = atoi(optarg)) < 1)
				errx(1, "bad time limit");
			break;
		case 'w':
			if ((minlength = atoi(optarg)) < 3)
				errx(1, "min word length must be > 2");
			break;
		case '?':
		default:
			usage();
E 2
		}
D 2
		else if (strcmp(argv[i], "+") == 0)
			reuse = 1;
		else if (strcmp(argv[i], "++") == 0)
			selfuse = 1;
		else if (islower(argv[i][0])) {
			if (strlen(argv[i]) != 16) {
				usage();
				/*NOTREACHED*/
			}
E 2
I 2
	argc -= optind;
	argv += optind;

	if (strcmp(argv[0], "+") == 0)
		reuse = 1;
	else if (strcmp(argv[0], "++") == 0)
		selfuse = 1;
	else if (islower(argv[0][0])) {
		if (strlen(argv[0]) != 16) {
			usage();

E 2
			/* This board is assumed to be valid... */
D 2
			bspec = argv[i];
		}
		else {
E 2
I 2
			bspec = argv[0];
		} else
E 2
			usage();
D 2
			/*NOREACHED*/
		}
E 2
	}

D 2
	if (batch && bspec == (char *) NULL) {
		(void) fprintf(stderr, "Must give both -b and a board setup\n");
		exit(1);
	}
E 2
I 2
	if (batch && bspec == NULL)
		errx(1, "must give both -b and a board setup");
E 2

D 2
	if (selfuse) {
E 2
I 2
	if (selfuse)
E 2
		for (i = 0; i < 16; i++)
			adjacency[i][i] = 1;
D 2
	}
E 2

	if (batch) {
		newgame(bspec);
D 2
		while ((p = batchword(stdin)) != (char *) NULL)
E 2
I 2
		while ((p = batchword(stdin)) != NULL)
E 2
			(void) printf("%s\n", p);
I 2
		exit (0);
E 2
	}
D 2
	else {
		setup(sflag, seed);
		prompt("Loading the dictionary...");
		if ((dictfp = opendict(DICT)) == (FILE *) NULL) {
			(void) fprintf(stderr, "Can't load %s\n", DICT);
			cleanup();
			exit(1);
		}
E 2
I 2
	setup(sflag, seed);
	prompt("Loading the dictionary...");
	if ((dictfp = opendict(DICT)) == NULL) {
		warn("%s", DICT);
		cleanup();
		exit(1);
	}
E 2
#ifdef LOADDICT
D 2
		if (loaddict(dictfp) < 0) {
			(void) fprintf(stderr, "Can't load %s\n", DICT);
			cleanup();
			exit(1);
		}
		(void) fclose(dictfp);
		dictfp = (FILE *) NULL;
E 2
I 2
	if (loaddict(dictfp) < 0) {
		warnx("can't load %s", DICT);
		cleanup();
		exit(1);
	}
	(void)fclose(dictfp);
	dictfp = NULL;
E 2
#endif
D 2
		if (loadindex(DICTINDEX) < 0) {
			(void) fprintf(stderr, "Can't load %s\n", DICTINDEX);
			cleanup();
			exit(1);
		}
E 2
I 2
	if (loadindex(DICTINDEX) < 0) {
		warnx("can't load %s", DICTINDEX);
		cleanup();
		exit(1);
	}
E 2

D 2
		prompt("Type <space> to begin...");
		while (inputch() != ' ')
			;
E 2
I 2
	prompt("Type <space> to begin...");
	while (inputch() != ' ');
E 2

D 2
		done = 0;
		while (!done) {
			newgame(bspec);
			bspec = (char *) NULL;		/* reset for subsequent games */
			playgame();
			prompt("Type <space> to continue, any cap to quit...");
			delay(50);					/* wait for user to quit typing */
			flushin(stdin);
			while (1) {
				int ch;

				ch = inputch();
				if (ch == '\033')
					findword();
				else if (ch == '\014' || ch == '\022')	/* ^l or ^r */
					redraw();
				else {
					if (isupper(ch)) {
						done = 1;
						break;
					}
					if (ch == ' ')
						break;
E 2
I 2
	for (done = 0; !done;) {
		newgame(bspec);
		bspec = NULL;	/* reset for subsequent games */
		playgame();
		prompt("Type <space> to continue, any cap to quit...");
		delay(50);	/* wait for user to quit typing */
		flushin(stdin);
		for (;;) {
			ch = inputch();
			if (ch == '\033')
				findword();
			else if (ch == '\014' || ch == '\022')	/* ^l or ^r */
				redraw();
			else {
				if (isupper(ch)) {
					done = 1;
					break;
E 2
				}
I 2
				if (ch == ' ')
					break;
E 2
			}
		}
D 2
		cleanup();
E 2
	}
D 2
	exit(0);
E 2
I 2
	cleanup();
	exit (0);
E 2
}

/*
 * Read a line from the given stream and check if it is legal
 * Return a pointer to a legal word or a null pointer when EOF is reached
 */
char *
batchword(fp)
D 2
FILE *fp;
E 2
I 2
	FILE *fp;
E 2
{
	register int *p, *q;
	register char *w;
D 2
	char *nextword();
E 2

	q = &wordpath[MAXWORDLEN + 1];
	p = wordpath;
	while (p < q)
		*p++ = -1;
D 2
	while ((w = nextword(fp)) != (char *) NULL) {
E 2
I 2
	while ((w = nextword(fp)) != NULL) {
E 2
		if (wordlen < minlength)
			continue;
		p = wordpath;
		while (p < q && *p != -1)
			*p++ = -1;
		usedbits = 0;
		if (checkword(w, -1, wordpath) != -1)
D 2
			return(w);
E 2
I 2
			return (w);
E 2
	}
D 2
	return((char *) NULL);
E 2
I 2
	return (NULL);
E 2
}

/*
 * Play a single game
 * Reset the word lists from last game
 * Keep track of the running stats
 */
I 2
void
E 2
playgame()
{
	/* Can't use register variables if setjmp() is used! */
	int i, *p, *q;
	long t;
	char buf[MAXWORDLEN + 1];
D 2
	int compar();
E 2

	ngames++;
	npwords = 0;
	pwordsp = pwords;
	nmwords = 0;
	mwordsp = mwords;

	time(&start_t);

	q = &wordpath[MAXWORDLEN + 1];
	p = wordpath;
	while (p < q)
		*p++ = -1;
	showboard(board);
	startwords();
	if (setjmp(env)) {
		badword();
		goto timesup;
	}

	while (1) {
D 2
		if (getline(buf) == (char *) NULL) {
E 2
I 2
		if (getline(buf) == NULL) {
E 2
			if (feof(stdin))
				clearerr(stdin);
			break;
		}
		time(&t);
		if (t - start_t >= tlimit) {
			badword();
			break;
		}
		if (buf[0] == '\0') {
			int remaining;

			remaining = tlimit - (int) (t - start_t);
D 2
			(void) sprintf(buf, "%d:%02d", remaining / 60, remaining % 60);
E 2
I 2
			(void)snprintf(buf, sizeof(buf),
			    "%d:%02d", remaining / 60, remaining % 60);
E 2
			showstr(buf, 1);
			continue;
		}
		if (strlen(buf) < minlength) {
			badword();
			continue;
		}

		p = wordpath;
		while (p < q && *p != -1)
			*p++ = -1;
		usedbits = 0;

		if (checkword(buf, -1, wordpath) < 0)
			badword();
		else {
			if (debug) {
				(void) printf("[");
				for (i = 0; wordpath[i] != -1; i++)
					(void) printf(" %d", wordpath[i]);
				(void) printf(" ]\n");
			}
			for (i = 0; i < npwords; i++) {
				if (strcmp(pword[i], buf) == 0)
					break;
			}
D 2
			if (i != npwords) {			/* already used the word */
E 2
I 2
			if (i != npwords) {	/* already used the word */
E 2
				badword();
				showword(i);
			}
			else if (!validword(buf))
				badword();
			else {
				int len;

				len = strlen(buf) + 1;
				if (npwords == MAXPWORDS - 1 ||
D 2
						pwordsp + len >= &pwords[MAXPSPACE]) {
					(void) fprintf(stderr, "Too many words!\n");
E 2
I 2
				    pwordsp + len >= &pwords[MAXPSPACE]) {
					warnx("Too many words!");
E 2
					cleanup();
					exit(1);
				}
				pword[npwords++] = pwordsp;
				(void) strcpy(pwordsp, buf);
				pwordsp += len;
				addword(buf);
			}
		}
	}

timesup: ;

	/*
	 * Sort the player's words and terminate the list with a null
	 * entry to help out checkdict()
	 */
	qsort(pword, npwords, sizeof(pword[0]), compar);
D 2
	pword[npwords] = (char *) NULL;
E 2
I 2
	pword[npwords] = NULL;
E 2

	/*
	 * These words don't need to be sorted since the dictionary is sorted
	 */
	checkdict();

	tnmwords += nmwords;
	tnpwords += npwords;

	results();
}

/*
 * Check if the given word is present on the board, with the constraint
 * that the first letter of the word is adjacent to square 'prev'
 * Keep track of the current path of squares for the word
 * A 'q' must be followed by a 'u'
 * Words must end with a null
 * Return 1 on success, -1 on failure
 */
I 2
int
E 2
checkword(word, prev, path)
D 2
char *word;
int prev, *path;
E 2
I 2
	char *word;
	int prev, *path;
E 2
{
	register char *p, *q;
	register int i, *lm;

	if (debug) {
		(void) printf("checkword(%s, %d, [", word, prev);
			for (i = 0; wordpath[i] != -1; i++)
				(void) printf(" %d", wordpath[i]);
			(void) printf(" ]\n");
	}

	if (*word == '\0')
D 2
		return(1);
E 2
I 2
		return (1);
E 2

	lm = letter_map[*word - 'a'];

	if (prev == -1) {
		char subword[MAXWORDLEN + 1];

		/*
		 * Check for letters not appearing in the cube to eliminate some
		 * recursive calls
		 * Fold 'qu' into 'q'
		 */
		p = word;
		q = subword;
		while (*p != '\0') {
			if (*letter_map[*p - 'a'] == -1)
D 2
				return(-1);
E 2
I 2
				return (-1);
E 2
			*q++ = *p;
			if (*p++ == 'q') {
				if (*p++ != 'u')
D 2
					return(-1);
E 2
I 2
					return (-1);
E 2
			}
		}
		*q = '\0';
		while (*lm != -1) {
			*path = *lm;
			usedbits |= (1 << *lm);
			if (checkword(subword + 1, *lm, path + 1) > 0)
D 2
				return(1);
E 2
I 2
				return (1);
E 2
			usedbits &= ~(1 << *lm);
			lm++;
		}
D 2
		return(-1);
E 2
I 2
		return (-1);
E 2
	}

	/*
	 * A cube is only adjacent to itself in the adjacency matrix if selfuse
D 2
	 * was set, so a cube can't be used twice in succession if only the reuse
	 * flag is set
E 2
I 2
	 * was set, so a cube can't be used twice in succession if only the
	 * reuse flag is set
E 2
	 */
	for (i = 0; lm[i] != -1; i++) {
		if (adjacency[prev][lm[i]]) {
			int used;

			used = 1 << lm[i];
D 2
			/* If necessary, check if the square has already been used */
E 2
I 2
			/*
			 * If necessary, check if the square has already
			 * been used.
			 */
E 2
			if (!reuse && (usedbits & used))
					continue;
			*path = lm[i];
			usedbits |= used;
			if (checkword(word + 1, lm[i], path + 1) > 0)
D 2
				return(1);
E 2
I 2
				return (1);
E 2
			usedbits &= ~used;
		}
	}
	*path = -1;		/* in case of a backtrack */
D 2
	return(-1);
E 2
I 2
	return (-1);
E 2
}

/*
 * A word is invalid if it is not in the dictionary
 * At this point it is already known that the word can be formed from
 * the current board
 */
I 2
int
E 2
validword(word)
D 2
char *word;
E 2
I 2
	char *word;
E 2
{
	register int j;
	register char *q, *w;
D 2
	char *nextword();
E 2

	j = word[0] - 'a';
	if (dictseek(dictfp, dictindex[j].start, 0) < 0) {
		(void) fprintf(stderr, "Seek error\n");
		cleanup();
		exit(1);
	}

D 2
	while ((w = nextword(dictfp)) != (char *) NULL) {
E 2
I 2
	while ((w = nextword(dictfp)) != NULL) {
E 2
		int ch;

		if (*w != word[0])	/* end of words starting with word[0] */
			break;
		q = word;
		while ((ch = *w++) == *q++ && ch != '\0')
			;
		if (*(w - 1) == '\0' && *(q - 1) == '\0')
D 2
			return(1);
E 2
I 2
			return (1);
E 2
	}
D 2
	if (dictfp != (FILE *) NULL && feof(dictfp))	/* Special case for z's */
E 2
I 2
	if (dictfp != NULL && feof(dictfp))	/* Special case for z's */
E 2
		clearerr(dictfp);
D 2
	return(0);
E 2
I 2
	return (0);
E 2
}

/*
 * Check each word in the dictionary against the board
 * Delete words from the machine list that the player has found
 * Assume both the dictionary and the player's words are already sorted
 */
I 2
void
E 2
checkdict()
{
	register char *p, **pw, *w;
	register int i;
	int prevch, previndex, *pi, *qi, st;

	mwordsp = mwords;
	nmwords = 0;
	pw = pword;
	prevch ='a';
	qi = &wordpath[MAXWORDLEN + 1];

	(void) dictseek(dictfp, 0L, 0);
D 2
	while ((w = nextword(dictfp)) != (char *) NULL) {
E 2
I 2
	while ((w = nextword(dictfp)) != NULL) {
E 2
		if (wordlen < minlength)
			continue;
		if (*w != prevch) {
			/*
D 2
			 * If we've moved on to a word with a different first letter
			 * then we can speed things up by skipping all words starting
			 * with a letter that doesn't appear in the cube
E 2
I 2
			 * If we've moved on to a word with a different first
			 * letter then we can speed things up by skipping all
			 * words starting with a letter that doesn't appear in
			 * the cube.
E 2
			 */
			i = (int) (*w - 'a');
			while (i < 26 && letter_map[i][0] == -1)
				i++;
			if (i == 26)
				break;
			previndex = prevch - 'a';
			prevch = i + 'a';
			/*
D 2
			 * Fall through if the word's first letter appears in the cube
			 * (i.e., if we can't skip ahead), otherwise seek to the
			 * beginning of words in the dictionary starting with the
			 * next letter (alphabetically) appearing in the cube and then
			 * read the first word
E 2
I 2
			 * Fall through if the word's first letter appears in
			 * the cube (i.e., if we can't skip ahead), otherwise
			 * seek to the beginning of words in the dictionary
			 * starting with the next letter (alphabetically)
			 * appearing in the cube and then read the first word.
E 2
			 */
			if (i != previndex + 1) {
D 2
				if (dictseek(dictfp, dictindex[i].start, 0) < 0) {
					(void) fprintf(stderr, "Seek error in checkdict()\n");
E 2
I 2
				if (dictseek(dictfp,
				    dictindex[i].start, 0) < 0) {
					warnx("seek error in checkdict()");
E 2
					cleanup();
					exit(1);
				}
				continue;
			}
		}

		pi = wordpath;
		while (pi < qi && *pi != -1)
			*pi++ = -1;
		usedbits = 0;
		if (checkword(w, -1, wordpath) == -1)
			continue;

		st = 1;
D 2
		while (*pw != (char *) NULL && (st = strcmp(*pw, w)) < 0)
E 2
I 2
		while (*pw != NULL && (st = strcmp(*pw, w)) < 0)
E 2
			pw++;
		if (st == 0)			/* found it */
			continue;
		if (nmwords == MAXMWORDS ||
D 2
					mwordsp + wordlen + 1 >= &mwords[MAXMSPACE]) {
			(void) fprintf(stderr, "Too many words!\n");
E 2
I 2
		    mwordsp + wordlen + 1 >= &mwords[MAXMSPACE]) {
			warnx("too many words!");
E 2
			cleanup();
			exit(1);
		}
		mword[nmwords++] = mwordsp;
		p = w;
D 2
		while (*mwordsp++ = *p++)
			;
E 2
I 2
		while (*mwordsp++ = *p++);
E 2
	}
}

/*
 * Crank up a new game
 * If the argument is non-null then it is assumed to be a legal board spec
 * in ascending cube order, oth. make a random board
 */
I 2
void
E 2
newgame(b)
D 2
char *b;
E 2
I 2
	char *b;
E 2
{
	register int i, p, q;
	char *tmp;
	int *lm[26];
	static char *cubes[16] = {
		"ednosw", "aaciot", "acelrs", "ehinps",
		"eefhiy", "elpstu", "acdemp", "gilruw",
		"egkluy", "ahmors", "abilty", "adenvz",
		"bfiorx", "dknotu", "abjmoq", "egintv"
	};

D 2
	if (b == (char *) NULL) {
E 2
I 2
	if (b == NULL) {
E 2
		/*
		 * Shake the cubes and make the board
		 */
		i = 0;
		while (i < 100) {
			p = (int) (random() % 16);
			q = (int) (random() % 16);
			if (p != q) {
				tmp = cubes[p];
				cubes[p] = cubes[q];
				cubes[q] = tmp;
				i++;
			}
			/* else try again */
		}

		for (i = 0; i < 16; i++)
			board[i] = cubes[i][random() % 6];
	}
	else {
		for (i = 0; i < 16; i++)
			board[i] = b[i];
	}
	board[16] = '\0';

	/*
	 * Set up the map from letter to location(s)
	 * Each list is terminated by a -1 entry
	 */
	for (i = 0; i < 26; i++) {
		lm[i] = letter_map[i];
		*lm[i] = -1;
	}

	for (i = 0; i < 16; i++) {
		register int j;

		j = (int) (board[i] - 'a');
		*lm[j] = i;
		*(++lm[j]) = -1;
	}

	if (debug) {
		for (i = 0; i < 26; i++) {
			int ch, j;

			(void) printf("%c:", 'a' + i);
			for (j = 0; (ch = letter_map[i][j]) != -1; j++)
				(void) printf(" %d", ch);
			(void) printf("\n");
		}
	}

}

I 2
int
E 2
compar(p, q)
D 2
char **p, **q;
E 2
I 2
	const void *p, *q;
E 2
{
D 2
	return(strcmp(*p, *q));
E 2
I 2
	return (strcmp(*(char **)p, *(char **)q));
E 2
}

I 2
void
E 2
usage()
{
D 2
(void) fprintf(stderr,
"Usage: bog [-b] [-d] [-s#] [-t#] [-w#] [+[+]] [boardspec]\n");
(void) fprintf(stderr, "-b: 'batch mode' (boardspec must be present)\n");
(void) fprintf(stderr, "-d: debug\n");
(void) fprintf(stderr, "-s#: use # as the random number seed\n");
(void) fprintf(stderr, "-t#: time limit is # seconds\n");
(void) fprintf(stderr, "-w#: minimum word length is # letters\n");
(void) fprintf(stderr, "+: can reuse a cube, but not twice in succession\n");
(void) fprintf(stderr, "++: can reuse cubes arbitrarily\n");
(void) fprintf(stderr, "boardspec: the first board to use (use 'q' for 'qu')\n");
E 2
I 2
	(void) fprintf(stderr,
	    "usage: bog [-bd] [-s#] [-t#] [-w#] [+[+]] [boardspec]\n");
E 2
	exit(1);
}
D 2

E 2
E 1
