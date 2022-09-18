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
#ifdef VT_TERMINFO
#include <curses.h>
#include <term.h>
#endif VT_TERMINFO

static unsigned int Latest_Odd_Mode;

#undef LONGPROB

#ifdef u3b
#define LONGPROB	1
#endif

#ifdef u3b5
#define LONGPROB	1
#endif

#ifdef u3b2
#define LONGPROB	1
#endif

#ifdef LONGPROB

vputch (xch)
register xch;
{
	register CHAR ch;
	register short int attribute;
	register char c;

	ch = xch;

#else

vputch (ch)
register CHAR ch;
{
	register short int attribute;
	register char c;

#endif

	attribute = ch & VT_VIDEO;
	c = ch & VT_CHAR;

	if (attribute & VT_INVISIBLE)
	{
		if (c)
			c = ' ';
		attribute &= ~(VT_INVISIBLE);
	}
	if (attribute != Latest_Odd_Mode)
	{
		Latest_Odd_Mode = attribute;
#ifdef VT_TERMINFO
		vidattr (attribute);
#endif VT_TERMINFO
	}
	if (c)
		putchar (c);
}
