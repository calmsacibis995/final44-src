h13042
s 00003/00002/00403
d D 8.3 94/05/04 06:24:35 bostic 36 35
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00000/00001/00405
d D 8.2 94/01/09 14:40:35 bostic 35 34
c don't need termios.h any longer
e
s 00002/00002/00404
d D 8.1 93/06/11 13:37:17 bostic 34 33
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00404
d D 5.23 93/06/11 13:37:01 bostic 33 31
c Round #4; try to get ONLCR/NONL right once again
e
s 00002/00002/00404
d R 8.1 93/06/07 12:19:46 bostic 32 31
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00404
d D 5.22 93/06/07 12:19:36 bostic 31 29
c original NONL test was flipped, and was simply translated forward
e
s 00002/00002/00405
d R 8.1 93/06/04 16:47:23 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00405
d D 5.21 93/06/04 16:11:57 marc 29 28
c changed to remember and restore TSTP handler, and also to resnapshot tty state when restarting from TSTP.  Also, hardwire GT variable since we always turn tab expansion off.  We still aren't sure what pfast is for, but we haven't given up yet.
e
s 00008/00001/00399
d D 5.20 93/05/25 16:06:59 bostic 28 27
c make mvcur a real function, it's just too painful otherwise
e
s 00001/00001/00399
d D 5.19 93/05/16 15:54:35 bostic 27 26
c change __TRACE to __CTRACE, so it doesn't collide with nvi
e
s 00001/00001/00399
d D 5.18 93/05/11 15:48:29 elan 26 25
c Fixed typo -- polarity of in_refresh check in plod().
e
s 00018/00019/00382
d D 5.17 93/05/11 15:40:03 elan 25 24
c Deleted ugly (and stupid) _win stuff for notifying mvcur() that 
c we are in refresh.  Added __mvcur as a private function.  Mvcur() is now a 
c macro that calls __mvcur().
e
s 00003/00002/00398
d D 5.16 93/01/24 20:13:53 bostic 24 23
c rename origtermio to be __orig_termios
e
s 00001/00001/00399
d D 5.15 93/01/11 11:53:42 bostic 23 22
c CURSES_{OK,ERR} -> OK,ERR
e
s 00001/00001/00399
d D 5.14 92/12/30 14:54:56 elan 22 21
c Changed ERR to CURSES_ERR and OK to CURSES_OK.
e
s 00007/00002/00393
d D 5.13 92/11/05 17:03:44 elan 21 20
c Bypassed plod if on last column due to inconsistent behavior of 
c backspace on last column.
e
s 00002/00002/00393
d D 5.12 92/10/26 12:46:39 elan 20 19
c Changed to new line data structures (__LDATA and __LINE) and 
c eliminated linked list representation of window (not useful).
e
s 00003/00002/00392
d D 5.11 92/10/20 10:45:16 elan 19 18
c Changes standout character representation so that characters are 
c eight bit clean.
e
s 00001/00001/00393
d D 5.10 92/09/22 13:38:07 elan 18 17
c Fixed standout bug.
e
s 00003/00003/00391
d D 5.9 92/09/14 11:00:22 elan 17 16
c Converted to new data structures.
e
s 00003/00002/00391
d D 5.8 92/08/31 14:23:21 elan 16 15
c deleted references to NONL.
e
s 00003/00001/00390
d D 5.7 92/08/23 14:38:27 bostic 15 14
c lint
e
s 00114/00114/00277
d D 5.6 92/08/23 10:32:38 bostic 14 12
c KNF, lint
e
s 00043/00037/00354
d R 5.6 92/05/15 14:19:04 bostic 13 12
c reformat to KNF, redo tracing interface, new version for vi
e
s 00001/00011/00390
d D 5.5 90/06/01 15:37:43 bostic 12 11
c new copyright notice
e
s 00001/00001/00400
d D 5.4 89/01/23 11:35:23 bostic 11 10
c can output chars with 8th bit set; bug report 4.3BSD-tahoe/usr.lib/5
e
s 00010/00005/00391
d D 5.3 88/06/30 17:21:20 bostic 10 9
c install approved copyright notice
e
s 00010/00004/00386
d D 5.2 88/06/08 13:56:50 bostic 9 8
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00002/00380
d D 5.1 85/06/07 20:59:03 mckusick 8 7
c Add copyright
e
s 00013/00025/00369
d D 1.6 85/06/07 20:53:55 mckusick 7 6
c fixes from arnold@ucsfcgl
e
s 00024/00023/00370
d D 1.5 85/05/01 16:46:21 bloom 6 4
c new version from arnold
e
s 00024/00023/00370
d R 1.5 85/05/01 16:44:51 bloom 5 4
c _putchar moved to separate file
e
s 00003/00004/00390
d D 1.4 83/03/27 15:08:24 arnold 4 3
c 
e
s 00005/00006/00389
d D 1.3 83/02/02 15:18:16 arnold 3 2
c format fixups
e
s 00156/00076/00239
d D 1.2 82/02/17 14:12:05 arnold 2 1
c adopt latest version of fgoto() and plod() from vi
e
s 00315/00000/00000
d D 1.1 81/01/26 17:02:42 arnold 1 0
c date and time created 81/01/26 17:02:42 by arnold
e
u
U
t
T
I 8
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
D 34
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
E 34
I 34
D 36
 * Copyright (c) 1981, 1993
E 36
I 36
 * Copyright (c) 1981, 1993, 1994
E 36
 *	The Regents of the University of California.  All rights reserved.
E 34
 *
D 12
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 10
E 9
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
D 14
#endif /* not lint */
E 14
I 14
#endif	/* not lint */
E 14
E 9

E 8
I 1
D 14
# include	"curses.ext"
E 14
I 14
D 36
#include <curses.h>
E 36
I 15
#include <string.h>
I 36

#include "curses.h"
E 36
I 16
D 35
#include <termios.h>
E 35
E 16
E 15
E 14
D 2
# include	"cr_ex.h"
E 2

D 14
# define	HARDTABS	8
E 14
I 14
#define	HARDTABS	8
E 14

D 14
extern char	*tgoto();
int		plodput();

E 14
/*
D 14
 * Terminal driving and line formatting routines.
 * Basic motion optimizations are done here as well
 * as formatting of lines (printing of control characters,
E 14
I 14
 * Terminal driving and line formatting routines.  Basic motion optimizations
 * are done here as well as formatting lines (printing of control characters,
E 14
 * line numbering and the like).
D 8
 *
D 6
 * %G% (Berkeley) %W%
E 6
I 6
 * %W% (Berkeley) %G%
E 8
E 6
 */

I 28
/* Stub function for the users. */
int
mvcur(ly, lx, y, x)
	int ly, lx, y, x;
{
	return (__mvcur(ly, lx, y, x, 0));
}

E 28
I 14
D 25
static void	fgoto __P((void));
static int	plod __P((int));
E 25
I 25
static void	fgoto __P((int));
static int	plod __P((int, int));
E 25
static void	plodput __P((int));
static int	tabcol __P((int, int));

I 25
static int outcol, outline, destcol, destline;

E 25
E 14
/*
D 14
 * Sync the position of the output cursor.
 * Most work here is rounding for terminal boundaries getting the
 * column position implied by wraparound or the lack thereof and
 * rolling up the screen to get destline on the screen.
E 14
I 14
 * Sync the position of the output cursor.  Most work here is rounding for
 * terminal boundaries getting the column position implied by wraparound or
 * the lack thereof and rolling up the screen to get destline on the screen.
E 14
 */
D 28

E 28
D 2
static int	outcol, outline, destcol, destline, plodcnt;
E 2
I 2
D 14
static int	outcol, outline, destcol, destline;
E 14
I 14
D 25
static int outcol, outline, destcol, destline;
E 14
E 2

D 14
WINDOW		*_win;
E 14
I 14
WINDOW *_win;
E 14

E 25
I 15
int
E 15
D 25
mvcur(ly, lx, y, x)
D 14
int	ly, lx, y, x; {

E 14
I 14
	int ly, lx, y, x;
E 25
I 25
__mvcur(ly, lx, y, x, in_refresh)
	int ly, lx, y, x, in_refresh;
E 25
{
E 14
#ifdef DEBUG
D 14
	fprintf(outf, "MVCUR: moving cursor from (%d,%d) to (%d,%d)\n", ly, lx, y, x);
E 14
I 14
D 27
	__TRACE("mvcur: moving cursor from (%d, %d) to (%d, %d)\n",
E 27
I 27
	__CTRACE("mvcur: moving cursor from (%d, %d) to (%d, %d)\n",
E 27
	    ly, lx, y, x);
E 14
#endif
	destcol = x;
	destline = y;
	outcol = lx;
	outline = ly;
D 25
	fgoto();
E 25
I 25
	fgoto(in_refresh);
E 25
I 14
D 22
	return (OK);
E 22
I 22
D 23
	return (CURSES_OK);
E 23
I 23
	return (OK);
E 23
E 22
E 14
D 25
}

E 25
I 25
}	
        
E 25
I 14
static void
E 14
D 2
fgoto() {
E 2
I 2
D 6
char
_putchar(c)
reg char	c; {
E 2

I 2
	putchar(c);
#ifdef DEBUG
	fprintf(outf, "_PUTCHAR(%s)\n", unctrl(c));
#endif
}

E 6
D 25
fgoto()
E 25
I 25
fgoto(in_refresh)
	int in_refresh;
E 25
{
E 2
D 14
	reg char	*cgp;
	reg int		l, c;
E 14
I 14
	register int c, l;
	register char *cgp;
E 14

D 7
	if (destcol > COLS - 1) {
E 7
I 7
	if (destcol >= COLS) {
E 7
		destline += destcol / COLS;
		destcol %= COLS;
	}
D 7
	if (outcol > COLS - 1) {
E 7
I 7
	if (outcol >= COLS) {
E 7
		l = (outcol + 1) / COLS;
		outline += l;
		outcol %= COLS;
		if (AM == 0) {
			while (l > 0) {
D 2
				putchar('\n');
E 2
D 14
				if (_pfast)
E 14
I 14
				if (__pfast)
E 14
D 2
					putchar('\r');
E 2
I 2
					if (CR)
D 6
						tputs(CR, 0, _putchar);
E 6
I 6
D 14
						_puts(CR);
E 14
I 14
						tputs(CR, 0, __cputchar);
E 14
E 6
					else
D 14
						_putchar('\r');
E 14
I 14
						putchar('\r');
E 14
				if (NL)
D 6
					tputs(NL, 0, _putchar);
E 6
I 6
D 14
					_puts(NL);
E 14
I 14
					tputs(NL, 0, __cputchar);
E 14
E 6
				else
D 14
					_putchar('\n');
E 14
I 14
					putchar('\n');
E 14
E 2
				l--;
			}
			outcol = 0;
		}
		if (outline > LINES - 1) {
			destline -= outline - (LINES - 1);
			outline = LINES - 1;
		}
	}
D 7
	if (destline > LINES - 1) {
E 7
I 7
	if (destline >= LINES) {
E 7
		l = destline;
		destline = LINES - 1;
		if (outline < LINES - 1) {
			c = destcol;
D 14
			if (_pfast == 0 && !CA)
E 14
I 14
			if (__pfast == 0 && !CA)
E 14
				destcol = 0;
D 25
			fgoto();
E 25
I 25
			fgoto(in_refresh);
E 25
			destcol = c;
		}
D 7
		while (l > LINES - 1) {
E 7
I 7
		while (l >= LINES) {
E 7
D 2
			putchar('\n');
E 2
I 2
D 14
			/*
			 * The following linefeed (or simulation thereof)
			 * is supposed to scroll up the screen, since we
			 * are on the bottom line.  We make the assumption
			 * that linefeed will scroll.  If ns is in the
			 * capability list this won't work.  We should
			 * probably have an sc capability but sf will
			 * generally take the place if it works.
			 *
			 * Superbee glitch:  in the middle of the screen we
			 * have to use esc B (down) because linefeed screws up
			 * in "Efficient Paging" (what a joke) mode (which is
			 * essential in some SB's because CRLF mode puts garbage
			 * in at end of memory), but you must use linefeed to
			 * scroll since down arrow won't go past memory end.
			 * I turned this off after recieving Paul Eggert's
			 * Superbee description which wins better.
E 14
I 14
			/* The following linefeed (or simulation thereof) is
			 * supposed to scroll up the screen, since we are on
			 * the bottom line.  We make the assumption that
			 * linefeed will scroll.  If ns is in the capability
			 * list this won't work.  We should probably have an
			 * sc capability but sf will generally take the place
			 * if it works.
			 * 
			 * Superbee glitch: in the middle of the screen have
			 * to use esc B (down) because linefeed screws up in
			 * "Efficient Paging" (what a joke) mode (which is
			 * essential in some SB's because CRLF mode puts
			 * garbage in at end of memory), but you must use
			 * linefeed to scroll since down arrow won't go past
			 * memory end. I turned this off after recieving Paul
			 * Eggert's Superbee description which wins better.
E 14
			 */
D 14
			if (NL /* && !XB */ && _pfast)
D 6
				tputs(NL, 0, _putchar);
E 6
I 6
				_puts(NL);
E 14
I 14
			if (NL /* && !XB */ && __pfast)
				tputs(NL, 0, __cputchar);
E 14
E 6
			else
D 14
				_putchar('\n');
E 14
I 14
				putchar('\n');
E 14
E 2
			l--;
D 14
			if (_pfast == 0)
E 14
I 14
			if (__pfast == 0)
E 14
				outcol = 0;
		}
	}
D 2
	if (destline < outline && !(CA || UP != NULL))
E 2
I 2
	if (destline < outline && !(CA || UP))
E 2
		destline = outline;
D 2
	cgp = tgoto(CM, destcol, destline);
E 2
D 7
	if (CA)
I 2
	{
E 7
I 7
	if (CA) {
E 7
		cgp = tgoto(CM, destcol, destline);
E 2
D 21
		if (plod(strlen(cgp)) > 0)
E 21
I 21

		/*
		 * Need this condition due to inconsistent behavior
		 * of backspace on the last column.
		 */
D 25
		if (outcol != COLS - 1 && plod(strlen(cgp)) > 0)
E 21
			plod(0);
E 25
I 25
		if (outcol != COLS - 1 && plod(strlen(cgp), in_refresh) > 0)
			plod(0, in_refresh);
E 25
D 21
		else
E 21
I 21
		else 
E 21
D 14
			tputs(cgp, 0, _putchar);
I 2
	}
E 2
	else
E 14
I 14
			tputs(cgp, 0, __cputchar);
	} else
E 14
D 25
		plod(0);
E 25
I 25
		plod(0, in_refresh);
E 25
	outline = destline;
	outcol = destcol;
}
D 14

E 14
D 2
char
_putchar(c)
reg char	c; {
E 2
I 2
/*
 * Move (slowly) to destination.
 * Hard thing here is using home cursor on really deficient terminals.
 * Otherwise just use cursor motions, hacking use of tabs and overtabbing
 * and backspace.
 */
E 2

D 2
	putchar(c);
#ifdef DEBUG
	fprintf(outf, "_PUTCHAR(%s)\n", unctrl(c));
#endif
E 2
I 2
static int plodcnt, plodflg;

I 14
static void
E 14
plodput(c)
I 14
	int c;
E 14
{
	if (plodflg)
D 14
		plodcnt--;
E 14
I 14
		--plodcnt;
E 14
	else
D 14
		_putchar(c);
E 14
I 14
		putchar(c);
E 14
E 2
}

I 14
static int
E 14
D 2
extern bool	plodflg;
extern int	plodcnt;

E 2
D 25
plod(cnt)
I 14
	int cnt;
E 25
I 25
plod(cnt, in_refresh)
	int cnt, in_refresh;
E 25
E 14
D 2
int	cnt; {
E 2
I 2
{
D 14
	register int i, j, k;
	register int soutcol, soutline;
E 14
I 14
	register int i, j, k, soutcol, soutline;
E 14
E 2

D 2
	reg int		i, j, k;
	reg int		soutcol, soutline;
	reg char	c;

E 2
	plodcnt = plodflg = cnt;
	soutcol = outcol;
	soutline = outline;
I 2
	/*
D 14
	 * Consider homing and moving down/right from there, vs moving
E 14
I 14
	 * Consider homing and moving down/right from there, vs. moving
E 14
	 * directly with local motions to the right spot.
	 */
E 2
	if (HO) {
I 2
		/*
D 14
		 * i is the cost to home and tab/space to the right to
		 * get to the proper column.  This assumes ND space costs
		 * 1 char.  So i+destcol is cost of motion with home.
E 14
I 14
		 * i is the cost to home and tab/space to the right to get to
		 * the proper column.  This assumes ND space costs 1 char.  So
		 * i + destcol is cost of motion with home.
E 14
		 */
E 2
		if (GT)
			i = (destcol / HARDTABS) + (destcol % HARDTABS);
		else
			i = destcol;
D 2
        if (destcol >= outcol) {
                j = destcol / HARDTABS - outcol / HARDTABS;
                if (GT && j)
                        j += destcol % HARDTABS;
E 2
I 2
D 14
		/*
		 * j is cost to move locally without homing
		 */
E 14
I 14

		/* j is cost to move locally without homing. */
E 14
		if (destcol >= outcol) {	/* if motion is to the right */
			j = destcol / HARDTABS - outcol / HARDTABS;
			if (GT && j)
				j += destcol % HARDTABS;
			else
				j = destcol - outcol;
D 14
		}
E 2
		else
E 14
I 14
		} else
E 14
D 2
			j = destcol - outcol;
        } else
E 2
I 2
			/* leftward motion only works if we can backspace. */
E 2
			if (outcol - destcol <= i && (BS || BC))
D 2
				i = j = outcol - destcol;
E 2
I 2
D 14
				i = j = outcol - destcol; /* cheaper to backspace */
E 14
I 14
				/* Cheaper to backspace. */
				i = j = outcol - destcol;
E 14
E 2
			else
D 2
				j = i + 1;
E 2
I 2
D 14
				j = i + 1; /* impossibly expensive */
E 14
I 14
				/* Impossibly expensive. */
				j = i + 1;
E 14

D 14
		/* k is the absolute value of vertical distance */
E 14
I 14
		/* k is the absolute value of vertical distance. */
E 14
E 2
		k = outline - destline;
		if (k < 0)
			k = -k;
		j += k;
D 2
		if (i + destline < j) {
E 2
I 2

D 14
		/*
		 * Decision.  We may not have a choice if no UP.
		 */
E 14
I 14
		/* Decision.  We may not have a choice if no UP. */
E 14
		if (i + destline < j || (!UP && destline < outline)) {
			/*
			 * Cheaper to home.  Do it now and pretend it's a
			 * regular local motion.
			 */
E 2
			tputs(HO, 0, plodput);
			outcol = outline = 0;
D 2
		} else if (LL) {
E 2
I 2
D 14
		}
		else if (LL) {
E 14
I 14
		} else if (LL) {
E 14
			/*
			 * Quickly consider homing down and moving from there.
			 * Assume cost of LL is 2.
			 */
E 2
			k = (LINES - 1) - destline;
D 2
			if (i + k + 2 < j) {
E 2
I 2
D 14
			if (i + k + 2 < j && (k<=0 || UP)) {
E 14
I 14
			if (i + k + 2 < j && (k <= 0 || UP)) {
E 14
E 2
				tputs(LL, 0, plodput);
				outcol = 0;
				outline = LINES - 1;
			}
		}
D 14
	}
I 2
	else
	/*
D 4
	 * No home and no up means it's impossible, so we return an
	 * incredibly big number to make cursor motion win out.
E 4
I 4
	 * No home and no up means it's impossible.
E 4
	 */
E 14
I 14
	} else
		/* No home and no up means it's impossible. */
E 14
		if (!UP && destline < outline)
D 4
			return (500);
E 4
I 4
D 14
			return -1;
E 14
I 14
			return (-1);
E 14
E 4
E 2
	if (GT)
D 2
        i = destcol % HARDTABS + destcol / HARDTABS;
E 2
I 2
D 3
		i = destcol % HARDTABS
		    + destcol / HARDTABS;
E 3
I 3
		i = destcol % HARDTABS + destcol / HARDTABS;
E 3
E 2
	else
		i = destcol;
D 14
/*
	if (BT && outcol > destcol && (j = (((outcol+7) & ~7) - destcol - 1) >> 3)) {
E 14
I 14
#ifdef notdef
	if (BT && outcol > destcol &&
	    (j = (((outcol+7) & ~7) - destcol - 1) >> 3)) {
E 14
		j *= (k = strlen(BT));
		if ((k += (destcol&7)) > 4)
			j += 8 - (destcol&7);
		else
			j += k;
D 2
	} else
E 2
I 2
	}
	else
E 2
D 14
*/
E 14
I 14
#endif
E 14
		j = outcol - destcol;
I 14

E 14
	/*
D 14
	 * If we will later need a \n which will turn into a \r\n by
	 * the system or the terminal, then don't bother to try to \r.
E 14
I 14
	 * If we will later need a \n which will turn into a \r\n by the
	 * system or the terminal, then don't bother to try to \r.
E 14
	 */
D 14
	if ((NONL || !_pfast) && outline < destline)
E 14
I 14
D 16
	if ((NONL || !__pfast) && outline < destline)
E 16
I 16
D 24
	if ((!(origtermio.c_oflag & ONLCR) || !__pfast) && outline < destline)
E 24
I 24
D 29
	if ((!(__orig_termios.c_oflag & ONLCR) ||
E 29
I 29
D 31
	if ((!(__baset.c_oflag & ONLCR) ||
E 29
	    !__pfast) && outline < destline)
E 31
I 31
D 33
	if ((__baset.c_oflag & ONLCR || !__pfast) && outline < destline)
E 33
I 33
	if ((NONL || !__pfast) && outline < destline)
E 33
E 31
E 24
E 16
E 14
		goto dontcr;
I 14

E 14
	/*
D 14
	 * If the terminal will do a \r\n and there isn't room for it,
	 * then we can't afford a \r.
E 14
I 14
	 * If the terminal will do a \r\n and there isn't room for it, then
	 * we can't afford a \r.
E 14
	 */
	if (NC && outline >= destline)
		goto dontcr;
I 14

E 14
	/*
D 14
	 * If it will be cheaper, or if we can't back up, then send
	 * a return preliminarily.
E 14
I 14
	 * If it will be cheaper, or if we can't back up, then send a return
	 * preliminarily.
E 14
	 */
	if (j > i + 1 || outcol > destcol && !BS && !BC) {
D 2
		plodput('\r');
E 2
I 2
		/*
D 14
		 * BUG: this doesn't take the (possibly long) length
		 * of CR into account.
E 14
I 14
		 * BUG: this doesn't take the (possibly long) length of CR
		 * into account.
E 14
		 */
		if (CR)
			tputs(CR, 0, plodput);
		else
			plodput('\r');
E 2
		if (NC) {
D 2
			plodput('\n');
E 2
I 2
D 6
			if (NL)
				tputs(NL, 0, plodput);
			else
				plodput('\n');
E 6
I 6
D 7
			put_nl();
E 7
I 7
			if (NL)
				tputs(NL, 0, plodput);
			else
				plodput('\n');
E 7
E 6
E 2
			outline++;
		}
		outcol = 0;
	}
D 14
dontcr:
	while (outline < destline) {
E 14
I 14

dontcr:	while (outline < destline) {
E 14
		outline++;
D 2
		plodput('\n');
E 2
I 2
D 6
		if (NL && _pfast)
			tputs(NL, 0, plodput);
		else
			plodput('\n');
E 6
I 6
D 7
		put_nl();
E 7
I 7
		if (NL)
			tputs(NL, 0, plodput);
		else
			plodput('\n');
E 7
E 6
E 2
		if (plodcnt < 0)
			goto out;
D 14
		if (NONL || _pfast == 0)
E 14
I 14
D 16
		if (NONL || __pfast == 0)
E 16
I 16
D 24
		if (!(origtermio.c_oflag & ONLCR) || __pfast == 0)
E 24
I 24
D 29
		if (!(__orig_termios.c_oflag & ONLCR) || __pfast == 0)
E 29
I 29
D 31
		if (!(__baset.c_oflag & ONLCR) || __pfast == 0)
E 31
I 31
D 33
		if (__baset.c_oflag & ONLCR || __pfast == 0)
E 33
I 33
		if (NONL || __pfast == 0)
E 33
E 31
E 29
E 24
E 16
E 14
			outcol = 0;
	}
	if (BT)
		k = strlen(BT);
	while (outcol > destcol) {
		if (plodcnt < 0)
			goto out;
D 14
/*
E 14
I 14
#ifdef notdef
E 14
D 2
		if (BT && outcol - destcol > 4+k) {
E 2
I 2
		if (BT && outcol - destcol > k + 4) {
E 2
			tputs(BT, 0, plodput);
			outcol--;
			outcol &= ~7;
			continue;
		}
D 14
*/
E 14
I 14
#endif
E 14
		outcol--;
		if (BC)
			tputs(BC, 0, plodput);
		else
			plodput('\b');
	}
	while (outline > destline) {
		outline--;
		tputs(UP, 0, plodput);
		if (plodcnt < 0)
			goto out;
	}
	if (GT && destcol - outcol > 1) {
D 2
        for (;;) {
                i = (outcol / HARDTABS + 1) * HARDTABS;
                if (i > destcol)
                        break;
E 2
I 2
D 3
	for (;;) {
		i = tabcol(outcol, HARDTABS);
		if (i > destcol)
			break;
E 3
I 3
		for (;;) {
			i = tabcol(outcol, HARDTABS);
			if (i > destcol)
				break;
E 3
E 2
			if (TA)
				tputs(TA, 0, plodput);
			else
				plodput('\t');
			outcol = i;
		}
		if (destcol - outcol > 4 && i < COLS && (BC || BS)) {
			if (TA)
				tputs(TA, 0, plodput);
			else
				plodput('\t');
			outcol = i;
			while (outcol > destcol) {
				outcol--;
				if (BC)
					tputs(BC, 0, plodput);
				else
					plodput('\b');
			}
		}
	}
	while (outcol < destcol) {
I 2
		/*
D 14
		 * move one char to the right.  We don't use ND space
		 * because it's better to just print the char we are
		 * moving over.
E 14
I 14
		 * Move one char to the right.  We don't use ND space because
		 * it's better to just print the char we are moving over.
E 14
		 */
E 2
D 25
		if (_win != NULL)
E 25
I 25
D 26
		if (!in_refresh)
E 26
I 26
		if (in_refresh)
E 26
E 25
D 14
			if (plodflg)	/* avoid a complex calculation */
E 14
I 14
			if (plodflg)	/* Avoid a complex calculation. */
E 14
				plodcnt--;
			else {
D 2
				c = _win->_y[outline-_win->_begy][outcol-_win->_begx];
				if ((c&_STANDOUT) == (curscr->_flags&_STANDOUT))
					putchar(c);
E 2
I 2
D 4
				i = _win->_y[outline-_win->_begy][outcol-_win->_begx];
E 4
I 4
D 17
				i = curscr->_y[outline][outcol];
E 4
D 14
				if ((i&_STANDOUT) == (curscr->_flags&_STANDOUT))
D 6
					putchar(i);
E 6
I 6
D 11
					_putchar(i);
E 11
I 11
					_putchar(i & 0177);
E 14
I 14
				if ((i & _STANDOUT) ==
				    (curscr->_flags & _STANDOUT))
E 17
I 17
D 20
				i = curscr->lines[outline]->line[outcol];
D 19
				if ((i & __STANDOUT) ==
E 19
I 19
				if ((curscr->lines[outline]->standout[outcol]
E 20
I 20
				i = curscr->lines[outline]->line[outcol].ch;
				if ((curscr->lines[outline]->line[outcol].attr
E 20
				     & __STANDOUT) ==
E 19
D 18
				    (curscr->flags & __STANDOUT))
E 18
I 18
				    (curscr->flags & __WSTANDOUT))
E 18
E 17
D 19
					putchar(i & 0177);
E 19
I 19
					putchar(i);
E 19
E 14
E 11
E 6
E 2
				else
					goto nondes;
			}
		else
D 14
nondes:
		     if (ND)
			tputs(ND, 0, plodput);
		else
			plodput(' ');
E 14
I 14
nondes:			if (ND)
				tputs(ND, 0, plodput);
			else
				plodput(' ');
E 14
		outcol++;
		if (plodcnt < 0)
			goto out;
	}
D 14
out:
	if (plodflg) {
E 14
I 14

out:	if (plodflg) {
E 14
		outcol = soutcol;
		outline = soutline;
	}
D 14
	return(plodcnt);
E 14
I 14
	return (plodcnt);
E 14
}

/*
D 2
 * Move (slowly) to destination.
 * Hard thing here is using home cursor on really deficient terminals.
 * Otherwise just use cursor motions, hacking use of tabs and overtabbing
 * and backspace.
E 2
I 2
 * Return the column number that results from being in column col and
 * hitting a tab, where tabs are set every ts columns.  Work right for
 * the case where col > COLS, even if ts does not divide COLS.
E 2
 */
I 14
static int
E 14
I 2
tabcol(col, ts)
D 14
int col, ts;
E 14
I 14
	int col, ts;
E 14
{
D 15
	int offset, result;
E 15
I 15
	int offset;
E 15
E 2

D 2
static	bool	plodflg;

plodput(c)
reg char	c; {

	if (plodflg)
		plodcnt--;
	else {
		putchar(c);
#ifdef DEBUG
		fprintf(outf, "PLODPUT(%s)\n", unctrl(c));
#endif
E 2
I 2
	if (col >= COLS) {
		offset = COLS * (col / COLS);
		col -= offset;
E 2
D 14
	}
D 2
}

/*
 * Put with padding
 */
putpad(cp)
reg char	*cp; {

	fflush(stdout);
#ifdef DEBUG
	fprintf(outf, "PUTPAD: _puts(\"%s\")\n", cp);
#endif
	_puts(cp);
E 2
I 2
	else
E 14
I 14
	} else
E 14
		offset = 0;
D 14
	return col + ts - (col % ts) + offset;
E 14
I 14
	return (col + ts - (col % ts) + offset);
E 14
I 6
D 7
}

/*
 * put out a newline appropriately, twice if necessary (uck)
 */
static
put_nl()
{
	if (NL)
		tputs(NL, 0, plodput);
	else
		plodput('\n');
	if (AM && XN && outcol == COLS - 1)
		if (NL)
			tputs(NL, 0, plodput);
		else
			plodput('\n');
E 7
E 6
E 2
}
E 1
