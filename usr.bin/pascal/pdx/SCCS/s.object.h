h41777
s 00002/00002/00029
d D 8.1 93/06/06 15:37:02 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00026
d D 5.3 91/04/16 15:42:36 bostic 6 5
c new copyright; att/bsd/shared
e
s 00002/00002/00028
d D 5.2 88/01/03 00:33:22 bostic 5 4
c neither K&R or ANSI C allow untyped function declarations
e
s 00007/00003/00023
d D 5.1 85/06/06 16:09:05 dist 4 3
c Add copyright
e
s 00000/00003/00026
d D 1.3 82/01/19 01:35:24 linton 3 2
c removed SIZELOC and BASEADDR, now "objfmt.h" is used
e
s 00001/00001/00028
d D 1.2 82/01/18 22:15:06 linton 2 1
c sccsid
e
s 00029/00000/00000
d D 1.1 82/01/18 19:02:43 linton 1 0
c date and time created 82/01/18 19:02:43 by linton
e
u
U
t
T
I 1
D 4
/* Copyright (c) 1982 Regents of the University of California */

D 2
static char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
/* static char sccsid[] = "%Z%%M% %I% %G%"; */
E 4
I 4
D 6
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 7
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */
E 4
E 2

/*
 * Object module definitions.
 *
 * The object module is the interface to the object file; in particular
 * it contains the routines that read symbol and line number information.
 */

char *objname;			/* name of object file */
int objsize;			/* size of object code */

struct {
	unsigned int stringsize;	/* size of the dumped string table */
	unsigned int nsyms;		/* number of symbols */
	unsigned int nfiles;		/* number of files */
	unsigned int nlines;		/* number of lines */
} nlhdr;

char *stringtab;	/* string table */
char *dotpfile;		/* name of compiled file */

D 3
#define SIZELOC 1016	/* location of objsize in obj file */
#define BASEADDR 1024	/* beginning of object code */

E 3
D 5
readobj();		/* read in the object file */
objfree();		/* release storage for object file information */
E 5
I 5
int readobj();		/* read in the object file */
int objfree();		/* release storage for object file information */
E 5
E 1
