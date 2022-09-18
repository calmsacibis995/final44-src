h52963
s 00058/00116/00075
d D 8.1 94/01/21 18:46:13 mckusick 2 1
c update for 4.4BSD-Lite
e
s 00191/00000/00000
d D 1.1 91/06/28 16:45:35 mckusick 1 0
c date and time created 91/06/28 16:45:35 by mckusick
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1982, 1986, 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 2
 *
 * %sccs.include.redist.c%
 *
D 2
 *	from: @(#)tty_subr.c	7.7 (Berkeley) 5/9/91
E 2
I 2
 *	from: @(#)tty_subr.c	8.2 (Berkeley) 9/5/93
E 2
 */

D 2
#include "param.h"
#include "systm.h"
#include "buf.h"
#include "ioctl.h"
#include "tty.h"
#include "clist.h"
E 2
I 2
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
E 2

D 2
/*
 * Initialize clists.
 */
cinit()
E 2
I 2
char cwaiting;
struct cblock *cfree, *cfreelist;
int cfreecount, nclist;

void
clist_init()
E 2
{

	/*
	 * Body deleted.
	 */
I 2
	return;
E 2
}

D 2
/*
 * Get a character from a clist.
 */
getc(clp)
	struct clist *clp;
E 2
I 2
getc(a1)
	struct clist *a1;
E 2
{
D 2
	char c;
E 2

	/*
	 * Body deleted.
	 */
D 2
	return (c);
E 2
I 2
	return ((char)0);
E 2
}

D 2
/*
 * Copy clist to buffer.
 * Return number of bytes moved.
 */
q_to_b(clp, cp, count)
	struct clist *clp;
	char *cp;
	int count;
E 2
I 2
q_to_b(a1, a2, a3)
	struct clist *a1;
	char *a2;
	int a3;
E 2
{
D 2
	int s, moved = 0;
E 2

D 2
	if (count <= 0)
		return (0);
	s = spltty();
E 2
	/*
	 * Body deleted.
	 */
D 2
	splx(s);
	return (moved);
E 2
I 2
	return (0);
E 2
}

D 2
/*
 * Return count of contiguous characters in clist.
 * Stop counting if flag&character is non-null.
 */
ndqb(clp, flag)
	struct clist *clp;
	int flag;
E 2
I 2
ndqb(a1, a2)
	struct clist *a1;
	int a2;
E 2
{
D 2
	int count = 0;
	int s;
E 2

D 2
	s = spltty();
E 2
	/*
	 * Body deleted.
	 */
D 2
	splx(s);
	return (count);
E 2
I 2
	return (0);
E 2
}

D 2
/*
 * Flush count bytes from clist.
 */
ndflush(clp, count)
	struct clist *clp;
	int count;
E 2
I 2
void
ndflush(a1, a2)
	struct clist *a1;
	int a2;
E 2
{
D 2
	int s;
E 2

D 2
	s = spltty();
E 2
	/*
	 * Body deleted.
	 */
D 2
	splx(s);
E 2
I 2
	return;
E 2
}

D 2
/*
 * Put a character into the output queue.
 */
putc(c, clp)
	char c;
	struct clist *clp;
E 2
I 2
putc(a1, a2)
	char a1;
	struct clist *a2;
E 2
{
D 2
	int s, error = 0;
E 2

D 2
	s = spltty();
E 2
	/*
	 * Body deleted.
	 */
D 2
	if (error) {
		splx(s);
		return (-1);
	}
	splx(s);
E 2
	return (0);
}

D 2
/*
 * Copy buffer to clist.
 * Return number of bytes not transfered.
 */
b_to_q(cp, count, clp)
	char *cp;
	int count;
	struct clist *clp;
E 2
I 2
b_to_q(a1, a2, a3)
	char *a1;
	int a2;
	struct clist *a3;
E 2
{
D 2
	int s, resid;
E 2

D 2
	if (count <= 0)
		return (0);
	resid = count;
	s = spltty();
E 2
	/*
	 * Body deleted.
	 */
D 2
	splx(s);
	return (resid);
E 2
I 2
	return (0);
E 2
}

D 2
/*
 * Given a non-NULL pointer into the clist return the pointer
 * to the next character in the list or return NULL if no more chars.
 *
 * Callers must not allow getc's to happen between nextc's so that the
 * pointer becomes invalid.  Note that interrupts are NOT masked.
 */
E 2
char *
D 2
nextc(clp, cp, count)
	struct clist *clp;
	char *cp;
	int *count;
E 2
I 2
nextc(a1, a2, a3)
	struct clist *a1;
	char *a2;
	int *a3;
E 2
{
D 2
	int empty = 0;
E 2

	/*
	 * Body deleted.
	 */
D 2
	if (!empty)
		return (cp);
	return (0);
E 2
I 2
	return ((char *)0);
E 2
}

D 2
/*
 * Remove the last character in the clist and return it.
 */
unputc(clp)
	struct clist *clp;
E 2
I 2
unputc(a1)
	struct clist *a1;
E 2
{
D 2
	char c;
	int s;
E 2

D 2
	s = spltty();
E 2
	/*
	 * Body deleted.
	 */
D 2
	splx(s);
	return (c);
E 2
I 2
	return ((char)0);
E 2
}

D 2
/*
 * Put the chars in the from queue on the end of the to queue.
 */
catq(from, to)
	struct clist *from, *to;
E 2
I 2
void
catq(a1, a2)
	struct clist *a1, *a2;
E 2
{
D 2
	char c;
E 2

D 2
	while ((c = getc(from)) >= 0)
		putc(c, to);
E 2
I 2
	/*
	 * Body deleted.
	 */
	return;
E 2
}
E 1
