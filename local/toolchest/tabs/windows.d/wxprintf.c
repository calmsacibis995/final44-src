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
#include "windows.h"

/*
 *	wxprintf (Winner, sp, ap1, ap2, ap3, ap4, ap5, ap6, ap7)
 *
 *	This procedure is a window based printf.  sp is the format string.
 *
 */

void
wxprintf (Winner, sp, ap1, ap2, ap3, ap4, ap5, ap6, ap7)
register struct window *Winner;
register char  *sp;
char   *ap1;
char   *ap2;
char   *ap3;
char   *ap4;
char   *ap5;
char   *ap6;
char   *ap7;
{
	waxprintf (Winner, 0, sp, ap1, ap2, ap3, ap4, ap5, ap6, ap7);
}

waxprintf (Winner, attributes, sp, ap1, ap2, ap3, ap4, ap5, ap6, ap7)
register struct window *Winner;
int attributes;
register char  *sp;
char   *ap1;
char   *ap2;
char   *ap3;
char   *ap4;
char   *ap5;
char   *ap6;
char   *ap7;
{
	char    sbuf[256];		/* buffer */

	W_Ok (Winner, "wxprintf");	/* Die on Illegal Window */

	C_window = Winner;

	sprintf (sbuf, sp, ap1, ap2, ap3, ap4, ap5, ap6, ap7);

#ifdef DO_META_CHARS

	sp = sbuf;
	while (*sp)
	{
		if (*sp == '\n')
			*sp = VTNEWLINE;
		sp++;
	}
#endif

	wxputl (Winner, sbuf, attributes, TRUE);
}
