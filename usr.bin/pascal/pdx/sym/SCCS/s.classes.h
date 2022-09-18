h46478
s 00002/00002/00036
d D 8.1 93/06/06 15:45:34 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00033
d D 5.2 91/04/16 15:03:16 bostic 4 3
c new copyright; att/bsd/shared
e
s 00007/00003/00030
d D 5.1 85/06/06 16:19:54 dist 3 2
c Add copyright
e
s 00001/00001/00032
d D 1.2 82/01/18 22:07:22 linton 2 1
c sccsid
e
s 00033/00000/00000
d D 1.1 82/01/18 19:21:13 linton 1 0
c date and time created 82/01/18 19:21:13 by linton
e
u
U
t
T
I 1
D 3
/* Copyright (c) 1982 Regents of the University of California */

D 2
static char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
/* static char sccsid[] = "%Z%%M% %I% %G%"; */
E 3
I 3
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 5
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */
E 3
E 2

/*
 * namelist classes
 */

#define BADUSE 0
#define CONST 1
#define TYPE 2
#define VAR 3
#define ARRAY 4
#define PTRFILE 5
#define RECORD 6
#define FIELD 7
#define PROC 8
#define FUNC 9
#define FVAR 10
#define REF 11
#define PTR 12
#define FILET 13
#define SET 14
#define RANGE 15
#define LABEL 16
#define WITHPTR 17
#define SCAL 18
#define STR 19
#define PROG 20
#define IMPROPER 21
#define VARNT 22
#define FPROC 23
#define FFUNC 24
E 1
