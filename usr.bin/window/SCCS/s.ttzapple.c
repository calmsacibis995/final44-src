h17866
s 00002/00002/00455
d D 8.1 93/06/06 22:30:34 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00090/00015/00367
d D 3.13 92/11/10 11:49:49 edward 14 13
c checkpointing stuff
e
s 00043/00000/00339
d D 3.12 92/06/24 14:54:42 edward 13 12
c input error correction stuff
e
s 00003/00000/00336
d D 3.11 90/06/06 21:44:36 bostic 12 11
c fix contrib notice (Edward Wang)
e
s 00001/00001/00335
d D 3.10 90/06/03 18:50:43 edward 11 10
c missing parens (how embarrassing)
e
s 00001/00011/00335
d D 3.9 90/06/02 15:22:18 bostic 10 9
c new copyright notice
e
s 00016/00007/00330
d D 3.8 89/09/15 17:48:58 edward 9 8
c compress control characters as well
e
s 00056/00059/00281
d D 3.7 89/08/27 05:52:45 edward 8 7
c cleanup of output of control characters
e
s 00051/00078/00289
d D 3.6 89/08/27 05:38:29 edward 7 5
c new escape sequences
e
s 00043/00071/00296
d R 3.6 89/08/27 05:23:44 edward 6 5
c new escape sequences
e
s 00002/00002/00365
d D 3.5 89/08/23 21:43:49 edward 5 4
c insert mode bug fix and cleanup
e
s 00004/00004/00363
d D 3.4 89/08/20 02:28:31 edward 4 3
c new, slightly different token protocol
e
s 00081/00192/00286
d D 3.3 89/08/02 19:13:19 edward 3 2
c data compression and some other stuff
e
s 00233/00081/00245
d D 3.2 89/05/11 17:02:13 edward 2 1
c the xx layer added, handle "ic" differently, compression added to zapple
e
s 00326/00000/00000
d D 3.1 89/04/20 06:02:22 edward 1 0
c date and time created 89/04/20 06:02:22 by edward
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1983 Regents of the University of California.
E 2
I 2
D 15
 * Copyright (c) 1989 Regents of the University of California.
E 2
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
I 12
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 12
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "ww.h"
#include "tt.h"
#include "char.h"

/*
D 7
zz|zapple|unorthodox apple:\
E 7
I 7
zz|zapple|perfect apple:\
E 7
	:am:pt:co#80:li#24:le=^H:nd=^F:up=^K:do=^J:\
D 7
	:ho=^[0:ll=^[1:cm=^]%+ %+ =:ch=^\%+ <:cv=^\%+ >:\
	:cl=^[4:ce=^[2:cd=^[3:rp=^]%.%+ @:\
	:so=^[+:se=^[-:\
	:dc=^[c:DC=^\%+ C:ic=^[i:IC=^\%+ I:\
	:al=^[a:AL=^\%+ A:dl=^[d:DL=^\%+ D:\
	:sf=^[f:SF=^\%+ F:sr=^[r:SR=^\%+ R:cs=^]%+ %+ ?:
E 7
I 7
	:ho=\E0:ll=\E1:cm=\E=%+ %+ :ch=\E<%+ :cv=\E>%+ :\
	:cl=\E4:ce=\E2:cd=\E3:rp=\E@%.%+ :\
	:so=\E+:se=\E-:\
	:dc=\Ec:DC=\EC%+ :ic=\Ei:IC=\EI%+ :\
	:al=\Ea:AL=\EA%+ :dl=\Ed:DL=\ED%+ :\
	:sf=\Ef:SF=\EF%+ :sr=\Er:SR=\ER%+ :cs=\E?%+ %+ :\
	:is=\E-\ET :
E 7
*/

D 3
#define NCOL	80
#define NROW	24
E 3
I 3
#define NCOL		80
#define NROW		24
#define TOKEN_MAX	32
E 3

D 8
#define pc(c)	ttputc(c)
D 7
#define esc()	pc(ctrl('['))
#define esc1()	pc(ctrl('\\'))
#define esc2()	pc(ctrl(']'))
E 7
I 7
#define esc(c)	(pc(ctrl('[')), pc(c))
E 7

E 8
D 2
#define ZZ_SETINSERT(new) (tt.tt_insert = new)

E 2
extern short gen_frame[];

I 13
	/* for error correction */
int zz_ecc;
I 14
int zz_lastc;
E 14

I 14
	/* for checkpointing */
int zz_sum;

E 14
E 13
D 2
zz_setinsert(new)
{
	ZZ_SETINSERT(new);
}
E 2
I 2
D 3
/*
 * stuff for token compression
 */
E 2

I 2
#define N	4
#define NTOKEN	128
#define NCTOKEN	(NTOKEN * 4)
#define H	11
#define HSIZE	(1 << H)
struct ctoken {
	short index;
	short hash;
	unsigned long time;
	unsigned long count;
	char string[N];
	struct ctoken *forw;
	struct ctoken *back;
};

static struct ctoken q1, q2;
static struct ctoken *htab[HSIZE];
static struct ctoken *line[NCOL];
static struct ctoken tokens[NTOKEN * 4];
static unsigned long tick;

#define zc_eval(t)	((int) ((t)->count * 400 + (t)->time - tick))
#define zc_hash(h, c)	((((h) << 1 | (h) >> H - 1) ^ (c)) & HSIZE - 1)
#define zc_unhash(h, c)	(((h) ^ (c) << N - 1 ^ (c) >> H - N + 1) & (HSIZE - 1))
#define zc_copy(f, t)	bcopy(f, t, N)
#define zc_equal(f, t)	(bcmp(f, t, N) == 0)
/*
#define zc_copy(f, t)	((t)[0] = (f)[0], (t)[1] = (f)[1], \
				(t)[2] = (f)[2], (t)[3] = (f)[3])
#define zc_equal(f, t)	((t)[0] == (f)[0] && (t)[1] == (f)[1] && \
				(t)[2] == (f)[2] && (t)[3] == (f)[3])
*/

E 3
E 2
zz_setmodes(new)
{
	if (new & WWM_REV) {
D 7
		if ((tt.tt_modes & WWM_REV) == 0) {
			esc();
			pc('+');
		}
E 7
I 7
		if ((tt.tt_modes & WWM_REV) == 0)
D 8
			esc('+');
E 8
I 8
			ttesc('+');
E 8
E 7
	} else
D 7
		if (tt.tt_modes & WWM_REV) {
			esc();
			pc('-');
		}
E 7
I 7
		if (tt.tt_modes & WWM_REV)
D 8
			esc('-');
E 8
I 8
			ttesc('-');
E 8
E 7
	tt.tt_modes = new;
}

D 2
zz_insline()
E 2
I 2
zz_insline(n)
E 2
{
D 2
	esc();
	pc('a');
E 2
I 2
D 7
	if (n == 0) {
		esc();
		pc('a');
	} else {
		esc1();
E 7
I 7
	if (n == 1)
D 8
		esc('a');
E 8
I 8
		ttesc('a');
E 8
	else {
D 8
		esc('A');
E 7
		pc(n + ' ');
E 8
I 8
		ttesc('A');
		ttputc(n + ' ');
E 8
D 7
		pc('A');
E 7
	}
E 2
}

D 2
zz_delline()
E 2
I 2
zz_delline(n)
E 2
{
D 2
	esc();
	pc('d');
E 2
I 2
D 7
	if (n == 0) {
		esc();
		pc('d');
	} else {
		esc1();
E 7
I 7
	if (n == 1)
D 8
		esc('d');
E 8
I 8
		ttesc('d');
E 8
	else {
D 8
		esc('D');
E 7
		pc(n + ' ');
E 8
I 8
		ttesc('D');
		ttputc(n + ' ');
E 8
D 7
		pc('D');
E 7
	}
E 2
}

zz_putc(c)
	char c;
{
D 2
	if (tt.tt_ninsert != tt.tt_insert)
		ZZ_SETINSERT(tt.tt_ninsert);
E 2
	if (tt.tt_nmodes != tt.tt_modes)
		zz_setmodes(tt.tt_nmodes);
D 2
	if (tt.tt_insert) {
		esc();
		pc('i');
		ttputc(c);
	} else
		ttputc(c);
E 2
I 2
	ttputc(c);
E 2
	if (++tt.tt_col == NCOL)
		tt.tt_col = 0, tt.tt_row++;
}

D 2
int zz_histo[127];

E 2
zz_write(p, n)
	register char *p;
	register n;
{
D 2
	if (n < 128)
		zz_histo[n]++;
	else
		zz_histo[127]++;
	if (tt.tt_ninsert != tt.tt_insert)
		ZZ_SETINSERT(tt.tt_ninsert);
E 2
	if (tt.tt_nmodes != tt.tt_modes)
		zz_setmodes(tt.tt_nmodes);
D 2
	if (tt.tt_insert) {
		esc1();
		pc(n + ' ');
		pc('I');
	}
	ttwrite(p, n);
E 2
I 2
D 3
	if (n < N)
		ttwrite(p, n);
	else
		zc_write(p, n);
E 3
I 3
	ttwrite(p, n);
E 3
E 2
	tt.tt_col += n;
	if (tt.tt_col == NCOL)
		tt.tt_col = 0, tt.tt_row++;
}

zz_move(row, col)
	register row, col;
{
I 3
	register x;

E 3
	if (tt.tt_row == row) {
I 9
same_row:
E 9
D 3
		if (tt.tt_col == col)
E 3
I 3
		if ((x = col - tt.tt_col) == 0)
E 3
			return;
		if (col == 0) {
D 8
			pc('\r');
E 8
I 8
			ttctrl('m');
E 8
			goto out;
		}
D 3
		if (tt.tt_col == col - 1) {
E 3
I 3
		switch (x) {
		case 2:
E 3
D 8
			pc(ctrl('f'));
E 8
I 8
			ttctrl('f');
E 8
I 3
		case 1:
D 8
			pc(ctrl('f'));
E 8
I 8
			ttctrl('f');
E 8
E 3
			goto out;
D 3
		}
		if (tt.tt_col == col + 1) {
E 3
I 3
		case -2:
E 3
D 8
			pc('\b');
E 8
I 8
			ttctrl('h');
E 8
I 3
		case -1:
D 8
			pc('\b');
E 8
I 8
			ttctrl('h');
E 8
E 3
			goto out;
		}
I 3
D 11
		if (col & 7 == 0 && x > 0 && x <= 16) {
E 11
I 11
		if ((col & 7) == 0 && x > 0 && x <= 16) {
E 11
D 8
			pc('\t');
E 8
I 8
			ttctrl('i');
E 8
			if (x > 8)
D 8
				pc('\t');
E 8
I 8
				ttctrl('i');
E 8
			goto out;
		}
E 3
D 7
		esc1();
E 7
I 7
D 8
		esc('<');
E 7
		pc(col + ' ');
E 8
I 8
		ttesc('<');
		ttputc(col + ' ');
E 8
D 7
		pc('<');
E 7
		goto out;
	}
	if (tt.tt_col == col) {
D 3
		if (tt.tt_row == row + 1) {
E 3
I 3
		switch (row - tt.tt_row) {
		case 2:
D 8
			pc('\n');
E 8
I 8
			ttctrl('j');
E 8
		case 1:
D 8
			pc('\n');
E 8
I 8
			ttctrl('j');
E 8
			goto out;
		case -2:
E 3
D 8
			pc(ctrl('k'));
E 8
I 8
			ttctrl('k');
E 8
I 3
		case -1:
D 8
			pc(ctrl('k'));
E 8
I 8
			ttctrl('k');
E 8
E 3
			goto out;
		}
D 3
		if (tt.tt_row == row - 1) {
			pc('\n');
			goto out;
		}
E 3
		if (col == 0) {
			if (row == 0)
				goto home;
			if (row == NROW - 1)
				goto ll;
		}
D 7
		esc1();
E 7
I 7
D 8
		esc('>');
E 7
		pc(row + ' ');
E 8
I 8
		ttesc('>');
		ttputc(row + ' ');
E 8
D 7
		pc('>');
E 7
		goto out;
	}
	if (col == 0) {
		if (row == 0) {
home:
D 7
			esc();
			pc('0');
E 7
I 7
D 8
			esc('0');
E 8
I 8
			ttesc('0');
E 8
E 7
			goto out;
		}
I 3
		if (row == tt.tt_row + 1) {
D 8
			pc('\r');
			pc('\n');
E 8
I 8
D 9
			ttctrl('m');
E 9
I 9
			/*
			 * Do newline first to match the sequence
			 * for scroll down and return
			 */
E 9
			ttctrl('j');
I 9
			ttctrl('m');
E 9
E 8
			goto out;
		}
E 3
		if (row == NROW - 1) {
ll:
D 7
			esc();
			pc('1');
E 7
I 7
D 8
			esc('1');
E 8
I 8
			ttesc('1');
E 8
E 7
			goto out;
		}
	}
I 9
	/* favor local motion for better compression */
	if (row == tt.tt_row + 1) {
		ttctrl('j');
		goto same_row;
	}
	if (row == tt.tt_row - 1) {
		ttctrl('k');
		goto same_row;
	}
E 9
D 7
	esc2();
E 7
I 7
D 8
	esc('=');
E 7
	pc(' ' + row);
	pc(' ' + col);
E 8
I 8
	ttesc('=');
	ttputc(' ' + row);
	ttputc(' ' + col);
E 8
D 7
	pc('=');
E 7
out:
	tt.tt_col = col;
	tt.tt_row = row;
}

D 3
zz_init()
E 3
I 3
zz_start()
E 3
{
D 2
	ZZ_SETINSERT(0);
E 2
D 14
	zz_setmodes(0);
	zz_setscroll(0, NROW - 1);
	zz_clear();
E 14
I 2
D 7
	esc1();
E 7
I 7
D 8
	esc('T');
E 7
D 3
	pc(N + ' ');
E 3
I 3
	pc(TOKEN_MAX + ' ');
E 8
I 8
	ttesc('T');
	ttputc(TOKEN_MAX + ' ');
I 13
	ttesc('U');
	ttputc('!');
	zz_ecc = 1;
I 14
	zz_lastc = -1;
	ttesc('v');
	ttflush();
	zz_sum = 0;
	zz_setscroll(0, NROW - 1);
	zz_clear();
	zz_setmodes(0);
E 14
E 13
E 8
E 3
D 7
	pc('T');
E 7
D 3
	zc_init();
E 3
E 2
}

I 14
zz_reset()
{
	zz_setscroll(0, NROW - 1);
	tt.tt_modes = WWM_REV;
	zz_setmodes(0);
	tt.tt_col = tt.tt_row = -10;
}

E 14
zz_end()
{
I 2
D 7
	esc1();
E 7
I 7
D 8
	esc('T');
E 7
	pc(' ');
E 8
I 8
	ttesc('T');
	ttputc(' ');
I 13
	ttesc('U');
	ttputc(' ');
	zz_ecc = 0;
E 13
E 8
D 7
	pc('T');
E 7
D 3
	pc(0);
E 3
E 2
}

zz_clreol()
{
D 7
	esc();
	pc('2');
E 7
I 7
D 8
	esc('2');
E 8
I 8
	ttesc('2');
E 8
E 7
}

zz_clreos()
{
D 7
	esc();
	pc('3');
E 7
I 7
D 8
	esc('3');
E 8
I 8
	ttesc('3');
E 8
E 7
}

zz_clear()
{
D 7
	esc();
	pc('4');
E 7
I 7
D 8
	esc('4');
E 8
I 8
	ttesc('4');
E 8
E 7
	tt.tt_col = tt.tt_row = 0;
}

D 2
zz_delchar()
E 2
I 2
D 5
zz_inschar(n)
E 5
I 5
zz_insspace(n)
E 5
E 2
{
D 2
	esc();
	pc('c');
E 2
I 2
D 7
	if (n != 1) {
		esc1();
E 7
I 7
	if (n == 1)
D 8
		esc('i');
E 8
I 8
		ttesc('i');
E 8
	else {
D 8
		esc('I');
E 7
		pc(n + ' ');
E 8
I 8
		ttesc('I');
		ttputc(n + ' ');
E 8
D 7
		pc('I');
	} else {
		esc();
		pc('i');
E 7
	}
E 2
}

D 2
zz_scroll_down()
E 2
I 2
zz_delchar(n)
E 2
{
D 2
	if (tt.tt_row == tt.tt_scroll_bot)
E 2
I 2
D 7
	if (n != 1) {
		esc1();
E 7
I 7
	if (n == 1)
D 8
		esc('c');
E 8
I 8
		ttesc('c');
E 8
	else {
D 8
		esc('C');
E 7
		pc(n + ' ');
E 8
I 8
		ttesc('C');
		ttputc(n + ' ');
E 8
D 7
		pc('C');
	} else {
		esc();
		pc('c');
E 7
	}
}

zz_scroll_down(n)
{
D 7
	if (n != 1) {
		esc1();
		pc(n + ' ');
		pc('F');
D 3
	} else if (tt.tt_row == tt.tt_scroll_bot)
E 3
I 3
	} else if (tt.tt_row == NROW - 1)
E 3
E 2
		pc('\n');
E 7
I 7
	if (n == 1)
		if (tt.tt_row == NROW - 1)
D 8
			pc('\n');
E 8
I 8
			ttctrl('j');
E 8
		else
D 8
			esc('f');
E 8
I 8
			ttesc('f');
E 8
E 7
	else {
D 7
		esc();
		pc('f');
E 7
I 7
D 8
		esc('F');
		pc(n + ' ');
E 8
I 8
		ttesc('F');
		ttputc(n + ' ');
E 8
E 7
	}
}

D 2
zz_scroll_up()
E 2
I 2
zz_scroll_up(n)
E 2
{
D 2
	esc();
	pc('r');
E 2
I 2
D 7
	if (n == 1) {
		esc();
		pc('r');
	} else {
		esc1();
E 7
I 7
	if (n == 1)
D 8
		esc('r');
E 8
I 8
		ttesc('r');
E 8
	else {
D 8
		esc('R');
E 7
		pc(n + ' ');
E 8
I 8
		ttesc('R');
		ttputc(n + ' ');
E 8
D 7
		pc('R');
E 7
	}
E 2
}

zz_setscroll(top, bot)
{
D 7
	esc2();
E 7
I 7
D 8
	esc('?');
E 7
	pc(top + ' ');
	pc(bot + ' ');
E 8
I 8
	ttesc('?');
	ttputc(top + ' ');
	ttputc(bot + ' ');
E 8
D 7
	pc('?');
E 7
	tt.tt_scroll_top = top;
	tt.tt_scroll_bot = bot;
}

D 2
#ifdef notdef
struct ctoken {
	char ct_index;
	short ct_hash
	unsigned long ct_time;
	unsigned long ct_count;
	char ct_string[8];
	struct ctoken ct_forw;
	struct ctoken ct_back;
	struct ctoken ct_hforw;
	struct ctoken ct_hback;
};

zz_compress(p, n)
	register char *p;
E 2
I 2
D 3
zc_write(s, n)
E 3
I 3
int zz_debug = 0;

zz_set_token(t, s, n)
E 3
	char *s;
E 2
D 3
	register n;
E 3
{
D 2
}

zc_insert(string, hash)
	char *string;
	short hash;
{
E 2
I 2
D 3
	register char *p;
	register h;
	register i;
E 2
	register struct ctoken *tp;

D 2
	for (tp = zc_hashtable[hash];
	     *tp && strncmp(string, tp->ct_string, 8) != 0;
	     tp = tp->ct_hforw)
E 2
I 2
	p = s;
	for (i = N - 2, h = zc_hash(0, *p++); --i >= 0; h = zc_hash(h, *p++))
E 2
		;
D 2
	if (tp == 0) {
		if (eval(q2.ct_back) < THRESH) {
			tp = q2.ct_back;
			bcopy(string, tp->string, 8);
			tp->hash = hash;
E 2
I 2
	for (i = 0;;) {
		tick++;
		h = zc_hash(h, *p++);
		if ((tp = htab[h]) == 0) {
			tp = q2.back;
			if (tp->hash >= 0)
				htab[tp->hash] = 0;
			zc_copy(p - N, tp->string);
			tp->hash = h;
E 2
			tp->count = 0;
I 2
			htab[h] = tp;
		} else if (!zc_equal(tp->string, p - N)) {
			if (tp->index == 0 && zc_eval(tp) < 0) {
				zc_copy(p - N, tp->string);
				tp->count = 0;
			} else {
				line[i] = 0;
				goto cont;
			}
E 2
		}
I 2
		tp->time = tick;
		tp->count++;
		if (tp->index == 0)
			zc_head(tp, &q2);
		else
			zc_head(tp, &q1);
		line[i] = tp;
	cont:
		if (++i > n - N)
			break;
		h = zc_unhash(h, p[- N]);
E 3
I 3
	if (tt.tt_nmodes != tt.tt_modes)
		zz_setmodes(tt.tt_nmodes);
	if (zz_debug) {
		char buf[100];
		zz_setmodes(WWM_REV);
		(void) sprintf(buf, "%02x=", t);
		ttputs(buf);
		tt.tt_col += 3;
E 3
E 2
	}
D 2
	tp->time = zc_time;
	tp->count++;
E 2
I 2
D 3
	while (i < n)
		line[i++] = 0;
	for (i = 0; i < n;) {
		register struct ctoken *tp;

		if ((tp = line[i]) == 0) {
			pc(s[i]);
			i++;
		} else if (tp->index > 0) {
			zc_head(tp, &q1);
			pc(tp->index - 1 | 0x80);
			wwzc1++;
			wwzcsave += N - 1;
			i += N;
		} else if (tp->index < 0) {
			tp->index = - tp->index;
			zc_head(tp, &q1);
			pc(ctrl('^'));
			pc(tp->index - 1);
			ttwrite(tp->string, N);
			wwzc0++;
			wwzcsave -= 2;
			i += N;
		} else if (tp->count > 1 && zc_eval(tp) > zc_eval(q1.back)) {
			tp->index = abs(q1.back->index);
			q1.back->index = 0;
			zc_head(q1.back, &q2);
			zc_head(tp, &q1);
			pc(ctrl('^'));
			pc(tp->index - 1);
			ttwrite(tp->string, N);
			wwzc0++;
			wwzcsave -= 2;
			i += N;
		} else {
			pc(s[i]);
			i++;
		}
	}
	wwzctotal += n;
E 3
I 3
D 4
	pc(ctrl('^'));
	pc(t);
E 4
I 4
D 8
	pc(0x80);
	pc(t + 1);
E 8
I 8
	ttputc(0x80);
	ttputc(t + 1);
E 8
E 4
	s[n - 1] |= 0x80;
	ttwrite(s, n);
	s[n - 1] &= ~0x80;
D 9
	tt.tt_col += n;
	if (tt.tt_col == NCOL)
		tt.tt_col = 0, tt.tt_row++;
E 9
E 3
}

D 3
zc_head(tp, q)
	register struct ctoken *tp, *q;
E 3
I 3
/*ARGSUSED*/
zz_put_token(t, s, n)
	char *s;
E 3
{
D 3

E 2
	tp->back->forw = tp->forw;
	tp->forw->back = tp->back;
D 2
	if (tp->index == 0) {
		if (eval(q1.ct_back) < eval(tp)) {
		}
E 2
I 2
	q->forw->back = tp;
	tp->forw = q->forw;
	q->forw = tp;
	tp->back = q;
}

zc_init()
{
	register struct ctoken *tp;

	for (tp = tokens; tp < tokens + sizeof tokens / sizeof *tokens; tp++)
		if (tp->index > 0)
			tp->index = - tp->index;
}

zc_start()
{
	register struct ctoken *tp;
	register i;

	tick = 0;
	bzero((char *)htab, sizeof htab);
	q1.forw = &q1;
	q1.back = &q1;
	for (i = 0, tp = tokens; i < NTOKEN; i++, tp++) {
		tp->index = i + 1;
		tp->hash = -1;
		tp->count = 0;
		tp->time = 0;
		q1.forw->back = tp;
		tp->forw = q1.forw;
		q1.forw = tp;
		tp->back = &q1;
E 3
I 3
	if (tt.tt_nmodes != tt.tt_modes)
		zz_setmodes(tt.tt_nmodes);
	if (zz_debug) {
		char buf[100];
		zz_setmodes(WWM_REV);
		(void) sprintf(buf, "%02x>", t);
		ttputs(buf);
		tt.tt_col += 3;
E 3
E 2
	}
I 2
D 3
	q2.forw = &q2;
	q2.back = &q2;
	for (; i < sizeof tokens / sizeof *tokens; i++, tp++) {
		tp->index = 0;
		tp->hash = -1;
		tp->count = 0;
		tp->time = 0;
		q2.forw->back = tp;
		tp->forw = q2.forw;
		q2.forw = tp;
		tp->back = &q2;
	}
E 3
I 3
D 4
	pc(t | 0x80);
E 4
I 4
D 8
	pc(t + 0x81);
E 8
I 8
	ttputc(t + 0x81);
E 8
E 4
D 9
	tt.tt_col += n;
	if (tt.tt_col == NCOL)
		tt.tt_col = 0, tt.tt_row++;
E 9
E 3
E 2
}
D 2
#endif
E 2

I 13
zz_rint(p, n)
	char *p;
{
D 14
	static lastc;
E 14
	register i;
	register char *q;

	if (!zz_ecc)
		return n;
	for (i = n, q = p; --i >= 0;) {
		register c = (unsigned char) *p++;
D 14
		if (zz_ecc == 1) {
			if (c)
				*q++ = c;
			else {
E 14
I 14

		if (zz_lastc == 0) {
			switch (c) {
			case 0:
				*q++ = 0;
				zz_lastc = -1;
				break;
			case 1:		/* start input ecc */
E 14
				zz_ecc = 2;
D 14
				lastc = -1;
E 14
I 14
				zz_lastc = -1;
				wwnreadstat++;
				break;
			case 2:		/* ack checkpoint */
				tt.tt_ack = 1;
				zz_lastc = -1;
				wwnreadack++;
				break;
			case 3:		/* nack checkpoint */
				tt.tt_ack = -1;
				zz_lastc = -1;
				wwnreadnack++;
				break;
			default:
				zz_lastc = c;
				wwnreadec++;
E 14
			}
I 14
		} else if (zz_ecc == 1) {
			if (c)
				*q++ = c;
			else
				zz_lastc = 0;
E 14
		} else {
D 14
			if (lastc < 0) {
				lastc = c;
			} else if (lastc == c) {
				*q++ = lastc;
				lastc = -1;
E 14
I 14
			if (zz_lastc < 0) {
				zz_lastc = c;
			} else if (zz_lastc == c) {
				*q++ = zz_lastc;
				zz_lastc = -1;
E 14
			} else {
				wwnreadec++;
D 14
				lastc = c;
E 14
I 14
				zz_lastc = c;
E 14
			}
		}
	}
	return q - (p - n);
}

I 14
zz_checksum(p, n)
	register char *p;
	register n;
{
	while (--n >= 0) {
		register c = *p++ & 0x7f;
		c ^= zz_sum;
		zz_sum = c << 1 | c >> 11 & 1;
	}
}

zz_compress(flag)
{
	if (flag)
		tt.tt_checksum = 0;
	else
		tt.tt_checksum = zz_checksum;
}

zz_checkpoint()
{
	static char x[] = { ctrl('['), 'V', 0, 0 };

	zz_checksum(x, sizeof x);
	ttesc('V');
	ttputc(' ' + (zz_sum & 0x3f));
	ttputc(' ' + (zz_sum >> 6 & 0x3f));
	ttflush();
	zz_sum = 0;
}

E 14
E 13
tt_zapple()
{
I 2
D 3
	zc_start();
E 3
D 5
	tt.tt_inschar = zz_inschar;
E 5
I 5
	tt.tt_insspace = zz_insspace;
E 5
E 2
	tt.tt_delchar = zz_delchar;
	tt.tt_insline = zz_insline;
	tt.tt_delline = zz_delline;
	tt.tt_clreol = zz_clreol;
	tt.tt_clreos = zz_clreos;
	tt.tt_scroll_down = zz_scroll_down;
	tt.tt_scroll_up = zz_scroll_up;
	tt.tt_setscroll = zz_setscroll;
	tt.tt_availmodes = WWM_REV;
D 2
	tt.tt_hasinsert = 1;
E 2
	tt.tt_wrap = 1;
	tt.tt_retain = 0;
D 3
	tt.tt_ncol = 80;
	tt.tt_nrow = 24;
	tt.tt_init = zz_init;
E 3
I 3
	tt.tt_ncol = NCOL;
	tt.tt_nrow = NROW;
	tt.tt_start = zz_start;
I 14
	tt.tt_reset = zz_reset;
E 14
E 3
	tt.tt_end = zz_end;
	tt.tt_write = zz_write;
	tt.tt_putc = zz_putc;
	tt.tt_move = zz_move;
	tt.tt_clear = zz_clear;
D 2
	tt.tt_setinsert = zz_setinsert;
E 2
	tt.tt_setmodes = zz_setmodes;
	tt.tt_frame = gen_frame;
I 9
	tt.tt_padc = TT_PADC_NONE;
E 9
I 3
D 4
	tt.tt_ntoken = 128;
E 4
I 4
	tt.tt_ntoken = 127;
E 4
	tt.tt_set_token = zz_set_token;
	tt.tt_put_token = zz_put_token;
	tt.tt_token_min = 1;
	tt.tt_token_max = TOKEN_MAX;
	tt.tt_set_token_cost = 2;
	tt.tt_put_token_cost = 1;
I 14
	tt.tt_compress = zz_compress;
	tt.tt_checksum = zz_checksum;
	tt.tt_checkpoint = zz_checkpoint;
	tt.tt_reset = zz_reset;
E 14
I 13
	tt.tt_rint = zz_rint;
E 13
E 3
	return 0;
}
E 1
