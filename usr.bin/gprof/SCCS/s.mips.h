h13938
s 00002/00002/00022
d D 8.1 93/06/06 14:46:40 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00000/00000
d D 5.1 93/03/08 19:21:06 ralph 1 0
c date and time created 93/03/08 19:21:06 by ralph
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley. Modified by Ralph Campbell for mips.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * From: @(#)sparc.h	5.1 (Berkeley) 7/8/92
 */

/*
 * offset (in bytes) of the code from the entry address of a routine.
 * (see asgnsamples for use and explanation.)
 */
#define OFFSET_OF_CODE	0
#define	UNITS_TO_CODE	(OFFSET_OF_CODE / sizeof(UNIT))

enum opermodes { dummy };
typedef enum opermodes	operandenum;
E 1
