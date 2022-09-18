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

/* dcost -- calculate display cost of a string */

#ifdef VT_TERMINFO

static int lncnt;			/* Very nice Eby trick */
					/*  Used to count length of strings */
static
counter()
{
	lncnt++;
}

dcost(sp)
register char *sp;
{
	char *cp, *tparm();		/* string pointer */

	if (sp == NULL)			/* high cost for missing capability */
		return 1000;
	cp = tparm(sp, 10, 10);		/* expand a 'typical' example */
	lncnt = 0;
	tputs(cp, 1, counter);
	return lncnt;			/* return its length */
}

#else

dcost (sp)
register char  *sp;
{
	register int    dc;
	char    dcbuf[512];		/* buffer for string */

	if (sp == NULL)
		return (1000);		/* infinite cost for missing
					 * capability
					 */
#ifdef TERMCAP	
	dc = 0;
	while (*sp)
	{
		if (*sp++ != '%')
			dc++;
	}
	return (dc);
#else
	seprintf (dcbuf, sp, 10, 10);	/* expand a 'typical' example */
	return (lng (dcbuf));		/* return its length */

#endif	TERMCAP
}
#endif VT_TERMINFO
