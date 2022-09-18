h63274
s 00012/00002/00015
d D 5.2 91/04/12 15:16:01 bostic 2 1
c new copyright; att/bsd/shared
e
s 00017/00000/00000
d D 5.1 86/11/03 20:00:10 mckusick 1 0
c from CCI
e
u
U
t
T
I 1
D 2
/*
 *	%W% (Berkeley) %G%
E 2
I 2
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.proprietary.c%
E 2
 */
I 2

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

/*
 *	@(#)no_lg.c	1.2
 *
 *	ld -lg ...
 * then /usr/lib/libg.a is loaded and defines _dbsubc as non-zero.
 * Otherwise, this is loaded defining it as zero.
 * in main.c, f77_abort() uses this to decide whether or not to call
 * abort to terminate.
 */

char id_no_lg[] = "@(#)no_lg.c	5.2";

int _dbsubc = 0;
E 1
