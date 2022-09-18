h05615
s 00002/00002/00029
d D 8.1 93/06/06 15:37:11 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00026
d D 5.3 91/04/16 15:42:38 bostic 5 4
c new copyright; att/bsd/shared
e
s 00006/00006/00024
d D 5.2 88/01/03 00:33:24 bostic 4 3
c neither K&R or ANSI C allow untyped function declarations
e
s 00007/00003/00023
d D 5.1 85/06/06 16:10:55 dist 3 2
c Add copyright
e
s 00001/00001/00025
d D 1.2 82/01/18 22:15:12 linton 2 1
c sccsid
e
s 00026/00000/00000
d D 1.1 82/01/18 19:02:46 linton 1 0
c date and time created 82/01/18 19:02:46 by linton
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
D 5
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 6
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */
E 3
E 2

/*
 * Definitions for the runtime environment.
 *
 * In general, runtime organization is language, machine, and
 * even compiler dependent.
 */

BOOLEAN isactive();		/* tell if a symbol is currently active */
ADDRESS entry_addr();		/* entry address of current proc/func */
ADDRESS entry_point();		/* point where environment is setup */
ADDRESS return_addr();		/* return address of current proc/func */
ADDRESS caller_addr();		/* entry of caller of current proc/func */
D 4
where();			/* print out currently active procedures */
dump();				/* dump the world */
callproc();			/* call a procedure */
procreturn();			/* return from a "call"-ed procedure */
E 4
I 4
int where();			/* print out currently active procedures */
int dump();			/* dump the world */
int callproc();			/* call a procedure */
int procreturn();		/* return from a "call"-ed procedure */
E 4
ADDRESS address();		/* address of a variable */
ADDRESS firstline();		/* address of first line in a procedure */
D 4
findbeginning();		/* find address of beginning of a procedure */
runtofirst();			/* step to first line in current procedure */
E 4
I 4
int findbeginning();		/* find address of beginning of a procedure */
int runtofirst();		/* step to first line in current procedure */
E 4
ADDRESS lastaddr();		/* address of last line in program */
ADDRESS fparamaddr();		/* entry address of a function parameter */
E 1
