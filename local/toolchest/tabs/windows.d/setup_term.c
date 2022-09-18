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

/*	contains terminal dependencies for initializing terminal */

setup_term()
{
	if (SCINIT)
	{
#ifdef VT_TERMINFO
		extern int e_putch ();
		tputs (SCINIT, 1, e_putch);
#undef clear
#undef refresh
#endif VT_TERMINFO
#ifdef TERMCAP
		putpad (SCINIT);		/* initialize screen */
#endif TERMCAP
#ifndef TERMCAP
#ifndef VT_TERMINFO
		eprintf (SCINIT);/* initialize screen */
#endif VT_TERMINFO
#endif TERMCAP
	}
	clear();
#ifndef TERMCAP
	refresh ();
#endif TERMCAP
}
