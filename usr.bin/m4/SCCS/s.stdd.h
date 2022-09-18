h14069
s 00002/00002/00028
d D 8.1 93/06/06 15:04:43 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00029
d D 5.2 91/11/20 16:27:15 bostic 2 1
c add affiliation for Oz
e
s 00027/00000/00000
d D 5.1 91/09/03 11:43:34 bostic 1 0
c New version from Oz Yigit
e
u
U
t
T
I 1
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
 * This code is derived from software contributed to Berkeley by
D 2
 * Ozan Yigit.
E 2
I 2
 * Ozan Yigit at York University.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * standard defines
 */

#define max(a,b) ((a) > (b)? (a): (b))
#define min(a,b) ((a) < (b)? (a): (b))

#define iswhite(c) ((c) == ' ' || (c) == '\t')

/* 
 * STREQ is an optimised strcmp(a,b)==0 
 * STREQN is an optimised strncmp(a,b,n)==0; assumes n > 0 
 */
#define STREQ(a, b) ((a)[0] == (b)[0] && strcmp(a, b) == 0)
#define STREQN(a, b, n) ((a)[0] == (b)[0] && strncmp(a, b, n) == 0)

#define YES 1
#define NO 0
E 1
