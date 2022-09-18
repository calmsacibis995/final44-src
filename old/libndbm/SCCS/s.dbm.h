h51311
s 00001/00001/00028
d D 5.5 91/03/12 09:47:12 bostic 9 8
c ANSI
e
s 00001/00011/00028
d D 5.4 90/06/01 15:36:52 bostic 8 7
c new copyright notice
e
s 00006/00000/00033
d D 5.3 89/07/25 15:12:20 jak 7 3
c Fix page block size at 1024 (what it always has been) preparatory to
c including ndbm.h, which would otherwise define it to be 4096.
e
s 00006/00000/00033
d R 5.3 89/07/25 15:11:18 jak 6 3
c Define page block size to 1024 (what it always has been) preparatory to
c including ndbm.h, which would otherwise define it to be 4096.
e
s 00006/00000/00033
d R 5.3 89/07/19 08:30:52 jak 5 3
c fix PBLKSIZ at old value preparatory to changing PBLKSIZ in ndbm.h
e
s 00007/00000/00033
d R 5.3 89/07/18 14:10:24 jak 4 3
c fix PBLKSIZ at old value preparatory to changing PBLKSIZ in ndbm.h
e
s 00014/00009/00019
d D 5.2 89/05/24 11:11:45 bostic 3 2
c done from scratch by Robert Elz; add Berkeley specific copyright
e
s 00018/00023/00010
d D 5.1 86/03/27 15:21:51 bloom 2 1
c add copyright
c
c >> A lot more got done on this delta -- this is when the new stuff by
c >> Robert Elz that used ndbm got checked in.  Keith Bostic.
e
s 00033/00000/00000
d D 4.1 83/05/03 13:47:56 sam 1 0
c date and time created 83/05/03 13:47:56 by sam
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
/*
D 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 3
 *
I 3
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 *
E 3
 *	%W% (Berkeley) %G%
 */
E 2

D 2
#define	PBLKSIZ	1024
#define	DBLKSIZ	4096
#define	BYTESIZ	8
E 2
I 2
#ifndef NULL
/*
 * this is lunacy, we no longer use it (and never should have
 * unconditionally defined it), but, this whole file is for
 * backwards compatability - someone may rely on this.
 */
E 2
#define	NULL	((char *) 0)
I 2
#endif
E 2

I 7
/*
 * Pre-define the page block size to be the old dbm size.
 */

#define PBLKSIZ 1024

E 7
D 2
long	bitno;
long	maxbno;
long	blkno;
long	hmask;
E 2
I 2
D 9
#include <ndbm.h>
E 9
I 9
#include "ndbm.h"
E 9
E 2

D 2
char	pagbuf[PBLKSIZ];
char	dirbuf[DBLKSIZ];

int	dirf;
int	pagf;
int	dbrdonly;

typedef	struct
{
	char	*dptr;
	int	dsize;
} datum;

E 2
datum	fetch();
D 2
datum	makdatum();
E 2
datum	firstkey();
datum	nextkey();
I 2
D 3
#if 0
datum	makdatum();
E 2
datum	firsthash();
long	calchash();
long	hashinc();
D 2

E 2
I 2
#endif
E 3
E 2
E 1
