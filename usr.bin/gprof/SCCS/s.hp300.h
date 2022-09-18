h58307
s 00002/00002/00016
d D 8.1 93/06/06 14:46:29 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00000/00000
d D 5.1 91/04/18 14:39:25 donn 1 0
c date and time created 91/04/18 14:39:25 by donn
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

    /*
     *	offset (in bytes) of the code from the entry address of a routine.
     *	(see asgnsamples for use and explanation.)
     */
#define OFFSET_OF_CODE	0
#define	UNITS_TO_CODE	(OFFSET_OF_CODE / sizeof(UNIT))

enum opermodes { dummy };
typedef enum opermodes	operandenum;
E 1
