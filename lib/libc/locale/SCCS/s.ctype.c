h51064
s 00005/00000/00041
d D 8.2 94/01/21 17:02:52 bostic 16 15
c add USL's copyright notice
e
s 00002/00002/00039
d D 8.1 93/06/04 12:42:53 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00003/00031
d D 5.9 93/05/27 13:37:16 bostic 14 13
c put a backward compatible ctype in place, for old binaries
e
s 00002/00000/00032
d D 5.8 92/03/15 23:09:32 bostic 13 12
c too many libraries know about _ctype_ for it to disappear
e
s 00001/00001/00031
d D 5.7 92/03/12 17:31:51 bostic 12 11
c use double underscores for ANSI C
e
s 00001/00011/00031
d D 5.6 90/06/01 14:09:31 bostic 11 10
c new copyright notice
e
s 00019/00002/00023
d D 5.5 89/05/27 10:29:07 bostic 10 9
c Berkeley specific copyright
e
s 00002/00002/00023
d D 5.4 86/03/09 19:45:37 donn 9 8
c added LIBC_SCCS condition for sccs ids
e
s 00001/00001/00024
d D 5.3 85/09/11 17:04:39 bloom 8 7
c fix iscntrl instead of the manual page
e
s 00001/00001/00024
d D 5.2 85/09/05 10:02:30 bloom 7 6
c isprint(space) should be true
e
s 00004/00001/00021
d D 5.1 85/06/05 12:12:57 mckusick 6 5
c Add copyright
e
s 00001/00001/00021
d D 4.4 85/03/01 15:16:51 karels 5 4
c so we change the manual?
e
s 00001/00001/00021
d D 4.3 85/02/04 11:01:12 serge 4 2
c changed size of _ctype_[] to 257 (EOF, '\0' ... '\377')
e
s 00001/00001/00021
d R 4.3 85/02/03 18:23:24 serge 3 2
c increased size of _ctype_[] to 256
e
s 00001/00001/00021
d D 4.2 83/07/08 23:03:36 sam 2 1
c space is a printing character according to the manual
e
s 00022/00000/00000
d D 4.1 80/12/21 16:39:35 wnj 1 0
c date and time created 80/12/21 16:39:35 by wnj
e
u
U
t
T
I 10
/*
D 15
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 16
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 16
E 15
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
 */

E 10
I 1
D 6
/* %W% (Berkeley) %G% */
E 6
I 6
D 9
#ifndef lint
E 9
I 9
#if defined(LIBC_SCCS) && !defined(lint)
E 9
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
D 10
#endif LIBC_SCCS and not lint
E 10
I 10
#endif /* LIBC_SCCS and not lint */
E 10
E 9

E 6
D 10
#include	<ctype.h>
E 10
I 10
D 14
#include <ctype.h>
E 14
I 14
#define	_U	0x01
#define	_L	0x02
#define	_N	0x04
#define	_S	0x08
#define	_P	0x10
#define	_C	0x20
#define	_X	0x40
#define	_B	0x80
E 14
E 10

I 13
D 14
char *_ctype_ = __ctype;		/* Backward compatibility. */

E 14
E 13
D 4
char _ctype_[] = {
E 4
I 4
D 12
char _ctype_[1 + 256] = {
E 12
I 12
char __ctype[1 + 256] = {
E 12
E 4
	0,
	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,
D 8
	_C,	_S,	_S,	_S,	_S,	_S,	_C,	_C,
E 8
I 8
	_C,	_C|_S,	_C|_S,	_C|_S,	_C|_S,	_C|_S,	_C,	_C,
E 8
	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,
	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,
D 2
	_S,	_P,	_P,	_P,	_P,	_P,	_P,	_P,
E 2
I 2
D 5
	_S|_P,	_P,	_P,	_P,	_P,	_P,	_P,	_P,
E 5
I 5
D 7
	_S,	_P,	_P,	_P,	_P,	_P,	_P,	_P,
E 7
I 7
	_S|_B,	_P,	_P,	_P,	_P,	_P,	_P,	_P,
E 7
E 5
E 2
	_P,	_P,	_P,	_P,	_P,	_P,	_P,	_P,
	_N,	_N,	_N,	_N,	_N,	_N,	_N,	_N,
	_N,	_N,	_P,	_P,	_P,	_P,	_P,	_P,
	_P,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U,
	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U,
	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U,
	_U,	_U,	_U,	_P,	_P,	_P,	_P,	_P,
	_P,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L,
	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L,
	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L,
	_L,	_L,	_L,	_P,	_P,	_P,	_P,	_C
};
I 14

char *_ctype_ = __ctype;		/* Backward compatibility. */
E 14
E 1
