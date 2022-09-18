h60011
s 00005/00000/00036
d D 8.2 94/01/21 16:53:01 bostic 7 6
c add USL's copyright notice
e
s 00002/00002/00034
d D 8.1 93/06/02 20:04:55 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00031
d D 5.4 91/04/03 16:04:07 bostic 5 4
c protect all user-level include files against reinclusion
e
s 00003/00001/00028
d D 5.3 91/03/12 11:36:58 bostic 4 3
c get the copyright notice right
e
s 00021/00014/00008
d D 5.2 91/01/17 18:23:04 bostic 3 2
c new version
e
s 00007/00001/00015
d D 5.1 85/05/30 09:34:56 dist 2 1
c Add copyright
e
s 00016/00000/00000
d D 4.1 83/05/03 13:47:51 sam 1 0
c date and time created 83/05/03 13:47:51 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
E 4
I 4
D 6
 * Copyright (c) 1991 The Regents of the University of California.
E 4
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 7
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 7
E 6
E 3
 *
I 3
 * This code is derived from software contributed to Berkeley by
 * Hugh Smith at The University of Guelph.
I 4
 *
 * %sccs.include.redist.c%
E 4
 *
E 3
 *	%W% (Berkeley) %G%
 */
E 2

I 5
#ifndef _AR_H_
#define	_AR_H_

E 5
D 3
#define	ARMAG	"!<arch>\n"
#define	SARMAG	8
E 3
I 3
/* Pre-4BSD archives had these magic numbers in them. */
#define	OARMAG1	0177555
#define	OARMAG2	0177545
E 3

D 3
#define	ARFMAG	"`\n"
E 3
I 3
#define	ARMAG		"!<arch>\n"	/* ar "magic number" */
#define	SARMAG		8		/* strlen(ARMAG); */
E 3

I 3
#define	AR_EFMT1	"#1/"		/* extended format #1 */

E 3
struct ar_hdr {
D 3
	char	ar_name[16];
	char	ar_date[12];
	char	ar_uid[6];
	char	ar_gid[6];
	char	ar_mode[8];
	char	ar_size[10];
	char	ar_fmag[2];
E 3
I 3
	char ar_name[16];		/* name */
	char ar_date[12];		/* modification time */
	char ar_uid[6];			/* user id */
	char ar_gid[6];			/* group id */
	char ar_mode[8];		/* octal file permissions */
	char ar_size[10];		/* size in bytes */
#define	ARFMAG	"`\n"
	char ar_fmag[2];		/* consistency check */
E 3
};
I 5

#endif /* !_AR_H_ */
E 5
E 1
