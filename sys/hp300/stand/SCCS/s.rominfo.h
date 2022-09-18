h52972
s 00002/00002/00039
d D 8.1 93/06/10 21:47:39 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00041/00000/00000
d D 7.1 90/05/08 22:45:56 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: rominfo.h 1.2 88/05/24$
 *
 *	%W% (Berkeley) %G%
 */

#define ROMADDR	0xFFFFF000

struct jmpvec {
	short op;	/* jmp instruction */
	long  addr;	/* address */
};

struct rominfo {
	char p1[0xDC0];
	short boottype;		/* ??                           (FFFFFDC0) */
	char  name[10];		/* HP system name, e.g. SYSHPUX (FFFFFDC2) */
	short p2;		/* ??                           (FFFFFDCC) */
	long  lowram;		/* lowest useable RAM location  (FFFFFDCE) */
	char  p3[0x100];	/* ??                           (FFFFFDD2) */
	char  sysflag;		/* HP system flags              (FFFFFED2) */
	char  p4;		/* ??                           (FFFFFED3) */
	long  rambase;		/* physaddr of lowest RAM       (FFFFFED4) */
	char  ndrives;		/* number of drives             (FFFFFED8) */
	char  p5;		/* ??                           (FFFFFED9) */
	char  sysflag2;		/* more system flags            (FFFFFEDA) */
	char  p6;		/* ??                           (FFFFFEDB) */
	long  msus;		/* ??                           (FFFFFEDC) */
	struct jmpvec jvec[48];	/* jump vectors                 (FFFFFEE0) */
};

E 1
