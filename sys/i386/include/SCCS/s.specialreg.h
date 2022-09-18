h07365
s 00002/00002/00017
d D 8.1 93/06/11 15:48:41 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00000/00010
d D 7.1 91/05/09 23:16:52 bostic 2 1
c new copyright; att/bsd/shared
e
s 00010/00000/00000
d D 1.1 91/01/15 14:53:52 william 1 0
c date and time created 91/01/15 14:53:52 by william
e
u
U
t
T
I 2
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
 * 386 Special registers:
 */

#define	CR0_PE	0x00000001	/* Protected mode Enable */
#define	CR0_MP	0x00000002	/* "Math" Present (e.g. npx), wait for it */
#define	CR0_EM	0x00000004	/* EMulate NPX, e.g. trap, don't execute code */
#define	CR0_TS	0x00000008	/* Process has done Task Switch, do NPX save */
#define	CR0_ET	0x00000010	/* 32 bit (if set) vs 16 bit (387 vs 287) */
#define	CR0_PG	0x80000000	/* Paging Enable */
E 1
