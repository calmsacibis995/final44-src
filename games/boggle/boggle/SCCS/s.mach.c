h00834
s 00002/00002/00648
d D 8.1 93/06/11 14:48:06 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00106/00158/00544
d D 5.2 93/06/11 14:43:57 bostic 2 1
c integrate into 4.4BSD
e
s 00702/00000/00000
d D 5.1 93/06/10 11:09:48 bostic 1 0
c date and time created 93/06/10 11:09:48 by bostic
e
u
U
t
T
I 1
D 2
/* vi: set tabstop=4 : */
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
 *
 * This code is derived from software contributed to Berkeley by
 * Barry Brachman.
 *
 * %sccs.include.redist.c%
 */
E 2

I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
/*
 * Terminal interface
 *
 * Input is raw and unechoed
 */
D 2

#ifdef unix
E 2
I 2
#include <ctype.h>
#include <curses.h>
#include <fcntl.h>
E 2
#include <sgtty.h>
D 2
#endif
E 2
#include <signal.h>
D 2
#include <curses.h>
#include <ctype.h>
E 2
#include <stdio.h>
I 2
#include <stdlib.h>
#include <time.h>
E 2

#include "bog.h"
I 2
#include "extern.h"
E 2

D 2
#ifdef ATARI
#include <osbind.h>
#endif

E 2
static int ccol, crow, maxw;
static int colstarts[MAXCOLS], ncolstarts;
static int lastline;
int ncols, nlines;

D 2
static int cont_catcher(), prwidth(), prword(), stop_catcher(), tty_cleanup();
static int tty_setup(), tty_showboard();
static int winch_catcher();

extern int ngames, nmwords, npwords, tnmwords, tnpwords;
E 2
extern char *pword[], *mword[];
I 2
extern int ngames, nmwords, npwords, tnmwords, tnpwords;
E 2

I 2
static void	cont_catcher __P((int));
static int	prwidth __P((char *[], int));
static void	prword __P((char *[], int));
static void	stop_catcher __P((int));
static void	tty_cleanup __P((void));
static int	tty_setup __P((void));
static void	tty_showboard __P((char *));
static void	winch_catcher __P((int));

E 2
/*
 * Do system dependent initialization
 * This is called once, when the program starts
 */
I 2
int
E 2
setup(sflag, seed)
D 2
int sflag;
long seed;
E 2
I 2
	int sflag;
	long seed;
E 2
{
	extern int debug;

	if (tty_setup() < 0)
		return(-1);

	if (!sflag)
D 2
#ifdef ATARI
		seed = Random();
#else
E 2
		time(&seed);
D 2
#endif
E 2
	srandom(seed);
	if (debug)
		(void) printf("seed = %ld\n", seed);
	return(0);
}

/*
 * Do system dependent clean up
 * This is called once, just before the program terminates
 */
I 2
void
E 2
cleanup()
{
D 2

E 2
	tty_cleanup();
}

/*
 * Display the player's word list, the list of words not found, and the running
 * stats
 */
I 2
void
E 2
results()
{
	int col, row;
D 2
    int denom1, denom2;
E 2
I 2
	int denom1, denom2;
E 2

D 2
    move(LIST_LINE, LIST_COL);
E 2
I 2
	move(LIST_LINE, LIST_COL);
E 2
	clrtobot();
D 2
    printw("Words you found (%d):", npwords);
E 2
I 2
	printw("Words you found (%d):", npwords);
E 2
	refresh();
D 2
    move(LIST_LINE + 1, LIST_COL);
    prtable(pword, npwords, 0, ncols, prword, prwidth);
E 2
I 2
	move(LIST_LINE + 1, LIST_COL);
	prtable(pword, npwords, 0, ncols, prword, prwidth);
E 2

	getyx(stdscr, row, col);
D 2
    move(row + 1, col);
    printw("Words you missed (%d):", nmwords);
E 2
I 2
	move(row + 1, col);
	printw("Words you missed (%d):", nmwords);
E 2
	refresh();
D 2
    move(row + 2, col);
    prtable(mword, nmwords, 0, ncols, prword, prwidth);
E 2
I 2
	move(row + 2, col);
	prtable(mword, nmwords, 0, ncols, prword, prwidth);
E 2

D 2
    denom1 = npwords + nmwords;
    denom2 = tnpwords + tnmwords;
E 2
I 2
	denom1 = npwords + nmwords;
	denom2 = tnpwords + tnmwords;
E 2
 
D 2
    move(SCORE_LINE, SCORE_COL);
    printw("Percentage: %0.2f%% (%0.2f%% over %d game%s)\n",
E 2
I 2
	move(SCORE_LINE, SCORE_COL);
	printw("Percentage: %0.2f%% (%0.2f%% over %d game%s)\n",
E 2
        denom1 ? (100.0 * npwords) / (double) (npwords + nmwords) : 0.0,
        denom2 ? (100.0 * tnpwords) / (double) (tnpwords + tnmwords) : 0.0,
        ngames, ngames > 1 ? "s" : "");
}

D 2
static
prword(base, index)
char **base;
int index;
E 2
I 2
static void
prword(base, indx)
	char *base[];
	int indx;
E 2
{
D 2
 
    printw("%s", base[index]);
E 2
I 2
	printw("%s", base[indx]);
E 2
}

D 2
static
prwidth(base, index)
char **base;
int index;
E 2
I 2
static int
prwidth(base, indx)
	char *base[];
	int indx;
E 2
{
D 2

    return(strlen(base[index]));
E 2
I 2
	return (strlen(base[indx]));
E 2
}

/*
 * Main input routine
 *
 * - doesn't accept words longer than MAXWORDLEN or containing caps
 */
char *
getline(q)
D 2
char *q;
E 2
I 2
	char *q;
E 2
{
	register int ch, done;
	register char *p;
	int row, col;

	p = q;
	done = 0;
	while (!done) {
D 2
		ch = rawch();
E 2
I 2
		ch = timerch();
E 2
		switch (ch) {
		case '\n':
		case '\r':
		case ' ':
			done = 1;
			break;
		case '\033':
			findword();
			break;
		case '\177':			/* <del> */
		case '\010':			/* <bs> */
			if (p == q)
				break;
			p--;
			getyx(stdscr, row, col);
			move(row, col - 1);
			clrtoeol();
			refresh();
			break;
		case '\025':			/* <^u> */
		case '\027':			/* <^w> */
			if (p == q)
				break;
			getyx(stdscr, row, col);
			move(row, col - (int) (p - q));
			p = q;
			clrtoeol();
			refresh();
			break;
#ifdef SIGTSTP
		case '\032':			/* <^z> */
D 2
			stop_catcher();
E 2
I 2
			stop_catcher(0);
E 2
			break;
#endif
		case '\023':			/* <^s> */
			stoptime();
			printw("<PAUSE>");
			refresh();
			while ((ch = inputch()) != '\021' && ch != '\023')
				;
			move(crow, ccol);
			clrtoeol();
			refresh();
			starttime();
			break;
		case '\003':			/* <^c> */
			cleanup();
			exit(0);
			/*NOTREACHED*/
		case '\004':			/* <^d> */
			done = 1;
			ch = EOF;
			break;
		case '\014':			/* <^l> */
		case '\022':			/* <^r> */
			redraw();
			break;
		case '?':
			stoptime();
			if (help() < 0)
				showstr("Can't open help file", 1);
			starttime();
			break;
		default:
			if (!islower(ch))
				break;
			if ((int) (p - q) == MAXWORDLEN) {
				p = q;
				badword();
				break;
			}
			*p++ = ch;
			addch(ch);
			refresh();
			break;
		}
	}
	*p = '\0';
	if (ch == EOF)
		return((char *) NULL);
	return(q);
}

I 2
int
E 2
inputch()
{
D 2

	return(getch() & 0177);
E 2
I 2
	return (getch() & 0177);
E 2
}

I 2
void
E 2
redraw()
{
D 2

E 2
	clearok(stdscr, 1);
	refresh();
}

D 2
#ifdef XXX
/*
 * Flush all pending input
 */
E 2
I 2
void
E 2
flushin(fp)
D 2
FILE *fp;
E 2
I 2
	FILE *fp;
E 2
{
D 2

	flushinp();
}
#endif XXX

#ifdef TIOCFLUSH
#include <sys/file.h>

flushin(fp)
FILE *fp;
{
E 2
	int arg;

	arg = FREAD;
D 2
	(void) ioctl(fileno(fp), TIOCFLUSH, &arg);
E 2
I 2
	(void)ioctl(fileno(fp), TIOCFLUSH, &arg);
E 2
}
D 2
#endif TIOCFLUSH
E 2

D 2
#ifdef ATARI
#include <osbind.h>

/*ARGSUSED*/
flushin(fp)
FILE *fp;
{

	while (Cconis() == -1)
		getch();
}
#endif ATARI

E 2
static int gone;

/*
 * Stop the game timer
 */
I 2
void
E 2
stoptime()
{
D 2
	long t;
E 2
	extern long start_t;
I 2
	long t;
E 2

D 2
	time(&t);
E 2
I 2
	(void)time(&t);
E 2
	gone = (int) (t - start_t);
}

/*
 * Restart the game timer
 */
I 2
void
E 2
starttime()
{
D 2
	long t;
E 2
	extern long start_t;
I 2
	long t;
E 2

D 2
	time(&t);
E 2
I 2
	(void)time(&t);
E 2
	start_t = t - (long) gone;
}

/*
 * Initialize for the display of the player's words as they are typed
 * This display starts at (LIST_LINE, LIST_COL) and goes "down" until the last
 * line.  After the last line a new column is started at LIST_LINE
 * Keep track of each column position for showword()
 * There is no check for exceeding COLS
 */
I 2
void
E 2
startwords()
{
D 2

E 2
	crow = LIST_LINE;
	ccol = LIST_COL;
	maxw = 0;
	ncolstarts = 1;
	colstarts[0] = LIST_COL;
	move(LIST_LINE, LIST_COL);
	refresh();
}

/*
 * Add a word to the list and start a new column if necessary
 * The maximum width of the current column is maintained so we know where
 * to start the next column
 */
I 2
void
E 2
addword(w)
D 2
char *w;
E 2
I 2
	char *w;
E 2
{
	int n;

	if (crow == lastline) {
		crow = LIST_LINE;
		ccol += (maxw + 5);
		colstarts[ncolstarts++] = ccol;
		maxw = 0;
		move(crow, ccol);
	}
	else {
		move(++crow, ccol);
		if ((n = strlen(w)) > maxw)
			maxw = n;
	}
	refresh();
}

/*
 * The current word is unacceptable so erase it
 */
I 2
void
E 2
badword()
{

	move(crow, ccol);
	clrtoeol();
	refresh();
}

/*
 * Highlight the nth word in the list (starting with word 0)
 * No check for wild arg
 */
I 2
void
E 2
showword(n)
D 2
int n;
E 2
I 2
	int n;
E 2
{
	int col, row;

	row = LIST_LINE + n % (lastline - LIST_LINE + 1);
	col = colstarts[n / (lastline - LIST_LINE + 1)];
	move(row, col);
	standout();
	printw("%s", pword[n]);
	standend();
	move(crow, ccol);
	refresh();
	delay(15);
	move(row, col);
	printw("%s", pword[n]);
	move(crow, ccol);
	refresh();
}

/*
 * Get a word from the user and check if it is in either of the two
 * word lists
 * If it's found, show the word on the board for a short time and then
 * erase the word
 *
 * Note: this function knows about the format of the board
 */
I 2
void
E 2
findword()
{
	int c, col, found, i, r, row;
	char buf[MAXWORDLEN + 1];
	extern char board[];
	extern int usedbits, wordpath[];
	extern char *mword[], *pword[];
	extern int nmwords, npwords;

	getyx(stdscr, r, c);
	getword(buf);
	found = 0;
	for (i = 0; i < npwords; i++) {
		if (strcmp(buf, pword[i]) == 0) {
			found = 1;
			break;
		}
	}
	if (!found) {
		for (i = 0; i < nmwords; i++) {
			if (strcmp(buf, mword[i]) == 0) {
				found = 1;
				break;
			}
		}
	}
	for (i = 0; i < MAXWORDLEN; i++)
		wordpath[i] = -1;
	usedbits = 0;
	if (!found || checkword(buf, -1, wordpath) == -1) {
		move(r, c);
		clrtoeol();
		addstr("[???]");
		refresh();
		delay(10);
		move(r, c);
		clrtoeol();
		refresh();
		return;
	}

	standout();
	for (i = 0; wordpath[i] != -1; i++) {
		row = BOARD_LINE + (wordpath[i] / 4) * 2 + 1;
		col = BOARD_COL + (wordpath[i] % 4) * 4 + 2;
		move(row, col);
		if (board[wordpath[i]] == 'q')
			printw("Qu");
		else
			printw("%c", toupper(board[wordpath[i]]));
		move(r, c);
		refresh();
		delay(5);
	}

	standend();

	for (i = 0; wordpath[i] != -1; i++) {
		row = BOARD_LINE + (wordpath[i] / 4) * 2 + 1;
		col = BOARD_COL + (wordpath[i] % 4) * 4 + 2;
		move(row, col);
		if (board[wordpath[i]] == 'q')
			printw("Qu");
		else
			printw("%c", toupper(board[wordpath[i]]));
	}
	move(r, c);
	clrtoeol();
	refresh();
}

/*
 * Display a string at the current cursor position for the given number of secs
 */
I 2
void
E 2
showstr(str, delaysecs)
D 2
char *str;
int delaysecs;
E 2
I 2
	char *str;
	int delaysecs;
E 2
{
D 2

E 2
	addstr(str);
	refresh();
	delay(delaysecs * 10);
	move(crow, ccol);
	clrtoeol();
	refresh();
}

I 2
void
E 2
putstr(s)
D 2
char *s;
E 2
I 2
	char *s;
E 2
{
D 2

E 2
	addstr(s);
}

/*
 * Get a valid word and put it in the buffer
 */
I 2
void
E 2
getword(q)
D 2
char *q;
E 2
I 2
	char *q;
E 2
{
	int ch, col, done, i, row;
	char *p;

	done = 0;
	i = 0;
	p = q;
	addch('[');
	refresh();
	while (!done && i < MAXWORDLEN - 1) {
		ch = getch() & 0177;
		switch (ch) {
		case '\177':			/* <del> */
		case '\010':			/* <bs> */
			if (p == q)
				break;
			p--;
			getyx(stdscr, row, col);
			move(row, col - 1);
			clrtoeol();
			break;
		case '\025':			/* <^u> */
		case '\027':			/* <^w> */
			if (p == q)
				break;
			getyx(stdscr, row, col);
			move(row, col - (int) (p - q));
			p = q;
			clrtoeol();
			break;
		case ' ':
		case '\n':
		case '\r':
			done = 1;
			break;
		case '\014':			/* <^l> */
		case '\022':			/* <^r> */
			clearok(stdscr, 1);
			refresh();
			break;
		default:
			if (islower(ch)) {
				*p++ = ch;
				addch(ch);
				i++;
			}
			break;
		}
		refresh();
	}
	*p = '\0';
	addch(']');
	refresh();
}

I 2
void
E 2
showboard(b)
D 2
char *b;
E 2
I 2
	char *b;
E 2
{
D 2

E 2
	tty_showboard(b);
}

I 2
void
E 2
prompt(mesg)
D 2
char *mesg;
E 2
I 2
	char *mesg;
E 2
{
D 2

E 2
	move(PROMPT_LINE, PROMPT_COL);
	printw("%s", mesg);
	move(PROMPT_LINE + 1, PROMPT_COL);
	refresh();
}

D 2
rawch()
{

#ifdef TIMER
	return(timerch());
#else
	return(getch() & 0177);
#endif
}

static
E 2
I 2
static int
E 2
tty_setup()
{
D 2
#ifdef SIGTSTP
	int stop_catcher(), cont_catcher();
#endif
#ifdef TIOCGWINSZ
	int winch_catcher();
#endif

E 2
	initscr();
	raw();
	noecho();

	/*
	 * Does curses look at the winsize structure?
	 * Should handle SIGWINCH ...
	 */
	nlines = LINES;
	lastline = nlines - 1;
	ncols = COLS;

D 2
#ifdef SIGTSTP
    (void) signal(SIGTSTP, stop_catcher);
    (void) signal(SIGCONT, cont_catcher);
#endif   
#ifdef TIOCGWINSZ
E 2
I 2
	(void) signal(SIGTSTP, stop_catcher);
	(void) signal(SIGCONT, cont_catcher);
E 2
	(void) signal(SIGWINCH, winch_catcher);
D 2
#endif
 
E 2
	return(0);
}

D 2
#ifdef SIGTSTP
static
stop_catcher()
E 2
I 2
static void
stop_catcher(signo)
	int signo;
E 2
{
D 2

E 2
	stoptime();
	noraw();
	echo();
	move(nlines - 1, 0);
	refresh();

	(void) signal(SIGTSTP, SIG_DFL);
D 2
#ifdef BSD42 
E 2
	(void) sigsetmask(sigblock(0) & ~(1 << (SIGTSTP-1)));
D 2
#endif
E 2
	(void) kill(0, SIGTSTP);
	(void) signal(SIGTSTP, stop_catcher);
}
 
D 2
static
cont_catcher()
E 2
I 2
static void
cont_catcher(signo)
	int signo;
E 2
{
D 2

E 2
	(void) signal(SIGCONT, cont_catcher);
	noecho();
	raw();
	clearok(stdscr, 1);
	move(crow, ccol);
	refresh();
	starttime();
}
D 2
#endif SIGTSTP
E 2
 
D 2
#ifdef SIGWINCH
E 2
/*
 * The signal is caught but nothing is done about it...
 * It would mean reformatting the entire display
 */
D 2
static
winch_catcher()
E 2
I 2
static void
winch_catcher(signo)
	int signo;
E 2
{
D 2

E 2
	struct winsize win;

	(void) signal(SIGWINCH, winch_catcher);
	(void) ioctl(fileno(stdout), TIOCGWINSZ, &win);
	/*
	LINES = win.ws_row;
	COLS = win.ws_col;
	*/
}
D 2
#endif
E 2

D 2
static
E 2
I 2
static void
E 2
tty_cleanup()
{
D 2

E 2
	move(nlines - 1, 0);
	refresh();
	noraw();
	echo();
	endwin();
}

D 2
static
E 2
I 2
static void
E 2
tty_showboard(b)
D 2
char *b;
E 2
I 2
	char *b;
E 2
{
	register int i;
	int line;

	clear();
	move(BOARD_LINE, BOARD_COL);
	line = BOARD_LINE;
	printw("+---+---+---+---+");
	move(++line, BOARD_COL);
	for (i = 0; i < 16; i++) {
		if (b[i] == 'q')
			printw("| Qu");
		else
			printw("| %c ", toupper(b[i]));
		if ((i + 1) % 4 == 0) {
			printw("|");
			move(++line, BOARD_COL);
			printw("+---+---+---+---+");
			move(++line, BOARD_COL);
		}
	}
D 2
    move(SCORE_LINE, SCORE_COL);
E 2
I 2
	move(SCORE_LINE, SCORE_COL);
E 2
	printw("Type '?' for help");
	refresh();
}
D 2

static
tty_prompt(p)
char *p;
{

	move(PROMPT_LINE, PROMPT_COL);
	printw("%s", p);
	clrtoeol();
	refresh();
}

E 2
E 1
