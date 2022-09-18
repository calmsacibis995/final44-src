h15516
s 00005/00005/00281
d D 8.1 93/05/31 17:54:17 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00048/00027/00238
d D 5.3 92/12/23 10:58:04 bostic 3 2
c make tetris use getopt, add SIGINT handler so you can quit
e
s 00003/00000/00262
d D 5.2 92/12/23 10:16:48 bostic 2 1
c update copyright notice with contrib notice
e
s 00262/00000/00000
d D 5.1 92/12/22 11:50:43 bostic 1 0
c date and time created 92/12/22 11:50:43 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Chris Torek and Darren F. Provine.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef lint
D 4
char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 4
I 4
static char copyright[] =
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 4
#endif /* not lint */

/*
 * Tetris (or however it is spelled).
 */

#include <sys/time.h>

I 3
#include <signal.h>
E 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "input.h"
#include "scores.h"
#include "screen.h"
#include "tetris.h"

I 3
void onintr __P((int));
void usage __P((void));

E 3
/*
D 3
 * Set up the initial board.
 * The bottom display row is completely set,
 * along with another (hidden) row underneath that.
 * Also, the left and right edges are set.
E 3
I 3
 * Set up the initial board.  The bottom display row is completely set,
 * along with another (hidden) row underneath that.  Also, the left and
 * right edges are set.
E 3
 */
static void
setup_board()
{
	register int i;
	register cell *p;

	p = board;
	for (i = B_SIZE; i; i--)
#ifndef mips
		*p++ = i <= (2 * B_COLS) || (i % B_COLS) < 2;
#else /* work around compiler bug */
		*p++ = i <= (2 * B_COLS) || (i % B_COLS) < 2 ? 1 : 0;
#endif
}

/*
 * Elide any full active rows.
 */
static void
elide()
{
	register int i, j, base;
	register cell *p;

	for (i = A_FIRST; i < A_LAST; i++) {
		base = i * B_COLS + 1;
		p = &board[base];
		for (j = B_COLS - 2; *p++ != 0;) {
			if (--j <= 0) {
				/* this row is to be elided */
				bzero(&board[base], B_COLS - 2);
				scr_update();
				tsleep();
				while (--base != 0)
					board[base + B_COLS] = board[base];
				scr_update();
				tsleep();
				break;
			}
		}
	}
}

int
main(argc, argv)
	int argc;
D 3
	char **argv;
E 3
I 3
	char *argv[];
E 3
{
	register int pos, c;
	register struct shape *curshape;
	register char *keys;
	register int level = 2;
	char key_write[6][10];
D 3
	int i, j;
E 3
I 3
	int ch, i, j;
E 3

	keys = "jkl pq";

D 3
	if (argc > 3)
		goto usage;

	while (argc-- >= 2)
		switch (argv[argc][0]) {

		case '-':
			keys = argv[argc];
			keys++;
			if (strlen(keys) < 6) {
	usage:
E 3
I 3
	while ((ch = getopt(argc, argv, "k:l:s")) != EOF)
		switch(ch) {
		case 'k':
			if (strlen(keys = optarg) != 6)
				usage();
			break;
		case 'l':
			level = atoi(optarg);
			if (level < MINLEVEL || level > MAXLEVEL) {
E 3
				(void)fprintf(stderr,
D 3
				    "usage: %s [level] [-keys]\n",
				    argv[0]);
E 3
I 3
				    "tetris: level must be from %d to %d",
				    MINLEVEL, MAXLEVEL);
E 3
				exit(1);
			}
			break;
D 3

E 3
I 3
		case 's':
			showscores(0);
			exit(0);
		case '?':
E 3
		default:
D 3
			level = atoi(argv[argc]);
			if (level < MINLEVEL) {
				showscores(level);
				exit(0);
			}
			if (level > MAXLEVEL)
				level = MAXLEVEL;
E 3
I 3
			usage();
E 3
		}

I 3
	argc -= optind;
	argv += optind;

	if (argc)
		usage();

E 3
	fallrate = 1000000 / level;

	for (i = 0; i <= 5; i++) {
		for (j = i+1; j <= 5; j++) {
			if (keys[i] == keys[j]) {
				(void)fprintf(stderr,
				    "%s: Duplicate command keys specified.\n",
				    argv[0]);
				exit (1);
			}
		}
		if (keys[i] == ' ')
			strcpy(key_write[i], "<space>");
		else {
			key_write[i][0] = keys[i];
			key_write[i][1] = '\0';
		}
	}

	sprintf(key_msg,
"%s - left   %s - rotate   %s - right   %s - drop   %s - pause   %s - quit",
		key_write[0], key_write[1], key_write[2], key_write[3],
		key_write[4], key_write[5]);

I 3
	(void)signal(SIGINT, onintr);
E 3
	scr_init();
	setup_board();

	srandom(getpid());
	scr_set();

	pos = A_FIRST*B_COLS + (B_COLS/2)-1;
	curshape = randshape();

	scr_msg(key_msg, 1);

	for (;;) {
		place(curshape, pos, 1);
		scr_update();
		place(curshape, pos, 0);
		c = tgetchar();
		if (c < 0) {
			/*
			 * Timeout.  Move down if possible.
			 */
			if (fits_in(curshape, pos + B_COLS)) {
				pos += B_COLS;
				continue;
			}

			/*
			 * Put up the current shape `permanently',
			 * bump score, and elide any full rows.
			 */
			place(curshape, pos, 1);
			score++;
			elide();

			/*
			 * Choose a new shape.  If it does not fit,
			 * the game is over.
			 */
			curshape = randshape();
			pos = A_FIRST*B_COLS + (B_COLS/2)-1;
			if (!fits_in(curshape, pos))
				break;
			continue;
		}

		/*
		 * Handle command keys.
		 */
		if (c == keys[5]) {
			/* quit */
			break;
		}
		if (c == keys[4]) {
			static char msg[] =
			    "paused - press RETURN to continue";

			place(curshape, pos, 1);
			do {
				scr_update();
				scr_msg(key_msg, 0);
				scr_msg(msg, 1);
				(void) fflush(stdout);
			} while (rwait((struct timeval *)NULL) == -1);
			scr_msg(msg, 0);
			scr_msg(key_msg, 1);
			place(curshape, pos, 0);
			continue;
		}
		if (c == keys[0]) {
			/* move left */
			if (fits_in(curshape, pos - 1))
				pos--;
			continue;
		}
		if (c == keys[1]) {
			/* turn */
			struct shape *new = &shapes[curshape->rot];

			if (fits_in(new, pos))
				curshape = new;
			continue;
		}
		if (c == keys[2]) {
			/* move right */
			if (fits_in(curshape, pos + 1))
				pos++;
			continue;
		}
		if (c == keys[3]) {
			/* move to bottom */
			while (fits_in(curshape, pos + B_COLS)) {
				pos += B_COLS;
				score++;
			}
			continue;
		}
		if (c == '\f')
			scr_clear();
	}

	scr_clear();
	scr_end();

	(void)printf("Your score:  %d point%s  x  level %d  =  %d\n",
	    score, score == 1 ? "" : "s", level, score * level);
	savescore(level);

	printf("\nHit RETURN to see high scores, ^C to skip.\n");

	while ((i = getchar()) != '\n')
		if (i == EOF)
			break;

	showscores(level);

	exit(0);
I 3
}

void
onintr(signo)
	int signo;
{
	scr_clear();
	scr_end();
	exit(0);
}

void
usage()
{
	(void)fprintf(stderr, "usage: tetris [-s] [-l level] [-keys]\n");
	exit(1);
E 3
}
E 1
