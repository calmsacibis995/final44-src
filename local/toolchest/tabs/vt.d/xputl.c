/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include "vt.h"

/* put a "logical line" of characters on the screen at the current position */

/* NOTE:  This is not very clean, but seems necessary to handle all of the
 * various strange possibilities for displaying characters.  We must
 * process a line at a time in order to handle things like
 * underscoring, by which multiple characters map to a single
 * display position.  The general principals here are:  that there
 * two ways of calling it, one with a C string to be printed, and
 * one with a buffer string to be printed.  C strings end in nulls,
 * and cause a special character to be mapped to embedded newlines. 
 * Buffer strings end in newlines, and map normally.  Underscoring
 * is inidicated by the presence of the meta (0200) bit on
 * characters in the display map, so that mapping is done here.  To
 * do this, a whole line is buffered for cput.  Underscoring will
 * work fine so long as the underscores are done one at a time, or
 * the underscores don't wrap lines.  Control and meta characters
 * map to their special emacs equivalents.
 */

xputl (cp, attribute)
register char  *cp;			/* string pointer */
int attribute;
{
	CHAR    cbuf[256];		/* line buffer */
	register CHAR  i;
	register int   b;
	int     mb;
	int     last;
	CHAR    a;

	mb = b = mcol;			/* buffer pointer */

	while (1)
	{
		if (b > mb)
			mb = b;
		if (b > SCRWID)
		{

/* Line has wrapped.  Put a ! on the end, and wrap anything that is left
 * over to the next line
 */
			if(WRAPON)
			{
				i = cbuf[SCRWID];
				a = cbuf[SCRWID + 1];

/* i is the character overwritten by the !, a is the character */
/* overwritten by the EOM in cflush */

				if (mline >= SCRNLIN - 1)
				{

/* Wrap from last line on screen, fold back up and don't write in */
/* the last position! */
					cflush (cbuf, SCRWID);
					mline--;	/* don't run overboard */
				}
				else
				{
					cbuf[SCRWID] = attribute + '!';
					cflush (cbuf, SCRWID + 1);
					mline++;
				}
				mcol = 0;
				b = 0;
				cbuf[b++] = i;
				last = SCRWID + 2;
				if (SCRWID + 1 < mb)
					cbuf[b++] = a;
			} else {
				if (mline >= SCRNLIN - 1)
				{

					cflush (cbuf, SCRWID);
					mline--;
				}
				else
				{
					cflush (cbuf, SCRWID + 1);
					mline++;
				}

				mcol = 0;
				b = 0;
				last = SCRWID + 2;
			}
			while (last < mb)
			{
				cbuf[b++] = cbuf[last++];
			}
			mb = b;		/* RESET */
		}

	/* Process Next character */
#ifdef DO_META_CHARS
		i =  attribute + ((*cp++) & 0177);	/* next char */
#else
		i =  attribute + ((*cp++) & 0377);
#endif
		if ((i & VT_CHAR) == 0)
		{
			cflush (cbuf, mb);
			return;		/* done */
		}
		if ((i & VT_CHAR) == VTNEWLINE)
		{			/* embedded newline */
			cflush (cbuf, b);
			/* clrl();		/* NOT Sure CDB */
			mb = b = 0;
			if (mline < SCRNLIN)
				mline++;/* don't overflow */
			mcol = 0;
			continue;	/* re-loop */
		}
#ifdef DO_META_CHARS
		if (i & META)
		{
			cbuf[b++] = attribute | 'M';
			cbuf[b++] = attribute | '-';
			if (b > mb)
				mb = b;
			i &= ~(META);
		}
#endif

reswitch: 
		switch (ptype[i & VT_CHAR])
		{
			case UL: 
			case PLAIN: 
				cbuf[b++] = i;
				break;

			case BACKSP: 
			/* explicit backspace mode ? */
			/*  Fall through to handle backspace in normal mode */

			case CONTRL: 
				cbuf[b++] = attribute + '^';
				i ^= 0100;
				goto reswitch;
			/* Handle things like ^_ correctly! */
			case TAB: 
				last = TABSTOP -
					((b - (LNOMOD * LNOWID)) % TABSTOP);
				while (last--)
				{
					cbuf[b++] = attribute + ' ';
				}
				break;
		}
	}
}
