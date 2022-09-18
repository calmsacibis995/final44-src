h50738
s 00003/00008/00215
d D 8.3 94/07/27 14:54:38 bostic 31 30
c delete __FULLLINE, it's never used
e
s 00003/00002/00220
d D 8.2 94/05/04 06:24:49 bostic 30 29
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00220
d D 8.1 93/07/20 07:23:54 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00219
d D 5.19 93/07/20 07:22:58 bostic 28 26
c win->orig is not initialized, but referenced in lots of routines.
c It should be initialized to NULL.
c Loop will reference element i == nl which is out of bounds.
c From: christos@deshaw.com (Christos Zoulas)
e
s 00002/00002/00218
d R 8.1 93/06/04 16:48:42 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00001/00214
d D 5.18 93/05/17 13:12:38 elan 26 25
c Flags field in line structures should be set by newwin, not by 
c __set_subwin(), so that refresh() can call __set_subwin().
e
s 00011/00011/00204
d D 5.17 93/05/16 15:54:43 bostic 25 24
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00027/00015/00188
d D 5.16 93/04/27 15:07:13 elan 24 23
c Fixed up subwin creation -- need line space, but point it into
c parent's window space.
e
s 00001/00001/00202
d D 5.15 93/03/02 14:43:39 elan 23 22
c Fixed cast to __hash().
e
s 00001/00001/00202
d D 5.14 93/02/02 14:45:11 elan 22 21
c __swflags is global.
e
s 00000/00001/00203
d D 5.13 93/02/02 13:50:08 elan 21 20
c Fixed inconsistency in function declarations (static vs. global).
e
s 00046/00056/00158
d D 5.12 92/11/12 12:39:56 elan 20 19
c Set up correct memory allocation and pointers for subwindows.
e
s 00006/00002/00208
d D 5.11 92/11/11 17:35:15 elan 19 18
c Added pointers to firstch and lastch for correct operation of 
c subwindows.
e
s 00038/00047/00172
d D 5.10 92/10/26 12:46:44 elan 18 17
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00007/00005/00212
d D 5.9 92/10/20 10:44:36 elan 17 16
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00002/00001/00215
d D 5.8 92/09/21 15:23:31 elan 16 15
c Added __ISPASTEOL support and changed hash fn interface.
e
s 00115/00100/00101
d D 5.7 92/09/14 11:00:37 elan 15 14
c Converted to new data structures.
e
s 00004/00004/00197
d D 5.6 92/08/23 14:38:54 bostic 14 13
c lint
e
s 00082/00090/00119
d D 5.5 92/08/23 11:32:35 bostic 13 11
c KNF, lint
e
s 00070/00079/00130
d R 5.5 92/05/15 15:22:29 bostic 12 11
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00208
d D 5.4 90/06/01 15:39:31 bostic 11 10
c new copyright notice
e
s 00010/00005/00209
d D 5.3 88/06/30 17:21:52 bostic 10 9
c install approved copyright notice
e
s 00010/00004/00204
d D 5.2 88/06/08 13:57:32 bostic 9 8
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00198
d D 5.1 85/06/07 11:37:49 dist 8 7
c Add copyright
e
s 00079/00052/00120
d D 1.7 85/05/01 17:27:09 bloom 7 6
c new version from arnold
e
s 00007/00001/00165
d D 1.6 83/05/09 20:35:38 arnold 6 5
c integrate subwindows fully into all parts of curses
e
s 00007/00003/00159
d D 1.5 83/03/27 15:08:34 arnold 5 4
c 
e
s 00007/00005/00155
d D 1.4 82/02/16 17:05:56 arnold 4 3
c check boundary conditions properly
e
s 00001/00001/00159
d D 1.3 81/10/26 00:06:20 arnold 3 2
c use calloc to get window structure to guarantee all zero start
e
s 00003/00001/00157
d D 1.2 81/10/26 00:03:30 arnold 2 1
c return NULL at all appropriate places
e
s 00158/00000/00000
d D 1.1 81/01/26 17:03:04 arnold 1 0
c date and time created 81/01/26 17:03:04 by arnold
e
u
U
t
T
I 1
/*
I 8
D 9
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
D 29
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 29
I 29
D 30
 * Copyright (c) 1981, 1993
E 30
I 30
 * Copyright (c) 1981, 1993, 1994
E 30
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
D 11
 * Redistribution and use in source and binary forms are permitted
D 10
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 10
I 10
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 10
E 9
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
D 13
#endif /* not lint */
E 13
I 13
#endif	/* not lint */
E 13
E 9

D 13
/*
E 8
 * allocate space for and set up defaults for a new window
 *
D 5
 * %G% (Berkeley) %W
E 5
I 5
D 7
 * %G% (Berkeley) %W%
E 7
I 7
D 8
 * %W% (Berkeley) %G%
E 8
E 7
E 5
 */
E 13
I 13
D 30
#include <curses.h>
E 30
#include <stdlib.h>
I 30

#include "curses.h"
E 30
E 13

D 13
# include	"curses.ext"
E 13
I 13
#undef	nl		/* Don't need it here, and it interferes. */
E 13

D 7
short	*calloc();
WINDOW	*malloc();
E 7
I 7
D 13
char	*malloc();
E 13
I 13
D 15
static WINDOW *makenew __P((int, int, int, int));
E 15
I 15
D 20
static WINDOW 	*makenew __P((int, int, int, int));
E 20
I 20
static WINDOW 	*__makenew __P((int, int, int, int, int));
E 20
D 21
static void	 __swflags __P((WINDOW *));
E 21
E 15
E 13
E 7

I 15
void	 __set_subwin __P((WINDOW *, WINDOW *));

E 15
I 7
D 13
# define	SMALLOC	(short *) malloc

E 7
static WINDOW	*makenew();

# undef		nl	/* don't need it here, and it interferes	*/

E 13
I 13
/*
 * newwin --
 *	Allocate space for and set up defaults for a new window.
 */
E 13
WINDOW *
D 15
newwin(num_lines, num_cols, begy, begx)
D 13
int	num_lines, num_cols, begy, begx;
E 13
I 13
	int num_lines, num_cols, begy, begx;
E 15
I 15
newwin(nl, nc, by, bx)
	register int nl, nc, by, bx;
E 15
E 13
{
D 13
	reg WINDOW	*win;
	reg char	*sp;
	reg int		i, by, bx, nl, nc;
I 7
	reg int		j;
E 13
I 13
	register WINDOW *win;
D 15
	register int by, bx, i, j, nl, nc;
E 15
I 15
D 18
	register LINE *lp;
E 18
I 18
	register __LINE *lp;
E 18
	register int  i, j;
E 15
D 18
	register char *sp;
E 18
I 18
	register __LDATA *sp;
E 18
E 13
E 7

D 15
	by = begy;
	bx = begx;
	nl = num_lines;
	nc = num_cols;

E 15
	if (nl == 0)
		nl = LINES - by;
	if (nc == 0)
		nc = COLS - bx;
I 15

E 15
D 20
	if ((win = makenew(nl, nc, by, bx)) == NULL)
E 20
I 20
	if ((win = __makenew(nl, nc, by, bx, 0)) == NULL)
E 20
D 13
		return ERR;
I 7
	if ((win->_firstch = SMALLOC(nl * sizeof win->_firstch[0])) == NULL) {
E 13
I 13
		return (NULL);
D 15
	if ((win->_firstch = malloc(nl * sizeof(win->_firstch[0]))) == NULL) {
E 13
		free(win->_y);
		free(win);
D 13
		return NULL;
E 13
I 13
		return (NULL);
E 13
	}
D 13
	if ((win->_lastch = SMALLOC(nl * sizeof win->_lastch[0])) == NULL) {
E 13
I 13
	if ((win->_lastch = malloc(nl * sizeof(win->_lastch[0]))) == NULL) {
E 13
		free(win->_y);
		free(win->_firstch);
		free(win);
D 13
		return NULL;
E 13
I 13
		return (NULL);
E 13
	}
	win->_nextp = win;
	for (i = 0; i < nl; i++) {
		win->_firstch[i] = _NOCHANGE;
		win->_lastch[i] = _NOCHANGE;
	}
E 7
	for (i = 0; i < nl; i++)
D 7
		if ((win->_y[i] = (char *) calloc(nc, sizeof (char))) == NULL) {
			reg int		j;

E 7
I 7
D 13
		if ((win->_y[i] = malloc(nc * sizeof win->_y[0])) == NULL) {
E 13
I 13
		if ((win->_y[i] = malloc(nc * sizeof(win->_y[0]))) == NULL) {
E 13
E 7
			for (j = 0; j < i; j++)
D 7
				cfree(win->_y[j]);
			cfree(win->_firstch);
			cfree(win->_lastch);
			cfree(win->_y);
			cfree(win);
E 7
I 7
				free(win->_y[j]);
			free(win->_firstch);
			free(win->_lastch);
			free(win->_y);
			free(win);
E 7
D 13
			return ERR;
		}
		else
			for (sp = win->_y[i]; sp < win->_y[i] + nc; )
E 13
I 13
			return (NULL);
		} else
			for (sp = win->_y[i]; sp < win->_y[i] + nc;)
E 13
				*sp++ = ' ';
I 6
D 7
	win->_nextp = win;
E 7
I 7
	win->_ch_off = 0;
E 15
I 15

	win->nextp = win;
	win->ch_off = 0;
I 28
	win->orig = NULL;
E 28

E 15
D 13
# ifdef DEBUG
	fprintf(outf, "NEWWIN: win->_ch_off = %d\n", win->_ch_off);
# endif
E 7
E 6
	return win;
E 13
I 13
#ifdef DEBUG
D 15
	__TRACE("newwin: win->_ch_off = %d\n", win->_ch_off);
E 15
I 15
D 25
	__TRACE("newwin: win->ch_off = %d\n", win->ch_off);
E 25
I 25
	__CTRACE("newwin: win->ch_off = %d\n", win->ch_off);
E 25
E 15
#endif
I 15

D 18
	for (lp = win->topline, i = 0; i < nl; i++, lp = lp->next) {
E 18
I 18
D 28
	for (lp = win->lines[0], i = 0; i < nl; i++, lp = win->lines[i]) {
E 28
I 28
	for (i = 0; i < nl; i++) {
		lp = win->lines[i];
E 28
E 18
		lp->flags = 0;
D 18
		lp->flags &= ~__ISDIRTY;
I 16
		lp->flags &= ~__ISPASTEOL;
E 16
D 17
		for (sp = lp->line; sp < lp->line + nc; sp++)
E 17
I 17
		for (sp = lp->line; sp < lp->line + nc; sp++) {
E 17
			*sp = ' ';
I 17
			*(sp + nc) &= ~__STANDOUT;
E 18
I 18
		for (sp = lp->line, j = 0; j < nc; j++, sp++) {
			sp->ch = ' ';
			sp->attr = 0;
E 18
		}
E 17
D 16
		lp->hash = __hash(lp->line);
E 16
I 16
D 18
		lp->hash = __hash(lp->line, nc);
E 18
I 18
D 23
		lp->hash = __hash(lp->line, nc * __LDATASIZE);
E 23
I 23
		lp->hash = __hash((char *) lp->line, nc * __LDATASIZE);
E 23
E 18
E 16
	}
D 17

E 17
E 15
	return (win);
E 13
}

WINDOW *
D 15
subwin(orig, num_lines, num_cols, begy, begx)
E 15
I 15
subwin(orig, nl, nc, by, bx)
E 15
D 13
reg WINDOW	*orig;
D 7
int		num_lines, num_cols, begy, begx; {

E 7
I 7
int		num_lines, num_cols, begy, begx;
E 13
I 13
	register WINDOW *orig;
D 15
	int num_lines, num_cols, begy, begx;
E 15
I 15
	register int by, bx, nl, nc;
E 15
E 13
{
I 26
	int i;
	__LINE *lp;
E 26
E 7
D 13
	reg int		i;
	reg WINDOW	*win;
	reg int		by, bx, nl, nc;
E 13
I 13
	register WINDOW *win;
D 14
	register int by, bx, i, nl, nc;
E 14
I 14
D 15
	register int by, bx, nl, nc;
E 15
E 14
E 13
D 7
	reg int		j, k;
E 7

D 15
	by = begy;
	bx = begx;
	nl = num_lines;
	nc = num_cols;

E 15
D 13
	/*
	 * make sure window fits inside the original one
	 */
# ifdef	DEBUG
	fprintf(outf, "SUBWIN(%0.2o, %d, %d, %d, %d)\n", orig, nl, nc, by, bx);
# endif
E 13
I 13
	/* Make sure window fits inside the original one. */
#ifdef	DEBUG
D 25
	__TRACE("subwin: (%0.2o, %d, %d, %d, %d)\n", orig, nl, nc, by, bx);
E 25
I 25
	__CTRACE("subwin: (%0.2o, %d, %d, %d, %d)\n", orig, nl, nc, by, bx);
E 25
#endif
E 13
D 15
	if (by < orig->_begy || bx < orig->_begx
D 4
	    || by + nl > orig->_maxy || bx + nc > orig->_maxx)
E 4
I 4
	    || by + nl > orig->_maxy + orig->_begy
D 5
	    || bx + nc > orig->_maxx + orig->_begx)
E 5
I 5
D 7
	    || bx + nc > orig->_maxx + orig->_begx) {
I 6
# ifdef	DEBUG
E 6
		fprintf(stderr, "returning ERR (1)\n");
I 6
		fprintf(stderr, "SUBWIN(begx = %d, begy = %d,maxx = %d, maxy = %d, nl = %d, nc = %d, by = %d, bx = %d)\n", orig->_begx,orig->_begy,orig->_maxx,orig->_maxy, nl, nc, by, bx);
# endif
E 7
I 7
	    || bx + nc > orig->_maxx + orig->_begx)
E 15
I 15
	if (by < orig->begy || bx < orig->begx
	    || by + nl > orig->maxy + orig->begy
	    || bx + nc > orig->maxx + orig->begx)
E 15
E 7
E 6
E 5
E 4
D 13
		return ERR;
E 13
I 13
		return (NULL);
E 13
I 5
D 7
	}
E 7
E 5
	if (nl == 0)
D 4
		nl = orig->_maxy - orig->_begy - by;
E 4
I 4
D 15
		nl = orig->_maxy + orig->_begy - by;
E 15
I 15
		nl = orig->maxy + orig->begy - by;
E 15
E 4
	if (nc == 0)
D 4
		nc = orig->_maxx - orig->_begx - bx;
E 4
I 4
D 15
		nc = orig->_maxx + orig->_begx - bx;
E 15
I 15
		nc = orig->maxx + orig->begx - bx;
E 15
E 4
D 5
	if ((win = makenew(nl, nc, by, bx)) == NULL)
E 5
I 5
D 7
	if ((win = makenew(nl, nc, by, bx)) == NULL) {
		fprintf(stderr, "returning ERR (2)\n");
E 7
I 7
D 20
	if ((win = makenew(nl, nc, by, bx)) == NULL)
E 20
I 20
	if ((win = __makenew(nl, nc, by, bx, 1)) == NULL)
E 20
E 7
E 5
D 13
		return ERR;
E 13
I 13
		return (NULL);
E 13
I 5
D 7
	}
E 5
D 4
	j = orig->_begy + by;
	k = orig->_begx + bx;
E 4
I 4
	j = by - orig->_begy;
	k = bx - orig->_begx;
E 4
	for (i = 0; i < nl; i++)
		win->_y[i] = &orig->_y[j++][k];
E 7
D 6
	win->_flags = _SUBWIN;
E 6
I 6
D 15
	win->_nextp = orig->_nextp;
	orig->_nextp = win;
	win->_orig = orig;
E 15
I 15
	win->nextp = orig->nextp;
	orig->nextp = win;
	win->orig = orig;
I 26

	/* Initialize flags here so that refresh can also use __set_subwin. */
	for (lp = win->lspace, i = 0; i < win->maxy; i++, lp++)
		lp->flags = 0;
E 26
E 15
I 7
D 13
	_set_subwin_(orig, win);
E 7
E 6
	return win;
E 13
I 13
	__set_subwin(orig, win);
	return (win);
E 13
}

/*
I 7
D 13
 * this code is shared with mvwin()
E 13
I 13
 * This code is shared with mvwin().
E 13
 */
D 13
_set_subwin_(orig, win)
register WINDOW	*orig, *win;
E 13
I 13
D 14
__set_subwin_(orig, win)
E 14
I 14
void
__set_subwin(orig, win)
E 14
	register WINDOW *orig, *win;
E 13
{
I 24
	int i;
	__LINE *lp, *olp;

E 24
D 13
	register int	i, j, k;
E 13
I 13
D 15
	register int i, j, k;
E 15
I 15
D 20
	register int j, k, ocnt, cnt;
D 18
	register LINE *lp, *olp;
E 18
I 18
	register __LINE *lp, *olp;
E 20
I 20
	win->ch_off = win->begx - orig->begx;
D 24
	win->lines = &orig->lines[win->begy];
E 24
I 24
	/*  Point line pointers to line space. */
	for (lp = win->lspace, i = 0; i < win->maxy; i++, lp++) {
		win->lines[i] = lp;
		olp = orig->lines[i + win->begy];
		lp->line = &olp->line[win->begx];
		lp->firstchp = &olp->firstch;
		lp->lastchp = &olp->lastch;
D 26
		lp->flags = 0;
E 26
		lp->hash = __hash((char *) lp->line, win->maxx * __LDATASIZE);
	}
E 24
E 20
E 18
E 15
E 13

D 15
	j = win->_begy - orig->_begy;
	k = win->_begx - orig->_begx;
	win->_ch_off = k;
E 15
I 15
D 20
	j = win->begy - orig->begy;
	k = win->begx - orig->begx;
	win->ch_off = k;
E 20
E 15
D 13
# ifdef DEBUG
	fprintf(outf, "_SET_SUBWIN_: win->_ch_off = %d\n", win->_ch_off);
# endif
E 13
I 13
#ifdef DEBUG
D 15
	__TRACE("__set_subwin: win->_ch_off = %d\n", win->_ch_off);
E 15
I 15
D 25
	__TRACE("__set_subwin: win->ch_off = %d\n", win->ch_off);
E 25
I 25
	__CTRACE("__set_subwin: win->ch_off = %d\n", win->ch_off);
E 25
E 15
#endif
E 13
D 15
	win->_firstch = &orig->_firstch[j];
	win->_lastch = &orig->_lastch[j];
	for (i = 0; i < win->_maxy; i++, j++)
		win->_y[i] = &orig->_y[j][k];
E 15
I 15
D 20

D 18
	lp = win->topline;
	olp = orig->topline; 
	ocnt = 0;
	for (ocnt = 0; ocnt < orig->maxy && cnt < win->maxy; ocnt++) {
		if (ocnt >= j) {
			lp->firstch = olp->firstch;
			lp->lastch = olp->lastch;
			lp->line = &olp->line[k];
			lp = lp->next;
			lp->flags = olp->flags;
			cnt++;
		}
		olp = olp->next;
E 18
I 18
	for (ocnt = j, cnt = 0; ocnt < orig->maxy && cnt < win->maxy; 
	     cnt++, ocnt++) {
		olp = orig->lines[ocnt];
		lp = win->lines[cnt];
D 19
		lp->firstch = olp->firstch;
		lp->lastch = olp->lastch;
E 19
I 19
		lp->firstchp = olp->firstchp;
		lp->lastchp = olp->lastchp;
E 19
		lp->line = &olp->line[k];
		lp->flags = olp->flags;
		cnt++;
E 18
	}
E 20
E 15
D 14

E 14
}

/*
E 7
D 13
 *	This routine sets up a window buffer and returns a pointer to it.
E 13
I 13
D 20
 * makenew --
E 20
I 20
 * __makenew --
E 20
 *	Set up a window buffer and returns a pointer to it.
E 13
 */
static WINDOW *
D 15
makenew(num_lines, num_cols, begy, begx)
D 13
int	num_lines, num_cols, begy, begx; {
E 13
I 13
	int num_lines, num_cols, begy, begx;
E 15
I 15
D 20
makenew(nl, nc, by, bx)
E 20
I 20
__makenew(nl, nc, by, bx, sub)
E 20
	register int by, bx, nl, nc;
I 20
	int sub;
E 20
E 15
{
	register WINDOW *win;
D 14
	register int by, bx, i, nl, nc;
E 14
I 14
D 15
	register int by, bx, nl, nc;
E 15
I 15
D 18
	register LINE *cur, *prev;
E 18
I 18
	register __LINE *lp;
E 18
	int i;
I 18
	
E 18
E 15
E 14
E 13

D 13
	reg int		i;
	reg WINDOW	*win;
	reg int		by, bx, nl, nc;

E 13
D 15
	by = begy;
	bx = begx;
	nl = num_lines;
	nc = num_cols;

E 15
D 13
# ifdef	DEBUG
	fprintf(outf, "MAKENEW(%d, %d, %d, %d)\n", nl, nc, by, bx);
# endif
D 3
	if ((win = (WINDOW *) malloc(sizeof (WINDOW))) == NULL)
E 3
I 3
D 7
	if ((win = (WINDOW *) calloc(1, sizeof (WINDOW))) == NULL)
E 7
I 7
	if ((win = (WINDOW *) malloc(sizeof *win)) == NULL)
E 7
E 3
		return NULL;
# ifdef DEBUG
	fprintf(outf, "MAKENEW: nl = %d\n", nl);
# endif
D 7
	if ((win->_y = (char **) calloc(nl, sizeof (char *))) == NULL) {
		cfree(win);
E 7
I 7
	if ((win->_y = (char **) malloc(nl * sizeof win->_y[0])) == NULL) {
E 13
I 13
#ifdef	DEBUG
D 25
	__TRACE("makenew: (%d, %d, %d, %d)\n", nl, nc, by, bx);
E 25
I 25
	__CTRACE("makenew: (%d, %d, %d, %d)\n", nl, nc, by, bx);
E 25
#endif
	if ((win = malloc(sizeof(*win))) == NULL)
		return (NULL);
#ifdef DEBUG
D 25
	__TRACE("makenew: nl = %d\n", nl);
E 25
I 25
	__CTRACE("makenew: nl = %d\n", nl);
E 25
#endif
D 15
	if ((win->_y = malloc(nl * sizeof(win->_y[0]))) == NULL) {
E 15
I 15

D 18
	/*
	 * Allocate structure of lines in a window.
E 18
I 18
D 20
	/* 
 	 * Set up line pointer array and line space.
E 18
         */
D 18
	if ((win->topline = malloc (nl * sizeof (LINE))) == NULL) {
E 18
I 18
	if ((win->lines = malloc (nl * sizeof(__LINE *))) == NULL) {
		free(win);
		return NULL;
E 20
I 20
D 24
	/* Don't allocate space if it's a subwindow */
E 24
I 24
	/* 
	 * Set up line pointer array and line space.
	 */
	if ((win->lines = malloc (nl * sizeof(__LINE *))) == NULL) {
		free(win);
		return NULL;
	}
	if ((win->lspace = malloc (nl * sizeof(__LINE))) == NULL) {
		free (win);
		free (win->lines);
		return NULL;
	}

	/* Don't allocate window and line space if it's a subwindow */
E 24
	if (!sub) {
D 24
		/* 
		 * Set up line pointer array and line space.
		 */
		if ((win->lines = malloc (nl * sizeof(__LINE *))) == NULL) {
			free(win);
			return NULL;
		}
		if ((win->lspace = malloc (nl * sizeof(__LINE))) == NULL) {
			free (win);
			free (win->lines);
			return NULL;
		}
		
E 24
		/*
		 * Allocate window space in one chunk.
		 */
		if ((win->wspace = 
		    malloc(nc * nl * sizeof(__LDATA))) == NULL) {
			free(win->lines);
			free(win->lspace);
			free(win);
			return NULL;
		}
		
		/*
		 * Point line pointers to line space, and lines themselves into
		 * window space.
		 */
		for (lp = win->lspace, i = 0; i < nl; i++, lp++) {
			win->lines[i] = lp;
			lp->line = &win->wspace[i * nc];
			lp->firstchp = &lp->firstch;
			lp->lastchp = &lp->lastch;
			lp->firstch = 0;
			lp->lastch = 0;
		}
E 20
	}
D 20
	if ((win->lspace = malloc (nl * sizeof(__LINE))) == NULL) {
E 18
		free (win);
I 18
		free (win->lines);
E 18
		return NULL;
	}

	/*
	 * Allocate window space in one chunk.
	 */
D 17
	if ((win->wspace = malloc(nc * nl)) == NULL) {
E 17
I 17
D 18
	if ((win->wspace = malloc(2 * nc * nl)) == NULL) {
E 17
		free(win->topline);
E 18
I 18
	if ((win->wspace = malloc(nc * nl * sizeof(__LDATA))) == NULL) {
		free(win->lines);
		free(win->lspace);
E 18
E 15
E 13
		free(win);
E 7
D 2
		return (WINDOW *) NULL;
E 2
I 2
D 13
		return NULL;
E 13
I 13
D 15
		return (NULL);
E 15
I 15
		return NULL;
E 15
E 13
E 2
	}
I 15
D 18
	/* 
 	 * Link up the lines, set up line pointer array and point line pointers
D 17
	 * to the line space.
E 17
I 17
	 * to the line space, and point standout arrays to follow lines.
E 17
         */
	if ((win->lines = malloc (nl * sizeof (LINE *))) == NULL) {
		free(win->wspace);
		free(win->topline);
		free(win);
		return NULL;
	}
	prev = &win->topline[nl - 1];
	cur = win->topline;
	for (i = 1; i <= nl; i++, prev = cur, cur = cur->next) {
		cur->next = &win->topline[i % nl];
		cur->prev = prev;
D 17
		cur->line = &win->wspace[(i - 1) * nc];
E 17
I 17
		cur->line = &win->wspace[(i - 1) * 2 * nc];
		cur->standout = cur->line + nc;
E 17
		win->lines[i - 1] = cur;
E 18
I 18

	/*
	 * Point line pointers to line space, and lines themselves into
	 * window space.
	 */
	for (lp = win->lspace, i = 0; i < nl; i++, lp++) {
		win->lines[i] = lp;
	        lp->line = &win->wspace[i * nc];
I 19
		lp->firstchp = &lp->firstch;
		lp->lastchp = &lp->lastch;
		lp->firstch = 0;
		lp->lastch = 0;
E 19
E 18
	}

E 20
E 15
D 7
	if ((win->_firstch = calloc(nl, sizeof (short))) == NULL) {
		cfree(win);
		cfree(win->_y);
I 2
		return NULL;
E 2
	}
	if ((win->_lastch = calloc(nl, sizeof (short))) == NULL) {
		cfree(win);
		cfree(win->_y);
		cfree(win->_firstch);
I 2
		return NULL;
E 2
	}
E 7
D 13
# ifdef DEBUG
	fprintf(outf, "MAKENEW: nc = %d\n", nc);
# endif
E 13
I 13
#ifdef DEBUG
D 25
	__TRACE("makenew: nc = %d\n", nc);
E 25
I 25
	__CTRACE("makenew: nc = %d\n", nc);
E 25
#endif
E 13
D 15
	win->_cury = win->_curx = 0;
D 7
	win->_clear = (nl == LINES && nc == COLS);
E 7
I 7
D 13
	win->_clear = FALSE;
E 13
I 13
	win->_clear = 0;
E 13
E 7
	win->_maxy = nl;
	win->_maxx = nc;
	win->_begy = by;
	win->_begx = bx;
I 4
	win->_flags = 0;
E 4
D 13
	win->_scroll = win->_leave = FALSE;
D 7
	for (i = 0; i < nl; i++)
		win->_firstch[i] = win->_lastch[i] = _NOCHANGE;
	if (bx + nc == COLS) {
		win->_flags |= _ENDLINE;
		if (bx == 0 && nl == LINES && by == 0)
			win->_flags |= _FULLWIN;
		if (by + nl == LINES)
			win->_flags |= _SCROLLWIN;
	}
E 7
I 7
	_swflags_(win);
E 7
# ifdef DEBUG
	fprintf(outf, "MAKENEW: win->_clear = %d\n", win->_clear);
	fprintf(outf, "MAKENEW: win->_leave = %d\n", win->_leave);
	fprintf(outf, "MAKENEW: win->_scroll = %d\n", win->_scroll);
	fprintf(outf, "MAKENEW: win->_flags = %0.2o\n", win->_flags);
	fprintf(outf, "MAKENEW: win->_maxy = %d\n", win->_maxy);
	fprintf(outf, "MAKENEW: win->_maxx = %d\n", win->_maxx);
	fprintf(outf, "MAKENEW: win->_begy = %d\n", win->_begy);
	fprintf(outf, "MAKENEW: win->_begx = %d\n", win->_begx);
# endif
	return win;
E 13
I 13
	win->_scroll = win->_leave = 0;
E 15
I 15
	win->cury = win->curx = 0;
	win->maxy = nl;
	win->maxx = nc;

	win->begy = by;
	win->begx = bx;
	win->flags = 0;
E 15
	__swflags(win);
#ifdef DEBUG
D 15
	__TRACE("makenew: win->_clear = %d\n", win->_clear);
	__TRACE("makenew: win->_leave = %d\n", win->_leave);
	__TRACE("makenew: win->_scroll = %d\n", win->_scroll);
	__TRACE("makenew: win->_flags = %0.2o\n", win->_flags);
	__TRACE("makenew: win->_maxy = %d\n", win->_maxy);
	__TRACE("makenew: win->_maxx = %d\n", win->_maxx);
	__TRACE("makenew: win->_begy = %d\n", win->_begy);
	__TRACE("makenew: win->_begx = %d\n", win->_begx);
E 15
I 15
D 25
	__TRACE("makenew: win->flags = %0.2o\n", win->flags);
	__TRACE("makenew: win->maxy = %d\n", win->maxy);
	__TRACE("makenew: win->maxx = %d\n", win->maxx);
	__TRACE("makenew: win->begy = %d\n", win->begy);
	__TRACE("makenew: win->begx = %d\n", win->begx);
E 25
I 25
	__CTRACE("makenew: win->flags = %0.2o\n", win->flags);
	__CTRACE("makenew: win->maxy = %d\n", win->maxy);
	__CTRACE("makenew: win->maxx = %d\n", win->maxx);
	__CTRACE("makenew: win->begy = %d\n", win->begy);
	__CTRACE("makenew: win->begx = %d\n", win->begx);
E 25
E 15
#endif
	return (win);
E 13
I 7
}

D 13
_swflags_(win)
register WINDOW	*win;
E 13
I 13
D 15
void
E 15
I 15
D 22
static void
E 22
I 22
void
E 22
E 15
__swflags(win)
	register WINDOW *win;
E 13
{
D 13
	win->_flags &= ~(_ENDLINE|_FULLLINE|_FULLWIN|_SCROLLWIN);
E 13
I 13
D 15
	win->_flags &= ~(_ENDLINE | _FULLLINE | _FULLWIN | _SCROLLWIN);
E 13
	if (win->_begx + win->_maxx == COLS) {
		win->_flags |= _ENDLINE;
		if (win->_begx == 0) {
E 15
I 15
D 31
	win->flags &= 
	    ~(__ENDLINE | __FULLLINE | __FULLWIN | __SCROLLWIN | __LEAVEOK);
E 31
I 31
	win->flags &= ~(__ENDLINE | __FULLWIN | __SCROLLWIN | __LEAVEOK);
E 31
	if (win->begx + win->maxx == COLS) {
		win->flags |= __ENDLINE;
D 31
		if (win->begx == 0) {
E 15
			if (AL && DL)
D 15
				win->_flags |= _FULLLINE;
			if (win->_maxy == LINES && win->_begy == 0)
				win->_flags |= _FULLWIN;
E 15
I 15
				win->flags |= __FULLLINE;
			if (win->maxy == LINES && win->begy == 0)
				win->flags |= __FULLWIN;
E 15
		}
E 31
I 31
		if (win->begx == 0 && win->maxy == LINES && win->begy == 0)
			win->flags |= __FULLWIN;
E 31
D 15
		if (win->_begy + win->_maxy == LINES)
			win->_flags |= _SCROLLWIN;
E 15
I 15
		if (win->begy + win->maxy == LINES)
			win->flags |= __SCROLLWIN;
E 15
	}
E 7
}
E 1
