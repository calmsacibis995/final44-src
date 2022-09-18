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

/* out of raw mode */

cook ()
{
	/* First, return the terminal to a sane state */

	vputch (0);		/* Turn off all of the attributes */
	if (osert)
		unsert ();

	if (VEXIT)
	{
#ifdef VT_TERMINFO
		extern int e_putch ();

		tputs (VEXIT, 1, e_putch);
#else
		eprintf (VEXIT);
#endif
	}

	fflush (stdout);		/* force output */
	cp_stty (STTYNORM);
}
