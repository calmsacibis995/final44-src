h03488
s 00002/00002/00355
d D 8.1 93/06/06 15:36:35 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00012/00356
d D 5.6 90/06/01 17:04:12 bostic 6 5
c new copyright notice
e
s 00025/00049/00343
d D 5.5 88/11/22 16:51:29 bostic 5 4
c less -> more
e
s 00002/00004/00390
d D 5.4 88/07/25 12:04:56 bostic 4 3
c update copyright notice
e
s 00001/00001/00393
d D 5.3 88/07/22 12:04:48 bostic 3 2
c void sprintfs
e
s 00000/00020/00394
d D 5.2 88/07/21 19:04:51 bostic 2 1
c rip out GET_TIME define
e
s 00414/00000/00000
d D 5.1 88/07/21 18:52:54 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 7
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 4
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 4
D 6
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 4
 * by the University of California, Berkeley.  The name of the
E 4
I 4
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 4
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Code to handle displaying line numbers.
 *
 * Finding the line number of a given file position is rather tricky.
 * We don't want to just start at the beginning of the file and
 * count newlines, because that is slow for large files (and also
 * wouldn't work if we couldn't get to the start of the file; e.g.
 * if input is a long pipe).
 *
 * So we use the function add_lnum to cache line numbers.
 * We try to be very clever and keep only the more interesting
 * line numbers when we run out of space in our table.  A line
 * number is more interesting than another when it is far from
 * other line numbers.   For example, we'd rather keep lines
 * 100,200,300 than 100,101,300.  200 is more interesting than
 * 101 because 101 can be derived very cheaply from 100, while
 * 200 is more expensive to derive from 100.
 *
 * The function currline() returns the line number of a given
 * position in the file.  As a side effect, it calls add_lnum
 * to cache the line number.  Therefore currline is occasionally
 * called to make sure we cache line numbers often enough.
 */

D 5
#include "less.h"
#include "position.h"
E 5
I 5
#include <sys/types.h>
#include <stdio.h>
#include <less.h>
E 5

/*
 * Structure to keep track of a line number and the associated file position.
 * A doubly-linked circular list of line numbers is kept ordered by line number.
 */
struct linenum
{
	struct linenum *next;		/* Link to next in the list */
	struct linenum *prev;		/* Line to previous in the list */
D 5
	POSITION pos;			/* File position */
	POSITION gap;			/* Gap between prev and next */
E 5
I 5
	off_t pos;			/* File position */
	off_t gap;			/* Gap between prev and next */
E 5
	int line;			/* Line number */
};
/*
 * "gap" needs some explanation: the gap of any particular line number
 * is the distance between the previous one and the next one in the list.
 * ("Distance" means difference in file position.)  In other words, the
 * gap of a line number is the gap which would be introduced if this
 * line number were deleted.  It is used to decide which one to replace
 * when we have a new one to insert and the table is full.
 */

#define	NPOOL	50			/* Size of line number pool */

#define	LONGTIME	(2)		/* In seconds */

D 5
public int lnloop = 0;			/* Are we in the line num loop? */
E 5
I 5
int lnloop = 0;				/* Are we in the line num loop? */
E 5

static struct linenum anchor;		/* Anchor of the list */
static struct linenum *freelist;	/* Anchor of the unused entries */
static struct linenum pool[NPOOL];	/* The pool itself */
static struct linenum *spare;		/* We always keep one spare entry */

extern int linenums;
extern int sigs;

/*
 * Initialize the line number structures.
 */
D 5
	public void
E 5
clr_linenum()
{
	register struct linenum *p;

	/*
	 * Put all the entries on the free list.
	 * Leave one for the "spare".
	 */
	for (p = pool;  p < &pool[NPOOL-2];  p++)
		p->next = p+1;
	pool[NPOOL-2].next = NULL;
	freelist = pool;

	spare = &pool[NPOOL-1];

	/*
	 * Initialize the anchor.
	 */
	anchor.next = anchor.prev = &anchor;
	anchor.gap = 0;
D 5
	anchor.pos = (POSITION)0;
E 5
I 5
	anchor.pos = (off_t)0;
E 5
	anchor.line = 1;
}

/*
 * Calculate the gap for an entry.
 */
D 5
	static void
E 5
I 5
static
E 5
calcgap(p)
	register struct linenum *p;
{
	/*
	 * Don't bother to compute a gap for the anchor.
	 * Also don't compute a gap for the last one in the list.
	 * The gap for that last one should be considered infinite,
	 * but we never look at it anyway.
	 */
	if (p == &anchor || p->next == &anchor)
		return;
	p->gap = p->next->pos - p->prev->pos;
}

/*
 * Add a new line number to the cache.
 * The specified position (pos) should be the file position of the
 * FIRST character in the specified line.
 */
D 5
	public void
E 5
add_lnum(line, pos)
	int line;
D 5
	POSITION pos;
E 5
I 5
	off_t pos;
E 5
{
	register struct linenum *p;
	register struct linenum *new;
	register struct linenum *nextp;
	register struct linenum *prevp;
D 5
	register POSITION mingap;
E 5
I 5
	register off_t mingap;
E 5

	/*
	 * Find the proper place in the list for the new one.
	 * The entries are sorted by position.
	 */
	for (p = anchor.next;  p != &anchor && p->pos < pos;  p = p->next)
		if (p->line == line)
			/* We already have this one. */
			return;
	nextp = p;
	prevp = p->prev;

	if (freelist != NULL)
	{
		/*
		 * We still have free (unused) entries.
		 * Use one of them.
		 */
		new = freelist;
		freelist = freelist->next;
	} else
	{
		/*
		 * No free entries.
		 * Use the "spare" entry.
		 */
		new = spare;
		spare = NULL;
	}

	/*
	 * Fill in the fields of the new entry,
	 * and insert it into the proper place in the list.
	 */
	new->next = nextp;
	new->prev = prevp;
	new->pos = pos;
	new->line = line;

	nextp->prev = new;
	prevp->next = new;

	/*
	 * Recalculate gaps for the new entry and the neighboring entries.
	 */
	calcgap(new);
	calcgap(nextp);
	calcgap(prevp);

	if (spare == NULL)
	{
		/*
		 * We have used the spare entry.
		 * Scan the list to find the one with the smallest
		 * gap, take it out and make it the spare.
		 * We should never remove the last one, so stop when
		 * we get to p->next == &anchor.  This also avoids
		 * looking at the gap of the last one, which is
		 * not computed by calcgap.
		 */
		mingap = anchor.next->gap;
		for (p = anchor.next;  p->next != &anchor;  p = p->next)
		{
			if (p->gap <= mingap)
			{
				spare = p;
				mingap = p->gap;
			}
		}
		spare->next->prev = spare->prev;
		spare->prev->next = spare->next;
	}
}

/*
 * If we get stuck in a long loop trying to figure out the
 * line number, print a message to tell the user what we're doing.
 */
D 5
	static void
E 5
I 5
static
E 5
longloopmessage()
{
	ierror("Calculating line numbers");
	/*
	 * Set the lnloop flag here, so if the user interrupts while
	 * we are calculating line numbers, the signal handler will 
	 * turn off line numbers (linenums=0).
	 */
	lnloop = 1;
}

/*
 * Find the line number associated with a given position.
 * Return 0 if we can't figure it out.
 */
D 5
	public int
E 5
find_linenum(pos)
D 5
	POSITION pos;
E 5
I 5
	off_t pos;
E 5
{
	register struct linenum *p;
	register int lno;
	register int loopcount;
D 5
	POSITION cpos;
D 2
#if GET_TIME
E 2
	long startime;
E 5
I 5
	off_t cpos, back_raw_line(), forw_raw_line();
	time_t startime, time();
E 5
D 2
#endif
E 2

	if (!linenums)
		/*
		 * We're not using line numbers.
		 */
		return (0);
	if (pos == NULL_POSITION)
		/*
		 * Caller doesn't know what he's talking about.
		 */
		return (0);
D 5
	if (pos == (POSITION)0)
E 5
I 5
	if (pos == (off_t)0)
E 5
		/*
		 * Beginning of file is always line number 1.
		 */
		return (1);

	/*
	 * Find the entry nearest to the position we want.
	 */
	for (p = anchor.next;  p != &anchor && p->pos < pos;  p = p->next)
		continue;
	if (p->pos == pos)
		/* Found it exactly. */
		return (p->line);

	/*
	 * This is the (possibly) time-consuming part.
	 * We start at the line we just found and start
	 * reading the file forward or backward till we
	 * get to the place we want.
	 *
	 * First decide whether we should go forward from the 
	 * previous one or backwards from the next one.
	 * The decision is based on which way involves 
	 * traversing fewer bytes in the file.
	 */
	flush();
D 2
#if GET_TIME
E 2
D 5
	startime = get_time();
E 5
I 5
	(void)time(&startime);
E 5
D 2
#endif
E 2
	if (p == &anchor || pos - p->prev->pos < p->pos - pos)
	{
		/*
		 * Go forward.
		 */
		p = p->prev;
		if (ch_seek(p->pos))
			return (0);
		loopcount = 0;
		for (lno = p->line, cpos = p->pos;  cpos < pos;  lno++)
		{
			/*
			 * Allow a signal to abort this loop.
			 */
			cpos = forw_raw_line(cpos);
			if (sigs || cpos == NULL_POSITION)
				return (0);
D 2
#if GET_TIME
E 2
D 5
			if (loopcount >= 0 && ++loopcount > 100)
			{
E 5
I 5
			if (loopcount >= 0 && ++loopcount > 100) {
E 5
				loopcount = 0;
D 5
				if (get_time() >= startime + LONGTIME)
				{
E 5
I 5
				if (time((time_t *)NULL)
				    >= startime + LONGTIME) {
E 5
					longloopmessage();
					loopcount = -1;
				}
			}
D 2
#else
			if (loopcount >= 0 && ++loopcount > LONGLOOP)
			{
				longloopmessage();
				loopcount = -1;
			}
#endif
E 2
		}
		lnloop = 0;
		/*
		 * If the given position is not at the start of a line,
		 * make sure we return the correct line number.
		 */
		if (cpos > pos)
			lno--;
	} else
	{
		/*
		 * Go backward.
		 */
		if (ch_seek(p->pos))
			return (0);
		loopcount = 0;
		for (lno = p->line, cpos = p->pos;  cpos > pos;  lno--)
		{
			/*
			 * Allow a signal to abort this loop.
			 */
			cpos = back_raw_line(cpos);
			if (sigs || cpos == NULL_POSITION)
				return (0);
D 2
#if GET_TIME
E 2
D 5
			if (loopcount >= 0 && ++loopcount > 100)
			{
E 5
I 5
			if (loopcount >= 0 && ++loopcount > 100) {
E 5
				loopcount = 0;
D 5
				if (get_time() >= startime + LONGTIME)
				{
E 5
I 5
				if (time((time_t *)NULL)
				    >= startime + LONGTIME) {
E 5
					longloopmessage();
					loopcount = -1;
				}
			}
D 2
#else
			if (loopcount >= 0 && ++loopcount > LONGLOOP)
			{
				longloopmessage();
				loopcount = -1;
			}
#endif
E 2
		}
		lnloop = 0;
	}

	/*
	 * We might as well cache it.
	 */
	add_lnum(lno, cpos);
	return (lno);
}

/*
 * Return the line number of the "current" line.
 * The argument "where" tells which line is to be considered
 * the "current" line (e.g. TOP, BOTTOM, MIDDLE, etc).
 */
D 5
	public int
E 5
currline(where)
	int where;
{
D 5
	POSITION pos;
E 5
I 5
	off_t pos, ch_length(), position();
E 5

D 5
	pos = position(where);
	if (pos == NULL_POSITION)
E 5
I 5
	if ((pos = position(where)) == NULL_POSITION)
E 5
		pos = ch_length();
D 5
	return (find_linenum(pos));
E 5
I 5
	return(find_linenum(pos));
E 5
}
D 5

#if DEBUG_STUFF
debug()
{
	register struct linenum *p;
	char buf[20];

	lower_left();
	clear_eol();
	for (p = anchor.next;  p != &anchor;  p = p->next)
	{
D 3
		sprintf(buf, "%d-%d ", p->line, p->pos);
E 3
I 3
		(void)sprintf(buf, "%d-%d ", p->line, p->pos);
E 3
		putstr(buf);
	}
	putstr("\n");
	error("DEBUG");
}
#endif /*DEBUG_STUFF*/
E 5
E 1
