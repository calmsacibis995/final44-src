h39706
s 00001/00001/00091
d D 8.2 94/02/22 12:58:36 bostic 4 3
c <unistd.h> used to include time.h, and no longer does
e
s 00002/00002/00090
d D 8.1 93/06/11 14:48:17 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00113/00058
d D 5.2 93/06/11 14:44:00 bostic 2 1
c integrate into 4.4BSD
e
s 00171/00000/00000
d D 5.1 93/06/10 11:09:54 bostic 1 0
c date and time created 93/06/10 11:09:54 by bostic
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

D 2
#include "bog.h"
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

D 2
#ifdef TIMER
E 2
I 2
#include <sys/param.h>
I 4
#include <sys/time.h>
E 4
E 2

D 2
#include <setjmp.h>
E 2
#include <curses.h>
I 2
#include <setjmp.h>
E 2
#include <stdio.h>
I 2
D 4
#include <time.h>
E 4
#include <unistd.h>
E 2

D 2
static int waitch();
E 2
I 2
#include "bog.h"
#include "extern.h"
E 2

I 2
static int waitch __P((long));

E 2
/*
 * Update the display of the remaining time while waiting for a character
 * If time runs out do a longjmp() to the game controlling routine, returning
 * non-zero; oth. return the character
 * Leave the cursor where it was initially
 */
I 2
int
E 2
timerch()
{
D 2
	int col, remaining, row;
	long prevt, t;
E 2
	extern int tlimit;
	extern long start_t;
	extern jmp_buf env;
I 2
	long prevt, t;
	int col, remaining, row;
E 2

	getyx(stdscr, row, col);
	prevt = 0L;
D 2
	while (1) {
E 2
I 2
	for (;;) {
E 2
		if (waitch(1000L) == 1)
			break;
		time(&t);
		if (t == prevt)
			continue;
		prevt = t;
		remaining = tlimit - (int) (t - start_t);
		if (remaining < 0) {
			longjmp(env, 1);
			/*NOTREACHED*/
		}
		move(TIMER_LINE, TIMER_COL);
		printw("%d:%02d", remaining / 60, remaining % 60);
		move(row, col);
		refresh();
	}
D 2
	return(getch() & 0177);
E 2
I 2
	return (getch() & 0177);
E 2
}

/*
 * Wait up to 'delay' microseconds for input to appear
 * Returns 1 if input is ready, 0 oth.
 */
D 2

#ifdef BSD42

#include <sys/time.h>

static
E 2
I 2
static int
E 2
waitch(delay)
D 2
long delay;
E 2
I 2
	long delay;
E 2
{
D 2
	int fdbits;
E 2
I 2
	fd_set fdbits;
E 2
	struct timeval duration;

D 2
	duration.tv_sec = 0L;
E 2
I 2
	duration.tv_sec = 0;
E 2
	duration.tv_usec = delay;
D 2
	fdbits = 1;
	return(select(32, &fdbits, 0, 0, &duration));
E 2
I 2
	FD_ZERO(&fdbits);
	FD_SET(STDIN_FILENO, &fdbits);
	return (select(32, &fdbits, NULL, NULL, &duration));
E 2
}

I 2
void
E 2
delay(tenths)
D 2
int tenths;
E 2
I 2
	int tenths;
E 2
{
	struct timeval duration;

	duration.tv_usec = (tenths % 10 ) * 100000L;
	duration.tv_sec = (long) (tenths / 10);
	select(32, 0, 0, 0, &duration);
}
D 2
#endif BSD42

#ifdef SYSV

#include <sys/ioctl.h>

/*
 * This is not too efficient...
 */
static
waitch(delay)
long delay;
{
	int nchars;

	if (ioctl(fileno(stdin), FIONREAD, &nchars) < 0) {
		perror("ioctl():");
		cleanup();
		exit(1);
	}
	return(nchars > 0);
}

/*
 * Do nothing for the given number of tenths of a second
 */
delay(tenths)
int tenths;
{
	int n;

	n = tenths / 10;
	if (n == 0)
		n == 1;
	sleep(n);
}

#endif SYSV

#ifdef ATARI

#include <osbind.h>

/*
 * The ST curses turns on the cursor only when a read is performed
 * Since there's nothing better to do at this point the cursor can
 * be enabled
 */
static
waitch(delay)
long delay;
{

	Bconout(2, '\033');
	Bconout(2, 'e');
	return(Cconis() == -1);
}

/*
 * Do nothing for the given number of tenths of a second
 */
delay(tenths)
int tenths;
{
	int n;

	n = tenths / 10;
	if (n == 0)
		n == 1;
	sleep(n);
}

#endif ATARI

#else !TIMER

/*
 * Do nothing for the given number of tenths of a second
 */
delay(tenths)
int tenths;
{
	int n;

	n = tenths / 10;
	if (n == 0)
		n == 1;
	sleep(n);
}

#endif TIMER

E 2
E 1
