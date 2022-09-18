h15600
s 00009/00006/00792
d D 8.7 94/08/13 15:40:33 bostic 66 65
c the cursor must be at the screen bottom for SF/sf
e
s 00015/00007/00783
d D 8.6 94/08/10 09:51:13 bostic 65 64
c don't leave the screen in stadnout mode
c bug fix taken from FreeBSD sources, fixes Sun console bug for nvi
e
s 00022/00015/00768
d D 8.5 94/08/10 07:50:01 bostic 64 63
c don't reenter standout mode on every character
c (test for already in standout mode was wrong)
e
s 00066/00074/00717
d D 8.4 94/08/04 08:26:26 bostic 63 62
c rework scrolling to us AL/DL if scrolling most of the screen, in
c preference to sf/sr
e
s 00180/00087/00611
d D 8.3 94/07/27 14:56:30 bostic 62 61
c add support for CS SF/sf/SR/sr combinations as scrolling commands
e
s 00003/00002/00695
d D 8.2 94/05/04 06:24:54 bostic 61 60
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00002/00002/00695
d D 8.1 93/07/20 07:24:02 bostic 60 59
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00695
d D 5.47 93/07/20 07:23:17 bostic 59 57
c Loop will loop one too many times, when wx == lch + 1
c From: christos@deshaw.com (Christos Zoulas)
e
s 00002/00002/00695
d R 8.1 93/06/04 16:49:01 bostic 58 57
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00696
d D 5.46 93/05/30 13:02:32 bostic 57 56
c no automatic aggregate initialization
e
s 00000/00002/00697
d D 5.45 93/05/30 11:51:21 bostic 56 55
c delete the emacs blank lines
e
s 00009/00001/00690
d D 5.44 93/05/17 13:11:32 elan 55 54
c Need to repoint line pointers in subwin's after quickch() rotation.
e
s 00054/00054/00637
d D 5.43 93/05/16 15:54:47 bostic 54 53
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00040/00014/00651
d D 5.42 93/05/11 15:38:57 elan 53 52
c Deleted ugly (and stupid) _win stuff for notifying mvcur() that 
c we are in refresh().
e
s 00032/00002/00633
d D 5.41 93/05/06 16:46:29 elan 52 51
c Added CE for clear to end of line.
e
s 00003/00012/00632
d D 5.40 93/05/06 16:01:04 elan 51 50
c Refresh() does not modify ISPASTEOL.
e
s 00018/00019/00626
d D 5.39 93/05/06 13:39:39 elan 50 49
c Fixed SCROLLWIN problems: don't output last character of window 
c until first character on next line is output.
e
s 00008/00006/00637
d D 5.38 93/04/27 15:07:58 elan 49 48
c Fixed unsigned -signed comparison error.
e
s 00010/00001/00633
d D 5.37 93/04/13 15:02:26 elan 48 47
c quickch() returns if there is a bottom unchanged region to prevent
e
s 00004/00001/00630
d D 5.36 93/03/02 15:07:44 elan 47 46
c Need to clear __ISPASTEOL if line is not dirty.
e
s 00002/00002/00629
d D 5.35 93/02/24 15:16:24 elan 46 45
c Cast argument to hash() to char *.
e
s 00001/00001/00630
d D 5.34 93/02/18 17:03:38 elan 45 44
c Deleted unused variable clsp.
e
s 00001/00001/00630
d D 5.33 93/02/18 16:18:42 elan 44 43
c bcopy -> memcpy.  Probably more portable.
e
s 00004/00056/00627
d D 5.32 93/02/18 15:30:57 elan 43 42
c Fixed bug in makech(): Don't need to special case XN terminals since
c we handle end-of-lines manually.  Cleaned up some #ifdef notdef's.
e
s 00010/00003/00673
d D 5.31 93/02/17 14:28:41 elan 42 41
c Added debugging info.  Made top and bot regions not dirty.
e
s 00044/00040/00632
d D 5.30 93/02/16 16:44:12 elan 41 40
c Optimized quickch() by eliminating the top and bottom regions from
c exhaustive search.  Also we don't descend into quickch() if less than a 
c quarter of the lines are dirty.  This prevents CPU intensive quickch from
c defeating the purpose of the optimization on small non-changing programs.
e
s 00007/00007/00665
d D 5.29 93/02/12 15:20:35 elan 40 39
c bcmp -> memcmp, probably more portable.
e
s 00004/00004/00668
d D 5.28 93/01/11 12:17:01 bostic 39 38
c tscroll -> __tscroll (for now)
e
s 00010/00010/00662
d D 5.27 93/01/11 11:53:57 bostic 38 37
c CURSES_{OK,ERR} -> OK,ERR
e
s 00010/00010/00662
d D 5.26 92/12/30 14:55:09 elan 37 36
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00011/00001/00661
d D 5.25 92/12/29 10:52:52 elan 36 35
c Added some debugging help.
e
s 00000/00008/00662
d D 5.24 92/12/22 15:01:45 elan 35 34
c delete __endwin (I don't understand it)
e
s 00012/00011/00658
d D 5.23 92/11/11 17:35:17 elan 34 33
c Added pointers to firstch and lastch for correct operation of 
c subwindows.
e
s 00016/00015/00653
d D 5.22 92/11/09 14:00:03 elan 33 32
c Fixed bug in scrolln() and quickch() that caused inconsistency 
c between curscr and actual screen.
e
s 00028/00008/00640
d D 5.21 92/11/05 17:01:00 elan 32 31
c Fixed bug in overlapping botoom, middle, and top region handling.
c Added debugging code.
e
s 00065/00038/00583
d D 5.20 92/10/27 17:25:02 elan 31 30
c Commented quickch() and cleaned up scrolln().
e
s 00048/00021/00573
d D 5.19 92/10/27 14:40:19 elan 30 29
c Changed touchline() to __touchline() so that user interface 
c touchline() forces repaint of line whereas __touchline() does not. 
c Fixed bug in scrolln() -- if there is no bottom range have to special case 
c so that curscr is consistent.
e
s 00083/00080/00511
d D 5.18 92/10/26 12:48:23 elan 29 28
c Changed to accomodate new line structures (__LDATA and __LINE).
c Fixed bug in screen rotation of quickch() -- scrolling regions are implemented
c rather than the whole screen being rotated.
e
s 00006/00004/00585
d D 5.17 92/10/20 16:43:01 elan 28 27
c Fixed bug in makech().
e
s 00061/00034/00528
d D 5.16 92/10/20 10:44:39 elan 27 26
c Changed standout character representation so that characters are 
c eight bit clean.
e
s 00069/00019/00493
d D 5.15 92/10/13 14:43:10 elan 26 25
c Optimized quickch() by checking for top and bottom regions of screen
c in addition to the regular block being scrolled.
e
s 00009/00003/00503
d D 5.14 92/10/13 12:32:29 elan 25 24
c Added verification of hash hit.
e
s 00005/00005/00501
d D 5.13 92/10/13 12:09:56 elan 24 23
c Fixed problem with __ISPASTOEL issue.
e
s 00031/00004/00475
d D 5.12 92/10/08 12:25:58 elan 23 22
c Fixed end-of-line problem with cursor not being on the same line 
c as the internal state.  Added #ifdef DEBUG's.
e
s 00096/00029/00383
d D 5.11 92/10/01 15:06:35 elan 22 21
c Fixed quickch() so it works now.
e
s 00105/00001/00307
d D 5.10 92/09/21 15:30:15 elan 21 20
c Added quickch() which optimizes scrolling by identifying the largest
c unchanged region in the screen and then scrolls it cleanly so that a complete
c repaint is not needed.
e
s 00082/00075/00226
d D 5.9 92/09/14 11:00:40 elan 20 19
c Converted to new data structures.
e
s 00002/00001/00299
d D 5.8 92/08/31 14:26:56 elan 19 18
c improved tracing data.
e
s 00098/00094/00202
d D 5.7 92/08/23 14:40:16 bostic 18 17
c reformat the code so you can actually read it -- no substantive change
e
s 00119/00134/00177
d D 5.6 92/08/23 12:03:29 bostic 17 15
c KNF
e
s 00081/00085/00226
d R 5.6 92/05/15 15:34:31 bostic 16 15
c reformat to KNF, redo tracing interface, new version for vi
e
s 00002/00000/00309
d D 5.5 91/03/03 18:36:26 bostic 15 14
c ANSI
e
s 00001/00011/00308
d D 5.4 90/06/01 15:40:03 bostic 14 13
c new copyright notice
e
s 00010/00005/00309
d D 5.3 88/06/30 17:22:01 bostic 13 12
c install approved copyright notice
e
s 00010/00004/00304
d D 5.2 88/06/08 13:57:41 bostic 12 11
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00002/00298
d D 5.1 85/06/07 20:58:15 mckusick 11 10
c Add copyright
e
s 00014/00002/00286
d D 1.10 85/06/07 20:53:28 mckusick 10 9
c fixes from arnold@ucsfcgl
e
s 00065/00032/00223
d D 1.9 85/05/01 17:31:44 bloom 9 8
c new version from arnold
e
s 00000/00002/00255
d D 1.8 83/05/12 13:22:07 arnold 8 7
c delete spurious debug abort()
e
s 00012/00004/00245
d D 1.7 83/05/10 15:11:40 arnold 7 6
c wrefresh(curscr) should put the cursor back where it was
e
s 00021/00014/00228
d D 1.6 83/03/27 15:08:18 arnold 6 5
c 
e
s 00004/00000/00238
d D 1.5 82/02/17 14:10:10 arnold 5 4
c don't move in standout unless MS is set
e
s 00003/00003/00235
d D 1.4 81/03/05 18:54:49 arnold 4 3
c fix bug that caused illegal scrolls
e
s 00003/00004/00235
d D 1.3 81/02/17 13:36:51 arnold 3 2
c fix bug in refresh if clear is set
e
s 00069/00039/00170
d D 1.2 81/01/27 12:28:48 arnold 2 1
c make wrefresh(curscr) make the screen look like curscr
e
s 00209/00000/00000
d D 1.1 81/01/26 17:03:10 arnold 1 0
c date and time created 81/01/26 17:03:10 by arnold
e
u
U
t
T
I 1
/*
I 11
D 12
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 12
I 12
D 60
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 60
I 60
D 61
 * Copyright (c) 1981, 1993
E 61
I 61
 * Copyright (c) 1981, 1993, 1994
E 61
 *	The Regents of the University of California.  All rights reserved.
E 60
 *
D 14
 * Redistribution and use in source and binary forms are permitted
D 13
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 13
I 13
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 13
E 12
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 12
#endif not lint
E 12
I 12
#endif /* not lint */
E 12

D 17
/*
E 11
 * make the current screen look like "win" over the area coverd by
 * win.
D 11
 *
D 9
 * %G% (Berkeley) %W%
E 9
I 9
 * %W% (Berkeley) %G%
E 11
E 9
 */
E 17
I 17
D 61
#include <curses.h>
E 61
I 18
#include <string.h>
I 61

#include "curses.h"
E 61
E 18
E 17

I 27
D 31
/* Equality of characters in terms of standout */
#define __SOEQ(a, b)	!(((a) & __STANDOUT) ^ ((b) & __STANDOUT))

E 31
E 27
D 17
# include	"curses.ext"
E 17
I 17
static int curwin;
static short ly, lx;
E 17

I 22
D 29
int doqch = 1;

E 29
E 22
D 2
# ifndef DEBUG
static short	ly, lx;
E 2
I 2
D 17
# ifdef DEBUG
# define	STATIC
E 2
# else
D 2
short		ly, lx;
E 2
I 2
# define	STATIC	static
E 2
# endif
E 17
I 17
D 53
WINDOW *_win;
E 17

E 53
I 2
D 17
STATIC short	ly, lx;
E 17
I 17
static void	domvcur __P((int, int, int, int));
static int	makech __P((WINDOW *, int));
E 17
D 21

E 21
I 21
D 62
static void	quickch __P((WINDOW *));	
E 62
I 62
static void	quickch __P((WINDOW *));
E 62
D 22
static void	scrolln __P((WINDOW*, int, int));
E 22
I 22
D 26
static void	scrolln __P((WINDOW *, int, int));
E 26
I 26
static void	scrolln __P((WINDOW *, int, int, int, int, int));
I 29

E 29
E 26
E 22
E 21
D 17
STATIC bool	curwin;

E 2
WINDOW	*_win = NULL;

I 15
STATIC int	domvcur(), makech();

E 17
I 17
/*
 * wrefresh --
 *	Make the current screen look like "win" over the area coverd by
 *	win.
 */
int
E 17
E 15
wrefresh(win)
D 17
reg WINDOW	*win;
E 17
I 17
	register WINDOW *win;
E 17
{
I 21
D 29
	register LINE *wlp;
E 29
I 29
	register __LINE *wlp;
E 29
E 21
D 17
	reg short	wy;
I 2
	reg int		retval;
I 9
	reg WINDOW	*orig;
E 17
I 17
D 18
	register WINDOW *orig;
E 18
	register int retval;
	register short wy;
E 17
E 9
E 2
D 41

E 41
I 41
	int dnum;
D 62
	
E 62
I 62

E 62
E 41
D 17
	/*
	 * make sure were in visual state
	 */
	if (_endwin) {
		_puts(VS);
		_puts(TI);
		_endwin = FALSE;
E 17
I 17
D 35
	/* Make sure were in visual state. */
	if (__endwin) {
		tputs(VS, 0, __cputchar);
		tputs(TI, 0, __cputchar);
		__endwin = 0;
E 17
	}
D 2
	if (win->_clear || curscr->_clear) {
E 2
I 2

E 35
D 17
	/*
	 * initialize loop parameters
	 */
E 17
I 17
	/* Initialize loop parameters. */
E 17
D 35

E 35
D 20
	ly = curscr->_cury;
	lx = curscr->_curx;
E 20
I 20
	ly = curscr->cury;
	lx = curscr->curx;
E 20
	wy = 0;
D 53
	_win = win;
E 53
	curwin = (win == curscr);

I 21
D 22
	for (wy = 0; wy < win->maxy; wy++) {
		wlp = win->lines[wy];
		if (wlp->flags & __ISDIRTY)
			wlp->hash = __hash(wlp->line, win->maxx);
	}
E 22
I 22
	if (!curwin)
		for (wy = 0; wy < win->maxy; wy++) {
			wlp = win->lines[wy];
			if (wlp->flags & __ISDIRTY)
D 27
				wlp->hash = __hash(wlp->line, win->maxx);
E 27
I 27
D 29
				/* need standout characteristics as well */
				wlp->hash = __hash(wlp->line, 2 * win->maxx);
E 29
I 29
D 62
				wlp->hash = 
E 62
I 62
D 65
				wlp->hash =
E 62
D 46
				   __hash(wlp->line, win->maxx * __LDATASIZE);
E 46
I 46
				   __hash((char *) wlp->line, win->maxx * __LDATASIZE);
E 65
I 65
				wlp->hash = __hash((char *)wlp->line,
				    win->maxx * __LDATASIZE);
E 65
E 46
E 29
E 27
		}

E 22
E 21
D 20
	if (win->_clear || curscr->_clear || curwin) {
E 2
		if ((win->_flags & _FULLWIN) || curscr->_clear) {
E 20
I 20
	if (win->flags & __CLEAROK || curscr->flags & __CLEAROK || curwin) {
		if ((win->flags & __FULLWIN) || curscr->flags & __CLEAROK) {
E 20
D 17
			_puts(CL);
E 17
I 17
			tputs(CL, 0, __cputchar);
E 17
D 2
			curscr->_curx = curscr->_cury = 0;
			curscr->_clear = FALSE;
			werase(curscr);
E 2
I 2
D 3
			if (!curwin) {
				curscr->_curx = curscr->_cury = 0;
				curscr->_clear = FALSE;
E 3
I 3
D 7
			ly = lx = curscr->_curx = curscr->_cury = 0;
			curscr->_clear = FALSE;
			if (!curwin)
E 7
I 7
			ly = 0;
			lx = 0;
			if (!curwin) {
D 17
				curscr->_clear = FALSE;
E 17
I 17
D 20
				curscr->_clear = 0;
E 17
				curscr->_cury = 0;
				curscr->_curx = 0;
E 20
I 20
				curscr->flags &= ~__CLEAROK;
				curscr->cury = 0;
				curscr->curx = 0;
E 20
E 7
E 3
				werase(curscr);
I 7
			}
E 7
D 3
			}
E 3
E 2
D 30
			touchwin(win);
E 30
I 30
			__touchwin(win);
E 30
		}
D 17
		win->_clear = FALSE;
E 17
I 17
D 20
		win->_clear = 0;
E 20
I 20
		win->flags &= ~__CLEAROK;
E 20
E 17
	}
	if (!CA) {
D 20
		if (win->_curx != 0)
E 20
I 20
		if (win->curx != 0)
E 20
D 9
			putchar('\n');
E 9
I 9
D 17
			_putchar('\n');
E 17
I 17
			putchar('\n');
E 17
E 9
D 2
		werase(curscr);
E 2
I 2
		if (!curwin)
			werase(curscr);
E 2
	}
D 17
# ifdef DEBUG
I 2
	fprintf(outf, "REFRESH(%0.2o): curwin = %d\n", win, curwin);
E 2
	fprintf(outf, "REFRESH:\n\tfirstch\tlastch\n");
# endif
E 17
I 17
#ifdef DEBUG
D 54
	__TRACE("wrefresh: (%0.2o): curwin = %d\n", win, curwin);
	__TRACE("wrefresh: \tfirstch\tlastch\n");
E 54
I 54
	__CTRACE("wrefresh: (%0.2o): curwin = %d\n", win, curwin);
	__CTRACE("wrefresh: \tfirstch\tlastch\n");
E 54
#endif
I 21

#ifndef NOQCH
D 22
	if (!__noqch)
E 22
I 22
D 41
	if (!__noqch && (win->flags & __FULLWIN) && !curwin)
E 22
    		quickch(win);
E 41
I 41
	if ((win->flags & __FULLWIN) && !curwin) {
		/*
		 * Invoke quickch() only if more than a quarter of the lines
		 * in the window are dirty.
		 */
		for (wy = 0, dnum = 0; wy < win->maxy; wy++)
			if (win->lines[wy]->flags & (__ISDIRTY | __FORCEPAINT))
				dnum++;
		if (!__noqch && dnum > (int) win->maxy / 4)
			quickch(win);
	}
E 41
#endif
I 53

#ifdef DEBUG
{ int i, j;
D 54
		__TRACE("#####################################\n");
E 54
I 54
		__CTRACE("#####################################\n");
E 54
		for (i = 0; i < curscr->maxy; i++) {
D 54
			__TRACE("C: %d:", i);
			__TRACE(" 0x%x \n", curscr->lines[i]->hash);
E 54
I 54
			__CTRACE("C: %d:", i);
			__CTRACE(" 0x%x \n", curscr->lines[i]->hash);
E 54
D 62
			for (j = 0; j < curscr->maxx; j++) 
D 54
				__TRACE("%c", 
E 54
I 54
				__CTRACE("%c", 
E 62
I 62
			for (j = 0; j < curscr->maxx; j++)
				__CTRACE("%c",
E 62
E 54
			           curscr->lines[i]->line[j].ch);
D 54
			__TRACE("\n");
E 54
I 54
			__CTRACE("\n");
E 54
D 62
			for (j = 0; j < curscr->maxx; j++) 
D 54
				__TRACE("%x", 
E 54
I 54
				__CTRACE("%x", 
E 62
I 62
			for (j = 0; j < curscr->maxx; j++)
				__CTRACE("%x",
E 62
E 54
			           curscr->lines[i]->line[j].attr);
D 54
			__TRACE("\n");
			__TRACE("W: %d:", i);
			__TRACE(" 0x%x \n", win->lines[i]->hash);
			__TRACE(" 0x%x ", win->lines[i]->flags);
E 54
I 54
			__CTRACE("\n");
			__CTRACE("W: %d:", i);
			__CTRACE(" 0x%x \n", win->lines[i]->hash);
			__CTRACE(" 0x%x ", win->lines[i]->flags);
E 54
D 62
			for (j = 0; j < win->maxx; j++) 
D 54
				__TRACE("%c", 
E 54
I 54
				__CTRACE("%c", 
E 62
I 62
			for (j = 0; j < win->maxx; j++)
				__CTRACE("%c",
E 62
E 54
			           win->lines[i]->line[j].ch);
D 54
			__TRACE("\n");
E 54
I 54
			__CTRACE("\n");
E 54
D 62
			for (j = 0; j < win->maxx; j++) 
D 54
				__TRACE("%x", 
E 54
I 54
				__CTRACE("%x", 
E 62
I 62
			for (j = 0; j < win->maxx; j++)
				__CTRACE("%x",
E 62
E 54
			           win->lines[i]->line[j].attr);
D 54
			__TRACE("\n");
E 54
I 54
			__CTRACE("\n");
E 54
		}
}
#endif /* DEBUG */

E 53
E 21
E 17
D 2
	ly = curscr->_cury;
	lx = curscr->_curx;
	wy = 0;
	_win = win;
E 2
D 20
	for (wy = 0; wy < win->_maxy; wy++) {
E 20
I 20
	for (wy = 0; wy < win->maxy; wy++) {
E 20
D 17
# ifdef DEBUG
D 9
		fprintf(outf, "%d\t%d\t%d\n", wy, win->_firstch[wy], win->_lastch[wy]);
E 9
I 9
		fprintf(outf, "%d\t%d\t%d\n", wy, win->_firstch[wy],
			win->_lastch[wy]);
E 9
# endif
E 17
I 17
#ifdef DEBUG
D 54
		__TRACE("%d\t%d\t%d\n",
E 54
I 54
		__CTRACE("%d\t%d\t%d\n",
E 54
D 20
		    wy, win->_firstch[wy], win->_lastch[wy]);
E 20
I 20
D 34
		    wy, win->lines[wy]->firstch, win->lines[wy]->lastch);
E 34
I 34
		    wy, *win->lines[wy]->firstchp, *win->lines[wy]->lastchp);
E 34
E 20
#endif
I 21
D 22
		curscr->lines[wy]->hash = win->lines[wy]->hash;
E 22
I 22
		if (!curwin)
			curscr->lines[wy]->hash = win->lines[wy]->hash;
E 22
E 21
E 17
D 20
		if (win->_firstch[wy] != _NOCHANGE)
E 20
I 20
D 30
		if (win->lines[wy]->flags & __ISDIRTY)
E 30
I 30
D 41
		if (win->lines[wy]->flags & __ISDIRTY ||
		    win->lines[wy]->flags & __FORCEPAINT)
E 41
I 41
D 47
		if (win->lines[wy]->flags & (__ISDIRTY | __FORCEPAINT))
E 47
I 47
		if (win->lines[wy]->flags & (__ISDIRTY | __FORCEPAINT)) {
E 47
E 41
E 30
E 20
D 37
			if (makech(win, wy) == ERR)
D 17
				return ERR;
E 17
I 17
				return (ERR);
E 37
I 37
D 38
			if (makech(win, wy) == CURSES_ERR)
				return (CURSES_ERR);
E 38
I 38
			if (makech(win, wy) == ERR)
				return (ERR);
E 38
E 37
E 17
D 9
			else
				win->_firstch[wy] = _NOCHANGE;
E 9
I 9
			else {
D 20
				if (win->_firstch[wy] >= win->_ch_off)
					win->_firstch[wy] = win->_maxx +
D 17
							    win->_ch_off;
E 17
I 17
					    win->_ch_off;
E 17
				if (win->_lastch[wy] < win->_maxx +
D 17
						       win->_ch_off)
E 17
I 17
				    win->_ch_off)
E 17
					win->_lastch[wy] = win->_ch_off;
				if (win->_lastch[wy] < win->_firstch[wy])
					win->_firstch[wy] = _NOCHANGE;
E 20
I 20
D 34
				if (win->lines[wy]->firstch >= win->ch_off)
					win->lines[wy]->firstch = win->maxx +
E 34
I 34
				if (*win->lines[wy]->firstchp >= win->ch_off)
					*win->lines[wy]->firstchp = win->maxx +
E 34
					    win->ch_off;
D 34
				if (win->lines[wy]->lastch < win->maxx +
E 34
I 34
				if (*win->lines[wy]->lastchp < win->maxx +
E 34
				    win->ch_off)
D 34
					win->lines[wy]->lastch = win->ch_off;
				if (win->lines[wy]->lastch < 
				    win->lines[wy]->firstch)
E 34
I 34
					*win->lines[wy]->lastchp = win->ch_off;
D 62
				if (*win->lines[wy]->lastchp < 
E 62
I 62
				if (*win->lines[wy]->lastchp <
E 62
D 42
				    *win->lines[wy]->firstchp)
E 42
I 42
				    *win->lines[wy]->firstchp) {
#ifdef DEBUG
D 54
					__TRACE("wrefresh: line %d notdirty \n", wy);
E 54
I 54
					__CTRACE("wrefresh: line %d notdirty \n", wy);
E 54
#endif
E 42
E 34
					win->lines[wy]->flags &= ~__ISDIRTY;
I 42
				}
E 42
E 20
			}
I 47

D 51
		} else
			win->lines[wy]->flags &= ~__ISPASTEOL;
E 51
I 51
		}
E 51
E 47
D 17
# ifdef DEBUG
		fprintf(outf, "\t%d\t%d\n", win->_firstch[wy],
			win->_lastch[wy]);
# endif
E 17
I 17
#ifdef DEBUG
D 20
		__TRACE("\t%d\t%d\n", win->_firstch[wy], win->_lastch[wy]);
E 20
I 20
D 34
		__TRACE("\t%d\t%d\n", win->lines[wy]->firstch, 
			win->lines[wy]->lastch);
E 34
I 34
D 54
		__TRACE("\t%d\t%d\n", *win->lines[wy]->firstchp, 
E 54
I 54
D 62
		__CTRACE("\t%d\t%d\n", *win->lines[wy]->firstchp, 
E 62
I 62
		__CTRACE("\t%d\t%d\n", *win->lines[wy]->firstchp,
E 62
E 54
			*win->lines[wy]->lastchp);
E 34
E 20
#endif
E 17
E 9
	}
I 9
D 20

E 20
I 20
D 62
	
E 62
I 62

E 62
I 21
#ifdef DEBUG
E 21
D 54
	__TRACE("refresh: ly=%d, lx=%d\n", ly, lx);
E 54
I 54
	__CTRACE("refresh: ly=%d, lx=%d\n", ly, lx);
E 54
I 21
#endif
I 23

E 23
E 21
E 20
E 9
D 7
	if (win->_leave) {
E 7
I 7
	if (win == curscr)
D 20
		domvcur(ly, lx, win->_cury, win->_curx);
E 20
I 20
		domvcur(ly, lx, win->cury, win->curx);
E 20
D 9
	else if (win->_leave) {
E 7
		curscr->_cury = ly;
		curscr->_curx = lx;
		ly -= win->_begy;
		lx -= win->_begx;
		if (ly >= 0 && ly < win->_maxy && lx >= 0 && lx < win->_maxx) {
			win->_cury = ly;
			win->_curx = lx;
E 9
I 9
	else {
D 20
		if (win->_leave) {
			curscr->_cury = ly;
			curscr->_curx = lx;
			ly -= win->_begy;
			lx -= win->_begx;
			if (ly >= 0 && ly < win->_maxy && lx >= 0 &&
			    lx < win->_maxx) {
				win->_cury = ly;
				win->_curx = lx;
E 20
I 20
		if (win->flags & __LEAVEOK) {
			curscr->cury = ly;
			curscr->curx = lx;
			ly -= win->begy;
			lx -= win->begx;
			if (ly >= 0 && ly < win->maxy && lx >= 0 &&
			    lx < win->maxx) {
				win->cury = ly;
				win->curx = lx;
E 20
D 17
			}
			else
E 17
I 17
			} else
E 17
D 20
				win->_cury = win->_curx = 0;
E 20
I 20
				win->cury = win->curx = 0;
E 20
E 9
D 17
		}
D 9
		else
			win->_cury = win->_curx = 0;
E 9
I 9
		else {
E 17
I 17
		} else {
E 17
D 20
			domvcur(ly, lx, win->_cury + win->_begy,
D 17
				win->_curx + win->_begx);
E 17
I 17
			    win->_curx + win->_begx);
E 17
			curscr->_cury = win->_cury + win->_begy;
			curscr->_curx = win->_curx + win->_begx;
E 20
I 20
			domvcur(ly, lx, win->cury + win->begy,
			    win->curx + win->begx);
			curscr->cury = win->cury + win->begy;
			curscr->curx = win->curx + win->begx;
E 20
		}
E 9
	}
D 9
	else {
D 6
		mvcur(ly, lx, win->_cury + win->_begy, win->_curx + win->_begx);
E 6
I 6
		domvcur(ly, lx, win->_cury+win->_begy, win->_curx+win->_begx);
E 6
		curscr->_cury = win->_cury + win->_begy;
		curscr->_curx = win->_curx + win->_begx;
	}
E 9
I 2
D 37
	retval = OK;
E 37
I 37
D 38
	retval = CURSES_OK;
E 38
I 38
	retval = OK;
E 38
E 37
D 18
ret:
E 18
I 18

E 18
E 2
D 53
	_win = NULL;
E 53
D 17
	fflush(stdout);
D 2
	return OK;
E 2
I 2
	return retval;
E 17
I 17
	(void)fflush(stdout);
	return (retval);
E 17
E 2
}

/*
D 17
 * make a change on the screen
E 17
I 17
 * makech --
 *	Make a change on the screen.
E 17
 */
D 2
# ifndef DEBUG
static
# endif
E 2
I 2
D 17
STATIC
E 17
I 17
static int
E 17
E 2
makech(win, wy)
D 17
reg WINDOW	*win;
short		wy;
E 17
I 17
	register WINDOW *win;
	int wy;
E 17
{
I 57
	static __LDATA blank = {' ', 0};
E 57
D 17
	reg char	*nsp, *csp, *ce;
	reg short	wx, lch, y;
	reg int		nlsp, clsp;	/* last space in lines		*/
E 17
I 17
D 45
	register int nlsp, clsp;		/* Last space in lines. */
E 45
I 45
D 52
	register int nlsp;		/* Last space in lines. */
E 52
I 52
D 64
	register int nlsp, clsp;		/* Last space in lines. */
E 52
E 45
D 49
	register short wx, lch, y;
E 49
I 49
	register int wx, lch, y;
E 49
D 27
	register char *nsp, *csp, *ce;
E 17

E 27
I 27
D 29
	register char *nsp, *csp, *ce, *nsop, *csop;
	char zero, soeq;
	
	zero = '\0';
E 29
I 29
D 52
	register __LDATA *nsp, *csp, *cp;
E 52
I 52
	register __LDATA *nsp, *csp, *cp, *cep;
E 64
I 64
	__LDATA *nsp, *csp, *cp, *cep;
E 64
E 52
I 30
	u_int force;
I 64
	int clsp, nlsp;			/* Last space in lines. */
	int lch, wx, y;
E 64
E 30
	char *ce;
D 57
	__LDATA blank = {' ', 0};
E 57

E 29
E 27
I 23
	/* Is the cursor still on the end of the last line? */
	if (wy > 0 && win->lines[wy - 1]->flags & __ISPASTEOL) {
D 24
			win->lines[wy - 1]->flags &= ~__ISPASTEOL;
			ly++;
			lx = 0;
	}			

E 24
I 24
D 51
		win->lines[wy - 1]->flags &= ~__ISPASTEOL;
E 51
		domvcur(ly, lx, ly + 1, 0);
		ly++;
		lx = 0;
	}
E 24
E 23
D 9
	wx = win->_firstch[wy];
E 9
I 9
D 20
	wx = win->_firstch[wy] - win->_ch_off;
	if (wx >= win->_maxx)
E 20
I 20
D 51
	if (!(win->lines[wy]->flags & __ISDIRTY))
E 20
D 17
		return OK;
E 17
I 17
D 37
		return (OK);
E 37
I 37
D 38
		return (CURSES_OK);
E 38
I 38
		return (OK);
I 49

E 51
E 49
E 38
E 37
I 20
D 34
	wx = win->lines[wy]->firstch - win->ch_off;
E 34
I 34
	wx = *win->lines[wy]->firstchp - win->ch_off;
E 34
D 49
	if (wx >= win->maxx)
D 37
		return (OK);
E 37
I 37
D 38
		return (CURSES_OK);
E 38
I 38
		return (OK);
E 38
E 37
E 20
E 17
	else if (wx < 0)
E 49
I 49
	if (wx < 0)
E 49
		wx = 0;
I 49
	else if (wx >= win->maxx)
		return (OK);
E 49
D 20
	lch = win->_lastch[wy] - win->_ch_off;
E 20
I 20
D 34
	lch = win->lines[wy]->lastch - win->ch_off;
E 34
I 34
	lch = *win->lines[wy]->lastchp - win->ch_off;
E 34
E 20
	if (lch < 0)
D 17
		return OK;
E 17
I 17
D 37
		return (OK);
E 37
I 37
D 38
		return (CURSES_OK);
E 38
I 38
		return (OK);
E 38
E 37
E 17
D 20
	else if (lch >= win->_maxx)
		lch = win->_maxx - 1;;
E 9
	y = wy + win->_begy;
E 20
I 20
D 49
	else if (lch >= win->maxx)
E 49
I 49
	else if (lch >= (int) win->maxx)
E 49
		lch = win->maxx - 1;
	y = wy + win->begy;
E 20
D 9
	lch = win->_lastch[wy];
E 9
I 9

E 9
D 2
	csp = &curscr->_y[wy + win->_begy][wx + win->_begx];
E 2
I 2
	if (curwin)
D 29
		csp = " ";
E 29
I 29
		csp = &blank;
E 29
	else
D 20
		csp = &curscr->_y[wy + win->_begy][wx + win->_begx];
E 20
I 20
		csp = &curscr->lines[wy + win->begy]->line[wx + win->begx];
E 20
I 9

E 9
E 2
D 20
	nsp = &win->_y[wy][wx];
E 20
I 20
	nsp = &win->lines[wy]->line[wx];
I 30
	force = win->lines[wy]->flags & __FORCEPAINT;
	win->lines[wy]->flags &= ~__FORCEPAINT;
E 30
E 20
D 2
	if (CE) {
E 2
I 2
	if (CE && !curwin) {
E 2
D 20
		for (ce = &win->_y[wy][win->_maxx - 1]; *ce == ' '; ce--)
			if (ce <= win->_y[wy])
E 20
I 20
D 29
		for (ce = &win->lines[wy]->line[win->maxx - 1]; 
D 27
		     *ce == ' '; ce--)
E 27
I 27
		     *ce == ' ' && !(*(ce + win->maxx) & __STANDOUT); ce--)
E 27
			if (ce <= win->lines[wy]->line)
E 29
I 29
D 62
		for (cp = &win->lines[wy]->line[win->maxx - 1]; 
E 62
I 62
		for (cp = &win->lines[wy]->line[win->maxx - 1];
E 62
		     cp->ch == ' ' && cp->attr == 0; cp--)
			if (cp <= win->lines[wy]->line)
E 29
E 20
				break;
D 20
		nlsp = ce - win->_y[wy];
E 20
I 20
D 29
		nlsp = ce - win->lines[wy]->line;
E 29
I 29
		nlsp = cp - win->lines[wy]->line;
E 29
E 20
	}
I 9
D 17

E 17
E 9
D 2
	ce = CE;
E 2
I 2
	if (!curwin)
		ce = CE;
	else
		ce = NULL;
I 9

I 30
	if (force) {
		if (CM)
			tputs(tgoto(CM, lx, ly), 0, __cputchar);
		else {
			tputs(HO, 0, __cputchar);
D 53
			mvcur(0, 0, ly, lx);
E 53
I 53
			__mvcur(0, 0, ly, lx, 1);
E 53
		}
	}
I 64

E 64
E 30
E 9
E 2
	while (wx <= lch) {
D 18
		if (*nsp != *csp) {
D 6
			mvcur(ly, lx, y, wx + win->_begx);
E 6
I 6
			domvcur(ly, lx, y, wx + win->_begx);
E 18
I 18
D 27
		if (*nsp == *csp) {
E 27
I 27
D 29
		if (*nsp == *csp && 
		    __SOEQ(*(nsp + win->maxx), *(csp + win->maxx))){
E 29
I 29
D 30
		if (bcmp(nsp, csp, sizeof(__LDATA)) == 0) {
E 30
I 30
D 40
		if (!force && bcmp(nsp, csp, sizeof(__LDATA)) == 0) {
E 40
I 40
		if (!force && memcmp(nsp, csp, sizeof(__LDATA)) == 0) {
E 40
E 30
E 29
E 27
			if (wx <= lch) {
D 27
				while (*nsp == *csp && wx <= lch) {
					nsp++;
E 27
I 27
D 29
				while (*nsp == *csp && 
				    __SOEQ(*(nsp + win->maxx), 
				    *(csp + win->maxx)) &&
				    wx <= lch) {
E 29
I 29
D 40
				while (bcmp(nsp, csp, sizeof(__LDATA)) == 0 &&
E 40
I 40
D 59
				while (memcmp(nsp, csp, sizeof(__LDATA)) == 0 &&
E 40
			            wx <= lch) {
E 59
I 59
				while (wx <= lch &&
D 64
				       memcmp(nsp, csp, sizeof(__LDATA)) == 0) {
E 59
E 29
					    nsp++;
E 27
D 29
					if (!curwin)
						csp++;
					++wx;
				}
E 29
I 29
					    if (!curwin)
						    csp++;
					    ++wx;
				    }
E 64
I 64
				    memcmp(nsp, csp, sizeof(__LDATA)) == 0) {
					nsp++;
					if (!curwin)
						++csp;
					++wx;
				}
E 64
E 29
				continue;
			}
			break;
		}
D 20
		domvcur(ly, lx, y, wx + win->_begx);
E 20
I 20
		domvcur(ly, lx, y, wx + win->begx);
I 22

E 22
E 20
E 18
E 6
D 17
# ifdef DEBUG
			fprintf(outf, "MAKECH: 1: wx = %d, lx = %d\n", wx, lx);
# endif	
E 17
I 17
#ifdef DEBUG
D 18
			__TRACE("makech: 1: wx = %d, lx = %d\n", wx, lx);
E 18
I 18
D 19
		__TRACE("makech: 1: wx = %d, lx = %d\n", wx, lx);
E 19
I 19
D 22
		__TRACE("makech: 1: wx = %d, lx = %d, newy = %d, newx = %d\n", 
D 20
		    wx, lx, y, wx + win->_begx);
E 20
I 20
		    wx, lx, y, wx + win->begx);
E 22
I 22
D 30
		__TRACE("makech: 1: wx = %d, ly= %d, lx = %d, newy = %d, newx = %d\n", 
		    wx, ly, lx, y, wx + win->begx);
E 30
I 30
D 54
		__TRACE("makech: 1: wx = %d, ly= %d, lx = %d, newy = %d, newx = %d, force =%d\n", 
E 54
I 54
D 62
		__CTRACE("makech: 1: wx = %d, ly= %d, lx = %d, newy = %d, newx = %d, force =%d\n", 
E 62
I 62
		__CTRACE("makech: 1: wx = %d, ly= %d, lx = %d, newy = %d, newx = %d, force =%d\n",
E 62
E 54
		    wx, ly, lx, y, wx + win->begx, force);
E 30
E 22
E 20
E 19
E 18
#endif
E 17
D 18
			ly = y;
			lx = wx + win->_begx;
			while (*nsp != *csp && wx <= lch) {
D 2
				if (ce && wx >= nlsp && *nsp == ' ') {
E 2
I 2
				if (ce != NULL && wx >= nlsp && *nsp == ' ') {
E 2
D 17
					/*
					 * check for clear to end-of-line
					 */
E 17
I 17
					/* Check for clear to end-of-line. */
E 17
					ce = &curscr->_y[ly][COLS - 1];
					while (*ce == ' ')
						if (ce-- <= csp)
							break;
					clsp = ce - curscr->_y[ly] - win->_begx;
E 18
I 18
		ly = y;
D 20
		lx = wx + win->_begx;
E 20
I 20
		lx = wx + win->begx;
E 20
D 27
		while (*nsp != *csp && wx <= lch) {
E 27
I 27
D 29
		nsop = nsp + win->maxx;
		if (!curwin)
			csop = csp + win->maxx;
		else
			csop = &zero;
		while ((*nsp != *csp || !__SOEQ(*nsop, *csop)) && wx <= lch) {
E 29
I 29
D 30
		while (bcmp(nsp, csp, sizeof(__LDATA)) != 0 && wx <= lch) {
E 30
I 30
D 40
		while ((force || bcmp(nsp, csp, sizeof(__LDATA)) != 0) 
E 40
I 40
D 62
		while ((force || memcmp(nsp, csp, sizeof(__LDATA)) != 0) 
E 62
I 62
		while ((force || memcmp(nsp, csp, sizeof(__LDATA)) != 0)
E 62
E 40
		    && wx <= lch) {
I 52

D 62
			if (ce != NULL && win->maxx + win->begx == 
E 62
I 62
D 65
			if (ce != NULL && win->maxx + win->begx ==
E 62
			    curscr->maxx && wx >= nlsp && nsp->ch == ' ') {
E 65
I 65
			if (ce != NULL &&
			    win->maxx + win->begx == curscr->maxx &&
			    wx >= nlsp && nsp->ch == ' ' && nsp->attr == 0) {
E 65
				/* Check for clear to end-of-line. */
				cep = &curscr->lines[wy]->line[win->maxx - 1];
				while (cep->ch == ' ' && cep->attr == 0)
					if (cep-- <= csp)
						break;
D 62
				clsp = cep - curscr->lines[wy]->line - 
E 62
I 62
				clsp = cep - curscr->lines[wy]->line -
E 62
				       win->begx * __LDATASIZE;
#ifdef DEBUG
D 54
			__TRACE("makech: clsp = %d, nlsp = %d\n", clsp, nlsp);
E 54
I 54
			__CTRACE("makech: clsp = %d, nlsp = %d\n", clsp, nlsp);
E 54
#endif
D 62
				if ((clsp - nlsp >= strlen(CE) 
E 62
I 62
				if ((clsp - nlsp >= strlen(CE)
E 62
				    && clsp < win->maxx * __LDATASIZE) ||
				    wy == win->maxy - 1) {
D 65
#ifdef DEBUG
D 54
					__TRACE("makech: using CE\n");
E 54
I 54
					__CTRACE("makech: using CE\n");
E 54
#endif
E 65
I 65
					if (curscr->flags & __WSTANDOUT) {
						tputs(SE, 0, __cputchar);
						curscr->flags &= ~__WSTANDOUT;
					}
E 65
					tputs(CE, 0, __cputchar);
					lx = wx + win->begx;
					while (wx++ <= clsp) {
						csp->ch = ' ';
						csp->attr = 0;
						csp++;
					}
					return (OK);
				}
				ce = NULL;
			}
E 52
E 30
E 29
E 27
I 22
D 43
#ifdef notdef
			/* XXX
			 * The problem with this code is that we can't count on
			 * terminals wrapping around after the 
			 * last character on the previous line has been output
			 * In effect, what then could happen is that the CE 
			 * clear the previous line and do nothing to the
			 * next line.
			 */
E 22
D 29
			if (ce != NULL && wx >= nlsp && *nsp == ' ') {
E 29
I 29
			if (ce != NULL && wx >= nlsp && 
			    nsp->ch == ' ') {
E 29
				/* Check for clear to end-of-line. */
D 20
				ce = &curscr->_y[ly][COLS - 1];
E 20
I 20
D 27
				ce = &curscr->lines[ly]->line[COLS - 1];
E 27
I 27
				ce = &curscr->lines[wy]->line[COLS - 1];
E 27
E 20
D 29
				while (*ce == ' ')
E 29
I 29
				while (ce->ch == ' ' && ce->attr = 0)
E 29
					if (ce-- <= csp)
						break;
D 20
				clsp = ce - curscr->_y[ly] - win->_begx;
E 20
I 20
D 27
				clsp = ce - curscr->lines[ly]->line - 
E 27
I 27
				clsp = ce - curscr->lines[wy]->line - 
E 27
D 29
				       win->begx;
E 29
I 29
				       win->begx * __LDATASIZE;
E 29
E 20
E 18
D 17
# ifdef DEBUG
					fprintf(outf, "MAKECH: clsp = %d, nlsp = %d\n", clsp, nlsp);
# endif
E 17
I 17
#ifdef DEBUG
D 18
				__TRACE("makech: clsp = %d, nlsp = %d\n",
				    clsp, nlsp);
E 18
I 18
			__TRACE("makech: clsp = %d, nlsp = %d\n", clsp, nlsp);
E 18
#endif
E 17
D 18
					if (clsp - nlsp >= strlen(CE)
					    && clsp < win->_maxx) {
E 18
I 18
D 29
				if (clsp - nlsp >= strlen(CE) &&
D 20
				    clsp < win->_maxx) {
E 20
I 20
				    clsp < win->maxx) {
E 29
I 29
				if (clsp - nlsp >= strlen(CE) 
				    && clsp < win->maxx * __LDATASIZE) {
E 29
E 20
E 18
D 17
# ifdef DEBUG
						fprintf(outf, "MAKECH: using CE\n");
# endif
						_puts(CE);
E 17
I 17
#ifdef DEBUG
D 18
						__TRACE("makech: using CE\n");
E 18
I 18
					__TRACE("makech: using CE\n");
E 18
#endif
D 18
						tputs(CE, 0, __cputchar);
E 17
						lx = wx + win->_begx;
						while (wx++ <= clsp)
							*csp++ = ' ';
D 9
						goto ret;
E 9
I 9
D 17
						return OK;
E 17
I 17
						return (OK);
E 17
E 9
					}
					ce = NULL;
E 18
I 18
					tputs(CE, 0, __cputchar);
D 20
					lx = wx + win->_begx;
E 20
I 20
					lx = wx + win->begx;
E 20
D 27
					while (wx++ <= clsp)
E 27
I 27
					while (wx++ <= clsp) {
E 27
D 29
						*csp++ = ' ';
I 27
						*csop++ &= ~__STANDOUT;
E 29
I 29
						csp->ch = ' ';
						csp->attr = 0;
						csp++;
E 29
					}
E 27
D 37
					return (OK);
E 37
I 37
D 38
					return (CURSES_OK);
E 38
I 38
					return (OK);
E 38
E 37
E 18
				}
D 17
				/*
				 * enter/exit standout mode as appropriate
				 */
				if (SO && (*nsp&_STANDOUT) != (curscr->_flags&_STANDOUT)) {
E 17
I 17
D 18
				/* Enter/exit standout mode as appropriate. */
				if (SO && (*nsp & _STANDOUT) !=
				    (curscr->_flags & _STANDOUT)) {
E 17
					if (*nsp & _STANDOUT) {
D 17
						_puts(SO);
E 17
I 17
						tputs(SO, 0, __cputchar);
E 17
						curscr->_flags |= _STANDOUT;
D 17
					}
					else {
						_puts(SE);
E 17
I 17
					} else {
						tputs(SE, 0, __cputchar);
E 17
						curscr->_flags &= ~_STANDOUT;
					}
E 18
I 18
				ce = NULL;
			}
I 22
#endif
E 43
E 22

D 64
			/* Enter/exit standout mode as appropriate. */
D 20
			if (SO && (*nsp & _STANDOUT) !=
			    (curscr->_flags & _STANDOUT)) {
				if (*nsp & _STANDOUT) {
E 20
I 20
D 27
			if (SO && (*nsp & __STANDOUT) !=
E 27
I 27
D 29
			if (SO && (*nsop & __STANDOUT) !=
E 29
I 29
			if (SO && (nsp->attr & __STANDOUT) !=
E 29
E 27
D 22
			    (curscr->flags & __STANDOUT)) {
E 22
I 22
			    (curscr->flags & __WSTANDOUT)) {
E 22
D 27
				if (*nsp & __STANDOUT) {
E 27
I 27
D 29
				if (*nsop & __STANDOUT) {
E 29
I 29
				if (nsp->attr & __STANDOUT) {
E 64
I 64
			/*
			 * Enter/exit standout mode as appropriate.
			 * XXX
			 * Should use UC if SO/SE not available.
			 */
			if (nsp->attr & __STANDOUT) {
				if (!(curscr->flags & __WSTANDOUT) &&
				    SO != NULL && SE != NULL) {
E 64
E 29
E 27
E 20
					tputs(SO, 0, __cputchar);
D 20
					curscr->_flags |= _STANDOUT;
E 20
I 20
					curscr->flags |= __WSTANDOUT;
E 20
D 64
				} else {
E 64
I 64
				}
			} else
				if (curscr->flags & __WSTANDOUT &&
				    SE != NULL) {
E 64
					tputs(SE, 0, __cputchar);
D 20
					curscr->_flags &= ~_STANDOUT;
E 20
I 20
					curscr->flags &= ~__WSTANDOUT;
E 20
E 18
				}
D 18
				wx++;
D 4
				if (wx >= win->_maxx && wy == win->_maxy)
E 4
I 4
				if (wx >= win->_maxx && wy == win->_maxy - 1)
E 4
D 2
						if (win->_scroll) {
						    if ((win->_flags&(_ENDLINE|_STANDOUT)) == (_ENDLINE|_STANDOUT))
							if (!MS) {
								_puts(SE);
								win->_flags &= ~_STANDOUT;
							}
						    putchar((*csp = *nsp) & 0177);
						    scroll(win);
						    if (win->_flags&_FULLWIN)
							scroll(curscr);
						    ly = win->_begy+win->_cury;
						    lx = win->_begx+win->_curx;
						    return OK;
E 2
I 2
					if (win->_scroll) {
D 6
					    if ((win->_flags&(_ENDLINE|_STANDOUT)) == (_ENDLINE|_STANDOUT))
						if (!MS) {
D 4
							_puts(SE);
							win->_flags &= ~_STANDOUT;
E 4
I 4
						    _puts(SE);
						    win->_flags &= ~_STANDOUT;
E 4
E 2
						}
E 6
I 6
D 17
					    if ((curscr->_flags&_STANDOUT) &&
					        (win->_flags & _ENDLINE))
						    if (!MS) {
							_puts(SE);
							curscr->_flags &= ~_STANDOUT;
						    }
E 6
D 2
						else if (win->_flags&_SCROLLWIN) {
						    lx = --wx;
						    return ERR;
						}
				putchar((*csp++ = *nsp) & 0177);
E 2
I 2
					    if (!curwin)
D 9
						putchar((*csp = *nsp) & 0177);
E 9
I 9
						_putchar((*csp = *nsp) & 0177);
E 9
					    else
D 9
						putchar(*nsp & 0177);
					    scroll(win);
E 9
I 9
						_putchar(*nsp & 0177);
E 9
					    if (win->_flags&_FULLWIN && !curwin)
						scroll(curscr);
					    ly = win->_begy+win->_cury;
					    lx = win->_begx+win->_curx;
					    return OK;
					}
					else if (win->_flags&_SCROLLWIN) {
					    lx = --wx;
					    return ERR;
					}
E 17
I 17
						if (curscr->_flags & _STANDOUT
						    && win->_flags & _ENDLINE)
							if (!MS) {
								tputs(SE, 0,
								    __cputchar);
								curscr->_flags &= ~_STANDOUT;
							}
						if (!curwin)
							putchar((*csp = *nsp) & 0177);
						else
							putchar(*nsp & 0177);
						if (win->_flags & _FULLWIN && !curwin)
							scroll(curscr);
						ly = win->_begy + win->_cury;
						lx = win->_begx + win->_curx;
						return (OK);
					} else
						if (win->_flags & _SCROLLWIN) {
							lx = --wx;
							return (ERR);
E 18
I 18
D 64
			}
E 64

			wx++;
D 20
			if (wx >= win->_maxx && wy == win->_maxy - 1)
				if (win->_scroll) {
					if (curscr->_flags & _STANDOUT
					    && win->_flags & _ENDLINE)
E 20
I 20
D 23
			if (wx >= win->maxx && wy == win->maxy - 1)
E 23
I 23
			if (wx >= win->maxx && wy == win->maxy - 1 && !curwin)
E 23
				if (win->flags & __SCROLLOK) {
					if (curscr->flags & __WSTANDOUT
					    && win->flags & __ENDLINE)
E 20
						if (!MS) {
							tputs(SE, 0,
							    __cputchar);
D 20
							curscr->_flags &=
							    ~_STANDOUT;
E 20
I 20
							curscr->flags &=
							    ~__WSTANDOUT;
E 20
E 18
						}
E 17
D 18
				if (!curwin)
D 9
					putchar((*csp++ = *nsp) & 0177);
E 9
I 9
D 17
					_putchar((*csp++ = *nsp) & 0177);
E 17
I 17
					putchar((*csp++ = *nsp) & 0177);
E 17
E 9
				else
D 9
					putchar(*nsp & 0177);
E 9
I 9
D 17
					_putchar(*nsp & 0177);
# ifdef FULLDEBUG
				fprintf(outf,
					"MAKECH:putchar(%c)\n", *nsp & 0177);
# endif
E 17
I 17
					putchar(*nsp & 0177);
E 18
I 18
D 27
					if (!curwin)
						putchar((*csp = *nsp) & 0177);
					else
						putchar(*nsp & 0177);
E 27
I 27
D 50
					if (!curwin) {
D 29
						*csop = *nsop;
						putchar(*csp = *nsp);
E 29
I 29
						csp->attr = nsp->attr;
						putchar(csp->ch = nsp->ch);
E 29
					} else
D 29
						putchar(*nsp);
E 27
D 20
					if (win->_flags & _FULLWIN && !curwin)
E 20
I 20
D 22
					if (win->flags & __FULLWIN && !curwin)
E 22
I 22
D 28
#ifdef notdef
E 28
I 28
#ifdef notdef /* why is this here? */
E 29
I 29
						putchar(nsp->ch);
D 43
#ifdef notdef /* XXX why is this here? */
E 29
E 28
D 23
					if (win->flags & __FULLWIN && !curwin){
E 23
I 23
					if (win->flags & __FULLWIN && !curwin)
E 23
E 22
E 20
						scroll(curscr);
D 20
					ly = win->_begy + win->_cury;
					lx = win->_begx + win->_curx;
E 20
I 20
D 22
					ly = win->begy + wy;
					lx = win->begx + wx;
E 22
I 22
#endif
E 43
I 43

E 50
I 50
					if (!(win->flags & __SCROLLWIN)) {
						if (!curwin) {
							csp->attr = nsp->attr;
							putchar(csp->ch = nsp->ch);
						} else
							putchar(nsp->ch);
					}
E 50
E 43
I 27
D 28
					domvcur(ly, wx + win->begx, 
						win->begy + win->maxy - 1,
						win->begx + win->maxx - 1);
E 28
I 28
					if (wx + win->begx < curscr->maxx) {
D 62
						domvcur(ly, wx + win->begx, 
E 62
I 62
						domvcur(ly, wx + win->begx,
E 62
						    win->begy + win->maxy - 1,
						    win->begx + win->maxx - 1);
					}
E 28
E 27
					ly = win->begy + win->maxy - 1;
					lx = win->begx + win->maxx - 1;
E 22
E 20
D 37
					return (OK);
E 37
I 37
D 38
					return (CURSES_OK);
E 38
I 38
					return (OK);
E 38
E 37
D 50
				} else
D 20
					if (win->_flags & _SCROLLWIN) {
E 20
I 20
					if (win->flags & __SCROLLWIN) {
E 20
						lx = --wx;
D 37
						return (ERR);
E 37
I 37
D 38
						return (CURSES_ERR);
E 38
I 38
						return (ERR);
E 38
E 37
					}
D 27
			if (!curwin)
				putchar((*csp++ = *nsp) & 0177);
			else
				putchar(*nsp & 0177);
E 27
I 27
			if (!curwin) {
D 29
				*csop++ = *nsop;
				putchar(*csp++ = *nsp);
			} else
				putchar(*nsp);
E 29
I 29
				csp->attr = nsp->attr;
				putchar(csp->ch = nsp->ch);
				csp++;
		       	} else
				putchar(nsp->ch);
E 29
E 27
I 23
			
E 50
I 50
D 62
				} 
			if (wx < win->maxx || wy < win->maxy - 1 || 
E 62
I 62
				}
			if (wx < win->maxx || wy < win->maxy - 1 ||
E 62
			    !(win->flags & __SCROLLWIN)) {
				if (!curwin) {
					csp->attr = nsp->attr;
					putchar(csp->ch = nsp->ch);
					csp++;
D 62
				} else 
E 62
I 62
				} else
E 62
					putchar(nsp->ch);
			}
E 50
E 23
E 18
#ifdef DEBUG
D 18
				__TRACE("makech: putchar(%c)\n", *nsp & 0177);
E 18
I 18
D 29
			__TRACE("makech: putchar(%c)\n", *nsp & 0177);
E 29
I 29
D 54
			__TRACE("makech: putchar(%c)\n", nsp->ch & 0177);
E 54
I 54
			__CTRACE("makech: putchar(%c)\n", nsp->ch & 0177);
E 54
E 29
E 18
#endif
E 17
E 9
E 2
D 18
				if (UC && (*nsp & _STANDOUT)) {
D 9
					putchar('\b');
E 9
I 9
D 17
					_putchar('\b');
E 9
					_puts(UC);
E 17
I 17
					putchar('\b');
					tputs(UC, 0, __cputchar);
E 17
				}
				nsp++;
E 18
I 18
D 20
			if (UC && (*nsp & _STANDOUT)) {
E 20
I 20
D 27
			if (UC && (*nsp & __STANDOUT)) {
E 27
I 27
D 29
			if (UC && (*nsop & __STANDOUT)) {
E 29
I 29
			if (UC && (nsp->attr & __STANDOUT)) {
E 29
E 27
E 20
				putchar('\b');
				tputs(UC, 0, __cputchar);
E 18
			}
I 18
			nsp++;
I 27
D 29
			nsop++;
E 29
E 27
D 50
		}
E 50
E 18
I 5
D 6
			if (!MS && (*nsp & _STANDOUT)  && (*csp & _STANDOUT)) {
				_puts(SE);
				win->_flags &= ~_STANDOUT;
			}
E 6
E 5
D 17
# ifdef DEBUG
			fprintf(outf, "MAKECH: 2: wx = %d, lx = %d\n", wx, lx);
# endif	
			if (lx == wx + win->_begx)	/* if no change */
E 17
I 17
#ifdef DEBUG
D 18
			__TRACE("makech: 2: wx = %d, lx = %d\n", wx, lx);
E 18
I 18
D 54
		__TRACE("makech: 2: wx = %d, lx = %d\n", wx, lx);
E 54
I 54
		__CTRACE("makech: 2: wx = %d, lx = %d\n", wx, lx);
E 54
E 18
#endif
I 50
		}
E 50
D 18
			if (lx == wx + win->_begx)	/* If no change. */
E 17
				break;
			lx = wx + win->_begx;
I 10
			if (lx >= COLS && AM) {
				lx = 0;
				ly++;
				/*
				 * xn glitch: chomps a newline after auto-wrap.
				 * we just feed it now and forget about it.
				 */
				if (XN) {
D 17
					_putchar('\n');
					_putchar('\r');
E 17
I 17
					putchar('\n');
					putchar('\r');
E 17
				}
			}
E 10
D 17
		}
D 10
		else if (wx < lch)
D 9
			while (*nsp == *csp) {
E 9
I 9
			while (*nsp == *csp && wx < lch) {
E 10
I 10
		else if (wx <= lch)
E 17
I 17
		} else if (wx <= lch)
E 17
			while (*nsp == *csp && wx <= lch) {
E 10
E 9
D 2
				nsp++, csp++;
E 2
I 2
				nsp++;
				if (!curwin)
					csp++;
E 2
				++wx;
			}
		else
E 18
I 18
D 20
		if (lx == wx + win->_begx)	/* If no change. */
E 20
I 20
		if (lx == wx + win->begx)	/* If no change. */
E 20
E 18
			break;
I 18
D 20
		lx = wx + win->_begx;
E 20
I 20
		lx = wx + win->begx;
E 20
D 51
		if (lx >= COLS && AM) {
D 23
			lx = 0;
			ly++;
E 23
D 43
			/*
			 * xn glitch: chomps a newline after auto-wrap.
			 * we just feed it now and forget about it.
			 */
			if (XN) {
I 23
				lx = 0;
				ly++;
E 23
				putchar('\n');
				putchar('\r');
I 23
			} else {
				if (wy != LINES)
					win->lines[wy]->flags |= __ISPASTEOL;
				lx = COLS - 1;
E 23
			}
E 43
I 43
			if (wy != LINES)
				win->lines[wy]->flags |= __ISPASTEOL;
E 51
I 51
		if (lx >= COLS && AM)
E 51
			lx = COLS - 1;
E 43
I 27
D 51
		} else if (wx >= win->maxx) {
			if (wy != win->maxy)
				win->lines[wy]->flags |= __ISPASTEOL;
E 51
I 51
		else if (wx >= win->maxx) {
E 51
			domvcur(ly, lx, ly, win->maxx + win->begx - 1);
			lx = win->maxx + win->begx - 1;
E 27
		}
I 27

E 27
E 18
D 17
# ifdef DEBUG
		fprintf(outf, "MAKECH: 3: wx = %d, lx = %d\n", wx, lx);
# endif	
E 17
I 17
#ifdef DEBUG
D 54
		__TRACE("makech: 3: wx = %d, lx = %d\n", wx, lx);
E 54
I 54
		__CTRACE("makech: 3: wx = %d, lx = %d\n", wx, lx);
E 54
#endif
I 65
	}

	/* Don't leave the screen in standout mode. */
	if (curscr->flags & __WSTANDOUT) {
		tputs(SE, 0, __cputchar);
		curscr->flags &= ~__WSTANDOUT;
E 65
E 17
	}
D 9
ret:
E 9
D 6
	if ((win->_flags & _STANDOUT) && !MS) {
E 6
I 6
D 17
	return OK;
E 17
I 17
D 37
	return (OK);
E 37
I 37
D 38
	return (CURSES_OK);
E 38
I 38
	return (OK);
E 38
E 37
E 17
}

/*
D 17
 * perform a mvcur, leaving standout mode if necessary
E 17
I 17
 * domvcur --
 *	Do a mvcur, leaving standout mode if necessary.
E 17
 */
D 9
static
E 9
I 9
D 17
STATIC
E 17
I 17
static void
E 17
E 9
domvcur(oy, ox, ny, nx)
D 17
int	oy, ox, ny, nx; {

E 17
I 17
	int oy, ox, ny, nx;
{
E 17
I 7
D 8
	if (ny == 0 && nx == 0)
		abort();
E 8
E 7
D 20
	if (curscr->_flags & _STANDOUT && !MS) {
E 20
I 20
	if (curscr->flags & __WSTANDOUT && !MS) {
E 20
E 6
D 17
		_puts(SE);
E 17
I 17
		tputs(SE, 0, __cputchar);
E 17
D 6
		win->_flags &= ~_STANDOUT;
E 6
I 6
D 20
		curscr->_flags &= ~_STANDOUT;
E 20
I 20
		curscr->flags &= ~__WSTANDOUT;
E 20
E 6
	}
I 22
D 27
#ifdef DEBUG
	__TRACE("domvcur: oy=%d, ox=%d, ny=%d, nx=%d\n", oy, ox, ny, nx);
#endif	
E 27
I 27

E 27
E 22
D 6
	return OK;
E 6
I 6
D 53
	mvcur(oy, ox, ny, nx);
E 53
I 53
	__mvcur(oy, ox, ny, nx, 1);
E 53
I 21
}

D 27

E 27
/*
 * Quickch() attempts to detect a pattern in the change of the window
D 25
 * inorder to optimize the change, e.g., scroll n lines as opposed to 
E 25
I 25
D 62
 * in order to optimize the change, e.g., scroll n lines as opposed to 
E 62
I 62
 * in order to optimize the change, e.g., scroll n lines as opposed to
E 62
E 25
 * repainting the screen line by line.
 */
I 34

E 34
D 48

E 48
static void
quickch(win)
	WINDOW *win;
{
D 22
#define THRESH		win->maxy / 2
E 22
I 22
D 41
#define THRESH		win->maxy / 4
E 41
I 41
#define THRESH		(int) win->maxy / 4
E 41
E 22

D 22
	register LINE *wlp, *clp;
	register int bsize, curs, curw, starts, startw, i;
E 22
I 22
D 29
	register LINE *clp, *tmp1, *tmp2;
E 29
I 29
	register __LINE *clp, *tmp1, *tmp2;
E 29
	register int bsize, curs, curw, starts, startw, i, j;
D 26
	int n, target, remember;
E 26
I 26
D 29
	int n, target, remember, bot, top;
E 26
	char buf[1024];
E 29
I 29
D 31
	int n, target, remember, bot, top, sc_region;
E 31
I 31
	int n, target, cur_period, bot, top, sc_region;
E 31
	__LDATA buf[1024];
E 29
	u_int blank_hash;
E 22

I 41
D 62
	/* 
E 62
I 62
	/*
E 62
	 * Find how many lines from the top of the screen are unchanged.
	 */
D 42
	for (top = 0; top < win->maxy; top++)
E 42
I 42
D 62
	for (top = 0; top < win->maxy; top++) 
E 62
I 62
	for (top = 0; top < win->maxy; top++)
E 62
E 42
		if (win->lines[top]->flags & __FORCEPAINT ||
D 62
		    win->lines[top]->hash != curscr->lines[top]->hash 
		    || memcmp(win->lines[top]->line, 
		    curscr->lines[top]->line, 
E 62
I 62
		    win->lines[top]->hash != curscr->lines[top]->hash
		    || memcmp(win->lines[top]->line,
		    curscr->lines[top]->line,
E 62
		    win->maxx * __LDATASIZE) != 0)
			break;
D 42
	
E 42
I 42
		else
			win->lines[top]->flags &= ~__ISDIRTY;
E 42
       /*
D 62
	* Find how many lines from bottom of screen are unchanged. 
E 62
I 62
	* Find how many lines from bottom of screen are unchanged.
E 62
	*/
	for (bot = win->maxy - 1; bot >= 0; bot--)
		if (win->lines[bot]->flags & __FORCEPAINT ||
D 62
		    win->lines[bot]->hash != curscr->lines[bot]->hash 
		    || memcmp(win->lines[bot]->line, 
		    curscr->lines[bot]->line, 
E 62
I 62
		    win->lines[bot]->hash != curscr->lines[bot]->hash
		    || memcmp(win->lines[bot]->line,
		    curscr->lines[bot]->line,
E 62
		    win->maxx * __LDATASIZE) != 0)
			break;
I 42
		else
			win->lines[bot]->flags &= ~__ISDIRTY;
I 48

D 49

E 49
I 49
#ifdef NO_JERKINESS
E 49
	/*
	 * If we have a bottom unchanged region return.  Scrolling the
	 * bottom region up and then back down causes a screen jitter.
	 * This will increase the number of characters sent to the screen
	 * but it looks better.
	 */
	if (bot < win->maxy - 1)
		return;
I 49
#endif /* NO_JERKINESS */
E 49
E 48
E 42

E 41
I 25
	/*
	 * Search for the largest block of text not changed.
I 31
	 * Invariants of the loop:
	 * - Startw is the index of the beginning of the examined block in win.
D 62
         * - Starts is the index of the beginning of the examined block in 
E 62
I 62
         * - Starts is the index of the beginning of the examined block in
E 62
	 *    curscr.
	 * - Curs is the index of one past the end of the exmined block in win.
D 62
	 * - Curw is the index of one past the end of the exmined block in 
E 62
I 62
	 * - Curw is the index of one past the end of the exmined block in
E 62
	 *   curscr.
	 * - bsize is the current size of the examined block.
E 31
         */
E 25
D 41
	for (bsize = win->maxy; bsize >= THRESH; bsize--)
		for (startw = 0; startw <= win->maxy - bsize; startw++)
			for (starts = 0; starts <= win->maxy - bsize; 
E 41
I 41
	for (bsize = bot - top; bsize >= THRESH; bsize--) {
		for (startw = top; startw <= bot - bsize; startw++)
D 62
			for (starts = top; starts <= bot - bsize; 
E 62
I 62
			for (starts = top; starts <= bot - bsize;
E 62
E 41
			     starts++) {
				for (curw = startw, curs = starts;
				     curs < starts + bsize; curw++, curs++)
D 30
					if (win->lines[curw]->hash !=
E 30
I 30
					if (win->lines[curw]->flags &
					    __FORCEPAINT ||
					    (win->lines[curw]->hash !=
E 30
D 25
					    curscr->lines[curs]->hash)
E 25
I 25
					    curscr->lines[curs]->hash ||
D 29
				            bcmp(&win->lines[curw], 
D 26
					    &win->lines[curs], win->maxx != 0))
E 26
I 26
					    &curscr->lines[curs], 
D 27
					    win->maxx != 0))
E 27
I 27
					    2 * win->maxx) != 0)
E 29
I 29
D 40
				            bcmp(win->lines[curw]->line, 
E 40
I 40
D 62
				            memcmp(win->lines[curw]->line, 
E 40
					    curscr->lines[curs]->line, 
E 62
I 62
				            memcmp(win->lines[curw]->line,
					    curscr->lines[curs]->line,
E 62
D 30
					    win->maxx * __LDATASIZE) != 0)
E 30
I 30
					    win->maxx * __LDATASIZE) != 0))
E 30
E 29
E 27
E 26
E 25
						break;
				if (curs == starts + bsize)
					goto done;
			}
I 41
	}
E 41
 done:
D 30
	/* Did not find anything or block is in correct place already. */
	if (bsize < THRESH || starts == startw)	
E 30
I 30
	/* Did not find anything */
D 62
	if (bsize < THRESH)	
E 62
I 62
	if (bsize < THRESH)
E 62
E 30
		return;

I 26
D 41
	/* 
	 * Find how many lines from the top of the screen are unchanged.
	 */
	if (starts != 0) {
		for (top = 0; top < win->maxy; top++)
D 30
			if (win->lines[top]->hash != curscr->lines[top]->hash 
E 30
I 30
			if (win->lines[top]->flags & __FORCEPAINT ||
			    win->lines[top]->hash != curscr->lines[top]->hash 
E 30
D 29
			    || bcmp(&win->lines[top], &curscr->lines[top], 
D 27
				 win->maxx) != 0)
E 27
I 27
				 2 * win->maxx) != 0)
E 29
I 29
D 40
			    || bcmp(win->lines[top]->line, 
E 40
I 40
			    || memcmp(win->lines[top]->line, 
E 40
			    curscr->lines[top]->line, 
			    win->maxx * __LDATASIZE) != 0)
E 29
E 27
				break;
	} else
		top = 0;
	
       /*
	* Find how many lines from bottom of screen are unchanged. 
	*/
	if (curs != win->maxy) {
		for (bot = win->maxy - 1; bot >= 0; bot--)
D 30
			if (win->lines[bot]->hash != curscr->lines[bot]->hash 
E 30
I 30
			if (win->lines[bot]->flags & __FORCEPAINT ||
			    win->lines[bot]->hash != curscr->lines[bot]->hash 
E 30
D 29
			    || bcmp(&win->lines[bot], &curscr->lines[bot], 
D 27
				 win->maxx) != 0)
E 27
I 27
				 2 * win->maxx) != 0)
E 29
I 29
D 40
			    || bcmp(win->lines[bot]->line, 
E 40
I 40
			    || memcmp(win->lines[bot]->line, 
E 40
			    curscr->lines[bot]->line, 
			    win->maxx * __LDATASIZE) != 0)
E 29
E 27
				break;
	} else
		bot = win->maxy - 1;
E 41
D 36

E 36
E 26
#ifdef DEBUG
D 26
	__TRACE("quickch:bsize=%d,starts=%d,startw=%d,curw=%d,curs=%d\n", 
		bsize, starts, startw, curw, curs);
E 26
I 26
D 54
	__TRACE("quickch:bsize=%d,starts=%d,startw=%d,curw=%d,curs=%d,top=%d,bot=%d\n", 
E 54
I 54
D 62
	__CTRACE("quickch:bsize=%d,starts=%d,startw=%d,curw=%d,curs=%d,top=%d,bot=%d\n", 
E 62
I 62
	__CTRACE("quickch:bsize=%d,starts=%d,startw=%d,curw=%d,curs=%d,top=%d,bot=%d\n",
E 62
E 54
		bsize, starts, startw, curw, curs, top, bot);
E 26
#endif
D 26
	scrolln(win, starts, startw);
E 26
D 22
	
	/* Mark the block as clean and retain consistency. */
	for (i = startw; i < startw + bsize; i++) {
		wlp = win->lines[i];
		clp = curscr->lines[i];
		wlp->flags &= ~(__ISDIRTY | __ISPASTEOL);
		bcopy(wlp->line, clp->line, win->maxx);
		clp->hash = wlp->hash;
	}
E 22

I 26
D 62
	/* 
	 * Make sure that there is no overlap between the bottom and top 
E 62
I 62
	/*
	 * Make sure that there is no overlap between the bottom and top
E 62
	 * regions and the middle scrolled block.
	 */
D 32
	if (bot < curw)
		bot = curw - 1;
	if (top > startw)
		top = startw;
E 32
I 32
	if (bot < curs)
		bot = curs - 1;
	if (top > starts)
		top = starts;
E 32

D 30
	scrolln(win, starts, startw, curs, top, bot);

E 30
E 26
I 22
	n = startw - starts;

I 32
#ifdef DEBUG
D 54
		__TRACE("#####################################\n");
E 54
I 54
		__CTRACE("#####################################\n");
E 54
		for (i = 0; i < curscr->maxy; i++) {
D 54
			__TRACE("C: %d:", i);
I 36
			__TRACE(" 0x%x \n", curscr->lines[i]->hash);
E 54
I 54
			__CTRACE("C: %d:", i);
			__CTRACE(" 0x%x \n", curscr->lines[i]->hash);
E 54
E 36
D 62
			for (j = 0; j < curscr->maxx; j++) 
D 54
				__TRACE("%c", 
E 54
I 54
				__CTRACE("%c", 
E 62
I 62
			for (j = 0; j < curscr->maxx; j++)
				__CTRACE("%c",
E 62
E 54
			           curscr->lines[i]->line[j].ch);
D 54
			__TRACE("\n");
E 54
I 54
			__CTRACE("\n");
E 54
I 36
D 62
			for (j = 0; j < curscr->maxx; j++) 
D 54
				__TRACE("%x", 
E 54
I 54
				__CTRACE("%x", 
E 62
I 62
			for (j = 0; j < curscr->maxx; j++)
				__CTRACE("%x",
E 62
E 54
			           curscr->lines[i]->line[j].attr);
D 54
			__TRACE("\n");
E 36
			__TRACE("W: %d:", i);
I 36
			__TRACE(" 0x%x \n", win->lines[i]->hash);
			__TRACE(" 0x%x ", win->lines[i]->flags);
E 54
I 54
			__CTRACE("\n");
			__CTRACE("W: %d:", i);
			__CTRACE(" 0x%x \n", win->lines[i]->hash);
			__CTRACE(" 0x%x ", win->lines[i]->flags);
E 54
E 36
D 62
			for (j = 0; j < win->maxx; j++) 
D 54
				__TRACE("%c", 
E 54
I 54
				__CTRACE("%c", 
E 62
I 62
			for (j = 0; j < win->maxx; j++)
				__CTRACE("%c",
E 62
E 54
			           win->lines[i]->line[j].ch);
I 36
D 54
			__TRACE("\n");
E 54
I 54
			__CTRACE("\n");
E 54
D 62
			for (j = 0; j < win->maxx; j++) 
D 54
				__TRACE("%x", 
E 54
I 54
				__CTRACE("%x", 
E 62
I 62
			for (j = 0; j < win->maxx; j++)
				__CTRACE("%x",
E 62
E 54
			           win->lines[i]->line[j].attr);
E 36
D 54
			__TRACE("\n");
E 54
I 54
			__CTRACE("\n");
E 54
		}
D 62
#endif 
E 32
I 30
D 53
	if (n != 0)
D 31
		scrolln(win, starts, startw, curs, top, bot);
E 31
I 31
D 33
		scrolln(win, starts, startw, curs, curw, top);
E 33
I 33
		scrolln(win, starts, startw, curs, bot, top);
E 53
E 33
E 31
D 41


E 41
I 41
	
E 62
I 62
#endif

E 62
E 41
E 30
	/* So we don't have to call __hash() each time */
D 29
	(void)memset(buf, ' ', win->maxx);
D 27
	blank_hash = __hash(buf, win->maxx);
E 27
I 27
	(void)memset(buf + win->maxx, '\0', win->maxx);
	blank_hash = __hash(buf, 2 * win->maxx);
E 29
I 29
	for (i = 0; i < win->maxx; i++) {
		buf[i].ch = ' ';
		buf[i].attr = 0;
	}
D 46
	blank_hash = __hash(buf, win->maxx * __LDATASIZE);
E 46
I 46
	blank_hash = __hash((char *) buf, win->maxx * __LDATASIZE);
E 46
E 29
E 27

	/*
	 * Perform the rotation to maintain the consistency of curscr.
I 31
D 32
	 * This is hairy!
E 32
I 32
	 * This is hairy since we are doing an *in place* rotation.
E 32
	 * Invariants of the loop:
	 * - I is the index of the current line.
	 * - Target is the index of the target of line i.
	 * - Tmp1 points to current line (i).
	 * - Tmp2 and points to target line (target);
D 62
	 * - Cur_period is the index of the end of the current period. 
E 62
I 62
	 * - Cur_period is the index of the end of the current period.
E 62
	 *   (see below).
	 *
	 * There are 2 major issues here that make this rotation non-trivial:
	 * 1.  Scrolling in a scrolling region bounded by the top
	 *     and bottom regions determined (whose size is sc_region).
D 62
	 * 2.  As a result of the use of the mod function, there may be a 
E 62
I 62
	 * 2.  As a result of the use of the mod function, there may be a
E 62
	 *     period introduced, i.e., 2 maps to 4, 4 to 6, n-2 to 0, and
	 *     0 to 2, which then causes all odd lines not to be rotated.
D 62
	 *     To remedy this, an index of the end ( = beginning) of the 
	 *     current 'period' is kept, cur_period, and when it is reached, 
	 *     the next period is started from cur_period + 1 which is 
E 62
I 62
	 *     To remedy this, an index of the end ( = beginning) of the
	 *     current 'period' is kept, cur_period, and when it is reached,
	 *     the next period is started from cur_period + 1 which is
E 62
	 *     guaranteed not to have been reached since that would mean that
	 *     all records would have been reached. (think about it...).
D 62
	 * 
E 62
I 62
	 *
E 62
	 * Lines in the rotation can have 3 attributes which are marked on the
	 * line so that curscr is consistent with the visual screen.
D 33
	 * 1.  Not dirty -- lines inside the scrolling region, top region or
E 33
I 33
	 * 1.  Not dirty -- lines inside the scrolled block, top region or
E 33
	 *                  bottom region.
D 33
	 * 2.  Blank lines -- lines in the differential of scrolled block 
	 *                    between win and curscr in the scrolling region.
	 *
E 33
I 33
D 62
	 * 2.  Blank lines -- lines in the differential of the scrolling 
	 *		      region adjacent to top and bot regions 
E 62
I 62
	 * 2.  Blank lines -- lines in the differential of the scrolling
	 *		      region adjacent to top and bot regions
E 62
	 *                    depending on scrolling direction.
E 33
	 * 3.  Dirty line -- all other lines are marked dirty.
E 31
	 */
D 29
	i = 0;
	tmp1 = curscr->lines[0];
	remember = 0;
	for (j = 0; j < win->maxy; j++) {
		target = (i + n + win->maxy) % win->maxy;
E 29
I 29
	sc_region = bot - top + 1;
	i = top;
	tmp1 = curscr->lines[top];
D 31
	remember = top;
E 31
I 31
	cur_period = top;
E 31
	for (j = top; j <= bot; j++) {
		target = (i - top + n + sc_region) % sc_region + top;
E 29
		tmp2 = curscr->lines[target];
		curscr->lines[target] = tmp1;
		/* Mark block as clean and blank out scrolled lines. */
		clp = curscr->lines[target];
I 23
#ifdef DEBUG
E 23
D 54
		__TRACE("quickch: n=%d startw=%d curw=%d i = %d target=%d ",
E 54
I 54
		__CTRACE("quickch: n=%d startw=%d curw=%d i = %d target=%d ",
E 54
			n, startw, curw, i, target);
I 23
#endif
E 23
D 26
		if (target >= startw && target < curw) {
E 26
I 26
D 32
		if (target >= startw && target < curw || target < top || 
		    target > bot) {
E 32
I 32
D 62
		if ((target >= startw && target < curw) || target < top 
E 62
I 62
		if ((target >= startw && target < curw) || target < top
E 62
		    || target > bot) {
E 32
E 26
I 23
#ifdef DEBUG
E 23
D 54
			__TRACE("-- notdirty");
E 54
I 54
			__CTRACE("-- notdirty");
E 54
I 23
#endif
E 23
			win->lines[target]->flags &= ~__ISDIRTY;
D 29
		} else if ((n < 0 && target >= win->maxy + n) || 
			 (n > 0 && target < n)) {
D 25
			if (clp->hash != blank_hash) {
E 25
I 25
			if (clp->hash != blank_hash || 
D 27
			    bcmp(clp->line, buf, win->maxx) != 0) {
E 25
				(void)memset(clp->line, ' ', win->maxx);
E 27
I 27
			    bcmp(clp->line, buf, 2 * win->maxx) != 0) {
				(void)bcopy(clp->line, buf, 2 * win->maxx);
E 29
I 29
D 33
		} else if ((n < 0 && target >= curw && target < curs) ||
		           (n > 0 && target < startw && target >= starts)) {
E 33
I 33
		} else if ((n > 0 && target >= top && target < top + n) ||
		           (n < 0 && target <= bot && target > bot + n)) {
E 33
D 40
			if (clp->hash != blank_hash ||  bcmp(clp->line, 
E 40
I 40
D 62
			if (clp->hash != blank_hash ||  memcmp(clp->line, 
E 62
I 62
			if (clp->hash != blank_hash ||  memcmp(clp->line,
E 62
E 40
			    buf, win->maxx * __LDATASIZE) !=0) {
D 44
				(void)bcopy(buf, clp->line,  
E 44
I 44
				(void)memcpy(clp->line,  buf,
E 44
				    win->maxx * __LDATASIZE);
E 29
E 27
I 23
#ifdef DEBUG
E 23
D 27
				__TRACE("-- memset");
E 27
I 27
D 29
				__TRACE("-- bcopy ");
E 29
I 29
D 54
				__TRACE("-- blanked out: dirty");
E 54
I 54
				__CTRACE("-- blanked out: dirty");
E 54
E 29
E 27
I 23
#endif
E 23
				clp->hash = blank_hash;
I 31
				__touchline(win, target, 0, win->maxx - 1, 0);
E 31
D 33
			} else 
E 33
I 33
			} else {
E 33
I 31
				__touchline(win, target, 0, win->maxx - 1, 0);
E 31
I 23
#ifdef DEBUG
E 23
D 27
				__TRACE(" -- nonmemset");
E 27
I 27
D 29
				__TRACE(" -- no bcopy");
E 29
I 29
D 54
				__TRACE(" -- blank line already: dirty");
E 54
I 54
				__CTRACE(" -- blank line already: dirty");
E 54
E 29
E 27
I 23
#endif
I 33
			}
E 33
E 23
D 30
			touchline(win, target, 0, win->maxx - 1);
E 30
I 30
D 31
			__touchline(win, target, 0, win->maxx - 1, 0);
E 31
E 30
		} else {
I 23
#ifdef DEBUG
E 23
D 29
			__TRACE(" -- just dirty");
E 29
I 29
D 54
			__TRACE(" -- dirty");
E 54
I 54
			__CTRACE(" -- dirty");
E 54
E 29
I 23
#endif
E 23
D 30
			touchline(win, target, 0, win->maxx - 1);
E 30
I 30
			__touchline(win, target, 0, win->maxx - 1, 0);
E 30
		}
I 23
#ifdef DEBUG
E 23
D 54
		__TRACE("\n");
E 54
I 54
		__CTRACE("\n");
E 54
I 23
#endif
E 23
D 31
		if (target == remember) {
E 31
I 31
		if (target == cur_period) {
E 31
			i = target + 1;
			tmp1 = curscr->lines[i];
D 31
			remember = i;
E 31
I 31
			cur_period = i;
E 31
		} else {
			tmp1 = tmp2;
			i = target;
		}
	}
I 23
#ifdef DEBUG
E 23
D 29
	__TRACE("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	for (i = 0; i < curscr->maxy; i++)
		__TRACE("Q: %d: %.70s\n", i,
	           curscr->lines[i]->line);
E 29
I 29
D 54
		__TRACE("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
E 54
I 54
		__CTRACE("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
E 54
		for (i = 0; i < curscr->maxy; i++) {
D 32
			__TRACE("Q: %d:", i);
E 32
I 32
D 54
			__TRACE("C: %d:", i);
E 54
I 54
			__CTRACE("C: %d:", i);
E 54
E 32
D 62
			for (j = 0; j < curscr->maxx; j++) 
D 54
				__TRACE("%c", 
E 54
I 54
				__CTRACE("%c", 
E 62
I 62
			for (j = 0; j < curscr->maxx; j++)
				__CTRACE("%c",
E 62
E 54
			           curscr->lines[i]->line[j].ch);
I 32
D 54
			__TRACE("\n");
			__TRACE("W: %d:", i);
E 54
I 54
			__CTRACE("\n");
			__CTRACE("W: %d:", i);
E 54
D 62
			for (j = 0; j < win->maxx; j++) 
D 54
				__TRACE("%c", 
E 54
I 54
				__CTRACE("%c", 
E 54
			           win->lines[i]->line[j].ch);
E 62
I 62
			for (j = 0; j < win->maxx; j++)
				__CTRACE("%c", win->lines[i]->line[j].ch);
E 62
E 32
D 54
			__TRACE("\n");
E 54
I 54
			__CTRACE("\n");
E 54
		}
E 29
I 23
#endif
I 53
D 55
	if (n != 0)
E 55
I 55
	if (n != 0) {
		WINDOW *wp;
E 55
		scrolln(win, starts, startw, curs, bot, top);
I 55
		/*
		 * Need to repoint any subwindow lines to the rotated
D 62
		 * line structured. 
E 62
I 62
		 * line structured.
E 62
		 */
		for (wp = win->nextp; wp != win; wp = wp->nextp)
			__set_subwin(win, wp);
	}
E 55
E 53
E 23
E 22
}

I 31
/*
D 62
 * Scrolln performs the scroll by n lines, where n is starts - startw.
E 62
I 62
 * scrolln --
 *	Scroll n lines, where n is starts - startw.
D 63
 *
 * XXX
 * The initial tests that set __noqch don't let us reach here unless we
 * have either CS + HO + SF/sf/SR/sr, or AL + DL.  SF/sf/SR/sr scrolling
 * can only scroll the entire screen, not just a part of it, which means
 * that the quickch() routine is going to be sadly disappointed in us.
 * I've left the code here, as it would be useful to be able to scroll
 * part of the screen and repaint the rest, instead painting the entire
 * screen, on a terminal that didn't have CS or AL/DL.
E 63
E 62
 */
E 31
static void
D 26
scrolln(win, starts, startw)
E 26
I 26
D 31
scrolln(win, starts, startw, curs, top, bot)
E 31
I 31
D 33
scrolln(win, starts, startw, curs, curw, top)
E 33
I 33
scrolln(win, starts, startw, curs, bot, top)
E 33
E 31
E 26
	WINDOW *win;
D 26
	int starts, startw;
E 26
I 26
D 31
	int starts, startw, curs, top, bot;
E 31
I 31
D 33
	int starts, startw, curs, curw, top;
E 33
I 33
	int starts, startw, curs, bot, top;
E 33
E 31
E 26
{
	int i, oy, ox, n;

	oy = curscr->cury;
	ox = curscr->curx;
	n = starts - startw;

I 63
	/*
	 * XXX
	 * The initial tests that set __noqch don't let us reach here unless
	 * we have either CS + HO + SF/sf/SR/sr, or AL + DL.  SF/sf and SR/sr
	 * scrolling can only shift the entire scrolling region, not just a
	 * part of it, which means that the quickch() routine is going to be
	 * sadly disappointed in us if we don't have CS as well.
	 *
	 * If CS, HO and SF/sf are set, can use the scrolling region.  Because
	 * the cursor position after CS is undefined, we need HO which gives us
	 * the ability to move to somewhere without knowledge of the current
	 * location of the cursor.  Still call __mvcur() anyway, to update its
	 * idea of where the cursor is.
	 *
	 * When the scrolling region has been set, the cursor has to be at the
	 * last line of the region to make the scroll happen.
	 *
	 * Doing SF/SR or AL/DL appears faster on the screen than either sf/sr
	 * or al/dl, and, some terminals have AL/DL, sf/sr, and CS, but not
	 * SF/SR.  So, if we're scrolling almost all of the screen, try and use
	 * AL/DL, otherwise use the scrolling region.  The "almost all" is a
	 * shameless hack for vi.
	 */
E 63
	if (n > 0) {
I 62
D 63
		/* If scrolling the entire screen, SF/sf is all we need. */
		if (top == 0 &&
		    bot == win->maxy && (SF != NULL || sf != NULL)) {
			__mvcur(oy, ox, win->maxy, 0, 1);
			if (SF != NULL)
				tputs(__tscroll(SF, n, 0), 0, __cputchar);
			else
				for (i = 0; i < n; i++)
					tputs(sf, 0, __cputchar);
			__mvcur(win->maxy, 0, oy, ox, 1);
			return;
		}

		/*
		 * If CS, HO and SF/sf are set, use the scrolling region.  We
		 * need HO because the cursor position after CS is undefined,
		 * so we need the ability to move to a fixed place without any
		 * knowledge of the current location.  Note, we call __mvcur()
		 * anyway, to update its idea of where the cursor is.
		 *
		 * When the scrolling region has been set, the cursor has to be
		 * at the last line of that region to make the scroll happen.
		 */
		if (CS != NULL && HO != NULL && (SF != NULL || sf != NULL)) {
E 63
I 63
		if (CS != NULL && HO != NULL && (SF != NULL ||
		    (AL == NULL || DL == NULL ||
		    top > 3 || bot + 3 < win->maxy) && sf != NULL)) {
E 63
			tputs(__tscroll(CS, top, bot + 1), 0, __cputchar);
			__mvcur(oy, ox, 0, 0, 1);
			tputs(HO, 0, __cputchar);
			__mvcur(0, 0, bot, 0, 1);
			if (SF != NULL)
				tputs(__tscroll(SF, n, 0), 0, __cputchar);
			else
				for (i = 0; i < n; i++)
					tputs(sf, 0, __cputchar);
			tputs(__tscroll(CS, 0, win->maxy), 0, __cputchar);
			__mvcur(bot, 0, 0, 0, 1);
			tputs(HO, 0, __cputchar);
			__mvcur(0, 0, oy, ox, 1);
			return;
		}

D 63
		/*
		 * Otherwise, we depend on having AL/al and DL/dl.
		 *
		 * Scroll up the block.
		 */
E 63
I 63
		/* Scroll up the block. */
E 63
E 62
D 22
		mvcur(oy, ox, startw, 0);
E 22
I 22
D 26
		mvcur(oy, ox, 0, 0);
E 26
I 26
D 53
		mvcur(oy, ox, top, 0);
E 53
I 53
D 66
		__mvcur(oy, ox, top, 0, 1);
E 53
D 62
		/* Scroll up the block */
E 62
E 26
E 22
D 63
		if (DL)
E 63
I 63
		if (SF != NULL && top == 0)
E 66
I 66
		if (SF != NULL && top == 0) {
			__mvcur(oy, ox, bot, 0, 1);
E 66
			tputs(__tscroll(SF, n, 0), 0, __cputchar);
D 66
		else if (DL != NULL)
E 66
I 66
		} else if (DL != NULL) {
			__mvcur(oy, ox, top, 0, 1);
E 66
E 63
D 39
			tputs(tscroll(DL, n), 0, __cputchar);
E 39
I 39
D 62
			tputs(__tscroll(DL, n), 0, __cputchar);
E 62
I 62
			tputs(__tscroll(DL, n, 0), 0, __cputchar);
E 62
E 39
D 63
		else
E 63
I 63
D 66
		else if (dl != NULL)
E 66
I 66
		} else if (dl != NULL) {
			__mvcur(oy, ox, top, 0, 1);
E 66
E 63
D 62
			for(i = 0; i < n; i++)
E 62
I 62
			for (i = 0; i < n; i++)
E 62
				tputs(dl, 0, __cputchar);
I 63
D 66
		else if (sf != NULL && top == 0)
E 66
I 66
		} else if (sf != NULL && top == 0) {
			__mvcur(oy, ox, bot, 0, 1);
E 66
			for (i = 0; i < n; i++)
				tputs(sf, 0, __cputchar);
D 66
		else
E 66
I 66
		} else
E 66
			abort();
E 63
I 31

E 31
D 22
		mvcur(startw, 0, oy, ox);
E 22
I 22
D 26
		mvcur(0, 0, oy, ox);
E 26
I 26
D 30
		/* Push back down the bottom region */
		if (bot < win->maxy - 1) {
			mvcur(top, 0, bot - n + 1, 0);
E 30
I 30
D 62
		/* 
D 31
		 * Push back down the bottom region.
E 31
I 31
		 * Push down the bottom region.
E 31
		 */
E 62
I 62
		/* Push down the bottom region. */
E 62
D 31
		if (bot <= win->maxy - 1) {
			if (bot == win->maxy - 1)
				mvcur(top, 0, bot - n, 0);
			else
				mvcur(top, 0, bot - n + 1, 0);
E 30
			if (AL)
				tputs(tscroll(AL, n), 0, __cputchar);
			else
				for(i = 0; i < n; i++)
					tputs(al, 0, __cputchar);
D 30
			mvcur(bot - n + 1, 0, oy, ox);
E 30
I 30
			if (bot == win->maxy - 1)
				mvcur(bot - n, 0, oy, ox);
			else
				mvcur(bot - n + 1, 0, oy, ox);
E 30
		} else
			mvcur(top, 0, oy, ox);
E 31
I 31
D 33
		mvcur(top, 0, curw, 0);
E 33
I 33
D 53
		mvcur(top, 0, bot - n + 1, 0);
E 53
I 53
		__mvcur(top, 0, bot - n + 1, 0, 1);
E 53
E 33
D 41
		if (AL)
E 41
I 41
D 62
		if (AL) 
E 41
D 39
			tputs(tscroll(AL, n), 0, __cputchar);
E 39
I 39
			tputs(__tscroll(AL, n), 0, __cputchar);
E 62
I 62
D 63
		if (AL)
E 63
I 63
		if (AL != NULL)
E 63
			tputs(__tscroll(AL, n, 0), 0, __cputchar);
E 62
E 39
D 63
		else
E 63
I 63
		else if (al != NULL)
E 63
D 62
			for(i = 0; i < n; i++)
E 62
I 62
			for (i = 0; i < n; i++)
E 62
				tputs(al, 0, __cputchar);
I 63
		else
			abort();
E 63
D 33
		mvcur(curw, 0, oy, ox);
E 33
I 33
D 53
		mvcur(bot - n + 1, 0, oy, ox);
E 53
I 53
		__mvcur(bot - n + 1, 0, oy, ox, 1);
E 53
E 33
E 31
E 26
E 22
	} else {
D 26
		/* Delete the bottom lines */
		mvcur(oy, 0, win->maxy + n, 0);		/* n < 0 */
		if (DL)
			tputs(tscroll(DL, -n), 0, __cputchar);
		else
			for(i = n; i < 0; i++)
				tputs(dl, 0, __cputchar);
		mvcur(win->maxy + n, 0, starts,  0);
E 26
I 26
D 30
		/* Preserve the bottom lines. (Pull them up) */
E 30
I 30
D 62
		/* Preserve the bottom lines */
E 62
I 62
D 63
		/* If scrolling the entire screen, SR/sr is all we need. */
		if (top == 0 &&
		    bot == win->maxy && (SR != NULL || sr != NULL)) {
			__mvcur(oy, ox, 0, 0, 1);

			n = -n;
			if (SR != NULL)
				tputs(__tscroll(SR, n, 0), 0, __cputchar);
			else
				for (i = 0; i < n; i++)
					tputs(sr, 0, __cputchar);
			__mvcur(0, 0, oy, ox, 1);
			return;
		}

E 63
		/*
D 63
		 * If CS, HO and SR/sr are set, use the scrolling region.  See
		 * the above comment for details.
E 63
I 63
		 * !!!
		 * n < 0
		 *
		 * If CS, HO and SR/sr are set, can use the scrolling region.
		 * See the above comments for details.
E 63
		 */
D 63
		if (CS != NULL && HO != NULL && (SR != NULL || sr != NULL)) {
E 63
I 63
		if (CS != NULL && HO != NULL && (SR != NULL ||
		    (AL == NULL || DL == NULL ||
		    top > 3 || bot + 3 < win->maxy) && sr != NULL)) {
E 63
			tputs(__tscroll(CS, top, bot + 1), 0, __cputchar);
			__mvcur(oy, ox, 0, 0, 1);
			tputs(HO, 0, __cputchar);
			__mvcur(0, 0, top, 0, 1);

D 63
			n = -n;
E 63
			if (SR != NULL)
D 63
				tputs(__tscroll(SR, n, 0), 0, __cputchar);
E 63
I 63
				tputs(__tscroll(SR, -n, 0), 0, __cputchar);
E 63
			else
D 63
				for (i = 0; i < n; i++)
E 63
I 63
				for (i = n; i < 0; i++)
E 63
					tputs(sr, 0, __cputchar);
			tputs(__tscroll(CS, 0, win->maxy), 0, __cputchar);
			__mvcur(top, 0, 0, 0, 1);
			tputs(HO, 0, __cputchar);
			__mvcur(0, 0, oy, ox, 1);
			return;
		}

D 63
		/*
		 * Otherwise, we depend on having AL/al and DL/dl.
		 *
		 * Preserve the bottom lines.
		 */
E 62
E 30
D 31
		if (bot < win->maxy - 1) {
			mvcur(oy, ox, curs, 0);
			if (DL)
				tputs(tscroll(DL, -n), 0, __cputchar);
			else
			       	for(i = n; i < 0; i++)
					tputs(dl, 0, __cputchar);
			mvcur(curs, 0, starts, 0);
		} else
			mvcur(oy, ox, starts,  0);
E 31
I 31
D 33
		mvcur(oy, ox, curs, 0);
E 33
I 33
D 53
		mvcur(oy, ox, bot + n + 1, 0);	/* n < 0 */
E 53
I 53
		__mvcur(oy, ox, bot + n + 1, 0, 1);	/* n < 0 */
E 53
E 33
		if (DL)
E 63
I 63
		/* Preserve the bottom lines. */
		__mvcur(oy, ox, bot + n + 1, 0, 1);
		if (SR != NULL && bot == win->maxy)
			tputs(__tscroll(SR, -n, 0), 0, __cputchar);
		else if (DL != NULL)
E 63
D 39
			tputs(tscroll(DL, -n), 0, __cputchar);
E 39
I 39
D 62
			tputs(__tscroll(DL, -n), 0, __cputchar);
E 62
I 62
			tputs(__tscroll(DL, -n, 0), 0, __cputchar);
E 62
E 39
D 63
		else
E 63
I 63
		else if (dl != NULL)
E 63
D 62
		       	for(i = n; i < 0; i++)
E 62
I 62
		       	for (i = n; i < 0; i++)
E 62
				tputs(dl, 0, __cputchar);
D 33
		mvcur(curs, 0, starts, 0);
E 33
I 33
D 53
		mvcur(bot + n + 1, 0, top, 0);
E 53
I 53
D 63
		__mvcur(bot + n + 1, 0, top, 0, 1);
E 63
I 63
		else if (sr != NULL && bot == win->maxy)
		       	for (i = n; i < 0; i++)
				tputs(sr, 0, __cputchar);
		else
			abort();
E 63
E 53
E 33
E 31
E 26

D 62
		/* Scroll the block down */
D 41
		if (AL)
E 41
I 41
		if (AL) 
E 41
D 39
			tputs(tscroll(AL, -n), 0, __cputchar);
E 39
I 39
			tputs(__tscroll(AL, -n), 0, __cputchar);
E 62
I 62
		/* Scroll the block down. */
D 63
		if (AL)
E 63
I 63
		__mvcur(bot + n + 1, 0, top, 0, 1);
		if (AL != NULL)
E 63
			tputs(__tscroll(AL, -n, 0), 0, __cputchar);
E 62
E 39
D 63
		else
E 63
I 63
		else if (al != NULL)
E 63
D 62
			for(i = n; i < 0; i++)
E 62
I 62
			for (i = n; i < 0; i++)
E 62
				tputs(al, 0, __cputchar);
I 63
		else
			abort();
E 63
D 33
		mvcur(starts, 0, oy, ox);
E 33
I 33
D 53
		mvcur(top, 0, oy, ox);
E 53
I 53
		__mvcur(top, 0, oy, ox, 1);
E 53
E 33
D 22
	}
E 22
I 22
D 62
	}		
E 62
I 62
	}
E 62
E 22
E 21
E 6
}
I 22
D 56


E 56
E 22
E 1
