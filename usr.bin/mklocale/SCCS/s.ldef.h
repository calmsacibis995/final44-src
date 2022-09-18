h02690
s 00002/00002/00025
d D 8.1 93/06/06 15:33:10 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00000/00000
d D 5.1 93/05/30 15:44:11 bostic 1 0
c date and time created 93/05/30 15:44:11 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Paul Borman at Krystal Technologies.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * This should look a LOT like a _RuneEntry
 */
typedef struct rune_list {
    rune_t		min;
    rune_t 		max;
    rune_t 		map;
    u_long		*types;
    struct rune_list	*next;
} rune_list;

typedef struct rune_map {
    u_long		map[_CACHED_RUNES];
    rune_list		*root;
} rune_map;
E 1
