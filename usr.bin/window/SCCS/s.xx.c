h29378
s 00002/00002/00224
d D 8.1 93/06/06 22:33:32 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00015/00203
d D 3.7 92/11/10 11:49:54 edward 7 6
c checkpointing stuff
e
s 00003/00000/00215
d D 3.6 90/06/06 21:46:04 bostic 6 5
c fix contrib notice (Edward Wang)
e
s 00001/00011/00214
d D 3.5 90/06/02 15:26:07 bostic 5 4
c new copyright notice
e
s 00006/00004/00219
d D 3.4 89/09/15 17:48:56 edward 4 3
c compress control characters as well
e
s 00005/00007/00218
d D 3.3 89/08/24 04:42:16 edward 3 2
c new compression algorithm
e
s 00017/00015/00208
d D 3.2 89/08/23 21:43:30 edward 2 1
c insert mode bug fix and cleanup
e
s 00223/00000/00000
d D 3.1 89/08/02 19:14:19 edward 1 0
c date and time created 89/08/02 19:14:19 by edward
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
I 6
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 6
D 5
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "ww.h"
#include "xx.h"
#include "tt.h"

xxinit()
{
	if (ttinit() < 0)
		return -1;
	xxbufsize = tt.tt_nrow * tt.tt_ncol * 2;
I 3
D 4
	/* xcinit may choose to change xxbufsize */
	if (tt.tt_ntoken > 0 && xcinit() < 0)
E 4
I 4
	/* ccinit may choose to change xxbufsize */
	if (tt.tt_ntoken > 0 && ccinit() < 0)
E 4
		return -1;
E 3
	xxbuf = malloc((unsigned) xxbufsize * sizeof *xxbuf);
	if (xxbuf == 0) {
		wwerrno = WWE_NOMEM;
		return -1;
	}
	xxbufp = xxbuf;
	xxbufe = xxbuf + xxbufsize;
D 3
	if (tt.tt_ntoken > 0 && xcinit() < 0)
		return -1;
E 3
	return 0;
}

xxstart()
{
	(*tt.tt_start)();
	if (tt.tt_ntoken > 0)
D 4
		xcstart();
E 4
I 4
		ccstart();
E 4
D 7
	xxreset();			/* might be a restart */
E 7
I 7
	xxreset1();			/* might be a restart */
E 7
}

I 7
xxreset()
{
	if (tt.tt_ntoken > 0)
		ccreset();
	xxreset1();
	(*tt.tt_reset)();
}

xxreset1()
{
	register struct xx *xp, *xq;

	for (xp = xx_head; xp != 0; xp = xq) {
		xq = xp->link;
		xxfree(xp);
	}
	xx_tail = xx_head = 0;
	xxbufp = xxbuf;
}

E 7
xxend()
{
	if (tt.tt_scroll_top != 0 || tt.tt_scroll_bot != tt.tt_nrow - 1)
		/* tt.tt_setscroll is known to be defined */
		(*tt.tt_setscroll)(0, tt.tt_nrow - 1);
D 2
	if (tt.tt_insert)
		(*tt.tt_setinsert)(0);
E 2
	if (tt.tt_modes)
		(*tt.tt_setmodes)(0);
	if (tt.tt_scroll_down)
		(*tt.tt_scroll_down)(1);
	(*tt.tt_move)(tt.tt_nrow - 1, 0);
I 4
	if (tt.tt_ntoken > 0)
		ccend();
E 4
	(*tt.tt_end)();
D 4
	ttflush();
E 4
I 4
D 7
	(*tt.tt_flush)();
E 7
I 7
	ttflush();
E 7
E 4
}

struct xx *
xxalloc()
{
	register struct xx *xp;

	if (xxbufp > xxbufe)
		abort();
	if ((xp = xx_freelist) == 0)
		/* XXX can't deal with failure */
		xp = (struct xx *) malloc((unsigned) sizeof *xp);
	else
		xx_freelist = xp->link;
	if (xx_head == 0)
		xx_head = xp;
	else
		xx_tail->link = xp;
	xx_tail = xp;
	xp->link = 0;
	return xp;
}

xxfree(xp)
	register struct xx *xp;
{
	xp->link = xx_freelist;
	xx_freelist = xp;
}

xxmove(row, col)
{
	register struct xx *xp = xx_tail;

	if (xp == 0 || xp->cmd != xc_move) {
		xp = xxalloc();
		xp->cmd = xc_move;
	}
	xp->arg0 = row;
	xp->arg1 = col;
}

xxscroll(dir, top, bot)
{
	register struct xx *xp = xx_tail;

	if (xp != 0 && xp->cmd == xc_scroll &&
	    xp->arg1 == top && xp->arg2 == bot &&
	    (xp->arg0 < 0 && dir < 0 || xp->arg0 > 0 && dir > 0)) {
		xp->arg0 += dir;
		return;
	}
	xp = xxalloc();
	xp->cmd = xc_scroll;
	xp->arg0 = dir;
	xp->arg1 = top;
	xp->arg2 = bot;
}

D 2
xxinschar(row, col, c)
E 2
I 2
xxinschar(row, col, c, m)
E 2
{
I 2
	register struct xx *xp;

	xp = xxalloc();
	xp->cmd = xc_inschar;
	xp->arg0 = row;
	xp->arg1 = col;
	xp->arg2 = c;
	xp->arg3 = m;
}

xxinsspace(row, col)
{
E 2
	register struct xx *xp = xx_tail;
D 2
	int m = c >> WWC_MSHIFT;
E 2

D 2
	if (xxbufp >= xxbufe)
		xxflush(0);
	c &= WWC_CMASK;
	if (xp != 0 && xp->cmd == xc_inschar &&
	    xp->arg0 == row && xp->arg1 + xp->arg2 == col && xp->arg3 == m) {
		xp->buf[xp->arg2++] = c;
		xxbufp++;
E 2
I 2
	if (xp != 0 && xp->cmd == xc_insspace && xp->arg0 == row &&
	    col >= xp->arg1 && col <= xp->arg1 + xp->arg2) {
		xp->arg2++;
E 2
		return;
	}
	xp = xxalloc();
D 2
	xp->cmd = xc_inschar;
E 2
I 2
	xp->cmd = xc_insspace;
E 2
	xp->arg0 = row;
	xp->arg1 = col;
	xp->arg2 = 1;
D 2
	xp->arg3 = m;
	xp->buf = xxbufp++;
	*xp->buf = c;
E 2
}

xxdelchar(row, col)
{
	register struct xx *xp = xx_tail;

	if (xp != 0 && xp->cmd == xc_delchar &&
	    xp->arg0 == row && xp->arg1 == col) {
		xp->arg2++;
		return;
	}
	xp = xxalloc();
	xp->cmd = xc_delchar;
	xp->arg0 = row;
	xp->arg1 = col;
	xp->arg2 = 1;
}

xxclear()
{
	register struct xx *xp;

D 7
	xxreset();
E 7
I 7
	xxreset1();
E 7
	xp = xxalloc();
	xp->cmd = xc_clear;
}

xxclreos(row, col)
{
	register struct xx *xp = xxalloc();

	xp->cmd = xc_clreos;
	xp->arg0 = row;
	xp->arg1 = col;
}

xxclreol(row, col)
{
	register struct xx *xp = xxalloc();

	xp->cmd = xc_clreol;
	xp->arg0 = row;
	xp->arg1 = col;
}

xxwrite(row, col, p, n, m)
	char *p;
{
	register struct xx *xp;

D 3
	if (xxbufp + n > xxbufe)
E 3
I 3
	if (xxbufp + n + 1 > xxbufe)
E 3
		xxflush(0);
	xp = xxalloc();
	xp->cmd = xc_write;
	xp->arg0 = row;
	xp->arg1 = col;
	xp->arg2 = n;
	xp->arg3 = m;
	xp->buf = xxbufp;
	bcopy(p, xxbufp, n);
	xxbufp += n;
D 3
	if (tt.tt_ntoken > 0)
		xcscan(xp->buf, n, xp->buf - xxbuf);
E 3
I 3
	*xxbufp++ = char_sep;
E 3
D 7
}

xxreset()
{
	register struct xx *xp, *xq;

	for (xp = xx_head; xp != 0; xp = xq) {
		xq = xp->link;
		xxfree(xp);
	}
	xx_tail = xx_head = 0;
	xxbufp = xxbuf;
E 7
D 3
	if (tt.tt_ntoken > 0)
		xcreset();
E 3
}
E 1
