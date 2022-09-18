h44993
s 00008/00005/00059
d D 5.2 91/04/12 15:23:36 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00057
d D 5.1 85/06/07 23:57:50 kre 2 1
c Add copyright
e
s 00058/00000/00000
d D 1.1 85/05/21 20:09:07 libs 1 0
c date and time created 85/05/21 20:09:07 by libs
e
u
U
t
T
I 1
D 3
/*
D 2
char id_wfi[] = "%W%";
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 3
E 2
 *
I 2
D 3
 *	%W%	%G%
E 3
I 3
 * %sccs.include.proprietary.c%
E 3
 */
I 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

/*
E 2
 * internal (character array) i/o: write formatted, sequential and direct
 */

#include "fio.h"

extern int w_ed(),w_ned();
extern int z_wnew(), z_putc(), z_tab();

LOCAL
c_wfi()
{
	reading = NO;
	doed=w_ed;
	doned=w_ned;
	putn=z_putc;
	doend = donewrec = z_wnew;
	dorevert = z_wnew;
	dotab = z_tab;
}

s_wsfi(a) icilist *a;
{
	int n;

	c_wfi();
	if( n = c_si(a) ) return (n);
	if(pars_f()) err(errflag,F_ERFMT,"wsfio")
	fmt_bg();
	return( OK );
}

s_wdfi(a) icilist *a;
{
	int n;

	c_wfi();
	if( n = c_di(a) ) return (n) ;
	if(pars_f()) err(errflag,F_ERFMT,"wdfio")
	fmt_bg();
	return( OK );
}

e_wsfi()
{
	int n;
	n = en_fio();
	fmtbuf = NULL;
	return(n);
}


e_wdfi()
{
	return(e_wsfi());
}
E 1
