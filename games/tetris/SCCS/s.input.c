h20492
s 00002/00002/00152
d D 8.1 93/05/31 17:53:51 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00150
d D 5.2 92/12/23 10:16:42 bostic 2 1
c update copyright notice with contrib notice
e
s 00150/00000/00000
d D 5.1 92/12/22 11:50:35 bostic 1 0
c date and time created 92/12/22 11:50:35 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
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

/*
 * Tetris input.
 */

#include <sys/types.h>
#include <sys/time.h>
I 2

E 2
#include <errno.h>
#include <unistd.h>

#include "input.h"
#include "tetris.h"

/* return true iff the given timeval is positive */
#define	TV_POS(tv) \
	((tv)->tv_sec > 0 || ((tv)->tv_sec == 0 && (tv)->tv_usec > 0))

/* subtract timeval `sub' from `res' */
#define	TV_SUB(res, sub) \
	(res)->tv_sec -= (sub)->tv_sec; \
	(res)->tv_usec -= (sub)->tv_usec; \
	if ((res)->tv_usec < 0) { \
		(res)->tv_usec += 1000000; \
		(res)->tv_sec--; \
	}

/*
 * Do a `read wait': select for reading from stdin, with timeout *tvp.
 * On return, modify *tvp to reflect the amount of time spent waiting.
 * It will be positive only if input appeared before the time ran out;
 * otherwise it will be zero or perhaps negative.
 *
 * If tvp is nil, wait forever, but return if select is interrupted.
 *
 * Return 0 => no input, 1 => can read() from stdin
 */
int
rwait(tvp)
	register struct timeval *tvp;
{
	int i;
	struct timeval starttv, endtv, *s;
	extern int errno;
#define	NILTZ ((struct timezone *)0)

	/*
	 * Someday, select() will do this for us.
	 * Just in case that day is now, and no one has
	 * changed this, we use a temporary.
	 */
	if (tvp) {
		(void) gettimeofday(&starttv, NILTZ);
		endtv = *tvp;
		s = &endtv;
	} else
		s = 0;
again:
	i = 1;
	switch (select(1, (fd_set *)&i, (fd_set *)0, (fd_set *)0, s)) {

	case -1:
		if (tvp == 0)
			return (-1);
		if (errno == EINTR)
			goto again;
		stop("select failed, help");
		/* NOTREACHED */

	case 0:	/* timed out */
		tvp->tv_sec = 0;
		tvp->tv_usec = 0;
		return (0);
	}
	if (tvp) {
		/* since there is input, we may not have timed out */
		(void) gettimeofday(&endtv, NILTZ);
		TV_SUB(&endtv, &starttv);
		TV_SUB(tvp, &endtv);	/* adjust *tvp by elapsed time */
	}
	return (1);
}

/*
 * `sleep' for the current turn time (using select).
 * Eat any input that might be available.
 */
void
tsleep()
{
	struct timeval tv;
	char c;

	tv.tv_sec = 0;
	tv.tv_usec = fallrate;
	while (TV_POS(&tv))
		if (rwait(&tv) && read(0, &c, 1) != 1)
			break;
}

/*
 * Eat up any input (used at end of game).
 */
void
eat_input()
{
	struct timeval tv;
	char c;

	do {
		tv.tv_sec = tv.tv_usec = 0;
	} while (rwait(&tv) && read(0, &c, 1) == 1);
}

/*
 * getchar with timeout.
 */
int
tgetchar()
{
	static struct timeval timeleft;
	char c;

	/*
	 * Reset timeleft to fallrate whenever it is not positive.
	 * In any case, wait to see if there is any input.  If so,
	 * take it, and update timeleft so that the next call to
	 * tgetchar() will not wait as long.  If there is no input,
	 * make timeleft zero or negative, and return -1.
	 *
	 * Most of the hard work is done by rwait().
	 */
	if (!TV_POS(&timeleft)) {
		faster();	/* go faster */
		timeleft.tv_sec = 0;
		timeleft.tv_usec = fallrate;
	}
	if (!rwait(&timeleft))
		return (-1);
	if (read(0, &c, 1) != 1)
		stop("end of file, help");
	return ((int)(unsigned char)c);
}
E 1
