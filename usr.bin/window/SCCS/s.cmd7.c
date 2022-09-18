h25260
s 00002/00002/00243
d D 8.1 93/06/06 22:28:11 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00187/00000/00058
d D 3.8 92/08/16 17:43:33 edward 8 7
c changes from Brian Buhrow, primitive yank and put, Posix MIN and TIME,
c and others
e
s 00003/00000/00055
d D 3.7 90/06/06 21:43:31 bostic 7 6
c fix contrib notice (Edward Wang)
e
s 00001/00011/00054
d D 3.6 90/06/02 15:19:29 bostic 6 5
c new copyright notice
e
s 00010/00005/00055
d D 3.5 88/06/29 21:35:49 bostic 5 4
c install approved copyright notice
e
s 00013/00007/00047
d D 3.4 88/02/21 13:36:48 bostic 4 3
c written by Edward Wang; attach Berkeley specific copyright
e
s 00006/00000/00048
d D 3.3 85/04/24 16:24:23 edward 3 2
c copyright messages
e
s 00000/00028/00048
d D 3.2 85/04/03 22:21:00 edward 2 1
c lint, and others
e
s 00076/00000/00000
d D 3.1 85/03/01 17:49:15 edward 1 0
c date and time created 85/03/01 17:49:15 by edward
e
u
U
t
T
I 1
D 4
#ifndef lint
static char sccsid[] = "%W% %G%";
#endif

E 4
I 3
/*
D 4
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 4
I 4
D 9
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
I 7
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 7
D 6
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
E 4
 */
I 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

E 3
#include "defs.h"
I 8
#include "string.h"
E 8

/*
 * Window size.
 */

c_size(w)
register struct ww *w;
{
	int col, row;

	if (!terse)
		wwputs("New window size (lower right corner): ", cmdwin);
	col = MIN(w->ww_w.r, wwncol) - 1;
	row = MIN(w->ww_w.b, wwnrow) - 1;
	wwadd(boxwin, framewin->ww_back);
	for (;;) {
		wwbox(boxwin, w->ww_w.t - 1, w->ww_w.l - 1,
			row - w->ww_w.t + 3, col - w->ww_w.l + 3);
		wwsetcursor(row, col);
		while (wwpeekc() < 0)
			wwiomux();
		switch (getpos(&row, &col, w->ww_w.t, w->ww_w.l,
			wwnrow - 1, wwncol - 1)) {
		case 3:
			wwunbox(boxwin);
			wwdelete(boxwin);
			return;
		case 2:
			wwunbox(boxwin);
			break;
		case 1:
			wwunbox(boxwin);
		case 0:
			continue;
		}
		break;
	}
	wwdelete(boxwin);
	if (!terse)
		wwputc('\n', cmdwin);
	wwcurtowin(cmdwin);
	sizewin(w, row - w->ww_w.t + 1, col - w->ww_w.l + 1);
I 8
}

/*
 * Yank and put
 */

struct yb {
	char *line;
	int length;
	struct yb *link;
};
struct yb *yb_head, *yb_tail;

c_yank()
{
	struct ww *w = selwin;
	int col1, row1;
	int col2, row2;
	int r, c;

	if (!terse)
		wwputs("Yank starting position: ", cmdwin);
	wwcursor(w, 0);
	row1 = w->ww_cur.r;
	col1 = w->ww_cur.c;
	for (;;) {
		wwsetcursor(row1, col1);
		while (wwpeekc() < 0)
			wwiomux();
		switch (getpos(&row1, &col1, w->ww_i.t, w->ww_i.l,
			       w->ww_i.b - 1, w->ww_i.r - 1)) {
		case 3:
			goto out;
		case 2:
			break;
		case 1:
		case 0:
			continue;
		}
		break;
	}
	if (!terse)
		wwputs("\nYank ending position: ", cmdwin);
	row2 = row1;
	col2 = col1;
	for (;;) {
		wwsetcursor(row2, col2);
		while (wwpeekc() < 0)
			wwiomux();
		r = row2;
		c = col2;
		switch (getpos(&row2, &col2, w->ww_i.t, w->ww_i.l,
			       w->ww_i.b - 1, w->ww_i.r - 1)) {
		case 3:
			yank_highlight(row1, col1, r, c);
			goto out;
		case 2:
			break;
		case 1:
			yank_highlight(row1, col1, r, c);
			yank_highlight(row1, col1, row2, col2);
		case 0:
			continue;
		}
		break;
	}
	if (row2 < row1 || row2 == row1 && col2 < col1) {
		r = row1;
		c = col1;
		row1 = row2;
		col1 = col2;
		row2 = r;
		col2 = c;
	}
	unyank();
	c = col1;
	for (r = row1; r < row2; r++) {
		yank_line(r, c, w->ww_b.r);
		c = w->ww_b.l;
	}
	yank_line(r, c, col2);
	yank_highlight(row1, col1, row2, col2);
	if (!terse)
		wwputc('\n', cmdwin);
out:
	wwcursor(w, 1);
}

yank_highlight(row1, col1, row2, col2)
{
	struct ww *w = selwin;
	int r, c;

	if ((wwavailmodes & WWM_REV) == 0)
		return;
	if (row2 < row1 || row2 == row1 && col2 < col1) {
		r = row1;
		c = col1;
		row1 = row2;
		col1 = col2;
		row2 = r;
		col2 = c;
	}
	c = col1;
	for (r = row1; r < row2; r++) {
		yank_highlight_line(r, c, w->ww_b.r);
		c = w->ww_b.l;
	}
	yank_highlight_line(r, c, col2);
}

yank_highlight_line(r, c, cend)
{
	struct ww *w = selwin;
	char *win;

	if (r < w->ww_i.t || r >= w->ww_i.b)
		return;
	if (c < w->ww_i.l)
		c = w->ww_i.l;
	if (cend >= w->ww_i.r)
		cend = w->ww_i.r;
	for (win = w->ww_win[r] + c; c < cend; c++, win++) {
		*win ^= WWM_REV;
		if (wwsmap[r][c] == w->ww_index) {
			if (*win == 0)
				w->ww_nvis[r]++;
			else if (*win == WWM_REV)
				w->ww_nvis[r]--;
			wwns[r][c].c_m ^= WWM_REV;
			wwtouched[r] |= WWU_TOUCHED;
		}
	}
}

unyank()
{
	struct yb *yp, *yq;

	for (yp = yb_head; yp; yp = yq) {
		yq = yp->link;
		str_free(yp->line);
		free((char *) yp);
	}
	yb_head = yb_tail = 0;
}

yank_line(r, c, cend)
{
	struct yb *yp;
	int nl = 0;
	int n;
	union ww_char *bp;
	char *cp;

	if (c == cend)
		return;
	if ((yp = (struct yb *) malloc(sizeof *yp)) == 0)
		return;
	yp->link = 0;
	nl = cend == selwin->ww_b.r;
	bp = selwin->ww_buf[r];
	for (cend--; cend >= c; cend--)
		if (bp[cend].c_c != ' ')
			break;
	yp->length = n = cend - c + 1;
	if (nl)
		yp->length++;
	yp->line = str_alloc(yp->length + 1);
	for (bp += c, cp = yp->line; --n >= 0;)
		*cp++ = bp++->c_c;
	if (nl)
		*cp++ = '\n';
	*cp = 0;
	if (yb_head)
		yb_tail = yb_tail->link = yp;
	else
		yb_head = yb_tail = yp;
}

c_put()
{
	struct yb *yp;

	for (yp = yb_head; yp; yp = yp->link)
		(void) write(selwin->ww_pty, yp->line, yp->length);
E 8
}
D 2

sizewin(w, nrow, ncol)
register struct ww *w;
{
	struct ww *back = w->ww_back;

	w->ww_alt.nr = w->ww_w.nr;
	w->ww_alt.nc = w->ww_w.nc;
	wwdelete(w);
	wwsize(w, nrow, ncol);
	wwadd(w, back);
	reframe();
}

iconwin(w)
register struct ww *w;
{
	struct ww_dim new;
	struct ww *back = w->ww_back;

	new = w->ww_alt;
	w->ww_alt = w->ww_w;
	wwdelete(w);
	wwsize(w, new.nr, new.nc);
	wwmove(w, new.t, new.l);
	wwadd(w, back);
	reframe();
}
E 2
E 1
