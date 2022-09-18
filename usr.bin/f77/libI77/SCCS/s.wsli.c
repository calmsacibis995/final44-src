h17716
s 00008/00005/00026
d D 5.2 91/04/12 15:23:40 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00024
d D 5.1 85/06/07 23:59:46 kre 2 1
c Add copyright
e
s 00025/00000/00000
d D 1.1 85/05/22 21:24:56 libs 1 0
c date and time created 85/05/22 21:24:56 by libs
e
u
U
t
T
I 1
D 3
/*
D 2
char id_wsli[] = "%W%";
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
 * internal (character array) i/o: write sequential list
 */

#include "fio.h"
#include "lio.h"

extern int l_write(), z_putc(), z_wnew();

s_wsli(a) icilist *a;
{
	reading = NO;
	putn = z_putc;
	lioproc = l_write;
	line_len = a->icirlen;
	return(c_li(a));
}

e_wsli()
{	fmtbuf = NULL;
	reclen = recpos;
	return(z_wnew());
}
E 1
