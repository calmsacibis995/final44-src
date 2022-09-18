h55546
s 00002/00002/00243
d D 8.1 93/06/06 22:33:21 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00242
d D 3.29 90/06/06 21:45:59 bostic 29 28
c fix contrib notice (Edward Wang)
e
s 00001/00011/00241
d D 3.28 90/06/02 15:25:56 bostic 28 27
c new copyright notice
e
s 00024/00032/00228
d D 3.27 89/08/25 05:22:52 edward 27 26
c better lower right corner update
e
s 00006/00009/00254
d D 3.26 89/08/23 21:43:24 edward 26 25
c insert mode bug fix and cleanup
e
s 00025/00041/00238
d D 3.25 89/08/02 19:13:09 edward 25 24
c data compression and some other stuff
e
s 00018/00002/00261
d D 3.24 89/05/11 17:02:04 edward 24 23
c the xx layer added, handle "ic" differently, compression added to zapple
e
s 00018/00002/00245
d D 3.23 88/11/23 04:23:30 edward 23 22
c some minor tuning and a small bug in counting changed lines
e
s 00001/00001/00246
d D 3.22 88/08/08 09:38:20 edward 22 21
c use > when scanning for best_col
e
s 00004/00003/00243
d D 3.21 88/08/04 21:01:14 edward 21 20
c some bug fixes
e
s 00133/00041/00113
d D 3.20 88/08/04 18:09:36 edward 20 19
c use clreos and always try clreol in wwupdate1
e
s 00010/00005/00144
d D 3.19 88/06/29 21:39:01 bostic 19 18
c install approved copyright notice
e
s 00013/00007/00136
d D 3.18 88/02/21 13:39:02 bostic 18 17
c written by Edward Wang; attach Berkeley specific copyright
e
s 00002/00002/00141
d D 3.17 86/08/05 00:15:56 edward 17 16
c make sure unavailable mode bits are not set,
c so wwupdate1() doesn't have to mask them out.
e
s 00006/00000/00137
d D 3.16 85/04/24 16:17:09 edward 16 15
c copyright messages
e
s 00004/00002/00133
d D 3.15 84/07/12 13:37:30 edward 15 14
c now it really works
e
s 00003/00002/00132
d D 3.14 84/07/08 17:22:49 edward 14 13
c improved last col, last line update
e
s 00001/00001/00133
d D 3.13 84/05/23 01:59:02 edward 13 12
c new sccs id
e
s 00003/00002/00131
d D 3.12 84/03/03 22:46:58 edward 12 11
c interrupt driven input
e
s 00040/00025/00093
d D 3.11 84/01/06 16:20:09 edward 11 10
c smart clreol algorithm
e
s 00021/00007/00097
d D 3.10 83/12/21 13:26:59 edward 10 9
c write last char bug
e
s 00029/00004/00075
d D 3.9 83/12/02 22:45:58 edward 9 8
c WWU_MAJOR, clreol in wwupdate(), and more optimizations.
e
s 00013/00018/00066
d D 3.8 83/09/15 12:23:43 edward 8 7
c reworked tt stuff
e
s 00000/00001/00084
d D 3.7 83/08/19 15:00:18 edward 7 6
c took out useless tt_setinsert()
e
s 00023/00003/00062
d D 3.6 83/08/17 17:41:21 edward 6 5
c better wrap around handling.
e
s 00037/00009/00028
d D 3.5 83/08/16 15:25:57 edward 5 4
c smart update:  do it by chunks.
e
s 00012/00001/00025
d D 3.4 83/08/16 12:55:31 edward 4 3
c wwtouched added
e
s 00001/00000/00025
d D 3.3 83/08/15 18:15:23 edward 3 2
c tt cleanup
e
s 00000/00000/00025
d D 3.2 83/08/11 17:24:56 edward 2 1
i
c last few day's work
e
s 00025/00000/00000
d D 3.1 83/08/09 18:37:55 edward 1 0
c date and time created 83/08/09 18:37:55 by edward
e
u
U
t
T
I 1
D 18
#ifndef lint
D 13
static	char *sccsid = "%W% %E%";
E 13
I 13
static char sccsid[] = "%W% %G%";
E 13
#endif

E 18
I 16
/*
D 18
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 18
I 18
D 30
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
I 29
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 29
D 28
 * Redistribution and use in source and binary forms are permitted
D 19
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 19
I 19
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
E 28
I 28
 * %sccs.include.redist.c%
E 28
E 19
E 18
 */
I 18

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 18

E 16
#include "ww.h"
I 3
#include "tt.h"
E 3

D 12
wwupdate()
E 12
I 12
wwupdate1(top, bot)
E 12
{
D 5
	register i, j;
E 5
I 5
	int i;
	register j;
D 11
	int c, x;
E 11
E 5
D 20
	register union ww_char *ns, *os;
E 20
I 4
D 5
	register char *touched;
E 5
I 5
D 11
	register char *p, *q;
	char m;
E 11
	char *touched;
I 20
	struct ww_update *upd;
E 20
E 5
D 11
	register didit;
I 5
	char buf[512];			/* > wwncol */
I 6
	union ww_char lastc;
E 11
I 11
D 24
	char didit;
E 24
I 20
	char check_clreos = 0;
	int scan_top, scan_bot;
E 20
E 11
E 6
E 5
E 4

I 24
D 25
	xxflush();
E 25
E 24
I 4
	wwnupdate++;
E 4
D 7
	(*tt.tt_setinsert)(0);
E 7
D 4
	for (i = 0; i < wwnrow; i++) {
E 4
I 4
D 12
	for (i = 0, touched = wwtouched; i < wwnrow; i++, touched++) {
E 12
I 12
D 20
	for (i = top, touched = &wwtouched[i]; i < bot && !wwinterrupt();
	     i++, touched++) {
E 12
		if (!*touched)
E 20
I 20
	{
		register char *t1 = wwtouched + top, *t2 = wwtouched + bot;
		register n;

		while (!*t1++)
			if (t1 == t2)
				return;
		while (!*--t2)
			;
		scan_top = top = t1 - wwtouched - 1;
		scan_bot = bot = t2 - wwtouched + 1;
D 21
		if (tt.tt_clreos != 0 || tt.tt_clear != 0) {
			int st = tt.tt_clreos == 0 ? scan_top : 0;
E 21
I 21
		if (scan_bot - scan_top > 1 &&
		    (tt.tt_clreos != 0 || tt.tt_clear != 0)) {
			int st = tt.tt_clreos != 0 ? scan_top : 0;
E 21

D 23
			for (n = 1; t1 < t2;)
E 23
I 23
			/*
			 * t1 is one past the first touched row,
			 * t2 is on the last touched row.
			 */
			for (t1--, n = 1; t1 < t2;)
E 23
				if (*t1++)
					n++;
I 23
			/*
			 * If we can't clreos then we try for clearing
			 * the whole screen.
			 */
E 23
			if (check_clreos = n * 10 > (wwnrow - st) * 9) {
				scan_top = st;
				scan_bot = wwnrow;
			}
		}
	}
	if (tt.tt_clreol == 0 && !check_clreos)
		goto simple;
	for (i = scan_top, touched = &wwtouched[i], upd = &wwupd[i];
	     i < scan_bot;
	     i++, touched++, upd++) {
		register gain = 0;
		register best_gain = 0;
		register best_col;
		register union ww_char *ns, *os;

		if (wwinterrupt())
			return;
		if (!check_clreos && !*touched)
E 20
			continue;
D 9
		wwntouched++;
		*touched = 0;
E 9
I 9
D 11
		if (*touched & WWU_MAJOR) {
			int ncleared = 0;
			int nsame = 0;
E 11
I 11
D 20
		if (*touched & WWU_MAJOR && tt.tt_clreol != 0) {
			register gain = 0;
			register best_gain = 0;
			register best;
E 20
I 20
		wwnupdscan++;
		j = wwncol;
		ns = &wwns[i][j];
		os = &wwos[i][j];
		while (--j >= 0) {
			/*
			 * The cost of clearing is:
			 *	ncol - nblank + X
			 * The cost of straight update is, more or less:
			 *	ncol - nsame
			 * We clear if  nblank - nsame > X
			 * X is the clreol overhead.
			 * So we make gain = nblank - nsame.
			 */
			if ((--ns)->c_w == (--os)->c_w)
				gain--;
			else
				best_gain--;
			if (ns->c_w == ' ')
				gain++;
D 22
			if (gain >= best_gain) {
E 22
I 22
			if (gain > best_gain) {
E 22
				best_col = j;
				best_gain = gain;
			}
		}
		upd->best_gain = best_gain;
		upd->best_col = best_col;
		upd->gain = gain;
	}
	if (check_clreos) {
		register struct ww_update *u;
		register gain = 0;
		register best_gain = 0;
		int best_row;
		register simple_gain = 0;
		char didit = 0;
E 20
E 11
E 9
I 5

I 23
		/*
		 * gain is the advantage of clearing all the lines.
		 * best_gain is the advantage of clearing to eos
		 * at best_row and u->best_col.
		 * simple_gain is the advantage of using only clreol.
		 * We use g > best_gain because u->best_col can be
		 * undefined when u->best_gain is 0 so we can't use it.
		 */
E 23
I 9
D 20
			wwnmajline++;
			j = wwncol;
D 11
			ns = wwns[i];
			os = wwos[i];
E 11
I 11
			ns = &wwns[i][j];
			os = &wwos[i][j];
E 11
			while (--j >= 0) {
D 11
				if (ns->c_w == ' ') {
					if (ns->c_w != os->c_w)
						ncleared++;
				} else
					if (ns->c_w == os->c_w)
						nsame++;
				ns++;
				os++;
E 11
I 11
				/*
				 * The cost of clearing is:
				 *	ncol - nblank + X
				 * The cost of straight update is:
				 *	ncol - nsame
				 * We clear if:  nblank - nsame > X
				 * X is the clreol overhead.
				 * So we make gain = nblank - nsame.
				 */
				if ((--ns)->c_w == (--os)->c_w)
					gain--;
				else
					best_gain--;
				if (ns->c_w == ' ')
					gain++;
				if (gain >= best_gain) {
					best = j;
					best_gain = gain;
				}
E 20
I 20
		for (j = scan_bot - 1, u = wwupd + j; j >= top; j--, u--) {
			register g = gain + u->best_gain;

D 23
			if (g >= best_gain) {
E 23
I 23
			if (g > best_gain) {
E 23
				best_gain = g;
				best_row = j;
			}
			gain += u->gain;
			if (tt.tt_clreol != 0 && u->best_gain > 4)
				simple_gain += u->best_gain - 4;
		}
		if (tt.tt_clreos == 0) {
			if (gain > simple_gain && gain > 4) {
D 25
				(*tt.tt_clear)();
E 25
I 25
				xxclear();
E 25
				i = top = scan_top;
				bot = scan_bot;
				j = 0;
				didit = 1;
E 20
E 11
			}
D 11
			if (tt.tt_clreol != 0 && ncleared > nsame + 4) {
				(*tt.tt_move)(i, 0);
E 11
I 11
D 20
			if (best_gain > 4) {
				(*tt.tt_move)(i, best);
E 11
				(*tt.tt_clreol)();
D 11
				for (j = wwncol, os = wwos[i]; --j >= 0;)
E 11
I 11
				for (j = wwncol - best, os = &wwos[i][best];
				     --j >= 0;)
E 20
I 20
		} else
			if (best_gain > simple_gain && best_gain > 4) {
				i = best_row;
D 25
				(*tt.tt_move)(i, j = wwupd[i].best_col);
				(*tt.tt_clreos)();
E 25
I 25
				xxclreos(i, j = wwupd[i].best_col);
E 25
				bot = scan_bot;
				didit = 1;
			}
		if (didit) {
			wwnupdclreos++;
			wwnupdclreosline += wwnrow - i;
			u = wwupd + i;
			while (i < scan_bot) {
				register union ww_char *os = &wwos[i][j];

				for (j = wwncol - j; --j >= 0;)
E 20
E 11
					os++->c_w = ' ';
D 20
			} else
				wwnmajmiss++;
		}
E 20
I 20
D 21
				wwtouched[i++] = WWU_TOUCHED;
E 21
I 21
				wwtouched[i++] |= WWU_TOUCHED;
E 21
				u++->best_gain = 0;
				j = 0;
			}
		} else
			wwnupdclreosmiss++;
	}
simple:
	for (i = top, touched = &wwtouched[i], upd = &wwupd[i]; i < bot;
	     i++, touched++, upd++) {
		register union ww_char *os, *ns;
		char didit;

		if (!*touched)
			continue;
E 20
I 14
		*touched = 0;
E 14
		wwnupdline++;
		didit = 0;
I 20
		if (tt.tt_clreol != 0 && upd->best_gain > 4) {
			wwnupdclreol++;
D 25
			(*tt.tt_move)(i, j = upd->best_col);
			(*tt.tt_clreol)();
E 25
I 25
			xxclreol(i, j = upd->best_col);
E 25
			for (os = &wwos[i][j], j = wwncol - j; --j >= 0;)
				os++->c_w = ' ';
			didit = 1;
		}
E 20
E 9
E 5
E 4
		ns = wwns[i];
		os = wwos[i];
I 4
D 9
		didit = 0;
E 9
E 4
D 5
		for (j = 0; j < wwncol; j++, ns++, os++) {
			if (ns->c_w != os->c_w) {
				(*tt.tt_move)(i, j);
				(*tt.tt_setmodes)(ns->c_m);
				(*tt.tt_putc)(ns->c_c);
				*os = *ns;
I 4
				didit++;
E 5
I 5
		for (j = 0; j < wwncol;) {
I 11
			register char *p, *q;
			char m;
			int c;
			register n;
			char buf[512];			/* > wwncol */
			union ww_char lastc;

E 11
			for (; j++ < wwncol && ns++->c_w == os++->c_w;)
				;
			if (j > wwncol)
				break;
			p = buf;
D 8
			m = ns[-1].c_m;
E 8
I 8
D 17
			m = ns[-1].c_m & tt.tt_availmodes;
E 17
I 17
			m = ns[-1].c_m;
E 17
E 8
			c = j - 1;
			os[-1] = ns[-1];
			*p++ = ns[-1].c_c;
D 11
			x = 5;
E 11
I 11
			n = 5;
E 11
			q = p;
D 8
			while (j < wwncol && ns->c_m == m) {
E 8
I 8
D 17
			while (j < wwncol && (ns->c_m&tt.tt_availmodes) == m) {
E 17
I 17
			while (j < wwncol && ns->c_m == m) {
E 17
E 8
				*p++ = ns->c_c;
				if (ns->c_w == os->c_w) {
D 11
					if (--x <= 0)
E 11
I 11
					if (--n <= 0)
E 11
						break;
					os++;
					ns++;
				} else {
D 11
					x = 5;
E 11
I 11
					n = 5;
E 11
					q = p;
I 6
					lastc = *os;
E 6
					*os++ = *ns++;
				}
				j++;
E 5
E 4
			}
I 8
D 25
			tt.tt_nmodes = m;
E 25
D 10
			(*tt.tt_move)(i, c);
E 10
E 8
I 5
D 6
			(*tt.tt_move)(i, c);
			(*tt.tt_setmodes)(m);
			(*tt.tt_write)(buf, q - 1);
E 6
I 6
D 27
			if (wwwrap
			    && i == wwnrow - 1 && q - buf + c == wwncol) {
D 8
				if (tt.tt_setinsert != 0) {
					(*tt.tt_move)(i, c);
					(*tt.tt_setmodes)(m);
					(*tt.tt_write)(buf + 1, q - 1);
					(*tt.tt_move)(i, c);
					(*tt.tt_setinsert)(1);
					(*tt.tt_write)(buf, buf);
					(*tt.tt_setinsert)(0);
E 8
I 8
D 24
				if (tt.tt_hasinsert) {
E 24
I 24
D 26
				if (tt.tt_setinsert) {
E 26
I 26
				if (tt.tt_inschar) {
E 26
E 24
D 10
					(*tt.tt_write)(buf + 1, q - buf - 1);
					(*tt.tt_move)(i, c);
					tt.tt_ninsert = 1;
					(*tt.tt_write)(buf, 1);
					tt.tt_ninsert = 0;
E 10
I 10
					if (q - buf != 1) {
D 25
						(*tt.tt_move)(i, c);
						(*tt.tt_write)(buf + 1,
							q - buf - 1);
						(*tt.tt_move)(i, c);
						tt.tt_ninsert = 1;
						(*tt.tt_write)(buf, 1);
						tt.tt_ninsert = 0;
E 25
I 25
						xxwrite(i, c, buf + 1,
							q - buf - 1, m);
D 26
						xxinschar(i, c, *buf |
							m << WWC_MSHIFT);
E 26
I 26
						xxinschar(i, c, *buf, m);
E 26
E 25
					} else {
D 25
						(*tt.tt_move)(i, c - 1);
						(*tt.tt_write)(buf, 1);
						tt.tt_nmodes = ns[-2].c_m;
						(*tt.tt_move)(i, c - 1);
						tt.tt_ninsert = 1;
						(*tt.tt_write)(&ns[-2].c_c, 1);
						tt.tt_ninsert = 0;
E 25
I 25
						xxwrite(i, c - 1, buf, 1, m);
						xxinschar(i, c - 1,
D 26
							ns[-2].c_w);
E 26
I 26
							ns[-2].c_c, ns[-2].c_m);
E 26
E 25
I 24
					}
D 26
				} else if (tt.tt_inschar) {
E 26
I 26
				} else if (tt.tt_insspace) {
E 26
					if (q - buf != 1) {
D 25
						(*tt.tt_move)(i, c);
						(*tt.tt_write)(buf + 1,
							q - buf - 1);
						(*tt.tt_move)(i, c);
						(*tt.tt_inschar)(1);
						(*tt.tt_write)(buf, 1);
E 25
I 25
						xxwrite(i, c, buf + 1,
							q - buf - 1, m);
D 26
						xxinschar(i, c, *buf |
							m << WWC_MSHIFT);
E 26
I 26
						xxinsspace(i, c);
E 26
						xxwrite(i, c, buf, 1, m);
E 25
					} else {
D 25
						(*tt.tt_move)(i, c - 1);
						(*tt.tt_write)(buf, 1);
						tt.tt_nmodes = ns[-2].c_m;
						(*tt.tt_move)(i, c - 1);
						(*tt.tt_inschar)(1);
						(*tt.tt_write)(&ns[-2].c_c, 1);
E 25
I 25
						xxwrite(i, c - 1, buf, 1, m);
D 26
						xxinschar(i, c - 1,
							ns[-2].c_w);
E 26
I 26
						xxinsspace(i, c - 1);
E 26
						xxwrite(i, c - 1, &ns[-2].c_c,
							1, ns[-2].c_m);
E 25
E 24
					}
E 10
E 8
				} else {
I 10
D 15
					(*tt.tt_move)(i, c);
E 10
D 14
					os[-1] = lastc;
E 14
D 8
					(*tt.tt_move)(i, c);
					(*tt.tt_setmodes)(m);
					(*tt.tt_write)(buf, q - 2);
E 8
I 8
					(*tt.tt_write)(buf, q - buf - 1);
E 15
I 15
D 25
					if (q - buf > 1) {
						(*tt.tt_move)(i, c);
						(*tt.tt_write)(buf, q-buf-1);
					}
E 25
I 25
					if (q - buf > 1)
						xxwrite(i, c, buf,
							q - buf - 1, m);
E 25
E 15
I 14
					os[-1] = lastc;
					*touched = WWU_TOUCHED;
E 27
I 27
			n = q - buf;
			if (!wwwrap || i != wwnrow - 1 || c + n != wwncol)
				xxwrite(i, c, buf, n, m);
			else if (tt.tt_inschar || tt.tt_insspace) {
				if (n > 1) {
					q[-2] = q[-1];
					n--;
				} else
					c--;
				xxwrite(i, c, buf, n, m);
				c += n - 1;
				if (tt.tt_inschar)
					xxinschar(i, c, ns[-2].c_c,
						ns[-2].c_m);
				else {
					xxinsspace(i, c);
					xxwrite(i, c, &ns[-2].c_c, 1,
						ns[-2].c_m);
E 27
E 14
E 8
				}
D 8
			} else {
				(*tt.tt_move)(i, c);
				(*tt.tt_setmodes)(m);
				(*tt.tt_write)(buf, q - 1);
			}
E 8
I 8
D 10
			} else
E 10
I 10
D 25
			} else {
				(*tt.tt_move)(i, c);
E 10
				(*tt.tt_write)(buf, q - buf);
I 10
			}
E 25
I 25
D 27
			} else
				xxwrite(i, c, buf, q - buf, m);
E 27
I 27
			} else {
				if (--n)
					xxwrite(i, c, buf, n, m);
				os[-1] = lastc;
				*touched = WWU_TOUCHED;
			}
E 27
E 25
E 10
E 8
E 6
D 20
			didit++;
E 20
I 20
			didit = 1;
E 20
E 5
		}
I 4
		if (!didit)
D 9
			wwnmiss++;
E 9
I 9
			wwnupdmiss++;
D 14
		*touched = 0;
E 14
E 9
E 4
	}
}
E 1
