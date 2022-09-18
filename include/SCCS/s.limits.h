h16017
s 00003/00000/00036
d D 8.2 94/01/04 14:53:05 bostic 11 10
c add _POSIX_SSIZE_MAX, _POSIX_STREAM_MAX, _POSIX_TZNAME_MAX
e
s 00002/00002/00034
d D 8.1 93/06/02 20:05:41 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00031
d D 5.9 91/04/03 16:12:58 bostic 9 8
c protect all user-level include files against reinclusion
e
s 00001/00001/00030
d D 5.8 90/12/02 11:41:23 bostic 8 7
c machine/machlimits.h -> machine/limits.h
e
s 00009/00002/00022
d D 5.7 90/11/01 09:26:02 bostic 7 6
c first cut at adding POSIX.2 limits (needed _POSIX2_LINE_MAX)
e
s 00002/00002/00024
d D 5.6 90/06/22 18:32:08 bostic 6 5
c make LINE_MAX real, give it an obscure name
e
s 00001/00011/00025
d D 5.5 90/06/01 13:59:09 bostic 5 4
c new copyright notice
e
s 00004/00000/00032
d D 5.4 89/12/20 16:16:16 bostic 4 3
c add LINE_MAX for POSIX 1003.2
e
s 00011/00000/00021
d D 5.3 89/02/16 13:58:10 bostic 3 2
c add POSIX 1003.1 defined limits
e
s 00001/00011/00020
d D 5.2 89/02/16 13:56:10 bostic 2 1
c move kernel stuf to h/syslimits.h
e
s 00031/00000/00000
d D 5.1 89/02/15 18:29:11 bostic 1 0
c date and time created 89/02/15 18:29:11 by bostic
e
u
U
t
T
I 1
/*
D 10
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

I 9
#ifndef _LIMITS_H_
#define	_LIMITS_H_

E 9
I 3
#define	_POSIX_ARG_MAX		4096
#define	_POSIX_CHILD_MAX	6
#define	_POSIX_LINK_MAX		8
#define	_POSIX_MAX_CANON	255
#define	_POSIX_MAX_INPUT	255
#define	_POSIX_NAME_MAX		14
#define	_POSIX_NGROUPS_MAX	0
#define	_POSIX_OPEN_MAX		16
#define	_POSIX_PATH_MAX		255
#define	_POSIX_PIPE_BUF		512
I 11
#define	_POSIX_SSIZE_MAX	32767
#define	_POSIX_STREAM_MAX	8
#define	_POSIX_TZNAME_MAX	3
E 11

I 7
#define	_POSIX2_BC_BASE_MAX	99
#define	_POSIX2_BC_DIM_MAX	2048
#define	_POSIX2_BC_SCALE_MAX	99
#define	_POSIX2_BC_STRING_MAX	1000
#define	_POSIX2_EQUIV_CLASS_MAX	2
#define	_POSIX2_EXPR_NEST_MAX	32
#define	_POSIX2_LINE_MAX	2048
#define	_POSIX2_RE_DUP_MAX	255

E 7
E 3
D 8
#include <machine/machlimits.h>
E 8
I 8
#include <machine/limits.h>
E 8
D 2

#define	ARG_MAX		4096	/* max bytes for an exec function */
#define	CHILD_MAX	6	/* max simultaneous processes */
#define	OPEN_MAX	16	/* max open files per process */
#define	LINK_MAX	8	/* max file link count */
#define	MAX_CANON	255	/* max bytes in terminal canonical input line */
#define	MAX_INPUT	255	/* max bytes in terminal input */
#define	NAME_MAX	14	/* max number of bytes in a file name */
#define	PATH_MAX	255	/* max number of bytes in pathname */
#define	PIPE_BUF	512	/* max number of bytes for atomic pipe writes */
#define	NGROUPS_MAX	0	/* max number of supplemental group id's */
E 2
I 2
#include <sys/syslimits.h>
I 9

#endif /* !_LIMITS_H_ */
E 9
I 4
D 7

D 6
#ifndef _POSIX_SOURCE
#define	LINE_MAX		2048
E 6
I 6
#define	_BSD_LINE_MAX		2048
E 7
E 6
D 6
#endif
E 6
E 4
E 2
E 1
