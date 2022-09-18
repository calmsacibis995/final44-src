h59614
s 00002/00002/00022
d D 8.1 93/06/10 22:30:25 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00000/00000
d D 7.1 92/12/13 03:50:30 akito 1 0
c date and time created 92/12/13 03:50:30 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * status.h -- status code table for internal commands
 * by A.Fujita, FEB-02-1992
 */


#define ST_NORMAL	0
#define ST_EXIT		-1
#define ST_NOTFOUND	-2

#define ST_ERROR	1
E 1
