/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)rsli.c	5.2 (Berkeley) 4/12/91";
#endif /* not lint */

/*
 * internal (character array) i/o: read sequential list
 */

#include "fio.h"
#include "lio.h"

extern int l_read(), z_getc(), z_ungetc();

s_rsli(a) icilist *a;
{
	reading = YES;
	lioproc = l_read;
	getn = z_getc;
	ungetn = z_ungetc;
	l_first = YES;
	lcount = 0;
	lquit = NO;
	return(c_li(a));
}

e_rsli()
{	fmtbuf = NULL;
	return(OK);
}
