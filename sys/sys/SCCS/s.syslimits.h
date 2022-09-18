h43449
s 00002/00002/00026
d D 8.1 93/06/02 19:55:36 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00018/00010
d D 7.5 93/05/04 08:59:36 bostic 5 4
c fold rest of POSIX 1003.1, 1003.2 configurable system variables into sysctl
e
s 00009/00000/00019
d D 7.4 91/02/04 17:49:58 bostic 4 3
c add first pass at POSIX.2 values
e
s 00001/00011/00018
d D 7.3 90/06/28 22:00:55 bostic 3 2
c new copyright notice
e
s 00001/00001/00028
d D 7.2 89/02/16 14:14:46 bostic 2 1
c add real max link count
e
s 00029/00000/00000
d D 7.1 89/02/16 14:11:48 bostic 1 0
c system limits for POSIX 1003.1; included by include/limits.h
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 5
#define	ARG_MAX		20480	/* max bytes for an exec function */
#define	CHILD_MAX	40	/* max simultaneous processes */
D 2
#define	LINK_MAX	8	/* max file link count */
E 2
I 2
#define	LINK_MAX	32767	/* max file link count */
E 2
#define	MAX_CANON	255	/* max bytes in terminal canonical input line */
#define	MAX_INPUT	255	/* max bytes in terminal input */
#define	NAME_MAX	255	/* max number of bytes in a file name */
#define	NGROUPS_MAX	16	/* max number of supplemental group id's */
#define	OPEN_MAX	64	/* max open files per process */
#define	PATH_MAX	1024	/* max number of bytes in pathname */
#define	PIPE_BUF	512	/* max number of bytes for atomic pipe writes */
E 5
I 5
#define	ARG_MAX			20480	/* max bytes for an exec function */
#define	CHILD_MAX		   40	/* max simultaneous processes */
#define	LINK_MAX		32767	/* max file link count */
#define	MAX_CANON		  255	/* max bytes in term canon input line */
#define	MAX_INPUT		  255	/* max bytes in terminal input */
#define	NAME_MAX		  255	/* max bytes in a file name */
#define	NGROUPS_MAX		   16	/* max supplemental group id's */
#define	OPEN_MAX		   64	/* max open files per process */
#define	PATH_MAX		 1024	/* max bytes in pathname */
#define	PIPE_BUF		  512	/* max bytes for atomic pipe writes */
E 5
I 4

D 5
#define	BC_BASE_MAX	99	/* max ibase/obase values allowed by bc(1) */
#define	BC_DIM_MAX	2048	/* max array elements allowed by bc(1) */
#define	BC_SCALE_MAX	99	/* max scale value allowed by bc(1) */
#define	BC_STRING_MAX	1000	/* max const string length allowed by bc(1) */
#define	EQUIV_CLASS_MAX	2	/* max weights for order keyword; see locale */
#define	EXPR_NEST_MAX	32	/* max expressions nested in expr(1) */
#define	LINE_MAX	2048	/* max length in bytes of an input line */
#define	RE_DUP_MAX	255	/* max repeated RE's using interval notation */
E 5
I 5
#define	BC_BASE_MAX		   99	/* max ibase/obase values in bc(1) */
#define	BC_DIM_MAX		 2048	/* max array elements in bc(1) */
#define	BC_SCALE_MAX		   99	/* max scale value in bc(1) */
#define	BC_STRING_MAX		 1000	/* max const string length in bc(1) */
#define	COLL_WEIGHTS_MAX	    0	/* max weights for order keyword */
#define	EXPR_NEST_MAX		   32	/* max expressions nested in expr(1) */
#define	LINE_MAX		 2048	/* max bytes in an input line */
#define	RE_DUP_MAX		  255	/* max RE's in interval notation */
E 5
E 4
E 1
