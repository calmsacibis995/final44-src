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

/*VARARGS1*/

#ifdef VT_TERMINFO

#include <curses.h>
#include <term.h>

eprintf (instring, p1, p2, p3, p4, p5, p6, p7, p8, p9)
char *instring;
int p1, p2, p3, p4, p5, p6, p7, p8 ,p9;
{
	extern int e_putch ();

	tputs (tparm(instring, p1, p2, p3, p4, p5, p6, p7, p8, p9), SREGION, e_putch);
}

e_putch (c)
{
	putchar (c);

#ifdef DOUBLE_DELAYS
	if ((c == NOP) || (c == 0) || (c == 0200))
		putchar (c);
#endif DOUBLE_DELAYS

}

#else

eprintf (string, a1)
char   *string;
{
	char    pbuf[1024];

	sxprintf (pbuf, string, &a1);
	puts (pbuf, stdout);
}

#endif VT_TERMINFO
