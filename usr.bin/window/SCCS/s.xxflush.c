h46683
s 00002/00002/00168
d D 8.1 93/06/06 22:33:38 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00169
d D 3.7 92/11/10 11:49:52 edward 7 6
c checkpointing stuff
e
s 00003/00000/00167
d D 3.6 90/06/06 21:46:07 bostic 6 5
c fix contrib notice (Edward Wang)
e
s 00001/00011/00166
d D 3.5 90/06/02 15:26:16 bostic 5 4
c new copyright notice
e
s 00002/00007/00175
d D 3.4 89/09/15 17:49:01 edward 4 3
c compress control characters as well
e
s 00002/00002/00180
d D 3.3 89/08/24 04:42:18 edward 3 2
c new compression algorithm
e
s 00006/00011/00176
d D 3.2 89/08/23 21:43:33 edward 2 1
c insert mode bug fix and cleanup
e
s 00187/00000/00000
d D 3.1 89/08/23 19:36:24 edward 1 0
c date and time created 89/08/23 19:36:24 by edward
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

xxflush(intr)
	register intr;
{
	register struct xx *xp, *xq;

I 3
D 4
	if (tt.tt_ntoken > 0)
		xcscan(xxbuf, xxbufp - xxbuf);	/* XXX, starting point */
E 4
E 3
	for (xp = xx_head; xp != 0 && !(intr && wwinterrupt()); xp = xq) {
		switch (xp->cmd) {
		case xc_move:
			if (xp->link == 0)
				(*tt.tt_move)(xp->arg0, xp->arg1);
			break;
		case xc_scroll:
			xxflush_scroll(xp);
			break;
		case xc_inschar:
D 2
			if (xp->arg1 + xp->arg2 >= tt.tt_ncol)
				break;
E 2
			(*tt.tt_move)(xp->arg0, xp->arg1);
D 2
			if (tt.tt_setinsert) {
				tt.tt_nmodes = xp->arg3;
				tt.tt_ninsert = 1;
				(*tt.tt_write)(xp->buf, xp->arg2);
				tt.tt_ninsert = 0;
			} else
				(*tt.tt_inschar)(xp->arg2);
E 2
I 2
			tt.tt_nmodes = xp->arg3;
			(*tt.tt_inschar)(xp->arg2);
E 2
			break;
I 2
		case xc_insspace:
			(*tt.tt_move)(xp->arg0, xp->arg1);
			(*tt.tt_insspace)(xp->arg2);
			break;
E 2
		case xc_delchar:
D 2
			if (xp->arg1 + xp->arg2 >= tt.tt_ncol)
				break;
E 2
			(*tt.tt_move)(xp->arg0, xp->arg1);
			(*tt.tt_delchar)(xp->arg2);
			break;
		case xc_clear:
			(*tt.tt_clear)();
			break;
		case xc_clreos:
			(*tt.tt_move)(xp->arg0, xp->arg1);
			(*tt.tt_clreos)();
			break;
		case xc_clreol:
			(*tt.tt_move)(xp->arg0, xp->arg1);
			(*tt.tt_clreol)();
			break;
		case xc_write:
			(*tt.tt_move)(xp->arg0, xp->arg1);
			tt.tt_nmodes = xp->arg3;
D 4
			if (tt.tt_ntoken > 0)
				xcwrite(xp->buf, xp->arg2, xp->buf - xxbuf);
			else
				(*tt.tt_write)(xp->buf, xp->arg2);
E 4
I 4
			(*tt.tt_write)(xp->buf, xp->arg2);
E 4
			break;
		}
		xq = xp->link;
		xxfree(xp);
	}
	if ((xx_head = xp) == 0) {
		xx_tail = 0;
		xxbufp = xxbuf;
D 3
		if (tt.tt_ntoken > 0)
			xcreset();
E 3
	}
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

xxflush_scroll(xp)
	register struct xx *xp;
{
	register struct xx *xq;

 top:
	if (xp->arg0 == 0)
		return;
	/*
	 * We handle retain (da and db) by putting the burden on scrolling up,
	 * which is the less common operation.  It must ensure that
	 * text is not pushed below the screen, so scrolling down doesn't
	 * have to worry about it.
	 *
	 * Try scrolling region (or scrolling the whole screen) first.
	 * Can we assume "sr" doesn't push text below the screen
	 * so we don't have to worry about retain below?
	 * What about scrolling down with a newline?  It probably does
	 * push text above (with da).  Scrolling up would then have
	 * to take care of that.
	 * It's easy to be fool proof, but that slows things down.
	 * The current solution is to disallow tt_scroll_up if da or db is true
	 * but cs (scrolling region) is not.  Again, we sacrifice scrolling
	 * up in favor of scrolling down.  The idea is having scrolling regions
	 * probably means we can scroll (even the whole screen) with impunity.
	 * This lets us work efficiently on simple terminals (use newline
	 * on the bottom to scroll), on any terminal without retain, and
	 * on vt100 style scrolling regions (I think).
	 */
	if (xp->arg0 > 0) {
		if ((xq = xp->link) != 0 && xq->cmd == xc_scroll &&
		    xp->arg2 == xq->arg2 && xq->arg0 < 0) {
			if (xp->arg1 < xq->arg1) {
				if (xp->arg2 - xp->arg0 <= xq->arg1) {
					xq->arg0 = xp->arg0;
					xq->arg1 = xp->arg1;
					xq->arg2 = xp->arg2;
					return;
				}
				xp->arg2 = xq->arg1 + xp->arg0;
				xq->arg0 += xp->arg0;
				xq->arg1 = xp->arg2;
				if (xq->arg0 > 0)
					xq->arg1 -= xq->arg0;
				goto top;
			} else {
				if (xp->arg1 - xq->arg0 >= xp->arg2)
					return;
				xq->arg2 = xp->arg1 - xq->arg0;
				xp->arg0 += xq->arg0;
				xp->arg1 = xq->arg2;
				if (xp->arg0 < 0)
					xp->arg1 += xp->arg0;
				goto top;
			}
		}
		if (xp->arg0 > xp->arg2 - xp->arg1)
			xp->arg0 = xp->arg2 - xp->arg1;
		if (tt.tt_scroll_down) {
			if (tt.tt_scroll_top != xp->arg1 ||
			    tt.tt_scroll_bot != xp->arg2 - 1) {
				if (tt.tt_setscroll == 0)
					goto down;
				(*tt.tt_setscroll)(xp->arg1, xp->arg2 - 1);
			}
			tt.tt_scroll_down(xp->arg0);
		} else {
		down:
			(*tt.tt_move)(xp->arg1, 0);
			(*tt.tt_delline)(xp->arg0);
			if (xp->arg2 < tt.tt_nrow) {
				(*tt.tt_move)(xp->arg2 - xp->arg0, 0);
				(*tt.tt_insline)(xp->arg0);
			}
		}
	} else {
		xp->arg0 = - xp->arg0;
		if (xp->arg0 > xp->arg2 - xp->arg1)
			xp->arg0 = xp->arg2 - xp->arg1;
		if (tt.tt_scroll_up) {
			if (tt.tt_scroll_top != xp->arg1 ||
			    tt.tt_scroll_bot != xp->arg2 - 1) {
				if (tt.tt_setscroll == 0)
					goto up;
				(*tt.tt_setscroll)(xp->arg1, xp->arg2 - 1);
			}
			tt.tt_scroll_up(xp->arg0);
		} else  {
		up:
			if (tt.tt_retain || xp->arg2 != tt.tt_nrow) {
				(*tt.tt_move)(xp->arg2 - xp->arg0, 0);
				(*tt.tt_delline)(xp->arg0);
			}
			(*tt.tt_move)(xp->arg1, 0);
			(*tt.tt_insline)(xp->arg0);
		}
	}
}
E 1
